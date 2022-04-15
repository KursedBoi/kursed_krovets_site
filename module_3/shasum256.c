#include <stdio.h>
#include <openssl/evp.h>

#define BUF_BYTES 128

int main(int argc, char *argv[]) {
    unsigned md_len;
    unsigned char buf[BUF_BYTES];
    unsigned char md_value[EVP_MAX_MD_SIZE];
    if (argc == 2) {
        FILE *f = fopen(argv[1], "r");
        if (f != NULL) {
            EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
            int bytes_read  = fread(buf,1,BUF_BYTES,f);
            while (bytes_read > 0) {
                EVP_DigestUpdate(mdctx, buf, bytes_read);
                bytes_read = fread(buf,1,BUF_BYTES,f);
            }
            EVP_DigestFinal_ex(mdctx, md_value, &md_len);
            for (unsigned i = 0; i < md_len; i++)
                printf("%02x", md_value[i]);
            printf("\n");
            fclose(f);
            EVP_MD_CTX_free(mdctx);
        }
    } else {
        printf("usage: %s filename\n", argv[0]);
    }
    return EXIT_SUCCESS;
}