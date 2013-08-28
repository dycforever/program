//#include "common.h"
#include <algorithm>
#include <iostream>

class MyClass {
private:
    void operator = (MyClass& m){}
    template <class T> void f(T) {}
};

// compile error: template function can't be virtual
// 
// class MyClass2 {
//     virtual template <class T> void f(T) {}
// };
//

//compile error: template function can't be virtual

class MyClass2 {
    template <class T> void f(T=2) {}
};


int main () {
    int a = 1;
    int b = 2;
    std::swap<int>(a, b);
    std::cout << a << " " << b << std::endl;
    // output:
    // 2 1

// compile error: the object can be swapped if only 
//                their have assignment operator and copy construction
//
//    MyClass ma;
//    MyClass mb;
//    std::swap<MyClass>(ma, mb);

}
