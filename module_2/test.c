#include <openssl/evp.h>

// Errata from video: my "iv" constant initializer was only 15 bytes. Adding
// another 0 fixed it. Changing my buffer types from char to unsigned char
// made all warnings go away.

int main() {
    unsigned char pt[44] = "The quick brown fox jumps over the lazy dog";
    unsigned char ct[44];
    unsigned char pt2[44];
    unsigned char key[16] = {1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6};
    unsigned char iv[16] = {1,2,3,4,5,6,7,8,0,0,0,0,0,0,0,1};
    int len;
    int ct_bytes_written = 0;
    int pt_bytes_written = 0;

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, ct, &len, pt, 44);
    ct_bytes_written = ct_bytes_written + len;
    EVP_EncryptFinal_ex(ctx, ct + ct_bytes_written, &len);
    ct_bytes_written = ct_bytes_written + len;
    
    iv[15] = 1;  // Rest iv to initial value
    EVP_DecryptInit_ex(ctx, EVP_aes_128_ctr(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, pt2, &len, ct, 44);
    pt_bytes_written = pt_bytes_written + len;
    EVP_DecryptFinal_ex(ctx, pt2 + pt_bytes_written, &len);
    pt_bytes_written = pt_bytes_written + len;
    EVP_CIPHER_CTX_free(ctx);
    
    printf("%s\n", pt2);
    
    return 0;
}
