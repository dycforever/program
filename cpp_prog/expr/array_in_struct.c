
#include <stdio.h>

struct str {
    char* datap;
    char data[1];
};

int main() {
    struct str s;
    printf("%p\n", s.data);
    printf("%p\n", s.datap);

    struct str* sp = NULL;
    printf("%p\n", sp->data);
    printf("%p\n", sp->datap);
}
