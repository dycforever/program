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

    int accepter(int fd) {
        char buf[1024];
        int count = read(fd, buf, 1024);
        if (count < 0) {
            FATAL("fd[%d] errno[%d]: %s", fd, errno, strerror(errno));
            return -1;
        }
        buf[count] = 0;
        NOTICE("recv %d bytes: %s", count, buf);
        return 0;
    }

    int echoRead(int fd) {
        char buf[1024];
        int count = read(fd, buf, 1024);
        if (count < 0) {
            FATAL("fd[%d] errno[%d]: %s", fd, errno, strerror(errno));
            return -1;
        }
        buf[count] = 0;
        NOTICE("recv %d bytes: %s", count, buf);
        return 0;
    }

int main() {
    InetAddress addr("127.0.0.1", 8714);
//    InetAddress addr("172.17.229.85", 8714);
    int sockfd = createBlockingSocket();
    assert(sockfd != -1);
    Socket socket(sockfd);

    Socket::CallbackFunc rcb = boost::bind(&echoRead, sockfd);
    Socket::CallbackFunc wcb;
    Socket::CallbackFunc ecb;

    socket.setReadCallback(rcb);
    socket.setWriteCallback(wcb);
    socket.setErrorCallback(ecb);

    int ret = socket.bind(addr);
    assert(ret != -1);

    ret = socket.listen();
    assert(ret != -1);

    Epoller* epoller = NEW Epoller();
    ret = epoller->createEpoll();
    CHECK_ERROR(-1, ret == 0, "create epoller failed");
    ret = epoller->addRW(&socket);
    CHECK_ERROR(-1, ret == 0, "add read write epoller failed");

//    while (1) {
//        InetAddress peerAddr;
//        ret = socket.accept(peerAddr);
//        assert(ret != -1);
//        NOTICE("accept addr:%s", peerAddr.toIpPort().c_str());
//    }
    epollRun(epoller);

    NOTICE("main go to sleep");
    while(1){ sleep(1000);}
}
