/**
 * @file Sensor.h
 * @brief 提供传感器解析相关算法
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2022-06-17
 * 
 * @copyright Copyright (c) 2022  RedlightASl
 * 
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author  <th>Description
 * <tr><td>2022-06-17  <td>1.0      <td>wangh   <td>Content
 * </table>
 */
#pragma once
#include "Defines.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef LIBROV_USE_SENSOR
#include "Driver.h"


/**
 * @brief 传感器控制方法类 
 * @note 借鉴betaflight的传感器框架
 */
struct sensor_ops
{
    int8_t(*preinit)(struct rov_sensor* sensor); //sensor hardware init
    int8_t(*init)(struct rov_sensor* sensor); //sensor init
    int8_t(*reset)(struct rov_sensor* sensor); //sensor reset
    int8_t(*deinit)(struct rov_sensor* sensor); //sensor deinit

    int8_t(*execute)(struct rov_sensor* sensor, ROV_VOID_POINTER sensor_data); //sensor polling write
    int8_t(*sense)(struct rov_sensor* sensor, ROV_VOID_POINTER sensor_data); //sensor polling read
    int8_t(*process)(struct rov_sensor* sensor, uint32_t cmd, uint32_t arg, ROV_VOID_POINTER input, ROV_VOID_POINTER output); //sensor data process
};
typedef struct sensor_ops sensor_ops_t;

struct rov_sensor
{
    rov_dev_t* sensor_devices;
    sensor_ops_t sensor_ops;
};
typedef struct rov_sensor rov_sensor_t;

#endif

#if defined (CONFIG_TARGET_RTOS_RTT)
struct DMA_DataStruct
{
    rt_device_t dev;
    rt_size_t size;
};
typedef struct DMA_DataStruct DMA_DataStruct_t;

struct DeepData
{
    rt_uint16_t WaterTemperature;
    rt_uint32_t WaterPressure;
    rt_uint8_t is_signed;
    rt_uint16_t WaterDepth;
};
typedef struct DeepData DeepData_t;

struct WT931Data
{
    rt_uint16_t Acceleration[3]; // 0x55 0x51
    rt_uint16_t AngularSpeed[3]; // 0x55 0x52
    rt_uint16_t EulerAngle[3]; // 0x55 0x53
    rt_uint16_t MagneticValue[3]; // 0x55 0x54
};
typedef struct WT931Data WT931Data_t;

#elif defined (CONFIG_TARGET_RTOS_FREERTOS)


#ifdef LIBROV_ENABLE_OSD
struct VideoData
{
    uint8_t VedioHead;
    uint8_t Command;
    uint8_t VedioEnd;
};
typedef struct VideoData VideoData_t;
#endif


#else













#endif

#ifdef __cplusplus
}
#endif
