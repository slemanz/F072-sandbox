#include "driver_gpio.h"
#include "stm32f0xx.h"

void GPIO_Init(void)
{
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;      // clock GPIOA

    GPIOA->MODER &= ~GPIO_MODER_MODER6;     // PA6 output push-pull
    GPIOA->MODER |= GPIO_MODER_MODER6_0;

    GPIOA->BSRR = GPIO_BSRR_BS_6;           // PA6 high
}
