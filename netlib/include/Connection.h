#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <list>
#include <sys/epoll.h>
#include <semaphore.h>

#include "InetAddress.h"
#include "Mutex.h"
#include "Socket.h"

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


#define AFTER(p) ((char*)p)+sizeof(*p)

class SendTask {
public:
    SendTask(const char* data, size_t len):_data(data), _len(len){;}
    const char* _data;
    size_t _len;

};

class RecvTask {
public:
    bool over() {
        return _finish;
    }

    typedef uint64_t Head;
    RecvTask():_hpos((char*)&_head), _needRead(sizeof(Head)){
        _data = NULL;
        _bpos = NULL;
        _finish = false;
    }

    char* _data;
    char* _hpos;
    char* _bpos;

    Head _head;
    size_t _needRead;
    bool _finish;

    int readHead(Socket* socket) {
        if (_hpos == AFTER(&_head)) {
            return true;
        }

        int count = socket->recv(_hpos, _needRead);
        CHECK_ERRORNO(-1, count >= 0, "socket[%d] read failed", socket->fd());
        _hpos += count;
        _needRead -= count;

        if (_needRead == 0) {
            _data = NEW char[_head];
            _needRead = _head;
            _bpos = _data;
            DEBUG("finish read head %lu", _head);
        }
        return count;
    }

    int readBody (Socket* socket) {
        int count = 0;
        if (_bpos != _data + _head) {
            count = socket->recv(_bpos, _needRead);
            CHECK_ERRORNO(-1, count >= 0, "socket[%d] read failed", socket->fd());
            if (count == 0) {
                WARNING("no body whith head: %lu", _head);
            }
            _bpos += count;
            _needRead -= count;
            if (_needRead == 0) {
                _finish = true;
            }
        }
        return count;
    }
};

class RecvTask;
class SendTask;
class EventLoop;

class Connection {
public:
    explicit Connection(Socket*, EventLoop*);
    int send(const char* data, int64_t size);

private:
    int recvData(Socket* socket);
    int sendData(Socket* socket);
    SendTask* createSendTask(char* path);
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


    uint64_t _wlen;
    const char* _wpos;
};

}

#endif
