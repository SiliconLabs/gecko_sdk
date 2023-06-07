/***************************************************************************//**
 * @file
 * @brief CLI for the Network Find plugin.
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
#include "network-find.h"

//------------------------------------------------------------------------------
// Definitions for legacy CLI

#include "app/util/serial/sl_zigbee_command_interpreter.h"
void findMaskCommand(sl_cli_command_arg_t *arguments)
{
  const uint8_t page = sl_cli_get_argument_uint8(arguments, 0);
  const uint32_t mask = sl_cli_get_argument_uint32(arguments, 1);

  const EmberStatus status = emberAfSetFormAndJoinChannelMask(page, mask);

  switch (status) {
    case EMBER_SUCCESS:
      break;
    case EMBER_PHY_INVALID_CHANNEL:
      emberAfCorePrintln("Invalid channel page %d", page);
      break;
    case EMBER_MAC_INVALID_CHANNEL_MASK:
      emberAfCorePrintln("Invalid mask for channel page %d", page);
      break;
    default:
      emberAfCorePrintln("Error 0x%X", status);
      break;
  }
}

void findModeCommand(sl_cli_command_arg_t *arguments)
{
  const uint8_t mode = sl_cli_get_argument_uint8(arguments, 0);

  const EmberStatus status = emberAfSetFormAndJoinSearchMode(mode);
  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("Error 0x%X", status);
  }
}

void findPrintCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t page;
  uint8_t mode;
  bool allowAllChannels;

  // Only page 0 (and 28-31 if sub-GHz support is included) are valid.
  // For simplicity, go from 0 to 31 and simply skip any invalid page.
  for (page = 0; page <= 31; ++page) {
    const uint32_t mask = emberAfGetFormAndJoinChannelMask(page);
    if (mask != 0xFFFFFFFFU) {
      emberAfCorePrint("Page %d mask 0x%4X, %p", page, mask, "channels: ");
      emberAfCoreDebugExec(emberAfPrintChannelListFromMask(mask));
      emberAfCorePrintln("");
    }
  }

  mode = emberAfGetFormAndJoinSearchMode();
  emberAfCorePrintln("%s%s scan is %sABLED",
                     "2.4 ",
                     "GHz",
                     (mode & FIND_AND_JOIN_MODE_ALLOW_2_4_GHZ) ? "EN" : "DIS");
  emberAfCorePrintln("%s%s scan is %sABLED",
                     "Sub-",
                     "GHz",
                     (mode & FIND_AND_JOIN_MODE_ALLOW_SUB_GHZ) ? "EN" : "DIS");

  allowAllChannels = emberAfPluginNetworkFindGetEnableScanningAllChannelsCallback();
  emberAfCorePrintln("%s%s scan is %sABLED",
                     "Fallback on ",
                     "all channels",
                     allowAllChannels ? "EN" : "DIS");
}
