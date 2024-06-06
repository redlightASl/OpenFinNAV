/**
 * @file Display.h
 * @brief 数据显示
 * @author RedlightASl (dddbbbdd@foxmail.com)
 * @version 1.0
 * @date 2023-05-24
 *
 * @copyright Copyright (c) 2023 RedlightASl
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date    <th>Version  <th>Author     <th>Description
 * <tr><td>2023-05-24  <td>1.0      <td>RedlightASl   <td>Content
 * </table>
 */
#pragma once
#include "Defines.h"



#ifdef LIBROV_ENABLE_OSD
#include "Driver.h"

//字库
extern uint8_t NumLib[15][2];

// generate ASCII-Art
static const uint8_t ASCII_ArtLib[] = "@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.   ";

//漏水指示
extern uint8_t String_WaterOn[2][27];
extern uint8_t String_WaterOff[2][27];

//  //警告1位置
// #define POSX_WARN1_HIGH 0x00
// #define POSX_WARN1_LOW 0x00
// #define POSY_WARN1_HIGH 0x00
// #define POSY_WARN1_LOW 0x00
// //警告2位置
// #define POSX_WARN2_HIGH 0x00
// #define POSX_WARN2_LOW 0x00
// #define POSY_WARN2_HIGH 0x00
// #define POSY_WARN2_LOW 0x00
// //水深位置
// #define POSX_WATERDEEP_HIGH 0x00
// #define POSX_WATERDEEP_LOW 0x00
// #define POSY_WATERDEEP_HIGH 0x00
// #define POSY_WATERDEEP_LOW 0x00
// //姿态位置
// #define POSX_ATTITUDE_HIGH 0x00
// #define POSX_ATTITUDE_LOW 0x00
// #define POSY_ATTITUDE_HIGH 0x00
// #define POSY_ATTITUDE_LOW 0x00
// //电池电压位置
// #define POSX_POWER_HIGH 0x00
// #define POSX_POWER_LOW 0x00
// #define POSY_POWER_HIGH 0x00
// #define POSY_POWER_LOW 0x00

// #define DISPLAY_ADDRESS 0x00

#define Init_QL504_DEFAULT(x) Init_QL504((x), (rt_uint8_t**)0, (uint8_t)1)

void Init_QL504(rt_device_t uart, uint8_t** init_table, uint8_t init_table_height);
void SendNum_QL504(rt_device_t uart, uint8_t Row, uint8_t Column, uint8_t Number);
void SendString_QL504(rt_device_t uart, uint8_t* StringLib, uint8_t StringLength);
void ClearScreen_QL504(rt_device_t uart);

void Init_QL504(UART_HandleTypeDef* uart, uint8_t** init_table, uint8_t init_table_height);
void SendNum_QL504(UART_HandleTypeDef* uart, uint8_t Row, uint8_t Column, uint8_t Number);
void ClearScreen_QL504(UART_HandleTypeDef* uart);



#endif /* LIBROV_ENABLE_OSD */
