/***************************************************************************//**
 * @file key_fob_app.c
 * @brief key_fob_app.c
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

/****************************************************************************/
/* INCLUDES                                                                 */
/****************************************************************************/

// System includes
#include <string.h>

#include "zw_config_rf.h"
#include "config_app.h"

#include <DebugPrintConfig.h>
//#define DEBUGPRINT
#include <DebugPrint.h>

#include <ZAF_Common_interface.h>
#include <ZAF_PM_Wrapper.h>
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>
#include <zaf_config_api.h>
#include <ZW_classcmd.h>
#include <ZW_TransportLayer.h>
#include <ZW_controller_api.h>
#include <ZW_system_startup_api.h>
#include <EventDistributor.h>
#include <SizeOf.h>
#include <AppTimer.h>
#include <KeyFob_hw.h>
#include <board_indicator.h>
#include <em_emu.h>
#include <em_wdog.h>
#include "events.h"

// Command Classes
#include <CC_Battery.h>
#include <ZAF_file_ids.h>
#include <ZAF_network_management.h>

#include "network_management.h"
#include "node_storage.h"
#include "zw_region_config.h"
#include "zw_build_no.h"

#include "sl_status.h"
#include "zw_region_config.h"
#include "zw_build_no.h"

#include "zpal_nvm.h"
#include "ZAF_nvm_app.h"
#include <stdio.h>
#include <zpal_misc.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/**
 * Due to a design choice in PowerManager.c for the implementation of PM_StayAwake(),
 * it is not possible to invoke the function with 0 (forever awake) if the the timer
 * is already running.
 * The below definition overcomes it.
 */
#define PM_STAY_AWAKE_DURATION_ONE_DAY      (1000 * 3600 * 24)  // [ms] 1 day (Used as indefinite keep-awake, but with secu)
#define PM_STAY_AWAKE_DURATION_TEN_MINUTES  (1000 * 60 * 10)
#define PM_STAY_AWAKE_DURATION_REBOOT       (1000 * 4)          // [ms]
#define PM_STAY_AWAKE_DURATION_BTN          (1000 * 15)         // [ms]
#define PM_STAY_AWAKE_DURATION_LEARN_MODE   (1000 * 10)         // [ms]

/**
 * Application states. Function AppStateManager(..) includes the state
 * event machine.
 */
typedef enum _STATE_APP_
{
  STATE_APP_STARTUP,            /**< STATE_APP_STARTUP */
  STATE_APP_IDLE,               /**< STATE_APP_IDLE */
  STATE_APP_INCLUDE_EXCLUDE,    /**< STATE_APP_INCLUDE_EXCLUDE */
  STATE_APP_ASSOCIATION,        /**< STATE_APP_ASSOCIATION */
  STATE_APP_TRANSMIT_DATA,      /**< STATE_APP_TRANSMIT_DATA */
  STATE_APP_NETWORK_LEARNMODE,  /**< STATE_APP_NETWORK_LEARNMODE */
} STATE_APP;

#define BASIC_SET_TRIGGER_VALUE       0xFF
#define BASIC_CLEAR_TRIGGER_VALUE     0x00

/**
 *
 * Note: enum order is important, should be in sync with g_aEventHandlerTable elements
 */
typedef enum EApplicationEvent
{
  EAPPLICATIONEVENT_TIMER = 0,
  EAPPLICATIONEVENT_ZWRX,
  EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
  EAPPLICATIONEVENT_APP,
  EAPPLICATIONEVENT_STATECHANGE,
} EApplicationEvent;

/****************************************************************************/
/*                        STATIC FUNCTION DECLARATION                       */
/****************************************************************************/

/**
 * Handler for Configuration CC get info command
 * @param[in] pRxOpt Receive options.
 * @param[in] pCmd Payload including command class.
 * @param[in] cmdLength Length of the received command.
 * @return Result of command parsing.
*/

/**
 * Task for initialize
 * @param[in] pAppHandles Application handle
 * @return None
*/
static void ApplicationTask(SApplicationHandles* pAppHandles);

/**
 * Task for handling receiving data
 * @param[in] None
 * @return None
*/
static void EventHandlerZwRx(void);

/**
 * Task for processing commands received through Z-Wave
 * @param[in] None
 * @return None
*/
static void EventHandlerZwCommandStatus(void);

/**
 * Handle state change
 * @param[in] None
 * @return None
*/
static void KeyFobStateHandler(void);

/**
 * Set state and notify the Queue
 * @param[in] state is the new state to set
 * @return None
*/
static void ChangeState(STATE_APP newState);

static uint8_t SetRFReceiveMode(uint8_t mode);

static uint8_t GetCommandResponse(SZwaveCommandStatusPackage *pCmdStatus, EZwaveCommandStatusType cmdType);

static void EventHandlerApp(void);

static void EventQueueInit();

SBatteryData readBatteryData(void);

/**
 * Handler for application related tasks, called from button push
 * @param[in] pRxOpt Receive options.
 * @return Result of command parsing.
*/
static void AppStateManager(EVENT_APP event);

static void handle_network_management_states(node_id_t current_node_id);

void SendDeviceResetLocally(void);

/****************************************************************************/
/* Application specific button and LED definitions                          */
/****************************************************************************/

static const EventDistributorEventHandler g_aEventHandlerTable[] =
{
  AppTimerNotificationHandler,   // EAPPLICATIONEVENT_TIMER           = 0
  EventHandlerZwRx,              // EAPPLICATIONEVENT_ZWRX            = 1
  EventHandlerZwCommandStatus,   // EAPPLICATIONEVENT_ZWCOMMANDSTATUS = 2
  EventHandlerApp,               // EAPPLICATIONEVENT_APP             = 3
  KeyFobStateHandler // EAPPLICATIONEVENT_STATECHANGE     = 4
};

static zpal_pm_handle_t m_RadioPowerLock;
static zpal_pm_handle_t m_PeripheralPowerLock;

static TaskHandle_t g_AppTaskHandle;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

static const uint8_t SecureKeysRequested = REQUESTED_SECURITY_KEYS;

static SRadioConfig_t RadioConfig = {
  .iListenBeforeTalkThreshold = ELISTENBEFORETALKTRESHOLD_DEFAULT,
  .iTxPowerLevelMax    = APP_MAX_TX_POWER,
  .iTxPowerLevelAdjust = APP_MEASURED_0DBM_TX_POWER,
  .iTxPowerLevelMaxLR  = APP_MAX_TX_POWER_LR,
  .eRegion   = ZW_REGION,
  .radio_debug_enable = ENABLE_RADIO_DEBUG
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListNonSecureNotIncluded[] =
{
  COMMAND_CLASS_ZWAVEPLUS_INFO,
  COMMAND_CLASS_TRANSPORT_SERVICE_V2,
  COMMAND_CLASS_BATTERY,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_SECURITY,
  COMMAND_CLASS_SECURITY_2,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
  COMMAND_CLASS_SUPERVISION,
  COMMAND_CLASS_VERSION
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
  COMMAND_CLASS_SUPERVISION,
};

/**
 * Please see the description of app_node_information_t.
 */
static uint8_t cmdClassListSecure[] =
{
  COMMAND_CLASS_BATTERY,
  COMMAND_CLASS_VERSION,
  COMMAND_CLASS_MANUFACTURER_SPECIFIC,
  COMMAND_CLASS_DEVICE_RESET_LOCALLY,
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

static SAppNodeInfo_t AppNodeInfo = {
  .CommandClasses.UnSecureIncludedCC.iListLength = sizeof_array(cmdClassListNonSecureNotIncluded),
  .CommandClasses.UnSecureIncludedCC.pCommandClasses = cmdClassListNonSecureNotIncluded,
  .CommandClasses.SecureIncludedUnSecureCC.iListLength = sizeof_array(cmdClassListNonSecureIncludedSecure),
  .CommandClasses.SecureIncludedUnSecureCC.pCommandClasses = cmdClassListNonSecureIncludedSecure,
  .CommandClasses.SecureIncludedSecureCC.iListLength = sizeof_array(cmdClassListSecure),
  .CommandClasses.SecureIncludedSecureCC.pCommandClasses = cmdClassListSecure,
  .NodeType.generic  = GENERIC_TYPE_GENERIC_CONTROLLER,
  .NodeType.specific = SPECIFIC_TYPE_PORTABLE_REMOTE_CONTROLLER,
  .DeviceOptionsMask = APPLICATION_NODEINFO_NOT_LISTENING
};

static const SProtocolConfig_t ProtocolConfig = {
    .pVirtualSlaveNodeInfoTable = NULL,
    .pSecureKeysRequested = &SecureKeysRequested,
    .pNodeInfo    = &AppNodeInfo,
    .pRadioConfig = &RadioConfig
};

static SEventDistributor g_EventDistributor;

/**
 * Application state-machine state.
 */
static STATE_APP currentState = STATE_APP_IDLE;

/**
 * Parameter is used to save wakeup reason after ApplicationInit(..)
 */
static EResetReason_t g_eResetReason;

//static SSwTimer EventJobsTimer;
static SSwTimer JobTimer;

#define APP_EVENT_QUEUE_SIZE          5

/**
 * The following four variables are used for the application event queue.
 */
static SQueueNotifying m_AppEventNotifyingQueue;
static StaticQueue_t m_AppEventQueueObject;
static EVENT_APP eventQueueStorage[APP_EVENT_QUEUE_SIZE];
static QueueHandle_t m_AppEventQueue;

static zpal_nvm_handle_t pFileSystemApplication;

/****************************************************************************/
/* MACRO                                                                    */
/****************************************************************************/

#define STOP_LEARNMODE()              Board_IndicateStatus(BOARD_STATUS_IDLE);  \
                                      ChangeState(STATE_APP_IDLE);              \
                                      zpal_pm_stay_awake(m_RadioPowerLock, 10)

#define PRINT_SUPPORTED_COMMAND_CLASSES();                                                  \
                                      if (CcListLength && pCcList)                                     \
                                      {                                                     \
                                        DPRINT("Supported command classes:\n\t");           \
                                        for (uint8_t cnt = 0; cnt < CcListLength; cnt++)    \
                                        {                                                   \
                                          DPRINTF("%X ", pCcList[cnt]);                     \
                                        }                                                   \
                                        DPRINT("\n");                                       \
                                      }

/****************************************************************************/
/* Static Functions                                                         */
/****************************************************************************/
#if defined(DEBUGPRINT) && defined(BUILDING_WITH_UC)
#include "sl_iostream.h"
static void DebugPrinter(const uint8_t * buffer, uint32_t len)
{
  sl_iostream_write(SL_IOSTREAM_STDOUT, buffer, len);
}
#endif

ZW_APPLICATION_STATUS
ApplicationInit(EResetReason_t eResetReason)
{

  /* Initialize the radio board (SAW filter setup, etc) */
  /* hardware initialization */
  Board_Init();

#ifdef DEBUGPRINT
#if BUILDING_WITH_UC
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), DebugPrinter);
#else
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
#endif // BUILDING_WITH_UC
#endif // DEBUGPRINT

  DPRINT("\n\n===ApplicationInit===\n");

  /* g_eResetReason now contains latest System Reset reason */
  g_eResetReason = eResetReason;

  /* Init state machine*/
  currentState = STATE_APP_STARTUP;

  DPRINT("\n-----------------------------\n");
  DPRINT("Z-Wave Sample App: KeyFob\n");
  DPRINTF("\nSDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);

  DPRINTF("ApplicationInit eResetReason = %d (0/7 = PIN/SW, 1 = EM4_WUT)\n", g_eResetReason);

  // Init file system
  ApplicationFileSystemInit(&pFileSystemApplication);


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

  return APPLICATION_RUNNING; /*Return false to enter production test mode*/
}

/**
 * The callback functions that will be called as the last step just before the
 * chip enters EM4 hibernate.
 *
 * NB: When the function is called the OS tick has been disabled and the FreeRTOS
 *     scheduler is no longer running. OS features like events, queues and timers
 *     are therefore unavailable and must not be called from the callback function.
 *
 *     The callback functions can be used to set pins and write to retention RAM.
 *     Do NOT try to write to the NVM file system.
 *
 * The maximum number of functions that can be registered is given by the macro
 * MAX_POWERDOWN_CALLBACKS in ZW_PowerManager_api.h
 */
static void powerDownCB(void)
{
  DPRINT("powerDownCB() - Powering down\n");
}

static void
ZCB_JobTimeout(SSwTimer *pTimer)
{
  UNUSED(pTimer);
  DPRINT("ZCB_JobTimeout\n");
  if (NETWORK_MANAGEMENT_STATE_ADD_GROUP == get_current_network_management_state() ||
      NETWORK_MANAGEMENT_STATE_REMOVE_GROUP == get_current_network_management_state())
  {
    DPRINT("ZCB: Add/Remove group timeout\n");
    // Timeout
    ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
    KeyFob_group_add_Led_handler(false);
    KeyFob_group_remove_Led_handler(false);
  } 
  else if (NETWORK_MANAGEMENT_STATE_START_INCLUSION == get_current_network_management_state() ||
      NETWORK_MANAGEMENT_STATE_START_EXCLUSION == get_current_network_management_state())
  {
    DPRINT("ZCB: Network Add/Remove timeout\n");
    Board_IndicateStatus(BOARD_STATUS_LEARNMODE_INACTIVE);
    handle_network_management_states(0);
  }
  else if (NETWORK_MANAGEMENT_STATE_LEARNMODE == get_current_network_management_state())
  {
    DPRINT("ZCB: Network LearnMode timeout\n");
    handle_network_management_states(0);
  }
}

static __attribute__((noreturn)) void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  DPRINT("\n\n===========ApplicationTask============\n");

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

  g_AppTaskHandle = xTaskGetCurrentTaskHandle();
  g_pAppHandles = pAppHandles;

  ZAF_Init(g_AppTaskHandle, pAppHandles, &ProtocolConfig, NULL);
  ZAF_setApplicationData(g_AppTaskHandle, pAppHandles,  &ProtocolConfig);

  EventQueueInit();  // Initialize the slew of modules made for event management.

  // Init AppTimer with an app handle
  AppTimerInit(EAPPLICATIONEVENT_TIMER, g_AppTaskHandle);

  AppTimerRegister(&JobTimer, false, ZCB_JobTimeout);

  // Setup power management.
  m_RadioPowerLock = zpal_pm_register(ZPAL_PM_TYPE_USE_RADIO);

  if ((ERESETREASON_DEEP_SLEEP_WUT != g_eResetReason) &&
      (ERESETREASON_DEEP_SLEEP_EXT_INT != g_eResetReason))
  {
    zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_REBOOT);  // Allowing time for choosing learnmode after reset.
  }
  ZAF_PM_SetPowerDownCallback(powerDownCB);

  // Generate event that says the APP needs additional initialization.
  ZAF_EventHelperEventEnqueue(EVENT_APP_INIT);  // The state is already set to STATE_APP_STARTUP.


  //Initialize buttons
  KeyFob_hw_init(g_eResetReason);

  Board_IndicatorInit();
  
  EventDistributorConfig(
      &g_EventDistributor,
      sizeof_array(g_aEventHandlerTable),
      g_aEventHandlerTable,
      KeyFobStateHandler);

  DPRINTF("IsWakeupCausedByRtccTimeout = %s\n", (IsWakeupCausedByRtccTimeout()) ? "true" : "false");
  DPRINTF("CompletedSleepDurationMs    = %u\n", GetCompletedSleepDurationMs());

  // This will start additional initialization of the app after the FreeRTOS tasks have started executing.
  ChangeState(STATE_APP_STARTUP);


  /**************************************************************
   * The below approach prevents the system from going to a sleep
   * mode that requires wake up from reset state.
   * (Not supported yet.)
   **************************************************************/
  m_PeripheralPowerLock = zpal_pm_register(ZPAL_PM_TYPE_DEEP_SLEEP);

  zpal_pm_stay_awake(m_PeripheralPowerLock, 0);
  /***********************************************************/


  // Wait for and process events
  DPRINT("KeyFob Event processor Started\n");
  uint32_t iMaxTaskSleep = 0xFFFFFFFF;
  for (;;)
  {
    EventDistributorDistribute(&g_EventDistributor, iMaxTaskSleep, 0);
  }
}


static void
SetProtocolDefault(uint8_t status, const TX_STATUS_TYPE * status_type)
{
  UNUSED(status);
  UNUSED(status_type);
  DPRINTF("%s status=%d\n", __func__, status);

  /* Reset protocol  regardless of TRANSMIT status */
  DPRINT("\nDisabling watchdog during reset\n");
  zpal_enable_watchdog(false);

  DPRINT("Resetting protocol FileSystem to default\n");
  SZwaveCommandPackage CommandPackage;
  CommandPackage.eCommandType = EZWAVECOMMANDTYPE_SET_DEFAULT;

  if (EQUEUENOTIFYING_STATUS_SUCCESS != QueueNotifyingSendToBack(g_pAppHandles->pZwCommandQueue,
                                                                 (uint8_t*) &CommandPackage,
                                                                 500))
  {
    DPRINT("Warning: Failed to perform SetDefault");
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
  zpal_status_t errCode;

  uint32_t appVersion = zpal_get_app_version();
  errCode = zpal_nvm_write(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);
  ASSERT(ZPAL_STATUS_OK == errCode); //Assert has been kept for debugging , can be removed from production code if this error can only be caused by some internal flash HW failure

  // Set default Basic Set Group - no members
  node_storage_init_group();
}


void AppResetNvm(void)
{
  DPRINT("Resetting application FileSystem to default\n");

  ASSERT(0 != pFileSystemApplication); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  zpal_status_t errCode = zpal_nvm_erase_all(pFileSystemApplication);
  ASSERT(ZPAL_STATUS_OK == errCode); //Assert has been kept for debugging , can be removed from production code. This error can only be caused by some internal flash HW failure

  /* Apparently there is no valid configuration in NVM, so load */
  /* default values and save them. */
  SetDefaultConfiguration();
}


/**
 * @brief This function loads the application settings from non-volatile memory.
 * If no settings are found, default values are used and saved.
 */
bool
LoadConfiguration(void)
{
  uint32_t appVersion;
  zpal_status_t versionFileStatus = zpal_nvm_read(pFileSystemApplication, ZAF_FILE_ID_APP_VERSION, &appVersion, ZAF_FILE_SIZE_APP_VERSION);

  if (ZPAL_STATUS_OK == versionFileStatus)
  {
    if (zpal_get_app_version() != appVersion)
    {
      DPRINT("ERROR: App-version did not match the app-version stored on NVM.\n");
      // Add code for migration of file system to higher version here.
    }

    // End Device node IDs in Basic Set Association group will be stored in non volatile memory
    node_storage_init_group();

    return true;
  }
  else
  {
    DPRINT("Application FileSystem Verify failed\n");

    pFileSystemApplication = ZAF_GetFileSystemHandle();
    // Reset the file system if ZAF_FILE_ID_APP_VERSION is missing since this indicates
    // corrupt or missing file system.
    AppResetNvm();
    return false;
  }
}

static void stayAwake(void)
{
  /* Don't sleep the next 10 seconds */
  zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_LEARN_MODE);
}

static void doRemainingInitialization()
{
  DPRINT("--> doRemainingInitialization()\n");

  /* Load the application settings from NVM file system */
  bool filesExist = LoadConfiguration();
  UNUSED(filesExist);

  /* Re-load and process EM4 persistent application timers.
   * NB: Before calling AppTimerEm4PersistentLoadAll here, all
   *     application timers must have been registered with
   *     AppTimerRegister() or AppTimerEm4PersistentRegister().
   *     Essentially it means that all CC handlers must be
   *     initialized first.
   */
//  AppTimerEm4PersistentLoadAll(g_eResetReason);

  /*
   * Initialize Event Scheduler.
   */
  Transport_OnApplicationInitSW( &m_AppNIF, stayAwake);


  DPRINTF("g_eResetReason: 0x%08x\n", g_eResetReason);
  if (ERESETREASON_DEEP_SLEEP_EXT_INT == g_eResetReason)
  {
    DPRINT("ERESETREASON_DEEP_SLEEP_EXT_INT\n");
    uint32_t em4_wakeup_flags = Board_GetGpioEm4Flags();

    if (0 != em4_wakeup_flags)
    {
      Board_ProcessEm4PinWakeupFlags(em4_wakeup_flags);
    }
    ChangeState(STATE_APP_IDLE);
  }

  if ((ERESETREASON_DEEP_SLEEP_WUT == g_eResetReason) && (STATE_APP_TRANSMIT_DATA != currentState))
  {
    ChangeState(STATE_APP_IDLE);
  }

  if(ERESETREASON_PIN == g_eResetReason ||
     ERESETREASON_BROWNOUT == g_eResetReason ||
     ERESETREASON_POWER_ON == g_eResetReason ||
     ERESETREASON_SOFTWARE == g_eResetReason ||
     ERESETREASON_WATCHDOG == g_eResetReason)
  {
    /* Init state machine*/
    ZAF_EventHelperEventEnqueue(EVENT_EMPTY);
  }
}


static void EventHandlerZwRx(void)
{
  DPRINT("EventHandlerZwRx()\n");

  const SApplicationHandles* pAppHandle = ZAF_getAppHandle();
  QueueHandle_t Queue = pAppHandle->ZwRxQueue;
  SZwaveReceivePackage RxPackage;

  // Handle incoming replies
  while (xQueueReceive(Queue, (uint8_t *)(&RxPackage), 0) == pdTRUE)
  {
    DPRINTF("Incoming Rx %x\n", RxPackage.eReceiveType);

    switch (RxPackage.eReceiveType)
    {
      case EZWAVERECEIVETYPE_SINGLE:
        DPRINT("-->EZWAVERECEIVETYPE_SINGLE\n");
        break;
      case EZWAVERECEIVETYPE_SECURE_FRAME_RECEIVED:
        ApplicationCommandHandler(NULL, &RxPackage);
      break;

      case EZWAVERECEIVETYPE_NODE_UPDATE:
        DPRINT("-->EZWAVERECEIVETYPE_NODE_UPDATE\n");
        if (NETWORK_MANAGEMENT_STATE_ADD_GROUP == get_current_network_management_state())
        {
          DPRINTF("Adding %u to group\n", RxPackage.uReceiveParams.RxNodeUpdate.NodeId);
          node_storage_add_group_member_nodeid(RxPackage.uReceiveParams.RxNodeUpdate.NodeId);
          ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
        }
        if (NETWORK_MANAGEMENT_STATE_REMOVE_GROUP == get_current_network_management_state())
        {
          DPRINTF("Removing %u from group\n", RxPackage.uReceiveParams.RxNodeUpdate.NodeId);
          node_storage_remove_group_member_nodeid(RxPackage.uReceiveParams.RxNodeUpdate.NodeId);
          ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
        }
        break;

      case EZWAVERECEIVETYPE_STAY_AWAKE:
        DPRINT("-->EZWAVERECEIVETYPE_STAY_AWAKE\n");
        /*
         * Non-application frame was received, that must keep device awake.
         */
        break;

      default:
        DPRINTF("-->Invalid Receive Type: %d\n", RxPackage.eReceiveType);
        break;
    }
  }
}

static void KeyFobStateHandler(void)
{
  DPRINT("KeyFobStateHandler()\n");

  switch (currentState)
  {
    case STATE_APP_STARTUP:
      SetRFReceiveMode(1);
      break;

    case STATE_APP_IDLE:
      break;

    default:
      DPRINT("KeyFobStateHandler - Default case\n\n\n");
      break;
  }
}


static void EventHandlerZwCommandStatus(void)
{
  DPRINT("EventHandlerZwCommandStatus()\n");

  const SApplicationHandles* pAppHandle = ZAF_getAppHandle();
  const QueueHandle_t Queue = pAppHandle->ZwCommandStatusQueue;
  SZwaveCommandStatusPackage Status;
  node_id_t sourceNode;

  // Handle incoming replies
  while (xQueueReceive(Queue, (uint8_t *)(&Status), 0) == pdTRUE)
  {
    DPRINTF("Incoming Status msg 0x%02x\n", Status.eStatusType);

    switch (Status.eStatusType)
    {
      case EZWAVECOMMANDSTATUS_SECURE_ON_NODE_ADDED:
        sourceNode = Status.Content.USecureAppNotification.nodeAddedNotification.node_id;
        DPRINTF("Included node: NodeID: %d\n", sourceNode);

        sl_status_t status = Status.Content.USecureAppNotification.nodeAddedNotification.status;
        if (SL_STATUS_OK != status)
        {
          DPRINTF("Inclusion Failed. Error: 0x%X\n", status);
        }
        else
        {
          uint8_t CcListLength =
              Status.Content.USecureAppNotification.nodeAddedNotification.nif.command_class_list_length;
          const uint16_t * pCcList =
              Status.Content.USecureAppNotification.nodeAddedNotification.nif.command_class_list;

          PRINT_SUPPORTED_COMMAND_CLASSES()
        }
        // This will stop the learnmode process.
        // Also end device is added to KeyFob Basic Set Group Association
        handle_network_management_states(sourceNode);
        DPRINT("Inclusion ended\n");
        break;

      case EZWAVECOMMANDSTATUS_SECURE_ON_NODE_DELETED:
        sourceNode = Status.Content.USecureAppNotification.nodeDeletedNotification.node_id;
        DPRINTF("Excluded Node: %d\n", sourceNode);

        // This will stop the learnmode process.
        handle_network_management_states(sourceNode);
        DPRINT("Exclusion ended\n");
        break;

      case EZWAVECOMMANDSTATUS_TX:
        DPRINT("-->EZWAVECOMMANDSTATUS_TX\n");
        SZWaveTransmitStatus *pTxStatus = &Status.Content.TxStatus;
        if ((pTxStatus->bIsTxFrameLegal) && (pTxStatus->Handle))
        {
          DPRINT("Tx Status received\n");

          void (*pCallback)(uint8_t, const TX_STATUS_TYPE *) = (void (*)(uint8_t,  const TX_STATUS_TYPE *))pTxStatus->Handle;
          pCallback(pTxStatus->TxStatus, &pTxStatus->ExtendedTxStatus);
        }
        else
        {
          // Drop it..
          DPRINT("Tx Status received - dropped\n");
        }
        break;
  
      case EZWAVECOMMANDSTATUS_SECURE_ON_NEW_NETWORK_ENTERED:
        ///< Node entered a new network
        DPRINTF("-->EZWAVECOMMANDSTATUS_SECURE_ON_NEW_NETWORK_ENTERED %08X, %u\n", Status.Content.USecureAppNotification.nodeEnteredNetwork.home_id, Status.Content.USecureAppNotification.nodeEnteredNetwork.node_id);
        handle_network_management_states(Status.Content.USecureAppNotification.nodeEnteredNetwork.node_id);
        break;

      case EZWAVECOMMANDSTATUS_SECURE_ON_NETWORK_MANAGEMENT_STATE_UPDATE:
        ///< Secure network management changed state
        DPRINTF("-->EZWAVECOMMANDSTATUS_SECURE_ON_NETWORK_MANAGEMENT_STATE_UPDATE %u\n", Status.Content.USecureAppNotification);
        if (0 == Status.Content.USecureAppNotification.nodeNetworkManagement.state)
        {
          handle_network_management_states(0);
        }
        break;

      case EZWAVECOMMANDSTATUS_SECURE_ON_NEW_SUC:
        ///< New SUC NodeID received
        DPRINT("-->EZWAVECOMMANDSTATUS_SECURE_ON_NEW_SUC\n");
        break;

      case EZWAVECOMMANDSTATUS_SECURE_ON_FRAME_TRANSMISSION:
        ///< Frame transmission result
        DPRINT("-->EZWAVECOMMANDSTATUS_SECURE_ON_FRAME_TRANSMISSION\n");
        break;

      case EZWAVECOMMANDSTATUS_SECURE_ON_RX_FRAME_RECEIVED_INDICATOR:
        ///< Frame received from NodeID indicator
        DPRINT("-->EZWAVECOMMANDSTATUS_SECURE_ON_RX_FRAME_RECEIVED_INDICATOR\n");
        break;

      case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
        DPRINT("-->EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS\n");
        break;

      case EZWAVECOMMANDSTATUS_SET_DEFAULT:
        DPRINT("-->EZWAVECOMMANDSTATUS_SET_DEFAULT\n");
        DPRINT("Portable Controller reset to Default\n");
        Board_ResetHandler();
        break;

      case EZWAVECOMMANDSTATUS_REPLACE_FAILED_NODE_ID:
        DPRINT("-->EZWAVECOMMANDSTATUS_REPLACE_FAILED_NODE_ID\n");
        break;

      case EZWAVECOMMANDSTATUS_REMOVE_FAILED_NODE_ID:
        DPRINT("-->EZWAVECOMMANDSTATUS_REMOVE_FAILED_NODE_ID\n");
        break;

      case EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST:
        DPRINT("-->EZWAVECOMMANDSTATUS_INVALID_TX_REQUEST\n");
        DPRINTF("Invalid TX Request to protocol - %d\n", Status.Content.InvalidTxRequestStatus.InvalidTxRequest);
        break;

      case EZWAVECOMMANDSTATUS_INVALID_COMMAND:
        DPRINT("-->EZWAVECOMMANDSTATUS_INVALID_COMMAND\n");
        DPRINTF("Invalid command to protocol - %d\n", Status.Content.InvalidCommandStatus.InvalidCommand);
        break;
      case EZWAVECOMMANDSTATUS_PM_SET_POWERDOWN_CALLBACK:
        DPRINT("-->EZWAVECOMMANDSTATUS_PM_SET_POWERDOWN_CALLBACK registered\n");
        break;

      default:
        DPRINTF("-->Unknown / Unexpected  CMD - %d\n", Status.eStatusType);
        ASSERT(false);
        break;
    }
  }
}

static void ChangeState(STATE_APP newState)
{
  if (currentState != newState)
  {
    DPRINTF("\nState changed: %d -> %d\n", currentState, newState);
    TimerStop(&JobTimer);
    xTaskNotify(g_AppTaskHandle,
                (1 << EAPPLICATIONEVENT_STATECHANGE),
                eSetBits);
    currentState = newState;
  }
}

static void
SendBasicSetToGroupCallback(
    uint8_t txStatus,
    const TX_STATUS_TYPE *txStatusType)
{
  UNUSED(txStatus);
  UNUSED(txStatusType);
  DPRINT("\nBasicSetDone\n");
  ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
  KeyFob_basic_off_Led_handler(false);  
  KeyFob_basic_on_Led_handler(false);
}


/* build a supervision get command
 * 
 * @param[out] getFrame   Buffer to store the built supervision get command
 * @param[out] getLen     The lenght of the built supervision get command
 * @param[in]  cmdFrame   The command to be encapsulated into the supervision get command
 * @param[in]  cmdLen     The lenght of the command to be encapsulated into the supervision get command
 */
static void BuildSupervisionGet(uint8_t  *getFrame,
                                uint16_t *getLen,
                                uint8_t  *cmdFrame,
                                uint8_t  cmdLen) 
{
  static uint8_t sv_session_id = 0;
  *getLen = 0;
  getFrame[(*getLen)++] = COMMAND_CLASS_SUPERVISION;
  getFrame[(*getLen)++] = SUPERVISION_GET;
  getFrame[(*getLen)++] = sv_session_id++ & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK;
  getFrame[(*getLen)++] = cmdLen;
  for (int8_t i = 0; i < cmdLen; i++) {
    getFrame[(*getLen)++] = cmdFrame[i];
  }
}

static uint8_t SendBasicSetToGroup(uint8_t value,  void (*pCallback)(uint8_t, const TX_STATUS_TYPE*))
{

  uint8_t nodesInGroup = node_storage_group_member_count();
  if (0 < nodesInGroup)
  {
    DPRINTF("\nBasicToGroup (%u nodes) value %u\n", nodesInGroup, value);

    /**
     * @attention
     * We will be sending a multicast to a list of nodes on our local group
     * maintained locally and with no dependency towards the ZAF.
     *
     * This group is persistently stored on NVM.
     */
	
    SZwaveTransmitPackage TransmitPackage;
    memset(&TransmitPackage, 0, sizeof(TransmitPackage));
    TransmitPackage.eTransmitType = EZWAVETRANSMITTYPE_SECURE;
    SSecureSendData *params = &TransmitPackage.uTransmitParams.SendDataParams;

    /* Set the destination node mask bits */
    node_storage_group_member_nodemask_get((uint8_t*)params->connection.remote.address.nodeList.nodeMask,
        sizeof(params->connection.remote.address.nodeList.nodeMask));

    params->connection.remote.is_multicast = true;
    params->tx_options.number_of_responses = 0;  // 0 for SET command.
    params->ptxCompleteCallback = pCallback;
    uint8_t basic_set_cmd[] = {COMMAND_CLASS_BASIC, BASIC_SET, value};
    // encapsulates basic set command into supervision get command    
    BuildSupervisionGet(params->data, &params->data_length, basic_set_cmd, sizeof(basic_set_cmd));

    // Put the package on queue (and don't wait for it)
    EQueueNotifyingStatus QueueStatus = QueueNotifyingSendToBack(g_pAppHandles->pZwTxQueue, (uint8_t*)&TransmitPackage, 0);
    if (EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus)
    {
      if (0 == value)
      {
        KeyFob_basic_off_Led_handler(true);
      }
      else
      {
        KeyFob_basic_on_Led_handler(true);
      }
      return true;
    }
    return false;
  }
  else
  {
    DPRINTF("Group Empty - Basic Set %s\n", value ? "ON" : "OFF");
    SendBasicSetToGroupCallback(0, NULL);
    return true;
  }
}

uint8_t IsPrimaryController(void)
{
  const SApplicationHandles *m_pAppHandles = ZAF_getAppHandle();
  SZwaveCommandPackage cmdPackage = {
      .eCommandType = EZWAVECOMMANDTYPE_IS_PRIMARY_CTRL};
  EQueueNotifyingStatus QueueStatus = QueueNotifyingSendToBack(m_pAppHandles->pZwCommandQueue, (uint8_t *)&cmdPackage, 500);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus);
  SZwaveCommandStatusPackage cmdStatus;
  if (GetCommandResponse(&cmdStatus, EZWAVECOMMANDSTATUS_IS_PRIMARY_CTRL))
  {
    return cmdStatus.Content.IsPrimaryCtrlStatus.result;
  }
  ASSERT(false);
  return 0;
}

/**
 * Sends Device Reset Locally Notification
 * @details Should only send notification if:
 * 1. Not a primary controller
 * 2. Has lifeline associations.
 */
void
SendDeviceResetLocally(void)
{
  if (IsPrimaryController())
  {
    DPRINTF("Primary controller. Skip Device Reset Locally Notification.\n");
    SetProtocolDefault(TRANSMIT_COMPLETE_OK, NULL);
    return;
  }

  uint8_t frame[] = {COMMAND_CLASS_DEVICE_RESET_LOCALLY, DEVICE_RESET_LOCALLY_NOTIFICATION};
  SZwaveTransmitPackage TransmitPackage;
  memset(&TransmitPackage, 0, sizeof(TransmitPackage));
  TransmitPackage.eTransmitType = EZWAVETRANSMITTYPE_SECURE;
  SSecureSendData *params = &TransmitPackage.uTransmitParams.SendDataParams;

  if (0 == node_storage_group_member_nodemask_get(
      (uint8_t*)params->connection.remote.address.nodeList.nodeMask,
      sizeof(params->connection.remote.address.nodeList.nodeMask)))
  {
    DPRINTF("No associations. Skip Device Reset Locally Notification.\n");
    SetProtocolDefault(TRANSMIT_COMPLETE_OK, NULL);
    return;
  }

  DPRINT("Send Device Reset Locally Notification\r\n");
  params->connection.remote.is_multicast = true;
  memcpy(params->data, frame, sizeof(frame));
  params->data_length = sizeof(frame);
  params->tx_options.number_of_responses = 0;
  params->ptxCompleteCallback = &SetProtocolDefault;

  if(EQUEUENOTIFYING_STATUS_SUCCESS != QueueNotifyingSendToBack(g_pAppHandles->pZwTxQueue, (uint8_t*)&TransmitPackage, 0))
  {
    DPRINT("Fail DEVICE_RESET_LOCALLY_NOTIFICATION\r\n");
    SetProtocolDefault(TRANSMIT_COMPLETE_FAIL, NULL);
  }
}

static uint8_t SetRFReceiveMode(uint8_t mode)
{
  DPRINTF("SetRFReceiveMode(%u)\n", mode);

  const SApplicationHandles* pAppHandle = ZAF_getAppHandle();
  SZwaveCommandPackage pCmdPackage = {
      .eCommandType = EZWAVECOMMANDTYPE_SET_RF_RECEIVE_MODE,
      .uCommandParams.SetRfReceiveMode.mode = mode};

  // Put the Command on queue (and dont wait for it, queue must be empty)
  EQueueNotifyingStatus QueueStatus = QueueNotifyingSendToBack(pAppHandle->pZwCommandQueue, (uint8_t *)&pCmdPackage, 0);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus);
  SZwaveCommandStatusPackage cmdStatus;
  if (GetCommandResponse(&cmdStatus, EZWAVECOMMANDSTATUS_SET_RF_RECEIVE_MODE))
  {
    return cmdStatus.Content.SetRFReceiveModeStatus.result;
  }

  return 0;
}


static uint8_t checkCommandType(TaskHandle_t pAppTaskHandle, QueueHandle_t Queue, SZwaveCommandStatusPackage *pCmdStatus, EZwaveCommandStatusType cmdType)
{
  if (pCmdStatus->eStatusType == cmdType)
  {
    if (pAppTaskHandle && (0 < uxQueueMessagesWaiting(Queue)))
    {
      /* Only call xTaskNotify if still elements in queue */
      BaseType_t Status = xTaskNotify(pAppTaskHandle, 1 << EAPPLICATIONEVENT_ZWCOMMANDSTATUS, eSetBits);
      ASSERT(pdPASS == Status); // We probably received a bad Task handle
    }
    return true;
  }
  else
  {
    BaseType_t result = xQueueSendToBack(Queue, (uint8_t*)pCmdStatus, 0);
    ASSERT(pdTRUE == result);
  }
  return false;
}


static uint8_t GetCommandResponse(SZwaveCommandStatusPackage *pCmdStatus, EZwaveCommandStatusType cmdType)
{
  const SApplicationHandles * m_pAppHandles = ZAF_getAppHandle();
  TaskHandle_t m_pAppTaskHandle = ZAF_getAppTaskHandle();
  QueueHandle_t Queue = m_pAppHandles->ZwCommandStatusQueue;
  if (!pCmdStatus)
  {
    return false;
  }
  for (uint8_t delayCount = 0; delayCount < 100; delayCount++)
  {
    for (UBaseType_t QueueElmCount = uxQueueMessagesWaiting(Queue);  QueueElmCount > 0; QueueElmCount--)
    {
      pCmdStatus->eStatusType = ~cmdType;
      BaseType_t queueStatus = xQueueReceive(Queue, (uint8_t*)pCmdStatus, 0);
      if ((pdPASS == queueStatus) && (true == checkCommandType(m_pAppTaskHandle, Queue, pCmdStatus, cmdType)))
      {
        // Found the needed cmdType
        return true ;
      }
    }
    vTaskDelay(10);
  }
  if (m_pAppTaskHandle && (0 < uxQueueMessagesWaiting(Queue)))
  {
    /* Only call xTaskNotify if still elements in queue */
    BaseType_t Status = xTaskNotify(m_pAppTaskHandle, 1 << EAPPLICATIONEVENT_ZWCOMMANDSTATUS, eSetBits);
    ASSERT(Status == pdPASS); // We probably received a bad Task handle
  }
  return false;
}


static void EventHandlerApp(void)
{
  uint8_t event;

  while (xQueueReceive(m_AppEventQueue, (uint8_t*)(&event), 0) == pdTRUE)
  {
    AppStateManager((EVENT_APP)event);
  }
}

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
   * the specific task about a pending job
   */
  QueueNotifyingInit(
      &m_AppEventNotifyingQueue,
      m_AppEventQueue,
      g_AppTaskHandle,
      EAPPLICATIONEVENT_APP);

  /*
   * Wraps the QueueNotifying module for simple event generations
   */
  ZAF_EventHelperInit(&m_AppEventNotifyingQueue);

  /*
   * Creates an internal queue to store no more than @ref JOB_QUEUE_BUFFER_SIZE jobs.
   * This module has no notification feature
   */
  ZAF_JobHelperInit();
}


void notAppStateDependentActivity(EVENT_APP event)
{
  UNUSED(event);
  /**
   * Contains actions that are always performed regardless of app-state.
   */
}


static void AppState_StartUp(EVENT_APP event)
{
  if (EVENT_APP_INIT == event)
  {
    /*
     * This approach makes it possible to do less initialization before the scheduler starts.
     * Hence, this was made to reduce the boot-up time.
     */
    doRemainingInitialization();
  }
  else
  {
    ChangeState(STATE_APP_IDLE);
  }
}

static void ResetToDefault(void)
{
  DPRINT("\n===Reset to Default===\n");
  SendDeviceResetLocally();
  AppResetNvm();
}

static void AppState_Idle(EVENT_APP event)
{
  /*************************************
   * Button functionalities
   ************************************/

  // Inclusion process starting
  if (EVENT_APP_BUTTON_INCLUDE_DEVICE == event)
  {
    if (IsPrimaryController())
    {
      DPRINT("\n===Inclusion process started===\n");

      bool ret = portable_controller_start_inclusion();  // This sets state to NETWORK_MANAGEMENT_STATE_START_INCLUSION
      if (ret == false)
      {
        DPRINT("Error, queue is full\n");
      }
      else
      {
        zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_ONE_DAY);
        Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
        ChangeState(STATE_APP_INCLUDE_EXCLUDE);
        TimerStart(&JobTimer, 61 * 1000);
      }
    }
    else
    {
      DPRINT("Inclusion not supported when Secondary\n");
    }
  }

  // Exclusion process starting
  if (EVENT_APP_BUTTON_EXCLUDE_DEVICE == event)
  {
    if (IsPrimaryController())
    {
      DPRINT("\n===Exclusion process started===\n");

      bool ret = portable_controller_start_exclusion();  // This sets state to NETWORK_MANAGEMENT_STATE_START_EXCLUSION
      if (ret == false)
      {
        DPRINT("Error, queue is full\n");
      }
      else
      {
        zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_ONE_DAY);
        Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
        ChangeState(STATE_APP_INCLUDE_EXCLUDE);
        TimerStart(&JobTimer, 61 * 1000);
      }
    }
    else
    {
      DPRINT("Exclusion not supported when Secondary\n");
    }
  }

  if (EVENT_APP_BUTTON_RESET == event)
  {
    ResetToDefault();
  }

  if (EVENT_APP_BUTTON_ASSOCIATION_GROUP_ADD == event)
  {
    DPRINT("\nAdd device to Group - release button and activate device nodeinformation\n");
    KeyFob_group_add_Led_handler(true);
    ChangeState(STATE_APP_ASSOCIATION);
    TimerStart(&JobTimer, 10 * 1000);
  }

  if (EVENT_APP_BUTTON_ASSOCIATION_GROUP_REMOVE == event)
  {
    DPRINT("\nRemove device from Group - release button and activate device nodeinformation\n");
    KeyFob_group_remove_Led_handler(true);
    ChangeState(STATE_APP_ASSOCIATION);
    TimerStart(&JobTimer, 10 * 1000);
  }

  // Send Basic Set ON with multicast
  if (EVENT_APP_BUTTON_BASIC_ON == event)
  {
    /* Basic Set ON to Group requested */
    DPRINT("\nBasic Set ON to Group requested\n");
    ChangeState(STATE_APP_TRANSMIT_DATA);
    zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_BTN);

    if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB))
    {
      DPRINT("\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
    }

    /*Add event's on job-queue*/
    ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BASIC_ON_JOB);
  }

  // Send Basic Set OFF with multicast
  if (EVENT_APP_BUTTON_BASIC_OFF == event)
  {
    /* Basic Set ON to Group requested */
    DPRINT("\nBasic Set OFF to Group requested\n");
    ChangeState(STATE_APP_TRANSMIT_DATA);
    zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_BTN);

    if (false == ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB))
    {
      DPRINT("\n** EVENT_APP_NEXT_EVENT_JOB fail\r\n");
    }

    /*Add event's on job-queue*/
    ZAF_JobHelperJobEnqueue(EVENT_APP_SEND_BASIC_OFF_JOB);
  }

  if (EVENT_APP_BUTTON_NETWORK_LEARNMODE_NWI == event)
  {
    DPRINT("\nSet LearnMode NWI\n");
    if (false == portable_controller_start_learnmode_include())
    {
      DPRINT("Error, queue is full\n");
    }
    else
    {
      KeyFob_network_learnmode_led_handler(true);
      ChangeState(STATE_APP_NETWORK_LEARNMODE);
      zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_TEN_MINUTES);
      TimerStart(&JobTimer, 61 * 1000);
    }
  }

  if (EVENT_APP_BUTTON_NETWORK_LEARNMODE_NWE == event)
  {
    if (!IsPrimaryController())
    {
      if (SetRFReceiveMode(true))
      {
        DPRINT("\nSet LearnMode NWE\n");
        if (false == portable_controller_start_learnmode_exclude())
        {
          DPRINT("Error, queue is full\n");
        }
        else
        {
          KeyFob_network_learnmode_led_handler(true);
          ChangeState(STATE_APP_NETWORK_LEARNMODE);
          zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_TEN_MINUTES);
          TimerStart(&JobTimer, 61 * 1000);
        }
      }
      else
      {
        DPRINT("Error, couldn't start radio\n");
      }
    }
    else
    {
      DPRINT("NWE not supported when Primary Controller\n");
    }
  }
}

static void AppState_IncludeExclude(EVENT_APP event)
{
  if (EVENT_APP_BUTTON_INCLUDE_DEVICE == event)
  {
    handle_network_management_states(0);
    return;
  }

  if (EVENT_APP_BUTTON_EXCLUDE_DEVICE == event)
  {
    handle_network_management_states(0);
    return;
  }

  if (EVENT_APP_BUTTON_RESET == event)
  {
    // First stop any active exclusion
    portable_controller_stop_exclusion();
    STOP_LEARNMODE();
    ResetToDefault();
  }
}

static void AppState_NetworkLearnMode(EVENT_APP event)
{
  if (EVENT_APP_BUTTON_NETWORK_LEARNMODE_NWI == event)
  {
    handle_network_management_states(0);
    return;
  }

  if (EVENT_APP_BUTTON_RESET == event)
  {
    KeyFob_network_learnmode_led_handler(false);
    zwave_network_management_abort();
    STOP_LEARNMODE();
    ResetToDefault();
  }
}

static void AppState_Association(EVENT_APP event)
{
  DPRINTF("\nSTATE_APP_ASSOCIATION (state: %d)\n", currentState);

  if (EVENT_APP_NEXT_EVENT_JOB == event)
  {
    uint8_t nextevent;
    /*check job-queue*/
    if (true == ZAF_JobHelperJobDequeue(&nextevent))
    {
      /*Let the event scheduler fire the event on state event machine*/
      ZAF_EventHelperEventEnqueue(nextevent);
    }
    else
    {
      DPRINT("  Enqueuing event: EVENT_APP_FINISH_EVENT_JOB\n");
      ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
    }
  }

  if (EVENT_APP_BUTTON_RESET == event)
  {
    ResetToDefault();
  }

  if (EVENT_APP_BUTTON_UP_ASSOCIATION_GROUP_ADD == event)
  {
    DPRINT("\nAdd Device to Group - Activate Device Nodeinformation\n");
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_ADD_GROUP);
    SetRFReceiveMode(true);
    zpal_pm_stay_awake(m_RadioPowerLock, 11 * 1000);
    Board_IndicatorControl(800, 200, 0, false);
    TimerStart(&JobTimer, 10 * 1000);
  }

  if (EVENT_APP_BUTTON_UP_ASSOCIATION_GROUP_REMOVE == event)
  {
    DPRINT("\nRemove Device from Group - Activate Device Nodeinformation\n");
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_REMOVE_GROUP);
    SetRFReceiveMode(true);
    zpal_pm_stay_awake(m_RadioPowerLock, 11 * 1000);
    Board_IndicatorControl(400, 600, 0, false);
    TimerStart(&JobTimer, 10 * 1000);
  }

  if (EVENT_APP_FINISH_EVENT_JOB == event
      || EVENT_APP_BUTTON_ASSOCIATION_GROUP_ADD    == event
      || EVENT_APP_BUTTON_ASSOCIATION_GROUP_REMOVE == event
	  //Since Association and Basic On/OFF shares buttons in this example application
	  //the Basic On/Off events are allowed to terminate Association.
      || EVENT_APP_BUTTON_BASIC_ON                 == event
      || EVENT_APP_BUTTON_BASIC_OFF                == event
    )
  {
    DPRINTF("\nSTATE_APP_ASSOCIATION done (state: %d)\n", currentState);
    ChangeState(STATE_APP_IDLE);
    SetRFReceiveMode(false);
    KeyFob_group_remove_Led_handler(false);
    KeyFob_group_add_Led_handler(false);
    zpal_pm_cancel(m_RadioPowerLock);
    Board_IndicateStatus(BOARD_STATUS_IDLE);
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_IDLE);
  }
}


static void AppState_TransmitData(EVENT_APP event)
{
  /**
   * This will take the queued job and put it on the event queue.
   */
  if (EVENT_APP_NEXT_EVENT_JOB == event)
  {
    uint8_t nextevent;
    /*check job-queue*/
    if (true == ZAF_JobHelperJobDequeue(&nextevent))
    {
      /*Let the event scheduler fire the event on state event machine*/
      ZAF_EventHelperEventEnqueue(nextevent);
    }
    else
    {
      DPRINT("  Enqueuing event: EVENT_APP_FINISH_EVENT_JOB\n");
      ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
    }
  }

  if (EVENT_APP_BUTTON_RESET == event)
  {
    ResetToDefault();
  }

  if (EVENT_APP_SEND_BASIC_ON_JOB == event)
  {
    if (true != SendBasicSetToGroup(0xFF, &SendBasicSetToGroupCallback))
    {
      DPRINT("\n*SendBasicSetToGroup ON TX FAILED\n");
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
    }
    DPRINT("  EVENT_APP_SEND_BASIC_ON_JOB\n");
  }

  if (EVENT_APP_SEND_BASIC_OFF_JOB == event)
  {
    if (true != SendBasicSetToGroup(0x00, &SendBasicSetToGroupCallback))
    {
      DPRINT("\n*SendBasicSetToGroup OFF TX FAILED\n");
      ZAF_EventHelperEventEnqueue(EVENT_APP_NEXT_EVENT_JOB);
    }
    DPRINT("  EVENT_APP_SEND_BASIC_OFF_JOB\n");
  }

  if (EVENT_APP_FINISH_EVENT_JOB == event)
  {
    ChangeState(STATE_APP_IDLE);
    zpal_pm_stay_awake(m_RadioPowerLock, 10);
  }
  DPRINTF("\nSTATE_APP_TRANSMIT_DATA done (state: %d)\n", currentState);
}


static void AppStateManager(EVENT_APP event)
{
  DPRINTF("AppStateManager() - event: 0x%02x\n", event);

  /*
   * Here we handle events that are not evaluated in the context of the app state.
   */
  notAppStateDependentActivity(event);

  switch(currentState)
  {
    case STATE_APP_STARTUP:
      AppState_StartUp(event);
      break;

    case STATE_APP_IDLE:  // Ready for input
      AppState_Idle(event);
      break;

    case STATE_APP_INCLUDE_EXCLUDE:
      AppState_IncludeExclude(event);
      break;

    case STATE_APP_ASSOCIATION:
      AppState_Association(event);
      break;

    case STATE_APP_TRANSMIT_DATA:
      AppState_TransmitData(event);
      break;

    case STATE_APP_NETWORK_LEARNMODE:
      AppState_NetworkLearnMode(event);
      break;

    default:
      // Do nothing.
      DPRINT("\nAppStateHandler(): Case is not handled\n");
      break;
  }
}


/**
 * Handle the next step in the iteration through all states of the inclusion process.
 * @param current_node_id
 */
static void handle_network_management_states(node_id_t current_node_id)
{
  DPRINTF("handle_network_management_states() - current_node_id: %d\n", current_node_id);

  switch (get_current_network_management_state())
  {
    case NETWORK_MANAGEMENT_STATE_START_INCLUSION:
      DPRINT("-->NETWORK_MANAGEMENT_STATE_START_INCLUSION\n");
      if (false == node_storage_is_nodeid_group_member(current_node_id))
      {
        DPRINTF("incl, node %d not in group\n", current_node_id);
      }
      portable_controller_stop_inclusion();
      STOP_LEARNMODE();
      break;

    case NETWORK_MANAGEMENT_STATE_START_EXCLUSION:
      DPRINT("-->NETWORK_MANAGEMENT_STATE_START_EXCLUSION\n");
      if (true == node_storage_is_nodeid_group_member(current_node_id))
      {
        DPRINTF("excl, remove node %d from group\n", current_node_id);
        node_storage_remove_group_member_nodeid(current_node_id);
      }
      portable_controller_stop_exclusion();
      STOP_LEARNMODE();
      break;

    case NETWORK_MANAGEMENT_STATE_LEARNMODE:
      DPRINTF("-->NETWORK_MANAGEMENT_STATE_LEARNMODE %u\n", current_node_id);
      KeyFob_network_learnmode_led_handler(false);
      zwave_network_management_abort();
      ChangeState(STATE_APP_IDLE);
      zpal_pm_stay_awake(m_RadioPowerLock, 1000 * 10);
      break;

    case NETWORK_MANAGEMENT_STATE_IDLE:
      DPRINT("-->NETWORK_MANAGEMENT_STATE_IDLE\n");
      KeyFob_network_learnmode_led_handler(false);
      STOP_LEARNMODE();
      break;

    default:
      DPRINTF("-->Invalid network management state: %d\n", get_current_network_management_state());
      break;
  }
}

/**
 * Report current battery level to battery command class handler
 *
 * @brief See description for function prototype in CC_Battery.h
 */
uint8_t
CC_Battery_BatteryGet_handler(uint8_t endpoint)
{
  UNUSED(endpoint);
  return KeyFob_hw_get_battery_level();
}

/***************************************************************************
 * The below material should be moved into a separate file.
 **************************************************************************/

#include <string.h>
#include "Min2Max2.h"

#define FILE_ID_APPLICATIONSETTINGS    102
#define FILE_ID_APPLICATIONCMDINFO     103

#define FILE_SIZE_APPLICATIONSETTINGS     (sizeof(SApplicationSettings))
#define FILE_SIZE_APPLICATIONCMDINFO     (sizeof(SApplicationCmdClassInfo))

typedef struct SApplicationSettings
{
  uint8_t listening;
  uint8_t generic;
  uint8_t specific;
} SApplicationSettings;

typedef struct SApplicationCmdClassInfo
{
  uint8_t UnSecureIncludedCCLen;
  uint8_t UnSecureIncludedCC[APPL_NODEPARM_MAX];
  uint8_t SecureIncludedUnSecureCCLen;
  uint8_t SecureIncludedUnSecureCC[APPL_NODEPARM_MAX];
  uint8_t SecureIncludedSecureCCLen;
  uint8_t SecureIncludedSecureCC[APPL_NODEPARM_MAX];

} SApplicationCmdClassInfo;

static uint8_t
SaveApplicationSettings(uint8_t bListening,
                        uint8_t bGeneric,
                        uint8_t bSpecific
                       )
{
  SApplicationSettings tApplicationSettings;
  uint8_t dataIsWritten = false;
  zpal_status_t tReturnVal;
  tReturnVal = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, FILE_SIZE_APPLICATIONSETTINGS);
  if (ZPAL_STATUS_OK == tReturnVal)
  {
    tApplicationSettings.listening = bListening;
    tApplicationSettings.generic = bGeneric;
    tApplicationSettings.specific = bSpecific;
    tReturnVal = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONSETTINGS, &tApplicationSettings, FILE_SIZE_APPLICATIONSETTINGS);
    if (ZPAL_STATUS_OK == tReturnVal)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}


uint8_t
SaveApplicationCCInfo (uint8_t bUnSecureIncludedCCLen,
                       const uint8_t* pUnSecureIncludedCC,
                       uint8_t bSecureIncludedUnSecureCCLen,
                       uint8_t* pSecureIncludedUnSecureCC,
                       uint8_t  bSecureIncludedSecureCCLen,
                       uint8_t* pSecureIncludedSecureCC)
{
  SApplicationCmdClassInfo tApplicationCmdClassInfo;
  uint8_t dataIsWritten = false;
  zpal_status_t tReturnVal;

  tReturnVal = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, FILE_SIZE_APPLICATIONCMDINFO);
  if (ZPAL_STATUS_OK == tReturnVal)
  {

    tApplicationCmdClassInfo.UnSecureIncludedCCLen = bUnSecureIncludedCCLen;
    tApplicationCmdClassInfo.SecureIncludedUnSecureCCLen = bSecureIncludedUnSecureCCLen;
    tApplicationCmdClassInfo.SecureIncludedSecureCCLen = bSecureIncludedSecureCCLen;

    for (uint8_t i = 0; i < APPL_NODEPARM_MAX; i++)
    {
      if (i < bUnSecureIncludedCCLen)
      {
        tApplicationCmdClassInfo.UnSecureIncludedCC[i] = pUnSecureIncludedCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.UnSecureIncludedCC[i] = 0;
      }

      if (i < bSecureIncludedUnSecureCCLen)
      {
        tApplicationCmdClassInfo.SecureIncludedUnSecureCC[i] = pSecureIncludedUnSecureCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.SecureIncludedUnSecureCC[i] = 0;
      }

      if (i < bSecureIncludedSecureCCLen)
      {
        tApplicationCmdClassInfo.SecureIncludedSecureCC[i] = pSecureIncludedSecureCC[i];
      }
      else
      {
        tApplicationCmdClassInfo.SecureIncludedSecureCC[i] = 0;
      }

      }
      tReturnVal = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCMDINFO, &tApplicationCmdClassInfo, FILE_SIZE_APPLICATIONCMDINFO);
      if (ZPAL_STATUS_OK == tReturnVal)
      {
        dataIsWritten = true;
      }
  }
  return dataIsWritten;

}

uint32_t portable_setApplicationNodeInformation(uint8_t listening,
                                            NODE_TYPE node_type,
                                            const uint8_t *nodeParm,
                                            uint8_t parmLength)
{
  /* listening | generic | specific | parmLength | nodeParms[] */

  AppNodeInfo.DeviceOptionsMask = listening;
  AppNodeInfo.NodeType.generic = node_type.generic;
  AppNodeInfo.NodeType.specific = node_type.specific;

  // As this serial API command only supports one set of command classes,
  // we use the same list for the entire CC set

  // Data for loopifying CC list writes
  SCommandClassList_t *const apCCLists[3] =
  {
    &AppNodeInfo.CommandClasses.UnSecureIncludedCC,
    &AppNodeInfo.CommandClasses.SecureIncludedUnSecureCC,
    &AppNodeInfo.CommandClasses.SecureIncludedSecureCC
  };

  const uint8_t aCCListSizes[3] =
  {
    sizeof(cmdClassListNonSecureNotIncluded),
    sizeof(cmdClassListNonSecureIncludedSecure),
    sizeof(cmdClassListSecure)
  };

  uint32_t iListLength = parmLength;
  for (uint32_t i = 0; i < 3; i++)
  {
    // NOTE: These are not really supposed to be edited run time.
    // So set list lengths to 0 at first to reduce chaos if protocol
    // accesses them while we edit them.
    apCCLists[i]->iListLength = 0;

    memset((uint8_t *)(apCCLists[i]->pCommandClasses), 0, aCCListSizes[i]); // Clear CCList
    memcpy((uint8_t *)(apCCLists[i]->pCommandClasses), nodeParm, Minimum2(iListLength, aCCListSizes[i]));

    // Set new list length after finishing CCList
    apCCLists[i]->iListLength = (uint8_t)Minimum2(iListLength, aCCListSizes[i]);
  }

  AppNodeInfo.DeviceOptionsMask = listening;
  AppNodeInfo.NodeType.generic = node_type.generic;
  AppNodeInfo.NodeType.specific = node_type.specific;

  bool bStatus = SaveApplicationSettings(listening, node_type.generic,
                          node_type.specific);
  bStatus &= SaveApplicationCCInfo(apCCLists[0]->iListLength, (const uint8_t*)apCCLists[0]->pCommandClasses,  // See comment at the beginning of the case.
                        0, NULL, 0, NULL);
#if defined(ZW_CONTROLLER)
  ZW_UpdateCtrlNodeInformation_API_IF(true);
#endif
  return bStatus;
}

/***********************************************************************
 * SECURE dependent material that was needed from SerialAPI app.
 **********************************************************************/

#define FILE_ID_APPLICATIONCONFIGURATION 104
#define FILE_SIZE_APPLICATIONCONFIGURATION (sizeof(SApplicationConfiguration))

typedef struct SApplicationConfiguration
{
  uint8_t     rfRegion;
  int8_t      iTxPower;
  int8_t      ipower0dbmMeasured;
  uint8_t     enablePTI;
  int16_t     maxTxPower;
} SApplicationConfiguration;


uint8_t
SaveApplicationTxPowerlevel(int8_t ipower, int8_t power0dbmMeasured)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t tReturnVal;

  tReturnVal = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == tReturnVal)
  {
    tApplicationConfiguration.iTxPower = ipower;
    tApplicationConfiguration.ipower0dbmMeasured = power0dbmMeasured;
    tReturnVal = zpal_nvm_write(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == tReturnVal)
    {
      dataIsWritten = true;
    }
  }
  return dataIsWritten;
}

static
bool ObjectExist(zpal_nvm_object_key_t key)
{
  zpal_status_t  tReturnVal;
  size_t   tDataLen;


  tReturnVal = zpal_nvm_get_object_size(pFileSystemApplication, key, &tDataLen);
  if (ZPAL_STATUS_OK != tReturnVal)
  {
    return false;
  }
  return true;
}

uint8_t
ReadApplicationRfRegion(uint8_t * rfRegion)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t tReturnVal;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    tReturnVal = zpal_nvm_read(pFileSystemApplication, FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == tReturnVal)
    {
      *rfRegion = tApplicationConfiguration.rfRegion;
      dataIsRead = true;
    }
  }
  return dataIsRead;
}

ZW_WEAK void KeyFob_hw_init(EResetReason_t reset_reason)
{
  (void)reset_reason;
}

ZW_WEAK void KeyFob_hw_deep_sleep_wakeup_handler(void)
{
}

ZW_WEAK void KeyFob_basic_on_Led_handler(bool ledOn)
{
  (void)ledOn;
}

ZW_WEAK void KeyFob_basic_off_Led_handler(bool ledOn)
{
  (void)ledOn;
}

ZW_WEAK void KeyFob_group_add_Led_handler(bool ledOn)
{
  (void)ledOn;
}

ZW_WEAK void KeyFob_group_remove_Led_handler(bool ledOn)
{
  (void)ledOn;
}

ZW_WEAK void KeyFob_node_add_remove_Led_handler(bool ledOn)
{
  (void)ledOn;
}

ZW_WEAK void KeyFob_network_learnmode_led_handler(bool ledOn)
{
  (void)ledOn;
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
  const size_t serial_length = zpal_get_serial_number_length();

  ASSERT(serial_length <= 0x1F); // Device ID Data Length field size is 5 bits

  *pDeviceIDType = DEVICE_ID_TYPE_SERIAL_NUMBER;
  *pDeviceIDDataFormat = DEVICE_ID_FORMAT_BINARY;
  *pDeviceIDDataLength = (uint8_t)serial_length;
  zpal_get_serial_number(pDeviceIDData);

  DPRINT("\r\nserial number: ");
  for (size_t i = 0; i < serial_length; ++i)
  {
    DPRINTF("%02x", pDeviceIDData[i]);
  }
  DPRINT("\r\n");
}
