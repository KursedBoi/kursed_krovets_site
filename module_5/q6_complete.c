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

// Parse Flow 2 into 5 BIGNUMs, check x≠1 and (x^q mod p)=1
int flow2_x_ok(void *p2) 
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
	adder += bytes[2];
	BIGNUM* x = BN_bin2bn(buf + 10 + adder, bytes[3], NULL);
	BN_CTX* ctx = BN_CTX_new();
	BIGNUM* one = BN_new();
	BIGNUM* res = BN_new();
	BN_one(one);
	
	//must not be 0 to pass check
	int one_check = BN_cmp(x, one);

	//must be 0 to pass check
	BN_mod_exp(res, x, q, p, ctx);
	int op_check = BN_cmp(res, one);

	BN_free(res);
	BN_free(one);
	BN_free(p);
	BN_free(q);
	BN_free(g);
	BN_free(x);
	BN_CTX_free(ctx);
	if(one_check != 0 && op_check == 0)
		return 1;
	else
		return 0;
}
