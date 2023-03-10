/**************************************************************************//**
* @file
* @brief BT Mesh Remote Provisioner Application component - CLI handler
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

#include "app.h"
#include "btmesh_app_prov.h"
#include "btmesh_app_remote_prov.h"
#include "app_log.h"
#include "app_assert.h"

#include "sl_common.h"
#include "sl_bt_api.h"
#include "btmesh_prov.h"
#include "btmesh_remote_prov.h"
// ----------------------------------------------------------------------------
// Macros

// ----------------------------------------------------------------------------
// Static Function Declarations

/**************************************************************************//**
* Handle --remote_serverlist functionality
*
******************************************************************************/
static void handle_remote_serverlist(void);

/**************************************************************************//**
* Handle --remote_scan functionality
*
******************************************************************************/
static void handle_remote_scan(void);

/**************************************************************************//**
* Handle --remote_provisioning functionality
*
******************************************************************************/
static void handle_remote_provision(void);

// ----------------------------------------------------------------------------
// Static Variables

/// Flag stating that the btmeshprov_initialized event has arrived
static bool initialized = false;
/// UUID passed as an argument
static uuid_128 command_uuid;
/// OOB capabilities of the node to be provisioned
static uint16_t oob_capabilities = 0;
/// The state of the current command
static command_state_t command_state = INIT;
/// The command in use
static command_t command = NONE;
/// Remote provisioner server address
static uint16_t remote_prov_server_addr = 0;
/// Command line options
static struct option remote_prov_long_options[REMOTE_PROV_OPTLENGTH] = {
  { "remote_serverlist", no_argument, 0, 'm' },
  { "remote_scan", required_argument, 0, 'o' },
  { "remote_provision", required_argument, 0, 'v' },
  { "remote_server", required_argument, 0, 'a' }
};

// ----------------------------------------------------------------------------
// Function definitions

sl_status_t btmesh_app_remote_prov_init(int cmd_opt, char *cmd_optarg)
{
  sl_status_t sc = SL_STATUS_OK;

  switch (cmd_opt) {
    case 'm':
      // Scan for remote provisioning servers
      app_log_info("Remote serverlist" APP_LOG_NEW_LINE);
      command = REMOTE_SERVERLIST;
      command_state = START;
      break;
    case 'o':
      // Remote scan for unprovisioned nodes
      app_log_info("Remote scan" APP_LOG_NEW_LINE);
      command = REMOTE_SCAN;
      command_state = START;
      remote_prov_server_addr = (uint16_t)strtol(cmd_optarg, NULL, 16);
      break;
    case 'v':
      // Remote provision the selected unprovisioned node
      command = REMOTE_PROVISION;
      command_state = START;
      char *pos = cmd_optarg;
      size_t len = strlen(cmd_optarg);
      // Parse input for UUID
      app_parse_uuid(pos, len, &command_uuid);
      break;
    case 'a':
      // Remote provision server address selection
      remote_prov_server_addr = (uint16_t)strtol(cmd_optarg, NULL, 16);
      break;
    default:
      sc = SL_STATUS_NOT_FOUND;
      break;
  }
  return sc;
}

void btmesh_app_remote_prov_process_action(void)
{
  if (initialized == true) {
    switch (command) {
      case REMOTE_SERVERLIST:
        handle_remote_serverlist();
        break;
      case REMOTE_SCAN:
        handle_remote_scan();
        break;
      case REMOTE_PROVISION:
        handle_remote_provision();
        break;
      default:
        break;
    }
  }
}

void btmesh_app_remote_prov_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id: {
      // Device successfully initialized in provisioner mode
      app_log_info("Remote provisioning client init" APP_LOG_NEW_LINE);
      app_log_nl();
      sl_status_t sc = sl_btmesh_remote_provisioning_client_init();
      app_assert_status_f(sc, "Failed to init remote provisioning client" APP_LOG_NEW_LINE);
      if (INIT == command_state) {
        command_state = START;
      }
      initialized = true;

      break;
    }
    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:

      break;
  }

  // Let other modules handle their events too
  btmesh_remote_prov_on_event(evt);
}

// ----------------------------------------------------------------------------
// App logic functions

void handle_remote_serverlist(void)
{
  switch (command_state) {
    case START: {
      uint16_t networks_number = btmesh_app_prov_get_networks_number();
      if (0 < networks_number) {
        bool db_stat;
        db_stat = btmesh_app_prov_get_ddb_status();
        if (true == db_stat) {
          sl_status_t sc = btmesh_remote_prov_start_server_capabilities_scan(APP_NETKEY_IDX);
          if (SL_STATUS_OK != sc) {
            app_log_info("Failed to start server scanning" APP_LOG_NEW_LINE);
            command_state = FINISHED;
          } else {
            app_log_info("Scanning for remote provisioner servers" APP_LOG_NEW_LINE);
            app_log_nl();
            command_state = IN_PROGRESS;
          }
        }
      } else {
        app_log_nl();
        app_log_info("No networks are present on the device" APP_LOG_NEW_LINE);
        command_state = FINISHED;
      }
      break;
    }
    case IN_PROGRESS:
      break;
    case FINISHED: {
      prov_mode_t prov_mode = btmesh_app_prov_get_mode();
      app_log_nl();
      app_log_info("Scanning for remote provisioner servers completed" APP_LOG_NEW_LINE);
      if (prov_mode == PROV_UI_MODE) {
        btmesh_app_remote_prov_end_of_cmd();
      } else {
        btmesh_prov_free_remote_serverlist();
        exit(EXIT_SUCCESS);
      }
      break;
    }
    default:
      break;
  }
}

void handle_remote_scan(void)
{
  sl_status_t sc;
  switch (command_state) {
    case START: {
      bool param_ready = true;
      prov_mode_t prov_mode = btmesh_app_prov_get_mode();
      if (prov_mode == PROV_UI_MODE) {
        param_ready = btmesh_app_remote_prov_get_server_address(&remote_prov_server_addr);
      }
      if (true == param_ready) {
        sc = btmesh_remote_prov_start_device_scan_by_address(0,
                                                             remote_prov_server_addr,
                                                             REMOTE_PROV_SCANNING_TIMEOUT);
        if (SL_STATUS_OK != sc) {
          app_log_info("Failed to start remote scanning" APP_LOG_NEW_LINE);
        } else {
          app_log_info("Remote scanning for unprovisioned nodes started" APP_LOG_NEW_LINE);
        }
        command_state = IN_PROGRESS;
      }
      break;
    }
    case IN_PROGRESS:
      break;
    case FINISHED: {
      prov_mode_t prov_mode = btmesh_app_prov_get_mode();
      app_log_nl();
      app_log_info("Remote scanning completed" APP_LOG_NEW_LINE);
      if (prov_mode == PROV_UI_MODE) {
        btmesh_app_remote_prov_end_of_cmd();
      } else {
        exit(EXIT_SUCCESS);
      }
      break;
    }
    default:
      break;
  }
}

void handle_remote_provision(void)
{
  static bd_addr mac = { 0 };
  switch (command_state) {
    case START: {
      bool param_ready = true;
      prov_mode_t prov_mode = btmesh_app_prov_get_mode();
      if (prov_mode == PROV_UI_MODE) {
        param_ready = btmesh_app_remote_prov_get_prov_data(&remote_prov_server_addr, &command_uuid, &oob_capabilities);
      }
      if (true == param_ready) {
        if (remote_prov_server_addr) {
          if (prov_mode == PROV_UI_MODE) {
            bool cbp_capability = oob_capabilities & BTMESH_OOB_FLAG_CBP_CAPABLE;
            btmesh_app_prov_set_cbp_capability(cbp_capability);
          }
          app_log_info("Remote provisioning..." APP_LOG_NEW_LINE);
          uint16_t netkey_index = 0;
          sl_status_t sc = btmesh_remote_prov_start_provisioning(netkey_index,
                                                                 remote_prov_server_addr,
                                                                 command_uuid,
                                                                 HOST_PROV_PB_ADV,
                                                                 REMOTE_PROV_ATTENTION_TIMER);
          app_assert_status_f(sc, "Provisioning failed" APP_LOG_NEW_LINE);
          command_state = IN_PROGRESS;
        } else {
          app_log_info("Remote provisioning failed, invalid server address: 0x%04x" APP_LOG_NEW_LINE,
                       remote_prov_server_addr);
          exit(EXIT_FAILURE);
        }
      }
      break;
    }
    case IN_PROGRESS:
      // Handle CBP if present, else don't do anything
      btmesh_app_prov_handle_cbp(APP_NETKEY_IDX, command_uuid, mac, HOST_PROV_PB_REMOTE);
      break;
    case FINISHED: {
      prov_mode_t prov_mode = btmesh_app_prov_get_mode();
      app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);
      app_log_nl();
      app_log_info("Provisioning finished" APP_LOG_NEW_LINE);
      if (prov_mode == PROV_UI_MODE) {
        btmesh_app_remote_prov_end_of_cmd();
      } else {
        exit(EXIT_SUCCESS);
      }
      break;
    }
    default:
      break;
  }
}

void btmesh_app_remote_prov_get_command(command_t *remote_prov_command, command_state_t *remote_prov_command_state)
{
  if (remote_prov_command != NULL) {
    *remote_prov_command = command;
  }
  if (remote_prov_command_state != NULL) {
    *remote_prov_command_state = command_state;
  }
}

void btmesh_app_remote_prov_set_command(command_t remote_prov_command)
{
  command = remote_prov_command;
}

void btmesh_app_remote_prov_set_command_state(command_state_t remote_prov_command_state)
{
  command_state = remote_prov_command_state;
}

// ----------------------------------------------------------------------------
// Callbacks

void btmesh_remote_prov_on_client_scan_capabilities(uint16_t server, uint8_t  max_items)
{
  app_log_info("Remote provisioning server address: 0x%04x" APP_LOG_NEW_LINE, server);
}

void btmesh_remote_prov_on_client_scan_capabilities_finished(void)
{
  command_state = FINISHED;
}

void btmesh_remote_prov_on_client_scan_report(uuid_128 uuid)
{
  app_log_nl();
  app_log_info("Unprovisioned device UUID: ");
  btmesh_app_prov_append_uuid(&uuid);
}

void btmesh_remote_prov_on_client_scan_finished(void)
{
  command_state = FINISHED;
}

void btmesh_app_on_provision_failed(void)
{
  if (command_state == IN_PROGRESS) {
    app_log_warning("Remote provision failed"APP_LOG_NEW_LINE);
    command_state = FINISHED;
  }
}

void btmesh_app_on_node_configuration_end(void)
{
  if (command_state == IN_PROGRESS) {
    command_state = FINISHED;
  }
}

void btmesh_app_on_build_cmd_options(struct option *long_options)
{
  if (NULL != long_options) {
    memcpy(long_options, remote_prov_long_options, REMOTE_PROV_OPTLENGTH * sizeof(struct option));
  }
}

sl_status_t btmesh_app_on_check_cmd_options(int cmd_opt, char *cmd_optarg)
{
  return btmesh_app_remote_prov_init(cmd_opt, cmd_optarg);
}

SL_WEAK void btmesh_app_remote_prov_end_of_cmd(void)
{
  exit(EXIT_SUCCESS);
}

SL_WEAK bool btmesh_app_remote_prov_get_server_address(uint16_t *ui_server_address)
{
  (void)ui_server_address;

  return true;
}

SL_WEAK bool btmesh_app_remote_prov_get_prov_data(uint16_t *remote_prov_server_addr,
                                                  uuid_128 *remote_prov_uuid,
                                                  uint16_t *remote_prov_oob_capabilities)
{
  (void)remote_prov_server_addr;
  (void)remote_prov_uuid;
  (void)remote_prov_oob_capabilities;

  return true;
}

SL_WEAK void btmesh_app_prov_handle_cbp(uint16_t netkey_index,
                                        uuid_128 uuid,
                                        bd_addr mac_address,
                                        uint8_t bearer_type)
{
  (void)netkey_index;
  (void)uuid;
  (void)mac_address;
  (void)bearer_type;
}

SL_WEAK void btmesh_app_prov_set_cbp_capability(bool capability)
{
  (void)capability;
}
