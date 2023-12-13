/**
 * @file
 * Zniffer Configuration
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef ZNIFFER_CONFIG_H
#define ZNIFFER_CONFIG_H

#include <em_gpio.h>

// <<< sl:start pin_tool >>>

// <usart signal=TX,RX> ZNIFFER

// $[USART_ZNIFFER]
#define ZNIFFER_PERIPHERAL     USART0
#define ZNIFFER_PERIPHERAL_NO  0

#define ZNIFFER_TX_PORT        gpioPortA
#define ZNIFFER_TX_PIN         8

#define ZNIFFER_RX_PORT        gpioPortA
#define ZNIFFER_RX_PIN         9
// [USART_ZNIFFER]$

// <<< sl:end pin_tool >>>

#endif // ZNIFFER_CONFIG_H
