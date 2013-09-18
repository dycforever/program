#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include <list>
#include <sys/epoll.h>
#include <semaphore.h>

#include "InetAddress.h"

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

class Task {
    public:

    typedef uint64_t Head;
    Task():_hpos((char*)&_head), _needRead(sizeof(Head)){
        _data = NULL;
         _bpos = NULL;
    }

    Task(char* data, size_t len): _data(data), _len(len){
    }

    char* _data;
    size_t _len;
    
    char* _hpos;
    char* _bpos;
    Head _head;
    size_t _needRead;


    int readHead(Socket* socket) {
        if (_hpos == AFTER(&_head)) {
            return true;
        }

        int count = socket->recv(_hpos, _needRead);
        CHECK_ERRORNO(-1, count >= 0, "socket[%d] read failed", socket->fd());
        if (count == 0) {
            remove from epoll
            DELETE(socket);
        }
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
        if (_bpos != _data + _head) {
            int count = socket->recv(_bpos, _needRead);
            CHECK_ERRORNO(-1, count >= 0, "socket[%d] read failed", socket->fd());
            if (count == 0) {
                WARNING("no body whith head: %lu", _head);
                remove from epoll
                DELETE(socket);
            }
            _bpos += count;
            _needRead -= count;
            if (_needRead == 0) {
                *(_bpos) = 0;
            }
        }
        return _needRead;
    }
};

class Task;

class Connection {
public:
    explicit Connection(Socket*);
    int64_t send(const char* data, int64_t size);

private:
    MutexLock _listMutex;
    list<Task*> _writeTasks;
    Task* _writingTask;
    size_t _wlen;
    char* _wpos;

    list<Task> _readTasks;
    Task* _readingTask;
    char* _rpos;
    bool _processingHead;

    InetAddress localAddr;
    InetAddress peerAddr;
    Socket* _socket;
};

}

#endif
