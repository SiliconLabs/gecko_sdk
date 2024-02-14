/***************************************************************************/ /**
 * @file
 * @brief CPC API implementation.
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

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

#include "sl_status.h"

#include "sl_cpc_config.h"
#include "sli_cpc_system_common.h"
#include "sli_cpc.h"
#include "sli_cpc_hdlc.h"
#include "sli_mem_pool.h"
#include "sli_cpc_debug.h"
#include "sli_cpc_drv.h"
#include "sl_assert.h"
#include "sl_common.h"
#include "sl_slist.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
// needed for definition of sli_cpc_system_command_handle_t;
#include "sli_cpc_system_primary.h"
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static sli_mem_pool_handle_t mempool_buffer_handle;
SLI_MEM_POOL_DECLARE_BUFFER_WITH_TYPE(mempool_buffer_handle,
                                      sl_cpc_buffer_handle_t,
                                      SLI_CPC_BUFFER_HANDLE_MAX_COUNT);

static sl_cpc_mem_pool_handle_t cpc_mempool_buffer_handle =
{ .pool_handle = &mempool_buffer_handle,
  .used_block_cnt = 0 };

static sli_mem_pool_handle_t mempool_hdlc_header;
SLI_MEM_POOL_DECLARE_BUFFER(mempool_hdlc_header,
                            SLI_CPC_HDLC_HEADER_RAW_SIZE,
                            SLI_CPC_HDLC_HEADER_MAX_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_hdlc_header =
{ .pool_handle = &mempool_hdlc_header,
  .used_block_cnt = 0 };

static sli_mem_pool_handle_t mempool_hdlc_reject;
SLI_MEM_POOL_DECLARE_BUFFER(mempool_hdlc_reject,
                            SLI_CPC_HDLC_REJECT_PAYLOAD_SIZE,
                            SLI_CPC_HDLC_REJECT_MAX_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_hdlc_reject =
{ .pool_handle = &mempool_hdlc_reject,
  .used_block_cnt = 0 };

static sli_mem_pool_handle_t mempool_rx_buffer;
SLI_MEM_POOL_DECLARE_BUFFER(mempool_rx_buffer,
                            SLI_CPC_RX_FRAME_MAX_LENGTH,
                            SL_CPC_RX_BUFFER_MAX_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_rx_buffer =
{ .pool_handle = &mempool_rx_buffer,
  .used_block_cnt = 0 };

static sli_mem_pool_handle_t mempool_endpoint;
SLI_MEM_POOL_DECLARE_BUFFER_WITH_TYPE(mempool_endpoint,
                                      sl_cpc_endpoint_t,
                                      SLI_CPC_ENDPOINT_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_endpoint =
{ .pool_handle = &mempool_endpoint,
  .used_block_cnt = 0 };

static sli_mem_pool_handle_t mempool_rx_queue_item;
SLI_MEM_POOL_DECLARE_BUFFER_WITH_TYPE(mempool_rx_queue_item,
                                      sl_cpc_receive_queue_item_t,
                                      SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_rx_queue_item =
{ .pool_handle = &mempool_rx_queue_item,
  .used_block_cnt = 0 };

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
static sli_mem_pool_handle_t mempool_command_handle;
SLI_MEM_POOL_DECLARE_BUFFER_WITH_TYPE(mempool_command_handle,
                                      sli_cpc_system_command_handle_t,
                                      SLI_CPC_SYSTEM_COMMAND_HANDLE_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_command_handle =
{ .pool_handle = &mempool_command_handle,
  .used_block_cnt = 0 };
#endif

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
static sli_mem_pool_handle_t mempool_system_command;
SLI_MEM_POOL_DECLARE_BUFFER(mempool_system_command,
                            SLI_CPC_SYSTEM_COMMAND_BUFFER_SIZE,
                            SLI_CPC_SYSTEM_COMMAND_BUFFER_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_system_command =
{ .pool_handle = &mempool_system_command,
  .used_block_cnt = 0 };
#endif

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
static sli_mem_pool_handle_t mempool_tx_security_tag;
SLI_MEM_POOL_DECLARE_BUFFER(mempool_tx_security_tag,
                            SLI_SECURITY_TAG_LENGTH_BYTES,
                            SL_CPC_TX_QUEUE_ITEM_MAX_COUNT);
static sl_cpc_mem_pool_handle_t cpc_mempool_tx_security_tag =
{ .pool_handle = &mempool_tx_security_tag,
  .used_block_cnt = 0 };
#endif

sl_slist_node_t *postponed_free_rx_queue_item;
#if !defined(SL_CATALOG_KERNEL_PRESENT)
static uint16_t tx_item_used_count = 0;
#endif
static uint16_t sframe_tx_item_used_count = 0;

#if defined(SL_CATALOG_KERNEL_PRESENT)
#if defined(SL_CATALOG_CMSIS_OS_COMMON_PRESENT)
__ALIGNED(4) static uint8_t tx_item_availability_semaphore_cb[osSemaphoreCbSize];
#endif
static osSemaphoreId_t tx_item_availability_signal;     ///< transmit queue item availability signal
#endif

extern sli_cpc_drv_capabilities_t sli_cpc_driver_capabilities;

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

static void* alloc_object(sl_cpc_mem_pool_handle_t *pool);

static void free_object(sl_cpc_mem_pool_handle_t *pool,
                        void *block);

static sl_status_t free_receive_queue_item(sl_cpc_receive_queue_item_t *item);

static sl_status_t free_receive_queue_item_from_postponed_list();

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize CPC buffers' handling module.
 ******************************************************************************/
sl_status_t sli_cpc_memory_init(void)
{
#if defined(SL_CATALOG_KERNEL_PRESENT)
  osSemaphoreAttr_t tx_item_availability_signal_semaphore_attr = { 0 };
#if defined(SL_CATALOG_CMSIS_OS_COMMON_PRESENT)
  tx_item_availability_signal_semaphore_attr.cb_mem = tx_item_availability_semaphore_cb;
  tx_item_availability_signal_semaphore_attr.cb_size = osSemaphoreCbSize;
#else
  semaphore_attr.cb_mem = NULL;
  semaphore_attr.cb_size = 0U;
#endif  // SL_CATALOG_CMSIS_OS_COMMON_PRESENT

  tx_item_availability_signal = osSemaphoreNew(SL_CPC_TX_QUEUE_ITEM_MAX_COUNT, SL_CPC_TX_QUEUE_ITEM_MAX_COUNT, &tx_item_availability_signal_semaphore_attr);
  if (tx_item_availability_signal == 0) {
    EFM_ASSERT(false);
    return SL_STATUS_ALLOCATION_FAILED;
  }

#endif

  SLI_CPC_DEBUG_MEMORY_POOL_INIT();

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_buffer_handle.pool_handle,
                      (uint16_t)sizeof(sl_cpc_buffer_handle_t),
                      SLI_CPC_BUFFER_HANDLE_MAX_COUNT,
                      mempool_buffer_handle_buffer,
                      sizeof(mempool_buffer_handle_buffer));

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_hdlc_header.pool_handle,
                      SLI_CPC_HDLC_HEADER_RAW_SIZE,
                      SLI_CPC_HDLC_HEADER_MAX_COUNT,
                      mempool_hdlc_header_buffer,
                      sizeof(mempool_hdlc_header_buffer));

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_hdlc_reject.pool_handle,
                      SLI_CPC_HDLC_REJECT_PAYLOAD_SIZE,
                      SLI_CPC_HDLC_REJECT_MAX_COUNT,
                      mempool_hdlc_reject_buffer,
                      sizeof(mempool_hdlc_reject_buffer));

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_rx_buffer.pool_handle,
                      SLI_CPC_RX_FRAME_MAX_LENGTH,
                      SL_CPC_RX_BUFFER_MAX_COUNT,
                      mempool_rx_buffer_buffer,
                      sizeof(mempool_rx_buffer_buffer));

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_endpoint.pool_handle,
                      (uint16_t)sizeof(sl_cpc_endpoint_t),
                      SLI_CPC_ENDPOINT_COUNT,
                      mempool_endpoint_buffer,
                      sizeof(mempool_endpoint_buffer));

  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_rx_queue_item.pool_handle,
                      (uint16_t)sizeof(sl_cpc_receive_queue_item_t),
                      SLI_CPC_RX_QUEUE_ITEM_MAX_COUNT,
                      mempool_rx_queue_item_buffer,
                      sizeof(mempool_rx_queue_item_buffer));

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_command_handle.pool_handle,
                      (uint16_t)sizeof(sli_cpc_system_command_handle_t),
                      SLI_CPC_SYSTEM_COMMAND_HANDLE_COUNT,
                      mempool_command_handle_buffer,
                      sizeof(mempool_command_handle_buffer));
#endif

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_system_command.pool_handle,
                      SLI_CPC_SYSTEM_COMMAND_BUFFER_SIZE,
                      SLI_CPC_SYSTEM_COMMAND_BUFFER_COUNT,
                      mempool_system_command_buffer,
                      sizeof(mempool_system_command_buffer));
#endif

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  sli_mem_pool_create((sli_mem_pool_handle_t *)cpc_mempool_tx_security_tag.pool_handle,
                      SLI_SECURITY_TAG_LENGTH_BYTES,
                      SL_CPC_TX_QUEUE_ITEM_MAX_COUNT,
                      mempool_tx_security_tag_buffer,
                      sizeof(mempool_tx_security_tag_buffer));
#endif

  sl_slist_init(&postponed_free_rx_queue_item);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get a CPC handle buffer from write operations
 ******************************************************************************/
sl_status_t sli_cpc_get_write_buffer_handle(sl_cpc_buffer_handle_t **handle, bool block, uint32_t timeout)
{
#if defined(SL_CATALOG_KERNEL_PRESENT)
  sl_status_t status;
  osStatus_t sem_status = osSemaphoreAcquire(tx_item_availability_signal, block ? timeout : 0);
  if (sem_status == osErrorResource ||  sem_status == osErrorTimeout) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }
  EFM_ASSERT(sem_status == osOK);
  status = sli_cpc_get_buffer_handle(handle, SL_CPC_TX_DATA_BUFFER_HANDLE);
  EFM_ASSERT(status != SL_STATUS_NO_MORE_RESOURCE); // On a kernel, this should not happen
  return status;
#else
  (void)block;
  (void)timeout;
  return sli_cpc_get_buffer_handle(handle, SL_CPC_TX_DATA_BUFFER_HANDLE);
#endif
}

/***************************************************************************//**
 * Get a CPC handle buffer
 ******************************************************************************/
sl_status_t sli_cpc_get_buffer_handle(sl_cpc_buffer_handle_t **handle, sl_cpc_buffer_handle_type_t type)
{
  MCU_DECLARE_IRQ_STATE;
  sl_cpc_buffer_handle_t *buf_handle;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  buf_handle = alloc_object(&cpc_mempool_buffer_handle);
  if (buf_handle == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  // Update counters
  MCU_ENTER_ATOMIC();
  switch (type) {
    case SL_CPC_RX_INTERNAL_BUFFER_HANDLE:
      break;
    case SL_CPC_TX_REJECT_BUFFER_HANDLE:
    case SL_CPC_TX_SFRAME_BUFFER_HANDLE:
      if (sframe_tx_item_used_count >= SLI_CPC_TX_QUEUE_ITEM_SFRAME_MAX_COUNT) {
        free_object(&cpc_mempool_buffer_handle, buf_handle);
        MCU_EXIT_ATOMIC();
        return SL_STATUS_NO_MORE_RESOURCE;
      }
      ++sframe_tx_item_used_count;
      break;
    case SL_CPC_TX_DATA_BUFFER_HANDLE:
#if !defined(SL_CATALOG_KERNEL_PRESENT)
      if (tx_item_used_count >= SL_CPC_TX_QUEUE_ITEM_MAX_COUNT) {
        free_object(&cpc_mempool_buffer_handle, buf_handle);
        MCU_EXIT_ATOMIC();
        return SL_STATUS_NO_MORE_RESOURCE;
      }
      ++tx_item_used_count;
#endif
      break;
    case SL_CPC_UNKNOWN_BUFFER_HANDLE:
    default:
      return SL_STATUS_INVALID_PARAMETER;
      break;
  }
  MCU_EXIT_ATOMIC();

  buf_handle->hdlc_header = NULL;
  buf_handle->data = NULL;
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  buf_handle->security_tag = NULL;
#endif
  buf_handle->data_length = 0;
  buf_handle->endpoint = NULL;
  buf_handle->fcs[0] = 0;
  buf_handle->fcs[1] = 0;
  buf_handle->control = 0;
  buf_handle->address = 0;
  buf_handle->type = type;
  buf_handle->arg = NULL;
  buf_handle->reason = SL_CPC_REJECT_NO_ERROR;
  buf_handle->ref_count = 0;
  EFM_ASSERT(buf_handle->core_node.node == NULL);
  EFM_ASSERT(buf_handle->driver_node.node == NULL);
  buf_handle->core_node.node = NULL;
  buf_handle->driver_node.node = NULL;

  *handle = buf_handle;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get a CPC header buffer
 ******************************************************************************/
sl_status_t sli_cpc_get_hdlc_header_buffer(void **header)
{
  if (header == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *header = alloc_object(&cpc_mempool_hdlc_header);
  if (*header == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get a CPC header buffer for transmitting a reject
 ******************************************************************************/
sl_status_t sli_cpc_get_reject_buffer(sl_cpc_buffer_handle_t **handle)
{
  sl_status_t status;
  sl_cpc_buffer_handle_t *buf_handle;

  status = sli_cpc_get_buffer_handle(&buf_handle, SL_CPC_TX_REJECT_BUFFER_HANDLE);
  if (status != SL_STATUS_OK) {
    return status;
  }

  buf_handle->data = alloc_object(&cpc_mempool_hdlc_reject);

  if (buf_handle->data == NULL) {
    sli_cpc_free_buffer_handle(buf_handle);
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  buf_handle->data_length = 1;
  *handle = buf_handle;

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get a CPC buffer for reception.
 ******************************************************************************/
sl_status_t sli_cpc_get_buffer_handle_for_rx(sl_cpc_buffer_handle_t **handle)
{
  sl_cpc_buffer_handle_t *buf_handle;
  sl_status_t status;
  void *data = NULL;
  void *hdlc_header = NULL;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (!sli_cpc_driver_capabilities.use_raw_rx_buffer) {
    data = alloc_object(&cpc_mempool_rx_buffer);
    if (data == NULL) {
      return SL_STATUS_NO_MORE_RESOURCE;
    }
  }

  status = sli_cpc_get_hdlc_header_buffer(&hdlc_header);
  if (hdlc_header == NULL) {
    goto rx_buffer_allocated;
  }

  status = sli_cpc_get_buffer_handle(&buf_handle, SL_CPC_RX_INTERNAL_BUFFER_HANDLE);
  if (status != SL_STATUS_OK) {
    goto hdlc_header_allocated;
  }

  buf_handle->data = data;
  buf_handle->hdlc_header = hdlc_header;
  buf_handle->data_length = 0u;
  buf_handle->reason = SL_CPC_REJECT_NO_ERROR;
  *handle = buf_handle;

  return SL_STATUS_OK;

  // Error path:
  hdlc_header_allocated:
  sli_cpc_free_hdlc_header(hdlc_header);

  rx_buffer_allocated:
  if (!sli_cpc_driver_capabilities.use_raw_rx_buffer) {
    free_object(&cpc_mempool_rx_buffer, data);
  }
  return status;
}

/***************************************************************************//**
 * Get a CPC RAW buffer for reception.
 ******************************************************************************/
sl_status_t sli_cpc_get_raw_rx_buffer(void **raw_rx_buffer)
{
  EFM_ASSERT(sli_cpc_driver_capabilities.use_raw_rx_buffer);

  *raw_rx_buffer = alloc_object(&cpc_mempool_rx_buffer);
  if (*raw_rx_buffer == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get a CPC RAW buffer for reception.
 ******************************************************************************/
sl_status_t sli_cpc_free_raw_rx_buffer(void *raw_rx_buffer)
{
  EFM_ASSERT(sli_cpc_driver_capabilities.use_raw_rx_buffer);

  if (raw_rx_buffer != NULL) {
    free_object(&cpc_mempool_rx_buffer, raw_rx_buffer);
  } else {
    return SL_STATUS_NULL_POINTER;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free rx handle and all associate buffers
 ******************************************************************************/
sl_status_t sli_cpc_free_buffer_handle(sl_cpc_buffer_handle_t *handle)
{
  MCU_DECLARE_IRQ_STATE;
  bool rx_buffer_handle_freed = false;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (handle->ref_count > 0) {
    // Can't free the buffer_handle, it is being used elsewhere
    return SL_STATUS_BUSY;
  }

  // Check if the buffer handle was still pointing to another buffer handle
  // If so, it could cause a dangling buffer_handle not referenced in any list
  EFM_ASSERT(handle->core_node.node == NULL);
  EFM_ASSERT(handle->driver_node.node == NULL);

  if (handle->hdlc_header != NULL) {
    sli_cpc_free_hdlc_header(handle->hdlc_header);
  }

#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  sli_cpc_free_security_tag_buffer(handle->security_tag);
#endif

  switch (handle->type) {
    case SL_CPC_RX_USER_BUFFER_HANDLE:
      rx_buffer_handle_freed = true;
      break;
    case SL_CPC_RX_INTERNAL_BUFFER_HANDLE:
      // Buffer was allocated but handle is freed before being passed to user
      // This means that we must free the rx buffer or it will be leaked

      if (handle->data != NULL) {
        sli_cpc_free_rx_buffer(handle->data);
      }
      rx_buffer_handle_freed = true;
#ifdef CPC_DEBUG_TRACE
      if (handle->endpoint != NULL) {
        SLI_CPC_DEBUG_TRACE_ENDPOINT_RXD_DATA_FRAME_DROPPED(handle->endpoint);
      } else {
        SLI_CPC_DEBUG_TRACE_CORE_RXD_DATA_FRAME_DROPPED();
      }
#endif
      break;
    case SL_CPC_TX_REJECT_BUFFER_HANDLE:
      free_object(&cpc_mempool_hdlc_reject, handle->data);
      SL_FALLTHROUGH
    case SL_CPC_TX_SFRAME_BUFFER_HANDLE:
    case SL_CPC_TX_DATA_BUFFER_HANDLE:
    case SL_CPC_UNKNOWN_BUFFER_HANDLE:
      break;
    default:
      EFM_ASSERT(false);
      break;
  }

  // Update counters
  MCU_ENTER_ATOMIC();
  free_object(&cpc_mempool_buffer_handle, handle);

  if (handle->type == SL_CPC_TX_DATA_BUFFER_HANDLE) {
#if defined(SL_CATALOG_KERNEL_PRESENT)
    osStatus_t sem_status = osSemaphoreRelease(tx_item_availability_signal);
    EFM_ASSERT(sem_status == osOK);
#else
    EFM_ASSERT(tx_item_used_count > 0);
    --tx_item_used_count;
#endif
  } else if (handle->type == SL_CPC_TX_SFRAME_BUFFER_HANDLE || handle->type == SL_CPC_TX_REJECT_BUFFER_HANDLE) {
    EFM_ASSERT(sframe_tx_item_used_count > 0);
    --sframe_tx_item_used_count;
  }
  MCU_EXIT_ATOMIC();

  if (rx_buffer_handle_freed) {
    // Notify the driver
    sli_cpc_drv_on_rx_buffer_handle_free();
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Convert rx buffer handle to a receive queue item;
 *  Free hdlc header and handle
 *  Alloc queue item and set fields
 ******************************************************************************/
sl_status_t sli_cpc_push_back_rx_data_in_receive_queue(sl_cpc_buffer_handle_t *handle,
                                                       sl_slist_node_t **head,
                                                       uint16_t data_length)
{
  sl_cpc_receive_queue_item_t *item;
  sl_status_t status;

  if (handle == NULL || head == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  status = sli_cpc_get_receive_queue_item(&item);
  if (status != SL_STATUS_OK) {
    return status;
  }

  item->node.node = NULL;
  item->data = handle->data;
  EFM_ASSERT(handle->type == SL_CPC_RX_INTERNAL_BUFFER_HANDLE);
  item->buffer_type = SL_CPC_RX_USER_BUFFER_HANDLE;
  item->data_length = data_length;

  sl_slist_push_back(head, &item->node);

  // Buffer is now owned by the user
  handle->type = SL_CPC_RX_USER_BUFFER_HANDLE;

  sli_cpc_free_buffer_handle(handle);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free rx buffer returned by sl_cpc_read().
 ******************************************************************************/
sl_status_t sl_cpc_free_rx_buffer(void *data)
{
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_rx_buffer, data);

  free_receive_queue_item_from_postponed_list();

  // Notify that at least one RX buffer is available
  sli_cpc_drv_on_rx_buffer_free();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free internal rx buffer; Not pushed in RX Queue.
 ******************************************************************************/
sl_status_t sli_cpc_free_rx_buffer(void *data)
{
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_rx_buffer, data);

  // Notify that at least one RX buffer is available
  sli_cpc_drv_on_rx_buffer_free();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free CPC hdlc header
 ******************************************************************************/
sl_status_t sli_cpc_free_hdlc_header(void *data)
{
  if (data == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_hdlc_header, data);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Get receive queue item
 ******************************************************************************/
sl_status_t sli_cpc_get_receive_queue_item(sl_cpc_receive_queue_item_t **item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *item = alloc_object(&cpc_mempool_rx_queue_item);
  if (*item == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free receive queue item
 ******************************************************************************/
static sl_status_t free_receive_queue_item(sl_cpc_receive_queue_item_t *item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_rx_queue_item, item);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free receive queue item and the data buffer
 ******************************************************************************/
void sli_cpc_free_receive_queue_item(sl_cpc_receive_queue_item_t *item)
{
  if (item == NULL) {
    return;
  }

  if (item->data != NULL) {
    EFM_ASSERT(item->buffer_type == SL_CPC_RX_USER_BUFFER_HANDLE);
    free_object(&cpc_mempool_rx_buffer, item->data);

    // Notify that at least one RX buffer is available
    sli_cpc_drv_on_rx_buffer_free();
  }

  free_object(&cpc_mempool_rx_queue_item, item);
}

/***************************************************************************//**
 * Push receive queue item queued to the postponed free list
 ******************************************************************************/
sl_status_t sli_cpc_push_receive_queue_item_to_postponed_list(sl_cpc_receive_queue_item_t *rx_queue_item,
                                                              void **data,
                                                              uint16_t * data_length)
{
  *data = rx_queue_item->data;
  *data_length = rx_queue_item->data_length;

  sl_slist_push(&postponed_free_rx_queue_item, &rx_queue_item->node);
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free receive queue item queued in the postponed free list
 ******************************************************************************/
static sl_status_t free_receive_queue_item_from_postponed_list()
{
  sl_slist_node_t *node = sl_slist_pop(&postponed_free_rx_queue_item);
  sl_cpc_receive_queue_item_t *item = SL_SLIST_ENTRY(node, sl_cpc_receive_queue_item_t, node);
  EFM_ASSERT(item != NULL);
  free_receive_queue_item(item);
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Pop a buffer handle from a list owned by the CPC core
 ******************************************************************************/
sl_cpc_buffer_handle_t* sli_cpc_pop_core_buffer_handle(sl_slist_node_t **head)
{
  sl_slist_node_t *item_node = sl_slist_pop(head);
  if (item_node == NULL) {
    return NULL;
  }
  sl_cpc_buffer_handle_t *item = SL_SLIST_ENTRY(item_node, sl_cpc_buffer_handle_t, core_node);
  EFM_ASSERT(item != NULL);
  EFM_ASSERT(item->ref_count > 0);
  --item->ref_count;
  return item;
}

/***************************************************************************//**
 * Pop a buffer handle from a list owned by the CPC driver
 ******************************************************************************/
sl_cpc_buffer_handle_t* sli_cpc_pop_driver_buffer_handle(sl_slist_node_t **head)
{
  sl_slist_node_t *item_node = sl_slist_pop(head);
  if (item_node == NULL) {
    return NULL;
  }
  sl_cpc_buffer_handle_t *item = SL_SLIST_ENTRY(item_node, sl_cpc_buffer_handle_t, driver_node);
  EFM_ASSERT(item != NULL);
  EFM_ASSERT(item->ref_count > 0);
  --item->ref_count;
  return item;
}

/***************************************************************************//**
 * Remove a buffer handle from a list owned by the CPC core
 ******************************************************************************/
void sli_cpc_remove_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buffer_handle)
{
  EFM_ASSERT(buffer_handle != NULL);
  EFM_ASSERT(buffer_handle->ref_count > 0);
  buffer_handle->ref_count--;
  sl_slist_remove(head, &buffer_handle->core_node);
}

/***************************************************************************//**
 * Remove a buffer handle from a list owned by the CPC driver
 ******************************************************************************/
void sli_cpc_remove_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buffer_handle)
{
  EFM_ASSERT(buffer_handle != NULL);
  EFM_ASSERT(buffer_handle->ref_count > 0);
  buffer_handle->ref_count--;
  sl_slist_remove(head, &buffer_handle->driver_node);
}

/***************************************************************************//**
 * Get endpoint
 ******************************************************************************/
sl_status_t sli_cpc_get_endpoint(sl_cpc_endpoint_t **endpoint)
{
  if (endpoint == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *endpoint = alloc_object(&cpc_mempool_endpoint);
  if (*endpoint == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  memset(*endpoint, 0, sizeof(sl_cpc_endpoint_t));

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free endpoint
 ******************************************************************************/
void sli_cpc_free_endpoint(sl_cpc_endpoint_t *endpoint)
{
  free_object(&cpc_mempool_endpoint, endpoint);
}

/***************************************************************************//**
 * Push back a list item containing an allocated buffer handle for the core
 ******************************************************************************/
void sli_cpc_push_back_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle)
{
  EFM_ASSERT(buf_handle != NULL);
  buf_handle->ref_count++;
  EFM_ASSERT(buf_handle->ref_count <= 2);
  sl_slist_push_back(head, &buf_handle->core_node);
}

/***************************************************************************//**
 * Push back a list item containing an allocated buffer handle for the driver
 ******************************************************************************/
void sli_cpc_push_back_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle)
{
  EFM_ASSERT(buf_handle != NULL);
  buf_handle->ref_count++;
  EFM_ASSERT(buf_handle->ref_count <= 2);
  sl_slist_push_back(head, &buf_handle->driver_node);
}

/***************************************************************************//**
 * Push a list item containing an allocated buffer handle for the core
 ******************************************************************************/
void sli_cpc_push_core_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle)
{
  EFM_ASSERT(buf_handle != NULL);
  buf_handle->ref_count++;
  EFM_ASSERT(buf_handle->ref_count <= 2);
  sl_slist_push(head, &buf_handle->core_node);
}

/***************************************************************************//**
 * Push a list item containing an allocated buffer handle for the driver
 ******************************************************************************/
void sli_cpc_push_driver_buffer_handle(sl_slist_node_t **head, sl_cpc_buffer_handle_t *buf_handle)
{
  EFM_ASSERT(buf_handle != NULL);
  buf_handle->ref_count++;
  EFM_ASSERT(buf_handle->ref_count <= 2);
  sl_slist_push(head, &buf_handle->driver_node);
}

#if defined(SL_CATALOG_CPC_PRIMARY_PRESENT)
/***************************************************************************//**
 * Get a system command handle
 ******************************************************************************/
sl_status_t sli_cpc_get_system_command_handle(sli_cpc_system_command_handle_t **item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *item = alloc_object(&cpc_mempool_command_handle);
  if (*item == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free a command buffer
 ******************************************************************************/
sl_status_t sli_cpc_free_system_command_handle(sli_cpc_system_command_handle_t *item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_command_handle, item);

  return SL_STATUS_OK;
}
#endif

#if defined(SL_CATALOG_CPC_SECONDARY_PRESENT)
/***************************************************************************//**
 * Get a command buffer
 ******************************************************************************/
sl_status_t sli_cpc_get_system_command_buffer(sli_cpc_system_cmd_t **item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *item = alloc_object(&cpc_mempool_system_command);
  if (*item == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Free a command buffer
 ******************************************************************************/
sl_status_t sli_cpc_free_command_buffer(sli_cpc_system_cmd_t *item)
{
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_system_command, item);

  return SL_STATUS_OK;
}
#endif

/***************************************************************************//**
 * Allocate a security tag buffer
 ******************************************************************************/
sl_status_t sli_cpc_get_security_tag_buffer(void **tag_buffer)
{
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  if (tag_buffer == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  *tag_buffer = alloc_object(&cpc_mempool_tx_security_tag);
  if (*tag_buffer == NULL) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  return SL_STATUS_OK;
#else
  (void)tag_buffer;

  return SL_STATUS_NOT_AVAILABLE;
#endif
}

/***************************************************************************//**
 * Free a security tag buffer
 ******************************************************************************/
sl_status_t sli_cpc_free_security_tag_buffer(void *tag_buffer)
{
#if (SL_CPC_ENDPOINT_SECURITY_ENABLED >= 1)
  if (tag_buffer == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  free_object(&cpc_mempool_tx_security_tag, tag_buffer);

  return SL_STATUS_OK;
#else
  (void)tag_buffer;

  return SL_STATUS_NOT_AVAILABLE;
#endif
}

/***************************************************************************//**
 * Alloc object from a specified pool; Manage stat as well
 ******************************************************************************/
static void* alloc_object(sl_cpc_mem_pool_handle_t *pool)
{
  void *block;

  #if (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1)
  MCU_DECLARE_IRQ_STATE;
  MCU_ENTER_ATOMIC();
  #endif

  block = sli_mem_pool_alloc((sli_mem_pool_handle_t *)pool->pool_handle);

  #if (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1)
  if (block != NULL) {
    pool->used_block_cnt++;
  }
  MCU_EXIT_ATOMIC();
  #endif

  return block;
}

/***************************************************************************//**
 * Free object from a specified pool; Manage stat as well
 ******************************************************************************/
static void free_object(sl_cpc_mem_pool_handle_t *pool,
                        void *block)
{
  #if (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1)
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();
  #endif

  sli_mem_pool_free((sli_mem_pool_handle_t *)pool->pool_handle, block);

  #if (SL_CPC_DEBUG_MEMORY_ALLOCATOR_COUNTERS == 1)
  pool->used_block_cnt--;
  CORE_EXIT_ATOMIC();
  #endif
}
