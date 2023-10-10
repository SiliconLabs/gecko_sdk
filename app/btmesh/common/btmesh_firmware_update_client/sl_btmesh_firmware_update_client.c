/***************************************************************************//**
 * @file
 * @brief BT Mesh Firmware Update Client
 *
 * The firmware update client application model performs the initialization only
 * because the distributor stack class calls the necessary firmware update client
 * stack class functions inside the BT Mesh stack therefore no additional logic
 * is necessary at application level.
 *
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

#include <stdbool.h>
#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "app_assert.h"
#include "app_timer.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#include "sl_btmesh_firmware_update_client.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup fw_upd_client BT Mesh Firmware Update Client
 * @{
 ******************************************************************************/
static void sl_btmesh_firmware_update_client_element_init(uint16_t elem_index)
{
  sl_status_t sc = sl_btmesh_fw_update_client_init(elem_index);

  app_assert_status_f(sc, "Failed to init Firmware Update Client");
}

static void sl_btmesh_firmware_update_client_init(void)
{
  sl_btmesh_firmware_update_client_element_init(BTMESH_FIRMWARE_UPDATE_CLIENT_GROUP_MAIN_ELEM_INDEX);
}

void sl_btmesh_firmware_update_client_on_event(const sl_btmesh_msg_t *const evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id: {
      sl_btmesh_firmware_update_client_init();
      break;
    }
    case sl_btmesh_evt_node_initialized_id: {
      if (0 != evt->data.evt_node_initialized.provisioned) {
        sl_btmesh_firmware_update_client_init();
      }
      break;
    }
  }
}

/** @} end fw_upd_client */
