#ifndef __NTL_INCLUDE_THREAD_POOL_H__
#define __NTL_INCLUDE_THREAD_POOL_H__

#include <map>
#include <list>
#include <iostream>
#include <semaphore.h>

#include "common.h"
#include "Task.h"

namespace dyc {

class ThreadPool;
// struct for pthread function parameter 
class ThreadParam {
public:
    ThreadParam(int id, ThreadPool* p) 
    {
        _thread_id = id;
        _pool = p;
    }
    int _thread_id;
    ThreadPool* _pool;
};

struct Thread {
    pthread_t _pthread_id;
    ThreadParam* _thread_param;
};

class ThreadPool {
protected:
    //  protect task list and busy count
    pthread_mutex_t _mutex;
    pthread_spinlock_t _busy_count_lock;

    // wait for new task 
    sem_t _has_task;

    // all threads 
    Thread* _threads;
    // task list
    std::list<Task*> _waiting_tasks;

    // pthread_t to id mapping
    std::map<pthread_t, int> _thread_to_id;
    // if all threads will exit
    volatile bool _stop;

    // threads number 
    volatile int _size;
    // number of working threads 
    volatile int _busy_count;

    // thread function 
    static void* thread_function(void* param);

public:
    // constructor 
    ThreadPool(int size);
    ~ThreadPool();

    // push task into thread pool 
    int push_task(Task* task);
    // init function 
    int init();

    // kill the task 
    int kill(Task*);
    // get the id of current thread
    int get_thread_id();
    // get the count of busy threads 
    int get_busy_thread_count();
    // destruct and release resource 
    int destroy();

    void dec_busy_count();
    void inc_busy_count();
    bool stop() { return _stop; }

    static Task* get_task(ThreadPool*);
    static void do_task(Task* task, int thread_id);

}; //class ThreadPool

}; // namespace ntl

#endif  //__NTL_INCLUDE_THREAD_POOL_H__
