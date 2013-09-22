
#include <stdio.h>

#include <boost/bind.hpp>
#include <boost/function.hpp>

using namespace boost;

int echo (int i) {
    printf("out %d\n", i);
}

int main() {
    function<int ()> func;
    if (func) {
        func();
    }
    func = bind(echo, 2);
    if (func) {
        func();
    }
}

