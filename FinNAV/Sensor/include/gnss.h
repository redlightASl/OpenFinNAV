#pragma once
#include "Defines.h"

struct GyroData
{
    uint32_t latitude;
    uint32_t longitude;
    uint32_t quality;
    uint32_t sat_num;
    uint32_t cogt; //真北对地航向
    uint32_t cogm; //磁北对地航向
    uint32_t sog; //对地速率 km/h
};
typedef struct GyroData GyroData_t;
