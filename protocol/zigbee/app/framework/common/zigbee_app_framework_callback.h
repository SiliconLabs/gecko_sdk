/***************************************************************************//**
 * @file
 * @brief Zigbee application framework stack callbacks
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

// *** Generated file. Do not edit! ***
#ifndef ZIGBEE_APP_FRAMEWORK_CALLBACK_H
#define ZIGBEE_APP_FRAMEWORK_CALLBACK_H

/**
 * @addtogroup stack_callback
 * @{
 */

/** @brief
 * A callback invoked when receiving a message.
 * @param type Incoming message type
 * @param apsFrame The aps Frame
 * @param message message
 */
void emberAfIncomingMessageCallback(
  // Incoming message type
  EmberIncomingMessageType type,
  // The aps Frame
  EmberApsFrame *apsFrame,
  // message
  EmberMessageBuffer message);

/** @brief
 * A callback that allows marking application buffers
 */
void emberAfMarkBuffersCallback(void);

/** @brief
 * incomingMfgTestMessageHandler
 */
void emberAfIncomingMfgTestMessageCallback(
  uint8_t messageType,
  uint8_t dataLength,
  // Return:
  uint8_t *data);

/** @brief
 * Allow the application to decide if it wants to append a source route to
 * packet header itself
 *
 * @return Added bytes
 */
uint8_t emberAfOverrideAppendSourceRouteCallback(
  EmberNodeId destination,
  // Return:
  EmberMessageBuffer *header,
  // Return:
  bool *consumed);

/** @brief
 * A callback invoked when the status of the stack changes. If the status
 * parameter equals EMBER_NETWORK_UP, then the getNetworkParameters command can
 * be called to obtain the new network parameters. If any of the parameters are
 * being stored in nonvolatile memory by the Host, the stored values should be
 * updated.
 * @param status Stack status
 */
void emberAfStackStatusCallback(
  // Stack status
  EmberStatus status);

/** @brief
 * A callback that allows the app to redirect the packet
 * @param mac_index The mac index used to redirect messages
 * @param header Packet buffer header
 * @param priority Transmit priority
 */
void emberAfRedirectOutgoingMessageCallback(
  // The mac index used to redirect messages
  uint8_t mac_index,
  // Packet buffer header
  EmberMessageBuffer header,
  // Transmit priority
  uint8_t priority);

/** @brief
 * Reports the result of an energy scan for a single channel. The scan is not
 * complete until the scanCompleteHandler callback is called.
 * @param channel The 802.15.4 channel number that was scanned.
 * @param maxRssiValue The maximum RSSI value found on the channel.
 */
void emberAfEnergyScanResultCallback(
  // The 802.15.4 channel number that was scanned.
  uint8_t channel,
  // The maximum RSSI value found on the channel.
  int8_t maxRssiValue);

/** @brief
 * Reports that a network was found as a result of a prior call to startScan.
 * Gives the network parameters useful for deciding which network to join.
 * @param networkFound The parameters associated with the network found.
 * @param lqi The link quality indication of the network found.
 * @param rssi The received signal strength indication of the network found.
 */
void emberAfNetworkFoundCallback(
  // The parameters associated with the network found.
  EmberZigbeeNetwork *networkFound,
  // The link quality indication of the network found.
  uint8_t lqi,
  // The received signal strength indication of the network found.
  int8_t rssi);

/** @brief
 * Returns the status of the current scan of type EMBER_ENERGY_SCAN or
 * EMBER_ACTIVE_SCAN. EMBER_SUCCESS signals that the scan has completed. Other
 * error conditions signify a failure to scan on the channel specified.
 * @param channel The channel on which the current error occurred. Undefined for
   the case of EMBER_SUCCESS.
 * @param status The error condition that occurred on the current channel. Value
   will be EMBER_SUCCESS when the scan has completed.
 */
void emberAfScanCompleteCallback(
  // The channel on which the current error occurred. Undefined for the case
  // of EMBER_SUCCESS.
  uint8_t channel,
  // The error condition that occurred on the current channel. Value will be
  // EMBER_SUCCESS when the scan has completed.
  EmberStatus status);

/** @brief
 * This function returns an unused panID and channel pair found via the find
 * unused panId scan procedure.
 * @param panId The unused panID which has been found.
 * @param channel The channel that the unused panID was found on.
 */
void emberAfUnusedPanIdFoundCallback(
  // The unused panID which has been found.
  EmberPanId panId,
  // The channel that the unused panID was found on.
  uint8_t channel);

/** @brief
 * Indicates that a child has joined or left.
 * @param index The index of the child of interest.
 * @param joining True if the child is joining. False the child is leaving.
 */
void emberAfChildJoinCallback(
  // The index of the child of interest.
  uint8_t index,
  // True if the child is joining. False the child is leaving.
  bool joining);

/** @brief
 * Callback fires when the duty cycle state has changed
 * @param channelPage The channel page whose duty cycle state has changed.
 * @param channel The channel number whose duty cycle state has changed.
 * @param state The current duty cycle state.
 */
void emberAfDutyCycleCallback(
  // The channel page whose duty cycle state has changed.
  uint8_t channelPage,
  // The channel number whose duty cycle state has changed.
  uint8_t channel,
  // The current duty cycle state.
  EmberDutyCycleState state);

/** @brief
 * The NCP used the external binding modification policy to decide how to handle
 * a remote set binding request. The Host cannot change the current decision, but
 * it can change the policy for future decisions using the setPolicy command.
 * @param entry The contents of the binding entry.
 * @param status ZDO status.
 */
void emberAfRemoteSetBindingCallback(
  // The contents of the binding entry.
  EmberBindingTableEntry *entry,
  // ZDO status.
  EmberZdoStatus status);

/** @brief
 * The NCP used the external binding modification policy to decide how to handle
 * a remote delete binding request. The Host cannot change the current decision,
 * but it can change the policy for future decisions using the setPolicy command.
 * @param index The index of the binding whose deletion was requested.
 * @param status ZDO status
 */
void emberAfRemoteDeleteBindingCallback(
  // The index of the binding whose deletion was requested.
  uint8_t index,
  // ZDO status
  EmberZdoStatus status);

/** @brief
 * Indicates the result of a data poll to the parent of the local node.
 * @param status An EmberStatus value: EMBER_SUCCESS - Data was received in
   response to the poll. EMBER_MAC_NO_DATA - No data was pending.
   EMBER_DELIVERY_FAILED - The poll message could not be sent.
   EMBER_MAC_NO_ACK_RECEIVED - The poll message was sent but not acknowledged by
   the parent.
 */
void emberAfPollCompleteCallback(
  // An EmberStatus value: EMBER_SUCCESS - Data was received in response to
  // the poll. EMBER_MAC_NO_DATA - No data was pending.
  // EMBER_DELIVERY_FAILED - The poll message could not be sent.
  // EMBER_MAC_NO_ACK_RECEIVED - The poll message was sent but not
  // acknowledged by the parent.
  EmberStatus status);

/** @brief
 * Indicates that the local node received a data poll from a child.
 * @param childId The node ID of the child that is requesting data.
 * @param transmitExpected True if transmit expected, false otherwise.
 */
void emberAfPollCallback(
  // The node ID of the child that is requesting data.
  EmberNodeId childId,
  // True if transmit expected, false otherwise.
  bool transmitExpected);

/** @brief
 * debugHandler
 * @param messageLength debug message length
 * @param messageContents debug message
 */
void emberAfDebugCallback(
  // debug message length
  uint8_t messageLength,
  // debug message
  uint8_t *messageContents);

/** @brief
 * A callback indicating that a many-to-one route to the concentrator with the
 * given short and long ID is available for use.
 * @param source The short id of the concentrator.
 * @param longId The EUI64 of the concentrator.
 * @param cost The path cost to the concentrator. The cost may decrease as
   additional route request packets for this discovery arrive, but the callback is
   made only once.
 */
void emberAfIncomingManyToOneRouteRequestCallback(
  // The short id of the concentrator.
  EmberNodeId source,
  // The EUI64 of the concentrator.
  EmberEUI64 longId,
  // The path cost to the concentrator. The cost may decrease as additional
  // route request packets for this discovery arrive, but the callback is
  // made only once.
  uint8_t cost);

/** @brief
 * A callback invoked when a route error message is received. The error indicates
 * that a problem routing to or from the target node was encountered.
 * @param status EMBER_SOURCE_ROUTE_FAILURE or EMBER_MANY_TO_ONE_ROUTE_FAILURE.
 * @param target The short id of the remote node.
 */
void emberAfIncomingRouteErrorCallback(
  // EMBER_SOURCE_ROUTE_FAILURE or EMBER_MANY_TO_ONE_ROUTE_FAILURE.
  EmberStatus status,
  // The short id of the remote node.
  EmberNodeId target);

/** @brief
 * A callback invoked when a network status/route error message is received. The
 * error indicates that there was a problem sending/receiving messages from the
 * target node
 * @param errorCode One byte over-the-air error code from network status message
 * @param target The short ID of the remote node
 */
void emberAfIncomingNetworkStatusCallback(
  // One byte over-the-air error code from network status message
  uint8_t errorCode,
  // The short ID of the remote node
  EmberNodeId target);

/** @brief
 * Reports the arrival of a route record command frame.
 * @param source The source of the route record.
 * @param sourceEui The EUI64 of the source.
 * @param relayCount The number of relays in relayList.
 * @param header Header.
 * @param relayListIndex The relay List Index.
 */
void emberAfIncomingRouteRecordCallback(
  // The source of the route record.
  EmberNodeId source,
  // The EUI64 of the source.
  EmberEUI64 sourceEui,
  // The number of relays in relayList.
  uint8_t relayCount,
  // Header.
  EmberMessageBuffer header,
  // The relay List Index.
  uint8_t relayListIndex);

/** @brief
 * A callback invoked by the EmberZNet stack when an id conflict is discovered,
 * that is, two different nodes in the network were found to be using the same
 * short id. The stack automatically removes the conflicting short id from its
 * internal tables (address, binding, route, neighbor, and child tables). The
 * application should discontinue any other use of the id.
 * @param conflictingId The short id for which a conflict was detected
 */
void emberAfIdConflictCallback(
  // The short id for which a conflict was detected
  EmberNodeId conflictingId);

/** @brief
 * A callback invoked by the EmberZNet stack when a MAC passthrough message is
 * received.
 * @param messageType The type of MAC passthrough message received.
 * @param lastHopLqi last hop LQI.
 * @param lastHopRssi last hop RSSI.
 * @param messageLength message length.
 * @param messageContents The raw message that was received.
 */
void emberAfMacPassthroughMessageCallback(
  // The type of MAC passthrough message received.
  EmberMacPassthroughType messageType,
  // last hop LQI.
  uint8_t lastHopLqi,
  // last hop RSSI.
  int8_t lastHopRssi,
  // message length.
  uint8_t messageLength,
  // The raw message that was received.
  uint8_t *messageContents);

/** @brief
 * A callback invoked to inform the application that a stack token has changed.
 * @param tokenAddress The address of the stack token that has changed.
 */
void emberAfStackTokenChangedCallback(
  // The address of the stack token that has changed.
  uint16_t tokenAddress);

/** @brief
 * A callback from the timer.
 * @param timerId Which timer generated the callback (0 or 1).
 */
void emberAfTimerCallback(
  // Which timer generated the callback (0 or 1).
  uint8_t timerId);

/** @brief
 * This call is fired when a counter exceeds its threshold
 * @param type Type of Counter
 */
void emberAfCounterRolloverCallback(
  // Type of Counter
  EmberCounterType type);

/** @brief
 * A callback invoked by the EmberZNet stack when the MAC has finished
 * transmitting a raw message.
 * @param message message, message always returns EMBER_NULL_MESSAGE_BUFFER on
   host
 * @param status EMBER_SUCCESS if the transmission was successful, or
   EMBER_DELIVERY_FAILED if not
 */
void emberAfRawTransmitCompleteCallback(
  // message, message always returns EMBER_NULL_MESSAGE_BUFFER on host
  EmberMessageBuffer message,
  // EMBER_SUCCESS if the transmission was successful, or
  // EMBER_DELIVERY_FAILED if not
  EmberStatus status);

/** @brief
 * A callback to inform the application that the Network Key has been updated and
 * the node has been switched over to use the new key. The actual key being used
 * is not passed up, but the sequence number is.
 * @param sequenceNumber The sequence number of the new network key.
 */
void emberAfSwitchNetworkKeyCallback(
  // The sequence number of the new network key.
  uint8_t sequenceNumber);

/** @brief
 * This is a callback that indicates the success or failure of an attempt to
 * establish a key with a partner device.
 * @param partner This is the IEEE address of the partner that the device
   successfully established a key with. This value is all zeros on a failure.
 * @param status This is the status indicating what was established or why the
   key establishment failed.
 */
void emberAfZigbeeKeyEstablishmentCallback(
  // This is the IEEE address of the partner that the device successfully
  // established a key with. This value is all zeros on a failure.
  EmberEUI64 partner,
  // This is the status indicating what was established or why the key
  // establishment failed.
  EmberKeyStatus status);

/** @brief
 * A callback by the Crypto Engine indicating that a new ephemeral public/private
 * key pair has been generated. The public/private key pair is stored on the NCP,
 * but only the associated public key is returned to the host. The node's
 * associated certificate is also returned.
 * @param status The result of the CBKE operation.
 * @return ephemeralPublicKey The generated ephemeral public key.
 */
void emberAfGenerateCbkeKeysCallback(
  // The result of the CBKE operation.
  EmberStatus status,
  // Return: The generated ephemeral public key.
  EmberPublicKeyData *ephemeralPublicKey);

/** @brief
 * A callback to indicate that the NCP has finished calculating the Secure
 * Message Authentication Codes (SMAC) for both the initiator and responder. The
 * associated link key is kept in temporary storage until the host tells the NCP
 * to store or discard the key via emberClearTemporaryDataMaybeStoreLinkKey().
 * @param status The Result of the CBKE operation.
 * @return initiatorSmac The calculated value of the initiator's SMAC
 * @return responderSmac The calculated value of the responder's SMAC
 */
void emberAfCalculateSmacsCallback(
  // The Result of the CBKE operation.
  EmberStatus status,
  // Return: The calculated value of the initiator's SMAC
  EmberSmacData *initiatorSmac,
  // Return: The calculated value of the responder's SMAC
  EmberSmacData *responderSmac);

/** @brief
 * The handler that returns the results of the signing operation. On success, the
 * signature will be appended to the original message (including the signature
 * type indicator that replaced the startIndex field for the signing) and both
 * are returned via this callback.
 * @param status The result of the DSA signing operation.
 * @param messageLength The length of message.
 * @param messageContents The message and attached which includes the original
   message and the appended signature.
 */
void emberAfDsaSignCallback(
  // The result of the DSA signing operation.
  EmberStatus status,
  // The length of message.
  uint8_t messageLength,
  // The message and attached which includes the original message and the
  // appended signature.
  uint8_t *messageContents);

/** @brief
 * This callback is executed by the stack when the DSA verification has completed
 * and has a result. If the result is EMBER_SUCCESS, the signature is valid. If
 * the result is EMBER_SIGNATURE_VERIFY_FAILURE then the signature is invalid. If
 * the result is anything else then the signature verify operation failed and the
 * validity is unknown.
 * @param status The result of the DSA verification operation.
 */
void emberAfDsaVerifyCallback(
  // The result of the DSA verification operation.
  EmberStatus status);

/** @brief
 * A callback invoked by the EmberZNet stack when a bootload message is received.
 * @param longId The EUI64 of the sending node.
 * @param lastHopLqi last hop LQI.
 * @param lastHopRssi last hop RSSI.
 * @param messageLength message length.
 * @param messageContents The bootload message that was sent.
 */
void emberAfIncomingBootloadMessageCallback(
  // The EUI64 of the sending node.
  EmberEUI64 longId,
  // last hop LQI.
  uint8_t lastHopLqi,
  // last hop RSSI.
  int8_t lastHopRssi,
  // message length.
  uint8_t messageLength,
  // The bootload message that was sent.
  uint8_t *messageContents);

/** @brief
 * A callback invoked by the EmberZNet stack when the MAC has finished
 * transmitting a bootload message.
 * @param status An EmberStatus value of EMBER_SUCCESS if an ACK was received
   from the destination or EMBER_DELIVERY_FAILED if no ACK was received.
 * @param messageLength message length.
 * @param messageContents The bootload message that was sent.
 */
void emberAfBootloadTransmitCompleteCallback(
  // An EmberStatus value of EMBER_SUCCESS if an ACK was received from the
  // destination or EMBER_DELIVERY_FAILED if no ACK was received.
  EmberStatus status,
  // message length.
  uint8_t messageLength,
  // The bootload message that was sent.
  uint8_t *messageContents);

/** @brief
 * This callback is invoked when a ZLL network scan finds a ZLL network.
 * @param isDeviceInfoNull Used to interpret deviceInfo field.
 * @param lastHopLqi The link quality from the node that last relayed the
   message.
 * @param lastHopRssi The energy level (in units of dBm) observed during
   reception.
 * @return networkInfo Information about the network.
 * @return deviceInfo Device specific information.
 */
void emberAfZllNetworkFoundCallback(
  // Used to interpret deviceInfo field.
  bool isDeviceInfoNull,
  // The link quality from the node that last relayed the message.
  uint8_t lastHopLqi,
  // The energy level (in units of dBm) observed during reception.
  int8_t lastHopRssi,
  // Return: Information about the network.
  const EmberZllNetwork *networkInfo,
  // Return: Device specific information.
  const EmberZllDeviceInfoRecord *deviceInfo);

/** @brief
 * This callback is invoked when a ZLL network scan is complete.
 * @param status Status of the operation.
 */
void emberAfZllScanCompleteCallback(
  // Status of the operation.
  EmberStatus status);

/** @brief
 * This callback is invoked when network and group addresses are assigned to a remote
 * mode in a network start or network join request.
 * @param lastHopLqi The link quality from the node that last relayed the
   message.
 * @param lastHopRssi The energy level (in units of dBm) observed during
   reception.
 * @return addressInfo Address assignment information.
 */
void emberAfZllAddressAssignmentCallback(
  // The link quality from the node that last relayed the message.
  uint8_t lastHopLqi,
  // The energy level (in units of dBm) observed during reception.
  int8_t lastHopRssi,
  // Return: Address assignment information.
  const EmberZllAddressAssignment *addressInfo);

/** @brief
 * This callback is invoked when the device is a target of a touch link.
 * @return networkInfo Information about the network.
 */
void emberAfZllTouchLinkTargetCallback(
  // Return: Information about the network.
  const EmberZllNetwork *networkInfo);

/** @brief
 * A callback invoked by the EmberZNet stack when a raw MAC message that has
 * matched one of the application's configured MAC filters.
 * @param filterIndexMatch filter index match.
 * @param messageType message type.
 * @param lastHopLqi last hop LQI.
 * @param lastHopRssi last hop RSSI.
 * @param messageLength message length.
 * @param messageContents message contents.
 */
void emberAfMacFilterMatchMessageCallback(
  // filter index match.
  uint8_t filterIndexMatch,
  // message type.
  EmberMacPassthroughType messageType,
  // last hop LQI.
  uint8_t lastHopLqi,
  // last hop RSSI.
  int8_t lastHopRssi,
  // message length.
  uint8_t messageLength,
  // message contents.
  uint8_t *messageContents);

/** @brief
 * A callback to the GP endpoint to indicate the result of the GPDF transmission.
 * @param status An EmberStatus value indicating success or the reason for
   failure.
 * @param gpepHandle The handle of the GPDF.
 */
void emberAfDGpSentCallback(
  // An EmberStatus value indicating success or the reason for failure.
  EmberStatus status,
  // The handle of the GPDF.
  uint8_t gpepHandle);

/** @brief
 * This handler is called by the stack to report the number of conflict reports
 * exceeds EMBER_PAN_ID_CONFLICT_REPORT_THRESHOLD within a period of 1 minute )
 *
 * @return An EmberStatus value indicating success or the reason for failure.
 */
EmberStatus emberAfPanIdConflictCallback(
  // Number of conflict reports
  int8_t conflictCount);

/** @brief
 * Inform the application that an orphan notification has been received. This is
 * generally not useful for applications. It could be useful in testing and is
 * included for this purpose.
 * @param longId The 8 byte EUI64 of the sender.
 */
void emberAfOrphanNotificationCallback(
  // The 8 byte EUI64 of the sender.
  EmberEUI64 longId);

/** @brief
 * This handler is called when the value of a counter has changed
 * @param type Type of Counter
 * @param Info Counter Info and value
 */
void emberAfCounterCallback(
  // Type of Counter
  EmberCounterType type,
  // Counter Info and value
  EmberCounterInfo Info);

/** @brief
 * This handler is called for messages that need to be matched against mac
 * passthrough filter
 *
 * @return True if mac passthrough filter was matched. False otherwise.
 */
bool emberAfMacPassthroughFilterCallback(
  // Return: Mac Header of the matched messgae
  uint8_t *macHeader);

/** @brief
 * A callback by the Crypto Engine indicating that a new ephemeral public/private
 * key pair has been generated. The public/private key pair is stored on the NCP,
 * but only the associated public key is returned to the host. The node's
 * associated certificate is also returned.
 * @param status The result of the CBKE operation.
 * @return ephemeralPublicKey The generated ephemeral public key.
 */
void emberAfGenerateCbkeKeysHandler283k1Callback(
  // The result of the CBKE operation.
  EmberStatus status,
  // Return: The generated ephemeral public key.
  EmberPublicKey283k1Data *ephemeralPublicKey);

/** @brief
 * A callback to indicate that the NCP has finished calculating the Secure
 * Message Authentication Codes (SMAC) for both the initiator and responder. The
 * associated link key is kept in temporary storage until the host tells the NCP
 * to store or discard the key via emberClearTemporaryDataMaybeStoreLinkKey().
 * @param status The Result of the CBKE operation.
 * @return initiatorSmac The calculated value of the initiator's SMAC
 * @return responderSmac The calculated value of the responder's SMAC
 */
void emberAfCalculateSmacsHandler283k1Callback(
  // The Result of the CBKE operation.
  EmberStatus status,
  // Return: The calculated value of the initiator's SMAC
  EmberSmacData *initiatorSmac,
  // Return: The calculated value of the responder's SMAC
  EmberSmacData *responderSmac);

/** @brief
 * A callback invoked by the ZigBee GP stack when a GPDF is received.
 * @param status The status of the GPDF receive.
 * @param gpdLink The gpdLink value of the received GPDF.
 * @param sequenceNumber The GPDF sequence number.
 * @param addr The address of the source GPD.
 * @param gpdfSecurityLevel The security level of the received GPDF.
 * @param gpdfSecurityKeyType The securityKeyType used to decrypt/authenticate
   the incoming GPDF.
 * @param autoCommissioning Whether the incoming GPDF had the auto-commissioning
   bit set.
 * @param bidirectionalInfo Bidirectional information represented in bitfields,
   where bit0 holds the rxAfterTx of incoming gpdf and bit1 holds if tx queue is
   available for outgoing gpdf.
 * @param gpdSecurityFrameCounter The security frame counter of the incoming
   GDPF.
 * @param gpdCommandId The gpdCommandId of the incoming GPDF.
 * @param mic The received MIC of the GPDF.
 * @param proxyTableIndex The proxy table index of the corresponding proxy table
   entry to the incoming GPDF.
 * @param gpdCommandPayloadLength The length of the GPD command payload.
 * @param gpdCommandPayload The GPD command payload.
 */
void emberAfGpepIncomingMessageCallback(
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
  uint8_t *gpdCommandPayload);

/** @brief
 * Rtos Stack Wakeup Isr Handler
 */
void emberAfRtosStackWakeupIsrCallback(void);

/** @brief
 * RadioNeedsCalibratingHandler
 */
void emberAfRadioNeedsCalibratingCallback(void);

/** @brief
 * scanErrorHandler
 * @param status The error status of a scan
 */
void emberAfScanErrorCallback(
  // The error status of a scan
  EmberStatus status);

/** @brief
 * A callback invoked when receiving a message.
 * Used when AF Support component is enabled on NCP.
 * User can use apsFrame to filter for which ZCL messages they want to process on NCP.
 * If this function returns true then the message is being processed on NCP, otherwise it
 * will be forwarded to the Host.
 * @param apsFrame The aps Frame
 */
bool emberAfSupportIncomingMessageCallback(
  // The aps Frame
  EmberApsFrame *apsFrame);

/** @} */ // stack-callback group

#endif // ZIGBEE_APP_FRAMEWORK_CALLBACK_H
