#include <iostream>
#include <boost/bind.hpp>
#include "netlib.h"

using namespace dyc;

class ReadCallback {
public:
    char buf[1024];
    void operator() (int fd) {
        int count = read(fd, buf, 1024);
        buf[count] = 0;
        NOTICE("recv %d bytes: %s", count, buf);
    }
};


    int echoRead(int fd) {
        char buf[1024];
        int count = read(fd, buf, 1024);
        if (count < 0) {
            FATAL("fd[%d] errno[%d]: %s", fd, errno, strerror(errno));
            return -1;
        }
        if (count == 0) {
            close(fd);
        }
        buf[count] = 0;
        NOTICE("recv %d bytes: %s", count, buf);
        return 0;
    }


int main() {

//    InetAddress addr("172.17.229.85", 8714);
    InetAddress addr("127.0.0.1", 8714);
    Server server(addr);
    server.start();
}
