/***************************************************************************//**
 * @file
 * @brief SL_SI446X_RADIO_USART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_SI446X_RADIO_CONFIG_H
#define SL_SI446X_RADIO_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX,CLK> SL_SI446X_RADIO
// $[USART_SL_SI446X_RADIO]
#define SL_SI446X_RADIO_PERIPHERAL               USART1
#define SL_SI446X_RADIO_PERIPHERAL_NO            1

// USART1 TX on PC6
#define SL_SI446X_RADIO_TX_PORT                  gpioPortC
#define SL_SI446X_RADIO_TX_PIN                   6
#define SL_SI446X_RADIO_TX_LOC                   11

// USART1 RX on PC7
#define SL_SI446X_RADIO_RX_PORT                  gpioPortC
#define SL_SI446X_RADIO_RX_PIN                   7
#define SL_SI446X_RADIO_RX_LOC                   11

// USART1 CLK on PC8
#define SL_SI446X_RADIO_CLK_PORT                 gpioPortC
#define SL_SI446X_RADIO_CLK_PIN                  8
#define SL_SI446X_RADIO_CLK_LOC                  11

// [USART_SL_SI446X_RADIO]$

// <gpio> SL_SI446X_RADIO_CS
// $[GPIO_SL_SI446X_RADIO_CS]
#define SL_SI446X_RADIO_CS_PORT                  gpioPortD
#define SL_SI446X_RADIO_CS_PIN                   10

// [GPIO_SL_SI446X_RADIO_CS]$

// <gpio> SL_SI446X_RADIO_INT
// $[GPIO_SL_SI446X_RADIO_INT]
#define SL_SI446X_RADIO_INT_PORT                 gpioPortD
#define SL_SI446X_RADIO_INT_PIN                  11

// [GPIO_SL_SI446X_RADIO_INT]$

// <gpio> SL_SI446X_RADIO_SDN
// $[GPIO_SL_SI446X_RADIO_SDN]
#define SL_SI446X_RADIO_SDN_PORT                 gpioPortD
#define SL_SI446X_RADIO_SDN_PIN                  12

// [GPIO_SL_SI446X_RADIO_SDN]$

// <<< sl:end pin_tool >>>

#endif // SL_SI446X_RADIO_CONFIG_H
