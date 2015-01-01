
#include <iostream>
#include "global.h"

void PrintGlobal(const char*);

extern "C"
{

void func2()
{
    PrintGlobal("in func2");
}

}
