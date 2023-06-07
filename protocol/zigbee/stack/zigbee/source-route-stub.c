/***************************************************************************//**
 * @file
 * @brief Source routing stub code
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

#include PLATFORM_HEADER
#include "stack/include/ember-types.h"
#include "stack/include/message.h"
#include "stack/include/ember-types-internal.h"
#include "source-route-table-update.h"
#include "stack/core/ember-multi-network.h"

// -----------------------------------------------------------------------------
// Functions

//Mtorr related functions

void sli_zigbee_source_route_update_event_handler(void)
{
}

void sli_zigbee_concentrator_support_route_error_handler(EmberStatus status,
                                                         EmberNodeId nodeId)
{
  (void)status;
  (void)nodeId;
}

//source route table related functions
uint8_t sli_zigbee_source_route_find_index(EmberNodeId id)
{
  return SOURCE_ROUTE_NULL_INDEX;
}

uint8_t sli_zigbee_source_route_add_entryWithCloserNextHop(EmberNodeId newId,
                                                           EmberNodeId closerNodeId)
{
  (void)newId;
  (void)closerNodeId;
  return 0xFF;
}

uint8_t emberGetSourceRouteTableFilledSize(void)
{
  return 0;
}

uint8_t emberGetSourceRouteTableTotalSize(void)
{
  return 0;
}

void sli_zigbee_change_source_route_entry(EmberNodeId newChildId,
                                          EmberNodeId newParentId,
                                          bool ourChild,
                                          bool deviceLeft)
{
  (void)newChildId;
  (void)newParentId;
  (void)ourChild;
  (void)deviceLeft;
}

void sli_zigbee_incoming_route_record(EmberNodeId source,
                                      EmberEUI64 sourceEui,
                                      uint8_t relayCount,
                                      EmberMessageBuffer header,
                                      uint8_t relayListIndex)
{
  bool apiConsumed = true;
  sli_zigbee_enable_application_current_network(); // SET app current network
  emberOverrideIncomingRouteRecordHandler(source,
                                          sourceEui,
                                          relayCount,
                                          header,
                                          relayListIndex,
                                          &apiConsumed);
  sli_zigbee_restore_current_network();   // RESTORE
}

uint8_t sli_zigbee_append_source_route(EmberNodeId destination,
                                       EmberMessageBuffer* header)
{
  bool appConsumed = true;
  return emberOverrideAppendSourceRouteHandler(destination, header, &appConsumed);
}

EmberStatus emberGetSourceRouteTableEntry(uint8_t index,
                                          EmberNodeId *destination,
                                          uint8_t *closerIndex)
{
  (void)index;
  (void)destination;
  (void)closerIndex;
  return EMBER_NOT_FOUND;
}

uint8_t emberGetSourceRouteOverhead(EmberNodeId destination)
{
  (void)destination;
  return 0;
}

void sli_zigbee_source_route_table_init(void)
{
}

void sli_zigbee_source_route_update_init(void)
{
}

EmberStatus emberSetConcentrator(bool on,
                                 uint16_t concentratorTypeParam,
                                 uint16_t minTime,
                                 uint16_t maxTime,
                                 uint8_t routeErrorThresholdParam,
                                 uint8_t deliveryFailureThresholdParam,
                                 uint8_t maxHopsParam)
{
  (void)on;
  (void)concentratorTypeParam;
  (void)minTime;
  (void)maxTime;
  (void)routeErrorThresholdParam;
  (void)deliveryFailureThresholdParam;
  (void)maxHopsParam;
  return EMBER_INVALID_CALL;
}

uint32_t emberSetSourceRouteDiscoveryMode(EmberSourceRouteDiscoveryMode mode)
{
  (void)mode;
  return MAX_INT32U_VALUE;
}

// mtorr related
void emberConcentratorNoteRouteError(EmberStatus status,
                                     EmberNodeId nodeId)
{
  (void)status;
  (void)nodeId;
}

void emberConcentratorNoteDeliveryFailure(EmberOutgoingMessageType type, EmberStatus status)
{
  (void)type;
  (void)status;
}
