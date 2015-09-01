#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <sys/time.h>

unsigned char *ecdh(size_t *secret_len)
{
  EVP_PKEY_CTX *pctx, *kctx;
  EVP_PKEY_CTX *ctx;
  unsigned char *secret;
  EVP_PKEY *pkey = NULL, *peerkey, *params = NULL;
  /* NB: assumes pkey, peerkey have been already set up */

  /* Create the context for parameter generation */
  if(NULL == (pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL))) ;

  /* Initialise the parameter generation */
  if(1 != EVP_PKEY_paramgen_init(pctx)) ;

  /* We're going to use the ANSI X9.62 Prime 256v1 curve */
  if(1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, NID_X9_62_prime256v1)) ;

  /* Create the parameter object params */
  if (!EVP_PKEY_paramgen(pctx, &params)) ;

  /* Create the context for the key generation */
  if(NULL == (kctx = EVP_PKEY_CTX_new(params, NULL))) ;

  /* Generate the key */
  if(1 != EVP_PKEY_keygen_init(kctx)) ;
  if (1 != EVP_PKEY_keygen(kctx, &pkey)) ;

  /* Get the peer's public key, and provide the peer with our public key -
   * how this is done will be specific to your circumstances */
  
  //EVP_PKEY_keygen(kctx, &peerkey);
  peerkey = pkey;

  /* Create the context for the shared secret derivation */
  if(NULL == (ctx = EVP_PKEY_CTX_new(pkey, NULL))) ;

  /* Initialise */
  if(1 != EVP_PKEY_derive_init(ctx));

  /* Provide the peer public key */
  if(1 != EVP_PKEY_derive_set_peer(ctx, peerkey)) ;

  /* Determine buffer length for shared secret */
  if(1 != EVP_PKEY_derive(ctx, NULL, secret_len)) ;

  /* Create the buffer */
  if(NULL == (secret = (unsigned char*)OPENSSL_malloc(*secret_len))) ;
  
  struct timeval start, end;
  time_t timer;
  gettimeofday(&start,NULL);
  /* Derive the shared secret */
  
  if(1 != (EVP_PKEY_derive(ctx, secret, secret_len))) ;
 
  gettimeofday(&end,NULL);
  timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

  printf("dche cost time:%ld us\n", timer);
  /* Never use a derived secret directly. Typically it is passed
   * through some hash function to produce a key */
  return secret;
}

void rsa() {
  struct timeval start, end;
  time_t timer;

  RSA* pRsa = RSA_generate_key(2048, RSA_F4, 0, 0);
  unsigned char sz[32];
  memset(sz, '0', sizeof(sz));
  int len = RSA_size(pRsa);
  unsigned char* p = (unsigned char*)malloc(sizeof(char)*len);
  memset(p, 0, len);
  gettimeofday(&start,NULL);

  RSA_public_encrypt(sizeof(sz), sz, p, pRsa, RSA_PKCS1_PADDING);
  
  gettimeofday(&end,NULL);
  timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
  printf("rsa encrypt cost time:%ld us\n", timer);

  unsigned char out[256]={0};
  gettimeofday(&start,NULL);
  
  RSA_private_decrypt(len, p, out, pRsa, RSA_PKCS1_PADDING);
  
  gettimeofday(&end,NULL);
  timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

  printf("rsa decrypt cost time:%ld us\n", timer);

  printf("%s\n", out);
}

int main() {
    size_t *len = (size_t*)malloc(sizeof(size_t));
    unsigned char* sestr;
    sestr = ecdh(len);
    printf("secret length is %ld\n", *len);
    rsa();
    return 0;
}
