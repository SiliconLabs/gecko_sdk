/***************************************************************************//**
 * @file
 * @brief CLI for the Network Steering plugin.
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

#include "network-steering.h"
#include "network-steering-internal.h"

// -----------------------------------------------------------------------------
// Helper macros and functions

static void addOrSubtractChannel(uint8_t maskToAddTo,
                                 uint8_t channelToAdd,
                                 bool operationIsAdd)
{
  if (channelToAdd < EMBER_MIN_802_15_4_CHANNEL_NUMBER
      || channelToAdd > EMBER_MAX_802_15_4_CHANNEL_NUMBER) {
    emberAfCorePrintln("Channel not valid: %d", channelToAdd);
  } else if (maskToAddTo == 1) {
    if (operationIsAdd) {
      SETBIT(sli_zigbee_af_network_steering_primary_channel_mask, channelToAdd);
    } else {
      CLEARBIT(sli_zigbee_af_network_steering_primary_channel_mask, channelToAdd);
    }

    emberAfCorePrintln("%p mask now 0x%4X",
                       "Primary",
                       sli_zigbee_af_network_steering_primary_channel_mask);
  } else if (maskToAddTo == 2) {
    if (operationIsAdd) {
      SETBIT(sli_zigbee_af_network_steering_secondary_channel_mask, channelToAdd);
    } else {
      CLEARBIT(sli_zigbee_af_network_steering_secondary_channel_mask, channelToAdd);
    }

    emberAfCorePrintln("%p mask now 0x%4X",
                       "Secondary",
                       sli_zigbee_af_network_steering_secondary_channel_mask);
  } else {
    emberAfCorePrintln("Mask not valid: %d", maskToAddTo);
  }
}

#include "app/util/serial/sl_zigbee_command_interpreter.h"

void emberAfPluginNetworkSteeringStartCommand(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_network_steering_options_mask = sl_cli_get_argument_uint8(arguments, 0);
  emberAfPluginNetworkSteeringStart();
}
// // -----------------------------------------------------------------------------
// // Command definitions

// // plugin network-steering mask add <[1=primary|2=secondary]:1> <channel:1>
// // plugin network-steering mask subtract <[1=primary|2=secondary]:1> <channel:1>
void emberAfPluginNetworkSteeringChannelAddOrSubtractCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t position = sl_cli_get_command_count(arguments) - 1;
  bool operationIsAdd = memcmp(sl_cli_get_command_string(arguments, position), "add", strlen("add")) == 0;
  uint8_t maskToAddTo  = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t channelToAdd = sl_cli_get_argument_uint8(arguments, 1);

  addOrSubtractChannel(maskToAddTo,
                       channelToAdd,
                       operationIsAdd);
}

void emberAfPluginNetworkSteeringChannelSetCommand(sl_cli_command_arg_t *arguments)
{
  bool maskIsPrimary = (sl_cli_get_argument_uint8(arguments, 0) == 1);
  uint32_t value = sl_cli_get_argument_uint32(arguments, 1);
  uint32_t *mask = (maskIsPrimary
                    ? &sli_zigbee_af_network_steering_primary_channel_mask
                    : &sli_zigbee_af_network_steering_secondary_channel_mask);

  emberAfCorePrintln("%p: Set %p mask to 0x%4X",
                     sli_zigbee_af_network_steering_plugin_name,
                     (maskIsPrimary ? "primary" : "secondary"),
                     (*mask = value));
}

// // plugin network-steering status
void emberAfPluginNetworkSteeringStatusCommand(sl_cli_command_arg_t *arguments)
{
  emberAfCorePrintln("%p: %p:",
                     sli_zigbee_af_network_steering_plugin_name,
                     "Status");

  emberAfCorePrintln("Channel mask:");
  emberAfCorePrint("    (1) 0x%4X [",
                   sli_zigbee_af_network_steering_primary_channel_mask);
  emberAfPrintChannelListFromMask(sli_zigbee_af_network_steering_primary_channel_mask);
  emberAfCorePrintln("]");
  emberAfCorePrint("    (2) 0x%4X [",
                   sli_zigbee_af_network_steering_secondary_channel_mask);
  emberAfPrintChannelListFromMask(sli_zigbee_af_network_steering_secondary_channel_mask);
  emberAfCorePrintln("]");

  emberAfCorePrintln("State: 0x%X (%s)",
                     sli_zigbee_af_network_steering_state,
                     sli_zigbee_af_network_steering_stateNames[sli_zigbee_af_network_steering_state]);
#ifndef OPTIMIZE_SCANS
  emberAfCorePrintln("Pan ID index: %d",
                     sli_zigbee_af_network_steering_pan_id_index);
#endif //  OPTIMIZE_SCANS
  emberAfCorePrintln("Current channel: %d",
                     sli_zigbee_af_network_steering_get_current_channel());
  emberAfCorePrintln("Total beacons: %d",
                     sli_zigbee_af_network_steering_total_beacons);
  emberAfCorePrintln("Join attempts: %d",
                     sli_zigbee_af_network_steering_join_attempts);
  emberAfCorePrintln("Network state: 0x%X",
                     emberAfNetworkState());
}

void emberAfPluginNetworkSteeringStopCommand(sl_cli_command_arg_t *arguments)
{
  emberAfCorePrintln("%s: %s: 0x%X",
                     sli_zigbee_af_network_steering_plugin_name,
                     "Stop",
                     emberAfPluginNetworkSteeringStop());
}

void emberAfPluginNetworkSteeringSetPreconfiguredKeyCommand(sl_cli_command_arg_t *arguments)
{
#ifndef OPTIMIZE_SCANS
  EmberKeyData keyData;
  size_t len = 16;
  uint8_t *ptr_string = sl_cli_get_argument_hex(arguments, 0, &len);
  MEMSET(keyData.contents, 0, EMBER_ENCRYPTION_KEY_SIZE);
  MEMMOVE(keyData.contents, ptr_string, EMBER_ENCRYPTION_KEY_SIZE); // Is the padding correct?

  sli_zigbee_af_network_steering_set_configured_key(keyData.contents, true);
#else // OPTIMIZE_SCANS
  emberAfCorePrintln("Unsupported feature when using optimized scans. To use"
                     " a configured key when joining, add the key to the"
                     " transient key table using the wildcard EUI (all FFs).");
#endif // OPTIMIZE_SCANS
}
