#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

#include <assert.h>
#include <stdint.h>
#include <pthread.h>
#include <tr1/functional>

namespace dyc {

class Thread
{
public:
    typedef std::tr1::function<void()> ThreadFunc;

public:
    Thread(const ThreadFunc &threadFunc)
        : mTid(0),
          mThreadFunc(threadFunc),
          mStarted(false) {
    }

public:
    int Start() {
        assert(!mStarted);
        int ret =  pthread_create(&mTid, NULL, Thread::Hook, &mThreadFunc);
        mStarted = (ret == 0);
        return ret;
    }

    int Join() {
        assert(mStarted);
        return pthread_join(mTid, NULL);
    }

    int Detach() {
        assert(mStarted);
        return pthread_detach(mTid);
    }

    int SetPriority(int priority, int policy = SCHED_OTHER) {
        struct sched_param schedparam;
        schedparam.sched_priority = priority;
        return pthread_setschedparam(mTid, policy, &schedparam);
    }

    static void *Hook(void *arg) {
        ThreadFunc *threadFunc = (ThreadFunc*) arg;
        if (threadFunc) {
            (*threadFunc)();
        }
        return (void*) NULL;
    }

private:
    pthread_t mTid;
    ThreadFunc mThreadFunc;
    bool mStarted;
};

}
#endif //UTIL_THREAD_H
