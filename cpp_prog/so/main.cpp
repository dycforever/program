#include "header.h"
#include "msg.h"
#include <dlfcn.h>

int main() {
    void* dl_handle = dlopen("./hehe/libdeleter.so", RTLD_LAZY);
    if (dl_handle == NULL) {
        std::cerr << "dlopen ./libdeleter.so failed:" << std::endl;
        return -1;
    }

    func_t deleter = (func_t)dlsym( dl_handle, "deleter");
    char* error = dlerror();
    if (error != NULL)
    {
        std::cerr << "dlsym failed:" << error << std::endl;
        return -1;
    }

    MsgMap intMap;
    func(intMap, deleter);
    while(1)
        sleep(100);
//    dlclose(dl_handle);
//
}

