#include <dlfcn.h>
#include "utils/DllWrapper.h"

namespace dyc {

DllWrapper::DllWrapper(const std::string& path)
    : mDllPath(path),
      mHandler(NULL)
{}

DllWrapper::~DllWrapper()
{
    DllClose();
}

bool DllWrapper::DllOpen()
{
    mHandler = ::dlopen(mDllPath.c_str(), RTLD_NOW);
    if (mHandler == NULL) {
        // FATAL_LOG("dllopen failed: %s", ::dlerror());
        snprintf(errorMsg, 1024, "dllopen failed: %s", ::dlerror());
        return false;
    }
    return true;
}

bool DllWrapper::DllClose()
{
    if (mHandler != NULL) {
        int ret = ::dlclose(mHandler);
        if (ret != 0) {
            // FATAL_LOG("dllclose failed: %s", ::dlerror());
            snprintf(errorMsg, 1024, "dllclose failed: %s", ::dlerror());
            return false;
        }
        mHandler = NULL;
    }
    return true;
}

void* DllWrapper::DllSymbol(const std::string& symbolName)
{
    if (mHandler == NULL) {
        return NULL;
    }
    void* symbol = ::dlsym(mHandler, symbolName.c_str());
    if (symbol == NULL) {
        // FATAL_LOG("dllsymbol failed: %s", ::dlerror());
        snprintf(errorMsg, 1024, "dllsymbol failed: %s", ::dlerror());
    }
    return symbol;
}

}
