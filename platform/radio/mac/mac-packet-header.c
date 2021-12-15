/***************************************************************************//**
 * @file mac-packet-header.c
 * @brief Definitions and macros of MAC headers, represented using in-memory
 * format.
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

void sl_mac_header_set_mac_info(PacketHeader header, uint16_t info)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->info.mac_info_flags = info;
}

void sl_mac_header_set_mac_info_bit(PacketHeader header, uint16_t bit, bool set)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (set) {
    in_memory_packet->info.mac_info_flags |= bit;
  } else {
    in_memory_packet->info.mac_info_flags &= ~bit;
  }
}

uint16_t sl_mac_header_mac_info(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->info.mac_info_flags;
}

uint8_t sl_mac_header_mac_info_frame_type(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return (in_memory_packet->info.mac_info_flags
          & (EMBER_MAC_INFO_TYPE_BEACON
             | EMBER_MAC_INFO_TYPE_DATA
             | EMBER_MAC_INFO_TYPE_PASSTHROUGH
             | EMBER_MAC_INFO_TYPE_MAC_COMMAND));
}

bool sl_mac_is_data_packet(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return ((in_memory_packet->info.mac_info_flags & EMBER_MAC_INFO_FRAME_TYPE_MASK) == EMBER_MAC_INFO_TYPE_DATA);
}

// For now we either have data OR raw packets, so the following method is moot,
// but still keeping it around for future-proofing.
bool sl_mac_is_raw_packet(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return ((in_memory_packet->info.mac_info_flags & EMBER_MAC_INFO_FRAME_TYPE_MASK) != EMBER_MAC_INFO_TYPE_DATA);
}

uint16_t sl_mac_destination_mode(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return MAC_FRAME_DESTINATION_MODE_SHORT;
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_dest_addr_mode(macHeader, false);
  }
}

sl_mac_node_id_t sl_mac_destination(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return in_memory_packet->info.pkt_info.tx_data.destination;
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_dest_short_address(macHeader, false);
  }
}

void sl_mac_set_destination(PacketHeader header, sl_mac_node_id_t id)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->info.pkt_info.tx_data.destination = id;
  return;
}

uint8_t *sl_mac_destination_pointer(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return (uint8_t *) &(in_memory_packet->info.pkt_info.tx_data.destination);
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_dest_long_address(macHeader, false);
  }
}

uint16_t sl_mac_source_mode(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return MAC_FRAME_DESTINATION_MODE_SHORT;
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_src_addr_mode(macHeader, false);
  }
}

sl_mac_node_id_t sl_mac_source(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return in_memory_packet->info.pkt_info.rx_data.source;
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_src_short_address(macHeader, false);
  }
}

uint8_t *sl_mac_source_pointer(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  if (sl_mac_is_data_packet(header)) {
    return (uint8_t *) &(in_memory_packet->info.pkt_info.rx_data.source);
  } else {
    uint8_t *macHeader = in_memory_packet->payload;
    return sl_mac_flat_src_long_address(macHeader, false);
  }
}

#ifndef EMBER_MULTI_NETWORK_STRIPPED
uint8_t sl_mac_nwk_index(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->info.nwk_index;
}
#endif

uint8_t sl_mac_lqi(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->appended_info.queue_info.lqi;
}

int8_t sl_mac_rssi(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->appended_info.queue_info.rssi;
}

uint8_t sl_mac_channel(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->appended_info.queue_info.channel;
}

uint32_t sl_mac_timestamp(PacketHeader header)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  return in_memory_packet->appended_info.queue_info.timestamp;
}

void sl_mac_set_lqi(PacketHeader header, uint8_t lqi)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->appended_info.queue_info.lqi = lqi;
}

void sl_mac_set_rssi(PacketHeader header, int8_t rssi)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->appended_info.queue_info.rssi = rssi;
}

void sl_mac_set_channel(PacketHeader header, uint8_t channel)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->appended_info.queue_info.channel = channel;
}

void sl_mac_set_timestamp(PacketHeader header, uint32_t timestamp)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(header);
  in_memory_packet->appended_info.queue_info.timestamp = timestamp;
}

PacketHeader sl_mac_make_data_message(sl_mac_node_id_t destination,
                                      uint8_t payloadLength,
                                      const uint8_t *payload,
                                      uint16_t macInfoFlags,
                                      uint8_t nwk_index)
{
  PacketHeader message = emAllocateBuffer(EMBER_MAC_IN_MEMORY_OVERHEAD + payloadLength);
  if (message == NULL_BUFFER) {
    return message;
  }
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(message);
  MEMSET(in_memory_packet, 0, emGetBufferLength(message) );
  in_memory_packet->info.nwk_index = NWK_INDEX;
  sl_mac_header_set_mac_info(message, macInfoFlags | EMBER_MAC_INFO_TYPE_DATA);
  in_memory_packet->info.pkt_info.tx_data.destination = destination;
  if (payload != NULL) {
    MEMCOPY(in_memory_packet->payload, payload, payloadLength);
  }
  return message;
}

PacketHeader sl_mac_make_raw_message(Buffer payload,
                                     uint16_t macInfoFlags,
                                     uint8_t nwk_index)
{
  PacketHeader message = emAllocateBuffer(EMBER_MAC_IN_MEMORY_OVERHEAD);
  if (message == NULL_BUFFER) {
    return message;
  }
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(message);
  MEMSET(in_memory_packet, 0, emGetBufferLength(message));
  in_memory_packet->info.nwk_index = NWK_INDEX;
  sl_mac_header_set_mac_info(message, macInfoFlags);
  if (payload != NULL_BUFFER) {
    emSetPayloadLink(message, payload);
  }
  return message;
}

uint8_t *sl_mac_payload_pointer(PacketHeader packet)
{
  sl_mac_in_memory_overhead_t *in_memory_packet = (sl_mac_in_memory_overhead_t *)emGetBufferPointer(packet);
  return in_memory_packet->payload;
}

uint8_t sl_mac_payload_length(PacketHeader packet)
{
  return emGetBufferLength(packet) - EMBER_MAC_IN_MEMORY_OVERHEAD;
}
