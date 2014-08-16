#ifndef __LOG_H__
#define __LOG_H__

#include <iostream>

#ifdef USE_LOG4C
#include "log4c.h"
#endif

namespace dyc {

const char* errno2str(int errno_p);
#ifndef USE_LOG4C

enum COLOR{BLACK=0,RED=1,GREEN=2,YELLOW=3,BLUE=4,WHITE=9};
enum Format{BOLD=1,NORMAL,UNDERSCORE=4,REVERSE=7,DELETE=9};
inline void PRINT_COLOR(COLOR foreground,COLOR background=BLACK,Format format=BOLD){
	std::cout<<"\E[3"<<foreground<<";4"<<background<<";"<<format<<"m";
}
inline void UNPRINT_COLOR(){
	std::cout<<"\033[0m";
}

class DYC_GLOBAL {
public:
    DYC_GLOBAL() {
        pthread_spin_init(&g_spin_lock, PTHREAD_PROCESS_PRIVATE);
    }
    void lock() {
        pthread_spin_lock(&g_spin_lock); 
    }

    void unlock() {
        pthread_spin_unlock(&g_spin_lock); 
    }
private:
    pthread_spinlock_t g_spin_lock;
};

extern DYC_GLOBAL dyc_global;

const char* syscall2str(int );

#define LOGOUT stdout

#define DEBUG_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(BLUE); \
        fprintf(LOGOUT," [DEBUG_LOG]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define TRACE_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT,"[TRACE_LOG]\t"); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        dyc_global.unlock(); \
    }while(0)

#define INFO_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT," [INFO_LOG] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define NOTICE_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT," [NOTICE_LOG] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define WARN_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(YELLOW); \
        fprintf(LOGOUT,"[WARN_LOG] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)

#define FATAL_LOG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(RED); \
        fprintf(LOGOUT," [FATAL_LOG]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)

#define FATAL_ERROR(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(RED); \
        fprintf(LOGOUT," [FATAL_LOG]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%s][%s:%d][%s()] " format"\n", errno2str(errno) ,strerror(errno) , __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)


#define CHECK(cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL_LOG(fmt, ##arg);  \
    } \
} while(0)

#define CHECK_ERROR(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL_LOG(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)

#define CHECK_ERRORNO(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL_ERROR(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)

#define CHECK_WARN(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        WARN_LOG(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)


#else  // if not define USE_LOG4C

extern log4c_category_t* gDYCLogObj;

class DYC_GLOBAL {
public:
    DYC_GLOBAL() {
        log4c_init();  
        gDYCLogObj = log4c_category_get("dyclog");
    }

    ~DYC_GLOBAL() {
        log4c_fini();
    }
};

#define DEBUG_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_DEBUG, format, ##arguments);  \
    }while(0)

#define TRACE_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_TRACE, format, ##arguments);  \
    }while(0)

#define INFO_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_INFO, format, ##arguments);  \
    }while(0)

#define NOTICE_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_NOTICE, format, ##arguments);  \
    }while(0)

#define WARN_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_WARN, format, ##arguments);  \
    } while(0)

#define FATAL_LOG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_FATAL, "[%s:%d][%s()] " format, __FILE__, __LINE__, __FUNCTION__, ##arguments);  \
    } while(0)

#define FATAL_ERROR(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_FATAL, "[%s:%s][%s:%d][%s()] " format, errno2str(errno) ,strerror(errno) , __FILE__, __LINE__, __FUNCTION__, ##arguments);  \
    } while(0)



#endif

} // namespace

#endif // __LOG_H__
