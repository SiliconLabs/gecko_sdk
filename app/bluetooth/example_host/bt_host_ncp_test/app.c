/***************************************************************************//**
 * @file
 * @brief Network Co-Processor (NCP) tester host application.
 * Demonstrates the communication between an NCP host and NCP target using
 * BGAPI user messages, responses and events. Can be used as a starting point
 * for creating custom commands or for testing purposes.
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
#include "app.h"
#include "ncp_host.h"
#include "ncp_user_cmd.h"
#include "test.h"
#include "app_log.h"
#include "app_log_cli.h"
#include "app_assert.h"
#include "sl_bt_api.h"

// Optstring argument for getopt.
#define OPTSTRING   NCP_HOST_OPTSTRING APP_LOG_OPTSTRING "c:w:i:e:h"

// Usage info.
#define USAGE       APP_LOG_NL "%s " NCP_HOST_USAGE APP_LOG_USAGE " -c <command id> [-w <width>] [-i <interval>] [-e <end>] [-h]" APP_LOG_NL

// Options info.
#define OPTIONS                                                                           \
  "\nOPTIONS\n"                                                                           \
  NCP_HOST_OPTIONS                                                                        \
  APP_LOG_OPTIONS                                                                         \
  "    -c  User BGAPI command ID. Defines which test case shall be executed.\n"           \
  "          %d:  USER_CMD_PERIODIC_ASYNC_ID (Used parameters: width, interval, end)\n"   \
  "          %d:  USER_CMD_GET_BOARD_NAME_ID\n"                                           \
  "          %d:  USER_CMD_PERIODIC_SYNC_ID (Used parameters: width, end)\n"              \
  "    -w  Length of the user event messages.\n"                                          \
  "        <width>          Length in bytes, min: 1, max: 255, default: %d\n"             \
  "                         In case a test fails experiment decreasing this parameter.\n" \
  "    -i  Time interval between user events.\n"                                          \
  "        <interval>       Interval in milliseconds, min: 1, max: 255, default: %d\n"    \
  "                         In case a test fails experiment increasing this parameter.\n" \
  "    -e  Number of user event messages to wait for before the test terminates.\n"       \
  "        <end>            Number of events, min: 1, max: 2147483647, default: %d\n"     \
  "    -h  Print this help message.\n",                                                   \
  USER_CMD_PERIODIC_ASYNC_ID,                                                             \
  USER_CMD_GET_BOARD_NAME_ID,                                                             \
  USER_CMD_PERIODIC_SYNC_ID,                                                              \
  TEST_LENGTH_DEFAULT,                                                                    \
  TEST_INTERVAL_DEFAULT,                                                                  \
  TEST_COUNT_STOP_DEFAULT

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
void app_init(int argc, char *argv[])
{
  sl_status_t sc;
  int opt, val;

  test_config_t test_config = {
    .command_id = TEST_COMMAND_ID_NOT_SPECIFIED,
    .length = TEST_LENGTH_DEFAULT,
    .interval = TEST_INTERVAL_DEFAULT,
    .count_stop = TEST_COUNT_STOP_DEFAULT
  };

  // Process command line options.
  while ((opt = getopt(argc, argv, OPTSTRING)) != -1) {
    switch (opt) {
      // Print help.
      case 'h':
        app_log(USAGE, argv[0]);
        app_log(OPTIONS);
        exit(EXIT_SUCCESS);

      // Command ID (test case).
      case 'c':
        val = atoi(optarg);
        if ((val <= 0) || (val > UINT8_MAX)) {
          app_log("Invalid value for option -%c: %s" APP_LOG_NL, opt, optarg);
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        test_config.command_id = (uint8_t)val;
        break;

      // Length.
      case 'w':
        val = atoi(optarg);
        if ((val <= 0) || (val > UINT8_MAX)) {
          app_log("Invalid value for option -%c: %s" APP_LOG_NL, opt, optarg);
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        test_config.length = (uint8_t)val;
        break;

      // Interval.
      case 'i':
        val = atoi(optarg);
        if ((val <= 0) || (val > UINT8_MAX)) {
          app_log("Invalid value for option -%c: %s" APP_LOG_NL, opt, optarg);
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        test_config.interval = (uint8_t)val;
        break;

      // End.
      case 'e':
        val = atoi(optarg);
        if ((val <= 0) || (val > UINT32_MAX)) {
          app_log("Invalid value for option -%c: %s" APP_LOG_NL, opt, optarg);
          app_log(USAGE, argv[0]);
          exit(EXIT_FAILURE);
        }
        test_config.count_stop = val;
        break;

      // Process options for other modules.
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

  // Validate command ID and log test case with corresponding parameters
  switch (test_config.command_id) {
    case TEST_COMMAND_ID_NOT_SPECIFIED:
      app_log("Command ID is a mandatory argument and was not specified." APP_LOG_NL);
      app_log(USAGE, argv[0]);
      exit(EXIT_FAILURE);
      break;

    case USER_CMD_PERIODIC_ASYNC_ID:
      app_log("Test case:\n\t%d\nParameters:\n\twidth = %d\n\tinterval = %d\n\tend = %d\n",
              test_config.command_id,
              test_config.length,
              test_config.interval,
              test_config.count_stop);
      break;

    case USER_CMD_PERIODIC_ASYNC_STOP_ID:
      app_log("The USER_CMD_PERIODIC_ASYNC_STOP_ID command cannot be called "
              "directly. Use USER_CMD_PERIODIC_ASYNC_ID instead." APP_LOG_NL);
      app_log(USAGE, argv[0]);
      exit(EXIT_FAILURE);
      break;

    case USER_CMD_GET_BOARD_NAME_ID:
      app_log("Test case:\n\t%d\nParameters:\n\tNone\n", test_config.command_id);
      break;

    case USER_CMD_PERIODIC_SYNC_ID:
      app_log("Test case:\n\t%d\nParameters:\n\twidth = %d\n\tend = %d\n",
              test_config.command_id,
              test_config.length,
              test_config.count_stop);
      break;

    default:
      app_log("Invalid Command ID." APP_LOG_NL);
      app_log(USAGE, argv[0]);
      exit(EXIT_FAILURE);
      break;
  }

  // Initialize NCP connection.
  sc = ncp_host_init();
  if (sc == SL_STATUS_INVALID_PARAMETER) {
    app_log(USAGE, argv[0]);
    exit(EXIT_FAILURE);
  }
  app_assert_status(sc);
  app_log_info("NCP host initialised." APP_LOG_NL);
  app_log_info("Press Crtl+C to quit" APP_LOG_NL APP_LOG_NL);

  test_init(test_config);
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
