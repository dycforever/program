#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <list>
#include <sys/epoll.h>
#include <semaphore.h>

#include "InetAddress.h"
#include "Mutex.h"
#include "Socket.h"
#include "Task.h"

namespace dyc {

struct MNTLHead {
    int32_t srcRank;
    int32_t destRank;
    int32_t tag;

    MNTLHead(
        int32_t src,
        int32_t dest,
        int32_t tag_):srcRank(src), destRank(dest), tag(tag_) {
    }
};


class EventLoop;

class Connection {
public:
    typedef boost::function< SendTask* (RecvTask*) > CallbackFunc;
    explicit Connection(Socket*, EventLoop*);
    int send(const char* data, int64_t size);
    void setReadCallback(CallbackFunc cb) { _readCallback = cb;}

private:
    int recvData(Socket* socket);
    int sendData(Socket* socket);
    SendTask* getNextTask(std::list<SendTask*>& list);
    void readTaskComplete();

    int pushWrite(SendTask* task);

    MutexLock _listMutex;
    std::list<SendTask*> _writeTasks;
    SendTask* _writingTask;

    RecvTask* _readingTask;
    char* _rpos;
    bool _processingHead;

    InetAddress localAddr;
    InetAddress peerAddr;
    Socket* _socket;

    EventLoop* _loop;

    CallbackFunc _readCallback;

    uint64_t _wlen;
    const char* _wpos;
};

}

#endif
