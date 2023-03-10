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

#ifdef UC_BUILD
#include "sl_component_catalog.h"
#endif // UC_BUILD

// Externs
extern bool emGetTrustCenterEui64(EmberEUI64 address);
extern EmberStatus emGetTransientKeyTableEntry(uint8_t index, EmberTransientKeyData *transientKeyData);
extern EmberStatus emGetKeyTableEntry(uint8_t index, EmberKeyStruct *result);
extern bool findTransientLinkKey(const EmberEUI64 eui64ToFind,
                                 EmberTransientKeyData *keyDataReturn,
                                 EmberKeyStructBitmask* bitmask);
extern void emStackTokenPrimitive(bool tokenRead,
                                  void* tokenStruct,
                                  uint16_t tokenAddress,
                                  uint8_t length);

void sl_zb_sec_man_init_context(sl_zb_sec_man_context_t* context)
{
  MEMSET(context, 0, sizeof(*context));
}

sl_status_t sl_zb_sec_man_import_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;

  if (context->derived_type != SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE) {
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
#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY:
      status = zb_sec_man_store_secure_ezsp_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
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
#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY:
      status = zb_sec_man_fetch_secure_ezsp_key(context, plaintext_key);
      break;
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
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

  status = sl_zb_sec_man_export_key(context, plaintext_key);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
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

void zb_sec_man_set_network_key_info(sl_zb_sec_man_network_key_info_t* network_key_info)
{
  tokTypeStackKeys tok;

  emStackTokenPrimitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  if (tok.activeKeySeqNum != network_key_info->network_key_sequence_number) {
    tok.activeKeySeqNum = network_key_info->network_key_sequence_number;
    emStackTokenPrimitive(false, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  }

  emStackTokenPrimitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  if (tok.activeKeySeqNum != network_key_info->alt_network_key_sequence_number) {
    tok.activeKeySeqNum = network_key_info->alt_network_key_sequence_number;
    emStackTokenPrimitive(false, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
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

  EmberEUI64 tcAddress;
  if (emGetTrustCenterEui64(tcAddress)) {
    if ((context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID)
        && (0 != MEMCOMPARE(context->eui64, tcAddress, EUI64_SIZE))) {
      return SL_STATUS_NOT_FOUND;
    }
    MEMMOVE(context->eui64, tcAddress, EUI64_SIZE);
    context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
  }

  MEMSET(key_data, 0, sizeof(*key_data));

  key_data->bitmask |= EMBER_KEY_HAS_OUTGOING_FRAME_COUNTER;
  key_data->outgoing_frame_counter = emberGetApsFrameCounter();

  if (emberGetNodeId() != 0x0000) {
    key_data->incoming_frame_counter = emIncomingTcLinkKeyFrameCounter;
    key_data->bitmask |= EMBER_KEY_HAS_INCOMING_FRAME_COUNTER;
  }

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_transient_key_info(sl_zb_sec_man_context_t* context,
                                                sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberTransientKeyData transientKeyData;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = emGetTransientKeyTableEntry(context->key_index, &transientKeyData);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    // emberGetTransientLinkKey is called when using the original transient and not the
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

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_link_key_table_key_info(sl_zb_sec_man_context_t* context,
                                                     sl_zb_sec_man_aps_key_metadata_t* key_data)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberKeyStruct result;
  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = emGetKeyTableEntry(context->key_index, &result);
  }
  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }
  MEMSET(key_data, 0, sizeof(*key_data));
  key_data->bitmask = result.bitmask;
  key_data->incoming_frame_counter = result.incomingFrameCounter;
  key_data->outgoing_frame_counter = result.outgoingFrameCounter;

  return SL_STATUS_OK;
}

//Defined here to support code that still calls this; sl_zb_sec_man_hmac_aes_mmo
//is designed to replace it.
void emberHmacAesHash(const uint8_t *key,
                      const uint8_t *data,
                      uint8_t dataLength,
                      uint8_t *result)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  (void) sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)key);
  (void) sl_zb_sec_man_load_key_context(&context);
  sl_zb_sec_man_hmac_aes_mmo(data, dataLength, result);
}
