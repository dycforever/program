#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <list>
#include <sys/epoll.h>
#include <semaphore.h>
#include <boost/shared_ptr.hpp>

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
//    typedef boost::shared_ptr<Socket> SocketPtr;
    typedef Socket* SocketPtr;
    typedef boost::shared_ptr<SendTask> SendTaskPtr;
    typedef boost::function< SendTaskPtr (RecvTask*) > CallbackFunc;

    explicit Connection(SocketPtr, boost::shared_ptr<EventLoop>);
    int send(const char* data, int64_t size);
    int rawSend(SendTaskPtr task);
    void setReadCallback(CallbackFunc cb) { _readCallback = cb;}

private:
    int recvData(SocketPtr socket);
    int sendData(SocketPtr socket);
    SendTaskPtr getNextTask(std::list<SendTaskPtr>& list);
    void readTaskComplete();

    int pushWrite(SendTaskPtr task);

    MutexLock _listMutex;
    std::list<SendTaskPtr> _writeTasks;
    SendTaskPtr _writingTask;

    RecvTask* _readingTask;
    char* _rpos;
    bool _processingHead;

    InetAddress localAddr;
    InetAddress peerAddr;
    SocketPtr _socket;

    boost::shared_ptr<EventLoop> _loop;

    CallbackFunc _readCallback;

};

}

#endif
