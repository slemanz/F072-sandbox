#ifndef INC_DRIVER_UART_H_
#define INC_DRIVER_UART_H_

#include <stdint.h>
#include <stdbool.h>
#include "stm32f0xx.h"

/**
 * @brief UART direction
 */
typedef enum
{
    UART_MODE_TX_RX = 0,    /**< Transmit and receive */
    UART_MODE_TX,           /**< Transmit only        */
    UART_MODE_RX            /**< Receive only         */
}uart_mode_e;

/**
 * @brief UART parity
 */
typedef enum
{
    UART_PARITY_NONE = 0,   /**< No parity   */
    UART_PARITY_EVEN,       /**< Even parity */
    UART_PARITY_ODD         /**< Odd parity  */
}uart_parity_e;

/**
 * @brief UART stop bits
 */
typedef enum
{
    UART_STOP_BITS_1 = 0,   /**< 1 stop bit  */
    UART_STOP_BITS_2        /**< 2 stop bits */
}uart_stop_bits_e;

/**
 * @brief UART configuration (always 8 data bits).
 */
typedef struct
{
    USART_TypeDef    *port;         /**< USART1..USART4                  */
    uint32_t          clock_hz;     /**< Peripheral clock (PCLK) in Hz   */
    uint32_t          baudrate;     /**< Baudrate. Ex: 115200            */
    uart_mode_e       mode;         /**< Direction                       */
    uart_parity_e     parity;       /**< Parity                          */
    uart_stop_bits_e  stop_bits;    /**< Stop bits                       */
}uart_config_t;

/********************************************************************************************
 *                              APIs supported by this driver
 *                  for more information check the function definitions
 ********************************************************************************************/

/*
 * Clock control
 */

void uart_clock_enable(USART_TypeDef *port);
void uart_clock_disable(USART_TypeDef *port);

/*
 * Init and De-init
 */

void uart_init(const uart_config_t *config);
void uart_deinit(USART_TypeDef *port);

/*
 * Write (blocking)
 */

void uart_write_byte(USART_TypeDef *port, uint8_t byte);
void uart_write(USART_TypeDef *port, const uint8_t *data, uint32_t len);
void uart_write_string(USART_TypeDef *port, const char *str);
void uart_flush(USART_TypeDef *port);

/*
 * Read (non-blocking)
 */

bool uart_read_byte(USART_TypeDef *port, uint8_t *byte);

#endif /* INC_DRIVER_UART_H_ */