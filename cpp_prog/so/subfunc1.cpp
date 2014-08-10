
#include "msg.h"

void subfunc1(MsgMap& intMap) {
    Object* msg = new Msg("123456789");
    intMap["key"] = msg;
}

