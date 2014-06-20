#include "ThreadPool.h"
namespace dyc {

Task* ThreadPool::get_task(ThreadPool* pool) {
    if (pool == NULL) {
        FATAL("pool == NULL");
        return NULL;
    }
    Task* task = NULL;
    pthread_mutex_lock(&pool->_mutex);
    if (!pool->_waiting_tasks.empty()) {
        task = pool->_waiting_tasks.front();
        assert(task != NULL);
        pool->_waiting_tasks.pop_front();
    }
    pthread_mutex_unlock(&pool->_mutex);
    return task;
}

// call task->run() and set return value 
void ThreadPool::do_task(Task* task, int thread_id) {
    task->set_owner(thread_id);
    task->set_stat(Task::RUNNING);
    task->_task_ret = task->run(task->get_param());
    task->set_stat(Task::FINISH);
    task->post();
    if (task->is_delete()) {
        DELETE(task);
    }
}

void ThreadPool::inc_busy_count() {
    pthread_spin_lock(&_busy_count_lock);
    _busy_count += 1;
    pthread_spin_unlock(&_busy_count_lock);
}

void ThreadPool::dec_busy_count() {
    pthread_spin_lock(&_busy_count_lock);
    _busy_count -= 1;
    pthread_spin_unlock(&_busy_count_lock);
}

// thread function, 
// run until all tasks finished and stop() return true;
void* ThreadPool::thread_function(void* general_param)
{
    ThreadParam* thread_param = (ThreadParam*)general_param;
    ThreadPool* pool = thread_param->_pool;

    while (!pool->stop()) {
        // get task from waiting list 
        Task* task = get_task(pool);
        // wait until there are tasks in waiting list 
        while (!pool->stop() && task == NULL) {
            sem_wait(&pool->_has_task);
            task = get_task(thread_param->_pool);
        }
        // consistency check
        if (task == NULL && pool->stop()) {
            break;
        } else if(task == NULL){
            FATAL("something is wrong:task[%p] stop[%d}", task, pool->stop());
            return (void*)-1;
        }

        NOTICE("thread[%d] find a task in waiting list ", thread_param->_thread_id);
        pool->inc_busy_count();
        do_task(task, thread_param->_thread_id);
        pool->dec_busy_count();
    }
    return NULL;
}


ThreadPool::ThreadPool(int size)
{
    _size = size;
    _busy_count = 0;
}

int ThreadPool::get_busy_thread_count()
{
    return _busy_count;
}

ThreadPool::~ThreadPool()
{
    ;
}

// release all resource 
int ThreadPool::destroy()
{
    NOTICE("will destroy thread pool: %lu, busy count:%d", _waiting_tasks.size(), _busy_count);
    int error = 0;
    void* thread_ret = NULL;
    _stop = true;

    for (int i = 0; i < _size; ++i) {
        sem_post(&_has_task);
    }

    for (int i = 0; i < _size; ++i) {
        int ret = pthread_join(_threads[i]._pthread_id, (void**)&thread_ret);
        if (ret != 0 || thread_ret != NULL) {
            FATAL("thread exit with error ret[%d] thread_ret[%p]", ret, thread_ret);
            ++error;
        }
        DELETE(_threads[i]._thread_param);
    }

    sem_destroy(&_has_task);
    pthread_mutex_destroy(&_mutex);
    pthread_spin_destroy(&_busy_count_lock);
    DELETES(_threads);
    return -error;
}

// get id of current thread
// return 0 if success, -1 for error
int ThreadPool::get_thread_id()
{
    std::map<pthread_t, int>::iterator iter;
    iter = _thread_to_id.find(pthread_self());
    if (iter == _thread_to_id.end()) {
        WARN("can not find this thread in map");
        return -1;
    }
    return iter->second;
}

// thread pool initialize 
// return 0 if success, -1 for error
int ThreadPool::init()
{
    if (_size <= 0) {
        FATAL("invalid size: %d", _size);
        return -1;
    }
    _threads = NEW Thread[_size];
    if (NULL == _threads) {
        FATAL("new threads failed");
        return -1;
    }
    memset(_threads, 0, sizeof(Thread)*_size);
    _stop = false;

    pthread_mutex_init(&_mutex, NULL);
    pthread_spin_init(&_busy_count_lock, PTHREAD_PROCESS_PRIVATE);
    sem_init(&_has_task, 0, 0);

    for (int i = 0; i < _size; ++i) {
        ThreadParam* param = NEW ThreadParam(i, this);
        if (NULL == param) {
            FATAL("new param failed");
            return -1;
        }
        int ret = pthread_create(&_threads[i]._pthread_id, NULL, thread_function, (void*)param);
        _threads[i]._thread_param = param;

        if (ret != 0) {
            FATAL("create thread failed");
            return -1;
        } else {
            NOTICE("create thread success");
        }

        try {
            _thread_to_id[_threads[i]._pthread_id] = i;
        } catch (std::bad_alloc exception) {
            FATAL("insert thread into id map failed %s", exception.what());
            return -1;
        }

    }
    NOTICE("wait all thread over");
    return 0;
}

// deprecated
int ThreadPool::kill(Task* task)
{
    return 0;
}

// push task into the waiting list
// return 0 if success, -1 for error
int ThreadPool::push_task(Task* task)
{
    NOTICE("push task %p", task);
    if (task == NULL) {
        FATAL("task is NULL");
        return -1;
    }
    pthread_mutex_lock(&_mutex);
    try {
        _waiting_tasks.push_back(task);
    } catch (std::bad_alloc exception) {
        pthread_mutex_unlock(&_mutex);
        FATAL("alloc failed %s", exception.what());
        return -1;
    }
    pthread_mutex_unlock(&_mutex);
    sem_post(&_has_task);
    return 0;
}

};
