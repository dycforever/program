
#include <iostream>

void func1();
void func2();

int main() 
{
    std::cout << "main start" << std::endl;
    func1();
    func2();
    std::cout << "main end" << std::endl;
}
