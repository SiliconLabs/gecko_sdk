/**************************************************************************//**
* @file
* @brief BT Mesh Provisioner Application component - CLI handler
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

// ----------------------------------------------------------------------------
// Includes

// standard library headers
#include <unistd.h>

// app-related headers
#include "app.h"
#include "btmesh_app_prov.h"
#include "app_log.h"
#include "app_assert.h"
#include "app_timer.h"

#include "sl_common.h"
#include "btmesh_prov.h"
#include "btmesh_db.h"
#include "btmesh_key_export.h"

#include "app_conf.h"

// ----------------------------------------------------------------------------
// Macros

// ----------------------------------------------------------------------------
// Static Function Declarations

/**************************************************************************//**
 * Handle --nodeinfo functionality
 *
 *****************************************************************************/
static void handle_nodeinfo(void);

/**************************************************************************//**
 * Handle --nodelist functionality
 *
 ****************************************************************************/
static void handle_nodelist(void);

/**************************************************************************//**
 * Handle --provision functionality
 *
 ****************************************************************************/
static void handle_provision(void);

/**************************************************************************//**
 * Handle --remove functionality
 *
 ****************************************************************************/
static void handle_remove(void);

/**************************************************************************//**
 * Handle --key-refresh functionality
 *
 ****************************************************************************/
static void handle_key_refresh(void);

/**************************************************************************//**
 * Handle --key-export functionality
 *
 ****************************************************************************/
static void handle_key_export(void);

/**************************************************************************//**
 * Handle --reset functionality
 *
 ****************************************************************************/
static void handle_reset(void);

/**************************************************************************//**
 * Handle --scan functionality
 *
 ****************************************************************************/
static void handle_scan(void);

/**************************************************************************//**
 * Exit in command line mode, call btmesh_app_prov_end_of_cmd() in UI mode
 *
 ****************************************************************************/
static void end_command(void);

/**************************************************************************//**
 *  Node removal job status callback
 *
 * @param[in] job The job this function is called from
 ****************************************************************************/
static void app_on_remove_node_job_status(const btmesh_conf_job_t *job);

/**************************************************************************//**
 * Callback for the timer used during scanning
 *
 * @param[in] timer Pointer to the timer used
 * @param[in] data Data from the timer
 ****************************************************************************/
static void app_on_scan_timer(app_timer_t *timer, void *data);

/**************************************************************************//**
 * Callback for the timer used during provisioner reset
 *
 * @param[in] timer Pointer to the timer used
 * @param[in] data Data from the timer
 ****************************************************************************/
static void app_on_reset_timer(app_timer_t *timer, void *data);

// ----------------------------------------------------------------------------
// Static Variables

static prov_mode_t app_prov_mode = PROV_CMD_LINE_MODE;
/// Flag stating that the btmeshprov_initialized event has arrived
static bool initialized = false;
/// Number of networks already present on the provisioner at startup
static uint16_t networks_on_startup = 0;
/// UUID passed as an argument
static uuid_128 command_uuid;
/// The state of the current command
static command_state_t command_state = INIT;
/// The command in use
static command_t command = NONE;
/// Flag indicating that a provisioning session has started
static bool prov_started = false;
/// Number of known devices in the DDB list
static uint16_t ddb_count = 0;
/// Flag for network database status
static bool db_ready = false;
static uint32_t phase_timeout_s = DEFAULT_PHASE_TIMEOUT_S;
/// Timer for scanning for unprovisioned devices
static app_timer_t scan_timer;
/// Timer for provisioner node reset
static app_timer_t reset_timer;
/// Command line options
static struct option prov_long_options[PROV_OPTLENGTH] = {
  { "nodeinfo", required_argument, 0, 'i' },
  { "nodelist", no_argument, 0, 'l' },
  { "provision", required_argument, 0, 'p' },
  { "remove", required_argument, 0, 'r' },
  { "key-refresh", required_argument, 0, 'k' },
  { "key-export", required_argument, 0, 'x' },
  { "reset", no_argument, 0, 'e' },
  { "scan", no_argument, 0, 's' }
};

// ----------------------------------------------------------------------------
// Function definitions

sl_status_t btmesh_app_prov_init(int opt, char *optarg)
{
  sl_status_t sc = SL_STATUS_OK;

  switch (opt) {
    case 'p':
      // provision selected node
      command = PROVISION;
      command_state = START;
      char *pos = optarg;
      size_t len = strlen(optarg);
      // Parse input for UUID
      app_parse_uuid(pos, len, &command_uuid);
      break;
    case 'l':
      // List all nodes in network
      app_log_info("Nodelist" APP_LOG_NEW_LINE);
      command = NODELIST;
      command_state = START;
      break;
    case 'i': {
      // Info about selected node
      app_log_info("Nodeinfo: %s" APP_LOG_NEW_LINE, optarg);
      char *pos = optarg;
      size_t len = strlen(optarg);
      // Parse input for UUID
      app_parse_uuid(pos, len, &command_uuid);
      command = NODEINFO;
      command_state = START;
      break;
    }
    case 'r': {
      // Remove node from network
      app_log_info("Remove: %s" APP_LOG_NEW_LINE, optarg);
      char *pos = optarg;
      size_t len = strlen(optarg);
      // Parse input for UUID
      app_parse_uuid(pos, len, &command_uuid);
      command = REMOVE_NODE;
      command_state = START;
      break;
    }
    case 'k': {
      // Refresh network keys
      app_log_info("Key refresh with phase timeout: %s" APP_LOG_NEW_LINE, optarg);
      long long timeout = strtoll(optarg, NULL, 0);
      app_assert(timeout > 0ll && timeout < (96 * 3600), "Invalid argument");
      phase_timeout_s = timeout;
      command = KEY_REFRESH;
      command_state = START;
      break;
    }
    case 'x': {
      // Export keys
      app_log_info("Export keys to: %s" APP_LOG_NEW_LINE, optarg);
      btmesh_key_export_set_file_name(optarg);
      command = KEY_EXPORT;
      command_state = START;
      break;
    }
    case 's':
      // Scan for unprovisioned nodes
      app_log_info("Scan" APP_LOG_NEW_LINE);
      command = SCAN;
      command_state = START;
      break;
    case 'e':
      // Factory reset
      app_log_info("Factory reset" APP_LOG_NEW_LINE);
      command = RESET;
      command_state = START;
      break;
    // Process options for other modules.
    default:
      sc = SL_STATUS_NOT_FOUND;
      break;
  }
  return sc;
}

void btmesh_app_prov_process_action(void)
{
  if (initialized == true) {
    switch (command) {
      case SCAN:
        handle_scan();
        break;
      case PROVISION:
        handle_provision();
        break;
      case NODELIST:
        handle_nodelist();
        break;
      case NODEINFO:
        handle_nodeinfo();
        break;
      case REMOVE_NODE:
        handle_remove();
        break;
      case KEY_REFRESH:
        handle_key_refresh();
        break;
      case KEY_EXPORT:
        handle_key_export();
        break;
      case RESET:
        handle_reset();
        break;
      default:
        break;
    }
    if (app_prov_mode == PROV_UI_MODE) {
      btmesh_app_prov_handle_ui();
    }
  }
}

void btmesh_app_prov_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id: {
      // Device successfully initialized in provisioner mode
      sl_btmesh_evt_prov_initialized_t *initialized_evt;
      initialized_evt = (sl_btmesh_evt_prov_initialized_t *)&(evt->data);

      initialized = true;
      networks_on_startup = initialized_evt->networks;

      if (INIT == command_state) {
        command_state = START;
      }
      break;
    }

    case sl_btmesh_evt_prov_ddb_list_id: {
      // DDB List event
      if (NODELIST == command) {
        // If nodelist is requested, print the information
        // This event can be fired from elsewhere, no logs needed in that case
        sl_btmesh_evt_prov_ddb_list_t *ddb_list_evt;
        ddb_list_evt = (sl_btmesh_evt_prov_ddb_list_t *)&(evt->data);
        uuid_128 uuid = ddb_list_evt->uuid;
        uint16_t address = ddb_list_evt->address;
        uint8_t elements = ddb_list_evt->elements;
        if (BTMESH_APP_PROV_NCP_ADDRESS != address) {
          app_log_nl();
          app_log_info("Address: 0x%04x" APP_LOG_NEW_LINE, address);
          app_log_info("Element count: %d" APP_LOG_NEW_LINE, elements);
          app_log_info("UUID:    ");
          btmesh_app_prov_append_uuid(&uuid);
        }
      }
      break;
    }
    case sl_btmesh_evt_prov_key_refresh_node_update_id: {
      sl_btmesh_evt_prov_key_refresh_node_update_t *evt_data;
      evt_data = &(evt->data.evt_prov_key_refresh_node_update);
      app_log_info("  Phase %d %s: ", evt_data->phase, evt_data->failure ? "failed" : "succeed");
      btmesh_app_prov_append_uuid(&evt_data->uuid);
      break;
    }
    case sl_btmesh_evt_prov_key_refresh_phase_update_id: {
      uint8_t phase = evt->data.evt_prov_key_refresh_phase_update.phase;
      app_log_info("Key refresh phase %d" APP_LOG_NEW_LINE, phase);
      break;
    }
    case sl_btmesh_evt_prov_key_refresh_complete_id: {
      uint16_t result = evt->data.evt_prov_key_refresh_complete.result;
      if (result == SL_STATUS_OK) {
        app_log_info("Key refresh succeed" APP_LOG_NEW_LINE);
      } else {
        app_log_error("Key refresh failed with error code 0x%04x." APP_LOG_NEW_LINE, result);
      }
      command_state = FINISHED;
      break;
    }
    case sl_btmesh_evt_node_reset_id:
      // Node reset successful
      app_log_info("Reset system" APP_LOG_NEW_LINE);
      sl_bt_system_reset(0);
      break;

    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
  // Let other modules handle their events too
  btmesh_key_export_on_event(evt);
  btmesh_prov_on_event(evt);
  btmesh_conf_on_event(evt);
}

// ----------------------------------------------------------------------------
// App logic functions

void handle_scan(void)
{
  switch (command_state) {
    case START: {
      sl_status_t sc;
      sc = btmesh_prov_start_scanning();
      if (SL_STATUS_OK != sc) {
        app_log_warning("Failed to start scanning" APP_LOG_NEW_LINE);
      } else {
        app_log_info("Scanning started" APP_LOG_NEW_LINE);
      }
      command_state = IN_PROGRESS;
      // Let the provisioner scan unprovisioned nodes
      app_timer_start(&scan_timer,       // Timer pointer
                      SCAN_TIMER_MS,           // Timer duration
                      app_on_scan_timer,       // Timer callback
                      NULL,                    // Timer data, not needed
                      false);                  // Not periodic
      break;
    }
    case IN_PROGRESS:
      // Do nothing, timer callback will trigger next state
      break;
    case FINISHED: {
      sl_status_t sc;
      sc = btmesh_prov_stop_scanning();
      if (SL_STATUS_OK != sc) {
        app_log_warning("Failed to stop scanning" APP_LOG_NEW_LINE);
      } else {
        app_log_nl();
        sc = btmesh_prov_list_unprovisioned_nodes();
        if (SL_STATUS_EMPTY == sc) {
          app_log_warning("No unprovisioned beaconing nodes were found" APP_LOG_NEW_LINE);
        }
        app_log_info("Scanning stopped" APP_LOG_NEW_LINE);
      }
      end_command();
      break;
    }
    default:
      break;
  }
}

void handle_provision(void)
{
  static bd_addr mac = { 0 };
  static uint16_t netkey_index = APP_NETKEY_IDX;

  switch (command_state) {
    case START: {
      bool param_ready = true;
      if (app_prov_mode == PROV_UI_MODE) {
        param_ready = btmesh_app_prov_get_uuid_from_unprov_list(&command_uuid);
      }
      if (true == param_ready) {
        if (app_prov_mode == PROV_UI_MODE) {
          btmesh_db_node_t* node = btmesh_db_node_get_by_uuid(command_uuid);
          if (node != NULL) {
            bool cbp_capability = node->prov.oob_capabilities & BTMESH_OOB_FLAG_CBP_CAPABLE;
            btmesh_app_prov_set_cbp_capability(cbp_capability);
          }
        }
        app_log_info("Starting provisioning session" APP_LOG_NEW_LINE);
        app_log_nl();
        // Try to create a network with index 0.
        // If one is already present, SL_STATUS_BT_MESH_ALREADY_EXISTS is handled
        sl_status_t sc = btmesh_prov_create_network(netkey_index, 0, 0);
        app_assert((sc == SL_STATUS_OK || sc == SL_STATUS_BT_MESH_ALREADY_EXISTS),
                   "Failed to create network" APP_LOG_NEW_LINE);
        if (SL_STATUS_OK == sc) {
          networks_on_startup++;
          db_ready = true;
          uint8_t appkey_data[16];
          size_t appkey_length;
          // If a new network is created then application key is created as
          // well because the appkeys are bound to network keys.
          // If the network already exists then it is not necessary to create
          // appkey because it has already been created.
          // Note: Output buffer is mandatory for create appkey API function
          sl_status_t sc = btmesh_prov_create_appkey(netkey_index,
                                                     APP_CONF_APPKEY_INDEX,
                                                     0,
                                                     NULL,
                                                     sizeof(appkey_data),
                                                     &appkey_length,
                                                     &appkey_data[0]);
          app_assert_status_f(sc, "Failed to create appkey" APP_LOG_NEW_LINE);
        }

        sc = btmesh_prov_setup_provisioning(netkey_index, command_uuid, HOST_PROV_PB_ADV, 0);
        app_assert_status_f(sc, "Provisioning failed" APP_LOG_NEW_LINE);
        command_state = IN_PROGRESS;
      }
      break;
    }
    case IN_PROGRESS:
      // Handle CBP if present, otherwise finish provisioning
      // MAC address is unknown here, but the database requires a bd_addr struct
      // so we use a 0 here.
      // Note: this won't affect provisioning as only UUID is used there
      btmesh_app_prov_handle_cbp(netkey_index, command_uuid, mac, HOST_PROV_PB_ADV);
      break;
    case FINISHED:
      prov_started = false;
      app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);
      app_log_nl();
      app_log_info("Provisioning session finished" APP_LOG_NEW_LINE);
      end_command();
      break;
    default:
      break;
  }
}

void handle_nodelist(void)
{
  switch (command_state) {
    case START: {
      // Check if any networks are present on the node on startup
      if (0 < networks_on_startup) {
        sl_status_t sc;
        app_log_info("Querying DDB list" APP_LOG_NEW_LINE);
        sc = btmesh_prov_list_ddb_entries(&ddb_count);
        if (SL_STATUS_OK != sc) {
          app_log_error("Failed to list DDB entries" APP_LOG_NEW_LINE);
          command_state = FINISHED;
          break;
        }
        if (ddb_count == 0) {
          // The count is synchronous, but individual nodes' info are sent
          // via sl_btmesh_on_event
          app_log_info("No nodes present in the network" APP_LOG_NEW_LINE);
          command_state = FINISHED;
        } else {
          command_state = IN_PROGRESS;
        }
      } else {
        app_log_info("No networks present on the device" APP_LOG_NEW_LINE);
        command_state = FINISHED;
      }
      break;
    }
    case IN_PROGRESS:
      // Wait for all nodes' information
      break;
    case FINISHED:
      end_command();
      break;
    default:
      break;
  }
}

void handle_nodeinfo(void)
{
  switch (command_state) {
    case START: {
      bool param_ready = true;
      if (app_prov_mode == PROV_UI_MODE) {
        param_ready = btmesh_app_prov_get_uuid_from_prov_list(&command_uuid);
      }
      if ((true == param_ready) && (true == db_ready)) {
        // Node information can only be obtained after the database is ready
        app_log_info("Querying node information" APP_LOG_NEW_LINE);
        app_log_nl();
        if (app_prov_mode == PROV_UI_MODE) {
          app_log_filter_threshold_set(APP_LOG_LEVEL_WARNING);
        }
        command_state = IN_PROGRESS;
        app_conf_print_nodeinfo_by_uuid(command_uuid);
      }
      break;
    }
    case IN_PROGRESS:
      // Wait for configurator to finish nodeinfo printing
      break;
    case FINISHED:
      app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);
      end_command();
      break;
    default:
      break;
  }
}

void handle_remove(void)
{
  switch (command_state) {
    case START: {
      sl_status_t sc;
      bool param_ready = true;
      if (app_prov_mode == PROV_UI_MODE) {
        param_ready = btmesh_app_prov_get_uuid_from_prov_list(&command_uuid);
      }
      if ((true == param_ready) && (true == db_ready)) {
        app_log_info("Unprovisioning..." APP_LOG_NEW_LINE);
        sc = btmesh_prov_remove_node_by_uuid(command_uuid,
                                             app_on_remove_node_job_status);
        if (SL_STATUS_OK != sc) {
          command_state = FINISHED;
        } else {
          command_state = IN_PROGRESS;
        }
        // DDB info is queried on startup
        command_state = IN_PROGRESS;
      }
      break;
    }
    case IN_PROGRESS:
      // Wait for confirmation callback
      break;
    case FINISHED:
      app_log_info("Refresh keys to prevent trashcan attacks." APP_LOG_NEW_LINE);
      end_command();
      break;
    default:
      break;
  }
}

void handle_key_refresh(void)
{
  switch (command_state) {
    case START: {
      sl_status_t sc;
      const uint8_t app_keys[] = { 0, 0 };
      sc = sl_btmesh_prov_phase_timeout_set(phase_timeout_s);
      app_log_status_f(sc, "Failed to set phase timeout" APP_LOG_NEW_LINE);
      sc = sl_btmesh_prov_start_key_refresh(0, 1, sizeof(app_keys), app_keys);
      app_assert_status_f(sc, "Key refresh failed" APP_LOG_NEW_LINE);
      app_log_info("Key refresh started" APP_LOG_NEW_LINE);
      command_state = IN_PROGRESS;
      break;
    }
    case IN_PROGRESS:
      // Wait for prov_key_refresh_complete event
      break;
    case FINISHED:
      end_command();
      break;
    default:
      break;
  }
}
void handle_key_export(void)
{
  switch (command_state) {
    case START:
      btmesh_key_export_start();
      command_state = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      btmesh_key_export_task();
      if (btmesh_key_export_is_idle()) {
        command_state = FINISHED;
      }
      break;
    case FINISHED:
      end_command();
      break;
    default:
      break;
  }
}

void handle_reset(void)
{
  switch (command_state) {
    case START:
      app_log_info("Initiating node reset" APP_LOG_NEW_LINE);
      sl_btmesh_node_reset();
      // Timer to let the NVM clear properly
      app_timer_start(&reset_timer,       // Timer pointer
                      RESET_TIMER_MS,           // Timer duration
                      app_on_reset_timer,       // Timer callback
                      NULL,                     // Timer data, not needed
                      false);                   // Not periodic
      command_state = IN_PROGRESS;
      break;
    case IN_PROGRESS:
      // Do nothing, timer callback will trigger next state
      break;
    case FINISHED: {
      btmesh_db_network_t *db_network = btmesh_db_network_get_network((uint16_t)APP_NETKEY_IDX);
      if (NULL != db_network) {
        btmesh_db_remove_network(db_network);
        networks_on_startup--;
      }
      app_log_info("Resetting hardware" APP_LOG_NEW_LINE);
      sl_bt_system_reset(sl_bt_system_boot_mode_normal);
      exit(EXIT_SUCCESS);
      break;
    }
    default:
      break;
  }
}

static void end_command(void)
{
  if (app_prov_mode == PROV_UI_MODE) {
    btmesh_app_prov_end_of_cmd();
  } else {
    exit(EXIT_SUCCESS);
  }
}

bool btmesh_app_prov_get_ddb_status(void)
{
  return db_ready;
}

void btmesh_app_prov_get_command(command_t *prov_command, command_state_t *prov_command_state)
{
  if (prov_command != NULL) {
    *prov_command = command;
  }
  if (prov_command_state != NULL) {
    *prov_command_state = command_state;
  }
}

void btmesh_app_prov_set_command(command_t prov_command)
{
  command = prov_command;
}

void btmesh_app_prov_set_command_state(command_state_t prov_command_state)
{
  command_state = prov_command_state;
}

void btmesh_app_prov_get_cmd_options(struct option **prov_options)
{
  *prov_options = prov_long_options;
}

void btmesh_app_prov_set_mode(prov_mode_t prov_mode)
{
  app_prov_mode = prov_mode;

  app_log_debug("Prov mode:  %s" APP_LOG_NEW_LINE, app_prov_mode == PROV_UI_MODE ? "PROV_UI_MODE" : "PROV_CMD_LINE_MODE");
}

prov_mode_t btmesh_app_prov_get_mode(void)
{
  return app_prov_mode;
}

uint16_t btmesh_app_prov_get_networks_number(void)
{
  return networks_on_startup;
}
// ----------------------------------------------------------------------------
// Callbacks

void btmesh_app_prov_on_nodeinfo_end(void)
{
  command_state = FINISHED;
}
void btmesh_prov_on_unprovisioned_node_list_evt(uint16_t id,
                                                uuid_128 uuid,
                                                uint16_t oob_capabilities)
{
  app_log_info("Unprovisioned node" APP_LOG_NEW_LINE);
  app_log_info("ID:      %d" APP_LOG_NEW_LINE, id);
  app_log_info("UUID:    ");
  btmesh_app_prov_append_uuid(&uuid);
  app_log_info("OOB Capabilities: 0x%04x" APP_LOG_NEW_LINE, oob_capabilities);
  app_log_nl();
}

void btmesh_prov_on_provisioned_node_list_evt(uint16_t id,
                                              uuid_128 uuid,
                                              uint16_t primary_address)
{
  app_log_info("Provisioned node" APP_LOG_NEW_LINE);
  app_log_info("ID:      %d" APP_LOG_NEW_LINE, id);

  app_log_info("UUID:    ");
  btmesh_app_prov_append_uuid(&uuid);

  app_log_info("Address: 0x%04x" APP_LOG_NEW_LINE, primary_address);
  app_log_nl();
}

void btmesh_app_prov_append_uuid(uuid_128 *uuid)
{
  app_log_append_info("%02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x" APP_LOG_NEW_LINE,
                      uuid->data[0],
                      uuid->data[1],
                      uuid->data[2],
                      uuid->data[3],
                      uuid->data[4],
                      uuid->data[5],
                      uuid->data[6],
                      uuid->data[7],
                      uuid->data[8],
                      uuid->data[9],
                      uuid->data[10],
                      uuid->data[11],
                      uuid->data[12],
                      uuid->data[13],
                      uuid->data[14],
                      uuid->data[15]);
}

void btmesh_prov_on_device_provisioned_evt(uint16_t address, uuid_128 uuid)
{
  app_log_info("Device provisioned" APP_LOG_NEW_LINE);
  app_log_info("UUID:    ");
  btmesh_app_prov_append_uuid(&uuid);
  app_log_info("Address: 0x%04x" APP_LOG_NEW_LINE, address);
  app_log_nl();

  if (PROV_UI_MODE == app_prov_mode) {
    app_log_filter_threshold_set(APP_LOG_LEVEL_WARNING);
  }

  sl_status_t sc = app_conf_start_node_configuration(APP_NETKEY_IDX,
                                                     address);
  if (SL_STATUS_OK != sc) {
    app_log_status_error_f(sc, "Failed to start configuration procedure." APP_LOG_NEW_LINE);
    command_state = FINISHED;
  }
}

void btmesh_prov_on_ddb_list_ready(uint16_t count)
{
  if (0 == count) {
    app_log_debug("No nodes in DDB" APP_LOG_NEW_LINE);
  } else {
    if (NODELIST == command) {
      // DDB list requested by user
      app_log_debug("All nodes in DDB listed" APP_LOG_NEW_LINE);
      // Finish only if not requested by UI mode
      command_state = FINISHED;
    }
  }
  // Some commands can only start after the database is ready
  db_ready = true;
}

void app_on_remove_node_job_status(const btmesh_conf_job_t *job)
{
  btmesh_prov_delete_ddb_entry(command_uuid);
  if (BTMESH_CONF_JOB_RESULT_SUCCESS == job->result) {
    app_log_info("Node removed from network" APP_LOG_NEW_LINE);
  } else {
    app_log_error("Remove node from network failed, removed from DDB anyway" APP_LOG_NEW_LINE);
  }
  command_state = FINISHED;
}

SL_WEAK void btmesh_app_prov_end_of_cmd(void)
{
  exit(EXIT_SUCCESS);
}

SL_WEAK void btmesh_app_prov_handle_ui(void)
{
}

SL_WEAK bool btmesh_app_prov_get_uuid_from_unprov_list(uuid_128 *command_uuid)
{
  (void)command_uuid;

  return true;
}

SL_WEAK bool btmesh_app_prov_get_uuid_from_prov_list(uuid_128 *command_uuid)
{
  (void)command_uuid;

  return true;
}

SL_WEAK void btmesh_app_prov_handle_cbp(uint16_t netkey_index,
                                        uuid_128 uuid,
                                        bd_addr mac_address,
                                        uint8_t bearer_type)
{
  // If CBP is not present, provisioning of the selected device must be started
  // at this point
  if (prov_started == false) {
    sl_status_t sc = btmesh_prov_provision_adv_device(netkey_index, uuid, mac_address, bearer_type, 0);
    app_assert_status_f(sc, "Provisioning failed" APP_LOG_NEW_LINE);
    prov_started = true;
  }
}

SL_WEAK void btmesh_app_prov_set_cbp_capability(bool capability)
{
  (void)capability;
}

// ----------------------------------------------------------------------------
// Private function definitions

static void app_on_scan_timer(app_timer_t *timer, void *data)
{
  command_state = FINISHED;
}

static void app_on_reset_timer(app_timer_t *timer, void *data)
{
  command_state = FINISHED;
}
