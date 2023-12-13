/***************************************************************************//**
 * @file
 * @brief CPC configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_CPC_PRIMARY_CONFIG_H
#define SL_CPC_PRIMARY_CONFIG_H

// <h>CPC Primary Configuration

// <q SL_CPC_PRIMARY_FIRMWARE_UPGRADE_SUPPORT_ENABLED> Enable Firmware upgrade support
// <i> Default: 1
#define SL_CPC_PRIMARY_FIRMWARE_UPGRADE_SUPPORT_ENABLED    0

// <q SL_CPC_PRIMARY_FIRMWARE_UPGRADE_RECOVERY_PINS_SUPPORT_ENABLED> Enable bootloader recovery pins
// <i> Default: 0
#define SL_CPC_PRIMARY_FIRMWARE_UPGRADE_RECOVERY_PINS_SUPPORT_ENABLED 0

// </h>

// <<< end of configuration section >>>

#if (SL_CPC_PRIMARY_FIRMWARE_UPGRADE_RECOVERY_PINS_SUPPORT_ENABLED >= 1)

// <<< sl:start pin_tool >>>
// <gpio> SL_CPC_DRV_SPI_INSTANCE_RESET
// $[GPIO_SL_CPC_DRV_SPI_INSTANCE_RESET]
#warning "CPC Bootloader RESET not configured"
// #define SL_CPC_DRV_SPI_INSTANCE_RESET_PORT               gpioPortB
// #define SL_CPC_DRV_SPI_INSTANCE_RESET_PIN                0
// [GPIO_SL_CPC_DRV_SPI_INSTANCE_RESET]$

// <gpio> SL_CPC_DRV_SPI_INSTANCE_WAKE
// $[GPIO_SL_CPC_DRV_SPI_INSTANCE_WAKE]
#warning "CPC Bootloader WAKE not configured"
// #define SL_CPC_DRV_SPI_INSTANCE_WAKE_PORT                gpioPortB
// #define SL_CPC_DRV_SPI_INSTANCE_WAKE_PIN                 0
// [GPIO_SL_CPC_DRV_SPI_INSTANCE_WAKE]$
// <<< sl:end pin_tool >>>

#endif

#endif /* SL_CPC_CONFIG_H */
