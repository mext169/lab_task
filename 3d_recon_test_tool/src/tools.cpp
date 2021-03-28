//
// Created by mext on 2021/3/23.
//

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <fstream>

#include "tools.h"

Eigen::Matrix<float, 4, 4> formMatrixT(Eigen::Matrix<float, 8, 1> &poseMatrix)
{
    Eigen::Matrix<float, 4, 4> Tcr;
    Tcr.setZero();

    float tx, ty, tz;
    tx = poseMatrix(1);
    ty = poseMatrix(2);
    tz = poseMatrix(3);
    Eigen::Vector3f t;
    t << tx, ty, tz;

    float qx, qy, qz, qw;
    qx = poseMatrix(4);
    qy = poseMatrix(5);
    qz = poseMatrix(6);
    qw = poseMatrix(7);

    Eigen::Quaternionf q(qw, qx, qy, qz);
    Eigen::Matrix3f R = q.toRotationMatrix();


    Tcr.block(0, 0, 3, 3) = R.block(0, 0, 3, 3);
    Tcr.block(0, 3, 3, 1) = t.block(0, 0, 3, 1);
    Tcr(3, 3) = 1;

    return Tcr;
}


Eigen::Vector3f pixel2cam(int &u, int &v)
{
    Eigen::Vector3f point_coor;
    point_coor(0) = ((float)u - cam_cx) / cam_fx;
    point_coor(1) = ((float)v - cam_cy) / cam_fy;
    point_coor(2) = 1.0f;

    return point_coor;
}


// 图片少，位姿多
void get_tum_like_data( std::string &pose_txt,
                        std::vector<std::string> &imgNames,
                        std::vector<Eigen::Matrix<float, 8, 1>> &poseMatrix)
{
    std::string poseDataLine;
    Eigen::Matrix<float, 8, 1> poseMatrixLine;
    Eigen::Matrix<float, 8, 1> bestPoseMatrixLine;

    bool found = false;

    int numDepImg = imgNames.size();
    for (int i = 0; i < numDepImg; ++i)
    {
        std::ifstream pose_file;
        pose_file.open(pose_txt);
        float pose_last_dt = 1e9;
        float img_curr_time = 0;
        float pose_curr_time = 0;
        float pose_last_time = 0;
        float pose_curr_dt = 0;

        // 每一张深度图的时间
        img_curr_time = atof(imgNames[i].c_str());

        while (!found && !pose_file.eof())
        {
            // 获取poseFile的一行
            std::getline(pose_file, poseDataLine);

            std::istringstream poseData(poseDataLine);
            // 每一行的第一个字符表示位姿的时间
            std::string poseTime;
            poseData >> poseTime;

            // 第一行时间为0，肯定找不到对应的图片
            if (poseTime == "0")
                continue;

            pose_curr_time = atof(poseTime.c_str());

            poseMatrixLine(0) = pose_curr_time;

            poseData >> poseMatrixLine(1) >> poseMatrixLine(2) >> poseMatrixLine(3)
                     >> poseMatrixLine(4) >> poseMatrixLine(5) >> poseMatrixLine(6) >> poseMatrixLine(7);

            pose_curr_dt = abs(pose_curr_time - img_curr_time);

            if (pose_curr_dt < pose_last_dt)
            {
                pose_last_dt = pose_curr_dt;
                pose_last_time = pose_curr_time;
                bestPoseMatrixLine = poseMatrixLine;
            }
            else
            {
                found = true;
            }

        }
        found = false;
        poseMatrix.push_back(bestPoseMatrixLine);

    }

}


void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}