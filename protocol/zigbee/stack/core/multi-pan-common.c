/***************************************************************************//**
 * @file
 * @brief Common code between multi PAN and non multi PAN support, which
 *  includes single PAN and multi-network.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "stack/include/ember.h"
#include "event_queue/event-queue.h"
#include "multi-pan.h"

extern EmberEventQueue sli_zigbee_stack_event_queue;
#ifdef EMBER_TEST
  #define testAssert assert
#else // EMBER_TEST
  #define testAssert(x) do {} while (0)
#endif // EMBER_TEST

extern EmberEvent sli_zigbee_beacon_events[];
extern void sli_zigbee_beacon_event_handler(EmberEvent *event);

extern EmberEvent sli_zigbee_permit_joiningEvents[];
extern void sli_zigbee_permit_joining_event_handler(EmberEvent *event);

extern EmberEvent sli_zigbee_network_management_events[];
extern void sli_zigbee_network_management_event_handler(EmberEvent *event);

#if !defined(SL_ZIGBEE_LEAF_STACK) || defined(CSL_SUPPORT)
extern EmberEvent sli_zigbee_neighbor_exchange_events[];
extern void sli_zigbee_neighbor_exchange_event_handler(EmberEvent *event);
#endif

extern EmberEvent sli_zigbee_request_key_events[];
extern void sli_zigbee_request_key_event_handler(EmberEvent *event);

#if !defined(SL_ZIGBEE_LEAF_STACK) || defined(CSL_SUPPORT)

extern EmberEvent sli_zigbee_send_parent_announce_events[];
extern void sli_zigbee_send_parent_announce_event_handler(EmberEvent *event);

#endif

extern EmberEvent sli_zigbee_transient_link_key_events[];
extern void sli_zigbee_transient_link_key_event_handler(EmberEvent *event);

extern EmberEvent sli_zigbee_gp_tx_events[];
extern void sli_zigbee_gp_tx_event_handler(EmberEvent *event);

extern EmberEvent sli_zigbee_source_route_update_events[];
extern void sli_zigbee_source_route_update_event_handler(EmberEvent *event);

#if !(defined(SL_ZIGBEE_ROUTER_STACK))
extern EmberEvent sli_zigbee_allow_tc_rejoins_using_well_known_key_events[];
extern void sli_zigbee_allow_tc_rejoins_using_well_known_key_event_handler(EmberEvent *event);
#endif

extern uint8_t sli_zigbee_supported_networks;

static void initializeForkedEvents(void)
{
  for (uint8_t j = 0; j < sli_zigbee_num_multi_pan_forks; j++) {
    sli_zigbee_beacon_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_beacon_events[j].actions.handler = sli_zigbee_beacon_event_handler;
    sli_zigbee_beacon_events[j].actions.marker = NULL;
    sli_zigbee_beacon_events[j].actions.name = EVENT_NAME("Beacon");
    sli_zigbee_beacon_events[j].next = NULL;

    sli_zigbee_permit_joiningEvents[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_permit_joiningEvents[j].actions.handler = sli_zigbee_permit_joining_event_handler;
    sli_zigbee_permit_joiningEvents[j].actions.marker = NULL;
    sli_zigbee_permit_joiningEvents[j].actions.name =  EVENT_NAME("Permit Joining");
    sli_zigbee_permit_joiningEvents[j].next = NULL;

    sli_zigbee_network_management_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_network_management_events[j].actions.handler = sli_zigbee_network_management_event_handler;
    sli_zigbee_network_management_events[j].actions.marker = NULL;
    sli_zigbee_network_management_events[j].actions.name =  EVENT_NAME("NWK mgm");
    sli_zigbee_network_management_events[j].next = NULL;

#if !defined(SL_ZIGBEE_LEAF_STACK) || defined(CSL_SUPPORT)
    sli_zigbee_neighbor_exchange_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_neighbor_exchange_events[j].actions.handler = sli_zigbee_neighbor_exchange_event_handler;
    sli_zigbee_neighbor_exchange_events[j].actions.marker = NULL;
    sli_zigbee_neighbor_exchange_events[j].actions.name =  EVENT_NAME("Neighbor exg");
    sli_zigbee_neighbor_exchange_events[j].next = NULL;
#endif

#if !defined(SL_ZIGBEE_LEAF_STACK) || defined(CSL_SUPPORT)
    sli_zigbee_send_parent_announce_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_send_parent_announce_events[j].actions.handler = sli_zigbee_send_parent_announce_event_handler;
    sli_zigbee_send_parent_announce_events[j].actions.marker = NULL;
    sli_zigbee_send_parent_announce_events[j].actions.name =  EVENT_NAME("Parent announce");
    sli_zigbee_send_parent_announce_events[j].next = NULL;
#endif

    sli_zigbee_transient_link_key_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_transient_link_key_events[j].actions.handler = sli_zigbee_transient_link_key_event_handler;
    sli_zigbee_transient_link_key_events[j].actions.marker = NULL;
    sli_zigbee_transient_link_key_events[j].actions.name =  EVENT_NAME("Transient link key");
    sli_zigbee_transient_link_key_events[j].next = NULL;

    sli_zigbee_gp_tx_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_gp_tx_events[j].actions.handler = sli_zigbee_gp_tx_event_handler;
    sli_zigbee_gp_tx_events[j].actions.marker = NULL;
    sli_zigbee_gp_tx_events[j].actions.name =  EVENT_NAME("GP TX");
    sli_zigbee_gp_tx_events[j].next = NULL;

    sli_zigbee_source_route_update_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_source_route_update_events[j].actions.handler = sli_zigbee_source_route_update_event_handler;
    sli_zigbee_source_route_update_events[j].actions.marker = NULL;
    sli_zigbee_source_route_update_events[j].actions.name =  EVENT_NAME("Source route update");
    sli_zigbee_source_route_update_events[j].next = NULL;

#if !(defined(SL_ZIGBEE_ROUTER_STACK))
    sli_zigbee_allow_tc_rejoins_using_well_known_key_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_allow_tc_rejoins_using_well_known_key_events[j].actions.handler = sli_zigbee_allow_tc_rejoins_using_well_known_key_event_handler;
    sli_zigbee_allow_tc_rejoins_using_well_known_key_events[j].actions.marker = NULL;
    sli_zigbee_allow_tc_rejoins_using_well_known_key_events[j].actions.name =  EVENT_NAME("Allow TC rejoin");
    sli_zigbee_allow_tc_rejoins_using_well_known_key_events[j].next = NULL;
#endif
  }

  for (uint8_t j = 0; j < sli_zigbee_supported_networks; j++) {
    sli_zigbee_request_key_events[j].actions.queue = &sli_zigbee_stack_event_queue;
    sli_zigbee_request_key_events[j].actions.handler = sli_zigbee_request_key_event_handler;
    sli_zigbee_request_key_events[j].actions.marker = NULL;
    sli_zigbee_request_key_events[j].actions.name =  EVENT_NAME("Req key");
    sli_zigbee_request_key_events[j].next = NULL;
  }
}

void sli_zigbee_multi_pan_init(void)
{
  initializeForkedEvents();
}
