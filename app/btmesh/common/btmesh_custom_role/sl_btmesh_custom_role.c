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

// -----------------------------------------------------------------------------
// Includes

#include "sl_bt_api.h"
#include "sl_btmesh_custom_role.h"
#include "sl_common.h"

/***************************************************************************//**
 * @addtogroup btmesh_custom_role
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Public function definitions

// Handle BLE events for the mesh custom role
void sl_bt_custom_role_on_event(sl_bt_msg_t* evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      sl_btmesh_custom_role_init();
      break;
    default:
      break;
  }
}

// -----------------------------------------------------------------------------
// Event / callback definitions

// Called on boot event and the application is able to override this function
// to initialize the device as a provisioner or as a provisionee.
SL_WEAK void sl_btmesh_custom_role_init(void)
{
}

/** @} (end addtogroup btmesh_custom_role) */
