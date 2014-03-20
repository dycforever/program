#include <stdio.h>

static inline int atomic_update(int delta, int num) {
    int tmp = delta;
    __asm__ __volatile__(
            "xadd %0,%1"
            : "+r" (tmp), "+m" (num)
            : : "memory");
    printf("delta: %d, num: %d\n", delta, num);
    return tmp + delta;
}

void down1() {
    printf("call down1\n");
}

void down2() {
    printf("call down2\n");
}

void down() {
    int i = 1;
    __asm__ __volatile__(
            "decl %0\n"
            "jns 1f\n"
            "call down2\n"
            "ret\n"
            "1:\n"
            "call down1\n"
            :"=m" (i)
            :
            :"memory"
            );
}

int main() {
    int a = 1;
    int b = 2;
    int res = -1;
    printf("a: %d, b: %d\n", a, b);
    res = atomic_update(a, b);
    printf("a: %d, b: %d, result: %d\n", a, b, res);

    down();
}