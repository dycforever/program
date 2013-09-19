

#include "common.h"
#include "Socket.h"
#include "Task.h"

namespace dyc {

RecvTask::RecvTask():_hpos((char*)&_head), _needRead(sizeof(Head)){
    _data = NULL;
    _bpos = NULL;
    _finish = false;
}


int RecvTask::readHead(Socket* socket) {
    DEBUG("begin to read head");
    if (_hpos == AFTER(&_head)) {
        return 0;
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

int RecvTask::readBody (Socket* socket) {
    DEBUG("begin to read body");
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

}


