
#ifndef TASK_H
#define TASK_H

#include <boost/shared_ptr.hpp>

namespace dyc {

#define AFTER(p) ((char*)p)+sizeof(*p)

//#pragma pack(push, 1)
struct Head {
    uint64_t _len;
    int64_t _type;
    Head(uint64_t len, int type):_len(len), _type(type) {}
};
//#pragma pack(pop)

class SendTask {
public:
    typedef Socket* SocketPtr;
    SendTask(Head head, const char* data):_head(head), _data(data) {
        FATAL("type: %d", _head._type);
        clear();
    }

    int64_t sendHead(SocketPtr);
    int64_t sendBody(SocketPtr);
    bool over() {return _finish;}
    void clear();

private:
    Head _head;
    const char* _data;
    const char* _hpos;
    const char* _bpos;
    size_t _needWrite;
    bool _finish;
};

class Socket;

class RecvTask {
public:
    typedef Socket* SocketPtr;

    bool over() { return _finish; }
    bool headFinish() { return _hpos == AFTER(&_head); }
    RecvTask();
    ~RecvTask() {
        // TODO
//        DELETES(_data);
    }
    char* getData() { return _data; }
    int clear();

    int readHead(SocketPtr socket);
    int readBody (SocketPtr socket);

    // TODO add class RecvMesg
//private:
    Head _head;
    char* _data;
    char* _hpos;
    char* _bpos;

    size_t _needRead;
    bool _finish;

    friend class Connection;
};

}

#endif