
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <strings.h>  // bzero

#include "InetAddress.h"
#include "Socket.h"  

namespace dyc {

Socket::~Socket()
{
    close(_sockfd);
}

int Socket::connect(const InetAddress& peerAddr) {
   const struct sockaddr_in& sockAddr = peerAddr.getSockAddrInet();
   int ret = ::connect(_sockfd, sockaddr_cast(&sockAddr), static_cast<socklen_t>(sizeof sockAddr));
   if (ret < 0) {
        FATAL("ret:%d bind socket[%d] raw_ip[%s] port[%u] Die errno[%d] with %s", 
                ret, _sockfd, inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port), errno, strerror(errno));
   }
   return ret;
}

int Socket::bind(const InetAddress& addr)
{

    struct sockaddr_in sockAddr = addr.getSockAddrInet();
    int ret = ::bind(_sockfd, sockaddr_cast(&sockAddr), static_cast<socklen_t>(sizeof sockAddr));
    if (ret < 0)
    {
        FATAL("ret:%d bind socket[%d] raw_ip[%s] port[%u] Die errno[%d] with %s", 
                ret, _sockfd, inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port), errno, strerror(errno));
        return ret;
    }
    setReuseAddr(true);
    NOTICE("bind with socket[%d] raw_ip[%s] port[%u]", 
           _sockfd, inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port));
    return 0;
}

int Socket::listen()
{
    int ret = ::listen(_sockfd, 100);
    if (ret < 0)
    {
        FATAL("listen  Die errno:%d with %s", errno, strerror(errno));
        return ret;
    }
    return 0;
}

int Socket::accept(int sockfd, struct sockaddr_in* addr)
{
    socklen_t addrlen = static_cast<socklen_t>(sizeof *addr);
    int connfd = ::accept(sockfd, sockaddr_cast(addr),
            &addrlen);

    if (connfd < 0)
    {
        int savedErrno = errno;
        switch (savedErrno)
        {
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EPROTO: // ???
            case EPERM:
            case EMFILE: // per-process lmit of open file desctiptor ???
                // expected errors
                errno = savedErrno;
                break;
            case EBADF:
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOBUFS:
            case ENOMEM:
            case ENOTSOCK:
            case EOPNOTSUPP:
                // unexpected errors
                FATAL("unexpected error of ::accept %d", savedErrno);
                break;
            default:
                FATAL("unknown error of ::accept %d", savedErrno);
                break;
        }
    }
    return connfd;
}

int Socket::accept(InetAddress& peeraddr)
{
    struct sockaddr_in addr;
    bzero(&addr, sizeof addr);
    int connfd = accept(_sockfd, &addr);
    if (connfd >= 0)
    {
        peeraddr.setSockAddrInet(addr);
    }
    return connfd;
}

void Socket::shutdownWrite()
{
    shutdown(_sockfd, SHUT_WR);
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(_sockfd, IPPROTO_TCP, TCP_NODELAY,
            &optval, static_cast<socklen_t>(sizeof optval));
}

void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    int ret = ::setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR,
            &optval, static_cast<socklen_t>(sizeof optval));
    if (ret < 0)
    {
        FATAL("SO_REUSEPORT failed.");
    }
}

void Socket::setKeepAlive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(_sockfd, SOL_SOCKET, SO_KEEPALIVE,
            &optval, static_cast<socklen_t>(sizeof optval));
}

}
