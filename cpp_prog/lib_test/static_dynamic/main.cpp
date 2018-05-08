
#include <iostream>

void ssl();
void curl();

int main() 
{
    std::cout << "main calling ssl()" << std::endl;
    ssl();
    std::cout << "main calling curl()" << std::endl;
    curl();
    std::cout << "main end" << std::endl;
}
