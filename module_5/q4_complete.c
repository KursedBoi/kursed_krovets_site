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

// Parse Flow 2 into 5 BIGNUMs, check p and q prime
int flow2_pqprime(void *p2) 
{
	uint8_t* buf = (uint8_t *)p2;
	uint16_t bytes[5];
	for(int i = 0; i < 5; i++)
	{
		bytes[i] = load_uint16_big(buf + (i*2));
	}

	BIGNUM* p = BN_bin2bn(buf + 10, bytes[0], NULL);
	BIGNUM* q = BN_bin2bn(buf + 10 + bytes[0], bytes[1], NULL);
	BN_CTX* ctx = BN_CTX_new();
	
	//BN_prime_checks_for_validation
	int res1 = BN_is_prime_ex(p, 32, ctx, NULL);
	int res2 = BN_is_prime_ex(q, 32, ctx, NULL);

	BN_CTX_free(ctx);
	BN_free(p);
	BN_free(q);
	if(res1 != 0 && res2 != 0)
		return 1;
	else
		return 0;
}
