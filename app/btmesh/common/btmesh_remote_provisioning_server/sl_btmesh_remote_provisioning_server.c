/***************************************************************************//**
 * @file
 * @brief BT Mesh Remote Provisioning Server Component
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

#include "sl_btmesh_api.h"
#include "sl_bt_api.h"
#include "sl_status.h"

#include "app_assert.h"

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_remote_provisioning_server_config.h"
#include "sl_btmesh_remote_provisioning_server.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup remote_provisioning_server BT Mesh Remote Provisioning Server
 * @brief BT Mesh Remote provisioning server component implementation
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * Initialize Remote Provisioning Server component
 ******************************************************************************/
static void mesh_remote_provisioning_server_init(void);

/*******************************************************************************
 * Handle Remote Provisioning Server events
 ******************************************************************************/
void sli_btmesh_handle_remote_provisioning_server_on_event(const sl_btmesh_msg_t *evt)
{
  if (NULL == evt) {
    return;
  }

  // Handle events
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        mesh_remote_provisioning_server_init();
      }
      break;

    case sl_btmesh_evt_node_provisioned_id:
      mesh_remote_provisioning_server_init();
      break;

    default:
      break;
  }
}

static void mesh_remote_provisioning_server_init(void)
{
  sl_status_t sc = sl_btmesh_remote_provisioning_server_init();
  app_assert_status_f(sc, "Failed to initialize remote provisioning server");

  sc = sl_btmesh_remote_provisioning_server_set_default_bearer(SL_BTMESH_REMOTE_PROVISIONING_SERVER_BEARER_TYPE);
  app_assert_status_f(sc, "Failed to set default bearer");

  log_info("Remote provisining server initialized" NL);
}

/** @} (end addtogroup remote_provisioning_server) */
