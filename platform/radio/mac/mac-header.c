/***************************************************************************//**
 * @file mac-header.c
 * @brief Generic mac header methods
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
#include "stack/core/ember-stack.h"
#include "mac-types.h"
#include "mac-header.h"
#include "scan.h"
#include "lower-mac.h"
#include "upper-mac.h"

#ifdef MAC_TEST_COMMANDS_SUPPORT
extern bool emEnableMacCertificationTestMode;
#endif

const EmberMacFilterMatchData* sl_mac_stack_filter_list = NULL;
const EmberMacFilterMatchData* sl_mac_custom_filter_list = NULL;

WEAK(uint16_t emberFetchLowHighInt16u(const uint8_t *contents))
{
  return HIGH_LOW_TO_INT(contents[1], contents[0]);
}

WEAK(void emberStoreLowHighInt16u(uint8_t *contents, uint16_t value))
{
  contents[0] = LOW_BYTE(value);
  contents[1] = HIGH_BYTE(value);
}

void emStoreInt32u(bool lowHigh, uint8_t* contents, uint32_t value)
{
  uint8_t ii;
  for (ii = 0; ii < 4; ii++) {
    uint8_t index = (lowHigh ? ii : 3 - ii);
    contents[index] = (uint8_t)(value & 0xFF);
    value = (value >> 8);
  }
}

uint32_t emFetchInt32u(bool lowHigh, const uint8_t* contents)
{
  uint8_t b0;
  uint8_t b1;
  uint8_t b2;
  uint8_t b3;

  if (lowHigh) {
    b0 = contents[3];
    b1 = contents[2];
    b2 = contents[1];
    b3 = contents[0];
  } else {
    b0 = contents[0];
    b1 = contents[1];
    b2 = contents[2];
    b3 = contents[3];
  }
  return ((((uint32_t) ((((uint16_t) b0) << 8) | ((uint16_t) b1)))
           << 16)
          | (uint32_t) ((((uint16_t) b2) << 8) | ((uint16_t) b3)));
}

sl_status_t sl_mac_set_filter_match_list(bool custom_filter,
                                         const EmberMacFilterMatchData* mac_filter_match_list)
{
  // The stack filter may be NULL (e.g. zigbee's
  // is NULL if neither Green Power nor ZLL is included)
  // In any case, we do not check for NULL/valid filters here,
  // since stack filters, and custom filters could overlap.
  // The check should be done on the stack e.g. in zigbee in
  // emberSetMacFilterMatchList()

  if (custom_filter) {
    sl_mac_custom_filter_list = mac_filter_match_list;
  } else {
    sl_mac_stack_filter_list = mac_filter_match_list;
  }
  return SL_STATUS_OK;
}

// Only intended to be used with MAC data messages.
bool sli_mac_filter_match_check(uint8_t mac_index, uint8_t nwk_index, uint8_t* mac_header)
{
  // Current upper MAC state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint16_t control = emberFetchLowHighInt16u(mac_header);
  uint16_t cleanControl = (control & ~(MAC_FRAME_FLAG_FRAME_PENDING
                                       | MAC_FRAME_FLAG_ACK_REQUIRED));
  EmberMacFilterMatchData incomingMessage = EMBER_MAC_FILTER_MATCH_ENABLED;

  uint8_t destIndex = 3;  // if no dest PAN is present,
                          // this is the index

  if (!sl_mac_stack_filter_list && !sl_mac_custom_filter_list) {
    return false;
  }

  if (((cleanControl & MAC_FRAME_DESTINATION_MODE_MASK)
       != MAC_FRAME_DESTINATION_MODE_NONE)) {
    uint16_t panDest = emberFetchLowHighInt16u(mac_header + 3);
    if (panDest == 0xFFFF) {
      incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_BROADCAST;
    } else { // Assume we only receive messages destined for our PAN
      incomingMessage = EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_LOCAL;
    }
    destIndex += 2;
  } // else
    // incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_PAN_DEST_NONE

  if ((cleanControl & MAC_FRAME_FLAG_INTRA_PAN)
      == MAC_FRAME_FLAG_INTRA_PAN) {
    incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_LOCAL;
  } else if ((cleanControl & MAC_FRAME_SOURCE_MODE_MASK)
             != MAC_FRAME_SOURCE_MODE_NONE) {
    // Then source PAN must be present.
    uint8_t panSourceIndex = destIndex
                             + (((cleanControl & MAC_FRAME_DESTINATION_MODE_MASK)
                                 == MAC_FRAME_DESTINATION_MODE_LONG)
                                ? EUI64_SIZE
                                : 2);
    uint16_t panSource = emberFetchLowHighInt16u(mac_header + panSourceIndex);

    if (panSource == state->nwk_radio_parameters[NWK_INDEX].pan_id) {
      incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_LOCAL;
    } else {
      incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_PAN_SOURCE_NON_LOCAL;
    }
  }

  if ((cleanControl & MAC_FRAME_SOURCE_MODE_MASK)
      == MAC_FRAME_SOURCE_MODE_SHORT) {
    incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_SOURCE_SHORT;
  } else if ((cleanControl & MAC_FRAME_SOURCE_MODE_MASK)
             == MAC_FRAME_SOURCE_MODE_NONE) {
    incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_SOURCE_NONE;
  }

  if ((cleanControl & MAC_FRAME_DESTINATION_MODE_MASK)
      == MAC_FRAME_DESTINATION_MODE_SHORT) {
    EmberNodeId macDestShort = emberFetchLowHighInt16u(mac_header + destIndex);
    if (macDestShort == state->nwk_radio_parameters[NWK_INDEX].local_node_id) {
      incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_DEST_UNICAST_SHORT;
    } // else
      // Assume the MAC hardware would only pass up incoming
      // messages destined for us (either broadcast node ID or local node ID)
      // incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_DEST_BROADCAST_SHORT;
  } else if ((cleanControl & MAC_FRAME_DESTINATION_MODE_MASK)
             == MAC_FRAME_DESTINATION_MODE_LONG) {
    incomingMessage |= EMBER_MAC_FILTER_MATCH_ON_DEST_UNICAST_LONG;
  }

  uint8_t i = 0;
  while (sl_mac_stack_filter_list != NULL
         && !(EMBER_MAC_FILTER_MATCH_END & sl_mac_stack_filter_list[i])) {
    if (incomingMessage == sl_mac_stack_filter_list[i]) {
      return true;
    }
    i++;
  }

  i = 0;
  while (sl_mac_custom_filter_list != NULL
         && !(EMBER_MAC_FILTER_MATCH_END & sl_mac_custom_filter_list[i])) {
    if (incomingMessage == sl_mac_custom_filter_list[i]) {
      return true;
    }
    i++;
  }

  return false;
}

// Simplify the MAC header parsing code by using a bitmask for the
// destination addresses of interest.

#define TO_BROADCAST_PAN_ID     0x01
#define TO_OUR_PAN_ID           0x02
#define TO_BROADCAST_ID         0x04
#define TO_OUR_ID               0x08

static uint8_t decodeShortDestination(uint8_t *macHeader,
                                      uint16_t ourPanId,
                                      uint16_t ourNodeId)
{
  uint8_t result = 0;

  // This is the source PAN ID if no destination is present.
  uint16_t destinationPanId = emberFetchLowHighInt16u(macHeader + 3);
  EmberNodeId destinationId = emberFetchLowHighInt16u(macHeader + 5);

  if (destinationPanId == 0xFFFF) {
    result |= TO_BROADCAST_PAN_ID;
  } else if (destinationPanId == ourPanId) {
    result |= TO_OUR_PAN_ID;
  }

  if (destinationId == 0xFFFF) {
    result |= TO_BROADCAST_ID;
  } else if (destinationId == ourNodeId) {
    result |= TO_OUR_ID;
  }

  return result;
}

sl_status_t sl_mac_radio_receive_mac_header_callback(uint8_t mac_index,
                                                     uint8_t nwk_index,
                                                     uint8_t *rawMacHeader,
                                                     uint8_t payloadLength,
                                                     PacketHeader *rxPayload)
{
  // Current upper MAC state
  sl_mac_upper_mac_state_t *state = sl_mac_upper_mac_state + MAC_INDEX;

  uint16_t control = emberFetchLowHighInt16u(rawMacHeader);
  uint8_t packetType = control & EMBER_MAC_HEADER_FC_FRAME_TYPE_MASK;
  uint16_t destAddressMode = control & EMBER_MAC_HEADER_FC_DEST_ADDR_MODE_MASK;
  bool hasSecurity = control & EMBER_MAC_HEADER_FC_SECURITY_ENABLED_BIT;

  PacketHeader header;

  uint8_t destinationFlags = decodeShortDestination(rawMacHeader,
                                                    state->nwk_radio_parameters[NWK_INDEX].pan_id,
                                                    state->nwk_radio_parameters[NWK_INDEX].local_node_id);

  uint16_t macInfoFlags = 0;

  // Simplify checks by clearing this bit.  The value has been saved
  // in the hasSecurity variable.
  control &= ~EMBER_MAC_HEADER_FC_SECURITY_ENABLED_BIT;

  // ***
  // TODO:
  // Note: The following processing code is specific to the Zigbee stack, we
  // want to make sure this uses a callback model where some of these checks
  // are deferred to the stack layer.
  // ***

  // In scan mode, don't process unless this is a frame we are
  // looking for.
  if (sl_mac_scan_pending()) {
    // TODO.  Cycle through various scan states when we're ready
    // with the scan implementation.
    // JAR disable this skip return SL_STATUS_BUSY;
  }

  // The only MAC-encrypted packets we handle are beacons, and then we
  // only look at the MAC header.
  if (hasSecurity
      && packetType != EMBER_MAC_HEADER_FC_FRAME_TYPE_BEACON) {
#ifdef MAC_TEST_COMMANDS_SUPPORT
    // pass through to application so that it can print comm status indication
    // required for a mac certification test.
    if (!emEnableMacCertificationTestMode)
#endif  // MAC_TEST_COMMANDS_SUPPORT
    return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
  }

  switch (packetType) {
    case EMBER_MAC_HEADER_FC_FRAME_TYPE_ACK:
      return SL_STATUS_MAC_ACK_HEADER_TYPE;

    case EMBER_MAC_HEADER_FC_FRAME_TYPE_BEACON: {
      if (!((sl_mac_scan_pending()
             || destinationFlags & TO_OUR_PAN_ID)
            && (control == EMBER_MAC_BEACON_SHORT_FRAME_CONTROL
                || control == EMBER_MAC_BEACON_ENHANCED_FRAME_CONTROL
                || control == EMBER_MAC_BEACON_LONG_FRAME_CONTROL))) {
        return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
      }
      macInfoFlags = EMBER_MAC_INFO_TYPE_BEACON;
      break;
    }

    case EMBER_MAC_HEADER_FC_FRAME_TYPE_DATA: {
      uint16_t cleanControl = (control & ~(EMBER_MAC_HEADER_FC_FRAME_PENDING_BIT
                                           | EMBER_MAC_HEADER_FC_ACK_REQUEST_BIT));
      if ((state->nwk_radio_parameters[NWK_INDEX].passthrough_filter_callback
           && state->nwk_radio_parameters[NWK_INDEX].passthrough_filter_callback(rawMacHeader,
                                                                                 payloadLength))
          || sli_mac_filter_match_check(MAC_INDEX, NWK_INDEX, rawMacHeader)) {
        macInfoFlags = EMBER_MAC_INFO_TYPE_PASSTHROUGH;
      } else if ((cleanControl != EMBER_MAC_DATA_FRAME_CONTROL
                  || (destinationFlags != (TO_OUR_PAN_ID | TO_OUR_ID)
                      && destinationFlags != (TO_OUR_PAN_ID | TO_BROADCAST_ID)))) {
        return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
      } else if ((destinationFlags & TO_BROADCAST_ID)
                 && (((state->nwk_radio_parameters[NWK_INDEX].rx_state != SL_MAC_RX_ON_WHEN_IDLE)
                      && (state->nwk_radio_parameters[NWK_INDEX].rx_state != SL_MAC_RX_DUTY_CYCLING))
                     || sl_mac_lower_mac_is_expecting_data())) {
        // Broadcasts are ignored by sleepy nodes or anyone waiting for data
        // from their parent.
        return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
      } else if (destinationFlags & TO_BROADCAST_ID) {
        macInfoFlags = EMBER_MAC_INFO_TYPE_DATA | EMBER_MAC_INFO_BROADCAST_NODE_ID;
      } else {
        macInfoFlags = EMBER_MAC_INFO_TYPE_DATA;
      }
      break;
    }

    case EMBER_MAC_HEADER_FC_FRAME_TYPE_CONTROL: {
      if (!((destinationFlags & (TO_OUR_PAN_ID | TO_BROADCAST_PAN_ID))
            || state->nwk_radio_parameters[NWK_INDEX].pan_id == 0xFFFF)) {
        return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
      }

      macInfoFlags = EMBER_MAC_INFO_TYPE_MAC_COMMAND;

      switch (destAddressMode) {
        case MAC_FRAME_DESTINATION_MODE_SHORT: {
          break;
        }
        case MAC_FRAME_DESTINATION_MODE_LONG: {
          if (MEMCOMPARE(rawMacHeader + 5,
                         state->nwk_radio_parameters[NWK_INDEX].local_eui,
                         EUI64_SIZE) != 0) {
            return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
          }
          break;
        }
        default:
          return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
      }
      break;
    }

    default:
      // Reject unknown packet types.
      return SL_STATUS_MAC_UNKNOWN_HEADER_TYPE;
  }

  if (control & MAC_FRAME_FLAG_FRAME_PENDING) {
    macInfoFlags |= EMBER_MAC_INFO_FRAME_PENDING_MASK;
  }

  if (control & MAC_FRAME_FLAG_ACK_REQUIRED) {
    macInfoFlags |= EMBER_MAC_INFO_OUTGOING_FRAME_PENDING;
  }

  if (MAC_INDEX) {
    macInfoFlags |= EMBER_MAC_INFO_PHY_INDEX;
  }

  if ((macInfoFlags & EMBER_MAC_INFO_FRAME_TYPE_MASK)
      == EMBER_MAC_INFO_TYPE_DATA) {
    uint16_t source = emberFetchLowHighInt16u(rawMacHeader + 7);
    header = sl_mac_make_data_message(source,
                                      payloadLength,
                                      rawMacHeader,
                                      macInfoFlags,
                                      state->current_nwk);
  } else {
    header = sl_mac_make_raw_message(NULL_BUFFER, macInfoFlags, state->current_nwk);
  }

  if (header == NULL_BUFFER) {
    return SL_STATUS_ALLOCATION_FAILED;
  }

  *rxPayload = header;
  return SL_STATUS_OK;
}

// The following functions are not multi-PAN specific, but right now
// they are only used by the multi-PAN code. So we strip them out
// to reduce the code size. We can enable them if non-multi-PAN code
// will use these functions in the future.
#ifndef EMBER_MULTI_NETWORK_STRIPPED
// Function to check if either destination or source broadcast PAN is set
bool sl_mac_is_broadcast_pan(uint8_t *rawMacHeader, bool hasPhyHeader)
{
  // Check if Destination PAN is present and if it is set to the broadcast PAN
  if (sl_mac_flat_dest_panid_present(rawMacHeader, hasPhyHeader)) {
    return (sl_mac_flat_dest_panid(rawMacHeader, hasPhyHeader) == EMBER_BROADCAST_PAN_ID);
  }

  // Check if Source PAN is present and if it is set to the broadcast PAN
  if (sl_mac_flat_src_panid_present(rawMacHeader, hasPhyHeader)) {
    return (sl_mac_flat_src_panid(rawMacHeader, hasPhyHeader) == EMBER_BROADCAST_PAN_ID);
  }
  return false;
}

sl_status_t sl_mac_get_pan_id(uint8_t *rawMacHeader, bool hasPhyHeader, uint16_t *pan_id)
{
  // Check if Destination PAN is present
  if (sl_mac_flat_dest_panid_present(rawMacHeader, hasPhyHeader)) {
    *pan_id = sl_mac_flat_dest_panid(rawMacHeader, hasPhyHeader);
    return SL_STATUS_OK;
  } else {
    // Check if Source PAN is present
    if (sl_mac_flat_src_panid_present(rawMacHeader, hasPhyHeader)) {
      *pan_id = sl_mac_flat_src_panid(rawMacHeader, hasPhyHeader);
      return SL_STATUS_OK;
    }
  }

  return SL_STATUS_FAIL;
}
#endif // EMBER_MULTI_NETWORK_STRIPPED
