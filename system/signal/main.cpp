#include <signal.h>
#include <iostream>
#include "signal_event_loop.h"

void BlockSignal()
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGHUP);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGTERM);
    sigaddset(&set, SIGPIPE);
    sigaddset(&set, SIGUSR1);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);
}

void UnblockSignal(int signo)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, signo);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
}

void IgnoreSignal(int signo)
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sigaction(signo, &sa, NULL);

}

void onReload()
{
    std::cout << "handle SIG QUIT" << std::endl;
} 

void onChildSuc()
{
    std::cout << "handle SIG USR1" << std::endl;
} 

void onChildExit()
{
    std::cout << "handle SIG CHLD" << std::endl;
} 

void onQuit()
{
    std::cout << "handle SIG QUIT" << std::endl;
} 

int main() 
{
    SignalEventLoop loop;
    loop.RegistEventCallBackFunc(SIGHUP, std::tr1::bind(&onReload));
    loop.RegistEventCallBackFunc(SIGUSR1, std::tr1::bind(&onChildSuc));
    loop.RegistEventCallBackFunc(SIGQUIT, std::tr1::bind(&onQuit));
    loop.RegistEventCallBackFunc(SIGCHLD, std::tr1::bind(&onChildExit));

    std::cout << "signal hander registered, press key to block siganl:" << std::endl;
    while (getchar() == -1) {
        ;
    }
    BlockSignal();

    std::cout << "signal blocked, press key to unblock CHLD siganl:" << std::endl;
    while (getchar() == -1) {
        ;
    }
    UnblockSignal(SIGCHLD);
    std::cout << "press key to start loop" << std::endl;
    BlockSignal();
    IgnoreSignal(SIGPIPE);
    while (getchar() == -1) {
        ;
    }
    loop.Start();
}
