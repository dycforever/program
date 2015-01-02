
#include "global.h"
#include <iostream>
#include <dlfcn.h>

#ifdef DLOPEN

int main() 
{
    std::cout << "main_dlopen start" << std::endl;
    typedef void (*Func)();

    void* dlHandle1 = dlopen("./liblib1.so", RTLD_LAZY);
    void* dlHandle2 = dlopen("./liblib2.so", RTLD_LAZY);
    if (dlHandle1 == NULL || dlHandle2 == NULL) {
        std::cerr << "dlopen failed:" << std::endl;
        return -1;
    }

    Func func1 = (Func)dlsym( dlHandle1, "func1");
    Func func2 = (Func)dlsym( dlHandle2, "func2");
    char* error = dlerror();
    if (error != NULL) {
        std::cerr << "dlsym failed:" << error << std::endl;
        return -1;
    }

    func1();
    func2();
    std::cout << "main end" << std::endl;
}

#else

extern "C" void func1();
extern "C" void func2();

extern Global global;

int main() 
{
    std::cout << "main_link start" << std::endl;
    func1();
    std::cout << "in main_link: " << &global << std::endl;
    func2();
    std::cout << "main end" << std::endl;
}

#endif

