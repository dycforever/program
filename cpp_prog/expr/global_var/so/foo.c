#include <stdio.h>

struct {
    int a;
    int b;
} b = { 3, 3 };

int main();

void foo()
{
    b.a = 4;
    b.b = 4;
    printf("foo:\t(&b)=0x%08x\n\tsizeof(b)=%d\n \
            \tb.a=%d\n\tb.b=%d\n\tmain:0x%08x\n",
            &b, sizeof b, b.a, b.b, main);
}
