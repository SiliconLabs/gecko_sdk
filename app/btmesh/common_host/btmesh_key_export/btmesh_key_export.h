/**************************************************************************//**
* @file
* @brief BT Mesh Key export functionality
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

#ifndef BTMESH_KEY_EXPORT_H
#define BTMESH_KEY_EXPORT_H

#include <stdbool.h>
#include "sl_btmesh_api.h"

/**************************************************************************//**
 * @brief Set the output file name
 *
 * @param name File name
 *****************************************************************************/
void btmesh_key_export_set_file_name(char* name);

/**************************************************************************//**
 * @brief Start the key export task
 *
 *****************************************************************************/
void btmesh_key_export_start();

/**************************************************************************//**
 * @brief Check if the key export task is idle
 *
 * @return true - idle
 * @return false - running
 *****************************************************************************/
bool btmesh_key_export_is_idle();

/**************************************************************************//**
 * @brief Key export task
 *
 *****************************************************************************/
void btmesh_key_export_task();

/**************************************************************************//**
 * @brief Key export event handler
 *
 * @param evt Event coming from the Bluetooth Mesh stack
 *****************************************************************************/
void btmesh_key_export_on_event(sl_btmesh_msg_t *evt);

#endif //BTMESH_KEY_EXPORT_H
