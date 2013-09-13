#include <iostream>
#include "netlib.h"

using namespace dyc;

int main() {
    InetAddress addr("127.0.0.1", 8714);
//    InetAddress addr("172.17.229.85", 8714);
    int sockfd = createBlockingSocket();
    {
    Socket socket(sockfd);

    int ret = socket.connect(addr);
    assert(ret != -1);
    sleep(1);

    NOTICE("success~ client go to sleep");
    }
    while(1){sleep(1000);}
}
