/**
 * @file
 * Command Class Notification helper module.
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/
#include <ZW_typedefs.h>
#include <CC_Notification.h>
#include <cc_notification_config.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup Notification
 * @{
 */

typedef uint8_t notification_event_state;

typedef struct _cc_notification_t {
  RECEIVE_OPTIONS_TYPE_EX         rxOpt;      // Must be first for true status
  const uint8_t                   endpoint;   // Must be second for list generator
  const notification_type_t       type;
  const agi_profile_t             agi_profile;
  const notification_event_state  events[CC_NOTIFICATION_MAX_EVENTS_PER_NOTIFICATION];
  notification_event_state        current_event; /// Current event state
  NOTIFICATION_STATUS             status;        /// Current status - On/Off
} cc_notification_t;


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

#endif /* _NOTIFICATION_H_ */
