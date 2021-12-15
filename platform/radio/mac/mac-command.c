/***************************************************************************//**
 * @file mac-command.c
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "buffer_manager/buffer-management.h"
#include "buffer_manager/legacy-packet-buffer.h"
#include "sl_status.h"

#include "stack/core/ember-stack.h"

#include "mac-command.h"
#include "mac-types.h"
#include "mac-header.h"
#include "lower-mac.h"
#include "upper-mac.h"

#ifndef EM_USE_LONG_ADDRESS
#define EM_USE_LONG_ADDRESS   0xFFFE
#endif
//beacon related
#define MAC_SUPERFRAME_BEACON_ORDER_MASK  (0x000F)
#define MAC_SUPERFRAME_BEACON_ORDER_SHIFT (0)
#define MAC_SUPERFRAME_ORDER_MASK         (0x00F0)
#define MAC_SUPERFRAME_ORDER_SHIFT        (4)
#define MAC_SUPERFRAME_FINAL_CAP_MASK     (0x0F00)
#define MAC_SUPERFRAME_FINAL_CAP_SHIFT    (8)
#define MAC_SUPERFRAME_BATTERY_EXTENSION  (0x1000)
#define MAC_SUPERFRAME_PAN_COORD          (0x4000)
#define MAC_SUPERFRAME_ASSOC_PERMIT       (0x8000)

#define MAC_BEACON_GTS_PERMIT    (0x80)

#define BEACON_SUPERFRAME_INDEX      0
#define BEACON_GTS_INDEX             2
#define BEACON_PENDING_ADDRESS_INDEX 3
#define BEACON_ADDRESS_LIST_INDEX    4

#define BASE_HEADER_LENGTH 5 // frame control, sequence, PAN ID.
#define ENHANCED_BEACON_FINAL_INFO_ELEMENTS_LENGTH  9
#define MAX_MAC_HEADER_LENGTH 126
//Zigbee Company ID
//This is assigned by IEEE and used for Zigbee Specific Information Elements
//in 15.4-2012 frames
// ToDo: move? This is zigbee-specific but used in enhanced_becaon_request call
// which origicates from mac (scan.c)
#define ZIGBEE_IEEE_COMPANY_ID 0x4A191B

#define BEACON_SUPERFRAME           \
  (MAC_SUPERFRAME_BEACON_ORDER_MASK \
   | MAC_SUPERFRAME_ORDER_MASK      \
   | MAC_SUPERFRAME_FINAL_CAP_MASK)

static uint8_t headerInfoElement[] = {
  0x00,
  0x3F,
};

PacketHeader sl_mac_make_command(uint8_t command,
                                 uint16_t macFrameControl,
                                 uint8_t *destination,
                                 uint16_t destinationPanId,
                                 uint8_t *source,
                                 uint16_t sourcePanId,
                                 uint8_t *frame,
                                 uint8_t frameLength,
                                 Buffer payloadBuffer,
                                 Buffer infoElementBuffer,
                                 uint8_t nwk_index)
{
  uint16_t srcAddressMode = (macFrameControl & MAC_FRAME_SOURCE_MODE_MASK);
  uint16_t destAddressMode = (macFrameControl & MAC_FRAME_DESTINATION_MODE_MASK);

  Buffer returnHeader = NULL_BUFFER;
  Buffer header = emAllocateBuffer(MAX_MAC_HEADER_LENGTH);
  if (header != NULL_BUFFER) {
    MEMSET(emGetBufferPointer(header), 0, MAX_MAC_HEADER_LENGTH);
    uint8_t *contents = emGetBufferPointer(header);
    uint8_t *finger = emGetBufferPointer(header);
    uint8_t macFrameLength = 0;
    uint8_t infoElementLength = 0;

    if (command != MAC_INVALID_COMMAND) {
      macFrameControl |= MAC_FRAME_TYPE_CONTROL;
    }

    *finger++ = LOW_BYTE(macFrameControl);
    *finger++ = HIGH_BYTE(macFrameControl);
    finger++;   // sequence number, set when transmitted

    if (destAddressMode != MAC_FRAME_DESTINATION_MODE_NONE) {
      *finger++ = LOW_BYTE(destinationPanId);
      *finger++ = HIGH_BYTE(destinationPanId);
    }

    uint8_t destLength = (destAddressMode == MAC_FRAME_DESTINATION_MODE_SHORT)
                         ? 2
                         : 8;
    MEMMOVE(finger, destination, destLength);
    finger += destLength;

    if (srcAddressMode != MAC_FRAME_SOURCE_MODE_NONE
        && !(macFrameControl & MAC_FRAME_FLAG_INTRA_PAN)) {
      uint16_t panId = sourcePanId;
      *finger++ = LOW_BYTE(panId);
      *finger++ = HIGH_BYTE(panId);
    }

    uint8_t sourceLength = (srcAddressMode == MAC_FRAME_SOURCE_MODE_SHORT)
                           ? 2
                           : ((srcAddressMode == MAC_FRAME_SOURCE_MODE_LONG) ? 8 : 0);
    MEMMOVE(finger, source, sourceLength);
    finger += sourceLength;

    macFrameLength = finger - contents;

    if (infoElementBuffer != NULL_BUFFER) {
      MEMCOPY(finger, headerInfoElement, sizeof(headerInfoElement));
      finger += sizeof(headerInfoElement);
      uint8_t *infoElement = emGetBufferPointer(infoElementBuffer);
      infoElementLength = emGetBufferLength(infoElementBuffer);
      MEMCOPY(finger, infoElement, infoElementLength);
      finger += infoElementLength;
      infoElementLength += sizeof(headerInfoElement); //account for the length in the headerLength sum below
    }

    if (command != MAC_INVALID_COMMAND) {
      *finger++ = command;
      macFrameLength++;
      MEMCOPY(finger, frame, frameLength);
      finger += frameLength;
    }

    uint16_t headerLength = macFrameLength + frameLength + infoElementLength;
    emSetBufferLength(header, headerLength); //set the buffer size to the actual buffer

    uint8_t macInfoFlags = EMBER_MAC_INFO_TYPE_MAC_COMMAND;
    if (command == MAC_INVALID_COMMAND) {
      macInfoFlags = EMBER_MAC_INFO_TYPE_PASSTHROUGH;
    }
    macInfoFlags = (macInfoFlags
                    | ((macFrameControl & EMBER_MAC_HEADER_FC_FRAME_PENDING_BIT)
                       ? EMBER_MAC_INFO_FRAME_PENDING_MASK : 0)
                    | ((macFrameControl & EMBER_MAC_HEADER_FC_ACK_REQUEST_BIT)
                       ? EMBER_MAC_INFO_OUTGOING_FRAME_PENDING : 0));
    returnHeader = sl_mac_make_raw_message(NULL_BUFFER,
                                           macInfoFlags,
                                           NWK_INDEX);

    emberAppendToLinkedBuffers(returnHeader, emGetBufferPointer(header), emGetBufferLength(header));
    emSetPayloadLink(returnHeader, payloadBuffer);
  }

  header = NULL_BUFFER;
  return returnHeader;
}

Buffer sl_mac_make_association_request(uint8_t mac_index,
                                       uint8_t nwk_index,
                                       EmberNodeId parent_id,
                                       EmberPanId pan_id,
                                       uint8_t capabilities)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + mac_index;

  return sl_mac_make_command(MAC_ASSOCIATION_REQUEST,
                             (MAC_FRAME_DESTINATION_MODE_SHORT
                              | MAC_FRAME_SOURCE_MODE_LONG
                              | MAC_FRAME_FLAG_ACK_REQUIRED),
                             (uint8_t *) &parent_id,
                             pan_id,
                             (uint8_t *) &state->nwk_radio_parameters[NWK_INDEX].local_eui,
                             SL_BROADCAST_PAN_ID,
                             &capabilities,
                             1,
                             NULL_BUFFER,
                             NULL_BUFFER,
                             NWK_INDEX);
}

Buffer sl_mac_make_association_response(uint8_t mac_index,
                                        uint8_t nwk_index,
                                        EmberEUI64 long_addr,
                                        EmberNodeId short_addr,
                                        uint8_t status)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  uint16_t pan_id = state->nwk_radio_parameters[NWK_INDEX].pan_id;

  uint8_t payload[3];
  payload[0] = LOW_BYTE(short_addr);
  payload[1] = HIGH_BYTE(short_addr);
  payload[2] = status;

  return sl_mac_make_command(MAC_ASSOCIATION_RESPONSE,
                             (MAC_FRAME_DESTINATION_MODE_LONG
                              | MAC_FRAME_SOURCE_MODE_LONG
                              | MAC_FRAME_FLAG_INTRA_PAN
                              | MAC_FRAME_FLAG_ACK_REQUIRED),
                             (uint8_t *) long_addr,
                             pan_id,
                             (uint8_t *) &state->nwk_radio_parameters[NWK_INDEX].local_eui,
                             0,
                             payload,
                             sizeof(payload),
                             NULL_BUFFER,
                             NULL_BUFFER,
                             NWK_INDEX);
}

Buffer sl_mac_make_data_request(uint8_t mac_index, uint8_t nwk_index)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint16_t short_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;
  uint8_t *long_id = state->nwk_radio_parameters[NWK_INDEX].local_eui;
  uint16_t pan_id = state->nwk_radio_parameters[NWK_INDEX].pan_id;
  uint16_t parentShortId = state->nwk_radio_parameters[NWK_INDEX].parent_node_id;
  uint8_t *parentLongId = state->nwk_radio_parameters[NWK_INDEX].parent_eui;

  if (parentShortId != EMBER_NULL_NODE_ID) {
    return sl_mac_make_command(MAC_DATA_REQUEST,
                               (short_id < 0xFFFE
                                ? (MAC_FRAME_SOURCE_MODE_SHORT
                                   | MAC_FRAME_DESTINATION_MODE_SHORT
                                   | MAC_FRAME_FLAG_INTRA_PAN
                                   | MAC_FRAME_FLAG_ACK_REQUIRED)
                                : (MAC_FRAME_SOURCE_MODE_LONG
                                   | MAC_FRAME_DESTINATION_MODE_SHORT
                                   | MAC_FRAME_FLAG_INTRA_PAN
                                   | MAC_FRAME_FLAG_ACK_REQUIRED)),
                               (uint8_t *) &parentShortId,
                               pan_id,
                               (short_id < 0xFFFE)
                               ? (uint8_t *) &short_id
                               : long_id,
                               0, // source pan, don't care
                               NULL,
                               0,
                               NULL_BUFFER,
                               NULL_BUFFER,
                               NWK_INDEX);
  } else {
    return sl_mac_make_command(MAC_DATA_REQUEST,
                               (short_id < 0xFFFE
                                ? (MAC_FRAME_SOURCE_MODE_SHORT
                                   | MAC_FRAME_DESTINATION_MODE_LONG
                                   | MAC_FRAME_FLAG_INTRA_PAN
                                   | MAC_FRAME_FLAG_ACK_REQUIRED)
                                : (MAC_FRAME_SOURCE_MODE_LONG
                                   | MAC_FRAME_DESTINATION_MODE_LONG
                                   | MAC_FRAME_FLAG_INTRA_PAN
                                   | MAC_FRAME_FLAG_ACK_REQUIRED)),
                               parentLongId,
                               pan_id,
                               (short_id < 0xFFFE)
                               ? (uint8_t *) &short_id
                               : long_id,
                               0, // source pan, don't care
                               NULL,
                               0,
                               NULL_BUFFER,
                               NULL_BUFFER,
                               NWK_INDEX);
  }
}

Buffer sl_mac_make_orphan_notification(uint8_t mac_index, uint8_t nwk_index)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint8_t* eui = state->nwk_radio_parameters[NWK_INDEX].local_eui;
  uint16_t broadcast_addr = SL_BROADCAST_ADDRESS;

  return sl_mac_make_command(MAC_ORPHAN_NOTIFICATION,
                             MAC_FRAME_SOURCE_MODE_LONG
                             | MAC_FRAME_DESTINATION_MODE_SHORT,
                             (uint8_t *) &broadcast_addr,
                             SL_BROADCAST_PAN_ID,
                             eui,
                             SL_BROADCAST_PAN_ID,
                             NULL,
                             0,
                             NULL_BUFFER,
                             NULL_BUFFER,
                             NWK_INDEX);
}

Buffer sl_mac_make_beacon_request(uint8_t mac_index, uint8_t nwk_index)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint16_t short_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;
  uint16_t broadcast_addr = SL_BROADCAST_ADDRESS;

  return sl_mac_make_command(MAC_BEACON_REQUEST,
                             MAC_FRAME_SOURCE_MODE_NONE | MAC_FRAME_DESTINATION_MODE_SHORT,
                             (uint8_t *) &broadcast_addr,
                             SL_BROADCAST_PAN_ID,
                             (uint8_t *) &short_id,
                             0,
                             NULL,
                             0,
                             NULL_BUFFER,
                             NULL_BUFFER,
                             NWK_INDEX);
}

Buffer sl_mac_make_enhanced_beacon_request(uint8_t mac_index,
                                           uint8_t nwk_index,
                                           Buffer payload_info_elements)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  uint8_t *long_id = state->nwk_radio_parameters[NWK_INDEX].local_eui;

  uint8_t destination[] = { 0xFF, 0xFF };

  uint16_t frameControl = (MAC_FRAME_SOURCE_MODE_LONG
                           | MAC_FRAME_DESTINATION_MODE_SHORT
                           | MAC_FRAME_FLAG_INTRA_PAN
                           | MAC_FRAME_VERSION_2012);

  if (payload_info_elements != NULL_BUFFER) {
    frameControl |= MAC_FRAME_FLAG_IE_LIST_PRESENT;
  }

  return sl_mac_make_command(MAC_BEACON_REQUEST,
                             frameControl,
                             destination,
                             SL_BROADCAST_PAN_ID,   // dest PAN ID
                             long_id,
                             SL_BROADCAST_PAN_ID,   // source PAN ID (suppressed)
                             NULL,                  // frame pointer
                             0,                     // frame length
                             NULL_BUFFER,           // payload (beacon request has none)
                             payload_info_elements,
                             NWK_INDEX);
}

Buffer sl_mac_make_coordinator_realign(uint8_t mac_index,
                                       uint8_t nwk_index,
                                       EmberEUI64 long_addr,
                                       EmberNodeId short_addr)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  uint16_t short_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;
  uint16_t pan_id = state->nwk_radio_parameters[NWK_INDEX].pan_id;
  uint8_t myChannel = state->nwk_radio_parameters[NWK_INDEX].channel;
  uint8_t *long_id = state->nwk_radio_parameters[NWK_INDEX].local_eui;

  uint8_t payload[7];
  payload[0] = LOW_BYTE(pan_id);
  payload[1] = HIGH_BYTE(pan_id);
  payload[2] = LOW_BYTE(short_id);
  payload[3] = HIGH_BYTE(short_id);
  payload[4] = myChannel;
  payload[5] = LOW_BYTE(short_addr);
  payload[6] = HIGH_BYTE(short_addr);

  return sl_mac_make_command(MAC_COORDINATOR_REALIGN,
                             (MAC_FRAME_DESTINATION_MODE_LONG
                              | MAC_FRAME_SOURCE_MODE_LONG),
                             (uint8_t *) long_addr,
                             SL_BROADCAST_PAN_ID,
                             long_id,
                             pan_id,
                             payload,
                             sizeof(payload),
                             NULL_BUFFER,
                             NULL_BUFFER,
                             NWK_INDEX);
}

//-----------------------------------------------------------------------------
// Beacons

Buffer sl_mac_make_beacon(uint8_t mac_index,
                          uint8_t nwk_index,
                          uint16_t superframe,
                          Buffer beacon_payload)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint16_t short_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;
  uint8_t *long_id = state->nwk_radio_parameters[NWK_INDEX].local_eui;
  uint16_t pan_id = state->nwk_radio_parameters[NWK_INDEX].pan_id;

  uint8_t beacon_header[MAX_MAC_HEADER_LENGTH];

  uint8_t macInfoFlags = (EMBER_MAC_INFO_TYPE_MAC_COMMAND);

  uint8_t *finger = beacon_header;

  if (short_id == EM_USE_LONG_ADDRESS) {
    *finger++ = LOW_BYTE(EMBER_MAC_BEACON_LONG_FRAME_CONTROL);
    *finger++ = HIGH_BYTE(EMBER_MAC_BEACON_LONG_FRAME_CONTROL);
  } else {
    *finger++ = LOW_BYTE(EMBER_MAC_BEACON_SHORT_FRAME_CONTROL);
    *finger++ = HIGH_BYTE(EMBER_MAC_BEACON_SHORT_FRAME_CONTROL);
  }
  finger++;  // sequence number, set when transmitted
  *finger++ = LOW_BYTE(pan_id);
  *finger++ = HIGH_BYTE(pan_id);

  // mac-test-app require a provision to generate beacon using both
  // short as well as extended addressing modes.
  if (short_id == EM_USE_LONG_ADDRESS) {
    MEMMOVE(finger, long_id, 8);
    finger += 8;
  } else {
    *finger++ = LOW_BYTE(short_id);
    *finger++ = HIGH_BYTE(short_id);
  }

  *finger++ = LOW_BYTE(superframe);
  *finger++ = HIGH_BYTE(superframe);
  *finger++ = 0;
  *finger++ = 0;

  PacketHeader beacon = NULL_BUFFER;

  beacon = sl_mac_make_raw_message(NULL_BUFFER,
                                   macInfoFlags,
                                   NWK_INDEX);

  if (beacon == NULL_BUFFER) {
    return beacon;
  }
  emberAppendToLinkedBuffers(beacon, beacon_header, (finger - beacon_header));
  emSetPayloadLink(beacon, beacon_payload);

  return beacon;
}

Buffer sl_mac_make_enhanced_beacon(uint8_t mac_index,
                                   uint8_t nwk_index,
                                   uint16_t superframe,
                                   Buffer beacon_payload,
                                   Buffer payload_info_elements)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint8_t *long_id = state->nwk_radio_parameters[NWK_INDEX].local_eui;
  uint16_t pan_id = state->nwk_radio_parameters[NWK_INDEX].pan_id;
  uint16_t node_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;

  PacketHeader beacon = NULL_BUFFER;

  uint8_t payload_info_size = emGetBufferLength(payload_info_elements);
  uint8_t payload_size = emGetBufferLength(beacon_payload);
  uint8_t size = (BASE_HEADER_LENGTH
                  + EUI64_SIZE
                  + payload_size
                  + payload_info_size /* 9 */
                  + ENHANCED_BEACON_FINAL_INFO_ELEMENTS_LENGTH);
  uint8_t *finger;

  uint8_t macInfoFlags = (EMBER_MAC_INFO_TYPE_MAC_COMMAND);

  beacon = sl_mac_make_raw_message(NULL_BUFFER, macInfoFlags, NWK_INDEX);
  emberExtendLinkedBuffer(beacon, size);

  if (beacon == NULL_BUFFER) {
    return beacon;
  }

  uint16_t frameControl = (MAC_FRAME_SOURCE_MODE_LONG
                           | MAC_FRAME_DESTINATION_MODE_NONE
                           | MAC_FRAME_FLAG_IE_LIST_PRESENT
                           | MAC_FRAME_VERSION_2012);

  finger = emGetBufferPointer(beacon) + EMBER_MAC_IN_MEMORY_OVERHEAD;

  *finger++ = LOW_BYTE(frameControl);
  *finger++ = HIGH_BYTE(frameControl);
  finger++; // sequence number, set when transmitted
  *finger++ = LOW_BYTE(pan_id);
  *finger++ = HIGH_BYTE(pan_id);

  MEMMOVE(finger, long_id, 8);
  finger += 8;

  if (payload_info_elements != NULL_BUFFER) {
    uint8_t *infoElement = emGetBufferPointer(payload_info_elements);
    MEMCOPY(finger, infoElement, payload_info_size);
    finger = finger + payload_info_size;
  }

  if (beacon_payload != NULL_BUFFER) {
    uint8_t *payload = emGetBufferPointer(beacon_payload);
    MEMCOPY(finger, payload, payload_size);
    finger = finger + payload_size;
  }

  *finger++ = LOW_BYTE(superframe);
  *finger++ = HIGH_BYTE(superframe);
  *finger++ = LOW_BYTE(node_id);
  *finger++ = HIGH_BYTE(node_id);
  *finger++ = 0x41,
  *finger++ = 0x00,
  #if defined(EMBER_TEST)
  *finger++ = 0x1B;
  #else
  *finger++ = sl_mac_lower_mac_get_radio_power(MAC_INDEX);
  //emFindEbrPowerByEui64(beaconRequesterEui); //sToDo: what should go here?
 #endif

  uint8_t termIE[] = {
    0x00,
    0xF8
  };

  MEMMOVE(finger, termIE, sizeof(termIE));
  finger += sizeof(termIE);

  return beacon;
}

#define MAX_INFO_ELEMENT_SIZE 25 //??
// To enable unknown information elements in enhanced beacon request, mainly required for
// required for mac certification test.
#ifdef MAC_TEST_COMMANDS_SUPPORT
extern bool includeUnknownIEsInEbr; //from zigbee
#endif  // MAC_TEST_COMMANDS_SUPPORT

#ifndef UNIFIED_MAC_SCRIPTED_TEST
// Needed for Zigbee enhanced beacon request payload
void emberGetExtendedPanId(uint8_t *resultLocation);
#endif

//ToDo: this whole code and anything else related to enhanced beacon probably
// needs to be removed from umac, and ported back to zigbee
Buffer sli_mac_make_enhanced_beacon_request_payload_info(uint8_t mac_index,
                                                         uint8_t nwk_index,
                                                         bool first_join)
{
  // Current upper mac state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;
  uint16_t short_id = state->nwk_radio_parameters[NWK_INDEX].local_node_id;
  int8_t radio_power = sl_mac_lower_mac_get_radio_power(MAC_INDEX);

  Buffer info_element_buffer;
  info_element_buffer = emAllocateBuffer(MAX_INFO_ELEMENT_SIZE);
  if (info_element_buffer != NULL_BUFFER) {
    uint8_t payloadInfoElementBeaconRequestWithFilter[] = {
      0x03, // Payload IE frame control
      0x88, //   Group ID = MLME Nested IE

      0x01, // Sub-IE descriptor
      0x1e, //   Group ID = Enhanced Beacon Filter

      0x01, // Enhanced Beacon Filter IE payload
            //  (consider only beacons with Permit Join = true)

//enable this define to test unrecognized IEs
//#define EXTRA_ELEMENT_TESTS
#ifdef EXTRA_ELEMENT_TESTS
      0x09,
#else
      0x06, // zigbee IE
#endif
      0x90, //vendor specific nested

      BYTE_0(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_1(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_2(ZIGBEE_IEEE_COMPANY_ID),

      0x41, //sub IE - Tx Power
      0x00,

      0x1B, //TODO fill in the TX Power
#ifdef EXTRA_ELEMENT_TESTS

      0x81,
      0x00,
      0xCC,

      0x04,
      0x90,

      0x84,
      0xED,
      0xCA,

      0xBB,

#endif

      0x00, // Payload Termination IE
      0xf8,
    };

#ifdef MAC_TEST_COMMANDS_SUPPORT
    // This is to test unrecognised IEs, required for mac certification test
    // TP/154/MAC/BEACON-MANAGEMENT-06
    uint8_t payloadInfoElementBeaconRequestWithUnknownIEs[] = {
      0x05, // Unrecognized 15.4 payload IE
      0x90,

      0x84, // Unknown vendor OUI
      0xED,
      0xCA,

      0xBB,
      0xAA,

      0x03,  // Payload IE frame control
      0x88,  //   Group ID = MLME Nested IE

      0x01,  // Sub-IE descriptor
      0x1e,  //   Group ID = Enhanced Beacon Filter

      0x01,  // Enhanced Beacon Filter IE payload
             //  (consider only beacons with Permit Join = true)

      0x09,
      0x90, //vendor specific nested

      BYTE_0(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_1(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_2(ZIGBEE_IEEE_COMPANY_ID),

      0xC1, //Reserved zigbee sub-Id
      0x00,
      0xCC, // content

      0x41, //sub IE - Tx Power
      0x00,

      0x1B, //TODO fill in the TX Power

      0x00,  // Payload Termination IE
      0xf8,
    };
#endif  // MAC_TEST_COMMANDS_SUPPORT

    uint8_t payloadInfoElementBeaconRequestWithExtPanId[] = {
      0x12, // Payload IE frame control
      0x90, //

      BYTE_0(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_1(ZIGBEE_IEEE_COMPANY_ID),
      BYTE_2(ZIGBEE_IEEE_COMPANY_ID),

      0x0A, // Zigbee rejoin sub-ie
      0x00,

      // Extended PAN ID (filled in later)
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,
      0x00,

      0x00, //sender short ID
      0x00,

      0x41, //tx power ie
      0x00,
      0x1B, //TODO fill in the TX Power

      0x00, // Payload Termination
      0xf8,
    };
    if (!first_join) {
#ifndef UNIFIED_MAC_SCRIPTED_TEST
      emberGetExtendedPanId(&payloadInfoElementBeaconRequestWithExtPanId[4 + 3]);
#endif
      payloadInfoElementBeaconRequestWithExtPanId[12 + 3] = LOW_BYTE(short_id);
      payloadInfoElementBeaconRequestWithExtPanId[13 + 3] = HIGH_BYTE(short_id);

      payloadInfoElementBeaconRequestWithExtPanId[19] =  radio_power;
    } else {
#ifdef MAC_TEST_COMMANDS_SUPPORT
      if (includeUnknownIEsInEbr) {
        payloadInfoElementBeaconRequestWithUnknownIEs[22] = radio_power;
      } else {
#endif  // MAC_TEST_COMMANDS_SUPPORT
      payloadInfoElementBeaconRequestWithFilter[12] =  radio_power;
#ifdef MAC_TEST_COMMANDS_SUPPORT
    }
#endif  // MAC_TEST_COMMANDS_SUPPORT
    }

    uint8_t info_element_buffer_size = (first_join
                                        ?
#ifdef MAC_TEST_COMMANDS_SUPPORT
                                        includeUnknownIEsInEbr
                                        ? sizeof(payloadInfoElementBeaconRequestWithUnknownIEs) :
#endif  // MAC_TEST_COMMANDS_SUPPORT
                                        sizeof(payloadInfoElementBeaconRequestWithFilter)
                                        : sizeof(payloadInfoElementBeaconRequestWithExtPanId));
    uint8_t *finger = first_join
                      ?
#ifdef MAC_TEST_COMMANDS_SUPPORT
                      includeUnknownIEsInEbr ? payloadInfoElementBeaconRequestWithUnknownIEs :
#endif  // MAC_TEST_COMMANDS_SUPPORT
                      payloadInfoElementBeaconRequestWithFilter
                      : payloadInfoElementBeaconRequestWithExtPanId;

    emSetBufferLength(info_element_buffer, info_element_buffer_size);
    uint8_t *info_element_buffer_ptr = emGetBufferPointer(info_element_buffer);
    MEMCOPY(info_element_buffer_ptr, finger, info_element_buffer_size);
  }

  return info_element_buffer;
}
