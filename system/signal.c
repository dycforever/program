#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef void (*SigHandler) (int);
/*
 * int open(const char *pathname, int flags, mode_t mode)
 *
 * flags can be:
 * O_RDWR and O_WRONLY and O_RDONLY
 * O_CLOEXEC, O_CREAT, O_DIRECTORY, O_EXCL, O_NOCTTY, O_NOFOLLOW, O_TRUNC, O_TTY_INIT, O_APPEND, O_ASYNC 
 *
 * mode can be follow:
 * S_IRWXU
 * 00700 user (file owner) has read, write and execute permission
 * S_IRUSR
 * 00400 user has read permission
 * S_IWUSR
 * 00200 user has write permission
 * S_IXUSR
 * 00100 user has execute permission
 * S_IRWXG
 * 00070 group has read, write and execute permission
 * S_IRGRP
 * 00040 group has read permission
 * S_IWGRP
 * 00020 group has write permission
 * S_IXGRP
 * 00010 group has execute permission
 * S_IRWXO
 * 00007 others have read, write and execute permission
 * S_IROTH
 * 00004 others have read permission
 * S_IWOTH
 * 00002 others have write permission
 * S_IXOTH
 * 00001 others have execute permission
 * */

void signalHandler(int signo)
{
    char* file = "/home/dyc/signal.out";
    int fd = open(file, O_CREAT|O_TRUNC|O_RDWR, S_IRWXU);
    if (fd < 0) {
        printf("open fd[%d]\n", fd);
        return;
    }
    char outputBuf[1024];
    memset(outputBuf, 0, 1024);
    snprintf(outputBuf, 1024, "received signal: %s\n", strsignal(signo));

    int n = write(fd, outputBuf, strlen(outputBuf));
    if (n < 0) {
        printf("write %d errno %d: %s\n", n, errno, strerror(errno));
    }
    close(fd);
}

// see: /usr/include/bits/signum.h
char* signo2str(int signo)
{
    switch(signo) {
        case 1 : return "SIGHUP"; 
        case 2 : return "SIGINT";
        case 3 : return "SIGQUIT";
        case 4 : return "SIGILL";
        case 5 : return "SIGTRAP";
        case 6 : return "SIGABRT";
        case 7 : return "SIGBUS";
        case 8 : return "SIGFPE";
        case 9 : return "SIGKILL";
        case 10 : return "SIGUSR1"; 
        case 11 : return "SIGSEGV";
        case 12 : return "SIGUSR2";
        case 13 : return "SIGPIPE";
        case 14 : return "SIGALRM";
        case 15 : return "SIGTERM";
        case 16 : return "SIGSTKFLT";
        case 17 : return "SIGCHLD"; 
        case 18 : return "SIGCONT";
        case 19 : return "SIGSTOP";
        case 20 : return "SIGTSTP";
        case 21 : return "SIGTTIN";
        case 22 : return "SIGTTOU";
        case 23 : return "SIGURG";
        case 24 : return "SIGXCPU";
        case 25 : return "SIGXFSZ";
        case 26 : return "SIGVTALRM";
        case 27 : return "SIGPROF";
        case 28 : return "SIGWINCH"; 
        case 29 : return "SIGIO"; 
        case 30 : return "SIGPWR"; 
        case 31 : return "SIGSYS"; 
    }
}

int registEventCallBackFunc(int signo)
{ 
    struct sigaction sa;
    memset((void*)&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(signo, &sa, NULL) == -1) {
        printf("sigaction signo[%d:%s] [%s] failed\n", signo, signo2str(signo), strsignal(signo));
    }
    return 0;
}

int main()
{
    int i = 0;
    sigset_t set;
    sigemptyset(&set);
    for (i = 1; i < 32; i++) {
        if (i == SIGINT) {
            continue;
        }
        sigaddset(&set, i);
        if(registEventCallBackFunc(i) != 0) {
            return -1;
        }
    }

    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
        printf("sigprocmask block failed\n");
        return -1;
    }
    sigemptyset(&set);
    for (;;) {
        sigsuspend(&set);
        printf("suspend wake\n");
    }
}    