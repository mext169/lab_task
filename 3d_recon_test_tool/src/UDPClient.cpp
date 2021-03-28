//
// Created by lab on 2021/3/27.
//

#include "UDPClient.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <unistd.h>


#include <iostream>

using namespace std;

//构造函数与类名相同，初始化类时自动执行
UDPClient::UDPClient()
{
    client_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_fd < 0)
    {
        cout << "socket error~" << endl;
    }
    nSendBuf = 5 * 1024 *1024;
//    setsockopt(client_fd, SOL_SOCKET, SO_SNDBUF, (const char *)&nSendBuf, sizeof(nSendBuf));
}

//析构函数，在对象销毁时自动执行，用于清理工作
UDPClient::~UDPClient()
{
    close(client_fd);
    cout << "Client Socket released" << endl;
}

//设置IP和Port
void UDPClient::setSockAddr(char *destAddr,int destPort)//设置IP和Port
{
    clientSockAddr.sin_family = AF_INET;
    clientSockAddr.sin_port = htons(destPort);
    clientSockAddr.sin_addr.s_addr = inet_addr(destAddr);
}

//发送函数
void UDPClient::sendData(char *buf,int len)
{
    sendto(client_fd, buf, len, 0, (struct sockaddr*)&clientSockAddr, sizeof(clientSockAddr));
}