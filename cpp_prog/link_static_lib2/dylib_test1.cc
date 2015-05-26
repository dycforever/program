#include <iostream>
#include <vector>

extern void hello();

class Test2 {
public:
    Test2() {
        std::cout << "Test2:" << this << std::endl;
    }

    ~Test2() {
        std::cout << "~Test2:" << this << std::endl;
    }
};

Test2 gTest2Obj;

std::vector<int> gIntVec;
static std::vector<int> sIntVec;
static Test2 sTest2Obj;

extern "C"
bool saySth1() {
    hello();
    std::cout << "sTest2Obj:" << &sTest2Obj << std::endl;
    return true;
}
