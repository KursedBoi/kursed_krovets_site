#include <stdint.h>

// Implement block cipher dst = perm384(k||0 xor src) xor k||0
// src and dst are both 48 bytes and k is 32 bytes
uint32_t rotl32(uint32_t x, int n);
void scramble(uint32_t *a, uint32_t *b, uint32_t *c);
void swap(uint32_t *a, uint32_t *b);
void perm384(void *p);
void increment(void *p);
int min(int a, int b);
void perm384bc_ctr(void *src, void *dst, int nbytes, void *n, void *k);

void perm384bc_ctr(void *src, void *dst, int nbytes, void *n, void *k) 
{
	uint8_t ctr[48];
	uint8_t output[48];
	uint8_t *x = (uint8_t *)src;
	uint8_t *y = (uint8_t *)dst;
	uint8_t *nonce = (uint8_t *)n;
	
	for(int i = 0; i < 48; i++)
	{
		if(i < 12)
			ctr[i] = *(nonce + i);
		else
			ctr[i] = 0;
		output[i] = 0;
	}
	
	while(nbytes > 0)
	{
		//we are counting from right to left with the function provided
		increment(ctr + 47);
		perm384bc(ctr, output, k);
		int count = min(48, nbytes);
		for(int i = 0; i < count; i++)
		{
			*(y + i) = output[i] ^ *(x + i);
		}
		x += count;
		y += count;
		nbytes -= count;
	}
}

void increment(void *p) 
{
    uint8_t *p8 = (uint8_t *)p;
    
    *p8 += 1;              // incement byte at p8
    
    //will handle the byte addition for us
    //if one byte is FF and we add, then the 1 will carry into the byte to the left
    while (*p8 == 0) 
    {     // if it wrapped to 0
        p8 -= 1;           // move pointer back 1 byte
        *p8 += 1;          // and increment that byte too
    }
}

int min(int a, int b) 
{ 
	if(b<a) 
		a=b; 
	return a; 
} 

// Implement block cipher dst = perm384(k||0 xor src) xor k||0
// src and dst are both 48 bytes and k is 32 bytes
void perm384bc(void *src, void *dst, void *k) 
{
	//our 48 byte array
	// first 8 elements are 256 bits
	uint32_t arr[12] = {0,0,0,0, 0,0,0,0, 0,0,0,0};
	
	//k'
	uint32_t *kp = (uint32_t *)k;
	
	//src is x
	uint32_t *x = (uint32_t *)src;
	
	//dst is y
	uint32_t *y = (uint32_t *)dst;
	
	//iterating through the first 256 bits of x
	for(int i = 0; i < 8; i++)
	{
		*(arr + i) = *(x + i) ^ *(kp + i);
	}
	
	//putting the last 128 bits of x into the last 128 bits of the array
	for(int i = 8; i < 12; i++)
	{
		*(arr + i) = *(x + i);
	}
	
	//passing x' into the perm384 function
	perm384(arr);
	
	//iterating through the first 256 bits of x'
	for(int i = 0; i < 8; i++)
	{
		*(y + i) = *(kp + i) ^ *(arr + i);
	}
	
	for(int i = 8; i < 12; i++)
	{
		*(y + i) = *(arr + i);
	}
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