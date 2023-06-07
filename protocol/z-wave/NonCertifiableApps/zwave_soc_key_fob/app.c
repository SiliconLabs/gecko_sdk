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

#include <string.h>
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include "ZAF_Common_helper.h"
#include "ZAF_Common_interface.h"
#include "zaf_config_security.h"
#include "ZW_system_startup_api.h"
#include "AppTimer.h"
#include "KeyFob_hw.h"
#include "board_indicator.h"
#include "events.h"
#include "network_management.h"
#include "node_storage.h"
#include "sl_status.h"
#include "ZAF_nvm_app.h"
#include "ZAF_nvm.h"
#include "board.h"
#include "board_init.h"
#include "MfgTokens.h"
#include "zpal_watchdog.h"
#include "ZAF_ApplicationEvents.h"
#include "zaf_event_distributor_soc.h"
#include "zpal_misc.h"
#include "zw_build_no.h"
#include "zaf_protocol_config.h"

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
#define PM_STAY_AWAKE_DURATION_3_SEC        (1000 * 3)
#define PM_STAY_AWAKE_DURATION_REPORT_WAIT  (1000 * 10)         // [ms]

/**
 * Task for initialize
 * @param[in] pAppHandles Application handle
 * @return None
*/
static void ApplicationTask(SApplicationHandles* pAppHandles);

static uint8_t SetRFReceiveMode(uint8_t mode);

static uint8_t GetCommandResponse(SZwaveCommandStatusPackage *pCmdStatus, EZwaveCommandStatusType cmdType);

static void SendBasicSetDone(void);

static void SupervisionReport(void *pSubscriberContext, void* pRxPackage);

static void handle_network_management_states(node_id_t current_node_id);

static zpal_pm_handle_t m_RadioPowerLock;
static zpal_pm_handle_t m_PeripheralPowerLock;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

/**
 * Parameter is used to save wakeup reason after ApplicationInit(..)
 */
static EResetReason_t g_eResetReason;

static SSwTimer JobTimer;

#define STOP_LEARNMODE()              Board_IndicateStatus(BOARD_STATUS_IDLE);  \
                                      zpal_pm_stay_awake(m_RadioPowerLock, 10)

#define PRINT_SUPPORTED_COMMAND_CLASSES();                                                  \
                                      if (CcListLength && pCcList)                          \
                                      {                                                     \
                                        DPRINT("Supported command classes:\n\t");           \
                                        for (uint8_t cnt = 0; cnt < CcListLength; cnt++)    \
                                        {                                                   \
                                          DPRINTF("%X ", pCcList[cnt]);                     \
                                        }                                                   \
                                        DPRINT("\n");                                       \
                                      }

ZW_APPLICATION_STATUS
ApplicationInit(EResetReason_t eResetReason)
{
  SRadioConfig_t* RadioConfig;

  /* Initialize the radio board (SAW filter setup, etc) */
  /* hardware initialization */
  Board_Init();

#ifdef DEBUGPRINT
  zpal_debug_init();
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
  DebugPrintf("ApplicationInit eResetReason = %d\n", eResetReason);
#endif // DEBUGPRINT

  DPRINT("\n\n===ApplicationInit===\n");

  /* g_eResetReason now contains latest System Reset reason */
  g_eResetReason = eResetReason;

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
  ZAF_nvm_app_init();
  ZAF_nvm_init();

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

  return APPLICATION_RUNNING; /*Return false to enter production test mode*/
}

/**
* Aquire a list of included nodes IDS in the network from protocol
*
* Method requires CommandStatus queue from protocol to be empty.
* Method requires CommandQueue to protocol to be empty.
* Method will cause assert on failure.
*
* @param[out]    node_id_list    Pointer to bitmask list where aquired included nodes IDs saved
*/
static void Get_included_nodes(uint8_t* node_id_list)
{
  const SApplicationHandles *m_pAppHandles = ZAF_getAppHandle();
  SZwaveCommandPackage GetIncludedNodesCommand = {
      .eCommandType = EZWAVECOMMANDTYPE_ZW_GET_INCLUDED_NODES};

  // Put the Command on queue (and dont wait for it, queue must be empty)
  EQueueNotifyingStatus QueueStatus = QueueNotifyingSendToBack(m_pAppHandles->pZwCommandQueue, (uint8_t *)&GetIncludedNodesCommand, 0);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus);
  // Wait for protocol to handle command (it shouldnt take long)
  SZwaveCommandStatusPackage includedNodes;
  if (GetCommandResponse(&includedNodes, EZWAVECOMMANDSTATUS_ZW_GET_INCLUDED_NODES))
  {
    memcpy(node_id_list, (uint8_t*)includedNodes.Content.GetIncludedNodes.node_id_list, sizeof(NODE_MASK_TYPE));
    return;
  }
  ASSERT(false);
}

static uint8_t sv_session_id = 0x30;
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
  *getLen = 0;
  if (0 == sv_session_id)
    sv_session_id = 1;
  getFrame[(*getLen)++] = COMMAND_CLASS_SUPERVISION;
  getFrame[(*getLen)++] = SUPERVISION_GET;
  getFrame[(*getLen)++] = sv_session_id++ & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK;
  getFrame[(*getLen)++] = cmdLen;
  memcpy(&getFrame[*getLen], cmdFrame, cmdLen);
  *getLen += cmdLen;
}

static uint8_t SendSecureFrame(node_id_t node_id,
                               zwave_keyset_t tx_key,
                               uint8_t number_of_responses,
                               bool isMultiCast,
                               uint8_t *pData,
                               size_t data_length,
                               void (*pCallback)(uint8_t, const TX_STATUS_TYPE*))
{
  SZwaveTransmitPackage TransmitPackage;
  memset(&TransmitPackage, 0, sizeof(TransmitPackage));
  TransmitPackage.eTransmitType = EZWAVETRANSMITTYPE_SECURE;
  SSecureSendData *params = &TransmitPackage.uTransmitParams.SendDataParams;
  if (isMultiCast) {
    node_storage_group_member_nodemask_get((uint8_t*)params->connection.remote.address.nodeList.nodeMask,
                                            sizeof(params->connection.remote.address.nodeList.nodeMask));
    params->connection.remote.is_multicast = isMultiCast;
  } else {
    params->connection.remote.address.node_id = node_id;
  }
  params->tx_options.number_of_responses = number_of_responses;
  params->tx_keys = tx_key;
  params->ptxCompleteCallback = pCallback;
  memcpy(params->data, pData, data_length);
  params->data_length = data_length;

  // Put the package on queue (and don't wait for it)
  return EQUEUENOTIFYING_STATUS_SUCCESS == QueueNotifyingSendToBack(ZAF_getZwTxQueue(), (uint8_t*)&TransmitPackage, 0);
}


/**
 * @brief keyfob is working as secondary then we need to know if the slave node is included with
 * security or not
 *
 * First we send basic get cmd using s2_unautnticated
 * If we received basic report then we update the security information for the node
 * if not then we try with s0 if we succeeded then we update the security information for the node
 */
static bool SendBasicGet(node_id_t node_id, zwave_keyset_t tx_key)
{
  DPRINT("\nbasic_get");
  uint8_t basic_get[] = {COMMAND_CLASS_BASIC, BASIC_GET};
  TimerStart(&JobTimer, PM_STAY_AWAKE_DURATION_REPORT_WAIT);
  // Put the package on queue (and don't wait for it)
  return (true == SendSecureFrame(node_id, tx_key, 0, false, basic_get, sizeof(basic_get), NULL));
}

static NODE_MASK_TYPE nodeid_list;
static node_id_t probed_nodeid = 0;
static void NodeSecurityProbe(bool init);

static void BasicReprotReceived (void *pSubscriberContext, void* pRxPackage) {
  (void)pSubscriberContext;
  (void)pRxPackage;
  TimerStop(&JobTimer);

  SZwaveCommandPackage CommandPackage;
  CommandPackage.eCommandType = EZWAVECOMMANDTYPE_SECURE_NETWORK_MANAGEMENT_SET_SECURITY_FLAGS;
  CommandPackage.uCommandParams.SetSecurityFlags.nodeID = probed_nodeid;

  if (NETWORK_MANAGEMENT_STATE_S2_PROBE == get_current_network_management_state())
  {
    CommandPackage.uCommandParams.SetSecurityFlags.nodeS2Capable      = true;
    CommandPackage.uCommandParams.SetSecurityFlags.nodeS2Included     = true;
    CommandPackage.uCommandParams.SetSecurityFlags.nodeSecureIncluded = true;
    QueueNotifyingSendToBack(ZAF_getZwCommandQueue(), (uint8_t*) &CommandPackage, 500);

    ZW_NODE_MASK_CLEAR_BIT(nodeid_list, probed_nodeid );
    NodeSecurityProbe(false);
  }
  else if (NETWORK_MANAGEMENT_STATE_S0_PROBE == get_current_network_management_state())
  {
    CommandPackage.uCommandParams.SetSecurityFlags.nodeS2Capable      = false;
    CommandPackage.uCommandParams.SetSecurityFlags.nodeS2Included     = false;
    CommandPackage.uCommandParams.SetSecurityFlags.nodeSecureIncluded = true;
    QueueNotifyingSendToBack(ZAF_getZwCommandQueue(), (uint8_t*) &CommandPackage, 500);

    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_S2_PROBE);
    ZW_NODE_MASK_CLEAR_BIT(nodeid_list, probed_nodeid );
    NodeSecurityProbe(false);
  }
}

static void NodeSecurityProbe(bool init)
{
  if (true == init) {
    Get_included_nodes(nodeid_list);
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_S2_PROBE);
    ZAF_CP_SubscribeToCmd(ZAF_getCPHandle(), NULL, BasicReprotReceived, COMMAND_CLASS_BASIC, BASIC_REPORT);
    probed_nodeid = 2;
  }

  while((0 == ZW_NODE_MASK_NODE_IN(nodeid_list, probed_nodeid)) ||
        (probed_nodeid == ZAF_GetNodeID()))
  {
    probed_nodeid++;
  }

  if (probed_nodeid < ZW_MAX_NODES) {
    zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_3_SEC);
    if (NETWORK_MANAGEMENT_STATE_S2_PROBE == get_current_network_management_state()) {
       SendBasicGet(probed_nodeid, SECURITY_KEY_S2_UNAUTHENTICATED_BIT);
    } else {
       SendBasicGet(probed_nodeid, SECURITY_KEY_S0_BIT);
    }
  } else {
    ZAF_CP_UnsubscribeToCmd(ZAF_getCPHandle(), NULL, BasicReprotReceived, COMMAND_CLASS_BASIC, BASIC_REPORT);
    zpal_pm_cancel(m_RadioPowerLock);
    KeyFob_network_learnmode_led_handler(false);
    zaf_event_distributor_enqueue_app_event(EVENT_APP_FINISH_EVENT);
  }

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
    zaf_event_distributor_enqueue_app_event(EVENT_APP_FINISH_EVENT);
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
  else if (NETWORK_MANAGEMENT_STATE_SECURITY_PROBE == get_current_network_management_state())
  {
    /*We start probing slave nodes for granted security keys*/
    NodeSecurityProbe(true);
  }
  else if (NETWORK_MANAGEMENT_STATE_S2_PROBE == get_current_network_management_state())
  {
    /*probing the current node for s2 failed then try s0*/
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_S0_PROBE);
    NodeSecurityProbe(false);
  }
  else if (NETWORK_MANAGEMENT_STATE_S0_PROBE == get_current_network_management_state())
  {
    set_new_network_management_state(NETWORK_MANAGEMENT_STATE_S2_PROBE);
    /*probing the current node for s0 (and s2) failed then removed with from the list*/
    ZW_NODE_MASK_CLEAR_BIT(nodeid_list, probed_nodeid );
    NodeSecurityProbe(false);
  }
  else if ((NETWORK_MANAGEMENT_STATE_IDLE == get_current_network_management_state())) {
    SendBasicSetDone();
  }
}

static __attribute__((noreturn)) void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  DPRINT("\n\n===========ApplicationTask============\n");

  DPRINT("Enabling watchdog\n");
  zpal_enable_watchdog(true);

  ZAF_Init(xTaskGetCurrentTaskHandle(), pAppHandles);

#ifdef DEBUGPRINT
  ZAF_PrintAppInfo();
#endif

  //Initialize hardware
  app_hw_init();

  AppTimerRegister(&JobTimer, false, ZCB_JobTimeout);

  ZAF_CP_SubscribeToCmd(ZAF_getCPHandle(), NULL, SupervisionReport, COMMAND_CLASS_SUPERVISION, SUPERVISION_REPORT);

  // Setup power management.
  m_RadioPowerLock = zpal_pm_register(ZPAL_PM_TYPE_USE_RADIO);

  if ((ERESETREASON_DEEP_SLEEP_WUT != g_eResetReason) &&
      (ERESETREASON_DEEP_SLEEP_EXT_INT != g_eResetReason))
  {
    zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_REBOOT); // Allowing time for choosing learnmode after reset.
  }

  DPRINTF("g_eResetReason: 0x%08x\n", g_eResetReason);
  if (ERESETREASON_DEEP_SLEEP_EXT_INT == g_eResetReason)
  {
    DPRINT("ERESETREASON_DEEP_SLEEP_EXT_INT\n");
    uint32_t em4_wakeup_flags = Board_GetGpioEm4Flags();

    if (0 != em4_wakeup_flags)
    {
      Board_ProcessEm4PinWakeupFlags(em4_wakeup_flags);
    }
  }

  if(ERESETREASON_PIN == g_eResetReason ||
     ERESETREASON_BROWNOUT == g_eResetReason ||
     ERESETREASON_POWER_ON == g_eResetReason ||
     ERESETREASON_SOFTWARE == g_eResetReason ||
     ERESETREASON_WATCHDOG == g_eResetReason)
  {
    /* Init state machine*/
    zaf_event_distributor_enqueue_app_event(EVENT_EMPTY);
  }
  
  DPRINTF("IsWakeupCausedByRtccTimeout = %s\n", (IsWakeupCausedByRtccTimeout()) ? "true" : "false");
  DPRINTF("CompletedSleepDurationMs    = %u\n", GetCompletedSleepDurationMs());

  SetRFReceiveMode(1);

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
  for (;;)
  {
    zaf_event_distributor_distribute();
  }
}

void
zaf_nvm_app_set_default_configuration(void)
{
  // Set default Basic Set Group - no members
  node_storage_init_group();
}


/**
 * @brief This function loads the application settings from non-volatile memory.
 * If no settings are found, default values are used and saved.
 */
void
zaf_event_distributor_load_configuration(void)
{
  // End Device node IDs in Basic Set Association group will be stored in non volatile memory
  node_storage_init_group();
}

void zaf_event_distributor_app_zw_rx(SZwaveReceivePackage *RxPackage)
{

  switch (RxPackage->eReceiveType)
  {
    case EZWAVERECEIVETYPE_SECURE_FRAME_RECEIVED:
      ZAF_CP_CommandPublish(ZAF_getCPHandle(), (void *) RxPackage);
      TimerStart(&JobTimer, PM_STAY_AWAKE_DURATION_3_SEC);
    break;

    case EZWAVERECEIVETYPE_NODE_UPDATE:
      DPRINT("-->EZWAVERECEIVETYPE_NODE_UPDATE\n");
      if (NETWORK_MANAGEMENT_STATE_ADD_GROUP == get_current_network_management_state())
      {
        DPRINTF("Adding %u to group\n", RxPackage->uReceiveParams.RxNodeUpdate.NodeId);
        node_storage_add_group_member_nodeid(RxPackage->uReceiveParams.RxNodeUpdate.NodeId);
        zaf_event_distributor_enqueue_app_event(EVENT_APP_FINISH_EVENT);
      }
      if (NETWORK_MANAGEMENT_STATE_REMOVE_GROUP == get_current_network_management_state())
      {
        DPRINTF("Removing %u from group\n", RxPackage->uReceiveParams.RxNodeUpdate.NodeId);
        node_storage_remove_group_member_nodeid(RxPackage->uReceiveParams.RxNodeUpdate.NodeId);
        zaf_event_distributor_enqueue_app_event(EVENT_APP_FINISH_EVENT);
      }
      break;

    default:
      break;
  }
}

void zaf_event_distributor_app_zw_command_status(SZwaveCommandStatusPackage *Status)
{
  node_id_t sourceNode;

  switch (Status->eStatusType)
  {
    case EZWAVECOMMANDSTATUS_SECURE_ON_NODE_ADDED:
      sourceNode = Status->Content.USecureAppNotification.nodeAddedNotification.node_id;
      DPRINTF("Included node: NodeID: %d\n", sourceNode);

      sl_status_t status = Status->Content.USecureAppNotification.nodeAddedNotification.status;
      if (SL_STATUS_OK != status)
      {
        DPRINTF("Inclusion Failed. Error: 0x%X\n", status);
      }
      else
      {
        uint8_t CcListLength =
            Status->Content.USecureAppNotification.nodeAddedNotification.nif.command_class_list_length;
        const uint16_t * pCcList =
            Status->Content.USecureAppNotification.nodeAddedNotification.nif.command_class_list;

        PRINT_SUPPORTED_COMMAND_CLASSES()
      }
      // This will stop the learnmode process.
      // Also end device is added to KeyFob Basic Set Group Association
      handle_network_management_states(sourceNode);
      DPRINT("Inclusion ended\n");
      break;

    case EZWAVECOMMANDSTATUS_SECURE_ON_NODE_DELETED:
      sourceNode = Status->Content.USecureAppNotification.nodeDeletedNotification.node_id;
      DPRINTF("Excluded Node: %d\n", sourceNode);

      // This will stop the learnmode process.
      handle_network_management_states(sourceNode);
      DPRINT("Exclusion ended\n");
      break;

    case EZWAVECOMMANDSTATUS_SECURE_ON_NEW_NETWORK_ENTERED:
      ///< Node entered a new network
      DPRINTF("-->EZWAVECOMMANDSTATUS_SECURE_ON_NEW_NETWORK_ENTERED %08X, %u\n", Status->Content.USecureAppNotification.nodeEnteredNetwork.home_id, Status->Content.USecureAppNotification.nodeEnteredNetwork.node_id);
      handle_network_management_states(Status->Content.USecureAppNotification.nodeEnteredNetwork.node_id);
      break;

    case EZWAVECOMMANDSTATUS_SECURE_ON_NETWORK_MANAGEMENT_STATE_UPDATE:
      ///< Secure network management changed state
      DPRINTF("-->EZWAVECOMMANDSTATUS_SECURE_ON_NETWORK_MANAGEMENT_STATE_UPDATE %u\n", Status->Content.USecureAppNotification.nodeNetworkManagement.state);
      if (0 == Status->Content.USecureAppNotification.nodeNetworkManagement.state)
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
      if ( NETWORK_MANAGEMENT_STATE_SECURITY_PROBE== get_current_network_management_state()) {
        TimerStart(&JobTimer, 2 * 1000);
      }
      break;

    case EZWAVECOMMANDSTATUS_SECURE_ON_RX_FRAME_RECEIVED_INDICATOR:
      ///< Frame received from NodeID indicator
      DPRINT("-->EZWAVECOMMANDSTATUS_SECURE_ON_RX_FRAME_RECEIVED_INDICATOR\n");
      if ( NETWORK_MANAGEMENT_STATE_SECURITY_PROBE== get_current_network_management_state()) {
        TimerStart(&JobTimer, 2 * 1000);
      }
      break;

    case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      DPRINT("-->EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS\n");
      break;

    case EZWAVECOMMANDSTATUS_REPLACE_FAILED_NODE_ID:
      DPRINT("-->EZWAVECOMMANDSTATUS_REPLACE_FAILED_NODE_ID\n");
      break;

    case EZWAVECOMMANDSTATUS_REMOVE_FAILED_NODE_ID:
      DPRINT("-->EZWAVECOMMANDSTATUS_REMOVE_FAILED_NODE_ID\n");
      break;

    case EZWAVECOMMANDSTATUS_PM_SET_POWERDOWN_CALLBACK:
      DPRINT("-->EZWAVECOMMANDSTATUS_PM_SET_POWERDOWN_CALLBACK registered\n");
      break;

    default:
      DPRINTF("-->Unknown / Unexpected  CMD - %d\n", Status->eStatusType);
      break;
  }
}

static uint8_t nodesInGroup = 0;
static void
SendBasicSetDone(void) {
  KeyFob_basic_off_Led_handler(false);
  KeyFob_basic_on_Led_handler(false);
}

static void SupervisionReport (void *pSubscriberContext, void* pRxPackage) {
  (void)pSubscriberContext;
  SZwaveReceivePackage* myPackage = (SZwaveReceivePackage *)pRxPackage;
  ZW_SUPERVISION_REPORT_FRAME* pReport = (ZW_SUPERVISION_REPORT_FRAME *)&myPackage->uReceiveParams.Rx.Payload.padding;
  if ((SUPERVISION_REPORT == pReport->cmd) &&
      ((pReport->properties1 & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK)
        == ((sv_session_id - 1) & SUPERVISION_GET_PROPERTIES1_SESSION_ID_MASK)))
  {
    if (!--nodesInGroup)
    {
      SendBasicSetDone();
    }
  }
}

static uint8_t SendBasicSetToGroup(uint8_t value,  void (*pCallback)(uint8_t, const TX_STATUS_TYPE*))
{
   nodesInGroup = node_storage_group_member_count();
  if (0 < nodesInGroup)
  {
    DPRINTF("\nBasicToGroup (%u nodes) value %u\n", nodesInGroup, value);
    zpal_pm_stay_awake(m_RadioPowerLock, 0);
    TimerStart(&JobTimer, PM_STAY_AWAKE_DURATION_3_SEC);
    /**
     * @attention
     * We will be sending a multicast to a list of nodes on our local group
     * maintained locally and with no dependency towards the ZAF.
     *
     * This group is persistently stored on NVM.
     */
    uint8_t basic_set_cmd[] = {COMMAND_CLASS_BASIC, BASIC_SET, value};
    uint8_t supervision_get[4 + sizeof(basic_set_cmd)];
    uint16_t frame_length;
    // encapsulates basic set command into supervision get command
    BuildSupervisionGet(supervision_get, &frame_length, basic_set_cmd, sizeof(basic_set_cmd));
    if (SendSecureFrame(0, 0, 1, true, supervision_get, frame_length, pCallback))
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
    SendBasicSetDone();
    return true;
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

static void beginAssociation(sl_network_management_states_t network_management_state)
{
  set_new_network_management_state(network_management_state);
  SetRFReceiveMode(true);
  zpal_pm_stay_awake(m_RadioPowerLock, 11 * 1000);
  Board_IndicatorControl(800, 200, 0, false);
  TimerStart(&JobTimer, 10 * 1000);
}

static void terminateAssociation(void)
{
  SetRFReceiveMode(false);
  KeyFob_group_remove_Led_handler(false);
  KeyFob_group_add_Led_handler(false);
  zpal_pm_cancel(m_RadioPowerLock);
  Board_IndicateStatus(BOARD_STATUS_IDLE);
  set_new_network_management_state(NETWORK_MANAGEMENT_STATE_IDLE);
}

void
zaf_event_distributor_app_event_manager(const uint8_t event)
{
  DPRINTF("zaf_event_distributor_app_event_manager() - event: 0x%02x\n", event);
  sl_network_management_states_t network_management_state;

  network_management_state = get_current_network_management_state();

  switch (event) {
    case EVENT_APP_INCLUDE_DEVICE:
      if (zaf_event_distributor_is_primary_controller()
          && network_management_state != NETWORK_MANAGEMENT_STATE_START_INCLUSION) {
        DPRINT("\n===Inclusion process started===\n");

        bool ret = key_fob_start_inclusion();  // This sets state to NETWORK_MANAGEMENT_STATE_START_INCLUSION
        if (ret == false) {
          DPRINT("Error, queue is full\n");
        } else {
          zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_ONE_DAY);
          Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
          TimerStart(&JobTimer, 61 * 1000);
        }
      } else if (zaf_event_distributor_is_primary_controller()
          && network_management_state == NETWORK_MANAGEMENT_STATE_START_INCLUSION) {
        handle_network_management_states(0);
      } else {
        DPRINT("Inclusion not supported when Secondary\n");
      }
      break;
    case EVENT_APP_EXCLUDE_DEVICE:
      if (zaf_event_distributor_is_primary_controller()
          && network_management_state != NETWORK_MANAGEMENT_STATE_START_EXCLUSION) {
        DPRINT("\n===Exclusion process started===\n");

        bool ret = key_fob_start_exclusion();  // This sets state to NETWORK_MANAGEMENT_STATE_START_EXCLUSION
        if (ret == false) {
          DPRINT("Error, queue is full\n");
        } else {
          zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_ONE_DAY);
          Board_IndicateStatus(BOARD_STATUS_LEARNMODE_ACTIVE);
          TimerStart(&JobTimer, 61 * 1000);
        }
      } else if (zaf_event_distributor_is_primary_controller()
          && network_management_state == NETWORK_MANAGEMENT_STATE_START_EXCLUSION) {
        handle_network_management_states(0);
      } else {
        DPRINT("Exclusion not supported when Secondary\n");
      }
      break;
    case EVENT_APP_ASSOCIATION_GROUP_ADD:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_REMOVE_GROUP
          || network_management_state == NETWORK_MANAGEMENT_STATE_ADD_GROUP) {
        terminateAssociation();
      } else {
        KeyFob_group_add_Led_handler(true);
        TimerStart(&JobTimer, 10 * 1000);
      }
      break;
    case EVENT_APP_ASSOCIATION_GROUP_REMOVE:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_REMOVE_GROUP
          || network_management_state == NETWORK_MANAGEMENT_STATE_ADD_GROUP) {
        terminateAssociation();
      } else {
        KeyFob_group_remove_Led_handler(true);
        TimerStart(&JobTimer, 10 * 1000);
      }
      break;
    case EVENT_APP_ASSOCIATION_GROUP_ADD_START:
      DPRINT("\nAdd Device to Group - Activate Device Nodeinformation\n");
      beginAssociation(NETWORK_MANAGEMENT_STATE_ADD_GROUP);
      break;
    case EVENT_APP_ASSOCIATION_GROUP_REMOVE_START:
      DPRINT("\nRemove Device from Group - Activate Device Nodeinformation\n");
      beginAssociation(NETWORK_MANAGEMENT_STATE_REMOVE_GROUP);
      break;
    // Send Basic Set ON with multicast
    case EVENT_APP_BASIC_ON:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_REMOVE_GROUP
          || network_management_state == NETWORK_MANAGEMENT_STATE_ADD_GROUP) {
        terminateAssociation();
      } else {
        /* Basic Set ON to Group requested */
        DPRINT("\nBasic Set ON to Group requested\n");
        zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_BTN);

        (void) SendBasicSetToGroup(0xFF, NULL);
      }
      break;
    // Send Basic Set OFF with multicast
    case EVENT_APP_BASIC_OFF:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_REMOVE_GROUP
          || network_management_state == NETWORK_MANAGEMENT_STATE_ADD_GROUP) {
        terminateAssociation();
      } else {
        /* Basic Set OFF to Group requested */
        DPRINT("\nBasic Set OFF to Group requested\n");
        zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_BTN);

        (void) SendBasicSetToGroup(0x00, NULL);
      }
      break;
    case EVENT_APP_FINISH_EVENT:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_REMOVE_GROUP
          || network_management_state == NETWORK_MANAGEMENT_STATE_ADD_GROUP) {
        terminateAssociation();
      } else {
        zpal_pm_stay_awake(m_RadioPowerLock, 10);
      }
      break;
    case EVENT_APP_NETWORK_LEARNMODE_NWI:
      if (network_management_state == NETWORK_MANAGEMENT_STATE_LEARNMODE) {
        handle_network_management_states(0);
      } else {
        if (SetRFReceiveMode(true)) {
          DPRINT("\nSet LearnMode NWI\n");
          if (false == key_fob_start_learnmode_include()) {
            DPRINT("Error, queue is full\n");
          } else {
            KeyFob_network_learnmode_led_handler(true);
            zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_TEN_MINUTES);
            TimerStart(&JobTimer, 61 * 1000);
          }
        } else {
          DPRINT("Error, couldn't start radio\n");
        }
      }
      break;
    case EVENT_APP_NETWORK_LEARNMODE_NWE:
      if (!zaf_event_distributor_is_primary_controller()) {
        if (SetRFReceiveMode(true)) {
          DPRINT("\nSet LearnMode NWE\n");
          if (false == key_fob_start_learnmode_exclude()) {
            DPRINT("Error, queue is full\n");
          } else {
            KeyFob_network_learnmode_led_handler(true);
            zpal_pm_stay_awake(m_RadioPowerLock, PM_STAY_AWAKE_DURATION_TEN_MINUTES);
            TimerStart(&JobTimer, 61 * 1000);
          }
        } else {
          DPRINT("Error, couldn't start radio\n");
        }
      } else {
        DPRINT("NWE not supported when Primary Controller\n");
      }
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
      key_fob_stop_network_managment();
      STOP_LEARNMODE();
      break;

    case NETWORK_MANAGEMENT_STATE_START_EXCLUSION:
      DPRINT("-->NETWORK_MANAGEMENT_STATE_START_EXCLUSION\n");
      if (true == node_storage_is_nodeid_group_member(current_node_id))
      {
        DPRINTF("excl, remove node %d from group\n", current_node_id);
        node_storage_remove_group_member_nodeid(current_node_id);
      }
      key_fob_stop_network_managment();
      STOP_LEARNMODE();
      break;

    case NETWORK_MANAGEMENT_STATE_LEARNMODE:
      DPRINTF("-->NETWORK_MANAGEMENT_STATE_LEARNMODE %u\n", current_node_id);
      key_fob_stop_network_managment();
      set_new_network_management_state(NETWORK_MANAGEMENT_STATE_SECURITY_PROBE);
      TimerStart(&JobTimer, 2 * 1000);
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

uint8_t
zaf_event_distributor_is_primary_controller(void)
{
  SApplicationHandles *pAppHandles;
  SZwaveCommandPackage cmdPackage;
  EQueueNotifyingStatus QueueStatus;
  SZwaveCommandStatusPackage cmdStatus;

  cmdPackage.eCommandType = EZWAVECOMMANDTYPE_IS_PRIMARY_CTRL;
  pAppHandles = ZAF_getAppHandle();

  QueueStatus = QueueNotifyingSendToBack(pAppHandles->pZwCommandQueue, (uint8_t *)&cmdPackage, 500);
  ASSERT(EQUEUENOTIFYING_STATUS_SUCCESS == QueueStatus);
  if (GetCommandResponse(&cmdStatus, EZWAVECOMMANDSTATUS_IS_PRIMARY_CTRL)) {
    return cmdStatus.Content.IsPrimaryCtrlStatus.result;
  }
  ASSERT(false);
  return 0;
}

#if defined(ZW_CONTROLLER)
static void ZW_UpdateCtrlNodeInformation_API_IF(void)
{
  // Create transmit frame package
  SZwaveCommandPackage FramePackage;
  FramePackage.eCommandType =  EZWAVECOMMANDTYPE_ZW_UPDATE_CTRL_NODE_INFORMATION;
  FramePackage.uCommandParams.UpdateCtrlNodeInformation.value = true;
  // Put the package on queue (and dont wait for it)
  QueueNotifyingSendToBack(ZAF_getZwCommandQueue(), (uint8_t *)&FramePackage, 0);
}
#endif

uint32_t portable_setApplicationNodeInformation()
{
#if defined(ZW_CONTROLLER)
  ZW_UpdateCtrlNodeInformation_API_IF();
#endif
  return true;
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
SaveApplicationTxPowerlevel(zpal_tx_power_t ipower, zpal_tx_power_t power0dbmMeasured)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsWritten = false;
  zpal_status_t tReturnVal;

  tReturnVal = ZAF_nvm_app_read(FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
  if (ZPAL_STATUS_OK == tReturnVal)
  {
    tApplicationConfiguration.iTxPower = ipower;
    tApplicationConfiguration.ipower0dbmMeasured = power0dbmMeasured;
    tReturnVal = ZAF_nvm_app_write(FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
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
  size_t tDataLen;
  return ZPAL_STATUS_OK == ZAF_nvm_app_get_object_size(key, &tDataLen);
}

uint8_t
ReadApplicationRfRegion(uint8_t * rfRegion)
{
  SApplicationConfiguration tApplicationConfiguration;
  uint8_t dataIsRead = false;
  zpal_status_t tReturnVal;

  if (ObjectExist(FILE_ID_APPLICATIONCONFIGURATION))
  {
    tReturnVal = ZAF_nvm_app_read(FILE_ID_APPLICATIONCONFIGURATION, &tApplicationConfiguration, FILE_SIZE_APPLICATIONCONFIGURATION);
    if (ZPAL_STATUS_OK == tReturnVal)
    {
      *rfRegion = tApplicationConfiguration.rfRegion;
      dataIsRead = true;
    }
  }
  return dataIsRead;
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
