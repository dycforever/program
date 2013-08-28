#include <stdio.h>

int b;
int c;

int t2()
{
    printf("t2:\t(&b)=0x%08x\n\t(&c)=0x%08x\n \
            \tsizeof(b)=%d\n\tb=%d\n\tc=%d\n",
            &b, &c, sizeof b, b, c);
    return 0;
}
