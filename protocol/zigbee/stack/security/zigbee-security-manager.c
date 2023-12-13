/***************************************************************************//**
 * @file
 * @brief Implementation of security-related APIs, including key storage, key
 *   fetching, and crypto operations. Keys are ultimately stored in Secure Vault
 *   for Vault-capable parts (like Series 2 chips) or in NVM3 tokens.
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

#include "stack/include/zigbee-security-manager.h"
#include "stack/security/zigbee-security-manager-internal.h"
#include "stack/include/security.h"
#include "stack/include/stack-info.h"
#include "stack/core/ember-multi-network.h"
#include "stack/include/ember-types-internal.h"
#include "hal.h" // for TOKEN_resolution
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

// Externs

extern bool sli_zigbee_get_trust_center_eui64(EmberEUI64 address);
extern EmberStatus sli_zigbee_get_transient_key_table_entry(uint8_t index, EmberTransientKeyData *transientKeyData);
extern EmberStatus sli_zigbee_get_key_table_entry(uint8_t index, EmberKeyStruct *result);
extern bool findTransientLinkKey(const EmberEUI64 eui64ToFind,
                                 EmberTransientKeyData *keyDataReturn,
                                 EmberKeyStructBitmask* bitmask);
extern void sli_zigbee_stack_token_primitive(bool tokenRead,
                                             void* tokenStruct,
                                             uint16_t tokenAddress,
                                             uint8_t length);
extern bool sli_zigbee_is_token_data_initialized(uint8_t* data, uint8_t length);
extern uint8_t sli_zigbee_find_key_table_entry(EmberEUI64 address, bool linkKey, uint8_t bitmask);
extern EmberStatus sli_zigbee_get_link_key(EmberEUI64 partner,
                                           EmberKeyData* key,
                                           sl_zb_sec_man_context_t* context,
                                           uint32_t **frameCounterLocLoc,
                                           uint8_t getKeyBitmask);
#define sli_zigbee_get_security_state(item) ((sli_zigbee_security_state_bitmask & (item)) == (item))
extern void sli_legacy_mfg_security_config_modify_key(EmberKeyData* key);

sl_status_t sl_zb_sec_man_import_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;

  if (context == NULL
      || plaintext_key == NULL
      || context->derived_type != SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE) {
    status = SL_STATUS_INVALID_PARAMETER;
    return status;
  }

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
      status = zb_sec_man_store_nwk_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      status = zb_sec_man_store_tc_link_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
      status = zb_sec_man_store_transient_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
      status = zb_sec_man_store_in_link_key_table(context, plaintext_key);
      break;
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
      status = zb_sec_man_store_zll_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
      status = zb_sec_man_store_gp_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      status = zb_sec_man_store_internal_key(context, plaintext_key);
      break;
    default:
      break;
  }

  return status;
}

sl_status_t sl_zb_sec_man_export_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;
  if (plaintext_key == NULL || context == NULL) {
    return status;
  }

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
      status = zb_sec_man_fetch_nwk_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      status = zb_sec_man_fetch_tc_link_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
      status = zb_sec_man_fetch_transient_key(context, plaintext_key);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
      status = zb_sec_man_fetch_from_link_key_table(context, plaintext_key);
      break;
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
      status = zb_sec_man_fetch_zll_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
      status = zb_sec_man_fetch_gp_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      status = zb_sec_man_fetch_internal_key(context, plaintext_key);
      break;
    default:
      break;
  }

  //Clear key data if read protection token instructs this.
  sli_legacy_mfg_security_config_modify_key((EmberKeyData*) plaintext_key);
  return status;
}

sl_status_t sl_zb_sec_man_import_link_key(uint8_t index,
                                          EmberEUI64 address,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);

  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  // Right now, a null address deletes the entry. This will be
  // eventually reworked
  if (address) {
    MEMMOVE(context.eui64, address, EUI64_SIZE);
  }
  context.key_index = index;

  status = sl_zb_sec_man_import_key(&context, plaintext_key);

  return status;
}

sl_status_t sl_zb_sec_man_export_link_key_by_index(uint8_t index,
                                                   sl_zb_sec_man_context_t* context,
                                                   sl_zb_sec_man_key_t* plaintext_key,
                                                   sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  sl_status_t status;

  sl_zb_sec_man_init_context(context);

  context->core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  context->key_index = index;
  context->flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

  status = sl_zb_sec_man_export_key(context, plaintext_key);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  status = sl_zb_sec_man_get_aps_key_info(context, key_data);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  return status;
}

sl_status_t sl_zb_sec_man_export_link_key_by_eui(EmberEUI64 eui,
                                                 sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key,
                                                 sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  sl_status_t status;

  sl_zb_sec_man_init_context(context);

  context->core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  if (eui != NULL) {
    MEMMOVE(context->eui64, eui, EUI64_SIZE);
  }
  context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;

  if (plaintext_key == NULL) {
    //For callers who want this to return a key's index but not its actual value
    context->key_index = sli_zigbee_find_key_table_entry(eui, true, 0);
    status = (context->key_index != 0xFF) ? SL_STATUS_OK : SL_STATUS_NOT_FOUND;
  } else {
    status = sl_zb_sec_man_export_key(context, plaintext_key);
  }

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }
  context->flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

  if (eui != NULL && key_data != NULL) {
    //populate key_data if we did find a link key for this EUI
    (void) sl_zb_sec_man_get_aps_key_info(context, key_data);
  }

  return status;
}

sl_status_t sl_zb_sec_man_get_aps_key_info(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  sl_status_t status = SL_STATUS_INVALID_TYPE;

  MEMSET(key_data, 0, sizeof(*key_data));

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      status = zb_sec_man_fetch_tc_link_key_info(context, key_data);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
      status = zb_sec_man_fetch_transient_key_info(context, key_data);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
      status = zb_sec_man_fetch_link_key_table_key_info(context, key_data);
      break;
    default:
      break;
  }

  return status;
}

sl_status_t zb_sec_man_import_transient_key(EmberEUI64 eui64,
                                            sl_zb_sec_man_key_t* plaintext_key,
                                            sl_zigbee_sec_man_flags_t flags)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);

  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT;
  context.flags = flags;
  MEMMOVE(context.eui64, eui64, EUI64_SIZE);

  status = sl_zb_sec_man_import_key(&context, plaintext_key);

  return status;
}

sl_status_t sl_zb_sec_man_export_transient_key_by_eui(EmberEUI64 eui,
                                                      sl_zb_sec_man_context_t* context,
                                                      sl_zb_sec_man_key_t* plaintext_key,
                                                      sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  sl_status_t status;

  sl_zb_sec_man_init_context(context);

  context->core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT;
  MEMMOVE(context->eui64, eui, EUI64_SIZE);
  context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;

  status = sl_zb_sec_man_export_key(context, plaintext_key);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  status = sl_zb_sec_man_get_aps_key_info(context, key_data);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  return status;
}

sl_status_t sl_zb_sec_man_export_transient_key_by_index(uint8_t index,
                                                        sl_zb_sec_man_context_t* context,
                                                        sl_zb_sec_man_key_t* plaintext_key,
                                                        sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  sl_status_t status;

  sl_zb_sec_man_init_context(context);

  context->core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT;
  context->key_index = index;
  context->flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

  status = sl_zb_sec_man_export_key(context, plaintext_key);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  status = sl_zb_sec_man_get_aps_key_info(context, key_data);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  return status;
}

sl_status_t sli_zigbee_sec_man_export_derived_key(sl_zb_sec_man_context_t* context,
                                                  sl_zb_sec_man_key_t* derived_key)
{
  sl_zb_sec_man_key_t plaintext_key;
  sl_status_t status = sl_zb_sec_man_export_key(context, &plaintext_key);
  if (status != SL_STATUS_OK) {
    return status;
  }
  status = zb_sec_man_derive_key(&plaintext_key, context, derived_key);
  return status;
}

void zb_sec_man_set_network_key_info(sl_zb_sec_man_network_key_info_t* network_key_info)
{
  tokTypeStackKeys tok;

  sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  if (tok.activeKeySeqNum != network_key_info->network_key_sequence_number) {
    tok.activeKeySeqNum = network_key_info->network_key_sequence_number;
    sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  }

  sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  if (tok.activeKeySeqNum != network_key_info->alt_network_key_sequence_number) {
    tok.activeKeySeqNum = network_key_info->alt_network_key_sequence_number;
    sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  }
}

sl_status_t zb_sec_man_fetch_tc_link_key_info(sl_zb_sec_man_context_t* context,
                                              sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  EmberCurrentSecurityState securityState;
  EmberStatus status = emberGetCurrentSecurityState(&securityState);

  if ((status != EMBER_SUCCESS)
      || (!(securityState.bitmask & EMBER_HAVE_TRUST_CENTER_LINK_KEY_TOKEN))) {
    return SL_STATUS_INVALID_MODE;
  }

  MEMSET(key_data, 0, sizeof(*key_data));

  EmberEUI64 tcAddress;
  if (sli_zigbee_get_trust_center_eui64(tcAddress)) {
    if ((context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID)
        && (0 != MEMCOMPARE(context->eui64, tcAddress, EUI64_SIZE))) {
      return SL_STATUS_NOT_FOUND;
    }
    MEMMOVE(context->eui64, tcAddress, EUI64_SIZE);
    context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
    key_data->bitmask |= EMBER_KEY_HAS_PARTNER_EUI64;
  }

  key_data->bitmask |= EMBER_KEY_HAS_OUTGOING_FRAME_COUNTER;
  key_data->outgoing_frame_counter = emberGetApsFrameCounter();

  if (emberGetNodeId() != 0x0000) {
    key_data->incoming_frame_counter = sli_zigbee_incoming_tc_link_key_frame_counter;
    key_data->bitmask |= EMBER_KEY_HAS_INCOMING_FRAME_COUNTER;
  }

  if (!sli_zigbee_get_security_state(KEY_IS_NOT_AUTHORIZED) ) {
    key_data->bitmask |= EMBER_KEY_IS_AUTHORIZED;
  }

  if (sli_zigbee_get_security_state(EMBER_TC_SUPPORTS_FC_SYNC)) {
    key_data->bitmask |= EMBER_KEY_FC_SYNC_SUPPORTED;
  }

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_transient_key_info(sl_zb_sec_man_context_t* context,
                                                sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberTransientKeyData transientKeyData;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = sli_zigbee_get_transient_key_table_entry(context->key_index, &transientKeyData);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    // sl_zb_sec_man_export_transient_key_by_eui is called when using the original transient and not the
    // unconfirmed transient key. Hence initializing the bitmask to 0.
    EmberKeyStructBitmask bitmask = 0;
    bool found = findTransientLinkKey(context->eui64, &transientKeyData, &bitmask);
    status = found ? EMBER_SUCCESS : EMBER_NOT_FOUND;
  }

  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }

  MEMSET(key_data, 0, sizeof(*key_data));

  key_data->bitmask = transientKeyData.bitmask;
  key_data->incoming_frame_counter = transientKeyData.incomingFrameCounter;
  key_data->ttl_in_seconds = transientKeyData.remainingTimeSeconds;

  context->multi_network_index = transientKeyData.networkIndex;
  MEMMOVE(context->eui64, transientKeyData.eui64, sizeof(EmberEUI64));

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_link_key_table_key_info(sl_zb_sec_man_context_t* context,
                                                     sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberKeyStruct result;
  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = sli_zigbee_get_key_table_entry(context->key_index, &result);
  }
  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }
  MEMMOVE(context->eui64, result.partnerEUI64, EUI64_SIZE);
  context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
  MEMSET(key_data, 0, sizeof(*key_data));
  key_data->bitmask = result.bitmask;
  key_data->incoming_frame_counter = result.incomingFrameCounter;
  key_data->bitmask |= EMBER_KEY_HAS_INCOMING_FRAME_COUNTER;
  key_data->outgoing_frame_counter = result.outgoingFrameCounter;

  return SL_STATUS_OK;
}

uint8_t zb_sec_man_version(void)
{
  return ZB_SEC_MAN_VERSION;
}

/// NOTE authentication token is only required for ZigBee Revision 23 and greater

// Symmetric Passphrase Functions

// NOTE auth token is in key table entry
// NOTE copied from aps-keys-full.h
// This bit indicates if entry in the key table is a Symmetric Passphrase
#define KEY_TABLE_SYMMETRIC_PASSPHRASE      (BIT(7))

uint8_t sl_zb_sec_man_find_symmetric_passphrase_key_table_index(EmberEUI64 address)
{
  // Look for the entry in the key table for the non-null address
  if (address != NULL) {
    return sli_zigbee_find_key_table_entry(address, true, KEY_TABLE_SYMMETRIC_PASSPHRASE);
  }
  return 0xFF;
}

sl_status_t sl_zb_sec_man_import_symmetric_passphrase(uint8_t index,
                                                      EmberEUI64 address,
                                                      EmberKeyData* key_data)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);

  MEMCOPY(&context.eui64, address, sizeof(EmberEUI64));
  // NOTE APP_LINK key type is a little misleading, as the symmetric
  // passphrase is technically not a link key, however this key type
  // corresponds to the correct storage type for the symmetric passphrase
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  context.key_index = index;

  context.flags |= ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE;
  status = sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *) key_data);

  return status;
}

sl_status_t sl_zb_sec_man_update_symmetric_passphrase_eui(EmberEUI64 old_eui64, EmberEUI64 new_eui64)
{
  uint8_t index = sl_zb_sec_man_find_symmetric_passphrase_key_table_index(old_eui64);
  if (index == 0xFF) {
    return SL_STATUS_NOT_FOUND;
  }
  tokTypeStackKeyTable tok;
  halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, index);
  MEMMOVE(&(tok[KEY_ENTRY_IEEE_OFFSET]),
          new_eui64,
          EUI64_SIZE);
  halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, index, (void*)&tok);
  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_export_symmetric_passphrase(EmberEUI64 address,
                                                      EmberKeyData* key_data)
{
  uint8_t index = sl_zb_sec_man_find_symmetric_passphrase_key_table_index(address);
  if (index == 0xFF) {
    return SL_STATUS_FAIL;
  }

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_aps_key_metadata_t metadata;

  return sl_zb_sec_man_export_link_key_by_index(index, &context, (sl_zb_sec_man_key_t *) key_data, &metadata);
}

bool sl_zb_sec_man_have_link_key(EmberEUI64 eui)
{
  // Since we are simply checking for the existence of a key,
  // we don't care if it is authorized or not.
  return (EMBER_SUCCESS
          == sli_zigbee_get_link_key(eui,
                                     NULL, // key return data
                                     NULL, // context return data
                                     NULL, // frame counter location
                                     0)); // key is not transient, and does not need to be authorized
}

bool sl_zigbee_sec_man_link_key_slot_available(EmberEUI64 eui64)
{
  sl_zb_sec_man_context_t context_existing;
  sl_zb_sec_man_context_t context_open;
  sl_zb_sec_man_export_link_key_by_eui(eui64, &context_existing, NULL, NULL);
  sl_zb_sec_man_export_link_key_by_eui(NULL, &context_open, NULL, NULL);
  if (0xFF != context_existing.key_index
      || 0xFF != context_open.key_index) {
    return true;
  }
  return false;
}
