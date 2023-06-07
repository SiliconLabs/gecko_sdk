/***************************************************************************//**
 * @file
 * @brief CLI for the Tunneling Server plugin.
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
#include "tunneling-server.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
void sli_zigbee_af_tunneling_server_cli_print(void);
void sli_zigbee_af_tunneling_server_printCliCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_tunneling_server_cli_print();
}

void sli_zigbee_af_tunneling_server_cli_transfer(sl_cli_command_arg_t *arguments)
{
  uint16_t tunnelIndex =  sl_cli_get_argument_uint16(arguments, 0);
  uint8_t data[255];
  uint16_t dataLen = sl_zigbee_copy_hex_arg(arguments, 1, data, sizeof(data), false);
  EmberAfStatus status = emberAfPluginTunnelingServerTransferData(tunnelIndex,
                                                                  data,
                                                                  dataLen);
  emberAfTunnelingClusterPrintln("%p 0x%x", "transfer", status);
}

void emberAfPluginTunnelingServerToggleBusyCliCommand(sl_cli_command_arg_t *arguments)
{
  emberAfPluginTunnelingServerToggleBusyCommand();
}
