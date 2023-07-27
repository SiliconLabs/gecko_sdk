/***************************************************************************//**
 * @file
 * @brief Code for multi-network support.
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

#ifndef EMBER_MULTI_NETWORK_H
#define EMBER_MULTI_NETWORK_H

#include "stack/include/ember.h"  // to get correct EMBER_MULTI_NETWORK_STRIPPED symbol
#include "stack/mac/multi-mac.h"
#include "upper-mac.h"

// We can only support up to 4 networks mainly because we only had 2 bits
// available in the MacInfo struct and only 2 bits available in the EZSP frame
// control. In order to support more than 4 networks, we need to redesign these
// two systems.

// Network index stack size.
#define EMBER_MULTI_NETWORK_MAX_DEPTH 10
// This value gets pushed on the network index stack when the application calls
#define EMBER_NETWORK_INDEX_STACK_APP_MARKER 0xFE

// If a node is coordinator/router on one network, it delays polls by 100ms
// in order to allow the node to switch back to the "always on" network.
#define EMBER_MULTI_NETWORK_POLLING_DELAY 100 // msec

// The way we set the current logical network is the following:
// - We set the current network with the call sli_zigbee_set_current_network()
// - The code after this call will be referring to the logical network we just
//   set
// - We call sli_zigbee_restore_current_network() to restore the previous logical network.
//   Note that the restore step is MANDATORY and the stack will assert in case
//   we forget to perform the restore.
//
// Follows an example:
// ...
// sli_zigbee_set_current_network(nwkIndex);
// ...
// code that is network-dependent
// ...
// sli_zigbee_restore_current_network();

// Declared in hal/config/ember-configuration.c
extern uint8_t sli_zigbee_default_stack_profile;

//------------------------------------------------------------------------------
// Common variables and functions. These are declared in both the regular and
// the stub libraries (in different flavors).
//------------------------------------------------------------------------------
extern uint8_t sli_zigbee_supported_networks;
extern uint8_t sli_zigbee_zc_and_zr_count;

extern const EmberLibraryStatus sli_zigbee_multi_network_library_status;

void sli_zigbee_network_descriptor_init(void);
EmberStatus sli_zigbee_multinetwork_radio_init(void);
uint8_t sli_zigbee_get_active_always_on_network_index(void);
bool sli_zigbee_is_network_joined(uint8_t nwkIndex);
bool sli_zigbee_is_network_always_on(uint8_t nwkIndex);

//------------------------------------------------------------------------------
// For saving flash on certain platforms, e.g. EFR32xG1, EFR32xG14, multi-network
// code is stripped by default. We do not maintain the network info in the
// NetworkInfo struct (which would result in accessing every field by using the
// '->' operator). Instead, we declare variables for storing the info related to
// the (only) network.
//------------------------------------------------------------------------------
#if defined(EMBER_MULTI_NETWORK_STRIPPED)
#define sli_zigbee_stack_profile (sli_zigbee_default_stack_profile)
#define sli_zigbee_parent_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].parent_node_id)
#define sli_parent_mac_index (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].mac_index)
#define sli_zigbee_parent_eui64 (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].parent_eui)
extern uint8_t sli_zigbee_node_type;
extern uint8_t sli_zigbee_state;
// Allow the capability byte to be updated at runtime
extern uint8_t sli_zigbee_dynamic_capabilities;
extern uint32_t sli_zigbee_security_state_bitmask;
extern uint8_t sli_zigbee_sequence_number;
extern uint8_t sli_zigbee_aps_sequence_number;
extern uint8_t sli_zigbee_network_security_level;
extern uint16_t sli_zigbee_unicast_tx_attempts;
extern uint16_t sli_zigbee_unicast_tx_failures;
extern uint8_t sli_zigbee_security_key_sequence_number;
extern uint32_t sli_zigbee_incoming_tc_link_key_frame_counter;
extern uint32_t sli_zigbee_last_child_age_time_ms;
extern uint32_t sli_zigbee_ms_since_last_poll;
#define sli_zigbee_stack_radio_channel (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].channel)
#define sli_zigbee_stack_radio_channelPage (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].channel_page)
#define sli_zigbee_stack_radio_power (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].tx_power)
#define sli_802154mac_local_node_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].local_node_id)
#define sli_802154mac_local_pan_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[0].pan_id)
extern uint32_t sli_zigbee_next_nwk_frame_counter;
#define sli_zigbee_neighbor_table ((sli_zigbee_neighbor_table_entry_t*)sli_zigbee_neighbor_data)
#define sli_zigbee_neighbor_table_size (sli_zigbee_router_neighbor_table_size)
extern uint8_t sli_zigbee_neighbor_count;
#define sli_zigbee_frame_counters (sli_zigbee_frame_countersTable)
extern uint16_t parentNwkInformation;
#define sli_zigbee_child_table (sli_zigbee_child_table_data)
#define sli_zigbee_child_status (sli_zigbee_child_status_data)
#define sli_zigbee_child_timers (sli_zigbee_child_timers_data)
#define sli_zigbee_child_lqi (sli_zigbee_child_lqi_data)
#define sli_zigbee_end_device_timeout (sli_zigbee_end_device_timeout_data)
extern uint8_t sli_zigbee_end_device_child_count;

#define sli_zigbee_route_record_table (sli_zigbee_route_record_table_data)
#define sli_zigbee_broadcast_table (sli_zigbee_broadcast_table_data)
extern uint32_t sli_zigbee_broadcast_age_cutoff_indices;
// Externed for zigbee test app.
extern uint8_t sli_zigbee_broadcast_head;
// This is zero if the time since bootup is longer than the broadcast
// table timeout.
extern uint8_t sli_zigbee_in_initial_broadcast_timeout;
// Used for sending link status more quickly at startup and only used by routers.
extern uint8_t sli_zigbee_fast_link_status_count;
// Association info
extern bool sli_zigbee_permit_joining;
extern bool sli_802154mac_permit_association;
extern bool sli_zigbee_allow_rejoins_with_well_known_key;
extern uint8_t sli_zigbee_parent_announce_index;
extern uint8_t sli_zigbee_total_initial_children;
extern EmberPanId sli_zigbee_new_pan_id;
#else
//------------------------------------------------------------------------------
// On all the other platforms we declare the networkInfo array (which is
// actually allocated in ember-configuration.c
// In this case we can either include the regular library or the stub library.
//------------------------------------------------------------------------------
extern EmberNetworkInfo sli_zigbee_network_descriptor[];
extern sli_zigbee_pan_info_t sli_zigbee_pan_info_table[];
//extern EmberNetworkInfo* sli_zigbee_current_network;
extern uint8_t sli_zigbee_current_network_index;
#define sli_zigbee_current_network (sli_zigbee_network_descriptor[sli_zigbee_current_network_index])

#define sli_zigbee_stack_profile (sli_zigbee_current_network.stackProfile)
#define sli_zigbee_parent_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].parent_node_id)
#define sli_parent_mac_index (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].mac_index)
#define sli_zigbee_parent_eui64 (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].parent_eui)
#define sli_zigbee_node_type (sli_zigbee_current_network.nodeType)
#define sli_zigbee_state (sli_zigbee_current_network.zigbeeState)
#define sli_zigbee_dynamic_capabilities (sli_zigbee_current_network.dynamicCapabilities)
#define sli_zigbee_security_state_bitmask (sli_zigbee_current_network.securityStateBitmask)
#define sli_zigbee_sequence_number (sli_zigbee_current_network.zigbeeSequenceNumber)
#define sli_zigbee_aps_sequence_number (sli_zigbee_current_network.apsSequenceNumber)
#define sli_zigbee_network_security_level (sli_zigbee_current_network.zigbeeNetworkSecurityLevel)
#define sli_zigbee_unicast_tx_attempts (sli_zigbee_current_network.unicastTxAttempts)
#define sli_zigbee_unicast_tx_failures (sli_zigbee_current_network.unicastTxFailures)
#define sli_zigbee_security_key_sequence_number (sli_zigbee_current_network.securityKeySequenceNumber)
#define sli_zigbee_incoming_tc_link_key_frame_counter (sli_zigbee_current_network.incomingTcLinkKeyFrameCounter)
#define sli_zigbee_last_child_age_time_ms (sli_zigbee_current_network.lastChildAgeTimeMs)
#define sli_zigbee_ms_since_last_poll (sli_zigbee_current_network.msSinceLastPoll)
#define sli_zigbee_stack_radio_channel (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].channel)
#define sli_zigbee_stack_radio_channelPage (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].channel_page)
#define sli_zigbee_stack_radio_power (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].tx_power)
#define sli_802154mac_local_node_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].local_node_id)
#define sli_802154mac_local_pan_id (sl_mac_upper_mac_state[0].nwk_radio_parameters[sli_zigbee_current_network_index].pan_id)
#define sli_zigbee_next_nwk_frame_counter (sli_zigbee_current_network.nextNwkFrameCounter)
#define sli_zigbee_neighbor_table (sli_zigbee_current_network.neighborTable)
#define sli_zigbee_neighbor_table_size (sli_zigbee_current_network.neighborTableSize)
#define sli_zigbee_neighbor_count (sli_zigbee_current_network.neighborCount)
#define sli_zigbee_frame_counters (sli_zigbee_current_network.frameCounters)
#define parentNwkInformation (sli_zigbee_current_network.parentNwkInformation)
#define sli_zigbee_child_table (sli_zigbee_current_network.panInfoData->childTable)
#define sli_zigbee_child_status (sli_zigbee_current_network.panInfoData->childStatus)
#define sli_zigbee_child_timers (sli_zigbee_current_network.panInfoData->childTimers)
#define sli_zigbee_child_lqi (sli_zigbee_current_network.panInfoData->childLqi)
#define sli_zigbee_end_device_timeout (sli_zigbee_current_network.panInfoData->endDeviceTimeout)
#define sli_zigbee_end_device_child_count (sli_zigbee_current_network.panInfoData->endDeviceChildCount)
#define sli_zigbee_route_record_table (sli_zigbee_current_network.panInfoData->routeRecordTable)
#define sli_zigbee_broadcast_table (sli_zigbee_current_network.panInfoData->broadcastTable)
#define sli_zigbee_broadcast_age_cutoff_indices (sli_zigbee_current_network.panInfoData->broadcastAgeCutoffIndexes)
#define sli_zigbee_broadcast_head (sli_zigbee_current_network.panInfoData->broadcastHead)
#define sli_zigbee_in_initial_broadcast_timeout (sli_zigbee_current_network.panInfoData->inInitialBroadcastTimeout)
#define sli_zigbee_fast_link_status_count (sli_zigbee_current_network.panInfoData->fastLinkStatusCount)
#define sli_zigbee_permit_joining (sli_zigbee_current_network.panInfoData->permitJoining)
#define sli_802154mac_permit_association  (sli_zigbee_current_network.panInfoData->macPermitAssociation)
#define sli_zigbee_allow_rejoins_with_well_known_key  (sli_zigbee_current_network.panInfoData->allowRejoinsWithWellKnownKey)
#define sli_zigbee_parent_announce_index (sli_zigbee_current_network.panInfoData->parentAnnounceIndex)
#define sli_zigbee_total_initial_children  (sli_zigbee_current_network.panInfoData->totalInitialChildren)
#define sli_zigbee_new_pan_id (sli_zigbee_current_network.panInfoData->newPanId)
#endif // defined(EMBER_MULTI_NETWORK_STRIPPED)

//------------------------------------------------------------------------------
// Certain platforms are multi-network-stripped by default. In order
// to save flash on these platforms we #define to () the following functions.
//------------------------------------------------------------------------------
#if defined(EMBER_MULTI_NETWORK_STRIPPED)
#define sli_zigbee_set_current_network(n)
#define sli_zigbee_restore_current_network()
#define sli_zigbee_get_current_network_index() (0)
#define sli_zigbee_enable_application_current_network()
#define sli_zigbee_is_current_network_stack_empty() (true)
#define sli_zigbee_association_in_progress() (false)
#define sli_zigbee_active_always_on_network_found() (false)
#define sli_zigbee_set_zigbee_event_network_index(offset)
#define sli_zigbee_get_zigbee_event_network_index(offset) (0)
#define sli_zigbee_get_radio_node_id() (sli_802154mac_local_node_id)
#define sli_zigbee_get_radio_pan_id() (sli_802154mac_local_pan_id)
#define sli_zigbee_note_node_type_change(nodeType)
#define sli_zigbee_schedule_next_poll() sl_mac_request_poll(0, sli_zigbee_get_current_network_index())
#else
#define sli_zigbee_set_current_network(n) (sli_zigbee_set_current_network_internal(n))
#define sli_zigbee_restore_current_network() (sli_zigbee_restore_current_network_internal())
uint8_t sli_zigbee_get_current_network_index(void);
void sli_zigbee_enable_application_current_network(void);
bool sli_zigbee_is_current_network_stack_empty(void);
bool sli_zigbee_association_in_progress(void);
bool sli_zigbee_active_always_on_network_found(void);
void sli_zigbee_set_current_network_internal(uint8_t nwkIndex);
void sli_zigbee_restore_current_network_internal(void);
void sli_zigbee_set_zigbee_event_network_index(uint8_t offset);
uint8_t sli_zigbee_get_zigbee_event_network_index(uint8_t offset);
EmberNodeId sli_zigbee_get_radio_node_id(void);
EmberPanId sli_zigbee_get_radio_pan_id(void);
uint8_t sli_zigbee_get_first_active_network_index(void);
bool sli_zigbee_is_active_coordinator_or_router_network_index(uint8_t index);
uint8_t sli_zigbee_get_active_coordinator_or_router_network_index(void);
void sli_zigbee_note_node_type_change(EmberNodeType nodeType);
void sli_zigbee_schedule_next_poll(void);
#endif // defined(EMBER_MULTI_NETWORK_STRIPPED)

//------------------------------------------------------------------------------
// Many zigbee events require storing the current network index when we schedule
// the event and restore it later once the event expired. We also save the the
// nerwork index for other asynchronous processes, for instance the MAC shutdown
// mechanism.
//------------------------------------------------------------------------------

#define ZIGBEE_NWK_INDEX_OFFSET_BEACON_EVENT                      0
#define ZIGBEE_NWK_INDEX_OFFSET_ASSOCIATION_EVENT                 2
#define ZIGBEE_NWK_INDEX_OFFSET_DISASSOCIATION_MAC_SHUTDOWN       4
#define ZIGBEE_NWK_INDEX_OFFSET_LEAVE_EVENT                       6
#define ZIGBEE_NWK_INDEX_OFFSET_NEW_CHANNEL_EVENT                 8
#define ZIGBEE_NWK_INDEX_OFFSET_SCAN_EVENT                        10
#define ZIGBEE_NWK_INDEX_OFFSET_MANAGEMENT_EVENT                  12
#define ZIGBEE_NWK_INDEX_OFFSET_ZDO_CHANNEL_CHANGE_EVENT          14
#define ZIGBEE_NWK_INDEX_OFFSET_ENTITY_AUTHENTICATION_EVENT       16
#define ZIGBEE_NWK_INDEX_OFFSET_ZIGBEE_DEVICE_EVENT               18
#define ZIGBEE_NWK_INDEX_OFFSET_POLL_DELAYING_EVENT               20
#define ZIGBEE_NWK_INDEX_OFFSET_SUPER_RETRY_FOR_POLL_EVENT        22
#define ZIGBEE_NWK_INDEX_OFFSET_NETWORK_TIMEOUT_REQUEST_EVENT   26
#define ZIGBEE_NWK_INDEX_OFFSET_SEND_ORPHAN_NOTIFICATION_EVENT    28
#define ZIGBEE_NWK_INDEX_OFFSET_SEND_PARENT_ANNOUNCE_EVENT      30

//------------------------------------------------------------------------------
// Wrappers for application callbacks that are called in many places in the code.
//------------------------------------------------------------------------------
#if defined(EMBER_MULTI_NETWORK_STRIPPED)
#define sli_zigbee_call_zigbee_key_establishment_handler(partner, status) \
  emberZigbeeKeyEstablishmentHandler(partner, status)
#define sli_zigbee_call_stack_status_handler(status) \
  emberStackStatusHandler(status)
#define sli_zigbee_call_poll_handler(childId, jit) \
  emberPollHandler(childId, jit)
#define sli_zigbee_call_packet_handoff_outgoing_handler(packetType, packetBuffer, index, data) \
  emberPacketHandoffOutgoingHandler(packetType, packetBuffer, index, data)
#define sli_zigbee_call_packet_handoff_incoming_handler(packetType, packetBuffer, index, data) \
  emberPacketHandoffIncomingHandler(packetType, packetBuffer, index, data)
#else
// Wrapper for the emberZigbeeKeyEstablishmentHandler() callback.
void sli_zigbee_call_zigbee_key_establishment_handler(EmberEUI64 partner,
                                                      EmberKeyStatus status);
// Wrapper for the emberStackStatusHandler() callback.
void sli_zigbee_call_stack_status_handler(EmberStatus status);
// Wrapper for the emberPollHandler() callback
void sli_zigbee_call_poll_handler(EmberNodeId childId, bool jit);

// Wrapper for the emberPacketHandoffOutgoingHandler() callback
EmberPacketAction sli_zigbee_call_packet_handoff_outgoing_handler(
  EmberZigbeePacketType packetType,
  EmberMessageBuffer packetBuffer,
  uint8_t index,
  // Return:
  void *data);

// Wrapper for the emberPacketHandoffIncomingHandler() callback
EmberPacketAction sli_zigbee_call_packet_handoff_incoming_handler(
  EmberZigbeePacketType packetType,
  EmberMessageBuffer packetBuffer,
  uint8_t index,
  // Return:
  void *data);
#endif // defined(EMBER_MULTI_NETWORK_STRIPPED)

//------------------------------------------------------------------------------
// Multi network events
//------------------------------------------------------------------------------
#if defined(EMBER_MULTI_NETWORK_STRIPPED)
// This code is for no multi-network at all
#define sli_zigbee_get_multi_network_forked_event(x)  (x)
#define sli_zigbee_get_network_index_from_multi_network_event(event, list) EMBER_NULL_NETWORK_INDEX
#else // !EMBER_MULTI_NETWORK_STRIPPED
// this code is multi-network and maybe multi-PAN
EmberEvent* sli_zigbee_get_multi_network_forked_event(EmberEvent *list);
uint8_t sli_zigbee_get_network_index_from_multi_network_event(EmberEvent *event,
                                                              EmberEvent *list);
#endif // EMBER_MULTI_NETWORK_STRIPPED

// This is called also from the HAL so we need to provide an implementation
// for both stripped and unstripped versions of the stack.
/*
 * This function is here to support the direct calls from platform/base
 * (for a few counters that only need the data field).
 * The following function should never be called from the stack, within the
 * stack we only use sli_zigbee_build_and_send_counter_info
 */
void sli_zigbee_call_counter_handler(EmberCounterType type, uint8_t data);
void sli_zigbee_build_and_send_counter_info(EmberCounterType counter, EmberNodeId dst, uint8_t data);

// sli_zigbee_build_and_send_counter_info() is used to log all counter types within stack,
// including phyIndex and/or destination Id required counters. For phyIndex required
// counters, we get the phyIndex by destination/node id look up.
// Following internal function is used for the counters where destination
// Id is not applicable/valid but counter requires the phyIndex.
// For all other counters, call sli_zigbee_build_and_send_counter_info().
void sli_zigbee_build_and_send_counter_info_with_phy_index(EmberCounterType counter,
                                                           uint8_t phyIndex,
                                                           uint8_t data);

//------------------------------------------------------------------------------

// This is a stub placed everywhere we used to call the current radio network
// handler to switch the configuration.  Things seem to work replacing it with
// nothing, but I wanted an easy way to add them back if necessary.
#define SET_RADIO_PARAMETERS()  if (sl_mac_lower_mac_is_idle(0)) { sli_upper_mac_update_lower_mac_params(0); }

#endif // EMBER_MULTI_NETWORK_H
