/***************************************************************************//**
 * @file
 * @brief CLI for the Messaging Client plugin.
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
#include "app/framework/plugin/messaging-client/messaging-client.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

// plugin messaging-client confirm <endpoint:1>
void sli_zigbee_af_messaging_client_cli_confirm(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  EmberAfStatus status = emberAfPluginMessagingClientConfirmMessage(endpoint);
  emberAfMessagingClusterPrintln("%p 0x%x", "confirm", status);
}

// plugin messaging-client print <endpoint:1>
void sli_zigbee_af_messaging_client_cli_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_messaging_client_print_info(endpoint);
}

// plugin messaging-client clear <endpoint:1>
void sli_zigbee_af_messaging_client_cli_clear(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_messaging_client_clear_message(endpoint);
}
