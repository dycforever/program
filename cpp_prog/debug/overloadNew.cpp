#include <stdio.h>
#include <stdlib.h>
#include <map>

#include "common.h"
using namespace std;

typedef struct {
    unsigned long address;
    unsigned long size;
    char file[1024];
    unsigned long line;
} ALLOC_INFO;

typedef map<unsigned long, ALLOC_INFO*> AllocMap;

AllocMap* allocMap;

#define _DEBUG

#ifdef _DEBUG

#define DEBUG_NEW new(__FILE__, __LINE__)

void AddTrack(unsigned long addr, unsigned long asize, const char *fname, unsigned long lnum) 
{ 
    ALLOC_INFO *info = new ALLOC_INFO();
    info->address = addr;
    strncpy(info->file, fname, 1024);
    info->line = lnum;
    info->size = asize;
    if (!allocMap)
    {
        allocMap = new AllocMap;
    }
    allocMap->insert(make_pair(addr,info));
}

void RemoveTrack(unsigned long addr)
{
    if(!allocMap || 0 == allocMap->size())
    {
        return;
    }
    AllocMap::iterator iter = allocMap->find(addr);
    if (iter != allocMap->end())
    {
        ALLOC_INFO* info = iter->second;
        delete info;
        allocMap->erase(iter);
    }
}

inline void * operator new(unsigned int size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    AddTrack((unsigned long)ptr, size, file, line);
    return(ptr);
}

inline void operator delete(void *p)
{
    RemoveTrack((unsigned long)p);
    free(p);
}
inline void * operator new[](unsigned int size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    AddTrack((unsigned long)ptr, size, file, line);
    return(ptr);
}
inline void operator delete[](void *p)
{
    RemoveTrack((unsigned long)p);
    free(p);
}
#else  // _DEBUG
#define DEBUG_NEW new
#endif // _DEBUG

// 用于检测内存并做最后的内存清理
void DumpUnfreed()
{
    AllocMap::iterator iter;
    ALLOC_INFO* info;
    unsigned long totalSize = 0;
    if(!allocMap || 0 == allocMap->size())
    {
        return;
    }

    for(iter = allocMap->begin(); iter != allocMap->end(); iter++)
    {
        printf("%-50s: LINE %lu, ADDRESS %lu %lu unfreed\n", iter->second->file, iter->second->line
                , iter->second->address, iter->second->size);
        totalSize += iter->second->size;
        info = iter->second;
        delete info;
    }
    printf("----------------------------------------------------------- \n");
    printf("Total Unfreed: %lu bytes \n", totalSize);
    delete allocMap;
};


#define new DEBUG_NEW

int main()
{
    char* pszCeshi = new char[5];
    DumpUnfreed();
    return 0;
}
