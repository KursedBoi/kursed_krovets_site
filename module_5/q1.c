#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/rand.h>

// Simulate first flow of key negotiation
// Write to p1: (2B BE s_a in 2000..4000) || (32B random)
void flow1(void *p1) 
{

}
