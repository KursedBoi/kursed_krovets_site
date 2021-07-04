#include <stdint.h>

uint32_t rotl32(uint32_t x, int n) {
    return (x << n) | (x >> (32-n));
}

// Implement the pseudocode here
void scramble(uint32_t *a, uint32_t *b, uint32_t *c) 
{
	
}