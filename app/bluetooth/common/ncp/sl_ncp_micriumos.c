/***************************************************************************//**
 * @file
 * @brief Bluetooth Network Co-Processor (NCP) Interface  Micrium OS implementation
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
#include "sl_ncp.h"
#include "sl_ncp_micriumos_config.h"

// Task stack definition and identifier
static CPU_STK ncp_task_stack[SL_NCP_TASK_STACK];
static OS_TCB  ncp_task_tcb;

// Semaphore to run the task only if its really necessary
static OS_SEM ncp_semaphore;

// Task function prototype
static void ncp_task(void *p_arg);

void sl_ncp_os_task_init(void)
{
  RTOS_ERR err;

  OSSemCreate(&ncp_semaphore,
              NCP_SEMAPHORE_NAME,
              1,
              &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] NCP semaphore creation failed!",
             (int)err.Code);

  OSTaskCreate(&ncp_task_tcb,
               NCP_TASK_NAME,
               ncp_task,
               DEF_NULL,
               SL_NCP_TASK_PRIO,
               &ncp_task_stack[0u],
               (SL_NCP_TASK_STACK / sizeof(CPU_STK) / 10u),
               (SL_NCP_TASK_STACK / sizeof(CPU_STK)),
               0u,
               0u,
               DEF_NULL,
               (OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
               &err);

  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] NCP task creation failed!",
             (int)err.Code);
}

void sl_ncp_os_task_proceed(void)
{
  RTOS_ERR err;
  OS_SEM_CTR sem_cnt;

  sem_cnt = OSSemPost(&ncp_semaphore, OS_OPT_POST_1, &err);
  app_assert(err.Code == RTOS_ERR_NONE,
             "[E: 0x%04x] NCP semaphore post failed! (Cnt: %d)",
             (int)err.Code, sem_cnt);
  (void)sem_cnt;
}

static void ncp_task(void *p_arg)
{
  PP_UNUSED_PARAM(p_arg);
  RTOS_ERR err;
  OS_SEM_CTR sem_cnt;

  sl_ncp_os_task_proceed();

  while (DEF_TRUE) {
    // Waiting for the semaphore forever, without blocking
    sem_cnt = OSSemPend(&ncp_semaphore,
                        0,
                        OS_OPT_PEND_BLOCKING,
                        DEF_NULL,
                        &err);
    app_assert(err.Code == RTOS_ERR_NONE,
               "[E: 0x%04x] NCP semaphore post failed! Count: %d",
               (int)err.Code, (int)sem_cnt);
    (void)sem_cnt;

    sl_ncp_step();
  }
}
