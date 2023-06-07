/***************************************************************************//**
 * @file
 * @brief CLI for the Tunneling Client plugin.
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
#include "tunneling-client.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

void sli_zigbee_af_tunneling_client_cli_printCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_tunneling_client_cli_print();
}
// plugin tunneling-client request <server:2> <client endpoint:1> <server endpoint:1> <protocol id:1> <manufacturer code:2> <flow control support:1>
void sli_zigbee_af_tunneling_client_cli_request(sl_cli_command_arg_t *arguments)
{
  EmberNodeId server = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t clientEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t serverEndpoint = sl_cli_get_argument_uint8(arguments, 2);
  uint8_t protocolId = sl_cli_get_argument_uint8(arguments, 3);
  uint16_t manufacturerCode = sl_cli_get_argument_uint16(arguments, 4);
  bool flowControlSupport = (bool)sl_cli_get_argument_uint8(arguments, 5);
  EmberAfPluginTunnelingClientStatus status = emberAfPluginTunnelingClientRequestTunnel(server,
                                                                                        clientEndpoint,
                                                                                        serverEndpoint,
                                                                                        protocolId,
                                                                                        manufacturerCode,
                                                                                        flowControlSupport);
  emberAfTunnelingClusterPrintln("%p 0x%x", "request", status);
}

// plugin tunneling-client transfer <tunnel index:1> <data>
void sli_zigbee_af_tunneling_client_cli_transfer(sl_cli_command_arg_t *arguments)
{
  uint8_t tunnelIndex = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t data[255];
  uint16_t dataLen = sl_zigbee_copy_hex_arg(arguments, 1, data, sizeof(data), false);
  EmberAfStatus status = emberAfPluginTunnelingClientTransferData(tunnelIndex,
                                                                  data,
                                                                  dataLen);
  emberAfTunnelingClusterPrintln("%p 0x%x", "transfer", status);
}

// plugin tunneling-client close <tunnel index:1>
void sli_zigbee_af_tunneling_client_cli_close(sl_cli_command_arg_t *arguments)
{
  uint8_t tunnelIndex = sl_cli_get_argument_uint8(arguments, 0);
  EmberAfStatus status = emberAfPluginTunnelingClientCloseTunnel(tunnelIndex);
  emberAfTunnelingClusterPrintln("%p 0x%x", "close", status);
}
