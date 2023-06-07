/***************************************************************************//**
 * @file
 * @brief ICM20648 Config
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

#ifndef SL_ICM20648_CONFIG_H
#define SL_ICM20648_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart signal=TX,RX,CLK> SL_ICM20648_SPI
// $[USART_SL_ICM20648_SPI]
#define SL_ICM20648_SPI_PERIPHERAL               USART3
#define SL_ICM20648_SPI_PERIPHERAL_NO            3

// USART3 TX on PC0
#define SL_ICM20648_SPI_TX_PORT                  gpioPortC
#define SL_ICM20648_SPI_TX_PIN                   0
#define SL_ICM20648_SPI_TX_LOC                   18

// USART3 RX on PC1
#define SL_ICM20648_SPI_RX_PORT                  gpioPortC
#define SL_ICM20648_SPI_RX_PIN                   1
#define SL_ICM20648_SPI_RX_LOC                   18

// USART3 CLK on PC2
#define SL_ICM20648_SPI_CLK_PORT                 gpioPortC
#define SL_ICM20648_SPI_CLK_PIN                  2
#define SL_ICM20648_SPI_CLK_LOC                  18

// [USART_SL_ICM20648_SPI]$

// <gpio> SL_ICM20648_SPI_CS
// $[GPIO_SL_ICM20648_SPI_CS]
#define SL_ICM20648_SPI_CS_PORT                  gpioPortC
#define SL_ICM20648_SPI_CS_PIN                   3

// [GPIO_SL_ICM20648_SPI_CS]$

// <gpio optional=true> SL_ICM20648_INT
// $[GPIO_SL_ICM20648_INT]
#define SL_ICM20648_INT_PORT                     gpioPortF
#define SL_ICM20648_INT_PIN                      12

// [GPIO_SL_ICM20648_INT]$

// <<< sl:end pin_tool >>>

#endif // SL_ICM20648_CONFIG_H
