/***************************************************************************//**
 * @file
 * @brief Definitions for the Sub-Ghz Client plugin.
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

#ifndef SUB_GHZ_CLIENT_H_INCLUDED
#define SUB_GHZ_CLIENT_H_INCLUDED

/**
 * @defgroup sub-ghz-client Sub GHz Client
 * @ingroup component cluster
 * @brief API and Callbacks for the Sub GHz Cluster Client Component
 *
 * The Smart Energy Sub-GHz client suspends the transmission of any ZCL messages
 * for a given period when instructed so by the Sub-GHz server.
 */

/**
 * @addtogroup sub-ghz-client
 * @{
 */

/**
 * @name API
 * @{
 */

/** @brief Send the 'Get Suspend ZCL Messages Status' command.
 *
 * This is a client command. The client sends it to determine the current status
 * of its ZCL communications from the server.
 *
 * @param nodeId The server's node ID.
 * @param endpoint The server's endpoint.
 */
EmberStatus emberAfPluginSubGhzClientSendGetSuspendZclMessagesStatusCommand(EmberNodeId nodeId,
                                                                            uint8_t endpoint);

/** @brief Send a request to change the channel to the server by
 * Mgmt_NWK_Unsolicited_Enhanced_Update_notify command.
 *
 * @param destination ........ the Sub-GHz server's node ID
 * @param channelPage ........ current channel page
 * @param channel ............ current channel
 *                             - the application needs to keep track of these values
 * @param macTxUcastTotal .... total number of Mac TX transaction attempts
 * @param macTxUcastFailures . total number of Mac TX transaction failures
 * @param macTxUcastRetries .. total number of Mac TX transaction retries
 * @param period ............. time in minutes over which macTxUcastXxx were measured
 *
 * @return An ::EmberStatus value.
 * - ::EMBER_SUCCESS
 * - ::EMBER_BAD_ARGUMENT if the channel page or channel are not in the valid range
 * - ::EMBER_NO_BUFFERS
 * - ::EMBER_NETWORK_DOWN
 * - ::EMBER_NETWORK_BUSY
 */
EmberStatus emberAfPluginSubGhzClientSendUnsolicitedEnhancedUpdateNotify(EmberNodeId destination,
                                                                         uint8_t channelPage,
                                                                         uint8_t channel,
                                                                         uint16_t macTxUcastTotal,
                                                                         uint16_t macTxUcastFailures,
                                                                         uint16_t macTxUcastRetries,
                                                                         uint8_t period);

/** @brief Return the current suspend status.
 *
 * @return  True if called within a suspend period, false otherwise.
 */
bool emberAfPluginSubGhzClientIsSendingZclMessagesSuspended();

/** @brief Ignore the SuspendZclMessages command.
 *
 * When the client receives the SuspendZclMessages command, it suspends sending
 * any ZCL messages for a given time. This function allows the client to ignore
 * the command and continue sending messages even when suspended.
 *
 * NOTE: For testing only.
 *       Ignoring the SuspendZclMessages command in production is non-compliant.
 *
 * @param ignore  True to ignore, false to switch back to normal behavior.
 */
void emberAfPluginSubGhzClientIgnoreSuspendZclMessagesCommand(bool ignore);
/** @} */ // end of name API
/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup sub_ghz_client_cb Sub GHz Client
 * @ingroup af_callback
 * @brief Callbacks for Sub GHz Client Component
 *
 */

/**
 * @addtogroup sub_ghz_client_cb
 * @{
 */

/** @brief Sub-GHz Cluster Suspend ZCL Messages.
 *
 * 'Suspend ZCL Messages' is a server command, sent to request the client
 * to temporarily suspend sending any ZCL messages to reduce the duty cycle.
 *
 * The clients' default action is to suspend ZCL messages for the requested period.
 *
 * @param period  suspend period in minutes
 *
 * @return  True to indicate the callback has been handled by the application,
 *          false to keep the default behavior
 */
bool emberAfPluginSubGhzSuspendZclMessagesCallback(uint8_t period);
/** @} */ // end of sub_ghz_client_cb
/** @} */ // end of name Callbacks
/** @} */ // end of sub-ghz-client

#endif // SUB_GHZ_CLIENT_H_INCLUDED
