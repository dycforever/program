#include <boost/bind.hpp> 
#include "Server.h"

namespace dyc {

Server::Server(const InetAddress& listen_addr):
    _listenAddr(listen_addr), _loop(NULL){}
Server::~Server() {}

int Server::accepter(Socket* sock, Epoller* poller) {
    InetAddress addr;
    int newfd = sock->accept(addr);
    NOTICE("accept a new conn with addr:%s", addr.toIpPort().c_str());
    if (newfd< 0) {
        FATAL("fd[%d] errno[%d]: %s", newfd, errno, strerror(errno));
        return -1;
    }
    Socket* newso = NEW Socket(newfd);
    Connection* conn = NEW Connection(newso, _loop);
    addConnection(conn);
    poller->addRead(newso);
    return 0;
}


int Server::addConnection(Connection* conn) {
    _connections.insert(conn);
    return 0;
}

//void Server::setReadCallback(CallbackFunc cb) {
//    _readCallback = cb;
//}
//
//void Server::setWriteCallback(CallbackFunc cb) {
//    _writeCallback = cb;
//}

int Server::start() {

    int sockfd = createBlockingSocket();
    assert(sockfd != -1);

    _listenSocket = NEW Socket(sockfd);
    int ret = _listenSocket->bind(_listenAddr);
    assert(ret != -1);

    ret = _listenSocket->listen();
    assert(ret != -1);

    _epoller = NEW Epoller();
    ret = _epoller->createEpoll();
    CHECK_ERROR(-1, ret == 0, "create epoller failed");

    CallbackFunc acceptCallback = boost::bind(&Server::accepter, this, _1, _epoller);
    _listenSocket->setReadCallback(acceptCallback);

    ret = _epoller->addRW(_listenSocket);
    CHECK_ERROR(-1, ret == 0, "add read write epoller failed");

    _loop = NEW EventLoop(_epoller);
    _loop->loop();
    return 0;
}

}
