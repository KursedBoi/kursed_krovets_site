#include <stdint.h>

// PASTE YOUR load_uint32_big function here
uint32_t load_uint32_big(void *p) 
{
	uint8_t *p8 = (uint8_t *) p;
	uint32_t a = p8[0];
	uint32_t b = p8[1];
	uint32_t c = p8[2];
	uint32_t d = p8[3];
	
	return (a << 24) | (b << 16) | (c << 8) | d;
}

// Treats p like an array of uint32_t and returns the sum of
// first nbytes/4 elements read big-endian
uint32_t sum32(void *p, int nbytes) 
{

}