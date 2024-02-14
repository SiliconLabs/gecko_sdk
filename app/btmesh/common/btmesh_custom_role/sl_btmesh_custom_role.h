/***************************************************************************//**
 * @file
 * @brief BT Mesh Custom Role Initializer
 *******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTMESH_CUSTOM_ROLE_H
#define SL_BTMESH_CUSTOM_ROLE_H

// -----------------------------------------------------------------------------
// Includes
#include "sl_bt_api.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @defgroup custom_role
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup custom_role
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Function declarations

/***************************************************************************//**
 * Handle BLE events for the mesh custom role.
 *
 * This function is called automatically after enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_bt_custom_role_on_event(sl_bt_msg_t* evt);

// -----------------------------------------------------------------------------
// Event / callback declarations

/***************************************************************************//**
 * Called on boot event and the application is able to override this function
 * to initialize the device as a provisioner or as a provisionee.
 *
 * The application should call one of the following BT Mesh stack initializer APIs
 * based on implementation-specific logic:
 * - sl_btmesh_node_init
 * - sl_btmesh_node_init_oob
 * - sl_btmesh_prov_init
 *
 * This is a callback (weak function) which can be implemented in the application.
 * @note If no implementation is provided in the application, then the default
 *   weak implementation will be an empty function, and the application shall
 *   handle the sl_bt_evt_system_boot_id event by calling the mentioned APIs.
 ******************************************************************************/
void sl_btmesh_custom_role_init(void);

/** @} (end addtogroup custom_role) */

#ifdef __cplusplus
}
#endif

#endif /* SL_BTMESH_CUSTOM_ROLE_H */
