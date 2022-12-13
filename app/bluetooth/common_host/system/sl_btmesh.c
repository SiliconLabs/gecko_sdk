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
#include "sl_btmesh.h"

#ifdef  SL_CATALOG_APP_PROV_PRESENT
#include "btmesh_app_prov.h"
#endif
#ifdef  SL_CATALOG_APP_REMOTE_PROV_PRESENT
#include "btmesh_app_remote_prov.h"
#endif

void sl_btmesh_init(void)
{
}

void sl_btmesh_process_event(sl_btmesh_msg_t *evt)
{
  sl_btmesh_on_event(evt);

#ifdef  SL_CATALOG_APP_PROV_PRESENT
  btmesh_app_prov_on_event(evt);
#endif
#ifdef  SL_CATALOG_APP_REMOTE_PROV_PRESENT
  btmesh_app_remote_prov_on_event(evt);
#endif
}

void sl_btmesh_step(void)
{
  sl_btmesh_msg_t evt;

  // Pop (non-blocking) a Bluetooth stack event from event queue.
  sl_status_t status = sl_btmesh_pop_event(&evt);
  if (status != SL_STATUS_OK) {
    return;
  }
  sl_btmesh_process_event(&evt);
}
