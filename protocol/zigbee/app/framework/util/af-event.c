/***************************************************************************//**
 * @file
 * @brief Application event code that is common to both the SOC and EZSP platforms.
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

#include PLATFORM_HEADER     // Micro and compiler specific typedefs and macros

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif //SL_COMPONENT_CATALOG_PRESENT

#if defined(EMBER_SCRIPTED_TEST) || defined (SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT) || defined(SL_CATALOG_ZIGBEE_GREEN_POWER_ADAPTER_PRESENT)
#include "../include/af.h"
#endif // EMBER_SCRIPTED_TEST || SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT || SL_CATALOG_ZIGBEE_GREEN_POWER_ADAPTER_PRESENT

#include "af-event.h"
#include "stack/include/error.h"
#include "../security/crypto-state.h"
#include "app/framework/util/service-discovery.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_ZIGBEE_TEST_HARNESS_PRESENT
#include "test-harness.h"
#endif

#include "app/framework/util/attribute-storage.h"

//------------------------------------------------------------------------------
// UC Globals

#include "zap-event.h"

#ifdef EMBER_SCRIPTED_TEST
#include "app/framework/util/af-event-test.h"
#endif

#ifdef EMBER_AF_GENERATED_UC_EVENTS_DEF
EMBER_AF_GENERATED_UC_EVENTS_DEF
#endif // EMBER_AF_GENERATED_UC_EVENTS_DEF

#if defined(EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT) && EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT > 0
sl_zigbee_event_context_t sli_zigbee_app_event_context[] = {
  EMBER_AF_GENERATED_UC_EVENT_CONTEXT
};
uint16_t sli_zigbee_app_event_context_length = sizeof(sli_zigbee_app_event_context) / sizeof(sl_zigbee_event_context_t);
#endif //EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT

//------------------------------------------------------------------------------
// UC functions

void sli_zigbee_af_zcl_framework_core_init_events_callback(uint8_t init_level)
{
  (void)init_level;

#ifdef EMBER_AF_GENERATED_UC_EVENTS_INIT
  EMBER_AF_GENERATED_UC_EVENTS_INIT
#endif
}

static sl_zigbee_event_context_t *find_event_context(uint8_t endpoint,
                                                     EmberAfClusterId clusterId,
                                                     bool isClient)
{
#if defined(EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT) && EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT > 0
  uint8_t i;
  for (i = 0; i < sli_zigbee_app_event_context_length; i++) {
    sl_zigbee_event_context_t *context = &(sli_zigbee_app_event_context[i]);
    if (context->endpoint == endpoint
        && context->clusterId == clusterId
        && context->isClient == isClient) {
      return context;
    }
  }
#endif //EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT
  return NULL;
}

EmberStatus sl_zigbee_zcl_schedule_tick_extended(uint8_t endpoint,
                                                 EmberAfClusterId clusterId,
                                                 bool isClient,
                                                 uint32_t delayMs,
                                                 EmberAfEventPollControl pollControl,
                                                 EmberAfEventSleepControl sleepControl)
{
  sl_zigbee_event_context_t *context = find_event_context(endpoint,
                                                          clusterId,
                                                          isClient);

  // Disabled endpoints cannot schedule events.  This will catch the problem in
  // simulation.
  EMBER_TEST_ASSERT(emberAfEndpointIsEnabled(endpoint));

  if (context != NULL
      && emberAfEndpointIsEnabled(endpoint)) {
    sl_zigbee_event_set_delay_ms(context->event, delayMs);
    context->pollControl = pollControl;
    context->sleepControl = sleepControl;
    return EMBER_SUCCESS;
  }
  return EMBER_BAD_ARGUMENT;
}

EmberStatus sl_zigbee_zcl_schedule_cluster_tick(uint8_t endpoint,
                                                EmberAfClusterId clusterId,
                                                bool isClient,
                                                uint32_t delayMs,
                                                EmberAfEventSleepControl sleepControl)
{
  return sl_zigbee_zcl_schedule_tick_extended(endpoint,
                                              clusterId,
                                              isClient,
                                              delayMs,
                                              (sleepControl == EMBER_AF_OK_TO_HIBERNATE
                                               ? EMBER_AF_LONG_POLL
                                               : EMBER_AF_SHORT_POLL),
                                              (sleepControl == EMBER_AF_STAY_AWAKE
                                               ? EMBER_AF_STAY_AWAKE
                                               : EMBER_AF_OK_TO_SLEEP));
}

EmberStatus sl_zigbee_zcl_schedule_client_tick_extended(uint8_t endpoint,
                                                        EmberAfClusterId clusterId,
                                                        uint32_t delayMs,
                                                        EmberAfEventPollControl pollControl,
                                                        EmberAfEventSleepControl sleepControl)
{
  return sl_zigbee_zcl_schedule_tick_extended(endpoint,
                                              clusterId,
                                              EMBER_AF_CLIENT_CLUSTER_TICK,
                                              delayMs,
                                              pollControl,
                                              sleepControl);
}

EmberStatus sl_zigbee_zcl_schedule_client_tick(uint8_t endpoint,
                                               EmberAfClusterId clusterId,
                                               uint32_t delayMs)
{
  return sl_zigbee_zcl_schedule_client_tick_extended(endpoint,
                                                     clusterId,
                                                     delayMs,
                                                     EMBER_AF_LONG_POLL,
                                                     EMBER_AF_OK_TO_SLEEP);
}

EmberStatus sl_zigbee_zcl_schedule_server_tick_extended(uint8_t endpoint,
                                                        EmberAfClusterId clusterId,
                                                        uint32_t delayMs,
                                                        EmberAfEventPollControl pollControl,
                                                        EmberAfEventSleepControl sleepControl)
{
  return sl_zigbee_zcl_schedule_tick_extended(endpoint,
                                              clusterId,
                                              EMBER_AF_SERVER_CLUSTER_TICK,
                                              delayMs,
                                              pollControl,
                                              sleepControl);
}

EmberStatus sl_zigbee_zcl_schedule_server_tick(uint8_t endpoint,
                                               EmberAfClusterId clusterId,
                                               uint32_t delayMs)
{
  return sl_zigbee_zcl_schedule_server_tick_extended(endpoint,
                                                     clusterId,
                                                     delayMs,
                                                     EMBER_AF_LONG_POLL,
                                                     EMBER_AF_OK_TO_SLEEP);
}

EmberStatus sl_zigbee_zcl_deactivate_cluster_tick(uint8_t endpoint,
                                                  EmberAfClusterId clusterId,
                                                  bool isClient)
{
  sl_zigbee_event_context_t *context = find_event_context(endpoint,
                                                          clusterId,
                                                          isClient);
  if (context != NULL) {
    sl_zigbee_event_set_inactive(context->event);
    return EMBER_SUCCESS;
  }
  return EMBER_BAD_ARGUMENT;
}

EmberStatus sl_zigbee_zcl_deactivate_client_tick(uint8_t endpoint,
                                                 EmberAfClusterId clusterId)
{
  return sl_zigbee_zcl_deactivate_cluster_tick(endpoint,
                                               clusterId,
                                               EMBER_AF_CLIENT_CLUSTER_TICK);
}

EmberStatus sl_zigbee_zcl_deactivate_server_tick(uint8_t endpoint,
                                                 EmberAfClusterId clusterId)
{
  return sl_zigbee_zcl_deactivate_cluster_tick(endpoint,
                                               clusterId,
                                               EMBER_AF_SERVER_CLUSTER_TICK);
}

#ifndef EMBER_AF_NCP
// There is only idling on NCP hence sleep control code is not needed.
static EmberAfEventSleepControl defaultSleepControl = EMBER_AF_OK_TO_SLEEP;
// Checks all application events to see if any active events require the micro to stay awake
EmberAfEventSleepControl emberAfGetCurrentSleepControlCallback(void)
{
  EmberAfEventSleepControl sleepControl = defaultSleepControl;
#if defined(EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT) && EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT > 0
  uint8_t i;
  for (i = 0; i < sli_zigbee_app_event_context_length; i++) {
    sl_zigbee_event_context_t *context = &sli_zigbee_app_event_context[i];
    if ( (0 == sl_zigbee_event_get_remaining_ms(&(*context->event))) //equivalent to emberEventControlGetActive
         && sleepControl < context->sleepControl) {
      sleepControl = context->sleepControl;
    }
  }
#endif // EMBER_AF_GENERATED_UC_EVENT_CONTEXT_COUNT
  return sleepControl;
}
EmberAfEventSleepControl emberAfGetDefaultSleepControlCallback(void)
{
  return defaultSleepControl;
}

void emberAfSetDefaultSleepControlCallback(EmberAfEventSleepControl sleepControl)
{
  defaultSleepControl = sleepControl;
}
#endif // EMBER_AF_NCP

//------------------------------------------------------------------------------
// Common functions

#define MS_TO_QS(ms)    ((ms) >> 8)
#define MS_TO_MIN(ms)   ((ms) >> 16)
#define QS_TO_MS(qs)    ((qs) << 8)
#define MIN_TO_MS(min) ((min) << 16)

// Used to calculate the duration and unit used by the host to set the sleep timer
void sli_zigbee_af_get_timer_duration_and_unit_from_ms(uint32_t durationMs,
                                                       uint16_t *duration,
                                                       EmberEventUnits *units)
{
  if (durationMs <= MAX_TIMER_UNITS_HOST) {
    *duration = (uint16_t)durationMs;
    *units = EMBER_EVENT_MS_TIME;
  } else if (MS_TO_QS(durationMs) <= MAX_TIMER_UNITS_HOST) {
    *duration = (uint16_t)(MS_TO_QS(durationMs));
    *units = EMBER_EVENT_QS_TIME;
  } else {
    *duration = (MS_TO_MIN(durationMs) <= MAX_TIMER_UNITS_HOST
                 ? (uint16_t)(MS_TO_MIN(durationMs))
                 : MAX_TIMER_UNITS_HOST);
    *units = EMBER_EVENT_MINUTE_TIME;
  }
}

uint32_t sli_zigbee_af_get_ms_from_timer_duration_and_unit(uint16_t duration,
                                                           EmberEventUnits units)
{
  uint32_t ms;
  if (units == EMBER_EVENT_MS_TIME) {
    ms = duration;
  } else if (units == EMBER_EVENT_QS_TIME) {
    ms = QS_TO_MS(duration);
  } else if (units == EMBER_EVENT_MINUTE_TIME) {
    ms = MIN_TO_MS(duration);
  } else if (units == EMBER_EVENT_ZERO_DELAY) {
    ms = 0;
  } else {
    ms = MAX_INT32U_VALUE;
  }
  return ms;
}
