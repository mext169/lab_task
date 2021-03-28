// 测试geodetic和geocentric坐标之间的转换
#include <iostream>
#include <cstdio>
#include <GeographicLib/Geodesic.hpp>
#include <GeographicLib/Geocentric.hpp>
#include <GeographicLib/Constants.hpp>
#include <GeographicLib/LocalCartesian.hpp>

using namespace std;

int main(){
    GeographicLib::Geocentric geodetic(GeographicLib::Constants::WGS84_a(), GeographicLib::Constants::WGS84_f());

    double lat, lon, h;
    lat = 39.95583;
    lon = 116.3111;
    h = 4003.3665;
    double X, Y, Z;

    std::cout << "geodetic和geocentric坐标之间的转换测试：" << std::endl;
    printf("lat_in = %f, lon_in = %f, h_in = %f\n", lat, lon, h);
    geodetic.Forward(lat, lon, h, X, Y, Z);
    printf("X = %f, Y = %f, Z = %f\n", X, Y, Z);

    std::cout << "变换回来" << std::endl;
    double lat_out, lon_out, h_out;
    geodetic.Reverse(X, Y, Z, lat_out, lon_out, h_out);
    printf("lat_out = %f, lon_out = %f, h_out = %f\n\n", lat_out, lon_out, h_out);

    std::cout << "geodetic和local cartesian坐标之间的转换测试：" << std::endl;
    // 构造函数设置原点，默认使用WGS84模型
    GeographicLib::LocalCartesian local(lat, lon, h);
    // 将一个点geodetic坐标转换成相对origin的local cartesian坐标
    // Z轴垂直椭球面向上，x轴沿经度向东，y轴相切于椭球面向北
    double lat_local, lon_local, h_local;
    lat_local = 39.9500;
    lon_local = 116.3078;
    h_local = 4800.21;
    printf("lat_local_in = %f, lon_local_in = %f, h_local_in = %f\n", lat_local, lon_local, h_local);

    double x_local, y_local, z_local;
    local.Forward(lat_local, lon_local, h_local, x_local, y_local, z_local);
    printf("x_local = %f, y_local = %f, z_local = %f\n", x_local, y_local, z_local);



    std::cout << "变换回来" << std::endl;
    double lat_local_back, lon_local_back, h_local_back;
    local.Reverse(x_local, y_local, z_local, lat_local_back, lon_local_back, h_local_back);
    printf("lat_local_back = %f, lon_local_back = %f, h_local_back = %f\n", lat_local_back, lon_local_back, h_local_back);















}