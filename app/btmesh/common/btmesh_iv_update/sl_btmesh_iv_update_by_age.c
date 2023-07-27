/***************************************************************************//**
 * @file
 * @brief Automatic IV Update by age implementation
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

#include "em_common.h"
#include "sl_status.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_btmesh_dcd.h"

#include <stdbool.h>
#include "app_assert.h"
#include "app_timer.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_iv_update_by_age.h"
#include "sl_btmesh_iv_update_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup iv_update
 * @{
 ******************************************************************************/

#define NORMAL_OPERATION 0
#define IV_UPDATE_IN_PROGRESS 1

static app_timer_t age_timer;
static void on_age_timer(app_timer_t *handle, void *data);

static void age_timer_start(uint32_t timeout_s);
static void age_timer_stop(void);
static void handle_iv_update_age(void);

/***************************************************************************//**
 *  Handling of mesh iv_update_by_age related events.
 *  @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_iv_update_by_age_on_event(sl_btmesh_msg_t* evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        handle_iv_update_age();
      }
      break;
    case sl_btmesh_evt_prov_initialized_id:
    case sl_btmesh_evt_node_provisioned_id:
    case sl_btmesh_evt_node_changed_ivupdate_state_id:
      handle_iv_update_age();
      break;
    default:
      break;
  }
}

/***************************************************************************//**
 *  Start or stop automatic IV update timer based on IV update state
 ******************************************************************************/
static void handle_iv_update_age(void)
{
  uint8_t iv_update_state;
  uint32_t iv_index;
  sl_status_t sc = sl_btmesh_node_get_ivupdate_state(&iv_index, &iv_update_state);
  log_status_error_f(sc, "Can't get IV update state");
  if (iv_update_state == NORMAL_OPERATION) {
    uint32_t age = get_iv_update_age();
    if (age < SL_BTMESH_IV_UPDATE_FIX_TIMEOUT_S) {
      age_timer_start(SL_BTMESH_IV_UPDATE_FIX_TIMEOUT_S - age);
    } else {
      age_timer_start(0);
    }
  } else {
    age_timer_stop();
  }
}

/***************************************************************************//**
 *  Request IV Update on timer callback
 ******************************************************************************/
static void on_age_timer(app_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;
  sl_status_t sc = sl_btmesh_node_request_ivupdate();
  app_assert_status_f(sc, "Failed to request IV Update");
}

/***************************************************************************//**
 *  Start age timer
 ******************************************************************************/
static void age_timer_start(uint32_t timeout_s)
{
  sl_status_t sc = app_timer_start(&age_timer,
                                   timeout_s * 1000,
                                   on_age_timer,
                                   NULL,
                                   false);
  app_assert_status_f(sc, "Failed to start timer");
}

/***************************************************************************//**
 *  Stop age timer
 ******************************************************************************/
static void age_timer_stop(void)
{
  sl_status_t sc = app_timer_stop(&age_timer);
  app_assert_status_f(sc, "Failed to stop timer");
}

SL_WEAK uint32_t get_iv_update_age(void)
{
  return 0;
}

/** @} (end addtogroup iv_update) */
