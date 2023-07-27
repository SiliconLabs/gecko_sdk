/***************************************************************************//**
 * @file
 * @brief Core ESL Tag Object Transfer Service logic.
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
 ******************************************************************************/
#include <stdbool.h>
#include "em_common.h"
#include "sl_bluetooth.h"
#include "esl_tag_log.h"
#include "esl_tag_core.h"
#include "esl_tag_image.h"
#include "sl_bt_ots_server.h"
#include "esl_tag_image_core.h"
#include "esl_tag_ots_server.h"
#include "sl_bt_ots_server_instances.h"

#define OBJECT_ID_NOT_FOUND -1

#define IMAGE_NAME_PREFIX   "Image-"

#define IMAGE_NAME_POSTFIX  "***"

#define IMAGE_NAME_FULL_STR IMAGE_NAME_PREFIX IMAGE_NAME_POSTFIX

const sl_bt_ots_object_type_t esl_image_type_1b = {
  false,
  (uint8_t[SL_BT_OTS_UUID_SIZE_128]){ 0xe5, 0x10, 0x00, 0x01, 0x4b, 0x1d, 0xb1, 0x9b, 0x00, 0xb1, 0xe5, 0x01, 0x8b, 0xad, 0xf0, 0x0d }
};

const sl_bt_ots_object_type_t esl_image_type_2b = {
  false,
  (uint8_t[SL_BT_OTS_UUID_SIZE_128]){ 0xe5, 0x10, 0x00, 0x06, 0x4b, 0x1d, 0xb1, 0x9b, 0x00, 0xb1, 0xe5, 0x01, 0x8b, 0xad, 0xf0, 0x0d }
};

// Image default name type
typedef union {
  char data[sizeof(IMAGE_NAME_FULL_STR)];
  struct {
    const char prefix[sizeof(IMAGE_NAME_PREFIX) - 1]; // exclude terminating zero!
    char       postfix[sizeof(IMAGE_NAME_POSTFIX)];
  };
} esl_ots_image_name_t;

// ESL Custom directory Listing Object
typedef struct {
  sl_bt_ots_object_id_t            id;          // Object ID
  const sl_bt_ots_object_type_t    *type;       // ESL Image object type
  sl_bt_ots_object_size_t          size;        // current and allocated size
  sl_bt_ots_object_properties_t    properties;  // ESL Image object properties
} esl_image_ots_object_t;

// Image default name - postfix to be overwritten on-the-fly according to object
esl_ots_image_name_t object_name = { { IMAGE_NAME_FULL_STR } };

// Array of objects
static esl_image_ots_object_t object_array[ESL_TAG_OTS_OBJECT_COUNT] = { 0 };

// Index for object registration
static uint8_t object_array_register_index = 0;

static int find_object_index_by_id(sl_bt_ots_object_id_t *object)
{
  const uint8_t image_count = esl_image_get_count();
  for (uint8_t i = 0; i < image_count; i++) {
    if (memcmp(object_array[i].id.data, object->data, sizeof(object->data)) == 0) {
      return i;
    }
  }
  return OBJECT_ID_NOT_FOUND;
}

// Fast and simple uint8_t to 10-base string converter
static char u8toa(uint8_t n, char *const buf)
{
  if (buf == NULL ) {
    return 0;
  }

  size_t length = n > 99 ? sizeof("123") : n > 9 ? sizeof("12") : sizeof("1");
  char *p = buf + --length;
  *p-- = 0;                         // Terminate the buffer

  do {
    uint8_t t = n;                  // save current value
    n /= 10;
    *p-- = (t - (n * 10)) + 0x30;   // Convert diff. to ASCII
  } while (n != 0 && p >= buf);

  return (char)length;              // The character count, w/o terminating nul!
}

static sl_bt_ots_object_metadata_read_response_code_t ots_meta_read(sl_bt_ots_server_handle_t                   server,
                                                                    uint16_t                                    client,
                                                                    sl_bt_ots_object_id_t                       *object,
                                                                    sl_bt_ots_object_metadata_read_event_type_t event,
                                                                    sl_bt_ots_object_metadata_read_parameters_t *parameters)
{
  (void)server;
  (void)client;

  sl_bt_ots_object_metadata_read_response_code_t response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_NOT_SUPPORTED;

  // Find the object index
  int object_index = find_object_index_by_id(object);
  if (object_index > OBJECT_ID_NOT_FOUND) {
    esl_image_ots_object_t *object_ptr = &object_array[object_index];
    switch (event) {
      case SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_NAME:
        // (Re)generate the name just-in-time
        parameters->object_name.length = sizeof(object_name.prefix) + u8toa(object_index, object_name.postfix);
        parameters->object_name.name = object_name.data;
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ots_meta_read: Name: %.*s",
                      parameters->object_name.length,
                      parameters->object_name.name);
        response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_SUCCESS;
        break;
      case SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_TYPE:
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ots_meta_read: Type: ");
        sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_OTS | ESL_LOG_FLAG_APPEND,
                              ESL_LOG_LEVEL_INFO,
                              object_ptr->type->uuid_data,
                              ((object_ptr->type->uuid_is_sig) ? SL_BT_OTS_UUID_SIZE_16 : SL_BT_OTS_UUID_SIZE_128));
        parameters->object_type.uuid_is_sig = object_ptr->type->uuid_is_sig;
        parameters->object_type.uuid_data = object_ptr->type->uuid_data;
        response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_SUCCESS;
        break;
      case SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_SIZE:
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ots_meta_read: Size - Current: %lu , Allocated: %lu",
                      object_ptr->size.current_size,
                      object_ptr->size.allocated_size);
        parameters->object_size.allocated_size = object_ptr->size.allocated_size;
        parameters->object_size.current_size = object_ptr->size.current_size;
        response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_SUCCESS;
        break;
      case SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_PROPERTIES:
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ots_meta_read: Properties: %02lx",
                      object_ptr->properties);
        parameters->object_properties = object_ptr->properties;
        response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_SUCCESS;
        break;
      case SL_BT_OTS_OBJECT_METADATA_READ_OBJECT_ID:
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ots_meta_read: ID: ");
        sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_OTS | ESL_LOG_FLAG_APPEND,
                              ESL_LOG_LEVEL_INFO,
                              object_ptr->id.data,
                              sizeof(object_ptr->id.data));
        memcpy(parameters->object_id.data,
               object_ptr->id.data,
               sizeof(object_ptr->id.data));
        response = SL_BT_OTS_OBJECT_METADATA_READ_RESPONSE_CODE_SUCCESS;
        break;
      default:
        break;
    }
  }
  return response;
}

static sl_bt_ots_olcp_response_code_t ots_olcp(sl_bt_ots_server_handle_t   server,
                                               uint16_t                    client,
                                               sl_bt_ots_object_id_t       *object,
                                               sl_bt_ots_olcp_event_t      event,
                                               sl_bt_ots_olcp_parameters_t *parameters,
                                               uint32_t                    *number_of_objects)
{
  sl_status_t sc = SL_STATUS_IN_PROGRESS;
  int         object_index = OBJECT_ID_NOT_FOUND;
  uint8_t     image_count  = esl_image_get_count();
  // Set the operation failed response as default
  sl_bt_ots_olcp_response_code_t response = SL_BT_OTS_OLCP_RESPONSE_CODE_OPEATION_FAILED;

  (void)number_of_objects;
  sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                ESL_LOG_LEVEL_INFO,
                "ots_olcp: OLCP OpCode: 0x%02x",
                event);

  switch (event) {
    case SL_BT_OTS_OLCP_OPCODE_FIRST:
      object_index = 0;
      break;

    case SL_BT_OTS_OLCP_OPCODE_LAST:
      if (image_count-- > 0) {
        object_index = image_count;
      }
      break;

    case SL_BT_OTS_OLCP_OPCODE_NEXT:
      object_index = find_object_index_by_id(object);
      if (object_index > OBJECT_ID_NOT_FOUND) {
        const uint8_t max_image_index = image_count - 1;
        if (!(object_index++ < max_image_index)) {
          // Reset index on error
          object_index = OBJECT_ID_NOT_FOUND;
          response = SL_BT_OTS_OLCP_RESPONSE_CODE_OUT_OF_BOUNDS;
          break;
        }
      }
      break;

    case SL_BT_OTS_OLCP_OPCODE_PREVIOUS:
      object_index = find_object_index_by_id(object);
      if (object_index > OBJECT_ID_NOT_FOUND) {
        if (object_index-- == 0) {
          object_index = OBJECT_ID_NOT_FOUND;
          response = SL_BT_OTS_OLCP_RESPONSE_CODE_OUT_OF_BOUNDS;
        }
      }
      break;

    case SL_BT_OTS_OLCP_OPCODE_GO_TO:
      object_index = find_object_index_by_id(&parameters->go_to.id);
      if (object_index == OBJECT_ID_NOT_FOUND) {
        response = SL_BT_OTS_OLCP_RESPONSE_CODE_OBJECT_ID_NOT_FOUND;
      }
      break;

    default:
      // Replace the default error response in case of unsupported opcodes
      response = SL_BT_OTS_OLCP_RESPONSE_CODE_OP_CODE_NOT_SUPPORTED;
      break;
  }

  if (object_index != OBJECT_ID_NOT_FOUND) {
    sc = sl_bt_ots_server_set_current_object(server,
                                             client,
                                             &object_array[object_index].id,
                                             &object_array[object_index].properties,
                                             &object_array[object_index].size);
    if (sc == SL_STATUS_OK) {
      sc = esl_image_select_object(&object_array[object_index].id,
                                   sizeof(object_array[object_index].id));
      if (sc != SL_STATUS_OK) {
        // Invalidate the previous OTS object selection, ignore (override) result.
        (void)sl_bt_ots_server_set_current_object(server, client, NULL, NULL, NULL);
        response = SL_BT_OTS_OLCP_RESPONSE_CODE_OPEATION_FAILED;
      } else {
        response = SL_BT_OTS_OLCP_RESPONSE_CODE_SUCCESS;
      }
    }
  }
  return response;
}

static sl_bt_ots_oacp_response_code_t ots_oacp(sl_bt_ots_server_handle_t      server,
                                               uint16_t                       client,
                                               sl_bt_ots_object_id_t          *object,
                                               sl_bt_ots_oacp_event_t         event,
                                               sl_bt_ots_oacp_parameters_t    *parameters,
                                               sl_bt_ots_oacp_response_data_t *response_data,
                                               uint16_t                       *max_sdu,
                                               uint16_t                       *max_pdu)
{
  (void)client;
  (void)server;
  (void)response_data;
  (void)parameters;
  sl_bt_ots_oacp_response_code_t response = SL_BT_OTS_OACP_RESPONSE_CODE_OP_CODE_NOT_SUPPORTED;

  sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                ESL_LOG_LEVEL_INFO,
                "ots_oacp: OACP OpCode: 0x%02x",
                event);

  // Find the object index
  int object_index = find_object_index_by_id(object);
  if (object_index > OBJECT_ID_NOT_FOUND) {
    // OACP events can be handled here
    // Transfer can be implemented.

    switch (event) {
      case SL_BT_OTS_OACP_OPCODE_WRITE:
        response = SL_BT_OTS_OACP_RESPONSE_CODE_SUCCESS;
        *max_pdu = ESL_TAG_OTS_TRANSFER_MAX_PDU_SIZE;
        *max_sdu = ESL_TAG_OTS_TRANSFER_MAX_SDU_SIZE;
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "Write object - Client %d.  Object ID: ",
                      client);
        sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_OTS | ESL_LOG_FLAG_APPEND,
                              ESL_LOG_LEVEL_INFO,
                              object->data,
                              sizeof(object->data));
        break;
      default:
        break;
    }
  }

  return response;
}

static sl_bt_ots_l2cap_credit_t ots_data(sl_bt_ots_server_handle_t server,
                                         uint16_t                  client,
                                         sl_bt_ots_object_id_t     *object,
                                         int32_t                   current_offset,
                                         void                      *data,
                                         int32_t                   size)
{
  sl_bt_ots_object_id_t current_object;
  sl_status_t sc = sl_bt_ots_server_get_current_object(server, client, &current_object);
  sl_bt_ots_l2cap_credit_t credit = 0;

  sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                ESL_LOG_LEVEL_DEBUG,
                "Data chunk received from client %u. Offset: %ld, Size %ld, Object ID: ",
                client,
                current_offset,
                size);
  sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_OTS | ESL_LOG_FLAG_APPEND,
                        ESL_LOG_LEVEL_DEBUG,
                        object->data,
                        sizeof(object->data));

  if (sc == SL_STATUS_OK
      && memcmp(object, &current_object, SL_BT_OTS_OBJECT_ID_SIZE) == 0) {
    sc = esl_image_chunk_received(data, current_offset, size);
    if (sc == SL_STATUS_OK) {
      credit++;
    } else {
      if (sc != SL_STATUS_FULL) {
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_ERROR,
                      "ESL Image error: 0x%04lX",
                      sc);
      } else {
        sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                      ESL_LOG_LEVEL_INFO,
                      "ESL Image: slot full");
      }
      sl_bt_ots_server_abort(server, client);
    }
  }

  return credit;
}

static void ots_data_finished(sl_bt_ots_server_handle_t   server,
                              uint16_t                    client,
                              sl_bt_ots_object_id_t       *object,
                              sl_bt_ots_transfer_result_t result)
{
  (void)client;
  (void)server;
  (void)result;
  (void)object;

  sl_bt_esl_log(ESL_LOG_COMPONENT_OTS,
                ESL_LOG_LEVEL_INFO,
                "Transfer finished with Client %d, result: %x Object ID: ",
                client,
                result);
  sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_OTS | ESL_LOG_FLAG_APPEND,
                        ESL_LOG_LEVEL_INFO,
                        object->data,
                        sizeof(object->data));

  esl_image_receive_finished();
}

// OTS Object Server Callbacks
static sl_bt_ots_server_callbacks_t ots_callbacks = {
  NULL,           // No callback to handle connection of a client
  NULL,           // No callback to handle disconnection of a client
  NULL,           // No callback to handle client subscription status changes
  NULL,           // No callback to handle metadata writes (unsupported)
  ots_meta_read,  // Callback to handle metadata read operations
  NULL,           // No callback to handle Object List Filter write operations
  NULL,           // No callback to handle Object List Filter read operations
  ots_olcp,          // Callback to handle OLCP List management events
  ots_oacp,          // Callback to handle OACP Data management events
  ots_data,          // Callback to handle incoming data
  ots_data_finished, // Callback to handle the end of a data transfer
  NULL               // No callback to handle outgoing data
};

void esl_tag_ots_server_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled
  // Handle stack events
  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      // Initialize OTS Server
      sc = sl_bt_ots_server_init(&sl_bt_ots_server_instance_esl_image,
                                 &sl_bt_ots_server_gatt_esl_image,
                                 &ots_callbacks);
      sl_bt_esl_assert(sc == SL_STATUS_OK);
      break;
    default:
      break;
  }
}

sl_status_t esl_tag_ots_add_object(const sl_bt_ots_object_type_t* type,
                                   uint32_t allocated_size,
                                   uint32_t properties)
{
  sl_status_t status = SL_STATUS_NO_MORE_RESOURCE;

  // Check for in-bound limit.
  if (object_array_register_index < (sizeof(object_array) / sizeof(object_array[0]))) {
    // Set Object ID according to ESLS spec.
    *(uint16_t*)&object_array[object_array_register_index].id.data = ESL_IMAGE_OBJECT_BASE | object_array_register_index;

    // Set initial size
    object_array[object_array_register_index].size.allocated_size = allocated_size;
    object_array[object_array_register_index].size.current_size   = 0;
    // Set properties
    object_array[object_array_register_index].properties = properties;
    // Set object type
    object_array[object_array_register_index].type = type;
    // Prepare for next object
    object_array_register_index++;
    status = SL_STATUS_OK;
  }

  return status;
}
