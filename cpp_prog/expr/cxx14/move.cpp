
#include <iostream>
#include <utility>

using namespace std;

class Obj {
};

void Inner(Obj& obj) { cout << "lvalue" << endl; }
void Inner(Obj&& obj) { cout << "rvalue" << endl; }

template <class T> void Outer(T&& t) {
    Inner(forward<T>(t));
    Inner((t));
}

void modify(string&& s) {
    s.append("x");
}

int main() {
    Obj obj;
    Outer(move(obj));
    string s = "dyc";
    cout << s << endl;
    modify(move(s));
    cout << s << endl;
    modify(string(move(s)));
    cout << s << endl;
}