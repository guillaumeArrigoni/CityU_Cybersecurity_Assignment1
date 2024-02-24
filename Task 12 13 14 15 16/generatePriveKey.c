#include <stdio.h>
#include <stdio.h>
#include <openssl/bn.h>

#define NBITS 128


int askValue(int length, BIGNUM **values, char **names) {
    for (int i = 0; i < length; i++) {
        char input[NBITS];
        printf("Enter the value for %s : ", names[i]);
        fgets(input, sizeof(input), stdin);
        BN_hex2bn(&values[i], input);
    }
    return 0;
}

void printBN(char *msg, BIGNUM * a){
    //FROM THE PDF FILE OF THE ASSIGNMENT
    char * number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    int length = 3;

    BN_CTX *ctx = BN_CTX_new();

    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *phi = BN_new();
    BIGNUM *d = BN_new();
    BIGNUM *values[length];
    BIGNUM *unite = BN_new();
    BN_dec2bn(&unite, "1");
    values[0] = p;
    values[1] = q;
    values[2] = e;

    char *names[length];
    names[0] = "p";
    names[1] = "q";
    names[2] = "e";

    askValue(length, values, names);

    BIGNUM *temporaryPhiFirstPart = BN_new();
    BIGNUM *temporaryPhiSecondPart = BN_new();
    BN_sub(temporaryPhiFirstPart, p, unite);
    BN_sub(temporaryPhiSecondPart, q, unite);
    BN_mul(phi, temporaryPhiFirstPart, temporaryPhiSecondPart, ctx);

    BN_mod_inverse(d, e, phi, ctx);

    printBN("La valeur de d est :", d);

    return 0;
}


