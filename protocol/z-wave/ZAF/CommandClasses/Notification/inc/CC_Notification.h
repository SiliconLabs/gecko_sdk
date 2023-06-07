/**
 * @file
 * Handler for Command Class Notification.
 *
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 *
 * Command Class Notification enables a device to send notifications like
 * "smoke detected" or "window opened".
 *
 * CC Notification is typically used in sensor applications because it supports
 * many different notification/sensor types.
 *
 * CC Notification requires at least one notification to be configured by
 * implementing the functions declared in cc_notification_config_api.h.
 * Simplicity Studio / SLC generates this configuration automatically based on
 * user configuration in *.cc_config files.
 *
 * This command class offers one single API function to be used by the
 * application:
 * - CC_Notification_TriggerAndTransmit()
 *
 * The specification of CC Notification can be found in
 * https://github.com/Z-Wave-Alliance/AWG/blob/main/source/application_command_classes/command_class_definitions/notification_command_class_version_3-8.rst.
 *
 * @}
 * @}
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _CC_NOTIFICATION_H_
#define _CC_NOTIFICATION_H_

#include "ZAF_types.h"
#include "cc_notification_types.h"
#include "cc_notification_events.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 */

/**
 *  the maximum length of the notification bitmask array
 */
#define NOTIFICATION_BITMASK_ARRAY_LENGTH   32

/**
 * General purpose notification event
 */
typedef enum
{
  NOTIFICATION_EVENT_NO_EVENT,
  NOTIFICATION_EVENT_UNKNOWN_EVENT = 0xFE
}NOTIFICATION_EVENT;

/**
 * Struct used to pass operational data to TSE module
 */
typedef struct s_CC_notification_data_t_
{
  RECEIVE_OPTIONS_TYPE_EX rxOptions; /**< rxOptions */
  uint8_t                 index; /// index of notification in notifications array
  uint8_t                *pEventParameters; /// Pointer to event parameters
  uint8_t                 eventParamLength; /// Length of event paramters
} s_CC_notification_data_t;

/**
 * @brief Triggers notification event and sends it to dedicated Agi profile
 * @param[in] index notification index.
 * @param[in] notificationEvent Event triggered.
 * @param[in] pEvPar point to event parameters.
 * @param[in] evParLen length of event parameters.
 * @param[out] pCallback callback function returning state on job
 * @param[in] tse True of false, depending if TSE should be triggered, or not
 * @return JOB_STATUS
 */
JOB_STATUS CC_Notification_TriggerAndTransmit(
    uint8_t index,
    uint8_t notificationEvent,
    uint8_t * pEvPar,
    uint8_t evParLen,
    void (*pCallback)(TRANSMISSION_RESULT * pTransmissionResult),
    bool tse);

/**
 * @}
 * @}
 */ 

#endif /*_CC_NOTIFICATION_H_*/
