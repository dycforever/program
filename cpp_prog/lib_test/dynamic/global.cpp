
#include <iostream>
#include <stdio.h>
#include "global.h"

__attribute__((constructor)) static void global_init();
__attribute__((destructor)) static void global_deinit();

void global_init()
{
    std::cout << "call global_init()" << std::endl;
}

void global_deinit()
{
    std::cout << "call global_deinit()" << std::endl;
}

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

