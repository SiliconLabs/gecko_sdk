/*
 *  Copyright (c) 2023, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 *   This file implements the OpenThread platform abstraction for the alarm.
 *
 */

#include <assert.h>
#include <openthread-core-config.h>
#include <openthread-system.h>
#include <stdbool.h>
#include <stdint.h>
#include <openthread/platform/alarm-micro.h>
#include <openthread/platform/alarm-milli.h>
#include <openthread/platform/diag.h>
#include "common/debug.hpp"
#include "common/logging.hpp"

#include "platform-efr32.h"
#include "utils/code_utils.h"

#include "em_core.h"
#include "rail.h"
#include "sl_sleeptimer.h"

// timer data for handling wrapping
typedef struct wrap_timer_data wrap_timer_data_t;
struct wrap_timer_data {
  uint16_t overflow_counter;
  uint16_t overflow_max;
};

// millisecond timer (sleeptimer)
static sl_sleeptimer_timer_handle_t sl_handle;
static uint64_t                     sMsAlarm     = 0;
static bool                         sIsMsRunning = false;
static wrap_timer_data_t            milli_timer_data = {0};

// microsecond timer (RAIL timer)
static RAIL_MultiTimer_t rail_timer;
static uint64_t          sUsAlarm     = 0;
static bool              sIsUsRunning = false;
static wrap_timer_data_t micro_timer_data = {0};

// millisecond-alarm callback
static void AlarmCallback(sl_sleeptimer_timer_handle_t *aHandle, void *aData)
{
    if (aData == NULL)
    {
        OT_UNUSED_VARIABLE(aHandle);
        otSysEventSignalPending();
    }
    else
    {
        sl_status_t status;
        wrap_timer_data_t *timer_data = (wrap_timer_data_t *) aData;

        if (timer_data->overflow_counter < timer_data->overflow_max)
        {
            status = sl_sleeptimer_start_timer_ms(aHandle,
                                                  sl_sleeptimer_get_max_ms32_conversion(),
                                                  AlarmCallback,
                                                  (void *) timer_data,
                                                  0,
                                                  SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
            OT_ASSERT(status == SL_STATUS_OK);
            timer_data->overflow_counter++;
        }
        else
        {
            if (timer_data->overflow_max != 0)
            {
                sIsMsRunning = false;
                sl_sleeptimer_stop_timer(aHandle);
            }
        }
    }
}

// microsecond-alarm callback
static void radioTimerExpired(struct RAIL_MultiTimer *tmr, RAIL_Time_t expectedTimeOfEvent, void *cbArg)
{
    if (cbArg == NULL)
    {
        OT_UNUSED_VARIABLE(tmr);
        OT_UNUSED_VARIABLE(expectedTimeOfEvent);
        otSysEventSignalPending();
    }
    else
    {
        RAIL_Status_t status;
        wrap_timer_data_t *timer_data = (wrap_timer_data_t *) cbArg;

        if (timer_data->overflow_counter < timer_data->overflow_max)
        {
            status = RAIL_SetMultiTimer(tmr, UINT32_MAX, RAIL_TIME_DELAY, radioTimerExpired, NULL);
            OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
            timer_data->overflow_counter++;
        }
        else
        {
            if (timer_data->overflow_max != 0)
            {
                sIsUsRunning = false;
                RAIL_CancelMultiTimer(tmr);
            }
        }
    }
}

void efr32AlarmInit(void)
{
    memset(&sl_handle, 0, sizeof sl_handle);
}

uint32_t otPlatAlarmMilliGetNow(void)
{
    uint64_t    ticks;
    uint64_t    now;
    sl_status_t status;

    ticks  = sl_sleeptimer_get_tick_count64();
    status = sl_sleeptimer_tick64_to_ms(ticks, &now);
    OT_ASSERT(status == SL_STATUS_OK);
    return (uint32_t)now;
}

uint32_t otPlatTimeGetXtalAccuracy(void)
{
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    // For sleepies, we need to account for the low-frequency crystal
    // accuracy when they go to sleep.  Accounting for that as well,
    // for the worst case.
    if (efr32AllowSleepCallback())
    {
        return SL_OPENTHREAD_HFXO_ACCURACY + SL_OPENTHREAD_LFXO_ACCURACY;
    }
#endif
    return SL_OPENTHREAD_HFXO_ACCURACY;
}

void otPlatAlarmMilliStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt)
{
    OT_UNUSED_VARIABLE(aInstance);

    sl_status_t       status;
    int64_t           remaining;
    uint32_t          initial_wrap_time;

    sl_sleeptimer_stop_timer(&sl_handle);

    sMsAlarm     = aT0 + aDt;
    remaining    = (int64_t)(sMsAlarm - otPlatAlarmMilliGetNow());
    sIsMsRunning = true;

    if (remaining <= 0)
    {
        otSysEventSignalPending();
    }
    else
    {
        // The maximum value accepted by sleep timer ms32 APIs can be retrieved
        // using sl_sleeptimer_get_max_ms32_conversion().
        //
        // (See platform/service/sleeptimer/inc/sl_sleeptimer.h)
        //
        if (remaining > sl_sleeptimer_get_max_ms32_conversion())
        {
            initial_wrap_time = (uint32_t)(remaining % sl_sleeptimer_get_max_ms32_conversion());
            milli_timer_data.overflow_max = (uint16_t)(remaining / sl_sleeptimer_get_max_ms32_conversion());
            milli_timer_data.overflow_counter = 0;

            // Start a timer with the initial time
            status = sl_sleeptimer_start_timer_ms(&sl_handle,
                                                  initial_wrap_time,
                                                  AlarmCallback,
                                                  (void *) &milli_timer_data,
                                                  0,
                                                  SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
            OT_ASSERT(status == SL_STATUS_OK);
        }
        else
        {
            status = sl_sleeptimer_start_timer_ms(&sl_handle,
                                                  (uint32_t) remaining,
                                                  AlarmCallback,
                                                  NULL,
                                                  0,
                                                  SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
            OT_ASSERT(status == SL_STATUS_OK);
        }
    }
}

uint64_t efr32AlarmPendingTime(void)
{
    uint64_t remaining = 0;
    uint32_t now       = otPlatAlarmMilliGetNow();
    if (sIsMsRunning && (sMsAlarm > now))
    {
        remaining = sMsAlarm - now;
    }
    return remaining;
}

bool efr32AlarmIsRunning(otInstance *aInstance)
{
    return (otInstanceIsInitialized(aInstance) ? sIsMsRunning : false);
}

void otPlatAlarmMilliStop(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    sl_sleeptimer_stop_timer(&sl_handle);
    sIsMsRunning = false;
}

void efr32AlarmProcess(otInstance *aInstance)
{
    int64_t remaining;
    bool    alarmMilliFired = false;
#if OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
    bool alarmMicroFired = false;
#endif

    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    if (sIsMsRunning)
    {
        remaining = (int64_t)(sMsAlarm - otPlatAlarmMilliGetNow());
        if (remaining <= 0)
        {
            otPlatAlarmMilliStop(aInstance);
            alarmMilliFired = true;
        }
    }

#if OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
    if (sIsUsRunning)
    {
        remaining = (int64_t)(sUsAlarm - otPlatAlarmMicroGetNow());
        if (remaining <= 0)
        {
            otPlatAlarmMicroStop(aInstance);
            alarmMicroFired = true;
        }
    }
#endif

    CORE_EXIT_ATOMIC();

    if (alarmMilliFired)
    {
#if OPENTHREAD_CONFIG_DIAG_ENABLE
        if (otPlatDiagModeGet())
        {
            otPlatDiagAlarmFired(aInstance);
        }
        else
#endif
        {
            otPlatAlarmMilliFired(aInstance);
        }
    }

#if OPENTHREAD_CONFIG_PLATFORM_USEC_TIMER_ENABLE
    if (alarmMicroFired)
    {
        otPlatAlarmMicroFired(aInstance);
    }
#endif
}

uint32_t otPlatAlarmMicroGetNow(void)
{
    return RAIL_GetTime();
}

// Note: This function should be called at least once per wrap
// period for the wrap-around logic to work below
uint64_t otPlatTimeGet(void)
{
    static uint32_t timerWraps   = 0U;
    static uint32_t prev32TimeUs = 0U;
    uint32_t        now32TimeUs;
    uint64_t        now64TimeUs;
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_CRITICAL();
    now32TimeUs = RAIL_GetTime();
    if (now32TimeUs < prev32TimeUs)
    {
        timerWraps += 1U;
    }
    prev32TimeUs = now32TimeUs;
    now64TimeUs  = ((uint64_t)timerWraps << 32) + now32TimeUs;
    CORE_EXIT_CRITICAL();
    return now64TimeUs;
}

void otPlatAlarmMicroStartAt(otInstance *aInstance, uint32_t aT0, uint32_t aDt)
{
    OT_UNUSED_VARIABLE(aInstance);
    RAIL_Status_t     status;
    int64_t           remaining;
    uint32_t          initial_wrap_time;

    RAIL_CancelMultiTimer(&rail_timer);

    sUsAlarm     = aT0 + aDt;
    remaining    = (int64_t)(sUsAlarm - otPlatAlarmMicroGetNow());
    sIsUsRunning = true;

    if (remaining <= 0)
    {
        otSysEventSignalPending();
    }
    else
    {
        if (remaining > UINT32_MAX)
        {
            initial_wrap_time = (uint32_t)(remaining % UINT32_MAX);
            micro_timer_data.overflow_max = (uint16_t)(remaining / UINT32_MAX);
            micro_timer_data.overflow_counter = 0;

            // Start a timer with the initial time
            status = RAIL_SetMultiTimer(&rail_timer,
                                        initial_wrap_time,
                                        RAIL_TIME_DELAY,
                                        radioTimerExpired,
                                        (void *) &micro_timer_data);
            OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
        }
        else
        {
            status = RAIL_SetMultiTimer(&rail_timer, remaining, RAIL_TIME_DELAY, radioTimerExpired, NULL);
            OT_ASSERT(status == RAIL_STATUS_NO_ERROR);
        }
    }
}

void otPlatAlarmMicroStop(otInstance *aInstance)
{
    OT_UNUSED_VARIABLE(aInstance);

    RAIL_CancelMultiTimer(&rail_timer);
    sIsUsRunning = false;
}
