/**
 * @file
 * Handler for Command Class Firmware Update.
 * @copyright 2018 Silicon Laboratories Inc.
 *
 * @brief Current version do not support FIRMWARE_UPDATE_ACTIVATION_SET_V4 why
 * FIRMWARE_UPDATE_ACTIVATION_STATUS_REPORT_V4 return status ERROR_ACTIVATION_FIRMWARE.
 * Customers who need this feature can modify command class source and header
 * files for the specific purpose.
 *
 * @addtogroup CC
 * @{
 * @addtogroup cc_firmware_update Firmware Update Meta Data
 * @{
 *
 * Command Class Firmware Update Meta Data enables a device to have its firmware updated remotely.
 *
 * CC Firmware Update MD can be configured in cc_firmware_update_config.h.
 *
 * This CC offers the option to define two functions in the application that will override the weak
 * implementations:
 * - CC_FirmwareUpdate_SetStartCallback()
 * - CC_FirmwareUpdate_SetFinishCallback()
 *
 * The specification of CC Firmware Update MD can be found in
 * https://github.com/Z-Wave-Alliance/AWG/tree/main/source/management_command_classes/command_class_definitions
 *
 * @}
 * @}
 */

#ifndef _CC_FIRMWAREUPDATE_H_
#define _CC_FIRMWAREUPDATE_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_classcmd.h>
#include <ZAF_types.h>
#include <CC_Common.h>
#include "ota_util.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup cc_firmware_update
 * @{
 */

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

typedef enum
{
  INVALID_COMBINATION = 0x00,
  ERROR_ACTIVATION_FIRMWARE = 0x01,
  FWU_SUCCESS = 0xFF
} e_firmware_update_activation_status_report_update_status;


//If this struct is changed please increase FIRMWARE_UPDATE_FILE_VERSION in ota_util.c
typedef struct
{
  /**
   * Required when booting for the first time after a firmware update. If set to 1 (true), the
   * current firmware (given a successful firmware update) was activated using Activation Set.
   * Otherwise, the firmware was updated instantly after transferring the firmware image.
   */
  uint8_t activation_was_applied;

  //Version number for this file.
  //WARNING: Do not move this field. It must always be the second byte of the struct.
  uint8_t fileVersion;

  /**
   * The checksum of the most recent firmware image transferred.
   */
  uint16_t checksum;

  /**
   * RX options from the Request Get frame sent by the initiator of the firmware update.
   *
   * The values are extracted from the type RECEIVE_OPTIONS_TYPE_EX instead of using the type
   * directly in the file. RECEIVE_OPTIONS_TYPE_EX contains values that are not needed and it
   * might change over time possibly making the file invalid.
   */
  node_id_t srcNodeID;
  uint8_t srcEndpoint;
  uint8_t rxStatus;
  uint32_t securityKey;

  //Extra padding to make this file larger than SFirmwareUpdateFile_DEPRECATED_V0 below
  //Needed to distinguish between the two formats for automatic file migration.
  //Can be used to contain new info if needed.
  uint32_t reserved_padding;
}
SFirmwareUpdateFile;

//Original version of SFirmwareUpdateFile.
//Used only for automatic migration of the file to newer version.
//The compiler automatically sets 2 padding bytes in the struct that ends up 12 bytes long.
typedef struct
{
  uint8_t  activation_was_applied;
//One padding byte here
  uint16_t checksum;
  uint8_t  srcNodeID;
  uint8_t  srcEndpoint;
  uint8_t  rxStatus;
//One padding byte here
  uint32_t securityKey;
}
SFirmwareUpdateFile_DEPRECATED_V0;

#define ZAF_FILE_SIZE_CC_FIRMWARE_UPDATE (sizeof(SFirmwareUpdateFile))

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/


/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

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
extern void
handleCmdClassFirmwareUpdateMdReport( uint16_t crc16Result,
                                      uint16_t firmwareUpdateReportNumber,
                                      uint8_t properties,
                                      uint8_t* pData,
                                      uint8_t fw_actualFrameSize);



/**
 * @brief Send a Md status report
 * @param[in] rxOpt receive options
 * @param[in] status Values used for Firmware Update Md Status Report command
 * FIRMWARE_UPDATE_MD_STATUS_REPORT_UNABLE_TO_RECEIVE_WITHOUT_CHECKSUM_ERROR_V3     0x00
 * FIRMWARE_UPDATE_MD_STATUS_REPORT_UNABLE_TO_RECEIVE_V3                            0x01
 * FIRMWARE_UPDATE_MD_STATUS_REPORT_SUCCESSFULLY_STORED_V3                          0xFE
 * FIRMWARE_UPDATE_MD_STATUS_REPORT_SUCCESSFULLY_V3                                 0xFF
 * @param[in] waitTime field MUST report the time that is needed before the receiving
 * node again becomes available for communication after the transfer of an image. The unit is
 * the second. The value 0 (zero) indicates that the node is already available again. The value
 * 0 (zero) MUST be returned when the Status field carries the values 0x00, 0x01 and 0xFE.
 * The value 0xFFFF is reserved for future use and MUST NOT be returned.
 * @param[out] pCbFunc function pointer returning status on the job.
 * @return JOB_STATUS..
 * @private
 */
JOB_STATUS
CmdClassFirmwareUpdateMdStatusReport(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  uint8_t status,
  uint16_t waitTime ,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult));

/**
 * @brief Send command Firmware update  MD Get
 * @param[in] rxOpt receive options
 * @param[in] firmwareUpdateReportNumber current frame number.
 * @param[out] pCbFunc function pointer returning status on the job.
 * @return JOB_STATUS
 * @private
 */
JOB_STATUS
CmdClassFirmwareUpdateMdGet(
  RECEIVE_OPTIONS_TYPE_EX *rxOpt,
  uint16_t firmwareUpdateReportNumber,
  ZAF_TX_Callback_t pCbFunc);

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
extern void
handleCmdClassFirmwareUpdateMdReqGet(
    RECEIVE_OPTIONS_TYPE_EX *rxOpt,
    ZW_FIRMWARE_UPDATE_MD_REQUEST_GET_V5_FRAME * pFrame,
    uint8_t cmdLength,
    uint8_t* pStatus);

/**
 * @brief ZCB_CmdClassFwUpdateMdReqReport
 * Callback function receive status on Send data FIRMWARE_UPDATE_MD_REQUEST_REPORT_V3
 * @param txStatus : TRANSMIT_COMPLETE_OK, TRANSMIT_COMPLETE_NO_ACK, TRANSMIT_COMPLETE_FAIL...
 * @private
 */
extern void
ZCB_CmdClassFwUpdateMdReqReport(uint8_t txStatus);

/**
 * Returns the maximum fragment size.
 * @return Maximum fragment size.
 * @private
 */
extern uint16_t handleCommandClassFirmwareUpdateMaxFragmentSize(void);

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
extern bool CC_FirmwareUpdate_ActivationSet_handler(
    ZW_FIRMWARE_UPDATE_ACTIVATION_SET_V5_FRAME * pFrame,
    uint8_t * pStatus);

/**
 * Transmits an Activation Status Report.
 *
 * Must be used only in the case of first boot after installing a new firmware image.
 * @param rxOpt Receive options tied to the Activation Set command.
 * @param checksum Checksum of the installed firmware image (included in Activation Set)
 * @param status Status of the firmware update.
 * @return Returns JOB_STATUS_SUCCESS if the frame was sent, otherwise JOB_STATUS_BUSY.
 * @private
 */
JOB_STATUS CC_FirmwareUpdate_ActivationStatusReport_tx(
    RECEIVE_OPTIONS_TYPE_EX * rxOpt,
    uint16_t checksum,
    uint8_t status);

/**
 * Invoked when another node initiates a firmware update of this device.
 *
 * If the function returns true, the process will continue. If the function returns false, the node
 * will report to the initiator that the firmware update requires authentication.
 *
 * The function must take two arguments where the first one is the firmware ID and the second one
 * is the CRC value of the firmware.
 *
 * @note This function is weakly defined to return true, but can be defined by the application if
 *       desired.
 *
 * @param fwId ID of the firmware.
 * @param CRC CRC of the firmware.
 * @return Return true to continue the firmware update process and false to cancel it.
 */
bool CC_FirmwareUpdate_SetStartCallback(uint16_t fwId, uint16_t CRC);

/**
 * Invoked when the firmware update process finishes either successfully or with an error.
 *
 * If the device reboots right after the firmware update, the function is invoked before the reboot.
 *
 * The function must take an argument that is the status of the firmware update.
 *
 * @note This function is weakly defined to do nothing and can be defined by the application if
 *       desired.
 *
 * @param pOtaFinish Status of the firmware update.
 */
void CC_FirmwareUpdate_SetFinishCallback(OTA_STATUS pOtaFinish);

/**
 * @}
 * @}
 */ 

#endif /* _CC_FIRMWAREUPDATE_H_*/

