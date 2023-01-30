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

#ifndef _SILABS_GREEN_POWER_STACK_WRAPPER_H_
#define _SILABS_GREEN_POWER_STACK_WRAPPER_H_

#include "zap-command.h"
#include "zap-id.h"
#include "zap-type.h"
#include "zap-enabled-incoming-commands.h"
#if !defined SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#define SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zap-command-structs.h"
#undef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#endif

#include "sl_service_function.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zcl-framework-core-config.h"
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-adapter-config.h"

#endif // SL_COMPONENT_CATALOG_PRESENT
/***************************************************************************
* Print stub functions
* Customer should define these in their own application code
***************************************************************************/

bool emberGpProxyTableProcessGpPairingWrapper(uint32_t options,
                                              EmberGpAddress* addr,
                                              uint8_t commMode,
                                              uint16_t sinkNwkAddress,
                                              uint16_t sinkGroupId,
                                              uint16_t assignedAlias,
                                              uint8_t* sinkIeeeAddress,
                                              EmberKeyData* gpdKey,
                                              uint32_t gpdSecurityFrameCounter,
                                              uint8_t forwardingRadius);

EmberStatus emGpProxyTableSetEntryWrapper(uint8_t proxyIndex,
                                          EmberGpProxyTableEntry *entry);
void emGpProxyTableInitWrapper(void);
EmberStatus emberGpProxyTableGetEntryWrapper(uint8_t proxyIndex,
                                             EmberGpProxyTableEntry *entry);
uint8_t emGpProxyTableGetFreeEntryIndexWrapper(void);
uint8_t emberGpProxyTableLookupWrapper(EmberGpAddress *addr);
uint8_t emGpProxyTableFindOrAllocateEntryWrapper(EmberGpAddress *addr);
void emGpProxyTableAddSinkWrapper(uint8_t index,
                                  uint8_t commMode,
                                  EmberEUI64 sinkIeeeAddress,
                                  EmberNodeId sinkNwkAddress,
                                  uint16_t sinkGroupId,
                                  uint16_t assignedAlias);
void emGpProxyTableRemoveSinkWrapper(uint8_t index,
                                     EmberEUI64 sinkIeeeAddress,
                                     uint16_t sinkGroupId,
                                     uint16_t assignedAlias);
void emGpProxyTableRemoveEntryWrapper(uint8_t index);
void emGpProxyTableSetKeyWrapper(uint8_t index, uint8_t * gpdKey, EmberGpKeyType securityKeyType);
void emGpProxyTableGetKeyWrapper(uint8_t index, EmberKeyData *key);
bool emGpAddressMatchWrapper(const EmberGpAddress *a1, const EmberGpAddress *a2);
void emClearGpTxQueueWrapper(void);
void emberGpSinkTableInitWrapper(void);
EmberStatus emberGpSinkTableSetEntryWrapper(uint8_t sinkTableIndex,
                                            EmberGpSinkTableEntry *entry);
EmberStatus emberGpSinkTableGetEntryWrapper(uint8_t sinkTableIndex,
                                            EmberGpSinkTableEntry *entry);
uint8_t emberGpSinkTableEntryInUseWrapper(uint8_t sinkTableIndex);
uint8_t emGpSinkTableGetFreeEntryIndexWrapper(void);
uint8_t emberGpSinkTableFindOrAllocateEntryWrapper(EmberGpAddress *addr);
void emGpSinkTableAddGroupWrapper(uint8_t index,
                                  uint16_t sinkGroupId,
                                  uint16_t alias);
bool emGpSinkTableRemoveGroupWrapper(uint8_t index,
                                     uint16_t sinkGroupId,
                                     uint16_t assignedAlias);
uint8_t emberGpSinkTableLookupWrapper(EmberGpAddress *addr);
void emberGpSinkTableRemoveEntryWrapper(uint8_t index);
void emberGpSinkTableSetSecurityFrameCounterWrapper(uint8_t index,
                                                    uint32_t sfc);

#define emberGpProxyTableProcessGpPairing emberGpProxyTableProcessGpPairingWrapper
#define emGpProxyTableSetEntry emGpProxyTableSetEntryWrapper
#define emGpProxyTableInit emGpProxyTableInitWrapper
#define emberGpProxyTableGetEntry emberGpProxyTableGetEntryWrapper
#define emGpProxyTableGetFreeEntryIndex emGpProxyTableGetFreeEntryIndexWrapper
#define emberGpProxyTableLookup emberGpProxyTableLookupWrapper
#define emGpProxyTableFindOrAllocateEntry emGpProxyTableFindOrAllocateEntryWrapper
#define emGpProxyTableAddSink emGpProxyTableAddSinkWrapper
#define emGpProxyTableRemoveSink emGpProxyTableRemoveSinkWrapper
#define emGpProxyTableRemoveEntry emGpProxyTableRemoveEntryWrapper
#define emGpProxyTableSetKey emGpProxyTableSetKeyWrapper
#define emGpProxyTableGetKey emGpProxyTableGetKeyWrapper
#define emGpAddressMatch emGpAddressMatchWrapper
#define emClearGpTxQueue emClearGpTxQueueWrapper
#define emberGpSinkTableInit emberGpSinkTableInitWrapper
#define emberGpSinkTableSetEntry emberGpSinkTableSetEntryWrapper
#define emberGpSinkTableGetEntry emberGpSinkTableGetEntryWrapper
#define emberGpSinkTableEntryInUse emberGpSinkTableEntryInUseWrapper
#define emGpSinkTableGetFreeEntryIndex emGpSinkTableGetFreeEntryIndexWrapper
#define emberGpSinkTableFindOrAllocateEntry emberGpSinkTableFindOrAllocateEntryWrapper
#define emGpSinkTableAddGroup emGpSinkTableAddGroupWrapper
#define emGpSinkTableRemoveGroup emGpSinkTableRemoveGroupWrapper
#define emberGpSinkTableLookup emberGpSinkTableLookupWrapper
#define emberGpSinkTableRemoveEntry emberGpSinkTableRemoveEntryWrapper
#define emberGpSinkTableSetSecurityFrameCounter emberGpSinkTableSetSecurityFrameCounterWrapper

#endif //_SILABS_GREEN_POWER_STACK_WRAPPER_H_
