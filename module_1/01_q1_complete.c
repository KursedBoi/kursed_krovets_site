#include <stdint.h>

// Read the four bytes begining at p and assemble them big-endian
uint32_t load_uint32_big(void *p) 
{
	uint8_t *p8 = (uint8_t *) p;
	uint32_t a = p8[0];
	uint32_t b = p8[1];
	uint32_t c = p8[2];
	uint32_t d = p8[3];
	
	return (a << 24) | (b << 16) | (c << 8) | d;
}

