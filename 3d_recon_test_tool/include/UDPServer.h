//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_UDPSERVER_H
#define INC_3D_RECON_TEST_TOOL_UDPSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <iostream>
#include <unistd.h>

using namespace std;
class UDPServer
{
private:
    int server_fd;
    struct sockaddr_in serverSockAddr;
    int nReceiveBuf;
public:
    UDPServer(); //函数声明,与UDPServer.cpp对应
    void listen(int port);
    int receive(char *buf,int len);
    ~UDPServer();
};

#endif //INC_3D_RECON_TEST_TOOL_UDPSERVER_H
