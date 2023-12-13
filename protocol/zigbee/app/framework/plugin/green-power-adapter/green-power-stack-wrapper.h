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
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#include "zcl-framework-core-config.h"
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

#include "green-power-adapter-config.h"

#endif // SL_COMPONENT_CATALOG_PRESENT
/***************************************************************************
* Stub functions
* Customer should define these in their own application code
***************************************************************************/

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_GP_STACK == 1)
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

EmberStatus sli_zigbee_af_gp_proxy_table_set_entryWrapper(uint8_t proxyIndex,
                                                          EmberGpProxyTableEntry *entry);
void sli_zigbee_af_gp_proxy_table_init_wrapper(void);
EmberStatus emberGpProxyTableGetEntryWrapper(uint8_t proxyIndex,
                                             EmberGpProxyTableEntry *entry);
uint8_t sli_zigbee_af_gp_proxy_table_get_free_entry_indexWrapper(void);
uint8_t emberGpProxyTableLookupWrapper(EmberGpAddress *addr);
uint8_t sli_zigbee_af_gp_proxy_table_find_or_allocate_entryWrapper(EmberGpAddress *addr);
void sli_zigbee_af_gp_proxy_table_add_sink_wrapper(uint8_t index,
                                                   uint8_t commMode,
                                                   EmberEUI64 sinkIeeeAddress,
                                                   EmberNodeId sinkNwkAddress,
                                                   uint16_t sinkGroupId,
                                                   uint16_t assignedAlias);
void sli_zigbee_af_gp_proxy_table_remove_sink_wrapper(uint8_t index,
                                                      EmberEUI64 sinkIeeeAddress,
                                                      uint16_t sinkGroupId,
                                                      uint16_t assignedAlias);
void sli_zigbee_af_gp_proxy_table_remove_entry_wrapper(uint8_t index);
void sli_zigbee_af_gp_proxy_table_set_key_wrapper(uint8_t index, uint8_t * gpdKey, EmberGpKeyType securityKeyType);
void sli_zigbee_af_gp_proxy_table_get_key_wrapper(uint8_t index, EmberKeyData *key);
bool sli_zigbee_af_gp_address_matchWrapper(const EmberGpAddress *a1, const EmberGpAddress *a2);
void sli_zigbee_af_clear_gp_tx_queueWrapper(void);
void emberGpSinkTableInitWrapper(void);
EmberStatus emberGpSinkTableSetEntryWrapper(uint8_t sinkTableIndex,
                                            EmberGpSinkTableEntry *entry);
EmberStatus emberGpSinkTableGetEntryWrapper(uint8_t sinkTableIndex,
                                            EmberGpSinkTableEntry *entry);
uint8_t emberGpSinkTableEntryInUseWrapper(uint8_t sinkTableIndex);
uint8_t sli_zigbee_af_gp_sink_table_get_free_entry_index_wrapper(void);
uint8_t emberGpSinkTableFindOrAllocateEntryWrapper(EmberGpAddress *addr);
void sli_zigbee_af_gp_sink_table_add_group_wrapper(uint8_t index,
                                                   uint16_t sinkGroupId,
                                                   uint16_t alias);
bool sli_zigbee_af_gp_sink_table_remove_group_wrapper(uint8_t index,
                                                      uint16_t sinkGroupId,
                                                      uint16_t assignedAlias);
uint8_t emberGpSinkTableLookupWrapper(EmberGpAddress *addr);
void emberGpSinkTableRemoveEntryWrapper(uint8_t index);
void emberGpSinkTableSetSecurityFrameCounterWrapper(uint8_t index,
                                                    uint32_t sfc);

#define emberGpProxyTableProcessGpPairing emberGpProxyTableProcessGpPairingWrapper
#define sli_zigbee_af_gp_proxy_table_set_entry sli_zigbee_af_gp_proxy_table_set_entryWrapper
#define sli_zigbee_af_gp_proxy_table_init sli_zigbee_af_gp_proxy_table_init_wrapper
#define emberGpProxyTableGetEntry emberGpProxyTableGetEntryWrapper
#define sli_zigbee_af_gp_proxy_table_get_free_entry_index sli_zigbee_af_gp_proxy_table_get_free_entry_indexWrapper
#define emberGpProxyTableLookup emberGpProxyTableLookupWrapper
#define sli_zigbee_af_gp_proxy_table_find_or_allocate_entry sli_zigbee_af_gp_proxy_table_find_or_allocate_entryWrapper
#define sli_zigbee_af_gp_proxy_table_add_sink sli_zigbee_af_gp_proxy_table_add_sink_wrapper
#define sli_zigbee_af_gp_proxy_table_remove_sink sli_zigbee_af_gp_proxy_table_remove_sink_wrapper
#define sli_zigbee_af_gp_proxy_table_remove_entry sli_zigbee_af_gp_proxy_table_remove_entry_wrapper
#define sli_zigbee_af_gp_proxy_table_set_key sli_zigbee_af_gp_proxy_table_set_key_wrapper
#define sli_zigbee_af_gp_proxy_table_get_key sli_zigbee_af_gp_proxy_table_get_key_wrapper
#define sli_zigbee_af_gp_address_match sli_zigbee_af_gp_address_matchWrapper
#define sli_zigbee_af_clear_gp_tx_queue sli_zigbee_af_clear_gp_tx_queueWrapper
#define emberGpSinkTableInit emberGpSinkTableInitWrapper
#define emberGpSinkTableSetEntry emberGpSinkTableSetEntryWrapper
#define emberGpSinkTableGetEntry emberGpSinkTableGetEntryWrapper
#define emberGpSinkTableEntryInUse emberGpSinkTableEntryInUseWrapper
#define sli_zigbee_af_gp_sink_table_get_free_entry_index sli_zigbee_af_gp_sink_table_get_free_entry_index_wrapper
#define emberGpSinkTableFindOrAllocateEntry emberGpSinkTableFindOrAllocateEntryWrapper
#define sli_zigbee_af_gp_sink_table_add_group sli_zigbee_af_gp_sink_table_add_group_wrapper
#define sli_zigbee_af_gp_sink_table_remove_group sli_zigbee_af_gp_sink_table_remove_group_wrapper
#define emberGpSinkTableLookup emberGpSinkTableLookupWrapper
#define emberGpSinkTableRemoveEntry emberGpSinkTableRemoveEntryWrapper
#define emberGpSinkTableSetSecurityFrameCounter emberGpSinkTableSetSecurityFrameCounterWrapper
#define emberGpSinkTableGetNumberOfActiveEntries emberGpSinkTableGetNumberOfActiveEntriesWrapper

#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_GP_STACK == 1)

#endif //_SILABS_GREEN_POWER_STACK_WRAPPER_H_
