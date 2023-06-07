/***************************************************************************//**
 * @file
 * @brief CLI for the Messaging Server plugin.
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
#include "app/framework/plugin/messaging-server/messaging-server.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

static EmberAfPluginMessagingServerMessage message;

// plugin messaging-server message <message string>
void sli_zigbee_af_messaging_server_cli_msg(sl_cli_command_arg_t *arguments)
{
  uint8_t length = sl_zigbee_copy_string_arg(arguments, 0,
                                             message.message + 1,
                                             EMBER_AF_PLUGIN_MESSAGING_SERVER_MESSAGE_SIZE,
                                             false);
  message.message[0] = length;
}

// plugin messaging-server append <message string>
void sli_zigbee_af_messaging_server_cli_append(sl_cli_command_arg_t *arguments)
{
  uint8_t oldLength = message.message[0];
  uint8_t length = sl_zigbee_copy_string_arg(arguments, 0,
                                             message.message + oldLength + 1,
                                             (EMBER_AF_PLUGIN_MESSAGING_SERVER_MESSAGE_SIZE
                                              - oldLength),
                                             false);
  message.message[0] = oldLength + length;
}

// plugin messaging-server id <messageId:4>
void sli_zigbee_af_messaging_server_cli_id(sl_cli_command_arg_t *arguments)
{
  message.messageId = sl_cli_get_argument_uint32(arguments, 0);
}

// plugin messaging-server time <start time:4> <duration:2>
void sli_zigbee_af_messaging_server_cli_time(sl_cli_command_arg_t *arguments)
{
  message.startTime = sl_cli_get_argument_uint32(arguments, 0);
  message.durationInMinutes = sl_cli_get_argument_uint16(arguments, 1);
}

// plugin messaging-server relative-time <+/-time> <duration>

// Rather than use absolute time, this will set the start-time relative to the current time +/-
// the CLI parameter in MINUTES.
void sli_zigbee_af_messaging_server_cli_relative_time(sl_cli_command_arg_t *arguments)
{
  message.startTime = (emberAfGetCurrentTime()
                       + (sl_cli_get_argument_uint32(arguments, 0) * 60));
  message.durationInMinutes = sl_cli_get_argument_uint16(arguments, 1);
}

// plugin messaging-server transmission <normal | ipan | both>
void sli_zigbee_af_messaging_server_cli_transmission(sl_cli_command_arg_t *arguments)
{
  uint8_t position = sl_cli_get_command_count(arguments) - 1;
  uint8_t* commandChar = (uint8_t *)sl_cli_get_command_string(arguments, position);
  message.messageControl &= ~ZCL_MESSAGING_CLUSTER_TRANSMISSION_MASK;
  if (memcmp(commandChar, "both", strlen("both")) == 0) { // both
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_TRANSMISSION_NORMAL_AND_ANONYMOUS;
  } else if (memcmp(commandChar, "ipan", strlen("ipan")) == 0) { // inter pan
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_TRANSMISSION_ANONYMOUS;
  } else {
    // Do nothing for 'normal'.
    // MISRA requires ..else if.. to have terminating else.
  }
}

// plugin messaging-server importance <low | medium | high | critical>
void sli_zigbee_af_messaging_server_cli_importance(sl_cli_command_arg_t *arguments)
{
  uint8_t* commandChar = (uint8_t *)sl_cli_get_command_string(arguments, 3);
  message.messageControl &= ~ZCL_MESSAGING_CLUSTER_IMPORTANCE_MASK;
  if (memcmp(commandChar, "medium", strlen("medium")) == 0) { // medium
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_MEDIUM;
  } else if (memcmp(commandChar, "high", strlen("high")) == 0) { // high
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_HIGH;
  } else if (memcmp(commandChar, "critical", strlen("critical")) == 0) { // critical
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_IMPORTANCE_CRITICAL;
  } else {
    // Do nothing for 'low' importance.
    // MISRA requires ..else if.. to have terminating else.
  }
}

// plugin messaging-server confirm <not | req>
void sli_zigbee_af_messaging_server_cli_confirm(sl_cli_command_arg_t *arguments)
{
  uint8_t* commandChar = (uint8_t *)sl_cli_get_command_string(arguments, 3);
  message.messageControl &= ~ZCL_MESSAGING_CLUSTER_CONFIRMATION_MASK;
  if (memcmp(commandChar, "req", strlen("req")) == 0) { // required
    message.messageControl |= EMBER_ZCL_MESSAGING_CONTROL_CONFIRMATION_REQUIRED;
  }
  // Do nothing for 'not' (not required).
}

// plugin messaging-server <valid | invalid>
void sli_zigbee_af_messaging_server_cli_valid(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t position = sl_cli_get_command_count(arguments) - 1;
  uint8_t command_first_character = sl_cli_get_command_string(arguments, position)[0];
  emberAfPluginMessagingServerSetMessage(endpoint,
                                         command_first_character == 'v'
                                         ? &message
                                         : NULL);
}

// plugin messaging-server display <nodeId:2> <srcEndpoint:1> <dstEndpoint:1>
void sli_zigbee_af_messaging_server_cli_display(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nodeId = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint = sl_cli_get_argument_uint8(arguments, 2);
  emberAfPluginMessagingServerDisplayMessage(nodeId,
                                             srcEndpoint,
                                             dstEndpoint);
}

// plugin messaging-server cancel <nodeId:2> <srcEndpoint:1> <dstEndpoint:1>
void sli_zigbee_af_messaging_server_cli_cancel(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nodeId = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint = sl_cli_get_argument_uint8(arguments, 2);
  emberAfPluginMessagingServerCancelMessage(nodeId,
                                            srcEndpoint,
                                            dstEndpoint);
}

// plugin messaging-server print <endpoint:1>
void sli_zigbee_af_messaging_server_cli_print(sl_cli_command_arg_t *arguments)
{
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_messaging_server_print_info(endpoint);
}
