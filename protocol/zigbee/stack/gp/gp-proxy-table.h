/***************************************************************************//**
 * @file
 * @brief Zigbee GP token definitions used by the stack.
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

//these are declared in the config/ember-configuration.c
extern uint8_t sli_zigbee_gp_proxy_table_size;
extern EmberGpProxyTableEntry sli_zigbee_gp_proxy_table[];

extern uint8_t sli_zigbee_gp_incoming_fc_token_table_size;
extern uint8_t sli_zigbee_gp_incoming_fc_token_timeout;

//#define EMBER_GP_PROXY_TABLE_ENTRY_STATUS_MASK 0x01

uint8_t sli_zigbee_gp_proxy_table_entry_in_use(uint8_t index);
void sli_zigbee_gp_clear_proxy_table(void);

//the follwoing gets called every sec and may be(?) every time a proxy table entry token is re-written
void sli_zigbee_gp_write_incoming_fc_to_token(uint8_t index);

/*
 #define sli_zigbee_gp_proxy_table_entry_in_use(index)                                  \
   ((sli_zigbee_gp_proxy_table[(index)].status                                          \
    & EMBER_GP_PROXY_TABLE_ENTRY_STATUS_MASK)                        \
    == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_ACTIVE)
 */

#define sli_zigbee_gp_proxy_table_entry_unused(index) \
  (sli_zigbee_gp_proxy_table[(index)].status          \
   == EMBER_GP_PROXY_TABLE_ENTRY_STATUS_UNUSED)

#define  sli_zigbee_gp_proxy_table_get_addr(index) \
  (&(sli_zigbee_gp_proxy_table[(index)].gpd))

#define sli_zigbee_gp_proxy_table_set_security_frame_counter(index, sfc) \
  (sli_zigbee_gp_proxy_table[(index)].gpdSecurityFrameCounter = (sfc))

#define sli_zigbee_gp_proxy_table_get_security_frame_counter(index) \
  (sli_zigbee_gp_proxy_table[(index)].gpdSecurityFrameCounter)

#define sli_zigbee_gp_proxy_table_get_options(index) \
  (sli_zigbee_gp_proxy_table[(index)].options)

#define sli_zigbee_gp_proxy_table_set_options(index, o) \
  (sli_zigbee_gp_proxy_table[(index)].options = (o))

#define sli_zigbee_gp_proxy_table_has_security(index)                                                \
  ((sli_zigbee_gp_proxy_table[(index)].options & EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_SECURITY_USE) \
   || (sli_zigbee_gp_proxy_table[(index)].securityOptions))

#define sli_zigbee_gp_proxy_table_get_security_options(index) \
  (sli_zigbee_gp_proxy_table[(index)].securityOptions)

#define sli_zigbee_gp_proxy_table_set_security_options(index, o) \
  (sli_zigbee_gp_proxy_table[(index)].securityOptions = (o))

#define sli_zigbee_gp_proxy_table_get_sink_list(index) \
  (sli_zigbee_gp_proxy_table[(index)].sinkList)

#define sli_zigbee_gp_proxy_table_entry_has_link_key(index) \
  (((sli_zigbee_gp_proxy_table[(index)].securityOptions) & 0x1C))

#define sli_zigbee_gp_proxy_table_get_security_key(index) \
  (sli_zigbee_gp_proxy_table[(index)].gpdKey)

#define sli_zigbee_gp_proxy_table_set_status(index, s) \
  (sli_zigbee_gp_proxy_table[(index)].status = (s))

#define sli_zigbee_gp_proxy_table_get_status(index) \
  (sli_zigbee_gp_proxy_table[(index)].status)

#define sli_zigbee_gp_proxy_table_get_assigned_alias(index) \
  (sli_zigbee_gp_proxy_table[(index)].assignedAlias)

#define sli_zigbee_gp_proxy_table_get_groupcast_radius(index) \
  (sli_zigbee_gp_proxy_table[(index)].groupcastRadius)

#define sli_zigbee_gp_proxy_table_set_in_range(index) \
  (sli_zigbee_gp_proxy_table[(index)].options |= GP_PROXY_TABLE_OPTIONS_IN_RANGE)
#define sli_zigbee_gp_proxy_table_clear_in_range(index) \
  (sli_zigbee_gp_proxy_table[(index)].options &= (~GP_PROXY_TABLE_OPTIONS_IN_RANGE))

#define sli_zigbee_gp_proxy_table_set_first_to_forward(index) \
  (sli_zigbee_gp_proxy_table[(index)].options |= EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_FIRST_TO_FORWARD)
#define sli_zigbee_gp_proxy_table_clear_first_to_forward(index) \
  (sli_zigbee_gp_proxy_table[(index)].options &= (~EMBER_AF_GP_PROXY_TABLE_ENTRY_OPTIONS_FIRST_TO_FORWARD))

void sli_zigbee_af_gp_proxy_table_init(void);
EmberStatus sli_zigbee_af_gp_proxy_table_set_entry(uint8_t proxyIndex,
                                                   EmberGpProxyTableEntry *entry);
uint8_t sli_zigbee_af_gp_proxy_table_get_free_entry_index(void);
uint8_t sli_zigbee_af_gp_proxy_table_find_or_allocate_entry(EmberGpAddress *addr);
//void sli_zigbee_af_gp_proxy_table_add_sink(uint8_t index,uint16_t options,EmberEUI64 sinkIeeeAddress,EmberNodeId sinkNwkAddress,uint16_t sinkGroupId,uint32_t gpdSecurityFrameCounter,uint8_t *gpdKey,uint16_t assignedAlias,uint8_t forwardingRadius);
void sli_zigbee_af_gp_proxy_table_add_sink(uint8_t index,
                                           //      uint16_t options,
                                           uint8_t commMode,
                                           EmberEUI64 sinkIeeeAddress,
                                           EmberNodeId sinkNwkAddress,
                                           uint16_t sinkGroupId,
//                           uint32_t gpdSecurityFrameCounter,
//                          uint8_t *gpdKey,
                                           uint16_t assignedAlias
                                           //                        uint8_t forwardingRadius)
                                           );
void sli_zigbee_af_gp_proxy_table_remove_sink(uint8_t index, EmberEUI64 sinkIeeeAddress, uint16_t sinkGroupId, uint16_t assignedAlias);
void sli_zigbee_af_gp_proxy_table_remove_entry(uint8_t index);
void sli_zigbee_af_gp_proxy_table_set_key(uint8_t index, uint8_t * gpdKey, EmberGpKeyType securityKeyType);
void sli_zigbee_af_gp_proxy_table_get_key(uint8_t index, EmberKeyData *key);
bool sli_zigbee_af_gp_address_match(const EmberGpAddress *a1, const EmberGpAddress *a2);

/** @brief Get Proxy table entry
 *
 * This function gets an entry from proxy table at the supplied index.
 *
 * @param proxyIndex a valid index to proxy table.
 * @param entry proxy table entry
 *
 * @return An ::EmberStatus as status.
 */
EmberStatus emberGpProxyTableGetEntry(uint8_t proxyIndex,
                                      EmberGpProxyTableEntry *entry);

/** @brief Proxy table look up
 *
 * This function looks up a gpd address in the Gp Proxy Table and returns index of the entry.
 *
 * @param addr The gpd address ::EmberGpAddress to look up.
 *
 * @return a valid index to the entry in proxy table and 0xFF in case of not found.
 */
uint8_t emberGpProxyTableLookup(EmberGpAddress *addr);

/** @brief Process Gp Pairing
 *
 * This function adds or updates the entry in the proxy table as part of Gp Pairing command processing.
 * All the input arguments for this API is derived directly from the incoming GP Pairing command
 *
 * @param options option field of the Gp Pairing command, this holds the validity of other inputs.
 * @param addr The gpd address ::EmberGpAddress.
 * @param commMode Communication mode as supplied in the Gp Pairing command.
 * @param sinkNwkAddress Network address of the sink.
 * @param sinkGroupId Group Id of the sink.
 * @param assignedAlias Assigned alias for the GPD under commissioning.
 * @param sinkIeeeAddress sink EUI64 address
 * @param gpdKey GPD key
 * @param gpdSecurityFrameCounter security frame counter from GPD.
 * @param forwardingRadius forwarding radius
 *
 * @return true on success and false for failure.
 */
bool emberGpProxyTableProcessGpPairing(uint32_t options,
                                       EmberGpAddress* addr,
                                       uint8_t commMode,
                                       uint16_t sinkNwkAddress,
                                       uint16_t sinkGroupId,
                                       uint16_t assignedAlias,
                                       uint8_t* sinkIeeeAddress,
                                       EmberKeyData *gpdKey,
                                       uint32_t gpdSecurityFrameCounter,
                                       uint8_t forwardingRadius);

void sli_zigbee_af_clear_gp_tx_queue(void);
