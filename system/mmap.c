
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM 500 * 1024 * 1024

void data_gen()
{
    const char* filename = "data";
    size_t i;
    size_t* data = malloc(NUM * sizeof(i));
    FILE* fp = fopen(filename, "w");
    for (i = 0; i < NUM; i++) {
        data[i] = i;
    }
    fwrite(data, sizeof(i), NUM, fp);
    printf("write done\n");
    getchar();
    free(data);
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
<<<<<<< HEAD
=======
    printf("data_gen() done\n");

>>>>>>> 75d89d6130f69a9c11af78f033bb414d84d2bc4f
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
<<<<<<< HEAD
    printf("will mmap\n");getchar();
    addr = (size_t*)mmap(NULL, length + offset - pa_offset, PROT_READ,
=======

    addr = (size_t*)mmap(NULL, length + offset - pa_offset, PROT_READ|PROT_WRITE,
>>>>>>> 75d89d6130f69a9c11af78f033bb414d84d2bc4f
            MAP_PRIVATE, fd, pa_offset);
    if (addr == MAP_FAILED)
        handle_error("mmap");

    for (i = 0; i < NUM; i++) {
        if (addr[i] != i) {
            handle_error("read");
        }
    }
    printf("all over\n");
    getchar();
    exit(EXIT_SUCCESS);
}
