/***************************************************************************//**
 * @file
 * @brief OTS Server FreeRTOS implementation
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
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "sl_status.h"
#include "em_common.h"
#include "app_assert.h"
#include "sl_bt_ots_server.h"
#include "sli_bt_ots_server_adaptation.h"
#include "sl_bt_ots_server_config.h"
#include "sl_bt_ots_server_freertos_config.h"
#include "sl_bluetooth_connection_config.h"

#define OTS_SERVER_INDICATION_TASK_NAME         "ots_server_indications"

// Task stack definition and identifier.
static StackType_t  indication_task_stack[SL_BT_OTS_SERVER_TASK_STACK] = { 0 };
static StaticTask_t indication_task_buffer;
static TaskHandle_t indication_task_handle;

// Binary semaphore to run the indication task only if its really necessary.
static SemaphoreHandle_t indication_semaphore;

// API mutex
static SemaphoreHandle_t api_mutex;

// Storage for indication queues
static uint8_t indication_queue_data[SL_BT_CONFIG_MAX_CONNECTIONS][(SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE * SL_BT_OTS_SERVER_CONFIG_INDICATION_SIZE_MAX)];

// Indication queue variables
static QueueHandle_t indication_queue[SL_BT_CONFIG_MAX_CONNECTIONS];
static StaticQueue_t indication_static_queue[SL_BT_CONFIG_MAX_CONNECTIONS];

// -----------------------------------------------------------------------------
// Forward declaration of private functions

// Task function-prototype.
static void ots_server_indication_task(void *p_arg);

// -----------------------------------------------------------------------------
// Public functions

void sli_bt_ots_server_adaptation_init(void)
{
  // Initialize binary semaphore for scheduling.
  indication_semaphore = xSemaphoreCreateBinary();

  // Initialize mutex.
  api_mutex = xSemaphoreCreateRecursiveMutex();

  indication_task_handle =
    xTaskCreateStatic(ots_server_indication_task,
                      OTS_SERVER_INDICATION_TASK_NAME,
                      SL_BT_OTS_SERVER_TASK_STACK,
                      NULL,
                      SL_BT_OTS_SERVER_TASK_PRIO,
                      indication_task_stack,
                      &indication_task_buffer);
  app_assert(NULL != indication_task_handle,
             "OTS Server Indication task creation failed!");

  for (uint8_t i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    indication_queue[i] = xQueueCreateStatic(SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE,
                                             SL_BT_OTS_SERVER_CONFIG_INDICATION_SIZE_MAX,
                                             indication_queue_data[i],
                                             &indication_static_queue[i]);
    app_assert(NULL != indication_queue[i],
               "OTS Server Indication queue %d. init failed!",
               i);
  }
}

bool sli_bt_ots_server_adaptation_indication_queue_is_empty(uint8_t index)
{
  bool res = false;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return true;
  }
  res = (uxQueueMessagesWaiting(indication_queue[index]) == 0);
  return res;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_add(uint8_t                            index,
                                                              sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  ret_val = xQueueSend(indication_queue[index],
                       item,
                       0);

  if (ret_val != pdTRUE) {
    sc = SL_STATUS_FAIL;
  } else {
    sli_bt_ots_server_adaptation_indication_queue_proceed();
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_peek(uint8_t                            index,
                                                               sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  ret_val = xQueuePeek(indication_queue[index],
                       item,
                       0);

  if (ret_val != pdTRUE) {
    sc = SL_STATUS_FAIL;
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_remove(uint8_t index)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  sli_bt_ots_indication_queue_item_t item;

  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  ret_val = xQueueReceive(indication_queue[index],
                          &item,
                          0);

  if (ret_val != pdTRUE) {
    sc = SL_STATUS_FAIL;
  } else {
    sc = sli_bt_ots_server_adaptation_indication_queue_proceed();
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_proceed(void)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  // Trigger the task to proceed.
  ret_val = xSemaphoreGive(indication_semaphore);

  if (ret_val != pdPASS) {
    sc = SL_STATUS_FAIL;
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_clear(uint8_t index)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  ret_val = xQueueReset(indication_queue[index]);

  if (ret_val != pdPASS) {
    sc = SL_STATUS_FAIL;
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_acquire(void)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  ret_val = xSemaphoreTakeRecursive(api_mutex,
                                    (TickType_t)SL_BT_OTS_SERVER_MUTEX_WAIT);
  if (ret_val != pdTRUE) {
    sc = SL_STATUS_FAIL;
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_release(void)
{
  sl_status_t sc = SL_STATUS_OK;
  BaseType_t ret_val;

  ret_val = xSemaphoreGiveRecursive(api_mutex);
  if (ret_val != pdPASS) {
    sc = SL_STATUS_FAIL;
  }
  return sc;
}

// -----------------------------------------------------------------------------
// Private functions

// Indication task function
static void ots_server_indication_task(void *p_arg)
{
  (void)p_arg;

  // Trigger first run.
  sli_bt_ots_server_adaptation_indication_queue_proceed();

  // Start task main loop.
  while (1) {
    if ( xSemaphoreTake(indication_semaphore, portMAX_DELAY) == pdTRUE ) {
      // Execute cyclic process
      sli_bt_ots_server_step();
    }
  }
}
