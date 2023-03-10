/***************************************************************************//**
 * @file
 * @brief BT Mesh Advertisement Extension Client
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

#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#include "app_assert.h"

#include "sl_btmesh_ae_client.h"

/***************************************************************************//**
 * @addtogroup ae_client BT Mesh Advertisement Extension Client
 * @{
 ******************************************************************************/
void sl_btmesh_ae_client_on_event(const sl_btmesh_msg_t *const evt)
{
  sl_status_t sc;
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_provisioned_id: {
      sc = sl_btmesh_silabs_config_client_init();
      app_assert_status_f(sc, "Failed to init AE client");
      break;
    }
    case sl_btmesh_evt_node_initialized_id: {
      if (0 != evt->data.evt_node_initialized.provisioned) {
        sc = sl_btmesh_silabs_config_client_init();
        app_assert_status_f(sc, "Failed to init AE client");
      }
      break;
    }
  }
}

/** @} end ae_client */
