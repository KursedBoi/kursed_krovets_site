#include <openssl/bn.h>
#include <stdio.h>

void gcd (BIGNUM *x, BIGNUM *y) {

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