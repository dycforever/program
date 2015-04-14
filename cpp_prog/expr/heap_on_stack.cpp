
#include <stdio.h>

class A {
public:
    A() {printf("construct A\n");}
    A(const A&) {printf("copy construct A\n");}
    ~A() {printf("destroy A\n");}

    int i;
};

const A func() {
    int i = 0;
    printf("in func() i: %p\n", &i);
    A a;
    printf("in func() a: %p\n", &a);
    return a;
}

int main() {
    const A* a = new A(func());
    printf("main(): %p\n", a);
}

