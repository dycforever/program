
#include "msg.h"

Msg::Msg(const std::string& str)
    :mMsg(str){}

Msg::Msg() {}

Msg::~Msg() {}

std::string Msg::str() 
{ return mMsg; }


