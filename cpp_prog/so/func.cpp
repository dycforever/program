
#include "header.h"

void func(MsgMap& intMap, func_t deleter) {
    subfunc1(intMap);
    Object* msg = intMap["key"];
    std::cout << "after subfunc1 " << msg->str() << std::endl;
    subfunc2(intMap);
    Object* msg2 = intMap["key"];
    std::cout << "after subfunc2 " << msg2->str() << std::endl;
    deleter(msg);
    deleter(msg2);
}
