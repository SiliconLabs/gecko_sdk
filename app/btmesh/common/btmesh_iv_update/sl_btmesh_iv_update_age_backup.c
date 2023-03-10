/***************************************************************************//**
 * @file
 * @brief IV Update age backup implementation
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
#include "sl_simple_timer.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_APP_LOG_PRESENT
#include "app_log.h"
#endif // SL_CATALOG_APP_LOG_PRESENT

#include "sl_btmesh_iv_update_config.h"

// Warning! The app_btmesh_util shall be included after the component configuration
// header file in order to provide the component specific logging macro.
#include "app_btmesh_util.h"

/***************************************************************************//**
 * @addtogroup iv_update
 * @{
 ******************************************************************************/

// IV Update age in seconds
static uint32_t age = 0;

static sl_simple_timer_t iv_update_age_backup_timer;
static void on_iv_update_age_backup_timer(sl_simple_timer_t *handle, void *data);

static void age_backup_timer_start(void);
static void backup_age(void);
static void restore_age(void);

/***************************************************************************//**
 *  Handling of mesh iv_update_age_backup related events.
 *  @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_iv_update_age_backup_on_event(sl_btmesh_msg_t* evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
      if (evt->data.evt_node_initialized.provisioned) {
        restore_age();
        age_backup_timer_start();
      }
      break;
    case sl_btmesh_evt_node_provisioned_id:
    case sl_btmesh_evt_node_changed_ivupdate_state_id:
      age = 0;
      backup_age();
      age_backup_timer_start();
      break;
    default:
      break;
  }
}

/***************************************************************************//**
 *  Restore the IV Update age from the nvm.
 ******************************************************************************/
static void restore_age(void)
{
  size_t age_len = sizeof(age);
  sl_status_t sc = app_btmesh_nvm_read(SL_BTMESH_IV_UPDATE_AGE_NVM_KEY_CFG_VAL,
                                       &age,
                                       &age_len);
  log_status_error_f(sc, "Failed to read from nvm" NL);
  if (sc == SL_STATUS_OK) {
    sc = sl_btmesh_node_set_iv_update_age(age);
    app_assert_status_f(sc, "Failed to restore IV Update age");
  }
}

/***************************************************************************//**
 *  Write the IV Update age to the nvm.
 ******************************************************************************/
static void backup_age(void)
{
  sl_status_t sc = app_btmesh_nvm_write(SL_BTMESH_IV_UPDATE_AGE_NVM_KEY_CFG_VAL,
                                        &age,
                                        sizeof(age));
  log_status_error_f(sc, "Failed to backup IV Update age" NL);
}

/***************************************************************************//**
 *  Increment and backup IV Update age
 ******************************************************************************/
static void on_iv_update_age_backup_timer(sl_simple_timer_t *handle, void *data)
{
  (void)data;
  (void)handle;
  age += SL_BTMESH_IV_UPDATE_AGE_BACKUP_PERIOD_S;
  backup_age();
}

/***************************************************************************//**
 *  Write the IV Update age to the nvm.
 ******************************************************************************/
static void age_backup_timer_start(void)
{
  sl_status_t sc = sl_simple_timer_start(&iv_update_age_backup_timer,
                                         SL_BTMESH_IV_UPDATE_AGE_BACKUP_PERIOD_S * 1000,
                                         on_iv_update_age_backup_timer,
                                         NULL,
                                         true);
  app_assert_status_f(sc, "Failed to start timer");
}

#if SL_BTMESH_IV_UPDATE_AGE_BACKUP_ENABLE
/***************************************************************************//**
 *  Strong implementation of the function declared in sl_btmesh_iv_update_by_age.h
 *  @return The restored IV Update age in seconds
 ******************************************************************************/
uint32_t get_iv_update_age(void)
{
  return age;
}
#endif

/** @} (end addtogroup iv_update) */
