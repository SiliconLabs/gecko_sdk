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
#include <sys/time.h>
#include "app.h"
#include "ncp_host.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "app_assert.h"
#include "sl_bt_api.h"
#include "abr_initiator.h"
#include "abr_file_log.h"
#include "host_comm.h"

// Optstring argument for getopt.
#define OPTSTRING      NCP_HOST_OPTSTRING APP_LOG_OPTSTRING HOST_COMM_CPC_OPTSTRING "hd:m:F:rw"

// Usage info.
#define USAGE          APP_LOG_NL "%s " NCP_HOST_USAGE APP_LOG_USAGE HOST_COMM_CPC_USAGE \
  "\n[-d <json_log_directory>] [-m <mode>] [-F <Reflector_BLE_address>] [-r] [-w] [-h]" APP_LOG_NL

// ABR Host Initiator options
#define ABR_HOST_INITIATOR_OPTIONS                                              \
  "    -d  JSON log directory.\n"                                               \
  "        <log_directory>\n"                                                   \
  "    -m  HADM mode.\n"                                                        \
  "        <mode>           Integer representing HADM mode, default: 2, PBR.\n" \
  "        1 : RTT\n"                                                           \
  "        2 : PBR\n"                                                           \
  "    -F  Reflector filter address.\n"                                         \
  "        <reflector_address>\n"                                               \
  "    -r  Enable RSSI distance measurement\n"                                  \
  "    -w  Use wired antenna offset\n"

// Options info.
#define OPTIONS              \
  "\nOPTIONS\n"              \
  NCP_HOST_OPTIONS           \
  APP_LOG_OPTIONS            \
  ABR_HOST_INITIATOR_OPTIONS \
  HOST_COMM_CPC_OPTIONS      \
  "    -h  Print this help message.\n"

#define USECSPERSEC 1000000UL

// Distance log file handles
FILE *distance_log_file       = NULL;
FILE *distance_log_file_rssi  = NULL;

// Distance log file names
#define DISTANCE_LOG_FILE       "distance.csv"
#define DISTANCE_LOG_FILE_RSSI  "distance_rssi.csv"

static abr_initiator_config_t initiator_config;

static void abr_on_result(abr_rtl_result_t *result, void *user_data);
static void abr_append_data_to_log_file(FILE *fp, const char *data);
static void abr_open_log_files(void);
static void abr_close_log_files(void);
static uint8_t filter_address[ADR_LEN];
static uint64_t measurement_counter;
static struct timeval tv_start;

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
  bool use_antenna_wired_offset;

  app_log_info("Silicon Labs ABR Initiator" APP_LOG_NL);
  app_log_info("--------------------------" APP_LOG_NL);

  // Default parameters
  sc = abr_initiator_config_set_default(&initiator_config);
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  rssi_measurement_enabled = false;
  use_antenna_wired_offset = false;

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
      case 'd':
        abr_file_log_set_dir(optarg);
        break;
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
      case 'w':
        use_antenna_wired_offset = true;
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
      break;
    case ABR_INITIATOR_MODE_PBR: // PBR
      initiator_config.mode = sl_bt_cs_mode_pbr;
      break;
    default:
      app_log_error("Invalid operation mode selected. "
                    "Please select either 1 (RTT) or 2 (PBR)" APP_LOG_NL);
      exit(EXIT_FAILURE);
      break;
  }

  initiator_config.rssi_measurement_enabled = rssi_measurement_enabled;
  initiator_config.use_antenna_wired_offset = use_antenna_wired_offset;

  if (arg_adr_len == ADR_LEN) {
    for (uint8_t adr_iter = 0; adr_iter < ADR_LEN; adr_iter++) {
      filter_address[adr_iter] = (uint8_t)address_cache[adr_iter];
    }
    initiator_config.filter_address = filter_address;
  } else {
    app_log_info("Accepting any suitable reflector." APP_LOG_NL);
  }

  // Log channel map
  app_log_info("CS channel map:" APP_LOG_NL "    ");
  for (uint32_t i = 0; i < initiator_config.channel_map_len; i++) {
    app_log_append_info("0x%02x ", initiator_config.channel_map.data[i]);
  }
  app_log_append_info(APP_LOG_NL);

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  app_assert_status(sc);
  app_log_info("NCP host initialised." APP_LOG_NL);
  app_log_info("Press Crtl+C to quit" APP_LOG_NL APP_LOG_NL);

  abr_open_log_files();
  abr_initiator_init(abr_on_result, &initiator_config);
  measurement_counter = 0;
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
  struct timeval tv_end;
  int ret;
  uint64_t run_time;
  double measurements_frequency;

  ret = gettimeofday(&tv_end, NULL);
  abr_initiator_deinit();
  ncp_host_deinit();

  if (ret == 0 && measurement_counter > 0) {
    run_time = (tv_end.tv_sec - tv_start.tv_sec)
               * USECSPERSEC + tv_end.tv_usec - tv_start.tv_usec;

    if (run_time > 0) {
      measurements_frequency =
        (double)(USECSPERSEC * measurement_counter) / run_time;
      app_log("Measurement frequency = %f\n", measurements_frequency);
    }
  }

  abr_close_log_files();

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

static void abr_append_data_to_log_file(FILE *fp, const char *data)
{
  if (fp != NULL && data != NULL) {
    fprintf(fp, "%s", data);
    fflush(fp); // Flush file buffer to avoid data loss
  }
}

static void abr_open_log_files(void)
{
  // Open empty files for distance results
  distance_log_file = fopen(DISTANCE_LOG_FILE, "w");
  if (distance_log_file != NULL) {
    fprintf(distance_log_file, "distance,distance_likeliness\n");
  } else {
    app_log_error("Failed to open file '%s'" APP_LOG_NL, DISTANCE_LOG_FILE);
  }

  if (initiator_config.rssi_measurement_enabled) {
    distance_log_file_rssi = fopen(DISTANCE_LOG_FILE_RSSI, "w");
    if (distance_log_file_rssi != NULL) {
      fprintf(distance_log_file_rssi, "rssi_distance\n");
    } else {
      app_log_error("Failed to open file '%s'" APP_LOG_NL, DISTANCE_LOG_FILE_RSSI);
    }
  }
}

static void abr_close_log_files(void)
{
  int ret;
  if (distance_log_file != NULL) {
    ret = fclose(distance_log_file);
    if (ret != 0) {
      app_log_error("Failed to close distance log file." APP_LOG_NL);
    }
  }
  if (distance_log_file_rssi != NULL) {
    ret = fclose(distance_log_file_rssi);
    if (ret != 0) {
      app_log_error("Failed to close RSSI distance log file." APP_LOG_NL);
    }
  }
}

static void abr_on_result(abr_rtl_result_t *result, void *user_data)
{
  int ret;
  (void) user_data;
  char log_buff[100]; // File log buffer
  size_t log_buff_size = sizeof(log_buff);

  app_log_info("Measurement result: %u mm" APP_LOG_NL,
               (uint32_t)(result->distance * 1000.f));

  app_log_info("Measurement likeliness: %f" APP_LOG_NL,
               result->likeliness);

  if (initiator_config.rssi_measurement_enabled) {
    app_log_info("RSSI distance: %u mm" APP_LOG_NL,
                 (uint32_t)(result->rssi_distance * 1000.f));

    memset(log_buff, 0, log_buff_size);
    ret = snprintf(log_buff, log_buff_size, "%f\n", result->rssi_distance);
    if (ret >= 0) {
      abr_append_data_to_log_file(distance_log_file_rssi, log_buff);
    } else {
      app_log_error("Failed to write buffer used by file log!" APP_LOG_NL);
    }
  }

  app_log_info("CS bit error rate: %u" APP_LOG_NL, result->cs_bit_error_rate);

  memset(log_buff, 0, log_buff_size);
  ret = snprintf(log_buff, log_buff_size, "%f,%f\n", result->distance, result->likeliness);
  if (ret >= 0) {
    abr_append_data_to_log_file(distance_log_file, log_buff);
  } else {
    app_log_error("Failed to write buffer used by file log!" APP_LOG_NL);
  }

  ret = 0;
  if (measurement_counter == 0) {
    // Get starting time
    ret = gettimeofday(&tv_start, NULL);
  }
  measurement_counter++;
  if (ret == -1) {
    measurement_counter = 0;
  }
}
