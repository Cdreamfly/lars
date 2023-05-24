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
    _total_mem += (size / 1024) * 5000;
}

BufferPool::BufferPool() : _total_mem(0)
{
    Create(m4K, 5000);
    Create(m16K, 1000);
    Create(m64K, 500);
    Create(m256K, 200);
    Create(m1M, 50);
    Create(m4M, 20);
    Create(m8M, 10);
}

Buffer *BufferPool::AllocBuffer()
{
}

Buffer *BufferPool::AllocBuffer(const int N)
{
    int index;
    if (N <= m4K)
    {
        index = m4K;
    }
    else if (N <= m16K)
    {
        index = m16K;
    }
    else if (N <= m64K)
    {
        index = m64K;
    }
    else if (N <= m256K)
    {
        index = m256K;
    }
    else if (N <= m1M)
    {
        index = m1M;
    }
    else if (N <= m4M)
    {
        index = m4M;
    }
    else if (N <= m8M)
    {
        index = m8M;
    }
    else
    {
        return nullptr;
    }
}

void BufferPool::Revert(Buffer *Buffer)
{
}