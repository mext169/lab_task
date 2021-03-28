//
// Created by lab on 2021/3/27.
//

#ifndef INC_3D_RECON_TEST_TOOL_UDPCLIENT_H
#define INC_3D_RECON_TEST_TOOL_UDPCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;
class UDPClient
{
private:
    int client_fd;
    struct sockaddr_in  clientSockAddr;
    int nSendBuf;
public:

    UDPClient();//函数声明,与UDPClient.cpp对应
    void setSockAddr(char *destAddr,int destPort);
    void sendData(char *buf,int len);
    ~UDPClient();
};

#endif //INC_3D_RECON_TEST_TOOL_UDPCLIENT_H
