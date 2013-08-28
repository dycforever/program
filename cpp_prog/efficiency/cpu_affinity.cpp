#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

// 设置线程的CPU亲和性，使不同线程同时运行在不同的CPU上
static int set_thread_affinity(int cpu_id)
{
    cpu_set_t cpuset;
    int ret;

    CPU_ZERO(&cpuset);
    CPU_SET(cpu_id, &cpuset);

    ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset);
    if (ret != 0) {
        printf("set affinity error\n");
        return -1;
    }

    return 0;
}

//检查线程的CPU亲和性
static void check_cpu_affinity(void)
{
    cpu_set_t cpu_set;
    int ret;
    int i;

    ret = pthread_getaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpu_set);
    if (ret != 0) {
        printf("check err!\n");
        return;
    }

    for (i = 0; i < CPU_SETSIZE; ++i) {
        if (CPU_ISSET(i, &cpu_set)) {
            printf("cpu %d\n", i);
        }
    }

}


#define CPU_NR          2
#define CACHE_LINE_SIZE 64
#define VAR_NR ((CACHE_LINE_SIZE/sizeof(int))-1)
//这个结构为多核编程中最频繁使用的结构
//其size大小为本文重点
struct key {
    int a[VAR_NR];
//    int pad;
} __attribute__((packed));
//使用空间换时间，每个CPU拥有不同的数据
static struct key* g_key;

//丑陋的硬编码——这里仅仅为了说明问题，我就不改了。
static void real_job(int index)
{
#define LOOP_NR 100000000
    struct key *k = g_key+index;

    int i;
    for (i = 0; i < VAR_NR; ++i) {
        k->a[i] = i;
    }

    for (i = 0; i < LOOP_NR; ++i) {
        k->a[14] = k->a[14]+k->a[3];
        k->a[3] = k->a[14]+k->a[5];
        k->a[0] = k->a[1]+k->a[7];
        k->a[7] = k->a[1]+k->a[9];
    }
}

static volatile int thread_ready = 0;

//这里使用丑陋的硬编码。最好是通过参数来设置亲和的CPU
//这个线程运行在CPU 1上
static void *thread_task(void *data)
{
    set_thread_affinity(1);
    check_cpu_affinity();

    thread_ready = 1;

    real_job(1);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t tid;
    int ret;

    g_key = (struct key*) malloc(2*sizeof(struct key) + CACHE_LINE_SIZE);
    printf("raw key:%p\n", g_key);

    g_key = (struct key*)( ((unsigned long)g_key + CACHE_LINE_SIZE-1 ) & 0xffffffc0 ) ;
    printf("start! sizeof(key):%d from:%p\n", sizeof(struct key), g_key);

    //设置主线程运行在CPU 0上
    ret = set_thread_affinity(0);
    if (ret != 0) {
        printf("err1\n");
        return -1;
    }
    check_cpu_affinity();

    //提高优先级，避免进程被换出。因为换出后，cache会失效，会影响测试效果
    ret = nice(-20);
    if (-1 == ret) {
        printf("err2\n");
        perror("nice failed:");
        return -1;
    }

    ret = pthread_create(&tid, NULL, thread_task, NULL);
    if (ret != 0) {
        printf("err3\n");
        return -1;
    }

    //忙等待，使两个real_job同时进行
    while (!thread_ready)
        ;

    real_job(0);

    pthread_join(tid, NULL);

    printf("Completed!\n");

    return 0;
}
