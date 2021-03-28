//
// Created by lab on 2021/3/28.
//

//
// Created by mext on 2021/3/23.
//
#include <iostream>
#include <queue>
#include <thread>
#include <GeographicLib/LocalCartesian.hpp>

#include "UDPServer.h"
#include "UdpDataProtocol.h"
#include "parameters.h"
#include "Draw.h"
#include "Data.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

using namespace std;

#pragma pack(1)

// Draw* pDraw;
std::shared_ptr<Draw> pDraw;
Data* pData;
GeographicLib::LocalCartesian *geodetic2enu;
std::queue<IIO> *pImuInfo;
std::queue<IRIO> *pImuAndRangeInfo;

int main()
{

    std::string cfg_path = "../config/config.yaml";
    readParameters(cfg_path);


    geodetic2enu = new GeographicLib::LocalCartesian(0.0, 0.0, 0.0);
    pData = new Data;
    pDraw.reset(new Draw(pData));
    std::thread thredDraw(&Draw::drawThread, pDraw, geodetic2enu);
    thredDraw.detach();
    // std::thread thredDraw(&Draw::drawThread, pDraw);




    geodetic lle_info;
    Eigen::Vector3i rgb_info;

    while (!pData->geodetic_info.empty()) {pData->geodetic_info.pop();}
    while (!pData->color_info.empty()) {pData->color_info.pop();}

    int BUFF_SIZE = CfgParam.buffSize;
    int total_num = 0;
    char buf[BUFF_SIZE];
    PIO depth_info;
    IIO imu_info;
    IRIO imu_range_info;

    UDPServer server;
    server.listen(CfgParam.portID);

    int numReceiveOnce;
    char firstByte;
    while (true)
    {
        memset(buf, 0, BUFF_SIZE);
        numReceiveOnce = server.receive(buf, BUFF_SIZE);

        if (numReceiveOnce)
        {
            firstByte = static_cast<char>(*buf);
            if (firstByte == '2')
            {
                for (int i = 0; i < 32; ++i)
                {
                    memcpy(&depth_info, buf + i * sizeof(depth_info), sizeof(depth_info));
                    char id = depth_info.ID;
                    lle_info._lon_ = depth_info.longitude;
                    lle_info._lat_ = depth_info.latitude;
                    lle_info._ela_ = (float)(depth_info.elevation * 6200 / 65535 - 200);

                    // std::cout << id << "  " << depth_info.longitude << "  " << depth_info.latitude << "  "
                    //           << depth_info.elevation << "  " << depth_info.R << "  " << depth_info.G << "  "
                    //           << depth_info.B << std::endl;

                    rgb_info << (int)depth_info.R, (int)depth_info.G, (int)depth_info.B;
                    pData->get_geodetic_and_rgb(lle_info, rgb_info);
                    total_num++;
                }
                // std::cout << "total num: " << total_num << endl;
            }
            else if (firstByte == '5')
            {
                memcpy(&imu_info, buf, sizeof(imu_info));
                pImuInfo->push(imu_info);
                std::cout << imu_info.ID << "  " << imu_info.timeStamp << "  " << imu_info._lon_ << "  " << imu_info._lat_ <<
                          "  " << imu_info._h_ << "  " << imu_info._azimuth_ << "  " << imu_info._pitch_ << "  " << imu_info._roll_ <<
                          "  " << imu_info._hori_field_ << std::endl;
            }
            else if (firstByte =='6')
            {
                memcpy(&imu_range_info, buf, sizeof(imu_range_info));
                pImuAndRangeInfo->push(imu_range_info);
                std::cout << imu_range_info.ID << "  " << imu_range_info._lon_ << "  " << imu_range_info._lat_ << "  " <<
                          imu_range_info._h_ << "  " << imu_range_info._range_ << "  " << imu_range_info._azimuth_ << "  " <<
                          imu_range_info._pitch_ << std::endl;
            }
            else
            {
                std::cout << "Undefined data." << std::endl;
            }
        }
    }
    return 0;
}
#pragma clang diagnostic pop