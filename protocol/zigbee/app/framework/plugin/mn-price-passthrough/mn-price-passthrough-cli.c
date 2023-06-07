/***************************************************************************//**
 * @file
 * @brief CLI for the MN Price Passthrough plugin.
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
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "app/framework/plugin/mn-price-passthrough/mn-price-passthrough.h"
#include "app/framework/plugin/price-common/price-common.h"
// plugin mn-price-passthrough start
void sli_zigbee_af_mn_price_start_command(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_mn_price_passthrough_start_poll_and_forward();
}

// plugin mn-price-passthrough start
void sli_zigbee_af_mn_price_stop_command(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_mn_price_passthrough_stop_poll_and_forward();
}

// plugin mn-price-passthrough setRouting <forwardingId:2> <forwardingEndpoint:1> <proxyEsiEndpoint:1>
void sli_zigbee_af_mn_price_set_routing_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId fwdId = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t fwdEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t esiEndpoint = sl_cli_get_argument_uint8(arguments, 2);
  sli_zigbee_af_mn_price_passthrough_routing_setup(fwdId,
                                                   fwdEndpoint,
                                                   esiEndpoint);
}

// plugin mn-price-passthrough print
void sli_zigbee_af_mn_price_print_command(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_mn_price_passthrough_print_current_price();
}
