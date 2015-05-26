#include <iostream>
#include <stdio.h>
#include <vector>

extern void hello2();

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
bool saySth2() {
    hello2();
    printf("static obj in lib2: %p\n", &sTest2Obj);
    return true;
}
