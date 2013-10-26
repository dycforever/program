#ifndef __COMMON_H__
#define __COMMON_H__

// C header
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>

// Linux C header
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <errno.h>

// C++ header
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>


namespace dyc {

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
        PRINT_COLOR(GREEN); \
        fprintf(LOGOUT,"[TRACE]\t"); \
        UNPRINT_COLOR(); \
        fprintf(LOGOUT,format"\n", ##arguments);\
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

#define WARNING(format, arguments...) \
    do{ \
        dyc_global.lock(); \
        PRINT_COLOR(YELLOW); \
        fprintf(LOGOUT,"[WARNING] "); \
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
        fprintf(LOGOUT,"[%d:%s][%s:%d][%s()] " format ,errno ,strerror(errno) , __FILE__, __LINE__, __FUNCTION__, ##arguments, errno, strerror(errno)); \
        fflush(LOGOUT);\
        dyc_global.unlock(); \
    } while(0)



#define CHECK_ERROR(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)

#define CHECK_ERRORNO(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        FATAL_ERROR(fmt" with error %d:%s\n", ##arg);  \
        return (ret);  \
    } \
} while(0)

#define CHECK_WARNING(ret, cond, fmt, arg...) do { \
    if (!(cond)) {   \
        WARNING(fmt, ##arg);  \
        return (ret);  \
    } \
} while(0)


typedef struct {
    void* address;
    unsigned long size;
    char file[1024];
    long line;
} ALLOC_INFO;

typedef std::map<void*, ALLOC_INFO*> AllocMap;
extern AllocMap* dycMemAllocMap;

void dumpUnfreed();
void addTrack(void* addr, unsigned long asize, const char *fname, long lnum);
bool RemoveTrack(void* addr);


#define DELETE(pointer) \
    do { \
        if ((pointer) != NULL) { \
            operator delete (((void*)pointer), 0); \
            (pointer) = NULL; \
        } \
    } while (0)

#define DELETES(pointer) \
    do { \
        if ((pointer) != NULL) { \
            operator delete[] (((void*)pointer), 0); \
            (pointer) = NULL; \
        } \
    } while (0)

// File operation define
#define FCLOSE(file_stream) \
    do { \
        if ((file_stream) != NULL) { \
            fclose((file_stream)); \
            (file_stream) = NULL; \
        } \
    } while (0)

// Some usefull const

const size_t KB = 1024LU;
const size_t MB = 1024LU * KB;
const size_t GB = 1024LU * MB;

const size_t MAX_FILE_PATH_LENGTH = 4 * KB;
const size_t MAX_FILE_NAME_LENGTH = 4 * KB;
const size_t MAX_FILE_FULL_PATH_LENGTH = MAX_FILE_PATH_LENGTH + MAX_FILE_NAME_LENGTH;

// the inline assembler code makes type blur,
// so we disable warnings for a while.
#if __GNUC_MINOR__ >= 6
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"

const pthread_t NULL_THREAD_HANDLE = (pthread_t)0;

#if __GNUC_MINOR__ >= 6
#pragma GCC diagnostic pop
#else
#pragma GCC diagnostic error "-Wconversion"
#pragma GCC diagnostic error "-Wold-style-cast"
#endif

// Do not passing const char[] to string_buffer, it will core dump
inline size_t trim_right(char *string_buffer, const size_t string_buffer_length) {
    if (NULL == string_buffer || 0 == string_buffer_length) {
        return 0;
    }

    size_t new_length = string_buffer_length;
    char *rbegin = string_buffer + new_length - 1;

    while (new_length > 0 && ('\0' == *rbegin || '\n' == *rbegin || '\r' == *rbegin || ' ' == *rbegin)) {
        *(rbegin--) = '\0';
        --new_length;
    }

    return new_length;
}

// Do not passing const char[] to start, it will core dump
// Be sure *end must equal to '\0', or the final token will apear unexpect phenomenon.
inline char *get_next_token(char *&start, const char *end, const char delimiter) {
    if (NULL == start || end == NULL) {
        return NULL;
    }

    if (start >= end) {
        return NULL;
    }

    char *token = start;

    for (; start < end; ++start) {
        if (delimiter == *start) {
            *start = '\0';
            ++start;
            break;
        }
    }

    return token;
}

// Simple function, not allowed lead blank, not allowed negative sign.
// typename should be integer type, do not use other types, it may cause some errors.
template<typename T>
inline int get_next_integer(char *&start, const char *end, const char delimiter, T &value) {
    value = 0;

    if (NULL == start || NULL == end) {
        return -1;
    }

    if (start >= end) {
        return -1;
    }

    if (*start == delimiter) {
        return -1;
    }

    for (; start < end; ++start) {
        if (delimiter == *start) {
            *start = '\0';
            ++start;
            break;
        } else if ('0' <= *start && *start <= '9') {
            value = value * 10 + (*start - '0');
        } else {
            WARNING("Try to read integer from a non-integer character[%c].", *start);
            return -1;
        }
    }

    return 0;
}

// Some usefull file operation
inline int create_file_folder(const std::string &file_path) {
    if (access(file_path.c_str(), F_OK) != 0) {
        if (mkdir(file_path.c_str(), 0777) != 0) {
            FATAL("Create file folder[%s] error!", file_path.c_str());
            return -1;
        }
    }

    return 0;
}

inline int getFileSize(const char *fileName, uint64_t &fileSize) {
    if (NULL == fileName) {
        FATAL("Input arguments error: file_name[address: %p] is NULL!", fileName);
        return -1;
    }

    struct stat fileInformation;
    if (stat(fileName, &fileInformation) < 0) {
        FATAL("Get file[%s] information failed!", fileName);
        return -1;
    }

    fileSize = (uint64_t)fileInformation.st_size;

    return 0;
}

template<typename T>
inline int get_elements_numbers(const char *file_name, uint64_t &elements_numbers) {
    uint64_t file_size = 0;
    if (getFileSize(file_name, file_size) != 0) {
        FATAL("Get file[%s] size failed!", file_name);
        return -1;
    }

    if ((file_size % sizeof(T)) != 0) {
        FATAL("File size must be multiply of sizeof uint64_t[%lu]!", sizeof(T));
        return -1;
    }

    elements_numbers = file_size / sizeof(T);

    return 0;
}

// A simple timer counter
class Timer {

private:

    struct timeval m_begin;
    struct timeval m_end;

public:

    Timer() {
        begin();
    }

    ~Timer() {
    }

    inline static uint64_t time() {
        struct timeval now_time = {0, 0};
        gettimeofday(&now_time, NULL);
        return (uint64_t)(now_time.tv_sec * 1000000 + now_time.tv_usec);
    }

    inline void begin() {
        gettimeofday(&m_begin, NULL);
    }

    inline uint64_t ms_spend() {
        gettimeofday(&m_end, NULL);
        return (uint64_t) ((m_end.tv_sec * 1000000 + m_end.tv_usec) - (m_begin.tv_sec * 1000000 + m_begin.tv_usec));
    }

    inline double second_spend() {
        return static_cast<double>(ms_spend() / 1000000.0);
    }
};

}; // namespace dyc 

#define _DEBUG

#ifdef _DEBUG

#define NEW new(__FILE__, __LINE__)
inline void * operator new(size_t size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    dyc::addTrack(ptr, size, file, line);
    return(ptr);
}

inline void operator delete(void *p, int)
{
    if (dyc::RemoveTrack(p)) {
//        printf("call free %p\n", p);
        free(p);
    }
}

inline void * operator new[](size_t size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    dyc::addTrack(ptr, size, file, line);
    return(ptr);
}

inline void operator delete[](void *p, int)
{
    if (dyc::RemoveTrack(p)) {
//        printf("call delete[]\n");
        free((void*)p);
    }
}
#else  // _DEBUG
#define NEW new(std::nothrow)
#endif // _DEBUG


template <class CON>
void print_container(std::string prefix, const CON& container) {
    std::copy(container.begin(), container.end(), 
            std::ostream_iterator<typename CON::value_type>(std::cout, " "));
    std::cout << std::endl;
}

#endif // __COMMON_H__


// vim: set ts=4 sw=4 sts=4 tw=100
