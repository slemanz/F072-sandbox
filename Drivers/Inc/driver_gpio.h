#ifndef INC_DRIVER_GPIO_H_
#define INC_DRIVER_GPIO_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f072xb.h"

typedef struct
{
    GPIO_TypeDef *port;
    GPIO_TypeDef  pin;      /* 0..15 */
}gpio_pin_t;

typedef enum
{
    GPIO_MODE_INPUT = 0,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTFN,
    GPIO_MODE_ANALOG
}gpio_mode_e;

typedef enum
{
    GPIO_OTYPE_PP = 0,
    GPIO_OTYPE_OD
}gpio_otype_e;

typedef enum
{
    GPIO_SPEED_LOW = 0,
    GPIO_SPEED_MEDIUM = 1,
    GPIO_SPEED_HIGH = 3
}gpio_speed_e;

typedef enum
{
    GPIO_PULL_NONE = 0,
    GPIO_PULL_UP,
    GPIO_PULL_DOWN
}gpio_pull_e;

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

void GPIO_Init(void);


#endif /* INC_DRIVER_GPIO_H_ */