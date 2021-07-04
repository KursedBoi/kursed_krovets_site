#include <stdint.h>

void swap(uint32_t *a, uint32_t *b) {
    uint32_t newb = *a;
    uint32_t newa = *b;
    *a = newa;
    *b = newb;
}

uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32-n));
}


// Implement the pseudocode here
void scramble(uint32_t *a, uint32_t *b, uint32_t *c) 
{
	uint32_t x = rotl32(*a, 24);
	uint32_t y = rotl32(*b, 9);
	uint32_t z = *c;
	*a = z ^ y ^ ((x&y) << 3);
	*b = y ^ x ^ ((x|z) << 1);
	*c = x ^ (z << 1) ^ ((y&z) << 2);
}

void perm384(void *p) 
{

}
