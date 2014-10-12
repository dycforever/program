#ifndef DYC_COMMON_H
#define DYC_COMMON_H

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

// linux kernel header
#include <sys/syscall.h>
//#include "poison.h"

namespace dyc {
extern char commonErrorMsgBuffer[];
void COMMON_ERROR_MSG(const char* msg, ...);

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

}; // namespace dyc 

struct profiler{
    profiler(const char* func_name){
        gettimeofday(&tv, NULL);
    }
    ~profiler(){
        struct timeval tv2;
        gettimeofday(&tv2, NULL);
        long cost = (tv.tv_sec - tv.tv_sec) * 1000000 + (tv.tv_usec - tv.tv_usec);
        //! post to some manager
    }
    struct timeval tv;
};

#define PROFILER() profiler(__FUNCTION__)

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
        free((void*)p);
    }
}
#else  // if not define _DEBUG

#define NEW new(std::nothrow)

#endif // _DEBUG


template <class CON>
void print_container(std::string prefix, const CON& container) {
    std::copy(container.begin(), container.end(), 
            std::ostream_iterator<typename CON::value_type>(std::cout, " "));
    std::cout << std::endl;
}

#endif // DYC_COMMON_H


// vim: set ts=4 sw=4 sts=4 tw=100

