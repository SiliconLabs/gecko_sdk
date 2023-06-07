/***************************************************************************//**
 * @file
 * @brief MX25 flash shutdown
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

#ifndef  SL_MX25_FLASH_SHUTDOWN_H
#define  SL_MX25_FLASH_SHUTDOWN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include "em_device.h"
#include "sl_mx25_flash_shutdown_usart_config.h"

/***************************************************************************//**
 * @addtogroup mx25_flash_shutdown MX25 SPI Flash Shutdown
 * @brief  Provide a function to put the MX25 SPI flash into deep power down
 * mode to reduce power consumption.
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *    Put the MX25 SPI flash into deep power down mode.
 *
 * This function initializes SPI communication with the MX25 flash and sends
 * the deep power-down instruction, which sets the device to minimal
 * power consumption. The SPI communication is disabled to free the USART.
 ******************************************************************************/
void sl_mx25_flash_shutdown(void);

/**@}*/

#ifdef __cplusplus
}
#endif
#endif // SL_MX25_FLASH_SHUTDOWN_H
