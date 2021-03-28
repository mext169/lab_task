//
// Created by lab on 2021/3/28.
//

//
// Created by lab on 2021/3/27.
//
#include <iostream>
#include <string.h>
#include "UdpDataProtocol.h"
#include "UDPClient.h"
#include "parameters.h"

int main()
{
    std::string cfg_path = "../config/config.yaml";
    readParameters(cfg_path);

    IIO imuInfo;
    imuInfo.ID = '5';
    imuInfo.timeStamp = 0;
    imuInfo._lon_ = 116.3111;
    imuInfo._lat_ = 39.95583;
    imuInfo._h_ = 4003.3665;
    imuInfo._azimuth_ = 10.1;
    imuInfo._pitch_ = 11.2;
    imuInfo._roll_ = 12.3;
    imuInfo._hori_field_ = 60.0;

    char buf[CfgParam.buffSize];

    UDPClient client;
    client.setSockAddr((char *)&CfgParam.serverIP, CfgParam.portID);

    while (true)
    {
        memcpy(buf, &imuInfo, sizeof(imuInfo));
        client.sendData(buf, sizeof(imuInfo));
        std::cout << "sending.." << std::endl;
        imuInfo.timeStamp += 1;
        if (imuInfo.timeStamp == 255)
            imuInfo.timeStamp = 0;

    }




}