#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct slist {
    struct slist *next;
    char         data[4096];
} slist;

slist input_list = {NULL, {"\'\0\'"}};
int count = 0;

static void stdin_read (int fd)
{
    char buf[4096];
    int ret;

    memset(buf, 0, 4096);

    fprintf(stderr, "please input string:");

    while (ret = read(fd, buf, 4096)) {

        slist *node = calloc(1, sizeof(slist));
        memcpy(node->data, buf, ret);
        node->next = input_list.next;
        input_list.next = node;
        count ++;

        if (memcmp(buf, "quit", 4) == 0) {
            fprintf(stdout, "input quit:\\n");
            return;
        }
        fprintf(stderr, "ret: %d, there is %d strings, current is %s\\nplease input string:", ret, count, buf);
    }
}

int main()
{
    fprintf(stderr, "main run!\n");

    stdin_read(STDIN_FILENO);

    slist *nlist;
    slist *list = input_list.next;
    while (list) {
        fprintf(stderr, "%s\\n", list->data);
        nlist = list->next;
        free(list);
        list = nlist;
    }

    return 0;
}
