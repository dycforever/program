#include <stdio.h>
#include <stdlib.h>
#include <map>

#include <string.h>

using namespace std;

typedef struct {
    void* address;
    unsigned long size;
    char file[1024];
    unsigned long line;
} ALLOC_INFO;

typedef map<void*, ALLOC_INFO*> AllocMap;

AllocMap* allocMap;

#define _DEBUG

#ifdef _DEBUG

#define NEW new(__FILE__, __LINE__)

void AddTrack(void* addr, unsigned long asize, const char *fname, unsigned long lnum) 
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

bool RemoveTrack(void* addr)
{
    if(!allocMap || 0 == allocMap->size())
    {
        return true;
    }
    AllocMap::iterator iter = allocMap->find(addr);
    if (iter != allocMap->end())
    {
        ALLOC_INFO* info = iter->second;
        delete info;
        allocMap->erase(iter);
        return true;
    }
    return false;
}

inline void * operator new(size_t size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    AddTrack(ptr, size, file, line);
    return(ptr);
}

inline void operator delete(void *p)
{
    if (RemoveTrack(p)) {
        printf("call free %p\n", p);
        free(p);
    }
}
inline void * operator new[](size_t size, const char *file, int line)
{
    void *ptr = (void *)malloc(size);
    AddTrack(ptr, size, file, line);
    return(ptr);
}
inline void operator delete[](void *p)
{
    if (RemoveTrack(p)) {
        printf("call delete[]\n");
        free(p);
    }
}
#else  // _DEBUG
#define NEW new(std::nothrow)
#endif // _DEBUG

void dumpUnfreed()
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
        printf("%-50s: LINE %lu, ADDRESS 0x%lx size %lu unfreed\n", iter->second->file, iter->second->line
                , iter->second->address, iter->second->size);
        totalSize += iter->second->size;
        info = iter->second;
        delete info;
    }
//    printf(" ============== calling map ==========\n");
    delete allocMap;
    printf("----------------------------------------------------------- \n");
    printf("Total Unfreed: %lu bytes \n", totalSize);
};



int main()
{
    char* testp = NEW char[5];
    char* testp2 = NEW char[5];
    char* testp3 = NEW char[5];
    delete[] testp;
    delete[] testp2;
    delete[] testp3;
    dumpUnfreed();
    printf("map:%p, testp:%p\n", allocMap, testp);
    return 0;
}
