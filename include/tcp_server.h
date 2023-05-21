#pragma once
#include <string>
#include <netinet/in.h>

class TcpServer
{
public:
    explicit TcpServer(const std::string &ip = "127.0.0.1", const uint16_t port = 8080);
    virtual ~TcpServer();
    void do_accept();

private:
    int _sockfd;
    sockaddr_in _connaddr;
    socklen_t _addrlen;
};