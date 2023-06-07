/***************************************************************************//**
 * @file
 * @brief CLI for the Simple Metering Server plugin.
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
#include "simple-metering-server.h"
#include "simple-metering-test.h"

#include  "sl_cli.h"

void sli_zigbee_af_simple_metering_server_cli_configure_mirror(sl_cli_command_arg_t *arguments)
{
  EmberNodeId dstAddr = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint =  sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint =  sl_cli_get_argument_uint8(arguments, 2);
  uint32_t issuerId = sl_cli_get_argument_uint32(arguments, 3);
  uint32_t reportingInterval = sl_cli_get_argument_uint32(arguments, 4);
  uint8_t mirrorNotificationReporting = sl_cli_get_argument_uint8(arguments, 5);
  uint8_t notificationScheme = sl_cli_get_argument_uint8(arguments, 6);

  emberAfFillCommandSimpleMeteringClusterConfigureMirror(issuerId,
                                                         reportingInterval,
                                                         mirrorNotificationReporting,
                                                         notificationScheme);
  emberAfSetCommandEndpoints(srcEndpoint, dstEndpoint);
  emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, dstAddr);
}

void sli_zigbee_af_simple_metering_cli_disable_fast_polling(sl_cli_command_arg_t * arguments)
{
  uint8_t toggleFastPolling = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_toggle_fast_polling(toggleFastPolling);
}
