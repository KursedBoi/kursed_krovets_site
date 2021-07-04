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

}
