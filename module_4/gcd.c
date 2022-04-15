#include <openssl/bn.h>
#include <stdio.h>

void gcd (BIGNUM *x, BIGNUM *y) {
  BN_CTX *ctx = BN_CTX_new();
  BIGNUM *t = BN_new(); 
  
  while( !(BN_is_zero(y)) ){
    BN_copy(t, y);
    BN_mod(y, x, y, ctx);
    ///y = x % y;
    BN_copy(x, t);
  }
  BN_free(t);
  BN_CTX_free(ctx);
}
 
int main ( int argc, char *argv[]){
  BIGNUM *a = BN_new();
  BIGNUM *b = BN_new();
  if  (argc > 2) {
    
    BN_dec2bn(&a, argv[1]);
    BN_dec2bn(&b, argv[2]);
    
  } else {
    exit(EXIT_FAILURE);
  }
  //  x  y
  gcd(a, b);
  char *s = BN_bn2dec(a);
  printf("%s\n", s);
  BN_free(a);
  BN_free(b);
  free(s); 
 
  return 0;
}