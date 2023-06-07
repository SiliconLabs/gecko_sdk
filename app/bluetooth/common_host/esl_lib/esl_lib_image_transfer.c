/***************************************************************************//**
 * @file
 * @brief ESL AP Library - Image Transfer implementation
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
#include <stdint.h>
#include <stdbool.h>
#include "esl_lib_image_transfer.h"
#include "sl_slist.h"
#include "sl_bt_ots_client.h"
#include "sl_bt_l2cap_transfer.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"
#include "app_timer.h"

// -----------------------------------------------------------------------------
// Definitions

#define INVALID_SERVICE_HANDLE        0
#define IMAGE_ID_OFFSET               0x100
#define L2CAP_CHANNEL_PDU             240
#define L2CAP_CHANNEL_SDU             SL_BT_L2CAP_TRANSFER_MAX_SDU
#define WRITE_MODE                    SL_BT_OTS_WRITE_MODE_TRUNCATE_MASK
#define ATT_ERR_OFFSET                0x1100
#define IT_FMT                        ESL_LIB_LOG_HANDLE_FORMAT
#define TIMEOUT_INIT_MS               10000
#define TIMEOUT_GATT_MS               1000
#define TIMEOUT_TRANSFER_MS           60000

typedef enum {
  OTS_STATE_NOT_INITIALIZED,          // Initial state
  OTS_STATE_ERROR,                    // Error state
  OTS_STATE_INITIALIZED,              // OTS Client initialized
  OTS_STATE_IDLE,                     // Server features read
  OTS_STATE_GO_TO,                    // SELECT by goto
  OTS_STATE_FIRST,                    // SELECT by first - next*
  OTS_STATE_NEXT,                     // SELECT by first - next*
  OTS_STATE_OBJECT_TYPE,              // Read object type (object selected)
  OTS_STATE_WRITE,                    // Write object data
} ots_state_t;

typedef enum {
  OTS_COMMAND_NONE,                   // No active command
  OTS_COMMAND_OBJECT_TYPE,            // Object type command
  OTS_COMMAND_WRITE,                  // Write object command
} ots_command_t;

// Structure type holding a client
typedef struct {
  sl_slist_node_t                            node;
  esl_lib_image_transfer_handle_t            image_transfer_handle;
  uint8_t                                    connection_handle;
  sl_bt_ots_client_t                         ots_client;
  sl_bt_ots_features_t                       ots_server_features;
  ots_state_t                                ots_state;
  ots_command_t                              ots_ongoing_command;
  uint32_t                                   ots_write_offset;
  uint32_t                                   ots_write_size;
  uint8_t                                    *ots_write_data;
  sl_bt_ots_object_id_t                      ots_current_object_id;
  sl_bt_ots_object_id_t                      ots_requested_object_id;
  uint8_t                                    requested_image_index;
  esl_image_transfer_state_t                 transfer_state;
  sl_status_t                                result;
  app_timer_t                                timer;
  esl_lib_image_transfer_type_callback_t     cb_type;
  esl_lib_image_transfer_finished_callback_t cb_finish;
  esl_lib_image_transfer_status_callback_t   cb_status;
} image_transfer_t;

// -----------------------------------------------------------------------------
// Forward declaration of private functions

// Utility functions
static sl_status_t ots_error_to_sl_status(uint16_t att_error,
                                          sl_bt_ots_oacp_response_code_t response);
static image_transfer_t *find_image_transfer_by_handle(esl_lib_image_transfer_handle_t handle);
static image_transfer_t *find_image_transfer_by_client(sl_bt_ots_client_handle_t client);
static void set_state(image_transfer_t           *transfer,
                      esl_image_transfer_state_t state,
                      sl_status_t                result,
                      sl_bt_ots_gattdb_handles_t *gattdb_handles);
static void image_index_to_object_id(uint8_t               image_index,
                                     sl_bt_ots_object_id_t *object_id);
static bool compare_ids(sl_bt_ots_object_id_t *object_id_a,
                        sl_bt_ots_object_id_t *object_id_b);
static sl_status_t search_image(image_transfer_t *image_transfer,
                                uint8_t          image_index,
                                bool             *current_object_selected);
static void start_requested_operation(image_transfer_t *image_transfer);
static void remove_transfer(image_transfer_t *image_transfer,
                            sl_status_t      sc,
                            bool             finish_transfer);
static void operation_finished(image_transfer_t *image_transfer,
                               sl_status_t sc,
                               bool finish_transfer);

// OTS private callback functions
static void ots_init(sl_bt_ots_client_handle_t  client,
                     sl_status_t                result,
                     sl_bt_ots_gattdb_handles_t *gattdb_handles);
static void ots_features(sl_bt_ots_client_handle_t client,
                         sl_status_t               status,
                         sl_bt_ots_features_t      features);
static void ots_meta_read(sl_bt_ots_client_handle_t                   client,
                          sl_bt_ots_object_id_t                       *object,
                          uint16_t                                    status,
                          sl_bt_ots_object_metadata_read_event_type_t event,
                          sl_bt_ots_object_metadata_read_parameters_t *parameters);
static void ots_olcp(sl_bt_ots_client_handle_t      client,
                     sl_bt_ots_object_id_t          *object,
                     sl_bt_ots_olcp_opcode_t        opcode,
                     uint16_t                       status,
                     sl_bt_ots_olcp_response_code_t response,
                     uint32_t                       number_of_objects);
static void ots_oacp(sl_bt_ots_client_handle_t      client,
                     sl_bt_ots_object_id_t          *object,
                     sl_bt_ots_oacp_opcode_t        opcode,
                     uint16_t                       status,
                     sl_bt_ots_oacp_response_code_t response,
                     sl_bt_ots_oacp_response_data_t *data);
static void ots_data_transmit(sl_bt_ots_client_handle_t client,
                              sl_bt_ots_object_id_t     *object,
                              uint32_t                  current_offset,
                              uint32_t                  size,
                              uint8_t                   **data,
                              uint32_t                  *data_size);
static void ots_finished(sl_bt_ots_client_handle_t   client,
                         sl_bt_ots_object_id_t       *object,
                         sl_bt_ots_transfer_result_t result);
static void ots_disconnect(sl_bt_ots_client_handle_t client);

// Timer callbacks
static void gatt_timeout(app_timer_t *timer,
                         void        *data);
static void init_timeout(app_timer_t *timer,
                         void        *data);
static void transfer_timeout(app_timer_t *timer,
                             void        *data);

// -----------------------------------------------------------------------------
// Private variables

// Start of the linked list which contains the transfers
static sl_slist_node_t *image_transfer_list = NULL;

// OTS Callback structure
static sl_bt_ots_client_callbacks_t callbacks = {
  .on_init                   = ots_init,
  .on_features_read          = ots_features,
  .on_metadata_read_finished = ots_meta_read,
  .on_olcp_response          = ots_olcp,
  .on_oacp_response          = ots_oacp,
  .on_data_transmit          = ots_data_transmit,
  .on_data_transfer_finished = ots_finished,
  .on_disconnect             = ots_disconnect
};

// -----------------------------------------------------------------------------
// Public functions

sl_status_t esl_lib_image_transfer_init(uint8_t                                    connection,
                                        uint32_t                                   ots_service_handle,
                                        esl_lib_image_transfer_status_callback_t   status_callback,
                                        esl_lib_image_transfer_type_callback_t     type_callback,
                                        esl_lib_image_transfer_finished_callback_t finish_callback,
                                        esl_lib_ots_gattdb_handles_t               *gattdb_handles,
                                        esl_lib_image_transfer_handle_t            *handle_out)
{
  sl_status_t sc;
  image_transfer_t *transfer;
  sl_bt_ots_gattdb_handles_t ots_handles;
  sl_bt_ots_gattdb_handles_t *ots_handle_ptr = NULL;

  esl_lib_log_it_info("Image transfer init, connection handle = %u" APP_LOG_NL,
                      connection);

  // Check for NULLs
  if (handle_out == NULL
      || status_callback == NULL
      || type_callback == NULL
      || finish_callback == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (connection == SL_BT_INVALID_CONNECTION_HANDLE
      || ots_service_handle == INVALID_SERVICE_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }

  transfer = (image_transfer_t *)esl_lib_memory_allocate(sizeof(image_transfer_t));
  if (transfer == ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE) {
    return SL_STATUS_ALLOCATION_FAILED;
  } else {
    transfer->image_transfer_handle = (esl_lib_image_transfer_handle_t)transfer;
    transfer->ots_state             = OTS_STATE_NOT_INITIALIZED;
    transfer->ots_ongoing_command   = OTS_COMMAND_NONE;
    transfer->transfer_state        = ESL_LIB_IMAGE_TRANSFER_STATE_NOT_INITIALIZED;
    transfer->result                = SL_STATUS_OK;
    transfer->ots_write_data        = NULL;
    transfer->connection_handle     = connection;
    memset(&transfer->ots_current_object_id, 0, sizeof(transfer->ots_current_object_id));

    if (gattdb_handles != NULL) {
      memcpy(ots_handles.characteristics.array,
             *gattdb_handles,
             sizeof(ots_handles.characteristics.array));
      ots_handles.service = ots_service_handle;
      ots_handle_ptr = &ots_handles;
      esl_lib_log_it_info("Image transfer GATTDB specified, connection handle = %u" APP_LOG_NL,
                          connection);
    }

    // Initialize OTS client
    sc = sl_bt_ots_client_init(&transfer->ots_client,
                               connection,
                               ots_service_handle,
                               &callbacks,
                               ots_handle_ptr);
    if (sc == SL_STATUS_OK) {
      // Assign callbacks
      transfer->cb_status = status_callback;
      transfer->cb_type   = type_callback;
      transfer->cb_finish = finish_callback;

      // Add to the transfer list
      sl_slist_push(&image_transfer_list, &transfer->node);

      *handle_out = transfer->image_transfer_handle;

      esl_lib_log_it_info(IT_FMT "Image transfer init started, connection handle = %u" APP_LOG_NL,
                          transfer->image_transfer_handle,
                          connection);
      // Start timer
      app_timer_start(&transfer->timer,
                      TIMEOUT_INIT_MS,
                      init_timeout,
                      transfer,
                      false);
    } else {
      esl_lib_log_it_error(IT_FMT "Image transfer init failed, sc = 0x%04x, connection handle = %u" APP_LOG_NL,
                           transfer->image_transfer_handle,
                           sc,
                           connection);
      // Free up memory on error
      esl_lib_memory_free(transfer);
    }
  }
  return sc;
}

sl_status_t esl_lib_image_transfer_get_type(esl_lib_image_transfer_handle_t handle,
                                            uint8_t                         image_index)
{
  sl_status_t sc;
  image_transfer_t *image_transfer;

  esl_lib_log_it_info(IT_FMT "Get type for image index %u" APP_LOG_NL,
                      handle,
                      image_index);

  if (handle == ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }

  image_transfer = find_image_transfer_by_handle(handle);
  if (image_transfer == NULL) {
    return SL_STATUS_NOT_FOUND;
  }
  switch (image_transfer->transfer_state) {
    case ESL_LIB_IMAGE_TRANSFER_STATE_BUSY:
      return SL_STATUS_BUSY;
    case ESL_LIB_IMAGE_TRANSFER_STATE_INIT_IN_PROGRESS:
    case ESL_LIB_IMAGE_TRANSFER_STATE_NOT_INITIALIZED:
      return SL_STATUS_NOT_INITIALIZED;
    case ESL_LIB_IMAGE_TRANSFER_REMOVED:
      return SL_STATUS_DELETED;
    default:
      break;
  }
  if (image_transfer->ots_state == OTS_STATE_IDLE) {
    bool current_object_requested = false;
    sc = search_image(image_transfer, image_index, &current_object_requested);
    if (sc == SL_STATUS_OK) {
      // Set requested image index
      image_transfer->requested_image_index = image_index;
      // Check if the current object was requested
      if (!current_object_requested) {
        // Other object requested, searching for it.
        image_transfer->ots_ongoing_command = OTS_COMMAND_OBJECT_TYPE;
        esl_lib_log_it_debug(IT_FMT "Searching image index %u" APP_LOG_NL,
                             handle,
                             image_index);
      } else {
        esl_lib_log_it_debug(IT_FMT "Getting type for current image, index %u" APP_LOG_NL,
                             handle,
                             image_index);
        // Requested object is selected, move on with reading the type
        sc = sl_bt_ots_client_read_object_type(&image_transfer->ots_client);
        if (sc == SL_STATUS_OK) {
          // Start timer
          app_timer_start(&image_transfer->timer,
                          TIMEOUT_GATT_MS,
                          gatt_timeout,
                          image_transfer,
                          false);
          image_transfer->ots_ongoing_command = OTS_COMMAND_OBJECT_TYPE;
          image_transfer->ots_state = OTS_STATE_OBJECT_TYPE;
          set_state(image_transfer,
                    ESL_LIB_IMAGE_TRANSFER_STATE_BUSY,
                    SL_STATUS_OK,
                    NULL);
          esl_lib_log_it_debug(IT_FMT "Get type started for current image, index %u" APP_LOG_NL,
                               handle,
                               image_index);
        }
      }
    }
  } else {
    sc = SL_STATUS_INVALID_STATE;
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_it_error(IT_FMT "Get image type for image index %u failed, sc = 0x%04x" APP_LOG_NL,
                         handle,
                         image_index,
                         sc);
  }

  return sc;
}

sl_status_t esl_lib_image_transfer_start(esl_lib_image_transfer_handle_t handle,
                                         uint8_t                         image_index,
                                         size_t                          image_offset,
                                         size_t                          image_size,
                                         uint8_t                         *allocated_image_data)
{
  sl_status_t sc;
  image_transfer_t *image_transfer;

  esl_lib_log_it_info(IT_FMT "Image transfer for image index %u" APP_LOG_NL,
                      handle,
                      image_index);

  // Check parameters
  if (handle == ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  if (image_size == 0) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  image_transfer = find_image_transfer_by_handle(handle);
  if (image_transfer == NULL) {
    return SL_STATUS_NOT_FOUND;
  }

  // Check state
  switch (image_transfer->transfer_state) {
    case ESL_LIB_IMAGE_TRANSFER_STATE_BUSY:
      return SL_STATUS_BUSY;
    case ESL_LIB_IMAGE_TRANSFER_STATE_INIT_IN_PROGRESS:
    case ESL_LIB_IMAGE_TRANSFER_STATE_NOT_INITIALIZED:
      return SL_STATUS_NOT_INITIALIZED;
    case ESL_LIB_IMAGE_TRANSFER_REMOVED:
      return SL_STATUS_DELETED;
    default:
      break;
  }

  if (image_transfer->ots_state == OTS_STATE_IDLE) {
    bool current_object_selected;
    sc = search_image(image_transfer, image_index, &current_object_selected);
    if (sc == SL_STATUS_OK) {
      // Set requested image index
      image_transfer->requested_image_index = image_index;
      // Allocate space for image data
      image_transfer->ots_write_data = allocated_image_data;
      if (!current_object_selected) {
        // Set parameters to use them later on.
        image_transfer->ots_ongoing_command = OTS_COMMAND_WRITE;
        image_transfer->ots_write_offset    = (uint32_t)image_offset;
        image_transfer->ots_write_size      = (uint32_t)image_size;
        esl_lib_log_it_debug(IT_FMT "Searching image index %u" APP_LOG_NL,
                             handle,
                             image_index);
      } else {
        esl_lib_log_it_debug(IT_FMT "Starting Image Transfer for current image, index %u" APP_LOG_NL,
                             handle,
                             image_index);
        // Current object is selected, move on with writing the object.
        sc = sl_bt_ots_client_oacp_write(&image_transfer->ots_client,
                                         (uint32_t)image_offset,
                                         (uint32_t)image_size,
                                         WRITE_MODE,
                                         L2CAP_CHANNEL_SDU,
                                         L2CAP_CHANNEL_PDU);
        if (sc == SL_STATUS_OK) {
          // Start timer
          app_timer_start(&image_transfer->timer,
                          TIMEOUT_TRANSFER_MS,
                          transfer_timeout,
                          image_transfer,
                          false);
          image_transfer->ots_ongoing_command = OTS_COMMAND_WRITE;
          image_transfer->ots_state = OTS_STATE_WRITE;
          set_state(image_transfer,
                    ESL_LIB_IMAGE_TRANSFER_STATE_BUSY,
                    SL_STATUS_OK,
                    NULL);
          esl_lib_log_it_debug(IT_FMT "Image transfer started for current image, index %u" APP_LOG_NL,
                               handle,
                               image_index);
        }
      }
    }
  } else {
    sc = SL_STATUS_INVALID_STATE;
  }

  if (sc != SL_STATUS_OK) {
    esl_lib_log_it_error(IT_FMT "Write image index %u failed, sc = 0x%04x" APP_LOG_NL,
                         handle,
                         image_index,
                         sc);
  }

  return sc;
}

sl_status_t esl_lib_image_transfer_abort(esl_lib_image_transfer_handle_t handle)
{
  sl_status_t sc;
  image_transfer_t *image_transfer;

  esl_lib_log_it_info(IT_FMT "Image transfer abort" APP_LOG_NL,
                      handle);

  if (handle == ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  image_transfer = find_image_transfer_by_handle(handle);
  if (image_transfer == NULL) {
    return SL_STATUS_NOT_FOUND;
  }
  // Check if write is in progress
  if (image_transfer->transfer_state != ESL_LIB_IMAGE_TRANSFER_STATE_BUSY
      || image_transfer->ots_ongoing_command != OTS_COMMAND_WRITE) {
    return SL_STATUS_INVALID_STATE;
  }

  sc = sl_bt_ots_client_abort(&image_transfer->ots_client);

  if (sc != SL_STATUS_OK) {
    esl_lib_log_it_error(IT_FMT "Abort failed, sc = 0x%04x" APP_LOG_NL,
                         handle,
                         sc);
  }

  return sc;
}

sl_status_t esl_lib_image_transfer_get_features(esl_lib_image_transfer_handle_t handle,
                                                esl_lib_ots_features_t          *features)
{
  sl_status_t sc = SL_STATUS_OK;
  image_transfer_t *image_transfer;

  esl_lib_log_it_info(IT_FMT "Image transfer get features" APP_LOG_NL,
                      handle);
  if (handle == ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  image_transfer = find_image_transfer_by_handle(handle);
  if (image_transfer == NULL) {
    return SL_STATUS_NOT_FOUND;
  }
  if (image_transfer->ots_state >= OTS_STATE_IDLE) {
    // Set features of the output
    features->olcp_features = image_transfer->ots_server_features.olcp_features;
    features->oacp_features = image_transfer->ots_server_features.oacp_features;
  } else {
    sc = SL_STATUS_NOT_INITIALIZED;
  }

  if (sc != SL_STATUS_OK) {
    esl_lib_log_it_error(IT_FMT "Get features failed, sc = 0x%04x" APP_LOG_NL,
                         handle,
                         sc);
  }
  return sc;
}

// -----------------------------------------------------------------------------
// Internal functions

void esl_lib_image_transfer_on_bt_event(sl_bt_msg_t *evt)
{
  sli_bt_ots_client_on_bt_event(evt);
  sli_bt_l2cap_transfer_on_bt_event(evt);
}

void esl_lib_image_transfer_step(void)
{
  sli_bt_ots_client_step();
  sli_bt_l2cap_transfer_process_action();
}

// -----------------------------------------------------------------------------
// Private functions

// Utility functions
static sl_status_t search_image(image_transfer_t *image_transfer,
                                uint8_t          image_index,
                                bool             *current_object_requested)
{
  sl_status_t sc = SL_STATUS_OK;
  // Set requested object ID
  image_index_to_object_id(image_index, &image_transfer->ots_requested_object_id);
  esl_lib_log_it_debug(IT_FMT "Searching index %u  = %02X %02X ..." APP_LOG_NL,
                       image_transfer->image_transfer_handle,
                       image_index,
                       image_transfer->ots_requested_object_id.data[0],
                       image_transfer->ots_requested_object_id.data[1]);

  // Check if the current object is requested
  *current_object_requested = compare_ids(&image_transfer->ots_requested_object_id,
                                          &image_transfer->ots_current_object_id);

  if (!*current_object_requested) {
    // Check server capabilities to GOTO
    bool goto_supported = (image_transfer->ots_server_features.olcp_features
                           & SL_BT_OTS_OLCP_FEATURE_GO_TO_OP_CODE_SUPPORTED_MASK);

    if (goto_supported) {
      esl_lib_log_it_debug(IT_FMT "Moving with GOTO to image, index %u" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           image_index);
      sc = sl_bt_ots_client_olcp_go_to(&image_transfer->ots_client,
                                       &image_transfer->ots_requested_object_id);
      if (sc == SL_STATUS_OK) {
        // Start timer
        app_timer_start(&image_transfer->timer,
                        TIMEOUT_GATT_MS,
                        gatt_timeout,
                        image_transfer,
                        false);
        image_transfer->ots_state = OTS_STATE_GO_TO;
        set_state(image_transfer,
                  ESL_LIB_IMAGE_TRANSFER_STATE_BUSY,
                  SL_STATUS_OK,
                  NULL);
      }
    } else {
      esl_lib_log_it_debug(IT_FMT "Moving with FIRST+NEXT to image, index %u" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           image_index);
      sc = sl_bt_ots_client_olcp_first(&image_transfer->ots_client);
      if (sc == SL_STATUS_OK) {
        // Start timer
        app_timer_start(&image_transfer->timer,
                        TIMEOUT_GATT_MS,
                        gatt_timeout,
                        image_transfer,
                        false);
        image_transfer->ots_state = OTS_STATE_FIRST;
        set_state(image_transfer,
                  ESL_LIB_IMAGE_TRANSFER_STATE_BUSY,
                  SL_STATUS_OK,
                  NULL);
      }
    }
  }
  if (sc != SL_STATUS_OK) {
    esl_lib_log_it_error(IT_FMT "Search image index %u failed, sc = 0x%04x" APP_LOG_NL,
                         image_transfer->image_transfer_handle,
                         image_index,
                         sc);
  }

  return sc;
}

static image_transfer_t *find_image_transfer_by_client(sl_bt_ots_client_handle_t client)
{
  image_transfer_t *image_transfer;
  // Check init needs
  SL_SLIST_FOR_EACH_ENTRY(image_transfer_list, image_transfer, image_transfer_t, node) {
    if (client == &image_transfer->ots_client) {
      return image_transfer;
    }
  }
  return ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE;
}

static image_transfer_t *find_image_transfer_by_handle(esl_lib_image_transfer_handle_t handle)
{
  image_transfer_t *image_transfer;
  // Check init needs
  SL_SLIST_FOR_EACH_ENTRY(image_transfer_list, image_transfer, image_transfer_t, node) {
    if ((image_transfer_t *)handle == image_transfer) {
      return image_transfer;
    }
  }
  return ESL_LIB_IMAGE_TRANSFER_INVALID_HANDLE;
}

static void set_state(image_transfer_t           *transfer,
                      esl_image_transfer_state_t state,
                      sl_status_t                result,
                      sl_bt_ots_gattdb_handles_t *gattdb_handles)
{
  if (transfer != NULL) {
    esl_lib_ots_gattdb_handles_t gattdb_out;
    esl_lib_ots_gattdb_handles_t *gattdb_ptr = NULL;

    if (gattdb_handles != NULL) {
      memcpy(gattdb_out, gattdb_handles->characteristics.array, sizeof(gattdb_out));
      gattdb_ptr = &gattdb_out;
    }
    transfer->transfer_state  = state;
    transfer->result = result;
    transfer->cb_status((esl_lib_image_transfer_handle_t)transfer,
                        transfer->connection_handle,
                        state,
                        result,
                        gattdb_ptr);
  }
}

static bool compare_ids(sl_bt_ots_object_id_t *object_id_a,
                        sl_bt_ots_object_id_t *object_id_b)
{
  int value = memcmp(object_id_a->data, object_id_b->data, sizeof(object_id_a->data));
  return (value == 0);
}

static void image_index_to_object_id(uint8_t image_index,
                                     sl_bt_ots_object_id_t *object_id)
{
  uint64_t id = image_index + IMAGE_ID_OFFSET;
  // Clear output
  memset(object_id->data, 0, sizeof(object_id->data));
  // Copy ID
  memcpy(object_id->data, &id, sizeof(object_id->data));
}

static sl_status_t ots_error_to_sl_status(uint16_t att_error,
                                          sl_bt_ots_oacp_response_code_t response)
{
  sl_status_t sc = SL_STATUS_OK;

  if (att_error != ATT_ERR_SUCCESS) {
    switch (att_error & ATT_STATUS_MASK) {
      case ATT_ERR_WRITE_REQUEST_REJECTED:
      case ATT_ERR_WRITE_NOT_PERMITTED:
      case ATT_ERR_CONCURRENCY_LIMIT_EXCEEDED:
      case ATT_ERR_OBJECT_NOT_SELECTED:
      case ATT_ERR_IMPORER_CCCD:
      case ATT_ERR_OBJECT_NAME_ALREADY_EXISTS:
      case ATT_ERR_NOT_SUPPORTED:
      case ATT_ERR_INSUFFICIENT_ENCRYPTION:
      case ATT_ERR_INVALID_ATTRIBUTE_LEN:
        sc = ATT_ERR_OFFSET | att_error;
        break;
      default:
        sc = SL_STATUS_FAIL;
        break;
    }
  } else {
    switch (response) {
      case SL_BT_OTS_OACP_RESPONSE_CODE_SUCCESS:
        sc = SL_STATUS_OK;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_CHANNEL_UNAVAILABLE:
        sc = SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_INSUFFICIENT_RESOURCES:
        sc = SL_STATUS_NO_MORE_RESOURCE;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_INVALID_OBJECT:
        sc = SL_STATUS_NOT_FOUND;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_INVALID_PARAMETER:
        sc = SL_STATUS_INVALID_PARAMETER;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_OP_CODE_NOT_SUPPORTED:
        sc = SL_STATUS_NOT_SUPPORTED;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_PROCEDURE_NOT_PERMITTED:
        sc = SL_STATUS_PERMISSION;
        break;
      case SL_BT_OTS_OACP_RESPONSE_CODE_UNSUPPORTED_TYPE:
        sc = SL_STATUS_INVALID_TYPE;
        break;
      default:
        sc = SL_STATUS_FAIL;
        break;
    }
  }
  return sc;
}

static void start_requested_operation(image_transfer_t *image_transfer)
{
  sl_status_t sc;
  if (image_transfer->ots_ongoing_command == OTS_COMMAND_OBJECT_TYPE) {
    esl_lib_log_it_debug(IT_FMT "Reading object type of current object" APP_LOG_NL,
                         image_transfer->image_transfer_handle);

    sc = sl_bt_ots_client_read_object_type(&image_transfer->ots_client);
    if (sc == SL_STATUS_OK) {
      // Start timer
      app_timer_start(&image_transfer->timer,
                      TIMEOUT_GATT_MS,
                      gatt_timeout,
                      image_transfer,
                      false);
      image_transfer->ots_state = OTS_STATE_OBJECT_TYPE;
    } else {
      esl_lib_log_it_error(IT_FMT "Read object type failed, sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           sc);
      // Could not read type, finish the operation
      operation_finished(image_transfer, sc, false);
    }
  } else if (image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE) {
    esl_lib_log_it_debug(IT_FMT "Write current object" APP_LOG_NL,
                         image_transfer->image_transfer_handle);

    // Current object is selected, move on with writing the object.
    sc = sl_bt_ots_client_oacp_write(&image_transfer->ots_client,
                                     image_transfer->ots_write_offset,
                                     image_transfer->ots_write_size,
                                     WRITE_MODE,
                                     L2CAP_CHANNEL_SDU,
                                     L2CAP_CHANNEL_PDU);
    if (sc == SL_STATUS_OK) {
      // Start timer
      app_timer_start(&image_transfer->timer,
                      TIMEOUT_TRANSFER_MS,
                      transfer_timeout,
                      image_transfer,
                      false);
      image_transfer->ots_state = OTS_STATE_WRITE;
    } else {
      esl_lib_log_it_error(IT_FMT "Write failed, sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           sc);
      // Could not start write, finish the operation
      operation_finished(image_transfer, sc, true);
    }
  }
}

static void remove_transfer(image_transfer_t *image_transfer,
                            sl_status_t sc,
                            bool finish_transfer)
{
  esl_lib_log_it_debug(IT_FMT "Removing transfer" APP_LOG_NL,
                       image_transfer->image_transfer_handle);
  sl_slist_remove(&image_transfer_list, &image_transfer->node);

  if (finish_transfer) {
    esl_lib_log_it_debug(IT_FMT "Finishing transfer" APP_LOG_NL,
                         image_transfer->image_transfer_handle);
    image_transfer->cb_finish((esl_lib_image_transfer_handle_t)image_transfer,
                              image_transfer->connection_handle,
                              sc,
                              image_transfer->requested_image_index);
  }
  set_state(image_transfer, ESL_LIB_IMAGE_TRANSFER_REMOVED, sc, NULL);
  // Remove transfer
  esl_lib_memory_free(image_transfer);
}

static void operation_finished(image_transfer_t *image_transfer,
                               sl_status_t sc,
                               bool finish_transfer)
{
  if (sc ==  SL_STATUS_OK) {
    esl_lib_log_it_debug(IT_FMT "Operation finished, sc = 0x%04x" APP_LOG_NL,
                         image_transfer->image_transfer_handle,
                         sc);
  } else {
    esl_lib_log_it_error(IT_FMT "Operation finished, sc = 0x%04x" APP_LOG_NL,
                         image_transfer->image_transfer_handle,
                         sc);
  }
  if (sc != SL_STATUS_OK && image_transfer->ots_ongoing_command == OTS_COMMAND_OBJECT_TYPE) {
    // Send type back
    image_transfer->cb_type((esl_lib_image_transfer_handle_t)image_transfer,
                            image_transfer->connection_handle,
                            sc,
                            image_transfer->requested_image_index,
                            NULL,
                            0);
  }

  image_transfer->ots_state = OTS_STATE_IDLE;
  image_transfer->ots_ongoing_command = OTS_COMMAND_NONE;
  set_state(image_transfer, ESL_LIB_IMAGE_TRANSFER_STATE_IDLE, sc, NULL);

  // Send error in case of object type requested

  if (finish_transfer) {
    esl_lib_log_it_debug(IT_FMT "Finishing transfer" APP_LOG_NL,
                         image_transfer->image_transfer_handle);
    image_transfer->cb_finish((esl_lib_image_transfer_handle_t)image_transfer,
                              image_transfer->connection_handle,
                              sc,
                              image_transfer->requested_image_index);
  }
}

// -----------------------------------------------------------------------------
// Private OTS callback implementations

static void ots_init(sl_bt_ots_client_handle_t  client,
                     sl_status_t                result,
                     sl_bt_ots_gattdb_handles_t *gattdb_handles)
{
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  sl_status_t sc;

  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    if (image_transfer->ots_state == OTS_STATE_NOT_INITIALIZED
        && result == SL_STATUS_OK) {
      esl_lib_log_it_debug(IT_FMT "OTS init finished, Reading features" APP_LOG_NL,
                           image_transfer->image_transfer_handle);
      sc = sl_bt_ots_client_read_ots_features(&image_transfer->ots_client);
      if (sc == SL_STATUS_OK) {
        // Start timer (with init callback)
        app_timer_start(&image_transfer->timer,
                        TIMEOUT_GATT_MS,
                        init_timeout,
                        image_transfer,
                        false);
        image_transfer->ots_state = OTS_STATE_INITIALIZED;
        set_state(image_transfer,
                  ESL_LIB_IMAGE_TRANSFER_STATE_INIT_IN_PROGRESS,
                  SL_STATUS_OK,
                  gattdb_handles);
      } else {
        esl_lib_log_it_error(IT_FMT "Failed to read features, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             sc);
        remove_transfer(image_transfer, sc, false);
      }
    } else {
      esl_lib_log_it_error(IT_FMT "OTS not initialized, sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           result);
      remove_transfer(image_transfer, result, false);
    }
  }
}

static void ots_features(sl_bt_ots_client_handle_t client,
                         sl_status_t               status,
                         sl_bt_ots_features_t      features)
{
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    if (status == SL_STATUS_OK) {
      // Save features
      memcpy(&image_transfer->ots_server_features,
             &features,
             sizeof(sl_bt_ots_features_t));
      esl_lib_log_it_debug(IT_FMT "OTS features arrived, OACP = 0x%04x , OLCP = 0x%04x , OTS init done" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           image_transfer->ots_server_features.oacp_features,
                           image_transfer->ots_server_features.olcp_features);
      // Set state to idle.
      image_transfer->ots_state = OTS_STATE_IDLE;
      set_state(image_transfer,
                ESL_LIB_IMAGE_TRANSFER_STATE_IDLE,
                SL_STATUS_OK,
                NULL);
    } else {
      esl_lib_log_it_error(IT_FMT "Failed to get OTS features, sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           status);
      // Error during feature read
      remove_transfer(image_transfer, status, false);
    }
  }
}

static void ots_meta_read(sl_bt_ots_client_handle_t                   client,
                          sl_bt_ots_object_id_t                       *object,
                          uint16_t                                    status,
                          sl_bt_ots_object_metadata_read_event_type_t event,
                          sl_bt_ots_object_metadata_read_parameters_t *parameters)
{
  (void)object;
  uint8_t *type = NULL;
  uint8_t len =   0;
  sl_status_t sc;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);

  sc = ots_error_to_sl_status(status, SL_BT_OTS_OACP_RESPONSE_CODE_SUCCESS);

  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    if (event == SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_TYPE
        && image_transfer->ots_state == OTS_STATE_OBJECT_TYPE
        && image_transfer->ots_ongoing_command == OTS_COMMAND_OBJECT_TYPE) {
      if (sc == SL_STATUS_OK) {
        esl_lib_log_it_debug(IT_FMT "OTS object type arrived, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             sc);
        type = parameters->object_type.uuid_data;
        len = SL_BT_OTS_UUID_SIZE_128;
        if (parameters->object_type.uuid_is_sig) {
          len = SL_BT_OTS_UUID_SIZE_16;
        }
      } else {
        esl_lib_log_it_error(IT_FMT "OTS object type read error, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             sc);
      }
      // Type read operation finished, also sends the error if present
      operation_finished(image_transfer,
                         sc,
                         false);
      // Send the type in case of success,
      if (sc == SL_STATUS_OK) {
        image_transfer->cb_type((esl_lib_image_transfer_handle_t)image_transfer,
                                image_transfer->connection_handle,
                                sc,
                                image_transfer->requested_image_index,
                                type,
                                len);
      }
    } else if (event == SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_ID) {
      if (sc == SL_STATUS_OK) {
        esl_lib_log_it_debug(IT_FMT "OTS object ID arrived, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             sc);
        memcpy(image_transfer->ots_current_object_id.data,
               parameters->object_id.data,
               sizeof(image_transfer->ots_current_object_id.data));
        // Check if the requested object was found
        if (memcmp(image_transfer->ots_current_object_id.data,
                   image_transfer->ots_requested_object_id.data,
                   sizeof(image_transfer->ots_requested_object_id.data)) == 0) {
          esl_lib_log_it_debug(IT_FMT "OTS object ID found, starting operation" APP_LOG_NL,
                               image_transfer->image_transfer_handle);

          // Found the requested object, start the operation.
          start_requested_operation(image_transfer);
        } else {
          esl_lib_log_it_debug(IT_FMT "Object ID does not match, move to next" APP_LOG_NL,
                               image_transfer->image_transfer_handle);
          // Not found the requested object, move to the next object
          sc = sl_bt_ots_client_olcp_next(&image_transfer->ots_client);
          if (sc == SL_STATUS_OK) {
            // Start timer
            app_timer_start(&image_transfer->timer,
                            TIMEOUT_GATT_MS,
                            gatt_timeout,
                            image_transfer,
                            false);
            image_transfer->ots_state = OTS_STATE_NEXT;
          } else {
            esl_lib_log_it_error(IT_FMT "Failed to move to next object, sc = 0x%04x" APP_LOG_NL,
                                 image_transfer->image_transfer_handle,
                                 sc);
            // Could not get next, finish transfer if in progress
            operation_finished(image_transfer,
                               sc,
                               image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
          }
        }
      } else {
        esl_lib_log_it_error(IT_FMT "OTS Object ID read error, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             sc);
        // Read Object ID failed - operation finished
        operation_finished(image_transfer,
                           sc,
                           image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
      }
    }
  }
}

static void ots_olcp(sl_bt_ots_client_handle_t      client,
                     sl_bt_ots_object_id_t          *object,
                     sl_bt_ots_olcp_opcode_t        opcode,
                     uint16_t                       status,
                     sl_bt_ots_olcp_response_code_t response,
                     uint32_t                       number_of_objects)
{
  (void)number_of_objects;
  (void)object;
  sl_status_t sc;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    if (status == SL_STATUS_OK && response == SL_BT_OTS_OLCP_RESPONSE_CODE_SUCCESS) {
      if ((opcode == SL_BT_OTS_OLCP_OPCODE_FIRST && image_transfer->ots_state == OTS_STATE_FIRST)
          || (opcode == SL_BT_OTS_OLCP_OPCODE_NEXT && image_transfer->ots_state == OTS_STATE_NEXT)) {
        esl_lib_log_it_debug(IT_FMT "OTS OLCP FIRST/NEXT operation succeeded" APP_LOG_NL,
                             image_transfer->image_transfer_handle);

        sc = sl_bt_ots_client_read_object_id(&image_transfer->ots_client);
        if (sc != SL_STATUS_OK) {
          esl_lib_log_it_error(IT_FMT "OTS Reading object ID failed, sc = 0x%04x" APP_LOG_NL,
                               image_transfer->image_transfer_handle,
                               sc);
          // Read ID failed
          operation_finished(image_transfer,
                             sc,
                             image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
        } else {
          esl_lib_log_it_debug(IT_FMT "OTS Reading object ID started" APP_LOG_NL,
                               image_transfer->image_transfer_handle);
          // Start timer
          app_timer_start(&image_transfer->timer,
                          TIMEOUT_GATT_MS,
                          gatt_timeout,
                          image_transfer,
                          false);
        }
      } else if (opcode == SL_BT_OTS_OLCP_OPCODE_GO_TO && image_transfer->ots_state == OTS_STATE_GO_TO) {
        esl_lib_log_it_debug(IT_FMT "OTS OLCP GOTO operation succeeded. Starting requested operation" APP_LOG_NL,
                             image_transfer->image_transfer_handle);

        // Object selected
        memcpy(&image_transfer->ots_current_object_id,
               &image_transfer->ots_requested_object_id,
               sizeof(sl_bt_ots_object_id_t));
        start_requested_operation(image_transfer);
      }
    } else {
      // Check for ATT errors
      sl_status_t gatt_status = ots_error_to_sl_status(status,
                                                       SL_BT_OTS_OACP_RESPONSE_CODE_SUCCESS);
      if (gatt_status != SL_STATUS_OK) {
        sc = gatt_status;
        esl_lib_log_it_error(IT_FMT "OTS OLCP operation failed due to ATT error 0x%04x, sc = 0x%04x" APP_LOG_NL,
                             image_transfer->image_transfer_handle,
                             response,
                             sc);
      } else {
        // Check if no more items in the list
        if (response == SL_BT_OTS_OLCP_RESPONSE_CODE_SUCCESS) {
          esl_lib_log_it_debug(IT_FMT "OTS OLCP operation succeeded" APP_LOG_NL,
                               image_transfer->image_transfer_handle);
          sc = SL_STATUS_OK;
        } else if (response == SL_BT_OTS_OLCP_RESPONSE_CODE_OUT_OF_BOUNDS
                   || response == SL_BT_OTS_OLCP_RESPONSE_CODE_OBJECT_ID_NOT_FOUND) {
          sc = SL_STATUS_NOT_FOUND;
          esl_lib_log_it_error(IT_FMT "OTS OLCP operation failed: object not found, sc = 0x%04x" APP_LOG_NL,
                               image_transfer->image_transfer_handle,
                               sc);
        } else {
          sc = SL_STATUS_FAIL;
          esl_lib_log_it_error(IT_FMT "OTS OLCP operation failed due unknown error, sc = 0x%04x, response = 0x%04x" APP_LOG_NL,
                               image_transfer->image_transfer_handle,
                               sc,
                               response);
        }
      }
      // OLCP operation failed
      operation_finished(image_transfer,
                         sc,
                         image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
    }
  }
}

static void ots_oacp(sl_bt_ots_client_handle_t      client,
                     sl_bt_ots_object_id_t          *object,
                     sl_bt_ots_oacp_opcode_t        opcode,
                     uint16_t                       status,
                     sl_bt_ots_oacp_response_code_t response,
                     sl_bt_ots_oacp_response_data_t *data)
{
  (void)data;
  (void)object;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    sl_status_t sc = ots_error_to_sl_status(status, response);
    if (opcode == SL_BT_OTS_OACP_OPCODE_WRITE && sc != SL_STATUS_OK) {
      esl_lib_log_it_error(IT_FMT "OTS OACP Write operation failed, status = 0x%04x, response = 0x%04x, sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           status,
                           response,
                           sc);
      // OACP operation failed
      operation_finished(image_transfer,
                         sc,
                         true);
    }
  }
}

static void ots_data_transmit(sl_bt_ots_client_handle_t client,
                              sl_bt_ots_object_id_t     *object,
                              uint32_t                  current_offset,
                              uint32_t                  size,
                              uint8_t                   **data,
                              uint32_t                  *data_size)
{
  (void)object;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    *data_size = size;
    *data = &(image_transfer->ots_write_data[current_offset]);
  }
}

static void ots_finished(sl_bt_ots_client_handle_t   client,
                         sl_bt_ots_object_id_t       *object,
                         sl_bt_ots_transfer_result_t result)
{
  (void)object;
  sl_status_t sc = SL_STATUS_OK;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    // Stop timer
    app_timer_stop(&image_transfer->timer);
    if (result != SL_BT_OTS_TRANSFER_FINISHED_RESPONSE_CODE_SUCCESS) {
      switch (result) {
        case SL_BT_OTS_TRANSFER_FINISHED_RESPONSE_CODE_CHANNEL_ERROR:
          sc = SL_STATUS_BT_CTRL_CONNECTION_REJECTED_DUE_TO_NO_SUITABLE_CHANNEL_FOUND;
          break;
        case SL_BT_OTS_TRANSFER_FINISHED_RESPONSE_CODE_ABORTED:
          sc = SL_STATUS_ABORT;
          break;
        case SL_BT_OTS_TRANSFER_FINISHED_RESPONSE_CODE_CONNECTION_LOST:
          sc = SL_STATUS_BT_L2CAP_REMOTE_DISCONNECTED;
          break;
        case SL_BT_OTS_TRANSFER_FINISHED_RESPONSE_CODE_TIMEOUT:
          sc = SL_STATUS_TIMEOUT;
          break;
        default:
          sc = SL_STATUS_FAIL;
          break;
      }
      esl_lib_log_it_error(IT_FMT "OTS transfer failed, result = 0x%04x , sc = 0x%04x" APP_LOG_NL,
                           image_transfer->image_transfer_handle,
                           result,
                           sc);
    } else {
      esl_lib_log_it_debug(IT_FMT "OTS transfer succeeded" APP_LOG_NL,
                           image_transfer->image_transfer_handle);
    }

    // OACP operation completed
    operation_finished(image_transfer,
                       sc,
                       true);
  }
}

static void ots_disconnect(sl_bt_ots_client_handle_t client)
{
  sl_status_t sc = SL_STATUS_OK;
  image_transfer_t *image_transfer = find_image_transfer_by_client(client);
  if (image_transfer != NULL) {
    // Stop timer on disconnect
    app_timer_stop(&image_transfer->timer);
    esl_lib_log_it_debug(IT_FMT "OTS disconnected" APP_LOG_NL,
                         image_transfer->image_transfer_handle);
    sc = SL_STATUS_BT_CTRL_REMOTE_USER_TERMINATED;
    remove_transfer(image_transfer,
                    sc,
                    image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
  }
}

static void init_timeout(app_timer_t *timer,
                         void        *data)
{
  image_transfer_t *image_transfer = (image_transfer_t *)data;
  esl_lib_log_it_error(IT_FMT "OTS init timeout" APP_LOG_NL,
                       image_transfer->image_transfer_handle);
  // Remove transfer that could not be initialized
  remove_transfer(image_transfer, SL_STATUS_TIMEOUT, false);
}

static void gatt_timeout(app_timer_t *timer,
                         void        *data)
{
  image_transfer_t *image_transfer = (image_transfer_t *)data;
  esl_lib_log_it_error(IT_FMT "OTS GATT timeout" APP_LOG_NL,
                       image_transfer->image_transfer_handle);
  // Send operation finished with error event
  operation_finished(image_transfer,
                     SL_STATUS_TIMEOUT,
                     image_transfer->ots_ongoing_command == OTS_COMMAND_WRITE);
}

static void transfer_timeout(app_timer_t *timer,
                             void        *data)
{
  image_transfer_t *image_transfer = (image_transfer_t *)data;
  esl_lib_log_it_error(IT_FMT "OTS transfer timeout" APP_LOG_NL,
                       image_transfer->image_transfer_handle);
  operation_finished(image_transfer, SL_STATUS_TIMEOUT, true);
}
