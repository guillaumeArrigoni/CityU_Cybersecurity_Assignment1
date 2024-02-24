#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bn.h>

#define NBITS 2048

int askValue(int length, BIGNUM **values, char **names) {
    for (int i = 0; i < length; i++) {
        char input[NBITS];
        printf("Enter the value for %s: ", names[i]);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        BN_hex2bn(&values[i], input);
    }
    return 0;
}


int verifySignature(BIGNUM *n, BIGNUM *e, BIGNUM *m, BIGNUM *s) {
    BIGNUM *computedMessage = BN_new();

    BN_mod_exp(computedMessage, s, e, n, BN_CTX_new());

    char *computedMessageHex = BN_bn2hex(computedMessage);

    int result = strcmp(computedMessageHex, BN_bn2hex(m));

    BN_free(computedMessage);
    OPENSSL_free(computedMessageHex);

    return result == 0;
}

int main() {
    int length = 4;

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *m = BN_new();
    BIGNUM *s = BN_new();

    BIGNUM *values[length];
    values[0] = n;
    values[1] = e;
    values[2] = m;
    values[3] = s;

    char *names[length];
    names[0] = "n";
    names[1] = "e";
    names[2] = "message";
    names[3] = "signature";

    askValue(length, values, names);

    int verificationResult = verifySignature(n, e, m, s);
    if (verificationResult) {
        printf("Signature verified.\n");
    } else {
        printf("Signature verification failed.\n");
    }

    for (int i = 0; i < length; i++) {
        BN_free(values[i]);
    }
    BN_CTX_free(ctx);

    return 0;
}
