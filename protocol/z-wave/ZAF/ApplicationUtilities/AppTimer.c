/**
* @file
* @brief Application Timer module
*
* @copyright 2018 Silicon Laboratories Inc.
*/


/* Z-Wave includes */
#include <AppTimer.h>
#include <SwTimerLiaison.h>
#include <SizeOf.h>
#include <ZW_system_startup_api.h>
#include <ZAF_RetentionRegisterBank.h>
//#define DEBUGPRINT
#include "DebugPrint.h"

#include <FreeRTOS.h>
#include <task.h>

#include "ZAF_PM_Wrapper.h"

/**
 * Max number of application timers
 */
#define MAX_NUM_APP_TIMERS           12 // Max number of timers total. I.e. the sum of normal timers and persistent timers
#define MAX_NUM_PERSISTENT_APP_TIMERS 6 // Do not increase. We have 8 retention registers allocated for ZAF/App timers. And 2 are used for admin purpose


/**
 * First (zero based) retention register to use for persisting application
 * timers during EM4 sleep. Other retention registers used for EM4 persistent
 * app timers are defined as offsets from this value.
 */
#define FIRST_APP_TIMER_RETENTION_REGISTER        16

/** Retention register to use for persisting the task tick value at power down */
#define TASKTICK_AT_POWERDOWN_RETENTION_REGISTER  (FIRST_APP_TIMER_RETENTION_REGISTER + 0)

/**
 * Retention register to use for persisting the task tick value when the timer
 * values are saved to retention registers
 */
#define TASKTICK_AT_SAVETIMERS_RETENTION_REGISTER (FIRST_APP_TIMER_RETENTION_REGISTER + 1)

/**
 * First retention register to use for persisting the EM4 persistent application
 * timers during EM4 sleep. (actual number of registers used is determined by
 * how many times AppTimerEm4PersistentRegister() is called).
 */
#define TIMER_VALUES_BEGIN_RETENTION_REGISTER     (FIRST_APP_TIMER_RETENTION_REGISTER + 2)

/**
 * On wakeup from EM4, if the difference between expected timeout of an
 * EM4 persistent application timer and the elapsed time at wake up, is
 * smaller than this value then the timer callback will be activated.
 */
#define APP_TIMER_TRIGGER_DELTA_MS 10

/**
* AppTimer object
*/
typedef struct  SAppTimer
{
  SSwTimerLiaison TimerLiaison;                     /**<  TimerLiaison object for Application task */
  SSwTimer* aTimerPointerArray[MAX_NUM_APP_TIMERS]; /**<  Array for TimerLiaison - for keeping registered timers */
  bool Em4Persistent[MAX_NUM_APP_TIMERS];           /**<  Is timer persistent (persistent timers will be save/reloaded to/from retention registers during EM4 hibernate) */
  void (*pEm4Callback[MAX_NUM_APP_TIMERS])(SSwTimer* pTimer); /**< Holds the SSwTimer callback for EM4 persistent timers. It will be called by AppTimerEm4CallbackWrapper() */
} SAppTimer;


/**
* AppTimer is a singleton, thus containing own object.
*/
static SAppTimer g_AppTimer;

/**
 * Flag used to track if we have registered AppTimerSaveTaskTickAtSleep()
 * to be called at power down
 */
static bool g_PowerDownCallbackRegistered = false;


void AppTimerInit(uint8_t iTaskNotificationBitNumber, void * ReceiverTask)
{
  TimerLiaisonInit(    
                    &g_AppTimer.TimerLiaison,
                    sizeof_array(g_AppTimer.aTimerPointerArray),
                    g_AppTimer.aTimerPointerArray,
                    iTaskNotificationBitNumber,
                    (TaskHandle_t) ReceiverTask
                  );
}


bool AppTimerRegister(
                SSwTimer* pTimer,
                bool bAutoReload,
                void(*pCallback)(SSwTimer* pTimer)
              )
{
  ESwTimerLiaisonStatus status = TimerLiaisonRegister(&g_AppTimer.TimerLiaison,
                                                      pTimer,
                                                      bAutoReload,
                                                      pCallback);

  DPRINTF("AppTimerRegister() id=%d\n", pTimer->Id);

  // Do not fail if timer is already registered, just return
  if (status == ESWTIMERLIAISON_STATUS_ALREADY_REGISTRERED)
  {
    return true;
  }

  if (status == ESWTIMERLIAISON_STATUS_SUCCESS)
  {
    g_AppTimer.Em4Persistent[pTimer->Id] = false;
    g_AppTimer.pEm4Callback[pTimer->Id]  = NULL;
    return true;
  }

  return false;
}


/* This function will be called in the correct task context */
void AppTimerEm4CallbackWrapper(SSwTimer* pTimer)
{
  DPRINTF("AppTimerEm4CallbackWrapper timerId=%d\n", pTimer->Id);
  AppTimerEm4PersistentSaveAll();

  ASSERT(g_AppTimer.Em4Persistent[pTimer->Id] && g_AppTimer.pEm4Callback[pTimer->Id]);

  if (g_AppTimer.pEm4Callback[pTimer->Id])
  {
    DPRINTF("Calling g_AppTimer.pEm4Callback[%d] = %p\n", pTimer->Id, g_AppTimer.pEm4Callback[pTimer->Id]);
    (g_AppTimer.pEm4Callback[pTimer->Id])(pTimer);
  }
}


bool AppTimerEm4PersistentRegister(SSwTimer* pTimer,
                                   bool bAutoReload,
                                   void(*pCallback)(SSwTimer* pTimer))
{
  /* We don't support auto reload of Em4 persistent timers (at least it has
   * not been tested - it might actually work now) */
  ASSERT(false == bAutoReload);

  /* Check that we have a retention register available for this new persistent timer */
  uint32_t count = 0;
  for (uint32_t timerId = 0; timerId < MAX_NUM_APP_TIMERS; timerId++)
  {
    if (true == g_AppTimer.Em4Persistent[timerId])
    {
      count++;
    }
  }
  if (count >= MAX_NUM_PERSISTENT_APP_TIMERS)
  {
    /* All timer retention registers are taken */
    DPRINTF("AppTimerEm4PersistentRegister: Max number of registrations exceeded (%d)\n", MAX_NUM_PERSISTENT_APP_TIMERS);
    return false;
  }

  /* We register AppTimerEm4CallbackWrapper() as the call back in order to
   * update the timer status in retention registers when the timer expires.
   * The actual callback is saved to g_AppTimer.pEm4Callback and will be
   * called by AppTimerEm4CallbackWrapper() */
  ESwTimerLiaisonStatus status = TimerLiaisonRegister(&g_AppTimer.TimerLiaison,
                                                      pTimer,
                                                      bAutoReload,
                                                      AppTimerEm4CallbackWrapper);

  DPRINTF("AppTimerEm4PersistentRegister() id=%d pCallback=%p\n", pTimer->Id, pCallback);
  if (status == ESWTIMERLIAISON_STATUS_SUCCESS)
  {
    if (false == g_PowerDownCallbackRegistered)
    {
      /* Capture the task tick value just before going to sleep so we can
       * reload the EM4 persistent application timers after waker-up */
      ZAF_PM_SetPowerDownCallback(AppTimerSaveTaskTickAtSleep);
      g_PowerDownCallbackRegistered = true;
    }

    g_AppTimer.Em4Persistent[pTimer->Id] = true;
    g_AppTimer.pEm4Callback[pTimer->Id]  = pCallback;
    return true;
  }

  return false;
}


ESwTimerStatus AppTimerEm4PersistentStart(SSwTimer* pTimer, uint32_t iTimeout)
{
  DPRINTF("AppTimerEm4PersistentStart() id=%d, timeout=%u\n", pTimer->Id, iTimeout);
  ESwTimerStatus status = TimerStart(pTimer, iTimeout);
  AppTimerEm4PersistentSaveAll();
  return status;
}


ESwTimerStatus AppTimerEm4PersistentRestart(SSwTimer* pTimer)
{
  DPRINTF("AppTimerEm4PersistentRestart() id=%d\n", pTimer->Id);
  ESwTimerStatus status = TimerRestart(pTimer);
  AppTimerEm4PersistentSaveAll();
  return status;
}


ESwTimerStatus AppTimerEm4PersistentStop(SSwTimer* pTimer)
{
  DPRINTF("AppTimerEm4PersistentStop() id=%d\n", pTimer->Id);
  ESwTimerStatus status = TimerStop(pTimer);
  AppTimerEm4PersistentSaveAll();
  return status;
}


void AppTimerNotificationHandler(void)
{
  TimerLiaisonNotificationHandler(&g_AppTimer.TimerLiaison);
}


void AppTimerSetReceiverTask(void * ReceiverTask)
{
  TimerLiaisonSetReceiverTask(&g_AppTimer.TimerLiaison,
                              (TaskHandle_t) ReceiverTask);
}


uint32_t AppTimerGetFirstRetentionRegister(void)
{
  return FIRST_APP_TIMER_RETENTION_REGISTER;
}


uint32_t AppTimerGetLastRetentionRegister(void)
{
  uint32_t count = 0;
  for (uint32_t timerId = 0; timerId < MAX_NUM_APP_TIMERS; timerId++)
  {
    if (true == g_AppTimer.Em4Persistent[timerId])
    {
      count++;
    }
  }
  return TIMER_VALUES_BEGIN_RETENTION_REGISTER + count - 1;
}


void AppTimerEm4PersistentResetStorage(void)
{
  uint32_t first       = AppTimerGetFirstRetentionRegister();
  uint32_t last        = AppTimerGetLastRetentionRegister();
  uint32_t writeStatus = 0;

  DPRINTF("\nResetEm4PersistentAppTimerStorage first=%u, last=%ux\n", first, last);

  ASSERT(first < last);
  for (uint32_t reg = first; reg <= last; reg++)
  {
    writeStatus = ZAF_RetentionRegBank_WriteReg(reg, 0);
    ASSERT(0 == writeStatus);
  }
}

/*
 * How the EM4 persistent application timers are saved to RTCC retention registers
 *
 * For example the following list of APPLICATION TIMERS (contained in struct
 * g_AppTimer) is assumed (ordered by timer id)
 *
 * 0 (Em4Persistent = false)
 * 1 (Em4Persistent = false)
 * 2 (Em4Persistent = true) MsUntilTimeout=30000
 * 3 (Em4Persistent = true) MsUntilTimeout=0xFFFFFFFF (not active when saved)
 * 4 (Em4Persistent = false)
 * 5 (Em4Persistent = true) MsUntilTimeout=20000
 * 6 (Em4Persistent = false)
 * 7 (Em4Persistent = false)
 *
 * - Em4Persistent is the flag in g_AppTimer ("true" implies that the
 *   timer should be saved, and it also implies that the timer exist)
 *
 * - MsUntilTimeout is the calculated number of milliseconds remaining
 *   before the timer times out. If equal to 0xFFFFFFFF then the timer is
 *   not active.
 *
 * The RETENTION REGISTERS will only contain the timer values for the EM4
 * persistent timers plus the task tick values when the timer values were
 * saved and when the device is going to sleep in EM4:
 *
 * 0 TaskTick at power-down
 * 1 TaskTick at save timers
 * 2 timerValue_ms=30000
 * 3 timerValue_ms=0xFFFFFFFF
 * 4 timerValue_ms=20000
 *
 * When the device wakes up from EM4 the values in the retention registers
 * together with the time spent in EM4 hibernate are used to determine if a
 * timer has expired or what value should be used to start it again to have
 * it time out at the right moment relative to its original start time.
 */


void AppTimerEm4PersistentSaveAll(void)
{
  uint32_t reg = TIMER_VALUES_BEGIN_RETENTION_REGISTER;
  uint32_t writeStatus = 0;

  uint32_t taskTickCount = xTaskGetTickCount();
  writeStatus = ZAF_RetentionRegBank_WriteReg(TASKTICK_AT_SAVETIMERS_RETENTION_REGISTER, taskTickCount);
  ASSERT(0 == writeStatus);

  DPRINTF("AppTimerEm4PersistentSaveAll tick: %u\n", taskTickCount);

  for (uint32_t timerId = 0; timerId < MAX_NUM_APP_TIMERS; timerId++)
  {
    if (true == g_AppTimer.Em4Persistent[timerId])
    {
      SSwTimer *pTimer        = g_AppTimer.aTimerPointerArray[timerId];
      uint32_t  timerValue_ms = UINT32_MAX;

      TimerGetMsUntilTimeout(pTimer, taskTickCount, &timerValue_ms);

      DPRINTF("Saving value for timer %d: %u (0x%x) ms\n", timerId, timerValue_ms, timerValue_ms);

      writeStatus = ZAF_RetentionRegBank_WriteReg(reg, timerValue_ms);
      ASSERT(0 == writeStatus);
      reg++;
    }
  }
}


void AppTimerSaveTaskTickAtSleep(void)
{
  uint32_t taskTickCount = xTaskGetTickCount();

  /* Called while the scheduler is disabled just before being forced into
   * EM4 hibernate. If printing to serial line we need to delay the function
   * return to allow for the serial buffer content to be flushed */
#ifdef DEBUGPRINT
  DPRINTF("Saving task tick: %u\n", taskTickCount);
  for(int i=0; i < 2000; i++) __asm__("nop"); // Allow the serial line to flush before sleeping
#endif

  uint32_t writeStatus = ZAF_RetentionRegBank_WriteReg(TASKTICK_AT_POWERDOWN_RETENTION_REGISTER, taskTickCount);
  ASSERT(0 == writeStatus);
}


void AppTimerEm4PersistentLoadAll(EResetReason_t resetReason)
{
  uint32_t tickValueAtPowerDown  = 0;
  uint32_t tickValueAtSaveTimers = 0;
  uint32_t readStatus            = 0;
  uint8_t  timerId               = 0;
  uint8_t  valIdx                = 0;
  uint32_t savedTimerValue       = 0;
  uint32_t elapsedMsFromSaveTimerValuesToSleep = 0;
  uint32_t elapsedMsFromTimerValueSave         = 0;
  uint32_t durationDiffMs = 0;
  bool em4TimersStarted   = false;

  /* Do nothing if we did not wake up from EM4 */
  if (ERESETREASON_EM4_EXT_INT != resetReason && ERESETREASON_EM4_WUT != resetReason)
  {
    return;
  }

  if (true == IsWakeupCausedByRtccTimeout())
  {
    DPRINT("\nRTCC wakeup!\n");
  }

  /* Read the task tick values saved before sleeping in EM4 */
  readStatus = ZAF_RetentionRegBank_ReadReg(TASKTICK_AT_POWERDOWN_RETENTION_REGISTER,
                                        &tickValueAtPowerDown);
  ASSERT(0 == readStatus);
  DPRINTF("Loaded tickValueAtPowerDown: %u\n", tickValueAtPowerDown);

  readStatus = ZAF_RetentionRegBank_ReadReg(TASKTICK_AT_SAVETIMERS_RETENTION_REGISTER,
                                        &tickValueAtSaveTimers);
  ASSERT(0 == readStatus);
  DPRINTF("Loaded tickValueAtSaveTimers: %u\n", tickValueAtSaveTimers);

  if ((0 == tickValueAtPowerDown) || (0 == tickValueAtSaveTimers))
  {
    /* Retention registers are still at initial value - nothing to process now */
    return;
  }

  /* How many ms before power-down were the timer values saved to
   * retention registers? (NB: one tick = one millisecond) */
  if (tickValueAtPowerDown >= tickValueAtSaveTimers)
  {
    elapsedMsFromSaveTimerValuesToSleep = tickValueAtPowerDown - tickValueAtSaveTimers;
  }
  else
  {
    /* The 32-bit task tick has wrapped around
     * (VERY unlikely for a sleeping node) */
    elapsedMsFromSaveTimerValuesToSleep = (UINT32_MAX - tickValueAtSaveTimers) + tickValueAtPowerDown;
  }

  /* How many ms since the timer values were saved, including the
   * time spent sleeping */
  elapsedMsFromTimerValueSave = elapsedMsFromSaveTimerValuesToSleep +
                                GetCompletedSleepDurationMs();

  DPRINTF("elapsedMsFromTimerValueSave=%u\n", elapsedMsFromTimerValueSave);

  /* Read saved timer values from retention registers into array
   * while looking for smallest value larger than savedBeforePowerdownMs */
  for (timerId = 0; timerId < MAX_NUM_APP_TIMERS; timerId++)
  {
    if (true == g_AppTimer.Em4Persistent[timerId])
    {
      readStatus = ZAF_RetentionRegBank_ReadReg(TIMER_VALUES_BEGIN_RETENTION_REGISTER + valIdx,
                                            &savedTimerValue);
      ASSERT(0 == readStatus);
      if (0 == readStatus)
      {
        SSwTimer *pTimer = g_AppTimer.aTimerPointerArray[timerId];

        DPRINTF("Loaded value for timer %d: %u ms\n", timerId, savedTimerValue);

        /* We don't expect any timer to expire before power down without being restarted */
        ASSERT(savedTimerValue > elapsedMsFromSaveTimerValuesToSleep);

        /* How close is the timer to its expire time? */
        if (savedTimerValue > elapsedMsFromTimerValueSave)
        {
          durationDiffMs = savedTimerValue - elapsedMsFromTimerValueSave;
        }
        else
        {
          //Time is past expiration. Make sure the callback is called.
          durationDiffMs = 0;
        }

        DPRINTF("durationDiffMs=%u\n", durationDiffMs);

        /* If the timer timeout is within APP_TIMER_TRIGGER_DELTA_MS milliseconds
         * of the wakeup time - no matter if the wakeup was caused by an RTCC
         * timeout or e.g. pin interrupt - we simply activate its callback now.
         * (A 10 ms difference means the timeout is so close to the wake-up event
         * that the timer could run out before the task tick and scheduler is
         * started. In any case, for fast repeating timers (if any), we would
         * never get here anyway since we only enter EM4 hibernate if we are
         * expected to sleep for at least 4000 ms (see enterPowerDown())
         */
        if (durationDiffMs < APP_TIMER_TRIGGER_DELTA_MS)
        {
          DPRINTF("Timer %d has expired. Activating callback.\n", timerId);

          /* Activate the callback for the expired timer (for EM4 persistent timer
           * this will call the wrapper AppTimerEm4CallcackWrapper that will call
           * AppTimerEm4PersistentSaveAll and the actual callback)
           */
          TimerLiaisonExpiredTimerCallback(pTimer);
        }
        else
        {
          /* Reduce all saved timer values (for active timers that have not yet expired) by
           * number of milliseconds elapsed since it was last saved. Then start the timer
           * with this new value.
           */
          if ((UINT32_MAX != savedTimerValue) && (elapsedMsFromTimerValueSave < savedTimerValue))
          {
            uint32_t newTimerValue = savedTimerValue - elapsedMsFromTimerValueSave;
            DPRINTF("Setting timer %d to %u ms\n", timerId, newTimerValue);
            /* We call TimerStart() here instead of AppTimerEm4PersistentStart()
             * to avoid AppTimerEm4PersistentSaveAll() being called multiple
             * times. Instead we call AppTimerEm4PersistentSaveAll() once for
             * all (if needed) outside the loop */
            ESwTimerStatus timerStatus = TimerStart(pTimer, newTimerValue);
            ASSERT(ESWTIMER_STATUS_SUCCESS == timerStatus);
            em4TimersStarted = true;
          }
        }
      }
      valIdx++; // Only increment when we have processed an EM4 persistent timer
    }
  }

  if (true == em4TimersStarted)
  {
    /* One or more EM4 persistent timers were started. Update the retention
     * registers.
     */
    AppTimerEm4PersistentSaveAll();
  }
}

void AppTimerStopAll(void)
{
  /*Stops all timers */
  for (uint32_t i = 0; i < g_AppTimer.TimerLiaison.iTimerCount; i ++)
  {
    if (g_AppTimer.Em4Persistent[i])
    {
      AppTimerEm4PersistentStop(g_AppTimer.aTimerPointerArray[i]);
    }
    else
    {
      TimerStop(g_AppTimer.aTimerPointerArray[i]);
    }
  }
}
