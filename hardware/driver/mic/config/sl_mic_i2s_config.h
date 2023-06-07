/***************************************************************************//**
 * @file
 * @brief MIC_I2S config
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

#ifndef SL_MIC_I2S_CONFIG_H
#define SL_MIC_I2S_CONFIG_H

// <<< sl:start pin_tool >>>
// <usart capability=i2s signal=RX,CLK,CS> SL_MIC_I2S
// $[USART_SL_MIC_I2S]
#warning "Microphone I2S peripheral not configured"
// #define SL_MIC_I2S_PERIPHERAL     USART1
// #define SL_MIC_I2S_PERIPHERAL_NO  1

// #define SL_MIC_I2S_RX_PORT         gpioPortC
// #define SL_MIC_I2S_RX_PIN          7
// #define SL_MIC_I2S_RX_LOC          11

// #define SL_MIC_I2S_CLK_PORT        gpioPortC
// #define SL_MIC_I2S_CLK_PIN         8
// #define SL_MIC_I2S_CLK_LOC         11

// #define SL_MIC_I2S_CS_PORT         gpioPortC
// #define SL_MIC_I2S_CS_PIN          9
// #define SL_MIC_I2S_CS_LOC          11
// [USART_SL_MIC_I2S]$
// <<< sl:end pin_tool >>>

#endif // SL_MIC_I2S_CONFIG_H
