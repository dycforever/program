#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>
using namespace std;

class Trival {
public:
    ~Trival() {cout << "~Trival" << endl;}
    Trival() {member = 3;}
    int member;
};

std::function<int (vector<int>&)> compareAndCount () {
    Trival tr;
    return [=](vector<int>& vec) {
        int count = 0;
        for (auto iter=vec.begin(); iter != vec.end(); ++iter) {
            if (*iter > tr.member) {
                ++count;
            }
        }
        return count;
    };
}

int main() {
    // [] named capture specification
    // () named arguement list
    auto helloFunc = [] () {cout << "hello world" << endl;};
    helloFunc();

    // []    Capture nothing (or, a scorched earth strategy?)
    // [&]   Capture any referenced variable by reference
    // [=]   Capture any referenced variable by making a copy
    // [=, &foo] Capture any referenced variable by making a copy, but capture variable foo by reference
    // [bar] Capture bar by making a copy; don't copy anything else
    // [this]    Capture the this pointer of the enclosing class.            WONDERFUL !!!!
    auto addFunc = [] (int& i) {return i++;};

    // a real function pointer can hold the lambda
    typedef int(*RawFuncPtr) (int&);
    RawFuncPtr fptr = addFunc;

    vector<int> vec;
    for (int i=0;i<10;i++) {
        vec.push_back(i);
    }
    for_each(vec.begin(), vec.end(), addFunc);
    for_each(vec.begin(), vec.end(), fptr);
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    // NOTICE !!! lambda below refers to an invalid local variable
    auto cmpFunc = compareAndCount();
    cout << "out of cmp&cnt" << endl;
    cout << "cmp count = " << cmpFunc(vec) << endl;
}
