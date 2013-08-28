    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdint.h>
    #include <pthread.h>
    
    pthread_cond_t g_cond;
    pthread_mutex_t g_mutex;
    
    void* thread_func(void*p) {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond, &g_mutex);
        pthread_mutex_unlock(&g_mutex);
    
        for (int i=0;i<200000;++i){
            int* p = new int[10*i];
            delete[] p;
        }
        return NULL;
    }
    
    #define THRD_NUM 4
    
    int main() {
        pthread_cond_init(&g_cond, NULL);
        pthread_mutex_init(&g_mutex, NULL);
        pthread_t pid[THRD_NUM];
    
        for (int i=0; i<THRD_NUM; i++) {
            pthread_create(&pid[i], NULL, thread_func, NULL);
        }
    
        sleep(1);
        for (int i=0; i<THRD_NUM; i++) {
            pthread_cond_broadcast(&g_cond);
        }
    
        for (int i=0; i<THRD_NUM; i++) {
            pthread_join(pid[i], NULL);
        }
    
        printf("finish \n");
    }
    
