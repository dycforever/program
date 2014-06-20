
#ifndef CONDITION_H
#define CONDITION_H

#include <boost/noncopyable.hpp>
#include <pthread.h>

#include "Mutex.h" 

namespace dyc {

class Condition : boost::noncopyable {
 public:
  explicit Condition(MutexLock& mutex)
    : mutex_(mutex) {
    MCHECK(pthread_cond_init(&pcond_, NULL));
  }

  ~Condition() {
    MCHECK(pthread_cond_destroy(&pcond_));
  }

  void wait() {
    MutexLock::UnassignGuard ug(mutex_);
    MCHECK(pthread_cond_wait(&pcond_, mutex_.getPthreadMutex()));
  }

  // returns true if time out, false otherwise.
  bool waitForSeconds(int seconds);

  void notify() {
    MCHECK(pthread_cond_signal(&pcond_));
  }

  void notifyAll() {
    MCHECK(pthread_cond_broadcast(&pcond_));
  }

 private:
  MutexLock& mutex_;
  pthread_cond_t pcond_;
};

}
#endif  // MUDUO_BASE_CONDITION_H
