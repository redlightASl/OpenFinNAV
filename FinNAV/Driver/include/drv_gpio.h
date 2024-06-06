#pragma once
#include "Defines.h"
#include "Driver.h"


#ifdef LIBROV_ENABLE_DRIVER_GPIO
typedef enum
{
    DRV_GPIO_LOW = 0x00,
    DRV_GPIO_HIGH = 0x01
} DrvGpioState_e;

typedef enum
{
    DRV_GPIO_AF = 0x00,
    DRV_GPIO_OUTPUT_PP,
    DRV_GPIO_OUTPUT_OD,
    DRV_GPIO_INPUT_PULLUP,
    DRV_GPIO_INPUT_PULLDOWN,
    DRV_GPIO_INPUT_FLOAT
} DrvGpioMode_e;

typedef enum
{
    DRV_GPIO_IRQ_DISABLE = 0x00,
    DRV_GPIO_IRQ_RISING,
    DRV_GPIO_IRQ_FALLING,
    DRV_GPIO_IRQ_EDGE,
    DRV_GPIO_IRQ_HIGH,
    DRV_GPIO_IRQ_LOW
} DrvGpioIRQ_e;

struct drv_gpio_cfg
{
    uint16_t pin;
    DrvGpioState_e state;
    DrvGpioMode_e mode;
};
typedef struct drv_gpio_cfg drv_gpio_cfg_t;

#ifdef LIBROV_HANDLE_INTERRUPT
struct drv_gpio_irq
{
    uint16_t pin;
    DrvGpioIRQ_e irq_mode;
    fin_irq_t irq;
}
typedef struct drv_gpio_irq drv_gpio_irq_t;
#endif /* LIBROV_HANDLE_INTERRUPT */

struct drv_gpio_opt
{
    uint16_t(*gpio_get_dev)(rov_dev_t* dev, const uint8_t* name);
    dev_instance_t(*gpio_get_inst)(rov_dev_t* dev, uint16_t pin_num);
    uint8_t(*gpio_read)(rov_dev_t* dev, uint16_t pin_num);
    void (*gpio_write)(rov_dev_t* dev, uint16_t pin_num, bool pin_state);
    void (*gpio_set_mode)(rov_dev_t* dev, uint16_t pin_num, DrvGpioMode_e mode);
#ifdef LIBROV_HANDLE_INTERRUPT
    void (*gpio_set_irq)(rov_dev_t* dev, , );
    void (*gpio_del_irq)(rov_dev_t* dev, , );
#endif /* LIBROV_HANDLE_INTERRUPT */

};
typedef struct drv_gpio_opt drv_gpio_opt_t;

struct drv_gpio
{
    rov_dev_t dev;
    drv_gpio_opt_t* opt;
    drv_gpio_cfg_t cfg;
#ifdef LIBROV_HANDLE_INTERRUPT
    drv_gpio_irq_t irq;
#endif /* LIBROV_HANDLE_INTERRUPT */
};
typedef struct drv_gpio drv_gpio_t;

extern drv_gpio_opt_t gpio_driver;
extern dev_ops_t gpio_device;

extern rov_dev_probe_t bsp_gpio_probe;
extern rov_dev_read_t bsp_gpio_read;
extern rov_dev_write_t bsp_gpio_write;
extern rov_dev_ioctl_t bsp_gpio_ioctl;

rov_err_e drv_gpio_sysinit(drv_gpio_t* gpio, const uint8_t* name, const drv_gpio_opt_t* opt, void* user_data);

uint16_t drv_gpio_get_pin(const uint8_t* name);
void drv_gpio_write(drv_gpio_t* gpio, uint16_t gpio_pin, bool gpio_state);
bool drv_gpio_read(drv_gpio_t* gpio, uint16_t gpio_pin);
void drv_gpio_set_mode(drv_gpio_t* gpio, uint16_t gpio_pin, DrvGpioMode_e mode);
#ifdef LIBROV_HANDLE_INTERRUPT
rov_err_e drv_gpio_irq_init(drv_gpio_t* gpio, uint16_t gpio_pin, DrvGpioIRQ_e irq_mode, fin_irq_cb irq_cb, ROV_VOID_POINTER irq_args);
rov_err_e drv_gpio_irq_deinit(drv_gpio_t* gpio, uint16_t gpio_pin);
rov_err_e drv_gpio_irq_ctrl(drv_gpio_t* gpio, bool is_enable);
#endif /* LIBROV_HANDLE_INTERRUPT */
#endif /* LIBROV_ENABLE_DRIVER_GPIO */
