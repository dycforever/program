#include <stdint.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

pthread_spinlock_t spinlock;
pthread_mutex_t mutexlock;
int gCount;
bool stop;

#define THREADNUM 10
#define GETWAITTIME 0
#define UPDATEWAITTIME 100
#define UPDATELOOP 100

class TimeUtil
{
public:
    static int64_t GetTimeInSec() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return tval.tv_sec;
    }

    static int64_t GetTimeInMs() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return (tval.tv_sec * 1000LL + tval.tv_usec / 1000);
    }
    
    static int64_t GetTimeInUs() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return (tval.tv_sec * 1000000LL + tval.tv_usec);
    }

    static timespec GetTimeSpec(int64_t usecOffset) {
        timespec tspec;
        int64_t uTime = GetTimeInUs() + usecOffset;
        tspec.tv_sec = uTime / 1000000;
        tspec.tv_nsec = (uTime % 1000000) * 1000;
        return tspec;
    }

    static std::string GetFormatTime(const std::string& format)
    {
        char outStr[256];
        time_t t = time(NULL);
        struct tm *tmp = localtime(&t);
        strftime(outStr, sizeof(outStr), format.c_str(), tmp);
        return std::string(outStr);
    }

}; // class TimeUtil


namespace spin_test {

void* SpinUpdateCount(void* p) 
{
    pthread_spin_lock(&spinlock);
    gCount++;
    pthread_spin_unlock(&spinlock);
}

void* SpinGetCount(void* p) 
{
    int tmp;
    uint64_t count = 0;
    int64_t start = TimeUtil::GetTimeInUs();
    while(!stop) {
        ++count;
        pthread_spin_lock(&spinlock);
        tmp += gCount;
        pthread_spin_unlock(&spinlock);
        if (GETWAITTIME)
            usleep(GETWAITTIME);
    }
    int64_t now = TimeUtil::GetTimeInUs();
    double* ret = new double;
    *ret = (now - start)*1.0/count;
    return ret;
}

void TestSpin() 
{
    stop = false;
    pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);
    int i;
    pthread_t tid[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, SpinGetCount, NULL);
    }
    int64_t start = TimeUtil::GetTimeInUs();

    for (i = 0; i < UPDATELOOP; ++i) {
        if (UPDATEWAITTIME)
            usleep(UPDATEWAITTIME);
        SpinUpdateCount(NULL);
    }

    int64_t now = TimeUtil::GetTimeInUs();
    stop = true;
    double avg = 0;
    for (int i = 0; i < THREADNUM; i++) {
        double* ret;
        pthread_join(tid[i], (void**)&ret);
	avg += *ret;
        std::cout << *ret << " " ;
    }
    pthread_spin_destroy(&spinlock);
    std::cout << "spinlock takes \t" << (now - start) << " us " << std::endl;
    std::cout << "read takes \t" << avg/10 << " us \n" << std::endl;
}

}  // namespace spin_test

namespace mutex_test {

void* MutexUpdateCount(void* p) 
{
    pthread_mutex_lock(&mutexlock);
    gCount++;
    pthread_mutex_unlock(&mutexlock);
}

void*  MutexGetCount(void* p) 
{
    int tmp;
    uint64_t count = 0;
    int64_t start = TimeUtil::GetTimeInUs();
    while(!stop) {
        count++;
        pthread_mutex_lock(&mutexlock);
        tmp += gCount;
        pthread_mutex_unlock(&mutexlock);
        if (GETWAITTIME)
            usleep(GETWAITTIME);
    }
    int64_t now = TimeUtil::GetTimeInUs();
    double* ret = new double;
    *ret = (now - start)*1.0/count;
    return (void*)ret;
}

void TestMutex() 
{
    stop = false;
    pthread_mutex_init(&mutexlock, NULL);
    int i;
    pthread_t tid[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, MutexGetCount, NULL);
    }
    int64_t start = TimeUtil::GetTimeInUs();

    for (i = 0; i < UPDATELOOP; ++i) {
        if (UPDATEWAITTIME)
            usleep(UPDATEWAITTIME);
        MutexUpdateCount(NULL);
    }

    int64_t now = TimeUtil::GetTimeInUs();
    stop = true;
    double avg = 0;
    for (int i = 0; i < THREADNUM; i++) {
        double* ret;
        pthread_join(tid[i], (void**)&ret);
	avg += *ret;
        std::cout << *ret << " " ;
    }
    pthread_mutex_destroy(&mutexlock);
    std::cout << "mutex takes \t" << (now - start) << " us " << std::endl;
    std::cout << "read takes \t" << avg/10 << " us \n" << std::endl;
}

} // namespace mutex_test

namespace rwlock_test {

pthread_rwlock_t rwlock;

void* RwUpdateCount(void* p) 
{
    pthread_rwlock_wrlock(&rwlock);
    gCount++;
    pthread_rwlock_unlock(&rwlock);
}

void* RwGetCount(void* p) 
{
    int tmp;
    uint64_t count = 0;
    int64_t start = TimeUtil::GetTimeInUs();
    while(!stop) {
        count++;
        pthread_rwlock_rdlock(&rwlock);
        tmp += gCount;
        pthread_rwlock_unlock(&rwlock);
        if (GETWAITTIME)
            usleep(GETWAITTIME);
    }
    int64_t now = TimeUtil::GetTimeInUs();
    double* ret = new double;
    *ret = (now - start)*1.0/count;
    return (void*)ret;
}


void TestRw() 
{
    stop = false;
    pthread_rwlock_init(&rwlock, NULL);
    int i;
    pthread_t tid[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, RwGetCount, NULL);
    }
    int64_t start = TimeUtil::GetTimeInUs();

    int loopCount = UPDATELOOP;
    for (i = 0; i < 10; ++i) {
        if (UPDATEWAITTIME)
            usleep(UPDATEWAITTIME);
        RwUpdateCount(NULL);
    }

    int64_t now = TimeUtil::GetTimeInUs();
    stop = true;
    double avg = 0;
    for (int i = 0; i < THREADNUM; i++) {
        double* ret;
        pthread_join(tid[i], (void**)&ret);
	avg += *ret;
        std::cout << *ret << " " ;
    }
    pthread_rwlock_destroy(&rwlock);
    std::cout << "rwlock takes \t" << (now - start) << " us " << std::endl;
    std::cout << "read takes \t" << avg/10 << " us \n" << std::endl;
}

} // namespace rwlock_test

namespace raw_test {

void* RawUpdateCount(void* p) 
{
    gCount++;
}

void* RawGetCount(void* p) 
{
    int tmp;
    uint64_t count = 0;
    int64_t start = TimeUtil::GetTimeInUs();
    while(!stop) {
        count++;
        tmp += gCount;
    }
    int64_t now = TimeUtil::GetTimeInUs();
    double* ret = new double;
    *ret = (now - start)*1.0/count;
    return (void*)ret;
}


void TestRaw() 
{
    stop = false;
    int i;
    pthread_t tid[THREADNUM];
    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, RawGetCount, NULL);
    }

    int64_t start = TimeUtil::GetTimeInUs();
    for (i = 0; i < UPDATELOOP; ++i) {
        usleep(UPDATEWAITTIME);
        RawUpdateCount(NULL);
    }

    int64_t now = TimeUtil::GetTimeInUs();
    stop = true;

    double avg = 0;
    for (int i = 0; i < THREADNUM; i++) {
        double* ret;
        pthread_join(tid[i], (void**)&ret);
	avg += *ret;
    }
    std::cout << "no lock takes \t" << (now - start) << " us " << std::endl;
    std::cout << "read takes \t" << avg/10 << " us \n" << std::endl;
}

} // namespace raw_test

int main() {
//    raw_test::TestRaw();
    spin_test::TestSpin();
    mutex_test::TestMutex();
    rwlock_test::TestRw();
}

