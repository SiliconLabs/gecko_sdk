/***************************************************************************/ /**
 * @file
 * @brief ZigBee Device Object (ZDO) functions included in the stack.
 *
 * See @ref zdo for documentation.
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

#ifndef SILABS_ZIGBEE_DEVICE_STACK_H
#define SILABS_ZIGBEE_DEVICE_STACK_H

/**
 * @addtogroup zdo
 *
 * See zigbee-device-stack.h for source code.
 * @{
 */

/** @brief Request the 16 bit network address of a node whose EUI64 is known.
 *
 * @param target           The EUI64 of the node.
 * @param reportKids       True to request that the target list their children
 *                         in the response.
 * @param childStartIndex  The index of the first child to list in the response.
 *                         Ignored if @c reportKids is false.
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS - The request was transmitted successfully.
 * - ::EMBER_NO_BUFFERS - Insufficient message buffers were available to construct
 * the request.
 * - ::EMBER_NETWORK_DOWN - The node is not part of a network.
 * - ::EMBER_NETWORK_BUSY - Transmission of the request failed.
 */
EmberStatus emberNetworkAddressRequest(EmberEUI64 target,
                                       bool reportKids,
                                       uint8_t childStartIndex);

/** @brief Request the EUI64 of a node whose 16 bit network address is known.
 *
 * @param target           The network address of the node.
 * @param reportKids       True to request that the target list their children
 *                         in the response.
 * @param childStartIndex  The index of the first child to list in the response.
 *                         Ignored if reportKids is false.
 * @param options          The options to use when sending the request.
 *                         See ::emberSendUnicast() for a description.
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS
 * - ::EMBER_NO_BUFFERS
 * - ::EMBER_NETWORK_DOWN
 * - ::EMBER_NETWORK_BUSY
 */
EmberStatus emberIeeeAddressRequest(EmberNodeId target,
                                    bool reportKids,
                                    uint8_t childStartIndex,
                                    EmberApsOption options);

EmberStatus emberIeeeAddressRequestToTarget(EmberNodeId discoveryNodeId,
                                            bool reportKids,
                                            uint8_t childStartIndex,
                                            EmberApsOption options,
                                            EmberNodeId targetNodeIdOfRequest);

/** @brief Request that an energy scan be performed and its results returned.
 *  This request may only be sent by the current network manager and must be
 *  unicast, not broadcast.
 *
 * @param target           The network address of the node to perform the scan.
 * @param scanChannels     A mask of the channels to be scanned.
 * @param scanDuration     How long to scan on each channel.  Allowed
 *                         values are 0..5, with the scan times as specified
 *                         by 802.15.4 (0 = 31 ms, 1 = 46 ms, 2 = 77 ms,
 *                         3 = 138 ms, 4 = 261 ms, 5 = 507 ms).
 * @param scanCount        The number of scans to be performed on each
 *                         channel (1 .. 8).
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS
 * - ::EMBER_NO_BUFFERS
 * - ::EMBER_NETWORK_DOWN
 * - ::EMBER_NETWORK_BUSY
 */
EmberStatus emberEnergyScanRequest(EmberNodeId target,
                                   uint32_t scanChannels,
                                   uint8_t  scanDuration,
                                   uint16_t scanCount);

/** @brief Broadcast a request to set the identity of the network manager and
 * the active channel mask. The mask is used when scanning
 *  for the network after missing a channel update.
 *
 * @param networkManager   The network address of the network manager.
 * @param activeChannels   The new active channel mask.
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS
 * - ::EMBER_NO_BUFFERS
 * - ::EMBER_NETWORK_DOWN
 * - ::EMBER_NETWORK_BUSY
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
EmberStatus emberSetNetworkManagerRequest(EmberNodeId networkManager,
                                          uint32_t activeChannels);
#else
#define emberSetNetworkManagerRequest(manager, channels)  \
  (emberEnergyScanRequest(EMBER_SLEEPY_BROADCAST_ADDRESS, \
                          (channels),                     \
                          0xFF,                           \
                          (manager)))
#endif

/** @brief Broadcast a request to change the channel. This request may
 * only be sent by the current network manager. A several second delay
 * occurs from receipt of the broadcast to changing the channel
 * to allow time for the broadcast to propagate.
 *
 * @param channel  The channel to change to.
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS
 * - ::EMBER_NO_BUFFERS
 * - ::EMBER_NETWORK_DOWN
 * - ::EMBER_NETWORK_BUSY
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
EmberStatus emberChannelChangeRequest(uint8_t channel);
#else
#define emberChannelChangeRequest(channel)                \
  (emberEnergyScanRequest(EMBER_SLEEPY_BROADCAST_ADDRESS, \
                          BIT32(channel),                 \
                          0xFE,                           \
                          0))
#endif

/** @brief Send a broadcast for a ZDO Device announcement. Normally,
 *    it is NOT required to call this as the stack automatically sends
 *    a device announcement during joining or rejoining, as per the spec.
 *
 *    May be used to re-send the device announcement.
 *
 *    @return An ::EmberStatus value.
 *    - ::EMBER_SUCCESS
 *    - ::EMBER_INVALID_CALL
 */
EmberStatus emberSendDeviceAnnouncement(void);

/** @brief Send a broadcast for a ZDO Parent Announcement. Normally,
 *    it is NOT required to call this as the stack automatically sends
 *    a Parent Announce when a Zigbee Router/Coordinator reboots, is in
 *    a joined or authenticated state, and has at least one device.
 *
 *    May be used to re-send the parent announcement.
 *
 *    @return An ::EmberStatus value.
 *    - ::EMBER_SUCCESS
 *    - ::EMBER_INVALID_CALL
 */
EmberStatus emberSendParentAnnouncement(void);

/**
 * @brief Provide access to the stack ZDO transaction sequence number for
 * the last request.
 *
 * @return  The last stack ZDO transaction sequence number used.
 */
uint8_t emberGetLastStackZigDevRequestSequence(void);

/** @} END addtogroup */

/**
 * @brief Set the ZDO (WWAH) configuration mode  in the stack.
 * ZDO configuration  mode is used to enable/disable ZDO command
 * processing and to protect the device from
 * unauthorized configuration changes during normal operation.
 *
 */

void emberSetZDOConfigurationMode(bool enabled);

/**
 * @brief Set the channel number the device will accept in ZDO Mgmt Network
 * Update command to change channel.
 *
 * If a ZDO Mgmt Network Update command is received by the device specifying
 * a channel that does not match with the given channel, the ZDO Mgmt
 * Network Update command will be ignored by the device. A value of 0xFF indicates
 * that any channel received in a ZDO Mgmt Network Update command will be accepted
 * which is also the default value set by the stack.
 *
 *  @param channel    A pending network update channel number.
 */
void emberSetPendingNetworkUpdateChannel(uint8_t channel);

/**
 * @brief This is an API to set the device capability extension TLV used by Zigbee Direct.
 *
 *
 * If the local device is a Zigbee virtual Device it needs to present the capability extension
 * TLV in the network commissioning request within the joiner encapsulation TLV.
 * This is required only for a Zigbee Virtual Device.
 *  @param attach_tlv    boolean value to indicate if the tlv should be attached to the joiner encapsulation tlv , set true to attach
 *  @param  capability_extension_bitmask 2 bytes value to be set as described in the Zigbee Direct specification.
 */
void sl_set_device_capability_extension_field_for_zigbee_virtual_device(boolean attach_tlv, uint16_t capability_extension_bitmask);

/**
 * @name ZigBee Device Object (ZDO) Definitions
 */
//@{

/**
 * Defines for ZigBee device profile cluster IDs follow. These
 * include descriptions of the formats of the messages.
 *
 * Note that each message starts with a 1-byte transaction sequence
 * number. This sequence number is used to match a response command frame
 * to the request frame that it is replying to. The application shall
 * maintain a 1-byte counter that is copied into this field and incremented
 * by one for each command sent. When a value of 0xff is reached, the next
 * command shall re-start the counter with a value of 0x00.
 */

/// @name Network and IEEE Address Request/Response
/// <br> @{
///
/// @code
/// Network request: <transaction sequence number: 1>
///                  <EUI64:8>   <type:1> <start index:1>
/// IEEE request:    <transaction sequence number: 1>
///                  <node ID:2> <type:1> <start index:1>
///                  <type> = 0x00 single address response, ignore the start index
///                  = 0x01 extended response -> sends kid's IDs as well
/// Response: <transaction sequence number: 1>
///           <status:1> <EUI64:8> <node ID:2>
///           <ID count:1> <start index:1> <child ID:2>*
/// @endcode
#define NETWORK_ADDRESS_REQUEST 0x0000u
#define NETWORK_ADDRESS_RESPONSE 0x8000u
#define IEEE_ADDRESS_REQUEST 0x0001u
#define IEEE_ADDRESS_RESPONSE 0x8001u
/// @}

/// @name Node Descriptor Request/Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1> <node ID:2> <tlvs: varies>
/// Response: <transaction sequence number: 1> <status:1> <node ID:2>
//            <node descriptor: 13> <tlvs: varies>
//
//  Node Descriptor field is divided into subfields of bitmasks as follows:
//      (Note: All lengths below are given in bits rather than bytes.)
//            Logical Type:                     3
//            Complex Descriptor Available:     1
//            User Descriptor Available:        1
//            (reserved/unused):                3
//            APS Flags:                        3
//            Frequency Band:                   5
//            MAC capability flags:             8
//            Manufacturer Code:               16
//            Maximum buffer size:              8
//            Maximum incoming transfer size:  16
//            Server mask:                     16
//            Maximum outgoing transfer size:  16
//            Descriptor Capability Flags:      8
//     See ZigBee document 053474, Section 2.3.2.3 for more details.
/// @endcode
#define NODE_DESCRIPTOR_REQUEST 0x0002u
#define NODE_DESCRIPTOR_RESPONSE 0x8002u
/// @}

/// @name Power Descriptor Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1> <node ID:2>
/// Response: <transaction sequence number: 1> <status:1> <node ID:2>
///           <current power mode, available power sources:1>
///           <current power source, current power source level:1>
//     See ZigBee document 053474, Section 2.3.2.4 for more details.
/// @endcode
#define POWER_DESCRIPTOR_REQUEST 0x0003u
#define POWER_DESCRIPTOR_RESPONSE 0x8003u
/// @}

/// @name Simple Descriptor Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <node ID:2> <endpoint:1>
/// Response: <transaction sequence number: 1>
///           <status:1> <node ID:2> <length:1> <endpoint:1>
///           <app profile ID:2> <app device ID:2>
///           <app device version, app flags:1>
///           <input cluster count:1> <input cluster:2>*
///           <output cluster count:1> <output cluster:2>*
/// @endcode
#define SIMPLE_DESCRIPTOR_REQUEST 0x0004u
#define SIMPLE_DESCRIPTOR_RESPONSE 0x8004u
/// @}

/// @name Active Endpoints Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1> <node ID:2>
/// Response: <transaction sequence number: 1>
///           <status:1> <node ID:2> <endpoint count:1> <endpoint:1>*
/// @endcode
#define ACTIVE_ENDPOINTS_REQUEST 0x0005u
#define ACTIVE_ENDPOINTS_RESPONSE 0x8005u
/// @}

/// @name Match Descriptors Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <node ID:2> <app profile ID:2>
///           <input cluster count:1> <input cluster:2>*
///           <output cluster count:1> <output cluster:2>*
/// Response: <transaction sequence number: 1>
///           <status:1> <node ID:2> <endpoint count:1> <endpoint:1>*
/// @endcode
#define MATCH_DESCRIPTORS_REQUEST 0x0006u
#define MATCH_DESCRIPTORS_RESPONSE 0x8006u
/// @}

/// @name End Device Announce and End Device Announce Response
/// <br> @{
///
/// @code
/// Request: <transaction sequence number: 1>
///          <node ID:2> <EUI64:8> <capabilities:1>
/// No response is sent.
/// @endcode
#define END_DEVICE_ANNOUNCE 0x0013u
#define END_DEVICE_ANNOUNCE_RESPONSE 0x8013u
/// @}

/// @name System Server Discovery Request / Response
/// <br> @{
///  This is broadcast and only servers which have matching services
/// respond.  The response contains the request services that the
/// recipient provides.
///
/// @code
/// Request:  <transaction sequence number: 1> <server mask:2>
/// Response: <transaction sequence number: 1>
///           <status (== EMBER_ZDP_SUCCESS):1> <server mask:2>
/// @endcode
#define SYSTEM_SERVER_DISCOVERY_REQUEST 0x0015u
#define SYSTEM_SERVER_DISCOVERY_RESPONSE 0x8015u
/// @}

/// @name Parent Announce and Parent Announce Response
/// <br> @{
///  This is broadcast and only servers which have matching children
/// respond.  The response contains the list of children that the
/// recipient now holds.
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <number of children:1> <child EUI64:8> <child Age:4>*
/// Response: <transaction sequence number: 1>
///           <number of children:1> <child EUI64:8> <child Age:4>*
/// @endcode
#define PARENT_ANNOUNCE 0x001Fu
#define PARENT_ANNOUNCE_RESPONSE 0x801Fu
/// @}

/// @name Find Node Cache Request / Response
/// <br> @{
/// This is broadcast and only discovery servers which have the information
/// for the device of interest, or the device of interest itself, respond.
/// The requesting device can then direct any service discovery requests
/// to the responder.
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <device of interest ID:2> <d-of-i EUI64:8>
/// Response: <transaction sequence number: 1>
///           <responder ID:2> <device of interest ID:2> <d-of-i EUI64:8>
/// @endcode
#define FIND_NODE_CACHE_REQUEST 0x001Cu
#define FIND_NODE_CACHE_RESPONSE 0x801Cu
/// @}

/// @name End Device Bind Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <node ID:2> <EUI64:8> <endpoint:1> <app profile ID:2>
///           <input cluster count:1> <input cluster:2>*
///           <output cluster count:1> <output cluster:2>*
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define END_DEVICE_BIND_REQUEST 0x0020u
#define END_DEVICE_BIND_RESPONSE 0x8020u
/// @}

/// @name Clear All Bindings Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <clear all bindings request EUI64 TLV:Variable>
/// Clear all bindings request EUI64 TLV:
///           <Count N:1><EUI64 1:8>...<EUI64 N:8>
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define CLEAR_ALL_BINDINGS_REQUEST 0x002Bu
#define CLEAR_ALL_BINDINGS_RESPONSE 0x802Bu
/// @}

/// @name Binding types and Request / Response
/// <br> @{
///  Bind and unbind have the same formats.  There are two possible
/// formats, depending on whether the destination is a group address
/// or a device address.  Device addresses include an endpoint, groups
/// don't.
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <source EUI64:8> <source endpoint:1>
///           <cluster ID:2> <destination address:3 or 10>
/// Destination address:
///           <0x01:1> <destination group:2>
/// Or:
///           <0x03:1> <destination EUI64:8> <destination endpoint:1>
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define UNICAST_BINDING 0x03u
#define UNICAST_MANY_TO_ONE_BINDING 0x83u
#define MULTICAST_BINDING 0x01u

#define BIND_REQUEST 0x0021u
#define BIND_RESPONSE 0x8021u
#define UNBIND_REQUEST 0x0022u
#define UNBIND_RESPONSE 0x8022u
/// @}

/// @name LQI Table Request / Response
/// <br> @{
///
///
/// @code
/// Request:  <transaction sequence number: 1> <start index:1>
/// Response: <transaction sequence number: 1> <status:1>
///           <neighbor table entries:1> <start index:1>
///           <entry count:1> <entry:22>*
///   <entry> = <extended PAN ID:8> <EUI64:8> <node ID:2>
///             <device type, RX on when idle, relationship:1>
///             <permit joining:1> <depth:1> <LQI:1>
/// @endcode
///
/// The device-type byte has the following fields:
///
/// @code
///      Name          Mask        Values
///
///   device type      0x03     0x00 coordinator
///                             0x01 router
///                             0x02 end device
///                             0x03 unknown
///
///   rx mode          0x0C     0x00 off when idle
///                             0x04 on when idle
///                             0x08 unknown
///
///   relationship     0x70     0x00 parent
///                             0x10 child
///                             0x20 sibling
///                             0x30 other
///                             0x40 previous child
///   reserved         0x10
/// @endcode
///
/// The permit-joining byte has the following fields
///
/// @code
///      Name          Mask        Values
///
///   permit joining   0x03     0x00 not accepting join requests
///                             0x01 accepting join requests
///                             0x02 unknown
///   reserved         0xFC
/// @endcode
///
#define LQI_TABLE_REQUEST 0x0031u
#define LQI_TABLE_RESPONSE 0x8031u
/// @}

/// @name Routing Table Request / Response
/// <br> @{
///
///
/// @code
/// Request:  <transaction sequence number: 1> <start index:1>
/// Response: <transaction sequence number: 1> <status:1>
///           <routing table entries:1> <start index:1>
///           <entry count:1> <entry:5>*
///   <entry> = <destination address:2>
///             <status:1>
///             <next hop:2>
///
/// @endcode
///
/// The status byte has the following fields:
/// @code
///      Name          Mask        Values
///
///   status           0x07     0x00 active
///                             0x01 discovery underway
///                             0x02 discovery failed
///                             0x03 inactive
///                             0x04 validation underway
///
///   flags            0x38
///                             0x08 memory constrained
///                             0x10 many-to-one
///                             0x20 route record required
///
///   reserved         0xC0
/// @endcode
#define ROUTING_TABLE_REQUEST 0x0032u
#define ROUTING_TABLE_RESPONSE 0x8032u
/// @}

/// @name Binding Table Request / Response
/// <br> @{
///
///
/// @code
/// Request:  <transaction sequence number: 1> <start index:1>
/// Response: <transaction sequence number: 1>
///           <status:1> <binding table entries:1> <start index:1>
///           <entry count:1> <entry:14/21>*
///   <entry> = <source EUI64:8> <source endpoint:1> <cluster ID:2>
///             <dest addr mode:1> <dest:2/8> <dest endpoint:0/1>
/// @endcode
/// <br>
/// @note If Dest. Address Mode = 0x03, then the Long Dest. Address will be
/// used and Dest. endpoint will be included.  If Dest. Address Mode = 0x01,
/// then the Short Dest. Address will be used and there will be no Dest.
/// endpoint.
///
#define BINDING_TABLE_REQUEST 0x0033u
#define BINDING_TABLE_RESPONSE 0x8033u
/// @}

/// @name Leave Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1> <EUI64:8> <flags:1>
///          The flag bits are:
///          0x40 remove children
///          0x80 rejoin
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define LEAVE_REQUEST 0x0034u
#define LEAVE_RESPONSE 0x8034u

#define LEAVE_REQUEST_REMOVE_CHILDREN_FLAG 0x40u
#define LEAVE_REQUEST_REJOIN_FLAG 0x80u
/// @}

/// @name Permit Joining Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <duration:1> <permit authentication:1>
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define PERMIT_JOINING_REQUEST 0x0036u
#define PERMIT_JOINING_RESPONSE 0x8036u
/// @}

/// @name Network Update Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <scan channels:4> <duration:1> <count:0/1> <manager:0/2>
///
///   If the duration is in 0x00 ... 0x05, 'count' is present but
///   not 'manager'.  Perform 'count' scans of the given duration on the
///   given channels.
///
///   If duration is 0xFE, 'channels' should have a single channel
///   and 'count' and 'manager' are not present.  Switch to the indicated
///   channel.
///
///   If duration is 0xFF, 'count' is not present.  Set the active
///   channels and the network manager ID to the values given.
///
///   Unicast requests always get a response, which is INVALID_REQUEST if the
///   duration is not a legal value.
///
/// Response: <transaction sequence number: 1> <status:1>
///   <scanned channels:4> <transmissions:2> <failures:2>
///   <energy count:1> <energy:1>*
/// @endcode
#define NWK_UPDATE_REQUEST 0x0038u
#define NWK_UPDATE_RESPONSE 0x8038u

#define NWK_UPDATE_ENHANCED_REQUEST 0x0039u
#define NWK_UPDATE_ENHANCED_RESPONSE 0x8039u

#define NWK_UPDATE_IEEE_JOINING_LIST_REQUEST 0x003Au
#define NWK_UPDATE_IEEE_JOINING_LIST_REPONSE 0x803Au

#define NWK_UNSOLICITED_ENHANCED_UPDATE_NOTIFY 0x803Bu

/// @}

/// @name Beacon Survey Request / Response
/// <br> @{
///
/// This command can be used by a remote device to survey the end
/// devices to determine how many potential parents they have
/// access to.
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one Beacon Survey Configuration TLV (variable octets),
/// which contain the ScanChannelListStructure (variable length)
/// and the ConfigurationBitmask (1 octet). This information provides
/// the configuration for the end device's beacon survey.
/// See R23 spec section 2.4.3.3.12 for the request and 3.2.2.2.1
/// for the ChannelListStructure.
///
/// @code
/// Response:  <transaction sequence number: 1>
///            <status: 1>
///            <TLVs: varies>
///
/// Contains one Beacon Survey Results TLV (4 octets), which contain
/// the number of on-network, off-network, potential parent and total
/// beacons recorded. If the device that received the request is not a
/// router, a Potential Parent TLV (variable octects) will be found. This
/// will contain information on the device's current parent, as well as
/// any potential parents found via beacons (up to a maximum of 5). A
/// Pan ID Conflict TLV can also found in the response.
/// See R23 spec section 2.4.4.3.13 for the response.
/// @endcode
#define BEACON_SURVEY_REQUEST 0x003Cu
#define BEACON_SURVEY_RESPONSE 0x803Cu
/// @}

/// @name Security Start Key Negotiation Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more Curve25519 Public Point TLVs (40 octets),
/// which contain an EUI64 and the 32-byte Curve public point.
/// See R23 spec section 2.4.3.4.1
///
/// @note This command SHALL NOT be APS encrypted regardless of
/// whether sent before or after the device joins the network.
/// This command SHALL be network encrypted if the device has a
/// network key, i.e. it has joined the network earlier and wants
/// to negotiate or renegotiate a new link key; otherwise, if it
/// is used prior to joining the network, it SHALL NOT be network
///  encrypted.
///
/// Response: <transaction sequence number: 1> <status:1>
///           <TLVs: varies>
///
/// Contains one or more Curve25519 Public Point TLVs (40 octets),
/// which contain an EUI64 and the 32-byte Curve public point, or
/// Local TLVs.
/// See R23 spec section 2.4.4.4.1
///
/// @note This command SHALL NOT be APS encrypted. When performing
/// Key Negotiation with an unauthenticated neighbor that is not
/// yet on the network, network layer encryption SHALL NOT be used
/// on the message. If the message is being sent to unauthenticated
/// device that is not on the network and is not a neighbor, it
/// SHALL be relayed as described in section 4.6.3.7.7. Otherwise
/// the message SHALL have network layer encryption.
/// @endcode
#define KEY_NEGOTIATION_REQUEST 0x0040u
#define KEY_NEGOTIATION_RESPONSE 0x8040u
/// @}

/// @name Retrieve Authentication Token Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more Authentication Token ID TLVs (1 octet),
/// which contain the TLV Type Tag ID of the source of the
/// authentication token. See R23 spec section 2.4.3.4.2
///
/// Response: <transaction sequence number: 1> <status:1>
///           <TLVs: varies>
///
/// Contains one or more 128-bit Symmetric Passphrase Global TLVs
/// (16 octets), which contain the symmetric passphrase authentication
/// token. See R23 spec section 2.4.4.4.2
///
/// @endcode
#define AUTHENTICATION_TOKEN_REQUEST 0x0041u
#define AUTHENTICATION_TOKEN_RESPONSE 0x8041u
/// @}

/// @name Retrieve Authentication Level Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more Target IEEE Address TLVs (8 octets),
/// which contain the EUI64 of the device of interest.
/// See R23 spec section 2.4.3.4.3
///
/// Response: <transaction sequence number: 1> <status:1>
///           <TLVs: varies>
///
/// Contains one or more Device Authentication Level TLVs
/// (10 octets), which contain the EUI64 of the inquired device,
/// along with the its initial join method and its active link
/// key update method.
/// See R23 spec section 2.4.4.4.3
///
/// @endcode
#define AUTHENTICATION_LEVEL_REQUEST      0x0042u
#define AUTHENTICATION_LEVEL_RESPONSE     0x8042u
/// @}

/// @name Set Configuration Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more Global TLVs (1 octet),
/// which contain the TLV Type Tag ID, and their
/// value.
///
/// Response: <transaction sequence number: 1> <status:1>
///
/// @endcode
#define SET_CONFIGURATION_REQUEST      0x0043u
#define SET_CONFIGURATION_RESPONSE     0x8043u
/// @}

/// @name Get Configuration Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more TLVs (1 octet),
/// which the sender wants to get information
///
/// Response: <transaction sequence number: 1> <status:1>
///           <TLVs: varies>
///
/// Contains one or more TLV tag Ids and their values
/// in response to the request
///
/// @endcode
#define GET_CONFIGURATION_REQUEST      0x0044u
#define GET_CONFIGURATION_RESPONSE     0x8044u
/// @}

/// @name Security Start Key Update Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains one or more TLVs. These TLVs can be Selected Key
/// Negotiation Method TLVs (10 octets), Fragmentation Parameters
/// Global TLVs (5 octets), or other TLVs.
/// See R23 spec section 2.4.3.4.6
///
/// @note This SHALL NOT be APS encrypted or NWK encrypted if the
/// link key update mechanism is done as part of the initial join
/// and before the receiving device has been issued a network
/// key. This SHALL be both APS encrypted and NWK encrypted if
/// the link key update mechanism is performed to refresh the
/// link key when the receiving device has the network key and
/// has previously successfully joined the network.
///
/// Response: <transaction sequence number: 1> <status:1>
///
/// See R23 spec section 2.4.4.4.6
///
/// @note This command SHALL be APS encrypted.
/// @endcode
#define KEY_UPDATE_REQUEST 0x0045u
#define KEY_UPDATE_RESPONSE 0x8045u
/// @}

/// @name Security Decommission Request / Response
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <security decommission request EUI64 TLV:Variable>
/// Security Decommission request EUI64 TLV:
///           <Count N:1><EUI64 1:8>...<EUI64 N:8>
/// Response: <transaction sequence number: 1> <status:1>
/// @endcode
#define SECURITY_DECOMMISSION_REQUEST 0x0046u
#define SECURITY_DECOMMISSION_RESPONSE 0x8046u
/// @}

/// @name Challenge for APS frame counter synchronization
/// <br> @{
///
/// @code
/// Request:  <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains at least the APS Frame Counter Challenge TLV, which holds the
/// sender EUI and the 64 bit challenge value.
///
/// Response: <transaction sequence number: 1>
///           <TLVs: varies>
///
/// Contains at least the APS Frame Counter Response TLV, which holds the
/// sender EUI, received challenge value, APS frame counter, challenge
/// security frame counter, and 8-byte MIC.
///
/// @endcode
#define SECURITY_CHALLENGE_REQUEST      0x0047u
#define SECURITY_CHALLENGE_RESPONSE     0x8047u
/// @}

/// @name Unsupported
/// <br> @{
///  Not mandatory and not supported.
#define COMPLEX_DESCRIPTOR_REQUEST 0x0010u
#define COMPLEX_DESCRIPTOR_RESPONSE 0x8010u
#define USER_DESCRIPTOR_REQUEST 0x0011u
#define USER_DESCRIPTOR_RESPONSE 0x8011u
#define DISCOVERY_REGISTER_REQUEST 0x0012u
#define DISCOVERY_REGISTER_RESPONSE 0x8012u
#define USER_DESCRIPTOR_SET 0x0014u
#define USER_DESCRIPTOR_CONFIRM 0x8014u
#define NETWORK_DISCOVERY_REQUEST 0x0030u
#define NETWORK_DISCOVERY_RESPONSE 0x8030u
#define DIRECT_JOIN_REQUEST 0x0035u
#define DIRECT_JOIN_RESPONSE 0x8035u

/// @name Discovery Cache Request / Response
/// <br> @{
/// DEPRECATED
/// @code
/// Request:  <transaction sequence number: 1>
///           <source node ID:2> <source EUI64:8>
/// Response: <transaction sequence number: 1>
///           <status (== EMBER_ZDP_SUCCESS):1>
/// @endcode
#define DISCOVERY_CACHE_REQUEST 0x0012u
#define DISCOVERY_CACHE_RESPONSE 0x8012u
/// @}

#define CLUSTER_ID_RESPONSE_MINIMUM 0x8000u
/// @}

//@} \\END ZigBee Device Object (ZDO) Definitions

#endif // SILABS_ZIGBEE_DEVICE_STACK_H
