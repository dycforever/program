#include "thread/ThreadPool.h"

namespace dyc {

ThreadPool::ThreadPool() 
    : mCond(mMutex),
      mTaskCount(0),
      mFinishCount(0),
      mState(TP_TERMINATED)
{
}

ThreadPool::~ThreadPool() { 
    Shutdown();
}

bool ThreadPool::Init(int numThreads)
{
    assert(numThreads > 0);
    mState = TP_RUNNING;
    for (int i = 0; i < numThreads; ++i) {
        Thread *thread = new Thread(std::tr1::bind(&ThreadPool::ThreadProc, this));
        mThreads.push_back(thread);
        thread->Start();
    }
    return true;
}

void ThreadPool::ShutdownNow()
{
    if (mState >= TP_STOP) {
        return;
    }

    mState = TP_TERMINATED;
    WakeupAllThread();
    WaitExit();

    /* free task that not be processed */
    std::list<Runnable*>::iterator it = mTaskQueue.begin();
    for (; it != mTaskQueue.end(); ++it) {
        delete *it;
    }
    mTaskQueue.clear();
    mTaskCount = 0;
}

void ThreadPool::Shutdown()
{
    if (mState >= TP_STOP) {
        return;
    }

    mState = TP_STOP;
    WakeupAllThread();
    WaitExit();
    mState = TP_TERMINATED;
}

void ThreadPool::WakeupAllThread()
{
    mMutex.lock();
    mCond.notifyAll();
    mMutex.unlock();
}

void ThreadPool::WaitExit()
{
    std::list<Thread*>::iterator it = mThreads.begin();
    for (; it != mThreads.end(); ++it) {
        (*it)->Join();
        delete *it;
    }    
}

Runnable *ThreadPool::PopTask()
{
    if (!mTaskQueue.empty()) {
        Runnable *runnable = mTaskQueue.front();
        mTaskQueue.pop_front();
        --mTaskCount;
        return runnable;
    }
    return NULL;
}

bool ThreadPool::Execute(Runnable *runnable)
{
    ScopedLock<MutexLock> lock(mMutex);
    if (mState >= TP_STOP || runnable == NULL) {
        return false;
    }
    mTaskQueue.push_back(runnable);
    ++mTaskCount;
    mCond.notify();
    return true;
}

void ThreadPool::ThreadProc()
{
    mMutex.lock();
    Runnable *runnable = NULL;
    while (mState <= TP_STOP) {
        while (mState <= TP_STOP && (runnable = PopTask()) != NULL) {
            mMutex.unlock();
            runnable->Run();
            runnable->Free();
            mMutex.lock();
            mFinishCount++;
        }
        if (mState < TP_STOP && runnable == NULL) {
            mCond.wait();
        } else {
            break;
        }
    }
    mMutex.unlock();
}

}
