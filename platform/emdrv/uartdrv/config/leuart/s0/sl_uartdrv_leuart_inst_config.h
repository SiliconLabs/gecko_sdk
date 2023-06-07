/***************************************************************************//**
 * @file
 * @brief UARTDRV_LEUART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_UARTDRV_LEUART_INSTANCE_CONFIG_H
#define SL_UARTDRV_LEUART_INSTANCE_CONFIG_H

#include "em_leuart.h"
// <<< Use Configuration Wizard in Context Menu >>>

// <h> UART settings
// <o SL_UARTDRV_LEUART_INSTANCE_BAUDRATE> Baud rate
// <i> Default: 115200
#define SL_UARTDRV_LEUART_INSTANCE_BAUDRATE        115200

// <o SL_UARTDRV_LEUART_INSTANCE_PARITY> Parity mode to use
// <leuartNoParity=> No Parity
// <leuartEvenParity=> Even parity
// <leuartOddParity=> Odd parity
// <i> Default: leuartNoParity
#define SL_UARTDRV_LEUART_INSTANCE_PARITY          leuartNoParity

// <o SL_UARTDRV_LEUART_INSTANCE_STOP_BITS> Number of stop bits to use.
// <leuartStopbits1=> 1 stop bits
// <leuartStopbits2=> 2 stop bits
// <i> Default: leuartStopbits1
#define SL_UARTDRV_LEUART_INSTANCE_STOP_BITS       leuartStopbits1

// <o SL_UARTDRV_LEUART_INSTANCE_FLOW_CONTROL_TYPE> Flow control method
// <uartdrvFlowControlNone=> None
// <uartdrvFlowControlSw=> Software XON/XOFF
// <uartdrvFlowControlHw=> nRTS/nCTS hardware handshake
// <uartdrvFlowControlHwUart=> UART peripheral controls nRTS/nCTS
// <i> Default: uartdrvFlowControlHwUart
#define SL_UARTDRV_LEUART_INSTANCE_FLOW_CONTROL_TYPE uartdrvFlowControlHwUart

// <o SL_UARTDRV_LEUART_INSTANCE_RX_BUFFER_SIZE> Size of the receive operation queue
// <i> Default: 6
#define SL_UARTDRV_LEUART_INSTANCE_RX_BUFFER_SIZE 6

// <o SL_UARTDRV_LEUART_INSTANCE_TX_BUFFER_SIZE> Size of the transmit operation queue
// <i> Default: 6
#define SL_UARTDRV_LEUART_INSTANCE_TX_BUFFER_SIZE 6
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <leuart signal=TX,RX> SL_UARTDRV_LEUART_INSTANCE
// $[LEUART_SL_UARTDRV_LEUART_INSTANCE]
#warning "UARTDRV LEUART peripheral not configured"
// #define SL_UARTDRV_LEUART_INSTANCE_PERIPHERAL        LEUART0
// #define SL_UARTDRV_LEUART_INSTANCE_PERIPHERAL_NO     0

// #define SL_UARTDRV_LEUART_INSTANCE_ROUTE_LOC         0

// #define SL_UARTDRV_LEUART_INSTANCE_TX_PORT           gpioPortA
// #define SL_UARTDRV_LEUART_INSTANCE_TX_PIN            0

// #define SL_UARTDRV_LEUART_INSTANCE_RX_PORT           gpioPortA
// #define SL_UARTDRV_LEUART_INSTANCE_RX_PIN            1
// [LEUART_SL_UARTDRV_LEUART_INSTANCE]$

// <gpio> SL_UARTDRV_LEUART_INSTANCE_CTS
// $[GPIO_SL_UARTDRV_LEUART_INSTANCE_CTS]
// #define SL_UARTDRV_LEUART_INSTANCE_CTS_PORT           gpioPortA
// #define SL_UARTDRV_LEUART_INSTANCE_CTS_PIN            2
// [GPIO_SL_UARTDRV_LEUART_INSTANCE_CTS]$

// <gpio> SL_UARTDRV_LEUART_INSTANCE_RTS
// $[GPIO_SL_UARTDRV_LEUART_INSTANCE_RTS]
// #define SL_UARTDRV_LEUART_INSTANCE_RTS_PORT           gpioPortA
// #define SL_UARTDRV_LEUART_INSTANCE_RTS_PIN            3
// [GPIO_SL_UARTDRV_LEUART_INSTANCE_RTS]$
// <<< sl:end pin_tool >>>
#endif // SL_UARTDRV_LEUART_INSTANCE_CONFIG_H
