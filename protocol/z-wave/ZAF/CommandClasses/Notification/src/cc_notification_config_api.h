/**
 * @file
 * Command Class Notification Configuration API
 * @copyright 2022 Silicon Laboratories Inc.
 */

#ifndef CC_NOTIFICATION_CONFIG_API_H
#define CC_NOTIFICATION_CONFIG_API_H

#include "ZAF_types.h"
#include "cc_notification_types.h"
#include "cc_notification_config.h"

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 * @addtogroup cc_notification_config Configuration of CC Notification
 * @{
 */

typedef uint8_t notification_event_state;

/**
 * Notification status
 */
typedef enum
{
  NOTIFICATION_STATUS_UNSOLICIT_DEACTIVATED = 0x00,
  NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED = 0xFF
} NOTIFICATION_STATUS;

typedef struct _cc_notification_t {
  RECEIVE_OPTIONS_TYPE_EX         rxOpt;      // Must be first for true status
  const uint8_t                   endpoint;   // Must be second for list generator
  const notification_type_t       type;
  const agi_profile_t             agi_profile;
  const notification_event_state* events;
  const uint8_t                   event_count;
  notification_event_state        current_event; /// Current event state
  NOTIFICATION_STATUS             status;        /// Current status - On/Off
} cc_notification_t;

/**
 * Returns the address of the first element in the notification array.
 * @return First element in the notification array.
 */
cc_notification_t * cc_notification_get_config(void);

/**
 * Returns the number of elements in the notification array.
 * @return Number of elements in the notification array.
 */
uint8_t cc_notification_get_config_length(void);

/**
 * Returns the total number of supported events for all notifications.
 * @return Total number of supported events.
 */
uint8_t cc_notification_get_supported_events_length(void);

/**
 * Returns the address of the notification located at the given index in the notification array.
 * @param[in] index Index in the notification array.
 * @return Address of notification.
 */
cc_notification_t* cc_notification_get(uint8_t index);

/**
 * Returns the index of a notification based on given type and endpoint.
 * @param[in] type Notification type.
 * @param[in] endpoint Endpoint.
 * @return Index of notification.
 */
int8_t cc_notification_get_index_by_type_and_endpoint(notification_type_t type, uint8_t endpoint);

/**
 * Returns the notification type from the given index.
 * @param[in] index Index in the notification array.
 * @return Notification type.
 */
notification_type_t cc_notification_get_type(uint8_t index);

/**
 * Returns the current event of a notification given by the index in the notification array.
 * @param[in] index Index in the notification array.
 * @return Current event.
 */
notification_event_state cc_notification_get_current_event(uint8_t index);

/**
 * Returns the AGI profile of a notification given by the index in the notification array.
 * @param[in] index Index in the notification array.
 * @return AGI profile.
 */
agi_profile_t cc_notification_get_agi_profile(uint8_t index);

/**
 * Returns endpoint of a notification given by the index in the notification array.
 * @param[in] index Index in the notification array.
 * @return Endpoint.
 */
uint8_t cc_notification_get_endpoint(uint8_t index);

/**
 * Returns the status (on/off) of a notification given by the index in the notification array.
 * @param[in] index Index in the notification array.
 * @return Returns \ref NOTIFICATION_STATUS_UNSOLICIT_DEACTIVATED if the notification is disabled.
 * @return Returns \ref NOTIFICATION_STATUS_UNSOLICIT_ACTIVATED if the notification is enabled.
 */
NOTIFICATION_STATUS cc_notification_get_status(uint8_t index);

/**
 * Returns whether a notification exists in the notification array based on a given notification
 * type.
 *
 * This function is used to check whether incoming CC Notification commands must be discarded or not.
 * @param[in] type Notification type.
 * @return true if available,
 */
bool cc_notification_is_type_supported(notification_type_t type);

/**
 * Returns the index of a given event, if supported, for a given notification index.
 *
 * @param[in] event Event to be found.
 * @param[in] index Notification index in notifications array
 * @return Returns event index if found
 * @return Returns -1 if the event is not supported for the given notification index.
 */
int8_t cc_notification_find_event(uint8_t event, uint8_t index);

/**
 * Returns the number of configured events for a given notification index.
 *
 * @param index Notification index.
 * @return Number of configured events.
 */
uint8_t cc_notification_config_get_number_of_events(uint8_t index);

/**
 * @}
 * @}
 * @}
 */ 

#endif /* CC_NOTIFICATION_CONFIG_API_H */
