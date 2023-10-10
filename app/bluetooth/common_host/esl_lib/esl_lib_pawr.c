/***************************************************************************//**
 * @file
 * @brief ESL Access Point PAwR source file.
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
#include <stdint.h>
#include "sl_status.h"
#include "sl_slist.h"
#include "esl_lib.h"
#include "esl_lib_pawr.h"
#include "esl_lib_event_list.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

// Value for no flag present for the advertiser
#define PERIODIC_ADVERTISER_FLAG_NONE     0

// Maximum count of PAWR set data call within one burst
// NOTE: best to align with NCP ESL AP's SL_BT_CONFIG_PAWR_PACKET_REQUEST_COUNT!
#define PAWR_DATA_MAX_BURST_READ          4

// PAwR handle print formatter alias
#define PAWR_FMT                          ESL_LIB_LOG_HANDLE_FORMAT

typedef enum {
  PAWR_RESPONSE_COMPLETE   = 0,
  PAWR_RESPONSE_INCOMPLETE = 1,
  PAWR_RESPONSE_TRUNCATED  = 2,
  PAWR_RESPONSE_FAILED     = 255
} pawr_response_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static sl_status_t send_pawr_response_event(esl_lib_pawr_t *pawr_ptr,
                                            uint8_t        subevent,
                                            uint8_t        response_slot);
static sl_status_t send_pawr_error(esl_lib_pawr_t       *pawr,
                                   esl_lib_status_t     lib_status,
                                   sl_status_t          status,
                                   esl_lib_pawr_state_t data);
static sl_status_t run_command(esl_lib_command_list_cmd_t *cmd);
static sl_status_t send_pawr_status(esl_lib_pawr_t *pawr_ptr);

// -----------------------------------------------------------------------------
// Private variables

// List of PAwR structures
static sl_slist_node_t *pawr_list       = NULL;

// -----------------------------------------------------------------------------
// Public functions

sl_status_t esl_lib_pawr_add(esl_lib_pawr_t **ptr_out)
{
  sl_status_t sc;
  esl_lib_pawr_t *ptr;

  if (ptr_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  esl_lib_log_pawr_debug("Adding PAwR" APP_LOG_NL);

  ptr = (esl_lib_pawr_t *)esl_lib_memory_allocate(sizeof(esl_lib_pawr_t));
  if (ptr != NULL) {
    sc = esl_lib_storage_create(&ptr->storage_handle);
    if (sc == SL_STATUS_OK) {
      // Set handle
      ptr->pawr_handle                  = SL_BT_INVALID_ADVERTISING_SET_HANDLE;
      // Set command parameters
      ptr->command                      = NULL;
      ptr->command_list                 = NULL;
      // Set states
      ptr->enabled                      = ESL_LIB_FALSE;
      ptr->configured                   = ESL_LIB_FALSE;
      ptr->state                        = ESL_LIB_PAWR_STATE_IDLE;
      // Config default values
      ptr->config.adv_interval.min      = ESL_LIB_PERIODIC_ADV_MIN_INTERVAL_DEFAULT;
      ptr->config.adv_interval.max      = ESL_LIB_PERIODIC_ADV_MAX_INTERVAL_DEFAULT;
      ptr->config.subevent.count        = ESL_LIB_PAWR_SUBEVENT_COUNT_DEFAULT;
      ptr->config.subevent.interval     = ESL_LIB_PAWR_SUBEVENT_INTERVAL_DEFAULT;
      ptr->config.response_slot.delay   = ESL_LIB_PAWR_RESPONSE_SLOT_DELAY_DEFAULT;
      ptr->config.response_slot.spacing = ESL_LIB_PAWR_RESPONSE_SLOT_SPACING_DEFAULT;
      ptr->config.response_slot.count   = ESL_LIB_PAWR_RESPONSE_SLOT_COUNT_DEFAULT;
      // Add to the linked list
      sl_slist_push_back(&pawr_list, &ptr->node);
      sc = SL_STATUS_OK;
      *ptr_out = ptr;

      esl_lib_log_pawr_debug(PAWR_FMT "Added PAwR" APP_LOG_NL, ptr);
    }
  } else {
    esl_lib_log_pawr_error("Adding PAwR error, allocation failed" APP_LOG_NL);
    sc = SL_STATUS_ALLOCATION_FAILED;
  }
  return sc;
}

sl_status_t esl_lib_pawr_find(uint8_t        pawr,
                              esl_lib_pawr_t **ptr_out)
{
  sl_status_t sc = SL_STATUS_NOT_FOUND;
  esl_lib_pawr_t *ptr;

  if (ptr_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  SL_SLIST_FOR_EACH_ENTRY(pawr_list, ptr, esl_lib_pawr_t, node) {
    if (pawr == ptr->pawr_handle) {
      *ptr_out = ptr;
      return SL_STATUS_OK;
    }
  }
  return sc;
}

sl_status_t esl_lib_pawr_remove_ptr(esl_lib_pawr_t *ptr)
{
  if (ptr == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  // Unlink PAwR item
  sl_slist_remove(&pawr_list, &ptr->node);
  // Clean command list
  esl_lib_command_list_cleanup(&ptr->command_list);
  if (ptr->command != NULL) {
    esl_lib_memory_free(ptr->command);
  }

  // Delete storage
  (void)esl_lib_storage_delete(&ptr->storage_handle);
  esl_lib_log_pawr_debug(PAWR_FMT "Removed PAwR" APP_LOG_NL, ptr);
  // Delete PAwR data
  esl_lib_memory_free(ptr);

  return SL_STATUS_OK;
}

sl_status_t esl_lib_pawr_remove_handle(uint8_t        pawr,
                                       esl_lib_pawr_t **ptr_out)
{
  sl_status_t sc;
  esl_lib_pawr_t *ptr;
  // Check if it exists
  sc = esl_lib_pawr_find(pawr, &ptr);
  if (sc == SL_STATUS_OK) {
    sc = esl_lib_pawr_remove_ptr(ptr);
    if (sc == SL_STATUS_OK) {
      *ptr_out = NULL;
    }
  }
  return sc;
}

bool esl_lib_pawr_contains(esl_lib_pawr_t *ptr)
{
  bool ret = false;
  esl_lib_pawr_t *iterator;

  SL_SLIST_FOR_EACH_ENTRY(pawr_list, iterator, esl_lib_pawr_t, node) {
    if (iterator == ptr) {
      return true;
    }
  }

  return ret;
}

void esl_lib_pawr_cleanup(void)
{
  esl_lib_pawr_t *pawr;
  // Clean PAwR list
  while ((pawr = (esl_lib_pawr_t *)sl_slist_pop(&pawr_list)) != NULL) {
    (void)sl_bt_periodic_advertiser_stop(pawr->pawr_handle);
    esl_lib_command_list_cleanup(&pawr->command_list);
    sl_slist_remove(&pawr_list, &pawr->node);
    (void)esl_lib_storage_delete(&pawr->storage_handle);
    if (pawr->command != NULL) {
      esl_lib_memory_free(pawr->command);
    }
    esl_lib_memory_free(pawr);
  }
  esl_lib_log_pawr_debug("PAwR cleanup complete" APP_LOG_NL);
}

sl_status_t esl_lib_pawr_add_command(esl_lib_pawr_t             *pawr,
                                     esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t sc;

  if (pawr == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (!esl_lib_pawr_contains(pawr)) {
    return SL_STATUS_NOT_FOUND;
  }
  sc = esl_lib_command_list_put(&pawr->command_list, cmd);
  if (sc == SL_STATUS_OK) {
    esl_lib_log_pawr_debug(PAWR_FMT "Added command %d" APP_LOG_NL,
                           pawr,
                           cmd->cmd_code);
  } else {
    esl_lib_log_pawr_error(PAWR_FMT "Add command %d failed, sc = 0x%04x" APP_LOG_NL,
                           pawr,
                           cmd->cmd_code,
                           sc);
  }
  return sc;
}

void esl_lib_pawr_step(void)
{
  esl_lib_pawr_t             *pawr;

  SL_SLIST_FOR_EACH_ENTRY(pawr_list, pawr, esl_lib_pawr_t, node) {
    uint8_t burst_count = PAWR_DATA_MAX_BURST_READ;
    // Move and execute next command.
    while ((pawr->command = esl_lib_command_list_get(&pawr->command_list)) != NULL
           && burst_count--) {
      sl_status_t sc;

      esl_lib_log_pawr_debug(PAWR_FMT "Execute command burst, cmd = %d, cycles left %u" APP_LOG_NL,
                             pawr,
                             pawr->command->cmd_code,
                             burst_count);
      sc = run_command(pawr->command);

      if (sc == SL_STATUS_TRANSMIT && pawr->command->cmd_code == ESL_LIB_CMD_PAWR_SET_DATA) {
        esl_lib_log_pawr_debug(PAWR_FMT "BREAK command burst due transmit failure, defer %u cycles" APP_LOG_NL,
                               pawr,
                               burst_count);
        if (pawr->command->data.cmd_pawr_set_data.retry-- != 0) {
          sl_slist_push(&pawr->command_list, &pawr->command->node); // retry "one step" later, keep command order
        } else {
          // Send pawr transmit error event if all retry attempt failed
          (void)send_pawr_error(pawr,
                                ESL_LIB_STATUS_PAWR_SET_DATA_FAILED,
                                sc,
                                pawr->state);
          esl_lib_command_list_remove(&pawr->command_list, pawr->command);
          pawr->command = NULL;
        }
        return; // break full PAwR processing cycle anyway, if BT CTRL seems busy
      } else {
        esl_lib_command_list_remove(&pawr->command_list, pawr->command);
        pawr->command = NULL;
      }
    }
  }
}

void esl_lib_pawr_on_bt_event(sl_bt_msg_t *evt)
{
  sl_status_t      sc          = SL_STATUS_OK;
  esl_lib_pawr_t   *pawr_ptr   = NULL;
  esl_lib_evt_t    *lib_evt    = NULL;
  esl_lib_status_t lib_status  = ESL_LIB_STATUS_NO_ERROR;
  uint8_t          data_status = 0;

  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_pawr_advertiser_response_report_id:
      sc = esl_lib_pawr_find(evt->data.evt_pawr_advertiser_response_report.advertising_set,
                             &pawr_ptr);
      if (sc == SL_STATUS_OK) {
        data_status = evt->data.evt_pawr_advertiser_response_report.data_status;
        esl_lib_log_pawr_debug(PAWR_FMT "PAwR response, data status = %u , PAwR handle = %u" APP_LOG_NL,
                               pawr_ptr,
                               data_status,
                               pawr_ptr->pawr_handle);
        if (data_status != PAWR_RESPONSE_FAILED) {
          esl_lib_log_pawr_debug(PAWR_FMT "Appending to storage , PAwR handle = %u" APP_LOG_NL,
                                 pawr_ptr,
                                 pawr_ptr->pawr_handle);
          sc = esl_lib_storage_append(pawr_ptr->storage_handle,
                                      &evt->data.evt_pawr_advertiser_response_report.data);
          if (sc == SL_STATUS_OK
              && (data_status == PAWR_RESPONSE_COMPLETE
                  || data_status == PAWR_RESPONSE_TRUNCATED)) {
            esl_lib_log_pawr_debug(PAWR_FMT "Sending response, PAwR handle = %u" APP_LOG_NL,
                                   pawr_ptr,
                                   pawr_ptr->pawr_handle);
            sc = send_pawr_response_event(pawr_ptr,
                                          evt->data.evt_pawr_advertiser_response_report.subevent,
                                          evt->data.evt_pawr_advertiser_response_report.response_slot);
            if (sc == SL_STATUS_OK) {
              // Clean storage
              sc = esl_lib_storage_clean(pawr_ptr->storage_handle);
              if (sc == SL_STATUS_OK) {
                esl_lib_log_pawr_debug(PAWR_FMT "PAwR storage cleaned, PAwR handle = %u" APP_LOG_NL,
                                       pawr_ptr,
                                       pawr_ptr->pawr_handle);
              }
            }
          }
        }
      }
      break;
    case sl_bt_evt_pawr_advertiser_subevent_data_request_id:
      sc = esl_lib_pawr_find(evt->data.evt_pawr_advertiser_subevent_data_request.advertising_set,
                             &pawr_ptr);
      if (sc == SL_STATUS_OK) {
        sc = esl_lib_event_list_allocate(ESL_LIB_EVT_PAWR_DATA_REQUEST, 0, &lib_evt);
        if (sc == SL_STATUS_OK) {
          lib_evt->evt_code = ESL_LIB_EVT_PAWR_DATA_REQUEST;
          lib_evt->data.evt_pawr_data_request.pawr_handle = (esl_lib_pawr_handle_t *) pawr_ptr;
          lib_evt->data.evt_pawr_data_request.subevent_data_count
            = evt->data.evt_pawr_advertiser_subevent_data_request.subevent_data_count;
          lib_evt->data.evt_pawr_data_request.subevent_start
            = evt->data.evt_pawr_advertiser_subevent_data_request.subevent_start;
          sc = esl_lib_event_list_push_back(lib_evt);
          if (sc != SL_STATUS_OK) {
            esl_lib_log_pawr_error(PAWR_FMT "Failed to add event %d", pawr_ptr, lib_evt->evt_code);
            esl_lib_memory_free(lib_evt);
          }
        }
      }
      break;
    default:
      break;
  }
  if (sc != SL_STATUS_OK && pawr_ptr != NULL) {
    esl_lib_log_pawr_error(PAWR_FMT "PAwR error, PAwR handle = %u, sc = 0x%04x" APP_LOG_NL,
                           pawr_ptr,
                           pawr_ptr->pawr_handle,
                           sc);

    // Send PAwR error if handle is present.
    (void)send_pawr_error(pawr_ptr,
                          lib_status,
                          sc,
                          pawr_ptr->state);
  }
}

// -----------------------------------------------------------------------------
// Private functions

static sl_status_t send_pawr_response_event(esl_lib_pawr_t *pawr_ptr,
                                            uint8_t        subevent,
                                            uint8_t        response_slot)
{
  sl_status_t   sc;
  size_t        data_size;
  esl_lib_evt_t *lib_evt;

  sc = esl_lib_storage_get_size(pawr_ptr->storage_handle, &data_size);
  if (sc == SL_STATUS_OK) {
    sc = esl_lib_event_list_allocate(ESL_LIB_EVT_PAWR_RESPONSE,
                                     (uint32_t)data_size,
                                     &lib_evt);
    if (sc == SL_STATUS_OK) {
      lib_evt->evt_code = ESL_LIB_EVT_PAWR_RESPONSE;
      lib_evt->data.evt_pawr_response.pawr_handle   = (esl_lib_pawr_handle_t *) pawr_ptr;
      lib_evt->data.evt_pawr_response.subevent      = subevent;
      lib_evt->data.evt_pawr_response.response_slot = response_slot;
      lib_evt->data.evt_pawr_response.data.len      = (uint32_t)data_size;
      sc = esl_lib_storage_copy(pawr_ptr->storage_handle, lib_evt->data.evt_pawr_response.data.data);
      if (sc == SL_STATUS_OK) {
        sc = esl_lib_event_list_push_back(lib_evt);
        if (sc != SL_STATUS_OK) {
          esl_lib_log_pawr_error(PAWR_FMT "Failed to add event %d", pawr_ptr, lib_evt->evt_code);
          esl_lib_memory_free(lib_evt);
        }
      }
    }
  }
  (void)esl_lib_storage_clean(pawr_ptr->storage_handle);
  return sc;
}

static sl_status_t send_pawr_status(esl_lib_pawr_t *pawr_ptr)
{
  sl_status_t   sc;
  esl_lib_evt_t *lib_evt;

  esl_lib_log_pawr_debug(PAWR_FMT "PAwR status = %u, PAwR handle = %u" APP_LOG_NL,
                         pawr_ptr,
                         pawr_ptr->enabled,
                         pawr_ptr->pawr_handle);

  sc = esl_lib_event_list_allocate(ESL_LIB_EVT_PAWR_STATUS, 0, &lib_evt);
  if (sc == SL_STATUS_OK) {
    lib_evt->evt_code = ESL_LIB_EVT_PAWR_STATUS;
    lib_evt->data.evt_pawr_status.pawr_handle  = (esl_lib_pawr_handle_t *)pawr_ptr;
    // Set state
    lib_evt->data.evt_pawr_status.enabled      = pawr_ptr->enabled;
    lib_evt->data.evt_pawr_status.configured   = pawr_ptr->configured;
    // Copy configuration data
    memcpy(&lib_evt->data.evt_pawr_status.config,
           &pawr_ptr->config,
           sizeof(esl_lib_pawr_config_t));
    // Emit the event
    sc = esl_lib_event_list_push_back(lib_evt);
    if (sc != SL_STATUS_OK) {
      esl_lib_log_pawr_error(PAWR_FMT "Failed to add event %d", pawr_ptr, lib_evt->evt_code);
      esl_lib_memory_free(lib_evt);
    }
  }
  return sc;
}

static sl_status_t send_pawr_error(esl_lib_pawr_t       *pawr,
                                   esl_lib_status_t     lib_status,
                                   sl_status_t          status,
                                   esl_lib_pawr_state_t data)
{
  sl_status_t sc;
  esl_lib_node_id_t node_id;
  node_id.type = ESL_LIB_NODE_ID_TYPE_PAWR;
  node_id.id.pawr.handle = (esl_lib_pawr_handle_t)pawr;
  sc = esl_lib_event_push_error(lib_status,
                                &node_id,
                                status,
                                (esl_lib_status_data_t)data);
  return sc;
}

static sl_status_t run_command(esl_lib_command_list_cmd_t *cmd)
{
  sl_status_t          sc                = SL_STATUS_OK;
  esl_lib_pawr_t       *pawr             = NULL;
  esl_lib_status_t     lib_status        = ESL_LIB_STATUS_NO_ERROR;

  switch (cmd->cmd_code) {
    case ESL_LIB_CMD_PAWR_ENABLE:
      // Get PAwR from the command
      pawr = (esl_lib_pawr_t *)cmd->data.cmd_pawr_enable.pawr_handle;
      esl_lib_log_pawr_debug(PAWR_FMT "Enable command, PAwR handle = %u" APP_LOG_NL,
                             pawr,
                             pawr->pawr_handle);
      // Enable or disable based on the request
      if (cmd->data.cmd_pawr_enable.enable == ESL_LIB_TRUE) {
        if (pawr->pawr_handle == SL_BT_INVALID_ADVERTISING_SET_HANDLE) {
          sc = sl_bt_advertiser_create_set(&pawr->pawr_handle);
        } else {
          // Stop first
          (void)sl_bt_periodic_advertiser_stop(pawr->pawr_handle);
        }

        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_PAWR_START_FAILED;
          // Start advertising with the stored configuration
          sc = sl_bt_pawr_advertiser_start(pawr->pawr_handle,
                                           pawr->config.adv_interval.min,
                                           pawr->config.adv_interval.max,
                                           PERIODIC_ADVERTISER_FLAG_NONE,
                                           pawr->config.subevent.count,
                                           pawr->config.subevent.interval,
                                           pawr->config.response_slot.delay,
                                           pawr->config.response_slot.spacing,
                                           pawr->config.response_slot.count);
          if (sc == SL_STATUS_OK) {
            lib_status = ESL_LIB_STATUS_NO_ERROR;
            pawr->state = ESL_LIB_PAWR_STATE_RUNNING;
            pawr->enabled = ESL_LIB_TRUE;
            send_pawr_status(pawr);
          }
        }
      } else {
        lib_status = ESL_LIB_STATUS_PAWR_STOP_FAILED;
        sc = sl_bt_periodic_advertiser_stop(pawr->pawr_handle);
        if (sc == SL_STATUS_OK) {
          lib_status = ESL_LIB_STATUS_NO_ERROR;
          pawr->state = ESL_LIB_PAWR_STATE_IDLE;
          pawr->enabled = ESL_LIB_FALSE;
          (void)sl_bt_advertiser_delete_set(pawr->pawr_handle);
          pawr->pawr_handle = SL_BT_INVALID_ADVERTISING_SET_HANDLE;
          send_pawr_status(pawr);
        }
      }
      break;
    case ESL_LIB_CMD_PAWR_SET_DATA:
      lib_status = ESL_LIB_STATUS_PAWR_SET_DATA_FAILED;
      pawr = (esl_lib_pawr_t *)cmd->data.cmd_pawr_set_data.pawr_handle;
      // is it a retry attempt?
      uint8_t retry_count = ESL_LIB_PAWR_SET_DATA_RETRY_COUNT_MAX - cmd->data.cmd_pawr_set_data.retry;

      if (retry_count) {
        esl_lib_log_pawr_warning("Retry set data %d / %d" APP_LOG_NL,
                                 (retry_count),
                                 ESL_LIB_PAWR_SET_DATA_RETRY_COUNT_MAX);
      } else {
        esl_lib_log_pawr_debug(PAWR_FMT "Set data command, PAwR handle = %u" APP_LOG_NL,
                               pawr,
                               pawr->pawr_handle);
      }

      sc = sl_bt_pawr_advertiser_set_subevent_data(pawr->pawr_handle,
                                                   cmd->data.cmd_pawr_set_data.subevent,
                                                   0,
                                                   cmd->data.cmd_pawr_set_data.response_slot_max,
                                                   cmd->data.cmd_pawr_set_data.data.len,
                                                   cmd->data.cmd_pawr_set_data.data.data);

      if (sc == SL_STATUS_OK) {
        esl_lib_log_pawr_debug(PAWR_FMT "Set data for subevent %u with %u expected responses, PAwR handle = %u" APP_LOG_NL,
                               pawr,
                               cmd->data.cmd_pawr_set_data.subevent,
                               cmd->data.cmd_pawr_set_data.response_slot_max,
                               pawr->pawr_handle);
        lib_status = ESL_LIB_STATUS_NO_ERROR;
      }
      break;
    case ESL_LIB_CMD_PAWR_CONFIGURE:
      pawr = (esl_lib_pawr_t *)cmd->data.cmd_pawr_config.pawr_handle;
      esl_lib_log_pawr_debug(PAWR_FMT "Configure command, PAwR handle = %u" APP_LOG_NL,
                             pawr,
                             pawr->pawr_handle);
      // Copy data
      memcpy(&pawr->config,
             &cmd->data.cmd_pawr_config.pawr_config,
             sizeof(esl_lib_pawr_config_t));
      lib_status = ESL_LIB_STATUS_NO_ERROR;
      // Set configured
      pawr->configured = ESL_LIB_TRUE;
      break;
    case ESL_LIB_CMD_GET_PAWR_STATUS:
      pawr = (esl_lib_pawr_t *)cmd->data.cmd_get_pawr_status;
      send_pawr_status(pawr);
      sc = SL_STATUS_OK;
      lib_status = ESL_LIB_STATUS_NO_ERROR;
      break;
    default:
      break;
  }
  if (sc != SL_STATUS_OK && pawr != NULL) {
    if (!(pawr->command->cmd_code == ESL_LIB_CMD_PAWR_SET_DATA
          && (sc == SL_STATUS_BT_CTRL_COMMAND_DISALLOWED
              || sc == SL_STATUS_BT_CTRL_PAWR_TOO_LATE
              || sc == SL_STATUS_BT_CTRL_PAWR_TOO_EARLY))) {
      esl_lib_log_pawr_error(PAWR_FMT "Command error, PAwR handle = %u, sc = 0x%04x" APP_LOG_NL,
                             pawr,
                             pawr->pawr_handle,
                             sc);
      // Send pawr error event immediately in almost all cases, but various set data issues
      (void)send_pawr_error(pawr,
                            lib_status,
                            sc,
                            pawr->state);
    } else {
      sc = SL_STATUS_TRANSMIT; // Convert to common status code for those set of failures
    }
  }
  return sc;
}
