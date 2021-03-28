//
// Created by mext on 2021/3/23.
//
#include <zconf.h>

#include "Draw.h"
#include "coordinate_transform.h"

Draw::Draw(Data *data_) {
    data = data_;
    coor_scale = 100000;
    pop_every_time = 10000;
    // enu_ori_lle._lon_ = 116.3105555f;
    // enu_ori_lle._lat_ = 39.5961111f;
    // enu_ori_lle._ela_ = 1278.53f;
    // GeographicLib::LocalCartesian geodetic2enu(CfgParam.lat, CfgParam.lon, CfgParam.h);
    // std::thread t1(&Draw::drawThread,this);

}

Draw::~Draw() {

}



// void
// Draw::drawThread()
// {
//     enu_ori_lle._lat_ = CfgParam.lat;
//     enu_ori_lle._lon_ = CfgParam.lon;
//     enu_ori_lle._ela_ = CfgParam.h;
//
//
//     curr_geodetic_coor._lon_ = 0.0f;
//     curr_geodetic_coor._lat_ = 0.0f;
//     curr_geodetic_coor._ela_ = 0.0f;
//     curr_color_info.setZero();
//
//     pangolin::CreateWindowAndBind("show point", 1024, 768);
//     glEnable(GL_DEPTH_TEST);
//     glEnable(GL_BLEND);
//     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//     pangolin::OpenGlRenderState s_cam(
//             pangolin::ProjectionMatrix(1024, 768, 1416.00680747438, 1419.99039898015, 946.539374967763, 540.480291703174, 0.2, 15000),
//             pangolin::ModelViewLookAt(150, 150, 150, 0, 0, 0, pangolin::AxisY)
//     );
//
//     pangolin::Handler3D handler(s_cam);
//     pangolin::View& d_cam = pangolin::CreateDisplay()
//             .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
//             .SetHandler(&handler);
//
//     while (!pangolin::ShouldQuit())
//     {
//
//         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         d_cam.Activate(s_cam);  // 放在while循环里面就能旋转了
//
//         if (!data->geodetic_info.empty() && !data->color_info.empty())
//         {
//
//             if (data->geodetic_info.size() > pop_every_time)
//             {
//                 pop_count = pop_every_time;
//                 data->m_data.lock();
//                 while (pop_count)
//                 {
//                     curr_geodetic_coor = data->geodetic_info.front();
//                     curr_color_info = data->color_info.front();
//                     data->geodetic_info.pop();
//                     data->color_info.pop();
//
//                     geodetic2ecef(curr_geodetic_coor, point_xyz);
//                     ecef2enu(point_xyz, enu_ori_lle, point_enu);
//
//                     // std::cout << "lat lon h: " << curr_geodetic_coor._lat_ << "  " << curr_geodetic_coor._lon_ << "  "
//                     //           << curr_geodetic_coor._ela_ << std::endl;
//
//                     // std::cout << "point_enu: " << point_enu._east_ << "  " << point_enu._north_ << "  " << point_enu._up_ << std::endl;
//
//                     point_info.emplace_back(point_enu._east_);
//                     point_info.emplace_back(point_enu._north_);
//                     point_info.emplace_back(point_enu._up_);
//                     point_info.emplace_back((float)(curr_color_info(0) / 255.0f));
//                     point_info.emplace_back((float)(curr_color_info(1) / 255.0f));
//                     point_info.emplace_back((float)(curr_color_info(2) / 255.0f));
//
//                     points_info.emplace_back(point_info);
//                     point_info.clear();
//                     pop_count --;
//                 }
//                 data->m_data.unlock();
//             }
//         }
//         // 画一个坐标轴
//         glLineWidth(10);
//         glBegin(GL_LINES);
//         glColor3f(0.9, 0, 0);
//         glVertex3f(0, 0, 0);
//         glVertex3f(1000, 0, 0);
//         glColor3f(0, 0.9, 0);
//         glVertex3f(0, 0, 0);
//         glVertex3f(0, 1000, 0);
//         glColor3f(0, 0, 0.9);
//         glVertex3f(0, 0, 0);
//         glVertex3f(0, 0, 1000);
//         glEnd();
//
//         glPointSize(5);
//         glBegin(GL_POINTS);
//         for (auto & i : points_info)
//         {
//             glColor3f(i[3], i[4], i[5]);
//             glVertex3f(i[0], i[1], i[2]);
//         }
//         glEnd();
//
//         pangolin::FinishFrame();
//         usleep(10);
//     }
//     pangolin::DestroyWindow("show point");
// }




void Draw::drawThread(GeographicLib::LocalCartesian *geo2enu)
{
    geo2enu->Reset(CfgParam.lat, CfgParam.lon, CfgParam.h);

    curr_geodetic_coor._lon_ = 0.0f;
    curr_geodetic_coor._lat_ = 0.0f;
    curr_geodetic_coor._ela_ = 0.0f;
    curr_color_info.setZero();

    pangolin::CreateWindowAndBind("show point", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 708.677487640093, 710.565527692411, 470.501646846344, 270.727968883543, 0.2, 15000),
            pangolin::ModelViewLookAt(150, 150, 150, 0, 0, 0, pangolin::AxisY)
    );

    pangolin::Handler3D handler(s_cam);
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f / 768.0f)
            .SetHandler(&handler);

    while (!pangolin::ShouldQuit())
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);  // 放在while循环里面就能旋转了

        if (!data->geodetic_info.empty() && !data->color_info.empty())
        {

            if (data->geodetic_info.size() > pop_every_time)
            {
                pop_count = pop_every_time;
                data->m_data.lock();
                while (pop_count)
                {
                    curr_geodetic_coor = data->geodetic_info.front();
                    curr_color_info = data->color_info.front();
                    data->geodetic_info.pop();
                    data->color_info.pop();

                    double x, y, z;

                    geo2enu->Forward((double)curr_geodetic_coor._lat_, (double)curr_geodetic_coor._lon_, (double)curr_geodetic_coor._ela_,
                                         x, y, z);

                    // std::cout << "-lat lon h: " << curr_geodetic_coor._lat_ << "  " << curr_geodetic_coor._lon_ << "  "
                    //           << curr_geodetic_coor._ela_ << std::endl;
                    // std::cout << "x,y,z: " << x << "  " << y << "  " << z << std::endl;


                    point_info.emplace_back((float)x);
                    point_info.emplace_back((float)y);
                    point_info.emplace_back((float)z);
                    point_info.emplace_back((float)(curr_color_info(0) / 255.0f));
                    point_info.emplace_back((float)(curr_color_info(1) / 255.0f));
                    point_info.emplace_back((float)(curr_color_info(2) / 255.0f));

                    points_info.emplace_back(point_info);
                    point_info.clear();
                    pop_count --;
                }
                data->m_data.unlock();
            }
        }
        // 画一个坐标轴
        glLineWidth(10);
        glBegin(GL_LINES);
        glColor3f(0.9, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1000, 0, 0);
        glColor3f(0, 0.9, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 1000, 0);
        glColor3f(0, 0, 0.9);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 1000);
        glEnd();

        glPointSize(5);
        glBegin(GL_POINTS);
        for (auto & i : points_info)
        {
            glColor3f(i[3], i[4], i[5]);
            glVertex3f(i[0], i[1], i[2]);
        }
        glEnd();

        pangolin::FinishFrame();
        usleep(10);
    }
    pangolin::DestroyWindow("show point");
}
