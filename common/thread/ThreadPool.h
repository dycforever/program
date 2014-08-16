#ifndef UTIL_THREAD_POOL_H
#define UTIL_THREAD_POOL_H

#include <pthread.h>
#include <list>

#include "thread/Runnable.h"
#include "thread/Thread.h"
#include "thread/ThreadLock.h"
#include "thread/Condition.h"

namespace dyc {

class ThreadPool
{
public:
    enum TPState 
    {
        TP_RUNNING, 
        TP_STOP, 
        TP_TERMINATED 
    };

public:
    ThreadPool();
    ~ThreadPool();

public:
    bool Init(int numThreads);
    void ShutdownNow();
    void Shutdown();
    bool Execute(Runnable *runnable);

public:
    size_t GetTaskCount()   
    { return mTaskCount; }

    size_t GetFinishCount()
    { return mFinishCount; }
    
private:
    Runnable *PopTask();
    void ThreadProc();
    void WakeupAllThread();
    void WaitExit();

private:
    MutexLock mMutex;
    Condition mCond;
    std::list<Runnable*> mTaskQueue;
    volatile size_t mTaskCount;
    volatile size_t mFinishCount;

private:
    std::list<Thread*> mThreads;
    volatile TPState mState;

};
}

#endif //UTIL_THREAD_POOL_H
