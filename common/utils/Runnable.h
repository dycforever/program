#ifndef UTIL_RUNNABLE_H
#define UTIL_RUNNABLE_H

namespace dyc {

class Runnable
{
public:
    Runnable() {}
    virtual ~Runnable() {}

public:
    virtual void Run() = 0;
    
    virtual void Free() {
        delete this;
    }
};

}

#endif //UTIL_RUNNABLE_H
