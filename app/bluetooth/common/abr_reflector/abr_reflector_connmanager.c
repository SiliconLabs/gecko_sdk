/***************************************************************************//**
 * @file
 * @brief ABR reflector connection manager
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

#include "abr_reflector_connmanager.h"
#include "sl_bt_api.h"

static connection_ctx_t connections[ABR_REFLECTOR_MAX_CONNECTIONS] = { {
                                                                         .conn_handle = UINT8_MAX,
                                                                         .in_use = false,
                                                                         .ras_control_point_indication_enabled = false,
                                                                         .ras_periodic_notification_mode_enabled = false,
                                                                         .indication_in_progress = false,
                                                                         .current_cs_subevent_index = 0u,
                                                                         .current_procedure_index = 0u
                                                                       }, };

static bool abr_rcm_get_idx_for_conn_handle(const uint8_t conn_handle, uint8_t *const idx);

static bool abr_rcm_get_idx_for_conn_handle(const uint8_t conn_handle, uint8_t *const idx)
{
  if (idx == NULL) {
    return false;
  }
  for (uint8_t i = 0; i < ABR_REFLECTOR_MAX_CONNECTIONS; i++) {
    if (connections[i].conn_handle == conn_handle) {
      *idx = i;
      return true;
    }
  }
  return false;
}

connection_ctx_t *abr_rcm_get_connection_ctx(const uint8_t conn_handle)
{
  uint8_t idx;
  if (!abr_rcm_get_idx_for_conn_handle(conn_handle, &idx)) {
    return NULL;
  }
  return &connections[idx];
}

bool abr_rcm_add_new_initiator_connection(const uint8_t conn_handle)
{
  // Find the first empty spot
  bool found = false;
  uint8_t i;
  for (i = 0; i < ABR_REFLECTOR_MAX_CONNECTIONS; i++) {
    if (!connections[i].in_use) {
      found = true;
      break;
    }
  }
  // No free spots available
  if (!found) {
    return false;
  }
  // Add the new connection and initialize the context
  connections[i].conn_handle = conn_handle;
  connections[i].in_use = true;
  connections[i].ras_control_point_indication_enabled = false;
  connections[i].ras_periodic_notification_mode_enabled = false;
  connections[i].indication_in_progress = false;
  connections[i].current_cs_subevent_index = 0u;
  connections[i].current_procedure_index = 0u;
  return true;
}

void abr_rcm_remove_initiator_connection(const uint8_t conn_handle)
{
  // Find the first empty spot
  uint8_t idx;
  bool found = abr_rcm_get_idx_for_conn_handle(conn_handle, &idx);
  // No free spots available
  if (!found) {
    return;
  }
  // Remove the connection and initialize the context
  connections[idx].conn_handle = UINT8_MAX;
  connections[idx].in_use = false;
  connections[idx].ras_control_point_indication_enabled = false;
  connections[idx].ras_periodic_notification_mode_enabled = false;
  connections[idx].indication_in_progress = false;
  connections[idx].current_cs_subevent_index = 0u;
  connections[idx].current_procedure_index = 0u;
}

bool abr_rcm_can_accept_new_connection(void)
{
  for (uint8_t i = 0; i < ABR_REFLECTOR_MAX_CONNECTIONS; i++) {
    if (!connections[i].in_use) {
      return true;
    }
  }
  return false;
}

uint32_t abr_rcm_get_number_of_connections(void)
{
  uint32_t num_of_connections = 0u;
  for (uint8_t i = 0; i < ABR_REFLECTOR_MAX_CONNECTIONS; i++) {
    if (connections[i].in_use) {
      num_of_connections++;
    }
  }
  return num_of_connections;
}
