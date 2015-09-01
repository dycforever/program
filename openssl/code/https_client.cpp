

#include "common.h"

#define CERTFILE "client/client.crt"
#define KEYFILE "client/private/client.key"
// #define CAFILE "client/client.crt"
#define CAFILE "ft-root.crt"
#define CADIR "server/private/server.key"

long post_connection_check(SSL *ssl, char *host)
{
    X509 *cert;
    X509_NAME *subj;
    char data[256];
    int extcount;
    int ok = 0;
    /* Checking the return from SSL_get_peer_certificate here is not
     * * strictly necessary. With our example programs, it is not
     * * possible for it to return NULL. However, it is good form to
     * * check the return since it can return NULL if the examples are
     * * modified to enable anonymous ciphers or for the server to not
     * * require a client certificate.
     * */
    if (!(cert = SSL_get_peer_certificate(ssl)) || !host)
        goto err_occured;
    if ((extcount = X509_get_ext_count(cert)) > 0) {
        int i;
        for (i = 0; i < extcount; i++) {
            const char *extstr;
            X509_EXTENSION *ext;
            ext = X509_get_ext(cert, i);
            extstr = OBJ_nid2sn(OBJ_obj2nid(X509_EXTENSION_get_object(ext)));
            if (!strcmp(extstr, "subjectAltName")) {
                int j;
                const unsigned char *data;
                STACK_OF(CONF_VALUE) *val;
                CONF_VALUE *nval;
                const X509V3_EXT_METHOD *meth;
                if (!(meth = X509V3_EXT_get(ext)))
                    break;
                data = ext->value->data;
                val = meth->i2v(meth,
                        meth->d2i(NULL, &data, ext->value->length),
                        NULL);
                for (j = 0; j < sk_CONF_VALUE_num(val); j++)
                {
                    nval = sk_CONF_VALUE_value(val, j);
                    if (!strcmp(nval->name, "DNS") && !strcmp(nval->value, host))
                    {
                        ok = 1;
                        break;
                    }
                }
            }
            if (ok)
                break;
        }
    }
    if (!ok && (subj = X509_get_subject_name(cert)) &&
            X509_NAME_get_text_by_NID(subj, NID_commonName, data, 256) > 0) {
        data[255] = 0;
        if (strcasecmp(data, host) != 0)
            goto err_occured;
    }
    X509_free(cert);
    return SSL_get_verify_result(ssl);
err_occured:
    if (cert)
        X509_free(cert);
    return X509_V_ERR_APPLICATION_VERIFICATION;
}

int verify_callback(int ok, X509_STORE_CTX *store)
{
//    std::cout << "ok: " << ok << std::endl;
    char data[256];
//    if (!ok)
    {
        X509 *cert = X509_STORE_CTX_get_current_cert(store);
        int depth = X509_STORE_CTX_get_error_depth(store);
        int err = X509_STORE_CTX_get_error(store);
        fprintf(stderr, "-Error with certificate at depth: %i\n",
                depth);
        X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
        fprintf(stderr, " issuer = %s\n", data);
        X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
        fprintf(stderr, " subject = %s\n", data);
        fprintf(stderr, " err %i:%s\n", err,
                X509_verify_cert_error_string(err));
    }
    return ok;
}

SSL_CTX *setup_client_ctx(void)
{
    SSL_CTX *ctx;

    ctx = SSL_CTX_new(SSLv23_method());
    if (SSL_CTX_load_verify_locations(ctx, CAFILE, NULL) != 1)
        int_error("Error loading CA file and/or directory");
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
        int_error("Error loading default CA file and/or directory");
//    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1)
//        int_error("Error loading certificate from file");
//    if (SSL_CTX_use_PrivateKey_file(ctx, KEYFILE,
//                SSL_FILETYPE_PEM) != 1)
//        int_error("Error loading private key from file");
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
    SSL_CTX_set_verify_depth(ctx, 4);
    return ctx;

}

int do_client_loop(SSL *ssl)
{
    int err, nwritten;

//    char* buf = "GET /s?q=qq HTTP/1.0\r\nConnection:closed\r\nHost:ft.sm.cn\r\nUser-Agent:Mozilla/5.0 (Linux; U; Android 4.2.2; zh-CN; Coolpad 8122 Build/JDQ39) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 UCBrowser/9.9.2.467 U3/0.8.0 Mobile Safari/533.1)\r\n\r\n";
    char* buf = "GET / HTTP/1.0\r\nConnection:closed\r\nHost:ft.sm.cn\r\n\r\n";
    for (nwritten = 0; nwritten < (int)strlen(buf); nwritten +=
            err)
    {
        err = SSL_write(ssl, buf + nwritten, strlen(buf) -
                nwritten);
        if (err <= 0)
            return 0;
    }

#define BUFFER_SIZE 10000
    char buffer[BUFFER_SIZE];
    for (int nread = 0; nread < (int)sizeof(buffer); nread += err)
    {
        err = SSL_read(ssl, buffer + nread, sizeof(buffer) - nread);
        std::cout << "read " << err << " nread " << nread << std::endl;
        if (err <= 0) {
            std::cout << "buffer: " << buffer << std::endl;
            break;
            print_errors();
        }
    }
    return 1;
}

int main()
{
    BIO *conn;
    SSL *ssl;
    SSL_CTX *ctx;

    init_OpenSSL();
    seed_prng();

    ctx = setup_client_ctx();

#define SERVER "10.99.12.17:443"
    conn = BIO_new_connect(SERVER);
    if (!conn)
        int_error("Error creating connection BIO");

    if (BIO_do_connect(conn) <= 0)
        int_error("Error connecting to remote machine");

    if (!(ssl = SSL_new(ctx)))
        int_error("Error creating an SSL context");
    SSL_set_bio(ssl, conn, conn);
    if (SSL_connect(ssl) <= 0)
        int_error("Error connecting SSL object");
//    int err = 0;
//    if ((err = post_connection_check(ssl, SERVER)) != X509_V_OK)
//    {
//        fprintf(stderr, "-Error: peer certificate: %s\n", X509_verify_cert_error_string(err));
//        int_error("Error checking SSL object after connection");
//    }

    fprintf(stderr, "SSL Connection opened\n");
    if (do_client_loop(ssl))
        SSL_shutdown(ssl);
    else
        SSL_clear(ssl);
    fprintf(stderr, "SSL Connection closed\n");

    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}

