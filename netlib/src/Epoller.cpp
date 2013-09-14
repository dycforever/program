#include <boost/bind.hpp>
#include "Epoller.h"

namespace dyc {

Epoller::Epoller() :_stop(false){
    _threadId = pthread_self();
}

bool Epoller::inThisThread() {
    return _threadId == pthread_self();
}

int Epoller::addRead(Socket* socket) {
    lock();
    int ret = addEvent(socket, EPOLLIN);
    unlock();
    return ret;
}

int Epoller::addWrite(Socket* socket) {
    lock();
    int ret = addEvent(socket, EPOLLOUT);
    unlock();
    return ret;
}

int Epoller::addRW(Socket* socket) {
    int ret = 0;
    if (inThisThread()) {
        ret = addEvent(socket, EPOLLIN|EPOLLOUT);
    } else {
        lock();
        waitQueue.push_back(boost::bind(&Epoller::addRW, this, socket));
        unlock();
    }
    return ret;
}

int Epoller::removeEvent(Socket* socket) {
    lock();
    _removeEvent(socket);
    unlock();
    return 0;
}

void Epoller::lock() {
    pthread_mutex_lock(&_mutex);
}

void Epoller::unlock() {
    pthread_mutex_unlock(&_mutex);
}

int Epoller::createEpoll() {
    pthread_mutex_init(&_mutex, NULL);
    _stop = false;
    int sock = epoll_create(EPOLL_MAX_LISTEN_NUMBER);
    if (sock < 0) {
        return sock;
    }
    NOTICE("create epoll socket:%d", sock);
    _epoll_socket = sock;
    _active_events = NEW Event[EPOLL_MAX_LISTEN_NUMBER];
    if (_active_events == NULL) {
        FATAL("new active events failed");
        return -1;
    }
    return 0;
}

int Epoller::_removeEvent(Socket* socket) {
    int sockfd = socket->fd();
    int epsfd = _epoll_socket;
    NOTICE("del port in epoll %d", epsfd);
    int ret = epoll_ctl(_epoll_socket, EPOLL_CTL_DEL, sockfd, NULL);
    if( ret < 0 ){
        FATAL("add socket:%d into epoll fd:%d failed", sockfd, epsfd);
        return -1;
    }
    return 0;
}

int Epoller::addEvent(Socket* socket, uint32_t op_types) {
    int sockfd = socket->fd();

    struct epoll_event* event = NEW struct epoll_event;
    event->data.fd = sockfd;
    event->data.ptr = (void*)socket;
    event->events = op_types;

    int epsfd = _epoll_socket;
    const char* ev = op_types==EPOLLIN ? "epoll_in" : "epoll_out";
    NOTICE("add %s port in epoll %d", ev, epsfd);
    int ret = epoll_ctl(_epoll_socket, EPOLL_CTL_ADD, sockfd, event);
    if( ret < 0 ){
        FATAL("add socket:%d into epoll fd:%d failed errno:%d %s", sockfd, epsfd, errno, strerror(errno));
        return -1;
    }
    return 0;
}

int Epoller::poll(Event* list) {
    NOTICE("epoll wait on %d list:%p size:%d", _epoll_socket, list, 10);
    int ret = epoll_wait(_epoll_socket, list, 10, -1);
    if (ret < 0) {
        perror("poll failed:");
    }
    return ret;
}

void Epoller::loop() {
    while(!_stop) {
        sleep(1);
        int nfds = poll(_active_events);
        NOTICE("get %d events", nfds);
        if (nfds < 0) {
            FATAL("poll failed: %d", nfds);
            return;
        }
        for(int i = 0; i < nfds; ++i) {
            Socket* socket = (Socket*)_active_events[i].data.ptr;
            int fd = socket->fd();
            if (socket == NULL) {
                FATAL("find socket for fd[%d] failed", fd);
            //    continue;
            }
            NOTICE("handle event in %d", fd);
            int ret = socket->handle(_active_events[i]);
            if (ret != 0) {
                WARNING("handle failed");
                removeEvent(socket);
            }
        }
        if (waitQueue.empty()) {
            continue;
        }
        std::vector<DelayFunctor>::iterator iter;
        for (iter = waitQueue.begin(); iter != waitQueue.end(); ++iter) {
            (*iter)();
        }
    } //while !stop
}

}
