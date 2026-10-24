#include "driver_gpio.h"
#include "driver_uart.h"
#include "driver_systick.h"

static const gpio_config_t uart_pins[] = {
    { .pin = { GPIOA, GPIO_PIN_2 }, .mode = GPIO_MODE_ALTFN, .af = GPIO_AF1 },
    { .pin = { GPIOA, GPIO_PIN_3 }, .mode = GPIO_MODE_ALTFN, .af = GPIO_AF1 },
};

int main(void)
{
    gpio_config_t pa5 = {
        .pin = {.port = GPIOA, GPIO_PIN_5},
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_init(&pa5);

    systick_init(8000000);
    systick_timeout_t blink;
    systick_timeout_start(&blink, 500);

    gpio_init_table(uart_pins, 2);
    uart_config_t uart = {
        .instance = USART2,
        .clock_hz = 8000000,
        .baudrate = 115200,
    };
    uart_init(&uart);

    uart_write_string(USART2, "Hello World\r\n");

    while(1)
    {
        if(systick_timeout_expired(&blink))
        {
            gpio_toggle(pa5.pin);
            systick_timeout_start(&blink, 500);
        }
    }
}