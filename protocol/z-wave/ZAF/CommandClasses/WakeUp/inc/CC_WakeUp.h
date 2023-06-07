/**
 * @file
 * Handler for Command Class Wake Up.
 *
 * CC WakeUp can be used in two scenarios:
 * 1) as a standalone wake up node waking up from reset, or
 * 2) combined with FLiRS waking up from sleep.
 *
 * In both scenarios, an application might want to do something, like sending a Battery Report
 * before transmitting a Wake Up Notification.
 *
 * Having an init function that takes a reset reason and a callback function, the module could
 * address both scenarios like this:
 *
 * 1) The init function is called with a reset reason set to ERESETREASON_DEEP_SLEEP_WUT. This means
 * that the chip woke up from reset caused by the wake up timer. In this case, the callback must be
 * invoked so that the application can do something.
 *
 * 2) The callback passed using the init function is registered with the timer. It is then invoked
 * when the timer triggers.
 *
 * In both scenarios, the application must call CC_WakeUp_notification_tx() when done with
 * something.
 *
 * General initialization:
 * 1) Call init and set values
 * 2) On resetting app: Call reset function
 *
 * @copyright 2018 Silicon Laboratories Inc.
 */

#ifndef _COMMANDCLASSWAKEUP_H_
#define _COMMANDCLASSWAKEUP_H_

/****************************************************************************/
/*                              INCLUDE FILES                               */
/****************************************************************************/

#include <ZW_TransportEndpoint.h>
#include <ZW_application_transport_interface.h>
#include <ZAF_nvm_app.h>
#include <ZAF_nvm.h>

/**
 * @addtogroup CC
 * @{
 * @addtogroup WakeUp
 * @{
 */

/****************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                       */
/****************************************************************************/

// Nothing here.

/****************************************************************************/
/*                              EXPORTED DATA                               */
/****************************************************************************/

// Used by application file system
typedef struct SWakeupCcData
{
  uint8_t MasterNodeId;
  uint32_t SleepPeriod;
} SWakeupCcData;

#define ZAF_FILE_SIZE_WAKEUPCCDATA        (sizeof(SWakeupCcData))


/****************************************************************************/
/*                           EXPORTED FUNCTIONS                             */
/****************************************************************************/

/**
 * Transmits a Wake Up Notification command and handles callback.
 * @param[in] pCallback Pointer to function which will be called on Wake Up Notification ACK/NACK.
 */
void CC_WakeUp_notification_tx(void (*pCallback)(uint8_t txStatus, TX_STATUS_TYPE* pExtendedTxStatus));

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the default sleep time in second between Wake Up Notifications.
 * 
 * @return Default sleep time in second between Wake Up Notifications
 */
uint32_t cc_wake_up_config_get_default_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the minimum sleep time in second between Wake Up Notifications.
 * 
 * @return Minimum sleep time in second
 */
uint32_t cc_wake_up_config_get_minimum_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the maximum sleep time in second between Wake Up Notifications.
 * 
 * @return Maximum sleep time in second
 */
uint32_t cc_wake_up_config_get_maximum_sleep_time_sec(void);

/**
 * @brief Used by the WakeUp Command Class configuration
 * Returns with the sleep step time in second.
 * 
 * @return sleep step time in second
 */
uint32_t cc_wake_up_config_get_sleep_step_time_sec(void);

/**
 * @}
 * @}
 */ 

#endif /* _COMMANDCLASSWAKEUP_H_ */
