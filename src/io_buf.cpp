#include "../include/io_buf.h"
#include <cassert>
#include <cstring>

Buffer::Buffer(const int size) : capacity(size), length(0), head(0), buffer(nullptr)
{
    data = new char[size];
    assert(data);
}
Buffer::~Buffer()
{
    this->Clear();
}
void Buffer::Clear()
{
    length = head = 0;
}
void Buffer::Pop(const int len)
{
    length -= len;
    head += len;
}
void Buffer::Copy(const Buffer *buffer)
{
    memcpy(data, buffer->data + buffer->head, buffer->length);
    head = 0;
    length = buffer->length;
}
void Buffer::AdJust()
{
    if (head != 0 && length != 0)
    {
        memmove(data, data + head, length);
        head = 0;
    }
}