//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_DRAW_H
#define INC_3D_RECON_TEST_TOOL_DRAW_H

#include <pangolin/pangolin.h>
#include <pangolin/platform.h>
#include <pangolin/gl/glinclude.h>
#include <pangolin/handler/handler_enums.h>
#include <pangolin/utils/params.h>
#include <pangolin/display/window.h>

#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/LocalCartesian.hpp>

#include <iostream>
#include <fstream>

#include "Data.h"
#include "UdpDataProtocol.h"
#include "parameters.h"
#include "coordinate_transform.h"


class Draw
{
public:

    Draw(Data* data_);
    ~Draw();

    // void drawThread();
    void drawThread(GeographicLib::LocalCartesian *geo2enu);

    Data* data;



    float coor_scale;
    int pop_every_time;
    int pop_count;

    geodetic curr_geodetic_coor;
    Eigen::Vector3i curr_color_info;

    geodetic enu_ori_lle;

    std::vector<float>  point_info;
    ecef point_xyz;
    enu point_enu;


    GeographicLib::LocalCartesian geodetic2enu;

    // 前三个是经纬度，后三个颜色信息
    std::vector< std::vector<float> > points_info;

};

#endif //INC_3D_RECON_TEST_TOOL_DRAW_H
