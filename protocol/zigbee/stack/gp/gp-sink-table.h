/***************************************************************************//**
 * @file
 * @brief Zigbee GP sink definitions used by the framework and stack.
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

#ifndef GP_SINK_TABLE
#define GP_SINK_TABLE

#ifdef __cplusplus
extern "C" {
#endif

//#include "gp-proxy-table.h"

extern uint8_t sli_zigbee_gp_incoming_fc_in_sink_token_table_size;
extern uint8_t sli_zigbee_gp_incoming_fc_in_sink_token_timeout;

//these are declared in the config/ember-configuration.c
extern uint8_t sli_zigbee_gp_sink_table_size;
extern EmberGpSinkTableEntry sli_zigbee_gp_sink_table[];

#define EMBER_GP_SINK_TABLE_SECURITY_MASK 0x1F

void sli_zigbee_gp_write_incoming_fc_in_sink_to_token(uint8_t index);

void emberGpSinkTableClearAll(void);

#define sli_zigbee_gp_sink_table_entry_unused(index) \
  ((sli_zigbee_gp_sink_table[(index)].status         \
    == EMBER_GP_SINK_TABLE_ENTRY_STATUS_UNUSED)      \
   || (sli_zigbee_gp_sink_table[(index)].status == 0))

#define sli_zigbee_gp_sink_table_entry_active(index) \
  (sli_zigbee_gp_sink_table[(index)].status          \
   == EMBER_GP_SINK_TABLE_ENTRY_STATUS_ACTIVE)

#define  sli_zigbee_gp_sink_table_get_addr(index) \
  (&(sli_zigbee_gp_sink_table[(index)].gpd))

#define sli_zigbee_gp_sink_table_set_security_frame_counter(index, sfc) \
  (sli_zigbee_gp_sink_table[(index)].gpdSecurityFrameCounter = (sfc))

#define sli_zigbee_gp_sink_table_get_security_frame_counter(index) \
  (sli_zigbee_gp_sink_table[(index)].gpdSecurityFrameCounter)

#define sli_zigbee_gp_sink_table_get_options(index) \
  (sli_zigbee_gp_sink_table[(index)].options)

#define sli_zigbee_gp_sink_table_set_options(index, o) \
  (sli_zigbee_gp_sink_table[(index)].options = o)

#define sli_zigbee_gp_sink_table_has_security(index) \
  (sli_zigbee_gp_sink_table[(index)].options & EMBER_AF_GP_SINK_TABLE_ENTRY_OPTIONS_SECURITY_USE)

#define sli_zigbee_gp_sink_table_get_security_options(index) \
  (sli_zigbee_gp_sink_table[(index)].securityOptions)

#define sli_zigbee_gp_sink_table_set_security_options(index, o) \
  ((sli_zigbee_gp_sink_table[(index)].securityOptions = o))

#define sli_zigbee_gp_sink_table_get_sink_list(index) \
  (sli_zigbee_gp_sink_table[(index)].sinkList)

#define sli_zigbee_gp_sink_table_entry_has_link_key(index) \
  (((sli_zigbee_gp_sink_table[(index)].securityOptions) & EMBER_GP_SINK_TABLE_SECURITY_MASK))

#define sli_zigbee_gp_sink_table_get_security_key(index) \
  (sli_zigbee_gp_sink_table[(index)].gpdKey)

#define sli_zigbee_gp_sink_table_set_status(index, s) \
  (sli_zigbee_gp_sink_table[(index)].status = (s))

#define sli_zigbee_gp_sink_table_get_status(index) \
  (sli_zigbee_gp_sink_table[(index)].status)

#define sli_zigbee_gp_sink_table_set_in_range(index) \
  (sli_zigbee_gp_sink_table[(index)].options |= GP_SINK_TABLE_OPTIONS_IN_RANGE)

#define sli_zigbee_gp_sink_table_set_assigned_alias(index, s) \
  (sli_zigbee_gp_sink_table[(index)].assignedAlias = (s))

#define sli_zigbee_gp_sink_table_get_assigned_alias(index) \
  (sli_zigbee_gp_sink_table[(index)].assignedAlias)

#define sli_zigbee_gp_sink_table_set_device_id(index, s) \
  (sli_zigbee_gp_sink_table[(index)].deviceId = (s))

#define sli_zigbee_gp_sink_table_get_device_id(index) \
  (sli_zigbee_gp_sink_table[(index)].deviceId)

#define sli_zigbee_gp_sink_table_set_groupcast_radius(index, s) \
  (sli_zigbee_gp_sink_table[(index)].groupcastRadius = (s))

#define sli_zigbee_gp_sink_table_get_groupcast_radius(index) \
  (sli_zigbee_gp_sink_table[(index)].groupcastRadius)

bool sli_zigbee_af_gp_address_match(const EmberGpAddress *a1, const EmberGpAddress *a2);
void emberGpSinkTableInit(void);
EmberStatus emberGpSinkTableSetEntry(uint8_t sinkTableIndex,
                                     EmberGpSinkTableEntry *entry);
EmberStatus emberGpSinkTableGetEntry(uint8_t sinkTableIndex,
                                     EmberGpSinkTableEntry *entry);
uint8_t emberGpSinkTableEntryInUse(uint8_t sinkTableIndex);
uint8_t sli_zigbee_af_gp_sink_table_get_free_entry_index(void);

uint8_t emberGpSinkTableFindOrAllocateEntry(EmberGpAddress *addr);

void sli_zigbee_af_gp_sink_table_add_group(uint8_t index,
                                           uint16_t sinkGroupId,
                                           uint16_t alias);
bool sli_zigbee_af_gp_sink_table_remove_group(uint8_t index,
                                              uint16_t sinkGroupId,
                                              uint16_t assignedAlias);
uint8_t emberGpSinkTableLookup(EmberGpAddress *addr);
void emberGpSinkTableRemoveEntry(uint8_t index);
void emberGpSinkTableSetSecurityFrameCounter(uint8_t index,
                                             uint32_t sfc);

#ifdef __cplusplus
}
#endif

#endif //GP_SINK_TABLE
