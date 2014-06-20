#ifndef __LOG_H__
#define __LOG_H__

#ifndef STDOUT_LOG
#include "log4c.h"
#endif

namespace dyc {

#ifdef STDOUT_LOG

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

const char* errno2str(int errno_p);
const char* syscall2str(int );

#define LOGOUT stdout

#define DEBUG(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(BLUE); \
        fprintf(LOGOUT," [DEBUG]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define TRACE(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT,"[TRACE]\t"); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        dyc_global.unlock(); \
    }while(0)

#define INFO(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT," [INFO] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define NOTICE(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT," [NOTICE] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    }while(0)

#define WARN(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(YELLOW); \
        fprintf(LOGOUT,"[WARN] "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)

#define FATAL(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(RED); \
        fprintf(LOGOUT," [FATAL]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%d][%s()] " format"\n", __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)

#define FATAL_ERROR(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(RED); \
        fprintf(LOGOUT," [FATAL]  "); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,"[%s:%s][%s:%d][%s()] " format"\n", errno2str(errno) ,strerror(errno) , __FILE__, __LINE__, __FUNCTION__, ##arguments); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)


#define CHECK(cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL(fmt, ##arg);  \
    } \
} while(0)

#define CHECK_ERROR(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL(fmt, ##arg);  \
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
        WARN(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)


#else  // if not define STDOUT_LOG

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

#define DEBUG(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_DEBUG, format, ##arguments);  \
    }while(0)

#define TRACE(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_TRACE, format, ##arguments);  \
    }while(0)

#define INFO(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_INFO, format, ##arguments);  \
    }while(0)

#define NOTICE(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_NOTICE, format, ##arguments);  \
    }while(0)

#define WARN(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_WARN, format, ##arguments);  \
    } while(0)

#define FATAL(format, arguments...) \
    do{ \
        log4c_category_log(gDYCLogObj, LOG4C_PRIORITY_FATAL, format, ##arguments);  \
    } while(0)

#endif

} // namespace

#endif // __LOG_H__
