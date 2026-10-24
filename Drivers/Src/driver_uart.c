#include "driver_uart.h"

/*
 * Private Helpers
 */

static bool uart_is_enabled(USART_TypeDef *instance)
{
    return (instance->CR1 & USART_CR1_UE) != 0;
}

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
    if(enabled)
    {
        instance->CR1 |= USART_CR1_UE;
    }else
    {
        instance->CR1 &= ~USART_CR1_UE;
    }
}

void uart_set_mode(USART_TypeDef *instance, uart_mode_e mode)
{
    instance->CR1 &= ~(USART_CR1_TE | USART_CR1_RE);

    if(mode != UART_MODE_RX) instance->CR1 |= USART_CR1_TE;
    if(mode != UART_MODE_TX) instance->CR1 |= USART_CR1_RE;
}

void uart_set_parity(USART_TypeDef *instance, uart_parity_e parity)
{
    bool uart_was_enabled = uart_is_enabled(instance);
    uart_set_enabled(instance, false);

    instance->CR1 &= ~(USART_CR1_PCE | USART_CR1_PS | USART_CR1_M0);

    if(parity != UART_PARITY_NONE)
    {
        instance->CR1 |= USART_CR1_PCE | USART_CR1_M0;
    }
    if(parity == UART_PARITY_ODD)
    {
        instance->CR1 |= USART_CR1_PS;
    }

    uart_set_enabled(instance, uart_was_enabled);
}

void uart_set_stop_bits(USART_TypeDef *instance, uart_stop_bits_e stop_bits)
{
    bool uart_was_enabled = uart_is_enabled(instance);
    uart_set_enabled(instance, false);

    instance->CR2 &= ~USART_CR2_STOP;

    if(stop_bits == UART_STOP_BITS_2)
    {
        instance->CR2 |= USART_CR2_STOP_1;
    }

    uart_set_enabled(instance, uart_was_enabled);
}

void uart_set_baudrate(USART_TypeDef *instance, uint32_t clock_hz, uint32_t baudrate)
{
    if(baudrate == 0) return;

    bool uart_was_enabled = uart_is_enabled(instance);
    uart_set_enabled(instance, false);

    instance->BRR = (clock_hz + (baudrate / 2U)) / baudrate; /* oversampling 16, rounded */

    uart_set_enabled(instance, uart_was_enabled);
}

/*
 * Init and De-init
 */

void uart_init(const uart_config_t *config)
{
    USART_TypeDef *instance = config->instance;

    uart_clock_enable(instance);

    uart_set_enabled(instance, false);

    uart_set_mode(instance, config->mode);
    uart_set_parity(instance, config->parity);
    uart_set_stop_bits(instance, config->stop_bits);
    uart_set_baudrate(instance, config->clock_hz, config->baudrate);

    uart_set_enabled(instance, true);
}

void uart_deinit(USART_TypeDef *instance)
{
    instance->CR1 = 0;
    uart_clock_disable(instance);
}

/*
 * Write (blocking)
 */

void uart_write_byte(USART_TypeDef *instance, uint8_t byte)
{
    while(!(instance->ISR & USART_ISR_TXE))
    {
        /* wait transmit register empty */
    } 
    instance->TDR = byte;
}

void uart_write(USART_TypeDef *instance, const uint8_t *data, uint32_t len)
{
    for(uint32_t i = 0; i < len; i++)
    {
        uart_write_byte(instance, data[i]);
    }
}

void uart_write_string(USART_TypeDef *instance, const char *str)
{
    while(*str != '\0')
    {
        uart_write_byte(instance, (uint8_t)*str);
        str++;
    }
}

void uart_flush(USART_TypeDef *instance)
{
    while(!(instance->ISR & USART_ISR_TC))
    {
        /* wait transmission complete */
    } 
}

/*
 * Read (non-blocking)
 */

bool uart_read_byte(USART_TypeDef *instance, uint8_t *byte)
{
    if(instance->ISR & USART_ISR_ORE)
    {
        instance->ICR = USART_ICR_ORECF;
    }

    if(!(instance->ISR & USART_ISR_RXNE))
    {
        return false;
    }

    *byte = (uint8_t)instance->RDR;
    return true;
}