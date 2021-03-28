//
// Created by mext on 2021/3/23.
//

#include "Data.h"
Data::Data()
{
    curr_geo_coor._lat_ = 0;
    curr_geo_coor._lon_ = 0;
    curr_geo_coor._ela_ = 0;
    curr_color.setZero();
    point_num = 32;
}

Data::~Data()
{

}

void Data::get_geodetic_and_rgb(geodetic & lle, Eigen::Vector3i & vcolor)
{
    m_data.lock();
    geodetic_info.push(lle);
    color_info.push(vcolor);
    m_data.unlock();

}

void Data::showSize()
{
    std::cout << "------------------------------------------size of geodetic_info" << geodetic_info.size() << std::endl;
    std::cout << "++++++++++++++++++++++++++++++++++++++++++size of color_info" << color_info.size() << std::endl;
}