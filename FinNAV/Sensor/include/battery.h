#pragma once
#include "Defines.h"

struct BatteryData
{
    uint32_t capicity;
    uint32_t remain;
    uint32_t voltage;
    uint32_t current;
    uint32_t power;
};
typedef struct BatteryData BatteryData_t;
