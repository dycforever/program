#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    const size_t MB = 1024 * 1024;
    const size_t GB = MB * 1024;
    char* datas[100];
    char* data = (char*)malloc(3 * GB);
    size_t i, j;
    for (j = 0; j < 3 * GB; j++) {
        data[j] = j;
    }
    for (i = 0; i < 80; i++) {
        size_t memSize = 100 * MB;
        printf("add %lu00 Mb\n", i);
        fflush(stdout);
        datas[i] = (char*)malloc(memSize);
        for (j = 0; j < 100 * MB; j++) {
            datas[i][j] = j;
        }
        sleep(2);
    }

    sleep(10);
}