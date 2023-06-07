/***************************************************************************//**
 * @file
 * @brief CLI for the Command Relay plugin.
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

#include "af.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "command-relay.h"
#include "command-relay-local.h"

static void parseDeviceEndpointsFromArguments(sl_cli_command_arg_t *arguments,
                                              EmberAfPluginCommandRelayDeviceEndpoint *inDeviceEndpoint,
                                              EmberAfPluginCommandRelayDeviceEndpoint *outDeviceEndpoint);

void sli_zigbee_af_command_relay_add_command(sl_cli_command_arg_t *arguments)
{
  EmberAfPluginCommandRelayDeviceEndpoint inDeviceEndpoint;
  EmberAfPluginCommandRelayDeviceEndpoint outDeviceEndpoint;
  parseDeviceEndpointsFromArguments(arguments, &inDeviceEndpoint, &outDeviceEndpoint);

  emberAfPluginCommandRelayAdd(&inDeviceEndpoint, &outDeviceEndpoint);
}

void sli_zigbee_af_command_relay_removeCommand(sl_cli_command_arg_t *arguments)
{
  EmberAfPluginCommandRelayDeviceEndpoint inDeviceEndpoint;
  EmberAfPluginCommandRelayDeviceEndpoint outDeviceEndpoint;
  parseDeviceEndpointsFromArguments(arguments, &inDeviceEndpoint, &outDeviceEndpoint);

  emberAfPluginCommandRelayRemove(&inDeviceEndpoint, &outDeviceEndpoint);
}

void sli_zigbee_af_command_relay_clear_command(sl_cli_command_arg_t *arguments)
{
  emberAfPluginCommandRelayClear();
}

void sli_zigbee_af_command_relay_save_command(sl_cli_command_arg_t *arguments)
{
  emberAfPluginCommandRelaySave();
}

void sli_zigbee_af_command_relay_load_command(sl_cli_command_arg_t *arguments)
{
  emberAfPluginCommandRelayLoad();
}

void sli_zigbee_af_command_relay_printCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_command_relay_print();
}

static void parseDeviceEndpointsFromArguments(sl_cli_command_arg_t *arguments,
                                              EmberAfPluginCommandRelayDeviceEndpoint *inDeviceEndpoint,
                                              EmberAfPluginCommandRelayDeviceEndpoint *outDeviceEndpoint)
{
  sl_zigbee_copy_eui64_arg(arguments, 0, inDeviceEndpoint->eui64, true);
  inDeviceEndpoint->endpoint = sl_cli_get_argument_uint8(arguments, 1);
  inDeviceEndpoint->clusterId = sl_cli_get_argument_uint16(arguments, 2);

  sl_zigbee_copy_eui64_arg(arguments, 3, outDeviceEndpoint->eui64, true);
  outDeviceEndpoint->endpoint = sl_cli_get_argument_uint8(arguments, 4);
  outDeviceEndpoint->clusterId = sl_cli_get_argument_uint16(arguments, 5);
}
