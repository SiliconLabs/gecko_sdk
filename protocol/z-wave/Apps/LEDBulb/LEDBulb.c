/**
 * Z-Wave Certified Application LED Bulb
 *
 * @copyright 2020 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include "zw_config_rf.h"
#include <stdbool.h>
#include <stdint.h>
#include "SizeOf.h"
#include "Assert.h"
#include <SWO_Debug.h>
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "config_app.h"
#include "ZAF_app_version.h"
#include <ZAF_file_ids.h>
#include "nvm3.h"
#include "ZAF_nvm3_app.h"
#include <em_system.h>
#include <ZW_slave_api.h>
#include <ZW_classcmd.h>
#include <ZW_TransportLayer.h>
#include <ZAF_uart_utils.h>
#include <string.h>
#include <ev_man.h>
#include <board.h>
#include <AppTimer.h>
#include <SwTimer.h>
#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>
#include <association_plus.h>
#include <agi.h>
#include <CC_Association.h>
#include <CC_AssociationGroupInfo.h>
#include <CC_Basic.h>
#include <CC_ColorSwitch.h>
#include <CC_MultilevelSwitch_Support.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_MultiChanAssociation.h>
#include <CC_PowerLevel.h>
#include <CC_Supervision.h>
#include <CC_Version.h>
#include <CC_ZWavePlusInfo.h>
#include <CC_FirmwareUpdate.h>
#include <CC_ManufacturerSpecific.h>
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>
#include <ZAF_Common_helper.h>
#include <ZAF_network_learn.h>
#include <ota_util.h>
#include <ZAF_TSE.h>
#include <ZAF_CmdPublisher.h>
#include <em_wdog.h>
#include <ZAF_network_management.h>
#include "events.h"
#include "zw_region_config.h"

#include <sl_simple_rgb_pwm_led.h>

#include "zw_build_no.h"

/****************************************************************************/
/* Application specific button and LED definitions                          */
/****************************************************************************/

/**
 * The default dimming duration is used if a received CC Multilevel Switch Set or Start Level Change
 * command contains no duration. This typically applies for older devices that do not support
 * the latest Multilevel Switch command class.
 */
#define CC_MULTILEVEL_SWITCH_DEFAULT_DIMMING_DURATION 1 // 1 second

#if defined(BUILDING_WITH_UC)
#include "sl_simple_rgb_pwm_led_instances.h"
#else

#include "sl_simple_rgb_pwm_led_led_config.h"

sl_led_pwm_t red_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_RED_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_RED_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_RED_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_RED_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_RED_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_RED_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_led_pwm_t green_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_GREEN_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_GREEN_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_led_pwm_t blue_led = {
  .port = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_PORT,
  .pin = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_PIN,
  .polarity = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_POLARITY,
  .channel = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_CHANNEL,
#if defined(SL_SIMPLE_RGB_PWM_LED_LED_BLUE_LOC)
  .location = SL_SIMPLE_RGB_PWM_LED_LED_BLUE_LOC,
#endif
  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

sl_simple_rgb_pwm_led_context_t simple_rgb_pwm_led_context = {
  .red = &red_led,
  .green = &green_led,
  .blue = &blue_led,

  .timer = SL_SIMPLE_RGB_PWM_LED_LED_PERIPHERAL,
  .frequency = SL_SIMPLE_RGB_PWM_LED_LED_FREQUENCY,
  .resolution = SL_SIMPLE_RGB_PWM_LED_LED_RESOLUTION,
};

const sl_led_rgb_pwm_t sl_led = {
  .led_common.context = &simple_rgb_pwm_led_context,
  .led_common.init = sl_simple_rgb_pwm_led_init,
  .led_common.turn_on = sl_simple_rgb_pwm_led_turn_on,
  .led_common.turn_off = sl_simple_rgb_pwm_led_turn_off,
  .led_common.toggle = sl_simple_rgb_pwm_led_toggle,
  .led_common.get_state = sl_simple_rgb_pwm_led_get_state,
  .set_rgb_color = sl_simple_rgb_pwm_led_set_color,
  .get_rgb_color = sl_simple_rgb_pwm_led_get_color,
};

#endif // BUILDING_WITH_UC

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/**
 * Application states. Function AppStateManager(..) includes the state
 * event machine.
 */
typedef enum _STATE_APP_
{
  STATE_APP_STARTUP,
  STATE_APP_IDLE,
  STATE_APP_LEARN_MODE,
  STATE_APP_RESET,
} STATE_APP;

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListNonSecureNotIncluded[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_SWITCH_COLOR_V3,
  COMMAND_CLASS_SWITCH_MULTILEVEL_V4,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION_V2,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE_V2,
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_SECURITY,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_SUPERVISION,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListNonSecureIncludedSecure[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE_V2,
  COMMAND_CLASS_SECURITY,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_SUPERVISION
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListSecure[] =
{
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_SWITCH_COLOR_V3,
  COMMAND_CLASS_SWITCH_MULTILEVEL_V4,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION_V2,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5
};

/**
 * Structure includes application node information list's and device type.
 */
app_node_information_t m_AppNIF =
{
  cmdClassListNonSecureNotIncluded, sizeof(cmdClassListNonSecureNotIncluded),
  cmdClassListNonSecureIncludedSecure, sizeof(cmdClassListNonSecureIncludedSecure),
  cmdClassListSecure, sizeof(cmdClassListSecure),
  DEVICE_OPTIONS_MASK, {GENERIC_TYPE, SPECIFIC_TYPE}
};


/**
* Set up security keys to request when joining a network.
* These are taken from the config_app.h header file.
*/
static const uint8_t SecureKeysRequested = REQUESTED_SECURITY_KEYS;

/**
 * Set up PowerDownDebug
 */
static const EPowerDownDebug PowerDownDebug = APP_POWERDOWNDEBUG;

static const SAppNodeInfo_t AppNodeInfo =
{
  .DeviceOptionsMask = DEVICE_OPTIONS_MASK,
  .NodeType.generic = GENERIC_TYPE,
  .NodeType.specific = SPECIFIC_TYPE,
  .CommandClasses.UnSecureIncludedCC.iListLength = sizeof_array(cmdClassListNonSecureNotIncluded),
  .CommandClasses.UnSecureIncludedCC.pCommandClasses = cmdClassListNonSecureNotIncluded,
  .CommandClasses.SecureIncludedUnSecureCC.iListLength = sizeof_array(cmdClassListNonSecureIncludedSecure),
  .CommandClasses.SecureIncludedUnSecureCC.pCommandClasses = cmdClassListNonSecureIncludedSecure,
  .CommandClasses.SecureIncludedSecureCC.iListLength = sizeof_array(cmdClassListSecure),
  .CommandClasses.SecureIncludedSecureCC.pCommandClasses = cmdClassListSecure
};

static const SRadioConfig_t RadioConfig =
{
  .iListenBeforeTalkThreshold = ELISTENBEFORETALKTRESHOLD_DEFAULT,
  .iTxPowerLevelMax = APP_MAX_TX_POWER,
  .iTxPowerLevelAdjust = APP_MEASURED_0DBM_TX_POWER,
  .iTxPowerLevelMaxLR = APP_MAX_TX_POWER_LR,
  .eRegion = ZW_REGION,
  .enablePTI = ENABLE_PTI
};

static const SProtocolConfig_t ProtocolConfig = {
  .pVirtualSlaveNodeInfoTable = NULL,
  .pSecureKeysRequested = &SecureKeysRequested,
  .pPowerDownDebug = &PowerDownDebug,
  .pNodeInfo = &AppNodeInfo,
  .pRadioConfig = &RadioConfig
};

/**************************************************************************************************
 * Configuration for Z-Wave Plus Info CC
 **************************************************************************************************
 */
static const SCCZWavePlusInfo CCZWavePlusInfo = {
                               .pEndpointIconList = NULL,
                               .roleType = APP_ROLE_TYPE,
                               .nodeType = APP_NODE_TYPE,
                               .installerIconType = APP_ICON_TYPE,
                               .userIconType = APP_USER_ICON_TYPE
};

/**
 * Application state-machine state.
 */
static STATE_APP currentState = STATE_APP_IDLE;

static TaskHandle_t g_AppTaskHandle;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

// Prioritized events that can wakeup protocol thread.
typedef enum EApplicationEvent
{
  EAPPLICATIONEVENT_TIMER = 0,
  EAPPLICATIONEVENT_ZWRX,
  EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
  EAPPLICATIONEVENT_APP
} EApplicationEvent;

static void EventHandlerZwRx(void);
static void EventHandlerZwCommandStatus(void);
static void EventHandlerApp(void);

// Event distributor object
static SEventDistributor g_EventDistributor;

// Event distributor event handler table
static const EventDistributorEventHandler g_aEventHandlerTable[4] =
{
  AppTimerNotificationHandler,  // Event 0
  EventHandlerZwRx,
  EventHandlerZwCommandStatus,
  EventHandlerApp
};

#define APP_EVENT_QUEUE_SIZE 5

/**
 * The following four variables are used for the application event queue.
 */
static SQueueNotifying m_AppEventNotifyingQueue;
static StaticQueue_t m_AppEventQueueObject;
static EVENT_APP eventQueueStorage[APP_EVENT_QUEUE_SIZE];
static QueueHandle_t m_AppEventQueue;

/* True Status Engine (TSE) variables */
/* Indicate here which End Points (including root device) support each command class */
static s_CC_indicator_data_t ZAF_TSE_localActuationIdentifyData = {
  .rxOptions = {
    .rxStatus = 0,          /* rxStatus, verified by the TSE for Multicast */
    .securityKey = 0,       /* securityKey, ignored by the TSE */
    .sourceNode = {0,0},    /* sourceNode (nodeId, endpoint), verified against lifeline destinations by the TSE */
    .destNode = {0,0}       /* destNode (nodeId, endpoint), verified by the TSE for local endpoint */
  },
  .indicatorId = 0x50      /* Identify Indicator*/
};

static nvm3_Handle_t* pFileSystemApplication;

/**
 * Color Switch CC data. Supported colors in the app.
 * This app supports RED, GREEN, BLUE
 */
// callbacks called after the change takes place (for example LED changed intensity from 5% to 15%)
void callback_RED(s_colorComponent * colorComponent);
void callback_GREEN(s_colorComponent * colorComponent);
void callback_BLUE(s_colorComponent * colorComponent);

// Array of all colors supported by the app
static s_colorComponent s_colorComponents[] = {
  {
    .ep = 0,
    .colorId = ECOLORCOMPONENT_RED,
    .cb = callback_RED,
  },
  {
    .ep = 0,
    .colorId = ECOLORCOMPONENT_GREEN,
    .cb = callback_GREEN,
  },
  {
    .ep = 0,
    .colorId = ECOLORCOMPONENT_BLUE,
    .cb = callback_BLUE,
  }
};

#define COLOR_SWITCH_DEFAULT_DURATION_SEC 2

cc_multilevel_switch_t multilevel_switch = {
                                            .endpoint = 0 // Root device
};

static uint8_t multilevel_switch_max;
static uint8_t color_switch_max;

void multilevel_switch_handler(cc_multilevel_switch_t * p_switch);

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
void DeviceResetLocallyDone(TRANSMISSION_RESULT * pTransmissionResult);
void DeviceResetLocally(void);
STATE_APP GetAppState(void);
void AppStateManager(EVENT_APP event);
static void ChangeState(STATE_APP newState);
static void ApplicationTask(SApplicationHandles* pAppHandles);
bool LoadConfiguration(void);
void SetDefaultConfiguration(void);
void AppResetNvm(void);

#if defined(DEBUGPRINT) && defined(BUILDING_WITH_UC)
#include "sl_iostream.h"
static void DebugPrinter(const uint8_t * buffer, uint32_t len)
{
  sl_iostream_write(SL_IOSTREAM_STDOUT, buffer, len);
}
#endif

/**
* @brief Called when protocol puts a frame on the ZwRxQueue.
*/
static void EventHandlerZwRx(void)
{
  QueueHandle_t Queue = g_pAppHandles->ZwRxQueue;
  SZwaveReceivePackage RxPackage;

  // Handle incoming replies
  while (xQueueReceive(Queue, (uint8_t*)(&RxPackage), 0) == pdTRUE)
  {
    DPRINT("Incoming Rx msg\r\n");

    switch (RxPackage.eReceiveType)
    {
      case EZWAVERECEIVETYPE_SINGLE:
      {
        ZAF_CP_CommandPublish(ZAF_getCPHandle(), (void *) &RxPackage);
        break;
      }

      case EZWAVERECEIVETYPE_NODE_UPDATE:
      {
        /*ApplicationSlaveUpdate() was called from this place in version prior to SDK7*/
        break;
      }

      case EZWAVERECEIVETYPE_SECURITY_EVENT:
      {
        /*ApplicationSecurityEvent() was used to support CSA, not needed in SDK7*/
        break;
      }

      case EZWAVERECEIVETYPE_STAY_AWAKE:
      {
        /*
         * Non-application frame was received, that must keep device awake.
         */
        break;
      }

    default:
      {
        ASSERT(false);
        break;
      }
    }
  }

}


/**
* @brief Triggered when protocol puts a message on the ZwCommandStatusQueue.
*/
static void EventHandlerZwCommandStatus(void)
{
  QueueHandle_t Queue = g_pAppHandles->ZwCommandStatusQueue;
  SZwaveCommandStatusPackage Status;

  // Handle incoming replies
  while (xQueueReceive(Queue, (uint8_t*)(&Status), 0) == pdTRUE)
  {
    DPRINT("Incoming Status msg\r\n");

    switch (Status.eStatusType)
    {
      case EZWAVECOMMANDSTATUS_TX:
      {
        SZWaveTransmitStatus* pTxStatus = &Status.Content.TxStatus;
        if (!pTxStatus->bIsTxFrameLegal)
        {
          DPRINT("Auch - not sure what to do\r\n");
        }
        else
        {
          DPRINT("Tx Status received\r\n");
          if (pTxStatus->Handle)
          {
            ZW_TX_Callback_t pCallback = (ZW_TX_Callback_t)pTxStatus->Handle;
            pCallback(pTxStatus->TxStatus, &pTxStatus->ExtendedTxStatus);
          }
        }
        break;
      }

      case EZWAVECOMMANDSTATUS_GENERATE_RANDOM:
      {
        DPRINT("Generate Random status\r\n");
        break;
      }

      case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      {
        DPRINTF("Learn status %d\r\n", Status.Content.LearnModeStatus.Status);
        if (ELEARNSTATUS_ASSIGN_COMPLETE == Status.Content.LearnModeStatus.Status)
        {
          // When security S0 or higher is set, remove all settings which happen before secure inclusion
          // calling function SetDefaultConfiguration(). The same function is used when there is an
          // EINCLUSIONSTATE_EXCLUDED.
          if ( (EINCLUSIONSTATE_EXCLUDED == ZAF_GetInclusionState()) ||
                      (SECURITY_KEY_NONE != GetHighestSecureLevel(ZAF_GetSecurityKeys())) )
          {
            SetDefaultConfiguration();
          }
          ZAF_EventHelperEventEnqueue((EVENT_APP) EVENT_SYSTEM_LEARNMODE_FINISHED);
          ZAF_Transport_OnLearnCompleted();
        }
        else if(ELEARNSTATUS_SMART_START_IN_PROGRESS == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue(EVENT_APP_SMARTSTART_IN_PROGRESS);
        }
        else if(ELEARNSTATUS_LEARN_IN_PROGRESS == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue(EVENT_APP_LEARN_IN_PROGRESS);
        }
        else if(ELEARNSTATUS_LEARN_MODE_COMPLETED_TIMEOUT == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue((EVENT_APP) EVENT_SYSTEM_LEARNMODE_FINISHED);
        }
        else if(ELEARNSTATUS_LEARN_MODE_COMPLETED_FAILED == Status.Content.LearnModeStatus.Status)
        {
          //Reformats protocol and application NVM. Then soft reset.
          ZAF_EventHelperEventEnqueue((EVENT_APP) EVENT_SYSTEM_RESET);
        }
        break;
      }

      case EZWAVECOMMANDSTATUS_NETWORK_LEARN_MODE_START:
      {
        // Status of ZAF_setNetworkLearnMode().
        break;
      }

      case EZWAVECOMMANDSTATUS_SET_DEFAULT:
      { // Received when protocol is started (not implemented yet), and when SetDefault command is completed
        DPRINT("Protocol Ready\r\n");
        ZAF_EventHelperEventEnqueue(EVENT_APP_FLUSHMEM_READY);

        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST:
      {
        DPRINTF("ERROR: Invalid TX Request to protocol - %d", Status.Content.InvalidTxRequestStatus.InvalidTxRequest);
        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_COMMAND:
      {
        DPRINTF("ERROR: Invalid command to protocol - %d", Status.Content.InvalidCommandStatus.InvalidCommand);
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_MAX_INCL_REQ_INTERVALS:
      {
        // Status response from calling the ZAF_SetMaxInclusionRequestIntervals function
        DPRINTF("SetMaxInclusionRequestIntervals status: %s\r\n",
                 Status.Content.NetworkManagementStatus.statusInfo[0] == true ? "SUCCESS" : "FAIL");

        // Add your application code here...
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_TX_ATTENUATION:
      {
        if (false == Status.Content.SetTxAttenuation.result)
        {
          DPRINT("Not allowed to attenuate tx-power\r\n");
        }
        break;
      }

      default:
        ASSERT(false);
        break;
    }
  }
}

/**
 *
 */
static void EventHandlerApp(void)
{
//  DPRINT("Got event!\r\n");

  uint8_t event;

  while (xQueueReceive(m_AppEventQueue, (uint8_t*)(&event), 0) == pdTRUE)
  {
    DPRINTF("Event: %d\r\n", event);
    AppStateManager((EVENT_APP)event);
  }
}

/*
 * Initialized all modules related to event queuing, task notifying and job registering.
 */
static void EventQueueInit()
{
  // Initialize Queue Notifier for events in the application.
  m_AppEventQueue = xQueueCreateStatic(
    sizeof_array(eventQueueStorage),
    sizeof(eventQueueStorage[0]),
    (uint8_t*)eventQueueStorage,
    &m_AppEventQueueObject
  );

  /*
   * Registers events with associated data, and notifies
   * the specific task about a pending job!
   */
  QueueNotifyingInit(
      &m_AppEventNotifyingQueue,
      m_AppEventQueue,
      g_AppTaskHandle,
      EAPPLICATIONEVENT_APP);

  /*
   * Wraps the QueueNotifying module for simple event generations!
   */
  ZAF_EventHelperInit(&m_AppEventNotifyingQueue);

  /*
   * Creates an internal queue to store no more than @ref JOB_QUEUE_BUFFER_SIZE jobs.
   * This module has no notification feature!
   */
  ZAF_JobHelperInit();
}

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS
ApplicationInit(EResetReason_t eResetReason)
{
  UNUSED(eResetReason);

  // NULL - We dont have the Application Task handle yet
  AppTimerInit(EAPPLICATIONEVENT_TIMER, NULL);

  /* hardware initialization */
  Board_Init();
  BRD420xBoardInit(RadioConfig.eRegion);

  //SWO_DebugPrintInit();

#ifdef DEBUGPRINT
#if BUILDING_WITH_UC
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), DebugPrinter);
#else
  ZAF_UART0_enable(115200, true, false);
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), ZAF_UART0_tx_send);
#endif // BUILDING_WITH_UC
#endif // DEBUGPRINT

  /* Init state machine*/
  currentState = STATE_APP_STARTUP;

  uint8_t versionMajor      = ZAF_GetAppVersionMajor();
  uint8_t versionMinor      = ZAF_GetAppVersionMinor();
  uint8_t versionPatchLevel = ZAF_GetAppVersionPatchLevel();

  DPRINT("\n\n--------------------------------\n");
  DPRINT("Z-Wave Sample App: LED Bulb\n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d [Freq: %d]\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          versionMajor,
          versionMinor,
          versionPatchLevel,
          ZAF_BUILD_NO,
          RadioConfig.eRegion);
  DPRINT("--------------------------------\n");
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINT("--------------------------------\n\n");

  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);

  CC_ZWavePlusInfo_Init(&CCZWavePlusInfo);

  CC_ColorSwitch_Init(s_colorComponents, sizeof_array(s_colorComponents), COLOR_SWITCH_DEFAULT_DURATION_SEC, NULL);
  cc_multilevel_switch_init(&multilevel_switch,
                            1,
                            CC_MULTILEVEL_SWITCH_DEFAULT_DIMMING_DURATION,
                            multilevel_switch_handler);
  color_switch_max = ZAF_Actuator_GetMax(&s_colorComponents[0].obj);
  multilevel_switch_max = ZAF_Actuator_GetMax(&multilevel_switch.actuator);

  CC_Version_SetApplicationVersionInfo(versionMajor, versionMinor, versionPatchLevel, ZAF_BUILD_NO);

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
static void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  // Init
  DPRINT("Enabling watchdog\n");
  WDOGn_Enable(DEFAULT_WDOG, true);

  g_AppTaskHandle = xTaskGetCurrentTaskHandle();
  g_pAppHandles = pAppHandles;
  AppTimerSetReceiverTask(g_AppTaskHandle);

  ZAF_Init(g_AppTaskHandle, pAppHandles, &ProtocolConfig, NULL);

  /*
   * Create an initialize some of the modules regarding queue and event handling and passing.
   * The UserTask that is dependent on modules initialized here, must be able to detect and wait
   * before using these modules. Specially if it has higher priority than this task!
   *
   * Currently, the UserTask is checking whether zaf_event_helper.h module is ready.
   * This module is the last to be initialized!
   */
  EventQueueInit();

  ZAF_EventHelperEventEnqueue(EVENT_APP_INIT);

#if !defined(BUILDING_WITH_UC)
  sl_led_init((sl_led_t *)&sl_led);
#endif /* !defined(BUILDING_WITH_UC) */

  Board_EnableButton(APP_BUTTON_LEARN_RESET);

  Board_IndicatorInit(APP_LED_INDICATOR);
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  CommandClassSupervisionInit(
      CC_SUPERVISION_STATUS_UPDATES_NOT_SUPPORTED,
      NULL,
      NULL);

  EventDistributorConfig(
    &g_EventDistributor,
    sizeof_array(g_aEventHandlerTable),
    g_aEventHandlerTable,
    NULL
    );

  // Wait for and process events
  DPRINT("LED Bulb Event processor Started\r\n");
  uint32_t iMaxTaskSleep = 0xFFFFFFFF;
  for (;;)
  {
    if (0xFFFFFFFF == EventDistributorDistribute(&g_EventDistributor, iMaxTaskSleep, 0))
    {
      return;
    }
  }
}

/**
 * @brief Returns the current state of the application state machine.
 * @return Current state
 */
STATE_APP
GetAppState(void)
{
  return currentState;
}

static void doRemainingInitialization()
{
  // Init file system
  ApplicationFileSystemInit(&pFileSystemApplication);

  /* Load the application settings from NVM3 file system */
  LoadConfiguration();
  /*it is not the time to wake completely*/

  // Setup AGI group lists
  AGI_Init();

  /*
   * Initialize Event Scheduler.
   */
  Transport_OnApplicationInitSW( &m_AppNIF, NULL);

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  /* Init state machine*/
  ZAF_EventHelperEventEnqueue(EVENT_EMPTY);
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of AppStateManager.
 */
void
AppStateManager(EVENT_APP event)
{
  DPRINTF("AppStateManager St: %d, Ev: %d\r\n", currentState, event);

  if ((BTN_EVENT_LONG_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event) ||
      (EVENT_SYSTEM_RESET == (EVENT_SYSTEM)event))
  {
    /*Force state change to activate system-reset without taking care of current state.*/
    ChangeState(STATE_APP_RESET);
    /* Send reset notification*/
    DeviceResetLocally();
  }

  switch(currentState)
  {

    case STATE_APP_STARTUP:
      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
      }

      if (EVENT_APP_INIT == event)
      {
        /*
         * This approach makes it possible to do less initialization before the scheduler starts.
         * Hence, this was made to reduce the boot-up time.
         */
        doRemainingInitialization();
        break;
      }
      CC_FirmwareUpdate_Init(NULL, NULL, true);
      ChangeState(STATE_APP_IDLE);
      break;

    case STATE_APP_IDLE:
      if(EVENT_APP_REFRESH_MMI == event)
      {
        Board_IndicateStatus(BOARD_STATUS_IDLE);
      }

      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        LoadConfiguration();
      }

      if (BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event ||
          (EVENT_SYSTEM_LEARNMODE_START == (EVENT_SYSTEM)event))
      {
        if (EINCLUSIONSTATE_EXCLUDED != g_pAppHandles->pNetworkInfo->eInclusionState)
        {
          DPRINT("LEARN_MODE_EXCLUSION\r\n");
          ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_EXCLUSION_NWE);
        }
        else
        {
          DPRINT("LEARN_MODE_INCLUSION\r\n");
          ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION);
        }
        ChangeState(STATE_APP_LEARN_MODE);
      }
      break;

    case STATE_APP_LEARN_MODE:
      if (EVENT_APP_REFRESH_MMI == event)
      {
        Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
      }

      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        LoadConfiguration();
      }

      if (BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event ||
          (EVENT_SYSTEM_LEARNMODE_STOP == (EVENT_SYSTEM)event))
      {
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_DISABLE);
        Board_IndicateStatus(BOARD_STATUS_IDLE);

        //Go back to smart start if the node was never included.
        //Protocol will not commence SmartStart if the node is already included in the network.
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

        ChangeState(STATE_APP_IDLE);

        /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
        CC_Indicator_RefreshIndicatorProperties();
        ZAF_TSE_Trigger(CC_Indicator_report_stx,
                        (void *)&ZAF_TSE_localActuationIdentifyData,
                        true);
      }

      if (EVENT_SYSTEM_LEARNMODE_FINISHED == (EVENT_SYSTEM)event)
      {
        //Go back to smart start if the node was excluded.
        //Protocol will not commence SmartStart if the node is already included in the network.
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

        ChangeState(STATE_APP_IDLE);

        /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
        CC_Indicator_RefreshIndicatorProperties();
        ZAF_TSE_Trigger(CC_Indicator_report_stx,
                        (void *)&ZAF_TSE_localActuationIdentifyData,
                        true);
      }
      break;

    case STATE_APP_RESET:
      if(EVENT_APP_REFRESH_MMI == event){}

      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        /* Soft reset */
        Board_ResetHandler();
      }
      break;

    default:
      // Do nothing.
      break;
  }
}

/**
 * @brief Sets the current state to a new, given state.
 * @param newState New state.
 */
static void
ChangeState(STATE_APP newState)
{
  DPRINTF("State changed from %d to %d\r\n", currentState, newState);

  currentState = newState;

  /**< Pre-action on new state is to refresh MMI */
  ZAF_EventHelperEventEnqueue(EVENT_APP_REFRESH_MMI);
}

/**
 * @brief Transmission callback for Device Reset Locally call.
 * @param pTransmissionResult Result of each transmission.
 */
void
DeviceResetLocallyDone(TRANSMISSION_RESULT * pTransmissionResult)
{
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    /* Reset protocol */
    // Set default command to protocol
    SZwaveCommandPackage CommandPackage;
    CommandPackage.eCommandType = EZWAVECOMMANDTYPE_SET_DEFAULT;

    DPRINT("\nDisabling watchdog during reset\n");
    WDOGn_Enable(DEFAULT_WDOG, false);

    EQueueNotifyingStatus Status = QueueNotifyingSendToBack(g_pAppHandles->pZwCommandQueue,
                                                            (uint8_t*)&CommandPackage,
                                                            500);
    ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == Status);
  }
}

/**
 * @brief Send reset notification.
 */
void
DeviceResetLocally(void)
{
  AGI_PROFILE lifelineProfile = {
      ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL,
      ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE
  };
  DPRINT("Call locally reset\r\n");

  CC_DeviceResetLocally_notification_tx(&lifelineProfile, DeviceResetLocallyDone);
}

/**
 * @brief See description for function prototype in CC_Version.h.
 */
uint8_t
CC_Version_getNumberOfFirmwareTargets_handler(void)
{
  return 1; /*CHANGE THIS - firmware 0 version*/
}

/**
 * @brief See description for function prototype in CC_Version.h.
 */
void
handleGetFirmwareVersion(
  uint8_t bFirmwareNumber,
  VG_VERSION_REPORT_V2_VG *pVariantgroup)
{
  /*firmware 0 version and sub version*/
  if(bFirmwareNumber == 0)
  {
    pVariantgroup->firmwareVersion = ZAF_GetAppVersionMajor();
    pVariantgroup->firmwareSubVersion = ZAF_GetAppVersionMinor();
  }
  else
  {
    /*Just set it to 0 if firmware n is not present*/
    pVariantgroup->firmwareVersion = 0;
    pVariantgroup->firmwareSubVersion = 0;
  }
}


/**
 * @brief Function resets configuration to default values.
 *
 * Add application specific functions here to initialize configuration values stored in persistent memory.
 * Will be called at any of the following events:
 *  - Network Exclusion
 *  - Network Secure Inclusion (after S2 bootstrapping complete)
 *  - Device Reset Locally
 */
void
SetDefaultConfiguration(void)
{
  AssociationInit(true, pFileSystemApplication);

  loadInitStatusPowerLevel();

  CC_ColorSwitch_Init(s_colorComponents, sizeof_array(s_colorComponents), COLOR_SWITCH_DEFAULT_DURATION_SEC, NULL);

  cc_multilevel_switch_init(&multilevel_switch,
                            1,
                            CC_MULTILEVEL_SWITCH_DEFAULT_DIMMING_DURATION,
                            multilevel_switch_handler);

  uint32_t appVersion = ZAF_GetAppVersion();
  Ecode_t result = nvm3_writeData(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);
  ASSERT(ECODE_NVM3_OK == result);
}

/**
 * @brief This function loads the application settings from file system.
 * If no settings are found, default values are used and saved.
 */
bool
LoadConfiguration(void)
{
  uint32_t appVersion;
  Ecode_t versionFileStatus = nvm3_readData(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);

  if (ECODE_NVM3_OK == versionFileStatus)
  {
    if (ZAF_GetAppVersion() != appVersion)
    {
      // Add code for migration of file system to higher version here.
    }

    /* Initialize association module */
    AssociationInit(false, pFileSystemApplication);

    return true;
  }
  else
  {
    DPRINT("Application FileSystem Verify failed\r\n");
    loadInitStatusPowerLevel();

    // Reset the file system if ZAF_FILE_ID_APP_VERSION is missing since this indicates
    // corrupt or missing file system.
    AppResetNvm();

    return false;
  }
}

void AppResetNvm(void)
{
  DPRINT("Resetting application FileSystem to default\r\n");

  ASSERT(0 != pFileSystemApplication); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  Ecode_t errCode = nvm3_eraseAll(pFileSystemApplication);
  ASSERT(ECODE_NVM3_OK == errCode); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  /* Apparently there is no valid configuration in file system, so load */
  /* default values and save them to file system. */
  SetDefaultConfiguration();
}

/**
 * @brief Handler for basic get. Handles received basic get commands.
 * @param endpoint Endpoint that supports Multilevel Switch
 * @return Multilevel Switch current value
 */
uint8_t
CC_Basic_GetCurrentValue_handler(uint8_t endpoint)
{
  return cc_multilevel_switch_get_current_value_handler(endpoint);
}

/**
 * @brief Report Multilevel Switch target value
 * @param endpoint Endpoint that supports Multilevel Switch
 * @return Multilevel Switch target value.
 */
uint8_t
CC_Basic_GetTargetValue_handler(uint8_t endpoint)
{
  return cc_multilevel_switch_get_target_value_handler(endpoint);
}

/**
 * @brief Report Multilevel Switch transition duration time.
 * @param endpoint Endpoint that supports Multilevel Switch
 * @return Multilevel Switch duration time.
 */
uint8_t
CC_Basic_GetDuration_handler(uint8_t endpoint)
{
  return cc_multilevel_switch_get_duration_handler(endpoint);
}

uint16_t handleFirmWareIdGet(uint8_t n)
{
  if (n == 0)
  {
    // Firmware 0
    return APP_FIRMWARE_ID;
  }
  // Invalid Firmware number.
  return 0;
}


/**
 * This function is used to return a pointer for input data for the TSE trigger.
 * @param rxOption pointer that will be included in the ZAF_TSE input data.
*/
void* CC_Basic_prepare_zaf_tse_data(RECEIVE_OPTIONS_TYPE_EX* pRxOpt)
{
  UNUSED(pRxOpt);
  // Nothing here
  return NULL;
}

/**
 * This function is used to return a pointer for input data for the TSE trigger.
 * @param rxOption pointer that will be included in the ZAF_TSE input data.
*/
void CC_Basic_report_stx(TRANSMIT_OPTIONS_TYPE_SINGLE_EX txOptions, void* pData)
{
  UNUSED(txOptions);
  UNUSED(pData);
  // Nothing here
}

/**
 * This function is used to notify the Application that the CC Basic Set
 * status is in a WORKING state. The application can subsequently make the TSE Trigger
 * using the information passed on from the rxOptions.
 * @param rxOption pointer used to when triggering the "working state"
*/
void CC_Basic_report_notifyWorking(RECEIVE_OPTIONS_TYPE_EX* pRxOpt)
{
  /* Handle here the case where Basic CC has triggered a working state.
  Look in the Door Lock keypad application for an example. */
  UNUSED(pRxOpt);
}


uint8_t CC_Version_GetHardwareVersion_handler(void)
{
  return 1;
}

void CC_ManufacturerSpecific_ManufacturerSpecificGet_handler(uint16_t * pManufacturerID,
                                                             uint16_t * pProductID)
{
  *pManufacturerID = APP_MANUFACTURER_ID;
  *pProductID = APP_PRODUCT_ID;
}

/*
 * This function will report a serial number in a binary format according to the specification.
 * The serial number is the chip serial number and can be verified using the Simplicity Commander.
 * The choice of reporting can be changed in accordance with the Manufacturer Specific
 * Command Class specification.
 */
void CC_ManufacturerSpecific_DeviceSpecificGet_handler(device_id_type_t * pDeviceIDType,
                                                       device_id_format_t * pDeviceIDDataFormat,
                                                       uint8_t * pDeviceIDDataLength,
                                                       uint8_t * pDeviceIDData)
{
  *pDeviceIDType = DEVICE_ID_TYPE_SERIAL_NUMBER;
  *pDeviceIDDataFormat = DEVICE_ID_FORMAT_BINARY;
  *pDeviceIDDataLength = 8;
  uint64_t uuID = SYSTEM_GetUnique();
  DPRINTF("\r\nuuID: %x", (uint32_t)uuID);
  *(pDeviceIDData + 0) = (uint8_t)(uuID >> 56);
  *(pDeviceIDData + 1) = (uint8_t)(uuID >> 48);
  *(pDeviceIDData + 2) = (uint8_t)(uuID >> 40);
  *(pDeviceIDData + 3) = (uint8_t)(uuID >> 32);
  *(pDeviceIDData + 4) = (uint8_t)(uuID >> 24);
  *(pDeviceIDData + 5) = (uint8_t)(uuID >> 16);
  *(pDeviceIDData + 6) = (uint8_t)(uuID >>  8);
  *(pDeviceIDData + 7) = (uint8_t)(uuID >>  0);
}

static uint8_t multilevel_switch_value;
static uint8_t color_switch_red_value;
static uint8_t color_switch_green_value;
static uint8_t color_switch_blue_value;

void callback_RED(s_colorComponent * colorComponent)
{
  color_switch_red_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}
void callback_GREEN(s_colorComponent * colorComponent)
{
  color_switch_green_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}
void callback_BLUE(s_colorComponent * colorComponent)
{
  color_switch_blue_value = ZAF_Actuator_GetCurrentValue(&colorComponent->obj);
  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}

void multilevel_switch_handler(cc_multilevel_switch_t * p_switch)
{
  multilevel_switch_value = cc_multilevel_switch_get_current_value(p_switch);
  DPRINTF("%s Setting RGB=(%u,%u,%u)\n", __func__,
          (color_switch_red_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_green_value * multilevel_switch_value) / multilevel_switch_max,
          (color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max);
  sl_led_set_rgb_color(&sl_led,
                        (uint16_t)((color_switch_red_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_green_value * multilevel_switch_value) / multilevel_switch_max),
                        (uint16_t)((color_switch_blue_value * multilevel_switch_value) / multilevel_switch_max));
}
