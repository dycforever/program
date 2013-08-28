#include <stdio.h>;

struct {
    int a;
    int b;
} b = { 2, 4 };

int main();

void foo()
{
    printf("foo:\t(&b)=0x%08x\n\tsizeof(b)=%d\n  \
            \tb.a=%d\n\tb.b=%d\n\tmain:0x%08x\n",
            &b, sizeof b, b.a, b.b, main);
}
