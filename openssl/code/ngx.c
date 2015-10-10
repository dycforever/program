
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/ocsp.h>
#include <openssl/rand.h>

    char* certificate_path = "certs/server/server.crt";
    char* certificate_key_path = "certs/server/private/server.key";
    char* ciphers_string = "ALL";

// int
// ngx_ssl_crl(ngx_ssl_t *ssl, ngx_str_t *crl)
// {
//     X509_STORE   *store;
//     X509_LOOKUP  *lookup;
// 
//     if (crl->len == 0) {
//         return 0;
//     }
// 
// 
//     store = SSL_CTX_get_cert_store(ctx);
// 
//     if (store == NULL) {
//             printf(
//                       "SSL_CTX_get_cert_store() failed");
//         return -1;
//     }
// 
//     lookup = X509_STORE_add_lookup(store, X509_LOOKUP_file());
// 
//     if (lookup == NULL) {
//             printf(
//                       "X509_STORE_add_lookup() failed");
//         return -1;
//     }
// 
//     if (X509_LOOKUP_load_file(lookup, (char *) crl->data, X509_FILETYPE_PEM)
//         == 0)
//     {
//             printf(
//                       "X509_LOOKUP_load_file(\"%s\") failed\n", crl->data);
//         return -1;
//     }
// 
//     X509_STORE_set_flags(store,
//                          X509_V_FLAG_CRL_CHECK|X509_V_FLAG_CRL_CHECK_ALL);
// 
//     return 0;
// }

int
ngx_ssl_trusted_certificate(SSL_CTX *ctx, char* cert, int depth)
{
    SSL_CTX_set_verify_depth(ctx, depth);

    if (SSL_CTX_load_verify_locations(ctx, (char *) cert, NULL)
        == 0) {
            printf("SSL_CTX_load_verify_locations(\"%s\") failed\n", cert);
        return -1;
    }

    return 0;
}

int
ngx_ssl_certificate(SSL_CTX *ctx, char* cert, char* key)
{
    BIO     *bio;
    X509    *x509;
    u_long   n;
    /*
     * we can't use SSL_CTX_use_certificate_chain_file() as it doesn't
     * allow to access certificate later from SSL_CTX, so we reimplement
     * it here
     */

    bio = BIO_new_file((char *) cert, "r");
    if (bio == NULL) {
        printf("BIO_new_file(\"%s\") failed\n", cert);
        return -1;
    }

    x509 = PEM_read_bio_X509_AUX(bio, NULL, NULL, NULL);
    if (x509 == NULL) {
            printf("PEM_read_bio_X509_AUX(\"%s\") failed\n", cert);
        BIO_free(bio);
        return -1;
    }

    if (SSL_CTX_use_certificate(ctx, x509) == 0) {
            printf("SSL_CTX_use_certificate(\"%s\") failed\n", cert);
        X509_free(x509);
        BIO_free(bio);
        return -1;
    }

    X509_free(x509);

    /* read rest of the chain */

    for ( ;; ) {

        x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
        if (x509 == NULL) {
            n = ERR_peek_last_error();

            if (ERR_GET_LIB(n) == ERR_LIB_PEM
                && ERR_GET_REASON(n) == PEM_R_NO_START_LINE)
            {
                /* end of file */
                ERR_clear_error();
                printf("end of cert file\n");
                break;
            }

            /* some real error */

            printf("PEM_read_bio_X509(\"%s\") failed\n", cert);
            BIO_free(bio);
            return -1;
        }

        if (SSL_CTX_add_extra_chain_cert(ctx, x509) == 0) {
            printf("SSL_CTX_add_extra_chain_cert(\"%s\") failed\n", cert);
            X509_free(x509);
            BIO_free(bio);
            return -1;
        }
    }

    BIO_free(bio);

    if (SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM)
        == 0)
    {
        printf("SSL_CTX_use_PrivateKey_file(\"%s\") failed\n", key);
        return -1;
    }

    return 0;
}

typedef void (*ssl_info_callback)();

static void
ngx_ssl_info_callback(SSL* ssl_conn, int where, int ret)
{
    printf("%p %d\n", ssl_conn, ret);
    if ((where & SSL_CB_LOOP) == where) {
        printf("SSL_CB_LOOP\n");
    }
    if ((where & SSL_CB_EXIT) == where) {
        printf("SSL_CB_EXIT\n");
    }
    if ((where & SSL_CB_READ) == where) {
        printf("SSL_CB_READ\n");
    }
    if ((where & SSL_CB_WRITE) == where) {
        printf("SSL_CB_WRITE\n");
    }
    if ((where & SSL_CB_ALERT) == where) {
        printf("SSL_CB_ALERT\n");
    }
    if ((where & SSL_CB_READ_ALERT) == where) {
        printf("SSL_CB_READ_ALERT\n");
    }
    if ((where & SSL_CB_WRITE_ALERT) == where) {
        printf("SSL_CB_WRITE_ALERT\n");
    }
    if ((where & SSL_CB_ACCEPT_LOOP) == where) {
        printf("SSL_CB_ACCEPT_LOOP\n");
    }
    if ((where & SSL_CB_ACCEPT_EXIT) == where) {
        printf("SSL_CB_ACCEPT_EXIT\n");
    }
    if ((where & SSL_CB_CONNECT_LOOP) == where) {
        printf("SSL_CB_CONNECT_LOOP\n");
    }
    if ((where & SSL_CB_CONNECT_EXIT) == where) {
        printf("SSL_CB_CONNECT_EXIT\n");
    }
    if ((where & SSL_CB_HANDSHAKE_DONE) == where) {
        printf("SSL_CB_HANDSHAKE_DONE\n");
    }
    if ((where & SSL_CB_HANDSHAKE_START) == where) {
        printf("SSL_CB_HANDSHAKE_START\n");
    }
}

inline void init_OpenSSL(void)
{
    if (!SSL_library_init())
    {
        fprintf(stderr, "** OpenSSL initialization failed!\n");
        exit(-1);
    }
    SSL_load_error_strings();
}

inline int seed_prng(int bytes)
{
    if (!RAND_load_file("/dev/random", bytes))
        return 0;
    return 1;
}

int main()
{
    init_OpenSSL();
    seed_prng(0);
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_method());

    SSL_CTX_set_options(ctx, SSL_OP_SSLREF2_REUSE_CERT_TYPE_BUG);

    SSL_CTX_set_options(ctx, SSL_OP_SSLEAY_080_CLIENT_DH_BUG);
    SSL_CTX_set_options(ctx, SSL_OP_TLS_D5_BUG);
    SSL_CTX_set_options(ctx, SSL_OP_TLS_BLOCK_PADDING_BUG);

    SSL_CTX_set_options(ctx, SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS);

    SSL_CTX_set_options(ctx, SSL_OP_SINGLE_DH_USE);

//    SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1);
//    SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_1);
//    SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_2);

#ifdef SSL_OP_NO_COMPRESSION
    SSL_CTX_set_options(ctx, SSL_OP_NO_COMPRESSION);
#endif

#ifdef SSL_MODE_RELEASE_BUFFERS
    SSL_CTX_set_mode(ctx, SSL_MODE_RELEASE_BUFFERS);
#endif

    SSL_CTX_set_read_ahead(ctx, 1);

    ssl_info_callback callback = ngx_ssl_info_callback;
    SSL_CTX_set_info_callback(ctx, callback);

    if (ngx_ssl_certificate(ctx, certificate_path,
                            certificate_key_path) != 0)
    {
        return -1;
    }

    if (ngx_ssl_certificate(ctx, "certs/server/server_sha1.crt",
                            "certs/server/private/server.key") != 0)
    {
        return -1;
    }

    if (SSL_CTX_set_cipher_list(ctx, (const char *) ciphers_string) == 0)
    {
        printf("SSL_CTX_set_cipher_list(\"%s\") failed\n",
                      ciphers_string);
    }
//    int verify_depth = 3;
//    char* trusted_certificate = "crt";
//    if (ngx_ssl_trusted_certificate(ctx, trusted_certificate, verify_depth) != 0)
//    {
//        return -1;
//    }
//
//    if (ngx_ssl_crl(&conf->ssl, &conf->crl) != 0) {
//        return -1;
//    }

    SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE);

    /* a temporary 512-bit RSA key is required for export versions of MSIE */
//    SSL_CTX_set_tmp_rsa_callback(ctx, ngx_ssl_rsa512_key_callback);

//    if (ngx_ssl_dhparam(&conf->ssl, &conf->dhparam) != 0) {
//        return -1;
//    }
//
//    if (ngx_ssl_ecdh_curve(&conf->ssl, &conf->ecdh_curve) != 0) {
//        return -1;
//    }

//    if (ngx_ssl_session_cache(&conf->ssl, &ngx_http_ssl_sess_id_ctx,
//                              conf->builtin_session_cache,
//                              conf->shm_zone, conf->session_timeout)
//        != 0)
//    {
//        return -1;
//    }
//
//    if (conf->stapling) {
//
//        if (ngx_ssl_stapling(&conf->ssl, &conf->stapling_file,
//                             &conf->stapling_responder, conf->stapling_verify) != 0)
//        {
//            return -1;
//        }
//
//    }

    struct sockaddr_in server_addr;
    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);
    server_addr.sin_port = htons(443);

    int server_socket = socket(PF_INET,SOCK_STREAM,0);
    if( server_socket < 0) {
        printf("Create Socket Failed!");
        exit(1);
    }
    { 
        int opt =1;
        setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
    }

    {
        socklen_t blen = sizeof(int);
        int buf = 0;
        getsockopt(server_socket, SOL_SOCKET, SO_RCVBUF, (void *) &buf, &blen);
        printf("recv buffer length: %d\n", buf);

        buf = 0;
        getsockopt(server_socket, SOL_SOCKET, SO_SNDBUF, (void *) &buf, &blen);
        printf("send buffer length: %d\n", buf);
    }

    if (bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))) {
        printf("Server Bind Port : %d Failed!", 443); 
        exit(1);
    }

    if (listen(server_socket, 11) ) {
        printf("Server Listen Failed!"); 
        exit(1);
    }


    while(1) {
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);

        int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
        if ( new_server_socket < 0) {
            printf("Server Accept Failed!\n");
            return -1;
        }
        printf("Server Accept !\n");
        // init above
        SSL* ssl = SSL_new(ctx);

        if (SSL_set_fd(ssl, new_server_socket) == 0) {
            printf("SSL_set_fd() failed");
            return -1;
        }
        SSL_set_accept_state(ssl);
        int n = SSL_do_handshake(ssl);

        if (n == 1) {
            char         buf[129], *s, *d;
            const SSL_CIPHER* cipher = SSL_get_current_cipher(ssl);

            if (cipher) {
                SSL_CIPHER_description(cipher, &buf[1], 128);

                for (s = &buf[1], d = buf; *s; s++) {
                    if (*s == ' ' && *d == ' ') {
                        continue;
                    }

                    if (*s == '\r' || *s == '\n') {
                        continue;
                    }

                    *++d = *s;
                }

                if (*d != ' ') {
                    d++;
                }

                *d = '\0';

                printf("SSL: %s, cipher: \"%s\"\n",
                        SSL_get_version(ssl), &buf[1]);

                if (SSL_session_reused(ssl)) {
                    printf("SSL reused session");
                }

            } else {
                printf("SSL no shared ciphers");
            }

            int sslerr = SSL_get_error(ssl, n);

            printf("SSL_get_error: %d\n", sslerr);

            if (sslerr == 6 || ERR_peek_error() == 0) {
                printf("peer closed connection in SSL handshake");
            }

            char* resp = "HTTP/1.1 200 OK\r\nServer: Tengine/2.1.0\r\nDate: Wed, 02 Sep 2015 05:50:39 GMT\r\nContent-Type: text/html\r\nConnection: close\r\n\r\nhehe\r\n\r\n";
            SSL_write(ssl, resp, strlen(resp));
        }
        SSL_free(ssl);
        close(new_server_socket);
    }
    return 0;
}


