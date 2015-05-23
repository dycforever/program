
#include <iostream>
#include <stdio.h>
#include "global.h"

Global::Global() 
{
    std::cout << "call Global::Global()" << std::endl;
}

Global global;

void PrintGlobal(const char* mesg)
{
    printf("[%s] global addr: %p\n", mesg, &global);
    fflush(stdout);
}

