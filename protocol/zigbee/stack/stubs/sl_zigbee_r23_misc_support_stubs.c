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
