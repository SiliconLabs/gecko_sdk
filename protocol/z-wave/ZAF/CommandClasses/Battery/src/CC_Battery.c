/**
*
* @brief Battery Command Class source file
* @copyright 2019 Silicon Laboratories Inc.
*
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_TransportLayer.h>

#include <CC_Battery.h>
#include "cc_battery_io.h"
#include <ZW_TransportMulticast.h>
#include <string.h>
#include <ZAF_Common_interface.h>
#include <ZAF_file_ids.h>

//#define DEBUGPRINT
#include "DebugPrint.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/
#define BATTERY_DATA_UNASSIGNED_VALUE (CMD_CLASS_BATTERY_LEVEL_FULL + 1)  // Just some value not defined in cc_battery_level_t

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/
static SBatteryData BatteryData;

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static received_frame_status_t
CC_Battery_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)  
{
  UNUSED(cmdLength);

  if (pCmd->ZW_Common.cmd == BATTERY_GET)
  {
    if (true == Check_not_legal_response_job(rxOpt))
    {
      // None of the following commands support endpoint bit addressing.
      return RECEIVED_FRAME_STATUS_FAIL;
    }

    pFrameOut->ZW_BatteryReportFrame.cmdClass = COMMAND_CLASS_BATTERY;
    pFrameOut->ZW_BatteryReportFrame.cmd = BATTERY_REPORT;
    pFrameOut->ZW_BatteryReportFrame.batteryLevel = CC_Battery_BatteryGet_handler(rxOpt->destNode.endpoint);

    *pFrameOutLength = sizeof(ZW_BATTERY_REPORT_FRAME);

    return RECEIVED_FRAME_STATUS_SUCCESS;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

static uint8_t lifeline_reporting(ccc_pair_t * p_ccc_pair)
{
  p_ccc_pair->cmdClass = COMMAND_CLASS_BATTERY;
  p_ccc_pair->cmd      = BATTERY_REPORT;
  return 1;
}

static void reset(void) {
  BatteryData.lastReportedBatteryLevel = BATTERY_DATA_UNASSIGNED_VALUE;
  cc_battery_write(&BatteryData);
}

static void init(void) {
  if(!cc_battery_read(&BatteryData)) {
    reset();
  }
}

/****************************************************************************/
/*                            PUBLIC FUNCTIONS                              */
/****************************************************************************/

bool cc_battery_check_level_changed(void)
{
  uint8_t currentBatteryLevel;

  if (EINCLUSIONSTATE_EXCLUDED == ZAF_GetInclusionState())
  {
    // We are not network included. Nothing to do.
    DPRINTF("\r\n%s: Not included\r\n", __func__);
    return false;
  }

  currentBatteryLevel = CC_Battery_BatteryGet_handler(ENDPOINT_ROOT);
  DPRINTF("\r\n%s: Current Level=%d, Last reported level=%d\r\n", __func__, currentBatteryLevel, BatteryData.lastReportedBatteryLevel);

  if ((currentBatteryLevel == BatteryData.lastReportedBatteryLevel) ||
      (currentBatteryLevel == BatteryData.lastReportedBatteryLevel + cc_battery_config_get_reporting_decrements())) // Hysteresis
  {
    // Battery level hasn't changed (significantly) since last reported. Do nothing
    return false;
  }

  return true;
}

bool
CC_Battery_LevelReport_tx(
  const AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult))
{
  CMD_CLASS_GRP cmdGrp = {COMMAND_CLASS_BATTERY, BATTERY_REPORT};
  uint8_t battLevel = CC_Battery_BatteryGet_handler(sourceEndpoint);

  if(JOB_STATUS_SUCCESS == cc_engine_multicast_request(pProfile, sourceEndpoint, &cmdGrp, &battLevel, 1, false, pCbFunc)) {
    BatteryData.lastReportedBatteryLevel = battLevel;
    cc_battery_write(&BatteryData);    
    return true;
  } else {
    return false;
  }
}

ZW_WEAK uint8_t 
CC_Battery_BatteryGet_handler(uint8_t endpoint)
{
  UNUSED(endpoint);

  return (uint8_t)CMD_CLASS_BATTERY_LEVEL_FULL;
}

REGISTER_CC_V4(COMMAND_CLASS_BATTERY, BATTERY_VERSION, CC_Battery_handler, NULL, NULL, lifeline_reporting, 0, init, reset);
