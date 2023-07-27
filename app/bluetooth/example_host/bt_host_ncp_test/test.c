/***************************************************************************//**
 * @file
 * @brief Bluetooth Network Co-Processor test module.
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
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sl_status.h"
#include "sl_bt_api.h"
#include "app_log.h"
#include "app.h"
#include "ncp_user_cmd.h"
#include "test.h"

#define test_assert(expr, ...)                                    \
  do {                                                            \
    if (!(expr)) {                                                \
      app_log_error("Test failed at [%s]." APP_LOG_NL, __func__); \
      app_log_error(__VA_ARGS__);                                 \
      app_log_nl();                                               \
      app_deinit();                                               \
      exit(EXIT_FAILURE);                                         \
    }                                                             \
  } while (0)

static void test_periodic_async(void);
static void test_periodic_async_stop(void);
static void test_get_board_name(void);
static void test_periodic_sync(void);
static sl_status_t message_to_target_helper(size_t send_data_len,
                                            uint8_t *send_data,
                                            size_t response_data_len,
                                            uint8_t *response_data);

static uint8_t test_data[UINT8_MAX];
static uint32_t event_count = 0;
static uint32_t response_count = 0;

static test_config_t test_config; // NCP test parameters

/**************************************************************************//**
 * Initialize NCP test module.
 *****************************************************************************/
void test_init(test_config_t config)
{
  srand(time(NULL));
  memcpy((void *)&test_config, (void *)&config, sizeof(test_config_t));
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
      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      test_assert(sc == SL_STATUS_OK,
                  "sl_bt_system_get_identity_address failed: 0x%04x",
                  (int)sc);
      app_log_info("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X",
                   address_type ? "static random" : "public device",
                   address.addr[5],
                   address.addr[4],
                   address.addr[3],
                   address.addr[2],
                   address.addr[1],
                   address.addr[0]);
      app_log_nl();

      // Start testing.
      event_count = 0;
      response_count = 0;

      switch (test_config.command_id) {
        case USER_CMD_PERIODIC_ASYNC_ID:
          test_periodic_async();
          break;

        case USER_CMD_PERIODIC_ASYNC_STOP_ID:
          test_periodic_async_stop();
          break;

        case USER_CMD_GET_BOARD_NAME_ID:
          test_get_board_name();
          break;

        case USER_CMD_PERIODIC_SYNC_ID:
          test_periodic_sync();
          break;

        default:
          break;
      }
      break;

    // -------------------------------
    // User event handler.
    case sl_bt_evt_user_message_to_host_id:
      test_assert(test_config.command_id == evt->data.evt_user_message_to_host.message.data[0],
                  "Unexpected event. Expected command id: %d. Received command id: %d.",
                  test_config.command_id,
                  evt->data.evt_user_message_to_host.message.data[0]);

      switch (evt->data.evt_user_message_to_host.message.data[0]) {
        case USER_CMD_PERIODIC_ASYNC_ID:
          app_log_info("Event received. Count: %d" APP_LOG_NL, event_count);
          test_assert(evt->data.evt_user_message_to_host.message.len == test_config.length,
                      "Incorrect event length: %d.",
                      evt->data.evt_user_message_to_host.message.len);

          test_data[0] = USER_CMD_PERIODIC_ASYNC_ID;
          memset((void *)&test_data[1], (uint8_t)(event_count & 0xff), test_config.length);
          test_assert(0 == memcmp((void *)&test_data[1], (void *)&evt->data.evt_user_message_to_host.message.data[1], test_config.length - 1),
                      "Incorrect event data.");

          event_count++;
          if (event_count >= test_config.count_stop) {
            app_log_info("Test passed. Invoking USER_CMD_PERIODIC_ASYNC_STOP_ID command." APP_LOG_NL);
            test_periodic_async_stop();
          }
          break;

        case USER_CMD_PERIODIC_SYNC_ID:
          app_log_info("Event received. Count: %d" APP_LOG_NL, event_count);
          test_assert(evt->data.evt_user_message_to_host.message.len == test_config.length,
                      "Incorrect event length: %d.",
                      evt->data.evt_user_message_to_host.message.len);
          test_assert(0 == memcmp(test_data, evt->data.evt_user_message_to_host.message.data, test_config.length),
                      "Incorrect event data.");

          event_count++;
          if (event_count < test_config.count_stop) {
            test_periodic_sync();
          } else {
            app_log_info("Test passed." APP_LOG_NL);
            app_deinit();
            exit(EXIT_SUCCESS);
          }
          break;

        default:
          test_assert(false,
                      "Invalid user command: %d",
                      evt->data.evt_user_message_to_host.message.data[0]);
          break;
      }
      break;

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}

/**************************************************************************//**
 * Start Asynchronous periodic test.
 *****************************************************************************/
static void test_periodic_async(void)
{
  sl_status_t sc;
  uint8_t send_data[3] = {
    USER_CMD_PERIODIC_ASYNC_ID,
    test_config.interval,
    test_config.length
  };
  uint8_t response_data[1];

  app_log_info("Test [%d]: Periodic asynchronous." APP_LOG_NL,
               USER_CMD_PERIODIC_ASYNC_ID);

  sc = message_to_target_helper(sizeof(send_data),
                                send_data,
                                sizeof(response_data),
                                response_data);

  test_assert(sc == SL_STATUS_OK,
              "Periodic asynchronous test failed: 0x%04x",
              (int)sc);
  test_assert(response_data[0] == USER_CMD_PERIODIC_ASYNC_ID,
              "Incorrect response data: %d",
              response_data[0]);
  app_log_info("Command response received. Waiting for event(s)..." APP_LOG_NL);
}

/**************************************************************************//**
 * Stop Asynchronous periodic test.
 *****************************************************************************/
static void test_periodic_async_stop(void)
{
  sl_status_t sc;
  uint8_t send_data[1] = { USER_CMD_PERIODIC_ASYNC_STOP_ID };
  uint8_t response_data[1];

  app_log_info("Test [%d]: Stopping Asynchronous periodic test." APP_LOG_NL,
               USER_CMD_PERIODIC_ASYNC_STOP_ID);

  sc = message_to_target_helper(sizeof(send_data),
                                send_data,
                                sizeof(response_data),
                                response_data);

  test_assert(sc == SL_STATUS_OK,
              "Stop Asynchronous periodic test failed: 0x%04x",
              (int)sc);
  test_assert(response_data[0] == USER_CMD_PERIODIC_ASYNC_STOP_ID,
              "Incorrect response data: %d",
              response_data[0]);
  app_log_info("Command response received. Test passed." APP_LOG_NL);
  app_deinit();
  exit(EXIT_SUCCESS);
}

/**************************************************************************//**
 * Start Get Board Name test.
 *****************************************************************************/
static void test_get_board_name(void)
{
  sl_status_t sc;
  uint8_t send_data = USER_CMD_GET_BOARD_NAME_ID;
  char response_data[USER_RSP_GET_BOARD_NAME_LEN + 1];

  app_log_info("Test [%d]: Get Board Name." APP_LOG_NL,
               USER_CMD_GET_BOARD_NAME_ID);

  sc = message_to_target_helper(sizeof(send_data),
                                &send_data,
                                USER_RSP_GET_BOARD_NAME_LEN,
                                (uint8_t *)response_data);

  test_assert(sc == SL_STATUS_OK,
              "Get Board Name test failed: 0x%04x",
              (int)sc);
  response_data[USER_RSP_GET_BOARD_NAME_LEN] = '\0'; // Place null character at the end
  app_log_info("Command response received. Detected board: %s. Test Passed." APP_LOG_NL,
               response_data);
  app_deinit();
  exit(EXIT_SUCCESS);
}

/**************************************************************************//**
 * Start Synchronous periodic test.
 *****************************************************************************/
static void test_periodic_sync(void)
{
  sl_status_t sc;
  test_data[0] = USER_CMD_PERIODIC_SYNC_ID;
  for (size_t i = 1; i < test_config.length; i++) {
    test_data[i] = rand() % 0xff;
  }
  uint8_t response_data[UINT8_MAX];

  app_log_info("Test [%d]: Periodic synchronous." APP_LOG_NL,
               USER_CMD_PERIODIC_SYNC_ID);

  sc = message_to_target_helper(test_config.length,
                                test_data,
                                test_config.length,
                                response_data);

  test_assert(sc == SL_STATUS_OK,
              "Periodic synchronous test failed: 0x%04x",
              (int)sc);
  test_assert(0 == memcmp(test_data, response_data, test_config.length),
              "Incorrect response data.");
  app_log_info("Command response received. Count: %d. Waiting for event..." APP_LOG_NL, response_count);
  response_count++;
}

/**************************************************************************//**
 * Helper for the tests.
 *
 * @param[in] send_data_len Length of the data to send in the user command
 * @param[in] send_data Data to send in the user command
 * @param[in] response_data_len The expected length of the response data
 * @param[out] response_data Received data in the user command response
 *****************************************************************************/
static sl_status_t message_to_target_helper(size_t send_data_len,
                                            uint8_t *send_data,
                                            size_t response_data_len,
                                            uint8_t *response_data)
{
  sl_status_t sc;
  size_t response_len_temp;
  uint8_t response_data_temp[UINT8_MAX];

  sc = sl_bt_user_message_to_target(send_data_len,
                                    send_data,
                                    sizeof(response_data_temp),
                                    &response_len_temp,
                                    response_data_temp);

  if (sc != SL_STATUS_OK) {
    return sc;
  } else if (response_len_temp != response_data_len) {
    return SL_STATUS_BT_ATT_INVALID_ATT_LENGTH;
  }

  memcpy((void *)response_data,
         (void *)response_data_temp,
         response_data_len);
  return SL_STATUS_OK;
}
