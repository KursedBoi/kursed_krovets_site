#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "bn152.h"

// Return 0 if x>=p, x<1, or p not prime.
// Otherwise return 1 and write x's inverse to res
int find_inverse(BIGNUM *res, BIGNUM *x, BIGNUM *p) 
{
    uint8_t two_arr[1] = {0x02};
    BIGNUM* two = BN_bin2bn(two_arr, 1, NULL);
    BIGNUM* pminus = BN_new();
    BN_copy(pminus, p);
    BN_sub(pminus, pminus, two);
    BN_CTX* ctx = BN_CTX_new();
    
    BN_zero(two);
    int zero = BN_cmp(x, two);
    int gp = BN_cmp(x, p);
    int prime = BN_is_prime_ex(p, 32, ctx, NULL);
    //res is good
    BN_mod_exp(res, x, pminus, p, ctx);
    
    BN_CTX_free(ctx);
    BN_free(pminus);
    BN_free(two);
    if(zero > 0 && gp < 0 && prime == 1)
        return 1;
    else
        return 0;
}