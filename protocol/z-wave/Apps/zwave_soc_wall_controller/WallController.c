/**
 * Z-Wave Certified Application Wall Controller
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
/* During development of your device, you may add features using command    */
/* classes which are not already included. Remember to include relevant     */
/* classes and utilities and add them in your make file.                    */
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
#include <SwTimer.h>
#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>
#include <CC_AssociationGroupInfo.h>
#include <CC_Basic.h>
#include <CC_CentralScene.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_MultilevelSwitch_Control.h>
#include <CC_FirmwareUpdate.h>
#include <zaf_config_api.h>
#include <zaf_config.h>
#include "zaf_config_security.h"
#include <ZW_TransportMulticast.h>
#include "zaf_event_helper.h"
#include "zaf_job_helper.h"
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include <ZAF_TSE.h>
#include <ota_util.h>
#include <ZAF_CmdPublisher.h>
#include "events.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <WallController_hw.h>
#include <board_indicator.h>
#include <board_init.h>
#include "zw_region_config.h"
#include "zw_build_no.h"
#include "ZAF_ApplicationEvents.h"
#include <zaf_event_distributor_soc.h>
#include <cc_association_config.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef enum {
  KEY01,
  KEY02,
  KEY03,
  NUMBER_OF_KEYS
} key_id_t;


typedef enum
{
  KEY_EVENT_SHORT_PRESS,
  KEY_EVENT_HOLD,
  KEY_EVENT_UP
} key_event_t;


#define EVENT_APP_CC_NO_JOB 0xFF

/**
 * Application states. Function zaf_event_distributor_app_event_manager(..) includes the state
 * event machine.
 */
typedef enum
{
  STATE_APP_IDLE,
  STATE_APP_STARTUP,
  STATE_APP_AWAIT_KEYPRESS,          // Unused
  STATE_APP_LEARN_MODE,
  STATE_APP_GET_NEXT_NODE,           // Unused
  STATE_APP_INITIATE_TRANSMISSION,   // Unused
  STATE_APP_AWAIT_TRANSMIT_CALLBACK, // Unused
  STATE_APP_RESET,
  STATE_APP_TRANSMIT_DATA
} STATE_APP;

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


typedef struct _NEXT_JOB_Q_
{
  agi_profile_t profile;
} NEXT_JOB_Q;

/**
 * Holds the latest button action.
 * The action is used to distinguish between which action to perform:
 * - Press    => Switch on/off
 * - Hold     => Start dimming
 * - Release  => Stop dimming
 */
static key_event_t keyEventGlobal;
static uint8_t centralSceneNumberHold;
static uint8_t centralSceneKeyAttributeHold;

static ESwTimerStatus centralSceneHoldTimerStatus = ESWTIMER_STATUS_FAILED;
// Timer
static SSwTimer CentralSceneHoldTimer;

static CCMLS_PRIMARY_SWITCH_T multiLevelDirection[NUMBER_OF_KEYS] = {CCMLS_PRIMARY_SWITCH_DOWN, CCMLS_PRIMARY_SWITCH_DOWN, CCMLS_PRIMARY_SWITCH_DOWN};
static uint8_t buttonStates[NUMBER_OF_KEYS] = {0, 0, 0};
static key_id_t m_button;
static NEXT_JOB_Q nextJob;

static bool isTxInProgress = false;
static bool isThereCentralScenePendingJob = false;

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
/*                              EXPORTED DATA                               */
/****************************************************************************/

// No exported data.

/****************************************************************************/
/* PRIVATE FUNCTION PROTOTYPES                                              */
/****************************************************************************/

void ApplicationTask(SApplicationHandles* pAppHandles);
static void PrepareAGITransmission(uint8_t profile, key_id_t nextActiveButton);
static JOB_STATUS InitiateTransmission(void);
void ZCB_TransmitCallback(TRANSMISSION_RESULT * pTransmissionResult);
static void InitiateCentralSceneTX(uint8_t keyAttribute, uint8_t sceneNumber);
static void ZCB_CentralSceneHoldTimerCallback(SSwTimer *pTimer);

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
#endif

  DPRINT("\n\n----------------------------------\n");
  DPRINT("Z-Wave Sample App: Wall Controller\n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);

  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);
  isTxInProgress = false;
  isThereCentralScenePendingJob = false;
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

  AppTimerRegister(&CentralSceneHoldTimer, true, ZCB_CentralSceneHoldTimerCallback);

  zaf_event_distributor_init();

  WallController_hw_init();

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  cc_firmware_update_send_status_report();

  // Wait for and process events
  DPRINT("WallController Event processor Started\r\n");
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

  switch(event) {
      /**************************************************************************************
       * KEY 1
       *************************************************************************************/
    case EVENT_APP_BUTTON_KEY01_SHORT_PRESS:
      DPRINT("\r\nK1SHORT_PRESS\r\n");
      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      centralSceneNumberHold = 1;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);
      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY01_HOLD:
      DPRINT("\r\nK1HOLD\r\n");
      keyEventGlobal = KEY_EVENT_HOLD;
      centralSceneNumberHold = 1;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY01_RELEASE:
      if (keyEventGlobal == KEY_EVENT_HOLD) {
        DPRINT("\r\nK1UP\r\n");
        keyEventGlobal = KEY_EVENT_UP;
        centralSceneNumberHold = 1;
        centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2;

        ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);
        PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY01, KEY01);
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;

      /**************************************************************************************
       * KEY 2
       *************************************************************************************/

    case EVENT_APP_BUTTON_KEY02_SHORT_PRESS:
      DPRINT("\r\nK2SHORT_PRESS\r\n");
      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      centralSceneNumberHold = 2;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY02_HOLD:
      DPRINT("\r\nK2HOLD\r\n");
      keyEventGlobal = KEY_EVENT_HOLD;
      centralSceneNumberHold = 2;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY02_RELEASE:
      if (keyEventGlobal == KEY_EVENT_HOLD) {
        DPRINT("\r\nK2UP\r\n");
        keyEventGlobal = KEY_EVENT_UP;
        centralSceneNumberHold = 2;
        centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2;

        ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

        PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY02, KEY02);
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;

      /**************************************************************************************
       * KEY 3
       *************************************************************************************/

    case EVENT_APP_BUTTON_KEY03_SHORT_PRESS:
      DPRINT("\r\nK3SHORT_PRESS\r\n");
      keyEventGlobal = KEY_EVENT_SHORT_PRESS;
      centralSceneNumberHold = 3;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_PRESSED_1_TIME_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY03_HOLD:
      DPRINT("\r\nK3HOLD\r\n");
      keyEventGlobal = KEY_EVENT_HOLD;
      centralSceneNumberHold = 3;
      centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_HELD_DOWN_V2;

      ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);

      PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      break;

    case EVENT_APP_BUTTON_KEY03_RELEASE:
      if (keyEventGlobal == KEY_EVENT_HOLD) {
        DPRINT("\r\nK3UP\r\n");
        keyEventGlobal = KEY_EVENT_UP;
        centralSceneNumberHold = 3;
        centralSceneKeyAttributeHold = CENTRAL_SCENE_NOTIFICATION_KEY_ATTRIBUTES_KEY_RELEASED_V2;

        ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);
        PrepareAGITransmission(ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL_KEY03, KEY03);
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    case EVENT_APP_NEXT_EVENT_JOB:
    {
      uint8_t event;
      if (true == ZAF_JobHelperJobDequeue(&event)) {
        /*
         * If we were able to dequeue an event from the job queue, let's process it right away
         * by adding it to the event queue.
         */
        ZAF_EventHelperEventEnqueue(event);
      }
      break;
    }
    case EVENT_APP_CENTRAL_SCENE_JOB:
      if (KEY_EVENT_HOLD == keyEventGlobal) {
        if (ESWTIMER_STATUS_FAILED == centralSceneHoldTimerStatus) {
          // Start the timer only if it's not started already.
            centralSceneHoldTimerStatus = TimerStart(&CentralSceneHoldTimer, ( 0 == cc_central_scene_get_configuration() ) ? 200 : 55000);
        }
      } else if (KEY_EVENT_UP == keyEventGlobal) {
        if (ESWTIMER_STATUS_FAILED != centralSceneHoldTimerStatus) {
          TimerStop(&CentralSceneHoldTimer);
          centralSceneHoldTimerStatus = ESWTIMER_STATUS_FAILED;
        }
      }
      if (true == isTxInProgress) {
        isThereCentralScenePendingJob = true;
      } else {
        isTxInProgress = true;
        isThereCentralScenePendingJob = false;
        InitiateCentralSceneTX(centralSceneKeyAttributeHold, centralSceneNumberHold);
      }
      break;

    case EVENT_APP_CC_BASIC_JOB:
      DPRINT("\r\nEVENT_APP_CC_BASIC_JOB");
      if(JOB_STATUS_SUCCESS != CC_Basic_Set_tx( &nextJob.profile, ENDPOINT_ROOT, buttonStates[m_button], true, ZCB_TransmitCallback))
      {
        DPRINT("\r\nEVENT_APP_CC_BASIC_JOB failed!\r\n");
        ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
      }
      break;
    case EVENT_APP_CC_SWITCH_MULTILEVEL_JOB:
    {
      JOB_STATUS jobStatus = InitiateTransmission();
      DPRINT("\r\nEVENT_APP_CC_SWITCH_MULTILEVEL_JOB");
      if (JOB_STATUS_SUCCESS != jobStatus)
      {
        TRANSMISSION_RESULT transmissionResult = {0, 0, TRANSMISSION_RESULT_FINISHED};
        DPRINT("\r\nCC_SWITCH_MULTILEVEL ERROR");
        ZCB_TransmitCallback(&transmissionResult);
      }
      break;
    }
    case EVENT_SYSTEM_LEARNMODE_FINISHED:
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
      // Do nothing.
      break;
  }
}

/**
 * @brief Prepares the transmission of commands stored in the AGI table.
 *
 * @param profile The profile key.
 * @param srcEndpoint The source endpoint.
 */
static void
PrepareAGITransmission(
        uint8_t profile,
        key_id_t nextActiveButton)
{
  DPRINTF("\r\nPrepareAGITransmission %d", keyEventGlobal);

  nextJob.profile.profile_MS = ASSOCIATION_GROUP_INFO_REPORT_PROFILE_CONTROL;
  nextJob.profile.profile_LS = profile;

  m_button = nextActiveButton;
  if (KEY_EVENT_SHORT_PRESS == keyEventGlobal)
  {
    ZAF_JobHelperJobEnqueue(EVENT_APP_CC_BASIC_JOB);
    if (0xFF == buttonStates[m_button])
    {
      /*
       * If button is on, turn device off.
       */
      buttonStates[m_button] = 0x00;
      DPRINT("\r\nBasic OFF");
    }
    else
    {
      /*
       * If button is off, turn device on.
       */
      buttonStates[m_button] = 0xFF;
      DPRINT("\r\nBasic ON");
    }
  }
  else if (KEY_EVENT_HOLD == keyEventGlobal)
  {
    DPRINT("\r\npre EVENT_APP_CC_SWITCH_MULTILEVEL_JOB");
    ZAF_JobHelperJobEnqueue(EVENT_APP_CC_SWITCH_MULTILEVEL_JOB);
    if (CCMLS_PRIMARY_SWITCH_UP == multiLevelDirection[m_button])
    {
      multiLevelDirection[m_button] = CCMLS_PRIMARY_SWITCH_DOWN;
    }
    else
    {
      multiLevelDirection[m_button] = CCMLS_PRIMARY_SWITCH_UP;
    }
  }
  else if (KEY_EVENT_UP == keyEventGlobal)
  {
    DPRINT("\r\npre BUTTON_UP EVENT_APP_CC_SWITCH_MULTILEVEL_JOB");
    ZAF_JobHelperJobEnqueue(EVENT_APP_CC_SWITCH_MULTILEVEL_JOB);
  }
}

/**
 * Initiates a Central Scene Notification to the lifeline.
 * We don't care about the result, since we have to proceed no matter what.
 * Therefore a callback function is called in any case.
 * @param keyAttribute The key attribute in action.
 * @param sceneNumber The scene in action.
 */
static void InitiateCentralSceneTX(uint8_t keyAttribute, uint8_t sceneNumber)
{
  agi_profile_t lifelineProfile = {
      ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_NA_V2,
      ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE
  };

  JOB_STATUS jobStatus = CommandClassCentralSceneNotificationTransmit(
          &lifelineProfile,
          ENDPOINT_ROOT,
          keyAttribute,
          sceneNumber,
          ZCB_TransmitCallback);

  if (JOB_STATUS_SUCCESS != jobStatus)
  {
    TRANSMISSION_RESULT transmissionResult;
    transmissionResult.nodeId = 0;
    transmissionResult.status = TRANSMIT_COMPLETE_FAIL;
    transmissionResult.isFinished = TRANSMISSION_RESULT_FINISHED;
    DPRINT("\r\nLL failure");
    ZCB_TransmitCallback(&transmissionResult);
  }
  else
  {
    DPRINT("\r\nLL success");
  }
}


/**
 * @brief Processes the transmission to related nodes.
 * @return Status of the job.
 */
static JOB_STATUS
InitiateTransmission(void)
{
  DPRINTF("\r\n### ITrans %d", keyEventGlobal);
  if (KEY_EVENT_HOLD == keyEventGlobal)
  {
    DPRINT("\r\n### Multilevel TX.Change");

    return CmdClassMultilevelSwitchStartLevelChange(
                &nextJob.profile,
                ENDPOINT_ROOT,
                ZCB_TransmitCallback,
                multiLevelDirection[m_button],
                CCMLS_IGNORE_START_LEVEL_TRUE,
                CCMLS_SECONDARY_SWITCH_NO_INC_DEC,
                0,
                2,
                0);
  }
  else if (KEY_EVENT_UP == keyEventGlobal)
  {
    DPRINT("\r\n### Multilevel Stop level change");
    return CmdClassMultilevelSwitchStopLevelChange(
                &nextJob.profile,
                ENDPOINT_ROOT,
                ZCB_TransmitCallback);
  }
  return JOB_STATUS_BUSY;
}

/**
 * @brief Callback function setting the application state.
 * @details Sets the application state when done transmitting.
 * @param pTransmissionResult Result of each transmission.
 */
void
ZCB_TransmitCallback(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINTF("\r\nTX CB for N %d: %d", pTransmissionResult->nodeId, pTransmissionResult->status);
  isTxInProgress = false;
  if(true == isThereCentralScenePendingJob)
  {
    ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);
  }
    if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished) {
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  }
}

void
ZCB_CentralSceneHoldTimerCallback(SSwTimer *pTimer)
{
  ZAF_JobHelperJobEnqueue(EVENT_APP_CENTRAL_SCENE_JOB);
  ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  UNUSED(pTimer);
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. WallController_hw.c.
 */
ZW_WEAK void WallController_hw_init(void)
{

}
