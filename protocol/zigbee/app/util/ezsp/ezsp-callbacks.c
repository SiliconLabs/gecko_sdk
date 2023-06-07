/***************************************************************************//**
 * @file
 * @brief Convenience stubs for little-used EZSP callbacks.
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
#include "stack/include/ember-types.h"
#include "stack/include/error.h"

// *****************************************
// Convenience Stubs
// *****************************************

#ifndef EZSP_APPLICATION_HAS_WAITING_FOR_RESPONSE
void ezspWaitingForResponse(void)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_NO_CALLBACKS
void ezspNoCallbacks(void)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_TIMER_HANDLER
WEAK(void ezspTimerHandler(uint8_t timerId))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_DEBUG_HANDLER
WEAK(void ezspDebugHandler(uint8_t messageLength,
                           uint8_t *messageContents))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_ZIGBEE_KEY_ESTABLISHMENT_HANDLER
void ezspZigbeeKeyEstablishmentHandler(EmberEUI64 partner, EmberKeyStatus status)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_REMOTE_BINDING_HANDLER
WEAK(void ezspRemoteSetBindingHandler(EmberBindingTableEntry *entry,
                                      uint8_t index,
                                      EmberStatus policyDecision))
{
}

WEAK(void ezspRemoteDeleteBindingHandler(uint8_t index,
                                         EmberStatus policyDecision))
{
}
#endif

WEAK(void ezspPollCompleteHandler(EmberStatus status))
{
}

#ifndef EZSP_APPLICATION_HAS_POLL_HANDLER
WEAK(void ezspPollHandler(EmberNodeId childId, bool transmitExpected))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_ENERGY_SCAN_RESULT_HANDLER
void ezspEnergyScanResultHandler(uint8_t channel, int8_t maxRssiValue)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_BUTTON_HANDLER
void halButtonIsr(uint8_t button, uint8_t state)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_INCOMING_SENDER_EUI64_HANDLER
void ezspIncomingSenderEui64Handler(EmberEUI64 senderEui64)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_ID_CONFLICT_HANDLER
WEAK(void ezspIdConflictHandler(EmberNodeId id))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_INCOMING_MANY_TO_ONE_ROUTE_REQUEST_HANDLER
WEAK(void ezspIncomingManyToOneRouteRequestHandler(EmberNodeId source,
                                                   EmberEUI64 longId,
                                                   uint8_t cost))
{
}
#endif

WEAK(void ezspIncomingRouteErrorHandler(EmberStatus status, EmberNodeId target))
{
}

#ifndef EZSP_APPLICATION_HAS_INCOMING_NETWORK_STATUS_HANDLER

WEAK(void ezspIncomingNetworkStatusHandler(uint8_t errorCode, EmberNodeId target))
{
}

#endif
#ifndef EZSP_APPLICATION_HAS_ROUTE_RECORD_HANDLER

WEAK(void ezspIncomingRouteRecordHandler(EmberNodeId source,
                                         EmberEUI64 sourceEui,
                                         uint8_t lastHopLqi,
                                         int8_t lastHopRssi,
                                         uint8_t relayCount,
                                         uint8_t *relayList))
{
}
#endif
#ifndef EZSP_APPLICATION_HAS_BOOTLOADER_HANDLER
WEAK(void ezspIncomingBootloadMessageHandler(EmberEUI64 longId,
                                             uint8_t lastHopLqi,
                                             int8_t lastHopRssi,
                                             uint8_t messageLength,
                                             uint8_t *messageContents))
{
}

WEAK(void ezspBootloadTransmitCompleteHandler(EmberStatus status,
                                              uint8_t messageLength,
                                              uint8_t *messageContents))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_MAC_PASSTHROUGH_HANDLER
WEAK(void ezspMacPassthroughMessageHandler(uint8_t messageType,
                                           uint8_t lastHopLqi,
                                           int8_t lastHopRssi,
                                           uint8_t messageLength,
                                           uint8_t *messageContents))
{
}
#endif

WEAK(void ezspMacFilterMatchMessageHandler(uint8_t filterIndexMatch,
                                           uint8_t legacyPassthroughType,
                                           uint8_t lastHopLqi,
                                           int8_t lastHopRssi,
                                           uint8_t messageLength,
                                           uint8_t *messageContents))
{
  ezspMacPassthroughMessageHandler(legacyPassthroughType,
                                   lastHopLqi,
                                   lastHopRssi,
                                   messageLength,
                                   messageContents);
}

#ifndef EZSP_APPLICATION_HAS_MFGLIB_HANDLER
void ezspMfglibRxHandler(
  uint8_t linkQuality,
  int8_t rssi,
  uint8_t packetLength,
  uint8_t *packetContents)
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_RAW_HANDLER
WEAK(void ezspRawTransmitCompleteHandler(EmberStatus status))
{
}
#endif

// Certificate Based Key Exchange (CBKE)
WEAK(void ezspGenerateCbkeKeysHandler(EmberStatus status,
                                      EmberPublicKeyData* ephemeralPublicKey))
{
}

WEAK(void ezspCalculateSmacsHandler(EmberStatus status,
                                    EmberSmacData* initiatorSmac,
                                    EmberSmacData* responderSmac))
{
}

WEAK(void ezspGenerateCbkeKeysHandler283k1(EmberStatus status,
                                           EmberPublicKey283k1Data* ephemeralPublicKey))
{
}

WEAK(void ezspCalculateSmacsHandler283k1(EmberStatus status,
                                         EmberSmacData* initiatorSmac,
                                         EmberSmacData* responderSmac))
{
}
// Elliptical Cryptography Digital Signature Verification
#ifndef EZSP_APPLICATION_HAS_DSA_VERIFY_HANDLER
WEAK(void ezspDsaVerifyHandler(EmberStatus status))
{
}
#endif

#ifndef EZSP_APPLICATION_HAS_FRAGMENT_SOURCE_ROUTE_HANDLER
EmberStatus ezspFragmentSourceRouteHandler(void)
{
  return EMBER_SUCCESS;
}
#endif

WEAK(void ezspCustomFrameHandler(uint8_t payloadLength, uint8_t* payload))
{
}

#ifndef EZSP_APPLICATION_HAS_STACK_TOKEN_CHANGED_HANDLER
WEAK(void ezspStackTokenChangedHandler(uint16_t tokenAddress))
{
}
#endif

// This call is fired when a ZLL network scan finds a ZLL network.
WEAK(void ezspZllNetworkFoundHandler(
       // Information about the network.
       EmberZllNetwork *networkInfo,
       // Used to interpret deviceInfo field.
       bool isDeviceInfoNull,
       // Device specific information.
       EmberZllDeviceInfoRecord *deviceInfo,
       // The link quality from the node that last relayed the message.
       uint8_t lastHopLqi,
       // The energy level (in units of dBm) observed during reception.
       int8_t lastHopRssi))
{
}

WEAK(void ezspZllScanCompleteHandler(EmberStatus status))
{
}

WEAK(void ezspZllAddressAssignmentHandler(
       // Address assignment information.
       EmberZllAddressAssignment *addressInfo,
       // The link quality from the node that last relayed the message.
       uint8_t lastHopLqi,
       // The energy level (in units of dBm) observed during reception.
       int8_t lastHopRssi))
{
}

WEAK(void ezspZllTouchLinkTargetHandler(EmberZllNetwork* networkInfo))
{
}

WEAK(void ezspCounterRolloverHandler(EmberCounterType type))
{
}

WEAK(void ezspGpepIncomingMessageHandler(
       // XXXAn EmberStatus value of EMBER_SUCCESS if the pairing process
       // succeeded and a pairing link has been established.
       EmberStatus status,
       // The index of the entry the pairing table corresponding to the pairing
       // link that was established during the pairing process.
       uint8_t gpdLink,
       // stuff
       uint8_t sequenceNumber,
       // The vendor information of the peer device. This parameter is non-NULL
       // only if the status parameter is EMBER_SUCCESS.
       EmberGpAddress *addr,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       EmberGpSecurityLevel gpdfSecurityLevel,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       EmberGpKeyType gpdfSecurityKeyType,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       bool autoCommissioning,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       bool rxAfterTx,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       uint32_t gpdSecurityFrameCounter,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       uint8_t gpdCommandId,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       uint32_t mic,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       uint8_t gpdCommandPayloadLength,
       // The application information of the peer device. This parameter is
       // non-NULL only if the status parameter is EMBER_SUCCESS.
       uint8_t *gpdCommandPayload))
{
}

WEAK(void ezspDGpSentHandler(EmberStatus status, uint8_t gpepHandle))
{
}

WEAK(void ezspDsaSignHandler(EmberStatus status,
                             uint8_t messageLength,
                             uint8_t* messageContents))
{
}
WEAK(void ezspChildJoinHandler(uint8_t index,
                               bool joining,
                               EmberNodeId childId,
                               EmberEUI64 childEui64,
                               EmberNodeType childType))
{
}

WEAK(void ezspDutyCycleHandler(uint8_t channelPage,
                               uint8_t channel,
                               EmberDutyCycleState state,
                               uint8_t totalDevices,
                               EmberPerDeviceDutyCycle *arrayOfDeviceDutyCycles))
{
}

WEAK(void ezspSwitchNetworkKeyHandler(uint8_t sequenceNumber))
{
}

WEAK(void ezspTrustCenterJoinHandler(EmberNodeId newNodeId,
                                     EmberEUI64 newNodeEui64,
                                     EmberDeviceUpdate status,
                                     EmberJoinDecision policyDecision,
                                     EmberNodeId parentOfNewNode))
{
}
