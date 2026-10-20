#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f072xb.h"

/**
 * @brief GPIO pin identification (port + pin number)
 */
typedef struct
{
    GPIO_TypeDef *port;
    uint8_t       number;      /* 0..15 */
}gpio_pin_t;

/**
 * @brief GPIO pin logic state
 */
typedef enum
{
    GPIO_STATE_RESET = 0,   /**< Logic low (0)  */
    GPIO_STATE_SET          /**< Logic high (1) */
}gpio_state_e;


/**
 * @brief GPIO pin mode
 */
typedef enum
{
    GPIO_MODE_INPUT = 0,    /**< Digital input                         */
    GPIO_MODE_OUTPUT,       /**< General purpose output                */
    GPIO_MODE_ALTFN,        /**< Alternate function (UART, SPI, TIM..) */
    GPIO_MODE_ANALOG        /**< Analog (ADC/DAC), lowest consumption  */
}gpio_mode_e;

/**
 * @brief GPIO output type
 */
typedef enum
{
    GPIO_OTYPE_PP = 0,      /**< Push-pull: drives high and low         */
    GPIO_OTYPE_OD           /**< Open-drain: drives low only (I2C, etc) */
}gpio_otype_e;

/**
 * @brief GPIO output speed
 */
typedef enum
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_HIGH = 3
}gpio_speed_e;

/**
 * @brief GPIO internal pull resistor
 */
typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
}gpio_pull_e;

/**
 * @brief GPIO alternate function
 */
typedef enum
{ 
    GPIO_AF0 = 0,
    GPIO_AF1,
    GPIO_AF2,
    GPIO_AF3,
    GPIO_AF4,
    GPIO_AF5,
    GPIO_AF6,
    GPIO_AF7
}gpio_af_e;

/**
 * @brief GPIO pin configuration.
 */
typedef struct
{
    gpio_pin_t   pin;
    gpio_mode_e  mode;
    gpio_otype_e otype;
    gpio_speed_e speed;
    gpio_pull_e  pull;
    gpio_af_e    af;
    bool         initial;   
} gpio_config_t;

/********************************************************************************************
 *                              APIs supported by this driver
 *                  for more information check the function definitions
 ********************************************************************************************/

void GPIO_Init(void);


#endif /* INC_DRIVER_GPIO_H_ */