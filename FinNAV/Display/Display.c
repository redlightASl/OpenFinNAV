#include "Display.h"

#ifdef LIBROV_ENABLE_OSD

uint8_t NumLib[15][2] = { 
        { 0xa3, 0xb0 }, //0
        { 0xa3, 0xb1 }, //1
        { 0xa3, 0xb2 }, //2
        { 0xa3, 0xb3 }, //3
        { 0xa3, 0xb4 }, //4
        { 0xa3, 0xb5 }, //5
        { 0xa3, 0xb6 }, //6
        { 0xa3, 0xb7 }, //7
        { 0xa3, 0xb8 }, //8
        { 0xa3, 0xb9 }, //9
        { 0xa3, 0xae }, //.
        { 0xa3, 0xad }, //-
        { 0xa3, 0xab }, //+
        { 0xa1, 0xa1 }, // space
        { 0xa3, 0xba } //:
};

// #include <rtthread.h>
// #include <rtdevice.h>

// static rt_uint8_t DEFAULT_INIT_TABLE[DEFAULT_INIT_TABLE_HEIGHT][5] = { { 0x55, 0x03, 0x00, 0x00, DISPLAY_ADDRESS }, //设置水平位,垂直位移为0
//         { 0x55, 0x04, 0x1E, 0x00, DISPLAY_ADDRESS }, //设置扫描起始垂直位移30

//     //设置从第一行到第十二行字符大小
//     { 0x55, 0x06, 0x00, 0x01, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x02, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x03, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x04, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x05, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x06, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x07, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x08, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x09, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0A, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0B, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0C, DISPLAY_ADDRESS }, //字符标准大小

//     { 0x55, 0x09, 0x71, 0x00, DISPLAY_ADDRESS }, //设置字符颜色
//     { 0x55, 0x02, 0x11, 0x00, DISPLAY_ADDRESS }, //设置扫描方式

//     { 0x55, 0x0A, 0x00, 0x00, DISPLAY_ADDRESS }, //设置行距为0
//     { 0x55, 0x01, 0x01, 0x01, DISPLAY_ADDRESS } //清屏并设置底色为蓝色
// };

// //show water warning
// rt_uint8_t String_WaterOn[2][27] = { { 0x55, 0x07, 0x06, 0x01, 0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x31, 0x06,
//         0x01, 0x00, 0xB2, 0xD5, 0xC4, 0xDA, 0xA3, 0xB1, 0xB5, 0xE3, 0xC2, 0xA9, 0xCB, 0xAE }, { 0x55, 0x07, 0x07, 0x01,
//         0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x31, 0x06, 0x01, 0x00, 0xB2, 0xD5, 0xC4, 0xDA, 0xA3, 0xB2, 0xB5,
//         0xE3, 0xC2, 0xA9, 0xCB, 0xAE } };

// //clear water warning
// rt_uint8_t String_WaterOff[2][27] = { { 0x55, 0x07, 0x05, 0x01, 0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x31, 0x06,
//         0x01, 0x00, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1 }, { 0x55, 0x07, 0x06, 0x01,
//         0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x31, 0x06, 0x01, 0x00, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1,
//         0xA1, 0xA1, 0xA1, 0xA1, 0xA1 } };

// void Init_QL504(rt_device_t uart, uint8_t** init_table, uint8_t init_table_height)
// {
//     static uint8_t SendTempBuffer_Command_q[17] = { 0x55, 0x06, 0x71, 0x00, 0x00, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71,
//             0x71, 0x71, 0x71, 0x71, 0x71, 0x71 };

//     if (init_table != (uint8_t**)0)
//     {
//         for (uint8_t i = 0; i < init_table_height; i++)
//         {
//             rt_device_write(uart, 0, init_table[i], sizeof(init_table[i]));
//             rt_thread_mdelay(1);
//         }
//     }
//     else
//     {
//         for (uint8_t i = 0; i < DEFAULT_INIT_TABLE_HEIGHT; i++)
//         {
//             rt_device_write(uart, 0, DEFAULT_INIT_TABLE[i], sizeof(DEFAULT_INIT_TABLE[i]));
//             rt_thread_mdelay(1);
//         }
//     }

//     rt_device_write(uart, 0, SendTempBuffer_Command_q, sizeof(SendTempBuffer_Command_q));
//     rt_thread_mdelay(1);
// }

// void SendNum_QL504(rt_device_t uart, uint8_t Row, uint8_t Column, uint8_t Number)
// {
//     static uint8_t SendTempBuffer[15] = { 0x55, 0x07, 0x00, 0x00, 0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x08,
//             0x00, 0x00, 0x00 };
//     SendTempBuffer[2] = Row + 1;
//     SendTempBuffer[3] = Column;
//     SendTempBuffer[12] = NumLib[Number][0];
//     SendTempBuffer[13] = NumLib[Number][1];

//     rt_device_write(uart, 0, SendTempBuffer, sizeof(SendTempBuffer));
//     //    rt_thread_mdelay(1);
// }

// void SendString_QL504(rt_device_t uart, uint8_t* StringLib, uint8_t StringLength)
// {
//     rt_device_write(uart, 0, StringLib, StringLength);
// }

// void ClearScreen_QL504(rt_device_t uart)
// {
//     static uint8_t SendTempBuffer[5] = { 0x55, 0x01, 0x01, 0x01, DISPLAY_ADDRESS }; //清屏并设置底色为蓝色
//     rt_device_write(uart, 0, SendTempBuffer, sizeof(SendTempBuffer));
//     rt_thread_mdelay(5);
// }




// #define DEFAULT_INIT_TABLE_HEIGHT 18
// static uint8_t DEFAULT_INIT_TABLE[DEFAULT_INIT_TABLE_HEIGHT][5] = { { 0x55, 0x03, 0x00, 0x00, DISPLAY_ADDRESS }, //设置水平位,垂直位移为0
//         { 0x55, 0x04, 0x1E, 0x00, DISPLAY_ADDRESS }, //设置扫描起始垂直位移30

//     //设置从第一行到第十二行字符大小
//     { 0x55, 0x06, 0x00, 0x01, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x02, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x03, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x04, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x05, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x06, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x07, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x08, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x09, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0A, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0B, DISPLAY_ADDRESS }, //字符标准大小
//     { 0x55, 0x06, 0x00, 0x0C, DISPLAY_ADDRESS }, //字符标准大小

//     { 0x55, 0x09, 0x71, 0x00, DISPLAY_ADDRESS }, //设置字符颜色
//     { 0x55, 0x02, 0x11, 0x00, DISPLAY_ADDRESS }, //设置扫描方式

//     { 0x55, 0x0A, 0x00, 0x00, DISPLAY_ADDRESS }, //设置行距为0
//     { 0x55, 0x01, 0x01, 0x01, DISPLAY_ADDRESS } //清屏并设置底色为蓝色
// };

// void Init_QL504(UART_HandleTypeDef* uart, uint8_t** init_table, uint8_t init_table_height)
// {
//     static uint8_t SendTempBuffer_Command_q[17] = { 0x55, 0x06, 0x71, 0x00, 0x00, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71,
//             0x71, 0x71, 0x71, 0x71, 0x71, 0x71 };

//     if (init_table != (uint8_t**)0)
//     {
//         for (uint8_t i = 0; i < init_table_height; i++)
//         {
//             HAL_UART_Transmit_DMA(uart, init_table[i], sizeof(init_table[i]));
//             osDelay(1);
//         }
//     }
//     else
//     {
//         for (uint8_t i = 0; i < DEFAULT_INIT_TABLE_HEIGHT; i++)
//         {
//             HAL_UART_Transmit_DMA(uart, DEFAULT_INIT_TABLE[i], sizeof(DEFAULT_INIT_TABLE[i]));
//             osDelay(1);
//         }
//     }

//     HAL_UART_Transmit_DMA(uart, SendTempBuffer_Command_q, sizeof(SendTempBuffer_Command_q));
//     osDelay(1);
// }

// void SendNum_QL504(UART_HandleTypeDef* uart, uint8_t Row, uint8_t Column, uint8_t Number)
// {
//     static uint8_t SendTempBuffer[15] = { 0x55, 0x07, 0x00, 0x00, 0x00, 0x55, 0x0A, 0x00, 0x00, 0x00, 0x55, 0x08,
//             0x00, 0x00, 0x00 };
//     SendTempBuffer[2] = Row + 1;
//     SendTempBuffer[3] = Column;
//     SendTempBuffer[12] = NumLib[Number][0];
//     SendTempBuffer[13] = NumLib[Number][1];

//     HAL_UART_Transmit_DMA(uart, SendTempBuffer, sizeof(SendTempBuffer));
//     osDelay(5);
// }

// void ClearScreen_QL504(UART_HandleTypeDef* uart)
// {
//     uint8_t SendTempBuffer[5] = { 0x55, 0x01, 0x01, 0x01, DISPLAY_ADDRESS }; //清屏并设置底色为蓝色
//     HAL_UART_Transmit_DMA(uart, SendTempBuffer, sizeof(SendTempBuffer));
//     osDelay(5);
// }

#endif /* LIBROV_ENABLE_OSD */
