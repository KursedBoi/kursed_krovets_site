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

}
