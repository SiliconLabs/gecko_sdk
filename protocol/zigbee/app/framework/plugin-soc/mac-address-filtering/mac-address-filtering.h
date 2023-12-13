/***************************************************************************//**
 * @file
 * @brief MAC Address Filtering - Public APIs
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

/**
 * @defgroup mac-address-filtering MAC Address Filtering
 * @ingroup component soc
 * @brief API and Callbacks for the MAC Address Filtering Component
 *
 * This plugin artificially limits what the stack hears by
 * filtering the packets just above the lower MAC.  The plugin can be
 * configured on the fly via CLI with the short or long address of devices
 * whose packets will be dropped or allowed.  There are two lists, a short
 * address list (2-byte node ID) and a long address list (8-byte IEEE address).
 * Each list may be configured as either an allow list or block list.
 * The default is a block list with no addresses configured (accept all packets normally).
 * A separate option allows or drops packets with no address
 * information (e.g., Beacon Requests).  NOTE:  The radio will still generate and
 * process MAC ACKs for packets.  This plugin cannot be used to effect the
 * behavior of MAC ACKs, which are handled by the RAIL library and radio hardware.
 *
 */

#ifndef SILABS_MAC_ADDRESS_FILTERING_H
#define SILABS_MAC_ADDRESS_FILTERING_H

#include "sl_cli_types.h"
/**
 * @addtogroup mac-address-filtering
 * @{
 */

// -----------------------------------------------------------------------------
// Types / Typedefs
#if defined(EMBER_SCRIPTED_TEST)
  #include "config/mac-address-filtering-config.h"
#else
  #include "mac-address-filtering-config.h"
  #define expectCheckpoint(...)
  #define debug(...)
#endif

#if defined (EMBER_SCRIPTED_TEST)
  #define EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH 10
  #define EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH  10
  #define EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH 10

  #undef EMBER_SUPPORTED_NETWORKS
  #define EMBER_SUPPORTED_NETWORKS 1
#elif defined (PRO_COMPLIANCE)

  #undef EMBER_SUPPORTED_NETWORKS
  #define EMBER_SUPPORTED_NETWORKS 1
#endif // EMBER_SCRIPTED_TEST || PRO_COMPLIANCE

#ifndef EMBER_TEST_ASSERT
 #define EMBER_TEST_ASSERT(...)
#endif // EMBER_TEST_ASSERT

#define MAC_FILTER_OPTIONS_NO_ADDRESS_MASK \
  (1 << MAC_FILTER_TYPE_NO_ADDRESS)
#define MAC_FILTER_OPTIONS_SHORT_ADDRESS_LIST_MASK \
  (1 << MAC_FILTER_TYPE_SHORT_ADDRESS)
#define MAC_FILTER_OPTIONS_LONG_ADDRESS_LIST_MASK \
  (1 << MAC_FILTER_TYPE_LONG_ADDRESS)
#define MAC_FILTER_OPTIONS_DEST_PAN_ID_LIST_MASK \
  (1 << MAC_FILTER_TYPE_PAN_ID)

// All possible options listed above
#define MAC_FILTER_OPTIONS_COUNT 4

#define MAC_FILTER_OPTIONS_DROP_NO_ADDRESS         0x00
#define MAC_FILTER_OPTIONS_SHORT_ADDRESS_BLACKLIST 0x00
#define MAC_FILTER_OPTIONS_LONG_ADDRESS_BLACKLIST  0x00

#define MAC_FILTER_OPTIONS_ALLOW_NO_ADDRESS        0x01
#define MAC_FILTER_OPTIONS_SHORT_ADDRESS_WHITELIST 0x02
#define MAC_FILTER_OPTIONS_LONG_ADDRESS_WHITELIST  0x04

#define MAC_FILTER_OPTIONS_DEST_PAN_ID_WHITELIST 0x08
#define MAC_FILTER_OPTIONS_DEST_PAN_ID_BLACKLIST 0x00

#define BROADCAST_PAN_ID 0xFFFF

// By default when a blacklist is enabled and there are no addresess in the
// list, then all messages will be accepted.
#define MAC_FILTER_OPTIONS_DEFAULTS (MAC_FILTER_OPTIONS_SHORT_ADDRESS_BLACKLIST  \
                                     | MAC_FILTER_OPTIONS_LONG_ADDRESS_BLACKLIST \
                                     | MAC_FILTER_OPTIONS_ALLOW_NO_ADDRESS       \
                                     | MAC_FILTER_OPTIONS_DEST_PAN_ID_BLACKLIST)

#define MAC_FRAME_CONTROL_FRAME_TYPE_MASK    0x0007
#define MAC_FRAME_CONTROL_FRAME_TYPE_BEACON  0x0000
#define MAC_FRAME_CONTROL_FRAME_TYPE_DATA    0x0001
#define MAC_FRAME_CONTROL_FRAME_TYPE_ACK     0x0002
#define MAC_FRAME_CONTROL_FRAME_TYPE_COMMAND 0x0003

#define MAC_FRAME_CONTROL_VERSION_MASK  0x3000
#define MAC_FRAME_CONTROL_VERSION_SHIFT 12
#define MAC_FRAME_CONTROL_VERSION_2003  0x0000
#define MAC_FRAME_CONTROL_VERSION_2012  0x0002

#define MAC_FRAME_CONTROL_SOURCE_ADDRESS_MODE_SHIFT 14

#define MAC_FRAME_CONTROL_ADDRESS_MODE_MASK     0x0003
#define MAC_FRAME_CONTROL_ADDRESS_MODE_NONE     0x0000
#define MAC_FRAME_CONTROL_ADDRESS_MODE_RESERVED 0x0001
#define MAC_FRAME_CONTROL_ADDRESS_MODE_SHORT    0x0002
#define MAC_FRAME_CONTROL_ADDRESS_MODE_LONG     0x0003

#define MAC_FRAME_CONTROL_DEST_ADDRESS_MODE_SHIFT 10

#define MAC_FRAME_CONTROL_DEST_ADDRESS_MODE_NONE 0x0000

#define MAC_FRAME_CONTROL_PANID_COMPRESSION 0x0040

#define WHITELIST_CHARACTER_INDEX 4

// These MUST correspond to the bit numbers defined for the filter options mask.
typedef enum {
  MAC_ADDRESS_MODE_NONE  = 0,
  MAC_ADDRESS_MODE_SHORT = 1,
  MAC_ADDRESS_MODE_LONG  = 2,
} MacAddressMode;

// NOTE:  We don't include the PAN ID as an "address mode" above because
// the PAN ID is separate from the address mode and it can be filtered
// on in addition to the source address.  However,
// we need to uniquely identify the list mask below in order to
// disambiguate the options we use to store stats and other items.

typedef enum {
  MAC_FILTER_TYPE_NO_ADDRESS    = 0,
  MAC_FILTER_TYPE_SHORT_ADDRESS = 1,
  MAC_FILTER_TYPE_LONG_ADDRESS  = 2,
  MAC_FILTER_TYPE_PAN_ID        = 3,
} MacFilterType;
typedef uint8_t MacAddressFilterOptions;

typedef struct {
  MacAddressFilterOptions bit;
  const char* optionName;
  const char* enabledDescription;
  const char* disabledDescription;
} MacAddressFilterOptionsDescription;

// A union could probably be used for the short/long and combine these two
// structs but that potentially creates developer errors if the wrong item
// in the struct is referenced.  Creating two structs will create compiler
// warnings/errors if used incorrectly.
typedef struct {
  uint32_t matchCount;
  EmberEUI64 longAddress;
} LongAddressFilterMatchStruct;

typedef struct {
  uint32_t matchCount;
  EmberNodeId shortAddress;
} ShortAddressFilterMatchStruct;

typedef struct {
  uint32_t matchCount;
  EmberPanId panId;
} PanIdFilterMatchStruct;

// This filter list should work regardless of the multi-MAC configuration
//   (i.e. the Dual-radio Smart Energy 2.4 ghz / sub-ghz devices)
// Short addresses are universal to the 2.4 ghz / sub-ghz MACs since
// there is one network across both.
// Multi-network will have a problem with Short address filtering because they
// will clash.  I am NOT making this code multi-network aware for the sake of
// simplicity.
typedef struct {
  ShortAddressFilterMatchStruct macShortAddressList[EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_SHORT_ADDRESS_FILTER_LENGTH];
  LongAddressFilterMatchStruct  macLongAddressList[EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_LONG_ADDRESS_FILTER_LENGTH];
  PanIdFilterMatchStruct panIdFilterMatchList[EMBER_AF_PLUGIN_MAC_ADDRESS_FILTERING_PAN_ID_FILTER_LENGTH];

  MacAddressFilterOptions options;

  uint32_t allowedPacketCount[MAC_FILTER_OPTIONS_COUNT];
  uint32_t droppedPacketCount[MAC_FILTER_OPTIONS_COUNT];
  uint32_t totalPackets;
} MacAddressFilterGlobals;

#if defined(EMBER_SUPPORTED_NETWORKS)
  #if EMBER_SUPPORTED_NETWORKS > 1
    #error "MAC Address Filtering plugin does NOT support multiple networks."
  #endif
#endif

typedef enum {
  ALLOW_PACKET = 0,
  DROP_PACKET  = 1,
} FilterResult;

// -----------------------------------------------------------------------------
// Globals
extern MacAddressFilterGlobals macAddressFilterData;

extern const EmberEUI64 zeroEui64;

/**
 * @name API
 * @{
 */

/** @brief Clear all lists for MAC address filtering.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringClearAll(void);

/** @brief Get stats for a short address.
 *
 * @param index Ver.: always
 * @param matchCountForIndexPtr Ver.: always
 *
 * @return EmberStatus status code
 *
 */
EmberStatus emberAfPluginMacAddressFilteringGetStatsForShortAddress(uint8_t index,
                                                                    uint32_t* matchCountForIndexPtr);
/** @brief Get MAC address filtering stats. Get the allowed, dropped and total packet counts.
 *
 * @param shortMode Ver.: always
 * @param allowedPacketCountPtr Ver.: always
 * @param droppedPacketCountPtr Ver.: always
 * @param totalPacketCountPtr Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringGetStats(bool shortMode,
                                              uint32_t* allowedPacketCountPtr,
                                              uint32_t* droppedPacketCountPtr,
                                              uint32_t* totalPacketCountPtr);

/** @brief Set the decision to manupulate the MAC address filtering tables.
 * @param filterNoAddress Ver.:always
 *
 */
void emberAfPluginMacAddressFilteringFilterNoAddress(bool filterNoAddress);

/** @brief Add the short address.
 * @param nodeId Ver.:always
 *
 */
void emberAfPluginMacAddressFilteringAddShortAddress(EmberNodeId nodeId);

/** @brief Add the long address.
 * @param eui64 Ver.:always
 *
 */
void emberAfPluginMacAddressFilteringAddLongAddress(EmberEUI64 eui64);

/** @brief Add the panID.
 * @param panId Ver.:always
 *
 */
void emberAfPluginMacAddressFilteringAddPanId(EmberPanId panId);

/** @brief Set the short address list type.
 * @param listType Ver.:always, listType can be "set-whitelist" or "set-blacklist".
 *
 */
void emberAfPluginMacAddressFilteringSetShortAddressListType(uint8_t * listType);

/** @brief Set the long address list type.
 * @param listType Ver.:always, listType can be "set-whitelist" or "set-blacklist".
 *
 */
void emberAfPluginMacAddressFilteringSetLongAddressListType(uint8_t * listType);

/** @brief Set the list type of panId list.
 * @param listType Ver.:always, listType can be "set-whitelist" or "set-blacklist".
 *
 */
void emberAfPluginMacAddressFilteringSetPanIdListType(uint8_t * listType);

/** @} */ // end of name API

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup mac_address_filtering_cb MAC Address Filtering
 * @ingroup af_callback
 * @brief Callbacks for MAC Address Filtering Component
 *
 */

/**
 * @addtogroup mac_address_filtering_cb
 * @{
 */

/** @brief Callback for MAC address filtering initialization.
 *
 * @param uint8_t init_level Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringInitCallback(uint8_t init_level);

/** @} */ // end of mac_address_filtering_cb
/** @} */ // end of name Callbacks
/** @} */ // end of mac-address-filtering

/** @brief Clear short address filter list */
void sli_zigbee_mac_address_filtering_clear_short_filter_list(void);

/** @brief Clear long address filter list */
void sli_zigbee_mac_address_filtering_clear_long_filter_list(void);

/** @brief Clear panID filter list */
void sli_zigbee_mac_address_filtering_clear_panid_filter_list(void);

#endif /* __SILABS_MAC_ADDRESS_FILTERING_H__ */
