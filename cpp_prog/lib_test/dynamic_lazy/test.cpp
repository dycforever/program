
#include <iostream>

void PrintGlobal();
extern "C"
{

void func(bool flag)
{
    if (flag) {
        std::cout << "in func" << std::endl;
    } else {
        PrintGlobal();
    }
}

}
