/**
 * Z-Wave Certified Application Power Strip
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
#include <CC_BinarySwitch.h>
#include "cc_binary_switch_config_api.h"
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_MultiChan.h>
#include <CC_MultilevelSwitch_Support.h>
#include <cc_multilevel_switch_support_config_api.h>
#include "cc_notification_config_api.h"
#include <CC_FirmwareUpdate.h>

#include "zaf_event_helper.h"
#include "zaf_job_helper.h"
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include "ZAF_TSE.h"
#include <ota_util.h>
#include <ZAF_CmdPublisher.h>
#include "events.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <PowerStrip_hw.h>
#include <board_indicator.h>
#include <board_init.h>

#include "zw_region_config.h"

#include "zw_build_no.h"
#include <zaf_config_api.h>
#include <zaf_config.h>
#include "zaf_config_security.h"
#include "ZAF_ApplicationEvents.h"
#include <zaf_event_distributor_soc.h>

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/**
* Set up security keys to request when joining a network.
* These are taken from the config_app.h header file.
*/
static const uint8_t SecureKeysRequested = ZAF_CONFIG_REQUESTED_SECURITY_KEYS;

static SAppNodeInfo_t AppNodeInfo =
{
  .DeviceOptionsMask = ZAF_CONFIG_DEVICE_OPTION_MASK,
  .NodeType.generic = ZAF_CONFIG_GENERIC_TYPE,
  .NodeType.specific = ZAF_CONFIG_SPECIFIC_TYPE
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

static EP_NIF endpointsNIF[ZAF_CONFIG_NUMBER_OF_END_POINTS] =
{
 /*
  * Endpoint 1
  */
  {
    GENERIC_TYPE_SWITCH_BINARY,
    SPECIFIC_TYPE_NOT_USED
  },
  /*
   * Endpoint 2
   */
  {
    GENERIC_TYPE_SWITCH_MULTILEVEL,
    SPECIFIC_TYPE_NOT_USED
  }
};

static EP_FUNCTIONALITY_DATA endPointFunctionality =
{
  {
    ZAF_CONFIG_NUMBER_OF_END_POINTS,    // Individual endpoints set to total number of endpoints.
    0,                                  // Reserved field => set to zero.
    0,                                  // No aggregated endpoints as they are OBSOLETED.
    0,                                  // Reserved field => set to zero.
    0,                                  // Reserved field => set to zero.
    ENDPOINT_IDENTICAL_DEVICE_CLASS_NO, // Different device class for the endpoints in this app.
    ENDPOINT_DYNAMIC_NO                 // No dynamic endpoints as they are OBSOLETED.
  }
};


static ESwTimerStatus notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
// Timer
static SSwTimer NotificationTimer;

static bool notificationOverLoadActiveState =  false;
static uint8_t notification_to_trigger = 0;

static int32_t level_change_direction = 1;

uint8_t supportedEvents = NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED;

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

/* True Status Engine (TSE) variables */

/* Indicate here which End Points (NOT including root device) support each command class */
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

// Nothing here.

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
void ApplicationTask(SApplicationHandles* pAppHandles);
void ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult);
void ZCB_NotificationTimerCallback(SSwTimer *pTimer);
static void notificationToggle(void);

void
zaf_event_distributor_app_zw_command_status(SZwaveCommandStatusPackage *Status)
{
  switch (Status->eStatusType)
  {
    case EZWAVECOMMANDSTATUS_LEARN_MODE_STATUS:
      DPRINTF("Learn status %d\r\n", Status->Content.LearnModeStatus.Status);
      if (ELEARNSTATUS_ASSIGN_COMPLETE == Status->Content.LearnModeStatus.Status)
      {
        if((EINCLUSIONSTATE_EXCLUDED == ZAF_GetInclusionState()))
        {
          if(ESWTIMER_STATUS_FAILED != notificationOverLoadTimerStatus)
          {
            TimerStop(&NotificationTimer);
            notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
          }
        }
      }
      break;

    default:
      break;
  }
}

/*
 * See description for function prototype in ZW_basis_api.h.
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

  DPRINT("\n\n------------------------------\n");
  DPRINT("Z-Wave Sample App: Power Strip\n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);

  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);

  Transport_AddEndpointSupport( &endPointFunctionality, endpointsNIF, ZAF_CONFIG_NUMBER_OF_END_POINTS);

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
 *
 * The function must be treated as a static function, but is left non-static for the purpose
 * of unit testing.
 */
void
ApplicationTask(SApplicationHandles* pAppHandles)
{
  g_pAppHandles = pAppHandles;

  ZAF_Init(&ProtocolConfig, xTaskGetCurrentTaskHandle(), pAppHandles);

  AppTimerRegister(&NotificationTimer, true, ZCB_NotificationTimerCallback);

  zaf_event_distributor_init();

  PowerStrip_hw_init();

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  cc_firmware_update_send_status_report();

  // Wait for and process events
  DPRINT("PowerStrip Event processor Started\r\n");
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
  cc_multilevel_switch_t *switches;

  switch (event) {
    case EVENT_APP_BUTTON_OUTLET1_TOGGLE:
    {
      cc_binary_switch_t * p_binary_switches = cc_binary_switch_get_config();
      cc_binary_switch_t * p_binary_switch = &p_binary_switches[0];

      if (cc_binary_switch_get_current_value(p_binary_switch) > 0) {
        cc_binary_switch_set(p_binary_switch, 0);
      } else {
        cc_binary_switch_set(p_binary_switch, 0xFF); // 0xFF for last on value.
      }
      break;
    }
    case EVENT_APP_BUTTON_OUTLET2_DIMMER_SHORT_PRESS:
      DPRINT("\nDimmer press");
      switches = cc_multilevel_switch_support_get_switches();
      cc_multilevel_switch_stop_level_change(&switches[0]);

      if (cc_multilevel_switch_get_current_value(&switches[0]) > 0) {
        cc_multilevel_switch_set(&switches[0], 0, 0); // Turn it off
      } else {
        cc_multilevel_switch_set(&switches[0], 0xFF, 0); // 0xFF for last on value.
      }
      break;
    case EVENT_APP_BUTTON_OUTLET2_DIMMER_RELEASE:
      DPRINT("\nDimmer up");
      switches = cc_multilevel_switch_support_get_switches();
      cc_multilevel_switch_stop_level_change(&switches[0]);
      break;

    case EVENT_APP_BUTTON_OUTLET2_DIMMER_HOLD:
      DPRINT("\nDimmer hold");
      switches = cc_multilevel_switch_support_get_switches();
      cc_multilevel_switch_start_level_change(&switches[0], (level_change_direction > 0 ? false : true), true, 0, 10);
      if (-1 == level_change_direction) {
        level_change_direction = 1;
      } else if (1 == level_change_direction) {
        level_change_direction = -1;
      }
      DPRINTF("\ndir: %d", level_change_direction);
      break;
    case EVENT_APP_BUTTON_NOTIFICATION_TOGGLE:
      /*
        * Pressing the NOTIFICATION_TOGGLE_BTN key will toggle the overload timer.
        * This timer will transmit a notification every 30th second.
        */
      notificationToggle();
      break;
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
      break;      
  }
}

void
ZCB_JobStatus(TRANSMISSION_RESULT * pTransmissionResult)
{
  DPRINTF("\r\nTX CB for N %u", pTransmissionResult->nodeId);

  if (TRANSMISSION_RESULT_FINISHED == pTransmissionResult->isFinished)
  {
    ZAF_EventHelperEventEnqueue(EVENT_APP_FINISH_EVENT_JOB);
  }
}

/**
 * @brief Called every time the notification timer triggers.
 */
void
ZCB_NotificationTimerCallback(SSwTimer *pTimer)
{
  UNUSED(pTimer);

  JOB_STATUS jobStatus;


  DPRINT("\r\nNtfctn timer");

  uint8_t *pEventParameters;
  uint8_t eventParamLength;
  uint8_t event;

  // Trigger all notifications
  if (false == notificationOverLoadActiveState) {
    DPRINTF("\r\nNtfctn[%u] enable", notification_to_trigger);

    notificationOverLoadActiveState = true;
    event = NOTIFICATION_EVENT_POWER_MANAGEMENT_OVERLOADED_DETECTED;
    pEventParameters = NULL;
    eventParamLength = 0;
  } else  {
    DPRINTF("\r\nNtfctn[%u] disable", notification_to_trigger);

    notificationOverLoadActiveState = false;
    event = NOTIFICATION_EVENT_POWER_MANAGEMENT_NO_EVENT;
    pEventParameters = &supportedEvents;
    eventParamLength = 1;
  }

  jobStatus = CC_Notification_TriggerAndTransmit(
      notification_to_trigger,
      event,
      pEventParameters,
      eventParamLength,
      ZCB_JobStatus,
      true);

    if (false == notificationOverLoadActiveState) {
    /*Find new notification in the list of defined notifications to trigger */
    if (++notification_to_trigger >= cc_notification_get_config_length()) {
      notification_to_trigger = 0;
    }
  }

  if (JOB_STATUS_SUCCESS != jobStatus)
  {
    TRANSMISSION_RESULT transmissionResult;

    DPRINTF("\r\nX%u", jobStatus);

    transmissionResult.status = false;
    transmissionResult.nodeId = 0;
    transmissionResult.isFinished = TRANSMISSION_RESULT_FINISHED;

    ZCB_JobStatus(&transmissionResult);
  }
}

/**
 * @brief Toggles the notification timer.
 */
static void notificationToggle(void)
{
  DPRINT("\r\nNtfctn toggle");


  if (ESWTIMER_STATUS_FAILED == notificationOverLoadTimerStatus)
  {
    DPRINT("\r\nNtfctn start");

    notificationOverLoadActiveState = false;

    notificationOverLoadTimerStatus = TimerStart(&NotificationTimer, 30*1000);

    /*
     * The timer will transmit the first notification in 30 seconds. We
     * call the callback function directly to transmit the first
     * notification right now.
     */
    ZCB_NotificationTimerCallback(NULL);
  }
  else
  {
    DPRINT("\r\nNtfctn stop");
    /* Deactivate overload timer */
    TimerStop(&NotificationTimer);
    notificationOverLoadTimerStatus = ESWTIMER_STATUS_FAILED;
  }
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. PowerStrip_hw.c.
 */
ZW_WEAK void PowerStrip_hw_init(void)
{

}
