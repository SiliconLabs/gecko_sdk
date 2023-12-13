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

const sli_zigbee_af_zigbee_pro_network sli_zigbee_af_zigbee_pro_networks[] = { { 2, 5 } };

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_GP_STACK == 1)

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

WEAK(EmberStatus sli_zigbee_af_gp_proxy_table_set_entryWrapper(uint8_t proxyIndex,
                                                               EmberGpProxyTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}

WEAK(void sli_zigbee_af_gp_proxy_table_init_wrapper(void))
{
}

WEAK(EmberStatus emberGpProxyTableGetEntryWrapper(uint8_t proxyIndex,
                                                  EmberGpProxyTableEntry *entry))
{
  return EMBER_INVALID_CALL;
}
WEAK(uint8_t sli_zigbee_af_gp_proxy_table_get_free_entry_indexWrapper(void))
{
  return 0xff;
}
WEAK(uint8_t emberGpProxyTableLookupWrapper(EmberGpAddress *addr))
{
  return 0xff;
}
WEAK(uint8_t sli_zigbee_af_gp_proxy_table_find_or_allocate_entryWrapper(EmberGpAddress *addr))
{
  return 0xff;
}
WEAK(void sli_zigbee_af_gp_proxy_table_add_sink_wrapper(uint8_t index,
                                                        uint8_t commMode,
                                                        EmberEUI64 sinkIeeeAddress,
                                                        EmberNodeId sinkNwkAddress,
                                                        uint16_t sinkGroupId,
                                                        uint16_t assignedAlias))
{
}
WEAK(void sli_zigbee_af_gp_proxy_table_remove_sink_wrapper(uint8_t index,
                                                           EmberEUI64 sinkIeeeAddress,
                                                           uint16_t sinkGroupId,
                                                           uint16_t assignedAlias))
{
}
WEAK(void sli_zigbee_af_gp_proxy_table_remove_entry_wrapper(uint8_t index))
{
}
WEAK(void sli_zigbee_af_gp_proxy_table_set_key_wrapper(uint8_t index, uint8_t * gpdKey, EmberGpKeyType securityKeyType))
{
}
WEAK(void sli_zigbee_af_gp_proxy_table_get_key_wrapper(uint8_t index, EmberKeyData *key))
{
}
WEAK(bool sli_zigbee_af_gp_address_matchWrapper(const EmberGpAddress *a1, const EmberGpAddress *a2))
{
  return false;
}

WEAK(void sli_zigbee_af_clear_gp_tx_queueWrapper(void))
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
WEAK(uint8_t sli_zigbee_af_gp_sink_table_get_free_entry_index_wrapper(void))
{
  return 0xff;
}

WEAK(uint8_t emberGpSinkTableFindOrAllocateEntryWrapper(EmberGpAddress *addr))
{
  return 0xff;
}

WEAK(void sli_zigbee_af_gp_sink_table_add_group_wrapper(uint8_t index,
                                                        uint16_t sinkGroupId,
                                                        uint16_t alias))
{
}
WEAK(bool sli_zigbee_af_gp_sink_table_remove_group_wrapper(uint8_t index,
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

WEAK(uint8_t emberGpSinkTableGetNumberOfActiveEntriesWrapper(void))
{
  return 0;
}

#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_GP_STACK == 1)
