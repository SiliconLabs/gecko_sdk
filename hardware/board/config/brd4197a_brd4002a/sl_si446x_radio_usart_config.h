/***************************************************************************//**
 * @file
 * @brief SL_SI446X_RADIO_USART Config
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_SI446X_RADIO_CONFIG_H
#define SL_SI446X_RADIO_CONFIG_H

// <<< sl:start pin_tool >>>
// {usart signal=TX,RX,CLK} SL_SI446X_RADIO
// [USART_SL_SI446X_RADIO]
#define SL_SI446X_RADIO_PERIPHERAL               USART0
#define SL_SI446X_RADIO_PERIPHERAL_NO            0

// USART0 TX on PC01
#define SL_SI446X_RADIO_TX_PORT                  gpioPortC
#define SL_SI446X_RADIO_TX_PIN                   1

// USART0 RX on PC02
#define SL_SI446X_RADIO_RX_PORT                  gpioPortC
#define SL_SI446X_RADIO_RX_PIN                   2

// USART0 CLK on PC03
#define SL_SI446X_RADIO_CLK_PORT                 gpioPortC
#define SL_SI446X_RADIO_CLK_PIN                  3

// [USART_SL_SI446X_RADIO]

// <gpio> SL_SI446X_RADIO_CS
// $[GPIO_SL_SI446X_RADIO_CS]
#define SL_SI446X_RADIO_CS_PORT                  gpioPortA
#define SL_SI446X_RADIO_CS_PIN                   5

// [GPIO_SL_SI446X_RADIO_CS]$

// <gpio> SL_SI446X_RADIO_INT
// $[GPIO_SL_SI446X_RADIO_INT]
#define SL_SI446X_RADIO_INT_PORT                 gpioPortA
#define SL_SI446X_RADIO_INT_PIN                  6

// [GPIO_SL_SI446X_RADIO_INT]$

// <gpio> SL_SI446X_RADIO_SDN
// $[GPIO_SL_SI446X_RADIO_SDN]
#define SL_SI446X_RADIO_SDN_PORT                 gpioPortA
#define SL_SI446X_RADIO_SDN_PIN                  7

// [GPIO_SL_SI446X_RADIO_SDN]$

// <<< sl:end pin_tool >>>

#endif // SL_SI446X_RADIO_CONFIG_H
