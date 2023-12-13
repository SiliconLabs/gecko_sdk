/***************************************************************************/ /**
 * @file
 * @brief CPC System Endpoint Primary API implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_cpc_weak_prototypes.h"
#include "sl_cpc_system_primary.h"
#include "sl_cpc_config.h"
#include "sl_cpc.h"
#include "sli_cpc.h"
#include "sli_cpc_system_common.h"
#include "sli_cpc_system_primary.h"
#include "sli_cpc_trace.h"
#include "sli_cpc_debug.h"

#include <string.h>

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/

#ifndef SL_CPC_SYSTEM_PRIMARY_OUT_OF_MEMORY_RETRY_TICK
#define SL_CPC_SYSTEM_PRIMARY_OUT_OF_MEMORY_RETRY_TICK  10
#endif

#if defined(DEBUG_EFM) || defined(DEBUG_EFM_USER)
#define  VALIDATE_COMMAND_HANDLE(command_handle)            \
  {                                                         \
    sl_slist_node_t *_node_;                                \
    SL_SLIST_FOR_EACH(commands, _node_) {                   \
      EFM_ASSERT(_node_ != &command_handle->node_commands); \
    }                                                       \
  }
#else
#define  VALIDATE_COMMAND_HANDLE(command_handle)
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * System endpoint handle
 ******************************************************************************/
static sl_cpc_endpoint_handle_t system_ep = { .ep = NULL };
static bool terminate_system_ep = false;
static bool system_ep_connected = false;
static uint8_t next_command_seq = 0;

static sl_slist_node_t *commands;
static sl_slist_node_t *retries;
static sl_slist_node_t *commands_in_error;
static sl_slist_node_t *event_listeners;
static uint32_t rx_unsolicited_count = 0;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

static void on_unsolicited(void *arg);

static void on_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                               void *buffer,
                               void *arg,
                               sl_status_t status);

static void on_final(uint8_t endpoint_id, void *arg, void *answer, uint32_t answer_length);

static void on_error(sl_cpc_user_endpoint_id_t endpoint_id);

static void process_retransmit(void);

static void process_command_in_error(void);

static void process_unsolicited(void);

static sl_status_t write_command(sli_cpc_system_command_handle_t *command_handle);

/***************************************************************************//**
 * Called when primary app version is requested.
 * The format is up to the user. The string should be null terminated.
 ******************************************************************************/
SL_WEAK const char* sl_cpc_primary_app_version(void)
{
  return "UNDEFINED";
}

/***************************************************************************//**
 * Initialize CPC System
 ******************************************************************************/
sl_status_t sli_cpc_system_init(void)
{
  sl_status_t status;

  sl_slist_init(&commands);
  sl_slist_init(&retries);
  sl_slist_init(&commands_in_error);
  sl_slist_init(&event_listeners);

  status = sli_cpc_init_service_endpoint(&system_ep, SL_CPC_ENDPOINT_SYSTEM,
                                         SL_CPC_ENDPOINT_FLAG_UFRAME_ENABLE); // Enable uframe for poll-final
  if (status != SL_STATUS_OK) {
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_FINAL, (void*) on_final);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_UFRAME_WRITE_COMPLETED, (void*) on_write_completed);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_IFRAME_WRITE_COMPLETED, (void*) on_write_completed);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_UFRAME_RECEIVE, (void*) on_unsolicited);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_IFRAME_RECEIVE, (void*) on_unsolicited);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  status = sl_cpc_set_endpoint_option(&system_ep, SL_CPC_ENDPOINT_ON_ERROR, (void *)on_error);
  if (status != SL_STATUS_OK) {
    sl_cpc_free_endpoint(&system_ep);
    return status;
  }

  return status;
}

/***************************************************************************//**
 * Start the system endpoint, effectively connecting it to the secondary
 ******************************************************************************/
sl_status_t sli_cpc_system_start(void)
{
  sl_status_t status;

  status = sl_cpc_connect_endpoint(&system_ep, SL_CPC_FLAG_NO_BLOCK);
  if (status == SL_STATUS_OK) {
    system_ep_connected = true;
  }

  return status;
}

/***************************************************************************//**
 * Callback called when uframe information is received
 ******************************************************************************/
static void on_unsolicited(void *arg)
{
  (void)arg;
  rx_unsolicited_count++;
  sli_cpc_signal_event(SL_CPC_SIGNAL_SYSTEM);
}

/***************************************************************************//**
 * Mark a command handle as being in error, it will be processed later by the dispatcher
 ******************************************************************************/
static void command_handle_set_in_error(sli_cpc_system_command_handle_t *command_handle,
                                        sl_status_t status)
{
  MCU_DECLARE_IRQ_STATE;

  MCU_ENTER_ATOMIC();

  if (!command_handle->is_first_try) {
    // command_handle is in the `commands` list if it was pushed to CPC
    // core at least once, ie. is_first_try is false.
    sl_slist_remove(&commands, &command_handle->node_commands);
  }

  // First write or not, the command ends up in the error list
  sl_slist_remove(&retries, &command_handle->node_retries);
  sl_slist_push_back(&commands_in_error, &command_handle->node_retries);

  command_handle->error_status = status;

  MCU_EXIT_ATOMIC();
}

/***************************************************************************//**
 * System endpoint on sleeptimer expired callback
 ******************************************************************************/
static void on_timer_expired(sli_cpc_timer_handle_t *handle,
                             void *arg)
{
  sli_cpc_system_command_handle_t *command_handle = (sli_cpc_system_command_handle_t*)arg;

  (void)handle;

  if (command_handle->retry_count > 0 || command_handle->is_first_try) {
    MCU_ATOMIC_SECTION(sl_slist_push_back(&retries, &command_handle->node_retries); );

    if (!command_handle->is_first_try) {
      // only decrement the retry count and update the status is the packet has been successfully sent over
      // the wire at least once (!command_handle->is_first_try) as this means its the secondary which didn't respond
      command_handle->retry_count--;
      command_handle->error_status = SL_STATUS_IN_PROGRESS; // At least one retransmission occurred.
    } else {
      // If the command has not been transfered on the wire (command_handle->is_first_try), it means
      // we landed here because there was not enough resources for the sl_cpc_write. Don't touch the retry
      // count nor the error status as this is misleading.
    }
  } else {
    // Max number of retransmission reached.
    command_handle_set_in_error(command_handle, SL_STATUS_TIMEOUT);
  }
}

/***************************************************************************//**
 * System endpoint on write completed callback
 ******************************************************************************/
static void on_write_completed(sl_cpc_user_endpoint_id_t endpoint_id,
                               void *buffer,
                               void *arg,
                               sl_status_t status)
{
  sli_cpc_system_command_handle_t *command_handle = (sli_cpc_system_command_handle_t *)arg;
  sl_status_t status_timer;

  (void)endpoint_id;
  (void)buffer;

  command_handle->being_transmitted = false;

  if (status == SL_STATUS_OK) {
    // If the write successfully completed for an I-Frame, it means the packet was
    // acknowledged by the secondary, start a timer to wait for the secondary to reply.
    // For a U-Frame, it means was successfully pushed over the wire. Other errors
    // indicate that the frame could not be pushed (the endpoint is being closed?)
    status_timer = sli_cpc_timer_restart_timer(&command_handle->timer,
                                               command_handle->retry_timeout_tick,
                                               on_timer_expired,
                                               command_handle);
    EFM_ASSERT(status_timer == SL_STATUS_OK);
  } else {
    // If the write failed and we're dealing with an I-Frame, it means the secondary didn't
    // acknowledge the frame in time, so it's an error that should be reported to caller.
    // In the case of a U-Frame, this indicates that the frame was never sent on the wire
    // before getting aborted.
    command_handle_set_in_error(command_handle, status);
  }
}

/***************************************************************************//**
 * Handle no-op from SECONDARY:
 *   This functions is called when a no-op command is received from the SECONDARY.
 *   The SECONDARY will send back a no-op in response to the one sent by the PRIMARY.
 ******************************************************************************/
static void on_final_noop(sli_cpc_system_command_handle_t *command_handle,
                          sl_status_t status)
{
  ((sli_cpc_system_noop_cmd_callback_t)command_handle->on_final)(status);
}

/***************************************************************************//**
 * Handle reset from SECONDARY:
 *   This functions is called when a reset command is received from the SECONDARY.
 *   The SECONDARY will send back a reset in response to the one sent by the PRIMARY.
 ******************************************************************************/
static void on_final_reset(sli_cpc_system_command_handle_t *handle,
                           sl_status_t handle_status,
                           sl_cpc_system_status_t system_status)
{
  ((sli_cpc_system_reset_cmd_callback_t)handle->on_final)(handle_status, system_status);
}

/***************************************************************************//**
 * Handle property-is from SECONDARY:
 *   This functions is called when a property-is command is received from the SECONDARY.
 *   The SECONDARY emits a property-is in response to a property-get/set.
 ******************************************************************************/
static void on_final_property_is(sli_cpc_system_command_handle_t *command_handle,
                                 sli_cpc_system_cmd_t *reply,
                                 sl_status_t status)
{
  sli_cpc_system_property_cmd_t *property_cmd;
  sli_cpc_property_id_t property_id;
  void *property_payload = NULL;
  size_t property_length = 0;

  if (reply) {
    property_cmd = (sli_cpc_system_property_cmd_t*)reply->payload;
    property_id = property_cmd->property_id;

    property_length = reply->length - sizeof(sli_cpc_system_property_cmd_t);
    property_payload = property_cmd->payload;
  } else {
    property_cmd = (sli_cpc_system_property_cmd_t *)command_handle->command.payload;
    property_id = property_cmd->property_id;
  }

  ((sli_cpc_system_property_get_set_cmd_callback_t)command_handle->on_final)(property_id,
                                                                             property_payload,
                                                                             property_length,
                                                                             command_handle->on_final_arg,
                                                                             status);
}

/***************************************************************************//**
 * Called by CPC core when uframe/poll is received
 ******************************************************************************/
static void on_final(uint8_t endpoint_id,
                     void *arg,
                     void *answer,
                     uint32_t answer_length)
{
  sli_cpc_system_command_handle_t *command = NULL;
  sli_cpc_system_command_handle_t *search_command;
  sli_cpc_system_cmd_t *reply = (sli_cpc_system_cmd_t *)answer;
  MCU_DECLARE_IRQ_STATE;

  (void)endpoint_id;
  (void)arg;
  (void)answer_length;

  MCU_ENTER_ATOMIC();

  SL_SLIST_FOR_EACH_ENTRY(commands, search_command, sli_cpc_system_command_handle_t, node_commands) {
    if (search_command->command.seq == reply->seq) {
      command = search_command;
      break;
    }
  }

  if (command != NULL) {
    // We found the command; stop the timer, execute its callback and clean the command
    sli_cpc_timer_stop_timer(&command->timer);
    sl_slist_remove(&commands, &command->node_commands);
    sl_slist_remove(&retries, &command->node_retries);
    sl_slist_remove(&commands_in_error, &command->node_retries);
    MCU_EXIT_ATOMIC();
    switch (reply->command_id) {
      case CMD_SYSTEM_NOOP:
        on_final_noop(command, SL_STATUS_OK);
        break;

      case CMD_SYSTEM_RESET:
        if (reply->length == sizeof(sl_cpc_system_status_t)) {
          sl_cpc_system_status_t system_status = *(sl_cpc_system_status_t*)reply->payload;

          on_final_reset(command,
                         SL_STATUS_OK,
                         system_status);
        } else {
          on_final_reset(command, SL_STATUS_FAIL, STATUS_INVALID_ARGUMENT);
        }
        break;

      case CMD_SYSTEM_PROP_VALUE_IS:
        on_final_property_is(command, reply, SL_STATUS_OK);
        break;

      case CMD_SYSTEM_PROP_VALUE_GET:   // Fallthrough, primary ain't supposed to receive those
      case CMD_SYSTEM_PROP_VALUE_SET:
      default:
        EFM_ASSERT(false);
        break;
    }

    sli_cpc_free_system_command_handle(command);
  } else {
    SL_CPC_JOURNAL_RECORD_WARNING("Reply with unknown seq", search_command->command.seq);
    MCU_EXIT_ATOMIC();
  }
}

/***************************************************************************//**
 * Called by CPC core when the system endpoint is in error.
 ******************************************************************************/
static void on_error(sl_cpc_user_endpoint_id_t endpoint_id)
{
  sl_slist_node_t *node;
  MCU_DECLARE_IRQ_STATE;

  EFM_ASSERT(endpoint_id == SL_CPC_ENDPOINT_SYSTEM);

  MCU_ENTER_ATOMIC();

  // handles in the `retries` list are not queued for transmission or being transmitted
  // so mark them as being in error
  do {
    node = sl_slist_pop(&retries);
    if (node != NULL) {
      sli_cpc_system_command_handle_t *handle = SL_SLIST_ENTRY(node, sli_cpc_system_command_handle_t, node_retries);

      command_handle_set_in_error(handle, SL_STATUS_FAIL);
    }
  } while (node != NULL);

  // handles in the `commands` list are a bit more tricky to manage as they can be
  // either transmitted over the wire and we're waiting for the secondary to reply;
  // or in the process of being transmitted. In the later case, the on_write_completed
  // will be called on completion and that function will move handles to the error
  // queue in case of errors. Extra care must be taken to avoid moving the handle twice
  node = commands;
  while (node != NULL) {
    sli_cpc_system_command_handle_t *handle = SL_SLIST_ENTRY(node, sli_cpc_system_command_handle_t, node_commands);

    // let node point to next element in the list
    node = node->node;

    // if this is false, it means that on_write_completed was already call
    // for that element and that handle must marked in error here, else the
    // on_write_completed will handle setting the command in error
    if (!handle->being_transmitted) {
      sli_cpc_timer_stop_timer(&handle->timer);
      sl_slist_remove(&commands, &handle->node_commands);

      sl_slist_push_back(&commands_in_error, &handle->node_retries);
    }
  }

  MCU_EXIT_ATOMIC();

  system_ep_connected = false;
  terminate_system_ep = true;
}

/***************************************************************************//**
 * Send no-operation command query
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_noop(sli_cpc_system_noop_cmd_callback_t on_noop_reply,
                                    void *on_noop_reply_arg,
                                    uint8_t retry_count_max,
                                    uint32_t retry_timeout_ms)
{
  sli_cpc_system_command_handle_t *command_handle;
  sl_status_t status;

  // Make sure the system endpoint is initialized
  EFM_ASSERT(system_ep.ep != NULL);

  status = sli_cpc_get_system_command_handle(&command_handle);
  if (status != SL_STATUS_OK) {
    return status;
  }

  // Populate command handle
  command_handle->frame_type = SYSTEM_EP_UFRAME;
  command_handle->is_first_try = true;
  command_handle->error_status = SL_STATUS_OK;
  command_handle->on_final = (void *)on_noop_reply;
  command_handle->on_final_arg = (void *)on_noop_reply_arg;
  command_handle->retry_count = retry_count_max;
  command_handle->retry_timeout_tick = sli_cpc_timer_ms_to_tick((uint16_t) retry_timeout_ms);

  // Populate system command
  command_handle->command.command_id = CMD_SYSTEM_NOOP;
  command_handle->command.seq = next_command_seq++;
  command_handle->command.length = 0;

  return write_command(command_handle);
}

/***************************************************************************//**
 * Send a reset query
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_reboot(sli_cpc_system_reset_cmd_callback_t on_reset_reply,
                                      void *on_reset_reply_arg,
                                      uint8_t retry_count_max,
                                      uint32_t retry_timeout_ms)
{
  sli_cpc_system_command_handle_t *command_handle;
  sl_status_t status;

  // Make sure the system endpoint is initialized
  EFM_ASSERT(system_ep.ep != NULL);

  status = sli_cpc_get_system_command_handle(&command_handle);
  if (status != SL_STATUS_OK) {
    return status;
  }

  // Populate command handle
  command_handle->frame_type = SYSTEM_EP_UFRAME;
  command_handle->is_first_try = true;
  command_handle->error_status = SL_STATUS_OK;
  command_handle->on_final = (void *)on_reset_reply;
  command_handle->on_final_arg = (void *)on_reset_reply_arg;
  command_handle->retry_count = retry_count_max;
  command_handle->retry_timeout_tick = sli_cpc_timer_ms_to_tick((uint16_t) retry_timeout_ms);

  // Populate system command
  command_handle->command.command_id = CMD_SYSTEM_RESET;
  command_handle->command.seq = next_command_seq++;
  command_handle->command.length = 0;

  return write_command(command_handle);
}

/***************************************************************************//**
 * Send a property-get query
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_property_get(sli_cpc_system_property_get_set_cmd_callback_t on_property_get_reply,
                                            void *on_property_get_reply_arg,
                                            sli_cpc_property_id_t property_id,
                                            uint8_t retry_count_max,
                                            uint32_t retry_timeout_ms,
                                            sli_cpc_system_ep_frame_type_t frame_type)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_command_handle_t *command_handle;
  sl_status_t status;

  // Make sure the system endpoint is initialized
  EFM_ASSERT(system_ep.ep != NULL);

  status = sli_cpc_get_system_command_handle(&command_handle);
  if (status != SL_STATUS_OK) {
    return status;
  }

  if (retry_count_max != 0 && frame_type == SYSTEM_EP_IFRAME) {
    EFM_ASSERT(false);
    sli_cpc_free_system_command_handle(command_handle);
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Populate command handle
  command_handle->is_first_try = true;
  command_handle->error_status = SL_STATUS_OK;
  command_handle->on_final = (void *)on_property_get_reply;
  command_handle->on_final_arg = (void *)on_property_get_reply_arg;
  command_handle->retry_count = retry_count_max;
  command_handle->frame_type = frame_type;
  command_handle->retry_timeout_tick = sli_cpc_timer_ms_to_tick((uint16_t) retry_timeout_ms);

  // Populate system command
  command_handle->command.length = sizeof(sli_cpc_property_id_t);
  command_handle->command.seq = next_command_seq++;
  command_handle->command.command_id = CMD_SYSTEM_PROP_VALUE_GET;

  // Populate payload
  tx_property_command = (sli_cpc_system_property_cmd_t *)command_handle->command.payload;
  tx_property_command->property_id = property_id;

  return write_command(command_handle);
}

/***************************************************************************//**
 * Send a property-set query
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_property_set(sli_cpc_system_property_get_set_cmd_callback_t on_property_set_reply,
                                            void *on_property_set_reply_arg,
                                            sli_cpc_property_id_t property_id,
                                            uint8_t retry_count_max,
                                            uint32_t retry_timeout_ms,
                                            const void *value,
                                            size_t value_length,
                                            sli_cpc_system_ep_frame_type_t frame_type)
{
  sli_cpc_system_property_cmd_t *tx_property_command;
  sli_cpc_system_command_handle_t *command_handle;
  sl_status_t status;

  // Make sure the system endpoint is initialized
  EFM_ASSERT(system_ep.ep != NULL);

  status = sli_cpc_get_system_command_handle(&command_handle);
  if (status != SL_STATUS_OK) {
    return status;
  }

  if (retry_count_max != 0 && frame_type == SYSTEM_EP_IFRAME) {
    EFM_ASSERT(false);
    sli_cpc_free_system_command_handle(command_handle);
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Populate command handle
  command_handle->is_first_try = true;
  command_handle->error_status = SL_STATUS_OK;
  command_handle->on_final = (void *)on_property_set_reply;
  command_handle->on_final_arg = (void *)on_property_set_reply_arg;
  command_handle->retry_count = retry_count_max;
  command_handle->frame_type = frame_type;
  command_handle->retry_timeout_tick = sli_cpc_timer_ms_to_tick((uint16_t) retry_timeout_ms);

  // Populate system command
  command_handle->command.command_id = CMD_SYSTEM_PROP_VALUE_SET;
  command_handle->command.seq = next_command_seq++;
  command_handle->command.length = (uint16_t) (sizeof(sli_cpc_property_id_t) + value_length);

  // Populate command payload
  tx_property_command = (sli_cpc_system_property_cmd_t*) command_handle->command.payload;
  tx_property_command->property_id = property_id;
  memcpy(tx_property_command->payload, value, value_length);

  return write_command(command_handle);
}

/***************************************************************************//**
 * Endpoint connection was terminated, notify the remote
 ******************************************************************************/
sl_status_t sli_cpc_send_terminate_notification(uint8_t endpoint_id)
{
  (void)endpoint_id;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Endpoint connection was shutdown, notify the remote
 ******************************************************************************/
sl_status_t sli_cpc_send_shutdown_request(uint8_t endpoint_id)
{
  (void)endpoint_id;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Process the system endpoint
 ******************************************************************************/
void sli_cpc_system_process(void)
{
  if (terminate_system_ep) {
    // wait until all commands are processed before doing anything
    if (!commands && !retries && !commands_in_error) {
      sl_status_t status;

      // terminate only when all command handles are dealt with
      status = sl_cpc_terminate_endpoint(&system_ep, 0);
      EFM_ASSERT(status == SL_STATUS_OK || status == SL_STATUS_IN_PROGRESS);

      if (status == SL_STATUS_OK) {
        terminate_system_ep = false;
      }
    }
  }

  process_retransmit();
  process_command_in_error();

  if (system_ep_connected) {
    process_unsolicited();
  }
}

/***************************************************************************//**
 * Retransmit commands
 ******************************************************************************/
static void process_retransmit(void)
{
  sl_slist_node_t *node;
  do {
    MCU_ATOMIC_SECTION(node = sl_slist_pop(&retries); );
    if (node != NULL) {
      sli_cpc_system_command_handle_t *handle = SL_SLIST_ENTRY(node, sli_cpc_system_command_handle_t, node_retries);

      write_command(handle);
    }
  } while (node != NULL);
}

/***************************************************************************//**
 * Process command in error: call callbacks with error status
 ******************************************************************************/
static void process_command_in_error(void)
{
  sl_slist_node_t *node;

  do {
    MCU_ATOMIC_SECTION(node = sl_slist_pop(&commands_in_error); );
    if (node != NULL) {
      sli_cpc_system_command_handle_t *handle;

      handle = SL_SLIST_ENTRY(node, sli_cpc_system_command_handle_t, node_retries);
      sl_slist_remove(&commands, node);

      switch (handle->command.command_id) {
        case CMD_SYSTEM_NOOP:
          on_final_noop(handle, handle->error_status);
          break;
        case CMD_SYSTEM_RESET:
          on_final_reset(handle, handle->error_status, STATUS_FAILURE);
          break;
        case CMD_SYSTEM_PROP_VALUE_GET:
        case CMD_SYSTEM_PROP_VALUE_SET:
          on_final_property_is(handle, NULL, handle->error_status);
          break;
        case CMD_SYSTEM_PROP_VALUE_IS: //fallthrough to default:
        default:
          EFM_ASSERT(false);
      }

      sli_cpc_free_system_command_handle(handle);
    }
  } while (node != NULL);
}

/***************************************************************************//**
 * Read unsolicited data received
 ******************************************************************************/
static void process_unsolicited(void)
{
  // Read process_unsolicited data
  do {
    if (rx_unsolicited_count > 0) {
      void *data = NULL;
      uint16_t length;
      sl_status_t status;
      bool is_i_frame = false;
      sli_cpc_system_cmd_t *command = NULL;
      sli_cpc_system_property_cmd_t *property_cmd = NULL;
      sl_cpc_system_status_t system_status;
      sl_cpc_endpoint_state_t ep_state;
      uint16_t expected_length;
      const uint16_t MINIMUM_LENGTH = (sizeof(sli_cpc_system_cmd_t) - PAYLOAD_LENGTH_MAX + sizeof(sli_cpc_system_property_cmd_t));

      // Process Pending Frames
      status = sl_cpc_read(&system_ep,
                           &data, &length,
                           0, SL_CPC_FLAG_NO_BLOCK | SL_CPC_FLAG_UNNUMBERED_INFORMATION);
      if (status == SL_STATUS_EMPTY) {
        is_i_frame = true;
        status = sl_cpc_read(&system_ep,
                             &data, &length,
                             0, SL_CPC_FLAG_NO_BLOCK);
      }

      if (status != SL_STATUS_OK || length < MINIMUM_LENGTH || data == NULL) {
        EFM_ASSERT(false);
        goto next;
      }

      command = (sli_cpc_system_cmd_t *)data;

      // Received unsupported or invalid unsolicited command
      if (command->command_id != CMD_SYSTEM_PROP_VALUE_IS
          || length != SIZEOF_SYSTEM_COMMAND(command)) {
        EFM_ASSERT(false);
        if (is_i_frame) {
          SLI_CPC_DEBUG_TRACE_ENDPOINT_RXD_DATA_FRAME_DROPPED(((sl_cpc_endpoint_t *)system_ep.ep));
        } else {
          SLI_CPC_DEBUG_TRACE_ENDPOINT_RXD_UNNUMBERED_DROPPED(((sl_cpc_endpoint_t *)system_ep.ep));
        }
        goto next;
      }

      property_cmd = (sli_cpc_system_property_cmd_t *)command->payload;

      // LAST STATUS
      if (property_cmd->property_id == PROP_LAST_STATUS) {
        expected_length = (sizeof(sli_cpc_system_property_cmd_t) + sizeof(sl_cpc_system_status_t));
        if (command->length != expected_length) {
          EFM_ASSERT(false);
          if (is_i_frame) {
            SLI_CPC_DEBUG_TRACE_ENDPOINT_RXD_DATA_FRAME_DROPPED(((sl_cpc_endpoint_t *)system_ep.ep));
          } else {
            SLI_CPC_DEBUG_TRACE_ENDPOINT_RXD_UNNUMBERED_DROPPED(((sl_cpc_endpoint_t *)system_ep.ep));
          }
          goto next;
        }
        system_status = *((sl_cpc_system_status_t*) property_cmd->payload);
        sl_cpc_system_unsolicited_last_status_callback(system_status);
      }

      // ENDPOINT STATE IS
      if (property_cmd->property_id >= PROP_ENDPOINT_STATE_0
          && property_cmd->property_id <= PROP_ENDPOINT_STATE_255) {
        expected_length = (sizeof(sli_cpc_system_property_cmd_t) + sizeof(sl_cpc_endpoint_state_t));
        if (command->length != expected_length) {
          EFM_ASSERT(false);
          goto next;
        }

        ep_state = *((sl_cpc_endpoint_state_t*) property_cmd->payload);

        // Listen notification
        if (ep_state == SL_CPC_STATE_OPEN) {
          sli_cpc_remote_open_unsolicited(PROPERTY_ID_TO_EP_ID(property_cmd->property_id));
        }
        // Closing notification
        else if (ep_state == SL_CPC_STATE_CLOSED) {
          // Remote has terminated the connection. Since this is an unsolicited
          // frame, the reply state is not used, because a terminate is a notification,
          // so the remote does not expect a reply.
          sl_cpc_endpoint_state_t state;
          sli_cpc_remote_terminated(PROPERTY_ID_TO_EP_ID(property_cmd->property_id), &state);
        }
        // Shutdown request
        else if (ep_state == SL_CPC_STATE_DISCONNECTED) {
          sli_cpc_remote_shutdown_unsolicited(PROPERTY_ID_TO_EP_ID(property_cmd->property_id));
        }
      }

      next:
      sl_cpc_free_rx_buffer(data);

      rx_unsolicited_count--;
    }
  } while (rx_unsolicited_count > 0);
}

/***************************************************************************//**
 * Write command on endpoint
 ******************************************************************************/
static sl_status_t write_command(sli_cpc_system_command_handle_t *command_handle)
{
  sl_status_t status;
  uint8_t write_flags = 0;

  switch (command_handle->frame_type) {
    case SYSTEM_EP_IFRAME:
      write_flags = SL_CPC_FLAG_INFORMATION_POLL_FINAL;
      break;
    case SYSTEM_EP_UFRAME:
      write_flags = SL_CPC_FLAG_UNNUMBERED_POLL_FINAL;
      break;
    default:
      EFM_ASSERT(false);
      break;
  }

  if (command_handle->frame_type == SYSTEM_EP_IFRAME) {
    // TODO incorporate the logic from the primary linux code
    // Can't send iframe commands on the system endpoint until the sequence numbers are reset

    // I-Frame should only be sent once, the re-transmit mechanism is managed by the core
    EFM_ASSERT(command_handle->is_first_try && command_handle->retry_count == 0);
  }

  status = sl_cpc_write(&system_ep,
                        (void *)&command_handle->command,
                        SIZEOF_SYSTEM_COMMAND((&command_handle->command)),
                        write_flags | SL_CPC_FLAG_NO_BLOCK,
                        (void *)command_handle);

  switch (status) {
    case SL_STATUS_OK:
      command_handle->being_transmitted = true;

      if (command_handle->is_first_try) {
        // This is the initial write_command() for this command. Since it was successfully written,
        // add it to the list of pending commands and mark put the is_first_try marker to false for
        // subsequent retries
        command_handle->is_first_try = false;
        MCU_ATOMIC_SECTION(sl_slist_push_back(&commands, &command_handle->node_commands); );
      } else {
        // This is a retransmission, do nothing as we don't want a duplicate in the 'commands' list
      }

      // Let the on_write_complete callback trigger the retransmit timer when the command is drained
      break;

    case SL_STATUS_NO_MORE_RESOURCE:
      status = sli_cpc_timer_restart_timer(&command_handle->timer,
                                           SL_CPC_SYSTEM_PRIMARY_OUT_OF_MEMORY_RETRY_TICK,
                                           on_timer_expired, command_handle);
      if (status != SL_STATUS_OK) {
        EFM_ASSERT(false);

        // if we failed to start the retry timer, move the command handle
        // to the error list to call the user callback and free resource
        command_handle_set_in_error(command_handle, SL_STATUS_FAIL);
      }
      break;

    default:
      command_handle_set_in_error(command_handle, SL_STATUS_FAIL);
      break;
  }

  return status;
}

/***************************************************************************//**
 * Initialize an event listener. Basically set all fields to zero, that way the
 * structure can be expanded but new attributes will be initialized to zero,
 * preventing CPC core from calling invalid function pointers.
 ******************************************************************************/
void sl_cpc_system_event_listener_init(sl_cpc_system_event_listener_t *listener)
{
  memset(listener, 0, sizeof(sl_cpc_system_event_listener_t));
}

/***************************************************************************//**
 * Add a listener to the global list of event listeners
 ******************************************************************************/
sl_status_t sl_cpc_system_event_listener_subscribe(sl_cpc_system_event_listener_t *listener)
{
  MCU_ATOMIC_SECTION(sl_slist_push_back(&event_listeners, &listener->node); );

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Remove a listener from the global list of event listeners. sl_slist_remove
 * asserts if the node to be removed is not present in the list.
 ******************************************************************************/
sl_status_t sl_cpc_system_event_listener_unsubscribe(sl_cpc_system_event_listener_t *listener)
{
  MCU_ATOMIC_SECTION(sl_slist_remove(&event_listeners, &listener->node); );

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Notify users that a reset has happened by going through the list of event
 * listeners.
 ******************************************************************************/
void sli_cpc_system_notify_reset(sl_cpc_system_status_t reset_reason)
{
  sl_cpc_system_event_listener_t *iterator;

  MCU_DECLARE_IRQ_STATE;
  MCU_ENTER_ATOMIC();

  SL_SLIST_FOR_EACH_ENTRY(event_listeners, iterator, sl_cpc_system_event_listener_t, node) {
    if (iterator->on_reset_callback) {
      iterator->on_reset_callback(reset_reason);
    }
  }

  MCU_EXIT_ATOMIC();

  sli_cpc_reset();
}

/***************************************************************************//**
 * Check if the system endpoint is connected and reboot sequence is done.
 ******************************************************************************/
bool sli_cpc_system_is_ready(void)
{
  return system_ep_connected && sli_cpc_reboot_is_sequence_done();
}
