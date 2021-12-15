/**
 * UART common utilities used by apps
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef ZAF_APPLICATIONUTILITIES_ZAF_UART_UTILS_H_
#define ZAF_APPLICATIONUTILITIES_ZAF_UART_UTILS_H_

#include <em_gpio.h>

/**
 * @brief Initializes UART0 and sets the specified tx and rx pins. Leaves UART disabled.
 * @param[in] txPort   Transmit port number
 * @param[in] txPin    Transmit pin number
 * @param[in] rxPort   Receive port number
 * @param[in] rxPin    Receive pin number
 */
void             /*RET Nothing */
ZAF_UART0_init(GPIO_Port_TypeDef txPort,
               unsigned int txPin,
               GPIO_Port_TypeDef rxPort,
               unsigned int rxPin);

/**
 * @brief Initializes UART1/USART1/EUSART1 and sets the specified tx and rx pins. Leaves UART/EUSART disabled.
 * @param[in] txPort   Transmit port number
 * @param[in] txPin    Transmit pin number
 * @param[in] rxPort   Receive port number
 * @param[in] rxPin    Receive pin number
 */
void             /*RET Nothing */
ZAF_UART1_init(GPIO_Port_TypeDef txPort,
               unsigned int txPin,
               GPIO_Port_TypeDef rxPort,
               unsigned int rxPin);

/**
 * @brief Enables UART0 and sets the specified baudrate.
 * @param[in] baudRate   Baud rate (e.g. 9600 => 9600baud/s, 115200 => 115200baud/s)
 * @param[in] bEnableTx  true: Tx enabled, false: Tx disabled
 * @param[in] bEnableRx  true: Rx enabled, false: Rx disabled
 */
void             /*RET Nothing */
ZAF_UART0_enable(uint32_t baudRate,
                 bool     bEnableTx,
                 bool     bEnableRx);

/**
 * @brief Enables UART1/EUSART1 and sets the specified baudrate.
 * @param[in] baudRate   Baud rate (e.g. 9600 => 9600baud/s, 115200 => 115200baud/s)
 * @param[in] bEnableTx  true: Tx enabled, false: Tx disabled
 * @param[in] bEnableRx  true: Rx enabled, false: Rx disabled
 */
void             /*RET Nothing */
ZAF_UART1_enable(uint32_t baudRate,
                 bool     bEnableTx,
                 bool     bEnableRx);

/**
 * @brief Sends array of bytes to UART0. Blocking
 * @param[in] pData    Pointer to array of bytes
 * @param[in] iLength  Length of array
 */
void          /*RET Nothing */
ZAF_UART0_tx_send(const uint8_t * pData,
                  uint32_t iLength);

/**
 * @brief Sends array of bytes to UART1/EUSART1. Blocking
 * @param[in] pData    Pointer to array of bytes
 * @param[in] iLength  Length of array
 */
void          /*RET Nothing */
ZAF_UART1_tx_send(const uint8_t * pData,
                  uint32_t iLength);

#endif /* ZAF_APPLICATIONUTILITIES_ZAF_UART_UTILS_H_ */
