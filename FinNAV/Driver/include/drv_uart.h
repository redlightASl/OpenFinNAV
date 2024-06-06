#pragma once
#include "Defines.h"
#include "Driver.h"

#ifdef LIBROV_ENABLE_DRIVER_UART



extern drv_uart_t sys_drv_uart;

typedef enum
{
    BAUD_RATE_2400 = 2400,
    BAUD_RATE_4800 = 4800,
    BAUD_RATE_9600 = 9600,
    BAUD_RATE_19200 = 19200,
    BAUD_RATE_38400 = 38400,
    BAUD_RATE_57600 = 57600,
    BAUD_RATE_115200 = 115200,
    BAUD_RATE_230400 = 230400,
    BAUD_RATE_460800 = 460800,
    BAUD_RATE_500000 = 500000,
    BAUD_RATE_921600 = 921600,
    BAUD_RATE_2000000 = 2000000,
    BAUD_RATE_2500000 = 2500000,
    BAUD_RATE_3000000 = 3000000
} uart_cfg_baudrate_e;

typedef enum
{
    DATABITS_5 = 5,
    DATABITS_6 = 6,
    DATABITS_7 = 7,
    DATABITS_8 = 8,
    DATABITS_9 = 9
} uart_cfg_databits_e;

typedef enum
{
    STOPBITS_1 = 0,
    STOPBITS_2 = 1,
    STOPBITS_3 = 2,
    STOPBITS_4 = 3
} uart_cfg_stopbits_e;

typedef enum
{
    CHECKBIT_NONE = 0,
    CHECKBIT_ODD,
    CHECKBIT_EVEN
} uart_cfg_checkbit_e;

typedef enum
{
    FLOW_CTRL_NONE = 0,
    FLOW_CTRL_CTSRTS
} uart_cfg_flow_e;

typedef enum
{
    UART_IOCTL_SET_BAUDRATE = 1,
    UART_IOCTL_SET_DATABITS,
    UART_IOCTL_SET_STOPBITS,
    UART_IOCTL_SET_PARITY,
    UART_IOCTL_SET_FLOW_TRL,
    UART_IOCTL_SET_RX_TIMEOUT,
    UART_IOCTL_SET_TX_TIMEOUT
} uart_cmd_e;

typedef enum
{
    UART_IRQ_COMPLETE = 0,
    UART_IRQ_IDLE,
    UART_IRQ_DMA_HALF,
    UART_IRQ_DMA_ALL
} uart_irq_e;

int8_t bsp_uart_probe(struct rov_dev* dev);
int8_t bsp_uart_read(struct rov_dev* dev, uint8_t* rd_buffer, uint32_t size);
int8_t bsp_uart_write(struct rov_dev* dev, uint8_t* wr_buffer, uint32_t size);
int8_t bsp_uart_ioctl(struct rov_dev* dev, uint32_t cmd, uint32_t arg);



#endif /* LIBROV_ENABLE_DRIVER_UART */

// struct drv_uart
// {
//     rov_dev_t device[UART_DEV_MAX_NUM];
// // #ifdef UART_DEV_TX_USE_DMA
// //     uint8_t* tx_dma_buffer[UART_DEV_MAX_NUM];
// //     uint32_t tx_dma_size[UART_DEV_MAX_NUM];
// // #else

// // #endif

// // #ifdef UART_DEV_RX_USE_DMA
// //     uint8_t* rx_dma_buffer[UART_DEV_MAX_NUM];
// //     uint32_t rx_dma_size[UART_DEV_MAX_NUM];
// // #else

// // #endif
// };
// typedef struct drv_uart drv_uart_t;


// void drv_uart_init(drv_uart_t* drv);
// void drv_uart_read(drv_uart_t* drv, uint32_t obj, uint8_t* rd_buffer, uint32_t size);
// void drv_uart_write(drv_uart_t* drv, uint32_t obj, uint8_t* wr_buffer, uint32_t size);
// void drv_uart_set_baudrate(drv_uart_t* drv, uint32_t obj, uint32_t baudrate);
// void drv_uart_set_databits(drv_uart_t* drv, uint32_t obj, uint8_t databits);
// void drv_uart_set_stopbit(drv_uart_t* drv, uint32_t obj, uint8_t stopbit);
// void drv_uart_set_parity(drv_uart_t* drv, uint32_t obj, uint8_t parity);
// void drv_uart_set_flow(drv_uart_t* drv, uint32_t obj, uint8_t flow_control);
// void drv_uart_set_tx_timeout(drv_uart_t* drv, uint32_t obj, uint8_t tx_timeout);
// void drv_uart_set_rx_timeout(drv_uart_t* drv, uint32_t obj, uint8_t rx_timeout);
// void drv_uart_find(drv_uart_t* drv, UART_DEV_INSTANCE* inst, uint8_t* obj);
