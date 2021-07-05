#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Reads inbytes from in and writes 32 bytes to out
void perm384hash256(void *in, int inbytes, void *out);
void perm384(void *p);
void swap(uint32_t *a, uint32_t *b);
uint32_t rotl32(uint32_t x, int n);
void scramble(uint32_t *a, uint32_t *b, uint32_t *c);

uint16_t load_uint16_big(void *p) 
{
	uint8_t *p8 = (uint8_t *) p;
	uint16_t a = p8[0];
	uint16_t b = p8[1];
	
	return (a << 8) | (b);
}

// Concat flows 1 and 2 (through X) and hash
void flow12_authb_hash(void *p1, void *p2, void* result) 
{
	uint8_t* buf1 = (uint8_t *)p1;
	uint8_t* buf2 = (uint8_t *)p2;
	uint16_t bytes[5];
	uint16_t adder = 0;
	for(int i = 0; i < 5; i++)
	{
		bytes[i] = load_uint16_big(buf2 + (i*2));
		//not including auth_b
		if(i != 4)
		{
			adder += bytes[i];	
		}
	}

	int sz = 34 + adder + 10;
	uint8_t buf[sz];
	for(int i = 0; i < 34; i++)
	{
		buf[i] = *(buf1 + i);
	}
	for(int i = 0; i < adder; i++)
	{
		buf[34+i] = *(buf2 + i);
	}

	perm384hash256(buf, sz, result);
}

void perm384hash256(void *in, int inbytes, void *out) 
{
    uint8_t* data = (uint8_t *)in;
    uint8_t* output = (uint8_t *)out;
    uint8_t block[B];
    for(int i = 0; i < B; i++)
    {
        block[i] = 0;
    }
    int ex = 0;
    for(int i = 0; i < inbytes; i+= R)
    {
        //this loop also XORs the remaining data
        for(int j = 0; j < R; j++)
        {
            //we are out of data
            if((i + j) >= inbytes)
            {
                ex = 1;
                break;
            }
            block[j] ^= data[i + j];
        }
        if(ex == 0)
            perm384(block);
    }
    block[(inbytes % R)] ^= 0b10000000;
    block[R-1] ^= 0b00000001;
    perm384(block);
    for(int i = 0; i < 16; i++)
    {
        output[i] = block[i];
    }
    perm384(block);
    for(int i = 0; i < 16; i++)
    {
        output[16 + i] = block[i];
    }
}

void perm384(void *p) 
{
	uint32_t *p32 = (uint32_t *)p;
	for(int round = 0; round < 24; round++)
	{
		//p32 is 4 bytes of memory, so 12 * 4 = 48
		scramble(p32, p32+4, p32+8);
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
