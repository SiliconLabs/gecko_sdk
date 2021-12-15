/***************************************************************************//**
 * @file mac-flat-header.c
 * @brief Definitions and macros of PHY and MAC headers, represented as flat
 * (over-the-air) packets.
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

static uint8_t fixedOffset[] = {
  EMBER_PHY_HEADER_OFFSET,
  EMBER_MAC_HEADER_OFFSET,
  EMBER_MAC_HEADER_SEQUENCE_NUMBER_OFFSET,
  EMBER_MAC_HEADER_SEQUENCE_NUMBER_OFFSET + 1
};

uint8_t sl_mac_flat_payload_length(uint8_t *phy_packet)
{
  return ((sl_mac_flat_security_enabled(phy_packet, true))
          ? (sl_mac_flat_phy_packet_length(phy_packet) - sl_mac_flat_payload_offset(phy_packet, true)
             - sl_mac_flat_aux_security_padding_size(phy_packet, true)
             - (sl_mac_flat_aux_security_level(phy_packet, true)
                == EMBER_MAC_SECURITY_2006_ENC_MIC_32
                ? EMBER_MAC_SECURITY_MIC_SIZE : 0)
             - EMBER_PHY_CRC_LENGTH)
          : (sl_mac_flat_phy_packet_length(phy_packet) - sl_mac_flat_payload_offset(phy_packet, true)
             - EMBER_PHY_CRC_LENGTH));
}

uint8_t sl_mac_flat_field_offset(uint8_t *packet, bool hasPhyHeader, uint8_t field)
{
  uint8_t offset;
  uint16_t macFrameControl;
  uint16_t addressMode;

  if (field < 4) {
    return fixedOffset[field];
  }

  if (!hasPhyHeader
      && (field == EMBER_PH_FIELD_PHY_HEADER
          || field == EMBER_PH_FIELD_PHY_PAYLOAD
          || field == EMBER_PH_FIELD_MAC_MIC)) {
    return 0xFF;
  } else if (field == EMBER_PH_FIELD_MAC_MIC) {
    // The last 4 bytes of the PHY payload, excluding the 2-bytes CRC.
    return (EMBER_PHY_PAYLOAD_OFFSET
            + sl_mac_flat_phy_payload_length(packet)
            - EMBER_MAC_SECURITY_MIC_SIZE
            - EMBER_PHY_CRC_LENGTH);
  }

  macFrameControl = sl_mac_flat_mac_frame_control(packet, hasPhyHeader);

  // MAC destination address mode
  addressMode = (macFrameControl & EMBER_MAC_HEADER_FC_DEST_ADDR_MODE_MASK);

  uint8_t destPanIdOffset = (fixedOffset[EMBER_PH_FIELD_MAC_HEADER_DEST_PAN_ID]
                             - (hasPhyHeader ? 0 : 1));
  offset = (addressMode == EMBER_MAC_HEADER_FC_DEST_ADDR_MODE_NONE
            ? destPanIdOffset
            : destPanIdOffset + 2);

  // MAC destination address
  if (field == EMBER_PH_FIELD_MAC_HEADER_DEST_ADDR) {
    return offset;
  }

  // MAC source PAN ID
  if (addressMode == EMBER_MAC_HEADER_FC_DEST_ADDR_MODE_SHORT) {
    offset += 2;
  } else if (addressMode == EMBER_MAC_HEADER_FC_DEST_ADDR_MODE_LONG) {
    offset += 8;
  }

  if (field == EMBER_PH_FIELD_MAC_HEADER_SRC_PAN_ID) {
    if (macFrameControl & EMBER_MAC_HEADER_FC_PAN_ID_COMPRESS_BIT) {
      return destPanIdOffset;
    } else {
      return offset;
    }
  }

  // MAC source address mode
  addressMode = (macFrameControl & EMBER_MAC_HEADER_FC_SRC_ADDR_MODE_MASK);

  // MAC source Address
  if (addressMode != EMBER_MAC_HEADER_FC_SRC_ADDR_MODE_NONE
      && !(macFrameControl & EMBER_MAC_HEADER_FC_PAN_ID_COMPRESS_BIT)) {
    offset += 2;
  }

  if (field == EMBER_PH_FIELD_MAC_HEADER_SRC_ADDR) {
    return offset;
  }

  // MAC Auxiliary frame
  if (addressMode == EMBER_MAC_HEADER_FC_SRC_ADDR_MODE_SHORT) {
    offset += 2;
  } else if (addressMode == EMBER_MAC_HEADER_FC_SRC_ADDR_MODE_LONG) {
    offset += 8;
  }

  if (field == EMBER_PH_FIELD_MAC_AUXILIARY_HEADER) {
    return offset;
  }

  if (field == EMBER_PH_FIELD_MAC_AUX_FRAME_COUNTER) {
    return (offset + EMBER_MAC_AUX_HEADER_FRAME_COUNTER_OFFSET);
  }

  if (macFrameControl & EMBER_MAC_HEADER_FC_SECURITY_ENABLED_BIT) {
    offset += EMBER_MAC_AUX_HEADER_SIZE;
  }

  // Also valid for NWK header and NWK frame control.
  if (field == EMBER_PH_FIELD_MAC_PAYLOAD) {
    return offset;
  }
  if (field < EMBER_PH_FIELD_MAC_MIC) {
    return offset;
  }
  return 0xFF;
}
