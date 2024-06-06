#pragma once

#define CPU_IRQNO_MAX 256
#define CPU_IRQNO_SHIFT 16

#if defined(CONFIG_TARGET_HAL_HAL) /* HAL Lib */
#include "stm32f4xx_hal.h"

#ifdef LIBROV_ENABLE_DRIVER_GPIO
#define GPIO_DEV_HANDLE(io_port, io_index) {GPIO##io_port, GPIO_PIN_##io_index}
#define GPIO_DEV_INSTANCE GPIO_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_UART
#include "usart.h"
#define UART_DEV_HANDLE(num) huart##num
#define UART_DEV_INSTANCE UART_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_PWM
#include "tim.h"
#define PWM_DEV_HANDLE(num) htim##num
#define PWM_DEV_INSTANCE TIM_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_HWTIM
#include "tim.h"
#define HWTIM_DEV_HANDLE(num) htim##num
#define HWTIM_DEV_INSTANCE TIM_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_RTC
#include "rtc.h"
#define RTC_DEV_HANDLE(num) hrtc##num
#define RTC_DEV_INSTANCE RTC_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_WDG
#include "iwdg.h"
#define WDG_DEV_HANDLE(num) hwdg##num
#define WDG_DEV_INSTANCE IWDG_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_I2C
#include "i2c.h"
#define I2C_DEV_HANDLE(num) hi2c##num
#define I2C_DEV_INSTANCE I2C_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_SPI
#include "spi.h"
#define SPI_DEV_HANDLE(num) hspi##num
#define SPI_DEV_INSTANCE SPI_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_I2C_SOFT
#include "i2c_soft.h"
#endif
#ifdef LIBROV_ENABLE_DRIVER_CAN
#include "can.h"
#define CAN_DEV_HANDLE(num) hcan##num
#define CAN_DEV_INSTANCE CAN_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_CANFD
#include "fdcan.h"
#define CANFD_DEV_HANDLE(num) hfdcan##num
#define CANFD_DEV_INSTANCE FDCAN_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_ADC
#include "adc.h"
#define ADC_DEV_HANDLE(num) hadc##num
#define ADC_DEV_INSTANCE ADC_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_DAC
#include "dac.h"
#define DAC_DEV_HANDLE(num) hdac##num
#define DAC_DEV_INSTANCE DAC_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_DMA
#include "dma.h"
#define DMA_TX_DEV_HANDLE(altdev, num) hdma_##altdev##num##_tx
#define DMA_RX_DEV_HANDLE(altdev, num) hdma_##altdev##num##_rx
#define DMA_TX_MEM_HANDLE(num) hdma_##num##_tx
#define DMA_RX_MEM_HANDLE(num) hdma_##num##_rx
#define DMA_DEV_INSTANCE DMA_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_FLASH
#endif
#ifdef LIBROV_ENABLE_DRIVER_PARALLEL
#endif
#ifdef LIBROV_ENABLE_DRIVER_SDIO
#include "sdio.h"
#define SDIO_DEV_HANDLE(num) hsd##num
#define SDIO_DEV_INSTANCE SD_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_ETH
#include "eth.h"
#define ETH_DEV_HANDLE(num) heth##num
#define ETH_DEV_INSTANCE ETH_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_DSP
#include "rng.h"
#include "crc.h"
#include "cordic.h"
#define RNG_DEV_HANDLE(num) hrng
#define RNG_DEV_INSTANCE RNG_HandleTypeDef
#define CRC_DEV_HANDLE(num) hcrc
#define CRC_DEV_INSTANCE CRC_HandleTypeDef
#define CORDIC_DEV_HANDLE(num) hcordic
#define CORDIC_DEV_INSTANCE CORDIC_HandleTypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_FPGA
#endif

#elif defined(CONFIG_TARGET_HAL_STDPERIPH) /* SPL Lib */
#include "stm32f4xx.h"

#ifdef LIBROV_ENABLE_DRIVER_GPIO
#define GPIO_DEV_HANDLE(io_port, io_index) {GPIO##io_port, GPIO_PIN_##io_index}
#define GPIO_DEV_INSTANCE GPIO_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_UART
#define UART_DEV_HANDLE(num) USART##num
#define UART_DEV_INSTANCE USART_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_PWM
#define PWM_DEV_HANDLE(num) TIM##num
#define PWM_DEV_INSTANCE TIM_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_HWTIM
#define HWTIM_DEV_HANDLE(num) TIM##num
#define HWTIM_DEV_INSTANCE TIM_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_RTC

#endif
#ifdef LIBROV_ENABLE_DRIVER_WDG

#endif
#ifdef LIBROV_ENABLE_DRIVER_I2C
#include "i2c.h"
#define I2C_DEV_HANDLE(num) I2C##num
#define I2C_DEV_INSTANCE I2C_TypeDef
#endif
#ifdef LIBROV_ENABLE_DRIVER_SPI
#include "spi.h"
#define SPI_DEV_HANDLE(num) SPI##num
#define SPI_DEV_INSTANCE SPI_TypeDef
#endif

//TODO
#elif defined(CONFIG_TARGET_HAL_REGISTER) /* Hardware Register Mapping Only */
//TODO
#endif /* CONFIG_TARGET_HAL_HAL, CONFIG_TARGET_HAL_STDPERIPH, CONFIG_TARGET_HAL_REGISTER */
