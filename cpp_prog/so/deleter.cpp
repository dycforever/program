
#include "header.h"

#include <sys/time.h>
int gettimeofday(struct timeval*tv, struct timezone *tz);

static void trival_loop()
{
    for (int i = 0; i < 100; i++) {
        ;
    }

}

void get_time()
{
    struct timeval tv;
    trival_loop();
//    gettimeofday(&tv, NULL);
}

extern "C" 
{
    void deleter(Object* obj)
    {
        for (int i = 0; i < 1000000; i++) {
            get_time();
        }
        delete obj;
    }
}
