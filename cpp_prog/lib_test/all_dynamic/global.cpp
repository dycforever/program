
#include <iostream>
#include <stdio.h>
#include "global.h"

Global::Global() 
{
    std::cout << "call Global::Global()" << std::endl;
}

Global global;
static int static_test;

void PrintGlobal(const char* mesg)
{
    printf("[%s] global addr: %p\n", mesg, &static_test);
    fflush(stdout);
}

