/**
 * Z-Wave Certified Application Sensor PIR
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "zw_config_rf.h"
#include <stdbool.h>
#include <stdint.h>

#include "SizeOf.h"
#include "Assert.h"
#include <MfgTokens.h>
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "config_app.h"
#include <ZAF_file_ids.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZW_slave_api.h>
#include <ZW_classcmd.h>
#include <ZW_TransportLayer.h>

#include <ev_man.h>
#include <AppTimer.h>
#include <string.h>
#include <SwTimer.h>
#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>

#include <CC_AssociationGroupInfo.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_Basic.h>
#include <CC_FirmwareUpdate.h>

#include <CC_Battery.h>
#include "cc_notification_config_api.h"

#include <CC_Supervision.h>
#include <CC_WakeUp.h>
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>
#include <zaf_config_api.h>
#include <zaf_config.h>
#include "zaf_config_security.h"
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include <ZAF_network_management.h>
#include <ZAF_TSE.h>
#include <ota_util.h>
#include <ZAF_CmdPublisher.h>
#include "events.h"
#include "zw_region_config.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <SensorPIR_hw.h>
#include <board_indicator.h>
#include <board_init.h>

#include "SensorPIR_UserTask_DataAcquisition.h"  // This module encapsulates an entire task!
#include <ZW_UserTask.h>

#include "zw_build_no.h"
#include "ZAF_ApplicationEvents.h"
#include <zaf_event_distributor_soc.h>
#include <agi.h>
#include <cc_agi_config_api.h>

/****************************************************************************/
/* CONFIGURATION                                                            */
/****************************************************************************/

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

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static zpal_pm_handle_t radio_power_lock;

/**
* Set up security keys to request when joining a network.
* These are taken from the config_app.h header file.
*/
static const uint8_t SecureKeysRequested = ZAF_CONFIG_REQUESTED_SECURITY_KEYS;

static const SAppNodeInfo_t AppNodeInfo =
{
  .DeviceOptionsMask = ZAF_CONFIG_DEVICE_OPTION_MASK,
  .NodeType.generic = ZAF_CONFIG_GENERIC_TYPE,
  .NodeType.specific = ZAF_CONFIG_SPECIFIC_TYPE,
};

static SRadioConfig_t RadioConfig =
{
  .iListenBeforeTalkThreshold = ELISTENBEFORETALKTRESHOLD_DEFAULT,
  .iTxPowerLevelMax = APP_MAX_TX_POWER,
  .iTxPowerLevelAdjust = APP_MEASURED_0DBM_TX_POWER,
  .iTxPowerLevelMaxLR = APP_MAX_TX_POWER_LR,
  .eRegion = ZW_REGION,
  .radio_debug_enable = ENABLE_RADIO_DEBUG
};

static const SProtocolConfig_t ProtocolConfig = {
  .pVirtualSlaveNodeInfoTable = NULL,
  .pSecureKeysRequested = &SecureKeysRequested,
  .pNodeInfo = &AppNodeInfo,
  .pRadioConfig = &RadioConfig
};

static const AGI_PROFILE lifelineProfile = {
    ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL,
    ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE
};

static uint8_t supportedEvents = NOTIFICATION_EVENT_HOME_SECURITY_MOTION_DETECTION_UNKNOWN_LOCATION;

static uint8_t basicValue = 0x00;

// Timer
static SSwTimer EventJobsTimer;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

/* True Status Engine (TSE) variables */
static s_CC_indicator_data_t ZAF_TSE_localActuationIdentifyData = {
  .rxOptions = {
    .rxStatus = 0,          /* rxStatus, verified by the TSE for Multicast */
    .securityKey = 0,       /* securityKey, ignored by the TSE */
    .sourceNode = {0,0,0},  /* sourceNode (nodeId, endpoint), verified against lifeline destinations by the TSE */
    .destNode = {0,0,0}     /* destNode (nodeId, endpoint), verified by the TSE for local endpoint */
  },
  .indicatorId = 0x50      /* Identify Indicator*/
};

/****************************************************************************/
/*                         Thread related variable                          */
/****************************************************************************/

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

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
void ZCB_BattReportSentDone(TRANSMISSION_RESULT * pTransmissionResult);
void ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult);
void ApplicationTask(SApplicationHandles* pAppHandles);

void ZCB_EventJobsTimer(SSwTimer *pTimer);

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(EResetReason_t eResetReason)
{
  UNUSED(eResetReason);

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
#endif // DEBUGPRINT

  DPRINT("\n\n-----------------------------\n");
  DPRINT("Z-Wave Sample App: Sensor PIR\n");
  DPRINTF("\r\nSDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);

  DPRINTF("\r\nApplicationInit eResetReason = %d", eResetReason);

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig.eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig.eRegion);
  }

  /*************************************************************************************
   * CREATE USER TASKS  -  ZW_ApplicationRegisterTask() and ZW_UserTask_CreateTask()
   *************************************************************************************
   * Register the main APP task function.
   *
   * ATTENTION: This function is the only task that can call ZAF aPI functions!!!
   * Failure to follow guidelines will result in undefined behavior.
   *
   * This function further is the only way to register Event Notification Bit Numbers
   * for associating to given event handlers.
   *
   * ZW_UserTask_CreateTask() can be used to create additional tasks.
   * @see SensorPIR_MultiThread example for more info.
   *************************************************************************************/
  bool bWasTaskCreated = ZW_ApplicationRegisterTask(
                                                    ApplicationTask,
                                                    EAPPLICATIONEVENT_ZWRX,
                                                    EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
                                                    &ProtocolConfig
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

static void doRemainingInitialization()
{
  EResetReason_t resetReason = GetResetReason();


  /* Check the battery level.
   * If required, go to TRANSMIT state to send the report to the lifeline.
   * The Battery Report must be sent out before the WakeUp Notification. Therefore this function
   * must called prior to anything CC Wakeup related.
   */
  if (true == cc_battery_check_level_changed())
  {
    if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB))  // Create a notification to check the job list!
    {
      DPRINT("\r\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
    }
    else
    {
      ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BATTERY_LEVEL_REPORT);
    }
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
    SensorPIR_hw_deep_sleep_wakeup_handler();
  }

  if(ERESETREASON_PIN == resetReason ||
     ERESETREASON_BROWNOUT == resetReason ||
     ERESETREASON_POWER_ON == resetReason ||
     ERESETREASON_SOFTWARE == resetReason ||
     ERESETREASON_WATCHDOG == resetReason)
  {
    /* Init state machine*/
    ZAF_EventHelperEventEnqueue(EVENT_EMPTY);
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

}

/**
 * Send battery level report
 */
bool ReportBatteryLevel(void)
{
  DPRINT("\r\nSending battery level report\r\n");

  // Battery level has changed. Send a new update to the lifeline
  if (!CC_Battery_LevelReport_tx(&lifelineProfile, ENDPOINT_ROOT, ZCB_BattReportSentDone))
  {
    DPRINTF("\r\n%s: TX FAILED ** \r\n", __func__);
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
    return false;
  }

  return true;
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  DPRINT("\r\nSensorPIR Main App/Task started! \n");

  g_pAppHandles = pAppHandles;

  ZAF_Init(&ProtocolConfig, xTaskGetCurrentTaskHandle(), pAppHandles);

  /* Make sure to call AppTimerDeepSleepPersistentRegister() _after_ ZAF_Init().
   * It will access the app handles */
  AppTimerDeepSleepPersistentRegister(&EventJobsTimer, false, ZCB_EventJobsTimer);  // register for event jobs timeout event

  radio_power_lock = zpal_pm_register(ZPAL_PM_TYPE_USE_RADIO);

  zaf_event_distributor_init();

  SensorPIR_hw_init();

  doRemainingInitialization();

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);
  cc_firmware_update_send_status_report();
  CC_WakeUp_send_first_notification();

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
  const AGI_GROUP* agiTableRootDeviceGroups = cc_agi_get_rootdevice_groups();

  switch (event) {
    case EVENT_APP_BUTTON_BATTERY_REPORT:
      /* BATTERY REPORT EVENT received. Send a battery level report */
      DPRINT("\r\nBattery Level report transmit (keypress trig)\r\n");
      if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB)) {
        DPRINT("\r\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
      }

      /*Add event's on job-queue*/
      ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BATTERY_LEVEL_REPORT);
      break;
    case EVENT_APP_SEND_BATTERY_LEVEL_REPORT:
      ReportBatteryLevel();
      break;
    case EVENT_APP_NEXT_EVENT_JOB:
    {
      uint8_t event;
      /*check job-queue*/
      if (true == ZAF_JobHelperJobDequeue(&event)) {
        /*Let the event scheduler fire the event on state event machine*/
        ZAF_EventHelperEventEnqueue(event);
      }
      break;
    }
    case EVENT_APP_BASIC_START_JOB:
      if (JOB_STATUS_SUCCESS != CC_Basic_Set_tx(&agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, BASIC_SET_TRIGGER_VALUE, true, ZCB_JobStatus)) {
        DPRINT("\r\nEVENT_APP_BASIC_START_JOB failed");
        basicValue = BASIC_SET_TRIGGER_VALUE;
        /*Kick next job*/
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    case EVENT_APP_BASIC_STOP_JOB:
      if (JOB_STATUS_SUCCESS != CC_Basic_Set_tx(&agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, 0, true, ZCB_JobStatus)) {
        DPRINT("\r\nEVENT_APP_BASIC_STOP_JOB failed");
        basicValue = 0;
        /*Kick next job*/
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    case EVENT_APP_NOTIFICATION_START_JOB:
    {
      DPRINT("\r\nEVENT_APP_NOTIFICATION_START_JOB");
      // Index of notification to be triggered in notifications array
      uint8_t notification_index = 0;
      if (JOB_STATUS_SUCCESS
          != CC_Notification_TriggerAndTransmit(notification_index,
                                                supportedEvents,
                                                NULL,
                                                0,
                                                ZCB_JobStatus,
                                                false)) {
        /*Kick next job*/
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    }
    case EVENT_APP_NOTIFICATION_STOP_JOB:
    {
      DPRINT("\r\nEVENT_APP_NOTIFICATION_STOP_JOB");
      // Index of notification to be triggered in notifications array
      uint8_t notification_index = 0;
      if (JOB_STATUS_SUCCESS
          != CC_Notification_TriggerAndTransmit(notification_index,
                                                NOTIFICATION_EVENT_HOME_SECURITY_NO_EVENT,
                                                &supportedEvents,
                                                1,
                                                ZCB_JobStatus,
                                                false)) {
        /*Kick next job*/
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    }
    case EVENT_APP_START_TIMER_EVENTJOB_STOP:
      DPRINT("\r\n#EVENT_APP_START_TIMER_EVENTJOB_STOP\r\n");
      AppTimerDeepSleepPersistentStart(&EventJobsTimer, BASIC_SET_TIMEOUT);
      break;
    case EVENT_APP_TRANSITION_TO_ACTIVE:
      zpal_pm_stay_awake(radio_power_lock, 0);
      DPRINT("\r\n");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n      *!*!*       PIR EVENT ACTIVE       *!*!*");
      DPRINT("\r\n      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*");
      DPRINT("\r\n");
      if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB)) {
        DPRINT("\r\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
      }
      /*Add event's on job-queue*/
      ZAF_JobHelperJobEnqueue(EVENT_APP_BASIC_START_JOB);
      ZAF_JobHelperJobEnqueue(EVENT_APP_NOTIFICATION_START_JOB);
      ZAF_JobHelperJobEnqueue(EVENT_APP_START_TIMER_EVENTJOB_STOP);
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
    case EVENT_SYSTEM_LEARNMODE_FINISHED:
      //Make sure that the application stays awake for 10 s after learn mode finished
      //to wait for more messages from the controller
      CC_WakeUp_stayAwake10s();

      /* Also tell application to automatically extend the stay awake period by 10
       * seconds on message activities - even though we did not get here by a proper
       * wakeup from Deep Sleep
       */
      CC_WakeUp_AutoStayAwakeAfterInclusion();

      // Start the wakeup timer if the learn mode operation finished in Included state
      if (EINCLUSIONSTATE_EXCLUDED != g_pAppHandles->pNetworkInfo->eInclusionState) {
        CC_WakeUp_startWakeUpNotificationTimer();
      }
      /* fall through */
    case EVENT_SYSTEM_LEARNMODE_STOP:
      /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
      if (!Board_IsIndicatorActive()) {
        CC_Indicator_RefreshIndicatorProperties();
      }
      ZAF_TSE_Trigger(CC_Indicator_report_stx,
                      (void *)&ZAF_TSE_localActuationIdentifyData,
                      true);
      break;
    default:
      break;
  }
}

/**
 * @brief Callback function used for unsolicited commands.
 * @param pTransmissionResult Result of each transmission.
 */
void
ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINT("Callback: ZCB_JobStatus()");
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  }
}

void
zaf_nvm_app_set_default_configuration(void)
{
  // TODO: Move it to CC Reset once ZAF_Init is moved into Application Task Context
  CC_WakeUp_notificationMemorySetDefault();
}

void 
zaf_nvm_app_reset(void)
{
  AppTimerDeepSleepPersistentResetStorage();
}

/**
 * @brief Callback function used when sending battery report.
 * This function will be called when the report is send!
 */
void
ZCB_BattReportSentDone(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINTF("\r\n%d  %d  %d ", pTransmissionResult->nodeId, pTransmissionResult->status, pTransmissionResult->isFinished);
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    DPRINT("\r\nBattery level report transmit finished\r\n");
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  }
}

/**
 * @brief event jobs timeout event
 *
 * @param pTimer Timer connected to this method
 */
void
ZCB_EventJobsTimer(SSwTimer *pTimer)
{
  DPRINTF("\r\nTimer callback: ZCB_EventJobsTimer() pTimer->Id=%d", pTimer->Id);

  /* If the node has been woken up from Deep Sleep because the event job timer timed out
   * the app will now be in the state STATE_APP_STARTUP. Need to switch to
   * STATE_APP_TRANSMIT_DATA to properly process the job events
   */
  ZAF_JobHelperJobEnqueue(EVENT_APP_NOTIFICATION_STOP_JOB);
  ZAF_JobHelperJobEnqueue(EVENT_APP_BASIC_STOP_JOB);
  ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);

  UNUSED(pTimer);
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. SensorPIR_hw.c.
 */
ZW_WEAK void SensorPIR_hw_init(void)
{

}

ZW_WEAK void SensorPIR_hw_deep_sleep_wakeup_handler(void)
{

}
