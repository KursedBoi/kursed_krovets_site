#include <stdint.h>

void lrot(uint32_t* x, uint32_t n)
{
    *x = (*x << n) | (*x >> (32 - n));
}

void one_round(uint32_t *Aptr, uint32_t *Bptr, uint32_t k1, uint32_t k2) 
{
  //circles xor
  // squares addition
  //  rectangles left rotate
}