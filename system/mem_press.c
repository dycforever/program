#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    const size_t MB = 1024 * 1024;
    const size_t GB = MB * 1024;
    char* datas[100];
    char* data = (char*)malloc(35 * GB);
    printf("malloced 3G    press key"); fflush(stdout); getchar();
    size_t i, j;
    for (j = 0; j < 30 * GB; j++) {
        data[j] = j;
    }
    printf("accessed 3G    press key"); fflush(stdout); getchar();
    for (i = 0; i < 80; i++) {
        size_t memSize = 100 * MB;
        datas[i] = (char*)malloc(memSize);
        printf("malloced 3G + %lu00 Mb", i); fflush(stdout); getchar();
        for (j = 0; j < 100 * MB; j++) {
            datas[i][j] = j;
        }
        printf("accessed 3G + %lu00 Mb", i); fflush(stdout); getchar();
    }
}