//
// Created by mext on 2021/3/23.
//

#ifndef INC_3D_RECON_TEST_TOOL_DATASTRUCTURE_H
#define INC_3D_RECON_TEST_TOOL_DATASTRUCTURE_H

#pragma pack(1)

// (2byte+200)*65535/6200再取整
#define th_high_4byte 65535
#define th_high_2byte 6200

// 17个byte
typedef struct pointCloudInfo
{
    char ID;                // 报文ID, 2
    float longitude;        // 点位置，经度，-180~180
    float latitude;         // 点位置，纬度，-90~90
    short elevation;        // 点位置，高程，-200~6000
    ushort R;                // R，0-255
    ushort G;                // G，0-255
    ushort B;                // B，0-255
}PIO;

// 22个byte
typedef struct imuInfo
{
    char ID;                // 报文ID, 5
    char timeStamp;         // 时间戳,0-255
    float _lon_;            // 视点位置，经度，-180～180
    float _lat_;            // 视点位置，纬度，-90~90
    float _h_;              // 视点位置，高程，-200~6000
    ushort _azimuth_;       // 传感器姿态角，方位，相对于真北的偏角，顺时针为正，0-360
    ushort _pitch_;         // 传感器姿态角，俯仰，相对于水平面，前部抬高为正，,-90~90
    ushort _roll_;          // 传感器姿态角，横滚，相对水平面，左侧抬高为正， -180~180
    ushort _hori_field_;    // 水平视场角，0-180
}IIO;

// 19个byte
typedef struct imuAndRangeInfo
{
    char ID;                // 报文ID，6
    ushort _range_;         // 距离，0-65535
    float _lon_;            // 视点位置，经度，-180～180
    float _lat_;            // 视点位置，纬度，-90~90
    float _h_;              // 视点位置，高程，-200~6000
    ushort _azimuth_;       // 瞄线姿态角，方位，相对于真北的偏角，顺时针为正，0-360
    ushort _pitch_;         // 瞄线姿态角，俯仰，相对于水平面，前部抬高为正，,-90~90
}IRIO;







#endif //INC_3D_RECON_TEST_TOOL_DATASTRUCTURE_H
