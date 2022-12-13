/***************************************************************************//**
 * @file
 * @brief BGAPI version check between NCP host and target.
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

#include "sl_bt_version.h"
#include "app_log.h"
#include "ncp_version.h"

void ncp_version_on_event(sl_bt_msg_t *evt)
{
  if (SL_BT_MSG_ID(evt->header) == sl_bt_evt_system_boot_id) {
    app_log_info("Bluetooth stack booted: v%d.%d.%d-b%d" APP_LOG_NL,
                 evt->data.evt_system_boot.major,
                 evt->data.evt_system_boot.minor,
                 evt->data.evt_system_boot.patch,
                 evt->data.evt_system_boot.build);
    if ((evt->data.evt_system_boot.major != SL_BT_VERSION_MAJOR)
        || (evt->data.evt_system_boot.minor != SL_BT_VERSION_MINOR)
        || (evt->data.evt_system_boot.patch != SL_BT_VERSION_PATCH)) {
      app_log_warning("BGAPI version mismatch: %d.%d.%d (target) != %d.%d.%d (host)" APP_LOG_NL,
                      evt->data.evt_system_boot.major,
                      evt->data.evt_system_boot.minor,
                      evt->data.evt_system_boot.patch,
                      SL_BT_VERSION_MAJOR,
                      SL_BT_VERSION_MINOR,
                      SL_BT_VERSION_PATCH);
    }
  }
}
