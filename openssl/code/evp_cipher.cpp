#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#define PLAIN_TEXT_LENGTH 1000000
const char *cipherFun[] =
{
    "rc4",
    "rc4-40",

    "bf-ecb",
    "bf-cbc",
    //block size is 64bit
    "bf-cfb64",
    "bf-ofb",

    //key size is 128bit
    "aes-128-ecb",
    "aes-128-cbc",
    "aes-128-cfb128",
    "aes-128-ofb",

    "aes-192-ecb",
    "aes-192-cbc",
    "aes-192-cfb128",
    "aes-192-ofb",

    "aes-256-ecb",
    "aes-256-cbc",
    "aes-256-cfb128",
    "aes-256-ofb",

    "des-ecb",
    "des-cbc",
    "des-cfb64",
    "des-ofb",
    "desx-cbc",

    "cast5-ecb",
    "cast5-cbc",
    "cast5-cfb64",
    "cast5-ofb",

    "rc2-ecb",
    "rc2-cbc",
    "rc2-cfb64",
    "rc2-ofb",

    "rc5-ecb",
    "rc5-cbc",
    "rc5-cfb64",
    "rc5-ofb",

    //version  openssl-1.0.1
    "rc4-hmac-md5",
    "aes-128-ctr",
    "aes-128-ccm",
    "aes-128-gcm",
    "aes-128-xts",
    "aes-128-wrap",
    "aes-128-cbc-hmac-sha1"
        // version openssl-1.0.2
        //"aes-128-cbc-hmac-sha256",
};

int seed_prng(int bytes)
{
    if (!RAND_load_file("/dev/random", bytes))
        return 0;
    return 1;
}

void select_random_key(unsigned char *key, int b)
{
    RAND_bytes(key, b);
}

void select_random_iv(unsigned char *iv, int b)
{
    RAND_pseudo_bytes(iv, b);
}

unsigned char *encrypt_example(EVP_CIPHER_CTX *ctx, unsigned char *data, int inl, int
        *rb)
{
    unsigned char *ret;
    int i, tmp, ol;
    ol = 0;
    ret = (unsigned char *)malloc(inl + EVP_CIPHER_CTX_block_size(ctx));
    for (i = 0; i < inl / 100; i++)
    {
        EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], 100);
        ol += tmp;
    }
    if (inl % 100)
    {
        EVP_EncryptUpdate(ctx, &ret[ol], &tmp, &data[ol], inl%100);
        ol += tmp;
    }
    EVP_EncryptFinal(ctx, &ret[ol], &tmp);
    *rb = ol + tmp;
    return ret;
}

 unsigned char *decrypt_example(EVP_CIPHER_CTX *ctx, unsigned char *ct, int inl)
{
    unsigned char *pt = (unsigned char *)malloc(inl + EVP_CIPHER_CTX_block_size(ctx) + 1);
    int ol;
    EVP_DecryptUpdate(ctx, pt, &ol, ct, inl);
    if (!ol)
    {
        free(pt);
        return NULL;
    }
    pt[ol] = 0;
    return pt;
}

int main()
{
    EVP_CIPHER_CTX ctx;
    unsigned char key[EVP_MAX_KEY_LENGTH];
    unsigned char iv[EVP_MAX_IV_LENGTH];
    if (!seed_prng(1))
        return 0;
    printf(" key is:\n");
    select_random_key(key, EVP_MAX_KEY_LENGTH);
    printf("\n iv is:\n");
    select_random_iv(iv, EVP_MAX_IV_LENGTH);

    unsigned int i;
    unsigned char *ct, *out;
    FILE *fp = NULL;
    unsigned char str[PLAIN_TEXT_LENGTH];
    memset(str, 1, PLAIN_TEXT_LENGTH);
    printf("Plaintext is %d bytes.\n", PLAIN_TEXT_LENGTH);

    // EVP_add_cipher(EVP_bf_cbc()); to load specific cipher
    OpenSSL_add_all_ciphers();
    fp = fopen("cipher.csv", "w");
    for(i = 0; i < sizeof(cipherFun) / sizeof(char*); ++i) {
        int len;
        struct timeval start, end;
        time_t timer1, timer2;
        printf("\n cipher name:%s\n", cipherFun[i]);
        EVP_EncryptInit(&ctx, EVP_get_cipherbyname(cipherFun[i]), key, iv);

        gettimeofday(&start,NULL);
        ct = encrypt_example(&ctx, str, PLAIN_TEXT_LENGTH, &len);
        gettimeofday(&end,NULL);
        timer1 = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

        printf("Encrypt time is %ld us.\n", timer1);
        printf("Ciphertext is %d bytes.\n", len);

        EVP_DecryptInit(&ctx, EVP_get_cipherbyname(cipherFun[i]), key, iv);
        gettimeofday(&start,NULL);
        out = decrypt_example(&ctx, ct, PLAIN_TEXT_LENGTH);
        gettimeofday(&end,NULL); 
        timer2 = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

        printf("Decrypt time is %ld us.\n", timer2);

        fprintf(fp, "%s,%ld,%ld,%d\n", cipherFun[i], timer1, timer2, len);
    }
    return 0;
}

