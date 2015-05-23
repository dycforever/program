
#include <iostream>
#include <dlfcn.h>

int main() 
{
    std::cout << "main_dlopen start" << std::endl;
    typedef void (*Func)(bool);

#ifdef LAZY
    void* dlHandle = dlopen("./libtest.so", RTLD_LAZY);
#else
    void* dlHandle = dlopen("./libtest.so", RTLD_NOW);
#endif
    if (dlHandle == NULL) {
        char* error = dlerror();
        if (error != NULL) {
            std::cerr << "dlopen failed:" << error << std::endl;
        }
        return -1;
    }
    std::cout << "dlopen success" << std::endl;

    Func func1 = (Func)dlsym(dlHandle, "func");
    char* error = dlerror();
    if (error != NULL) {
        std::cerr << "dlsym failed:" << error << std::endl;
        return -1;
    }

    func1(true);
    func1(false);
    if (dlclose(dlHandle) != 0) {
        std::cerr << "dlclose failed:" << std::endl;
        return -1;
    }
    std::cout << "main end" << std::endl;
}


