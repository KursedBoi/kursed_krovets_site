#include <stdint.h>

// Sponge constants
#define R 16     // Rate: bytes of 'in' read per iteration
#define C 32     // Capacity: part of state that 'in' doesn't touch
#define B 48     // Block length

void prof_perm384(void *p);

/*
let block be 48 bytes of zero
let R=16 be the number of bytes of the rate part of the block
while data remaining is not less than R bytes
   xor next R bytes of data with the first R bytes of the block
   update block using perm384
Xor any remaining data into the beginning of the block
Xor 0b10000000 into the next byte (after the data) of the block
Xor 0b00000001 at byte index R-1 of the block
update block using perm384
output R bytes from beginning of block
update block using perm384
output R bytes from beginning of block
*/
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
            prof_perm384(block);
    }
    block[(inbytes % R)] ^= 0b10000000;
    block[R-1] ^= 0b00000001;
    prof_perm384(block);
    for(int i = 0; i < 16; i++)
    {
        output[i] = block[i];
    }
    prof_perm384(block);
    for(int i = 0; i < 16; i++)
    {
        output[16 + i] = block[i];
    }
}
