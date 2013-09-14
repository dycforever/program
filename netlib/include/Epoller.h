#ifndef __EPOLLER_H__
#define __EPOLLER_H__

#include "Socket.h"
#include "common.h"

namespace dyc {

typedef struct epoll_event Event;

class Epoller {
public:
    typedef boost::function<void()> DelayFunctor;

    Epoller();
    ~Epoller() {pthread_mutex_destroy(&_mutex);}
    int createEpoll();

    int addRead(Socket*);
    int addWrite(Socket*);
    int addRW(Socket*);
    int addEvent(Socket* socket, uint32_t op_types);
    int removeEvent(Socket* socket);
    int poll(Event*);
    void loop();
    void stop() {_stop = true;}

private:
    static const int EPOLL_MAX_LISTEN_NUMBER=500;

    void lock();
    void unlock();
    int _removeEvent(Socket* socket);
    bool inThisThread();

    pthread_mutex_t _mutex;
    int _epoll_socket;
    bool _stop;
    Event* _active_events;
    std::vector<DelayFunctor> waitQueue;
    pthread_t _threadId;
};

inline void* epollRun(void* p) {
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
