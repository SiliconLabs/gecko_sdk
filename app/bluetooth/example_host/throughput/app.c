/***************************************************************************//**
 * @file
 * @brief Throughput test application.
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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "app.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "throughput_central.h"
#include "throughput_ui_types.h"
#include "throughput_types.h"
#include "cf_parse.h"
#include "sl_bt_api.h"
#include "app_assert.h"
#include "throughput_central_interface.h"
#include "ncp_host.h"

// Optstring argument for getopt.
#define OPTSTRING NCP_HOST_OPTSTRING APP_LOG_OPTSTRING "o:p:i:M:T:D:c:hn"

// Usage info.
#define USAGE APP_LOG_NL "%s " NCP_HOST_USAGE APP_LOG_USAGE " [-T <time> | -D <data_length>] [-p <phy>] [-i <interval>] [-M <mtu>] [-n] [-c <config>] [-o <log>] [-h]" APP_LOG_NL

// Options info.
#define OPTIONS                                                                            \
  "\nOPTIONS\n"                                                                            \
  NCP_HOST_OPTIONS                                                                         \
  APP_LOG_OPTIONS                                                                          \
  "    -T  Select fixed time mode.\n"                                                      \
  "        <time>           Measurement duration in seconds\n"                             \
  "    -D  Select fixed data length mode.\n"                                               \
  "        <data_length>    Measurement data length in bytes\n"                            \
  "    -p  Select PHY type.\n"                                                             \
  "        <phy>            1 (1M, default), 2 (2M), 4 (Coded, 125k) or 8 (Coded, 500k)\n" \
  "    -i  Set connection interval.\n"                                                     \
  "        <interval>       Connection interval in milliseconds\n"                         \
  "    -M  Set Maximum Transmission Unit (MTU) size.\n"                                    \
  "        <mtu>            Size of the MTU in bytes\n"                                    \
  "    -n  If given, notification is used. Default is indication.\n"                       \
  "    -c  Configuration file.\n"                                                          \
  "        <config>         Path to the configuration file\n"                              \
  "    -o  Log file.\n"                                                                    \
  "        <log>            Path to the log file\n"                                        \
  "    -h  Print this help message.\n"

#define MAX_LOG_LINE_LEN              1024
#define LOG_INTERVAL                  60.0

typedef struct {
  uint16_t connection_interval;
  uint8_t phy;
  uint16_t mtu_size;
  uint8_t client_conf_flag;
  uint8_t mode;
  uint32_t fixed_amount;
} throughput_test_parameters_t;

static sl_status_t open_log_file(char *filename);
static void log_step(void);
static sl_status_t write_log_entry(float time, throughput_value_t throughput);

static throughput_test_parameters_t test_parameters;

static int logfile_descriptor = -1;
static float last_log_time;
static bool log_enabled = false;

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  int opt;
  sl_status_t sc;
  char *configuration;

  last_log_time = timer_end();

// Set default parameters

  test_parameters.connection_interval = 40;
  test_parameters.phy = sl_bt_gap_1m_phy_uncoded;
  test_parameters.mtu_size = 250;
  test_parameters.mode = THROUGHPUT_MODE_CONTINUOUS;
  test_parameters.client_conf_flag = sl_bt_gatt_indication;

// These constants are used for input validation

  #define MAX_DATA 10000000
  #define MIN_DATA 1000
  #define MAX_DURATION 600
  #define MIN_DURATION 1
  #define MIN_INTERVAL 20
  #define MIN_MTU 23
  #define MAX_MTU 250

  configuration = NULL;

  // Parse command line arguments
  while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (opt) {
      case 'o': //Log data to file
        open_log_file(optarg);
        break;
      case 'T': //Fixed time
        test_parameters.fixed_amount = strtoul(optarg, NULL, 0);
        test_parameters.mode = THROUGHPUT_MODE_FIXED_TIME;
        break;
      case 'D': //Fixed data length
        test_parameters.fixed_amount = strtoul(optarg, NULL, 0);
        test_parameters.mode = THROUGHPUT_MODE_FIXED_LENGTH;
        break;
      case 'p': //PHY to use
        test_parameters.phy = (uint8_t) strtoul(optarg, NULL, 0);
        break;
      case 'i': //Connection interval
        test_parameters.connection_interval = (uint16_t) strtoul(optarg, NULL, 0);
        break;
      case 'M': //MTU size
        test_parameters.mtu_size = strtoul(optarg, NULL, 0);
        break;
      case 'n': //Notifiaction or indication?
        test_parameters.client_conf_flag = sl_bt_gatt_notification;
        break;
      case 'c': //Parse config file
        app_log("Parsing config file %s..." APP_LOG_NL, optarg);
        configuration = cf_parse_load_file(optarg);
        break;
      case 'h': //Help!
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);
        break;
      default: //Process options for other modules.
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

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }

  if (configuration != NULL) {
    uint8_t address[6];
    uint8_t address_type;

    cf_parse_init(configuration);
    while (cf_parse_allowlist(address, &address_type) == SL_STATUS_OK) {
      throughput_central_allowlist_add(address);
    }
    cf_parse_deinit();
  } else {
    app_log_info("No configuration." APP_LOG_NL);
  }

  //Sanity check of command line arguments

  if (test_parameters.mode == THROUGHPUT_MODE_FIXED_LENGTH
      && (test_parameters.fixed_amount < MIN_DATA || test_parameters.fixed_amount > MAX_DATA)) {
    app_log_critical("Fixed data must be between %u and %u." APP_LOG_NL, MIN_DATA, MAX_DATA);
    exit(EXIT_FAILURE);
  }

  if (test_parameters.mode == THROUGHPUT_MODE_FIXED_TIME
      && (test_parameters.fixed_amount < MIN_DURATION || test_parameters.fixed_amount > MAX_DURATION)) {
    app_log_critical("Fixed time must be between %u and %u." APP_LOG_NL, MIN_DURATION, MAX_DURATION);
    exit(EXIT_FAILURE);
  }

  if (test_parameters.connection_interval < MIN_INTERVAL) {
    app_log_critical("Connection interval should be or above 20 (20 * 1.25 = 25 ms)." APP_LOG_NL);
    exit(EXIT_FAILURE);
  }

  if (test_parameters.mtu_size < MIN_MTU || test_parameters.mtu_size > MAX_MTU) {
    app_log_critical("MTU should be between %u and %u." APP_LOG_NL, MIN_MTU, MAX_MTU);
    exit(EXIT_FAILURE);
  }

  if (test_parameters.phy != 1 && test_parameters.phy != 2 && test_parameters.phy != 4 ) {
    app_log_critical("PHY must be one of these: 1 => 1M, 2 => 2M, 4 => 125k, 8 => 500k" APP_LOG_NL);
    exit(EXIT_FAILURE);
  }

  app_log_info("Resetting NCP..." APP_LOG_NL);
  // Reset NCP to ensure it gets into a defined state.
  // Once the chip successfully boots, boot event should be received.
  sl_bt_system_reset(0);

  // App specific init
}

/**************************************************************************//**
 * Bluetooth event handler
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_system_boot_id:
      // Print boot message.
      app_log_info("Bluetooth stack booted: v%d.%d.%d-b%d" APP_LOG_NL,
                   evt->data.evt_system_boot.major,
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

      // Enable the Central component
      throughput_central_enable();

      // configure the component
      sc = throughput_central_set_mode(test_parameters.mode, test_parameters.fixed_amount);
      app_assert_status(sc);
      sc = throughput_central_set_mtu_size(test_parameters.mtu_size);
      app_assert_status(sc);
      sc = throughput_central_set_type(test_parameters.client_conf_flag);
      app_assert_status(sc);
      break;
    default:
      bt_on_event_central(evt);
      break;
  }
}

/**************************************************************************//**
 * Application step functions
 *****************************************************************************/
void app_process_action(void)
{
  throughput_central_step();
  timer_step_rssi();
  log_step();
}

/**************************************************************************//**
 * State change callback implementation
 *****************************************************************************/
void throughput_central_on_state_change(throughput_state_t state)
{
  static bool have_work = true;
  log_enabled = false;

  #ifdef SL_CATALOG_THROUGHPUT_UI_PRESENT
  throughput_ui_set_state(state);
  throughput_ui_update();
  #else
  switch (state) {
    case THROUGHPUT_STATE_CONNECTED:
      app_log_info(THROUGHPUT_UI_STATE_CONNECTED_TEXT);
      break;
    case THROUGHPUT_STATE_DISCONNECTED:
      app_log_info(THROUGHPUT_UI_STATE_DISCONNECTED_TEXT);
      break;
    case THROUGHPUT_STATE_SUBSCRIBED:
      app_log_info(THROUGHPUT_UI_STATE_SUBSCRIBED_TEXT);
      if (test_parameters.mode == THROUGHPUT_MODE_FIXED_TIME || test_parameters.mode == THROUGHPUT_MODE_FIXED_LENGTH) {
        if (have_work) {
          app_log_nl();
          throughput_central_start();
          have_work = false;
        } else {
          //This is the normal exit point of the program
          exit(EXIT_SUCCESS);
        }
      }
      break;
    case THROUGHPUT_STATE_TEST:
      app_log_info(THROUGHPUT_UI_STATE_TEST_TEXT);
      if (logfile_descriptor > 0) {
        log_enabled = true;
      }
      break;
    default:
      app_log_info(THROUGHPUT_UI_STATE_UNKNOWN_TEXT);
      break;
  }
  app_log_nl();
  #endif
}

/**************************************************************************//**
 * Open data log file
 *****************************************************************************/
static sl_status_t open_log_file(char *filename)
{
  sl_status_t ret_val;

  app_log_info("Opening log file %s..." APP_LOG_NL, filename);

  logfile_descriptor = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

  if (logfile_descriptor == -1) {
    ret_val = SL_STATUS_FAIL;
    app_log_warning("Error opening log file %s." APP_LOG_NL, filename);
  } else {
    ret_val = SL_STATUS_OK;
  }

  return ret_val;
}

/**************************************************************************//**
 * Write log record to the log file
 *****************************************************************************/
static sl_status_t write_log_entry(float time, throughput_value_t throughput)
{
  sl_status_t ret_val = SL_STATUS_OK;
  static bool first_call = true;
  char line[MAX_LOG_LINE_LEN];
  static uint64_t line_id = 0;
  int ret = 0;

  if (logfile_descriptor == -1) {
    ret_val = SL_STATUS_NOT_INITIALIZED;
  } else {
    if (first_call == true) {
      ret = snprintf(line, MAX_LOG_LINE_LEN, "ID, Time [s], Throughput [bps]\n\n");
      if (ret > 0) {
        ret = write(logfile_descriptor, line, ret);
        first_call = false;
      } else {
        ret_val = SL_STATUS_NOT_INITIALIZED;
      }
    }
    ret = snprintf(line, MAX_LOG_LINE_LEN, "%llu, %f, %u\n", line_id, time, throughput);
    if (ret > 0) {
      ret = write(logfile_descriptor, line, ret);
      line_id++;
    } else {
      ret_val = SL_STATUS_NOT_INITIALIZED;
    }
  }

  if (ret < 0) {
    ret_val = SL_STATUS_NOT_INITIALIZED;
  }

  return ret_val;
}

/**************************************************************************//**
 * Check if we have to log
 *****************************************************************************/
static void log_step(void)
{
  float now;
  throughput_value_t throughput;

  if (log_enabled) {
    now = throughput_central_calculate(&throughput);

    if (now < last_log_time) {
      last_log_time = now;
    }

    if (now - last_log_time >= LOG_INTERVAL) {
      write_log_entry(now, throughput);
      last_log_time = now;
    }
  }
}

/**************************************************************************//**
 * Application deinit
 *****************************************************************************/
void app_deinit(void)
{
  app_log_info("Shutting down." APP_LOG_NL);
  ncp_host_deinit();
  if (logfile_descriptor > 0) {
    close(logfile_descriptor);
  }
}
