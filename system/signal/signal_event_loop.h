
#include <map>
#include <tr1/functional>


class SignalEventLoop
{
public:
    typedef std::tr1::function<void()> EventCallBackFunc;

public:
    SignalEventLoop();
    virtual ~SignalEventLoop();
    
public:
    bool Start();

public:
    bool RegistEventCallBackFunc(int signo, const EventCallBackFunc &callBack);

private:
    static void SignalHandler(int signo);
    const static int sMaxSigno = 32; // max signo in linux
    static bool sSignoArray[sMaxSigno];

private:
    std::map<int, EventCallBackFunc> mEventCallBackMap;

};

