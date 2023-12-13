/***************************************************************************/
/**
 * @file
 * @brief CMSIS RTOS2 adaptation for running OpenThread in RTOS
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 *
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 *
 * This software is distributed to you in Source Code format and is governed by
 * the sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <assert.h>
#include <stdio.h>

#include <openthread-core-config.h>
#include <openthread-system.h>
#include <openthread/tasklet.h>

#include <mbedtls/platform.h>

#include "cmsis_os2.h"
#include "sl_ot_rtos_adaptation.h"
#include "sl_ot_init.h"
#include "sl_cmsis_os2_common.h"
#include "sl_component_catalog.h"

static osThreadId_t      sMainThread   = NULL;
__ALIGNED(8) static uint8_t openthread_task_stack[SL_OPENTHREAD_OS_STACK_TASK_SIZE];
__ALIGNED(4) static uint8_t openthread_task_cb[osThreadCbSize];

static void mainloop(void *aContext);
otInstance *otGetInstance(void);

const osThreadAttr_t otMainThreadAttr = {
  .name  = "otMainThread",
  .attr_bits = 0u,
  .stack_size = SL_OPENTHREAD_OS_STACK_TASK_SIZE,
  .stack_mem = openthread_task_stack,
  .cb_mem = openthread_task_cb,
  .cb_size = osThreadCbSize,
  .priority = (osPriority_t) SL_OPENTHREAD_RTOS_TASK_PRIORITY,
};

void sl_ot_rtos_init(void)
{
    sMainThread =  osThreadNew(mainloop, NULL, &otMainThreadAttr);
    // Handling OpenThread initialization here
    // ensures that, any functions calling mbedTLS API
    // (and subsequently OSMutexPend), are called after the kernel has started.
    sl_ot_init();
}

static void mainloop(void *aContext)
{
    (void)aContext;

#if defined(SL_CATALOG_OT_CRASH_HANDLER_PRESENT)
    efr32PrintResetInfo();
#endif

    otInstance *instance = otGetInstance();
    while (!otSysPseudoResetWasRequested())
    {
        otSysProcessDrivers(instance);
        otTaskletsProcess(instance);
        sl_ot_rtos_application_tick();

        if (!otTaskletsArePending(instance)) {
            osThreadFlagsWait (0x0001, osFlagsWaitAny, osWaitForever);
        }
    }

    otInstanceFinalize(instance);
    osThreadTerminate(sMainThread);
}



static void resumeThread()
{
    if (sMainThread != NULL)
    {
        osThreadFlagsSet(sMainThread, 0x0001);
    }
}

void otTaskletsSignalPending(otInstance *aInstance)
{
    (void)aInstance;
    resumeThread();
}

void otSysEventSignalPending(void)
{
    resumeThread();
}

__WEAK void sl_ot_rtos_application_tick(void)
{
}
