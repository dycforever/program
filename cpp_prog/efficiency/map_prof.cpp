#include <map>
#include <tr1/unordered_map>
#include <string>
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <stdint.h>

class TimeUtil
{
public:
    static int64_t GetTimeInSec() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return tval.tv_sec;
    }

    static int64_t GetTimeInMs() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return (tval.tv_sec * 1000LL + tval.tv_usec / 1000);
    }
    
    static int64_t GetTimeInUs() {
        struct timeval tval;
        gettimeofday(&tval, NULL);
        return (tval.tv_sec * 1000000LL + tval.tv_usec);
    }

    static timespec GetTimeSpec(int64_t usecOffset) {
        timespec tspec;
        int64_t uTime = GetTimeInUs() + usecOffset;
        tspec.tv_sec = uTime / 1000000;
        tspec.tv_nsec = (uTime % 1000000) * 1000;
        return tspec;
    }
};

std::string int2str(size_t i)
{
    std::stringstream ss;
    ss << i;
    std::string str;
    ss >> str;
    return str;
}

int main()
{
    size_t LOOPCOUNT = 300000;
    size_t sum = 0;
    int64_t start = 0;

#ifdef TEST_HASH_MAP 
    std::tr1::unordered_map<std::string, size_t> hashMap;
    for (size_t i = 0; i < 100; i++) {
        hashMap[int2str(i)] = i;
    }
    sum = 0;
    start = TimeUtil::GetTimeInMs();
    for (size_t i = 0; i < LOOPCOUNT; i++) {
        sum += hashMap[int2str(i % 100)];
    }
    std::cout << "sum = " << sum 
        << " hash cost " << TimeUtil::GetTimeInMs() - start << std::endl;
#endif

#ifdef TEST_STD_MAP 
    std::map<std::string, size_t> stdMap;
    for (size_t i = 0; i < 100; i++) {
        stdMap[int2str(i)] = i;
    }
    sum = 0;
    start = TimeUtil::GetTimeInMs();
    for (size_t i = 0; i < LOOPCOUNT; i++) {
        sum += stdMap[int2str(i % 100)];
    }
    std::cout << "sum = " << sum 
        << " std cost " << TimeUtil::GetTimeInMs() - start << std::endl;
#endif
}