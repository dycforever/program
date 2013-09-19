#include <iostream>
#include "netlib.h"

#include <boost/shared_ptr.hpp>

using namespace dyc;
using namespace boost;


int main(int argc, char** argv) {
    int port = 8714;
//    if (argc > 1) {
//        port = atoi(argv[1]);
//    }
    InetAddress addr("127.0.0.1", port);
//    InetAddress addr("172.17.229.85", 8714);
    Client client(addr);
    const char* file = "/home/dyc/program/netlib/makefile.g";
    if (argc > 1) {
        file = argv[1];
    }

    shared_ptr<Socket> socket;
    socket.reset(client.connect());
    uint64_t len = strlen(file);
    socket->send((char*)&len, sizeof len);
    int count = socket->send(file, len);
    NOTICE("send %d bytes over", count);

    char* buf = NEW char[1024 * 1024 * 10];
    (void)buf;
    uint64_t fileSize = 0;

    count = socket->recv((char*)&fileSize, sizeof(fileSize));

//    int ret = socket->shutdownWrite();
//    CHECK_ERROR(-1, ret==0, "socket shutdown failed");

    NOTICE("get response: %lu ", fileSize);
}
