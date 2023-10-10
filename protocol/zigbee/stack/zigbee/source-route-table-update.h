/***************************************************************************//**
 * @file
 * @brief Code used for managing source route table
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

#ifndef SILABS_ZIGBEE_SOURCE_ROUTE_TABLE_UPDATE_H
#define SILABS_ZIGBEE_SOURCE_ROUTE_TABLE_UPDATE_H

// source-route-table related

extern uint8_t sli_zigbee_source_route_table_size;
extern SourceRouteTableEntry sli_zigbee_source_route_table_data[];
extern uint8_t sourceRouteTableEntryCount[];
extern uint8_t sourceRouteTableNewestIndex[];

// A special index. For destinations that are neighbors of the gateway,
// closerIndex is set to 0xFF. For the oldest entry, olderIndex is set to
// 0xFF.
#define SOURCE_ROUTE_NULL_INDEX 0xFF

uint8_t sli_zigbee_source_route_find_index(EmberNodeId id);
uint8_t sli_zigbee_source_route_add_entry(EmberNodeId id,
                                          uint8_t furtherIndex);
EmberStatus sli_zigbee_source_route_delete_entry(EmberNodeId id);
void sli_zigbee_source_route_table_init(void);
void sli_zigbee_source_route_update_init(void);
uint8_t sli_zigbee_source_route_get_count(void);
void sli_zigbee_source_route_clear_table(void);
uint8_t sli_zigbee_source_route_add_entryWithCloserNextHop(EmberNodeId newId,
                                                           EmberNodeId closerNodeId);

/** @brief Updates the source route entry based on new information about the
 * change of the child's parent and status
 * @param newChildId    The short address of the child
 * @param newParentId   The short address of the parent of the child
 * @param ourChild      True if the child is associated to the local node
 * @param deviceLeft    True if device has left network
 */
void sli_zigbee_change_source_route_entry (EmberNodeId newChildId,
                                           EmberNodeId newParentId,
                                           bool ourChild,
                                           bool deviceLeft);

/** @brief
 *
 * If header is :EMBER_NULL_MESSAGE_BUFFER, the only action is to return
 * the size of the source route frame needed to the destination.
 *
 * @param destination   The network destination of the message.
 * @param header        The pointer to the message buffer containing the partially
 * complete packet header.  The application appends the source
 * route frame to this header.
 *
 * @return The size in bytes of the source route frame, or zero
 * if one isn't available.
 */
uint8_t sli_zigbee_append_source_route (EmberNodeId destination,
                                        EmberMessageBuffer* header);

/** @brief Reports the arrival of a route record command frame
 *
 * The route record command frame lists the short
 * IDs of the relays that were used along the route from the source to us.
 * This information is used by aggregators to initiate
 * source routed messages.
 *
 * @param source          The ID of the node that initiated the route record.
 * @param sourceEui       The EUI64 of the node that initiated the route record.
 * @param relayCount      The number of relays in the list.
 * @param header          The message buffer containing the route record frame.
 * @param relayListIndex  The starting index of the relay list. The
 * relay closest to the source is listed first, and the relay closest
 * to the local device is listed last.  Short IDs are stored low byte first.  Be
 * careful to use buffer-boundary-safe APIs to read the list.
 */
void sli_zigbee_incoming_route_record(EmberNodeId source,
                                      EmberEUI64 sourceEui,
                                      uint8_t relayCount,
                                      EmberMessageBuffer header,
                                      uint8_t relayListIndex);

/** @brief The application can implement this callback to override the source route's closer index.
 * This callback can be consumed by the application to override the source routing information.
 * This is not recommended and should only be used for testing purposes.
 */
void emberOverrideFurthurIndexForSourceRouteAddEntryHandler(EmberNodeId id,
                                                            uint8_t* furtherIndex);

#endif // SILABS_ZIGBEE_SOURCE_ROUTE_TABLE_UPDATE_H
