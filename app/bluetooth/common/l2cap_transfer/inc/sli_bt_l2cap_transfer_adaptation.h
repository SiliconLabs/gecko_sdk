/***************************************************************************//**
 * @file
 * @brief L2CAP transfer internal interface for RTOS adaptation
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
#ifndef SLI_BT_L2CAP_TRANSFER_ADAPTATION_H
#define SLI_BT_L2CAP_TRANSFER_ADAPTATION_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
 * Internal L2CAP transfer system init
 * Initialize linked lists which are storing transfers
 *****************************************************************************/
void sli_bt_l2cap_transfer_adaptation_init(void);

/**************************************************************************//**
 * Acquire Mutex
 *****************************************************************************/
bool sli_bt_l2cap_transfer_adaptation_acquire(void);

/**************************************************************************//**
 * Release Mutex
 *****************************************************************************/
void sli_bt_l2cap_transfer_adaptation_release(void);

/**************************************************************************//**
 * Internal function allows the cyclic process to continue, in case of xRTOS
 * scheduling.
 *****************************************************************************/
void sli_bt_l2cap_transfer_adaptation_proceed(void);

#ifdef __cplusplus
};
#endif

#endif // SLI_BT_L2CAP_TRANSFER_ADAPTATION_H
