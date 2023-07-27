/***************************************************************************//**
 * @file
 * @brief
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
#include "stack/include/library.h"

EmberStatus sli_zigbee_gp_init(void)
{
  return EMBER_SUCCESS;
}

void sli_zigbee_af_gp_proxy_table_init(void)
{
}
void sli_zigbee_gp_incoming_message_handler(PacketHeader header)
{
  (void)header;
}
//CGP Stub

// CGP-DATA.request
void sli_zigbee_c_gp_send(bool useCca,
                          EmberGpAddress *src,
                          EmberGpAddress *dst,
                          uint8_t gpdCommandId,
                          EmberMessageBuffer asdu)
{
  (void)useCca;
  (void)src;
  (void)dst;
  (void)gpdCommandId;
  (void)asdu;
  return;
}

//CGP-DATA.confirm
void sli_zigbee_c_gp_sent_handler(EmberStatus status, uint8_t gpMpduHandle)
{
  (void)status;
  (void)gpMpduHandle;
  return;
}

//GP-DATA.request
EmberStatus emberDGpSend(bool action,
                         bool useCca,
                         EmberGpAddress *addr,
                         uint8_t gpdCommandId,
                         uint8_t gpdAsduLength,
                         uint8_t const *gpdAsdu,
                         uint8_t gpepHandle,
                         uint16_t gpTxQueueEntryLifetimeMs)
{
  (void)action;
  (void)useCca;
  (void)addr;
  (void)gpdCommandId;
  (void)gpdAsduLength;
  (void)gpdAsdu;
  (void)gpepHandle;
  (void)gpTxQueueEntryLifetimeMs;
  return EMBER_LIBRARY_NOT_PRESENT;
}

void sli_zigbee_read_gp_tokens(void)
{
  return;
}

bool sli_zigbee_is_gp_id_conflict(EmberNodeId shortId)
{
  (void)shortId;
  return false;
}

void sli_zigbee_detect_gp_id_conflict_and_resolve(EmberNodeId shortId,
                                                  uint8_t *longId)
{
  (void)shortId;
  (void)longId;
}
void sli_zigbee_update_gp_proxy_table(uint8_t *longId, EmberNodeId shortId)
{
  (void)longId;
  (void)shortId;
}

void sli_zigbee_gp_tx_event_handler(void)
{
}

bool emberGpProxyTableProcessGpPairing(uint32_t options,
                                       EmberGpAddress* addr,
                                       uint8_t commMode,
                                       uint16_t sinkNwkAddress,
                                       uint16_t sinkGroupId,
                                       uint16_t assignedAlias,
                                       uint8_t* sinkIeeeAddress,
                                       EmberKeyData* gpdKey,
                                       uint32_t gpdSecurityFrameCounter,
                                       uint8_t forwardingRadius)
{
  (void)options;
  (void)addr;
  (void)commMode;
  (void)sinkNwkAddress;
  (void)sinkGroupId;
  (void)assignedAlias;
  (void)sinkIeeeAddress;
  (void)gpdKey;
  (void)gpdSecurityFrameCounter;
  (void)forwardingRadius;
  return false;
}

uint8_t emberGpProxyTableLookup(EmberGpAddress *addr)
{
  (void)addr;
  return 0xFF;
}
EmberStatus emberGpProxyTableGetEntry(uint8_t proxyIndex,
                                      EmberGpProxyTableEntry *entry)
{
  (void)proxyIndex;
  (void)entry;
  return EMBER_LIBRARY_NOT_PRESENT;
}

EmberStatus emberGpSinkTableGetEntry(uint8_t sinkIndex,
                                     EmberGpSinkTableEntry *entry)
{
  (void)sinkIndex;
  (void)entry;
  return EMBER_LIBRARY_NOT_PRESENT;
}

uint8_t emberGpSinkTableLookup(EmberGpAddress *addr)
{
  (void)addr;
  return 0xFF;
}

EmberStatus emberGpSinkTableSetEntry(uint8_t sinkTableIndex,
                                     EmberGpSinkTableEntry *entry)
{
  (void)sinkTableIndex;
  (void)entry;
  return EMBER_LIBRARY_NOT_PRESENT;
}

uint8_t emberGpSinkTableFindOrAllocateEntry(EmberGpAddress *addr)
{
  (void)addr;
  return 0xFF;
}

void emberGpSinkTableRemoveEntry(uint8_t index)
{
  (void)index;
}

void emberGpSinkTableClearAll(void)
{
}
void emberGpSinkTableInit(void)
{
}

void emberGpSinkTableSetSecurityFrameCounter(uint8_t index,
                                             uint32_t sfc)
{
  (void)index;
  (void)sfc;
}
