//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_TOOLS_H
#define INC_3D_RECON_TEST_TOOL_TOOLS_H

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>

#pragma pack(1)

const float cam_fx = 708.677487640093;
const float cam_fy = 710.565527692411;
const float cam_cx = 470.501646846344;
const float cam_cy = 270.727968883543;

const float scale_factor = 0.091554135084;                // 6000/65535
const float scale_factor_inv = 10.922499656677;           // 65535/6000

/*only for debug*/
typedef struct depth_point_Info_
{
    int dep;
    double tx;
    double ty;
    double tz;
    double qx;
    double qy;
    double qz;
    double qw;
}DPIO;

Eigen::Matrix<float, 4, 4> formMatrixT(Eigen::Matrix<float, 8, 1> &poseMatrix);


Eigen::Vector3f pixel2cam(int &u, int &v);

void get_tum_like_data( std::string &pose_txt,
                        std::vector<std::string> &imgNames,
                        std::vector<Eigen::Matrix<float, 8, 1>> &poseMatrix);

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);

#endif //INC_3D_RECON_TEST_TOOL_TOOLS_H
