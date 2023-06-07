/***************************************************************************//**
 * @brief Zigbee Force sleep component source code
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

#include "af.h"
#include "force-sleep-wakeup.h"
#include "rail.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
#include "sl_rail_mux_rename.h"
#endif
#include "sl_zigbee_debug_print.h"

extern EmberEventQueue sli_zigbee_stack_event_queue;
//externed from lower-mac-rail-802.15.4.c
extern void sli_mac_lower_mac_force_sleep(bool sleep);

//externed from mac-dispatch.h
extern void sli_802154mac_cancel_polls(void);
extern void sli_802154mac_purge_transmit_queue(void);
extern void sli_802154mac_purge_incoming_queue(void);

bool force_sleep = false;

void sl_zigbee_app_framework_force_stop(void)
{
  sl_zigbee_core_debug_print("Sleep\n");

  sli_802154mac_cancel_polls();
  sli_802154mac_purge_transmit_queue();
  sli_802154mac_purge_incoming_queue();

  emberCancelAllEvents(&sli_zigbee_stack_event_queue);
  emberCancelAllEvents(&sli_zigbee_af_app_event_queue);

  sli_mac_lower_mac_force_sleep(true);
  force_sleep = true;
}

void sl_zigbee_app_framework_force_wakeup(void)
{
  force_sleep = false;
  sl_power_manager_sleep();
  sli_mac_lower_mac_force_sleep(false);
  sl_zigbee_core_debug_print("Wakeup\n");
}
// When force_sleep is set, this function will bypass power manager logic and immediately
// setup zigbee so it is ready to sleep
bool sli_zigbee_app_framework_get_force_sleep_flag(void)
{
  return force_sleep;
}

#ifdef SL_CATALOG_CLI_PRESENT
void sli_zigbee_app_framework_force_sleep_cli_handler(sl_cli_command_arg_t *arguments)
{
  // Do other things like turn off LEDs etc in the callback implemented in the app
  sli_zigbee_app_framework_force_sleep_callback();
  sl_zigbee_app_framework_force_stop();
}
#endif //SL_CATALOG_CLI_PRESENT

WEAK(void sli_zigbee_app_framework_force_sleep_callback(void)) {
}
