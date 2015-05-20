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
    sigaddset(&set, SIGUSR2);
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
    std::cout << "begin run" << std::endl;
    loop.RegistEventCallBackFunc(SIGHUP, std::tr1::bind(&onReload));
    loop.RegistEventCallBackFunc(SIGUSR1, std::tr1::bind(&onChildSuc));
    loop.RegistEventCallBackFunc(SIGQUIT, std::tr1::bind(&onQuit));
    loop.RegistEventCallBackFunc(SIGCHLD, std::tr1::bind(&onChildExit));

    BlockSignal();
    pid_t pid = fork();
    if (pid > 0) {
        // parent
        // loop.Start();
        while(1) {;}
    } else if (pid == 0) {
        // child
        // loop.Start();
        while(1) {;}
    }

}
