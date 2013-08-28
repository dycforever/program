#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>
#include <atomic>

atomic_t g_acnt;

uint64_t g_lcnt;
pthread_spinlock_t glock;

pthread_cond_t g_cond;
pthread_mutex_t g_mutex;

void at_inc() {
    atomic_inc(&g_acnt);
}

void lock_inc() {
    pthread_spin_lock(&glock);
    ++g_lcnt;
    pthread_spin_unlock(&glock);
}

void* thread_func(void*p) {
    printf("in thread func %p\n", p);
    fflush(stdout);
    printf("thread %lu will wait\n", pthread_self());
    pthread_mutex_t* pp = (pthread_mutex_t*)p;
    pthread_mutex_lock(pp);
    pthread_cond_wait(&g_cond, pp);
    pthread_mutex_unlock(pp);

    printf("%lu wake \n", pthread_self());
    fflush(stdout);

    for (int i=0;i<1000000;++i){
        if (i %10000) {
            printf("progress %d\n", i);
        }
        at_inc();
        lock_inc();
    }
    return NULL;
}

int main() {
    atomic_set(&g_acnt, 0);
    g_lcnt = 0;
    pthread_cond_init(&g_cond, NULL);
    pthread_mutex_init(&g_mutex, NULL);
    pthread_spin_init(&glock, PTHREAD_PROCESS_PRIVATE);
    pthread_t pid[20];

    for (int i=0;i<20;i++) {
        pthread_create(&pid[i], NULL, thread_func, &g_mutex);
    }

    sleep(1);
    for (int i=0;i<20;i++) {
        pthread_cond_broadcast(&g_cond);
    }

    for (int i=0;i<10;i++) {
        pthread_join(pid[i], NULL);
    }

    long ans1 = atomic_read(&g_acnt);
    if (ans1 != g_lcnt) {
        printf("wrong! ans1:%ld g_lcnt:%ld \n", ans1, g_lcnt);
    }
    else 
        printf("right answer\n");
}

