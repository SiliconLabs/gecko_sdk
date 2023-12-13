/***************************************************************************//**
 * @file
 * @brief User-configurable stack memory allocation and convenience stubs
 * for little-used callbacks.
 *
 *
 * \b Note: Application developers should \b not modify any portion
 * of this file. Doing so may lead to mysterious bugs. Allocations should be
 * adjusted only with macros in a custom CONFIGURATION_HEADER.
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

#include PLATFORM_HEADER
#include "hal.h"
#include "stack/include/ember.h"
#include "stack/include/error.h"
#include "stack/include/message.h" // Required for packetHandlers
#include "mac-child.h" // unified-mac
#include "scan.h" // Required for PG_CH_BITMASK32

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

// *****************************************
// Memory Allocations & declarations
// *****************************************

#if defined(CORTEXM3)
  #define align(value) (((value) + 3) & ~0x03)
#else
  #define align(value) (value)
#endif

//------------------------------------------------------------------------------
// API Version

const uint8_t sli_zigbee_api_version
  = (EMBER_API_MAJOR_VERSION << 4) + EMBER_API_MINOR_VERSION;

//------------------------------------------------------------------------------
// Multi PAN globals

#ifndef UC_BUILD
#define EMBER_ZC_AND_ZR_DEVICE_COUNT EMBER_AF_ZC_AND_ZR_DEVICE_COUNT
#endif // UC_BUILD

#define NUM_MULTI_PAN_FORKS    (EMBER_ZC_AND_ZR_DEVICE_COUNT == 0 \
                                ? 1                               \
                                : EMBER_ZC_AND_ZR_DEVICE_COUNT)
uint8_t sli_zigbee_num_multi_pan_forks = NUM_MULTI_PAN_FORKS;

uint8_t blackListedIdByteArray[NUM_MULTI_PAN_FORKS] = { 0 };
EmberMessageBuffer blacklistedIdsArray[NUM_MULTI_PAN_FORKS] = { EMBER_NULL_MESSAGE_BUFFER };
uint8_t panConflictMeters[NUM_MULTI_PAN_FORKS];
uint16_t trustCenterPolicies[NUM_MULTI_PAN_FORKS];
bool sl_permit_panid_conflict_reports[NUM_MULTI_PAN_FORKS] = { true };
uint16_t sl_zigbee_local_panid_conflict_count[NUM_MULTI_PAN_FORKS];
uint16_t sl_local_panid_conflict_last_reset_sec[NUM_MULTI_PAN_FORKS];
//------------------------------------------------------------------------------
// Multi PAN events

// In multi-PAN, we fork events that are required for both ZC and ZR networks.
// Each index of the event array maps 1-to-1 to the network index.
// For multi-network and single network, we only allocate 1 copy
// of the event (i.e. an array of element size 1).

// The following are not resizable, and we especially don't want their addresses
// to change, so we don't allocate them from emAvailableMemory

EmberEvent sli_zigbee_beacon_events[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_permit_joiningEvents[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_network_management_events[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_neighbor_exchange_events[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_request_key_events[EMBER_SUPPORTED_NETWORKS];

#if !defined(SL_ZIGBEE_LEAF_STACK) || defined (CSL_SUPPORT)
EmberEvent sli_zigbee_send_parent_announce_events[NUM_MULTI_PAN_FORKS];
#endif
EmberEvent sli_zigbee_transient_link_key_events[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_gp_tx_events[NUM_MULTI_PAN_FORKS];
EmberEvent sli_zigbee_source_route_update_events[NUM_MULTI_PAN_FORKS];
#if !(defined(SL_ZIGBEE_ROUTER_STACK))
EmberEvent sli_zigbee_allow_tc_rejoins_using_well_known_key_events[NUM_MULTI_PAN_FORKS];
#endif

//------------------------------------------------------------------------------

// Timeout in milliseconds
// before the entry in the transient table will be purged or
// copied into the relevant table (child / neighbor)
// It is also the proposed apsSecurityTimeoutPeriod
uint16_t sli_zigbee_transient_device_timeout = SL_ZIGBEE_TRANSIENT_DEVICE_DEFAULT_TIMEOUT_MS;

//Allows the aps acks for APSME commands to be turned off or on
//This should be "true" by default but to keep it consistend with the current stack behaviour this is "false" by default.
bool sl_zigbee_enable_aps_ack_for_cmds = SL_ZIGBEE_ENABLE_APS_ACKS_FOR_COMMANDS;
//------------------------------------------------------------------------------
// MAC Layer

const EmberMacFilterMatchData zigbeeMacFilterList[] = {
#if (defined(EMBER_AF_PLUGIN_GP_LIBRARY) || defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT))
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_NONE
   | EMBER_MAC_FILTER_MATCH_ON_DEST_BROADCAST_SHORT
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_NONE),
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_LOCAL
   | EMBER_MAC_FILTER_MATCH_ON_DEST_BROADCAST_SHORT
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_LONG),
#endif // EMBER_AF_PLUGIN_GP_LIBRARY
#if (defined(EMBER_AF_PLUGIN_ZLL_LIBRARY) || defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT))
  // ZLL Scan requests
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_NON_LOCAL
   | EMBER_MAC_FILTER_MATCH_ON_DEST_BROADCAST_SHORT
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_LONG),
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_LOCAL
   | EMBER_MAC_FILTER_MATCH_ON_DEST_BROADCAST_SHORT
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_LONG),

  // All other incoming inter-pan ZLL messages
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_NON_LOCAL
   | EMBER_MAC_FILTER_MATCH_ON_DEST_UNICAST_LONG
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_LONG),
  (EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST
   | EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_LOCAL
   | EMBER_MAC_FILTER_MATCH_ON_DEST_UNICAST_LONG
   | EMBER_MAC_FILTER_MATCH_ON_SOURCE_LONG),
#endif // EMBER_AF_PLUGIN_ZLL_LIBRARY
  EMBER_MAC_FILTER_MATCH_END
};

// Pass a pointer to child table in memory to the unified mac layer.
//sl_mac_child_entry_t *sli_zigbee_child_table_data = (sl_mac_child_entry_t *) &emAvailableMemory[0];
sl_mac_child_entry_t sli_zigbee_child_table_data[1 + EMBER_CHILD_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT];
#if defined(SL_ZIGBEE_LEAF_STACK) && defined(EMBER_AF_NCP)
uint8_t emberChildTableSize = 0;
#else // !(defined(SL_ZIGBEE_LEAF_STACK) && defined(EMBER_AF_NCP))
uint8_t emberChildTableSize = EMBER_CHILD_TABLE_SIZE;
#endif // defined(SL_ZIGBEE_LEAF_STACK) && defined(EMBER_AF_NCP)

//------------------------------------------------------------------------------
// NWK Layer

#ifdef EMBER_DISABLE_RELAY
uint8_t sli_zigbee_allow_relay = false;
#else
uint8_t sli_zigbee_allow_relay = true;
#endif

uint16_t sli_zigbee_child_status_data[1 + EMBER_CHILD_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT];

uint32_t sli_zigbee_child_timers_data[1 + EMBER_CHILD_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT];

int8_t sli_zigbee_child_power[1 + EMBER_CHILD_TABLE_SIZE];

// sli_zigbee_child_lqi >> 8 keeps the average Lqi values mapped from 0-255 to 1-255 after initialization
// LQI data (0-255) is stored in a 16 bit variable so we end up with greater
// precision after the weighted averaging operation
uint16_t sli_zigbee_child_lqi_data[1 + EMBER_CHILD_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT];

sli_zigbee_route_table_entry_t sli_zigbee_route_table[1 + EMBER_ROUTE_TABLE_SIZE];
uint8_t sli_zigbee_route_table_size = EMBER_ROUTE_TABLE_SIZE;

// Duplicate the table for multi PAN mode depending on how many ZC and ZR devices are present.
uint8_t sli_zigbee_route_record_table_data[1 + (((EMBER_CHILD_TABLE_SIZE + 7) >> 3) * EMBER_ROUTE_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT)];

sli_zigbee_discovery_table_entry_t sli_zigbee_discovery_table[EMBER_DISCOVERY_TABLE_SIZE];
uint8_t sli_zigbee_discovery_table_size = EMBER_DISCOVERY_TABLE_SIZE;

EmberMulticastTableEntry emberMulticastTable[EMBER_MULTICAST_TABLE_SIZE];
uint8_t emberMulticastTableSize = EMBER_MULTICAST_TABLE_SIZE;

// Broadcast table exists in all device types so we allocate memory to it even if no ZC and ZR device present.
// Duplicate the table if more than one ZC and ZR devices present.
sli_zigbee_broadcast_table_entry_t sli_zigbee_broadcast_table_data[EMBER_BROADCAST_TABLE_SIZE * NUM_MULTI_PAN_FORKS];
uint8_t sli_zigbee_broadcast_table_size = EMBER_BROADCAST_TABLE_SIZE;

//------------------------------------------------------------------------------
// Network descriptor (multi-network support)

#if !defined(EMBER_MULTI_NETWORK_STRIPPED)
EmberNetworkInfo sli_zigbee_network_descriptor[EMBER_SUPPORTED_NETWORKS];
uint8_t sli_zigbee_supported_networks = EMBER_SUPPORTED_NETWORKS;

// PAN info exists in all device types so we allocate memory to it even if no ZC and ZR device present.
// Duplicate it if more than one ZC and ZR devices present.
sli_zigbee_pan_info_t sli_zigbee_pan_info_table[NUM_MULTI_PAN_FORKS];
#else
uint8_t sli_zigbee_supported_networks = 1;
#define END_sli_zigbee_pan_info_data END_emberBroadcastTable
#endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)

//------------------------------------------------------------------------------
// Neighbor Table
// Neighbor and frame counter table exist on end device as well but it contains only one entry.
// Duplicate neighbor and frame counter tables per ZC and ZR device.
// If there is no ZC and ZR device present, then allocate one entry for each end device.
sli_zigbee_neighbor_table_entry_t sli_zigbee_neighbor_data[((EMBER_NEIGHBOR_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT) + EMBER_SUPPORTED_NETWORKS)];
uint8_t sli_zigbee_router_neighbor_table_size = EMBER_NEIGHBOR_TABLE_SIZE;

uint32_t sli_zigbee_frame_countersTable[((EMBER_NEIGHBOR_TABLE_SIZE + EMBER_CHILD_TABLE_SIZE) * EMBER_ZC_AND_ZR_DEVICE_COUNT + EMBER_SUPPORTED_NETWORKS)];

//------------------------------------------------------------------------------
// NWK Retry Queue

sli_zigbee_retry_queue_entry_t sli_zigbee_retry_queue[EMBER_RETRY_QUEUE_SIZE];
uint8_t sli_zigbee_retry_queue_size = EMBER_RETRY_QUEUE_SIZE;

// NWK Store And Forward Queue

sli_zigbee_store_and_forward_queue_entry_t sli_zigbee_store_and_forward_queue[EMBER_STORE_AND_FORWARD_QUEUE_SIZE];
uint8_t sli_zigbee_store_and_forward_queue_size = EMBER_STORE_AND_FORWARD_QUEUE_SIZE;

//------------------------------------------------------------------------------
// Green Power stack tables
uint8_t sli_zigbee_gp_incoming_fc_token_table_size = EMBER_GP_INCOMING_FC_TOKEN_TABLE_SIZE;
uint8_t sli_zigbee_gp_incoming_fc_token_timeout = EMBER_GP_INCOMING_FC_TOKEN_TIMEOUT;

EmberGpProxyTableEntry sli_zigbee_gp_proxy_table[EMBER_GP_PROXY_TABLE_SIZE];
uint8_t sli_zigbee_gp_proxy_table_size = EMBER_GP_PROXY_TABLE_SIZE;

uint8_t sli_zigbee_gp_incoming_fc_in_sink_token_table_size = EMBER_GP_INCOMING_FC_IN_SINK_TOKEN_TABLE_SIZE;
uint8_t sli_zigbee_gp_incoming_fc_in_sink_token_timeout = EMBER_GP_INCOMING_FC_IN_SINK_TOKEN_TIMEOUT;

#if (EMBER_GP_SINK_TABLE_SIZE > 0)
EmberGpSinkTableEntry sli_zigbee_gp_sink_table[EMBER_GP_SINK_TABLE_SIZE];
#else
// Provide a dummy entry to avoid 0 length array
EmberGpSinkTableEntry sli_zigbee_gp_sink_table[1];
#endif
uint8_t sli_zigbee_gp_sink_table_size = EMBER_GP_SINK_TABLE_SIZE;

//------------------------------------------------------------------------------
// Source routing

#if (defined(EMBER_AF_PLUGIN_SOURCE_ROUTE_LIBRARY) || defined(SL_CATALOG_ZIGBEE_SOURCE_ROUTE_PRESENT))

// Source Route info
uint8_t sourceRouteTableEntryCount[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteTableNewestIndex[NUM_MULTI_PAN_FORKS];
uint16_t sourceRouteUpdateConcentratorType[NUM_MULTI_PAN_FORKS];
uint16_t sourceRouteUpdateMinQS[NUM_MULTI_PAN_FORKS];
uint16_t sourceRouteUpdateMaxQS[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteUpdateRouteErrorThreshold[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteUpdateDeliveryFailureThreshold[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteUpdateMaxHops[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteUpdateRouteErrorCount[NUM_MULTI_PAN_FORKS];
uint8_t sourceRouteUpdateDeliveryFailureCount[NUM_MULTI_PAN_FORKS];
EmberNodeId sourceRouteUpdateNodeIdWithBrokenRoute[NUM_MULTI_PAN_FORKS];
bool sourceRouteUpdateSendAddressDiscoveryNextEvent[NUM_MULTI_PAN_FORKS];
bool sourceRouteUpdateActiveEvent[NUM_MULTI_PAN_FORKS];

SourceRouteTableEntry sli_zigbee_source_route_table_data[EMBER_SOURCE_ROUTE_TABLE_SIZE * NUM_MULTI_PAN_FORKS];
uint8_t sli_zigbee_source_route_table_size = EMBER_SOURCE_ROUTE_TABLE_SIZE;
#else
SourceRouteTableEntry *sli_zigbee_source_route_table_data = NULL;
uint8_t sli_zigbee_source_route_table_size = 0;
#define END_sli_zigbee_source_route_table END_sli_zigbee_gp_sink_table
#endif // EMBER_AF_PLUGIN_SOURCE_ROUTE_LIBRARY || SL_CATALOG_ZIGBEE_SOURCE_ROUTE_PRESENT

//------------------------------------------------------------------------------
// Binding Table

uint16_t sli_zigbee_binding_remote_node[1 + EMBER_BINDING_TABLE_SIZE];
uint8_t emberBindingTableSize = EMBER_BINDING_TABLE_SIZE;

uint8_t sli_zigbee_binding_flags[1 + EMBER_BINDING_TABLE_SIZE];

//------------------------------------------------------------------------------
//End Device Timeouts

uint8_t sli_zigbee_end_device_timeout_data[1 + EMBER_CHILD_TABLE_SIZE * EMBER_ZC_AND_ZR_DEVICE_COUNT];

//------------------------------------------------------------------------------

// APS Layer
uint8_t  sli_zigbee_aps_duplicate_rejection_max_size = SL_ZIGBEE_APS_DUPLICATE_REJECTION_MAX_ENTRIES;
sl_zigbee_aps_duplicate_msg_entry_t sli_zigbee_aps_duplicate_rejection_entries[SL_ZIGBEE_APS_DUPLICATE_REJECTION_MAX_ENTRIES];

uint8_t sli_zigbee_address_table_size = EMBER_ADDRESS_TABLE_SIZE;
uint8_t sli_zigbee_address_tableMaxSize = EMBER_ADDRESS_TABLE_SIZE + 4;
sli_zigbee_address_table_entry_t sli_zigbee_address_table[EMBER_ADDRESS_TABLE_SIZE + 4];

uint8_t sli_zigbee_max_aps_unicast_messages = EMBER_APS_UNICAST_MESSAGE_COUNT;
sli_zigbee_aps_unicast_message_data_t sli_zigbee_aps_unicast_message_data[EMBER_APS_UNICAST_MESSAGE_COUNT];

uint16_t emberApsAckTimeoutMs =
  ((EMBER_APSC_MAX_ACK_WAIT_HOPS_MULTIPLIER_MS
    * EMBER_MAX_HOPS)
   + EMBER_APSC_MAX_ACK_WAIT_TERMINAL_SECURITY_MS);

uint8_t sli_zigbee_fragment_delay_ms = EMBER_FRAGMENT_DELAY_MS;
uint8_t emberFragmentWindowSize = EMBER_FRAGMENT_WINDOW_SIZE;

uint8_t emberKeyTableSize = EMBER_KEY_TABLE_SIZE;
uint32_t sli_zigbee_incoming_aps_frame_counters[1 + EMBER_KEY_TABLE_SIZE];

EmberTcLinkKeyRequestPolicy emberTrustCenterLinkKeyRequestPolicies[NUM_MULTI_PAN_FORKS];
EmberAppLinkKeyRequestPolicy emberAppLinkKeyRequestPolicies[NUM_MULTI_PAN_FORKS];

uint8_t sli_zigbee_certificate_table_size = EMBER_CERTIFICATE_TABLE_SIZE;

uint8_t sli_zigbee_zdo_beacon_survey_unique_nwks = SL_ZIGBEE_ZDO_BEACON_SURVEY_MAX_UNIQUE_NETWORKS;

uint8_t sli_zigbee_app_zdo_configuration_flags =
  0

// Define this in order to receive supported ZDO request messages via
// the incomingMessageHandler callback.  A supported ZDO request is one that
// is handled by the EmberZNet stack.  The stack will continue to handle the
// request and send the appropriate ZDO response even if this configuration
// option is enabled.
#ifdef EMBER_APPLICATION_RECEIVES_SUPPORTED_ZDO_REQUESTS
  | EMBER_APP_RECEIVES_SUPPORTED_ZDO_REQUESTS
#endif

// Define this in order to receive unsupported ZDO request messages via
// the incomingMessageHandler callback.  An unsupported ZDO request is one that
// is not handled by the EmberZNet stack, other than to send a 'not supported'
// ZDO response.  If this configuration option is enabled, the stack will no
// longer send any ZDO response, and it is the application's responsibility
// to do so.  To see if a response is required, the application must check
// the APS options bitfield within the emberIncomingMessageHandler callback to see
// if the EMBER_APS_OPTION_ZDO_RESPONSE_REQUIRED flag is set.
#ifdef EMBER_APPLICATION_HANDLES_UNSUPPORTED_ZDO_REQUESTS
  | EMBER_APP_HANDLES_UNSUPPORTED_ZDO_REQUESTS
#endif

// Define this in order to receive the following ZDO request
// messages via the emberIncomingMessageHandler callback: SIMPLE_DESCRIPTOR_REQUEST,
// MATCH_DESCRIPTORS_REQUEST, and ACTIVE_ENDPOINTS_REQUEST.  If this
// configuration option is enabled, the stack will no longer send any ZDO
// response, and it is the application's responsibility to do so.
// To see if a response is required, the application must check
// the APS options bitfield within the emberIncomingMessageHandler callback to see
// if the EMBER_APS_OPTION_ZDO_RESPONSE_REQUIRED flag is set.
#ifdef EMBER_APPLICATION_HANDLES_ENDPOINT_ZDO_REQUESTS
  | EMBER_APP_HANDLES_ZDO_ENDPOINT_REQUESTS
#endif

// Define this in order to receive the following ZDO request
// messages via the emberIncomingMessageHandler callback: BINDING_TABLE_REQUEST,
// BIND_REQUEST, and UNBIND_REQUEST.  If this
// configuration option is enabled, the stack will no longer send any ZDO
// response, and it is the application's responsibility to do so.
// To see if a response is required, the application must check
// the APS options bitfield within the emberIncomingMessageHandler callback
// to see if the EMBER_APS_OPTION_ZDO_RESPONSE_REQUIRED flag is set.
#ifdef EMBER_APPLICATION_HANDLES_BINDING_ZDO_REQUESTS
  | EMBER_APP_HANDLES_ZDO_BINDING_REQUESTS
#endif
;

uint16_t emberTransientKeyTimeoutS = EMBER_TRANSIENT_KEY_TIMEOUT_S;

// This configuration is for non trust center node to assume a
// concentrator type of the trust center it join to, until it receive
// many-to-one route request from the trust center. For the trust center
// node, concentrator type is configured from the concentrator plugin.
// The stack by default assumes trust center be a low RAM concentrator.
// By setting to a low RAM concentrator, other devices send route record
// to the trust center even without receiving many-to-one route request.
EmberAssumeTrustCenterConcentratorType emberAssumedTrustCenterConcentratorType =
  EMBER_ASSUME_TRUST_CENTER_IS_LOW_RAM_CONCENTRATOR;
//
// Packet Buffers
uint8_t sli_zigbee_packet_buffer_count = EMBER_PACKET_BUFFER_COUNT;
const uint32_t heapMemorySize = EMBER_PACKET_BUFFER_COUNT * 32;

// The actual memory for buffers.
#if defined(CORTEXM3)
SL_ALIGN(4)
uint16_t heapMemory[EMBER_PACKET_BUFFER_COUNT * 16] SL_ATTRIBUTE_ALIGN(4);
#else
uint16_t heapMemory[EMBER_PACKET_BUFFER_COUNT * 16] __attribute__ ((aligned(4)));
#endif

// *****************************************
// Non-dynamically configurable structures
// *****************************************
//const uint8_t sli_event_control_task_count = EMBER_TASK_COUNT;
//EmberTaskControl sli_event_control_tasks[EMBER_TASK_COUNT];

// *****************************************
// Stack Profile Parameters
// *****************************************

const uint8_t emberStackProfileId[8] = { 0, };

uint8_t sli_zigbee_stack_compliance_revision = SL_ZIGBEE_STACK_COMPLIANCE_REVISION;

uint8_t sli_zigbee_default_stack_profile = EMBER_STACK_PROFILE;
uint8_t sli_zigbee_default_security_level = EMBER_SECURITY_LEVEL;
uint8_t sli_zigbee_max_end_device_children = EMBER_MAX_END_DEVICE_CHILDREN;
uint8_t sli_zigbee_max_hops = EMBER_MAX_HOPS;
uint16_t emberMacIndirectTimeout = EMBER_INDIRECT_TRANSMISSION_TIMEOUT;
uint8_t emberEndDevicekeepAliveSupportMode = EMBER_END_DEVICE_KEEP_ALIVE_SUPPORT_MODE;
uint8_t emberEndDevicePollTimeout = EMBER_END_DEVICE_POLL_TIMEOUT;
//STATIC_ASSERT(EMBER_END_DEVICE_POLL_TIMEOUT <= MINUTES_16384, "End device timeout out of range");
uint16_t emberLinkPowerDeltaInterval = EMBER_LINK_POWER_DELTA_INTERVAL;
uint8_t sli_zigbee_request_key_timeout = EMBER_REQUEST_KEY_TIMEOUT;
uint8_t sli_zigbee_pan_id_conflict_report_threshold = EMBER_PAN_ID_CONFLICT_REPORT_THRESHOLD;
uint8_t sli_zigbee_zc_and_zr_count = EMBER_ZC_AND_ZR_DEVICE_COUNT;
uint8_t sli_zigbee_max_network_retries = EMBER_ZIGBEE_NUM_NETWORK_RETRIES_DEFAULT;

#ifndef EMBER_NO_STACK
uint8_t sli_zigbee_end_device_configuration = EMBER_END_DEVICE_CONFIG_PERSIST_DATA_ON_PARENT;
#endif

// Normally multicasts do NOT go to the sleepy address (0xFFFF), they go to
// RxOnWhenIdle=true (0xFFFD).  This can be changed, but doing so is not
// ZigBee Pro Compliant and is possibly NOT interoperable.
bool sli_zigbee_send_multicasts_to_sleepy_address = EMBER_SEND_MULTICASTS_TO_SLEEPY_ADDRESS;

// *****************************************
// ZigBee Light Link
// *****************************************

EmberZllPolicy sli_zigbee_zll_policy = EMBER_ZLL_POLICY_DISABLED;

// The number of groups required by the ZLL application.
uint8_t sli_zigbee_zll_group_addresses_needed = EMBER_ZLL_GROUP_ADDRESSES;
int8_t sli_zigbee_zll_rssi_threshold = EMBER_ZLL_RSSI_THRESHOLD;
#ifdef EMBER_ZLL_APPLY_THRESHOLD_TO_ALL_INTERPANS
bool sli_zigbee_zll_apply_threshold_to_all_interpans = true;
#else
bool sli_zigbee_zll_apply_threshold_to_all_interpans = false;
#endif

// *****************************************
// Convenience Stubs
// *****************************************

// This macro is #define'd at the top of NCP framework applications.
// Since appbuilder generates stubs to callbacks, these convinience stubs
// are not needed for framework apps.
#ifndef __NCP_CONFIG__

#ifndef EMBER_APPLICATION_HAS_TRUST_CENTER_JOIN_HANDLER
EmberJoinDecision emberDefaultTrustCenterDecision = EMBER_USE_PRECONFIGURED_KEY;

WEAK(EmberJoinDecision emberTrustCenterJoinHandler(EmberNodeId newNodeId,
                                                   EmberEUI64 newNodeEui64,
                                                   EmberDeviceUpdate status,
                                                   EmberNodeId parentOfNewNode))
{
  (void)newNodeId;
  (void)newNodeEui64;
  (void)status;
  (void)parentOfNewNode;

  //emzigbee-241-4
#if defined(EMBER_AF_PLUGIN_CONCENTRATOR)
  if (emberDefaultTrustCenterDecision != EMBER_DENY_JOIN
      && parentOfNewNode != emberGetNodeId()) {
    // stodo: not sure about the condition above,
    // because we should get here only if the new child is not our
    // direct child and it is multiple hops away?
    bool deviceLeft = (status == EMBER_DEVICE_LEFT);
    sli_zigbee_change_source_route_entry(newNodeId, parentOfNewNode, false, deviceLeft);
  }
#endif

  if (status == EMBER_STANDARD_SECURITY_SECURED_REJOIN
      || status == EMBER_DEVICE_LEFT) {
    return EMBER_NO_ACTION;
  }

  return emberDefaultTrustCenterDecision;
}
#endif

#ifndef EMBER_APPLICATION_HAS_SWITCH_KEY_HANDLER
WEAK(void emberSwitchNetworkKeyHandler(uint8_t sequenceNumber))
{
  (void)sequenceNumber;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ZIGBEE_KEY_ESTABLISHMENT_HANDLER
WEAK(void emberZigbeeKeyEstablishmentHandler(EmberEUI64 partner, EmberKeyStatus status))
{
  (void)partner;
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_CHILD_JOIN_HANDLER
WEAK(void emberChildJoinHandler(uint8_t index, bool joining))
{
  (void)index;
  (void)joining;
}
#endif

#ifndef EMBER_APPLICATION_HAS_POLL_COMPLETE_HANDLER
WEAK(void emberPollCompleteHandler(EmberStatus status))
{
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_BOOTLOAD_HANDLERS
WEAK(void emberIncomingBootloadMessageHandler(EmberEUI64 longId,
                                              EmberMessageBuffer message))
{
  (void)longId;
  (void)message;
}
WEAK(void emberBootloadTransmitCompleteHandler(EmberMessageBuffer message,
                                               EmberStatus status))
{
  (void)message;
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_MAC_FILTER_MATCH_MESSAGE_HANDLER
WEAK(void emberMacFilterMatchMessageHandler(const EmberMacFilterMatchStruct* macFilterMatchStruct))
{
  emberMacPassthroughMessageHandler(macFilterMatchStruct->legacyPassthroughType,
                                    macFilterMatchStruct->message);
}
#endif

#ifndef EMBER_APPLICATION_HAS_MAC_PASSTHROUGH_HANDLER
WEAK(void emberMacPassthroughMessageHandler(EmberMacPassthroughType messageType,
                                            EmberMessageBuffer message))
{
  (void)messageType;
  (void)message;
}
#endif
#ifndef EMBER_APPLICATION_HAS_RAW_HANDLER
WEAK(void emberRawTransmitCompleteHandler(EmberMessageBuffer message,
                                          EmberStatus status))
{
  (void)message;
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_INCOMING_MFG_TEST_MESSAGE_HANDLER
WEAK(void emberIncomingMfgTestMessageHandler(uint8_t messageType,
                                             uint8_t dataLength,
                                             uint8_t *data))
{
  (void)messageType;
  (void)dataLength;
  (void)data;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ENERGY_SCAN_RESULT_HANDLER
WEAK(void emberEnergyScanResultHandler(uint8_t channel, int8_t maxRssiValue))
{
  (void)channel;
  (void)maxRssiValue;
}
#endif

#ifndef EMBER_APPLICATION_HAS_DEBUG_HANDLER
WEAK(void emberDebugHandler(EmberMessageBuffer message))
{
  (void)message;
}
#endif

#ifndef EMBER_APPLICATION_HAS_POLL_HANDLER
WEAK(void emberPollHandler(EmberNodeId childId, bool transmitExpected))
{
  (void)childId;
  (void)transmitExpected;
}
#endif

#ifndef EMBER_APPLICATION_HAS_REMOTE_BINDING_HANDLER
WEAK(EmberStatus emberRemoteSetBindingHandler(EmberBindingTableEntry *entry))
{
  (void)entry;

  // Don't let anyone mess with our bindings.
  return EMBER_INVALID_BINDING_INDEX;
}
WEAK(EmberStatus emberRemoteDeleteBindingHandler(uint8_t index))
{
  (void)index;

  // Don't let anyone mess with our bindings.
  return EMBER_INVALID_BINDING_INDEX;
}
#endif

#ifndef EMBER_APPLICATION_HAS_INCOMING_MANY_TO_ONE_ROUTE_REQUEST_HANDLER
WEAK(void emberIncomingManyToOneRouteRequestHandler(EmberNodeId source,
                                                    EmberEUI64 longId,
                                                    uint8_t cost))
{
  (void)source;
  (void)longId;
  (void)cost;
}
#endif

#ifndef EMBER_APPLICATION_HAS_INCOMING_ROUTE_ERROR_HANDLER
WEAK(void emberIncomingRouteErrorHandler(EmberStatus status,
                                         EmberNodeId target))
{
  (void)status;
  (void)target;
}
#endif

#ifndef EMBER_APPLICATION_HAS_INCOMING_NETWORK_STATUS_HANDLER
WEAK(void emberIncomingNetworkStatusHandler(uint8_t errorCode,
                                            EmberNodeId target))
{
  (void)errorCode;
  (void)target;
}
#endif

#ifndef EMBER_APPLICATION_HAS_SOURCE_ROUTING //DEPRECATED
//Deprecated
WEAK(void emberIncomingRouteRecordHandler(EmberNodeId source,
                                          EmberEUI64 sourceEui,
                                          uint8_t relayCount,
                                          EmberMessageBuffer header,
                                          uint8_t relayListIndex))
{
  (void)source;
  (void)sourceEui;
  (void)relayCount;
  (void)header;
  (void)relayListIndex;
}
//Deprecated
WEAK(uint8_t emberAppendSourceRouteHandler(EmberNodeId destination,
                                           EmberMessageBuffer header))
{
  (void)destination;
  (void)header;

  return 0;
}
#endif

#ifndef EMBER_APPLICATION_HAS_OVERRIDE_SOURCE_ROUTING
WEAK(void emberOverrideIncomingRouteRecordHandler(EmberNodeId source,
                                                  EmberEUI64 sourceEui,
                                                  uint8_t relayCount,
                                                  EmberMessageBuffer header,
                                                  uint8_t relayListIndex,
                                                  bool* consumed))
{
  emberIncomingRouteRecordHandler(source,
                                  sourceEui,
                                  relayCount,
                                  header,
                                  relayListIndex);
}

WEAK(uint8_t emberOverrideAppendSourceRouteHandler(EmberNodeId destination,
                                                   EmberMessageBuffer* header,
                                                   bool* consumed))
{
  (void)destination;
  (void)header;
  (void)consumed;

  return 0;
}

WEAK(void emberOverrideFurthurIndexForSourceRouteAddEntryHandler(EmberNodeId id,
                                                                 uint8_t* furtherIndex))
{
  (void)id;
  (void)furtherIndex;
}
#endif

#if !defined(EMBER_APPLICATION_HAS_GET_ENDPOINT) && !defined(EMBER_AF_NCP)
uint8_t emberGetEndpoint(uint8_t index)
{
  return emberEndpoints[index].endpoint;
}

bool emberGetEndpointDescription(uint8_t endpoint,
                                 EmberEndpointDescription *result)
{
  uint8_t i;
  EmberEndpoint *endpoints = emberEndpoints;
  for (i = 0; i < emberEndpointCount; i++, endpoints++) {
    if (endpoints->endpoint == endpoint) {
      EmberEndpointDescription const * d = endpoints->description;
      result->profileId                   = d->profileId;
      result->deviceId                    = d->deviceId;
      result->deviceVersion               = d->deviceVersion;
      result->inputClusterCount           = d->inputClusterCount;
      result->outputClusterCount          = d->outputClusterCount;
      return true;
    }
  }
  return false;
}

uint16_t emberGetEndpointCluster(uint8_t endpoint,
                                 EmberClusterListId listId,
                                 uint8_t listIndex)
{
  uint8_t i;
  EmberEndpoint *endpoints = emberEndpoints;
  for (i = 0; i < emberEndpointCount; i++, endpoints++) {
    if (endpoints->endpoint == endpoint) {
      switch (listId) {
        case EMBER_INPUT_CLUSTER_LIST:
          return endpoints->inputClusterList[listIndex];
        case EMBER_OUTPUT_CLUSTER_LIST:
          return endpoints->outputClusterList[listIndex];
        default: {
        }
      }
    }
  }
  return 0;
}

uint8_t emberGetEndpointCount(void)
{
  return emberEndpointCount;
}

#endif // defined EMBER_APPLICATION_HAS_GET_ENDPOINT

// Inform the application that an orphan notification has been received.
// This is generally not useful for applications. It could be useful in
// testing and is included for this purpose.
#ifndef EMBER_APPLICATION_HAS_ORPHAN_NOTIFICATION_HANDLER
WEAK(void emberOrphanNotificationHandler(EmberEUI64 longId))
{
  (void)longId;
}
#endif

#ifndef EMBER_APPLICATION_HAS_PAN_ID_CONFLICT_HANDLER
// This handler is called by the
//  stack to report the number of conflict reports exceeds
//  EMBER_PAN_ID_CONFLICT_REPORT_THRESHOLD within a period of 1 minute )
WEAK(EmberStatus emberPanIdConflictHandler(int8_t conflictCount))
{
  (void)conflictCount;

  return EMBER_SUCCESS;
}
#endif

#ifndef EMBER_APPLICATION_HAS_COUNTER_HANDLER

WEAK(void emberCounterHandler(EmberCounterType type, EmberCounterInfo info))
{
  (void)type;
  (void)info;
}
#endif

#ifndef EMBER_APPLICATION_HAS_COUNTER_ROLLOVER_HANDLER
WEAK(void emberCounterRolloverHandler(EmberCounterType type))
{
  (void)type;
}
#endif

#ifndef EMBER_APPLICATION_HAS_STACK_TOKEN_CHANGED_HANDLER
WEAK(void emberStackTokenChangedHandler(uint16_t tokenAddress))
{
  (void)tokenAddress;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ID_CONFLICT_HANDLER
WEAK(void emberIdConflictHandler(EmberNodeId conflictingId))
{
  (void)conflictingId;
}
#endif

#ifndef EMBER_APPLICATION_HAS_MAC_PASSTHROUGH_FILTER_HANDLER
WEAK(bool emberMacPassthroughFilterHandler(uint8_t *macHeader))
{
  (void)macHeader;

  return false;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ZLL_ADDRESS_ASSIGNMENT_HANDLER
WEAK(void emberZllAddressAssignmentHandler(const EmberZllAddressAssignment* addressInfo))
{
  (void)addressInfo;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ZLL_NETWORK_FOUND_HANDLER
WEAK(void emberZllNetworkFoundHandler(const EmberZllNetwork* networkInfo,
                                      const EmberZllDeviceInfoRecord* deviceInfo))
{
  (void)networkInfo;
  (void)deviceInfo;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ZLL_SCAN_COMPLETE_HANDLER
WEAK(void emberZllScanCompleteHandler(EmberStatus status))
{
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_ZLL_TOUCH_LINK_TARGET_HANDLER
WEAK(void emberZllTouchLinkTargetHandler(const EmberZllNetwork* networkInfo))
{
  (void)networkInfo;
}
#endif

#ifndef EMBER_APPLICATION_HAS_CALCULATE_SMACS_HANDLER
WEAK(void emberCalculateSmacsHandler(EmberStatus status,
                                     EmberSmacData* initiatorSmac,
                                     EmberSmacData* responderSmac))
{
  (void)status;
  (void)initiatorSmac;
  (void)responderSmac;
}
#endif

#ifndef EMBER_APPLICATION_HAS_GENERATE_CBKE_KEYS_HANDLER
WEAK(void emberGenerateCbkeKeysHandler(EmberStatus status,
                                       EmberPublicKeyData *ephemeralPublicKey))
{
  (void)status;
  (void)ephemeralPublicKey;
}
#endif

#ifndef EMBER_APPLICATION_HAS_CALCULATE_SMACS_HANDLER_283K1
WEAK(void emberCalculateSmacsHandler283k1(EmberStatus status,
                                          EmberSmacData *initiatorSmac,
                                          EmberSmacData *responderSmac))
{
  (void)status;
  (void)initiatorSmac;
  (void)responderSmac;
}
#endif

#ifndef EMBER_APPLICATION_HAS_GENERATE_CBKE_KEYS_HANDLER_283K1
WEAK(void emberGenerateCbkeKeysHandler283k1(EmberStatus status,
                                            EmberPublicKey283k1Data *ephemeralPublicKey))
{
  (void)status;
  (void)ephemeralPublicKey;
}
#endif

#ifndef EMBER_APPLICATION_HAS_DSA_SIGN_HANDLER
WEAK(void emberDsaSignHandler(EmberStatus status,
                              EmberMessageBuffer signedMessage))
{
  (void)status;
  (void)signedMessage;
}
#endif

#ifndef EMBER_APPLICATION_HAS_DSA_VERIFY_HANDLER
WEAK(void emberDsaVerifyHandler(EmberStatus status))
{
  (void)status;
}
#endif

#ifndef EMBER_APPLICATION_HAS_RTOS_IDLE_HANDLER
WEAK(bool emberRtosIdleHandler(uint32_t *idleTimeMs))
{
  (void)idleTimeMs;

  return false;
}
#endif

#ifndef EMBER_APPLICATION_HAS_RTOS_STACK_WAKEUP_ISR_HANDLER
WEAK(void emberRtosStackWakeupIsrHandler(void))
{
}
#endif

#ifndef EMBER_APPLICATION_HAS_DUTY_CYCLE_HANDLER
WEAK(void emberDutyCycleHandler(uint8_t channelPage,
                                uint8_t channel,
                                EmberDutyCycleState state))
{
  (void)channelPage;
  (void)channel;
  (void)state;
}
#endif
#ifndef EMBER_APPLICATION_HAS_AF_COUNTER_HANDLER
WEAK(void emberAfCounterHandler(EmberCounterType type, EmberCounterInfo info))
{
  (void)type;
  (void)info;
}
#endif

#ifndef EMBER_APPLICATION_HAS_BUFFER_MARKER
WEAK(void emberMarkBuffersHandler())
{
}
#endif

#ifndef EMBER_AF_PLUGIN_PACKET_HANDOFF
  #if defined(EMBER_CALLBACK_INCOMING_PACKET_FILTER) \
  || defined(EMBER_CALLBACK_OUTGOING_PACKET_FILTER)
    #error "Use of the Packet Filter Callbacks requires the Packet Handoff Plugin"
  #endif
WEAK(EmberPacketAction emberPacketHandoffIncomingHandler(EmberZigbeePacketType packetType,
                                                         EmberMessageBuffer packetBuffer,
                                                         uint8_t index,
                                                         void *data))
{
  (void)packetType;
  (void)packetBuffer;
  (void)index;
  (void)data;

  return EMBER_ACCEPT_PACKET;
}

WEAK(EmberPacketAction emberPacketHandoffOutgoingHandler(EmberZigbeePacketType packetType,
                                                         EmberMessageBuffer packetBuffer,
                                                         uint8_t index,
                                                         void *data))
{
  (void)packetType;
  (void)packetBuffer;
  (void)index;
  (void)data;

  return EMBER_ACCEPT_PACKET;
}
#endif

#endif /* __NCP_CONFIG__ */

#if (defined(EMBER_AF_NCP) || defined(SL_CATALOG_ZIGBEE_NCP_FRAMEWORK_PRESENT) || defined(EMBER_TEST))
// The buffer to host tag map needs to keep track of messages that we send
// from the host. In handleSendCommand(), there are three different types of
// messages that consume a sli_legacy_buffer_manager_buffer_to_host_tag_map entry:
// a) unicasts, which are limited by sli_zigbee_max_aps_unicast_messages
// b) broadcasts, which are limited by sli_zigbee_broadcast_table_size
// c) multicasts, which are limited by sli_zigbee_broadcast_table_size
// To give enough space for all message types, we size the
// sli_legacy_buffer_manager_buffer_to_host_tag_map buffer to be of size sli_zigbee_max_aps_unicast_messages +
// sli_zigbee_broadcast_table_size.
#define TAG_MAP_EXTRA_ENTRIES 5

#define BUFFER_TO_HOST_TAG_MAP_SIZE  (EMBER_APS_UNICAST_MESSAGE_COUNT \
                                      + EMBER_BROADCAST_TABLE_SIZE * NUM_MULTI_PAN_FORKS)

EmberTagMapEntry sli_legacy_buffer_manager_buffer_to_host_tag_map[BUFFER_TO_HOST_TAG_MAP_SIZE]; //XXXJAR temp
uint16_t sli_legacy_buffer_manager_buffer_to_host_tag_map_size = BUFFER_TO_HOST_TAG_MAP_SIZE;

uint8_t customMacFilterTableSize = EMBER_CUSTOM_MAC_FILTER_TABLE_SIZE;
EmberMacFilterMatchData sli_zigbee_custom_mac_filter_match_list_data[EMBER_CUSTOM_MAC_FILTER_TABLE_SIZE];

#endif
// Stubs that apply to both SoC and NCP

// This whole if block can be removed once UC_BUILD is removed
#ifndef UC_BUILD
#ifndef EMBER_AF_PLUGIN_ZIGBEE_EVENT_LOGGER
#include "stack/framework/zigbee-event-logger-stub-gen.c"
#endif // !EMBER_AF_PLUGIN_ZIGBEE_EVENT_LOGGER
#endif // UC_BUILD

// The following function is called for a Multi-MAC end device to allow the user configuration of
// the device to update channel mask for the scenario where a rejoin is initated due to end device
// timeout event. Based on the Multi-MAC end device configuration this call is expected to update
// the mask so that the rejoin interface will be selected. As per the SE 1.4 errata, the
// "Multi-MAC Selection" end device can change the rejoin interface (this is default) where as the
// Multi-MAC Joining end devices shall not, hence supply the channel mask based on the joined interface.
extern uint8_t emberGetLogicalChannel(void);
WEAK(void emberUpdateMultiMacRejoinChannelMaskForSelectionOrJoiningDevice(uint32_t *rejoinChannelMask))
{
#ifdef SL_CATALOG_ZIGBEE_PHY_2_4_SUBGHZ_JOINING_END_DEVICE_PRESENT
  *rejoinChannelMask = PG_CH_BITMASK32(emberGetLogicalChannel());
#endif
}
