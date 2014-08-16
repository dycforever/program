
#ifndef __RUNNABLE_INCLUDE__
#define __RUNNABLE_INCLUDE__

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

#endif //__RUNNABLE_INCLUDE__
