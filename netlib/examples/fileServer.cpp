#include <iostream>
#include <list>

#include <boost/bind.hpp>
#include "netlib.h"
#include "Task.h"

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

typedef boost::shared_ptr<SendTask> SendTaskPtr;
typedef boost::function< SendTaskPtr (RecvTask*) > ReadCallbackFunc;

SendTaskPtr replyFileSize(RecvTask* task) {
    char* path = task->getData();
    DEBUG("look for file [%s]", path);
    uint64_t* len = NEW uint64_t;
    int ret = getFileSize(path, *len);
    CHECK_ERROR(SendTaskPtr(), ret==0, "get file[%s] size failed", path);

    Head head(8, 0);
    SendTaskPtr sendtask( NEW SendTask(head, (char*)len) );
    return sendtask;
}


void* serverRun(void* p) {
    Server* server = (Server*) p;
    server->start();
    return NULL;
}

int main(int argc, char** argv) {
//    InetAddress addr("172.17.229.85", 8714);
    int port = 8714;
    if (argc > 1) {
        port = atoi(argv[1]);
    }
    InetAddress addr("127.0.0.1", port);
    Server server(addr);
    server.setReadCallback(bind(&replyFileSize, _1));
    pthread_t pid;
    pthread_create(&pid, NULL, serverRun, &server);
    getchar();
    NOTICE("server will quit");
    dumpUnfreed();
    server.stop();
    pthread_join(pid, NULL);
}

