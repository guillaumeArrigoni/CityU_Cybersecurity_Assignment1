#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

#define NBITS 128

int askValue(int length, BIGNUM **values, char **names) {
    for (int i = 0; i < length; i++) {
        char input[NBITS];
        printf("Enter the value for %s: ", names[i]);
        fgets(input, sizeof(input), stdin);
        BN_hex2bn(&values[i], input);
    }
    return 0;
}

int decryptRSA(BIGNUM *n, BIGNUM *d, BIGNUM *c, char *plaintext) {
    BIGNUM *m = BN_new();

    BN_mod_exp(m, c, d, n, BN_CTX_new());

    int plaintextLength = BN_num_bytes(m);
    BN_bn2bin(m, (unsigned char *)plaintext);
    plaintext[plaintextLength] = '\0';

    BN_free(m);
    return plaintextLength;
}

int main() {
    int length = 3;

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *c = BN_new();

    BIGNUM *values[length];
    values[0] = n;
    values[1] = d;
    values[2] = c;

    char *names[length];
    names[0] = "n";
    names[1] = "d";
    names[2] = "ciphertext";

    askValue(length, values, names);

    char plaintext[NBITS];
    int plaintextLength = decryptRSA(n, d, c, plaintext);

    if (plaintextLength > 0) {
        printf("Decrypted Text: %s\n", plaintext);
    }

    for (int i = 0; i < length; i++) {
        BN_free(values[i]);
    }
    BN_CTX_free(ctx);
    return 0;
}
