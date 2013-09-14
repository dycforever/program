#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <vector>

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "Mutex.h"
#include "Epoller.h"

namespace dyc 
{

class Socket;
class Epoller;

class EventLoop
{
 public:
    typedef boost::function<void()> DelayFunctor;
    typedef struct epoll_event Event;

    EventLoop(Epoller* );
    ~EventLoop();  // force out-line dtor, for scoped_ptr members.

    void loop();
    void quit();

    int64_t iteration() const { return iteration_; }

    void runInLoop(const DelayFunctor& cb);
    void queueInLoop(const DelayFunctor& cb);

    // internal usage
    void updateSocket(Socket* Socket);
    void removeSocket(Socket* Socket);

    bool inThisThread() {return _threadId == pthread_self();}
    static EventLoop* getEventLoopOfCurrentThread();

private:
    Event* _active_events;
    void callPendingFunctors();

    void printActiveSockets() const; // DEBUG

    typedef std::vector<Socket*> SocketList;

    bool looping_; /* atomic */
    bool quit_; /* atomic */
    bool eventHandling_; /* atomic */
    int64_t iteration_;
    pthread_t _threadId;
    boost::scoped_ptr<Epoller> _poller;

    MutexLock _mutex;
    std::vector<DelayFunctor> _waitQueue;
};

}
#endif  // EVENTLOOP_H
