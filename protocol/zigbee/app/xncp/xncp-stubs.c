/***************************************************************************//**
 * @file
 * @brief Programmable NCP stubs.
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

#include "xncp.h"
#include "app/util/ezsp/ezsp-frame-utilities.h"

bool sli_zigbee_xncp_allow_incoming_ezsp_command(void)
{
  return true;
}

bool sli_zigbee_xncp_allow_outgoing_ezsp_callback(uint8_t *callback,
                                                  uint8_t callbackLength)
{
  (void)callback;
  (void)callbackLength;
  return true;
}

bool sli_zigbee_af_xncp_incoming_message_callback(EmberIncomingMessageType type,
                                                  EmberApsFrame *apsFrame,
                                                  EmberMessageBuffer message)
{
  (void)type;
  (void)apsFrame;
  (void)message;
  return false;
}

void sli_zigbee_xncp_handle_incoming_custom_ezsp_message(void)
{
  appendInt8u(EMBER_INVALID_CALL);
  appendInt8u(0); // Bug 14838: We always need to append the reply length
}
void sli_zigbee_xncp_handle_get_info_command(void)
{
  appendInt8u(EMBER_INVALID_CALL);
}

void emberAfPluginXncpGetXncpInformation(uint16_t *manufacturerId,
                                         uint16_t *versionNumber)
{
  *versionNumber = *manufacturerId = 0;
}
