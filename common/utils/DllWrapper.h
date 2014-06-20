#ifndef DLL_WRAPPER_H
#define DLL_WRAPPER_H

#include <common.h>
#include <log.h>

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

private:
    std::string mDllPath;
    void *mHandler;

};

}

#endif //DLL_WRAPPER_H
