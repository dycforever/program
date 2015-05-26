#include <unistd.h>
#include <dlfcn.h>

#include <iostream>

typedef bool (*func_t)();

class CloseHandleHelper {
public:
    CloseHandleHelper(void* handle) : handle_(handle) {
    }

    ~CloseHandleHelper() {
        if (handle_) {
            dlclose(handle_);
        }
    }

private:
    void* handle_;
};

int main(int argc, char* argv[])
{
    void* handle1 = dlopen("./libtest1.so", RTLD_NOW);
    if (!handle1) {
        std::cerr << "dlopen failed" << std::endl;
        return (-1);
    }
    CloseHandleHelper closeHelper1(handle1);

    void* handle2 = dlopen("./libtest2.so", RTLD_NOW);
    if (!handle2) {
        std::cerr << "dlopen failed" << std::endl;
        return (-1);
    }
    CloseHandleHelper closeHelper2(handle2);

    func_t f1 = (func_t)dlsym(handle1, "saySth1");
    if (!f1) {
        std::cerr << "dlsym failed, saySth1:" << dlerror() << std::endl;
        return (-1);
    }
    func_t f2 = (func_t)dlsym(handle2, "saySth2");
    if (!f2) {
        std::cerr << "dlsym failed, saySth2:" << dlerror() << std::endl;
        return (-1);
    }

    f1();
    f2();

    return (0);
}
