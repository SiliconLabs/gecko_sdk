/**
* @file
* Command Class Firmware Update source file.
* @copyright 2018 Silicon Laboratories Inc.
*/

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include "CC_FirmwareUpdate.h"
#include <ZW_TransportLayer.h>
#include "ota_util.h"
#include <CRC.h>
#include <string.h>
#include <zaf_config_api.h>
#include <cc_firmware_update_config.h>
#include "zaf_transport_tx.h"

//#define DEBUGPRINT
#include "DebugPrint.h"
/****************************************************************************/
/*                      PRIVATE TYPES and DEFINITIONS                       */
/****************************************************************************/


/****************************************************************************/
/*                              PRIVATE DATA                                */
/****************************************************************************/

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

/****************************************************************************/
/*                            PRIVATE FUNCTIONS                             */
/****************************************************************************/

static received_frame_status_t
CC_FirmwareUpdate_handler(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_APPLICATION_TX_BUFFER *pCmd,
  uint8_t cmdLength,
  ZW_APPLICATION_TX_BUFFER *pFrameOut,
  uint8_t * pFrameOutLength)
{
  if (true == Check_not_legal_response_job(rxOpt))
  {
    // None of the following commands support endpoint bit addressing.
    DPRINT("RECEIVED_FRAME_STATUS_FAIL\n");
    return RECEIVED_FRAME_STATUS_FAIL;
  }

  switch (pCmd->ZW_Common.cmd)
  {
    case FIRMWARE_MD_GET_V5:
    {
      uint8_t * pData;

      uint16_t manufacturerID = zaf_config_get_manufacturer_id();

      uint8_t numberOfFirmwareTargets;

      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.cmdClass = COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5;
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.cmd = FIRMWARE_MD_REPORT_V5;
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.manufacturerId1 = (uint8_t)(manufacturerID >> 8);
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.manufacturerId2 = (uint8_t)(manufacturerID & 0xFF);
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.firmware0Id1 = (uint8_t)(handleFirmWareIdGetExtended(0) >> 8);
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.firmware0Id2 = (uint8_t)(handleFirmWareIdGetExtended(0) & 0xff);
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.firmware0Checksum1 = 0x00; // Checksum N/A for SDK7
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.firmware0Checksum2 = 0x00; // Checksum N/A for SDK7
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.firmwareUpgradable = 0xFF; // Hardcode to upgradable.
      numberOfFirmwareTargets = zaf_config_get_firmware_target_count();
      if(zaf_config_get_bootloader_upgradable()) {
        numberOfFirmwareTargets++;
      }
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.numberOfFirmwareTargets = numberOfFirmwareTargets - 1; /* -1 : Firmware version 0 */
      uint16_t maxFragmentSize = handleCommandClassFirmwareUpdateMaxFragmentSize();
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.maxFragmentSize1 = (uint8_t)(maxFragmentSize >> 8);
      pFrameOut->ZW_FirmwareMdReport1byteV5Frame.maxFragmentSize2 = (uint8_t)maxFragmentSize;
      pData = (uint8_t *)pFrameOut;
      uint8_t  i;
      for (i = 1; i < numberOfFirmwareTargets; i++)
      {
        *(pData + 10 + (2 * i)) = (uint8_t)(handleFirmWareIdGetExtended(i) >> 8);
        *(pData + 10 + (2 * i) + 1) = (uint8_t)(handleFirmWareIdGetExtended(i) & 0xff);
      }
      // Fill out the hardwareVersion field, located right after the 0-n extra firmwareId fields
      *(pData + 10 + (2 * i)) = zaf_config_get_hardware_version();

      *pFrameOutLength = (uint8_t)(10 + (2 * i) + 1);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    }
    break;
    case FIRMWARE_UPDATE_MD_REPORT_V5:
      {
        DPRINT("FIRMWARE_UPDATE_MD_REPORT_V5 - Report received!\n");

        uint16_t crc16Result = CRC_CheckCrc16(CRC_INITAL_VALUE, &(pCmd->ZW_Common.cmdClass), cmdLength);
        DPRINTF("crc16Result = 0x%04x (valid CRC = %s)\n", crc16Result, (crc16Result == 0) ? "true" : "false");

        uint16_t  firmwareUpdateReportNumber = (uint16_t)((uint16_t)(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.properties1 &
                                      FIRMWARE_UPDATE_MD_REPORT_PROPERTIES1_REPORT_NUMBER_1_MASK_V5) << 8) +
                                     (uint16_t)(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.reportNumber2);
        DPRINTF("Report number = 0x%04x (dec: %u)\n", firmwareUpdateReportNumber, firmwareUpdateReportNumber);

        uint8_t fw_actualFrameSize =  cmdLength -
                                  /* Calculate length of actual data1 field */
                                  (uint8_t)(sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.cmdClass) +
                                   sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.cmd) +
                                   sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.properties1) +
                                   sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.reportNumber2) +
                                   sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.checksum1) +
                                   sizeof(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.checksum2));
        DPRINTF("fw_actualFrameSize = 0x%02x\n", fw_actualFrameSize);

        handleCmdClassFirmwareUpdateMdReport(crc16Result,
                                             firmwareUpdateReportNumber,
                                             pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.properties1,
                                             &(pCmd->ZW_FirmwareUpdateMdReport1byteV5Frame.data1),
                                             fw_actualFrameSize);


      }
      return RECEIVED_FRAME_STATUS_SUCCESS;
    case FIRMWARE_UPDATE_MD_REQUEST_GET_V5:
      {
        uint8_t status = 0;
        zaf_tx_options_t tx_options;

        handleCmdClassFirmwareUpdateMdReqGet(
            rxOpt,
            (ZW_FIRMWARE_UPDATE_MD_REQUEST_GET_V5_FRAME *)pCmd,
            cmdLength,
            &status);

        ZAF_TRANSPORT_TX_BUFFER  TxBuf = {
          .appTxBuf.ZW_FirmwareUpdateMdRequestReportV5Frame.cmdClass = COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5,
          .appTxBuf.ZW_FirmwareUpdateMdRequestReportV5Frame.cmd = FIRMWARE_UPDATE_MD_REQUEST_REPORT_V5,
          .appTxBuf.ZW_FirmwareUpdateMdRequestReportV5Frame.status = status
        };

        zaf_transport_rx_to_tx_options(rxOpt, &tx_options);
        tx_options.use_supervision = true;
        if(!zaf_transport_tx((uint8_t *)&(TxBuf.appTxBuf),
                sizeof(ZW_FIRMWARE_UPDATE_MD_REQUEST_REPORT_V5_FRAME),
                ZCB_CmdClassFwUpdateMdReqReport, &tx_options))
        {
          transmission_result_t txResult = {
            .status = TRANSMIT_COMPLETE_FAIL
          };
          ZCB_CmdClassFwUpdateMdReqReport(&txResult);
        }
        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
    case FIRMWARE_UPDATE_ACTIVATION_SET_V5:
    {
      uint8_t status;
      if (true != CC_FirmwareUpdate_ActivationSet_handler((ZW_FIRMWARE_UPDATE_ACTIVATION_SET_V5_FRAME *)pCmd, &status))
      {
        memcpy(
            ((uint8_t*)pFrameOut),
            ((uint8_t*)pCmd),
            sizeof(ZW_FIRMWARE_UPDATE_ACTIVATION_SET_V5_FRAME) - 1);

        pFrameOut->ZW_FirmwareUpdateActivationStatusReportV5Frame.cmd = FIRMWARE_UPDATE_ACTIVATION_STATUS_REPORT_V5;
        pFrameOut->ZW_FirmwareUpdateActivationStatusReportV5Frame.firmwareUpdateStatus = FIRMWARE_UPDATE_ACTIVATION_STATUS_REPORT_INVALID_COMBINATION_V5;
        pFrameOut->ZW_FirmwareUpdateActivationStatusReportV5Frame.hardwareVersion = pCmd->ZW_FirmwareUpdateActivationSetV5Frame.hardwareVersion;
        pFrameOut->ZW_FirmwareUpdateActivationStatusReportV5Frame.firmwareUpdateStatus = status;

        *pFrameOutLength = sizeof(ZW_FIRMWARE_UPDATE_ACTIVATION_STATUS_REPORT_V5_FRAME);

        return RECEIVED_FRAME_STATUS_SUCCESS;
      }
      return RECEIVED_FRAME_STATUS_FAIL;
    }
    case FIRMWARE_UPDATE_MD_PREPARE_GET_V5:
    {
      pFrameOut->ZW_FirmwareUpdateMdPrepareReportV5Frame.cmdClass = COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5;
      pFrameOut->ZW_FirmwareUpdateMdPrepareReportV5Frame.cmd = FIRMWARE_UPDATE_MD_PREPARE_REPORT_V5;

      pFrameOut->ZW_FirmwareUpdateMdPrepareReportV5Frame.status = FIRMWARE_UPDATE_MD_PREPARE_REPORT_NOT_DOWNLOADABLE_V5;

      // The firmware checksum is irrelevant when we report that it's not downloadable.
      pFrameOut->ZW_FirmwareUpdateMdPrepareReportV5Frame.firmwareChecksum1 = 0x00;
      pFrameOut->ZW_FirmwareUpdateMdPrepareReportV5Frame.firmwareChecksum2 = 0x00;

      *pFrameOutLength = sizeof(ZW_FIRMWARE_UPDATE_MD_PREPARE_REPORT_V5_FRAME);

      return RECEIVED_FRAME_STATUS_SUCCESS;
    }
    default:
      break;
  }
  return RECEIVED_FRAME_STATUS_NO_SUPPORT;
}

ZW_WEAK bool CC_FirmwareUpdate_SetStartCallback(__attribute__((unused)) uint16_t fwId, __attribute__((unused)) uint16_t CRC)
{
  return true;
}

ZW_WEAK void CC_FirmwareUpdate_SetFinishCallback(__attribute__((unused)) OTA_STATUS pOtaFinish)
{
}

static void init_and_reset(void)
{
  CC_FirmwareUpdate_Init(&CC_FirmwareUpdate_SetStartCallback,
                         &CC_FirmwareUpdate_SetFinishCallback,
                         CC_FIRMWARE_UPDATE_CONFIG_SUPPORT_ACTIVATION);
}

REGISTER_CC_V4(COMMAND_CLASS_FIRMWARE_UPDATE_MD_V5, FIRMWARE_UPDATE_MD_VERSION_V5, CC_FirmwareUpdate_handler, NULL, NULL, NULL, 0, init_and_reset, init_and_reset);

