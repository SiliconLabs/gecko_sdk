/***************************************************************************//**
 * @file
 * @brief Provisioner initializer
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

#ifndef SL_BTMESH_PROVISIONER_H
#define SL_BTMESH_PROVISIONER_H

#include "sl_btmesh_api.h"
#include "sl_btmesh_provisioner_config.h"

/***************************************************************************//**
 * @defgroup provisioner
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup provisioner
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * This function is called after the sl_btmesh_prov_init() function.
 *
 * @param[in] result return value of the function call
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 ******************************************************************************/
void sl_btmesh_provisioner_on_init(sl_status_t result);

/***************************************************************************//**
 * Handle BLE events for the provisioner.
 *
 * This function is called automatically after enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_bt_provisioner_on_event(sl_bt_msg_t* evt);

/** @} (end addtogroup provisioner) */

#endif /* SL_BTMESH_PROVISIONEE_H */
