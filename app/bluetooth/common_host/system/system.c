/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_bt_api.h"
#include "sl_bt_ncp_host.h"
#include "system.h"
#ifdef BTMESH
#include "sl_btmesh.h"
#endif
#ifdef SL_CATALOG_SIMPLE_TIMER_PRESENT
#include "sl_simple_timer.h"
#endif
#ifdef SL_CATALOG_BTMESH_CONF_PRESENT
#include "btmesh_conf.h"
#endif
#ifdef SL_CATALOG_NCP_GATT_PRESENT
#include "sl_ncp_gatt.h"
#endif

static void sl_bt_init(void);
static void sl_bt_step(void);

#ifdef BTMESH
extern void sl_btmesh_init(void);
extern void sl_btmesh_step(void);
#endif

void sl_system_init(void)
{
  sl_bt_init();
#ifdef BTMESH
  sl_btmesh_init();
#endif
#ifdef SL_CATALOG_SIMPLE_TIMER_PRESENT
  sl_simple_timer_init();
#endif
}

void sl_system_process_action(void)
{
  sl_bt_step();
#ifdef BTMESH
  sl_btmesh_step();
#endif
#ifdef SL_CATALOG_SIMPLE_TIMER_PRESENT
  sli_simple_timer_step();
#endif
#ifdef SL_CATALOG_BTMESH_CONF_PRESENT
  // BT Mesh Host Configurator component cyclic function
  btmesh_conf_step();
#endif
}

// Bluetooth stack event handler
SL_WEAK void sl_bt_on_event(sl_bt_msg_t *evt)
{
  (void)(evt);
}

// Initialize Bluetooth stack
static void sl_bt_init(void)
{
  // nothing to do
}

// Poll Bluetooth stack for an event and call event handler
static void sl_bt_step(void)
{
  sl_bt_msg_t evt;

  // Pop (non-blocking) a Bluetooth stack event from event queue.
  sl_status_t status = sl_bt_pop_event(&evt);
  if (status != SL_STATUS_OK) {
    return;
  }
#ifdef SL_CATALOG_NCP_GATT_PRESENT
  sl_ncp_gatt_on_event(&evt);
#endif
  sl_bt_on_event(&evt);
}
