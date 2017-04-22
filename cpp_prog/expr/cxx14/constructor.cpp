#include <execinfo.h>
#include <iostream>
#include <string>

using namespace std;

class FooClass
{
public:
    FooClass()
    {
        cout << "calling FooClass()" << endl;
    }

    ~FooClass()
    {
    }

    FooClass(const FooClass&& a)
    {
        cout << "calling FooClass(const FooClass&&)" << endl;
    }

    FooClass(FooClass&& a)
    {
        cout << "calling FooClass(FooClass&&)" << endl;
    }

    FooClass(const FooClass &a)
    {
        cout << "calling FooClass(const FooClass&)" << endl;
    }

    FooClass& operator = (FooClass &&rhs)
    {
        cout << "calling operator = (FooClass &&rhs)" << endl;
        return *this;
    }
};

FooClass Get()
{
    return FooClass();
}

/* *******************
 * 输出:
 *
 * calling FooClass()
 * calling FooClass(const FooClass&)
 * ===========
 * calling FooClass()
 * calling FooClass(FooClass&&)
 * calling FooClass(FooClass&&)
 * ===========
 * calling FooClass()
 * calling FooClass(FooClass&&)
 * calling FooClass(FooClass&&)
 *
 * *********************/

int main() {
    FooClass f;
    // 调用 FooClass(const FooClass &a)
    FooClass f1(f);
    cout << "===========" << endl;
    // 调用 FooClass(FooClass &&a)
    // 注意要在编译时指定 -fno-elide-constructors 才能防止编译器自动 RVO
    FooClass f2(Get());
    cout << "===========" << endl;
    // 调用 FooClass(FooClass &&a)
    FooClass f3(move(Get()));
}