#include "thread/LoopThread.h"
#include "utils/TimeUtil.h"

namespace dyc {

LoopThread::LoopThread()
    : mRunning(false),
      mInterval(-1),
      mThread(NULL),
      mCond(mMutex)
{
}

LoopThread::~LoopThread() 
{ 
    Stop();
}

bool LoopThread::Start(const ThreadFunc& loopFunc, uint32_t interval)
{
    mLoopFunc = loopFunc;
    mInterval = interval * 1000;
    mThread = new Thread(std::tr1::bind(&LoopThread::Loop, this));
    mRunning = true;
    mThread->Start();
    return true;
}

void LoopThread::Stop()
{
    {
        ScopedLock<MutexLock> scopedlock(mMutex);
        if (mThread == NULL) {
            return;
        }
        mRunning = false;
        mCond.notify();
    }
    mThread->Join();
    DELETE(mThread);
}

void LoopThread::Loop()
{
    int64_t nextTime = 0;
    while (true) {
        {
            ScopedLock<MutexLock> lock(mMutex);
            if (!mRunning) {
                return;
            }
            int64_t nowTime = TimeUtil::GetTimeInUs();
            if (nowTime < nextTime) {
                mCond.wait(nextTime - nowTime);
                if (!mRunning) {
                    return;
                }
            }
            nowTime = TimeUtil::GetTimeInUs();
            if (nowTime < nextTime) {
                continue;
            }
        }
        mLoopFunc();
        nextTime = TimeUtil::GetTimeInUs() + mInterval;
    }
}

}

