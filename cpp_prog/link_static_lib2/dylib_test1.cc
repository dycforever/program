#include <iostream>
#include <vector>
#include <stdio.h>

extern void hello();

class Test2 {
public:
    Test2() {
//        std::cout << "Test2:" << this << std::endl;
    }

    ~Test2() {
//        std::cout << "~Test2:" << this << std::endl;
    }
};

Test2 gTest2Obj;

std::vector<int> gIntVec;
static std::vector<int> sIntVec;
static Test2 sTest2Obj;

extern "C"
bool saySth1() {
    hello();
    printf("static obj in lib1: %p\n", &sTest2Obj);
    return true;
}
