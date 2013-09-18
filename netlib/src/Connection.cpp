#include "Connection.h"
#include "util.h"

namespace dyc {

Connection::Connection(Socket* socket):_writingTask(NULL), _readingTask(NULL), _processingHead(false), _socket(socket) {
    _socket->setReadCallback(boost::bind(&recvData, this, _socket));
    _socket->setWriteCallback(boost::bind(&sendData, this, _socket));
}

int Connection::recvData(Socket* socket) {
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

        close fd && delete socket

    } else if(bodyret < 0) {
        FATAL("read body failed");
        return -1;
    }
    if (_readingTask->over()) {
        _processingHead = false;
        // TODO this is read complete callback !!
        Task* task = createSendTask(_readingTask->_data);
        DEBUG("push task %p", task->_data);
        pushWrite(task);

        free _readingTask->_data and data
        DELETE(_readingTask);
    }

    return 0;
}

Task* Connection::createSendTask(char* path) {
    DEBUG("look for file %s", path);
    uint64_t len;
    int ret = getFileSize(path, len);
    CHECK_ERROR(NULL, ret==0, "get file[%s] size failed", path);
    // TODO malloc callback
    char* buf = NEW char[len];
    FILE* fp = fopen(path, "r");
    uint64_t hr = fread(buf, 1, len, fp);
    CHECK_ERROR(NULL, hr==len, "read file[%s] size failed: read %lu", path, hr);
    DEBUG("read file %lu bytes: %p", hr, buf);

    Task* task = NEW Task(buf, len);
    return task;
}

int64_t Connection::send(const char* data, int64_t size) {
    Task* task = Task(data, size);
    pushWrite(Task* task);
}

void Connection::pushWrite(Task* task) {
    MutexLockGuard lock(_listMutex);
    _writeTasks.push_back(task);
    _loop->update(task, write);
}

Task* Connection::getNextTask(list<Task*>& list) {
    MutexLockGuard lock(_listMutex);
    if (list.empty()) {
        return NULL;
    }
    CHECK_ERROR(NULL, !list.empty(), "list is empty");
    Task* task = list.front();
    list.pop_front();
    return task;
}

void Connection::readTaskComplete() {
}

int Connection::sendData(Socket* socket) {
    DEBUG("this time _writingTask:%p", _writingTask);
    if (_writingTask == NULL) {
        _writingTask = getNextTask(_writeTasks);
        if (_writingTask == NULL) {
            _loop->update(task, no write);
            return 0;
        }
        _wpos = _writingTask->_data;
        _wlen = _writingTask->_len;
    }
    DEBUG("begin to send file");
    int hasWrite = socket->send(_wpos, _wlen);
    CHECK_ERRORNO(-1, hasWrite >= 0, "socket[%d] write %p failed", socket->fd(), _wpos);

    _wlen -= hasWrite;
    _wpos += hasWrite;

    if (_wlen == 0) {
        // TODO _writeComplete(_writingTask);
         
        _writingTask = NULL;
    }
    return 0;
}

}
