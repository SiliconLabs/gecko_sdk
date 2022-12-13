/**
 * @file
 * Handler for Command Class Battery.
 * @copyright 2019 Silicon Laboratories Inc.
 */

#ifndef _CC_BATTERY_H_
#define _CC_BATTERY_H_

#include <stdbool.h>
#include <ZW_classcmd.h>
#include <CC_Common.h>

/**
 * @addtogroup CC Command Classes
 * @{
 * @addtogroup Battery
 * @{
 */

/**
 * Battery value can range from 0 to 100 (0x00 to 0x64) representing the
 * battery level in percentage from 0 to 100%.
 * The value 255 (0xFF) is used to indicate low-battery warning.
 * All other values are reserved and SHALL be ignored by the receiving device.
 */
typedef enum
{
  CMD_CLASS_BATTERY_LEVEL_LOW      = 0x00, /**< battery level low */
  CMD_CLASS_BATTERY_LEVEL_HIGH     = 0x10, /**< battery level high */
  CMD_CLASS_BATTERY_LEVEL_FULL     = 0x64, /**< battery level full */
  CMD_CLASS_BATTERY_LEVEL_WARNING  = 0xFF  /**< battery low-level warning */
}
cc_battery_level_t;

/**
 * Used to store the last reported battery level
 */
typedef struct SBatteryData
{
  uint8_t lastReportedBatteryLevel;
} SBatteryData;

/**
 * Send unsolicited battery report
 * @param[in] pProfile pointer to AGI profile
 * @param[in] sourceEndpoint source endpoint
 * @param[out] pCbFunc callback funtion returning status destination node receive job.
 * @return status on protocol exuted the job.
 */
bool CC_Battery_LevelReport_tx(
  const AGI_PROFILE* pProfile,
  uint8_t sourceEndpoint,
  VOID_CALLBACKFUNC(pCbFunc)(TRANSMISSION_RESULT * pTransmissionResult));

/**
 * Get current battery level from application.
 *
 * This function must be implemented in the application code.
 * Called by battery command class handler.
 *
 * @param[in] endpoint binary switch endpoint
 * @return current battery level
 */
uint8_t CC_Battery_BatteryGet_handler(uint8_t endpoint);

/**
 * Function for periodically checking if the battery level differs from what was last reported.
 *
 * @return true if the battery level has changed since last reported 
 * @return false if the battery level hasn't changed
 */
bool cc_battery_check_level_changed(void);

/**
 * @}
 * @}
 */

#endif
