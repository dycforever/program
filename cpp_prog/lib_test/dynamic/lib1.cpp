
#include <iostream>
#include "global.h"

void PrintGlobal(const char*);
extern "C"
{

void func1()
{
    PrintGlobal("in func1");
}

}
