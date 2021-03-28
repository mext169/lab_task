//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_PARAMETERS_H
#define INC_3D_RECON_TEST_TOOL_PARAMETERS_H

struct Config_Param
{
    int txtOutPut;
    int pangolinOutPut;
    std::string serverIP;
    int portID;
    int buffSize;

    // 原点经纬度
    double lat;
    double lon;
    double h;
};

extern Config_Param CfgParam;


void
readParameters(std::string config_file);




#endif //INC_3D_RECON_TEST_TOOL_PARAMETERS_H
