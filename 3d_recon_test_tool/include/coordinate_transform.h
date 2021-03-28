//
// Created by lab on 2021/3/26.
//

#ifndef INC_3D_RECON_TEST_TOOL_COORDINATE_TRANSFORM_H
#define INC_3D_RECON_TEST_TOOL_COORDINATE_TRANSFORM_H


const float a = 6378137;
const float e = 0.081819190842621;

typedef struct geodetic_coor
{
    float _lon_;
    float _lat_;
    float _ela_;
}geodetic;

typedef struct enu_coor
{
    float _east_;
    float _north_;
    float _up_;
}enu;

typedef struct ecef_coor
{
    float _x_;
    float _y_;
    float _z_;
}ecef;

void geodetic2ecef(const geodetic &lle, ecef &xyz);

void ecef2geodetic(const ecef &xyz, geodetic &lle);

void ecef2enu(const ecef &xyz, geodetic &lle_origin, enu &enu_);

void enu2ecef(enu &enu_, geodetic &lle_origin, ecef &xyz);





#endif //INC_3D_RECON_TEST_TOOL_COORDINATE_TRANSFORM_H
