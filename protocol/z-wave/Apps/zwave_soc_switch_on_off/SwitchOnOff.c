/**
 * Z-Wave Certified Application Switch On/Off
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

#include <string.h>
#include <ev_man.h>

#include <AppTimer.h>
#include <SwTimer.h>
#include <EventDistributor.h>
#include <ZW_system_startup_api.h>
#include <ZW_application_transport_interface.h>

#include <CC_AssociationGroupInfo.h>
#include <CC_Basic.h>
#include <CC_BinarySwitch.h>
#include <CC_DeviceResetLocally.h>
#include <CC_Indicator.h>
#include <CC_Supervision.h>
#include <CC_FirmwareUpdate.h>
#include <zaf_config_api.h>
#include <zaf_config.h>
#include "zaf_config_security.h"
#include <zaf_event_helper.h>
#include <zaf_job_helper.h>

#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include <ota_util.h>
#include <ZAF_TSE.h>
#include <ZAF_CmdPublisher.h>
#include <ZAF_network_management.h>
#include "events.h"
#include <zpal_watchdog.h>
#include <zpal_misc.h>
#include <zpal_radio.h>
#include <SwitchOnOff_hw.h>
#include <board_indicator.h>
#include <board_init.h>
#include "zw_region_config.h"
#include "zw_build_no.h"
#include "ZAF_ApplicationEvents.h"
#include "cc_binary_switch_config_api.h"
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

#ifdef DEBUGPRINT
static uint8_t m_aDebugPrintBuffer[96];
#endif

// Pointer to AppHandles that is passed as input to ApplicationTask(..)
SApplicationHandles* g_pAppHandles;

/* True Status Engine (TSE) variables */
/* Indicate here which End Points (including root device) support each command class */
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

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/
void ApplicationTask(SApplicationHandles* pAppHandles);

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

  DPRINT("\n\n--------------------------------\n");
  DPRINT("Z-Wave Sample App: Switch On/Off\n");
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

  zaf_event_distributor_init();

  SwitchOnOff_hw_init();

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  cc_firmware_update_send_status_report();

  // Wait for and process events
  DPRINT("SwitchOnOff Event processor Started\r\n");
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
zaf_event_distributor_app_event_manager(uint8_t event)
{
  DPRINTF("zaf_event_distributor_app_event_manager Ev: %d\r\n", event);
  cc_binary_switch_t * p_switches;

  switch (event)
  {
    case EVENT_APP_BUTTON_TOGGLE_SHORT_PRESS:

      p_switches = cc_binary_switch_get_config();
      if (cc_binary_switch_get_current_value(&p_switches[0]) > 0) 
        {
          cc_binary_switch_set(&p_switches[0], 0);
        } 
      else 
        {
          cc_binary_switch_set(&p_switches[0], 0xFF); // 0xFF for last on value.
        }
      break;
    
    case EVENT_APP_BUTTON_TOGGLE_HOLD:
      /*
       * This shows how to force the transmission of an Included NIF. Normally, an INIF is
       * transmitted when the product is power cycled while already being included in a network.
       * If the enduser cannot power cycle the product, e.g. because the battery cannot be
       * removed, the transmission of an INIF must be manually triggered.
       */
      DPRINT("TX INIF");
      ZAF_SendINIF(NULL);
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
      // Unknow event - do nothing.
      break;
  }
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. SwitchOnOff_hw.c.
 */
ZW_WEAK void SwitchOnOff_hw_init(void)
{

}
