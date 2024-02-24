#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

#define NBITS 128

int askValue(int length, BIGNUM **values, const char **names) {
    for (int i = 0; i < length; i++) {
        char input[NBITS];
        printf("Enter the value for %s: ", names[i]);
        fgets(input, sizeof(input), stdin);
        BN_hex2bn(&values[i], input);
    }
    return 0;
}


int encryptRSA(BIGNUM *m, BIGNUM *n, BIGNUM *e, unsigned char *ciphertext, int *ciphertextLength) {
    BIGNUM *c = BN_new();

    BN_mod_exp(c, m, e, n, BN_CTX_new());

    *ciphertextLength = BN_num_bytes(c);
    BN_bn2bin(c, ciphertext);

    BN_free(c);
    return 0;
}

int main() {
    int length = 3;
    const char *names[length];
    names[0] = "n";
    names[1] = "e";
    names[2] = "message in hexadecimal";

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *values[length];

    for (int i = 0; i < length; i++) {
        values[i] = BN_new();
    }

    askValue(length, values, names);

    unsigned char ciphertext[NBITS];
    int ciphertextLength;

    int result = encryptRSA(values[2], values[0], values[1], ciphertext, &ciphertextLength);
    if (result == 0) {
        printf("Texte chiffré : ");
        for (int i = 0; i < ciphertextLength; i++) {
            printf("%02x", ciphertext[i]);
        }
        printf("\n");
    }

    for (int i = 0; i < length; i++) {
        BN_free(values[i]);
    }
    BN_CTX_free(ctx);

    return 0;
}
