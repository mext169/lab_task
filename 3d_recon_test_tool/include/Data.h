//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_DATA_H
#define INC_3D_RECON_TEST_TOOL_DATA_H

#include <Eigen/Dense>
#include <queue>
#include <thread>
#include <mutex>
#include <iostream>

#include "tools.h"
#include "UdpDataProtocol.h"
#include "coordinate_transform.h"

class Data
{
public:
    Data();
    ~Data();

    void get_geodetic_and_rgb(geodetic & lle, Eigen::Vector3i & vcolor);

    void showSize();

    std::queue<geodetic> geodetic_info;
    std::queue<Eigen::Vector3i> color_info;

    std::mutex m_data;

    int point_num;

    geodetic curr_geo_coor;
    Eigen::Vector3i curr_color;

};

#endif //INC_3D_RECON_TEST_TOOL_DATA_H
