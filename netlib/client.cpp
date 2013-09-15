#include <iostream>
#include "netlib.h"

#include <boost/shared_ptr.hpp>

using namespace dyc;
using namespace boost;


int main(int argc, char** argv) {
    int port = 8714;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    InetAddress addr("127.0.0.1", port);
//    InetAddress addr("172.17.229.85", 8714);
    Client client(addr);
    char* file = (char*)"/home/dyc/program/netlib/makefile.g";

    shared_ptr<Socket> socket;
    socket.reset(client.connect());
    uint64_t len = strlen(file);
    socket->send((char*)&len, sizeof len);
    socket->send(file, sizeof file);
    NOTICE("send over");

    char* buf = NEW char[1024 * 1024 * 10];

    int count = socket->recv(buf, 234);

//    int ret = socket->shutdownWrite();
//    CHECK_ERROR(-1, ret==0, "socket shutdown failed");

    NOTICE("get response: %d", count);
}
