#pragma once
#include "Defines.h"

struct IenvData
{
    uint16_t Temperature;
    uint16_t Humidity;
    uint32_t Barometric;
    uint16_t Illumination;
};
typedef struct IenvData IenvData_t;


void CarbinData2Payload(IenvData_t* carbin_data, uint8_t* payload, uint8_t payload_size);
