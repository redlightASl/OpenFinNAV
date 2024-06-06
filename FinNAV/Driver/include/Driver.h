/**
 * @file Driver.h
 * @brief
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

#ifdef LIBROV_USE_DRIVER

#ifndef BSP_CONFIG_FILE
#error "Modify BSP Configuration Header File!"
#else
#include BSP_CONFIG_FILE
#endif /* BSP_CONFIG_FILE */

#define DEV_TYPE_EMPTY      0x00
#define DEV_TYPE_GPIO       0x01
#define DEV_TYPE_UART       0x02
#define DEV_TYPE_DMA        0x03
#define DEV_TYPE_PWM        0x04
#define DEV_TYPE_HWTIM      0x05
#define DEV_TYPE_RTC        0x06
#define DEV_TYPE_WDG        0x07
#define DEV_TYPE_I2C_HARD   0x08
#define DEV_TYPE_SPI        0x09
#define DEV_TYPE_I2C_SOFT   0x0A
#define DEV_TYPE_CAN        0x0B
#define DEV_TYPE_CANFD      0x0C
#define DEV_TYPE_ADC        0x0D
#define DEV_TYPE_DAC        0x0E
#define DEV_TYPE_FLASH      0x0F
#define DEV_TYPE_SDIO       0x10
#define DEV_TYPE_PARALLEL   0x11
#define DEV_TYPE_ETH        0x12
#define DEV_TYPE_DSP        0x13
#define DEV_TYPE_FPGA       0x14
#define DEV_TYPE_GENERAL    0x15
#define DEV_TYPE_UNKNOWN    0xFF
typedef uint8_t dev_type_t;

#define DEV_FLAG_REMOVABLE  0x01 /**< removable device */
#define DEV_FLAG_STANDALONE 0x02 /**< standalone device */
#define DEV_FLAG_ACTIVATED  0x10 /**< device is activated */
#define DEV_FLAG_SUSPENDED  0x20 /**< device is suspended */
#define DEV_FLAG_STREAM     0x40 /**< stream mode */

struct dev_reg
{
    vuint32_t _base; //base address
    vuint32_t _size; //register size
};
typedef struct dev_reg dev_reg_t;

struct dev_instance_regs
{
    uint32_t _regs_num; //Total number of device registers
    dev_reg_t* _regs; //device register info table pointer
};

#if defined(CONFIG_TARGET_HAL_HAL)
typedef ROV_VOID_POINTER dev_instance_t; //device instance
#elif defined(CONFIG_TARGET_HAL_STDPERIPH)
typedef ROV_VOID_POINTER dev_instance_t; //device instance
#else
typedef struct dev_instance_regs* dev_instance_t; //device register table
#endif

#ifdef LIBROV_HANDLE_INTERRUPT
#include "fin_interrupt.h"
#endif /* LIBROV_HANDLE_INTERRUPT */

struct dev_ops
{
    rov_err_t(*probe)(struct rov_dev* device); // 设备自检
    rov_err_t(*reset)(struct rov_dev* device); // 设备复位
    rov_err_t(*sleep)(struct rov_dev* device, const uint32_t time); //设备休眠
    uint32_t(*read)(struct rov_dev* device, void* rd_buffer, const uint32_t size); //设备读取
    uint32_t(*write)(struct rov_dev* device, const void* wr_buffer, const uint32_t size); //设备写入
    rov_err_t(*ioctl)(struct rov_dev* device, const int32_t cmd, void* args); //设备综合控制
};
typedef struct dev_ops dev_ops_t;

struct rov_dev
{
    uint8_t id; //设备ID
    uint8_t flag; //设备特性标志
    rov_list_t list; //设备链表
    dev_type_t type; //设备类型
    dev_instance_t inst; //设备实例指针
#ifdef LIBROV_HANDLE_INTERRUPT
    dev_irq_t irq; //设备中断服务函数
#endif /* LIBROV_HANDLE_INTERRUPT */
    dev_ops_t* ops; //设备操作接口指针
    ROV_VOID_POINTER user_data; //用户定义数据区指针
};
typedef struct rov_dev rov_dev_t;

typedef rov_err_t(*rov_dev_probe_t)(struct rov_dev* device);
typedef rov_err_t(*rov_dev_reset_t)(struct rov_dev* device);
typedef rov_err_t(*rov_dev_sleep_t)(struct rov_dev* device, const uint32_t time);
typedef uint32_t(*rov_dev_read_t)(struct rov_dev* device, void* rd_buffer, const uint32_t size);
typedef uint32_t(*rov_dev_write_t)(struct rov_dev* device, const void* wr_buffer, const uint32_t size);
typedef rov_err_t(*rov_dev_ioctl_t)(struct rov_dev* device, const int32_t cmd, void* args);

rov_err_t drv_device_attach(rov_dev_t* dev, dev_type_t type, dev_ops_t* ops);
rov_err_t drv_device_detach(rov_dev_t* dev);
rov_err_t drv_device_regmap(rov_dev_t* dev, dev_instance_t inst);
rov_dev_t* drv_device_find_from_id(uint8_t id);
rov_dev_t* drv_device_find_from_inst(dev_instance_t inst);
uint8_t drv_device_get_id(rov_dev_t* dev);
dev_type_t drv_device_get_type(rov_dev_t* dev);
dev_instance_t drv_device_get_inst(rov_dev_t* dev);
#ifdef LIBROV_HANDLE_INTERRUPT
rov_err_t drv_device_irq_hook(rov_dev_t* dev, fin_irq_t* irq);
#endif /* LIBROV_HANDLE_INTERRUPT */


#ifdef LIBROV_ENABLE_DRIVER_GPIO
#include "drv_gpio.h"
#endif /* LIBROV_ENABLE_DRIVER_GPIO */

#ifdef LIBROV_ENABLE_DRIVER_UART
#include "drv_uart.h"
#endif /* LIBROV_ENABLE_DRIVER_UART */

#ifdef LIBROV_ENABLE_DRIVER_DMA
#include "drv_dma.h"
#endif /* LIBROV_ENABLE_DRIVER_DMA */

void drv_soc_init(void);
void drv_linkcom_init(void);
void drv_console_init(void);
ROV_WEAK void drv_board_init(void);

#endif /* LIBROV_USE_DRIVER */
