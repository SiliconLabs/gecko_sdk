/***************************************************************************//**
 * @file
 * @brief ABR initiator Example Project.
 *
 * Reference implementation of a ABR initiator host, which is
 * typically run on a host computer without radio. It can connect to a ABR enabled NCP via
 * VCOM to access the Bluetooth stack of the NCP and to control it using BGAPI.
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
#include <string.h>
#include "app.h"
#include "ncp_host.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "app_assert.h"
#include "sl_bt_api.h"
#include "abr_initiator.h"
#include "abr_file_log.h"

// Optstring argument for getopt.
#define OPTSTRING      NCP_HOST_OPTSTRING APP_LOG_OPTSTRING "hm:F:r"

// Usage info.
#define USAGE          APP_LOG_NL "%s " NCP_HOST_USAGE APP_LOG_USAGE " [-m <mode>] [-F <Reflector_BLE_address>] [-r] [-h]" APP_LOG_NL

// ABR Host Initiator options
#define ABR_HOST_INITIATOR_OPTIONS                                              \
  "    -m  HADM mode.\n"                                                        \
  "        <mode>           Integer representing HADM mode, default: 2, RTP.\n" \
  "        1 : RTT\n"                                                           \
  "        2 : RTP\n"                                                           \
  "    -F  Reflector filter address.\n"                                         \
  "        <reflector_address>\n"                                               \
  "    -r  Enable RSSI distance measurement\n"

// Options info.
#define OPTIONS              \
  "\nOPTIONS\n"              \
  NCP_HOST_OPTIONS           \
  APP_LOG_OPTIONS            \
  ABR_HOST_INITIATOR_OPTIONS \
  "    -h  Print this help message.\n"

static abr_initiator_config_t initiator_config;

static void abr_on_result(abr_rtl_result_t *result, void *user_data);
static uint8_t filter_address[ADR_LEN];

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  sl_status_t sc;
  int opt;
  int arg_adr_len;
  int abr_mode;
  unsigned int address_cache[ADR_LEN];
  bool rssi_measurement_enabled;

  // Default parameters
  sc = abr_initiator_config_set_default(&initiator_config);
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  rssi_measurement_enabled = false;

  for (uint8_t adr_iter = 0; adr_iter > ADR_LEN; adr_iter++) {
    address_cache[adr_iter] = 0;
  }
  arg_adr_len = 0;

  // Process command line options.
  while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (opt) {
      // Print help.
      case 'h':
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);
      case 'm':
        // Mode.
        // 1 - RTT
        // 2 - Phase based
        abr_mode = atoi(optarg);
        break;
      // Process options for other modules.
      case 'F':
        // Filter reflectors.
        arg_adr_len = sscanf(optarg, "%2X%2X%2X%2X%2X%2X",
                             &address_cache[5],
                             &address_cache[4],
                             &address_cache[3],
                             &address_cache[2],
                             &address_cache[1],
                             &address_cache[0]);
        break;
      case 'r':
        rssi_measurement_enabled = true;
        break;
      default:
        sc = ncp_host_set_option((char)opt, optarg);
        if (sc == SL_STATUS_NOT_FOUND) {
          sc = app_log_set_option((char)opt, optarg);
        }
        if (sc != SL_STATUS_OK) {
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        break;
    }
  }

  switch (abr_mode) {
    case ABR_INITIATOR_MODE_RTT: // RTT
      initiator_config.mode = sl_bt_cs_mode_rtt;
      initiator_config.submode = 0xff;
      break;
    case ABR_INITIATOR_MODE_PBR: // PBR
      initiator_config.mode = sl_bt_cs_mode_pbr;
      initiator_config.submode = sl_bt_cs_mode_rtt;
      break;
    default:
      app_log_error("Invalid operation mode selected. "
                    "Please select either 1 (RTT) or 2 (PBR)" APP_LOG_NL);
      exit(EXIT_FAILURE);
      break;
  }

  initiator_config.rssi_measurement_enabled = rssi_measurement_enabled;

  if (arg_adr_len == ADR_LEN) {
    for (uint8_t adr_iter = 0; adr_iter < ADR_LEN; adr_iter++) {
      filter_address[adr_iter] = (uint8_t)address_cache[adr_iter];
    }
    initiator_config.filter_address = filter_address;
  } else {
    app_log_info("Accepting any suitable reflector." APP_LOG_NL);
  }

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  app_assert_status(sc);
  app_log_info("NCP host initialised." APP_LOG_NL);
  app_log_info("Resetting NCP target..." APP_LOG_NL);
  // Reset NCP to ensure it gets into a defined state.
  // Once the chip successfully boots, boot event should be received.
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);

  app_log_info("Press Crtl+C to quit" APP_LOG_NL APP_LOG_NL);

  // rewrite the content of output distance file
  FILE* output_distance_storage = fopen("distance.txt", "w");
  fclose(output_distance_storage);

  abr_initiator_init(abr_on_result, &initiator_config);
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
  bd_addr address;
  uint8_t address_type;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Print boot message.
      app_log_info("Bluetooth stack booted: v%d.%d.%d-b%d" APP_LOG_NL,
                   evt->data.evt_system_boot.major,
                   evt->data.evt_system_boot.minor,
                   evt->data.evt_system_boot.patch,
                   evt->data.evt_system_boot.build);
      abr_file_log_app_version(evt->data.evt_system_boot.major,
                               evt->data.evt_system_boot.minor,
                               evt->data.evt_system_boot.patch,
                               evt->data.evt_system_boot.build);
      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);
      app_log_info("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X" APP_LOG_NL,
                   address_type ? "static random" : "public device",
                   address.addr[5],
                   address.addr[4],
                   address.addr[3],
                   address.addr[2],
                   address.addr[1],
                   address.addr[0]);

      abr_initiator_enable();

      break;

    default:
      // All other event is handled by the initiator.
      bt_on_event_initiator(evt);
      break;
  }
}

static void abr_append_data_to_log_file(const char* filename, float data)
{
  FILE* logfile = fopen(filename, "a");
  app_assert(logfile != NULL, "Failed to open file '%s'", filename);
  fprintf(logfile, "%f\n", data);
  fclose(logfile);
}

static void abr_on_result(abr_rtl_result_t *result, void *user_data)
{
  (void) user_data;
  app_log_info("Measurement result: %u mm",
               (uint32_t)(result->distance * 1000.f));

  if (initiator_config.rssi_measurement_enabled) {
    app_log_append_info(" | RSSI distance: %u mm" APP_LOG_NL,
                        (uint32_t)(result->rssi_distance * 1000.f));
    abr_append_data_to_log_file("distance_rssi.txt", result->rssi_distance);
  } else {
    app_log_append_info(APP_LOG_NL);
  }

  abr_append_data_to_log_file("distance.txt", result->distance);
}
