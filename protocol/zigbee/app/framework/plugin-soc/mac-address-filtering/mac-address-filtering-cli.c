/***************************************************************************//**
 * @file
 * @brief CLI for the MAC address filtering plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifdef PRO_COMPLIANCE
 #include "app/test/pro-compliance.h"
 #include "app/test/pro-compliance-printing.h"
#else // PRO_COMPLIANCE
 #include "app/framework/include/af.h"
 #include "app/util/serial/sl_zigbee_command_interpreter.h"
#endif /* PRO_COMPLIANCE */

#include "mac-address-filtering.h"

// *****************************************************************************
// Globals
#if (defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DIAGNOSTICS_CLUSTER)) || (SL_ZIGBEE_DEBUG_CORE_GROUP_ENABLED == 1)

static const MacAddressFilterOptionsDescription optionsDescription[] = {
  { MAC_FILTER_OPTIONS_NO_ADDRESS_MASK, "No Address Packets  ", "Accept   ", "Drop     " },
  { MAC_FILTER_OPTIONS_SHORT_ADDRESS_LIST_MASK, "Short Address Filter", "Whitelist", "Blacklist" },
  { MAC_FILTER_OPTIONS_LONG_ADDRESS_LIST_MASK, "Long Address Filter ", "Whitelist", "Blacklist" },
  { MAC_FILTER_OPTIONS_DEST_PAN_ID_LIST_MASK, "Dest PAN ID Filter", "Whitelist", "Blacklist" },

  { 0, NULL, NULL, NULL }, // terminator
};
#endif

// // -----------------------------------------------------------------------------
// // Command definitions

// Command: plugin mac-address-filtering print-config
// Description: Prints the current filtering config and statistics.
void emberAfPluginMacAddressFilteringPrintConfigCommand(sl_cli_command_arg_t * arguments)
{
  #if (defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_DIAGNOSTICS_CLUSTER)) || (SL_ZIGBEE_DEBUG_CORE_GROUP_ENABLED == 1)
  uint8_t i;
  emberAfCorePrintln("Total MAC Packets received: %lu", macAddressFilterData.totalPackets);
  emberAfCorePrintln("Options bitmask: 0x%X", macAddressFilterData.options);
  for ( i = 0; i < MAC_FILTER_OPTIONS_COUNT; i++ ) {
    const char* enabledDisabledTextPointer = ( (macAddressFilterData.options & optionsDescription[i].bit)
                                               ? optionsDescription[i].enabledDescription
                                               : optionsDescription[i].disabledDescription);
    emberAfCorePrintln("%s: %s  Packets Accepted %lu, Dropped: %lu",
                       optionsDescription[i].optionName,
                       enabledDisabledTextPointer,
                       macAddressFilterData.allowedPacketCount[i],
                       macAddressFilterData.droppedPacketCount[i]);
  }

  emberAfCorePrintln("Short Address Filter List");

  for ( i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++ ) {
    emberAfCorePrint("%d: ", i);
    if (macAddressFilterData.macShortAddressList[i].shortAddress
        == EMBER_NULL_NODE_ID) {
      emberAfCorePrintln("---");
    } else {
      emberAfCorePrintln("0x%2X  Match Count: %lu",
                         macAddressFilterData.macShortAddressList[i].shortAddress,
                         macAddressFilterData.macShortAddressList[i].matchCount);
    }
  }

  emberAfCorePrintln("\nLong Address Filter List");

  for ( i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH; i++ ) {
    emberAfCorePrint("%d: ", i);
    if (0 == MEMCOMPARE(macAddressFilterData.macLongAddressList[i].longAddress,
                        zeroEui64,
                        EUI64_SIZE)) {
      emberAfCorePrintln("---");
    } else {
      emberAfPrintBigEndianEui64(macAddressFilterData.macLongAddressList[i].longAddress);
      emberAfCorePrintln("  Match Count: %lu",
                         macAddressFilterData.macLongAddressList[i].matchCount);
    }
  }
  #endif
}

// Plugin CLI Description: Commands to manipulate the MAC address filtering tables.
// Command: plugin mac-address-filtering set-config no-address-filter <enable>
// Description: Enable/disable filtering of no-address messages.
// Arg: enable | bool | True means drop no-address messages, false means allow.
void emberAfPluginMacAddressFilteringFilterNoAddressCommand(sl_cli_command_arg_t * arguments)
{
  bool filterNoAddress = (bool)sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginMacAddressFilteringFilterNoAddress(filterNoAddress);
}

// Command: plugin mac-address-filtering short-address-list add <node-id>
// Description: Adds an address to the short address list.
// Arg: node-id | EmberNodeId | The node-id to add to the short list.
void emberAfPluginMacAddressFilteringAddShortAddressCommand(sl_cli_command_arg_t * arguments)
{
  EmberNodeId nodeId = (uint16_t)sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginMacAddressFilteringAddShortAddress(nodeId);
}

// Command: plugin mac-address-filtering short-address-list set-blacklist/set-whitelist
// Description:  Sets the short address list filter to a blacklist/whitelist.
void emberAfPluginMacAddressFilteringSetShortAddressListTypeCommand(sl_cli_command_arg_t * arguments)
{
  uint8_t* pointer
    = sl_zigbee_cli_get_argument_string_and_length(arguments, -1, // argument number
                                                   NULL); // returned length
  emberAfPluginMacAddressFilteringSetShortAddressListType(pointer);
}

// Command: plugin mac-address-filtering long-address-list set-blacklist/set-whitelist
// Description: Sets the long address list filter to a blacklist/whitelist.
void emberAfPluginMacAddressFilteringSetLongAddressListTypeCommand(sl_cli_command_arg_t * arguments)
{
  uint8_t* pointer
    = sl_zigbee_cli_get_argument_string_and_length(arguments, -1, // argument number
                                                   NULL); // returned length
  emberAfPluginMacAddressFilteringSetLongAddressListType(pointer);
}

// Command: plugin mac-address-filtering long-address-list add <eui64>
// Description: Adds a long address to the long address filter.
// Arg: eui64 | EmberEUI64 | The long address to add.
void emberAfPluginMacAddressFilteringAddLongAddressCommand(sl_cli_command_arg_t * arguments)
{
  EmberEUI64 eui64;
  sl_zigbee_copy_eui64_arg(arguments, 0, eui64, true);
  emberAfPluginMacAddressFilteringAddLongAddress(eui64);
}

// Command: plugin mac-address-filtering short-address-list clear
// Description: Clears the short address list filter.
void emberAfPluginMacAddressFilteringClearShortAddressList(sl_cli_command_arg_t * arguments)
{
  sli_zigbee_mac_address_filtering_clear_short_filter_list();
  emberAfCorePrintln("Short address list cleared.");
}

// Command: plugin mac-address-filtering long-address-list clear
// Description: Clears the long address list filter.
void emberAfPluginMacAddressFilteringClearLongAddressList(sl_cli_command_arg_t * arguments)
{
  sli_zigbee_mac_address_filtering_clear_long_filter_list();
  emberAfCorePrintln("Long address list cleared.");
}

// Command: plugin mac-address-filtering pan-id-list add <pan-id>
// Description: Adds a PAN ID to the filter.
// Arg: pan-id | uint16_t | The PAN ID to add to the list.
void emberAfPluginMacAddressFilteringAddPanIdCommand(sl_cli_command_arg_t * arguments)
{
  EmberPanId panId = (EmberPanId)sl_cli_get_argument_uint32(arguments, 0);
  emberAfPluginMacAddressFilteringAddPanId(panId);
}

// Command: plugin mac-address-filtering pan-id-list delete <index>
// Description: Deletes an entry in the PAN ID list filter.
// Arg: index | uint8_t | The index of the entry to delete.
void emberAfPluginMacAddressFilteringPanIdDeleteEntry(sl_cli_command_arg_t * arguments)
{
  uint8_t index = sl_cli_get_argument_uint32(arguments, 0);
  if (index >= EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH) {
    emberAfCorePrintln("Error: Index is greater than or equal to list length (%d)",
                       EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH);
    return;
  }

  macAddressFilterData.panIdFilterMatchList[index].panId = BROADCAST_PAN_ID;
  emberAfCorePrintln("Entry deleted.");
}

// Command: plugin mac-address-filtering pan-id-list clear
// Description: Clears the PAN ID list filter.
void emberAfPluginMacAddressFilteringClearPanIdList(sl_cli_command_arg_t * arguments)
{
  sli_zigbee_mac_address_filtering_clear_panid_filter_list();
}

// Command: plugin mac-address-filtering pan-id-list set-blacklist/set-whitelist
// Description:  Sets the PAN_ID list filter to a blacklist/whitelist.
void emberAfPluginMacAddressFilteringSetPanIdListTypeCommand(sl_cli_command_arg_t * arguments)
{
  uint8_t* pointer
    = sl_zigbee_cli_get_argument_string_and_length(arguments, -1, // argument number
                                                   NULL); // returned length
  emberAfPluginMacAddressFilteringSetPanIdListType(pointer);
}

// Command: plugin mac-address-filtering reset
// Description: Resets the state of the plugin to the default of no filtering.
void emberAfPluginMacAddressFilteringReset(sl_cli_command_arg_t * arguments)
{
  // TODO: update once we port the init callback
  emberAfPluginMacAddressFilteringInitCallback(SL_ZIGBEE_INIT_LEVEL_LOCAL_DATA);
  emberAfCorePrintln("All filter data cleared.");
}

// Command: plugin mac-address-filtering short-address-list delete <index>
// Description: Deletes an entry in the short address list filter.
// Arg: index | uint8_t | The index of the entry to delete.
void emberAfPluginMacAddressFilteringShortAddressDeleteEntry(sl_cli_command_arg_t * arguments)
{
  uint8_t index = sl_cli_get_argument_uint32(arguments, 0);
  if (index >= EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH) {
    emberAfCorePrintln("Error: Index is greater than or equal to list length (%d)",
                       EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH);
    return;
  }

  macAddressFilterData.macShortAddressList[index].shortAddress = EMBER_NULL_NODE_ID;
  emberAfCorePrintln("Entry deleted.");
}

// Command: plugin mac-address-filtering long-address-list delete <index>
// Description: Deletes an entry in the long address list filter.
// Arg: index | uint8_t | The entry in the long address list to delete.
void emberAfPluginMacAddressFilteringLongAddressDeleteEntry(sl_cli_command_arg_t * arguments)
{
  uint8_t index = sl_cli_get_argument_uint32(arguments, 0);
  if (index >= EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH) {
    emberAfCorePrintln("Error: Index is greater than or equal to list length (%d)",
                       EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH);
    return;
  }

  MEMSET(macAddressFilterData.macLongAddressList[index].longAddress,
         0,
         EUI64_SIZE);
  emberAfCorePrintln("Entry deleted.");
}
