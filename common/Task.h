#ifndef __NTL_INCLUDE_TASK_H__
#define __NTL_INCLUDE_TASK_H__
#include <stdio.h>
#include <errno.h>
#include <semaphore.h>

#include "common.h"

namespace dyc {

class Task {
public:
    // task stats: WAITING -> RUNNING -> FINISH
    enum TaskStat {
        WAITING, RUNNING, FINISH
    };
    
    Task() {
        _param = NULL;
        _auto_delete = false;
        int ret = sem_init(&_task_over, 0, 0);
        if (ret != 0) {
            FATAL("sem_init failed ret:%d errno:%d %s", ret, errno, strerror(errno));
        }
    }

    Task(void* param) {
        _param = param;
        _auto_delete = false;
        int ret = sem_init(&_task_over, 0, 0);
        if (ret != 0) {
            FATAL("sem_init failed ret:%d errno:%d %s", ret, errno, strerror(errno));
        }
    }

    virtual void* run(void*) = 0;

    TaskStat get_stat() {
        TaskStat ret = _stat;
        return ret;
    }

    void* get_param() {
        return _param;
    }

    void set_auto_delete() {
        _auto_delete = true;
    }

    void set_param(void* param) {
        _param = param;
    }

    void set_owner(int id) {
        _owner_id = id;
    }

    bool is_delete() {
        return _auto_delete;
    }

    virtual ~Task(){
        sem_destroy(&_task_over);
    };

    void wait() {
        sem_wait(&_task_over);
    }

    void post() {
        sem_post(&_task_over);
    }

    // return value of the task, set by thread pool
    void* _task_ret;

    friend class ThreadPool;
private:
    void set_stat(TaskStat stat) {
        _stat = stat;
    }

    // parameter of this task, set by user 
    void* _param;
    // current stat of the task, set by thread pool
    TaskStat _stat;
    // working thread id of task 
    int _owner_id;
    // if true, the task will be deleted when the task->run() over
    bool _auto_delete;

    // wait this task to finish
    sem_t _task_over;

}; //class Task

}; //namespace ntl

#endif  //__NTL_INCLUDE_TASK_H__
