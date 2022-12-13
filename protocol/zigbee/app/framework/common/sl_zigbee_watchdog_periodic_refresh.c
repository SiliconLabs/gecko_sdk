/***************************************************************************//**
 * @file
 * @brief Sample watchdog refresh event implementation and related configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include PLATFORM_HEADER
#include "hal.h"
#include "ember.h"
#include "zigbee_app_framework_event.h"
#include "zigbee_app_framework_common.h"
#include "zigbee_watchdog_periodic_refresh_config.h"

#if (SL_ZIGBEE_WATCHDOG_PERIODIC_REFRESH_ENABLE == 1)

static sl_zigbee_event_t watchdog_refresh_event;
static void watchdog_refresh_event_handler(sl_zigbee_event_t *event);

// Initialization of watchdog refresh event
void sli_zigbee_watchdog_refresh_handler_init(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT:
    {
      sl_zigbee_event_init(&watchdog_refresh_event, watchdog_refresh_event_handler);
      sl_zigbee_event_set_active(&watchdog_refresh_event);
      break;
    }
    default:
      break;
  }
}

// In RTOS-based applications, the Zigbee task refreshes the watchdog.
// However, when the node is not on a network the Zigbee task does not run.
// Therefore, there needs to be a way to ensure that the watchdog does not fire
// and reset the node unnecessarily. Below we provide an example of an application
// event that periodically resets the watchdog.
// Note, such a periodic event gets the node out of EM1/EM2 low power modes,
// which may result in unnecessary energy consumption.
// The application should ultimately own the refreshing of the watchdog and tailor
// it based on the specific use case.
// In the bare-metal case, this is done in the zigbee stack and app framework ticks
static void watchdog_refresh_event_handler(sl_zigbee_event_t *event)
{
  halResetWatchdog();
  sl_zigbee_event_set_delay_ms(&watchdog_refresh_event, SL_ZIGBEE_WATCHDOG_REFRESH_DURATION_MS);
}
#endif //(SL_ZIGBEE_WATCHDOG_PERIODIC_REFRESH_ENABLE == 1)
