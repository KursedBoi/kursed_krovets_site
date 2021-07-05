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
	//first 10 spots are byte lengths
	//the rest are our bignums separated by their respective byte-lengths
	uint8_t* buf = (uint8_t *)p2;

	uint16_t bytes[5];
	for(int i = 0; i < 5; i++)
	{
		bytes[i] = load_uint16_big(buf + (i * 2));
		//printf("bytes[%d] = %u\n", i, bytes[i]);
	}
	uint16_t adder = 0;
	BN_bin2bn(buf + 10, bytes[0], p);
	adder += bytes[0];
	BN_bin2bn(buf + 10 + adder, bytes[1], q);
	adder += bytes[1];
	BN_bin2bn(buf + 10 + adder, bytes[2], g);
	adder += bytes[2];
	BN_bin2bn(buf + 10 + adder, bytes[3], x);
	adder += bytes[3];
	BN_bin2bn(buf + 10 + adder, bytes[4], a);
}