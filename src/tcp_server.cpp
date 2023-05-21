#include "tcp_server.h"
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <signal.h>

TcpServer::TcpServer(const std::string &ip, const uint16_t port)
{
    memset(&_connaddr, 0, sizeof(_connaddr));
    _addrlen = sizeof(_connaddr);

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR)
    {
        fprintf(stderr, "signal ignore SIGHUP\n");
    }
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    {
        fprintf(stderr, "signal ignore SIGPIPE");
    }

    _sockfd = ::socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    if (_sockfd == -1)
    {
        fprintf(stderr, "tcp::server :socket()\n");
        exit(1);
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_aton(ip.c_str(), &server_addr.sin_addr);

    int op = 1;
    if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &op, sizeof(op)) < 0)
    {
        fprintf(stderr, "setsocketopt SO_REUSEADDR\n");
    }

    if (::bind(_sockfd, (const sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        fprintf(stderr, "tcp::server :bind()\n");
        exit(1);
    }

    if (::listen(_sockfd, SOMAXCONN) < 0)
    {
        fprintf(stderr, "tcp::server :listen()\n");
        exit(1);
    }
    std::cout << "server start ip " << ip << " port " << port << std::endl;
}

TcpServer::~TcpServer()
{
    ::close(_sockfd);
}

void TcpServer::do_accept()
{
    int connfd;
    while (true)
    {
        connfd = ::accept(_sockfd, (struct sockaddr *)&_connaddr, &_addrlen);
        if (connfd == -1)
        {

            if (errno == EINTR)
            {
                fprintf(stderr, "accept errno = EINTR\n");
                continue;
            }
            else if (errno == EAGAIN)
            {
                fprintf(stderr, "accept errno=EINTR\n");
                break;
            }
            else if (errno == EMFILE)
            {
                // accept errno=EINTR
                fprintf(stderr, "accept errno=EMFILE\n");
                break;
            }
            else
            {
                fprintf(stderr, "accept errno\n");
            }
        }
        else
        {
            int writed;
            const char *data = "hello world";
            do
            {
                writed = ::write(connfd, data, strlen(data));
            } while (writed == -1 && errno == EINTR);
            if (writed > 0)
            {
                std::cout << "write success" << std::endl;
            }
            if (writed == -1 && errno == EAGAIN)
            {
                writed = 0;
            }
        }
    }
}