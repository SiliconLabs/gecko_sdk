/**
 * @file sl_zigbee_fragmenation_stubs.c
 * @brief stubs for fragmenation
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
#include "ember-types.h"

WEAK(EmberStatus sli_zigbee_af_fragmentation_send_unicast(EmberOutgoingMessageType type,
                                                          uint16_t indexOrDestination,
                                                          EmberApsFrame *apsFrame,
                                                          uint8_t *buffer,
                                                          uint16_t bufLen,
                                                          uint16_t *messageTag))
{
  (void)type;
  (void)indexOrDestination;
  (void)apsFrame;
  (void)buffer;
  (void)bufLen;
  (void)messageTag;
  return EMBER_NOT_FOUND;;
}

WEAK(bool sli_zigbee_af_fragmentation_incoming_message(EmberIncomingMessageType type,
                                                       EmberApsFrame *apsFrame,
                                                       EmberNodeId sender,
                                                       uint8_t **buffer,
                                                       uint16_t *bufLen))
{
  (void)type;
  (void)apsFrame;
  (void)sender;
  (void)buffer;
  (void)bufLen;
  return false;
}
