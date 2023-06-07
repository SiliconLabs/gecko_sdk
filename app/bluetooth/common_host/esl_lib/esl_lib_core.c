/***************************************************************************//**
 * @file
 * @brief ESL Host Library core component.
 *
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
#include <stdlib.h>
#include <unistd.h>
#include "ncp_host.h"
#include "app_log_cli.h"
#include "sl_bt_api.h"
#include "sl_bt_ots_client.h"
#include "sl_status.h"
#include "simple_argparse.h"
#include "esl_lib_command_list.h"
#include "esl_lib.h"
#include "esl_lib_core.h"
#include "esl_lib_connection.h"
#include "esl_lib_pawr.h"
#include "esl_lib_ap_control.h"
#include "app_timer.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

// Connection type values
#define NCP_CONN_TYPE_NOT_INITIALIZED 0
#define NCP_CONN_TYPE_SERIAL          'u'
#define NCP_CONN_TYPE_TCP             't'

// ESL library internal event codes
#define  ESL_LIB_EVT_CONNECTION_REQ_TIMEOUT        20
#define  ESL_LIB_EVT_CONNECTED                     21
#define  ESL_LIB_EVT_PARSING_SERVICES_DONE         22
#define  ESL_LIB_EVT_PARSING_CHARS_DONE            23
#define  ESL_LIB_EVT_SUBSCRIBED_TO_NOTIFICATION    24

// AD types
#define  AD_TYPE_INCOMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS 0x02
#define  AD_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS   0x03

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static void parse_config(char *config, esl_lib_ap_state_t *data);
static sl_status_t ap_init(esl_lib_ap_state_t **handle_out);
static void run_command(esl_lib_command_list_cmd_t *cmd);
static void esl_lib_core_step(void);
static void esl_lib_core_on_bt_event(sl_bt_msg_t *evt);
static sl_status_t send_core_error(esl_lib_status_t     lib_status,
                                   sl_status_t          status,
                                   esl_lib_core_state_t data);
static sl_status_t send_tag_found(uint8_t *addr,
                                  uint8_t addr_type,
                                  int8_t  rssi);
static sl_status_t send_scan_status(void);
static bool find_service_in_advertisement(uint8_t *data, uint8_t len);

// -----------------------------------------------------------------------------
// Private variables

// Access Point State
esl_lib_ap_state_t *ap_state = NULL;

/// Input argument set for initialization.
static struct argparse_descriptor_s arg_descriptor[] =
{
  { "-connection", "ip,serial" },   // define whatever key-value pairs you like
  { "-device", "" },                // empty string as option allows anything
  { "-baud", "115200,921600" },
  { "-handshake", "no,ctsrts,hw" }, // more options can be given where it's needed
  { NULL, NULL }
};

// -----------------------------------------------------------------------------
// Public functions

void esl_lib_init(char *config)
{
  sl_status_t sc;

  // Allocate and intialize radio data container
  sc = ap_init(&ap_state);
  if (sc != SL_STATUS_OK) {
    esl_lib_log_core_critical("Failed to allocate memory!" APP_LOG_NL);
    exit(EXIT_FAILURE);
  }

  // Parse configuration
  esl_lib_log_core_info("Parsing host library configuration: %s" APP_LOG_NL, config);
  parse_config(config, ap_state);
  esl_lib_log_core_info("AP host library instance started." APP_LOG_NL);

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    esl_lib_log_core_critical("Failed to initialize host library!" APP_LOG_NL);
    exit(EXIT_FAILURE);
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_core_critical("Error initializing host library: 0x%04x" APP_LOG_NL, sc);
    exit(EXIT_FAILURE);
  }
  esl_lib_log_core_info("NCP host initialised." APP_LOG_NL);
  esl_lib_log_core_info("Resetting NCP target..." APP_LOG_NL);
  // Reset NCP to ensure it gets into a defined state.
  // Once the chip successfully boots, boot event should be received.
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);

  // Initialize L2CAP transfer
  sli_bt_l2cap_transfer_init();

  // Initialize OTS Client
  sli_bt_ots_client_init();
}

void esl_lib_process_action(void)
{
  esl_lib_core_step();
  esl_lib_connection_step();
  esl_lib_pawr_step();
  esl_lib_image_transfer_step();
}

void esl_lib_deinit(void)
{
  // Clean command list
  esl_lib_command_list_cleanup(&ap_state->command_list);

  // Cleanup relationship
  esl_lib_connection_cleanup();
  esl_lib_pawr_cleanup();
  esl_lib_ap_control_cleanup();

  esl_lib_memory_free(ap_state);

  // Log memory status
  esl_lib_memory_log();

  ncp_host_deinit();
}

sl_status_t esl_lib_core_add_command(esl_lib_command_list_cmd_t *cmd)
{
  return esl_lib_command_list_put(&ap_state->command_list, cmd);
}

void sl_bt_on_event(sl_bt_msg_t *evt)
{
  esl_lib_core_on_bt_event(evt);
  esl_lib_connection_on_bt_event(evt);
  esl_lib_pawr_on_bt_event(evt);
  esl_lib_image_transfer_on_bt_event(evt);
  esl_lib_ap_control_on_bt_event(evt);
}

// -----------------------------------------------------------------------------
// Private functions

static void esl_lib_core_on_bt_event(sl_bt_msg_t *evt)
{
  sl_status_t      sc                 = SL_STATUS_OK;
  esl_lib_status_t lib_status         = ESL_LIB_STATUS_NO_ERROR;
  bool             lib_critical_error = false;
  esl_lib_evt_t    *new_event         = NULL;
  bd_addr          address;
  uint8_t          address_type;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      lib_status = ESL_LIB_STATUS_INIT_FAILED;
      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      if (sc != SL_STATUS_OK) {
        lib_critical_error = true;
      }

      esl_lib_log_core_info("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X" APP_LOG_NL,
                            address_type ? "static random" : "public device",
                            address.addr[5],
                            address.addr[4],
                            address.addr[3],
                            address.addr[2],
                            address.addr[1],
                            address.addr[0]);

      // Configure Security Manager to default
      sc = sl_bt_sm_configure(0,
                              sl_bt_sm_io_capability_noinputnooutput);
      if (sc != SL_STATUS_OK) {
        esl_lib_log_core_critical("Failed to configure SM, sc = 0x%04x" APP_LOG_NL, sc);
        lib_critical_error = true;
      }

      sc = sl_bt_sm_set_oob(false, NULL, NULL);
      if (sc != SL_STATUS_OK) {
        esl_lib_log_core_critical("Failed to clear local OOB, sc = 0x%04x" APP_LOG_NL, sc);
        lib_critical_error = true;
      }

      sc = sl_bt_sm_set_bondable_mode(true);
      if (sc != SL_STATUS_OK) {
        esl_lib_log_core_critical("Failed to set bondable mode, sc = 0x%04x" APP_LOG_NL, sc);
        lib_critical_error = true;
      }

      // Allocate and add event to the event list
      sc = esl_lib_event_list_allocate(ESL_LIB_EVT_SYSTEM_BOOT, 0, &new_event);
      if (sc == SL_STATUS_OK) {
        new_event->evt_code = ESL_LIB_EVT_SYSTEM_BOOT;
        new_event->data.evt_boot.status = SL_STATUS_OK;
        memcpy((void *)&new_event->data.evt_boot.address,
               (void *)&address,
               sizeof(bd_addr));
        sc = esl_lib_event_list_push_back(new_event);
      }
      if (sc != SL_STATUS_OK) {
        esl_lib_log_core_critical("Failed to allocate event list memory, sc = 0x%04x" APP_LOG_NL, sc);
        lib_critical_error = true;
      } else {
        lib_status = ESL_LIB_STATUS_NO_ERROR;
      }
      break;
    case sl_bt_evt_scanner_legacy_advertisement_report_id:
      if (find_service_in_advertisement(evt->data.evt_scanner_legacy_advertisement_report.data.data,
                                        evt->data.evt_scanner_legacy_advertisement_report.data.len)) {
        esl_lib_log_core_debug("Tag found with %s address: %02X:%02X:%02X:%02X:%02X:%02X , RSSI = %d" APP_LOG_NL,
                               evt->data.evt_scanner_legacy_advertisement_report.address_type ? "static random" : "public device",
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[5],
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[4],
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[3],
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[2],
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[1],
                               evt->data.evt_scanner_legacy_advertisement_report.address.addr[0],
                               evt->data.evt_scanner_legacy_advertisement_report.rssi);
        (void)send_tag_found(evt->data.evt_scanner_legacy_advertisement_report.address.addr,
                             evt->data.evt_scanner_legacy_advertisement_report.address_type,
                             evt->data.evt_scanner_legacy_advertisement_report.rssi);
      }
      break;
    case sl_bt_evt_system_resource_exhausted_id:
      lib_status = ESL_LIB_STATUS_RESOURCE_EXCEEDED;
      esl_lib_log_core_error("Resource exhausted" APP_LOG_NL);
      (void)send_core_error(lib_status,
                            SL_STATUS_ALLOCATION_FAILED,
                            ap_state->core_state);
      break;
    default:
      break;
  }
  if (lib_critical_error) {
    esl_lib_log_core_critical("Critical error, exiting..." APP_LOG_NL);
    // Send error
    (void)send_core_error(lib_status, sc, ap_state->core_state);
    // Exit on critical error
    exit(EXIT_FAILURE);
  }
}

/***************************************************************************//**
 * Parse configuration string.
 *
 * @param[in]  config Library configuration.
 * @param[out] rdata Radio data structure handle.
 ******************************************************************************/
static void parse_config(char *config, esl_lib_ap_state_t *data)
{
  sl_status_t sc;
  simple_argparse_parameter_pair_p parsed;
  simple_argparse_handle_p handle;
  int parsed_count;
  uint8_t conn_type = NCP_CONN_TYPE_NOT_INITIALIZED;

  sc = simple_argparse_init(arg_descriptor, &handle);
  if (sc != SL_STATUS_OK) {
    esl_lib_log_core_critical("Failed to initialize AP Host Library! sc = 0x%04x" APP_LOG_NL, sc);
    exit(EXIT_FAILURE);
  }

  int ret = simple_argparse_validate(handle, config, &parsed, &parsed_count);

  if (ret) {
    esl_lib_log_core_critical("Library argument parser error: status=%d, \"%s\" " APP_LOG_NL,
                              ret,
                              &config[parsed_count]);
    simple_argparse_deinit(handle);
    exit(EXIT_FAILURE);
  } else {
    esl_lib_log_core_info("AP Host Library parsed commands: %d" APP_LOG_NL, parsed_count);
    for (size_t i = 0; i < parsed_count; ++i) {
      esl_lib_log_core_info("%s : %s" APP_LOG_NL, parsed[i].arg, parsed[i].opt);

      if (strcmp(arg_descriptor[0].arg, parsed[i].arg) == 0) {
        // Connection type
        if (strcmp("ip", parsed[i].opt) == 0) {
          // TCP/IP connection
          conn_type = NCP_CONN_TYPE_TCP;
        } else if (strcmp("serial", parsed[i].opt) == 0) {
          // Serial connection
          conn_type = NCP_CONN_TYPE_SERIAL;
        }
      } else if (conn_type != NCP_CONN_TYPE_NOT_INITIALIZED
                 && strcmp(arg_descriptor[1].arg, parsed[i].arg) == 0) {
        // Device
        (void)ncp_host_set_option(conn_type, parsed[i].opt);
      } else if (strcmp(arg_descriptor[2].arg, parsed[i].arg) == 0) {
        // Baud rate
        (void)ncp_host_set_option('b', parsed[i].opt);
      } else if (strcmp(arg_descriptor[3].arg, parsed[i].arg) == 0) {
        // Flow control
        if (strcmp("no", parsed[i].opt) == 0) {
          (void)ncp_host_set_option('f', parsed[i].opt);
        }
      }
    }
  }

  sc = simple_argparse_deinit(handle);
  if (sc != SL_STATUS_OK) {
    esl_lib_log_core_critical("Failed to deinit arparse, sc = 0x%04x" APP_LOG_NL, sc);
    exit(EXIT_FAILURE);
  }
  esl_lib_log_core_info("AP Host Library initialized" APP_LOG_NL);
}

/***************************************************************************//**
 * Allocate and initialize radio data.
 *
 * @return Radio data pointer.
 ******************************************************************************/
static sl_status_t ap_init(esl_lib_ap_state_t **handle_out)
{
  sl_status_t sc = SL_STATUS_OK;

  esl_lib_ap_state_t *handle = esl_lib_memory_allocate(sizeof(esl_lib_ap_state_t));
  if (handle == NULL) {
    esl_lib_log_core_critical("Failed to allocate memory for AP library!" APP_LOG_NL);
    return SL_STATUS_ALLOCATION_FAILED;
  }
  // Configure default scanning parameters
  handle->scan.enabled                  = ESL_LIB_FALSE;
  handle->scan.configured               = ESL_LIB_FALSE;
  handle->scan.parameters.scanning_phy  = sl_bt_gap_phy_1m;
  handle->scan.parameters.discover_mode = sl_bt_scanner_discover_generic;
  handle->scan.parameters.mode          = sl_bt_scanner_scan_mode_passive;
  handle->scan.parameters.interval      = 16;
  handle->scan.parameters.window        = 16;
  handle->command_list                  = NULL;
  handle->command                       = NULL;
  handle->command_complete              = true;
  handle->core_state                    = ESL_LIB_CORE_STATE_IDLE;

  // Set output
  *handle_out = handle;

  return sc;
}

static sl_status_t send_scan_status(void)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  esl_lib_log_core_info("Scanning = %u" APP_LOG_NL, ap_state->scan.enabled);

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_SCAN_STATUS,
                                   0,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_SCAN_STATUS;
    // Copy status data
    memcpy(&lib_evt->data,
           &ap_state->scan,
           sizeof(esl_lib_scan_status_t));
    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_tag_found(uint8_t *addr,
                                  uint8_t addr_type,
                                  int8_t  rssi)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_TAG_FOUND,
                                   0,
                                   &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_TAG_FOUND;
    lib_evt->data.evt_tag_found.rssi = rssi;
    lib_evt->data.evt_tag_found.address.addr_type = addr_type;
    // Copy address
    memcpy(lib_evt->data.evt_tag_found.address.addr,
           addr,
           sizeof(bd_addr));

    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      // Free up memory on failure
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_core_error(esl_lib_status_t     lib_status,
                                   sl_status_t          status,
                                   esl_lib_core_state_t data)
{
  sl_status_t sc;
  esl_lib_node_id_t node_id;
  node_id.type = ESL_LIB_NODE_ID_TYPE_NONE;
  sc = esl_lib_event_push_error(lib_status,
                                &node_id,
                                status,
                                (esl_lib_status_data_t)data);
  return sc;
}

// Process single command.
static void run_command(esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t                sc                = SL_STATUS_FAIL;
  esl_lib_status_t           lib_status        = ESL_LIB_STATUS_NO_ERROR;

  if (cmd != NULL) {
    switch (cmd->cmd_code) {
      case ESL_LIB_CMD_AP_CONTROL_ADV_ENABLE:
        esl_lib_log_core_debug("Command: Enable AP control advertising" APP_LOG_NL);
        lib_status = ESL_LIB_STATUS_CONTROL_FAILED;
        if (cmd->data.cmd_ap_control.len == 1) {
          sc = esl_lib_ap_control_adv_enable(cmd->data.cmd_ap_control.data[0]);
          if (sc == SL_STATUS_OK) {
            lib_status = ESL_LIB_STATUS_NO_ERROR;
          }
        } else {
          sc = SL_STATUS_INVALID_PARAMETER;
        }
        if (sc != SL_STATUS_OK) {
          esl_lib_log_core_error("Failed to %s AP control adveritsing, sc = 0x%04x" APP_LOG_NL,
                                 (cmd->data.cmd_ap_control.data[0] == ESL_LIB_TRUE) ? "enable" : "disable",
                                 sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_AP_CONTROL_CP_RESPONSE:
        esl_lib_log_core_debug("Command: AP control CP response" APP_LOG_NL);
        lib_status = ESL_LIB_STATUS_CONTROL_FAILED;
        sc = esl_lib_ap_control_response(&cmd->data.cmd_ap_control);
        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_core_error("Failed to send AP control CP response, sc = 0x%04x" APP_LOG_NL, sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_AP_CONTROL_IT_RESPONSE:
        esl_lib_log_core_debug("Command: AP control IT response" APP_LOG_NL);
        lib_status = ESL_LIB_STATUS_CONTROL_FAILED;
        sc = esl_lib_ap_control_image_transfer_response(&cmd->data.cmd_ap_control);
        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_core_error("Failed to send AP control IT response, sc = 0x%04x" APP_LOG_NL, sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_AP_CONTROL_INIT_GATTDB:
        esl_lib_log_core_debug("Command: AP control init GATT DB" APP_LOG_NL);
        lib_status = ESL_LIB_STATUS_CONTROL_FAILED;
        sc = esl_lib_ap_control_init();
        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_core_error("Failed to initialize AP control GATTDB, sc = 0x%04x" APP_LOG_NL, sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_GET_SCAN_STATUS:
        send_scan_status();
        lib_status = ESL_LIB_STATUS_NO_ERROR;
        sc = SL_STATUS_OK;
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_SCAN_CONFIG:
        esl_lib_log_core_debug("Command: scan config" APP_LOG_NL);
        lib_status = ESL_LIB_STATUS_SCAN_CONFIG_FAILED;
        sc = sl_bt_scanner_set_parameters(cmd->data.cmd_scan_config.mode,
                                          cmd->data.cmd_scan_config.interval,
                                          cmd->data.cmd_scan_config.window);
        if (sc == SL_STATUS_OK) {
          // Save parameters
          ap_state->scan.parameters.mode          = cmd->data.cmd_scan_config.mode;
          ap_state->scan.parameters.interval      = cmd->data.cmd_scan_config.interval;
          ap_state->scan.parameters.window        = cmd->data.cmd_scan_config.window;
          ap_state->scan.parameters.scanning_phy  = cmd->data.cmd_scan_config.scanning_phy;
          ap_state->scan.parameters.discover_mode = cmd->data.cmd_scan_config.discover_mode;
          // Set configured state
          ap_state->scan.configured               = ESL_LIB_TRUE;
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_core_error("Failed to configure scanning, sc = 0x%04x" APP_LOG_NL, sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_SCAN_ENABLE:
        esl_lib_log_core_debug("Command: scan enable" APP_LOG_NL);
        if (cmd->data.cmd_scan_enable.enable == ESL_LIB_TRUE) {
          lib_status = ESL_LIB_STATUS_SCAN_START_FAILED;
          if (!(ap_state->scan.enabled == ESL_LIB_TRUE)) {
            sc = sl_bt_scanner_start(ap_state->scan.parameters.scanning_phy,
                                     ap_state->scan.parameters.discover_mode);
            if (sc == SL_STATUS_OK) {
              ap_state->scan.enabled = ESL_LIB_TRUE;
              lib_status = ESL_LIB_STATUS_NO_ERROR;
              send_scan_status();
            }
          } else {
            sc = SL_STATUS_INVALID_STATE;
          }
          ap_state->command_complete = true;
        } else {
          lib_status = ESL_LIB_STATUS_SCAN_STOP_FAILED;
          sc = sl_bt_scanner_stop();

          if (sc == SL_STATUS_OK) {
            ap_state->scan.enabled = ESL_LIB_FALSE;
            lib_status = ESL_LIB_STATUS_NO_ERROR;
            send_scan_status();
          }
        }
        if (sc != SL_STATUS_OK) {
          esl_lib_log_core_error("Failed to %s scanning, sc = 0x%04x" APP_LOG_NL,
                                 (cmd->data.cmd_scan_enable.enable == ESL_LIB_TRUE) ? "enable" : "disable",
                                 sc);
        }
        ap_state->command_complete = true;
        break;
      case ESL_LIB_CMD_CONNECT:
        esl_lib_log_core_debug("Command: connect" APP_LOG_NL);
        // Assume that the connect command is failed
        // and try to initiate the connection.
        lib_status = ESL_LIB_STATUS_CONN_FAILED;
        sc = esl_lib_connection_open(cmd, ESL_LIB_INVALID_HANDLE);
        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_NO_ERROR;
        } else {
          esl_lib_log_core_error("Failed to open connection, sc = 0x%04x" APP_LOG_NL, sc);
        }
        ap_state->command_complete = true;
        break;
      default:
        break; // default
    }
  }

  if (sc != SL_STATUS_OK) {
    esl_lib_node_id_t node_id;
    esl_lib_status_data_t status_data;
    status_data = (esl_lib_status_data_t)ap_state->core_state;
    node_id.type = ESL_LIB_NODE_ID_TYPE_NONE;
    esl_lib_log_core_error("Error in BT state machine, lib status = %d, sc = 0x%04x, core status = %d" APP_LOG_NL,
                           lib_status,
                           sc,
                           ap_state->core_state);
    // Send available data in the error message
    (void)esl_lib_event_push_error(lib_status,
                                   &node_id,
                                   sc,
                                   status_data);
    // Move to the next command in case of error
    ap_state->command_complete = true;
  }
}

// Process common commands.
static void esl_lib_core_step(void)
{
  esl_lib_command_list_cmd_t *cmd;

  if (ap_state->command_complete) {
    // If there is an ongoing but complete command, remove that.
    if (ap_state->command != NULL) {
      esl_lib_command_list_remove(&ap_state->command_list, ap_state->command);
      ap_state->command = NULL;
    }
    // Move and execute next command.
    cmd = esl_lib_command_list_get(&ap_state->command_list);
    if (cmd != NULL) {
      esl_lib_log_core_debug("Running next command = %d" APP_LOG_NL,
                             cmd->cmd_code);
      ap_state->command = cmd;
      ap_state->command_complete = false;
      run_command(ap_state->command);
    }
  }
}

// Parse advertisements looking for advertised ESL service
static bool find_service_in_advertisement(uint8_t *data, uint8_t len)
{
  uint8_t  ad_field_length;
  uint8_t  ad_field_type;
  uint8_t  i               = 0;
  uint8_t  esl_uuid_arr[2] = ESL_SERVICE_UUID;
  uint16_t esl_uuid        = *((uint16_t *)esl_uuid_arr);
  uint8_t  uuid_len        = sizeof(esl_uuid);
  uint16_t *ptr;

  if (len < 2 + uuid_len) {
    return 0;
  }
  // Parse advertisement packet
  while (i < len) {
    ad_field_length = data[i];
    ad_field_type   = data[i + 1];
    if (ad_field_type == AD_TYPE_INCOMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS
        || ad_field_type == AD_TYPE_COMPLETE_LIST_OF_16_BIT_SERVICE_CLASS_UUIDS) {
      for (uint8_t j = i + 2; j < i + ad_field_length + 1; j += sizeof(uint16_t)) {
        ptr = ((uint16_t *)&data[j]);
        if (*ptr == esl_uuid) {
          return true;
        }
      }
    }
    // advance to the next AD struct
    i = i + ad_field_length + 1;
  }
  return false;
}
