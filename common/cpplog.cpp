
#include <boost/format.hpp>
#include <iostream>

template<typename ARG1>
void logtrace(const char* fmt, ARG1 arg1){
    boost::format s(fmt);
    s % arg1;
    std::cout << s << std::endl;
}

int main() {
    logtrace("i = %d", 1234);
}