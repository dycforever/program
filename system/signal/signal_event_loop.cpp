#include "signal_event_loop.h"
#include <signal.h>
#include <iostream>

bool SignalEventLoop::sSignoArray[sMaxSigno];

SignalEventLoop::SignalEventLoop() 
{
}

SignalEventLoop::~SignalEventLoop() 
{
}

bool SignalEventLoop::Start()
{
    sigset_t set;
    sigemptyset(&set);
    for ( ;; ) {
        std::cout << "goto sigsuspend" << std::endl; 
        sigsuspend(&set);
        std::cout << "sigsuspend awake" << std::endl;
        sleep(5);
        //while (sleep(5) == -1) {
        //           ;
        //}

        for (int i = 0; i < sMaxSigno; i++) {
            if (sSignoArray[i]) {
                sSignoArray[i] = false;
                std::map<int, EventCallBackFunc>::iterator it = 
                    mEventCallBackMap.find(i);
                if (it != mEventCallBackMap.end()) {
                    (it->second)();
                } else {
                    std::cout << "receive signal without callback function";
                }
            }
        }
    }

    return true;
}

bool SignalEventLoop::RegistEventCallBackFunc(int signo,
        const EventCallBackFunc &callBack)
{ 
    mEventCallBackMap[signo] = callBack;
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = SignalEventLoop::SignalHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(signo, &sa, NULL) == -1) {
        return false;
    }
    return true;
}

void SignalEventLoop::SignalHandler(int signo)
{
    sSignoArray[signo] = true;
//    std::cout << "in signal" << signo << std::endl;
    psignal(signo, "receive signal:");
}
