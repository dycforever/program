#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

int main() {
    struct timeval tv;
    unsigned long start_time;
    char *dst, *src;

    dst = (char*)malloc(1024 * 1024);
    src = (char*)malloc(1024 * 512);
    memset(dst, 'a', 1024 * 512);
    memset(src, 'b', 1024 * 512);
    src[1024 * 512 - 1] = '\0';
    dst[1024 * 512] = '\0';

    gettimeofday(&tv, (struct timezone *)NULL); 
    start_time = (tv.tv_sec * 1000000) + tv.tv_usec;

    /* snprintf */
    snprintf(dst, 1024 * 1024, "%s%s", dst, src);

    gettimeofday(&tv, (struct timezone *)NULL); 
    printf("snprintf time: %ld\n", (tv.tv_sec * 1000000) + tv.tv_usec - start_time);

    dst[1024 * 512] = '\0';
    gettimeofday(&tv, (struct timezone *)NULL); 
    start_time = (tv.tv_sec * 1000000) + tv.tv_usec;

    /* strncat */
    strncat(dst, src, 1024 * 512);

    gettimeofday(&tv, (struct timezone *)NULL); 
    printf("strncat time: %ld\n", (tv.tv_sec * 1000000) + tv.tv_usec - start_time);



    return 0;
}

//output
////snprintf time: 220
////strncat time: 1347
