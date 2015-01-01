#ifndef DLL_WRAPPER_H
#define DLL_WRAPPER_H

#include "common.h"

namespace dyc {

class DllWrapper
{
public:
    DllWrapper(const std::string& path);
    ~DllWrapper();

public:
    bool DllOpen();
    bool DllClose();
    void* DllSymbol(const std::string &symbolName);

    static char* errstr();

private:
    std::string mDllPath;
    void *mHandler;

    static char errorMsg[1024];
};

}

#endif //DLL_WRAPPER_H
