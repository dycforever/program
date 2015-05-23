
#include <iostream>
#include <dlfcn.h>

extern "C" void func();

int main() 
{
    std::cout << "main_link start" << std::endl;
    func();
    std::cout << "main end" << std::endl;
}

