#ifndef HEADER
#define HEADER

#include <map>
#include <unistd.h>
#include <string>
#include <iostream>

class Object
{
public:
    Object(){}
    virtual ~Object() {}
    virtual std::string str() = 0;
};

typedef std::map<std::string, Object*> MsgMap;

typedef void (*func_t) (Object*);
void func(MsgMap&, func_t);

void subfunc1(MsgMap&);
void subfunc2(MsgMap&);

extern "C" void deleter(Object* obj);

#endif
