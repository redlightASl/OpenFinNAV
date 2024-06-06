#ifndef __GY26_DRIVER_H_
#define __GY26_DRIVER_H_
#include "Driver.h"


struct gy26_driver
{
    uint16_t mag_data;
    uint16_t temp_data;
};
typedef struct gy26_driver gy26_driver_t;


#define DEVICE_ADDR 0xE0

void read_mag(gy26_driver_t* dev);
void read_temp(gy26_driver_t* dev);
// int8_t gy26_init(struct rov_dev* device);
// int8_t gy26_sense(struct rov_dev* device, ROV_VOID_POINTER sensor_data);
#endif
