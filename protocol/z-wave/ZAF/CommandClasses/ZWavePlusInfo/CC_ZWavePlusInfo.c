/***************************************************************************
*
* @copyright 2018 Silicon Laboratories Inc.
* @brief ZWave+ Info Command Class source file
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <cc_zwave_plus_info_config_api.h>
#include <ZW_plus_version.h>
#include <string.h>
#include <ZW_TransportEndpoint.h>
#include "Assert.h"
#include "ZAF_tx_mutex.h"
#include "zaf_config.h"

/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/

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
    uint8_t cmdLength
)
{
  UNUSED(cmdLength);

  if (pCmd->ZW_Common.cmd == ZWAVEPLUS_INFO_GET)
  {
    /*Check pTxBuf is free*/
    if(false == Check_not_legal_response_job(rxOpt))
    {

      ZAF_TRANSPORT_TX_BUFFER  TxBuf;
      ZW_APPLICATION_TX_BUFFER *pTxBuf = &(TxBuf.appTxBuf);
      memset((uint8_t*)pTxBuf, 0, sizeof(ZW_APPLICATION_TX_BUFFER) );
      ZW_ZWAVEPLUS_INFO_REPORT_V2_FRAME * pFrame = &pTxBuf->ZW_ZwaveplusInfoReportV2Frame;

      TRANSMIT_OPTIONS_TYPE_SINGLE_EX *pTxOptionsEx;
      RxToTxOptions(rxOpt, &pTxOptionsEx);
      pFrame->cmdClass = COMMAND_CLASS_ZWAVEPLUS_INFO;
      pFrame->cmd = ZWAVEPLUS_INFO_REPORT;
      pFrame->zWaveVersion = ZW_PLUS_VERSION;
      pFrame->roleType = ZAF_CONFIG_APP_ROLE_TYPE;
      pFrame->nodeType = ZWAVEPLUS_INFO_REPORT_NODE_TYPE_ZWAVEPLUS_NODE;  /* Hardcoded */

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

      pFrame->installerIconType1 = ZWPLUSINFO_ICONTYPE_HIGH(pIcons->installer_icon_type);
      pFrame->installerIconType2 = ZWPLUSINFO_ICONTYPE_LOW(pIcons->installer_icon_type);
      pFrame->userIconType1 = ZWPLUSINFO_ICONTYPE_HIGH(pIcons->user_icon_type);
      pFrame->userIconType2 = ZWPLUSINFO_ICONTYPE_LOW(pIcons->user_icon_type);

      {
        uint8_t txResult;

        txResult = Transport_SendResponseEP(
                      (uint8_t *)pTxBuf,
                      sizeof(pTxBuf->ZW_ZwaveplusInfoReportV2Frame),
                      pTxOptionsEx,
                      NULL);

        if (ZAF_ENQUEUE_STATUS_SUCCESS != txResult)
        {
          ;
        }
      }
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

ZW_WEAK zw_plus_info_config_icons_t * cc_zwave_plus_info_config_get_endpoint_entry(uint8_t endpoint)
{
  UNUSED(endpoint);
  return &unassinged_icons;
}

REGISTER_CC(COMMAND_CLASS_ZWAVEPLUS_INFO, ZWAVEPLUS_INFO_VERSION_V2, CC_ZWavePlusInfo_handler);
