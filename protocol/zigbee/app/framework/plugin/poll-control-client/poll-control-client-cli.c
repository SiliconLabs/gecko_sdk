/***************************************************************************//**
 * @file
 * @brief CLI for the Poll Control Client plugin.
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
#include "app/framework/plugin/poll-control-client/poll-control-client.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"
void mode(sl_cli_command_arg_t *arguments)
{
  uint8_t mode = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_set_fast_polling_mode(mode);
  emberAfPollControlClusterPrintln("%p 0x%x", "mode", mode);
}

// plugin poll-control-client timeout <timeout:2>
void timeout(sl_cli_command_arg_t *arguments)
{
  uint16_t timeout = sl_cli_get_argument_uint16(arguments, 0);
  sli_zigbee_af_set_fast_polling_timeout(timeout);
  emberAfPollControlClusterPrintln("%p 0x%2x", "timeout", timeout);
}

// plugin poll-control-client respond <mode:1>
void respond(sl_cli_command_arg_t *arguments)
{
  uint8_t mode = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_set_response_mode(mode);
  emberAfPollControlClusterPrintln("%p 0x%x", "respond", mode);
}

void print(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_poll_control_client_print();
}
