
#include <iostream>

class Obj {
public:
    Obj() {
        std::cout << "construct obj " << &i << std::endl;
    }
    Obj(const Obj&) {
        std::cout << "construct copy obj " << &i << std::endl;
    }
    ~Obj() {
        std::cout << "destruct obj " << &i << std::endl;
    }
    int i;
};

Obj f() {
    Obj* op = new Obj;
    std::cout << "op=" << op << std::endl;
    return *op;
}

Obj f2() {
    return *(new Obj);
}

int main() {
    Obj o = f();
    Obj o2 = f2();
    std::cout << "&o=" << &o << std::endl;
    std::cout << "&o2=" << &o2 << std::endl;
}