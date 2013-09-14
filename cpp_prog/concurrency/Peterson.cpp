#include <iostream>
#include <stdio.h>

class Peterson {
    private:
        bool flags[2];
        long victim;

    public:
        Peterson() {
        }
        void lock(long i) {
            long j = 1 - i;
            flags[i] = true;
            asm volatile ("mfence" ::: "memory");
            victim = i;
            while (flags[j] && victim == i){}
            //while (victim == i && flags[j]){}
        }

        void unlock (long i) {
            flags[i] = false;
        }

};

long long sum;
Peterson plock;

void* add (void* p) {
    for (long i=0; i<1000000; ++i) {
        plock.lock((long)p);
        ++sum;
        plock.unlock((long)p);
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

