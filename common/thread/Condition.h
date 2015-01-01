
#ifndef CONDITION_H
#define CONDITION_H

#include <sys/time.h>
#include <pthread.h>
#include <boost/noncopyable.hpp>

#include "thread/ThreadLock.h" 
#include "utils/TimeUtil.h" 

namespace dyc {

class Condition : boost::noncopyable {
 public:
  explicit Condition(MutexLock& mutex)
    : mMutex(mutex) {
    MCHECK(pthread_cond_init(&mCond, NULL));
  }

  ~Condition() {
    MCHECK(pthread_cond_destroy(&mCond));
  }

  void wait() {
    MutexLock::UnassignGuard ug(mMutex);
    MCHECK(pthread_cond_wait(&mCond, mMutex.getPthreadMutex()));
  }

  int wait(int64_t usec) {
      timespec ts = TimeUtil::GetTimeSpec(usec);
      return pthread_cond_timedwait(&mCond, &mMutex._mutex, &ts);
  }

  void notify() {
    MCHECK(pthread_cond_signal(&mCond));
  }

  void notifyAll() {
    MCHECK(pthread_cond_broadcast(&mCond));
  }

 private:
  MutexLock& mMutex;
  pthread_cond_t mCond;
};

}
#endif  // MUDUO_BASE_CONDITION_H
