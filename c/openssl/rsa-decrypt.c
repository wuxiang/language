/*
gcc -o rsa-decrypt rsa-decrypt.c -lcrypto
*/
#include <openssl/rsa.h>
#include <string.h>

#define MODULUS "C8FBCF21"
#define PUBLIC_EXPONENT RSA_F4
#define PRIVATE_EXPONENT "97B55D7D"

int main()
{
    int ret, flen;
    BIGNUM *bnn, *bne;
    unsigned char in[] = {0x98, 0x79, 0xb2, 0x76};
    unsigned char *out;

    bnn = BN_new();
    bne = BN_new();
    BN_hex2bn(&bnn, MODULUS);
    BN_set_word(bne, PUBLIC_EXPONENT);

    RSA *r = RSA_new();
    r->n = bnn;
    r->e = bne;
    RSA_print_fp(stdout, r, 5);

    flen = RSA_size(r);
    out = (unsigned char *)malloc(flen);
    bzero(out, flen);

    printf("Begin decrypt... ");
    ret = RSA_public_decrypt(sizeof(in), in, out, r, RSA_NO_PADDING);
    if (ret < 0)
    {
        printf("Decrypt failed! ");
        return 1;
    }

    printf("Size:%d ", ret);
    printf("ClearText:%s \n", out);

    free(out);
    RSA_free(r);
    return 0;
}
