#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>
#include <openssl/rand.h>

// Simulate first flow of key negotiation
// Write to p1: (2B BE s_a in 2000..4000) || (32B random)
void flow1(void *p1) 
{
  uint8_t* buf = (uint8_t *)p1;
	buf[0] = 0x09;
	buf[1] = 0x01;
	RAND_bytes(buf+2, 32);
}
