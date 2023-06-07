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

#include "sl_cli_types.h"
/**
 * @addtogroup mac-address-filtering
 * @{
 */

/**
 * @name API
 * @{
 */

/** @brief Print configuration command.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringPrintConfigCommand(sl_cli_command_arg_t * arguments);

/** @brief Filter out the no address command.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringFilterNoAddressCommand(sl_cli_command_arg_t * arguments);

/** @brief Add the short address command.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringAddShortAddressCommand(sl_cli_command_arg_t * arguments);

/** @brief Set the short address list type.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringSetShortAddressListType(sl_cli_command_arg_t * arguments);

/** @brief Set the long address list type.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringSetLongAddressListType(sl_cli_command_arg_t * arguments);

/** @brief Add long address.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringAddLongAddressCommand(sl_cli_command_arg_t * arguments);

/** @brief Clear the short address list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringClearShortAddressList(sl_cli_command_arg_t * arguments);

/** @brief Clear the long address list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringClearLongAddressList(sl_cli_command_arg_t * arguments);

/** @brief Add panID.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringAddPanIdCommand(sl_cli_command_arg_t * arguments);

/** @brief Delete a panID entry.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringPanIdDeleteEntry(sl_cli_command_arg_t * arguments);

/** @brief Clear the panID list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringClearPanIdList(sl_cli_command_arg_t * arguments);

/** @brief Set the list type for panID list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringSetPanIdListType(sl_cli_command_arg_t * arguments);

/** @brief MAC address filtering reset.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringReset(sl_cli_command_arg_t * arguments);

/** @brief Clear all lists for MAC address filtering.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringClearAll(void);

/** @brief Delete an entry from short address list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringShortAddressDeleteEntry(sl_cli_command_arg_t * arguments);

/** @brief Delete an entry from long address list.
 *
 * @param sl_cli_command_arg_t * arguments Ver.: always
 *
 */
void emberAfPluginMacAddressFilteringLongAddressDeleteEntry(sl_cli_command_arg_t * arguments);

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
