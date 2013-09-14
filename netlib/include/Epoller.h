#ifndef __EPOLLER_H__
#define __EPOLLER_H__

#include "Socket.h"
#include "common.h"

namespace dyc {


class Epoller {
public:

    typedef struct epoll_event Event;
    Epoller();
    ~Epoller() {pthread_mutex_destroy(&_mutex);}
    int createEpoll();

    int addRead(Socket*);
    int addWrite(Socket*);
    int addRW(Socket*);
    int addEvent(Socket* socket, uint32_t op_types);
    int removeEvent(Socket* socket);
    int poll(Event*);

    static const int EPOLL_MAX_LISTEN_NUMBER=500;

private:
    void lock();
    void unlock();
    int _removeEvent(Socket* socket);

    pthread_mutex_t _mutex;
    int _epoll_socket;
};

inline void* epollRun(void* p) {
    return p;
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
