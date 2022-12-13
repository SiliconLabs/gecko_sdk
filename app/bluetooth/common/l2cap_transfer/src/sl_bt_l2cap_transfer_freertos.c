/***************************************************************************//**
 * @file
 * @brief L2CAP transfer FreeRTOS implementation
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
#include "em_common.h"
#include "app_assert.h"
#include "sl_bt_l2cap_transfer.h"
#include "sli_bt_l2cap_transfer_adaptation.h"
#include "sl_bt_l2cap_transfer_freertos_config.h"

#define L2CAP_TRANSFER_TASK_NAME         "l2cap_transfer"

/// Task stack definition and identifier.
static StackType_t  l2cap_transfer_task_stack[SL_BT_L2CAP_TRANSFER_TASK_STACK] = { 0 };
static StaticTask_t l2cap_transfer_task_buffer;
static TaskHandle_t l2cap_transfer_task_handle;

/// Binary semaphore to run the task only if its really necessary.
static SemaphoreHandle_t l2cap_transfer_semaphore;

/// L2CAP Transfer mutex
static SemaphoreHandle_t l2cap_transfer_mutex;

/// Task function-prototype.
static void l2cap_transfer_task(void *p_arg);

void sli_bt_l2cap_transfer_adaptation_init(void)
{
  // Initialize binary semaphore for scheduling.
  l2cap_transfer_semaphore = xSemaphoreCreateBinary();

  // Initialize mutex.
  l2cap_transfer_mutex = xSemaphoreCreateRecursiveMutex();

  l2cap_transfer_task_handle =
    xTaskCreateStatic(l2cap_transfer_task,
                      L2CAP_TRANSFER_TASK_NAME,
                      SL_BT_L2CAP_TRANSFER_TASK_STACK,
                      NULL,
                      SL_BT_L2CAP_TRANSFER_TASK_PRIO,
                      l2cap_transfer_task_stack,
                      &l2cap_transfer_task_buffer);
  app_assert(NULL != l2cap_transfer_task_handle,
             "L2CAP transfer task creation failed!");
}

bool sli_bt_l2cap_transfer_adaptation_acquire(void)
{
  BaseType_t success;
  success = xSemaphoreTakeRecursive(l2cap_transfer_mutex,
                                    (TickType_t)SL_BT_L2CAP_TRANSFER_MUTEX_WAIT);
  return (success == pdTRUE);
}

void sli_bt_l2cap_transfer_adaptation_release(void)
{
  xSemaphoreGiveRecursive(l2cap_transfer_mutex);
}

void sli_bt_l2cap_transfer_adaptation_proceed(void)
{
  // Trigger the task to proceed.
  (void)xSemaphoreGive(l2cap_transfer_semaphore);
}

static void l2cap_transfer_task(void *p_arg)
{
  (void)p_arg;

  // Trigger task.
  sli_bt_l2cap_transfer_adaptation_proceed();

  // Start task main loop.
  while (1) {
    if ( xSemaphoreTake(l2cap_transfer_semaphore, portMAX_DELAY) == pdTRUE ) {
      // Execute cyclic process
      sli_bt_l2cap_transfer_process_action();
    }
  }
}
