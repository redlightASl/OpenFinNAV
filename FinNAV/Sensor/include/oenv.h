#pragma once
#include "Defines.h"

struct OenvData
{
    uint16_t Temperature;
    uint32_t Pressure;
    uint16_t Depth;
    uint16_t Salinity;
};
typedef struct OenvData OenvData_t;


void DepthData2Payload(OenvData_t* depth_data, uint8_t* payload, uint8_t payload_size);
