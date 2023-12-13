/***************************************************************************//**
 * @file sl_zigbee_r23_misc_support_stubs.c
 * @brief various non-specific stubs for stack features
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_common.h"
#include "ember-types.h"
#include "sl_zigbee_tlv_core.h"
#include "ember-types-internal.h"
#include "sl_zigbee_address_info.h"

// refer to sl_router_info_bitmask_fields in sl_zigbee_stack_specific_tlvs.h
SL_WEAK uint16_t sl_zigbee_get_router_info_bitmask(void)
{
  return 0U;
}

SL_WEAK uint16_t sli_zigbee_get_pan_id_conflict_count(void)
{
  return 0U;
}

SL_WEAK sl_status_t sli_zigbee_zdo_handle_rsp_extended(uint16_t cluster_id,
                                                       EmberApsFrame *apsFrame,
                                                       PacketHeader header,
                                                       uint8_t payload_index,
                                                       EmberNodeId source)
{
  UNUSED_VAR(cluster_id);
  UNUSED_VAR(header);
  UNUSED_VAR(payload_index);
  UNUSED_VAR(source);
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sli_zigbee_zdo_handle_req_extended(uint16_t cluster_id,
                                                       PacketHeader header,
                                                       uint8_t payload_index,
                                                       EmberNodeId source,
                                                       bool broadcast_request,
                                                       EmberApsOption options,
                                                       uint8_t sequence)
{
  UNUSED_VAR(cluster_id);
  UNUSED_VAR(header);
  UNUSED_VAR(payload_index);
  UNUSED_VAR(source);
  UNUSED_VAR(options);
  UNUSED_VAR(sequence);
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sli_zigbee_zdo_handle_extended_rsp(uint16_t cluster_id,
                                                       PacketHeader header,
                                                       uint8_t payload_index,
                                                       EmberNodeId source)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sli_zigbee_zdo_handle_extended_req(uint16_t cluster_id,
                                                       PacketHeader header,
                                                       uint8_t payload_index,
                                                       EmberNodeId source,
                                                       EmberApsOption options)

{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK bool sli_zigbee_get_global_fc_sync_flag(void)
{
  return false;
}

SL_WEAK sl_status_t sl_zigbee_send_security_challenge_request(EmberNodeId destShort,
                                                              EmberKeyData* keyToChallenge)

{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sli_zigbee_set_aps_fc_sync_required(void)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sl_zigbee_tlv_initialize_chain(sl_zigbee_tlv_chain *chain,
                                                   uint8_t *memory,
                                                   const size_t chain_length,
                                                   const size_t memory_length)
{
  UNUSED_VAR(chain);
  UNUSED_VAR(memory);
  UNUSED_VAR(chain_length);
  UNUSED_VAR(memory_length);
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK uint16_t sl_zigbee_tlv_serial_length(const sl_zigbee_tlv_t *tlv)
{
  UNUSED_VAR(tlv);
  return 0;
}

SL_WEAK bool sli_zigbee_process_network_commissioning_messages(uint8_t firstNetworkPayloadByte,
                                                               PacketHeader header,
                                                               uint8_t* frame,
                                                               uint8_t network_payload_index)
{
  (void)firstNetworkPayloadByte;
  (void)header;
  (void)network_payload_index;
  return false;
}

WEAK(bool sli_zigbee_prioritize_on_parent_selection(EmberBeaconData storedBeacon, EmberBeaconData rxBeacon))
{
  (void)storedBeacon;
  (void)rxBeacon;
  return false;
}

WEAK(bool sli_zigbee_append_beacon_tlvs(PacketHeader* beacon))
{
  (void)beacon;
  return false;
}

WEAK(void sli_zigbee_parse_beacon_tlvs(PacketHeader beacon,
                                       uint8_t tlvPayloadStartIndex,
                                       EmberBeaconData* beaconData))
{
  (void)beacon;
  (void)tlvPayloadStartIndex;
  (void)beaconData;
}

WEAK(void sli_zigbee_update_function_and_state_for_network_commissioining(bool extended_beacon,
                                                                          JoinState* joinState,
                                                                          sli_zigbee_network_request_t* network_req_fn))
{
  (void)extended_beacon;
  (void)network_req_fn;
  (void)joinState;
}

WEAK(void sli_zigbee_update_rejoin_state_for_network_commissioining(bool extended_beacon,
                                                                    JoinState* joinState))
{
  (void)extended_beacon;
  (void)joinState;
}

SL_WEAK bool sli_zigbee_aps_relay_frame_required(EmberNodeId dest_short_id)
{
  UNUSED_VAR(dest_short_id);
  return false;
}

SL_WEAK sl_status_t sli_zigbee_reconstruct_as_relay_packet(PacketHeader original_packet,
                                                           EmberNodeId dest_short,
                                                           EmberEUI64 dest_long,
                                                           PacketHeader *header_result)
{
  UNUSED_VAR(original_packet);
  UNUSED_VAR(dest_short);
  UNUSED_VAR(dest_long);
  UNUSED_VAR(header_result);
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK void sli_zigbee_handle_aps_relay_command(PacketHeader nwk_header)
{
  UNUSED_VAR(nwk_header);
}

// The stub when R23 APS relay is not present
SL_WEAK sl_status_t sli_zigbee_aps_relay_check_and_add_relay_if_required(PacketHeader *header)
{
  (void)header;
  // always return false if AF Support component is not present
  return SL_STATUS_OK;
}

SL_WEAK void sli_zigbee_clone_packet_header_for_relay_frames(PacketHeader *original, PacketHeader *header)
{
  (void)original;
  (void)header;
}

SL_WEAK sl_status_t sl_zigbee_initiate_security_challenge(EmberNodeId partnerNodeId,
                                                          EmberEUI64 partnerLong,
                                                          uint8_t keyIndex)
{
  (void)partnerNodeId;
  (void)partnerLong;
  (void)keyIndex;
  // always return false if AF Support component is not present
  return SL_STATUS_OK;
}

SL_WEAK sl_status_t sli_zigbee_zdo_retry_with_fragmentation_for_new_requests(uint8_t mode,
                                                                             EmberNodeId destination,
                                                                             EmberApsFrame *zigDevApsStruct,
                                                                             EmberMessageBuffer* message)
{
  (void)mode;
  (void)destination;
  (void)zigDevApsStruct;
  (void)message;
  return SL_STATUS_FAIL;
}

SL_WEAK PacketHeader sli_zigbee_aps_relay_maybe_reconstruct_command(PacketHeader header,
                                                                    bool use_tunnel,
                                                                    uint8_t aps_command,
                                                                    EmberNodeId destination_short,
                                                                    EmberEUI64 destination_long)
{
  UNUSED_VAR(use_tunnel);
  UNUSED_VAR(aps_command);
  UNUSED_VAR(destination_short);
  UNUSED_VAR(destination_long);
  return header;
}

SL_WEAK sl_status_t sli_zigbee_get_device_capability_extension_data(bool* attach_tlv, uint16_t* bitmask)
{
  (void)attach_tlv;
  (void)bitmask;

  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK bool  sli_zigbee_zdo_check_and_handle_fragmented_messages(uint8_t* apsFrameControl,
                                                                  PacketHeader* header)
{
  (void)apsFrameControl;
  (void)header;
  return false;
}
