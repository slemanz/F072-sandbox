#include "driver_gpio.h"
#include "stm32f0xx.h"

/**
 * PRIVATE HELPERS
 */

static void enable_clock(GPIO_TypeDef *port)
{
    if      (port == GPIOA) RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHBENR |= RCC_AHBENR_GPIODEN;
    else if (port == GPIOE) RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
    else if (port == GPIOF) RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
}

/**
 * Implementations
 */

void gpio_set_mode(gpio_pin_t pin, gpio_mode_e mode)
{
    pin.port->MODER &= ~(0x3U << (pin.number * 2));
    pin.port->MODER |=  (mode << (pin.number * 2));
}

void gpio_set_pull(gpio_pin_t pin, gpio_pull_e pull)
{
    pin.port->PUPDR &= ~(0x3U << (pin.number * 2));
    pin.port->PUPDR |=  (pull << (pin.number * 2));
}

void gpio_init(const gpio_config_t *config)
{
    GPIO_TypeDef *port = config->pin.port;
    uint8_t pin_number = config->pin.number;

    enable_clock(port);

    gpio_write(config->pin, config->init_state);

    

}

/**
 * Data read and write
 */

void gpio_set(gpio_pin_t pin)
{
    pin.port->BSRR = (1 << pin.number);
}

void gpio_clear(gpio_pin_t pin)
{
    pin.port->BRR = (1 << pin.number);
}

void gpio_write(gpio_pin_t pin, gpio_state_e state)
{
    if(state == GPIO_STATE_SET)
    {
        gpio_set(pin);
    }else
    {
        gpio_clear(pin);
    }
}

gpio_state_e gpio_read(gpio_pin_t pin)
{
    if(pin.port->IDR & (1U << pin.number))
    {
        return GPIO_STATE_SET;
    }
    return GPIO_STATE_RESET;
}

void gpio_toggle(gpio_pin_t pin)
{
    if(pin.port->ODR & (1U << pin.number))
    {
        gpio_clear(pin);
    }else
    {
        gpio_set(pin);
    }
}