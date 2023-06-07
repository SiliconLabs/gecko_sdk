/***************************************************************************//**
 * @file
 * @brief L2CAP transfer Micrium OS implementation
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
#include "em_common.h"
#include "app_assert.h"
#include "sl_bt_l2cap_transfer.h"
#include "sli_bt_l2cap_transfer_adaptation.h"
#include "sl_bt_l2cap_transfer_micriumos_config.h"

// Task, semaphore and mutex names
#define L2CAP_TRANSFER_TASK_NAME              "l2cap_transfer"
#define L2CAP_TRANSFER_SEMAPHORE_NAME         "l2cap_semaphore"
#define L2CAP_TRANSFER_MUTEX_NAME             "l2cap_nmutex"

// Task stack definition and identifier.
static CPU_STK l2cap_transfer_task_stack[SL_BT_L2CAP_TRANSFER_TASK_STACK];
static OS_TCB  l2cap_transfer_task_tcb;

// Semaphore to run the task only if its really necessary.
static OS_SEM l2cap_transfer_semaphore;

// L2CAP Transfer mutex
static OS_MUTEX l2cap_transfer_mutex;

// Task function prototype.
static void l2cap_transfer_task(void *p_arg);

void sli_bt_l2cap_transfer_adaptation_init(void)
{
  RTOS_ERR err;

  // Initialize semaphore for scheduling.
  OSSemCreate(&l2cap_transfer_semaphore,
              L2CAP_TRANSFER_SEMAPHORE_NAME,
              1,
              &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] L2CAP transfer semaphore create failed!",
             (int)err.Code);

  OSMutexCreate(&l2cap_transfer_mutex,
                L2CAP_TRANSFER_MUTEX_NAME,
                &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] L2CAP transfer mutex create failed!",
             (int)err.Code);

  OSTaskCreate(&l2cap_transfer_task_tcb,
               L2CAP_TRANSFER_TASK_NAME,
               l2cap_transfer_task,
               DEF_NULL,
               SL_BT_L2CAP_TRANSFER_TASK_PRIO,
               &l2cap_transfer_task_stack[0u],
               (SL_BT_L2CAP_TRANSFER_TASK_STACK / sizeof(CPU_STK) / 10u),
               (SL_BT_L2CAP_TRANSFER_TASK_STACK / sizeof(CPU_STK)),
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] L2CAP transfer task creation failed!",
             (int)err.Code);
}

bool sli_bt_l2cap_transfer_adaptation_acquire(void)
{
  RTOS_ERR err;

  OSMutexPend(&l2cap_transfer_mutex,
              (OS_TICK)SL_BT_L2CAP_TRANSFER_MUTEX_WAIT,
              OS_OPT_PEND_BLOCKING,
              DEF_NULL,
              &err);
  // Allow nesting
  if (err.Code == RTOS_ERR_NONE || err.Code == RTOS_ERR_IS_OWNER ) {
    return true;
  }
  app_assert(err.Code == RTOS_ERR_NONE || err.Code == RTOS_ERR_IS_OWNER,
             "[E: 0x%04x] L2CAP transfer mutex pend failed!",
             (int)err.Code);
  return false;
}

void sli_bt_l2cap_transfer_adaptation_release(void)
{
  RTOS_ERR err;

  OSMutexPost(&l2cap_transfer_mutex,
              OS_OPT_POST_NONE,
              &err);
  // Allow nesting
  app_assert(err.Code == RTOS_ERR_NONE || err.Code == RTOS_ERR_IS_OWNER,
             "[E: 0x%04x] L2CAP transfer mutex post failed!",
             (int)err.Code);
}

void sli_bt_l2cap_transfer_adaptation_proceed(void)
{
  RTOS_ERR err;
  OS_SEM_CTR sem_cnt;
  // Trigger task to proceed
  sem_cnt = OSSemPost(&l2cap_transfer_semaphore, OS_OPT_POST_1, &err);
  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] L2CAP transfer semaphore post failed! (Cnt: %d)",
             (int)err.Code, sem_cnt);
}

static void l2cap_transfer_task(void *p_arg)
{
  PP_UNUSED_PARAM(p_arg);
  RTOS_ERR err;
  OS_SEM_CTR sem_cnt;

  // Trigger task.
  sli_bt_l2cap_transfer_adaptation_proceed();

  // Start task main loop.
  while (DEF_TRUE) {
    // Waiting for the semaphore forever, without blocking.
    // No timestamp needed.
    sem_cnt = OSSemPend(&l2cap_transfer_semaphore,
                        0,
                        OS_OPT_PEND_BLOCKING,
                        DEF_NULL,
                        &err);
    app_assert(err.Code == RTOS_ERR_NONE,
               "[E: 0x%04x] L2CAP transfer semaphore post failed! Count: %d",
               (int)err.Code, (int)sem_cnt);
    // Execute cyclic process
    sli_bt_l2cap_transfer_process_action();
  }
}
