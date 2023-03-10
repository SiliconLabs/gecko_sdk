/**************************************************************************//**
* @file
* @brief BT Mesh Host Remote Provisioner Example Project - UI mode handler.
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

// ----------------------------------------------------------------------------
// Includes
#include <stdlib.h>

#include "app_log.h"
#include "app_assert.h"
#include "btmesh_app_remote_prov.h"
#include "btmesh_app_prov_ui.h"
#include "btmesh_remote_prov.h"
#include "btmesh_app_remote_prov_ui.h"

// ----------------------------------------------------------------------------
// Static Variables

/// The remote provisioner server address used throughout remote provisioning process
static uint16_t remote_address;

// ----------------------------------------------------------------------------
// Function definitions

sl_status_t btmesh_app_prov_ui_handle_remote_prov_cmd(char cmd_id)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;

  switch (cmd_id) {
    case REMOTE_SERVERLIST_COMMAND:
      btmesh_app_remote_prov_set_command(REMOTE_SERVERLIST);
      btmesh_app_remote_prov_set_command_state(START);
      sc = SL_STATUS_OK;
      break;
    case REMOTE_SCAN_COMMAND:
      btmesh_app_remote_prov_set_command(REMOTE_SCAN);
      btmesh_app_remote_prov_set_command_state(START);
      sc = SL_STATUS_OK;
      break;
    case REMOTE_PROVISION_COMMAND:
      btmesh_app_remote_prov_set_command(REMOTE_PROVISION);
      btmesh_app_remote_prov_set_command_state(START);
      sc = SL_STATUS_OK;
      break;
    default:
      break;
  }
  return sc;
}

bool btmesh_app_remote_prov_get_server_address(uint16_t *ui_server_address)
{
  bool return_value = false;
  sl_status_t sc;

  sl_ui_state prov_ui_state = btmesh_app_prov_ui_get_ui_state();

  if (UI_CMD_PROCESSING == prov_ui_state) {
    app_log("Select a remote provisioning server" APP_LOG_NEW_LINE);
    app_log("Type either the ID or the address from the list below" APP_LOG_NEW_LINE);
    app_log_nl();
    sc = btmesh_remote_prov_list_active_servers();
    app_log_nl();
    if (SL_STATUS_EMPTY == sc) {
      app_log_info("No remote provisioning server nodes available" APP_LOG_NEW_LINE);
      app_log_info("Check the available active remote provisioning server list first" APP_LOG_NEW_LINE);
      btmesh_app_remote_prov_end_of_cmd();
    } else {
      // push ui in UI_WAITING_FOR_INPUT state and waiting for server address
      // return value is not important
      btmesh_app_prov_ui_get_input_buffer(NULL);
    }
  } else if (UI_WAITING_FOR_INPUT == prov_ui_state) {
    char *ui_input_data;
    return_value = btmesh_app_prov_ui_get_input_buffer(&ui_input_data);
    if (true == return_value) {
      size_t len = strlen(ui_input_data);
      if (ADDRESS_LEN_WITHOUT_PREFIX > len) {
        uint16_t id = (uint16_t)atoi(ui_input_data);
        sc = btmesh_remote_prov_get_server_address_by_id(id, ui_server_address);
        if (SL_STATUS_OK != sc) {
          app_log_warning("Server with ID: %d not found"APP_LOG_NEW_LINE, id);
          return_value = false;
        }
      } else if (ADDRESS_LEN_WITHOUT_PREFIX == len
                 || ADDRESS_LEN_WITH_PREFIX == len) {
        app_parse_address(ui_input_data, len, ui_server_address);
      } else {
        app_log_error("Invalid input format!" APP_LOG_NEW_LINE);
        return_value = false;
      }
    }
  }

  return return_value;
}

bool btmesh_app_remote_prov_get_prov_data(uint16_t *remote_prov_server_addr,
                                          uuid_128 *remote_prov_uuid,
                                          uint16_t *remote_prov_oob_capabilities)
{
  bool return_value = false;
  sl_status_t sc;
  uint16_t id;
  char *ui_input_data = NULL;
  size_t len;

  sl_ui_state prov_ui_state = btmesh_app_prov_ui_get_ui_state();

  // get server address from UI
  if (0 == remote_address) {
    return_value = btmesh_app_remote_prov_get_server_address(&remote_address);
    if (true == return_value) {
      if (0 != remote_address) {
        return_value = false;
        app_log_info("Selected remote provisioning server address 0x%04x"APP_LOG_NEW_LINE, remote_address);
      } else {
        app_log_warning("Invalid remote server address 0x%04x"APP_LOG_NEW_LINE, remote_address);
        return_value = false;
      }
    }
  } else {
    if (UI_CMD_PROCESSING == prov_ui_state) {
      app_log_nl();
      app_log("Select the unprovisioned node for remote provisioning" APP_LOG_NEW_LINE);
      app_log("Type either the ID, or UUID from the list below" APP_LOG_NEW_LINE);
      app_log_nl();
      sc = btmesh_remote_prov_list_unprovisioned_nodes_by_addr(remote_address);
      if (SL_STATUS_EMPTY == sc) {
        app_log_nl();
        app_log_info("No unprovisioned nodes available" APP_LOG_NEW_LINE);
        app_log_info("Try remote scanning with server: 0x%04x for unprovisioned nodes first"APP_LOG_NEW_LINE, remote_address);
        btmesh_app_remote_prov_end_of_cmd();
      } else {
        // push ui in UI_WAITING_FOR_INPUT state and waiting for unprovisioned node uuid
        // return value is not important
        btmesh_app_prov_ui_get_input_buffer(NULL);
      }
    } else if (UI_WAITING_FOR_INPUT == prov_ui_state) {
      return_value = btmesh_app_prov_ui_get_input_buffer(&ui_input_data);
      if (true == return_value) {
        len = strlen(ui_input_data);
        sc = SL_STATUS_OK;
        if (ADDRESS_LEN_WITHOUT_PREFIX > len) {
          // Unprovisioned node by ID
          id = (uint16_t)atoi(ui_input_data);
          sc = btmesh_remote_prov_get_unprov_uuid_by_id(id, remote_address, remote_prov_uuid, remote_prov_oob_capabilities);
        } else if (UUID_LEN_WITHOUT_SEPARATORS == len
                   || UUID_LEN_WITH_SEPARATORS == len) {
          // Unprovisioned node by UUID
          app_parse_uuid(ui_input_data, len, remote_prov_uuid);
        } else {
          app_log_error("Invalid input format!" APP_LOG_NEW_LINE);
          return_value = false;
        }
        if (SL_STATUS_EMPTY == sc) {
          app_log_nl();
          app_log_info("No unprovisioned nodes available" APP_LOG_NEW_LINE);
          app_log_info("Try scanning for unprovisioned nodes first" APP_LOG_NEW_LINE);
          return_value = false;
          btmesh_app_remote_prov_end_of_cmd();
        } else {
          *remote_prov_server_addr = remote_address;
          remote_address = 0;
        }
      }
    }
  }

  return return_value;
}

// ----------------------------------------------------------------------------
// Private function definitions

// ----------------------------------------------------------------------------
// Callbacks

void btmesh_remote_prov_on_unprovisioned_node_list(uint16_t id,
                                                   uuid_128 uuid)
{
  app_log_info("Unprovisioned node" APP_LOG_NEW_LINE);
  app_log_info("ID:      %d" APP_LOG_NEW_LINE, id);
  app_log_info("UUID:    ");
  btmesh_app_prov_append_uuid(&uuid);
  app_log_nl();
}

void btmesh_app_remote_prov_end_of_cmd(void)
{
  btmesh_app_remote_prov_set_command(NONE);
  btmesh_app_remote_prov_set_command_state(START);
  remote_address = 0;
  btmesh_app_prov_end_of_cmd();
}

void btmesh_remote_prov_on_serverlist(uint16_t id, uint16_t server)
{
  app_log_info("%u. Remote provisioning server: 0x%04x"APP_LOG_NEW_LINE, id, server);
}
