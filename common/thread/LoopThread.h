#ifndef UTIL_LOOP_THREAD_H
#define UTIL_LOOP_THREAD_H

#include <tr1/functional>

#include "thread/Thread.h"
#include "thread/ThreadLock.h"
#include "thread/Condition.h"

namespace dyc {

class LoopThread
{
public:
    typedef std::tr1::function<void()> ThreadFunc;

public:
    LoopThread();
    ~LoopThread();

public:
    bool Start(const ThreadFunc& loopFunc, uint32_t interval /* ms */);
    void Stop();

private:
    void Loop();

private:
    volatile bool mRunning;
    ThreadFunc mLoopFunc;
    uint32_t mInterval; //us
    Thread *mThread;
    MutexLock mMutex;
    Condition mCond;
};

}

#endif //UTIL_LOOP_THREAD_H
