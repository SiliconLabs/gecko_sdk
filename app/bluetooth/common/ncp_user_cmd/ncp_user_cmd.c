/***************************************************************************//**
 * @file
 * @brief BGAPI user command handler.
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

#include "sl_ncp.h"
#include "sl_malloc.h"
#include "app_timer.h"
#include "ncp_user_cmd.h"

PACKSTRUCT(struct periodic_event_test_s {
  uint8_t interval;
  uint8_t length;
});
typedef struct periodic_event_test_s periodic_event_test_t;

PACKSTRUCT(struct user_cmd {
  uint8_t hdr;
  // Example: union of user commands.
  union {
    uint8_t echo[254];
    periodic_event_test_t periodic_event_test;
  } data;
});

typedef struct user_cmd user_cmd_t;

#ifndef SL_BOARD_NAME
#define SL_BOARD_NAME "UNKNOWN!"
#endif
static char board_name[USER_RSP_GET_BOARD_NAME_LEN + 1] = SL_BOARD_NAME;

static void test_timer_callback(app_timer_t *timer, void *data);

static app_timer_t test_timer;
static uint8_t *test_data;
static uint8_t test_length = 0;
static uint8_t test_interval = 0;
static uint32_t test_count = 0;

/***************************************************************************//**
 * User command (message_to_target) handler callback.
 *
 * Handles user defined commands received from NCP host.
 * The user commands handled here are solely meant for example purposes.
 * If not needed, this function can be removed entirely or replaced with a
 * custom one.
 * @param[in] data Data received from NCP host.
 *
 * @note This overrides the dummy weak implementation.
 ******************************************************************************/
void sl_ncp_user_cmd_message_to_target_cb(void *data)
{
  uint8array *cmd = (uint8array *)data;
  user_cmd_t *user_cmd = (user_cmd_t *)cmd->data;
  sl_status_t sc;

  switch (user_cmd->hdr) {
    case USER_CMD_PERIODIC_ASYNC_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Example: Respond, then send events with the given interval until the
      // USER_CMD_PERIODIC_ASYNC_STOP_ID command is received.
      test_length = user_cmd->data.periodic_event_test.length;
      test_interval = user_cmd->data.periodic_event_test.interval;
      test_count = 0;

      // Allocate memory for test array
      if (test_data != NULL) {
        sl_free(test_data);
        test_data = NULL;
      }

      test_data = (uint8_t *)sl_malloc(test_length * sizeof(uint8_t));

      if (test_data == NULL) {
        sc = SL_STATUS_ALLOCATION_FAILED;
      } else {
        sc = app_timer_start(&test_timer,
                             (uint32_t)test_interval,
                             test_timer_callback,
                             NULL,
                             true);
      }

      // Send response to user command to NCP host.
      sl_ncp_user_cmd_message_to_target_rsp(sc, 1, &user_cmd->hdr);
      break;

    case USER_CMD_PERIODIC_ASYNC_STOP_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Example: Stop sending events that were started when the
      // USER_CMD_PERIODIC_ASYNC_ID command was received.
      sc = app_timer_stop(&test_timer);
      // Send response to user command to NCP host.
      sl_ncp_user_cmd_message_to_target_rsp(sc, 1, &user_cmd->hdr);
      break;

    case USER_CMD_GET_BOARD_NAME_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Example: Sending back board name.
      // Send response to user command to NCP host.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK,
                                            strlen(board_name),
                                            (uint8_t *)board_name);
      break;

    case USER_CMD_RESPONSE_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Example: Send back received command as a response.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK, cmd->len, cmd->data);
      break;

    case USER_CMD_PERIODIC_SYNC_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Example: Send back received command as a response and then as an event.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK, cmd->len, cmd->data);
      sl_ncp_user_evt_message_to_host(cmd->len, cmd->data);
      break;

    /////////////////////////////////////////////////
    // Add further user command handler code here! //
    /////////////////////////////////////////////////

    // Unknown user command.
    default:
      // Send error response to NCP host.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_FAIL, 0, NULL);
      break;
  }
}

static void test_timer_callback(app_timer_t *timer, void *data)
{
  (void)timer;
  (void)data;
  // Generate test data with the given length using the counter.
  test_data[0] = USER_CMD_PERIODIC_ASYNC_ID;
  memset((void *)&test_data[1], (uint8_t)(test_count & 0xff), test_length);

  // Send event to NCP host.
  sl_ncp_user_evt_message_to_host(test_length, test_data);
  test_count++;
}
