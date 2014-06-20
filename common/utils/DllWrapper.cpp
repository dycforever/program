#include <DllWrapper.h>
#include <dlfcn.h>

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
        ERROR("dllopen failed: %s", ::dlerror());
        return false;
    }
    return true;
}

bool DllWrapper::DllClose()
{
    if (mHandler != NULL) {
        int ret = ::dlclose(mHandler);
        if (ret != 0) {
            ERROR("dllclose failed: %s", ::dlerror());
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
        ERROR("dllsymbol failed: %s", ::dlerror());
    }
    return symbol;
}

}
