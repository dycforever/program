
#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

#include <sys/unistd.h>
#include <fcntl.h>

#include "Socket.h"
#include "InetAddress.h"

using namespace dyc;

void* thread_function (void* pp) {
    sleep(1);
    return NULL;
}

int main() {
    char c;
    pid_t pid;
    pid = getpid();
    printf ("my pid is %d\n", pid);

    pid = fork();
    if (pid > 0) {
        printf("my child: %d\n", pid);
    } else if (pid == 0) {
        // process state: S+ now
        printf("press key to new session:\n");
        fflush(stdout);
        getchar();
//        pid = setsid();
//        if (pid < 0) {
//            printf("errno = %d, %s\n", errno, strerror(errno));
//        }
        // process state: Ss now
        printf ("session pid = %d\n", pid);
        fflush(stdout);
        while(1) {sleep(1);}
    } else {
        printf("error: %d, %s\n", errno, strerror(errno));
        fflush(stdout);
    }


    pthread_t tid;
    pthread_create(&tid, NULL, thread_function, NULL);

    c = getchar();
    printf ("getchar: %c parent exit\n", c);
    fflush(stdout);
}


