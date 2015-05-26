#include <iostream>
#include <stdio.h>
#include <vector>

#ifdef HELLO2
extern void hello2();
#else
extern void hello();
#endif

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
#ifdef HELLO2
    hello2();
#else
    hello();
#endif
    printf("static obj in lib2: %p\n", &sTest2Obj);
    return true;
}
