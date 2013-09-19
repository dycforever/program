
#ifndef TASK_H
#define TASK_H

namespace dyc {


#define AFTER(p) ((char*)p)+sizeof(*p)

class SendTask {
public:
    SendTask(const char* data, size_t len):_data(data), _len(len){;}
    const char* _data;
    size_t _len;

};

class Socket;

class RecvTask {
public:
    bool over() {
        return _finish;
    }
    RecvTask();
    ~RecvTask() {
        DELETES(_data);
    }
    char* getData() { return _data; }

    int readHead(Socket* socket);
    int readBody (Socket* socket);

private:
    typedef uint64_t Head;
    char* _data;
    char* _hpos;
    char* _bpos;

    Head _head;
    size_t _needRead;
    bool _finish;

    friend class Connection;
};

}

#endif
