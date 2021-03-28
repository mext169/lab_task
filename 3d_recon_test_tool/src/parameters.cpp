//
// Created by mext on 2021/3/23.
//
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "../include/parameters.h"

Config_Param CfgParam;

void readParameters(std::string config_file)
{
    cv::FileStorage fsSettings(config_file, cv::FileStorage::READ);
    std::cout << "loading parameters......" << std::endl;

    CfgParam.txtOutPut = fsSettings["txtOutPut"];
    CfgParam.pangolinOutPut = fsSettings["pangolinOutPut"];
    CfgParam.portID = fsSettings["portID"];
    fsSettings["serverIP"] >> CfgParam.serverIP;
    CfgParam.buffSize = fsSettings["buffSize"];

    CfgParam.lat = fsSettings["lat"];
    CfgParam.lon = fsSettings["lon"];
    CfgParam.h = fsSettings["h"];


}