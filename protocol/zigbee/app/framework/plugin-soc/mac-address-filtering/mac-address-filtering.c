/***************************************************************************//**
 * @brief This plugin is used for testing. It creates MAC address filters to
 * artificially drop packets from certain devices to force a multi-hop
 * topology even if all devices are within radio range.
 * The packets are dropped above the lower MAC before the stack has a chance
 * to really process them but AFTER the radio has generated MAC ACKs for them.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories, Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of  Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software  is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER

#ifdef PRO_COMPLIANCE
 #include "app/test/pro-compliance.h"
 #include "app/test/pro-compliance-printing.h"
#else // PRO_COMPLIANCE
// this file contains all the common includes for clusters in the zcl-util
 #include "app/framework/include/af.h"
 #include "app/framework/util/common.h"
 #include "app/framework/util/util.h"
#endif // PRO_COMPLIANCE

#include "stack/include/ember-types.h"
#include "mac-address-filtering.h"

#if defined(EMBER_SCRIPTED_TEST)
  #include "app/framework/test/test-framework.h"
#endif

// *****************************************************************************
// Globals
const EmberEUI64 zeroEui64 = { 0, 0, 0, 0, 0, 0, 0, 0 };
MacAddressFilterGlobals macAddressFilterData;

// *****************************************************************************
// Internal Functions

static void clearStatsForFilterType(MacFilterType type)
{
  uint8_t i;
  macAddressFilterData.allowedPacketCount[type] = 0;
  macAddressFilterData.droppedPacketCount[type] = 0;

  if (type == MAC_FILTER_TYPE_SHORT_ADDRESS) {
    for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++) {
      macAddressFilterData.macShortAddressList[i].matchCount = 0;
    }
  } else if (type == MAC_FILTER_TYPE_LONG_ADDRESS) {
    for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH; i++) {
      macAddressFilterData.macLongAddressList[i].matchCount = 0;
    }
  } else if (type == MAC_FILTER_TYPE_PAN_ID) {
    for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH; i++) {
      macAddressFilterData.panIdFilterMatchList[i].matchCount = 0;
    }
  }
}

static void changeListConfig(bool currentConfigIsWhitelist,
                             MacFilterType type,
                             MacAddressFilterOptions valueForWhitelist,
                             uint8_t* pointer)
{
  bool changeToWhitelist = false;

  if (pointer[WHITELIST_CHARACTER_INDEX] == 'w') {
    changeToWhitelist = true;
  }

  if ((changeToWhitelist && !currentConfigIsWhitelist)
      || (!changeToWhitelist && currentConfigIsWhitelist)) {
    // If we are setting the list to the opposite of its current value,
    // clear the stats for that item.  Otherwise don't.
    // Prevents a problem where accidentally setting the list type
    // to the same thing clears the stats when that doesn't seem
    // like what the user wants.
    clearStatsForFilterType(type);
    emberAfCorePrintln("Cleared dropped packet count for list.");
  }

  if (changeToWhitelist) {
    macAddressFilterData.options |= valueForWhitelist;
  } else {
    macAddressFilterData.options &= ~valueForWhitelist;
  }

  emberAfCorePrintln("%s list changed to %slist.\n",
                     ((type == MAC_FILTER_TYPE_SHORT_ADDRESS)
                      ? "Short address"
                      : ((type == MAC_FILTER_TYPE_LONG_ADDRESS)
                         ? "Long address"
                         : ((type == MAC_FILTER_TYPE_PAN_ID)
                            ? "PAN ID"
                            : "No Address"))),
                     (changeToWhitelist
                      ? "white"
                      : "black"));
}

static FilterResult filterPacket(MacAddressMode mode,
                                 EmberNodeId shortAddress,
                                 EmberEUI64 longAddress,
                                 EmberPanId panId)
{
  uint8_t i;
  FilterResult result = ALLOW_PACKET;

  // We process Dest PAN ID separately because
  // although the packet may pass pan ID filtering, it may get filtered later
  // for other resaons.
  // PAN ID is the first order filtering, as is done in the real radio.
  // If the message is to the broadcast PAN ID always accept because it would
  // add unnecessary complexity making that yet another filter criteria.
  if (panId != BROADCAST_PAN_ID) {
    // PAN ID Filtering

    // PAN ID is a whitelist
    //   Any Dest PAN IDs *not* on the whitelist would be dropped
    //     If no PAN IDs are listed, all messages with a Source PAN ID would be dropped.
    //   Broadcast PAN ID would be accepted.
    //   Messages without PAN ID would also be accepted.

    // PAN ID is a blacklist
    //   Any Dest PAN ID on the list would be dropped.
    //   Broadcast PAN ID would be accepted
    //   Messages without PAN ID would also be accepted.

    bool found = false;
    result = ((macAddressFilterData.options & MAC_FILTER_OPTIONS_DEST_PAN_ID_WHITELIST)
              ? ALLOW_PACKET
              : DROP_PACKET);
    debug("Dest PAN ID: 0x%04X\n", panId);
    for (i = 0; !found && i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH; i++) {
      debug("Considering entry %d: 0x%04X\n",
            i,
            macAddressFilterData.panIdFilterMatchList[i].panId);
      if (macAddressFilterData.panIdFilterMatchList[i].panId != BROADCAST_PAN_ID
          && macAddressFilterData.panIdFilterMatchList[i].panId == panId) {
        macAddressFilterData.panIdFilterMatchList[i].matchCount++;
        found = true;
      }
    }

    if (!found) {
      // If not found, the result is the opposite of the list is configured to be.
      result = (result == ALLOW_PACKET ? DROP_PACKET : ALLOW_PACKET);
    }

    if (result == ALLOW_PACKET) {
      macAddressFilterData.allowedPacketCount[MAC_FILTER_TYPE_PAN_ID]++;

      // Keep going...
    } else {
      macAddressFilterData.droppedPacketCount[MAC_FILTER_TYPE_PAN_ID]++;
      expectCheckpoint("Message DROPPED due to PAN ID filtering.");
      return result;
    }
  }

  if (mode == MAC_ADDRESS_MODE_NONE) {
    if (!(macAddressFilterData.options & MAC_FILTER_OPTIONS_ALLOW_NO_ADDRESS)) {
      result = DROP_PACKET;
    }

    // We want to skip down to the end because we don't want to
    // invert the result as we do for the whitelists/blacklists for
    // short and long addressing.
    goto filterPacketDone;
  } else if (mode == MAC_ADDRESS_MODE_SHORT) {
    debug("Short Address mode, source: 0x%04X\n", shortAddress);
    result = ((macAddressFilterData.options & MAC_FILTER_OPTIONS_SHORT_ADDRESS_WHITELIST)
              ? ALLOW_PACKET
              : DROP_PACKET);

    for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++) {
      debug("Considering entry %d: 0x%04X\n",
            i,
            macAddressFilterData.macShortAddressList[i].shortAddress);
      if (shortAddress == macAddressFilterData.macShortAddressList[i].shortAddress
          && (macAddressFilterData.macShortAddressList[i].shortAddress
              != EMBER_NULL_NODE_ID)) {
        macAddressFilterData.macShortAddressList[i].matchCount++;
        goto filterPacketDone;
      }
    }

    // Keep going.
  } else if (mode == MAC_ADDRESS_MODE_LONG) {
    result = ((macAddressFilterData.options & MAC_FILTER_OPTIONS_LONG_ADDRESS_WHITELIST)
              ? ALLOW_PACKET
              : DROP_PACKET);
    debug("Long address mode, source: (>) 0x%02X%02X%02X%02X%02X%02X%02X%02X\n",
          longAddress[7],
          longAddress[6],
          longAddress[5],
          longAddress[4],
          longAddress[3],
          longAddress[2],
          longAddress[1],
          longAddress[0]);

    for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++) {
      if ((0 == MEMCOMPARE(longAddress,
                           macAddressFilterData.macLongAddressList[i].longAddress,
                           EUI64_SIZE))
          && (0 != MEMCOMPARE(longAddress, zeroEui64, EUI64_SIZE))) {
        debug("Found match to IEEE Address on list.\n");
        macAddressFilterData.macLongAddressList[i].matchCount++;
        goto filterPacketDone;
      }
    }

    // Keep going
  } else {
    // We should never reach here unless the caller has a bug.  That's okay in
    // real hardware but we want to catch that in simulation & unit tests.
    EMBER_TEST_ASSERT(0);
  }

  {
    // This should only be executed if there was no match on the above
    // whitelist/blacklists.
    // If there was no match, the result is the opposite of the configured option.
    result = (result == ALLOW_PACKET ? DROP_PACKET : ALLOW_PACKET);
  }

  // Fall through to below.

  filterPacketDone:
  expectCheckpoint("Parsed packet for address mode %s, filter result: %s",
                   ((mode == MAC_ADDRESS_MODE_NONE)
                    ? "NONE"
                    : ((mode == MAC_ADDRESS_MODE_SHORT)
                       ? "SHORT"
                       : "LONG")),
                   (result == ALLOW_PACKET
                    ? "ALLOWED"
                    : "DROPPED"));

  if (result == DROP_PACKET) {
    macAddressFilterData.droppedPacketCount[mode]++;
  } else {
    macAddressFilterData.allowedPacketCount[mode]++;
  }
  return result;
}

static FilterResult parseAndMaybeFilterPacket(uint8_t* rawMacContents,
                                              uint8_t macFrameControlStartIndex)
{
  MacAddressMode sourceMode;
  EmberNodeId macSourceShortAddress = EMBER_NULL_NODE_ID;
  EmberEUI64 macSourceLongAddress;
  EmberPanId panId = BROADCAST_PAN_ID;
  MEMCOPY(macSourceLongAddress, zeroEui64, EUI64_SIZE);

  uint16_t frameControl = (rawMacContents[macFrameControlStartIndex]
                           + (rawMacContents[macFrameControlStartIndex + 1] << 8));
  uint16_t frameType = (frameControl & MAC_FRAME_CONTROL_FRAME_TYPE_MASK);

  debug("FC: 0x%04X, Type: 0x%02X\n", frameControl, frameType);

  switch (frameType) {
    case MAC_FRAME_CONTROL_FRAME_TYPE_BEACON:
    case MAC_FRAME_CONTROL_FRAME_TYPE_DATA:
    case MAC_FRAME_CONTROL_FRAME_TYPE_COMMAND: {
      // 3 = 2 bytes for FC and 1 byte seq
      uint16_t index = macFrameControlStartIndex + 3;
      uint16_t sourceAddressModeFrameControl = ((frameControl
                                                 >> MAC_FRAME_CONTROL_SOURCE_ADDRESS_MODE_SHIFT)
                                                & MAC_FRAME_CONTROL_ADDRESS_MODE_MASK);
      uint16_t destAddressModeFrameControl = ((frameControl
                                               >> MAC_FRAME_CONTROL_DEST_ADDRESS_MODE_SHIFT)
                                              & MAC_FRAME_CONTROL_ADDRESS_MODE_MASK);
      debug("Src Mode: 0x%02X, Dest Mode: 0x%02X\n",
            sourceAddressModeFrameControl,
            destAddressModeFrameControl);

      if (sourceAddressModeFrameControl == MAC_FRAME_CONTROL_ADDRESS_MODE_RESERVED
          || destAddressModeFrameControl == MAC_FRAME_CONTROL_ADDRESS_MODE_RESERVED) {
        // Ignore packets with invalid address modes.
        break;
      }

      uint16_t fcVersion = (frameControl & MAC_FRAME_CONTROL_VERSION_MASK) >> MAC_FRAME_CONTROL_VERSION_SHIFT;

      if ((fcVersion != MAC_FRAME_CONTROL_VERSION_2003)     // enhanced beacon has version 2012
          && (!(fcVersion == MAC_FRAME_CONTROL_VERSION_2012 && frameType == MAC_FRAME_CONTROL_FRAME_TYPE_BEACON))) {
        // Ignore packets not using ZigBee's IEEE-802.15.4 2003 version since
        // this effects the "Intra-pan" field, a.k.a. PAN ID Compression,
        // and where address fields are interpreted.
        break;
      }

      sourceMode = ((sourceAddressModeFrameControl
                     == MAC_FRAME_CONTROL_ADDRESS_MODE_SHORT)
                    ? MAC_ADDRESS_MODE_SHORT
                    : ((sourceAddressModeFrameControl
                        == MAC_FRAME_CONTROL_ADDRESS_MODE_LONG)
                       ? MAC_ADDRESS_MODE_LONG
                       : MAC_ADDRESS_MODE_NONE));

      debug("Source Mode enum: %d\n", sourceMode);

      if (((destAddressModeFrameControl == MAC_FRAME_CONTROL_ADDRESS_MODE_NONE)
           && (sourceMode != MAC_ADDRESS_MODE_NONE))
          || ((destAddressModeFrameControl != MAC_FRAME_CONTROL_ADDRESS_MODE_NONE)
              && (sourceMode == MAC_ADDRESS_MODE_NONE))) {
        // The interpretation of the PAN ID compression bit in IEEE 802.15.4
        // is just crazy.  Instead of making that bit indicate the absence or
        // presence of both source and dest PAN, the bit is contigent
        // on the addressing modes.  This is further complicated by the fact
        // the addresses come after the PAN ID fields and thus we have
        // a strange interdependency between the two.

        // If dest is present but not source, or vice versa, then the
        // PAN ID Compression bit is set zero and only a single PAN ID
        // is included in the message.
        // Otherwise if both src and dest addresses are present,
        // the PAN ID compression bit indicates whether there is both
        // source and dest PAN ID (0), or just dest PAN ID (1).

        // If source address is present then the source PAN ID is present
        // If dest address is present, then dest PAN ID is present
        // Ultimately we only care about the dest address, which
        // is located at the end of the header after any PAN ID field.
        panId = (rawMacContents[index] + (rawMacContents[index + 1] << 8));

        index += 2; // PAN ID is 2-bytes.
      } else {  // Both source and dest address are present
        panId = (rawMacContents[index] + (rawMacContents[index + 1] << 8));

        index += 2; // dest PAN ID is 2-bytes

        if (!(frameControl & MAC_FRAME_CONTROL_PANID_COMPRESSION)) {
          // Technically the source and dest PAN ID can be different.
          // We don't record that because it not really used in ZigBee.
          // The only time it happens is for Association request, and then
          // the source PAN ID is 0xFFFF.  It really begs the question
          // of why bother including it then.
          // For simplicity, just filter on the previously parsed PAN ID.

          index += 2; // source PAN ID is 2-bytes
        }
      }

      if (destAddressModeFrameControl == MAC_FRAME_CONTROL_ADDRESS_MODE_SHORT) {
        index += 2;  // short addresses are 2-bytes
      } else if (destAddressModeFrameControl == MAC_FRAME_CONTROL_ADDRESS_MODE_LONG) {
        index += EUI64_SIZE;
      }

      if (sourceMode == MAC_ADDRESS_MODE_SHORT) {
        macSourceShortAddress = (rawMacContents[index] + (rawMacContents[index + 1] << 8));
      } else if (sourceMode == MAC_ADDRESS_MODE_LONG) {
        MEMCOPY(macSourceLongAddress, rawMacContents + index, EUI64_SIZE);
      }

      return (filterPacket(sourceMode,
                           macSourceShortAddress,
                           macSourceLongAddress,
                           panId));
    }

      // Default: Fall through
  }

  // By default accept the packet and let the stack sort it out.
  // This is the safest and more future proof thing to do.  We don't
  // want this plugin to require an update when the stack changes.
  return ALLOW_PACKET;
}

// *****************************************************************************
// Public Functions

EmberPacketAction emberAfIncomingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void *data)
{
  FilterResult result;
  if (packetType != EMBER_ZIGBEE_PACKET_TYPE_RAW_MAC) {
    expectCheckpoint("Ignoring non-matching callback type.");
    return EMBER_ACCEPT_PACKET;
  }

  macAddressFilterData.totalPackets++;

  // @TODO figure decide on how to deal with index being 0
  result = parseAndMaybeFilterPacket(packetData, 0);
  if (result == DROP_PACKET) {
    return EMBER_DROP_PACKET;
  } else {
    return EMBER_ACCEPT_PACKET;
  }
}

void emberAfPluginMacAddressFilteringInitCallback(uint8_t init_level)
{
  (void)init_level;

  MEMSET(&macAddressFilterData, 0, sizeof(MacAddressFilterGlobals));
  macAddressFilterData.options = MAC_FILTER_OPTIONS_DEFAULTS;
  sli_zigbee_mac_address_filtering_clear_short_filter_list();
  sli_zigbee_mac_address_filtering_clear_long_filter_list();
  sli_zigbee_mac_address_filtering_clear_panid_filter_list();
}

EmberStatus emberAfPluginMacAddressFilteringGetStatsForShortAddress(uint8_t index,
                                                                    uint32_t* matchCountForIndexPtr)
{
  if (index >= EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH) {
    return EMBER_BAD_ARGUMENT;
  }

  *matchCountForIndexPtr = macAddressFilterData.macShortAddressList[index].matchCount;

  return EMBER_SUCCESS;
}

void emberAfPluginMacAddressFilteringGetStats(bool shortMode,
                                              uint32_t* allowedPacketCountPtr,
                                              uint32_t* droppedPacketCountPtr,
                                              uint32_t* totalPacketCountPtr)
{
  MacAddressMode mode = (shortMode
                         ? MAC_ADDRESS_MODE_SHORT
                         : MAC_ADDRESS_MODE_LONG);

  *allowedPacketCountPtr = macAddressFilterData.allowedPacketCount[mode];
  *droppedPacketCountPtr = macAddressFilterData.droppedPacketCount[mode];
  *totalPacketCountPtr   = macAddressFilterData.totalPackets;
}

void emberAfPluginMacAddressFilteringClearStats(sl_cli_command_arg_t * arguments)
{
  clearStatsForFilterType(MAC_FILTER_TYPE_NO_ADDRESS);
  clearStatsForFilterType(MAC_FILTER_TYPE_SHORT_ADDRESS);
  clearStatsForFilterType(MAC_FILTER_TYPE_LONG_ADDRESS);
  clearStatsForFilterType(MAC_FILTER_TYPE_PAN_ID);
}

void emberAfPluginMacAddressFilteringFilterNoAddress(bool filterNoAddress)
{
  if (filterNoAddress) {
    macAddressFilterData.options &= ~MAC_FILTER_OPTIONS_ALLOW_NO_ADDRESS;
  } else {
    macAddressFilterData.options |= MAC_FILTER_OPTIONS_ALLOW_NO_ADDRESS;
  }
}

void emberAfPluginMacAddressFilteringAddLongAddress(EmberEUI64 eui64)
{
  uint8_t i;
  for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH; i++) {
    if (0 == MEMCOMPARE(macAddressFilterData.macLongAddressList[i].longAddress,
                        zeroEui64,
                        EUI64_SIZE)) {
      MEMCOPY(macAddressFilterData.macLongAddressList[i].longAddress,
              eui64,
              EUI64_SIZE);
      macAddressFilterData.macLongAddressList[i].matchCount = 0;
      return;
    }
  }

  emberAfCorePrintln("Error: No free entries in the long list.");
}

void emberAfPluginMacAddressFilteringAddPanId(EmberPanId panId)
{
  uint8_t i = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH; i++) {
    if (BROADCAST_PAN_ID
        == macAddressFilterData.panIdFilterMatchList[i].panId) {
      macAddressFilterData.panIdFilterMatchList[i].panId = panId;
      macAddressFilterData.panIdFilterMatchList[i].matchCount = 0;
      emberAfCorePrintln("Added PAN ID to list.");
      return;
    }
  }

  emberAfCorePrintln("Error: No free entries in the PAN ID list.");
}

void emberAfPluginMacAddressFilteringAddShortAddress(EmberNodeId nodeId)
{
  uint8_t i = 0;
  for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++) {
    if (EMBER_NULL_NODE_ID
        == macAddressFilterData.macShortAddressList[i].shortAddress) {
      macAddressFilterData.macShortAddressList[i].shortAddress = nodeId;
      macAddressFilterData.macShortAddressList[i].matchCount = 0;
      emberAfCorePrintln("Added short address to list.");
      return;
    }
  }

  emberAfCorePrintln("Error: No free entries in the short list.");
}

void emberAfPluginMacAddressFilteringSetShortAddressListType(uint8_t * listType)
{
  changeListConfig((macAddressFilterData.options
                    & MAC_FILTER_OPTIONS_SHORT_ADDRESS_WHITELIST),
                   MAC_FILTER_TYPE_SHORT_ADDRESS,
                   MAC_FILTER_OPTIONS_SHORT_ADDRESS_WHITELIST,
                   listType);
}

void emberAfPluginMacAddressFilteringSetLongAddressListType(uint8_t * listType)
{
  changeListConfig((macAddressFilterData.options
                    & MAC_FILTER_OPTIONS_LONG_ADDRESS_WHITELIST),
                   MAC_FILTER_TYPE_LONG_ADDRESS,
                   MAC_FILTER_OPTIONS_LONG_ADDRESS_WHITELIST,
                   listType);
}

void emberAfPluginMacAddressFilteringSetPanIdListType(uint8_t * listType)
{
  changeListConfig(macAddressFilterData.options
                   & MAC_FILTER_OPTIONS_DEST_PAN_ID_WHITELIST,
                   MAC_FILTER_TYPE_PAN_ID,
                   MAC_FILTER_OPTIONS_DEST_PAN_ID_WHITELIST,
                   listType);
}

void sli_zigbee_mac_address_filtering_clear_short_filter_list(void)
{
  // We need to set the short address list to be EMBER_NULL_NODE_ID by default
  // (0xFFFF) because 0x0000 is a valid address.  Thus our MEMSET() to 0 for
  // the global struct is not good enough.
  // We can't use MEMSET() because the ShortAddressFilterMatchStruct contains
  // a count variable that should be set to 0.
  uint8_t i;
  for (i = 0; i < EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH; i++) {
    macAddressFilterData.macShortAddressList[i].shortAddress
      = EMBER_NULL_NODE_ID;
  }
  clearStatsForFilterType(MAC_FILTER_TYPE_SHORT_ADDRESS);
}

void sli_zigbee_mac_address_filtering_clear_long_filter_list(void)
{
  MEMSET(macAddressFilterData.macLongAddressList,
         0,
         sizeof(LongAddressFilterMatchStruct)
         * EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH);
}

void sli_zigbee_mac_address_filtering_clear_panid_filter_list(void)
{
  MEMSET(macAddressFilterData.panIdFilterMatchList,
         0xFF,
         sizeof(PanIdFilterMatchStruct)
         * EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH);
}
