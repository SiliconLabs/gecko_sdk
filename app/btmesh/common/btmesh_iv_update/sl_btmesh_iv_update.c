/***************************************************************************//**
 * @file
 * @brief Automatic IV Update implementation
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

#include <stdbool.h>

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_iv_update.h"
#include "sl_btmesh_iv_update_config.h"

#include "sl_btmesh_iv_update_age_backup.h"
#include "sl_btmesh_iv_update_by_age.h"
#include "sl_btmesh_iv_update_by_seq_num.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup iv_update
 * @{
 ******************************************************************************/

/***************************************************************************//**
 *  Handling of mesh iv_update related events.
 *  @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_iv_update_on_event(sl_btmesh_msg_t* evt)
{
#if SL_BTMESH_IV_UPDATE_AGE_BACKUP_ENABLE
  sl_btmesh_iv_update_age_backup_on_event(evt);
#endif
#if SL_BTMESH_IV_UPDATE_BY_AGE
  sl_btmesh_iv_update_by_age_on_event(evt);
#endif
#if SL_BTMESH_IV_UPDATE_BY_SEQ_NUM
  sl_btmesh_iv_update_by_seq_num_on_event(evt);
#endif
#if SL_BTMESH_IV_UPDATE_AUTO_RECOVERY
  if (SL_BT_MSG_ID(evt->header) == sl_btmesh_evt_node_ivrecovery_needed_id) {
    sl_btmesh_node_set_ivrecovery_mode(true);
  }
#endif
}

/** @} (end addtogroup iv_update) */
