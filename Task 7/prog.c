#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>

#define IV_SIZE 32

void askValue(unsigned char *ciphertext, unsigned char *plaintext, unsigned char *iv, int *X) {
    char hex_ciphertext[256], hex_iv[IV_SIZE*2+1];

    printf("Enter ciphertext: ");
    fgets(hex_ciphertext, sizeof(hex_ciphertext), stdin);
    hex_ciphertext[strcspn(hex_ciphertext, "\n")] = 0;

    printf("Enter plaintext: ");
    fgets((char*)plaintext, 128, stdin);
    plaintext[strcspn((char*)plaintext, "\n")] = 0;

    printf("Enter IV (32 hexadecimal characters): ");
    fgets(hex_iv, sizeof(hex_iv), stdin);
    hex_iv[strcspn(hex_iv, "\n")] = 0;

    printf("Enter X: ");
    scanf("%d", X);
    while(getchar() != '\n');

    for(int i = 0; i < strlen(hex_ciphertext); i+=2) {
        sscanf(&hex_ciphertext[i], "%2hhx", &ciphertext[i/2]);
    }
    for(int i = 0; i < strlen(hex_iv); i+=2) {
        sscanf(&hex_iv[i], "%2hhx", &iv[i/2]);
    }
}

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    unsigned char key_128[17] = {0};
    strncpy((char*)key_128, (char*)key, 16);
    for (int i = strlen((char*)key); i < 16; i++) {
        key_128[i] = '#';
    }

    if(!(ctx = EVP_CIPHER_CTX_new())) return 0;

    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key_128, iv)) return 0;

    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) return 0;
    ciphertext_len = len;

    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) return 0;
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int main(void)
{
    unsigned char ciphertext[128], plaintext[128], iv[128], encryptedtext[128];
    int X;
    int keyFound = 0;

    askValue(ciphertext, plaintext, iv, &X);

    FILE *fp;
    char word[17];
    fp = fopen("dictionary.txt", "r");
    if (fp == NULL) {
        printf("Could not open file dictionary.txt");
        return 1;
    }

    while (fgets(word, sizeof(word), fp) != NULL && keyFound == 0) {
        word[strcspn(word, "\n")] = 0;
        if (strlen(word) <= X) {
            int encryptedtext_len = encrypt(plaintext, strlen((char*)plaintext), word, iv, encryptedtext);
            encryptedtext[encryptedtext_len] = '\0';
            int t = 0;

            for(int i = 0; i < encryptedtext_len; i++) {
                if (encryptedtext[i] != ciphertext[i]) {
                    t = 1;
                }
            }
            if (t == 0) {
                printf("Found the key: %s\n", word);
                keyFound = 1;
                break;
            }
        }
    }

    fclose(fp);

    if (keyFound == 0) {
        printf("No key found\n");
    }

    return 0;
}
