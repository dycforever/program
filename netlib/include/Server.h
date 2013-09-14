#ifndef Server_H
#define Server_H

#include <map>
#include <vector>
#include <list>
#include <algorithm>

#include "InetAddress.h" 
#include "Socket.h" 
#include "Epoller.h"
#include "EventLoop.h"

namespace dyc {

class Server {
public:

    typedef boost::function<int()> CallbackFunc;
    Server(const InetAddress& listenAddr);
    ~Server();  

    const InetAddress& host_address() const { return _listenAddr; }

    int start();

    Socket* new_connection(const InetAddress& peerAddr, uint32_t);
    Socket* new_connection(const InetAddress& peerAddr);

    void remove_connection(const Socket& conn);

    int accepter(Socket* sock, Epoller* poller);
private:

    const InetAddress _listenAddr;
    Socket* _listenSocket;
    Epoller* _epoller;
    EventLoop* _loop;

    CallbackFunc _readCallback;
    CallbackFunc _writeCallback;
    CallbackFunc _errorCallback;
};

}

#endif  
