#include <iostream>

using namespace std;

template<typename T1, typename T2, typename T3>
T3 func(T1 a, T2 b) {
    return a>b ? a : b;
}

template<typename T1, typename T2>
T2 func2(const T1 a) {
    return (T2)(a);
}

template<typename T>
void overTest (T p) {
    (void)p;
    cout << "call template" << endl;
}

template<>
void overTest (int p) {
    (void)p;
    cout << "call template -> int" << endl;
}

void overTest (int p) {
    (void)p;
    cout << "call int" << endl;
}

int main () {
    int i=1;
    double b=2.3;
    (void)b;

    // must specify return type
    float f = func<int, double, float>(10, 2.3);
    cout << f << endl;

    // OK, use cast
    float f2 = static_cast<float>( func2<int, double>(i) );
    cout << f2 << endl;
    
    overTest(1.2);
    overTest(1);
    overTest<int>(1);
}
