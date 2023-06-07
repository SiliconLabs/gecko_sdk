/***************************************************************************//**
 * @file
 * @brief CLI for the DRLC plugin.
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
#include "app/framework/plugin/drlc/demand-response-load-control.h"
#include "app/framework/plugin/drlc/load-control-event-table.h"

// plugin drlc opt <in | out> <endpoint:1> <id:4>
void emberAfPluginDrlcOptCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_load_control_event_opt_in_or_out(sl_cli_get_argument_uint8(arguments, 0),
                                                 sl_cli_get_argument_uint32(arguments, 1),
                                                 memcmp(arguments->argv[arguments->arg_ofs - 1], "in", strlen("in")) == 0);
}

// plugin drlc print <endpoint:1>
void emberAfPluginDrlcPrintCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_load_control_event_table_print(sl_cli_get_argument_uint8(arguments, 0));
}

// plugin drlc clear <endpoint:1>
void emberAfPluginDrlcClearCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_load_control_event_table_clear(sl_cli_get_argument_uint8(arguments, 0));

  emberAfCorePrintln("Events cleared");
}
