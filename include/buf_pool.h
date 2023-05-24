#pragma once
#include <map>
#include <stdint.h>
#include "io_buf.h"

enum MEM_CAP
{
    m4K = 4096,
    m16K = 16384,
    m64K = 65536,
    m256K = 262144,
    m1M = 1048576,
    m4M = 4194304,
    m8M = 8388608
};

class BufferPool
{
public:
    BufferPool(const BufferPool &) = delete;
    const BufferPool &operator=(const BufferPool &) = delete;
    ~BufferPool() = default;

    static BufferPool &Instance();

    Buffer *AllocBuffer(const int size);
    Buffer *AllocBuffer();
    void Revert(Buffer *buffer);

    void Create(const int size, const int count);

private:
    BufferPool();

private:
    std::map<int, Buffer *> _pool;
    uint64_t _total_mem;
};