//
// Created by mext on 2021/3/23.
//

#include "UDPServer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <unistd.h>

using namespace std;



//构造函数,与类名相同，初始化类时自动执行
UDPServer::UDPServer()
{
    server_fd = socket(AF_INET, SOCK_DGRAM, 0);//创建socket
    if (server_fd < 0)
    {
        cout << "socket error~" << endl;
    }
//    setsockopt(server_fd, SOL_SOCKET, SO_RCVBUF, (const char *)&nReceiveBuf, sizeof(nReceiveBuf));
}

//绑定端口
void UDPServer::listen(int port)
{
    serverSockAddr.sin_family = AF_INET;
    serverSockAddr.sin_port = htons(port);
    serverSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_fd, (struct sockaddr*)&serverSockAddr, sizeof(serverSockAddr)) == 0)
    {
        cout << " Server Socket initialized Successful" << endl;
    }
    else
    {
        cout << "Server Socket initialized Failed" << endl;
    }
}

//接收函数
int UDPServer::receive(char *buf,int len)
{
    int count;
    int serverSockAddrSize = sizeof(serverSockAddr);
    count = recvfrom(server_fd, buf, len, 0, (struct sockaddr *)&serverSockAddr, (socklen_t *)&serverSockAddrSize);

    // std::cout << count << std::endl;
    return count;
}

//析构函数，在对象销毁时自动执行，用于清理工作
UDPServer::~UDPServer()
{
    close(server_fd);
    cout << "Server Socket released" << endl;
}
