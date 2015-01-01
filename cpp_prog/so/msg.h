
#include "header.h"

class Msg : public Object
{
public:
    Msg();
    Msg(const std::string& str);
    ~Msg();
    std::string str();

private:
    std::string mMsg;
};


