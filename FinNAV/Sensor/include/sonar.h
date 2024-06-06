#pragma once
#include "Defines.h"

struct HeightSonarData
{
    uint32_t Height;
    uint16_t Confidence;
};
typedef struct HeightSonarData HeightSonarData_t;

struct FrontSonarData
{
    uint32_t Distance;
    uint16_t Confidence;
};
typedef struct FrontSonarData FrontSonarData_t;


// void HeightSonar2Payload(SonarData_t* sonar_data, uint8_t* payload, uint8_t payload_size);
