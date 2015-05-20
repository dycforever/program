
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void data_gen()
{
    const char* filename = "data";
    size_t i;
    FILE* fp = fopen(filename, "w");
    for (i = 0; i < 100 * 1024 * 1024; i++) {
        fwrite(&i, sizeof(i), 1, fp);
    }
    fclose(fp);
}

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    size_t *addr;
    int fd;
    struct stat sb;
    off_t offset, pa_offset;
    size_t length, i;

    data_gen();
    fd = open("data", O_RDONLY);
    if (fd == -1)
        handle_error("open");

    if (fstat(fd, &sb) == -1)           /* To obtain file size */
        handle_error("fstat");

    offset = 0;
    pa_offset = offset & ~(sysconf(_SC_PAGE_SIZE) - 1);
    /* offset for mmap() must be page aligned */

    if (offset >= sb.st_size) {
        fprintf(stderr, "offset is past end of file\n");
        exit(EXIT_FAILURE);
    }
   /* No length arg ==> display to end of file */
        length = sb.st_size - offset;
    printf("will mmap\n");getchar();
    addr = (size_t*)mmap(NULL, length + offset - pa_offset, PROT_READ,
            MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    while(1)
    for (i = 0; i < 100 * 1024 * 1024; i++) {
        if (addr[i] != i) {
            handle_error("read");
        }
    }
    printf("all over\n");
    exit(EXIT_SUCCESS);
}