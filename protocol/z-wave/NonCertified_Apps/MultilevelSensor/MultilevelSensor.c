/**
 * Z-Wave Certified Application Multilevel Sensor
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "zw_config_rf.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#include "SizeOf.h"
#include "Assert.h"
#include "DebugPrintConfig.h"

//To enable DEBUGPRINT you must first undefine DISABLE_USART0
//In Simplicity Studio open Project->Properties->C/C++ General->Paths and Symbols
//Remove DISABLE_USART0 from list found under # Symbols->GNU C
#if !defined(DISABLE_USART1) || !defined(DISABLE_USART0)
//#define DEBUGPRINT
#endif

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

/*IO control*/
#include <board.h>
#include <ev_man.h>
#include <AppTimer.h>
#include <string.h>
#include <SwTimer.h>
#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>

#include <association_plus.h>
#include <agi.h>
#include <CC_Association.h>
#include <CC_AssociationGroupInfo.h>
#include <CC_Version.h>
#include <CC_ZWavePlusInfo.h>
#include <CC_PowerLevel.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_Basic.h>
#include <CC_FirmwareUpdate.h>
#include <CC_ManufacturerSpecific.h>

#include <CC_MultilevelSensor_Support.h>
#include <CC_MultilevelSensor_SensorHandler.h>
#include <CC_MultilevelSensor_SensorHandlerTypes.h>
#include "MultilevelSensor_interface.h"

#include <CC_MultiChanAssociation.h>
#include <CC_Supervision.h>

#include <CC_WakeUp.h>
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>

#include <ZAF_Common_helper.h>
#include <ZAF_PM_Wrapper.h>
#include <ZAF_network_learn.h>
#include <ZAF_network_management.h>
#include <ZAF_TSE.h>
#include <ota_util.h>
#include "ZAF_adc.h"
#include <ZAF_CmdPublisher.h>
#include <em_wdog.h>
#include "events.h"
#include "zw_region_config.h"

#include <CC_Configuration.h>
#include <ZW_UserTask.h>
#include "Configuration_interface.h"

#include "zw_build_no.h"

/****************************************************************************/
/* Application specific button and LED definitions                          */
/****************************************************************************/

#if defined(RADIO_BOARD_EFR32ZG13P32) || defined(RADIO_BOARD_EFR32ZG13S)
  // The EFR32ZG13P32 device has reduced number of GPIO pins and hence less
  // button inputs available for the application to use. Therefore alternative
  // button mapping is required

  #define EVENT_BTN        APP_BUTTON_LEARN_RESET  // Overload the LEARN_RESET button to also function as the  event button
                                                       // (It's the only button that can wakeup from EM4 on EFR32ZG13P32)

  // Define the button events used to signify  sensor state transitions:
  //
  // EVENT_TRANSITION_TO_ACTIVE
  //   Triggered by the BTN_EVENT_HOLD event which means the button is pressed and held
  #define EVENT_TRANSITION_TO_ACTIVE(event)   (BTN_EVENT_HOLD(EVENT_BTN) == (BUTTON_EVENT)event)
  //
  // EVENT_TRANSITION_TO_DEACTIVE
  //   Triggered by the BTN_EVENT_UP event which means the button was released after a BTN_EVENT_HOLD period
  #define EVENT_TRANSITION_TO_DEACTIVE(event) (BTN_EVENT_UP(EVENT_BTN) == (BUTTON_EVENT)event)

#else

  #define EVENT_BTN        APP_WAKEUP_SLDR_BTN  // We prefer a wakeup enabled slider, but a button will do

  // Define the button events used to signify  sensor state transitions:
  //
  // EVENT_TRANSITION_TO_ACTIVE
  //   The EVENT_BTN could be allocated to either a slider or a button.
  //   - The slider will always send a DOWN event when moved to the ON position.
  //   - A button will send SHORT_PRESS or HOLD event when pressed. Only the
  //     HOLD event will be followed by an UP event when the button is
  //     released. Since we need the UP event later to cancel the power
  //     lock, we ignore the SHORT_PRESS event here.
  #define EVENT_TRANSITION_TO_ACTIVE(event)   ((BTN_EVENT_DOWN(EVENT_BTN) == (BUTTON_EVENT)event) || \
                                                   (BTN_EVENT_HOLD(EVENT_BTN) == (BUTTON_EVENT)event))
  // EVENT_TRANSITION_TO_DEACTIVE
  //   The EVENT_BTN could be allocated to either a slider or a button.
  //   The slider will always send an UP event when moved to the OFF position.
  //   A button will send either an UP, SHORT_PRESS or LONG_PRESS on release
  //   depending on how long it has been pressed.
  #define EVENT_TRANSITION_TO_DEACTIVE(event) ((BTN_EVENT_UP(EVENT_BTN) == (BUTTON_EVENT)event) || \
                                                   (BTN_EVENT_SHORT_PRESS(EVENT_BTN) == (BUTTON_EVENT)event) || \
                                                   (BTN_EVENT_LONG_PRESS(EVENT_BTN) == (BUTTON_EVENT)event))

#endif

/* Ensure we did not allocate the same physical button to more than one function */
#if !defined(RADIO_BOARD_EFR32ZG13P32) && !defined(RADIO_BOARD_EFR32ZG13S) // Skipped for EFR32ZG13P32 where the shortage of GPIOs means we need to assign dual function to buttons
STATIC_ASSERT((APP_BUTTON_LEARN_RESET != EVENT_BTN),
              STATIC_ASSERT_FAILED_button_overlap);
#endif

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
  STATE_APP_TRANSMIT_DATA
}
STATE_APP;

/**
 * The following values determine how long the application sleeps between
 * Wake Up Notifications. The more sleep, the less battery consumption.
 * The values in Sensor  are set to relatively low values because of
 * testing. An actual product would benefit from having high values.
 * All values in seconds.
 */
#define DEFAULT_SLEEP_TIME 300   // 5 minutes
#define MIN_SLEEP_TIME     20
#define MAX_SLEEP_TIME     86400 // 24 hours
#define STEP_SLEEP_TIME    20

#define BTN_EVENT_FILTER(btnEvent)          ((btnEvent >= DEFINE_EVENT_KEY_NBR) && (btnEvent < EVENT_BTN_MAX))

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

static SPowerLock_t m_RadioPowerLock;
/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListNonSecureNotIncluded[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION_V2,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE_V2,
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_WAKE_UP,
  COMMAND_CLASS_SUPERVISION,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5,
  COMMAND_CLASS_CONFIGURATION_V4,
  COMMAND_CLASS_SENSOR_MULTILEVEL_V11
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListNonSecureIncludedSecure[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE_V2,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_SUPERVISION
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListSecure[] =
{
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_ASSOCIATION,
  COMMAND_CLASS_MULTI_CHANNEL_ASSOCIATION_V2,
  COMMAND_CLASS_ASSOCIATION_GRP_INFO,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_INDICATOR,
  COMMAND_CLASS_POWERLEVEL,
  COMMAND_CLASS_WAKE_UP,
  COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5,
  COMMAND_CLASS_CONFIGURATION_V4,
  COMMAND_CLASS_SENSOR_MULTILEVEL_V11
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

/**
 * Setup AGI root device groups table from config_app.h
 */
AGI_GROUP agiTableRootDeviceGroups[] = {AGITABLE_ROOTDEVICE_GROUPS};

static const AGI_PROFILE lifelineProfile = {
    ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL,
    ASSOCIATION_GROUP_INFO_REPORT_PROFILE_GENERAL_LIFELINE
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

static uint8_t basicValue = 0x00;

// Timer
static SSwTimer EventJobsTimer;

static TaskHandle_t g_AppTaskHandle;

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

/* True Status Engine (TSE) variables */
static s_CC_indicator_data_t ZAF_TSE_localActuationIdentifyData = {
  .rxOptions = {
    .rxStatus = 0,          /* rxStatus, verified by the TSE for Multicast */
    .securityKey = 0,       /* securityKey, ignored by the TSE */
    .sourceNode = {0,0},    /* sourceNode (nodeId, endpoint), verified against lifeline destinations by the TSE */
    .destNode = {0,0}       /* destNode (nodeId, endpoint), verified by the TSE for local endpoint */
  },
  .indicatorId = 0x50      /* Identify Indicator*/
};

void AppResetNvm(void);

#if defined(DEBUGPRINT) && defined(BUILDING_WITH_UC)
#include "sl_iostream.h"
static void DebugPrinter(const uint8_t * buffer, uint32_t len)
{
  sl_iostream_write(SL_IOSTREAM_STDOUT, buffer, len);
}
#endif

#define APP_EVENT_QUEUE_SIZE 5

/**
 * The following four variables are used for the application event queue.
 */
static SQueueNotifying m_AppEventNotifyingQueue;
static StaticQueue_t m_AppEventQueueObject;
static EVENT_APP eventQueueStorage[APP_EVENT_QUEUE_SIZE];
static QueueHandle_t m_AppEventQueue;

static nvm3_Handle_t* pFileSystemApplication;

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
/**
 * Write a specific amount data to nvm3
 *
 * @param[in] data pointer to the data to be written
 * @param[in] size amount of data in byte dimension
 * @return Returns true if successfuly wrote to nvm3, else false
 */
static bool
cc_configuration_io_write(nvm3_ObjectKey_t file_id, uint8_t const* data, size_t size);

/**
 * Read a specific amount data to nvm3
 *
 * @param[in] data pointer to the buffer where the data will be read into
 * @param[in] size wanted amount of data in byte dimension
 * @return Returns true if successfuly read from nvm3, else false
 */
static bool
cc_configuration_io_read(nvm3_ObjectKey_t file_id, uint8_t *data, size_t size);

static sl_cc_configuration_io_interface_t configuration_io_interface = {
  .write_handler = cc_configuration_io_write,
  .read_handler  = cc_configuration_io_read
};

void DeviceResetLocallyDone(TRANSMISSION_RESULT * pTransmissionResult);
void DeviceResetLocally(void);
STATE_APP GetAppState();
void AppStateManager( EVENT_APP event);
static void ChangeState( STATE_APP newState);
void ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult);
void SetDefaultConfiguration(void);
bool LoadConfiguration(void);
static void ApplicationTask(SApplicationHandles* pAppHandles);

void ZCB_EventJobsTimer(SSwTimer *pTimer);

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
    DPRINTF("Incoming Rx msg  type:%u class:%u\n", RxPackage.eReceiveType, RxPackage.uReceiveParams.Rx.Payload.rxBuffer.ZW_Common.cmdClass);

    switch (RxPackage.eReceiveType)
    {
      case EZWAVERECEIVETYPE_SINGLE:
      {
        ZAF_CP_CommandPublish(ZAF_getCPHandle(), &RxPackage);
        break;
      }

      case EZWAVERECEIVETYPE_NODE_UPDATE:
      {
        /*ApplicationSlaveUpdate() was called from this place in version prior to SDK7*/
        CC_WakeUp_stayAwakeIfActive();
        break;
      }

      case EZWAVERECEIVETYPE_SECURITY_EVENT:
      {
        /*ApplicationSecurityEvent() was used to support CSA, not needed in SDK7*/
        break;
      }

      case EZWAVERECEIVETYPE_STAY_AWAKE:
      {
        /* Non-application frame was received, that must keep device awake.
         * Just inform the app not to go to sleep */
        if (STATE_APP_LEARN_MODE != currentState)
        {
          /* Ignore it if inclusion is in progress, device must be awake anyway. */
          CC_WakeUp_stayAwakeIfActive();
        }
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
    DPRINTF("Incoming Status msg type %u\n", Status.eStatusType);

    switch (Status.eStatusType)
    {
      case EZWAVECOMMANDSTATUS_TX:
      {
        SZWaveTransmitStatus* pTxStatus = &Status.Content.TxStatus;
        if (!pTxStatus->bIsTxFrameLegal)
        {
          DPRINT("Auch - not sure what to do\n");
        }
        else
        {
          DPRINT("Tx Status received\n");
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
        DPRINT("Generate Random status\n");
        break;
      }

      case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      {
        DPRINTF("Learn status %d\n", Status.Content.LearnModeStatus.Status);
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
        else if(ELEARNSTATUS_LEARN_MODE_COMPLETED_TIMEOUT == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue((EVENT_APP) EVENT_SYSTEM_LEARNMODE_FINISHED);
        }
        else if(ELEARNSTATUS_SMART_START_IN_PROGRESS == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue(EVENT_APP_SMARTSTART_IN_PROGRESS);
        }
        else if(ELEARNSTATUS_LEARN_IN_PROGRESS == Status.Content.LearnModeStatus.Status)
        {
          ZAF_EventHelperEventEnqueue(EVENT_APP_LEARN_IN_PROGRESS);
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
        break;
      }

      case EZWAVECOMMANDSTATUS_SET_DEFAULT:
      { // Received when protocol is started (not implemented yet), and when SetDefault command is completed
        DPRINT("Protocol Ready\n");
        ZAF_EventHelperEventEnqueue(EVENT_APP_FLUSHMEM_READY);
        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST:
      {
        DPRINTF("ERROR: Invalid TX Request to protocol - %d\n", Status.Content.InvalidTxRequestStatus.InvalidTxRequest);
        break;
      }

      case EZWAVECOMMANDSTATUS_INVALID_COMMAND:
      {
        DPRINTF("ERROR: Invalid command to protocol - %d\n", Status.Content.InvalidCommandStatus.InvalidCommand);
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_MAX_INCL_REQ_INTERVALS:
      {
        // Status response from calling the ZAF_SetMaxInclusionRequestIntervals function
        DPRINTF("SetMaxInclusionRequestIntervals status: %s\n",
                 Status.Content.NetworkManagementStatus.statusInfo[0] == true ? "SUCCESS" : "FAIL");

        // Add your application code here...
        break;
      }

      case EZWAVECOMMANDSTATUS_PM_SET_POWERDOWN_CALLBACK:
      {
        // Status response from calling the ZAF_PM_SetPowerDownCallback function
        if(false == Status.Content.SetPowerDownCallbackStatus.result)
        {
          DPRINT("Failed to register PowerDown Callback function\n");
          ASSERT(false);
        }
        break;
      }

      case EZWAVECOMMANDSTATUS_ZW_SET_TX_ATTENUATION:
      {
        if (false == Status.Content.SetTxAttenuation.result)
        {
          DPRINT("CC_PowerLevel failed to set TX power\r\n");
        }
        break;
      }

      default:
        DPRINTF("  == >     Not handled case: 0x%04x\n", Status.eStatusType);
        ASSERT(false);  // A Z-Wave Command Status of value 160 (0xA0) is being ASSERTed here and cause halts during OTA.
        break;
    }
  }
}

/**
 *
 */
static void EventHandlerApp(void)
{
  uint8_t event;

  while (xQueueReceive(m_AppEventQueue, (uint8_t*)(&event), 0) == pdTRUE)
  {
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
  // NULL - We dont have the Application Task handle yet
  AppTimerInit(EAPPLICATIONEVENT_TIMER, NULL);

  /* hardware initialization */
  Board_Init();
  BRD420xBoardInit(RadioConfig.eRegion);

#ifdef DEBUGPRINT
#if BUILDING_WITH_UC
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), DebugPrinter);
#else
  static uint8_t m_aDebugPrintBuffer[96];
  ZAF_UART0_enable(115200, true, false);
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), ZAF_UART0_tx_send);
#endif // BUILDING_WITH_UC
#endif // DEBUGPRINT

  /* Init state machine*/
  currentState = STATE_APP_STARTUP;

  uint8_t versionMajor      = ZAF_GetAppVersionMajor();
  uint8_t versionMinor      = ZAF_GetAppVersionMinor();
  uint8_t versionPatchLevel = ZAF_GetAppVersionPatchLevel();

  DPRINT("\n\n-----------------------------\n");
  DPRINT("Z-Wave Sample App: Multilevel Sensor \n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d [Freq: %d]\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          versionMajor,
          versionMinor,
          versionPatchLevel,
          ZAF_BUILD_NO,
          RadioConfig.eRegion);
  DPRINT("-----------------------------\n");
  DPRINTF("%s: Toggle learn mode\n", Board_GetButtonLabel(APP_BUTTON_LEARN_RESET));
  DPRINT("      Hold 5 sec: Reset\n");
  DPRINTF("%s: Activate  event\n", Board_GetButtonLabel(EVENT_BTN));
  DPRINT("      (leave deactivated to allow going to sleep)\n");
  DPRINTF("%s: Learn mode + identify\n", Board_GetLedLabel(APP_LED_INDICATOR));
  DPRINT("-----------------------------\n\n");

  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);
  DPRINTF("Board_GetGpioEm4Flags()      = 0b%08x\n", Board_GetGpioEm4Flags());

  if (eResetReason == ERESETREASON_EM4_WUT || eResetReason == ERESETREASON_EM4_EXT_INT)
  {
    #ifdef DEBUGPRINT
      Board_DebugPrintEm4WakeupFlags(Board_GetGpioEm4Flags());
    #endif
  }

  CC_ZWavePlusInfo_Init(&CCZWavePlusInfo);

  CC_Version_SetApplicationVersionInfo(versionMajor, versionMinor, versionPatchLevel, ZAF_BUILD_NO);

  static sl_sensor_interface_t test_sensor_temperature;
  sl_cc_multilevel_sensor_init_interface(&test_sensor_temperature, SL_SENSOR_NAME_AIR_TEMPERATURE);
  sl_cc_multilevel_sensor_add_supported_scale_interface(&test_sensor_temperature, SL_SENSOR_SCALE_CELSIUS);
  sl_cc_multilevel_sensor_add_supported_scale_interface(&test_sensor_temperature, SL_SENSOR_SCALE_FAHRENHEIT);
  test_sensor_temperature.init         = MultilevelSensor_interface_temperature_init;
  test_sensor_temperature.deinit       = MultilevelSensor_interface_temperature_deinit;
  test_sensor_temperature.read_value   = MultilevelSensor_interface_temperature_read;

  static sl_sensor_interface_t test_sensor_humidity;
  sl_cc_multilevel_sensor_init_interface(&test_sensor_humidity, SL_SENSOR_NAME_HUMIDITY);
  sl_cc_multilevel_sensor_add_supported_scale_interface(&test_sensor_humidity, SL_SENSOR_SCALE_PERCENTAGE);
  test_sensor_humidity.init         = MultilevelSensor_interface_humidity_init;
  test_sensor_humidity.deinit       = MultilevelSensor_interface_humidity_deinit;
  test_sensor_humidity.read_value   = MultilevelSensor_interface_humidity_read;

  sl_cc_multilevel_sensor_registration(&test_sensor_temperature);
  sl_cc_multilevel_sensor_registration(&test_sensor_humidity);

  /* Register task function */
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
   * @see Sensor_MultiThread example for more info.
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
  task.pTaskFunc = (TaskFunction_t)Sensor_DataAcquisitionTask;
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
static void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  DPRINT("Multilevel Sensor Main App/Task started!\n");

  // Init
  DPRINT("Enabling watchdog\n");
  WDOGn_Enable(DEFAULT_WDOG, true);

  g_AppTaskHandle = xTaskGetCurrentTaskHandle();
  g_pAppHandles = pAppHandles;

  ZAF_Init(g_AppTaskHandle, pAppHandles, &ProtocolConfig, CC_WakeUp_stayAwakeIfActive);

  sl_cc_multilevel_sensor_init();

  AppTimerSetReceiverTask(g_AppTaskHandle);

  /* Make sure to call AppTimerEm4PersistentRegister() _after_ ZAF_Init().
   * It will access the app handles */
  AppTimerEm4PersistentRegister(&EventJobsTimer, false, ZCB_EventJobsTimer);  // register for event jobs timeout event

  // Initialize CC Wake Up
  CC_WakeUp_setConfiguration(WAKEUP_PAR_DEFAULT_SLEEP_TIME, DEFAULT_SLEEP_TIME);
  CC_WakeUp_setConfiguration(WAKEUP_PAR_MAX_SLEEP_TIME,     MAX_SLEEP_TIME);
  CC_WakeUp_setConfiguration(WAKEUP_PAR_MIN_SLEEP_TIME,     MIN_SLEEP_TIME);
  CC_WakeUp_setConfiguration(WAKEUP_PAR_SLEEP_STEP,         STEP_SLEEP_TIME);

  ZAF_PM_Register(&m_RadioPowerLock, PM_TYPE_RADIO);

  /*
   * Create an initialize some of the modules regarding queue and event handling and passing.
   * The UserTask that is dependent on modules initialized here, must be able to detect and wait
   * before using these modules. Specially if it has higher priority than this task!
   *
   * Currently, the UserTask is checking whether zaf_event_helper.h module is ready.
   * This module is the last to be initialized!
   */
  EventQueueInit();

  // Generate event that says the APP is initialized
  ZAF_EventHelperEventEnqueue(EVENT_APP_INIT);

  //Enables events on test board
  Board_EnableButton(APP_BUTTON_LEARN_RESET);
  Board_EnableButton(EVENT_BTN);

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

  DPRINTF("IsWakeupCausedByRtccTimeout=%s\n", (IsWakeupCausedByRtccTimeout()) ? "true" : "false");
  DPRINTF("CompletedSleepDurationMs   =%u\n", GetCompletedSleepDurationMs());

  // Wait for and process events
  DPRINT("Multilevel Sensor Event Distributor Started\n");
  uint32_t iMaxTaskSleep = 0xFFFFFFFF;  // Block forever
  for (;;)
  {
    EventDistributorDistribute(&g_EventDistributor, iMaxTaskSleep, 0);
  }
}


static void doRemainingInitialization()
{
  EResetReason_t resetReason = GetResetReason();

  // Init file system
  ApplicationFileSystemInit(&pFileSystemApplication);

  /* Load the application settings from NVM3 file system */
  LoadConfiguration();

  /* Setup AGI group lists*/
  AGI_Init();
  AGI_ResourceGroupSetup(agiTableRootDeviceGroups, (sizeof(agiTableRootDeviceGroups)/sizeof(AGI_GROUP)), ENDPOINT_ROOT);

  CC_WakeUp_init(resetReason, pFileSystemApplication);

  /*
   * Initialize Event Scheduler.
   */
  Transport_OnApplicationInitSW( &m_AppNIF, CC_WakeUp_stayAwakeIfActive);

  /* Re-load and process EM4 persistent application timers.
   * NB: Before calling AppTimerEm4PersistentLoadAll here all
   *     application timers must have been been registered with
   *     AppTimerRegister() or AppTimerEm4PersistentRegister().
   *     Essentially it means that all CC handlers must be
   *     initialized first.
   */
  AppTimerEm4PersistentLoadAll(resetReason);

  CC_FirmwareUpdate_Init(NULL, NULL, true);

  if (ERESETREASON_EM4_EXT_INT == resetReason)
  {
    uint32_t em4_wakeup_flags = Board_GetGpioEm4Flags();

    if (0 != em4_wakeup_flags)
    {
      Board_ProcessEm4PinWakeupFlags(em4_wakeup_flags);
    }
    ChangeState(STATE_APP_IDLE);
  }

  /* If we entered TRANSMIT state to send battery report, don't change it */
  if ((ERESETREASON_EM4_WUT == resetReason) && (STATE_APP_TRANSMIT_DATA != currentState))
  {
    ChangeState(STATE_APP_IDLE);
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

  if(ERESETREASON_EM4_EXT_INT != resetReason)
  {
    /* Enter SmartStart*/
    /* Protocol will commence SmartStart only if the node is NOT already included in the network */
    ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);
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

void notAppStateDependentActivity(EVENT_APP event)
{
  if ((BTN_EVENT_LONG_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event) || (EVENT_SYSTEM_RESET == (EVENT_SYSTEM)event))
  {
    DPRINT("Reset system\n");
    /*Force state change to activate system-reset without taking care of current
      state.*/
    ChangeState(STATE_APP_RESET);
    /* Send reset notification*/
    DeviceResetLocally();
  }

  // Handle received  event
  if (EVENT_TRANSITION_TO_DEACTIVE(event))
  {
    DPRINT("\n");
    DPRINT("      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*\n");
    DPRINT("      *!*!*       EVENT INACTIVE         *!*!*\n");
    DPRINT("      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*\n");
    DPRINT("\n");
    ZAF_PM_Cancel(&m_RadioPowerLock);
  }

  if (event == EVENT_APP_USERTASK_DATA_ACQUISITION_READY)
  {
    DPRINT("MainApp: Data Acquisition UserTask started and ready!\n");
  }

  if (event == EVENT_APP_USERTASK_DATA_ACQUISITION_FINISHED)
  {
    DPRINT("MainApp: Data Acquisition UserTask finished!\n");
  }
}

/**
 * @brief The core state machine of this sample application.
 * @param event The event that triggered the call of AppStateManager.
 */
void
AppStateManager(EVENT_APP event)
{
  DPRINTF("AppStateManager St: %d, Ev: 0x%02x\n", currentState, event);

  /*
   * Here we handle events that are not evaluated in the context of the app state.
   */
  notAppStateDependentActivity(event);

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
      ChangeState(STATE_APP_IDLE);
      break;

    case STATE_APP_IDLE:
      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        LoadConfiguration();
      }

      if (EVENT_APP_SMARTSTART_IN_PROGRESS == event)
      {
        ChangeState(STATE_APP_LEARN_MODE);
      }

      if ((BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event) ||
          (EVENT_SYSTEM_LEARNMODE_START == (EVENT_SYSTEM)event))
      {
        if (EINCLUSIONSTATE_EXCLUDED != g_pAppHandles->pNetworkInfo->eInclusionState){
          DPRINT("LEARN_MODE_EXCLUSION\n");
          ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_EXCLUSION_NWE);
        }
        else{
          DPRINT("LEARN_MODE_INCLUSION\n");
          ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION);
        }
        Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
        ChangeState(STATE_APP_LEARN_MODE);
      }

      // Handle received  event
      if (EVENT_TRANSITION_TO_ACTIVE(event))
      {
        ZAF_PM_StayAwake(&m_RadioPowerLock, 0);
        DPRINT("\n");
        DPRINT("      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*\n");
        DPRINT("      *!*!*        EVENT ACTIVE          *!*!*\n");
        DPRINT("      *!*!**!*!**!*!**!*!**!*!**!*!**!*!**!*!*\n");
        DPRINT("\n");
        ChangeState(STATE_APP_TRANSMIT_DATA);

        if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB))
        {
          DPRINT("** EVENT_APP_NEXT_EVENT_JOB fail\n");
        }
        /*Add event's on job-queue*/
        ZAF_JobHelperJobEnqueue(EVENT_APP_BASIC_START_JOB);
        ZAF_JobHelperJobEnqueue(EVENT_APP_START_TIMER_EVENTJOB_STOP);
      }
      break;

    case STATE_APP_LEARN_MODE:
      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        LoadConfiguration();
      }

      if ((BTN_EVENT_SHORT_PRESS(APP_BUTTON_LEARN_RESET) == (BUTTON_EVENT)event) ||
          (EVENT_SYSTEM_LEARNMODE_STOP == (EVENT_SYSTEM)event))
      {
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_DISABLE);

        //Go back to smart start if the node was never included.
        //Protocol will not commence SmartStart if the node is already included in the network.
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

        Board_IndicateStatus(BOARD_STATUS_IDLE);
        ChangeState(STATE_APP_IDLE);

        /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
        CC_Indicator_RefreshIndicatorProperties();
        ZAF_TSE_Trigger(CC_Indicator_report_stx,
                        (void *)&ZAF_TSE_localActuationIdentifyData,
                        true);
      }

      if (EVENT_SYSTEM_LEARNMODE_FINISHED == (EVENT_SYSTEM)event)
      {
        //Make sure that the application stays awake for 10 s after learn mode finished
        //to wait for more messages from the controller
        CC_WakeUp_stayAwake10s();

        /* Also tell application to automatically extend the stay awake period by 10
         * seconds on message activities - even though we did not get here by a proper
         * wakeup from EM4
         */
        CC_WakeUp_AutoStayAwakeAfterInclusion();

        //Go back to smart start if the node was excluded.
        //Protocol will not commence SmartStart if the node is already included in the network.
        ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

        Board_IndicateStatus(BOARD_STATUS_IDLE);
        ChangeState(STATE_APP_IDLE);

        /* If we are in a network and the Identify LED state was changed to idle due to learn mode, report it to lifeline */
        CC_Indicator_RefreshIndicatorProperties();
        ZAF_TSE_Trigger(CC_Indicator_report_stx,
                        (void *)&ZAF_TSE_localActuationIdentifyData,
                        true);

        // Start the wakeup timer if the learn mode operation finished in Included state
        if (EINCLUSIONSTATE_EXCLUDED != g_pAppHandles->pNetworkInfo->eInclusionState)
        {
          CC_WakeUp_startWakeUpNotificationTimer();
        }
      }
      break;

    case STATE_APP_RESET:
      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        /* Soft reset */
        Board_ResetHandler();
      }
      break;

    case STATE_APP_TRANSMIT_DATA:
      if(EVENT_APP_FLUSHMEM_READY == event)
      {
        AppResetNvm();
        LoadConfiguration();
      }

      if (EVENT_APP_NEXT_EVENT_JOB == event)
      {
        uint8_t event;
        /*check job-queue*/
        if (true == ZAF_JobHelperJobDequeue(&event))
        {
          /*Let the event scheduler fire the event on state event machine*/
          ZAF_EventHelperEventEnqueue(event);
        }
        else
        {
          DPRINT("  Enqueuing event: EVENT_APP_FINISH_EVENT_JOB\n");
          ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
        }
      }

      if (EVENT_APP_BASIC_START_JOB == event)
      {
        if (JOB_STATUS_SUCCESS != CC_Basic_Set_tx( &agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, BASIC_SET_TRIGGER_VALUE, ZCB_JobStatus))
        {
          DPRINT("EVENT_APP_BASIC_START_JOB failed\n");
          basicValue = BASIC_SET_TRIGGER_VALUE;
          /*Kick next job*/
          ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
        }
      }

      if (EVENT_APP_BASIC_STOP_JOB == event)
      {
        if (JOB_STATUS_SUCCESS != CC_Basic_Set_tx( &agiTableRootDeviceGroups[0].profile, ENDPOINT_ROOT, 0, ZCB_JobStatus))
        {
          DPRINT("EVENT_APP_BASIC_STOP_JOB failed\n");
          basicValue = 0;
          /*Kick next job*/
          ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
        }
      }

      if (EVENT_APP_START_TIMER_EVENTJOB_STOP== event)
      {
        DPRINT("#EVENT_APP_START_TIMER_EVENTJOB_STOP\n");
        AppTimerEm4PersistentStart(&EventJobsTimer, BASIC_SET_TIMEOUT);
      }

      if (EVENT_APP_FINISH_EVENT_JOB == event)
      {
        ChangeState(STATE_APP_IDLE);
      }
      DPRINTF("STATE_APP_TRANSMIT_DATA done (state: %d)\n", currentState);
      break;

    default:
      // Do nothing.
      DPRINT("AppStateHandler(): Case is not handled!!!\n");
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
  DPRINTF("State changed: %d -> %d\n", currentState, newState);

  currentState = newState;
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

    EQueueNotifyingStatus Status = QueueNotifyingSendToBack(g_pAppHandles->pZwCommandQueue, (uint8_t*)&CommandPackage, 500);
    ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == Status);
  }
}

/**
 * @brief Reset delay callback.
 */
void
DeviceResetLocally(void)
{
  DPRINT("Call locally reset\n");

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
  if (bFirmwareNumber == 0)
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
 * @brief Callback function used for unsolicited commands.
 * @param pTransmissionResult Result of each transmission.
 */
void
ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINT("Callback: ZCB_JobStatus()\n");
  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
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
  Ecode_t errCode;
  cc_configuration_t const* cc_configuration_defaults;

  DPRINT("Set Default Configuration\n");
  AssociationInit(true, pFileSystemApplication);

  CC_WakeUp_notificationMemorySetDefault(pFileSystemApplication);
  DPRINT("Ended Set Default Configuration\n");

  loadInitStatusPowerLevel();

  cc_configuration_defaults = sl_configuration_get_configuration_pool();
  sl_cc_configuration_init(cc_configuration_defaults, &configuration_io_interface);

  uint32_t appVersion = ZAF_GetAppVersion();
  errCode = nvm3_writeData(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);
  ASSERT(ECODE_NVM3_OK == errCode); //Assert has been kept for debugging , can be removed from production code if this error can only be caused by some internal flash HW failure
}

/**
 * @brief This function loads the application settings from non-volatile memory.
 * If no settings are found, default values are used and saved.
 */
bool
LoadConfiguration(void)
{
  cc_configuration_t const* cc_configuration_defaults;

  cc_configuration_defaults     = sl_configuration_get_configuration_pool();

  sl_cc_configuration_init(cc_configuration_defaults, &configuration_io_interface);

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

    loadStatusPowerLevel();
    return true;
  }
  else
  {
    DPRINT("Application FileSystem Verify failed\n");
    loadInitStatusPowerLevel();

    // Reset the file system if ZAF_FILE_ID_APP_VERSION is missing since this indicates
    // corrupt or missing file system.
    AppResetNvm();
    return false;
  }
}

void AppResetNvm(void)
{
  DPRINT("Resetting application FileSystem to default\n");

  ASSERT(0 != pFileSystemApplication); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  Ecode_t errCode = nvm3_eraseAll(pFileSystemApplication);
  ASSERT(ECODE_NVM3_OK == errCode); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  /* Apparently there is no valid configuration in NVM3, so load */
  /* default values and save them. */
  SetDefaultConfiguration();

  AppTimerEm4PersistentResetStorage();
}

/**
 * @brief Handler for basic get. Handles received basic get commands.
 */
uint8_t
CC_Basic_GetTargetValue_handler(uint8_t endpoint)
{
  /* CHANGE THIS - Fill in your application code here */
  UNUSED(endpoint);
  return basicValue;
}

/**
 * @brief Report the target value
 * @return target value.
 */
uint8_t
CC_Basic_GetCurrentValue_handler(uint8_t endpoint)
{
  UNUSED(endpoint);
  /* CHANGE THIS - Fill in your application code here */
  return 0;
}

/**
 * @brief Report transition duration time.
 * @return duration time.
 */
uint8_t
CC_Basic_GetDuration_handler(uint8_t endpoint)
{
  UNUSED(endpoint);
  /* CHANGE THIS - Fill in your application code here */
  return 0;
}

/**
 * @brief event jobs timeout event
 *
 * @param pTimer Timer connected to this method
 */
void
ZCB_EventJobsTimer(SSwTimer *pTimer)
{
  DPRINTF("Timer callback: ZCB_EventJobsTimer() pTimer->Id=%d\n", pTimer->Id);

  /* If the node has been woken up from EM4 because the event job timer timed out
   * the app will now be in the state STATE_APP_STARTUP. Need to switch to
   * STATE_APP_TRANSMIT_DATA to properly process the job events
   */
  ZAF_JobHelperJobEnqueue(EVENT_APP_BASIC_STOP_JOB);

  if (STATE_APP_TRANSMIT_DATA != currentState)
  {
    ChangeState(STATE_APP_TRANSMIT_DATA);
    ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  }
  UNUSED(pTimer);
}

uint16_t handleFirmWareIdGet(uint8_t n)
{
  if (n == 0)
  {
    // Firmware 0
    return APP_FIRMWARE_ID;
  }
  // Invalid Firmware number
  return 0;
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
  DPRINTF(" uuID: %x\n", (uint32_t)uuID);
  *(pDeviceIDData + 0) = (uint8_t)(uuID >> 56);
  *(pDeviceIDData + 1) = (uint8_t)(uuID >> 48);
  *(pDeviceIDData + 2) = (uint8_t)(uuID >> 40);
  *(pDeviceIDData + 3) = (uint8_t)(uuID >> 32);
  *(pDeviceIDData + 4) = (uint8_t)(uuID >> 24);
  *(pDeviceIDData + 5) = (uint8_t)(uuID >> 16);
  *(pDeviceIDData + 6) = (uint8_t)(uuID >>  8);
  *(pDeviceIDData + 7) = (uint8_t)(uuID >>  0);
}

static bool
cc_configuration_io_write(nvm3_ObjectKey_t file_id, uint8_t const* data, size_t size)
{
  Ecode_t nvm3_return_value = ECODE_NVM3_ERR_PARAMETER;

  if((pFileSystemApplication != NULL) && (data != NULL) && (size > 0))
  {
    nvm3_return_value = nvm3_writeData( pFileSystemApplication,
                                        file_id,
                                        data,
                                        size);
  }
  return (nvm3_return_value == ECODE_NVM3_OK)?true:false;
}

static bool
cc_configuration_io_read(nvm3_ObjectKey_t file_id, uint8_t *data, size_t size)
{
  Ecode_t nvm3_return_value = ECODE_NVM3_ERR_PARAMETER;

  if((pFileSystemApplication != NULL) && (data != NULL) && (size > 0))
  {
    nvm3_return_value = nvm3_readData(pFileSystemApplication,
                                      file_id,
                                      data,
                                      size);
  }

  return (nvm3_return_value == ECODE_NVM3_OK)?true:false;
}
