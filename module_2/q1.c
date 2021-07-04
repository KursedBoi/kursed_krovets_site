#include <stdint.h>

uint32_t rotl32(uint32_t x, int n);
void scramble(uint32_t *a, uint32_t *b, uint32_t *c);
void swap(uint32_t *a, uint32_t *b);
void perm384(void *p);

// Implement block cipher dst = perm384(k||0 xor src) xor k||0
// src and dst are both 48 bytes and k is 32 bytes
void perm384bc(void *src, void *dst, void *k) 
{

}

void perm384(void *p) 
{
	uint32_t *p32 = (uint32_t *)p;
	for(int round = 0; round < 24; round++)
	{
		//p32 is 4 bytes of memory, so 12 * 4 = 48
		scramble(p32+0, p32+4, p32+8);
		scramble(p32+1, p32+5, p32+9);
		scramble(p32+2, p32+6, p32+10);
		scramble(p32+3, p32+7, p32+11);
		if(round % 4 == 0)
		{
			swap(p32+0, p32+1);
			swap(p32+2, p32+3);
			*p32 = *p32 ^ (0x79379E00 ^ round);
		}
		if(round % 4 == 2)
		{
			swap(p32+0, p32+2);
			swap(p32+1, p32+3);
		}
	}
}

uint32_t rotl32(uint32_t x, int n) 
{
    return (x << n) | (x >> (32-n));
}

void scramble(uint32_t *a, uint32_t *b, uint32_t *c) 
{
	uint32_t x = rotl32(*a, 24);
	uint32_t y = rotl32(*b, 9);
	uint32_t z = *c;
	*a = z ^ y ^ ((x&y) << 3);
	*b = y ^ x ^ ((x|z) << 1);
	*c = x ^ (z << 1) ^ ((y&z) << 2);
}

void swap(uint32_t *a, uint32_t *b) 
{
    uint32_t newb = *a;
    uint32_t newa = *b;
    *a = newa;
    *b = newb;
}