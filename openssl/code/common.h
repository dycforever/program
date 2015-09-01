
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
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

#define int_error(msg) handle_error(__FILE__, __LINE__, msg)

inline void handle_error(const char *file, int lineno, const char *msg)
{
    fprintf(stderr, "** %s:%i %s\n", file, lineno, msg);
    ERR_print_errors_fp(stderr);
    exit(-1);
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

inline void init_OpenSSL(void)
{
    if (!SSL_library_init())
    {
        fprintf(stderr, "** OpenSSL initialization failed!\n");
        exit(-1);
    }
    SSL_load_error_strings();
}

inline int seed_prng(int bytes = 0)
{
    if (!RAND_load_file("/dev/random", bytes))
        return 0;
    return 1;
}
