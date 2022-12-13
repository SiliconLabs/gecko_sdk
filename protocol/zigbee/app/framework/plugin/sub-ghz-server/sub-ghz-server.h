/***************************************************************************//**
 * @file
 * @brief Definitions for the Sub-Ghz Server plugin.
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

#ifndef SUB_GHZ_SERVER_H_INCLUDED
#define SUB_GHZ_SERVER_H_INCLUDED

/**
 * @defgroup sub-ghz-server Sub GHz Server
 * @ingroup component cluster
 * @brief API and Callbacks for the Sub GHz Cluster Server Component
 *
 * The Smart Energy Sub-GHz server monitors clients' and its own duty cycles.
 * After a Limited threshold is reached, the Sub-GHz server instructs the offending
 * client to suspend sending any more ZCL messages for a certain period. On
 * reaching the Critical threshold, the suspend ZCL messages command is
 * broadcast to all clients.
 *
 */

/**
 * @addtogroup sub-ghz-server
 * @{
 */

/**
 * @name API
 * @{
 */

/** @brief Send the 'Suspend ZCL Messages' command.
 *
 * This is a server command. The server sends it to temporarily suspend ZCL messages
 * from clients it identifies as causing too much traffic.
 * It is also sent in response to the 'Get Suspend ZCL Messages Status' command.
 *
 * @param nodeId  The client's node ID.
 * @param endpoint The client's endpoint (ignored, backwards compatibility only).
 * @param period The suspension period in minutes.
 *
 * Note:
 * If endpoint == 0, the framework will choose the suitable endpoint based on
 * the past communication with the given node. If GetSuspendZclMessagesStatus has
 * never been received by the server, the server will not know which endpoint
 * implements the Sub-GHz Client and will default to endpoint 1. The application
 * can "teach" the server the client endpoint by discovering the Sub-GHz clients
 * and call this function for each of them with period == 0.
 */
EmberStatus emberAfPluginSubGhzServerSendSuspendZclMessagesCommand(EmberNodeId nodeId,
                                                                   uint8_t endpoint,
                                                                   uint8_t period);

/** @brief Get the current suspend status for a given client.
 *
 * @param nodeId The client's node ID.
 *
 * @return  The number of seconds remaining; 0 = not suspended.
 */
uint16_t emberAfPluginSubGhzServerSuspendZclMessagesStatus(EmberNodeId nodeId);

//------------------------------------------------------------------------------
// Application Framework Internal Functions
//
// The functions below are non-public internal function used by the application
// framework. They are NOT to be used by the application.

/** @brief An incoming message handler.
 *
 * Used to handle any incoming message from clients.
 * Based on the Duty Cycle state, client's ID (has the client been suspended?)
 * and the message type, determines the right action, which could be one of:
 * - let the message through to allow the framework to process it further
 * - respond with 'Suspend ZCL Messages' and suppress this message
 * - suppress the message silently.
 *
 * @return True if the message has been processed by the Sub-GHz plugin and
 *         should be suppressed, false to allow the message through.
 */
bool emAfSubGhzServerIncomingMessage(EmberIncomingMessageType type,
                                     EmberApsFrame *apsFrame,
                                     EmberNodeId sender,
                                     uint16_t messageLength,
                                     uint8_t *messageContents);

/** @} */ // end of name API

/**
 * @name Callbacks
 * @{
 */

/**
 * @defgroup sub_ghz_server Sub GHz Server
 * @ingroup af_callback
 * @brief Callbacks for Sub GHz Server Component
 *
 */

/**
 * @addtogroup sub_ghz_server
 * @{
 */

/** @brief Incoming ZDO message handler.
 *
 * Used to handle the incoming Mgmt_NWK_Unsolicited_Enhanced_Update_notify command.
 * Calls the user's emberAfPluginSubGhzUnsolicitedEnhancedUpdateNotifyCallback in response.
 */
void emAfSubGhzServerZDOMessageReceivedCallback(EmberNodeId sender,
                                                const uint8_t* message,
                                                uint16_t length);

/** @brief Callback to let the application handle the incoming
 * Mgmt_NWK_Unsolicited_Enhanced_Update_notify command.
 *
 * 'Mgmt_NWK_Unsolicited_Enhanced_Update_notify' is a client command. The client
 * sends it to notify the server about the poor link quality. The server should
 * determine whether a channel change is necessary and change the channel if so.
 * There is no default action performed by the application framework. If not
 * handled by the application, no action is taken.
 *
 * @param channelPage ........ current channel page
 * @param channel ............ current channel
 * @param macTxUcastTotal .... total number of Mac Tx transaction attempts
 * @param macTxUcastFailures . total number of Mac Tx transaction failures
 * @param macTxUcastRetries .. total number of Mac Tx transaction retries
 * @param period ............. time in minutes over which macTxUcastXxx were measured
 */
void emberAfPluginSubGhzUnsolicitedEnhancedUpdateNotifyCallback(uint8_t channelPage,
                                                                uint8_t channel,
                                                                uint16_t macTxUcastTotal,
                                                                uint16_t macTxUcastFailures,
                                                                uint16_t macTxUcastRetries,
                                                                uint8_t period);

/** @brief Duty cycle state change callback for the use with the Sub-GHz plugin.
 *
 * The Sub-GHz plugin monitors the duty cycle and calls this callback every time
 * the duty cycle state changes.
 *
 * @param channel   the channel that registered a Duty Cycle state change
 * @param curMode   current Duty Cycle mode
 * @param oldState  the previous Duty Cycle state
 * @param newState  the current Duty Cycle state
 *
 * @return  true to handle in the application, false for default behaviour
 *
 * The default response is sending the 'Suspend ZCL Messages' command, either by
 * unicast to the most offending client of a broadcast to all clients, depending
 * on the old and new duty cycle state.
 */
bool emberAfPluginSubGhzDutyCycleCallback(uint8_t channelPage,
                                          uint8_t channel,
                                          EmberDutyCycleState oldState,
                                          EmberDutyCycleState newState);

/** @brief Get the suspend ZCL messages status.
 *
 * 'Get Suspend ZCL Messages Status' is a client command. The client can send it
 * to the server to query the status instead of waiting for the 'Suspend ZCL Messages'
 * command.
 *
 * The server's default action is sending the 'Suspend ZCL Messages' command
 * with the parameter indicating the remaining suspend time in minutes.
 *
 * @return  True to indicate the callback has been handled by the application,
 *          false to keep the default behavior
 */
bool emberAfPluginSubGhzGetSuspendZclMessagesStatusCallback(void);

/** @} */ // end of sub_ghz_server
/** @} */ // end of name Callbacks
/** @} */ // end of sub-ghz-server

#endif // SUB_GHZ_SERVER_H_INCLUDED
