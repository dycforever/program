#include <sys/epoll.h>
#include <boost/function.hpp>
#ifndef __SOCKET_H__
#define __SOCKET_H__

namespace dyc {

class InetAddress;
// Wrapper of socket file descriptor.
//
// It closes the sockfd when desctructs.
// It's thread safe, all operations are delagated to OS.
class Socket {
public:
    typedef boost::function<int()> CallbackFunc;

    explicit Socket(int sockfd)
        : _sockfd(sockfd)
    { }

    ~Socket();

    int bind(const InetAddress& localaddr);
    int listen();
    int accept(InetAddress& peeraddr);
    int connect(const InetAddress& localaddr);

    int fd() {return _sockfd;}
    void shutdownWrite();

    /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
    void setTcpNoDelay(bool on);
    /// Enable/disable SO_REUSEADDR
    void setReuseAddr(bool on);
    /// Enable/disable SO_KEEPALIVE
    void setKeepAlive(bool on);

    int handle(const epoll_event& event);
    void setWriteCallback(CallbackFunc cb) {_writeCallback = cb;}
    void setReadCallback(CallbackFunc cb) {_readCallback = cb;}
    void setErrorCallback(CallbackFunc cb) {_errorCallback = cb;}

private:
    /// On success, returns a non-negative integer that is
    /// a descriptor for the accepted socket, which has been
    /// set to non-blocking and close-on-exec. *peeraddr is assigned.
    /// On error, -1 is returned, and *peeraddr is untouched.
    int accept(int sockfd, struct sockaddr_in* addr);

    int _sockfd;
    CallbackFunc _readCallback;
    CallbackFunc _writeCallback;
    CallbackFunc _errorCallback;

    int handleRead();
    int handleWrite();
    int handleError();
};

}

#endif
