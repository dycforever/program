
#include <pthread.h>
#include <signal.h>
#include <stdio.h>

pthread_cond_t cond;
pthread_mutex_t mutex;
int main_exit;
int t_exit;

void* hook(void* args)
{
    for (;!t_exit;) {
        usleep(1000);
        pthread_cond_signal(&cond);
    }
}

void sig_handler(int no)
{
    if (no == SIGINT) {
        main_exit = 1;
    }
}

void func1()
{
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&mutex, NULL);
    signal(SIGINT, sig_handler);

    pthread_t tid;
    int ret = pthread_create(&tid, NULL, hook, NULL);
    if (ret != 0) {
        return;
    }
    for (;!main_exit;) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    t_exit = 1;
    pthread_join(tid, NULL);

    printf("exiting\n");
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}

void func2()
{
    for(;;) {
    }
}

int main(int argc, char** argv)
{
    if (argc < 2) {
        return -1;
    }
    int no = atoi(argv[1]);
    if (no == 1) {
        func1();
    } else if (no == 2) {
        func2();
    } else {
    }
}

