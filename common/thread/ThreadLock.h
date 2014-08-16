
#ifndef THREADLOCK_H
#define THREADLOCK_H

#include <boost/noncopyable.hpp>
#include <assert.h>
#include <pthread.h>


__BEGIN_DECLS
extern void __assert_perror_fail (int errnum,
                                  const char *file,
                                  unsigned int line,
                                  const char *function)
    __THROW __attribute__ ((__noreturn__));
__END_DECLS

#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})

namespace dyc {

class MutexLock : boost::noncopyable
{
 public:
  MutexLock()
    : _holder(0)
  {
    MCHECK(pthread_mutex_init(&_mutex, NULL));
  }

  ~MutexLock()
  {
    assert(_holder == 0);
    MCHECK(pthread_mutex_destroy(&_mutex));
  }

  // must be called when locked, i.e. for assertion
  bool isLockedByThisThread() const
  {
    return _holder == pthread_self();
  }

  void assertLocked() const
  {
    assert(isLockedByThisThread());
  }

  // internal usage

  void lock()
  {
    MCHECK(pthread_mutex_lock(&_mutex));
    _holder = pthread_self();
  }

  void unlock()
  {
    _holder = 0;
    MCHECK(pthread_mutex_unlock(&_mutex));
  }

  pthread_mutex_t* getPthreadMutex() /* non-const */
  {
    return &_mutex;
  }

 private:
  friend class Condition;

  pthread_mutex_t _mutex;
  pthread_t _holder;

  class UnassignGuard : boost::noncopyable
  {
   public:
    UnassignGuard(MutexLock& owner)
      : _owner(owner)
    {
      _owner._holder = 0;
    }

    ~UnassignGuard()
    {
      _owner._holder = pthread_self();
    }

   private:
    MutexLock& _owner;
  };

};  // MutexLock


class SpinLock : boost::noncopyable {
 public:
  SpinLock()
    : _holder(0) {
    MCHECK(pthread_spin_init(&mSpinLock, PTHREAD_PROCESS_PRIVATE));
  }

  ~SpinLock() {
    assert(_holder == 0);
    MCHECK(pthread_spin_destroy(&mSpinLock));
  }

  // must be called when locked, i.e. for assertion
  bool isLockedByThisThread() const {
    return _holder == pthread_self();
  }

  void assertLocked() const {
    assert(isLockedByThisThread());
  }

  // internal usage

  void lock() {
    MCHECK(pthread_spin_lock(&mSpinLock));
    _holder = pthread_self();
  }

  void unlock() {
    _holder = 0;
    MCHECK(pthread_spin_unlock(&mSpinLock));
  }

  pthread_spinlock_t* getPthreadMutex() 
  {
    return &mSpinLock;
  }

 private:
  pthread_spinlock_t mSpinLock;
  pthread_t _holder;

  class UnassignGuard : boost::noncopyable {
   public:
    UnassignGuard(SpinLock& owner)
      : _owner(owner)
    {
      _owner._holder = 0;
    }

    ~UnassignGuard()
    {
      _owner._holder = pthread_self();
    }

   private:
    SpinLock& _owner;
  }; // UnassignGuard

}; // SpinLock

template<typename LOCK>
class LockGuard : boost::noncopyable
{
 public:
  explicit LockGuard(LOCK& lock)
    : _lock(lock)
  {
    _lock.lock();
  }

  ~LockGuard()
  {
    _lock.unlock();
  }

 private:

  LOCK& _lock;
};


template<typename LOCK>
class ScopedLock : boost::noncopyable
{
 public:
  explicit ScopedLock(LOCK& lock)
    : _lock(lock)
  {
    _lock.lock();
  }

  ~ScopedLock()
  {
    _lock.unlock();
  }

 private:

  LOCK& _lock;
};



}

// Prevent misuse like:
// LockGuard(_mutex);
// A tempory object doesn't hold the lock for long!
#define LockGuard(x) error "Missing guard object name"

#endif  // THREADLOCK_H
