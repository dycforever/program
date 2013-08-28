#include <iostream>
#include "Inter.h"

using namespace std;

struct Inter::Pimpl {
    void run() {
        std::cout << "Pimpl run()" << endl;
    }
};

Inter::Inter() {
    cout << "construct Inter" << endl;
    impl = new Pimpl();
}

void Inter::run() {
    impl->run();
}
