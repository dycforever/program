
#include <boost/bind.hpp>

#include "Connection.h"
#include "EventLoop.h"
#include "util.h"

namespace dyc {

Connection::Connection(Socket* socket, EventLoop* loop): _writingTask(NULL), _readingTask(NULL), 
                                        _processingHead(false), _socket(socket),
                                        _loop(loop) {
    _socket->setReadCallback(boost::bind(&Connection::recvData, this, _socket));
    _socket->setWriteCallback(boost::bind(&Connection::sendData, this, _socket));
}

int Connection::recvData(Socket* socket) {
    int headret = 0;
    if (_readingTask == NULL) {
        _readingTask = NEW RecvTask();
    }
    headret = _readingTask->readHead(socket);
    if(headret > 0) {
        return 0;
    } else if (headret != 0) {
        FATAL("read head failed");
        return -1;
    }
    // headret == 0

    int bodyret = 0;
    bodyret = _readingTask->readBody(socket);

    if (bodyret == 0) {
        _loop->remove(socket);
        DELETE(socket);
    } else if(bodyret < 0) {
        FATAL("read body failed");
        return -1;
    }
    if (_readingTask->over()) {
        _processingHead = false;
        // TODO create RecvData and call read complete callback !!
        SendTask* task = _readCallback(_readingTask);
        pushWrite(task);
        socket->enableWrite();
        _loop->updateSocket(socket);
        DELETE(_readingTask);
    }

    return 0;
}

int Connection::send(const char* data, int64_t size) {
    SendTask* task = NEW SendTask(data, size);
    pushWrite(task);
    _socket->enableWrite();
    _loop->updateSocket(_socket);
    return 0;
}

int Connection::pushWrite(SendTask* task) {
    MutexLockGuard lock(_listMutex);
    _writeTasks.push_back(task);
    return 0;
}

SendTask* Connection::getNextTask(std::list<SendTask*>& list) {
    MutexLockGuard lock(_listMutex);
    if (list.empty()) {
        return NULL;
    }
    CHECK_ERROR(NULL, !list.empty(), "list is empty");
    SendTask* task = list.front();
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
            socket->disableWrite();
            _loop->updateSocket(socket);
            return 0;
        }
        _wpos = _writingTask->_data;
        _wlen = _writingTask->_len;
    }
    DEBUG("begin to send %p len: %lu", _wpos, _wlen);
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
