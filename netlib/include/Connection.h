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

class SendMesg {
public:
    SendMesg(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize) :head(srcRank, destRank, tag),
                                       _data(sendBuf), _length(bufferSize) {
        isBody = false;
        _ptr = &head;
        sem_init(&sem, 0, 0);
    }

    void wait() {
        sem_wait(&sem);
    }

    void post() {
        sem_post(&sem);
    }

private:
    MNTLHead head;
    const void* _data;
    uint64_t _length;

    bool isBody;
    void* _ptr;
    sem_t sem;

friend class Connection;
};

class RecvMesg {
public:
    RecvMesg(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize) :head(srcRank, destRank, tag),
                                       _data(sendBuf), _length(bufferSize) {
        isBody = false;
        _ptr = &head;
        sem_init(&sem, 0, 0);
    }

    void wait() {
        sem_wait(&sem);
    }

    void post() {
        sem_post(&sem);
    }

private:
    MNTLHead head;
    const void* _data;
    uint64_t _length;

    bool isBody;
    void* _ptr;
    sem_t sem;
};


    RecvMesg* pushSendTask(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize);

    RecvMesg* pushRecvTask(
        int32_t           srcRank,
        int32_t           destRank,
        int32_t           tag,
        const void        *sendBuf,
        uint32_t          bufferSize);



class Connection {
public:
    explicit Connection(int);
    Connection(int, const char* ip, uint16_t port);

    int handle(const epoll_event& event);
    int writeCallback();
    int readCallback();

    uint64_t writeMesg(SendMesg*);
    int fd(){return _socket;}
    int establish();
private:
    int _socket;
    std::list<SendMesg*> _sendMesgList;
    std::list<RecvMesg*> _recvMesgList;
    SendMesg* _onWrite;
    RecvMesg* _onRead;
    InetAddress localAddr;
    InetAddress peerAddr;

    bool _isReadingHead;
    MNTLHead _headHasRead;
    char* _headReadingPtr;
    sem_t _waitMesg;
};

}

#endif
