/**
 * Z-Wave Certified Application LED Bulb
 *
 * @copyright 2020 Silicon Laboratories Inc.
 */
#include "zw_config_rf.h"
#include <stdbool.h>
#include <stdint.h>
#include <MfgTokens.h>
#include "DebugPrintConfig.h"
//#define DEBUGPRINT
#include "DebugPrint.h"
#include <ZW_classcmd.h>
#include <ZW_system_startup_api.h>
#include <cc_multilevel_switch_support_config_api.h>
#include <CC_Indicator.h>
#include "zaf_config_security.h"
#include <ZAF_Common_helper.h>
#include <ZAF_Common_interface.h>
#include <ZAF_network_learn.h>
#include <ota_util.h>
#include <ZAF_TSE.h>
#include "events.h"
#include <zpal_watchdog.h>
#include <LEDBulb_hw.h>
#include <board_indicator.h>
#include "zw_region_config.h"
#include "zw_build_no.h"
#include "ZAF_ApplicationEvents.h"
#include <zaf_event_distributor_soc.h>
#include <zpal_misc.h>

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

static void ApplicationTask(SApplicationHandles* pAppHandles);

/**
 * @brief See description for function prototype in ZW_basis_api.h.
 */
ZW_APPLICATION_STATUS ApplicationInit(EResetReason_t eResetReason)
{
  UNUSED(eResetReason);

  zpal_enable_watchdog(true);

#ifdef DEBUGPRINT
  zpal_debug_init();
  static uint8_t m_aDebugPrintBuffer[96];
  DebugPrintConfig(m_aDebugPrintBuffer, sizeof(m_aDebugPrintBuffer), zpal_debug_output);
#endif

  DPRINT("\n\n--------------------------------\n");
  DPRINT("Z-Wave Sample App: LED Bulb\n");
  DPRINTF("SDK: %d.%d.%d ZAF: %d.%d.%d.%d\n",
          SDK_VERSION_MAJOR,
          SDK_VERSION_MINOR,
          SDK_VERSION_PATCH,
          zpal_get_app_version_major(),
          zpal_get_app_version_minor(),
          zpal_get_app_version_patch(),
          ZAF_BUILD_NO);

  DPRINTF("ApplicationInit eResetReason = %d\n", eResetReason);

  // Read Rf region from MFG_ZWAVE_COUNTRY_FREQ
  zpal_radio_region_t regionMfg;
  ZW_GetMfgTokenDataCountryFreq((void*) &regionMfg);
  if (isRfRegionValid(regionMfg)) {
    RadioConfig.eRegion = regionMfg;
  } else {
    ZW_SetMfgTokenDataCountryRegion((void*) &RadioConfig.eRegion);
  }

  /*
   * Register the main application task.
   *
   * Attention: this is the only FreeRTOS task that can invoke the ZAF API.
   *
   * ZW_UserTask_CreateTask() can be used to create additional application tasks. See the
   * Sensor PIR application for an example use of ZW_UserTask_CreateTask().
   */
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
static void ApplicationTask(SApplicationHandles* pAppHandles)
{
  ZAF_Init(&ProtocolConfig, xTaskGetCurrentTaskHandle(), pAppHandles);

  zaf_event_distributor_init();

  LEDBulb_hw_init();

  Board_IndicatorInit();
  Board_IndicateStatus(BOARD_STATUS_IDLE);

  /* Enter SmartStart*/
  /* Protocol will commence SmartStart only if the node is NOT already included in the network */
  ZAF_setNetworkLearnMode(E_NETWORK_LEARN_MODE_INCLUSION_SMARTSTART);

  cc_firmware_update_send_status_report();

  // Wait for and process events
  DPRINT("LED Bulb Event processor Started\r\n");
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

  switch(event)
  {
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
      // Unknow event - do nothing.
      break;
  }
}

/*
 * The below functions should be implemented as hardware specific functions in a separate source
 * file, e.g. LEDBulb_hw.c.
 */
ZW_WEAK void LEDBulb_hw_init(void)
{
}
