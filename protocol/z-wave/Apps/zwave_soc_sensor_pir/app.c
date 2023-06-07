/**
 * Z-Wave Certified Application Sensor PIR
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#include <stdbool.h>
#include <stdint.h>
#include "Assert.h"
#include "MfgTokens.h"
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "AppTimer.h"
#include "ZW_system_startup_api.h"
#include "CC_Basic.h"
#include "CC_Battery.h"
#include "CC_Notification.h"
#include "cc_notification_config_api.h"
#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "ZAF_network_learn.h"
#include "ZAF_network_management.h"
#include "events.h"
#include "zpal_watchdog.h"
#include "app_hw.h"
#include "board_indicator.h"
#include "SensorPIR_UserTask_DataAcquisition.h"
#include "ZAF_ApplicationEvents.h"
#include "zaf_event_distributor_soc.h"
#include "cc_agi_config_api.h"
#include "zpal_misc.h"
#include "zw_build_no.h"
#include "zaf_protocol_config.h"
#include "ZW_TransportEndpoint.h"
#ifdef DEBUGPRINT
#include "ZAF_PrintAppInfo.h"
#endif

/*****************************************************
 * Set this macro to create a multi-threaded
 * application example! - This feature add a separate
 * UserTask to run with this application.
 * Place any code with external output in the separate
 * user-task file along side this application.
 *
 * Creating a user task will lead to increased power
 * consumption so if it is not needed it should be
 * disabled.
 *
 * Disable: 0
 * Enable:  1
 ****************************************************/
#define CREATE_USER_TASK          0

/**
 * The value basic set command should use when an event occur.
 */
#define BASIC_SET_TRIGGER_VALUE   (0xFF)
/**
 * The timeout value in milli seconds that used when sending basic set command due to an event
 */
#define BASIC_SET_TIMEOUT         10000

static zpal_pm_handle_t radio_power_lock;

static uint8_t supportedEvents = NOTIFICATION_EVENT_HOME_SECURITY_MOTION_DETECTION_UNKNOWN_LOCATION;

// Timer
static SSwTimer EventJobsTimer;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

/********************************
 * Data Acquisition Task
 *******************************/
#if CREATE_USER_TASK
#define TASK_STACK_SIZE_DATA_ACQUISITION           1000  // [bytes]

static TaskHandle_t m_xTaskHandleDataAcquisition   = NULL;

// Task and stack buffer allocation for the default/main application task!
static StaticTask_t DataAcquisitionTaskBuffer;
static uint8_t      DataAcquisitionStackBuffer[TASK_STACK_SIZE_DATA_ACQUISITION];
#endif //CREATE_USER_TASK

void ApplicationTask(SApplicationHandles* pAppHandles);

void ZCB_EventJobsTimer(SSwTimer *pTimer);

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(EResetReason_t eResetReason)
{
  SRadioConfig_t* RadioConfig;

  UNUSED(eResetReason);

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
  DebugPrintf("ApplicationInit eResetReason = %d\n", eResetReason);
#endif // DEBUGPRINT

  RadioConfig = zaf_get_radio_config();

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig->eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig->eRegion);
  }

  /*************************************************************************************
   * CREATE USER TASKS  -  ZW_ApplicationRegisterTask() and ZW_UserTask_CreateTask()
   *************************************************************************************
   * Register the main APP task function.
   *
   * ATTENTION: This function is the only task that can call ZAF API functions!!!
   * Failure to follow guidelines will result in undefined behavior.
   *
   * Furthermore, this function is the only way to register Event Notification
   * Bit Numbers for associating to given event handlers.
   *
   * ZW_UserTask_CreateTask() can be used to create additional tasks.
   * @see zwave_soc_sensor_pir example for more info.
   *************************************************************************************/
  bool bWasTaskCreated = ZW_ApplicationRegisterTask(
                                                    ApplicationTask,
                                                    EAPPLICATIONEVENT_ZWRX,
                                                    EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
                                                    zaf_get_protocol_config()
                                                    );
  ASSERT(bWasTaskCreated);

  /*****************************************************
   * This is an multi-threaded application example!
   *
   * This next section creates the additional threads
   * by using ZW_UserTask.h API.
   *
   * If a multi-threaded application is not needed,
   * this next section can be removed by setting the
   * macro CREATE_USER_TASK to zero.
   ****************************************************/
#if CREATE_USER_TASK

  // Create the buffer bundle!
  ZW_UserTask_Buffer_t mainAppTaskBuffer;
  mainAppTaskBuffer.taskBuffer = &DataAcquisitionTaskBuffer;
  mainAppTaskBuffer.stackBuffer = DataAcquisitionStackBuffer;
  mainAppTaskBuffer.stackBufferLength = TASK_STACK_SIZE_DATA_ACQUISITION;

  // Create the task setting-structure!
  ZW_UserTask_t task;
  task.pTaskFunc = (TaskFunction_t)SensorPIR_DataAcquisitionTask;
  task.pTaskName = "DataAcqu";
  task.pUserTaskParam = NULL;  // We pass nothing here, as the EventHelper is already initialized and can be used for task IPC!
  task.priority = USERTASK_PRIORITY_HIGHEST;  // The difficult example is with the HIGHEST priority.
  task.taskBuffer = &mainAppTaskBuffer;

  // Create the task!
  ZW_UserTask_CreateTask(&task, &m_xTaskHandleDataAcquisition);

#endif //CREATE_USER_TASK

  return(APPLICATION_RUNNING);
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  EResetReason_t resetReason;

  DPRINT("\r\nSensorPIR Main App/Task started! \n");

  ZAF_Init(xTaskGetCurrentTaskHandle(), pAppHandles);

#ifdef DEBUGPRINT
  ZAF_PrintAppInfo();
#endif

  app_hw_init();

  /* Make sure to call AppTimerDeepSleepPersistentRegister() _after_ ZAF_Init().
   * It will access the app handles */
  AppTimerDeepSleepPersistentRegister(&EventJobsTimer, false, ZCB_EventJobsTimer);  // register for event jobs timeout event

  radio_power_lock = zpal_pm_register(ZPAL_PM_TYPE_USE_RADIO);

  resetReason = GetResetReason();

  /* Check the battery level.
   * If required, go to TRANSMIT state to send the report to the lifeline.
   * The Battery Report must be sent out before the WakeUp Notification. Therefore this function
   * must called prior to anything CC Wakeup related.
   */
  if (true == cc_battery_check_level_changed())
  {
    zaf_event_distributor_enqueue_app_event(EVENT_APP_BATTERY_REPORT);
  }

  /* Re-load and process Deep Sleep persistent application timers.
   * NB: Before calling AppTimerDeepSleepPersistentLoadAll here all
   *     application timers must have been been registered with
   *     AppTimerRegister() or AppTimerDeepSleepPersistentRegister().
   *     Essentially it means that all CC handlers must be
   *     initialized first.
   */
  AppTimerDeepSleepPersistentLoadAll(resetReason);

  if (ERESETREASON_DEEP_SLEEP_EXT_INT == resetReason)
  {
    app_hw_deep_sleep_wakeup_handler();
  }

  /**
   * Set the maximum inclusion request interval for SmartStart.
   * Valid range 0 and 5-99. 0 is default value and corresponds to 512 sec.
   * The range 5-99 corresponds to 640-12672sec in units of 128sec/tick in between.
   */
  ZAF_SetMaxInclusionRequestIntervals(0);

  if(ERESETREASON_DEEP_SLEEP_EXT_INT != resetReason)
  {
    /* Enter SmartStart*/
    /* Protocol will commence SmartStart only if the node is NOT already included in the network */
    ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);
  }

  DPRINTF("\r\nIsWakeupCausedByRtccTimeout=%s", (IsWakeupCausedByRtccTimeout()) ? "true" : "false");
  DPRINTF("\r\nCompletedSleepDurationMs   =%u", GetCompletedSleepDurationMs());

  // Wait for and process events
  DPRINT("\r\nSensorPIR Event processor Started\n");
  for (;;)
  {
    if (!zaf_event_distributor_distribute())
    {
      return;
    }
  }
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of zaf_event_distributor_app_event_manager.
 */
void
zaf_event_distributor_app_event_manager(const uint8_t event)
{
  DPRINTF("zaf_event_distributor_app_event_manager Ev: 0x%02x\r\n", event);
  cc_agi_group_t const * const agiTableRootDeviceGroups = cc_agi_get_rootdevice_groups();

  switch (event) {
    case EVENT_APP_BATTERY_REPORT:
      /* BATTERY REPORT EVENT received. Send a battery level report */
      DPRINT("\r\nBattery Level report transmit\n");
      (void) CC_Battery_LevelReport_tx(NULL, ENDPOINT_ROOT, NULL);
      break;
    case EVENT_APP_TRANSITION_TO_ACTIVE:
      zpal_pm_stay_awake(radio_power_lock, 0);
      DPRINT("\r\n");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n      *!*!*       PIR EVENT ACTIVE       *!*!*");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n");

      (void) CC_Basic_Set_tx(&agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, BASIC_SET_TRIGGER_VALUE, true, NULL);
      (void) CC_Notification_TriggerAndTransmit(0,
                                                supportedEvents,
                                                NULL,
                                                0,
                                                NULL,
                                                false);
      (void) AppTimerDeepSleepPersistentStart(&EventJobsTimer, BASIC_SET_TIMEOUT);
      break;
    case EVENT_APP_TRANSITION_TO_DEACTIVE:
      DPRINT("\r\n");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n      *!*!*      PIR EVENT INACTIVE      *!*!*");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n");
      zpal_pm_cancel(radio_power_lock);
      break;
    case EVENT_APP_USERTASK_DATA_ACQUISITION_READY:
      DPRINT("\r\nMainApp: Data Acquisition UserTask started and ready!");
      break;
    case EVENT_APP_USERTASK_DATA_ACQUISITION_FINISHED:
      DPRINT("MainApp: Data Acquisition UserTask finished!\r\n");
      break;
    default:
      break;
  }
}

void 
zaf_nvm_app_reset(void)
{
  AppTimerDeepSleepPersistentResetStorage();
}

/**
 * @brief event jobs timeout event
 *
 * @param pTimer Timer connected to this method
 */
void
ZCB_EventJobsTimer(SSwTimer *pTimer)
{
  UNUSED(pTimer);

  cc_agi_group_t const * const agiTableRootDeviceGroups = cc_agi_get_rootdevice_groups();

  DPRINTF("\r\nTimer callback: ZCB_EventJobsTimer() pTimer->Id=%d", pTimer->Id);

  /* If the node has been woken up from Deep Sleep because the event job timer timed out
   * the app will now be in the state STATE_APP_STARTUP. Need to switch to
   * STATE_APP_TRANSMIT_DATA to properly process the job events
   */
  (void) CC_Notification_TriggerAndTransmit(0,
                                            NOTIFICATION_EVENT_HOME_SECURITY_NO_EVENT,
                                            &supportedEvents,
                                            1,
                                            NULL,
                                            false);
  (void) CC_Basic_Set_tx(&agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, 0, true, NULL);
}
