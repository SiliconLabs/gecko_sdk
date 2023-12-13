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

#ifndef SL_CPC_DRV_SPI_EUSART_INSTANCE_SECONDARY_CONFIG_H
#define SL_CPC_DRV_SPI_EUSART_INSTANCE_SECONDARY_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> CPC-Secondary SPI Driver Configuration

// <h> Queues size configuration

// <o SL_CPC_DRV_SPI_INSTANCE_RX_QUEUE_SIZE> Number of frame that can be queued in the driver receive queue
// <i> A greater number decreases the chances of retransmission due to dropped frames at the cost of memory footprint
// <i> Default : 10
// <d> 10
#define SL_CPC_DRV_SPI_INSTANCE_RX_QUEUE_SIZE              10

// <o SL_CPC_DRV_SPI_INSTANCE_TX_QUEUE_SIZE> Number of frame that can be queued in the driver transmit queue
// <i> A greater number increases the transmission responsiveness at the cost of memory footprint
// <i> Default : 10
// <d> 10
#define SL_CPC_DRV_SPI_INSTANCE_TX_QUEUE_SIZE              10
// </h>

// <h> LDMA SYNCTRIG bit configuration
// <o SL_CPC_DRV_SPI_INSTANCE_TX_AVAILABILITY_SYNCTRIG_CH> The LDMA SYNCTRIG bit number for the TX availability [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> Default : 7
// <d> 7
#define SL_CPC_DRV_SPI_INSTANCE_TX_AVAILABILITY_SYNCTRIG_CH 6

// <o SL_CPC_DRV_SPI_INSTANCE_CS_SYNCTRIG_PRS_CH> The LDMA SYNCTRIG bit number for the CS PRS channel [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> This bit number is tied to the equivalent PRS channel number. Keep that in mind if using PRS channels elsewhere in the project.
// <i> Default : 5
// <d> 5
#define SL_CPC_DRV_SPI_INSTANCE_CS_SYNCTRIG_PRS_CH          5

// <o SL_CPC_DRV_SPI_INSTANCE_TXC_SYNCTRIG_PRS_CH> The LDMA SYNCTRIG bit number for the TXC PRS channel [bit] <0-7>
// <i> Specify which SYNCTRIG bit is used. Modify this value to avoid collisions if specific LDMA SYNCTRIG bits need to be used elsewhere in the project.
// <i> This bit number is tied to the equivalent PRS channel number. Keep that in mind if using PRS channels elsewhere in the project.
// <i> Default : 6
// <d> 6
#define SL_CPC_DRV_SPI_INSTANCE_TXC_SYNCTRIG_PRS_CH         4
// </h>

// <h> Chip Select PRS Routing
// <o SL_CPC_DRV_SPI_INSTANCE_CS_EXTI_NUMBER> The Chip Select input to EXTernal Interrupt number <0-7>
// <i> The CS input needs to be routed to a PRS channel in order to manipulate its LDMA SYNCTRIG bit.
// <i> Modify this value to avoid collisions if any specific EXTI number needs to be used elsewhere in the project.
// <i> Note that only EXTI0..7 can be used as input for a PRS channel, and only pins Px0..7 can be routed to those.
// <i> Default : 0 (pin0..4 of any port)
// <d> 0
#define SL_CPC_DRV_SPI_INSTANCE_CS_EXTI_NUMBER              0
// </h>

// </h>
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_CPC_DRV_SPI_INSTANCE_RX_IRQ
// $[GPIO_SL_CPC_DRV_SPI_INSTANCE_RX_IRQ]
#warning "CPC SPI IRQ not configured"
// #define SL_CPC_DRV_SPI_INSTANCE_RX_IRQ_PORT                gpioPortB
// #define SL_CPC_DRV_SPI_INSTANCE_RX_IRQ_PIN                 14
// [GPIO_SL_CPC_DRV_SPI_INSTANCE_RX_IRQ]$

// <eusart signal=TX,RX,SCLK,(CS)> SL_CPC_DRV_SPI_INSTANCE
// $[EUSART_SL_CPC_DRV_SPI_INSTANCE]
#warning "CPC EUSART peripheral not configured"
// #define SL_CPC_DRV_SPI_INSTANCE_PERIPHERAL                 EUSART0
// #define SL_CPC_DRV_SPI_INSTANCE_PERIPHERAL_NO              0
//
// #define SL_CPC_DRV_SPI_INSTANCE_TX_PORT                    gpioPortD
// #define SL_CPC_DRV_SPI_INSTANCE_TX_PIN                     13
//
// #define SL_CPC_DRV_SPI_INSTANCE_RX_PORT                    gpioPortD
// #define SL_CPC_DRV_SPI_INSTANCE_RX_PIN                     14
//
// #define SL_CPC_DRV_SPI_INSTANCE_SCLK_PORT                  gpioPortD
// #define SL_CPC_DRV_SPI_INSTANCE_SCLK_PIN                   15
//
// #define SL_CPC_DRV_SPI_INSTANCE_CS_PORT                    gpioPortB
// #define SL_CPC_DRV_SPI_INSTANCE_CS_PIN                     11
// [EUSART_SL_CPC_DRV_SPI_INSTANCE]$
// <<< sl:end pin_tool >>>

#endif /* SL_CPC_DRV_SPI_INSTANCE_SECONDARY_CONFIG_H */
