
#include "msg.h"

std::string reverse(const std::string& str)
{
    if (str.size() > 0) {
        return str.substr(str.size() - 1, 1) + reverse(str.substr(0, str.size() - 1));
    }
    return "";
}

void subfunc2(MsgMap& intMap) {
    Object* msg = intMap["key"];
    Object* newMsg = new Msg(reverse(msg->str()));
    intMap["key"] = newMsg;
}


