//
// Created by lab on 2021/3/26.
//

#include "coordinate_transform.h"
#include <cmath>


/**
 *
 * @param lle 输入经纬度信息
 * @param xyz 输出ecef坐标信息
 */
void geodetic2ecef(const geodetic &lle, ecef &xyz)
{
    geodetic lle_radian;

    lle_radian._lon_ = lle._lon_ * M_PI / 180;
    lle_radian._lat_ = lle._lat_ * M_PI / 180;
    lle_radian._ela_ = lle._ela_;

    float f = e * e / (1 + sqrtf(1 - e * e));
    float e2 = f * (2 - f);
    float N = a / sqrtf(1 - e2 * sinf(lle_radian._lat_) * sinf(lle_radian._lat_));
    float rho = (N + lle_radian._ela_) * cosf(lle_radian._lat_);
    xyz._z_ = (N * (1 - e2) + lle_radian._ela_) * sinf(lle_radian._lat_);
    xyz._x_ = rho * cosf(lle_radian._lon_);
    xyz._y_ = rho * sinf(lle_radian._lon_);

}

/**
 *
 * @param xyz 输入ecef信息
 * @param lle 输出geodetic信息
 */
void ecef2geodetic(const ecef &xyz, geodetic &lle)
{

    float f = e * e / (1 + sqrtf(1 - e * e));
    // 这里算出了经度
    lle._lon_ = atan2f(xyz._y_, xyz._x_);

    float rho = sqrtf(xyz._x_ * xyz._x_ + xyz._y_ * xyz._y_);
    // Semiminor axis
    float b = (1 - f) * a;
    // Square of (first) eccentricity
    float e2 = f * (2 - f);
    // Square of second eccentricity
    float ep2 = e2 / (1 - e2);

    float beta = atan2f(xyz._z_, (1 - f) * rho);

    float phi = atan2f(xyz._z_ + b * ep2 * pow(sinf(beta), 3), rho - a * e2 * pow(cosf(beta), 3));

//    float betaNew = atan2((1 - f) * sin(phi), cos(phi));
//    int count = 0;
//    while (beta != betaNew && count < 5)
//    {
//        beta = betaNew;
//        phi = atan2(z + b * pow(sin(beta), 3), rho - a * e2 * pow(cos(beta), 3));
//        betaNew = atan2((1 - f) * sin(phi), cos(phi));
//        count++;
//    }

    float sinphi = sinf(phi);
    float N = a / sqrtf(1 - e2 * sinphi * sinphi);
    float h = rho * cosf(phi) + (xyz._z_ + e2 * N * sinphi) * sinphi - N;

    float ela = h;
    float lat = phi;

    lle._lon_ = lle._lon_ * 180 / M_PI;
    lle._lat_ = lat * 180 / M_PI;
    lle._ela_ = ela;
}

/**
 *
 * @param xyz 输入，要进行转化的ecef坐标
 * @param enu_ 输出，enu坐标
 * @param lle_origin 输入，enu坐标原点在ecef坐标系下的坐标
 */
void ecef2enu(const ecef &xyz, geodetic &lle_origin, enu &enu_)
{

    // enu坐标原点的经纬度转换为ecef坐标
    ecef enu_ori_ecef;
    geodetic2ecef(lle_origin, enu_ori_ecef);
//    std::cout << "**enu ori coordinate in ecef**" << std::endl;
//    std::cout << "** enu_ori_ecef.x:" << enu_ori_ecef._x_ << " enu_ori_ecef.y:" << enu_ori_ecef._y_ << " enu_ori_ecef.z:" << enu_ori_ecef._z_ << std::endl;

    float lat_ = lle_origin._lat_ * M_PI / 180;
    float lon_ = lle_origin._lon_ * M_PI / 180;
    float cosLat = cosf(lat_);
    float sinLat = sinf(lat_);
    float cosLon = cosf(lon_);
    float sinLon = sinf(lon_);

    enu_._east_ = -sinLon * (xyz._x_ - enu_ori_ecef._x_) + cosLon * (xyz._y_ - enu_ori_ecef._y_);
    enu_._north_ = -cosLon * sinLat * (xyz._x_ - enu_ori_ecef._x_) - sinLon * sinLat * (xyz._y_ - enu_ori_ecef._y_) + cosLat * (xyz._z_ - enu_ori_ecef._z_);
    enu_._up_ = cosLat * cosLon * (xyz._x_ - enu_ori_ecef._x_) + sinLon * cosLat * (xyz._y_ - enu_ori_ecef._y_) + sinLat * (xyz._z_ - enu_ori_ecef._z_);

}


/**
 *
 * @param enu_ 输入enu坐标信息
 * @param lle_origin 选取的enu坐标原点在ecef坐标系下的坐标
 * @param xyz
 */
void enu2ecef(enu &enu_, geodetic &lle_origin, ecef &xyz)
{

    // enu坐标原点的经纬度转换为ecef坐标
    ecef enu_ori_ecef;
    geodetic2ecef(lle_origin, enu_ori_ecef);
//    std::cout << "**enu ori coordinate in ecef**" << std::endl;
//    std::cout << "** enu_ori_ecef.x:" << enu_ori_ecef._x_ << " enu_ori_ecef.y:" << enu_ori_ecef._y_ << " enu_ori_ecef.z:" << enu_ori_ecef._z_ << std::endl;

    float lat_ = lle_origin._lat_ * M_PI / 180;
    float lon_ = lle_origin._lon_ * M_PI / 180;
    float cosLat = cosf(lat_);
    float sinLat = sinf(lat_);
    float cosLon = cosf(lon_);
    float sinLon = sinf(lon_);

    float dx = -sinLon * enu_._east_ - cosLon * sinLat * enu_._north_ + cosLon * cosLat * enu_._up_;
    float dy = cosLon * enu_._east_ - sinLon * sinLat * enu_._north_ + sinLon * cosLat * enu_._up_;
    float dz = cosLat * enu_._north_ + sinLat * enu_._up_;

    xyz._x_ = enu_ori_ecef._x_ + dx;
    xyz._y_ = enu_ori_ecef._y_ + dy;
    xyz._z_ = enu_ori_ecef._z_ + dz;

}


