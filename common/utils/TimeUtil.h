#ifndef TIME_UTIL_H
#define TIME_UTIL_H

#include <sys/time.h>

#include "common.h"

namespace dyc {

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
}

#endif //TIME_UTIL_H
