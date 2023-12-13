/**
 * @file
 * This module implements functions used in combination with command class firmware update.
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _OTA_UTIL_H_
#define _OTA_UTIL_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <stdbool.h>
#include <stdint.h>
#include "ZAF_types.h"
#include "CC_FirmwareUpdate.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup cc_firmware_update
 * @{
 */

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

/**
 * Defines for WaitTime field used in commmand = FIRMWARE_UPDATE_MD_STATUS_REPORT.
 * The WaitTime field MUST report the time that is needed before the receiving
 * node again becomes available for communication after the transfer of an image.
 * The unit is the second.
 */
#ifndef WAITTIME_FWU_FAIL
#define WAITTIME_FWU_FAIL 2
#endif

/**
 * Please see description of CC_FirmwareUpdate_Init().
 * @private
 */
typedef bool (*CC_FirmwareUpdate_start_callback_t)(uint16_t fwId, uint16_t CRC);

/**
 * Please see description of CC_FirmwareUpdate_Init().
 * @private
 */
typedef void (*CC_FirmwareUpdate_finish_callback_t)(OTA_STATUS status);

/**
 * Initializes the Firmware Update Meta Data Command Class.
 *
 * This function must be invoked before a firmware update can be initiated.
 *
 * @param[in] pOtaStart Pointer to a function that is invoked when another node initiates a firmware
 *                      update. If the function returns true, the process will continue. If the
 *                      function returns false, the node will report to the initiator that the
 *                      firmware update requires authentication. The function must take two
 *                      arguments where the first one is the firmware ID and the second one is the
 *                      CRC value of the firmware.
 *                      The argument is not required and can be set to NULL. In that case the
 *                      firmware update process will continue without invoking the function.
 *
 * @param[in] pOtaFinish Pointer to a function that is invoked when the firmware update process
 *                       finishes either successfully or with an error. If the device reboots right
 *                       after the firmware update, the function is invoked before the reboot.
 *                       The function must take an argument that is the status of the firmware
 *                       update.
 *                       The argument is not required and can be set to NULL.
 *
 * @param[in] support_activation Lets the application decide whether delayed activation of the
 *                               firmware is supported. If set to true and the Activation bit in
 *                               Request Get is set to 1, the node will not reboot to the new
 *                               firmware image, but will instead wait for an Activation Set
 *                               command.
 * @return 1 if NVM is supported else 0.
 * @private
 */
bool CC_FirmwareUpdate_Init(
  CC_FirmwareUpdate_start_callback_t pOtaStart,
  CC_FirmwareUpdate_finish_callback_t pOtaFinish,
  bool support_activation);

/**
 * @brief ZCB_CmdClassFwUpdateMdReqReport
 * Callback function receive status on Send data FIRMWARE_UPDATE_MD_REQUEST_REPORT_V3
 * @param pTxResult : TRANSMIT_COMPLETE_OK, TRANSMIT_COMPLETE_NO_ACK, TRANSMIT_COMPLETE_FAIL...
 * @private
 */
void ZCB_CmdClassFwUpdateMdReqReport(transmission_result_t * pTxResult);

/**
 * Handles an Activation Set command.
 *
 * If the fields in the frame match the firmware that is ready to be activated, the device
 * will reboot into the new image and transmit an Activation Report.
 * If the fields do not match, the function will return false.
 * @param pFrame The Activation Set frame.
 * @param pStatus Status if the activation failed.
 * @return Returns false if the received values do not match with the stored firmware image. If
 *         they match, the function will not return, but the device will reboot from the new image.
 * @private
 */
bool CC_FirmwareUpdate_ActivationSet_handler(
  ZW_FIRMWARE_UPDATE_ACTIVATION_SET_V5_FRAME * pFrame,
  uint8_t * pStatus);

/**
 * Returns the maximum fragment size.
 * @return Maximum fragment size.
 * @private
 */
uint16_t handleCommandClassFirmwareUpdateMaxFragmentSize(void);

/**
 * Gets maximum number of reports that can be sent in FW Update MD Get
 * @return Number of Reports, greater of equal to 1.
 * @private
 */
uint8_t getFWUpdateMDGetNumberOfReports(void);

/**
 * @brief This function returns a firmware ID based on a given target index.
 *
 * @param[in] n the target index (0,1..N-1)
 * @return target n firmware ID
 * @private
 */
uint16_t handleFirmWareIdGetExtended(uint8_t n);

/**
 * Initiates a firmware update.
 * @param[in] rxOpt The options that the Firmware Update MD Request Get was received with. The
 *                  options must be passed because they are used later when sending a status report.
 * @param[in] pFrame Pointer to the Firmware Update MD Request Get frame.
 * @param[in] cmdLength Length of the frame.
 * @param[out] pStatus Pointer to a value where the status of the initiation can be written. The
 *                     status can take one of the following values:
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_INVALID_COMBINATION_V5,
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_REQUIRES_AUTHENTICATION_V5,
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_INVALID_FRAGMENT_SIZE_V5,
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_NOT_UPGRADABLE_V5,
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_INVALID_HARDWARE_VERSION_V5, or
 *                       FIRMWARE_UPDATE_MD_REQUEST_REPORT_VALID_COMBINATION_V5
 * @private
 */
void
handleCmdClassFirmwareUpdateMdReqGet(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  ZW_FIRMWARE_UPDATE_MD_REQUEST_GET_V5_FRAME * pFrame,
  uint8_t cmdLength,
  uint8_t* pStatus);

/**
 * @brief handleCmdClassFirmwareUpdateMdReport
 * Application function to handle incoming frame Firmware update MD Report
 * @param crc16Result
 * @param firmwareUpdateReportNumber
 * @param properties
 * @param pData
 * @param fw_actualFrameSize
 * @private
 */
void
handleCmdClassFirmwareUpdateMdReport(uint16_t crc16Result,
                                     uint16_t firmwareUpdateReportNumber,
                                     uint8_t properties,
                                     uint8_t* pData,
                                     uint8_t fw_actualFrameSize);

/**
 * @}
 * @}
 */

#endif /* _OTA_UTIL_H_ */
