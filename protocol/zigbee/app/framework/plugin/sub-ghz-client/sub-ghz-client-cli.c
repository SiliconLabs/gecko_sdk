/***************************************************************************//**
 * @file
 * @brief CLI for the Sub-Ghz Client plugin.
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
#include "sub-ghz-client.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

//-----------------------------------------------------------------------------
// Private functions

/** @brief Print "Success" or "Error"
 *
 * Simples.
 */
static void printSuccessOrError(EmberStatus status)
{
  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("OK");
  } else {
    emberAfCorePrintln("Error %d (0x%x)", status, status);
  }
}

//-----------------------------------------------------------------------------
// Public functions

/** @brief Send the 'Get Suspend ZCL Messages Status' command to a given server.
 *
 * @param nodeId .... server's node ID
 * @param endpoint .. server's endpoint
 */
void sli_zigbee_af_sub_ghz_client_cli_get_suspend_status(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;

  EmberNodeId nodeId = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);

  status = emberAfPluginSubGhzClientSendGetSuspendZclMessagesStatusCommand(nodeId, endpoint);
  printSuccessOrError(status);
}

/** @brief Ignore the SuspendZclMessages command.
 *
 * When the client receives the SuspendZclMessages command, it suspends sending
 * any ZCL messages for a given time. This function allows the client to ignore
 * the command and continue sending messages even when suspended.
 *
 * @param ignore  true to ignore, false to switch back to normal behaviour
 */
void sli_zigbee_af_sub_ghz_client_cli_ignore_suspend_status(sl_cli_command_arg_t *arguments)
{
  bool ignore = (bool)sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginSubGhzClientIgnoreSuspendZclMessagesCommand(ignore);
}

/** @brief Broadcasts a request to change the channel by means of the
 * Mgmt_NWK_Unsolicited_Enhanced_Update_notify command.
 *
 * @param destination ........ the Sub-GHz server's node ID
 * @param channelPage ........ current channel page
 * @param channel ............ current channel
 * @param macTxUcastTotal .... total number of Mac Tx transaction attempts
 * @param macTxUcastFailures . total number of Mac Tx transaction failures
 * @param macTxUcastRetries .. total number of Mac Tx transaction retries
 * @param period ............. time in minutes over which macTxUcastXxx were measured
 */
void sli_zigbee_af_sub_ghz_client_cli_request_channel_change(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;

  EmberNodeId nodeId = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t page = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t channel = sl_cli_get_argument_uint8(arguments, 2);
  uint16_t macTxUcastTotal = sl_cli_get_argument_uint16(arguments, 3);
  uint16_t macTxUcastFailures = sl_cli_get_argument_uint16(arguments, 4);
  uint16_t macTxUcastRetries = sl_cli_get_argument_uint16(arguments, 5);
  uint8_t period = sl_cli_get_argument_uint8(arguments, 6);

  status = emberAfPluginSubGhzClientSendUnsolicitedEnhancedUpdateNotify(nodeId,
                                                                        page,
                                                                        channel,
                                                                        macTxUcastTotal,
                                                                        macTxUcastFailures,
                                                                        macTxUcastRetries,
                                                                        period);
  printSuccessOrError(status);
}
