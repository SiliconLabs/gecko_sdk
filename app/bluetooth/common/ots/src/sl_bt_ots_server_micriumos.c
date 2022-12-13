/***************************************************************************//**
 * @file
 * @brief OTS Server Micrium OS implementation
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

#include "os.h"
#include "sl_status.h"
#include "em_common.h"
#include "app_assert.h"
#include "sl_bt_ots_server.h"
#include "sli_bt_ots_server_adaptation.h"
#include "sl_bt_ots_server_config.h"
#include "sl_bt_ots_server_micriumos_config.h"
#include "sl_bluetooth_connection_config.h"

#define OTS_SERVER_INDICATION_TASK_NAME   "ots_server_indications"
#define OTS_SERVER_SEMAPHORE_NAME         "ots_server_semaphore"
#define OTS_SERVER_MUTEX_NAME             "ots_server_mutex"

// Task stack definition and identifier.
static CPU_STK indication_task_stack[SL_BT_OTS_SERVER_TASK_STACK] = { 0 };
static OS_TCB indication_task_handle;

// Binary semaphore to run the indication task only if its really necessary.
static OS_SEM indication_semaphore;

// API mutex
static OS_MUTEX api_mutex;

// Storage for indication queues
static sli_bt_ots_indication_queue_item_t indication_queue_data[SL_BT_CONFIG_MAX_CONNECTIONS]
[SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE];
static bool indication_queue_reservation[SL_BT_CONFIG_MAX_CONNECTIONS]
[SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE]
  = { { 0 } };
// Pointers to current indications
static sli_bt_ots_indication_queue_item_t *active_indication_table[SL_BT_CONFIG_MAX_CONNECTIONS] = { NULL };

// Indication queue variables
static OS_Q indication_queue[SL_BT_CONFIG_MAX_CONNECTIONS];

// -----------------------------------------------------------------------------
// Forward declaration of private functions

// Task function-prototype.
static void ots_server_indication_task(void *p_arg);

// Memory utility functions
static sli_bt_ots_indication_queue_item_t *reserve_slot(uint8_t index);
static void free_slot(uint8_t index, sli_bt_ots_indication_queue_item_t *slot);

// -----------------------------------------------------------------------------
// Public functions

void sli_bt_ots_server_adaptation_init(void)
{
  RTOS_ERR err;

  // Initialize semaphore for scheduling.
  OSSemCreate(&indication_semaphore,
              OTS_SERVER_SEMAPHORE_NAME,
              1,
              &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] OTS Server semaphore create failed!",
             (int)err.Code);

  // Initialize API mutex.
  OSMutexCreate(&api_mutex,
                OTS_SERVER_MUTEX_NAME,
                &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] OTS Server mutex create failed!",
             (int)err.Code);

  OSTaskCreate(&indication_task_handle,
               OTS_SERVER_INDICATION_TASK_NAME,
               ots_server_indication_task,
               DEF_NULL,
               SL_BT_OTS_SERVER_TASK_PRIO,
               &indication_task_stack[0u],
               (SL_BT_OTS_SERVER_TASK_STACK / sizeof(CPU_STK) / 10u),
               (SL_BT_OTS_SERVER_TASK_STACK / sizeof(CPU_STK)),
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] OTS Server indication task creation failed!",
             (int)err.Code);

  for (uint8_t i = 0; i < SL_BT_CONFIG_MAX_CONNECTIONS; i++) {
    // Initialize queue
    OSQCreate(&indication_queue[i],
              NULL,
              SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE * SL_BT_OTS_SERVER_CONFIG_INDICATION_SIZE_MAX,
              &err);
    app_assert(err.Code == RTOS_ERR_NONE,
               "[E: 0x%04x] OTS Server Indication queue %d. init failed!",
               (int)err.Code, i);
  }
}

bool sli_bt_ots_server_adaptation_indication_queue_is_empty(uint8_t index)
{
  bool res = false;
  sl_status_t sc;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    res = true;
  } else if (active_indication_table[index] == NULL) {
    sc = sli_bt_ots_server_adaptation_indication_queue_peek(index, NULL);
    if (sc == SL_STATUS_EMPTY) {
      res = true;
    }
  }

  return res;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_add(uint8_t                            index,
                                                              sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc = SL_STATUS_FAIL;
  RTOS_ERR err;

  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  sli_bt_ots_indication_queue_item_t *item_stored =
    reserve_slot(index);

  if (item_stored != NULL) {
    memcpy(item_stored, item, sizeof(sli_bt_ots_indication_queue_item_t));

    OSQPost(&indication_queue[index],
            item_stored,
            sizeof(sli_bt_ots_indication_queue_item_t),
            OS_OPT_POST_FIFO + OS_OPT_POST_NO_SCHED,
            &err);

    if (err.Code == RTOS_ERR_NONE) {
      sc = sli_bt_ots_server_adaptation_indication_queue_proceed();
    }
  } else {
    sc = SL_STATUS_ALLOCATION_FAILED;
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_peek(uint8_t                            index,
                                                               sli_bt_ots_indication_queue_item_t *item)
{
  sl_status_t sc;
  RTOS_ERR err;
  OS_MSG_SIZE size = SL_BT_OTS_SERVER_CONFIG_INDICATION_SIZE_MAX;
  sli_bt_ots_indication_queue_item_t *item_received = NULL;
  if (item == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }

  if (active_indication_table[index] == NULL) {
    item_received = OSQPend(&indication_queue[index],
                            0,
                            OS_OPT_PEND_NON_BLOCKING,
                            &size,
                            NULL,
                            &err);
    if (err.Code == RTOS_ERR_NONE) {
      active_indication_table[index] = item_received;
    }
  }
  if (active_indication_table[index] != NULL) {
    if (item != NULL) {
      memcpy(item,
             active_indication_table[index],
             size);
    }
    sc = SL_STATUS_OK;
  } else {
    sc = SL_STATUS_EMPTY;
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_remove(uint8_t index)
{
  sl_status_t sc = SL_STATUS_FAIL;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }
  free_slot(index,
            active_indication_table[index]);
  active_indication_table[index] = NULL;

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_proceed(void)
{
  sl_status_t sc = SL_STATUS_OK;
  RTOS_ERR err;

  // Trigger task to proceed
  (void)OSSemPost(&indication_semaphore, OS_OPT_POST_1, &err);

  if (err.Code != RTOS_ERR_NONE) {
    sc = SL_STATUS_FAIL;
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_indication_queue_clear(uint8_t index)
{
  sl_status_t sc = SL_STATUS_OK;
  RTOS_ERR err;
  OS_MSG_SIZE size;
  uint8_t *item = NULL;
  bool flush_done = false;
  if (index >= SL_BT_CONFIG_MAX_CONNECTIONS) {
    return SL_STATUS_NOT_FOUND;
  }
  // Free active indication
  if (active_indication_table[index] != NULL) {
    free_slot(index,
              active_indication_table[index]);
    active_indication_table[index] = NULL;
  }

  // Free others in the queue
  while (!flush_done) {
    item = OSQPend(&indication_queue[index],
                   0,
                   OS_OPT_PEND_NON_BLOCKING,
                   &size,
                   NULL,
                   &err);
    if (err.Code != RTOS_ERR_NONE) {
      sc = SL_STATUS_FAIL;
      flush_done = true;
    } else {
      if (item == NULL) {
        // Queue is empty
        sc = SL_STATUS_OK;
        flush_done = true;
      } else {
        free_slot(index,
                  (sli_bt_ots_indication_queue_item_t *)item);
      }
    }
  }

  if (err.Code != RTOS_ERR_NONE) {
    sc = SL_STATUS_FAIL;
  }

  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_acquire(void)
{
  sl_status_t sc = SL_STATUS_OK;
  RTOS_ERR err;

  OSMutexPend(&api_mutex,
              (OS_TICK)SL_BT_OTS_SERVER_MUTEX_WAIT,
              OS_OPT_PEND_BLOCKING,
              DEF_NULL,
              &err);

  if (err.Code != RTOS_ERR_NONE && err.Code != RTOS_ERR_IS_OWNER) {
    sc = SL_STATUS_FAIL;
  }
  return sc;
}

sl_status_t sli_bt_ots_server_adaptation_release(void)
{
  sl_status_t sc = SL_STATUS_OK;
  RTOS_ERR err;

  OSMutexPost(&api_mutex,
              OS_OPT_POST_NONE,
              &err);

  if (err.Code != RTOS_ERR_NONE && err.Code != RTOS_ERR_IS_OWNER) {
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
  PP_UNUSED_PARAM(p_arg);
  RTOS_ERR err;
  OS_SEM_CTR sem_cnt;

  // Trigger first run.
  sli_bt_ots_server_adaptation_indication_queue_proceed();

  // Start task main loop.
  while (DEF_TRUE) {
    // Waiting for the semaphore forever, without blocking.
    // No timestamp needed.
    sem_cnt = OSSemPend(&indication_semaphore,
                        0,
                        OS_OPT_PEND_BLOCKING,
                        DEF_NULL,
                        &err);
    app_assert(err.Code == RTOS_ERR_NONE,
               "[E: 0x%04x] OTS Server Indication semaphore post failed! Count: %d",
               (int)err.Code, (int)sem_cnt);
    // Execute cyclic process
    sli_bt_ots_server_step();
  }
}

static sli_bt_ots_indication_queue_item_t *reserve_slot(uint8_t index)
{
  sli_bt_ots_indication_queue_item_t *data = NULL;
  for (uint8_t i = 0; i < SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE; i++) {
    if (indication_queue_reservation[index][i] == false) {
      indication_queue_reservation[index][i] = true;
      data = &(indication_queue_data[index][i]);
      break;
    }
  }
  return data;
}
static void free_slot(uint8_t index, sli_bt_ots_indication_queue_item_t *slot)
{
  for (uint8_t i = 0; i < SL_BT_OTS_SERVER_CONFIG_INDICATION_QUEUE_SIZE; i++) {
    if (&(indication_queue_data[index][i]) == slot) {
      indication_queue_reservation[index][i] = false;
      break;
    }
  }
}
