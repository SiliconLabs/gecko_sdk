/**
 * @file
 * Defines default events used by Silicon Labs applications.
 *
 * These events can be used by customer applications as well. In case a customer application
 * requires additional events, this file can be modified.
 *
 * @copyright 2022 Silicon Laboratories Inc.
 */
#ifndef ZAF_APPLICATIONEVENTS_H_
#define ZAF_APPLICATIONEVENTS_H_

/**
 * @addtogroup ZAF
 * @{
 * @addtogroup ApplicationEvent
 * @{
 */

/// Prioritized events that can wakeup protocol thread.
typedef enum EApplicationEvent
{
  EAPPLICATIONEVENT_TIMER = 0,
  EAPPLICATIONEVENT_ZWRX,
  EAPPLICATIONEVENT_ZWCOMMANDSTATUS,
  EAPPLICATIONEVENT_APP,
  EAPPLICATIONEVENT_CC
} EApplicationEvent;

/**
 * @} // ApplicationEvent
 * @} //ZAF
 */

#endif /* ZAF_APPLICATIONEVENTS_H_ */
