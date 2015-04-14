
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

void func0() {
    struct timeval now;
    int i;
    for (i = 0; i < 100000000; ++i) {
        gettimeofday(&now, NULL);
    }
}

// ************************

pthread_spinlock_t spinlock1;
struct timeval gtime1;

void* update_time1(void* p) {
    while(1) {
        pthread_spin_lock(&spinlock1);
        gettimeofday(&gtime1, NULL);
        pthread_spin_unlock(&spinlock1);
    }
}

struct timeval gettime1() {
    struct timeval ret;
    pthread_spin_lock(&spinlock1);
    ret = gtime1;
    pthread_spin_unlock(&spinlock1);
    return ret;
}

void func1() {
    pthread_spin_init(&spinlock1, PTHREAD_PROCESS_PRIVATE);
    struct timeval now;
    int i;
    pthread_t tid;
    pthread_create(&tid, NULL, update_time1, NULL);

    for (i = 0; i < 10000000; ++i) {
        now = gettime1();
    }
    pthread_spin_destroy(&spinlock1);
}

// ************************

pthread_spinlock_t spinlock2;
struct timeval gtime2;

void* update_time2(void* p) {
    while(1) {
        usleep(1000);
        struct timeval tmp;
        gettimeofday(&tmp, NULL);
        pthread_spin_lock(&spinlock2);
        gtime2 = tmp;
        pthread_spin_unlock(&spinlock2);
    }
}

struct timeval gettime2() {
    struct timeval ret;
    pthread_spin_lock(&spinlock2);
    ret = gtime2;
    pthread_spin_unlock(&spinlock2);
    return ret;
}


void func2() {
    pthread_spin_init(&spinlock2, PTHREAD_PROCESS_PRIVATE);
    struct timeval now;
    int i;
    pthread_t tid;
    pthread_create(&tid, NULL, update_time2, NULL);

    for (i = 0; i < 100000000; ++i) {
        now = gettime2();
    }
    pthread_spin_destroy(&spinlock2);
}

int main() {
    func0();
    func1();
    func2();
}

