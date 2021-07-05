#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bn152.h"

// Bob's RSA modulus
const static char *Bn = "EC91624BED3AFC5B9FD6D5A7B830999DC1B993560137368167B3719F04976C72"
                        "D9A685F8FDAD9815309901C00EF08641A28EC93ACA0BA05A73FD5CDCA28F76BF";
// Public exponent. Use BN_set_word to turn into a BIGNUM
const static uint32_t e =  0x10001;

// Concat flows 1 and 2 (through X) and hash
void prof_flow12_authb_hash(void *p1, void *p2, void* result);

// Concat flows 1 and 2 (through X) and hash. Verify that Auth_B
// is a signature from Bob of the hash.
int flow12_authb_verify(void *p1, void *p2) {

}
