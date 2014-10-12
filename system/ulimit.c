
#include <stdio.h>
#include <sys/resource.h>

//  /* Kinds of resource limit.  */
//  enum __rlimit_resource
//  {
//    RLIMIT_CPU = 0,
//    RLIMIT_FSIZE = 1,
//    RLIMIT_DATA = 2,
//    RLIMIT_STACK = 3,
//    RLIMIT_CORE = 4,
//    __RLIMIT_RSS = 5,
//    RLIMIT_NOFILE = 7,
//    RLIMIT_AS = 9,
//    __RLIMIT_NPROC = 6,
//    __RLIMIT_MEMLOCK = 8,
//    __RLIMIT_LOCKS = 10,
//    __RLIMIT_SIGPENDING = 11,
//    __RLIMIT_MSGQUEUE = 12,
//    __RLIMIT_NICE = 13,
//    __RLIMIT_RTPRIO = 14,
//    __RLIMIT_RTTIME = 15,
//    __RLIMIT_NLIMITS = 16,
//  };

const char* ulimitName(int i)
{
    switch(i) {
        case 0 :  return "CPU";
        case 1 :  return "FSIZE";
        case 2 :  return "DATA";
        case 3 :  return "STACK";
        case 4 :  return "CORE";
        case 5 :  return "RSS";
        case 7 :  return "NOFILE";
        case 9 :  return "AS";
        case 6 :  return "NPROC";
        case 8 :  return "MEMLOCK";
        case 10 :  return "LOCKS";
        case 11 :  return "SIGPENDING";
        case 12 :  return "MSGQUEUE";
        case 13 :  return "NICE";
        case 14 :  return "RTPRIO";
        case 15 :  return "RTTIME";
        case 16 :  return "NLIMITS";
    }
}

int main()
{
    struct rlimit rlim, rlim_new;  
    int i = 0;
    for (i = 0; i < 17; i++) {
        if (getrlimit(i, &rlim) == 0) {  
            printf("%s: cur[%ld] max[%ld]\n", ulimitName(i), rlim.rlim_cur, rlim.rlim_max);
        }
    }
    getrlimit(RLIMIT_CORE, &rlim);
    rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;  
    printf("set %d\n", setrlimit(RLIMIT_CORE, &rlim_new));

    for (i = 0; i < 17; i++) {
        if (getrlimit(i, &rlim) == 0) {  
            printf("%s: cur[%ld] max[%ld]\n", ulimitName(i), rlim.rlim_cur, rlim.rlim_max);
        }
    }
//            rlim_new.rlim_cur = rlim_new.rlim_max = RLIM_INFINITY;  
//            if (setrlimit(RLIMIT_CORE, &rlim_new)!= 0) {  
//                /* failed. try raising just to the old max */  
//                rlim_new.rlim_cur = rlim_new.rlim_max = rlim.rlim_max;  
//                (void)setrlimit(RLIMIT_CORE, &rlim_new);  
//            }  
}
