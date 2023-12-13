/***************************************************************************//**
 * @file
 * @brief NCP reset module.
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
#include "ncp_reset.h"
#include "ncp_reset_config.h"
#include "sl_bt_api.h"
#include "sl_bt_version.h"
#include "app_log.h"
#include "app_timer.h"
#include "app_assert.h"

static bool booted;
static uint8_t boot_retry_count;
static app_timer_t boot_timer;

static void on_boot_timer_expire(app_timer_t *timer, void *data);

/**************************************************************************//**
 * Module initialization.
 *****************************************************************************/
void ncp_reset_init(void)
{
  booted = false;
  boot_retry_count = 0;
  sl_status_t sc = app_timer_start(&boot_timer,
                                   NCP_RESET_TIMEOUT_INIT_MS,
                                   on_boot_timer_expire,
                                   NULL,
                                   false);
  app_assert_status(sc);
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 *****************************************************************************/
sl_status_t ncp_reset_on_event(sl_bt_msg_t *evt)
{
  if (booted) {
    // Target is operational, nothing to do.
    return SL_STATUS_OK;
  }

  // Catch boot event
  if (SL_BT_MSG_ID(evt->header) == sl_bt_evt_system_boot_id) {
    (void)app_timer_stop(&boot_timer);
    booted = true;
    return SL_STATUS_OK;
  }

  return SL_STATUS_NOT_READY;
}

/**************************************************************************//**
 * Send system reset request to the NCP target.
 *****************************************************************************/
void ncp_reset(void)
{
  booted = false;
  boot_retry_count = 0;
  on_boot_timer_expire(&boot_timer, NULL);
}

/**************************************************************************//**
 * Boot timer callback.
 *****************************************************************************/
static void on_boot_timer_expire(app_timer_t *timer, void *data)
{
  (void)data;

  if (boot_retry_count < NCP_RESET_RETRY_COUNT) {
    app_log_info("Resetting NCP target (%d)..." APP_LOG_NL, boot_retry_count);
    boot_retry_count++;
    sl_bt_system_reset(sl_bt_system_boot_mode_normal);
    sl_status_t sc = app_timer_start(timer,
                                     NCP_RESET_TIMEOUT_RETRY_MS,
                                     on_boot_timer_expire,
                                     NULL,
                                     false);
    app_assert_status(sc);
  } else {
    app_assert(false, "NCP target unreachable.");
  }
}
