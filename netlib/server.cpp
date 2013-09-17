#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include "netlib.h"

using namespace dyc;
using namespace std;
using namespace boost;

int showRead(Socket* socket) {
    int fd = socket->fd();
    char buf[1024];
    int count = read(fd, buf, 1024);
    if (count < 0) {
        FATAL("fd[%d] errno[%d]: %s", fd, errno, strerror(errno));
        return -1;
    }
    if (count == 0) {
        DEBUG("recv 0 byte now will close fd[%d]", fd);
        close(fd);
    }
    buf[count] = 0;
    DEBUG("recv %d bytes: %s", count, buf);
    return 0;
}

int echoWrite(Socket* socket) {
    int fd = socket->fd();
    char buf[] = "hello back";
    int count = write(fd, buf, sizeof(buf));
    if (count < 0) {
        FATAL("fd[%d] errno[%d]: %s", fd, errno, strerror(errno));
        return -1;
    }

    DEBUG("send back %lu bytes: %s", sizeof(buf), buf);
    return 0;
}

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
            DELETE(socket);
        }
        _hpos += count;
        _needRead -= count;

        if (_needRead == 0) {
            _data = NEW char[_head];
            _needRead = _head;
            _bpos = _data;
            DEBUG("finish read head %lu", _head);
            return 0;
        }
        return 1;
    }

    int readBody (Socket* socket) {
        if (_bpos != _data + _head) {
            int count = socket->recv(_bpos, _needRead);
            CHECK_ERRORNO(-1, count >= 0, "socket[%d] read failed", socket->fd());
            if (count == 0) {
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

class Connection {
public:

    Connection():_writingTask(NULL), _readingTask(NULL), _processingHead(false) {
    }

    int recvData(Socket* socket) {
        int headret = 0;
        if (_readingTask == NULL) {
            _readingTask = NEW Task();
        }
        headret = _readingTask->readHead(socket);
        if(headret == 1) {
            return 0;
        } else if (headret != 0) {
            FATAL("read head failed");
            return -1;
        }

        int bodyret = 0;
        bodyret = _readingTask->readBody(socket);

        if (bodyret == 0) {
            Task* task = createSendTask(_readingTask->_data);
            DEBUG("push task %p", task->_data);
            pushWrite(task);
            // TODO
            DELETE(_readingTask);
        } else if(bodyret < 0) {
            FATAL("read body failed");
            return -1;
        }

        return 0;
    }

    Task* createSendTask(char* path) {
        DEBUG("look for file %s", path);
        uint64_t len;
        int ret = getFileSize(path, len);
        CHECK_ERROR(NULL, ret==0, "get file[%s] size failed", path);
        char* buf = NEW char[len];
        FILE* fp = fopen(path, "r");
        uint64_t hr = fread(buf, 1, len, fp);
        CHECK_ERROR(NULL, hr==len, "read file[%s] size failed: read %lu", path, hr);
        DEBUG("read file %lu bytes: %p", hr, buf);

        Task* task = NEW Task(buf, len);
        return task;
    }

    void pushWrite(Task* task) {
        MutexLockGuard lock(_listMutex);
        _writeTasks.push_back(task);
    }

    Task* getNextTask(list<Task*>& list) {
        MutexLockGuard lock(_listMutex);
        if (list.empty()) {
            return NULL;
        }
        CHECK_ERROR(NULL, !list.empty(), "list is empty");
        Task* task = list.front();
        list.pop_front();
        return task;
    }

    void readTaskComplete() {
        _processingHead = false;
    }

    int sendData(Socket* socket) {
        DEBUG("this time _writingTask:%p", _writingTask);
        if (_writingTask == NULL) {
            _writingTask = getNextTask(_writeTasks);
            if (_writingTask == NULL) 
                return 0;
            _wpos = _writingTask->_data;
            _wlen = _writingTask->_len;
        }
        DEBUG("begin to send file");
        int hasWrite = socket->send(_wpos, _wlen);
        CHECK_ERRORNO(-1, hasWrite >= 0, "socket[%d] write %p failed", socket->fd(), _wpos);

        _wlen -= hasWrite;
        _wpos += hasWrite;

        if (_wlen == 0) {
            // TODO
//           _writeComplete(_writingTask);
            _writingTask = NULL;
        }
        return 0;
    }

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

};

int main(int argc, char** argv) {
//    InetAddress addr("172.17.229.85", 8714);
    int port = 8714;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    InetAddress addr("127.0.0.1", port);
    Server server(addr);
    Connection downloader;
    server.setReadCallback(bind(&Connection::recvData, &downloader, _1));
    server.setWriteCallback(bind(&Connection::sendData, &downloader, _1));
    server.start();
}
