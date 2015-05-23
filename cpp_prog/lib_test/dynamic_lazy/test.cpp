
#include <iostream>

extern int undefinedInt;
void PrintGlobal();
extern "C"
{

void func(bool flag)
{
    if (flag) {
        std::cout << "in func" << std::endl;
    } else {
        PrintGlobal();
//        std::cout << "addr: " << &undefinedInt << std::endl;
    }
}

}
