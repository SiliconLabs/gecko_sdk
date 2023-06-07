/**
 * @file sl_zigbee_zdo_dlk_negotiation.h
 * @brief declarations of ZDO interface for dynamic link key negotiation
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

#include "include/ember.h"
#include "buffer_manager/buffer-management.h"
#include "sl_common.h"
#include "sl_status.h"

SL_WEAK sl_status_t sli_zigbee_zdo_dlk_handle_start_key_negotiation_rsp(Buffer response,
                                                                        uint8_t payload_index,
                                                                        EmberNodeId source)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK void sl_zigbee_zdo_dlk_get_supported_negotiation_parameters(uint8_t *method_mask,
                                                                    uint8_t *secret_mask)
{
}

SL_WEAK sl_status_t sli_zigbee_zdo_dlk_handle_start_key_update_req(Buffer request,
                                                                   uint8_t payload_index,
                                                                   EmberNodeId source,
                                                                   uint8_t sequence)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK sl_status_t sli_zigbee_zdo_dlk_handle_start_key_negotiation_req(Buffer request,
                                                                        uint8_t payload_index,
                                                                        EmberNodeId source,
                                                                        uint8_t sequence)
{
  return SL_STATUS_NOT_SUPPORTED;
}

SL_WEAK void sli_zigbee_zdo_dlk_node_desc_req_additional_tlvs(EmberNodeId target, uint8_t **extra_req_data, uint8_t *data_length)
{
}

SL_WEAK void sli_zigbee_zdo_dlk_node_desc_req_handle_additional_tlvs(Buffer request,
                                                                     uint8_t payload_index,
                                                                     EmberNodeId source,
                                                                     uint8_t **extra_rsp_data,
                                                                     uint8_t *data_length)
{
}

SL_WEAK bool sli_zigbee_zdo_dlk_node_desc_rsp_handle_additional_tlvs(Buffer request,
                                                                     uint8_t payload_index,
                                                                     EmberNodeId source)
{
  return false;
}

SL_WEAK bool sl_zigbee_zdo_dlk_enabled(void)
{
  return false;
}

SL_WEAK void slx_zigbee_gu_zdo_stack_toggle_dlk(bool do_dlk)
{
  (void) do_dlk;
}
