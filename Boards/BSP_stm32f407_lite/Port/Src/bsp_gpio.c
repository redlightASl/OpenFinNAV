#include "Driver.h"
#include "bsp_stm32f407xx.h"

#ifdef LIBROV_ENABLE_DRIVER_GPIO

drv_gpio_opt_t gpio_driver ={
    
};

struct drv_gpio_opt bsp_gpio_ops = {
    .gpio_read = bsp_gpio_read,
    .gpio_write = bsp_gpio_write,
    .gpio_setmode = bsp_gpio_setmode
};

struct stm32_gpio_pin
{
    GPIO_DEV_INSTANCE* port;
    uint16_t pin;
};

struct stm32_gpio_pin gpio_pins[GPIO_DEV_MAX_NUM][16] =
{
    {
        GPIO_DEV_HANDLE(A, 0),
        GPIO_DEV_HANDLE(A, 1),
        GPIO_DEV_HANDLE(A, 2),
        GPIO_DEV_HANDLE(A, 3),
        GPIO_DEV_HANDLE(A, 4),
        GPIO_DEV_HANDLE(A, 5),
        GPIO_DEV_HANDLE(A, 6),
        GPIO_DEV_HANDLE(A, 7),
        GPIO_DEV_HANDLE(A, 8),
        GPIO_DEV_HANDLE(A, 9),
        GPIO_DEV_HANDLE(A, 10),
        GPIO_DEV_HANDLE(A, 11),
        GPIO_DEV_HANDLE(A, 12),
        GPIO_DEV_HANDLE(A, 13),
        GPIO_DEV_HANDLE(A, 14),
        GPIO_DEV_HANDLE(A, 15)
    },
    {
        GPIO_DEV_HANDLE(B, 0),
        GPIO_DEV_HANDLE(B, 1),
        GPIO_DEV_HANDLE(B, 2),
        GPIO_DEV_HANDLE(B, 3),
        GPIO_DEV_HANDLE(B, 4),
        GPIO_DEV_HANDLE(B, 5),
        GPIO_DEV_HANDLE(B, 6),
        GPIO_DEV_HANDLE(B, 7),
        GPIO_DEV_HANDLE(B, 8),
        GPIO_DEV_HANDLE(B, 9),
        GPIO_DEV_HANDLE(B, 10),
        GPIO_DEV_HANDLE(B, 11),
        GPIO_DEV_HANDLE(B, 12),
        GPIO_DEV_HANDLE(B, 13),
        GPIO_DEV_HANDLE(B, 14),
        GPIO_DEV_HANDLE(B, 15)
    }
};

uint8_t bsp_gpio_read(rov_dev_t* dev, uint8_t pin_num)
{
    uint8_t pin_state = 0;
    pin_state = HAL_GPIO_ReadPin(gpio_pins[dev->dev_id][pin_num].port, gpio_pins[dev->dev_id][pin_num].pin);
    return pin_state;
}

void bsp_gpio_write(rov_dev_t* dev, uint8_t pin_num, uint8_t pin_state)
{
    HAL_GPIO_WritePin(gpio_pins[dev->dev_id][pin_num].port,
        gpio_pins[dev->dev_id][pin_num].pin,
        ((pin_state == DRV_GPIO_HIGH) ? (GPIO_PIN_SET) : (GPIO_PIN_RESET)));
}

void bsp_gpio_setmode(rov_dev_t* dev, uint8_t pin_num, uint8_t mode)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = gpio_pins[dev->dev_id][pin_num].pin;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    switch (mode)
    {
    case DRV_GPIO_OUTPUT:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case DRV_GPIO_INPUT:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    case DRV_GPIO_INPUT_PULLUP:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        break;
    case DRV_GPIO_INPUT_PULLDOWN:
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLDOWN;
        break;
    case DRV_GPIO_OUTPUT_OD:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    default:
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        break;
    }
    HAL_GPIO_Init(gpio_pins[dev->dev_id][pin_num].port, &GPIO_InitStruct);
}

void bsp_gpio_irq_handler(rov_dev_t* dev)
{
    dev->dev_irq->cb_function(dev->dev_irq->arg);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case GPIO_PIN_0:
        break;
    case GPIO_PIN_1:
        break;
    case GPIO_PIN_2:
        break;
    case GPIO_PIN_3:
        break;
    case GPIO_PIN_4:
        break;
    case GPIO_PIN_5:
        break;
    case GPIO_PIN_6:
        break;
    case GPIO_PIN_7:
        break;
    case GPIO_PIN_8:
        break;
    case GPIO_PIN_9:
        break;
    case GPIO_PIN_10:
        break;
    case GPIO_PIN_11:
        break;
    case GPIO_PIN_12:
        break;
    case GPIO_PIN_13:
        break;
    case GPIO_PIN_14:
        break;
    case GPIO_PIN_15:
        break;
    default:
        break;
    }

    // dev->dev_irq->cb_function(dev->dev_irq.arg);
}
#endif
