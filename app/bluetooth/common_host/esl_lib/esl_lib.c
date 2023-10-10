/***************************************************************************//**
 * @file
 * @brief ESL Access Point Host Library.
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
#include "system.h"
#include "esl_lib.h"
#include "esl_lib_core.h"
#include "app_log.h"
#include "esl_lib_event_list.h"
#include "esl_lib_command_list.h"
#include "esl_lib_connection.h"
#include "esl_lib_pawr.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Forward declaration of private functions

static void event_handler_step(void);
static bool filter_event(esl_lib_evt_t *evt);

// -----------------------------------------------------------------------------
// Private variables

// Main loop execution status.
static volatile bool run = true;

// Event handler function
static esl_lib_on_event_t event_handler_cb;

// -----------------------------------------------------------------------------
// Library public functions

// -------------------------------
// Library management functions

sl_status_t esl_lib_start(char                   *config,
                          esl_lib_on_event_t     event_handler,
                          esl_lib_log_callback_t log_fn)
{
  esl_lib_log_api_debug("Requested: Start" APP_LOG_NL);

  CHECK_NULL(event_handler);

  // Save event handler callback
  event_handler_cb = event_handler;

  esl_lib_log_set_callback(log_fn);

  // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
  // Note that if the kernel is present, processing task(s) will be created by
  // this call.
  sl_system_init();

  // Initialize the library.
  esl_lib_init(config);

  while (run) {
    // Do not remove this call: Silicon Labs components process action routine
    // must be called from the super loop.
    sl_system_process_action();

    // Library process.
    esl_lib_process_action();

    // Run event handler
    event_handler_step();
  }

  // Deinitialize the library
  esl_lib_deinit();

  return SL_STATUS_OK;
}

sl_status_t esl_lib_stop(void)
{
  esl_lib_log_api_debug("Requested: Stop" APP_LOG_NL);

  run = false;
  return SL_STATUS_OK;
}

// -------------------------------
// Connection handling

sl_status_t esl_lib_connect(esl_lib_address_t         address,
                            esl_lib_pawr_subevent_t   *pawr,
                            esl_lib_address_t         *identity,
                            esl_lib_key_type_t        key_type,
                            esl_lib_array_t           *key,
                            esl_lib_gattdb_handles_t  *gattdb)
{
  sl_status_t                sc;
  esl_lib_command_list_cmd_t *cmd;

  uint32_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_connect_t);

  uint32_t tlv_size  = 0;
  uint8_t  *data_ptr = NULL;
  esl_lib_connect_tlv_t *tlv = NULL;

  esl_lib_log_api_debug("Requested: Connect" APP_LOG_NL);

  // Check for NULL key
  if (key_type != ESL_LIB_KEY_TYPE_NO_KEY && key == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  // Check for valid LTK
  if (key_type == ESL_LIB_KEY_TYPE_LTK && key->len != ESL_LIB_LTK_SIZE) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (key_type == ESL_LIB_KEY_TYPE_OOB_DATA && key->len != ESL_LIB_OOB_SIZE) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (key_type == ESL_LIB_KEY_TYPE_PASSKEY && key->len != ESL_LIB_PASSKEY_SIZE) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (gattdb != NULL) {
    // Check validity of the handles.
    sc = esl_lib_connection_check_gattdb_handles(gattdb);
    if (sc != SL_STATUS_OK) {
      return sc;
    }
    // Add GATTDB handle size with overhead
    tlv_size += sizeof(esl_lib_connect_tlv_t) + sizeof(esl_lib_gattdb_handles_t);
  }

  // Add key size with overhead
  if (key_type != ESL_LIB_KEY_TYPE_NO_KEY) {
    tlv_size += sizeof(esl_lib_connect_tlv_t) + key->len;
  }
  // Add PAwR size with overhead
  if (pawr != NULL) {
    // Check handle
    if (pawr->handle == ESL_LIB_INVALID_HANDLE) {
      return SL_STATUS_INVALID_HANDLE;
    }
    tlv_size += sizeof(esl_lib_connect_tlv_t) + sizeof(esl_lib_pawr_subevent_t);
  }
  // Add identity address size with overhead
  if (identity != NULL) {
    tlv_size += sizeof(esl_lib_connect_tlv_t) + sizeof(esl_lib_address_t);
  }

  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size + tlv_size);
  if (cmd != NULL) {
    cmd->data.cmd_connect.retries_left = ESL_LIB_CONNECTION_RETRY_COUNT_MAX;
    cmd->cmd_code = ESL_LIB_CMD_CONNECT;
    cmd->data.cmd_connect.conn_hnd = ESL_LIB_INVALID_HANDLE;
    // Set address and type
    cmd->data.cmd_connect.address.address_type = address.address_type;
    memcpy(cmd->data.cmd_connect.address.addr,
           address.addr,
           sizeof(address.addr));

    // Set TLV data length
    cmd->data.cmd_connect.tlv_data.len = tlv_size;
    data_ptr = (uint8_t *)cmd->data.cmd_connect.tlv_data.data;

    // Point TLV
    tlv = (esl_lib_connect_tlv_t *)data_ptr;

    // Add PAwR
    if (pawr != NULL) {
      tlv->type = ESL_LIB_CONNECT_DATA_TYPE_PAWR;
      tlv->data.len = sizeof(esl_lib_pawr_subevent_t);
      memcpy(tlv->data.data, (uint8_t*)pawr, tlv->data.len);
      data_ptr += sizeof(esl_lib_connect_tlv_t) + tlv->data.len;
      // Point TLV
      tlv = (esl_lib_connect_tlv_t *)data_ptr;
    }

    // Add identity address
    if (identity != NULL) {
      tlv->type = ESL_LIB_CONNECT_DATA_TYPE_IDENTITY_ADDRESS;
      tlv->data.len = sizeof(esl_lib_address_t);
      memcpy(tlv->data.data, (uint8_t*)identity, tlv->data.len);
      data_ptr += sizeof(esl_lib_connect_tlv_t) + tlv->data.len;
    }

    // Point TLV
    tlv = (esl_lib_connect_tlv_t *)data_ptr;

    // Add GATT DB handles
    if (gattdb != NULL) {
      tlv->type = ESL_LIB_CONNECT_DATA_TYPE_GATTDB_HANDLES;
      tlv->data.len = sizeof(esl_lib_gattdb_handles_t);
      memcpy(tlv->data.data, (uint8_t*)gattdb, tlv->data.len);
      data_ptr += sizeof(esl_lib_connect_tlv_t) + tlv->data.len;
      // Point TLV
      tlv = (esl_lib_connect_tlv_t *)data_ptr;
    }

    // Add key
    if (key != NULL) {
      switch (key_type) {
        case ESL_LIB_KEY_TYPE_LTK:
          tlv->type = ESL_LIB_CONNECT_DATA_TYPE_LTK;
          break;
        case ESL_LIB_KEY_TYPE_PASSKEY:
          tlv->type = ESL_LIB_CONNECT_DATA_TYPE_PASSKEY;
          break;
        case ESL_LIB_KEY_TYPE_OOB_DATA:
          tlv->type = ESL_LIB_CONNECT_DATA_TYPE_OOB_DATA;
          break;
        default:
          break;
      }
      tlv->data.len = key->len;
      memcpy(tlv->data.data, key->data, tlv->data.len);
    }

    // Send command to core connection handle present in this command
    sc = esl_lib_core_add_command(cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t esl_lib_close_connection(esl_lib_connection_handle_t connection_handle)
{
  sl_status_t sc = SL_STATUS_INVALID_PARAMETER;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Close connection" APP_LOG_NL);

  if (!esl_lib_connection_contains(connection_handle)) {
    return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
  }

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN + sizeof(esl_lib_connection_handle_t);

  if (connection_handle != ESL_LIB_INVALID_HANDLE) {
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_CLOSE_CONNECTION;
      cmd->data.cmd_close_connection = connection_handle;
      // Send command
      sc = esl_lib_connection_add_command(connection_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  } else {
    sc = SL_STATUS_INVALID_HANDLE;
  }

  return sc;
}

// -------------------------------
// ESL information

sl_status_t esl_lib_get_tag_info(esl_lib_connection_handle_t connection_handle)
{
  sl_status_t sc = SL_STATUS_INVALID_PARAMETER;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Get Tag Info" APP_LOG_NL);

  if (!esl_lib_connection_contains(connection_handle)) {
    return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
  }

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN + sizeof(esl_lib_connection_handle_t);

  if (connection_handle != ESL_LIB_INVALID_HANDLE) {
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_GET_TAG_INFO;
      cmd->data.cmd_get_tag_info = connection_handle;
      // Send command
      sc = esl_lib_connection_add_command(connection_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  } else {
    sc = SL_STATUS_INVALID_HANDLE;
  }

  return sc;
}

sl_status_t esl_lib_configure_tag(esl_lib_connection_handle_t connection_handle,
                                  esl_lib_long_array_t        *tlv_data,
                                  esl_lib_bool_t              att_response)
{
  sl_status_t sc = SL_STATUS_INVALID_PARAMETER;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Configure Tag %s response" APP_LOG_NL,
                        (att_response == ESL_LIB_TRUE) ? "with" : "without");

  if (tlv_data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (!esl_lib_connection_contains(connection_handle)) {
    return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
  }

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                + sizeof(esl_lib_command_list_cmd_configure_tag_t)
                + tlv_data->len;

  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);

  if (cmd != NULL) {
    cmd->cmd_code = ESL_LIB_CMD_CONFIGURE_TAG;
    cmd->data.cmd_configure_tag.connection_handle = connection_handle;
    cmd->data.cmd_configure_tag.att_response = att_response;
    // Copy array
    cmd->data.cmd_configure_tag.tlv_data.len = tlv_data->len;
    memcpy(cmd->data.cmd_configure_tag.tlv_data.data,
           tlv_data->data,
           tlv_data->len);
    // Send command
    sc = esl_lib_connection_add_command(connection_handle,
                                        cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t esl_lib_write_control_point(esl_lib_connection_handle_t connection_handle,
                                        esl_lib_array_t             *data,
                                        esl_lib_bool_t              att_response)
{
  sl_status_t sc = SL_STATUS_INVALID_PARAMETER;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Write Control Point %s response" APP_LOG_NL,
                        (att_response == ESL_LIB_TRUE) ? "with" : "without");
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (!esl_lib_connection_contains(connection_handle)) {
    return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
  }
  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                + sizeof(esl_lib_command_list_cmd_write_control_point_t)
                + data->len;
  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
  if (cmd != NULL) {
    cmd->cmd_code = ESL_LIB_CMD_WRITE_CONTROL_POINT;
    cmd->data.cmd_write_control_point.connection_handle = connection_handle;
    cmd->data.cmd_write_control_point.att_response = att_response;
    // Copy array
    cmd->data.cmd_write_control_point.data.len = data->len;
    memcpy(cmd->data.cmd_write_control_point.data.data,
           data->data,
           data->len);
    // Send command
    sc = esl_lib_connection_add_command(connection_handle,
                                        cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

// -------------------------------
// PAwR functions

sl_status_t esl_lib_pawr_create(esl_lib_pawr_handle_t *handle_out)
{
  esl_lib_pawr_t *pawr_ptr = ESL_LIB_INVALID_HANDLE;
  sl_status_t sc = SL_STATUS_NULL_POINTER;

  esl_lib_log_api_debug("Requested: PAwR Create" APP_LOG_NL);

  if (handle_out != NULL) {
    // Add the set to the relationships and get the handle
    sc = esl_lib_pawr_add(&pawr_ptr);
    if (sc == SL_STATUS_OK) {
      // Assign handle
      *handle_out = (esl_lib_pawr_handle_t)pawr_ptr;
    }
  }

  return sc;
}

sl_status_t esl_lib_pawr_remove(esl_lib_pawr_handle_t pawr_handle)
{
  sl_status_t    sc    = SL_STATUS_INVALID_HANDLE;
  esl_lib_pawr_t *pawr = (esl_lib_pawr_t *)pawr_handle;

  esl_lib_log_api_debug("Requested: PAwR Remove" APP_LOG_NL);

  if (pawr_handle != ESL_LIB_INVALID_HANDLE) {
    // Check if it can be removed
    if (pawr->state > ESL_LIB_PAWR_STATE_IDLE) {
      sc = SL_STATUS_IN_PROGRESS;
    } else {
      // Must be stopped before removal
      sc = esl_lib_pawr_remove_ptr(pawr);
    }
  }

  return sc;
}

sl_status_t esl_lib_pawr_enable(esl_lib_pawr_handle_t pawr_handle,
                                esl_lib_bool_t        enable)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: PAwR Enable" APP_LOG_NL);

  if (pawr_handle != ESL_LIB_INVALID_HANDLE) {
    if (!esl_lib_pawr_contains(pawr_handle)) {
      return SL_STATUS_NOT_FOUND;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_pawr_enable_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_PAWR_ENABLE;
      // Copy data
      cmd->data.cmd_pawr_enable.pawr_handle = pawr_handle;
      cmd->data.cmd_pawr_enable.enable      = enable;
      // Send command
      sc = esl_lib_pawr_add_command(pawr_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }
  return sc;
}

sl_status_t esl_lib_pawr_set_data(esl_lib_pawr_handle_t pawr_handle,
                                  uint8_t               subevent,
                                  uint8_t               response_slot_max,
                                  esl_lib_array_t       *payload)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: PAwR Set Data for subevent %u" APP_LOG_NL, subevent);

  if (payload == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (pawr_handle != ESL_LIB_INVALID_HANDLE) {
    if (!esl_lib_pawr_contains(pawr_handle)) {
      return SL_STATUS_NOT_FOUND;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_pawr_set_data_t)
                  + payload->len;
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_PAWR_SET_DATA;
      // Copy data
      cmd->data.cmd_pawr_set_data.pawr_handle       = pawr_handle;
      cmd->data.cmd_pawr_set_data.subevent          = subevent;
      cmd->data.cmd_pawr_set_data.response_slot_max = response_slot_max;
      cmd->data.cmd_pawr_set_data.retry             = ESL_LIB_PAWR_SET_DATA_RETRY_COUNT_MAX;
      cmd->data.cmd_pawr_set_data.data.len          = payload->len;
      // Copy payload array
      memcpy(cmd->data.cmd_pawr_set_data.data.data,
             payload->data,
             payload->len);
      // Send command
      sc = esl_lib_pawr_add_command(pawr_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }
  return sc;
}

sl_status_t esl_lib_pawr_configure(esl_lib_pawr_handle_t       pawr_handle,
                                   const esl_lib_pawr_config_t *pawr_config)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: PAwR Configure" APP_LOG_NL);

  if (pawr_config == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (pawr_handle != ESL_LIB_INVALID_HANDLE) {
    if (!esl_lib_pawr_contains(pawr_handle)) {
      return SL_STATUS_NOT_FOUND;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_pawr_configure_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_PAWR_CONFIGURE;
      // Copy data
      cmd->data.cmd_pawr_config.pawr_handle = pawr_handle;
      // Copy config
      memcpy(&cmd->data.cmd_pawr_config.pawr_config,
             pawr_config,
             sizeof(esl_lib_pawr_config_t));
      // Send command
      sc = esl_lib_pawr_add_command(pawr_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }
  return sc;
}

sl_status_t esl_lib_get_pawr_status(esl_lib_pawr_handle_t pawr_handle)
{
  sl_status_t sc;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Get PAwR status" APP_LOG_NL);

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN + sizeof(esl_lib_pawr_handle_t);
  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
  if (cmd != NULL) {
    cmd->cmd_code = ESL_LIB_CMD_GET_PAWR_STATUS;
    cmd->data.cmd_get_pawr_status = pawr_handle;
    // Send command
    sc = esl_lib_pawr_add_command(pawr_handle, cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }
  return sc;
}

sl_status_t esl_lib_initiate_past(esl_lib_connection_handle_t connection_handle,
                                  esl_lib_pawr_handle_t       pawr_handle)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Initiate PAST" APP_LOG_NL);

  if ((connection_handle != ESL_LIB_INVALID_HANDLE)
      && (pawr_handle != ESL_LIB_INVALID_HANDLE)) {
    if (!esl_lib_connection_contains(connection_handle)
        || !esl_lib_pawr_contains(pawr_handle)) {
      return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_initiate_past_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_INITIATE_PAST;
      // Copy data
      cmd->data.cmd_init_past.pawr_handle       = pawr_handle;
      cmd->data.cmd_init_past.connection_handle = connection_handle;
      // Send command
      sc = esl_lib_connection_add_command(connection_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }

  return sc;
}

// -------------------------------
// Image transfer

sl_status_t esl_lib_write_image(esl_lib_connection_handle_t connection_handle,
                                uint8_t                     img_index,
                                size_t                      img_size,
                                void                        *img_data)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Write %u bytes of image data to slot %u " APP_LOG_NL,
                        (uint32_t)img_size, img_index);

  if (connection_handle != ESL_LIB_INVALID_HANDLE) {
    if (!esl_lib_connection_contains(connection_handle)) {
      return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_write_image_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      // Allocate image data
      uint8_t *internal_img_data = (uint8_t *)esl_lib_memory_allocate(img_size);
      if (internal_img_data != NULL) {
        // Copy image data
        memcpy(internal_img_data, img_data, img_size);
        // Set command parameters
        cmd->cmd_code = ESL_LIB_CMD_WRITE_IMAGE;

        // Copy data
        cmd->data.cmd_write_image.connection_handle = connection_handle;
        cmd->data.cmd_write_image.img_index         = img_index;
        cmd->data.cmd_write_image.img_size          = img_size;
        cmd->data.cmd_write_image.img_data_copied   = internal_img_data;
        // Send command
        sc = esl_lib_connection_add_command(connection_handle, cmd);
        if (sc != SL_STATUS_OK) {
          // Free data on error
          esl_lib_memory_free(cmd);
          esl_lib_memory_free(internal_img_data);
        }
      } else {
        // Free command on fail
        esl_lib_memory_free(cmd);
        sc = SL_STATUS_ALLOCATION_FAILED;
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }

  return sc;
}

sl_status_t esl_lib_get_image_type(esl_lib_connection_handle_t connection_handle,
                                   uint8_t                     img_index)
{
  sl_status_t sc = SL_STATUS_INVALID_HANDLE;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Get Image Type of index %u" APP_LOG_NL, img_index);

  if (connection_handle != ESL_LIB_INVALID_HANDLE) {
    if (!esl_lib_connection_contains(connection_handle)) {
      return SL_STATUS_BT_CTRL_UNKNOWN_CONNECTION_IDENTIFIER;
    }
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_command_list_cmd_get_image_type_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      // Set command parameters
      cmd->cmd_code = ESL_LIB_CMD_GET_IMAGE_TYPE;

      // Copy data
      cmd->data.cmd_get_image_type.connection_handle = connection_handle;
      cmd->data.cmd_get_image_type.img_index         = img_index;
      // Send command
      sc = esl_lib_connection_add_command(connection_handle, cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }

  return sc;
}

// -------------------------------
// Scanning

sl_status_t esl_lib_scan_configure(esl_lib_scan_parameters_t *params)
{
  sl_status_t sc = SL_STATUS_NULL_POINTER;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Scan configure" APP_LOG_NL);

  if (params != NULL) {
    size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN
                  + sizeof(esl_lib_scan_parameters_t);
    // Allocate memory for the command
    cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
    if (cmd != NULL) {
      cmd->cmd_code = ESL_LIB_CMD_SCAN_CONFIG;
      // Copy parameters
      memcpy(&cmd->data.cmd_scan_config,
             params,
             sizeof(esl_lib_scan_parameters_t));
      // Send command
      sc = esl_lib_core_add_command(cmd);
      if (sc != SL_STATUS_OK) {
        esl_lib_memory_free(cmd);
      }
    } else {
      sc = SL_STATUS_ALLOCATION_FAILED;
    }
  }
  return sc;
}

sl_status_t esl_lib_scan_enable(esl_lib_bool_t enable)
{
  sl_status_t sc;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Scan enable" APP_LOG_NL);

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN + sizeof(esl_lib_command_list_cmd_scan_enable_t);
  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
  if (cmd != NULL) {
    cmd->cmd_code = ESL_LIB_CMD_SCAN_ENABLE;
    cmd->data.cmd_scan_enable.enable  = enable;
    // Send command
    sc = esl_lib_core_add_command(cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t esl_lib_get_scan_status(void)
{
  sl_status_t sc;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: Get scan status" APP_LOG_NL);

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN;
  // Allocate memory for the command
  cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
  if (cmd != NULL) {
    cmd->cmd_code = ESL_LIB_CMD_GET_SCAN_STATUS;
    // Send command
    sc = esl_lib_core_add_command(cmd);
    if (sc != SL_STATUS_OK) {
      esl_lib_memory_free(cmd);
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }
  return sc;
}

sl_status_t esl_lib_general_cmd(uint8_t              cmd_code,
                                esl_lib_long_array_t *data)
{
  sl_status_t sc;
  esl_lib_command_list_cmd_t *cmd;

  esl_lib_log_api_debug("Requested: General CMD 0x%02x" APP_LOG_NL, cmd_code);

  size_t size = ESL_LIB_COMMAND_LIST_HEADER_LEN;
  switch (cmd_code) {
    case ESL_LIB_CMD_AP_CONTROL_ADV_ENABLE:
    case ESL_LIB_CMD_AP_CONTROL_CP_RESPONSE:
    case ESL_LIB_CMD_AP_CONTROL_IT_RESPONSE:
      if (data != NULL) {
        size += sizeof(esl_lib_long_array_t) + data->len;
        // Allocate memory for the command
        cmd = (esl_lib_command_list_cmd_t *)esl_lib_memory_allocate(size);
        if (cmd != NULL) {
          cmd->cmd_code = cmd_code;
          cmd->data.cmd_ap_control.len = data->len;
          memcpy(cmd->data.cmd_ap_control.data,
                 data->data,
                 data->len);
          // Send command
          sc = esl_lib_core_add_command(cmd);
          if (sc != SL_STATUS_OK) {
            esl_lib_memory_free(cmd);
          }
        } else {
          sc = SL_STATUS_ALLOCATION_FAILED;
        }
      } else {
        sc = SL_STATUS_NULL_POINTER;
      }
      break;
    default:
      sc = SL_STATUS_INVALID_PARAMETER;
      break;
  }

  return sc;
}

// -----------------------------------------------------------------------------
// Private functions

static bool filter_event(esl_lib_evt_t *evt)
{
  switch (evt->evt_code) {
    case ESL_LIB_EVT_PAWR_DATA_REQUEST:
    case ESL_LIB_EVT_TAG_FOUND:
      return false;
    default:
      return true;
  }
}

// Event handler mechanism
static void event_handler_step(void)
{
  esl_lib_evt_t *last_evt = esl_lib_event_list_get_first();
  if (last_evt != NULL) {
    const bool log_event = filter_event(last_evt);
    if (log_event) {
      esl_lib_log_api_debug("EVT emitted, type = %u" APP_LOG_NL, last_evt->evt_code);
    }
    if (event_handler_cb != NULL) {
      if (log_event) {
        esl_lib_log_api_debug("Calling EVT callback for type %u" APP_LOG_NL, last_evt->evt_code);
      }
      event_handler_cb(last_evt->evt_code, &(last_evt->data));
      if (log_event) {
        esl_lib_log_api_debug("EVT callback finished for type %u" APP_LOG_NL, last_evt->evt_code);
      }
    }
    esl_lib_event_list_remove_first();
  }
}
