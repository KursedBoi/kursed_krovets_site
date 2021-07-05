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

// Parse Flow 2 into 5 pre-allocated BIGNUMs
void flow2_to_BN(void *p2, BIGNUM *p, BIGNUM *q, BIGNUM *g, BIGNUM *x, BIGNUM *a) 
{

}