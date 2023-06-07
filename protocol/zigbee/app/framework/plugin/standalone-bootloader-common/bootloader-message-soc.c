/***************************************************************************//**
 * @file
 * @brief This file defines the interface to the host to send Ember proprietary
 * bootloader messages.
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

#include "app/framework/include/af.h"
#include "bootloader-protocol.h"

#define emberBootloadTransmitCompleteHandler sli_zigbee_af_standalone_bootloader_common_bootload_transmit_complete_callback
#define emberIncomingBootloadMessageHandler sli_zigbee_af_standalone_bootloader_common_incoming_bootload_message_callback

//------------------------------------------------------------------------------
// External Declarations

void sli_zigbee_aes_encrypt(uint8_t *block, const uint8_t *key);

//------------------------------------------------------------------------------
// Globals

//------------------------------------------------------------------------------
// Functions

EmberStatus sli_zigbee_af_send_bootload_message(bool isBroadcast,
                                                EmberEUI64 destEui64,
                                                uint8_t length,
                                                uint8_t* message)
{
  EmberStatus status;
  EmberMessageBuffer buffer = emberFillLinkedBuffers(message,
                                                     length);
  if (buffer == EMBER_NULL_MESSAGE_BUFFER) {
    return EMBER_NO_BUFFERS;
  }

  status = emberSendBootloadMessage(isBroadcast, destEui64, buffer);
  emberReleaseMessageBuffer(buffer);
  return status;
}

void emberIncomingBootloadMessageHandler(EmberEUI64 longId,
                                         EmberMessageBuffer message)
{
  uint8_t incomingBlock[MAX_BOOTLOAD_MESSAGE_SIZE];
  uint8_t length = emberMessageBufferLength(message);
  if (length > MAX_BOOTLOAD_MESSAGE_SIZE) {
    bootloadPrintln("Bootload message too long (%d > %d), dropping!",
                    length,
                    MAX_BOOTLOAD_MESSAGE_SIZE);
    return;
  }
  emberCopyFromLinkedBuffers(message,
                             0,       // start index
                             incomingBlock,
                             length);

  emberAfPluginStandaloneBootloaderCommonIncomingMessageCallback(longId,
                                                                 length,
                                                                 incomingBlock);
}

void emberBootloadTransmitCompleteHandler(EmberMessageBuffer message,
                                          EmberStatus status)
{
  if (status != EMBER_SUCCESS) {
    uint8_t commandId = 0xFF;
    if (emberMessageBufferLength(message) >= 2) {
      commandId = emberGetLinkedBuffersByte(message, 1);
    }
    bootloadPrintln("Bootload message (0x%X) send failed: 0x%X",
                    commandId,
                    status);
  }
}

void sli_zigbee_af_standalone_bootloader_client_encrypt(uint8_t* block, uint8_t* key)
{
  sli_zigbee_aes_encrypt(block, key);
}
