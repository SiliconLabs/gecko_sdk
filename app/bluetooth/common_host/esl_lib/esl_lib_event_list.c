/***************************************************************************//**
 * @file
 * @brief ESL Event List manipulation.
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
#include <string.h>
#include "sl_slist.h"
#include "esl_lib_event_list.h"
#include "esl_lib_ap_control.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

#define ESL_LIB_EVENT_HEADER_SIZE (sizeof(esl_lib_evt_t) - sizeof(esl_lib_evt_data_t))

// -----------------------------------------------------------------------------
// Private variables

// Event list
static sl_slist_node_t    *evt_list;
static uint32_t           evt_counter = 0;

// -----------------------------------------------------------------------------
// Public function definitions

sl_status_t esl_lib_event_list_remove_first(void)
{
  esl_lib_evt_t *first;

  // Save first item
  first = esl_lib_event_list_get_first();

  if (first == NULL) {
    return SL_STATUS_EMPTY;
  }

  // Remove first item
  sl_slist_remove(&evt_list, &first->node);

  // Free allocated event memory
  esl_lib_memory_free(first);

  return SL_STATUS_OK;
}

esl_lib_evt_t *esl_lib_event_list_get_first(void)
{
  esl_lib_evt_t *first;

  // First element is the head
  first = (esl_lib_evt_t *) evt_list;

  return first;
}

sl_status_t esl_lib_event_list_push_back(esl_lib_evt_t *evt)
{
  if (evt == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  evt->id = evt_counter++;

  sl_slist_push_back(&evt_list, &evt->node);

  return SL_STATUS_OK;
}

sl_status_t esl_lib_event_list_allocate(esl_lib_evt_type_t event_type,
                                        uint32_t           additional_size,
                                        esl_lib_evt_t      **ptr_out)
{
  sl_status_t sc = SL_STATUS_OK;

  size_t size = ESL_LIB_EVENT_HEADER_SIZE;

  switch ((uint8_t)event_type) {
    case ESL_LIB_EVT_SYSTEM_BOOT:
      size += sizeof(esl_lib_evt_system_boot_t);
      break;
    case ESL_LIB_EVT_SCAN_STATUS:
      size += sizeof(esl_lib_evt_scan_status_t);
      break;
    case ESL_LIB_EVT_TAG_FOUND:
      size += sizeof(esl_lib_evt_tag_found_t);
      break;
    case ESL_LIB_EVT_TAG_INFO:
      size += sizeof(esl_lib_evt_tag_info_t);
      size += additional_size;
      break;
    case ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE:
      size += sizeof(esl_lib_evt_configure_tag_response_t);
      break;
    case ESL_LIB_EVT_CONTROL_POINT_RESPONSE:
      size += sizeof(esl_lib_evt_control_point_response_t);
      size += additional_size;
      break;
    case ESL_LIB_EVT_CONTROL_POINT_NOTIFICATION:
      size += sizeof(esl_lib_evt_control_point_notification_t);
      size += additional_size;
      break;
    case ESL_LIB_EVT_CONNECTION_CLOSED:
      size += sizeof(esl_lib_evt_connection_closed_t);
      break;
    case ESL_LIB_EVT_CONNECTION_OPENED:
      size += sizeof(esl_lib_evt_connection_opened_t);
      break;
    case ESL_LIB_EVT_BONDING_DATA:
      size += sizeof(esl_lib_evt_bonding_data_t);
      break;
    case ESL_LIB_EVT_BONDING_FINISHED:
      size += sizeof(esl_lib_evt_bonding_finished_t);
      break;
    case ESL_LIB_EVT_PAWR_STATUS:
      size += sizeof(esl_lib_evt_pawr_status_t);
      break;
    case ESL_LIB_EVT_PAWR_RESPONSE:
      size += sizeof(esl_lib_evt_pawr_response_t);
      size += additional_size;
      break;
    case ESL_LIB_EVT_PAWR_DATA_REQUEST:
      size += sizeof(esl_lib_evt_pawr_data_request_t);
      break;
    case ESL_LIB_EVT_SHUTDOWN_READY:
      break;
    case ESL_LIB_EVT_ERROR:
      size += sizeof(esl_lib_evt_error_t);
      break;
    case ESL_LIB_EVT_IMAGE_TRANSFER_FINISHED:
      size += sizeof(esl_lib_evt_image_transfer_finished_t);
      break;
    case ESL_LIB_EVT_IMAGE_TYPE:
      size += sizeof(esl_lib_evt_image_type_t);
      size += additional_size;
      break;
    case ESL_LIB_EVT_GENERAL:
      size += sizeof(esl_lib_long_array_t);
      size += additional_size;
      break;
    default:
      return SL_STATUS_INVALID_PARAMETER;
  }

  void *ptr = esl_lib_memory_allocate(size);

  if (ptr == NULL) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  memset(ptr, 0, size);

  *ptr_out = (esl_lib_evt_t *)ptr;

  return sc;
}

sl_status_t esl_lib_event_push_error(esl_lib_status_t      lib_status,
                                     esl_lib_node_id_t     *node_id,
                                     sl_status_t           status,
                                     esl_lib_status_data_t data)
{
  sl_status_t        sc;
  esl_lib_evt_t      *evt;
  esl_lib_evt_type_t type = ESL_LIB_EVT_ERROR;

  sc = esl_lib_event_list_allocate(type, 0, &evt);
  if (sc == SL_STATUS_OK) {
    evt->evt_code                  = type;
    evt->data.evt_error.lib_status = lib_status;
    evt->data.evt_error.sl_status  = status;
    evt->data.evt_error.data       = data;
    if (node_id != NULL) {
      // Copy ID
      memcpy(&evt->data.evt_error.node_id,
             node_id,
             sizeof(esl_lib_node_id_t));
    } else {
      // Clear ID and set None type
      memset(&evt->data.evt_error.node_id, 0, sizeof(esl_lib_node_id_t));
      evt->data.evt_error.node_id.type = ESL_LIB_NODE_ID_TYPE_NONE;
    }
    sc = esl_lib_event_list_push_back(evt);
  }
  return sc;
}
