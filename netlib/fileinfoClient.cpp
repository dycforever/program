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

    {
    shared_ptr<Socket> socket;
    socket.reset(client.connect());
    uint64_t len = strlen(file);
    socket->send((char*)&len, sizeof len);
    socket->send((char*)&len, sizeof(int));
    socket->send(file, len);
    NOTICE("send request:[%s] size:[%lu]", file, len);

    char* buf = NEW char[1024 * 1024 * 10];
    (void)buf;
    uint64_t fileSize = 0;

    socket->recv((char*)&fileSize, sizeof(fileSize));
    socket->recv((char*)&fileSize, 4);
    socket->recv((char*)&fileSize, sizeof(fileSize));
    NOTICE("socket owner:%d", socket.use_count());

    NOTICE("get response: %lu ", fileSize);
    std::cerr << fileSize << std::endl;
    }
    dumpUnfreed();
    return 0;
}
