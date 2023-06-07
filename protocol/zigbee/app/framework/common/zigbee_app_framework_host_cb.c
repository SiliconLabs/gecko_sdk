/*****************************************************************************/
/**
 * Copyright 2020 Silicon Laboratories, Inc.
 *
 *****************************************************************************/
//
// EMZIGBEE-7387: modify "gen_stack_callback_dispatchers.py" to generate this file
// as well as zigbee_stack_callback_dispatcher jinja templates to support UC host
// *** Generated file. Do not edit! ***
//

#include PLATFORM_HEADER
#include "zigbee_stack_callback_dispatcher.h"
#include "zigbee_app_framework_callback.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "af.h"
#else
#define emberAfPushCallbackNetworkIndex()
#define emberAfPopNetworkIndex()
#endif

#if defined(EMBER_AF_PRINT_SECURITY)  || defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT)
// Corresponds to the EmberJoinDecision status codes
static const char * joinDecisionText[] = {
  EMBER_JOIN_DECISION_STRINGS
};

// Corresponds to the EmberDeviceUpdate status codes
static const char * deviceUpdateText[] = {
  EMBER_DEVICE_UPDATE_STRINGS
};

#endif // EMBER_AF_PRINT_APP

// -----------------------------------------------------------------------------
// A callback invoked when receiving a message.
void ezspIncomingMessageHandler(
  // Incoming message type
  EmberIncomingMessageType type,
  // The APS frame from the incoming message.
  EmberApsFrame *apsFrame,
  // The link quality from the node that last relayed the message.
  uint8_t lastHopLqi,
  // The energy level (in units of dBm) observed during the reception.
  int8_t lastHopRssi,
  // The sender of the message.
  EmberNodeId sender,
  // The index of a binding that matches the message or 0xFF if there is no
  // matching binding.
  uint8_t bindingIndex,
  // The index of the entry in the address table that matches the sender of
  // the message or 0xFF if there is no matching entry.
  uint8_t addressIndex,
  // The length of the messageContents parameter in bytes.
  uint8_t messageLength,
  // The incoming message.
  uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zb_af_incoming_message(type, apsFrame, lastHopLqi, lastHopRssi, sender, bindingIndex, addressIndex, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// A callback invoked when a messageSend has been tried by the stack.

WEAK(void sli_zigbee_af_message_sent_callback(EmberOutgoingMessageType type,
                                              uint16_t indexOrDestination,
                                              EmberApsFrame *apsFrame,
                                              uint8_t messageTag,
                                              EmberStatus status,
                                              uint8_t messageLength,
                                              uint8_t *messageContents))
{
  sli_zigbee_af_message_sent(type,
                             indexOrDestination,
                             apsFrame,
                             messageTag,
                             status,
                             messageLength,
                             messageContents);
}

void ezspMessageSentHandler(
  // The type of message sent.
  EmberOutgoingMessageType type,
  // The destination to which the message was sent, for direct unicasts, or
  // the address table or binding index for other unicasts. The value is
  // unspecified for multicasts and broadcasts.
  uint16_t indexOrDestination,
  // The APS frame for the message.
  EmberApsFrame *apsFrame,
  // The value supplied by the Host in the ezspSendUnicast,
  // ezspSendBroadcast or ezspSendMulticast command.
  uint8_t messageTag,
  // An EmberStatus value of EMBER_SUCCESS if an ACK was received from the
  // destination or EMBER_DELIVERY_FAILED if no ACK was received.
  EmberStatus status,
  // The length of the messageContents parameter in bytes.
  uint8_t messageLength,
  // The unicast message supplied by the Host. The message contents are only
  // included here if the decision for the messageContentsInCallback policy
  // is messageTagAndContentsInCallback.
  uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_message_sent_callback(type, indexOrDestination, apsFrame, messageTag, status, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfZigbeeKeyEstablishmentCallback
WEAK(void emberAfZigbeeKeyEstablishmentCallback(
       // This is the IEEE address of the partner that the device successfully
       // established a key with. This value is all zeros on a failure.
       EmberEUI64 partner,
       // This is the status indicating what was established or why the key
       // establishment failed.
       EmberKeyStatus status))
{
  (void)partner;
  (void)status;
}

// This is a callback that indicates the success or failure of an attempt to
// establish a key with a partner device.
void ezspZigbeeKeyEstablishmentHandler(
  // This is the IEEE address of the partner that the device successfully
  // established a key with. This value is all zeros on a failure.
  EmberEUI64 partner,
  // This is the status indicating what was established or why the key
  // establishment failed.
  EmberKeyStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_zigbee_key_establishment(partner, status);
  emberAfZigbeeKeyEstablishmentCallback(partner, status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfGpepIncomingMessageCallback
WEAK(void emberAfGpepIncomingMessageCallback(
       // The status of the GPDF receive.
       EmberStatus status,
       // The gpdLink value of the received GPDF.
       uint8_t gpdLink,
       // The GPDF sequence number.
       uint8_t sequenceNumber,
       // The address of the source GPD.
       EmberGpAddress *addr,
       // The security level of the received GPDF.
       EmberGpSecurityLevel gpdfSecurityLevel,
       // The securityKeyType used to decrypt/authenticate the incoming GPDF.
       EmberGpKeyType gpdfSecurityKeyType,
       // Whether the incoming GPDF had the auto-commissioning bit set.
       bool autoCommissioning,
       // Bidirectional information represented in bitfields, where bit0 holds
       // the rxAfterTx of incoming gpdf and bit1 holds if tx queue is available
       // for outgoing gpdf.
       uint8_t bidirectionalInfo,
       // The security frame counter of the incoming GDPF.
       uint32_t gpdSecurityFrameCounter,
       // The gpdCommandId of the incoming GPDF.
       uint8_t gpdCommandId,
       // The received MIC of the GPDF.
       uint32_t mic,
       // The proxy table index of the corresponding proxy table entry to the
       // incoming GPDF.
       uint8_t proxyTableIndex,
       // The length of the GPD command payload.
       uint8_t gpdCommandPayloadLength,
       // The GPD command payload.
       uint8_t *gpdCommandPayload))
{
  (void)status;
  (void)gpdLink;
  (void)sequenceNumber;
  (void)addr;
  (void)gpdfSecurityLevel;
  (void)gpdfSecurityKeyType;
  (void)autoCommissioning;
  (void)bidirectionalInfo;
  (void)gpdSecurityFrameCounter;
  (void)gpdCommandId;
  (void)mic;
  (void)proxyTableIndex;
  (void)gpdCommandPayloadLength;
  (void)gpdCommandPayload;
}

// A callback invoked by the ZigBee GP stack when a GPDF is received.
void ezspGpepIncomingMessageHandler(
  // The status of the GPDF receive.
  EmberStatus status,
  // The gpdLink value of the received GPDF.
  uint8_t gpdLink,
  // The GPDF sequence number.
  uint8_t sequenceNumber,
  // The address of the source GPD.
  EmberGpAddress *addr,
  // The security level of the received GPDF.
  EmberGpSecurityLevel gpdfSecurityLevel,
  // The securityKeyType used to decrypt/authenticate the incoming GPDF.
  EmberGpKeyType gpdfSecurityKeyType,
  // Whether the incoming GPDF had the auto-commissioning bit set.
  bool autoCommissioning,
  // Bidirectional information represented in bitfields, where bit0 holds
  // the rxAfterTx of incoming gpdf and bit1 holds if tx queue is available
  // for outgoing gpdf.
  uint8_t bidirectionalInfo,
  // The security frame counter of the incoming GDPF.
  uint32_t gpdSecurityFrameCounter,
  // The gpdCommandId of the incoming GPDF.
  uint8_t gpdCommandId,
  // The received MIC of the GPDF.
  uint32_t mic,
  // The proxy table index of the corresponding proxy table entry to the
  // incoming GPDF.
  uint8_t proxyTableIndex,
  // The length of the GPD command payload.
  uint8_t gpdCommandPayloadLength,
  // The GPD command payload.
  uint8_t *gpdCommandPayload)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_gpep_incoming_message(status, gpdLink, sequenceNumber, addr, gpdfSecurityLevel, gpdfSecurityKeyType, autoCommissioning, bidirectionalInfo, gpdSecurityFrameCounter, gpdCommandId, mic, proxyTableIndex, gpdCommandPayloadLength, gpdCommandPayload);
  emberAfGpepIncomingMessageCallback(status, gpdLink, sequenceNumber, addr, gpdfSecurityLevel, gpdfSecurityKeyType, autoCommissioning, bidirectionalInfo, gpdSecurityFrameCounter, gpdCommandId, mic, proxyTableIndex, gpdCommandPayloadLength, gpdCommandPayload);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfDGpSentCallback
WEAK(void emberAfDGpSentCallback(
       // An EmberStatus value indicating success or the reason for failure.
       EmberStatus status,
       // The handle of the GPDF.
       uint8_t gpepHandle))
{
  (void)status;
  (void)gpepHandle;
}

// A callback to the GP endpoint to indicate the result of the GPDF
// transmission.
void ezspDGpSentHandler(
  // An EmberStatus value indicating success or the reason for failure.
  EmberStatus status,
  // The handle of the GPDF.
  uint8_t gpepHandle)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_d_gp_sent(status, gpepHandle);
  emberAfDGpSentCallback(status, gpepHandle);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfStackStatusCallback
WEAK(void emberAfStackStatusCallback(
       // Stack status. One of the following: EMBER_NETWORK_UP,
       // EMBER_NETWORK_DOWN, EMBER_JOIN_FAILED, EMBER_MOVE_FAILED
       EmberStatus status))
{
  (void)status;
}

// A callback invoked when the status of the stack changes. If the status
// parameter equals EMBER_NETWORK_UP, then the getNetworkParameters command can
// be called to obtain the new network parameters. If any of the parameters are
// being stored in nonvolatile memory by the Host, the stored values should be
// updated.
void ezspStackStatusHandler(
  // Stack status. One of the following: EMBER_NETWORK_UP,
  // EMBER_NETWORK_DOWN, EMBER_JOIN_FAILED, EMBER_MOVE_FAILED
  EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_stack_status(status);
  emberAfStackStatusCallback(status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfEnergyScanResultCallback
WEAK(void emberAfEnergyScanResultCallback(
       // The 802.15.4 channel number that was scanned.
       uint8_t channel,
       // The maximum RSSI value found on the channel.
       int8_t maxRssiValue))
{
  (void)channel;
  (void)maxRssiValue;
}

// Reports the result of an energy scan for a single channel. The scan is not
// complete until the scanCompleteHandler callback is called.
void ezspEnergyScanResultHandler(
  // The 802.15.4 channel number that was scanned.
  uint8_t channel,
  // The maximum RSSI value found on the channel.
  int8_t maxRssiValue)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_energy_scan_result(channel, maxRssiValue);
  emberAfEnergyScanResultCallback(channel, maxRssiValue);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfNetworkFoundCallback
WEAK(void emberAfNetworkFoundCallback(
       // The parameters associated with the network found.
       EmberZigbeeNetwork *networkFound,
       // The link quality indication of the network found.
       uint8_t lqi,
       // The received signal strength indication of the network found.
       int8_t rssi))
{
  (void)networkFound;
  (void)lqi;
  (void)rssi;
}

// Reports that a network was found as a result of a prior call to startScan.
// Gives the network parameters useful for deciding which network to join.
void ezspNetworkFoundHandler(
  // The parameters associated with the network found.
  EmberZigbeeNetwork *networkFound,
  // The link quality indication of the network found.
  uint8_t lqi,
  // The received signal strength indication of the network found.
  int8_t rssi)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_network_found(networkFound, lqi, rssi);
  emberAfNetworkFoundCallback(networkFound, lqi, rssi);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfScanCompleteCallback
WEAK(void emberAfScanCompleteCallback(
       // The channel on which the current error occurred. Undefined for the case
       // of EMBER_SUCCESS.
       uint8_t channel,
       // The error condition that occurred on the current channel. Value will be
       // EMBER_SUCCESS when the scan has completed.
       EmberStatus status))
{
  (void)channel;
  (void)status;
}

// Returns the status of the current scan of type EMBER_ENERGY_SCAN or
// EMBER_ACTIVE_SCAN. EMBER_SUCCESS signals that the scan has completed. Other
// error conditions signify a failure to scan on the channel specified.
void ezspScanCompleteHandler(
  // The channel on which the current error occurred. Undefined for the case
  // of EMBER_SUCCESS.
  uint8_t channel,
  // The error condition that occurred on the current channel. Value will be
  // EMBER_SUCCESS when the scan has completed.
  EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_scan_complete(channel, status);
  emberAfScanCompleteCallback(channel, status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfUnusedPanIdFoundCallback
WEAK(void emberAfUnusedPanIdFoundCallback(
       // The unused panID which has been found.
       EmberPanId panId,
       // The channel that the unused panID was found on.
       uint8_t channel))
{
  (void)panId;
  (void)channel;
}

// This function returns an unused panID and channel pair found via the find
// unused panId scan procedure.
void ezspUnusedPanIdFoundHandler(
  // The unused panID which has been found.
  EmberPanId panId,
  // The channel that the unused panID was found on.
  uint8_t channel)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_unused_pan_id_found(panId, channel);
  emberAfUnusedPanIdFoundCallback(panId, channel);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfScanErrorCallback
WEAK(void emberAfScanErrorCallback(
       // The error status of a scan
       EmberStatus status))
{
  (void)status;
}

// scanErrorHandler
void emberScanErrorHandler(
  // The error status of a scan
  EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_scan_error(status);
  emberAfScanErrorCallback(status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfSwitchNetworkKeyCallback
WEAK(void emberAfSwitchNetworkKeyCallback(
       // The sequence number of the new network key.
       uint8_t sequenceNumber))
{
  (void)sequenceNumber;
}

// A callback to inform the application that the Network Key has been updated
// and the node has been switched over to use the new key. The actual key being
// used is not passed up, but the sequence number is.
void ezspSwitchNetworkKeyHandler(
  // The sequence number of the new network key.
  uint8_t sequenceNumber)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_switch_network_key(sequenceNumber);
  emberAfSwitchNetworkKeyCallback(sequenceNumber);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfChildJoinCallback
WEAK(void emberAfChildJoinCallback(
       // The index of the child of interest.
       uint8_t index,
       // True if the child is joining. False the child is leaving.
       bool joining))
{
  (void)index;
  (void)joining;
}

// Indicates that a child has joined or left.
void ezspChildJoinHandler(
  // The index of the child of interest.
  uint8_t index,
  // True if the child is joining. False the child is leaving.
  bool joining,
  // The node ID of the child.
  EmberNodeId childId,
  // The EUI64 of the child.
  EmberEUI64 childEui64,
  // The node type of the child.
  EmberNodeType childType)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_child_join(index, joining, childId, childEui64, childType);
  emberAfChildJoinCallback(index, joining);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfDutyCycleCallback
WEAK(void emberAfDutyCycleCallback(
       // The channel page whose duty cycle state has changed.
       uint8_t channelPage,
       // The channel number whose duty cycle state has changed.
       uint8_t channel,
       // The current duty cycle state.
       EmberDutyCycleState state))
{
  (void)channelPage;
  (void)channel;
  (void)state;
}

// Callback fires when the duty cycle state has changed
void ezspDutyCycleHandler(
  // The channel page whose duty cycle state has changed.
  uint8_t channelPage,
  // The channel number whose duty cycle state has changed.
  uint8_t channel,
  // The current duty cycle state.
  EmberDutyCycleState state,
  // The total number of connected end devices that are being monitored for
  // duty cycle.
  uint8_t totalDevices,
  // Consumed duty cycles of end devices that are being monitored. The first
  // entry always be the local stack's nodeId, and thus the total aggregate
  // duty cycle for the device.
  EmberPerDeviceDutyCycle *arrayOfDeviceDutyCycles)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_duty_cycle(channelPage, channel, state, totalDevices, arrayOfDeviceDutyCycles);
  emberAfDutyCycleCallback(channelPage, channel, state);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfPollCompleteCallback
WEAK(void emberAfPollCompleteCallback(
       // An EmberStatus value: EMBER_SUCCESS - Data was received in response to
       // the poll. EMBER_MAC_NO_DATA - No data was pending.
       // EMBER_DELIVERY_FAILED - The poll message could not be sent.
       // EMBER_MAC_NO_ACK_RECEIVED - The poll message was sent but not
       // acknowledged by the parent.
       EmberStatus status))
{
  (void)status;
}

// Indicates the result of a data poll to the parent of the local node.
void ezspPollCompleteHandler(
  // An EmberStatus value: EMBER_SUCCESS - Data was received in response to
  // the poll. EMBER_MAC_NO_DATA - No data was pending.
  // EMBER_DELIVERY_FAILED - The poll message could not be sent.
  // EMBER_MAC_NO_ACK_RECEIVED - The poll message was sent but not
  // acknowledged by the parent.
  EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_poll_complete(status);
  emberAfPollCompleteCallback(status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public callback emberAfDsaSignCallback
// The handler that returns the results of the signing operation. On success,
// the signature will be appended to the original message (including the
// signature type indicator that replaced the startIndex field for the signing)
// and both are returned via this callback.
WEAK(void emberAfDsaSignCallback(
       // The result of the DSA signing operation.
       EmberStatus status,
       // The length of message.
       uint8_t messageLength,
       // The message and attached which includes the original message and the
       // appended signature.
       uint8_t *messageContents))
{
  (void)status;
  (void)messageLength;
  (void)messageContents;
}

// Indicates the completion of a DSA signature operation.
void ezspDsaSignHandler(
  //Status of DSA sign operation.
  EmberStatus status,
  // length of the message
  uint8_t messageLength,
  // message content
  uint8_t *message)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_dsa_sign(status, messageLength, message);
  emberAfDsaSignCallback(status, messageLength, message);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------

void ezspTrustCenterJoinHandler(EmberNodeId newNodeId,
                                EmberEUI64 newNodeEui64,
                                EmberDeviceUpdate status,
                                EmberJoinDecision policyDecision,
                                EmberNodeId parentOfNewNode)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_trust_center_join(newNodeId,
                                  newNodeEui64,
                                  status,
                                  policyDecision,
                                  parentOfNewNode);
  // Allow users of the framework an opportunity to see this notification.
  emberAfTrustCenterJoinCallback(newNodeId,
                                 newNodeEui64,
                                 parentOfNewNode,
                                 status,
                                 policyDecision);
  emberAfSecurityPrintln("Trust Center Join Handler: status = %p, decision = %p (%x), shortid 0x%2x",
                         deviceUpdateText[status],
                         joinDecisionText[policyDecision],
                         policyDecision,
                         newNodeId);
  emberAfSecurityFlush();
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfZllTouchLinkTargetCallback
WEAK(void emberAfZllTouchLinkTargetCallback(
       // Return: Information about the network.
       const EmberZllNetwork *networkInfo))
{
  (void)networkInfo;
}

// This call is fired when the device is a target of a touch link.
void ezspZllTouchLinkTargetHandler(
  // Return: Information about the network.
  EmberZllNetwork *networkInfo)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_zll_touch_link_target(networkInfo);
  emberAfZllTouchLinkTargetCallback(networkInfo);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfStackTokenChangedCallback
WEAK(void emberAfStackTokenChangedCallback(
       // The address of the stack token that has changed.
       uint16_t tokenAddress))
{
  (void)tokenAddress;
}

void ezspStackTokenChangedHandler(uint16_t tokenAddress)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_stack_token_changed(tokenAddress);
  emberAfStackTokenChangedCallback(tokenAddress);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfDsaVerifyCallback
WEAK(void emberAfDsaVerifyCallback(
       // The result of the DSA verification operation.
       EmberStatus status))
{
  (void)status;
}

void ezspDsaVerifyHandler(EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_dsa_verify(status);
  emberAfDsaVerifyCallback(status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfIncomingNetworkStatusCallback
WEAK(void emberAfIncomingNetworkStatusCallback(
       // One byte over-the-air error code from network status message
       uint8_t errorCode,
       // The short ID of the remote node
       EmberNodeId target))
{
  (void)errorCode;
  (void)target;
}

void ezspIncomingNetworkStatusHandler(uint8_t errorCode, EmberNodeId target)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_incoming_network_status(errorCode, target);
  emberAfIncomingNetworkStatusCallback(errorCode, target);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfIncomingRouteErrorCallback
WEAK(void emberAfIncomingRouteErrorCallback(
       // EMBER_SOURCE_ROUTE_FAILURE or EMBER_MANY_TO_ONE_ROUTE_FAILURE.
       EmberStatus status,
       // The short id of the remote node.
       EmberNodeId target))
{
  (void)status;
  (void)target;
}

void ezspIncomingRouteErrorHandler(EmberStatus status, EmberNodeId target)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_incoming_route_error(status, target);
  emberAfIncomingRouteErrorCallback(status, target);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
//emberAfIncomingManyToOneRouteRequestCallback
WEAK(void emberAfIncomingManyToOneRouteRequestCallback(
       // The short id of the concentrator.
       EmberNodeId source,
       // The EUI64 of the concentrator.
       EmberEUI64 longId,
       // The path cost to the concentrator. The cost may decrease as additional
       // route request packets for this discovery arrive, but the callback is
       // made only once.
       uint8_t cost))
{
  (void)source;
  (void)longId;
  (void)cost;
}

void ezspIncomingManyToOneRouteRequestHandler(EmberNodeId source,
                                              EmberEUI64 longId,
                                              uint8_t cost)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_incoming_many_to_one_route_request(source, longId, cost);
  emberAfIncomingManyToOneRouteRequestCallback(source, longId, cost);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfIdConflictCallback
WEAK(void emberAfIdConflictCallback(
       // The short id for which a conflict was detected
       EmberNodeId conflictingId))
{
  (void)conflictingId;
}

void ezspIdConflictHandler(EmberNodeId id)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_id_conflict(id);
  emberAfIdConflictCallback(id);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfTimerCallback
WEAK(void emberAfTimerCallback(
       // Which timer generated the callback (0 or 1).
       uint8_t timerId))
{
  (void)timerId;
}

void ezspTimerHandler(uint8_t timerId)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_timer(timerId);
  emberAfTimerCallback(timerId);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfCounterRolloverCallback
WEAK(void emberAfCounterRolloverCallback(
       // Type of Counter
       EmberCounterType type))
{
  (void)type;
}

void ezspCounterRolloverHandler(EmberCounterType type)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_counterRollover(type);
  emberAfCounterRolloverCallback(type);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfZllAddressAssignmentCallback
WEAK(void emberAfZllAddressAssignmentCallback(
       // The link quality from the node that last relayed the message.
       uint8_t lastHopLqi,
       // The energy level (in units of dBm) observed during reception.
       int8_t lastHopRssi,
       // Return: Address assignment information.
       const EmberZllAddressAssignment *addressInfo))
{
  (void)lastHopLqi;
  (void)lastHopRssi;
  (void)addressInfo;
}

// This call is fired when network and group addresses are assigned to a remote
// mode in a network start or network join request.
void ezspZllAddressAssignmentHandler(
  // Address assignment information.
  EmberZllAddressAssignment *addressInfo,
  // The link quality from the node that last relayed the message.
  uint8_t lastHopLqi,
  // The energy level (in units of dBm) observed during reception.
  int8_t lastHopRssi)
{
  emberAfPushCallbackNetworkIndex();
  sli_zb_af_zll_address_assignment(addressInfo, lastHopLqi, lastHopRssi);
  emberAfZllAddressAssignmentCallback(lastHopLqi, lastHopRssi, addressInfo);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfZllScanCompleteCallback
WEAK(void emberAfZllScanCompleteCallback(
       // Status of the operation.
       EmberStatus status))
{
  (void)status;
}

// This call is fired when a ZLL network scan is complete.
void ezspZllScanCompleteHandler(
  // Status of the operation.
  EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_zll_scan_complete(status);
  emberAfZllScanCompleteCallback(status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfZllNetworkFoundCallback
WEAK(void emberAfZllNetworkFoundCallback(
       // Used to interpret deviceInfo field.
       bool isDeviceInfoNull,
       // The link quality from the node that last relayed the message.
       uint8_t lastHopLqi,
       // The energy level (in units of dBm) observed during reception.
       int8_t lastHopRssi,
       // Return: Information about the network.
       const EmberZllNetwork *networkInfo,
       // Return: Device specific information.
       const EmberZllDeviceInfoRecord *deviceInfo))
{
  (void)networkInfo;
  (void)isDeviceInfoNull;
  (void)deviceInfo;
  (void)lastHopLqi;
  (void)lastHopRssi;
}

// This call is fired when a ZLL network scan finds a ZLL network.
void ezspZllNetworkFoundHandler(
  // Information about the network.
  EmberZllNetwork *networkInfo,
  // Used to interpret deviceInfo field.
  bool isDeviceInfoNull,
  // Device specific information.
  EmberZllDeviceInfoRecord *deviceInfo,
  // The link quality from the node that last relayed the message.
  uint8_t lastHopLqi,
  // The energy level (in units of dBm) observed during reception.
  int8_t lastHopRssi)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_zll_networkFound(networkInfo, isDeviceInfoNull, deviceInfo, lastHopLqi, lastHopRssi);
  emberAfZllNetworkFoundCallback(isDeviceInfoNull, lastHopLqi, lastHopRssi, networkInfo, deviceInfo);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
WEAK(void emberAfDebugCallback(
       // debug message length
       uint8_t messageLength,
       // debug message
       uint8_t *messageContents))
{
  (void)messageLength;
  (void)messageContents;
}

void ezspDebugHandler(uint8_t messageLength,
                      uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_debug(messageLength, messageContents);
  emberAfDebugCallback(messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfRawTransmitCompleteCallback
WEAK(void emberAfRawTransmitCompleteCallback(
       // message
       EmberMessageBuffer message,
       // EMBER_SUCCESS if the transmission was successful, or
       // EMBER_DELIVERY_FAILED if not
       EmberStatus status))
{
  (void)message;
  (void)status;
}

void ezspRawTransmitCompleteHandler(EmberStatus status)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_raw_transmit_complete(0, status);
  emberAfRawTransmitCompleteCallback(0, status);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfMacFilterMatchMessageCallback
WEAK(void emberAfMacFilterMatchMessageCallback(
       // filter index match.
       uint8_t filterIndexMatch,
       // message type.
       EmberMacPassthroughType messageType,
       // last hop lqi.
       uint8_t lastHopLqi,
       // last hop rssi.
       int8_t lastHopRssi,
       // message length.
       uint8_t messageLength,
       // message contents.
       uint8_t *messageContents))
{
  (void)filterIndexMatch;
  (void)messageType;
  (void)lastHopLqi;
  (void)lastHopRssi;
  (void)messageLength;
  (void)messageContents;
}

void ezspMacFilterMatchMessageHandler(uint8_t filterIndexMatch,
                                      uint8_t legacyPassthroughType,
                                      uint8_t lastHopLqi,
                                      int8_t lastHopRssi,
                                      uint8_t messageLength,
                                      uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_mac_filter_match_message(filterIndexMatch, legacyPassthroughType, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfMacFilterMatchMessageCallback(filterIndexMatch, legacyPassthroughType, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
WEAK(void emberAfMacPassthroughMessageCallback(
       // The type of MAC passthrough message received.
       EmberMacPassthroughType messageType,
       // last hop lqi.
       uint8_t lastHopLqi,
       // last hop rssi.
       int8_t lastHopRssi,
       // message length.
       uint8_t messageLength,
       // The raw message that was received.
       uint8_t *messageContents))
{
  (void)messageType;
  (void)lastHopLqi;
  (void)lastHopRssi;
  (void)messageLength;
  (void)messageContents;
}

void ezspMacPassthroughMessageHandler(uint8_t messageType,
                                      uint8_t lastHopLqi,
                                      int8_t lastHopRssi,
                                      uint8_t messageLength,
                                      uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_mac_passthrough_message(messageType, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfMacPassthroughMessageCallback(messageType, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
WEAK(void emberAfBootloadTransmitCompleteCallback(
       // An EmberStatus value of EMBER_SUCCESS if an ACK was received from the
       // destination or EMBER_DELIVERY_FAILED if no ACK was received.
       EmberStatus status,
       // message length.
       uint8_t messageLength,
       // The bootload message that was sent.
       uint8_t *messageContents))
{
  (void)status;
  (void)messageLength;
  (void)messageContents;
}

void ezspBootloadTransmitCompleteHandler(EmberStatus status,
                                         uint8_t messageLength,
                                         uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_bootload_transmit_complete(status, messageLength, messageContents);
  emberAfBootloadTransmitCompleteCallback(status, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfIncomingBootloadMessageCallback
WEAK(void emberAfIncomingBootloadMessageCallback(
       // The EUI64 of the sending node.
       EmberEUI64 longId,
       // last hop lqi.
       uint8_t lastHopLqi,
       // last hop rssi.
       int8_t lastHopRssi,
       // message length.
       uint8_t messageLength,
       // The bootload message that was sent.
       uint8_t *messageContents))
{
  (void)longId;
  (void)lastHopLqi;
  (void)lastHopRssi;
  (void)messageLength;
  (void)messageContents;
}

void ezspIncomingBootloadMessageHandler(EmberEUI64 longId,
                                        uint8_t lastHopLqi,
                                        int8_t lastHopRssi,
                                        uint8_t messageLength,
                                        uint8_t *messageContents)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_incoming_bootload_message(longId, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfIncomingBootloadMessageCallback(longId, lastHopLqi, lastHopRssi, messageLength, messageContents);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfPollCallback
WEAK(void emberAfPollCallback(
       // The node ID of the child that is requesting data.
       EmberNodeId childId,
       // True if transmit expected, false otherwise.
       bool transmitExpected))
{
  (void)childId;
  (void)transmitExpected;
}

void ezspPollHandler(EmberNodeId childId, bool transmitExpected)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_poll(childId, transmitExpected);
  emberAfPollCallback(childId, transmitExpected);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfRemoteDeleteBindingCallback
WEAK(void emberAfRemoteDeleteBindingCallback(
       // The index of the binding whose deletion was requested.
       uint8_t index,
       // ZDO response status
       EmberZdoStatus status))
{
  (void)index;
  (void)status;
  return;
}

void ezspRemoteDeleteBindingHandler(uint8_t index,
                                    EmberStatus policyDecision)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_remote_delete_binding(index);
  emberAfRemoteDeleteBindingCallback(index, policyDecision);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfRemoteSetBindingCallback
WEAK(void emberAfRemoteSetBindingCallback(
       // The contents of the binding entry.
       EmberBindingTableEntry *entry,
       // ZDO status.
       EmberZdoStatus status))
{
  (void)entry;
  (void)status;
  return;
}

void ezspRemoteSetBindingHandler(EmberBindingTableEntry *entry,
                                 uint8_t index,
                                 EmberStatus policyDecision)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_remote_set_binding(entry);
  emberAfRemoteSetBindingCallback(entry, policyDecision);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback
//emberAfCalculateSmacsHandler283k1Callback
WEAK(void emberAfCalculateSmacsHandler283k1Callback(
       // The Result of the CBKE operation.
       EmberStatus status,
       // Return: The calculated value of the initiator's SMAC
       EmberSmacData *initiatorSmac,
       // Return: The calculated value of the responder's SMAC
       EmberSmacData *responderSmac))
{
  (void)status;
  (void)initiatorSmac;
  (void)responderSmac;
}

void ezspCalculateSmacsHandler283k1(EmberStatus status,
                                    EmberSmacData* initiatorSmac,
                                    EmberSmacData* responderSmac)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_calculate_smacsHandler283k1(status, initiatorSmac, responderSmac);
  emberAfCalculateSmacsHandler283k1Callback(status, initiatorSmac, responderSmac);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback
//emberAfGenerateCbkeKeysHandler283k1Callback
WEAK(void emberAfGenerateCbkeKeysHandler283k1Callback(
       // The result of the CBKE operation.
       EmberStatus status,
       // Return: The generated ephemeral public key.
       EmberPublicKey283k1Data *ephemeralPublicKey))
{
  (void)status;
  (void)ephemeralPublicKey;
}

void ezspGenerateCbkeKeysHandler283k1(EmberStatus status,
                                      EmberPublicKey283k1Data* ephemeralPublicKey)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_generate_cbke_keys_handler283k1(status, ephemeralPublicKey);
  emberAfGenerateCbkeKeysHandler283k1Callback(status, ephemeralPublicKey);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfCalculateSmacsCallback
WEAK(void emberAfCalculateSmacsCallback(
       // The Result of the CBKE operation.
       EmberStatus status,
       // Return: The calculated value of the initiator's SMAC
       EmberSmacData *initiatorSmac,
       // Return: The calculated value of the responder's SMAC
       EmberSmacData *responderSmac))
{
  (void)status;
  (void)initiatorSmac;
  (void)responderSmac;
}

void ezspCalculateSmacsHandler(EmberStatus status,
                               EmberSmacData* initiatorSmac,
                               EmberSmacData* responderSmac)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_calculate_smacs(status, initiatorSmac, responderSmac);
  emberAfCalculateSmacsCallback(status, initiatorSmac, responderSmac);
  emberAfPopNetworkIndex();
}

// -----------------------------------------------------------------------------
// Weak implementation of public Callback emberAfGenerateCbkeKeysCallback
WEAK(void emberAfGenerateCbkeKeysCallback(
       // The result of the CBKE operation.
       EmberStatus status,
       // Return: The generated ephemeral public key.
       EmberPublicKeyData *ephemeralPublicKey))
{
  (void)status;
  (void)ephemeralPublicKey;
}

void ezspGenerateCbkeKeysHandler(EmberStatus status,
                                 EmberPublicKeyData* ephemeralPublicKey)
{
  emberAfPushCallbackNetworkIndex();
  sli_zigbee_af_generate_cbke_keys(status, ephemeralPublicKey);
  emberAfGenerateCbkeKeysCallback(status, ephemeralPublicKey);
  emberAfPopNetworkIndex();
}
