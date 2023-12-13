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

/** @brief Clear sink table.
 *
 * @returns Nothing
 *
 * Detailed This function clears all entries in the sink table.
 *
 */
void emberGpSinkTableClearAll(void);

/******************************************************************************
 * Brief This function Initialises the sink table entries in the sink table
 *
 * @returns Nothing
 *
 * Detailed This function initializes the sink table in RAM. It copies the non-volatile sink table entries to
 *          a RAM table which is used during operation. By design,the non-volatile token entry for the sink table
 *          are compressed and does not hold the data that can be derived. This function is only called during
 *          initialization of the green power stack to initialize the entire table with derived data.
 *****************************************************************************/
void emberGpSinkTableInit(void);

/******************************************************************************
 * Brief This function adds a sink table entry for a given index.
 *
 * @param sinkIndex This is the proxy / combo table index for the new entry
 * @param entry This is a pointer to the sink table data to add. If 0
 *              the entry at the specified indexis set to unused.
 * @returns Return EMBER_INDEX_OUT_OF_RANGE if sinkIndex is bigger than the
 *                 table. If entry is set to 0 it returns
 *                 EMBER_GP_SINK_TABLE_ENTRY_STATUS_UNUSED, If entry is non zero
 *                 it returns EMBER_SUCCESS
 *
 * Detailed For a given index the entry in the Proxy / combo table is accessed
 *          If it is an illegal index it returns with EMBER_INDEX_OUT_OF_RANGE
 *          If the entry parameter is set to 0 the entry is set to
 *          EMBER_GP_SINK_TABLE_ENTRY_STATUS_UNUSED. Otherwise the entry is set
 *          to the value pointed at by entr and EMBER_SUCCESS returned.
 *****************************************************************************/
EmberStatus emberGpSinkTableSetEntry(uint8_t sinkTableIndex,
                                     EmberGpSinkTableEntry *entry);

/**************************************************************************//**
 * Brief get sink Table entry located @sinkIndex.
 *
 * @param sinkIndex This is the proxy / combo table index for the entry
 * @param entry This is a pointer to the buffer where the entry is to be copied
 * @returns Return EMBER_INDEX_OUT_OF_RANGE if sinkIndex is bigger than the
 *                 table. EMBER_NOT_FOUND If the entry at sinkIndex is not a
 *                 sink or EMBER_SUCCESS if the buffer is successfully copied
 *
 * Detailed This function copies the sink table entry for a given index into a
 *          buffer provided by the calling program if the specified entry is a
 *          sink table entry and returns EMBER_SUCCESS. Otherwise if sinkIndex
 *          is bigger than the table. EMBER_NOT_FOUND If the entry at sinkIndex
 *          is not a sink.
 *****************************************************************************/
EmberStatus emberGpSinkTableGetEntry(uint8_t sinkTableIndex,
                                     EmberGpSinkTableEntry *entry);

/******************************************************************************
 * Brief This function determines if an entry is currently an active sink entry
 *
 * @param index This is the index to an entry in the sink / combo table to
 *               evaluate
 * @returns Return 0xFF if the index is invalid or contains a proxy table entry
 *          If a sink table entry is present in in the index 0 (true) is
 *          returned else 1 (false) is returned
 *
 * Detailed This function searches for the address passed in and returns the
 *          index. If the address cannot be matched return 0xFF. If a sink
 *          table entry is present in in the index 0 (true) is returned
 *          else 1 (false) is returned
 *****************************************************************************/
uint8_t emberGpSinkTableEntryInUse(uint8_t sinkTableIndex);

/**************************************************************************//**
 * Brief This function returns the index of the first free table entry
 *
 * @returns Return the index of the unused sink/combo table entry or 0xFF if
 *                 no free entry exists.
 *
 * Detailed Return the index of the unused sink/combo table entry or 0xFF if
 *                 no free entry exists.
 *****************************************************************************/
uint8_t sli_zigbee_af_gp_sink_table_get_free_entry_index(void);

/******************************************************************************
 * Brief This function finds the sink table entry which matches to the address
 * of the GPD device supplied and if not found it creates a sink entry.
 *  .
 * @param addr This is a pointer to an  address block containing the address to
 *             match
 * @returns Return The index of a unused entry or one that contains the address
 *                 passed in. If the address cannot be matched and a free entry
 *                 cannot be found return 0xFF.
 *
 * Detailed This function searches for the address passed in and returns the
 *          index of a unused entry or one that contains the address passed in.
 *          If the address cannot be matched and a free entry cannot be found
 *          return 0xFF.
 *****************************************************************************/
uint8_t emberGpSinkTableFindOrAllocateEntry(EmberGpAddress *addr);

/******************************************************************************
 * Brief This function adds a sink group entry for a given index.
 *
 * @param index This is the proxy / combo table index for the entry
 * @param sinkGroupId This is the ID of the group to add to the sink list
 * @param assignedAlias this is the alias of the group to add.
 * @returns Nothing
 *
 * Detailed For a given index the entry in the Proxy / combo table is accessed
 *          If it is an illegal index or a proxy entry it returns with no
 *          action. If the groupId, alias pair alrready exists it returns
 *          with no action
 *          Otherwise the entry is added to an unused slot in the sink grouop
 *          list, and the entry then written to non volatile storage.
 *****************************************************************************/
void sli_zigbee_af_gp_sink_table_add_group(uint8_t index,
                                           uint16_t sinkGroupId,
                                           uint16_t alias);

/******************************************************************************
 * Brief This function removes a sink group entry for a given index.
 *
 * @param index This is the proxy / combo table index for the entry
 * @param sinkGroupId This is the ID of the group to remove from the sink list
 * @param assignedAlias this is the alias of the group to remove.
 * @returns true if the entry is removed else false if it cannot be found.
 *
 * Detailed For a given index the entry in the Proxy / combo table is accessed
 *          If it is an illegal index false is returned. If the groupId,
 *          alias pair cannot be found in the sink group list false is returned
 *          If it is found the sink group entry is set to unused and true
 *          returned.
 *****************************************************************************/
bool sli_zigbee_af_gp_sink_table_remove_group(uint8_t index,
                                              uint16_t sinkGroupId,
                                              uint16_t assignedAlias);

/******************************************************************************
 * Brief This function finds the sink table entry which matches to the address
 * of the GPD device supplied and if found returns the index of that entry
 *  .
 *
 * @param addr This is a pointer to an  address block containing the address to
 *             match
 * @returns Return The index of the entry that contains the address
 *                 passed in. If the address cannot be matched return 0xFF

 *
 * Detailed This function searches for the address passed in and returns the
 *          index. If the address cannot be matched return 0xFF
 *****************************************************************************/
uint8_t emberGpSinkTableLookup(EmberGpAddress *addr);

/**************************************************************************//**
 * Brief This function sets the sink table entry at the specified index to
 *       unused
 *
 * @param index This is the sink table index of the entry to be removed
 *
 * @returns Nothing.
 *
 * Detailed If index = 0xFF clear all.
            If the entry is a sink table entry this function sets its status to
 *          unused so that it can be used for other entries. If index is out
 *          of range it is ignored.
 *
 *
 *****************************************************************************/
void emberGpSinkTableRemoveEntry(uint8_t index);

/******************************************************************************
 * Brief This function sets the security framecounter in the Sink table
 *
 * @param index Index to the sink table
 * @param scf Security frame counter
 * Detailed This function sets the security framecounter in the security frame
 *          array for a given index.
 *****************************************************************************/
void emberGpSinkTableSetSecurityFrameCounter(uint8_t index,
                                             uint32_t sfc);

/******************************************************************************
 * Brief This function returns number of active entries in sink table.
 *
 * @returns number of active entries in sink table.
 *
 *****************************************************************************/
uint8_t emberGpSinkTableGetNumberOfActiveEntries(void);
#ifdef __cplusplus
}
#endif

#endif //GP_SINK_TABLE
