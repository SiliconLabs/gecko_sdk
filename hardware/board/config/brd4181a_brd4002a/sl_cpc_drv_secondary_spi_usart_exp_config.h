/***************************************************************************//**
 * @file
 * @brief CPC SPI SECONDARY driver configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_CPC_DRV_SPI_USART_EXP_SECONDARY_CONFIG_H
#define SL_CPC_DRV_SPI_USART_EXP_SECONDARY_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> CPC-Secondary SPI Driver Configuration

// <h> Queues size configuration

// <o SL_CPC_DRV_SPI_EXP_RX_QUEUE_SIZE> Number of frame that can be queued in the driver receive queue
// <i> A greater number decreases the chances of retransmission due to dropped frames at the cost of memory footprint.
// <i> Default : 10
// <d> 10
#define SL_CPC_DRV_SPI_EXP_RX_QUEUE_SIZE               10

// <o SL_CPC_DRV_SPI_EXP_TX_QUEUE_SIZE> Number of frame that can be queued in the driver transmit queue
// <i> A greater number increases the transmission responsiveness at the cost of memory footprint.
// <i> Default : 10
// <d> 10
#define SL_CPC_DRV_SPI_EXP_TX_QUEUE_SIZE               10
// </h>

// <h> LDMA SYNCTRIG bit configuration
// <o SL_CPC_DRV_SPI_EXP_TX_AVAILABILITY_SYNCTRIG_CH> The LDMA SYNCTRIG bit number for the TX availability [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> Default : 7
// <d> 7
#define SL_CPC_DRV_SPI_EXP_TX_AVAILABILITY_SYNCTRIG_CH 6

// <o SL_CPC_DRV_SPI_EXP_CS_SYNCTRIG_PRS_CH> The LDMA SYNCTRIG bit number for the CS PRS channel [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> This bit number is tied to the equivalent PRS channel number. Keep that in mind if using PRS channels elsewhere in the project.
// <i> Default : 5
// <d> 5
#define SL_CPC_DRV_SPI_EXP_CS_SYNCTRIG_PRS_CH          5

// <o SL_CPC_DRV_SPI_EXP_TXC_SYNCTRIG_PRS_CH> The LDMA SYNCTRIG bit number for the TXC PRS channel [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> This bit number is tied to the equivalent PRS channel number. Keep that in mind if using PRS channels elsewhere in the project.
// <i> Default : 6
// <d> 6
#define SL_CPC_DRV_SPI_EXP_TXC_SYNCTRIG_PRS_CH         4

// </h>
// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_CPC_DRV_SPI_EXP_RX_IRQ
// $[GPIO_SL_CPC_DRV_SPI_EXP_RX_IRQ]
#define SL_CPC_DRV_SPI_EXP_RX_IRQ_PORT           gpioPortD
#define SL_CPC_DRV_SPI_EXP_RX_IRQ_PIN            2

// [GPIO_SL_CPC_DRV_SPI_EXP_RX_IRQ]$

// <usart signal=TX,RX,CLK,(CS)> SL_CPC_DRV_SPI_EXP
// $[USART_SL_CPC_DRV_SPI_EXP]
#define SL_CPC_DRV_SPI_EXP_PERIPHERAL            USART2
#define SL_CPC_DRV_SPI_EXP_PERIPHERAL_NO         2

// USART2 TX on PC00
#define SL_CPC_DRV_SPI_EXP_TX_PORT               gpioPortC
#define SL_CPC_DRV_SPI_EXP_TX_PIN                0

// USART2 RX on PC01
#define SL_CPC_DRV_SPI_EXP_RX_PORT               gpioPortC
#define SL_CPC_DRV_SPI_EXP_RX_PIN                1

// USART2 CLK on PC02
#define SL_CPC_DRV_SPI_EXP_CLK_PORT              gpioPortC
#define SL_CPC_DRV_SPI_EXP_CLK_PIN               2

// USART2 CS on PC03
#define SL_CPC_DRV_SPI_EXP_CS_PORT               gpioPortC
#define SL_CPC_DRV_SPI_EXP_CS_PIN                3

// [USART_SL_CPC_DRV_SPI_EXP]$
// <<< sl:end pin_tool >>>

#endif /* SL_CPC_DRV_SPI_EXP_SECONDARY_CONFIG_H */
