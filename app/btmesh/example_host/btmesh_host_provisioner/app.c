/***************************************************************************//**
* @file
* @brief BT Mesh Host Provisioner Example Project - CLI mode handler.
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
*******************************************************************************/

// -----------------------------------------------------------------------------
// Includes

// standard library headers
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <getopt.h>

#include "app.h"
#include "ncp_host.h"
#include "app_log.h"
#include "app_assert.h"
#include "sl_common.h"
#include "sl_bt_api.h"
#include "sl_btmesh_api.h"
#include "sl_bt_api.h"
#include "sl_btmesh_ncp_host.h"
#include "sl_bt_ncp_host.h"
#include "sl_ncp_evt_filter_common.h"

#include "btmesh_app_prov.h"
#include "btmesh_prov.h"
#include "btmesh_conf.h"

#ifdef SL_CATALOG_APP_REMOTE_PROV_PRESENT
#ifdef SL_CATALOG_APP_PROV_CBP_PRESENT
#include "btmesh_app_prov_cbp.h"
#endif // SL_CATALOG_APP_PROV_CBP_PRESENT
#include "btmesh_app_remote_prov.h"
#include "btmesh_remote_prov.h"
#else
#ifdef SL_CATALOG_APP_PROV_CBP_PRESENT
#include "btmesh_app_prov_cbp.h"
#endif // SL_CATALOG_APP_PROV_CBP_PRESENT
#include "app_prov_only.h"
#endif // SL_CATALOG_APP_REMOTE_PROV_PRESENT

// -----------------------------------------------------------------------------
// Macros

// This characteristic handle value has to match the value in gatt_db.h of
// NCP empty example running on the connected WSTK.
#define GATTDB_SYSTEM_ID    18

// -----------------------------------------------------------------------------
// Static Variables

// -----------------------------------------------------------------------------
// Static Function Declarations

/***************************************************************************//**
* Filter not needed NCP events
*
* @param[in] event_id ID of the event to filter
* @return Status of the stack call
*******************************************************************************/
static sl_status_t app_add_user_event_filter(const uint32_t event_id);

/***************************************************************************//**
*  Command line long options struct array build
*
* @param[in] long_options Options struct array address
*******************************************************************************/
static void btmesh_app_build_long_options(struct option *long_options);

// -----------------------------------------------------------------------------
// Function definitions

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  sl_status_t sc = SL_STATUS_FAIL;
  int opt;
  prov_mode_t app_mode = PROV_UI_MODE;
  static struct option long_options[LONG_OPT_SIZE];

  app_log_filter_threshold_set(APP_LOG_LEVEL_INFO);

  btmesh_app_build_long_options(long_options);

  int option_index = 0;
  // Process command line options.
  while ((opt = getopt_long(argc, argv, OPTSTRING, long_options, &option_index)) != -1) {
    switch (opt) {
      // Print help.
      case '?':
      case 'h':
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);

      // Process options for other modules
      default:
        sc = btmesh_app_prov_init(opt, optarg);

        if (sc != SL_STATUS_OK) {
          sc = btmesh_cbp_on_check_cmd_options(opt, optarg);
        }

        if (sc != SL_STATUS_OK) {
          sc = btmesh_app_on_check_cmd_options(opt, optarg);
        }

        if (sc != SL_STATUS_OK) {
          sc = ncp_host_set_option((char)opt, optarg);
          if (sc != SL_STATUS_OK) {
            app_log(USAGE, argv[0]);
            exit(EXIT_FAILURE);
          }
        } else {
          app_mode = PROV_CMD_LINE_MODE;
        }
        break;
    }
  }

  //set the app_prov mode
  btmesh_app_prov_set_mode(app_mode);

  // Initialize NCP connection
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  app_assert_status(sc);

  SL_BTMESH_API_REGISTER();

  app_log_info("Empty NCP-host initialised." APP_LOG_NEW_LINE);
  app_log_info("Resetting NCP..." APP_LOG_NEW_LINE);
  // Reset NCP to ensure it gets into a defined state
  // Once the chip successfully boots, boot event should be received
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up                                     //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Deinit.
 *****************************************************************************/
void app_deinit(void)
{
  ncp_host_deinit();

  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application deinit code here!                       //
  // This is called once during termination.                                 //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
    {
      // Filter legacy and new scanner report events as it would send a message
      // every 5 ms and clog UART while scanning for unprovisioned nodes
      sc = app_add_user_event_filter(sl_bt_evt_scanner_scan_report_id);
      app_assert_status_f(sc, "Failed to enable filtering on the target" APP_LOG_NEW_LINE);

      sc = app_add_user_event_filter(sl_bt_evt_scanner_legacy_advertisement_report_id);
      app_assert_status_f(sc, "Failed to enable filtering on the target" APP_LOG_NEW_LINE);

      sc = app_add_user_event_filter(sl_bt_evt_scanner_extended_advertisement_report_id);
      app_assert_status_f(sc, "Failed to enable filtering on the target" APP_LOG_NEW_LINE);

      // Print boot message.
      app_log_info("Bluetooth stack booted: v%d.%d.%d-b%d" APP_LOG_NEW_LINE,
                   evt->data.evt_system_boot.major,
                   evt->data.evt_system_boot.minor,
                   evt->data.evt_system_boot.patch,
                   evt->data.evt_system_boot.build);

      // Initialize Mesh stack in Provisioner mode,
      // wait for initialized event
      app_log_info("Provisioner init" APP_LOG_NEW_LINE);
      sc = sl_btmesh_prov_init();
      app_assert_status_f(sc, "Failed to init provisioner\n");
      sc = btmesh_prov_init_provisioning_records();
      app_assert_status_f(sc, "Failed to init provisioning records\n");
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
}

/**************************************************************************//**
 * Bluetooth Mesh stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth Mesh stack.
 *****************************************************************************/
void sl_btmesh_on_event(sl_btmesh_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_prov_initialized_id: {
      // Device successfully initialized in provisioner mode
      sl_btmesh_evt_prov_initialized_t *initialized_evt;
      initialized_evt = (sl_btmesh_evt_prov_initialized_t *)&(evt->data);

      app_log_info("Network initialized" APP_LOG_NEW_LINE);
      app_log_info("Networks: %x" APP_LOG_NEW_LINE, initialized_evt->networks);
      app_log_info("Address : %x" APP_LOG_NEW_LINE, initialized_evt->address);
      app_log_info("IV Index: %x" APP_LOG_NEW_LINE, initialized_evt->iv_index);

      break;
    }
    case sl_btmesh_evt_prov_initialization_failed_id: {
      // Device failed to initialize in provisioner mode
      sl_btmesh_evt_prov_initialization_failed_t *initialization_failed_evt;
      initialization_failed_evt = (sl_btmesh_evt_prov_initialization_failed_t *)&(evt->data);
      uint16_t res = initialization_failed_evt->result;
      if (0 != res) {
        app_log_status_error_f(res, "Failed to initialize provisioning node" APP_LOG_NEW_LINE);
      }
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
}

//-------------------------------------
// Helper functions
void btmesh_app_build_long_options(struct option *long_options)
{
  struct option *source_options = NULL;

  memset(long_options, 0, LONG_OPT_SIZE * sizeof(struct option));
  btmesh_app_prov_get_cmd_options(&source_options);
  memcpy(long_options, source_options, PROV_OPTLENGTH * sizeof(struct option));

  btmesh_app_on_build_cmd_options(long_options + PROV_OPTLENGTH);
  btmesh_cbp_on_build_cmd_options(long_options + PROV_OPTLENGTH + REMOTE_PROV_OPTLENGTH);
}

void app_parse_uuid(char *input, size_t length, uuid_128 *parsed_uuid)
{
  // Sanity check, do nothing if length is incorrect
  if (UUID_LEN_WITHOUT_SEPARATORS == length
      || UUID_LEN_WITH_SEPARATORS == length) {
    for (size_t count = 0; count < 16; count++) {
      sscanf(input, "%2hhx", &parsed_uuid->data[count]);
      // If data is in AA:BB:CC format move the pointer by 3 bytes and
      // skip the separator, otherwise move by 2 bytes
      input += (UUID_LEN_WITHOUT_SEPARATORS == length ? 2 : 3);
    }
  }
}

void app_parse_address(char *input, size_t length, uint16_t *address)
{
  // Sanity check, do nothing if length is incorrect
  if (ADDRESS_LEN_WITHOUT_PREFIX == length
      || ADDRESS_LEN_WITH_PREFIX == length) {
    if (ADDRESS_LEN_WITH_PREFIX == length) {
      // Discard prefix if address is in 0x1234 format
      input += 2;
    }
    sscanf(input, "%4hx", address);
  }
}

sl_status_t app_add_user_event_filter(const uint32_t event_id)
{
  sl_status_t sc = SL_STATUS_OK;
  uint8_t user_data[SL_NCP_EVT_FILTER_CMD_ADD_LEN];

  user_data[0] = SL_NCP_EVT_FILTER_CMD_ADD_ID;
  user_data[1] = event_id >> 0;
  user_data[2] = event_id >> 8;
  user_data[3] = event_id >> 16;
  user_data[4] = event_id >> 24;

  sc = sl_bt_user_manage_event_filter(SL_NCP_EVT_FILTER_CMD_ADD_LEN, user_data);
  return sc;
}

// -----------------------------------------------------------------------------
// Callbacks

void btmesh_prov_on_provision_failed_evt(uint8_t reason, uuid_128 uuid)
{
  command_state_t prov_command_state;

  btmesh_app_prov_get_command(NULL, &prov_command_state);

  if (prov_command_state == IN_PROGRESS) {
    btmesh_app_prov_set_command_state(FINISHED);
  }

  btmesh_app_on_provision_failed();
}

void app_on_node_configuration_end(uint16_t netkey_index,
                                   uint16_t server_address)
{
  command_state_t prov_command_state;

  btmesh_app_prov_get_command(NULL, &prov_command_state);

  if (prov_command_state == IN_PROGRESS) {
    btmesh_app_prov_set_command_state(FINISHED);
  }

  btmesh_app_on_node_configuration_end();
}

//-------------------------------------
// Weak function definitions
SL_WEAK void btmesh_app_on_provision_failed(void)
{
}

SL_WEAK void btmesh_app_on_node_configuration_end(void)
{
}

SL_WEAK void btmesh_app_on_build_cmd_options(struct option *long_options)
{
  (void)long_options;
}

SL_WEAK void btmesh_cbp_on_build_cmd_options(struct option *long_options)
{
  (void)long_options;
}

SL_WEAK sl_status_t btmesh_app_on_check_cmd_options(int cmd_opt, char *cmd_optarg)
{
  (void)cmd_opt;
  (void)cmd_optarg;

  return SL_STATUS_NOT_FOUND;
}

SL_WEAK sl_status_t btmesh_cbp_on_check_cmd_options(int cmd_opt, char *cmd_optarg)
{
  (void)cmd_opt;
  (void)cmd_optarg;

  return SL_STATUS_NOT_FOUND;
}

SL_WEAK sl_status_t btmesh_prov_init_provisioning_records(void)
{
  return SL_STATUS_OK;
}
