/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "green-power-stack-wrapper.h"

const EmAfZigbeeProNetwork emAfZigbeeProNetworks[] = { { 2, 5 } };

WEAK(bool emberGpProxyTableProcessGpPairingWrapper(uint32_t options,
                                                   EmberGpAddress* addr,
                                                   uint8_t commMode,
                                                   uint16_t sinkNwkAddress,
                                                   uint16_t sinkGroupId,
                                                   uint16_t assignedAlias,
                                                   uint8_t* sinkIeeeAddress,
                                                   EmberKeyData* gpdKey,
                                                   uint32_t gpdSecurityFrameCounter,
                                                   uint8_t forwardingRadius))
{
  return false;
}

WEAK(EmberStatus emGpProxyTableSetEntryWrapper(uint8_t proxyIndex,
                                               EmberGpProxyTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}

WEAK(void emGpProxyTableInitWrapper(void))
{
}

WEAK(EmberStatus emberGpProxyTableGetEntryWrapper(uint8_t proxyIndex,
                                                  EmberGpProxyTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}
WEAK(uint8_t emGpProxyTableGetFreeEntryIndexWrapper(void))
{
  return 0xff;
}
WEAK(uint8_t emberGpProxyTableLookupWrapper(EmberGpAddress *addr))
{
  return 0xff;
}
WEAK(uint8_t emGpProxyTableFindOrAllocateEntryWrapper(EmberGpAddress *addr))
{
  return 0xff;
}
WEAK(void emGpProxyTableAddSinkWrapper(uint8_t index,
                                       uint8_t commMode,
                                       EmberEUI64 sinkIeeeAddress,
                                       EmberNodeId sinkNwkAddress,
                                       uint16_t sinkGroupId,
                                       uint16_t assignedAlias))
{
}
WEAK(void emGpProxyTableRemoveSinkWrapper(uint8_t index,
                                          EmberEUI64 sinkIeeeAddress,
                                          uint16_t sinkGroupId,
                                          uint16_t assignedAlias))
{
}
WEAK(void emGpProxyTableRemoveEntryWrapper(uint8_t index))
{
}
WEAK(void emGpProxyTableSetKeyWrapper(uint8_t index, uint8_t * gpdKey, EmberGpKeyType securityKeyType))
{
}
WEAK(void emGpProxyTableGetKeyWrapper(uint8_t index, EmberKeyData *key))
{
}
WEAK(bool emGpAddressMatchWrapper(const EmberGpAddress *a1, const EmberGpAddress *a2))
{
  return false;
}

WEAK(void emClearGpTxQueueWrapper(void))
{
}

WEAK(void emberGpSinkTableInitWrapper(void))
{
}
WEAK(EmberStatus emberGpSinkTableSetEntryWrapper(uint8_t sinkTableIndex,
                                                 EmberGpSinkTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}
WEAK(EmberStatus emberGpSinkTableGetEntryWrapper(uint8_t sinkTableIndex,
                                                 EmberGpSinkTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}
WEAK(uint8_t emberGpSinkTableEntryInUseWrapper(uint8_t sinkTableIndex))
{
  return 0xff;
}
WEAK(uint8_t emGpSinkTableGetFreeEntryIndexWrapper(void))
{
  return 0xff;
}

WEAK(uint8_t emberGpSinkTableFindOrAllocateEntryWrapper(EmberGpAddress *addr))
{
  return 0xff;
}

WEAK(void emGpSinkTableAddGroupWrapper(uint8_t index,
                                       uint16_t sinkGroupId,
                                       uint16_t alias))
{
}
WEAK(bool emGpSinkTableRemoveGroupWrapper(uint8_t index,
                                          uint16_t sinkGroupId,
                                          uint16_t assignedAlias))
{
  return false;
}
WEAK(uint8_t emberGpSinkTableLookupWrapper(EmberGpAddress *addr))
{
  return 0xff;
}
WEAK(void emberGpSinkTableRemoveEntryWrapper(uint8_t index))
{
}
WEAK(void emberGpSinkTableSetSecurityFrameCounterWrapper(uint8_t index,
                                                         uint32_t sfc))
{
}

// Stack Handlers
void emAfIncomingMessageHandler(EmberIncomingMessageType type,
                                EmberApsFrame *apsFrame,
                                uint8_t lastHopLqi,
                                int8_t lastHopRssi,
                                uint16_t messageLength,
                                uint8_t *messageContents);

WEAK(void emAfIncomingMessageCallback(EmberIncomingMessageType type,
                                      EmberApsFrame *apsFrame,
                                      EmberMessageBuffer message))
{
  uint8_t lastHopLqi;
  int8_t lastHopRssi;

  emberGetLastHopLqi(&lastHopLqi);
  emberGetLastHopRssi(&lastHopRssi);

  emAfIncomingMessageHandler(type,
                             apsFrame,
                             lastHopLqi,
                             lastHopRssi,
                             emGetBufferLength(message),
                             emGetBufferPointer(message));
}

void emberAfIncomingMessageCallback(
  // Incoming message type
  EmberIncomingMessageType type,
  // The aps Frame
  EmberApsFrame *apsFrame,
  // message
  EmberMessageBuffer message)
{
  emAfIncomingMessageCallback(type, apsFrame, message);
}
