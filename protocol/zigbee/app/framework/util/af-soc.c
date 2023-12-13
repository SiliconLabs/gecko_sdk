/***************************************************************************//**
 * @file af-soc.c
 * @brief SoC-specific APIs and infrastructure code.
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

#include "af.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#include "app/framework/util/af-main.h"
#include "app/framework/util/attribute-storage.h"
#include "app/framework/util/common.h"
#include "app/util/security/security.h"
#include "app/util/zigbee-framework/zigbee-device-library.h"
#include "stack/include/source-route.h"
#include "stack/config/ember-configuration-defaults.h"

#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
#include "fragmentation.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_FORM_AND_JOIN_PRESENT
#include "app/util/common/form-and-join.h"
#endif

#if (defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT) && !defined(EMBER_TEST))
#define EXTENDED_RESET_INFO
#include "cortexm3/diagnostic.h"
#endif // !defined(EMBER_TEST)

//------------------------------------------------------------------------------
// Forward declarations

//------------------------------------------------------------------------------
// Internal callbacks

void sli_zigbee_af_initCallback(uint8_t init_level)
{
  (void)init_level;

  emberAfCorePrintln("Reset info: 0x%x (%p)",
                     halGetResetInfo(),
                     halGetResetString());

  // This will initialize the stack of networks maintained by the framework,
  // including setting the default network.
  sli_zigbee_af_initializeNetworkIndexStack();

  // Initialize messageSentCallbacks table
  sli_zigbee_af_initialize_message_sent_callback_array();

  emberAfEndpointConfigure();

  // The address cache needs to be initialized and used with the source routing
  // code for the trust center to operate properly.
  securityAddressCacheInit(EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE,                     // offset
                           EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE); // size

  sli_zigbee_af_network_security_init();

  // Set the manufacturing code. This is defined by ZigBee document 053874r10
  // Ember's ID is 0x1002 and is the default, but this can be overridden in App Builder.
  emberSetManufacturerCode(EMBER_AF_MANUFACTURER_CODE);

  emberSetMaximumIncomingTransferSize(EMBER_AF_INCOMING_BUFFER_LENGTH);
  emberSetMaximumOutgoingTransferSize(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);
  emberSetTxPowerMode(EMBER_AF_TX_POWER_MODE);

  (void)emberSetRadioIeee802154CcaMode(EMBER_RADIO_802154_CCA_MODE);
}

EmberZdoStatus sli_zigbee_af_remote_set_binding_callback(EmberBindingTableEntry *entry)
{
  EmberZdoStatus status = EMBER_ZDP_TABLE_FULL;
#if (EMBER_BINDING_TABLE_SIZE > 0)
  EmberStatus setStatus;
  EmberBindingTableEntry candidate;
  uint8_t i;

  // If we receive a bind request for the Key Establishment cluster and we are
  // not the trust center, then we are doing partner link key exchange.  We
  // don't actually have to create a binding.
  if (emberAfGetNodeId() != EMBER_TRUST_CENTER_NODE_ID
      && entry->clusterId == ZCL_KEY_ESTABLISHMENT_CLUSTER_ID) {
    status = emberAfPartnerLinkKeyExchangeRequestCallback(entry->identifier);
    goto kickout;
  }

  // ask the application if current binding request is allowed or not
  status = emberAfRemoteSetBindingPermissionCallback(entry) == EMBER_SUCCESS ? EMBER_ZDP_SUCCESS : EMBER_ZDP_NOT_AUTHORIZED;
  if (status == EMBER_ZDP_SUCCESS) {
    // For all other requests, we search the binding table for an unused entry
    // and store the new entry there if we find one.
    for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
      if (emberGetBinding(i, &candidate) == EMBER_SUCCESS
          && candidate.type == EMBER_UNUSED_BINDING) {
        setStatus = emberSetBinding(i, entry);
        status = setStatus == EMBER_SUCCESS ? EMBER_ZDP_SUCCESS // binding set
                 : (setStatus == EMBER_BINDING_IS_ACTIVE ? EMBER_ZDP_NOT_PERMITTED // selected index is active
                    : EMBER_ZDP_TABLE_FULL); // report full for any other failure
        goto kickout;
      }
    }
    // If we get here, we didn't find an empty table slot, so table is full.
    status = EMBER_ZDP_TABLE_FULL;
  }

  kickout:
#endif
  return status;
}

EmberZdoStatus sli_zigbee_af_remote_delete_binding_callback(uint8_t index)
{
  EmberStatus deleteStatus;
  EmberZdoStatus status;

  // ask the application if current binding request is allowed or not
  status = emberAfRemoteDeleteBindingPermissionCallback(index) == EMBER_SUCCESS
           ? EMBER_ZDP_SUCCESS
           : EMBER_ZDP_NOT_AUTHORIZED;
  if (status == EMBER_SUCCESS) {
    deleteStatus = emberDeleteBinding(index);
    status = deleteStatus == EMBER_SUCCESS ? EMBER_ZDP_SUCCESS // binding deleted
             : (deleteStatus == EMBER_BINDING_IS_ACTIVE ? EMBER_ZDP_NOT_PERMITTED //selected index is active
                : EMBER_ZDP_NO_ENTRY); // report no entry for any other failure
    emberAfZdoPrintln("delete binding: %x %x", index, status);
  }

  return status;
}

void sli_zigbee_af_incoming_message_callback(EmberIncomingMessageType type,
                                             EmberApsFrame *apsFrame,
                                             EmberMessageBuffer message)
{
  uint8_t lastHopLqi;
  int8_t lastHopRssi;

  emberGetLastHopLqi(&lastHopLqi);
  emberGetLastHopRssi(&lastHopRssi);

  sli_zigbee_af_incoming_message_handler(type,
                                         apsFrame,
                                         lastHopLqi,
                                         lastHopRssi,
                                         sli_legacy_buffer_manager_get_buffer_length(message),
                                         sli_legacy_buffer_manager_get_buffer_pointer(message));
}

extern void sli_zigbee_af_message_sent(EmberOutgoingMessageType type,
                                       uint16_t indexOrDestination,
                                       EmberApsFrame *apsFrame,
                                       EmberMessageBuffer message,
                                       EmberStatus status);

// Called when a message we sent is acked by the destination or when an
// ack fails to arrive after several retransmissions.
void sli_zigbee_af_message_sent_callback(EmberOutgoingMessageType type,
                                         uint16_t indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         EmberMessageBuffer message,
                                         EmberStatus status)
{
  uint8_t* messageContents = sli_legacy_buffer_manager_get_buffer_pointer(message);
  uint8_t messageLength = sli_legacy_buffer_manager_get_buffer_length(message);
  uint16_t messageTag;

#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
  // This call if returns true, ends up calling
  // sli_zigbee_af_fragmentation_message_sent_handler() when the last fragment was received.
  if (sli_zigbee_af_fragmentation_message_sent(apsFrame, status)) {
    return;
  }
#endif //SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT

  emberConcentratorNoteDeliveryFailure(type, status);

  messageTag = sli_zigbee_af_calculate_message_tag_hash(messageContents, messageLength);

  sli_zigbee_af_message_sent_handler(type,
                                     indexOrDestination,
                                     apsFrame,
                                     status,
                                     messageLength,
                                     messageContents,
                                     messageTag);

  // Generated dispatcher
  sli_zigbee_af_message_sent(type,
                             indexOrDestination,
                             apsFrame,
                             message,
                             status);
}

#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
void sli_zigbee_af_fragmentation_message_sent_handler(EmberOutgoingMessageType type,
                                                      uint16_t indexOrDestination,
                                                      EmberApsFrame *apsFrame,
                                                      uint8_t *buffer,
                                                      uint16_t bufLen,
                                                      EmberStatus status,
                                                      uint16_t messageTag)
{
  EmberMessageBuffer message = emberFillLinkedBuffers(buffer, bufLen);

  // the fragmented message is no longer in process
  emberAfDebugPrintln("%pend.", "Fragmentation:");
  sli_zigbee_af_message_sent_handler(type,
                                     indexOrDestination,
                                     apsFrame,
                                     status,
                                     bufLen,
                                     buffer,
                                     messageTag);

  // Generated dispatcher
  sli_zigbee_af_message_sent(type,
                             indexOrDestination,
                             apsFrame,
                             message,
                             status);

  // EMZIGBEE-4437: setting back the buffers to the original in case someone set
  // that to something else.
  emberAfSetExternalBuffer(appResponseData,
                           EMBER_AF_RESPONSE_BUFFER_LEN,
                           &appResponseLength,
                           &emberAfResponseApsFrame);
}
#endif // SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT

//------------------------------------------------------------------------------
// Public APIs

void emberAfGetMfgString(uint8_t* returnData)
{
  halCommonGetMfgToken(returnData, TOKEN_MFG_STRING);
}

EmberNodeId emberAfGetNodeId(void)
{
  return emberGetNodeId();
}

EmberPanId emberAfGetPanId(void)
{
  return emberGetPanId();
}

EmberNetworkStatus emberAfNetworkState(void)
{
  return emberNetworkState();
}

uint8_t emberAfGetRadioChannel(void)
{
  return emberGetRadioChannel();
}

uint8_t emberAfGetBindingIndex(void)
{
  return emberGetBindingIndex();
}

uint8_t emberAfGetStackProfile(void)
{
  return emberStackProfile();
}

uint8_t emberAfGetAddressIndex(void)
{
  EmberEUI64 longId;
  EmberEUI64 longIdIterator;
  uint8_t i;

  if ((emberGetSenderEui64(longId)) == EMBER_SUCCESS) {
    for (i = 0; i < EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE; i++) {
      emberGetAddressTableRemoteEui64(i, longIdIterator);
      if (MEMCOMPARE(longIdIterator, longId, EUI64_SIZE) == 0) {
        return i;
      }
    }
  } else {
    EmberNodeId nodeId = emberGetSender();
    if (nodeId == EMBER_NULL_NODE_ID) {
      return EMBER_NULL_ADDRESS_TABLE_INDEX;
    }
    for (i = 0; i < EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE; i++) {
      if (emberGetAddressTableRemoteNodeId(i) == nodeId) {
        return i;
      }
    }
  }
  return EMBER_NULL_ADDRESS_TABLE_INDEX;
}

uint8_t emberGetEndpoint(uint8_t index)
{
  return sli_zigbee_af_get_endpoint(index);
}

// must return the endpoint desc of the endpoint specified
bool emberGetEndpointDescription(uint8_t endpoint,
                                 EmberEndpointDescription *result)
{
  return sli_zigbee_af_get_endpoint_description(endpoint, result);
}

// must return the clusterId at listIndex in the list specified for the
// endpoint specified
uint16_t emberGetEndpointCluster(uint8_t endpoint,
                                 EmberClusterListId listId,
                                 uint8_t listIndex)
{
  return sli_zigbee_af_get_endpoint_cluster(endpoint, listId, listIndex);
}

void emberAfGetEui64(EmberEUI64 returnEui64)
{
  MEMMOVE(returnEui64, emberGetEui64(), EUI64_SIZE);
}

EmberStatus emberAfGetNetworkParameters(EmberNodeType* nodeType,
                                        EmberNetworkParameters* parameters)
{
  emberGetNetworkParameters(parameters);
  return emberGetNodeType(nodeType);
}

EmberStatus emberAfGetNodeType(EmberNodeType *nodeType)
{
  return emberGetNodeType(nodeType);
}

uint8_t emberAfGetSecurityLevel(void)
{
  return emberSecurityLevel();
}

uint8_t emberAfGetKeyTableSize(void)
{
  return EMBER_KEY_TABLE_SIZE;
}

uint8_t emberAfGetBindingTableSize(void)
{
  return EMBER_BINDING_TABLE_SIZE;
}

uint8_t emberAfGetAddressTableSize(void)
{
  return EMBER_ADDRESS_TABLE_SIZE;
}

uint8_t emberAfGetChildTableSize(void)
{
  return EMBER_CHILD_TABLE_SIZE;
}

uint8_t emberAfGetNeighborTableSize(void)
{
  return EMBER_NEIGHBOR_TABLE_SIZE;
}

uint8_t emberAfGetRouteTableSize(void)
{
  return EMBER_ROUTE_TABLE_SIZE;
}

uint8_t emberAfGetSleepyMulticastConfig(void)
{
  return EMBER_SEND_MULTICASTS_TO_SLEEPY_ADDRESS;
}

EmberStatus emberAfGetSourceRouteTableEntry(
  uint8_t index,
  EmberNodeId *destination,
  uint8_t *closerIndex)
{
  return emberGetSourceRouteTableEntry(index,
                                       destination,
                                       closerIndex);
}

uint8_t emberAfGetSourceRouteTableTotalSize(void)
{
  return emberGetSourceRouteTableTotalSize();
}

uint8_t emberAfGetSourceRouteTableFilledSize(void)
{
  return emberGetSourceRouteTableFilledSize();
}

EmberStatus emberAfGetChildData(uint8_t index,
                                EmberChildData *childData)
{
  return emberGetChildData(index,
                           childData);
}

//------------------------------------------------------------------------------
// Internal APIs

uint8_t sli_zigbee_af_get_packet_buffer_free_count(void)

{
  return sli_legacy_buffer_manager_buffer_bytes_remaining() / PACKET_BUFFER_SIZE;
}

uint8_t sli_zigbee_af_get_packet_buffer_total_count(void)
{
  return sli_legacy_buffer_manager_buffer_bytes_total() / PACKET_BUFFER_SIZE;
}

uint8_t emberAfGetOpenNetworkDurationSec(void)
{
  return sli_zigbee_get_permit_joining_remaining_duration_sec();
}

void sli_zigbee_af_cli_version_command(void)
{
  sli_zigbee_af_parse_and_print_version(emberVersion);
}

void sli_zigbee_af_print_ezsp_endpoint_flags(uint8_t endpoint)
{
  // Not applicable for SOC
}

uint8_t emberGetEndpointCount(void)
{
  return emberAfEndpointCount();
}
