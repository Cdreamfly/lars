#pragma once

class Buffer
{
public:
    explicit Buffer(const int size);
    ~Buffer();
    void Clear();
    // 处理长度为len的数据，移动head和修正length
    void Pop(const int len);
    // 将其他io_buf对象数据考本到自己中
    void Copy(const Buffer *buffer);
    // 将已经处理过的数据，清空,将未处理的数据提前至数据首地址
    void AdJust();

public:
    // 如果存在多个buffer，是采用链表的形式链接起来
    Buffer *next;

private:
    // 当前buffer的缓存容量大小
    int capacity;
    // 当前buffer有效数据长度
    int length;
    // 未处理数据的头部位置索引
    int head;
    // 当前io_buf所保存的数据地址
    char *data;
};