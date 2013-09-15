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

class DownloadServer {

public:

    typedef uint64_t Head;

    class Task {
        public:

        Task(char* data, size_t len):_data(data), _len(len) {
        }
        char* _data;
        size_t _len;
    };

    DownloadServer():_readingTask(NULL), _processingHead(false) {
    }

    int recvData(Socket* socket) {
        if (!_processingHead && _readingTask == NULL) {
            _processingHead = true;
            _readingTask = NEW Task((char*)&_head, sizeof(_head));
            _rpos = _readingTask->_data;
            _needRead = _readingTask->_len;
            DEBUG("OK, Let's process a new request len:%lu", _needRead);
        }

        if (_readingTask == NULL) {
            _processingHead = false;
            char* buf = NEW char[_head];
            _readingTask = NEW Task(buf, _head);
            _rpos = _readingTask->_data;
            _needRead = _readingTask->_len;
            DEBUG("OK, now it's a request bodylen:%lu", _needRead);
        }

        int hasRead = socket->recv(_rpos, _needRead);
        CHECK_ERRORNO(-1, hasRead >= 0, "socket[%d] read failed", socket->fd());

        _needRead -= hasRead;
        _rpos += hasRead;

        if (_needRead == 0) {
            DEBUG("_needRead = 0");
            if (_processingHead) {
                DEBUG("get head %lu", _head);
            }
            if (!_processingHead) {
                Task* task = createSendTask(_readingTask->_data);
                pushWrite(task);
            }
            DELETE(_readingTask);
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
        if (_writingTask != NULL) {
            _writingTask = getNextTask(_writeTasks);
            if (_writingTask == NULL) 
                return 0;
            _wpos = _writingTask->_data;
            _wlen = _writingTask->_len;
        }
        DEBUG("begin to send file");
        int hasWrite = socket->send(_wpos, _wlen);
        CHECK_ERRORNO(-1, hasWrite >= 0, "socket[%d] write failed", socket->fd());

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
    size_t _needRead;
    bool _processingHead;

    Head _head;
};

int main(int argc, char** argv) {
//    InetAddress addr("172.17.229.85", 8714);
    int port = 8714;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    InetAddress addr("127.0.0.1", port);
    Server server(addr);
    DownloadServer downloader;
    server.setReadCallback(bind(&DownloadServer::recvData, &downloader, _1));
    server.setWriteCallback(bind(&DownloadServer::sendData, &downloader, _1));
    server.start();
}
