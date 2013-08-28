#include <iostream>
#include <stdio.h>

long long sum;

class Peterson {
private:
    bool flags[2];
    int victim;
    pthread_spinlock_t splock;

public:
    Peterson() {
        pthread_spin_init(&splock, PTHREAD_PROCESS_PRIVATE );
    }
    void lock(long i) {
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        int j = 1 - i;
//        bool other = flags[j];
//        pthread_spin_lock(&splock);
//        pthread_spin_unlock(&splock);
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        victim = i;
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        flags[i] = true;
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
//        pthread_spin_lock(&splock);
//        pthread_spin_unlock(&splock);
//        while (other && victim == i){}
//        while (flags[j] && victim == i){}
        while (victim == i && flags[j]){}
    }

    void unlock (int i) {
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        flags[i] = false;
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
    }

};

Peterson plock;

void* add (void* p) {
    for (int i=0; i<10000000; ++i) {
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        plock.lock((long)p);
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        ++sum;
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
        plock.unlock((long)p);
        asm volatile ("lock; addl $0,0(%%esp)" ::: "cc", "memory");
    }
    return NULL;
}

int main () {
    pthread_t tids[2];
    pthread_create(tids, NULL, add, (void*)0);
    pthread_create(tids+1, NULL, add, (void*)1);
    printf("join 0\n");
    pthread_join(tids[0], NULL);
    printf("join 1\n");
    pthread_join(tids[1], NULL);
    printf("sum=%lld \n", sum);
}
