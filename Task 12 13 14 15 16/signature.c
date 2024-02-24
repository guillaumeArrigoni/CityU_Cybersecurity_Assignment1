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

void signMessage(BIGNUM *n, BIGNUM *d, BIGNUM *m, char **signature) {
    BIGNUM *s = BN_new();

    BN_mod_exp(s, m, d, n, BN_CTX_new());

    *signature = BN_bn2hex(s);

    BN_free(s);
}

int main() {
    int length = 3;

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *m = BN_new();

    BIGNUM *values[length];
    values[0] = n;
    values[1] = d;
    values[2] = m;

    char *names[length];
    names[0] = "n";
    names[1] = "d";
    names[2] = "message";

    askValue(length, values, names);

    char *signature;
    signMessage(n, d, m, &signature);

    printf("Signature: %s\n", signature);

    for (int i = 0; i < length; i++) {
        BN_free(values[i]);
    }
    BN_CTX_free(ctx);
    OPENSSL_free(signature);
    return 0;
}
