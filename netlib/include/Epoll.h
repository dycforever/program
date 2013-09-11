#ifndef __EPOLLER_H__
#define __EPOLLER_H__

#include "Socket.h"
#include "common.h"

namespace dyc {

typedef struct epoll_event Event;

class Epoller {
public:
    Epoller():_stop(false) {}
    ~Epoller() {pthread_mutex_destroy(&_mutex);}
    int createEpoll();

    int addRead(Connection*);
    int addWrite(Connection*);
    int addEvent(Connection* conn, uint32_t op_types);
    int removeEvent(Connection* conn);
    int poll(Event*);
    void loop();
    void stop() {_stop = true;}

//    int add_listen_port(int socket);
private:
    void lock();
    void unlock();
    pthread_mutex_t _mutex;
    int m_epoll_socket;
    bool _stop;
    // if need
//    EventList m_listen_events;
    Event* m_active_events;
    int _removeEvent(Connection* conn);

    static const int EPOLL_MAX_LISTEN_NUMBER=500;
};

inline int Epoller::addRead(Connection* conn) {
    return addEvent(conn, EPOLLIN);
}

inline int Epoller::addWrite(Connection* conn) {
    lock();
    addEvent(conn, EPOLLOUT);
    unlock();
    return 0;
}

inline int Epoller::removeEvent(Connection* conn) {
    lock();
    _removeEvent(conn);
    unlock();
    return 0;
}

inline void Epoller::lock() {
    pthread_mutex_lock(&_mutex);
}

inline void Epoller::unlock() {
    pthread_mutex_unlock(&_mutex);
}

inline int Epoller::createEpoll() {
    pthread_mutex_init(&_mutex, NULL);
    _stop = false;
    int sock = epoll_create(EPOLL_MAX_LISTEN_NUMBER);
    if (sock < 0) {
        return sock;
    }
    NOTICE("create epoll socket:%d", sock);
    m_epoll_socket = sock;
    m_active_events = NEW Event[EPOLL_MAX_LISTEN_NUMBER];
    if (m_active_events == NULL) {
        FATAL("new active events failed");
        return -1;
    }
    return 0;
}

inline int Epoller::_removeEvent(Connection* conn) {
    int sockfd = conn->fd();
    int epsfd = m_epoll_socket;
    NOTICE("del port in epoll %d", epsfd);
    int ret = epoll_ctl(m_epoll_socket, EPOLL_CTL_DEL, sockfd, NULL);
    if( ret < 0 ){
        FATAL("add socket:%d into epoll fd:%d failed", sockfd, epsfd);
        return -1;
    }
    return 0;
}

inline int Epoller::addEvent(Connection* conn, uint32_t op_types) {
    int sockfd = conn->fd();

    struct epoll_event* event = NEW struct epoll_event;
    event->data.fd = sockfd;
    event->data.ptr = (void*)conn;
    event->events = op_types;

    int epsfd = m_epoll_socket;
    const char* ev = op_types==EPOLLIN ? "epoll_in" : "epoll_out";
    NOTICE("add %s port in epoll %d", ev, epsfd);
    int ret = epoll_ctl(m_epoll_socket, EPOLL_CTL_ADD, sockfd, event);
    if( ret < 0 ){
        FATAL("add socket:%d into epoll fd:%d failed", sockfd, epsfd);
        return -1;
    }
    return 0;
}

inline int Epoller::poll(Event* list) {
    NOTICE("epoll wait on %d list:%p size:%d", m_epoll_socket, list, 10);
    int ret = epoll_wait(m_epoll_socket, list, 10, 100);
    if (ret < 0) {
        perror("poll failed:");
    }
    return ret;
}

inline void Epoller::loop() {
    while(!_stop) {
        int nfds = poll(m_active_events);
        NOTICE("get %d events", nfds);
        if (nfds < 0) {
            FATAL("poll failed: %d", nfds);
            return;
        }
        for(int i = 0; i < nfds; ++i) {
            int fd = m_active_events[i].data.fd;
            Connection* conn = (Connection*)m_active_events[i].data.ptr;
            if (conn == NULL) {
                FATAL("find conn for fd[%d] failed", fd);
            //    continue;
            }
            NOTICE("handle event in %d", fd);
            int ret = conn->handle(m_active_events[i]);
            if (ret == 0) {
                removeEvent(conn);
            }
        }
    } //while !stop
}

inline void* epollerRun(void* p) {
    Epoller* epoller = (Epoller*)p;
    epoller->loop();
    return NULL;
}

//class EpollTask : public Task {
//public:
//    EpollTask(Epoller* poller) {
//        _param = reinterpret_cast<void*>(poller);
//    }
//
//    void* run(void* p) {
//        Epoller* poller = reinterpret_cast<Epoller*>(p);
//        poller->loop();
//        return NULL;
//    }
//};

}
#endif
