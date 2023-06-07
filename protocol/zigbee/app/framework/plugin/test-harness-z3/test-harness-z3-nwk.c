/***************************************************************************//**
 * @file
 * @brief ZigBee 3.0 nwk test harness functionality
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

#include "test-harness-z3-core.h"
#include "test-harness-z3-nwk.h"

// -----------------------------------------------------------------------------
// Globals

bool sli_zigbee_af_test_harness_z3_ignore_leave_commands = false;

// private stack API
extern void sli_zigbee_change_pan_id_now(EmberPanId panId);

// -----------------------------------------------------------------------------
// NWK CLI Commands

#ifdef EZSP_HOST
  #define sli_zigbee_network_sendCommand(...) false
#else

// Internal stack API's.
extern bool sli_zigbee_network_sendCommand(EmberNodeId destination,
                                           uint8_t *commandFrame,
                                           uint8_t length,
                                           bool tryToInsertLongDest,
                                           EmberEUI64 destinationEui);
extern uint8_t sli_zigbee_set_nwk_update_id(uint8_t id);

#endif /* EZSP_HOST */

static EmberStatus sendNetworkCommand(EmberNodeId destinationShort,
                                      uint8_t *commandFrame,
                                      uint8_t length)
{
  EmberEUI64 destinationLong;
  bool haveDestinationLong = false;

  haveDestinationLong
    = (emberLookupEui64ByNodeId(destinationShort, destinationLong)
       == EMBER_SUCCESS);

  return (sli_zigbee_network_sendCommand(destinationShort,
                                         commandFrame,
                                         length,
                                         haveDestinationLong,
                                         destinationLong)
          ? EMBER_SUCCESS
          : EMBER_DELIVERY_FAILED);
}

// plugin test-harness z3 nwk nwk-rejoin-request <dstShort:2>
void sli_zigbee_af_test_harness_z3_nwk_nwk_rejoin_request_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status;
  EmberNodeId destinationShort = sl_cli_get_argument_uint16(arguments, 0);
  EmberNodeType nodeType;
  uint8_t commandFrame[2];

  status = emberAfGetNodeType(&nodeType);
  if (status != EMBER_SUCCESS) {
    goto done;
  }

  commandFrame[0] = NWK_REJOIN_REQUEST_COMMAND;
  commandFrame[1] = 0;
  switch (nodeType) {
    case EMBER_COORDINATOR:
      commandFrame[1] |= BIT(0); // alternate pan coordinator
    // fallthrough
    case EMBER_ROUTER:
      commandFrame[1] |= BIT(1); // device type
    // fallthrough
    case EMBER_END_DEVICE:
      commandFrame[1] |= BIT(2); // mains-powered
      commandFrame[1] |= BIT(3); // rx on when idle
    // fallthrough
    case EMBER_SLEEPY_END_DEVICE:
      commandFrame[1] |= BIT(7); // allocate address
      break;
    default:
      status = EMBER_ERR_FATAL;
  }

  status = sendNetworkCommand(destinationShort,
                              commandFrame,
                              sizeof(commandFrame));

  done:
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Rejoin request",
                     status);
}

// plugin test-harness z3 nwk nwk-rejoin-response <addr:2> <status:1> <dstShort:2>
void sli_zigbee_af_test_harness_z3_nwk_nwk_rejoin_response_command(SL_CLI_COMMAND_ARG)
{
  uint8_t     frame[4];
  EmberStatus status;

  EmberNodeId networkAddress   = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t     rejoinStatus     = sl_cli_get_argument_uint8(arguments, 1);
  EmberNodeId destinationShort = sl_cli_get_argument_uint16(arguments, 2);

  frame[0] = NWK_REJOIN_RESPONSE_COMMAND;
  frame[1] = LOW_BYTE(networkAddress);
  frame[2] = HIGH_BYTE(networkAddress);
  frame[3] = rejoinStatus;

  status = sendNetworkCommand(destinationShort, frame, sizeof(frame));

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Rejoin response",
                     status);
}

// plugin test-harness z3 nwk nwk-leave <rejoin:1> <request:1>
// <removeChildren:1> <dstShort:2> <options:4>
void sli_zigbee_af_test_harness_z3_nwk_nwk_leave_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status;
  uint8_t frame[2] = { NWK_LEAVE_COMMAND, 0, };

  bool rejoin                  = (bool)sl_cli_get_argument_uint32(arguments, 0);
  bool request                 = (bool)sl_cli_get_argument_uint32(arguments, 1);
  // CCB 2047
  // - CCB makes the first step to depracate the 'leave and remove children' functionality.
  // - We were proactive here and deprecated it right away.
  // bool removeChildren          = (bool)emberUnsignedCommandArgument(2);

  EmberNodeId destinationShort = sl_cli_get_argument_uint16(arguments, 3);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 4);

  if (rejoin) {
    frame[1] |= BIT(5);
  }
  if (request) {
    frame[1] |= BIT(6);
  }

  switch (options) {
    case BIT(0): // no ieee addr field
      status = (sli_zigbee_network_sendCommand(destinationShort,
                                               frame,
                                               sizeof(frame),
                                               false,
                                               NULL)
                ? EMBER_SUCCESS
                : EMBER_DELIVERY_FAILED);
      break;
    case BIT(1): // don't actually leave network
    // fallthrough
    default:
      status = sendNetworkCommand(destinationShort, frame, sizeof(frame));
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Leave",
                     status);
}

// plugin test-harness z3 nwk nwk-leave-supression on
// plugin test-harness z3 nwk nwk-leave-supression off
void sli_zigbee_af_test_harness_z3_nwk_nwk_leave_supression(SL_CLI_COMMAND_ARG)
{
  sli_zigbee_af_test_harness_z3_ignore_leave_commands
    = (sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL)[1] == 'n');

  emberAfCorePrintln("%s: %s: %s",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Supress network leave",
                     (sli_zigbee_af_test_harness_z3_ignore_leave_commands
                      ? "YES"
                      : "NO"));
}

// plugin test-harness z3 nwk nwk-key-supression on
// plugin test-harness z3 nwk nwk-key-supression off
void sli_zigbee_af_test_harness_z3_nwk_nwk_key_supression(SL_CLI_COMMAND_ARG)
{
  // TODO:
}

// plugin test-harness z3 nwk get-network-update-id
void sli_zigbee_af_test_harness_z3_nwk_get_network_update_id(SL_CLI_COMMAND_ARG)
{
  EmberNetworkParameters networkParameters;
  EmberNodeType nodeType;
  emberAfGetNetworkParameters(&nodeType, &networkParameters);
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network Update Id",
                     networkParameters.nwkUpdateId);
}

// plugin test-harness z3 nwk set-network-update-id
void sli_zigbee_af_test_harness_z3_nwk_set_network_update_id(SL_CLI_COMMAND_ARG)
{
  uint8_t updateId = sl_cli_get_argument_uint8(arguments, 0);
  // Note, we can't use emberSetNwkUpdateId here, since that only sets
  // the update ID in a variable that is used when forming a network
  sli_zigbee_set_nwk_update_id(updateId);
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Set network update id",
                     updateId);
}
