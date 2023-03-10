/***************************************************************************//**
* @file
* @brief BT Mesh Host Provisioner Example Project - UI mode handler.
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

#include "app.h"
#include "app_assert.h"
#include "app_log.h"
#include "app_sleep.h"
#include "btmesh_app_prov.h"
#include "btmesh_prov.h"
#include "sl_common.h"

#include "btmesh_app_prov_ui.h"
#ifdef SL_CATALOG_APP_REMOTE_PROV_PRESENT
#include "btmesh_app_remote_prov_ui.h"
#endif

#include <pthread.h>
#include <string.h>

// -----------------------------------------------------------------------------
// Macros

#if defined(POSIX) && POSIX == 1
  #define CLEARSCR "clear"
  #include <stdio.h>
  #include <sys/select.h>
  #include <unistd.h>
#else
  #define CLEARSCR "cls"
  #include <windows.h>
  #include <conio.h>
#endif // defined(POSIX) && POSIX == 1

/// Buffer length for user input
#define INPUT_BUFFER_LEN 100
/// Time to sleep between user input checking in microseconds
#define INPUT_SLEEP_US 10000

// -----------------------------------------------------------------------------
// Static Function Declarations

/***************************************************************************//**
* Helper script to print instructions for provisioning
*
*******************************************************************************/
static void select_unprovisioned_node_instruction(void);

/***************************************************************************//**
* Helper script to print instructions for unprovisioning
*
*******************************************************************************/
static void select_provisioned_node_instruction(void);

/***************************************************************************//**
* The user input handler called in a new thread
*
* @param[in] ptr Unused
*******************************************************************************/
static void *handle_input(void *ptr);

/***************************************************************************//**
* Peek the standard input
*
* @param[out] buf Character array to save the input to
* @param[in] buffer_length Length of buffer
* @param[out] num_read Actual number of characters read
* @return Status of the peek.
* @retval true If user input is ready
* @retval false If user input is still being processed
*******************************************************************************/
static bool peek_stdin(char *buf, int buffer_length, int *num_read);

// -----------------------------------------------------------------------------
// Static Variables

static volatile bool run = true;
/// Flag indicating the user input is ready to be processed
static volatile bool input_ready = false;
/// Flag indicating the end of command execution
static volatile bool command_end = false;
/// User input handler thread
static pthread_t thread_input;
/// Buffer for user input
static char input_buffer[INPUT_BUFFER_LEN];
/// UI state
sl_ui_state ui_state = UI_MENU;

// -----------------------------------------------------------------------------
// Public function definitions

void btmesh_app_prov_handle_ui(void)
{
  switch (ui_state) {
    case UI_MENU: {
      system(CLEARSCR);
      app_log(PROV_UI_MENU);
      input_ready = false;
      ui_state = UI_WAITING_FOR_CMD;
      if (0 == thread_input) {
        int ret = pthread_create(&thread_input, NULL, handle_input, NULL);
        if (0 != ret) {
          app_log_critical("Failed to create input thread!" APP_LOG_NL);
          exit(EXIT_FAILURE);
        }
      }
      break;
    }
    case UI_WAITING_FOR_CMD:
      if (true == input_ready) {
        char c = input_buffer[0];
        switch (c) {
          case SCAN_COMMAND:
            btmesh_app_prov_set_command(SCAN);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case PROVISION_COMMAND:
            btmesh_app_prov_set_command(PROVISION);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case NODELIST_COMMAND:
            btmesh_app_prov_set_command(NODELIST);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case NODEINFO_COMMAND:
            btmesh_app_prov_set_command(NODEINFO);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case REMOVE_NODE_COMMAND:
            btmesh_app_prov_set_command(REMOVE_NODE);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case KEY_REFRESH_COMMAND:
            btmesh_app_prov_set_command(KEY_REFRESH);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case KEY_EXPORT_COMMAND:
            btmesh_app_prov_set_command(KEY_EXPORT);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case RESET_COMMAND:
            btmesh_app_prov_set_command(RESET);
            btmesh_app_prov_set_command_state(START);
            ui_state = UI_CMD_PROCESSING;
            break;
          case EXIT_COMMAND:
            ui_state = UI_EXIT;
            run = false;
            break;
          default: {
            sl_status_t sc = btmesh_app_prov_ui_handle_remote_prov_cmd(c);
            if (SL_STATUS_OK != sc) {
              btmesh_app_prov_end_of_cmd();
            } else {
              ui_state = UI_CMD_PROCESSING;
            }
            break;
          }
        }
      }
      break;
    case UI_CMD_PROCESSING:
      break;
    case UI_WAITING_FOR_INPUT:
      if ((true == input_ready) && (true == command_end)) {
        command_end = false;
        ui_state = UI_MENU;
      }
      break;

    case UI_EXIT:
      run = false;
      pthread_join(thread_input, NULL);
      //btmesh_prov_free_remote_serverlist();
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
  }
}

void btmesh_app_prov_end_of_cmd(void)
{
  btmesh_app_prov_set_command(NONE);
  btmesh_app_prov_set_command_state(START);
  app_log_nl();
  app_log("Press enter to continue..." APP_LOG_NEW_LINE);
  input_ready = false;
  command_end = true;
  ui_state = UI_WAITING_FOR_INPUT;
}

bool btmesh_app_prov_get_uuid_from_unprov_list(uuid_128 *command_uuid)
{
  bool return_value = false;
  sl_status_t sc;

  if (UI_CMD_PROCESSING == ui_state) {
    select_unprovisioned_node_instruction();
  } else if ((UI_WAITING_FOR_INPUT == ui_state) && (true == input_ready)) {
    size_t len = strlen(input_buffer);
    if (ADDRESS_LEN_WITHOUT_PREFIX > len) {
      uint16_t id = (uint16_t)atoi(input_buffer);
      sc = btmesh_prov_get_unprov_uuid_by_id(id, command_uuid);
      if (SL_STATUS_OK != sc) {
        btmesh_app_prov_end_of_cmd();
      } else {
        return_value = true;
        ui_state = UI_CMD_PROCESSING;
      }
    } else if (UUID_LEN_WITHOUT_SEPARATORS == len
               || UUID_LEN_WITH_SEPARATORS == len) {
      app_parse_uuid(input_buffer, len, command_uuid);
      return_value = true;
      ui_state = UI_CMD_PROCESSING;
    } else {
      app_log_error("Invalid input format!" APP_LOG_NEW_LINE);
      btmesh_app_prov_end_of_cmd();
    }
  }
  return return_value;
}

bool btmesh_app_prov_get_uuid_from_prov_list(uuid_128 *command_uuid)
{
  bool return_value = false;
  sl_status_t sc;

  if (UI_CMD_PROCESSING == ui_state) {
    select_provisioned_node_instruction();
  } else if ((UI_WAITING_FOR_INPUT == ui_state) && (true == input_ready)) {
    size_t len = strlen(input_buffer);
    if (ADDRESS_LEN_WITHOUT_PREFIX > len) {
      uint16_t id = (uint16_t)atoi(input_buffer);
      sc = btmesh_prov_get_prov_uuid_by_id(id, command_uuid);
      if (SL_STATUS_OK != sc) {
        btmesh_app_prov_end_of_cmd();
      } else {
        return_value = true;
        ui_state = UI_CMD_PROCESSING;
      }
    } else if (ADDRESS_LEN_WITHOUT_PREFIX == len
               || ADDRESS_LEN_WITH_PREFIX == len) {
      uint16_t addr;
      app_parse_address(input_buffer, len, &addr);
      sc = btmesh_prov_get_prov_uuid_by_address(addr, command_uuid);
      if (SL_STATUS_OK != sc) {
        btmesh_app_prov_end_of_cmd();
      } else {
        return_value = true;
        ui_state = UI_CMD_PROCESSING;
      }
    } else if (UUID_LEN_WITHOUT_SEPARATORS == len
               || UUID_LEN_WITH_SEPARATORS == len) {
      app_parse_uuid(input_buffer, len, command_uuid);
      return_value = true;
      ui_state = UI_CMD_PROCESSING;
    } else {
      app_log_error("Invalid input format!" APP_LOG_NEW_LINE);
      btmesh_app_prov_end_of_cmd();
    }
  }
  return return_value;
}

bool btmesh_app_prov_ui_get_input_buffer(char **ui_input_buffer)
{
  bool return_value = false;
  if (UI_CMD_PROCESSING == ui_state) {
    input_ready = false;
    ui_state = UI_WAITING_FOR_INPUT;
  } else if ((UI_WAITING_FOR_INPUT == ui_state) && (true == input_ready)) {
    *ui_input_buffer = &(input_buffer[0]);
    ui_state = UI_CMD_PROCESSING;
    return_value = true;
  }

  return return_value;
}

sl_ui_state btmesh_app_prov_ui_get_ui_state(void)
{
  return ui_state;
}

// -----------------------------------------------------------------------------
// Private function definitions

void *handle_input(void *ptr)
{
  int num_read = 0;
  while (run) {
    if (false == input_ready) {
      if (peek_stdin(input_buffer, sizeof(input_buffer), &num_read)) {
        input_buffer[num_read - 1] = '\0';
        app_log_debug("Command received: %s" APP_LOG_NEW_LINE, input_buffer);
        app_log_debug("Length: %d" APP_LOG_NEW_LINE, num_read);
        input_ready = true;
      }
    }
    app_sleep_us(INPUT_SLEEP_US);
  }
  return 0;
}

static bool peek_stdin(char *buf, int buffer_length, int *num_read)
{
#if defined(POSIX) && POSIX == 1
  // Setup an instant non-blocking peek
  fd_set rfds;
  struct timeval tv = { .tv_sec = 0, .tv_usec = 0 };
  FD_ZERO(&rfds);
  FD_SET(0, &rfds);
  // Peek standard input
  int retval = select(1, &rfds, NULL, NULL, &tv);
  if (-1 == retval) {
    // Some kind of error happened
    app_log_error("Can't check stdin" APP_LOG_NEW_LINE);
    return false;
  } else if (0 == retval) {
    // No input data available
    return false;
  } else {
    // Input data available
    *num_read = read(STDIN_FILENO, buf, buffer_length);
    if (-1 == *num_read) {
      app_log_error("Can't read from stdin" APP_LOG_NEW_LINE);
    }
    return true;
  }
#else
  static int current_length = 0;
  if (_kbhit()) {
    // Get the last character while echoing it back
    buf[current_length] = _getche();
    current_length++;
    *num_read = current_length;
    if (13 == buf[current_length - 1]) { // Enter pressed
      // Fake the newline char to behave like read()
      buf[current_length - 1] = '\n';
      current_length = 0;
      // Write a newline so it behaves like POSIX
      app_log_nl();
      return true;
    } else if (8 == buf[current_length - 1]) { // Backspace
      current_length--;
      if (0 != current_length) {
        current_length--;
      }
      return false;
    } else if (current_length == buffer_length) { // Buffer length reached
      buf[buffer_length - 1] = '\n';
      current_length = 0;
      // As a full buffer is considered as a finished command, add a newline here as well
      app_log_nl();
      return true;
    } else {
      return false;
    }
  }
  return false;
#endif // defined(POSIX) && POSIX == 1
}

static void select_unprovisioned_node_instruction(void)
{
  sl_status_t sc;

  app_log("Select a node to provision" APP_LOG_NEW_LINE);
  app_log("Type either the ID or UUID from the list below" APP_LOG_NEW_LINE);
  app_log_nl();
  sc = btmesh_prov_list_unprovisioned_nodes();
  if (SL_STATUS_EMPTY == sc) {
    app_log_info("No unprovisioned nodes available" APP_LOG_NEW_LINE);
    app_log_info("Try scanning for unprovisioned nodes first" APP_LOG_NEW_LINE);
    btmesh_app_prov_end_of_cmd();
  } else {
    input_ready = false;
    ui_state = UI_WAITING_FOR_INPUT;
  }
}

static void select_provisioned_node_instruction(void)
{
  sl_status_t sc;

  app_log("Select a node" APP_LOG_NEW_LINE);
  app_log("Type either the ID, UUID or address from the list below" APP_LOG_NEW_LINE);
  app_log_nl();
  sc = btmesh_prov_list_provisioned_nodes();
  if (SL_STATUS_EMPTY == sc) {
    app_log_info("No provisioned nodes available" APP_LOG_NEW_LINE);
    btmesh_app_prov_end_of_cmd();
  } else {
    input_ready = false;
    ui_state = UI_WAITING_FOR_INPUT;
  }
}

// -----------------------------------------------------------------------------
// Callbacks

SL_WEAK sl_status_t btmesh_app_prov_ui_handle_remote_prov_cmd(char cmd_id)
{
  (void)cmd_id;

  return SL_STATUS_NOT_FOUND;
}
