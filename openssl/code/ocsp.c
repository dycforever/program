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

#define ngx_base64_encoded_length(len)  (((len + 2) / 3) * 4)

typedef struct {
    size_t      len;
    char     *data;
} ngx_str_t;

int ssl_certificate_index;

char*
ngx_escape_uri(char *dst, char *src, size_t size, int type)
{
    unsigned long      n;
    uint32_t       *escape;
    static char   hex[] = "0123456789abcdef";

                    /* " ", "#", "%", "?", %00-%1F, %7F-%FF */

    static uint32_t   uri[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x80000029, /* 1000 0000 0000 0000  0000 0000 0010 1001 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x80000000, /* 1000 0000 0000 0000  0000 0000 0000 0000 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };

                    /* " ", "#", "%", "&", "+", "?", %00-%1F, %7F-%FF */

    static uint32_t   args[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x88000869, /* 1000 1000 0000 0000  0000 1000 0110 1001 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x80000000, /* 1000 0000 0000 0000  0000 0000 0000 0000 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };

                    /* not ALPHA, DIGIT, "-", ".", "_", "~" */

    static uint32_t   uri_component[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0xfc009fff, /* 1111 1100 0000 0000  1001 1111 1111 1111 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x78000001, /* 0111 1000 0000 0000  0000 0000 0000 0001 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0xb8000001, /* 1011 1000 0000 0000  0000 0000 0000 0001 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };

                    /* " ", "#", """, "%", "'", %00-%1F, %7F-%FF */

    static uint32_t   html[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x000000ad, /* 0000 0000 0000 0000  0000 0000 1010 1101 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x80000000, /* 1000 0000 0000 0000  0000 0000 0000 0000 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };

                    /* " ", """, "%", "'", %00-%1F, %7F-%FF */

    static uint32_t   refresh[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x00000085, /* 0000 0000 0000 0000  0000 0000 1000 0101 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x80000000, /* 1000 0000 0000 0000  0000 0000 0000 0000 */

        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */
        0xffffffff  /* 1111 1111 1111 1111  1111 1111 1111 1111 */
    };

                    /* " ", "%", %00-%1F */

    static uint32_t   memcached[] = {
        0xffffffff, /* 1111 1111 1111 1111  1111 1111 1111 1111 */

                    /* ?>=< ;:98 7654 3210  /.-, +*)( '&%$ #"!  */
        0x00000021, /* 0000 0000 0000 0000  0000 0000 0010 0001 */

                    /* _^]\ [ZYX WVUT SRQP  ONML KJIH GFED CBA@ */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

                    /*  ~}| {zyx wvut srqp  onml kjih gfed cba` */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */

        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
        0x00000000, /* 0000 0000 0000 0000  0000 0000 0000 0000 */
    };

                    /* mail_auth is the same as memcached */

    static uint32_t  *map[] =
        { uri, args, uri_component, html, refresh, memcached, memcached };


    escape = map[type];

    if (dst == NULL) {

        /* find the number of the characters to be escaped */

        n = 0;

        while (size) {
            if (escape[*src >> 5] & (1 << (*src & 0x1f))) {
                n++;
            }
            src++;
            size--;
        }

        return (char*)n;
    }

    while (size) {
        if (escape[*src >> 5] & (1 << (*src & 0x1f))) {
            *dst++ = '%';
            *dst++ = hex[*src >> 4];
            *dst++ = hex[*src & 0xf];
            src++;

        } else {
            *dst++ = *src++;
        }
        size--;
    }

    return dst;
}

void
ngx_encode_base64(ngx_str_t *dst, ngx_str_t *src)
{
    char         *d, *s;
    size_t          len;
    static char   basis64[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    len = src->len;
    s = src->data;
    d = dst->data;

    while (len > 2) {
        *d++ = basis64[(s[0] >> 2) & 0x3f];
        *d++ = basis64[((s[0] & 3) << 4) | (s[1] >> 4)];
        *d++ = basis64[((s[1] & 0x0f) << 2) | (s[2] >> 6)];
        *d++ = basis64[s[2] & 0x3f];

        s += 3;
        len -= 3;
    }

    if (len) {
        *d++ = basis64[(s[0] >> 2) & 0x3f];

        if (len == 1) {
            *d++ = basis64[(s[0] & 3) << 4];
            *d++ = '=';

        } else {
            *d++ = basis64[((s[0] & 3) << 4) | (s[1] >> 4)];
            *d++ = basis64[(s[1] & 0x0f) << 2];
        }

        *d++ = '=';
    }

    dst->len = d - dst->data;
}

char*
ssl_ocsp_create_request(X509* cert, X509* issuer)
{
    int            len;
    char        *p;
    char        *escape;
    ngx_str_t      binary, base64;
    char *b;
    OCSP_CERTID   *id;
    OCSP_REQUEST  *ocsp;

    ocsp = OCSP_REQUEST_new();
    if (ocsp == NULL) {
        printf(
                      "OCSP_REQUEST_new() failed\n");
        return NULL;
    }

    id = OCSP_cert_to_id(NULL, cert, issuer);
    if (id == NULL) {
        printf(
                      "OCSP_cert_to_id() failed\n");
        goto failed;
    }

    if (OCSP_request_add0_id(ocsp, id) == NULL) {
        printf(
                      "OCSP_request_add0_id() failed\n");
        goto failed;
    }

    len = i2d_OCSP_REQUEST(ocsp, NULL);
    if (len <= 0) {
        printf(
                      "i2d_OCSP_REQUEST() failed\n");
        goto failed;
    }

    binary.len = len;
    binary.data = malloc(len);
    if (binary.data == NULL) {
        goto failed;
    }

    p = binary.data;
    len = i2d_OCSP_REQUEST(ocsp, (void*)&p);
    if (len <= 0) {
        printf(
                      "i2d_OCSP_REQUEST() failed\n");
        goto failed;
    }

    base64.len = ngx_base64_encoded_length(binary.len);
    base64.data = malloc(base64.len);
    if (base64.data == NULL) {
        goto failed;
    }

    ngx_encode_base64(&base64, &binary);

#define NGX_ESCAPE_URI_COMPONENT 2
    escape = ngx_escape_uri(NULL, (char*)base64.data, base64.len,
                            NGX_ESCAPE_URI_COMPONENT);

    printf("ssl ocsp request length %lu, escape %p\n", base64.len, escape);

    char* host = "test.com";
    char* uri = "";
    len = sizeof("GET ") - 1 + strlen(uri) + sizeof("/") - 1
          + base64.len + 2 * (unsigned long)escape + sizeof(" HTTP/1.0\r\n") - 1
          + sizeof("Host: ") - 1 + strlen(host) + sizeof("\r\n") - 1
          + sizeof("\r\n") - 1;

    b = malloc(len);
    if (b == NULL) {
        goto failed;
    }

    p = b;

    memcpy(p, "GET ", sizeof("GET ") - 1);
    p += sizeof("GET ") - 1;
    memcpy(p, uri, strlen(uri));
    p += strlen(uri);

    if (uri[strlen(uri) - 1] != '/') {
        *p++ = '/';
    }

    if (escape == 0) {
        strncpy(p, base64.data, base64.len);
        p += base64.len;

    } else {
        p = (char *) ngx_escape_uri(p, base64.data, base64.len, NGX_ESCAPE_URI_COMPONENT);
    }

    strncpy((char*)p, " HTTP/1.0" "\r\n", sizeof(" HTTP/1.0" "\r\n") - 1);
    p += sizeof(" HTTP/1.0" "\r\n") - 1;
    strncpy(p, "Host: ", sizeof("Host: ") - 1);
    p += sizeof("Host: ") - 1;
    strncpy(p, host, strlen(host));
    p += strlen(host);
    *p++ = '\r'; *p++ = '\n';
    /* add "\r\n" at the header end */
    *p++ = '\r'; *p++ = '\n';

    FILE* fp = fopen("ocsp.req", "w");
    fwrite(b, 1, len, fp);
    fclose(fp);
    return b;

failed:

    OCSP_REQUEST_free(ocsp);
    return NULL;
}

inline void init_OpenSSL(void)
{
    if (!SSL_library_init())
    {
        fprintf(stderr, "** OpenSSL initialization failed\n!\n");
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

inline void print_errors(void)
{
    int flags, line;
    const char *data, *file;
    unsigned long code;
    code = ERR_get_error_line_data(&file, &line, &data, &flags);
    while (code)
    {
        printf("error code: %lu in %s line %d.\n", code, file, line);
        if (data && (flags & ERR_TXT_STRING))
            printf("error data: %s\n", data);
        code = ERR_get_error_line_data(&file, &line, &data, &flags);
    }
}

X509* get_issuer_from_cert(SSL_CTX *ctx)
{
    X509_STORE          *store;
    store = SSL_CTX_get_cert_store(ctx);
    if (store == NULL) {
        printf("SSL_CTX_get_cert_store() failed");
        return NULL;
    }

    X509_STORE_CTX      *store_ctx = X509_STORE_CTX_new();
    if (store_ctx == NULL) {
        printf("X509_STORE_CTX_new() failed");
        return NULL;
    }

    if (X509_STORE_CTX_init(store_ctx, store, NULL, NULL) == 0) {
        printf("X509_STORE_CTX_init() failed");
        return NULL;
    }

    X509* issuer;
    X509* cert = SSL_CTX_get_ex_data(ctx, ssl_certificate_index);
    int rc = X509_STORE_CTX_get1_issuer(&issuer, store_ctx, cert);

    if (rc == -1) {
        printf("X509_STORE_CTX_get1_issuer() failed");
        X509_STORE_CTX_free(store_ctx);
        return NULL;
    }

    if (rc == 0) {
        printf("\"ssl_stapling\" ignored, issuer certificate not found");
        X509_STORE_CTX_free(store_ctx);
        return NULL;
    }

    X509_STORE_CTX_free(store_ctx);
    return issuer;
}

int main(int argc, char** argv) {
    char* cert_file_name = "certs/server/server.crt";
    if (argc > 1) {
        cert_file_name = argv[1];
    }
    init_OpenSSL();
    seed_prng(0);
    SSL_CTX *ctx = SSL_CTX_new(SSLv23_method());


    ssl_certificate_index = SSL_CTX_get_ex_new_index(0, NULL, NULL, NULL,
                                                         NULL);
    if (ssl_certificate_index == -1) {
        printf(
                      "SSL_CTX_get_ex_new_index() failed\n");
        return -1;
    }

    BIO     *bio;
    bio = BIO_new_file((char *) cert_file_name, "r");
    if (bio == NULL) {
        printf(
                      "BIO_new_file(\"%s\") failed\n", cert_file_name);
        return -1;
    }

    X509    *x509;
    x509 = PEM_read_bio_X509_AUX(bio, NULL, NULL, NULL);
    if (x509 == NULL) {
        printf( "PEM_read_bio_X509_AUX(\"%s\") failed\n", cert_file_name);
        BIO_free(bio);
        return -1;
    }

    if (SSL_CTX_use_certificate(ctx, x509) == 0) {
        printf(
                      "SSL_CTX_use_certificate(\"%s\") failed\n", cert_file_name);
        X509_free(x509);
        BIO_free(bio);
        return -1;
    }

    if (SSL_CTX_set_ex_data(ctx, ssl_certificate_index, x509)
        == 0)
    {
        printf(
                      "SSL_CTX_set_ex_data() failed\n");
        return -1;
    }

    X509_free(x509);

    for ( ;; ) {

        x509 = PEM_read_bio_X509(bio, NULL, NULL, NULL);
        if (x509 == NULL) {
            int n = ERR_peek_last_error();

            if (ERR_GET_LIB(n) == ERR_LIB_PEM
                && ERR_GET_REASON(n) == PEM_R_NO_START_LINE)
            {
                /* end of file */
                ERR_clear_error();
                break;
            }

            /* some real error */

            printf(
                          "PEM_read_bio_X509(\"%s\") failed", cert_file_name);
            BIO_free(bio);
            return -1;
        }

        if (SSL_CTX_add_extra_chain_cert(ctx, x509) == 0) {
            printf(
                          "SSL_CTX_add_extra_chain_cert(\"%s\") failed",
                          cert_file_name);
            X509_free(x509);
            BIO_free(bio);
            return -1;
        }
    }


    X509* cert = SSL_CTX_get_ex_data(ctx, ssl_certificate_index);
    STACK_OF(X509)      *chain;

#if OPENSSL_VERSION_NUMBER >= 0x10001000L
    SSL_CTX_get_extra_chain_certs(ctx, &chain);
#else
    chain = ctx->extra_certs;
#endif

    int n = sk_X509_num(chain);
    printf( "SSL get issuer: %d extra certs\n", n);
    print_errors();
    int i;
    X509* issuer = NULL;
    for (i = 0; i < n; i++) {
        issuer = sk_X509_value(chain, i);
        if (X509_check_issued(issuer, cert) == X509_V_OK) {
            CRYPTO_add(&issuer->references, 1, CRYPTO_LOCK_X509);
            printf("SSL get issuer: found %p in extra certs[%d]\n", issuer, i);

//            return 0;
        }
    }
    X509* issuer2 = get_issuer_from_cert(ctx);
    ssl_ocsp_create_request(cert, issuer);
    printf("SSL get issuer: found %p in cert store\n", issuer2);

    return 0;
}

