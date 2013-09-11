#include <iostream>
#include "netlib.h"

using namespace dyc;

int main() {
    InetAddress addr("127.0.0.1", 8714);
//    InetAddress addr("172.17.229.85", 8714);
    int sockfd = createBlockingSocket();
    assert(sockfd != -1);
    Socket socket(sockfd);

    int ret = socket.bind(addr);
    assert(ret != -1);

    ret = socket.listen();
    assert(ret != -1);

    while (1) {
        InetAddress peerAddr;
        ret = socket.accept(peerAddr);
        assert(ret != -1);
        NOTICE("accept addr:%s", peerAddr.toIpPort().c_str());
    }
    

    NOTICE("main go to sleep");
    while(1){ sleep(1000);}
}
