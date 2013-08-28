#include "Inter.h"

class Sub: public Inter {

    // will get error:
    //
    // error: invalid use of incomplete type ‘struct Inter::Pimpl’
    // error: forward declaration of ‘struct Inter::Pimpl’
    //
    //    void subrun() {
    //        impl->run();
    //    }
};

int main() {
    Inter inter;
    inter.run();
    Sub sub;
}
