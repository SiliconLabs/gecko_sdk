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

/**
 * @addtogroup CC
 * @{
 * @addtogroup cc_firmware_update
 * @{
 */

/**
 * enum type OTA_STATUS use to
 */
typedef enum
{
  OTA_STATUS_DONE = 0,
  OTA_STATUS_ABORT = 1,
  OTA_STATUS_TIMEOUT = 2
} OTA_STATUS;

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

