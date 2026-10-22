#include <stdio.h>
#include "driver_gpio.h"

int main(void)
{
    gpio_config_t pa5;
    pa5.pin.port = GPIOA;
    pa5.pin.number = 5;
    pa5.mode = GPIO_MODE_OUTPUT;
    pa5.otype = GPIO_OTYPE_PP;
    pa5.init_state = GPIO_STATE_RESET;
    pa5.pull = GPIO_PULL_NONE;
    pa5.speed = GPIO_SPEED_LOW;
    pa5.af = GPIO_AF0;
    gpio_init(&pa5);

    while(1)
    {
    

    }
}