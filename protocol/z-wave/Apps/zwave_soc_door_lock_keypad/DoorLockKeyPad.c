/**
 * Z-Wave Certified Application Door Lock Key Pad
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "zw_config_rf.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "SizeOf.h"
#include "Assert.h"
#include <MfgTokens.h>
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "DebugPrintConfig.h"
#include "config_app.h"
#include <ZAF_file_ids.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>
#include <ZW_slave_api.h>
#include <ZW_typedefs.h>
#include <ZW_classcmd.h>
#include <ZW_TransportLayer.h>

#include <ev_man.h>
#include <AppTimer.h>
#include <SwTimer.h>

#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>

#include <CC_Basic.h>
#include <CC_AssociationGroupInfo.h>
#include <CC_DeviceResetLocally.h>
#include <CC_DoorLock.h>
#include <CC_Indicator.h>
#include <CC_UserCode.h>
#include <cc_user_code_config.h>
#include <CC_Battery.h>
#include <CC_Supervision.h>
#include <CC_FirmwareUpdate.h>
#include <zaf_config_api.h>
#include <zaf_config.h>
#include <zaf_config_flirs.h>
#include "zaf_config_security.h"
#include <string.h>

#include "zaf_event_helper.h"
#include "zaf_job_helper.h"

#include <ZAF_Common_helper.h>
#include "ZAF_Common_interface.h"
#include <ZAF_network_learn.h>
#include <ota_util.h>
#include "ZAF_TSE.h"
#include <ZAF_CmdPublisher.h>
#include "events.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <board_indicator.h>
#include <board_init.h>
#include <DoorLockKeyPad_hw.h>
#include "zw_region_config.h"
#include "zw_build_no.h"
#include "ZAF_ApplicationEvents.h"
#include <zaf_event_distributor_soc.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

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

extern cc_door_lock_data_t myDoorLock;

/**
 * Setup AGI lifeline profile
 */
AGI_PROFILE lifelineProfile = {ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL,
                               ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE};

/**
 * Used by the Supervision Get handler. Holds RX options.
 */
static RECEIVE_OPTIONS_TYPE_EX rxOptionSupervision;

/**
 * Used by the Supervision Get handler. Holds Supervision session ID.
 */
static uint8_t sessionID;

// Timer
static SSwTimer SupervisionTimer;
#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

/* TSE variables */
/* Door Lock CC has a command returning WORKING, the application needs a timer for this */
static SSwTimer ZAF_TSE_operation_report_ActivationTimer;
s_CC_doorLock_data_t ZAF_TSE_doorLockData;
/* Keep an array of "working" stage endpoints */
static bool doorlock_in_working_state;
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

/**
* TSE simulated RX option for local change addressed to the Root Device
* All applications can use this variable when triggering the TSE after
* a local / non Z-Wave initiated change
*/
static RECEIVE_OPTIONS_TYPE_EX zaf_tse_local_actuation = {
    .rxStatus = 0,        /* rxStatus, verified by the TSE for Multicast */
    .securityKey = 0,     /* securityKey, ignored by the TSE */
    .sourceNode = {0,0,0},/* sourceNode (nodeId, endpoint), verified against lifeline destinations by the TSE */
    .destNode = {0,0,0}   /* destNode (nodeId, endpoint), verified by the TSE for local endpoint */
};

/* Interval for checking and reporting battery status (in minutes) */
#define PERIODIC_BATTERY_CHECKING_INTERVAL_MINUTES 5

static SSwTimer BatteryCheckTimer;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

void ZCB_BattReportSentDone(TRANSMISSION_RESULT * pTransmissionResult);
void ApplicationTask(SApplicationHandles* pAppHandles);
void ZCB_CommandClassSupervisionGetReceived(SUPERVISION_GET_RECEIVED_HANDLER_ARGS * pArgs);
void ZCB_SupervisionTimerCallback(SSwTimer *pTimer);
void ZAF_TSE_operation_report_ActivationTimerCallback(SSwTimer *pTimer);
void ZCB_BatteryCheckTimerCallback(SSwTimer *pTimer);

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS ApplicationInit(EResetReason_t eResetReason)
{
  UNUSED(eResetReason);

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
#endif

  DPRINT("\n\n-----------------------------------\n");
  DPRINT("Z-Wave Sample App: Door Lock Keypad\n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);


  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig.eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig.eRegion);
  }

  DPRINTF("Rf region: %d\n", RadioConfig.eRegion);
  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);

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

  return(APPLICATION_RUNNING);
}

/**
 * A pointer to this function is passed to ZW_ApplicationRegisterTask() making it the FreeRTOS
 * application task.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  g_pAppHandles = pAppHandles;

  ZAF_Init(&ProtocolConfig, xTaskGetCurrentTaskHandle(), pAppHandles);

  AppTimerRegister(&SupervisionTimer, false, ZCB_SupervisionTimerCallback);
  /* TSE initializations */
  AppTimerRegister(&ZAF_TSE_operation_report_ActivationTimer,false,ZAF_TSE_operation_report_ActivationTimerCallback);
  /* Timer for periodic battery level checking */
  AppTimerRegister(&BatteryCheckTimer, true, ZCB_BatteryCheckTimerCallback);
  TimerStart(&BatteryCheckTimer, PERIODIC_BATTERY_CHECKING_INTERVAL_MINUTES * 60 * 1000);

  zaf_event_distributor_init();

  DoorLockKeyPad_hw_init();

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  cc_firmware_update_send_status_report();

  // Wait for and process events
  DPRINT("DoorLockKeyPad Event processor Started\r\n");
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
  DPRINTF("zaf_event_distributor_app_event_manager Ev: %d\r\n", event);

  switch (event) {
    case EVENT_APP_SEND_BATTERY_LEVEL_REPORT:
    {
      if (!CC_Battery_LevelReport_tx(&lifelineProfile, ENDPOINT_ROOT, ZCB_BattReportSentDone)) {
        DPRINT("\r\n** CC_Battery TX FAILED ** \r\n");
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
    }
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
    case EVENT_APP_BUTTON_BATTERY_REPORT:
      DPRINT("\r\nBattery Level report transmit (keypress trig)\r\n");

      if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB)) {
        DPRINT("\r\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
      }

      /*Add event's on job-queue*/
      ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BATTERY_LEVEL_REPORT);
      break;
    case EVENT_APP_PERIODIC_BATTERY_CHECK_TRIGGER:
      /* Check the battery level and send a report to lifeline if required */
      if (cc_battery_check_level_changed()) {
        /*Add event's on job-queue*/
        ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BATTERY_LEVEL_REPORT);
      }

      if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB)) {
        DPRINT("\r\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
      }
      break;
    case EVENT_APP_BUTTON_ENTER_USER_CODE:
      /*
       * Pressing the Enter User Code button simulates entering a user code
       * on a key pad.
       * The entered user code is hardcoded with the value of the default user
       * code of the application. Hence, the lock can be secured/unsecured by
       * default.
       *
       * If the user code for user ID 1 is changed to something else than the
       * default user code the lock can no longer be secured/unsecured by
       * pressing the button.
       */
      DPRINT("\r\nUser code entered!\r\n");

      uint8_t userCode[] = CC_USER_CODE_DEFAULT;
      if (CC_UserCode_Validate(1, userCode, sizeof(userCode))) {
        DPRINT("\r\nValid user code!\r\n");

        CC_DoorLock_Toggle();

        /* Update the lifeline destinations when the door status has changed */
        void* pData = CC_Doorlock_prepare_zaf_tse_data(&zaf_tse_local_actuation);
        ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, pData, true);
      }
      break;
    case EVENT_APP_DOORHANDLE_ACTIVATED:
    {
      /* Outside door handle #1 activated? */
      CC_DoorLock_SetOutsideDoorHandleState(DOOR_HANDLE_1);
      /* Update the lifeline destinations when the door status has changed */
      void* pData = CC_Doorlock_prepare_zaf_tse_data(&zaf_tse_local_actuation);
      ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, pData, true);
      break;
    }
    case EVENT_APP_DOORHANDLE_DEACTIVATED:
    {
      /* Outside door handle #1 deactivated? */
      CC_DoorLock_ClearOutsideDoorHandleState(DOOR_HANDLE_1);
      /* Update the lifeline destinations when the door status has changed */
      void* pData = CC_Doorlock_prepare_zaf_tse_data(&zaf_tse_local_actuation);
      ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx, pData, true);
      break;
    }
    case EVENT_SYSTEM_LEARNMODE_STOP:
    case EVENT_SYSTEM_LEARNMODE_FINISHED:
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
 * @brief Callback function used when sending battery report.
 */
void
ZCB_BattReportSentDone(TRANSMISSION_RESULT * pTransmissionResult)
{
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    DPRINT("\r\nBattery level report transmit finished\r\n");
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  }
}

void cc_supervision_get_received_handler(SUPERVISION_GET_RECEIVED_HANDLER_ARGS * pArgs)
{
  ZCB_CommandClassSupervisionGetReceived(pArgs);
}

/**
 * Handles Supervision Get commands sent to this node.
 *
 * The purpose of Supervision is to inform the source node (controller) when the door lock
 * operation is finished. Since this application does not run on in a real door lock and therefore
 * has no door lock hardware, a timer is implemented to show how Supervision can be used. This timer
 * represents the physical bolt of a door lock.
 * The first Supervision report will be transmitted automatically by the ZAF, but transmission
 * of the next report(s) must be handled by the application.
 *
 * When receiving a Supervision Get, this handler will be invoked. For this specific application
 * only a Door Lock Operation Set is a special case. The function will change the Supervision
 * status to be 'working'. A timer is then started and when it triggers, it will send another
 * Supervision Report with the status of 'done'.
 *
 * In the case of other commands than Door Lock Operation Set, the application must make sure that
 * the 'more status updates' field in properties1 are set to zero indicating that no more status
 * updates will be sent.
 */
void
ZCB_CommandClassSupervisionGetReceived(SUPERVISION_GET_RECEIVED_HANDLER_ARGS * pArgs)
{
  if ((DOOR_LOCK_OPERATION_SET_V2 == pArgs->cmd && COMMAND_CLASS_DOOR_LOCK_V2 == pArgs->cmdClass) ||
      (BASIC_SET_V2 == pArgs->cmd && COMMAND_CLASS_BASIC_V2 == pArgs->cmdClass)) // Basic Set mimics Door Lock Operation Set
  {
    /* Status for DOOR_LOCK_OPERATION_SET_V2 or BASIC_SET_V2 */
    pArgs->status = CC_SUPERVISION_STATUS_WORKING;
    pArgs->duration = 2;

    if(true == CC_SUPERVISION_EXTRACT_STATUS_UPDATE(pArgs->properties1))
    {
      if (TimerIsActive(&SupervisionTimer))
      {
        // The timer is active. It means we have a WORKING session pending from previous Supervision Get command.
        // Complete that session first. By stopping the timer and manually calling the timer callback function.
        TimerStop(&SupervisionTimer);
        ZCB_SupervisionTimerCallback(NULL);
      }

      // Save the data
      rxOptionSupervision = *(pArgs->rxOpt);
      sessionID = CC_SUPERVISION_EXTRACT_SESSION_ID(pArgs->properties1);

      pArgs->properties1 = CC_SUPERVISION_ADD_MORE_STATUS_UPDATE(CC_SUPERVISION_MORE_STATUS_UPDATES_REPORTS_TO_FOLLOW);
      /*We need first to assign the sessionid to uint16_t variable then typecast it to uint8_t due to -Werror=conversion*/
      uint16_t val = CC_SUPERVISION_ADD_SESSION_ID(sessionID);
      pArgs->properties1 |= (uint8_t)val;
      // Start timer which will send another Supervision report when triggered.
      DPRINT("\r\n*** CC_SUPERVISION_STATUS_UPDATES_SUPPORTED\r\n");

      TimerStart(&SupervisionTimer, 2 * 1000);
    }
  }
  else
  {
    /* Status for all other commands */
    pArgs->properties1 &= (CC_SUPERVISION_ADD_MORE_STATUS_UPDATE(CC_SUPERVISION_MORE_STATUS_UPDATES_THIS_IS_LAST) | 0x7F);
    pArgs->duration = 0;
  }
}


/**
 * @brief Transmits a Supervision report.
 * @details This function is triggered by the timer set in the Supervision Get handler.
 * @param pTimer Timer object assigned to this function
 */
void
ZCB_SupervisionTimerCallback(SSwTimer *pTimer)
{
  TRANSMIT_OPTIONS_TYPE_SINGLE_EX * pTxOptions;
  RxToTxOptions(&rxOptionSupervision, &pTxOptions);
  CmdClassSupervisionReportSend(
      pTxOptions,
      CC_SUPERVISION_ADD_MORE_STATUS_UPDATE(CC_SUPERVISION_MORE_STATUS_UPDATES_THIS_IS_LAST) | CC_SUPERVISION_ADD_SESSION_ID(sessionID),
      CC_SUPERVISION_STATUS_SUCCESS,
      0);
  UNUSED(pTimer);
}

/**
 * @brief This function triggers the TSE after a WORKING status for
 * the Door Lock Operation Set handler
 * @param pTimer SSwTimer pointer that triggered the callback
 */
void
ZAF_TSE_operation_report_ActivationTimerCallback(SSwTimer *pTimer)
{
  if (&ZAF_TSE_operation_report_ActivationTimer != pTimer)
  {
    DPRINTF("%s(): Call with wrong SSwTimer pointer. Ignoring\n\r", __func__);
    return ;
  }
  /* Find out if we have been in the working state and need a TSE trigger */
  if (true == doorlock_in_working_state)
  {
    /* Start a TSE trigger for the Door Lock Operation Report */
    if (true == ZAF_TSE_Trigger(CC_DoorLock_operation_report_stx,
                                (void*)&ZAF_TSE_doorLockData,
                                true))
    {
      /* If successful, mark the Endpoint as handled. Else just wait for the next callback and retry */
      doorlock_in_working_state = false;
    }
  }
}

/**
 * @brief Timer function for periodic battery level checking
 * @param pTimer Timer object assigned to this function
 */
void
ZCB_BatteryCheckTimerCallback(SSwTimer *pTimer)
{
  UNUSED(pTimer);

  /* Send a battery level report to the lifeline  */
  if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_PERIODIC_BATTERY_CHECK_TRIGGER))
  {
    DPRINT("\r\n** Periodic battery checking trigger FAILED\r\n");
  }
}

/**
 * This function is used to notify the Application that the CC Door Lock Operation Set
 * status is in a WORKING state. The application can subsequently make the TSE Trigger
 * using the information passed on from the rxOptions.
 * @param rxOption pointer used to when triggering the "working state"
*/
void CC_DoorLock_operation_report_notifyWorking(RECEIVE_OPTIONS_TYPE_EX *pRxOpt)
{
  /* Pick up the end point and reset previous RxOptions data.
  Here treat each endpoint differently if they do not map to the same command */
  CC_Doorlock_prepare_zaf_tse_data(pRxOpt);

  /* Set a flag to remember we have been in the Working state */
  doorlock_in_working_state= true;

  /* If the status is working, the application is in charge of making the TSE trigger
  at the proper time. Start a timer to callback the TSE Trigger at a later stage */
  TimerStart(&ZAF_TSE_operation_report_ActivationTimer, 5*1000);
}

/**
 * Prepare the data input for the TSE for any Door Lock CC command based on the pRxOption pointer.
 * @param pRxOpt pointer used to indicate how the frame was received (if any) and what endpoints are affected
*/
void* CC_Doorlock_prepare_zaf_tse_data(RECEIVE_OPTIONS_TYPE_EX* pRxOpt)
{
  /* Here we ignore the pRxOpt->destNode.endpoint since we have only the root device */
  memset(&ZAF_TSE_doorLockData, 0, sizeof(s_CC_doorLock_data_t));
  ZAF_TSE_doorLockData.rxOptions = *pRxOpt;

  return &ZAF_TSE_doorLockData;
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. DoorLockKeyPad_hw.c.
 */
ZW_WEAK void DoorLockKeyPad_hw_init(void)
{

}
