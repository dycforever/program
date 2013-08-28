#include <stdio.h>

int b;
int c;

int main()
{
    if (0 == fork()) {
        sleep(1);
        b = 1;
        printf("child:\tsleep(1)\n\t(&b):0x%08x\n \
                \t(&c)=0x%08x\n\tsizeof(b)=%d\n\tset b=%d\n\tc=%d\n",
                &b, &c, sizeof b, b, c);
        foo();
    } else {
        foo();
        printf("parent:\t(&b)=0x%08x\n\t(&c)=0x%08x\n \
                \tsizeof(b)=%d\n\tb=%d\n\tc=%d\n\twait child...\n",
                &b, &c, sizeof b, b, c);
        wait(-1);
        printf("parent:\tchild over\n\t(&b)=0x%08x\n \
                \t(&c)=0x%08x\n\tsizeof(b)=%d\n\tb=%d\n\tc=%d\n",
                &b, &c, sizeof b, b, c);
    }
    return 0;
}
