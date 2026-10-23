#include "driver_uart.h"

/*
 * Clock control
 */

void uart_clock_enable(USART_TypeDef *instance)
{
    if      (instance == USART1) RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    else if (instance == USART2) RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    else if (instance == USART3) RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    else if (instance == USART4) RCC->APB1ENR |= RCC_APB1ENR_USART4EN;
}

void uart_clock_disable(USART_TypeDef *instance)
{
    if      (instance == USART1) RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
    else if (instance == USART2) RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
    else if (instance == USART3) RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
    else if (instance == USART4) RCC->APB1ENR &= ~RCC_APB1ENR_USART4EN;
}

/*
 * Configuration
 */

void uart_set_enabled(USART_TypeDef *instance, bool enabled)
{

}

void uart_set_mode(USART_TypeDef *instance, uart_mode_e mode)
{

}

void uart_set_parity(USART_TypeDef *instance, uart_parity_e parity)
{

}

void uart_set_stop_bits(USART_TypeDef *instance, uart_stop_bits_e stop_bits)
{

}

void uart_set_baudrate(USART_TypeDef *instance, uint32_t clock_hz, uint32_t baudrate)
{

}

/*
 * Init and De-init
 */

void uart_init(const uart_config_t *config)
{
    USART_TypeDef *instance = config->instance;
    uint32_t usart_cr1 = 0;

    uart_clock_enable(instance);        /* disabled while configuring */

    instance->CR1 = 0;
}

void uart_deinit(USART_TypeDef *instance);

/*
 * Write (blocking)
 */

void uart_write_byte(USART_TypeDef *instance, uint8_t byte);
void uart_write(USART_TypeDef *instance, const uint8_t *data, uint32_t len);
void uart_write_string(USART_TypeDef *instance, const char *str);
void uart_flush(USART_TypeDef *instance);

/*
 * Read (non-blocking)
 */

bool uart_read_byte(USART_TypeDef *instance, uint8_t *byte);