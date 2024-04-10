#include "memorymanger.h"
MemoryManger *MemoryManger::activeMemoryManger = nullptr;
MemoryManger::MemoryManger(size_t start, size_t size)
{
    activeMemoryManger = this;
    if (size < sizeof(MemoryChunk)) // 分配内存比管理的都小
    {
        first = nullptr;
    }
    else
    {
        first = (MemoryChunk *)start;
        first->allocated = false;
        first->next = nullptr;
        first->pre = nullptr;
        first->size = size - sizeof(MemoryChunk);
    }
}
MemoryManger::~MemoryManger()
{
    if (activeMemoryManger == this)
        activeMemoryManger = nullptr;
}

void *MemoryManger::malloc(size_t size)
{
    MemoryChunk *result = nullptr;
    for (MemoryChunk *chunk = first; chunk != nullptr && result == nullptr; chunk->next)
    {
        if (!chunk->allocated && chunk->size > size)
        {
            result = chunk;
        }
    }
    if (result == nullptr)
        return nullptr;
    if (result->size > size + sizeof(MemoryChunk))
    {
        MemoryChunk *temp = (MemoryChunk *)((uint32_t)result + sizeof(MemoryChunk) + size);
        temp->size = result->size - size - sizeof(MemoryChunk);
        temp->allocated = false;
        temp->pre = result;
        temp->next = result->next;
        if (temp->next != nullptr)
        {
            temp->next->pre = temp;
        }
        result->next = temp;
        result->size = size;
    }
    result->allocated = true;
    return (void *)((uint32_t)result + sizeof(MemoryChunk));
}
void MemoryManger::free(void *ptr)
{
    MemoryChunk *chunk = (MemoryChunk *)((uint32_t)ptr - sizeof(MemoryChunk));
    chunk->allocated = false;
    if (chunk->pre != nullptr && chunk->pre->allocated == false)
    {
        chunk->pre->size += chunk->size + sizeof(MemoryChunk);
        chunk->pre->next = chunk->next;
        if (chunk->next != nullptr)
        {
            chunk->next->pre = chunk->pre;
        }
    }
    chunk = chunk->pre;
    if (chunk->next != nullptr && chunk->next->allocated == false)
    {
        chunk->size += chunk->next->size + sizeof(MemoryChunk);
        chunk->next = chunk->next->next;
        if (chunk->next != nullptr)
        {
            chunk->next->pre = chunk;
        }
    }
}
void *operator new(size_t size)
{
    if (MemoryManger::activeMemoryManger == nullptr)
        return (void *)nullptr;
    return MemoryManger::activeMemoryManger->malloc(size);
}
void *operator new[](size_t size)
{
    if (MemoryManger::activeMemoryManger == nullptr)
        return (void *)nullptr;
    return MemoryManger::activeMemoryManger->malloc(size);
}
void *operator new(size_t size, void *ptr)
{
    return ptr;
}
void *operator new[](size_t size, void *ptr)
{
    return ptr;
}
void operator delete(void *ptr)
{
    if (MemoryManger::activeMemoryManger != 0)
    {
        MemoryManger::activeMemoryManger->free(ptr);
    }
}
void operator delete[](void *ptr)
{
    if (MemoryManger::activeMemoryManger != 0)
    {
        MemoryManger::activeMemoryManger->free(ptr);
    }
}