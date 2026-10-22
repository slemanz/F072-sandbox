#include <stdio.h>
#include "driver_gpio.h"

int main(void)
{
    gpio_config_t pa5 = {
        .pin = {.port = GPIOA, GPIO_PIN_5},
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_init(&pa5);

    while(1)
    {
    

    }
}