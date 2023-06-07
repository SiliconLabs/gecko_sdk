/***************************************************************************//**
 * @file
 * @brief Stubs for new ZDO commands for R22
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
#include "stack/include/ember-types-internal.h"

void sli_zigbee_handle_ieee_joining_list_request(EmberNodeId source,
                                                 PacketHeader header,
                                                 bool broadcastRequest,
                                                 uint8_t *contents)
{
  (void)source;
  (void)header;
  (void)broadcastRequest;
  (void)contents;
}

void sli_zigbee_process_ieee_list_response(uint8_t *contents,
                                           EmberMessageBuffer header,
                                           uint8_t payloadIndex)
{
  (void)contents;
  (void)header;
  (void)payloadIndex;
}

EmberStatus sli_zigbee_send_link_power_delta(uint8_t options, EmberNodeId sender, uint8_t delta)
{
  (void)options;
  (void)sender;
  (void)delta;
  return EMBER_SUCCESS;
}

void sli_zigbee_process_link_power_delta(PacketHeader header)
{
  (void)header;
}

int8_t sli_zigbee_get_new_power_calculated_using_lpd(void)
{
  return MAX_RADIO_POWER_USER_PROVIDED;
}

void sli_zigbee_set_new_power_calculated_using_lpd(int8_t power)
{
  (void)power;
}

EmberStatus emberSendLinkPowerDeltaRequest(void)
{
  return EMBER_SUCCESS;
}

void sli_zigbee_clear_negotiated_power_by_end_device(void)
{
}
