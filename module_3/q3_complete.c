#include <stdint.h>

// Sponge constants
#define R 16     // Rate: bytes of 'in' read per iteration
#define C 32     // Capacity: part of state that 'in' doesn't touch
#define B 48     // Block length

void prof_perm384(void *p);
/*
In the authentication chapter of our textbook you read about HMAC, which is a way of using a cryptographic hash function for 
message authentication. It was defined something like H(K || H(K || M)), where || is concatenation. It used a nested 
double-hash to avoid the length-extension attacks in MD5, SHA-1 and SHA-2. Since the sponge construction is immune to 
length extension attacks, double-hashing is not needed when using a hash function based on it. Thus a very simple 
authentication shceme such as H(K || M) where K is a fixed-length key and M is the data being authenticated works well for 
authentication tag generation.

If Alice and Bob know K and Eve does not, H's 2nd-preimage resistance means that noone can find a second M' that hashes to 
the same output at M. Also, because Eve does not know K, she cannot generate her own outputs that would pass a validation 
test by either Alice or Bob.

Implement perm384mac256(K, M) as perm384hash256(K || M) where K is 256 bits, M is any length, and the function returns 256 
bits. We want to avoid creating a large temporary buffer and copying K and M to it before calling the hash function. 
Instead use the logic of the prvious programming problem, but modify it to incorporate K into the hash before incorporating M.
*/
// Reads inbytes from in, 32 bytes from k, and writes 32 bytes to out
void perm384mac256(void *in, int inbytes, void *out, void *k) 
{
    uint8_t* data = (uint8_t *)in;
    uint8_t* output = (uint8_t *)out;
    uint8_t block[B];
    uint8_t* key = (uint8_t *)k;
    for(int i = 0; i < B; i++)
    {
        block[i] = 0;
    }
    for(int i = 0; i < 32; i+= R)
    {
        for(int j = 0; j < R; j++)
        {
            block[j] ^= key[i + j];
        }
        prof_perm384(block);
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