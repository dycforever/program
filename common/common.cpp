#include <stdarg.h>
#include "common.h"
namespace dyc {

#define COMMON_ERROR_MSG_BUFFER_LENGTH 1024
#define COMMON_ERROR_MSG_BUFFER_ALLOC_LENGTH (COMMON_ERROR_MSG_BUFFER_LENGTH+1)

char commonErrorMsgBuffer[COMMON_ERROR_MSG_BUFFER_ALLOC_LENGTH];
void COMMON_ERROR_MSG(const char*fmt, ...) 
{
    va_list argptr;
    va_start(argptr, fmt);
    vsnprintf(commonErrorMsgBuffer, COMMON_ERROR_MSG_BUFFER_LENGTH, fmt, argptr);
    va_end(argptr);
}

char* getErrorMsg() 
{
    return commonErrorMsgBuffer;
}

AllocMap* dycMemAllocMap;

void addTrack(void* addr, unsigned long asize, const char *fname, long lnum) 
{ 
    ALLOC_INFO *info = new ALLOC_INFO();
    info->address = addr;
    strncpy(info->file, fname, 1024);
    info->line = lnum;
    info->size = asize;
    if (!dycMemAllocMap)
    {
        dycMemAllocMap = new AllocMap;
    }
    dycMemAllocMap->insert(std::make_pair(addr,info));
}

bool RemoveTrack(void* addr)
{
    if(!dycMemAllocMap || 0 == dycMemAllocMap->size())
    {
        return true;
    }
    AllocMap::iterator iter = dycMemAllocMap->find(addr);
    if (iter != dycMemAllocMap->end())
    {
        ALLOC_INFO* info = iter->second;
        delete info;
        dycMemAllocMap->erase(iter);
        return true;
    }
    return false;
}

void dumpUnfreed()
{
    AllocMap::iterator iter;
    ALLOC_INFO* info;
    unsigned long totalSize = 0;
    if(!dycMemAllocMap || 0 == dycMemAllocMap->size())
    {
        return;
    }

    for(iter = dycMemAllocMap->begin(); iter != dycMemAllocMap->end(); iter++)
    {
        printf("%-50s: LINE %lu, ADDRESS 0x%p size %lu unfreed\n", iter->second->file, iter->second->line
                , iter->second->address, iter->second->size);
        totalSize += iter->second->size;
        info = iter->second;
        delete info;
    }
//    printf(" ============== calling map ==========\n");
    delete dycMemAllocMap;
    printf("----------------------------------------------------------- \n");
    printf("Total Unfreed: %lu bytes \n", totalSize);
}

};
