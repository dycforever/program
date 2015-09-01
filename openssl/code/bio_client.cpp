
#include "common.h"


void handle_error(BIO *conn)
{
                int ret = BIO_should_retry(conn);
                if (ret != 0) {
                    std::cout << "BIO_should_retry: " << ret << std::endl;
                } else {
                    std::cout << "BIO_don't_need_retry: " << ret << std::endl;
                }

                ret = BIO_should_read(conn);
                if (ret != 0) {
                    std::cout << "BIO_should_read: " << ret << std::endl;
                } else {
                    std::cout << "BIO_don't_need_read: " << ret << std::endl;
                }

                ret = BIO_should_io_special(conn);
                if (ret != 0) {
                    std::cout << "BIO_should_io_special: " << ret << std::endl;
                } else {
                    std::cout << "BIO_not_io_special: " << ret << std::endl;
                }

                int type = BIO_retry_type(conn);
                if (type & BIO_FLAGS_READ) {
                    std::cout << "type: BIO_FLAGS_READ" << std::endl;
                } else if(type & BIO_FLAGS_WRITE) {
                    std::cout << "type: BIO_FLAGS_WRITE" << std::endl;
                } else if(type & BIO_FLAGS_IO_SPECIAL) {
                    std::cout << "type: BIO_FLAGS_WRITE" << std::endl;
                } else {
                    std::cout << "unknow type" << std::endl;
                }
}

void do_client_loop(BIO *conn)
{
    int err, nwritten, nread;
    char* buf = "GET /s?q=qq HTTP/1.0\r\nConnection:closed\r\nHost:ft.sm.cn\r\nUser-Agent:Mozilla/5.0 (Linux; U; Android 4.2.2; zh-CN; Coolpad 8122 Build/JDQ39) AppleWebKit/533.1 (KHTML, like Gecko) Version/4.0 UCBrowser/9.9.2.467 U3/0.8.0 Mobile Safari/533.1)\r\n\r\n";

        for (nwritten = 0; nwritten < (int)strlen(buf); ) {
            err = BIO_write(conn, buf + nwritten, strlen(buf) - nwritten);
            nwritten += err;
            std::cout << "write " << err << " nwritten " << nwritten << std::endl;
            if (err <= 0) {
                break;
            }
        }
#define BUFFER_SIZE 10
        char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
        for (nread = 0; nread < (int)sizeof(buffer); nread += err)
        {
            err = BIO_read(conn, buffer + nread, sizeof(buffer) - nread);
            std::cout << "read " << err << " nread " << nread << std::endl;
            if (err <= 0) {
                if (err == 0) {
//                    std::cout << "buffer: " << buffer << std::endl;
                    break;
                }
                print_errors();
                handle_error(conn);
            }
        }
}

int main()
{
    BIO *conn;
    init_OpenSSL();

//    conn = BIO_new_connect("ft.sm.cn:443");
    conn = BIO_new_connect("10.99.12.17:443");
    if (!conn)
        int_error("Error creating connection BIO");

    if (BIO_do_connect(conn) <= 0)
        int_error("Error connecting to remote machine");

    fprintf(stderr, "Connection opened\n");
    do_client_loop(conn);
    fprintf(stderr, "Connection closed\n");

    BIO_free(conn);
    return 0;
}

