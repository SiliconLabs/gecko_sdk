/***************************************************************************//**
 * @file
 * @brief ESL Access Point Storage file
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

#include "sl_slist.h"
#include "esl_lib_storage.h"
#include "esl_lib.h"
#include "esl_lib_log.h"
#include "esl_lib_memory.h"

// -----------------------------------------------------------------------------
// Definitions

typedef struct {
  size_t          size;
  sl_slist_node_t *list_head;
} esl_lib_storage_t;

typedef struct {
  sl_slist_node_t node;
  uint8array      data;
} esl_lib_segment_t;

// -----------------------------------------------------------------------------
// Public functions

sl_status_t esl_lib_storage_create(esl_lib_storage_handle_t *handle_out)
{
  sl_status_t sc = SL_STATUS_OK;
  // Allocate data for storage
  esl_lib_storage_t *storage_ptr = esl_lib_memory_allocate(sizeof(esl_lib_storage_t));
  if (storage_ptr != NULL) {
    // Initialize state
    storage_ptr->list_head = NULL;
    storage_ptr->size      = 0;
    *handle_out = (esl_lib_storage_handle_t *)storage_ptr;
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t esl_lib_storage_append(esl_lib_storage_handle_t handle,
                                   uint8array               *data)
{
  sl_status_t sc = SL_STATUS_OK;

  if (handle == ESL_LIB_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  esl_lib_storage_t *storage_ptr = (esl_lib_storage_t *)handle;

  size_t size = sizeof(esl_lib_segment_t) + data->len;

  // Allocate data fot the fragment
  esl_lib_segment_t *segment_ptr = esl_lib_memory_allocate(size);
  if (segment_ptr != NULL) {
    // Set length
    segment_ptr->data.len = data->len;
    // Copy data
    memcpy(segment_ptr->data.data, data->data, data->len);
    // Add to the list
    sl_slist_push_back(&storage_ptr->list_head, &segment_ptr->node);
    // Increment length
    storage_ptr->size += segment_ptr->data.len;
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t esl_lib_storage_get_size(esl_lib_storage_handle_t handle,
                                     size_t                   *size_out)
{
  sl_status_t sc = SL_STATUS_OK;
  if (handle == ESL_LIB_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  esl_lib_storage_t *storage_ptr = (esl_lib_storage_t *)handle;

  // Set output
  *size_out = storage_ptr->size;

  return sc;
}

sl_status_t esl_lib_storage_copy(esl_lib_storage_handle_t handle,
                                 uint8_t                  *data_out)
{
  sl_status_t sc = SL_STATUS_OK;

  if (handle == ESL_LIB_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }
  if (data_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  esl_lib_storage_t *storage_ptr = (esl_lib_storage_t *)handle;
  esl_lib_segment_t *segment;
  size_t data_index = 0;

  SL_SLIST_FOR_EACH_ENTRY(storage_ptr->list_head, segment, esl_lib_segment_t, node) {
    memcpy(&data_out[data_index], segment->data.data, segment->data.len);
    data_index += segment->data.len;
  }

  return sc;
}

sl_status_t esl_lib_storage_clean(esl_lib_storage_handle_t handle)
{
  sl_status_t sc = SL_STATUS_OK;

  if (handle == ESL_LIB_INVALID_HANDLE) {
    return SL_STATUS_INVALID_HANDLE;
  }

  esl_lib_storage_t *storage_ptr = (esl_lib_storage_t *)handle;
  esl_lib_segment_t *segment;

  // Clean the list
  while ((segment = (esl_lib_segment_t *)sl_slist_pop(&storage_ptr->list_head)) != NULL) {
    sl_slist_remove(&storage_ptr->list_head, &segment->node);
    esl_lib_memory_free(segment);
  }

  storage_ptr->size = 0;

  return sc;
}

sl_status_t esl_lib_storage_delete(esl_lib_storage_handle_t *handle)
{
  sl_status_t sc;

  // Clean storage
  sc = esl_lib_storage_clean(*handle);

  if (sc == SL_STATUS_OK) {
    // Free up memory
    esl_lib_memory_free(*handle);
  }

  return sc;
}
