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

}