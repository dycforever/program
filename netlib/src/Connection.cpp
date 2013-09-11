#include "Connection.h"
#include "util.h"

namespace dyc {
Connection::Connection(int fd) {
    _sockfd = fd;
//    peerAddr = ;
}

Connection::Connection(int fd, const char* ip, uint16_t port) {
    peerAddr = InetAddress(ip, port);
    _sockfd = fd;
//    peerAddr = ;
}

int Connection::establish() {

   const struct sockaddr_in& sockAddr = peerAddr.getSockAddrInet();
   int ret = ::connect(_sockfd, ::sockaddr_cast(&sockAddr), static_cast<socklen_t>(sizeof sockAddr));
   if (ret < 0) {
        FATAL("ret:%d bind socket[%d] raw_ip[%s] port[%u] Die errno[%d] with %s", 
                ret, _sockfd, inet_ntoa(sockAddr.sin_addr), ntohs(sockAddr.sin_port), errno, strerror(errno));
   }
   return ret; 
}

uint64_t writeMesg(SendMesg* mesg) {
    char* end = NULL;
    if (mesg->isBody) {
        end = &head + sizeof(head);
    } else {
        end = _data + _length;
    }

BEGIN_SEND:
    uint64_t left = (uint64_t)(end - ptr);
    if (left > 0) {
        uint64_t nwrite = write(_sockfd, mesg->ptr, left);
        if (nwrite < 0 && errno != EAGAIN) {
                FATAL("write failed with errno:%d %s", errno, strerror());
                return (uint64_t)-1;
        } else {
            mesg->ptr += nwrite;
            left -= nwrite;
        }
    }
    if (mesg->isBody) {
        ptr = _data;
        end = _data + _length;
        goto BEGIN_SEND;
    }
    return left;
}

int Connection::writeCallback() {
    NOTICE("calling write callback");
    while (_onWrite == NULL) {
        if (_sendMesgList.size() == 0) {
            NOTICE("no more need write");
            return 0;
        }
        _onWrite = _sendMesgList.front();
        _sendMesgList.pop_front();

        uint64_t ret = writeMesg(_onWrite);
        if (ret == 0) {
            _onWrite->post();
            _onWrite = NULL;
            continue;
        } else if (ret == (uint64_t)-1) {
            return -1;
        }
        break;
    }
    return 1;
}


uint64_t Connection::readMesg(RecvMesg* mesg) {

}

uint64_t Connection::parseHead() {
    char* end = (char*)&_headHasRead + sizeof(_headHasRead);
    int leng = end - _headReadingPtr;
    uint64_t nread = read(_sockfd, _headReadingPtr, length);
    _headReadingPtr += nread;
    if (_headReadingPtr == end) {
        return 0;
    }
}

int Connection::readCallback() {
    if (_isReadingHead) {
        if (parseHead() == 0) {
            sem_post(&_waitMesg);
            _isReadingHead = false;
        }
    }
    if (_onRead == NULL) {
        if (_recvMesgList.get(_headHasRead) == NULL) {
            NOTICE("no more need write");
        }
        uint64_t ret = 0;
        ret = readMesg(_onRead);
        if (ret == 0) {
            _onRead->post();
            _onRead = NULL;
            _isReadingHead = true;
        }
    }

    return 0;
}

// return 0 means the socket can be removed
int Connection::handle(const epoll_event& event) {
    int ret = 0;
    if (event.events & EPOLLIN) {
        DEBUG("will read callback");
        ret = readCallback();
    } else if (event.events & EPOLLOUT) {
        DEBUG("will write callback");
        ret = writeCallback();
    } else {
        ret = -1;
        NOTICE("unknow event");
    }
    if (ret < 0) {
        errorCallback();
    }
    return ret;
}

SendMesg* Connection::pushSendTask(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize) {
    SendMesg* mesg = NEW SendMesg(srcRank, destRank, tag, sendBuf, bufferSize);

    if (mesg == NULL) {
        FATAL("new send mesg failed");
        return NULL;
    }
    _sendMesgList.push_back(mesg);
    return mesg;
}

RecvMesg* Connection::pushRecvTask(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize) {
    RecvMesg* mesg = NEW RecvMesg(srcRank, destRank, tag, sendBuf, bufferSize);

    if (mesg == NULL) {
        FATAL("new send mesg failed");
        return NULL;
    }
    _recvMesgList.push_back(mesg);
    return mesg;
}

}
