/***************************************************************************//**
 * @file
 * @brief Zigbee Specific Radio Coexistence callbacks.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
#include "sl_rail_mux_rename.h"
#endif

#include "coexistence-802154.h"
#include "stack/include/ember-types.h"

extern void sli_zigbee_call_counter_handler(EmberCounterType type, uint8_t data);

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
static void sl_zigbee_coex_counter_on_event(sl_rail_util_coex_event_t event)
#else
void sl_rail_util_coex_counter_on_event(sl_rail_util_coex_event_t event)
#endif
{
  EmberCounterType type = EMBER_COUNTER_PTA_LO_PRI_REQUESTED + (EmberCounterType)event;
  sli_zigbee_call_counter_handler(type, 1);
}

#ifdef SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
void sl_rail_util_coex_enable_counter(RAIL_Handle_t railHandle)
{
  sl_rail_mux_set_coex_counter_handler(railHandle, &sl_zigbee_coex_counter_on_event);
}
#endif //SL_CATALOG_RAIL_MULTIPLEXER_PRESENT
