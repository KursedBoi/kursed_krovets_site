#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

uint16_t load_uint16_big(void *p) 
{
	uint8_t *p8 = (uint8_t *) p;
	uint16_t a = p8[0];
	uint16_t b = p8[1];
	
	return (a << 8) | (b);
}

// Parse Flow 2 into 5 BIGNUMs, check q|(p-1), q≠1 and (g^q mod p)=1
int flow2_generator_ok(void *p2) 
{
	uint8_t* buf = (uint8_t *)p2;
	uint16_t bytes[5];
	for(int i = 0; i < 5; i++)
	{
		bytes[i] = load_uint16_big(buf + (i*2));
	}

	uint16_t adder = 0;
	BIGNUM* p = BN_bin2bn(buf + 10, bytes[0], NULL);
	adder = bytes[0];
	BIGNUM* q = BN_bin2bn(buf + 10 + adder, bytes[1], NULL);
	adder += bytes[1];
	BIGNUM* g = BN_bin2bn(buf + 10 + adder, bytes[2], NULL);
	BIGNUM* mod_res = BN_new();
	BIGNUM* zero = BN_new();
	BIGNUM* one = BN_new();
	BN_one(one);
	BN_CTX* ctx = BN_CTX_new();
	
	BN_sub(p, p, one);
	BN_nnmod(mod_res, p, q, ctx);
	BN_add(p,p,one);
	//must be 0 to pass the check
	int q_check = BN_cmp(mod_res, zero);

	//must not be 0 to pass the check
	int g_check = BN_cmp(g, one);

	BN_mod_exp(mod_res, g, q, p, ctx);
	//must be 0 to pass the check
	//char* mod = BN_bn2dec(mod_res);
	//printf("%s\n", mod);
	int one_check = BN_cmp(mod_res, one);

	BN_CTX_free(ctx);
	BN_free(p);
	BN_free(zero);
	BN_free(q);
	BN_free(g);
	BN_free(one);
	BN_free(mod_res);
	if(q_check == 0 && g_check != 0 && one_check == 0)
		return 1;
	else
		return 0;
}