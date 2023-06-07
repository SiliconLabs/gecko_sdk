/***************************************************************************//**
 * @file
 * @brief Interface for the application event mechanism
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SILABS_AF_EVENT_H
#define SILABS_AF_EVENT_H

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif //SL_COMPONENT_CATALOG_PRESENT

#if defined(EMBER_SCRIPTED_TEST) || defined (SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT) || defined(SL_CATALOG_ZIGBEE_GREEN_POWER_ADAPTER_PRESENT)
#include "../include/af.h"
#endif // EMBER_SCRIPTED_TEST || SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT || SL_CATALOG_ZIGBEE_GREEN_POWER_ADAPTER_PRESENT

#define MAX_TIMER_UNITS_HOST 0x7fff
#define MAX_TIMER_MILLISECONDS_HOST (MAX_TIMER_UNITS_HOST * MILLISECOND_TICKS_PER_MINUTE)

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zap-event.h"
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

extern uint16_t sli_zigbee_app_event_context_length;
extern sl_zigbee_event_context_t sli_zigbee_app_event_context[];
#ifndef EMBER_AF_NCP
extern EmberAfEventSleepControl emberAfGetCurrentSleepControlCallback(void);
#endif //#ifndef EMBER_AF_NCP

#if !defined(DOXYGEN_SHOULD_SKIP_THIS)
extern EmberEventQueue sli_zigbee_af_app_event_queue;
#endif // !defined(DOXYGEN_SHOULD_SKIP_THIS)

/**
 * @brief Retrieve the number of milliseconds until
 * the next event scheduled in the application framework's event
 * mechanism.
 * @param uint32_t maxMs, the maximum number of milliseconds until the next
 *        event.
 * @return uint32_t The number of milliseconds until the next event or
 * maxMs if no event is scheduled before then.
 */
#define emberAfMsToNextEvent(maxMs) emberMsToNextQueueEvent(&sli_zigbee_af_app_event_queue)

/**
 * @brief This is the same as the function emberAfMsToNextEvent() with the
 *  following addition.  If returnIndex is non-NULL it returns the index
 *  of the event that is ready to fire next.
 *
 * @deprecated Please use \ref emberAfMsToNextEvent instead. Since GSDK version
 * 4.0.0.0 or EmberZNet 7.0.0.0, returnIndex is implicitly 0 since events are
 * ordered by time-until-execution. This function will be removed in a future
 * release.
 */
#define emberAfMsToNextEventExtended(maxMs, returnIndex) emberAfMsToNextEvent(maxMs)

/**
 * @brief Retrieve the number of quarter seconds until
 * the next event scheduled in the application framework's event
 * mechanism. This function will round down and will return 0 if the
 * next event must fire within a quarter second.
 * @param maxQS, the maximum number of quarter seconds until the next
 *        event.
 * @return The number of quarter seconds until the next event or
 * maxQS if no event is scheduled before then.
 */
#define emberAfQSToNextEvent(maxQS)                                  \
  (emberAfMsToNextEvent(maxQS * MILLISECOND_TICKS_PER_QUARTERSECOND) \
   / MILLISECOND_TICKS_PER_QUARTERSECOND)

// A function used to retrieve the proper NCP timer duration and unit based on a given
// passed number of milliseconds.
void sli_zigbee_af_get_timer_duration_and_unit_from_ms(uint32_t durationMs,
                                                       uint16_t *duration,
                                                       EmberEventUnits *units);

// A function (inverse of the above) to retrieve the number of milliseconds
// represented by a given timer duration and unit.
uint32_t sli_zigbee_af_get_ms_from_timer_duration_and_unit(uint16_t duration,
                                                           EmberEventUnits units);

//A function to initialize the Event mechanism used to drive the application framework.
void sli_zigbee_af_initEvents(void);

const char * emberAfGetEventString(uint8_t index);

#endif // SILABS_AF_EVENT_H
