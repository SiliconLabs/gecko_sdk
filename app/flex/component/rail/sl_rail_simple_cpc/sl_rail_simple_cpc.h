/***************************************************************************//**
 * @file
 * @brief Simple RAIL CPC for NCP projects Interface for CPC
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

#ifndef SL_RAIL_SIMPLE_CPC_H
#define SL_RAIL_SIMPLE_CPC_H

#include <stdint.h>
#include "sl_status.h"

/**************************************************************************//**
 * Simple Comm Init
 *****************************************************************************/
void sl_rail_simple_cpc_init(void);

/**************************************************************************//**
 * Step function (used in CPC mode)
 *****************************************************************************/
void sl_rail_simple_cpc_step(void);

/**************************************************************************//**
 * Transmit function
 *****************************************************************************/
void sl_rail_simple_cpc_transmit(uint32_t len, uint8_t *data);

/**************************************************************************//**
 * Transmit completed callback
 *****************************************************************************/
void sl_rail_simple_cpc_transmit_cb(sl_status_t status);

/**************************************************************************//**
 * Receive function (used in UART mode)
 *****************************************************************************/
void sl_rail_simple_cpc_receive(void);

/**************************************************************************//**
 * Receive completed callback
 *****************************************************************************/
void sl_rail_simple_cpc_receive_cb(sl_status_t status, uint32_t len, uint8_t *data);

/**************************************************************************//**
 * OS initialization function - if the OS is present
 *****************************************************************************/
void sl_rail_simple_cpc_os_task_init(void);

/**************************************************************************//**
 * Function to trigger the OS task to proceed - if the OS is present
 *****************************************************************************/
void sl_rail_simple_cpc_os_task_proceed(void);

#endif // SL_RAIL_SIMPLE_CPC_H
