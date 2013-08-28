#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

#include <semaphore.h>

sem_t beginSema1;
sem_t beginSema2;
sem_t endSema;

int X, Y;
int r1, r2;

void *thread_func1(void *param)
{
    for (;;)                                  
    {
        sem_wait(&beginSema1);                // Wait for signal from main thread
        while (rand() % 8 != 0) {}  // Add a short, random delay

        X = 1;
//        asm volatile("mfence" ::: "memory");        // Prevent CPU reordering
        asm volatile("" ::: "memory");        // Prevent compiler reordering
        r1 = Y;

        sem_post(&endSema);                   // Notify transaction complete
    }
    return NULL;  // Never returns
};

void *thread_func2(void *param)
{
    for (;;)                                  
    {
        sem_wait(&beginSema2);                // Wait for signal from main thread
        while (rand() % 8 != 0) {}  // Add a short, random delay

        Y = 1;
//        asm volatile("mfence" ::: "memory");        // Prevent CPU reordering
        asm volatile("" ::: "memory");        // Prevent compiler reordering
        r2 = X;

        sem_post(&endSema);                   // Notify transaction complete
    }
    return NULL;  // Never returns
};

int main()
{
//    Initialize the semaphores
    sem_init(&beginSema1, 0, 0);
    sem_init(&beginSema2, 0, 0);
    sem_init(&endSema, 0, 0);

    // Spawn the threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, thread_func1, NULL);
    pthread_create(&thread2, NULL, thread_func2, NULL);

    //设置CPU亲和性，或者设置CPU barrier才能消除内存操作的reorder
    cpu_set_t cpus;
    CPU_ZERO(&cpus);
    CPU_SET(0, &cpus);
    pthread_setaffinity_np(thread1, sizeof(cpu_set_t), &cpus);
    pthread_setaffinity_np(thread2, sizeof(cpu_set_t), &cpus);

    // Repeat the experiment ad infinitum
    int detected = 0;
    for (int iterations = 1; ; iterations++)
    {
        // Reset X and Y
        X = 0;
        Y = 0;
        // Signal both threads
        sem_post(&beginSema1);
        sem_post(&beginSema2);
        // Wait for both threads
        sem_wait(&endSema);
        sem_wait(&endSema);
        // Check if there was a simultaneous reorder
        if (r1 == 0 && r2 == 0)
        {
            detected++;
            printf("%d reorders detected after %d iterations\n", detected, iterations);
        }
    }
    return 0;  // Never returns
}
