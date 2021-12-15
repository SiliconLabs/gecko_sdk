/***************************************************************************//**
 * @file
 * @brief app_cli.c
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
#include <string.h>
#include PLATFORM_HEADER
#include "hal/hal.h"
#include "sl_cli.h"
#include "app_log.h"
#include "sl_string.h"
#include "sl_ecdh_key_exchange.h"
#include "app_process.h"
#include "app_init.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define PAN_ID                  0x1FF
#define RADIO_TX_POWER              0

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * Command handler to set the device's node id.
 *
 * @param arguments Contains the requested node id to be set, which must be
 * an integer.
 *
 * @note After a restart the node id is still set. It is stored in
 * non-volatile memory.
 *****************************************************************************/
void cmd_set_node_id(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  EmberNodeId nodeId;
  EmberNetworkParameters params;

  // Initialize the security key to the default key prior to forming the
  // network.
  nodeId = sl_cli_get_argument_int8(arguments, 0);
  params.panId = PAN_ID;
  params.radioChannel = default_channel;
  params.radioTxPower = RADIO_TX_POWER;

  status = emberJoinCommissioned(EMBER_DIRECT_DEVICE,
                                 nodeId,
                                 &params);

  if ( status != EMBER_SUCCESS ) {
    app_log_error("Commissioning failed, 0x%x\n", status);
  } else {
    app_log_info("Commissioning succeeded!\n");
  }
}

/**************************************************************************//**
 * Command handler to send the device's public key to an another node.
 *
 * @param arguments Contains the requested node id to where the public key
 * should be sent. The node id is an integer.
 *
 *****************************************************************************/
void cmd_send_public_key(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  EmberNodeId nodeId;
  uint8_t message[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES * 2];
  uint8_t* pPublicXLocal = sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXLOCAL);
  uint8_t* pPublicYLocal = sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYLOCAL);

  if (pPublicXLocal != NULL && pPublicYLocal != NULL) {
    nodeId = sl_cli_get_argument_int8(arguments, 0);

    memcpy(message, pPublicXLocal, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
    memcpy(&message[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES], pPublicYLocal, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);

    status = emberMessageSend(nodeId,
                              SL_CONNECT_ECDH_PUBLIC_KEY_EXCHANGE_ENDPOINT,
                              0,
                              sizeof(message),
                              message,
                              tx_options);

    if ( status != EMBER_SUCCESS ) {
      app_log_error("Public key transmission failed: 0x%x\n", status);
    } else {
      app_log_info("Public key transmission Succeeded\n");
    }
  } else {
    app_log_error("SendPublicKey buffer error\n");
  }
}

/**************************************************************************//**
 * Command handler to send the network key to an another node.
 *
 * @param arguments Contains the requested node id to where the network key
 * should be sent. The node id is an integer.
 *
 * @note The network key is encrypted by AES and should be sent from the server
 * to the client node.
 *****************************************************************************/
void cmd_send_network_key(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  EmberStatus status;
  EmberNodeId nodeId;
  uint8_t message[EMBER_ENCRYPTION_KEY_SIZE];

  nodeId = sl_cli_get_argument_int8(arguments, 0);

  if (sl_ecdh_key_exchange_network_key_encrypt(network_key.contents, message) == SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK) {
    status = emberMessageSend(nodeId,
                              SL_CONNECT_ECDH_NETWORK_KEY_EXCHANGE_ENDPOINT,
                              0,
                              sizeof(message),
                              message,
                              tx_options);

    if ( status != EMBER_SUCCESS ) {
      app_log_error("Network key transmission failed: 0x%x", status);
    }
  } else {
    app_log_error("Network key encryption failed!\n");
  }
}

/**************************************************************************//**
 * Command handler to generate shared key and secret.
 *
 * @param arguments Not used
 *
 * The generation process works with the device's own keys and the received
 * public key from the other device.
 *
 *****************************************************************************/
void cmd_generate_shared_key(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  if (sl_ecdh_key_exchange_shared_key_generate() == SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK) {
    app_log_info("Shared key generated successfully!\n");
  } else {
    app_log_error("Shared key generation failed!\n");
  }
}

/**************************************************************************//**
 * Command handler to print shared key.
 *
 * @param arguments Not used
 *
 * Prints the shared key to the console.
 *****************************************************************************/
void cmd_print_shared_key(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  uint8_t* ecdh_shared_key_buffer = sl_ecdh_key_exchange_shared_key_get();
  for (uint16_t i = 0; i < SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES; i++) {
    app_log_info("%02X", ecdh_shared_key_buffer[i]);
  }
  app_log_info("\n");
}

/**************************************************************************//**
 * Command handler to print network key.
 *
 * @param arguments Not used
 *
 * Prints the network key to the console.
 *****************************************************************************/
void cmd_print_network_key(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  for (uint16_t i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    app_log_info("%02X", network_key.contents[i]);
  }
  app_log_info("\n");
}

/**************************************************************************//**
 * Command handler to apply network key on the Connect stack.
 *
 * @param arguments Not used
 *
 *****************************************************************************/
void cmd_apply_network_key(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  if (emberSetSecurityKey(&network_key) == EMBER_SUCCESS) {
    app_log_info("Security key set\n");
  } else {
    app_log_error("Security key set failed\n");
  }
}

/**************************************************************************//**
 * Command handler to set network key.
 *
 * @param arguments Not used
 *
 * @note It does not apply the key but stores into a variable
 *****************************************************************************/
void cmd_set_network_key(sl_cli_command_arg_t *arguments)
{
  size_t key_len = 0;
  const uint8_t* const key_input_string = sl_cli_get_argument_hex(arguments, 0, &key_len);
  memcpy(network_key.contents, key_input_string, key_len);
}

/**************************************************************************//**
 * Command handler to set security on Connect.
 *
 * @param arguments It contains integer, if 0 the security is off, else on.
 *
 *****************************************************************************/
void cmd_set_security(sl_cli_command_arg_t *arguments)
{
  uint8_t arg = sl_cli_get_argument_int8(arguments, 0);

  if (arg > 0) {
    tx_options |= EMBER_OPTIONS_SECURITY_ENABLED;
    app_log_info("Security enabled\n");
  } else {
    tx_options &= ~EMBER_OPTIONS_SECURITY_ENABLED;
    app_log_info("Security disabled\n");
  }
}

/**************************************************************************//**
 * Command handler to send message to a target node.
 *
 * @param arguments It contains a target node id, and the message itself.
 * The node id is an integer, the message is a string.
 *
 *****************************************************************************/
void cmd_send_message(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  EmberNodeId nodeId;
  char* inputString;

  nodeId      = sl_cli_get_argument_int8(arguments, 0);
  inputString = sl_cli_get_argument_string(arguments, 1);

  status = emberMessageSend(nodeId,
                            SL_CONNECT_ECDH_DEFAULT_DATA_ENDPOINT,
                            0,
                            sl_strnlen(inputString, 32),
                            (uint8_t*)inputString,
                            tx_options);
  if ( status != EMBER_SUCCESS ) {
    app_log_error("Commissioning failed, 0x%x", status);
  }
}

/**************************************************************************//**
 * Command handler to reset the Connect stacks data in non volatile memroy.
 *
 * @param arguments Not used
 *****************************************************************************/
void cmd_leave(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  emberResetNetworkState();
}
