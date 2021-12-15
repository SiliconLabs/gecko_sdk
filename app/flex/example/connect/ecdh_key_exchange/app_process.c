/***************************************************************************//**
 * @file
 * @brief app_process.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include PLATFORM_HEADER
#include "stack/include/ember.h"
#include "app_log.h"
#include "sl_ecdh_key_exchange.h"
#include "app_framework_common.h"
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// Buffer for the network key
EmberKeyData network_key;
/// Contains option flags for transmit
uint8_t tx_options = EMBER_OPTIONS_ACK_REQUESTED;
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Application state machine, called infinitely
 *****************************************************************************/
void emberAfTickCallback(void)
{
  ///////////////////////////////////////////////////////////////////////////
  // Put your application code here!                                       //
  // This is called infinitely.                                            //
  // Do not call blocking functions from here!                             //
  ///////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * This function handles the received messages.
 *
 * @param message Contains the message context.
 *
 * In this example this application handles three endpoints, one for public
 * key exchange, one for network key exchange and a data endpoint.
 *
 *****************************************************************************/
void emberAfIncomingMessageCallback(EmberIncomingMessage *message)
{
  if (message->endpoint == SL_CONNECT_ECDH_PUBLIC_KEY_EXCHANGE_ENDPOINT) {
    app_log_info("Public key received\n");

    uint8_t* pPublicXRemote = sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXREMOTE);
    uint8_t* pPublicYRemote = sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYREMOTE);

    if (pPublicXRemote != NULL && pPublicYRemote != NULL) {
      memcpy(pPublicXRemote, message->payload, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
      memcpy(pPublicYRemote, &message->payload[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES], SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
    } else {
      app_log_error("IncomingMessageCallback buffer error\n");
    }
  }
  if (message->endpoint == SL_CONNECT_ECDH_NETWORK_KEY_EXCHANGE_ENDPOINT) {
    app_log_info("Network key received\n");

    if (sl_ecdh_key_exchange_network_key_decrypt(message->payload, network_key.contents) != SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK) {
      app_log_error("Network key decryption failed!\n");
    }
  }
  if (message->endpoint == SL_CONNECT_ECDH_DEFAULT_DATA_ENDPOINT) {
    if ((tx_options & EMBER_OPTIONS_SECURITY_ENABLED) && !(message->options & EMBER_OPTIONS_SECURITY_ENABLED)) {
      app_log_info("Warning: security is enabled, but the incoming message not encrypted\n");
    }
    app_log_info("Incoming message from 0x%02x: %.*s\n", message->source, message->length, message->payload);
  }
}

/**************************************************************************//**
 * This function called when the Connect stack status is changed.
 *
 * @param status Current status.
 *
 *****************************************************************************/
void emberAfStackStatusCallback(EmberStatus status)
{
  switch (status) {
    case EMBER_NETWORK_UP:
      app_log_info("Network is UP\n");
      break;
    case EMBER_NETWORK_DOWN:
      app_log_info("Network is DOWN\n");
      break;
    default:
      break;
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
