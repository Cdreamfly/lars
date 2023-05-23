#include "../include/buf_pool.h"
#include <stdio.h>
#include <stdlib.h>
BufferPool &BufferPool::Instance()
{
    static BufferPool pool;
    return pool;
}

void BufferPool::Create(const int size, const int count)
{
    Buffer *prev = _pool[size];
    _pool[size] = new Buffer(size);
    if (_pool[size] == nullptr)
    {
        fprintf(stderr, "new io_buf %d error", size);
        exit(1);
    }
    for (int i = 0; i < count; ++i)
    {
        prev->next = new Buffer(size);
        if (prev->next == nullptr)
        {
            fprintf(stderr, "new io_buf %d error", size);
            exit(1);
        }
        prev = prev->next;
    }
}

BufferPool::BufferPool() : _total_mem(0)
{
    Create(m4k, 5000);
    _total_mem += 4 * 5000;
    Create(m16k, 1000);
    _total_mem += 16 * 1000;
    Create(m64K, 500);
    _total_mem += 64 * 500;
    Create(m256K, 200);
    _total_mem += 256 * 200;
    Create(m1M, 50);
    _total_mem += 1024 * 50;
    Create(m4M, 20);
    _total_mem += 4096 * 20;
    Create(m8M, 10);
    _total_mem += 8192 * 10;
}

Buffer *BufferPool::AllocBuffer()
{
}

Buffer *BufferPool::AllocBuffer(const int size)
{
}

void BufferPool::Revert(Buffer *Buffer)
{
}