#ifndef __MEMORYMANGER_H__
#define __MEMORYMANGER_H__
#include "common/types.h"
struct MemoryChunk
{
    MemoryChunk *next;
    MemoryChunk *pre;
    bool allocated;
    size_t size;
};

class MemoryManger
{
public:
    void *malloc(size_t size);
    void free(void *ptr);
    static MemoryManger *activeMemoryManger;

    MemoryManger(size_t start, size_t size);
    ~MemoryManger();

private:
    // static MemoryManger *MemoryMangerSingle(size_t start, size_t size);
    MemoryChunk *first;
};

void *operator new(size_t size);
void *operator new[](size_t size);

void *operator new(size_t size, void *ptr);
void *operator new[](size_t size, void *ptr);

void operator delete(void *ptr);
void operator delete[](void *ptr);
#endif // !__MEMORYMANGER_H__