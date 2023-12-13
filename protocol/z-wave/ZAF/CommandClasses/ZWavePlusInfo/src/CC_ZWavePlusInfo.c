/***************************************************************************
*
* @copyright 2018 Silicon Laboratories Inc.
* @brief ZWave+ Info Command Class source file
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <cc_zwave_plus_info_config_api.h>
#include <string.h>
#include <ZW_TransportEndpoint.h>
#include "Assert.h"
#include "zaf_config.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

/**
 * Define current version of Z-Wave+
 */
#define ZW_PLUS_VERSION 2

#define ZWPLUSINFO_ICONTYPE_HIGH(byte) ((uint8_t)(byte >> 8))
#define ZWPLUSINFO_ICONTYPE_LOW(byte)  ((uint8_t)(byte & 0xff))

/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

zw_plus_info_config_icons_t unassinged_icons =
{
  .installer_icon_type = ICON_TYPE_UNASSIGNED,
  .user_icon_type = ICON_TYPE_UNASSIGNED,
  .endpoint = 0
};

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static received_frame_status_t
CC_ZWavePlusInfo_handler(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_APPLICATION_TX_BUFFER *pCmd,
    __attribute__((unused)) uint8_t cmdLength,
    ZW_APPLICATION_TX_BUFFER * pFrameOut,
    uint8_t * pLengthOut
)
{

  if (pCmd->ZW_Common.cmd == ZWAVEPLUS_INFO_GET)
  {
    /*Check pTxBuf is free*/
    if(false == Check_not_legal_response_job(rxOpt))
    {
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.cmdClass = COMMAND_CLASS_ZWAVEPLUS_INFO;
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.cmd = ZWAVEPLUS_INFO_REPORT;
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.zWaveVersion = ZW_PLUS_VERSION;
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.roleType = ZAF_CONFIG_APP_ROLE_TYPE;
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.nodeType = ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE;  /* Hardcoded */

      uint8_t numOfEndpoint = cc_zwave_plus_info_config_get_endpoint_count();
      zw_plus_info_config_icons_t *pIcons;

      if ((0 != numOfEndpoint ) &&                       // Must be the first check so that we avoid reading from a NULL pointer.
         (numOfEndpoint >= rxOpt->destNode.endpoint) &&
         (0 != rxOpt->destNode.endpoint))
      {
        pIcons = cc_zwave_plus_info_config_get_endpoint_entry(rxOpt->destNode.endpoint);
      }
      else
      {
        pIcons = cc_zwave_plus_info_config_get_root_icons();
      }

      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.installerIconType1 = ZWPLUSINFO_ICONTYPE_HIGH(pIcons->installer_icon_type);
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.installerIconType2 = ZWPLUSINFO_ICONTYPE_LOW(pIcons->installer_icon_type);
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.userIconType1 = ZWPLUSINFO_ICONTYPE_HIGH(pIcons->user_icon_type);
      pFrameOut->ZW_ZwaveplusInfoReportV2Frame.userIconType2 = ZWPLUSINFO_ICONTYPE_LOW(pIcons->user_icon_type);

      *pLengthOut = sizeof(ZW_ZWAVEPLUS_INFO_REPORT_V2_FRAME);
      return RECEIVED_FRAME_STATUS_SUCCESS;
    }
    return RECEIVED_FRAME_STATUS_FAIL;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

ZW_WEAK uint8_t cc_zwave_plus_info_config_get_endpoint_count(void)
{
  return 0;
}

ZW_WEAK zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_endpoint_entry(__attribute__((unused)) uint8_t endpoint)
{
  return &unassinged_icons;
}

REGISTER_CC_V2(COMMAND_CLASS_ZWAVEPLUS_INFO, ZWAVEPLUS_INFO_VERSION_V2, CC_ZWavePlusInfo_handler);
