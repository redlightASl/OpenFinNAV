#include "Defines.h"
#include "Driver.h"
#include "drv_gpio.h"


#ifdef LIBROV_ENABLE_DRIVER_GPIO
#ifndef BSP_CONFIG_FILE
#error "Modify BSP Configuration Header File!"
#else
#include BSP_CONFIG_FILE
#endif

static drv_gpio_t _drv_gpio_inst;

rov_err_e drv_gpio_init(drv_gpio_t* drv, uint8_t id, ROV_VOID_POINTER user_data)
{
    rov_err_e ret = ROV_ERROR;
    rov_dev_t* dev;
    rov_assert(drv != NULL);
    dev = &(drv->device);
    dev->id = id;
    dev->user_data = user_data;
    ret = drv_device_attach(dev, DEV_TYPE_GPIO, drv->opt);
    return ret;

}



int rt_device_pin_register(const char *name, const struct rt_pin_ops *ops, void *user_data)
{
    _hw_pin.parent.type         = RT_Device_Class_Pin;
    _hw_pin.parent.rx_indicate  = RT_NULL;
    _hw_pin.parent.tx_complete  = RT_NULL;

#ifdef RT_USING_DEVICE_OPS
    _hw_pin.parent.ops          = &pin_ops;
#else
    _hw_pin.parent.init         = RT_NULL;
    _hw_pin.parent.open         = RT_NULL;
    _hw_pin.parent.close        = RT_NULL;
    _hw_pin.parent.read         = _pin_read;
    _hw_pin.parent.write        = _pin_write;
    _hw_pin.parent.control      = _pin_control;
#endif

    _hw_pin.ops                 = ops;
    _hw_pin.parent.user_data    = user_data;

    /* register a character device */
    rt_device_register(&_hw_pin.parent, name, RT_DEVICE_FLAG_RDWR);

    return 0;
}



















uint8_t drv_gpio_read(drv_gpio_t* drv, uint32_t obj, uint8_t pin_num)
{
    if (pin_num < 32)
    {
        return drv->opt.gpio_read(&drv->device[obj], pin_num);
    }
}

void drv_gpio_write(drv_gpio_t* drv, uint32_t obj, uint8_t pin_num, uint8_t gpio_state)
{
    if (pin_num < 32)
    {
        drv->opt.gpio_write(&drv->device[obj], pin_num, gpio_state);
    }
}

ROV_INLINE void drv_gpio_setmode(drv_gpio_t* drv, uint32_t obj, uint8_t pin_num, uint8_t mode)
{
    drv->opt.gpio_setmode(&drv->device[obj], pin_num, mode);
}

ROV_INLINE void drv_gpio_find(drv_gpio_t* drv, GPIO_DEV_INSTANCE* inst, uint8_t* obj)
{
    *obj = drv_device_find_obj(&drv->device, GPIO_DEV_MAX_NUM, (ROV_VOID_POINTER)inst);
}

#endif
