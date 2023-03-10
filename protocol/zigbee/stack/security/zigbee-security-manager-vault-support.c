/***************************************************************************//**
 * @file
 * @brief Implementation of security-related APIs, including key storage, key
 *   fetching, and crypto operations. In this file, keys are stored in Vault.
 *   This file is only compiled for parts with Vault support.
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
#include "sl_status.h"
#include "stack/config/token-stack.h"
#include "zigbee-security-manager-vault-support.h"
#include "security_manager.h"
#include "hal.h"

// Externs
extern bool emIsNullKey(EmberKeyData * key);
extern void emStackTokenPrimitive(bool tokenRead,
                                  void* tokenStruct,
                                  uint16_t tokenAddress,
                                  uint8_t length);
extern bool emGetTrustCenterEui64(EmberEUI64 address);
extern EmberNodeId emberGetNodeId(void);
extern EmberStatus emAddTransientLinkKey(const EmberKeyStruct* keyStruct);
extern EmberStatus emGetTransientKeyTableEntry(uint8_t index, EmberTransientKeyData *transientKeyData);
extern bool findTransientLinkKey(const EmberEUI64 eui64ToFind,
                                 EmberTransientKeyData *keyDataReturn,
                                 EmberKeyStructBitmask* bitmask);
extern bool removeTransientLinkKey(const EmberEUI64 eui64ToFind,
                                   EmberKeyStructBitmask* bitmask);
sl_status_t find_transient_key(sl_zb_sec_man_context_t* context,
                               EmberTransientKeyData* transientKey);
sl_status_t find_link_key_table_key(sl_zb_sec_man_context_t* context);
extern EmberStatus emSetKeyTableEntry(bool erase,
                                      uint8_t index,
                                      EmberKeyStruct* keyStruct);
extern EmberStatus emGetKeyTableEntry(uint8_t index, EmberKeyStruct *result);
extern void emMfgSecurityConfigModifyKey(EmberKeyData* key);
extern uint8_t emFindKeyTableEntry(EmberEUI64 address, bool linkKey);
extern bool emMemoryByteCompare(const uint8_t *bytes, uint8_t count, uint8_t target);

// Globals
static psa_key_id_t zb_sm_context_psa_key_id;
static psa_key_id_t zb_sec_man_internal_key_psa_id;
static psa_key_id_t zb_sec_man_derived_key_psa_id = 0;

static bool zb_sec_is_key_present(uint32_t key_id);

// Eventually pull this from aps-keys-full.h
#define KEY_TABLE_ENTRY_HAS_PSA_ID          (BIT(6))

void emSecurityHardwareInit(void)
{
}

sl_status_t sl_zb_sec_man_delete_key(sl_zb_sec_man_context_t* context)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;

  psa_key_id_t key_id = 0;
  bool key_handled = false;

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
      key_id = (context->key_index == 0) ? ZB_PSA_KEY_ID_ACTIVE_NWK_KEY : ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
      status = sl_zb_sec_man_delete_transient_key(context);
      key_handled = true;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
      status = sl_zb_sec_man_delete_key_table_key(context);
      key_handled = true;
      break;
#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY:
      key_id = ZB_PSA_KEY_ID_SECURE_EZSP_KEY;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
      key_id = ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
      key_id = ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
      key_id = ZB_PSA_KEY_ID_GP_PROXY_TABLE_START + context->key_index;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
      key_id = ZB_PSA_KEY_ID_GP_SINK_TABLE_START + context->key_index;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      key_id = zb_sec_man_internal_key_psa_id;
      break;
    default:
      break;
  }

  if (!key_handled) {
    status = (sl_sec_man_destroy_key(key_id) == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
  }

  return status;
}

sl_status_t sl_zb_sec_man_load_key_context(sl_zb_sec_man_context_t* context)
{
  sl_status_t status = SL_STATUS_OK;

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
      zb_sm_context_psa_key_id = (context->key_index == 0) ? ZB_PSA_KEY_ID_ACTIVE_NWK_KEY : ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
    {
      EmberTransientKeyData transientKey;
      status = find_transient_key(context, &transientKey);
      if (status == SL_STATUS_OK) {
        zb_sm_context_psa_key_id = transientKey.psa_id;
      }
    }
    break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
    {
      status = find_link_key_table_key(context);
      if (status == SL_STATUS_OK) {
        zb_sm_context_psa_key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;
      }
    }
    break;
#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_SECURE_EZSP_KEY;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_GP_PROXY_TABLE_START + context->key_index;
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
      zb_sm_context_psa_key_id = ZB_PSA_KEY_ID_GP_SINK_TABLE_START + context->key_index;
      break;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      zb_sm_context_psa_key_id = zb_sec_man_internal_key_psa_id;
      break;
    default:
      return SL_STATUS_INVALID_TYPE;
  }

  if (status != SL_STATUS_OK || zb_sm_context_psa_key_id == 0) {
    return SL_STATUS_NOT_FOUND;
  }

  bool is_key_in_psa = zb_sec_is_key_present(zb_sm_context_psa_key_id);

  if (!is_key_in_psa) {
    return SL_STATUS_NOT_FOUND;
  }

  if (context->derived_type != SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE) {
    sl_zb_sec_man_key_t source_key;
    sl_zb_sec_man_key_t derived_key;
    sl_zb_sec_man_export_key(context, &source_key);
    zb_sec_man_derive_key(&source_key, context, &derived_key);
    if (zb_sec_man_derived_key_psa_id != 0) {
      (void) sl_sec_man_destroy_key(zb_sec_man_derived_key_psa_id);
    }
    //import derived key like an internal/volatile key here, but call
    //separately so we don't write the derived key's ID to the internal key's.
    sl_sec_man_status_t sec_man_status;

    sec_man_status = sl_sec_man_import_key(&zb_sec_man_derived_key_psa_id,
                                           ZB_PSA_KEY_TYPE,
                                           ZB_PSA_ALG,
                                           ZB_PSA_KEY_USAGE,
                                           PSA_KEY_LIFETIME_VOLATILE,
                                           (const uint8_t*)&derived_key.key,
                                           EMBER_ENCRYPTION_KEY_SIZE);

    // Use this derived key for crypto operations
    zb_sm_context_psa_key_id = zb_sec_man_derived_key_psa_id;

    status = (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
  }

  return status;
}

sl_status_t zb_sec_man_derive_key(sl_zb_sec_man_key_t* source_key,
                                  const sl_zb_sec_man_context_t* context,
                                  sl_zb_sec_man_key_t* derived_key)
{
  uint8_t tag;

  //source_key is used as the key for hashing;
  //When loading a key context that includes a derived key,
  //callers must set the core key type correctly to ensure that
  //key derivation is done correctly.

  switch (context->derived_type) {
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_TRANSPORT_KEY:
    {
      tag = DERIVE_TRANSPORT_KEY_TAG;
      sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*)derived_key);
      break;
    }
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_LOAD_KEY:
    {
      tag = DERIVE_LOAD_KEY_TAG;
      sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*) derived_key);
      break;
    }
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_VERIFY_KEY:
    {
      tag = DERIVE_VERIFY_KEY_TAG;
      sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*) derived_key);
      break;
    }
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_SWAP_OUT_KEY:
    {
      emberAesHashSimple(EMBER_ENCRYPTION_KEY_SIZE,
                         (const uint8_t*) source_key,
                         (uint8_t* ) derived_key);
      break;
    }
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_HASHED_LINK_KEY:
      sl_zb_sec_man_hmac_aes_mmo(context->eui64, EUI64_SIZE, (uint8_t*) derived_key);
      break;
    default:
      return SL_STATUS_INVALID_PARAMETER;
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_delete_key_by_psa_id(uint32_t psa_id)
{
  sl_sec_man_status_t sec_man_status = sl_sec_man_destroy_key(psa_id);

  return (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  sl_sec_man_status_t status = SL_STATUS_NOT_SUPPORTED;
  uint32_t key_id;
  if (context->key_index == 0 ) {
    key_id = ZB_PSA_KEY_ID_ACTIVE_NWK_KEY;
  } else {
    key_id = ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY;
  }
  (void)sl_sec_man_destroy_key(key_id);
  status = sl_sec_man_import_key(&key_id, ZB_PSA_KEY_TYPE, ZB_PSA_ALG,
                                 ZB_PSA_KEY_USAGE,
                                 PSA_KEY_PERSISTENCE_DEFAULT, plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);

  return status;
}

sl_status_t zb_sec_man_fetch_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id;
  if (context->key_index == 0 ) {
    key_id = ZB_PSA_KEY_ID_ACTIVE_NWK_KEY;
  } else {
    key_id = ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY;
  }
  size_t    sl_psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  (void)sl_sec_man_export_key(key_id, plaintext_key->key,
                              EMBER_ENCRYPTION_KEY_SIZE,
                              &sl_psa_key_len);
  return SL_STATUS_OK;
}

static bool zb_sec_is_key_present(uint32_t key_id)
{
  sl_zb_sec_man_key_t plaintext_key;
  size_t    sl_psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  sl_sec_man_status_t sec_man_status = sl_sec_man_export_key(key_id,
                                                             plaintext_key.key,
                                                             EMBER_ENCRYPTION_KEY_SIZE,
                                                             &sl_psa_key_len);
  return ((sec_man_status == SL_SECURITY_MAN_SUCCESS) && !emIsNullKey((EmberKeyData * )plaintext_key.key)) ? true : false;
}

sl_status_t sl_zb_sec_man_get_network_key_info(sl_zb_sec_man_network_key_info_t * network_key_info)
{
  tokTypeStackKeys tok;
  //Fetch Alternate nwk key info
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  network_key_info->alt_network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->alternate_network_key_set = zb_sec_is_key_present(ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY);
  //Fetch nwk key info
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  network_key_info->network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->network_key_set = zb_sec_is_key_present(ZB_PSA_KEY_ID_ACTIVE_NWK_KEY);
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t * plaintext_key)
{
  uint32_t key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
  (void) sl_sec_man_destroy_key(key_id);
  sl_sec_man_status_t sec_man_status;
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         ZB_PSA_ALG,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_PERSISTENCE_DEFAULT,
                                         (const uint8_t *)plaintext_key->key,
                                         sizeof(plaintext_key->key));
  if (sec_man_status != SL_SECURITY_MAN_SUCCESS) {
    return SL_STATUS_FAIL;
  }

  // Write a bit in the token to tell the upgrade code that this token already
  // points to a PSA ID
  tokTypeStackTrustCenter tok;
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  if ((tok.mode & TRUST_CENTER_KEY_LIVES_IN_PSA) == 0) {
    tok.mode |= TRUST_CENTER_KEY_LIVES_IN_PSA;
    emStackTokenPrimitive(false, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  }

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
  EmberEUI64 tcAddress;
  if (emberGetNodeId() != 0x0000
      && emGetTrustCenterEui64(tcAddress)) {
    if ((context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID)
        && (0 != MEMCOMPARE(context->eui64, tcAddress, EUI64_SIZE))) {
      return SL_STATUS_NOT_FOUND;
    }
    MEMMOVE(context->eui64, tcAddress, EUI64_SIZE);
    context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
  }
  sl_sec_man_status_t sec_man_status;
  size_t returned_key_len;
  sec_man_status = sl_sec_man_export_key(key_id,
                                         (uint8_t*) plaintext_key,
                                         EMBER_ENCRYPTION_KEY_SIZE,
                                         &returned_key_len);
  if (sec_man_status != SL_SECURITY_MAN_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }
  return SL_STATUS_OK;
}

#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
sl_status_t zb_sec_man_fetch_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY) {
    key_id = ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY;
  } else {
    key_id = ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY;
  }
  size_t    sl_psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  (void)sl_sec_man_export_key(key_id, plaintext_key->key,
                              EMBER_ENCRYPTION_KEY_SIZE,
                              &sl_psa_key_len);
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  sl_sec_man_status_t status = SL_STATUS_NOT_SUPPORTED;
  uint32_t key_id;
  tokTypeStackZllSecurity zllSecurityToken;
  halCommonGetToken(&zllSecurityToken, TOKEN_STACK_ZLL_SECURITY);
  zllSecurityToken.bitmask |= EMBER_ZLL_TOKEN_POINTS_TO_PSA_ID;

  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY) {
    key_id = ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY;
    emberStoreHighLowInt32u(zllSecurityToken.encryptionKey, key_id);
  } else {
    key_id = ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY;
    emberStoreHighLowInt32u(zllSecurityToken.preconfiguredKey, key_id);
  }
  (void)sl_sec_man_destroy_key(key_id);
  status = sl_sec_man_import_key(&key_id, ZB_PSA_KEY_TYPE, ZB_PSA_ALG,
                                 ZB_PSA_KEY_USAGE,
                                 PSA_KEY_PERSISTENCE_DEFAULT,
                                 plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);

  if (status == SL_STATUS_OK) {
    halCommonSetToken(TOKEN_STACK_ZLL_SECURITY, &zllSecurityToken);
  }
  return status;
}
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)

#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
sl_status_t zb_sec_man_fetch_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY) {
    key_id = ZB_PSA_KEY_ID_GP_PROXY_TABLE_START + context->key_index;
  } else if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY) {
    key_id = ZB_PSA_KEY_ID_GP_SINK_TABLE_START + context->key_index;
  } else {
    // NOTE unreachable - callers must set core_key_type to valid 'gp' type
    return SL_STATUS_INVALID_TYPE;
  }
  size_t psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  sl_sec_man_status_t sec_status = sl_sec_man_export_key(
    key_id, plaintext_key->key,
    EMBER_ENCRYPTION_KEY_SIZE,
    // NOTE unused...
    &psa_key_len
    );
  return sec_status == SL_SECURITY_MAN_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY) {
    key_id = ZB_PSA_KEY_ID_GP_PROXY_TABLE_START + context->key_index;
  } else if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY) {
    key_id = ZB_PSA_KEY_ID_GP_SINK_TABLE_START + context->key_index;
  } else {
    // NOTE unreachable - callers must set core_key_type to valid 'gp' type
    return SL_STATUS_INVALID_TYPE;
  }
  // NOTE multiple imports do not perform an update - must clear the key before importing...
  (void) sl_sec_man_destroy_key(key_id);
  sl_sec_man_status_t sec_status =
    sl_sec_man_import_key(
      &key_id,
      ZB_PSA_KEY_TYPE,
      ZB_PSA_ALG,
      ZB_PSA_KEY_USAGE,
      PSA_KEY_PERSISTENCE_DEFAULT,
      plaintext_key->key,
      EMBER_ENCRYPTION_KEY_SIZE);
  return sec_status == SL_SECURITY_MAN_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)

sl_status_t zb_sec_man_store_in_link_key_table(sl_zb_sec_man_context_t* context,
                                               sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;

  if (key_id >= ZB_PSA_KEY_ID_LINK_KEY_TABLE_END) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  EmberKeyStruct keyStruct;
  MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));

  sl_sec_man_status_t sec_man_status;
  // destroy first, if it exists
  (void)sl_sec_man_destroy_key(key_id);
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         ZB_PSA_ALG,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_PERSISTENCE_DEFAULT,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  if (sec_man_status != SL_SECURITY_MAN_SUCCESS) {
    return SL_STATUS_FAIL;
  }

  MEMMOVE(keyStruct.partnerEUI64, context->eui64, EUI64_SIZE);
  keyStruct.type = EMBER_APPLICATION_LINK_KEY;

  EmberStatus status = emSetKeyTableEntry(false,  // no delete
                                          context->key_index,
                                          &keyStruct);

  if (status == EMBER_SUCCESS) {
    // Write a bit in the token to tell the upgrade code that this token already
    // points to a PSA ID
    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, context->key_index);
    if ((tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_ENTRY_HAS_PSA_ID) == 0) {
      emberStoreHighLowInt32u(&tok[KEY_ENTRY_KEY_DATA_OFFSET], key_id);
      tok[KEY_ENTRY_INFO_OFFSET] |= KEY_TABLE_ENTRY_HAS_PSA_ID;
    }
    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, context->key_index, (void*)&tok);
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t find_link_key_table_key(sl_zb_sec_man_context_t* context)
{
  EmberStatus status = EMBER_NOT_FOUND;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    EmberKeyStruct result = { 0 };
    status = emGetKeyTableEntry(context->key_index, &result);
    if (status == EMBER_SUCCESS) {
      MEMMOVE(context->eui64, result.partnerEUI64, EUI64_SIZE);
      context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
    }
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    context->key_index = emFindKeyTableEntry(context->eui64, true);
    if (context->key_index != 0xFF) {
      status = EMBER_SUCCESS;
      context->flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;
    }
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_NOT_FOUND;
}

sl_status_t zb_sec_man_fetch_from_link_key_table(sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status;

  // find_link_key_table_key always fills in the ->key_index field upon success
  status = find_link_key_table_key(context);

  if (status != SL_STATUS_OK) {
    return SL_STATUS_NOT_FOUND;
  }

  bool lookForEmptyEntry = false;
  if ((context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID)
      && emMemoryByteCompare(context->eui64, EUI64_SIZE, 0x0)) {
    lookForEmptyEntry = true;
  }

  if (!lookForEmptyEntry) {
    uint32_t key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;

    size_t size_returned;
    sl_sec_man_status_t sec_man_status = sl_sec_man_export_key(key_id,
                                                               plaintext_key->key,
                                                               sizeof(plaintext_key->key),
                                                               &size_returned);

    if (sec_man_status != SL_SECURITY_MAN_SUCCESS) {
      return SL_STATUS_FAIL;
    }
  }

  emMfgSecurityConfigModifyKey((EmberKeyData*)plaintext_key);
  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_delete_key_table_key(sl_zb_sec_man_context_t* context)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    context->key_index = emFindKeyTableEntry(context->eui64, true); // linkKey
  }

  if (context->key_index != 0xFF) {
    status = emSetKeyTableEntry(true,   // delete
                                context->key_index,
                                NULL);  // key data, don't care
  }

  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }

  // remove the key from secure storage
  // We may be deleting a key that was never added to begin with (the
  // emSetKeyTableEntry call above simply wipes a token and returns success),
  // so ignore the return from Security Manager
  uint32_t key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;
  (void)sl_sec_man_destroy_key(key_id);

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key)
{
  EmberStatus status;
  EmberKeyStruct keyStruct;

  // First import into PSA
  psa_key_id_t key_id;
  sl_sec_man_status_t sec_man_status;
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         ZB_PSA_ALG,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_LIFETIME_VOLATILE,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  if (sec_man_status != SL_SECURITY_MAN_SUCCESS) {
    return SL_STATUS_FAIL;
  }

  MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));
  MEMMOVE(keyStruct.partnerEUI64, context->eui64, EUI64_SIZE);
  keyStruct.psa_id = key_id;
  keyStruct.bitmask |= EMBER_KEY_HAS_PSA_ID;
  keyStruct.type = EMBER_TRUST_CENTER_LINK_KEY;

  if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
    keyStruct.bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
  }

  status = emAddTransientLinkKey(&keyStruct);

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t find_transient_key(sl_zb_sec_man_context_t* context,
                               EmberTransientKeyData* transientKey)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = emGetTransientKeyTableEntry(context->key_index, transientKey);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    EmberKeyStructBitmask bitmask = 0;
    if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
      bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
    }
    bool found = findTransientLinkKey(context->eui64, transientKey, &bitmask);
    status = found ? EMBER_SUCCESS : EMBER_NOT_FOUND;
  }

  if (status == EMBER_SUCCESS) {
    MEMMOVE(context->eui64, transientKey->eui64, EUI64_SIZE);
    context->multi_network_index = transientKey->networkIndex;
    if (transientKey->bitmask & EMBER_UNCONFIRMED_TRANSIENT_KEY) {
      context->flags |= ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY;
    }
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_NOT_FOUND;
}

sl_status_t zb_sec_man_fetch_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key)
{
  sl_status_t status;
  EmberTransientKeyData transientKeyData;

  status = find_transient_key(context, &transientKeyData);

  if (status != SL_STATUS_OK) {
    return status;
  }

  // Get the key from PSA
  size_t size_returned;
  sl_sec_man_status_t sec_man_status = sl_sec_man_export_key(transientKeyData.psa_id,
                                                             plaintext_key->key,
                                                             sizeof(plaintext_key->key),
                                                             &size_returned);

  return (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sl_zb_sec_man_delete_transient_key(sl_zb_sec_man_context_t* context)
{
  EmberTransientKeyData transientKeyData = { 0 };
  EmberKeyStructBitmask bitmask = 0;

  if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
    bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
  }

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    EmberStatus status = emGetTransientKeyTableEntry(context->key_index, &transientKeyData);
    if (status != EMBER_SUCCESS) {
      return SL_STATUS_NOT_FOUND;
    }
  } else {  // search by EUI
    if (!findTransientLinkKey(context->eui64, &transientKeyData, &bitmask)) {
      return SL_STATUS_NOT_FOUND;
    }
  }

  // remove the key from our internal buffers, which hold everything except the
  // actual key value
  if (!removeTransientLinkKey(context->eui64, &transientKeyData.bitmask)) {
    return SL_STATUS_NOT_FOUND;
  }

  // remove the key from secure storage
  sl_sec_man_status_t sec_man_status = sl_sec_man_destroy_key(transientKeyData.psa_id);

  return (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_secure_ezsp_key(sl_zb_sec_man_context_t* context,
                                             sl_zb_sec_man_key_t * plaintext_key)
{
  // NOTE no need to check key type because calls to this should be multiplexed into by key type(?)
  uint32_t key_id = ZB_PSA_KEY_ID_SECURE_EZSP_KEY;
  // NOTE multiple imports do not perform an update - must clear the key before importing...
  (void) sl_sec_man_destroy_key(key_id);
  sl_sec_man_status_t sec_status =
    sl_sec_man_import_key(
      &key_id,
      ZB_PSA_KEY_TYPE,
      ZB_PSA_ALG,
      ZB_PSA_KEY_USAGE,
      PSA_KEY_PERSISTENCE_DEFAULT,
      plaintext_key->key,
      EMBER_ENCRYPTION_KEY_SIZE);
  return sec_status == SL_SECURITY_MAN_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_fetch_secure_ezsp_key(sl_zb_sec_man_context_t* context,
                                             sl_zb_sec_man_key_t * plaintext_key)
{
  // NOTE no need to check key type because calls to this should be multiplexed into by key type(?)
  uint32_t key_id = ZB_PSA_KEY_ID_SECURE_EZSP_KEY;
  size_t psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  sl_sec_man_status_t sec_status =
    sl_sec_man_export_key(
      key_id,
      plaintext_key->key,
      EMBER_ENCRYPTION_KEY_SIZE,
      // NOTE unused...
      &psa_key_len);
  return sec_status == SL_SECURITY_MAN_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  sl_sec_man_status_t sec_man_status;

  // Destroy first, if it exists
  (void)sl_sec_man_destroy_key(zb_sec_man_internal_key_psa_id);

  sec_man_status = sl_sec_man_import_key(&zb_sec_man_internal_key_psa_id,
                                         ZB_PSA_KEY_TYPE,
                                         ZB_PSA_ALG,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_LIFETIME_VOLATILE,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  return (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_fetch_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  size_t size_returned;
  sl_sec_man_status_t sec_man_status = sl_sec_man_export_key(zb_sec_man_internal_key_psa_id,
                                                             plaintext_key->key,
                                                             sizeof(plaintext_key->key),
                                                             &size_returned);
  return (sec_man_status == SL_SECURITY_MAN_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sl_zb_sec_man_check_key_context(sl_zb_sec_man_context_t* context)
{
  sl_status_t status;

  // Save off loaded key context, as we don't want to overwrite it
  psa_key_id_t temp = zb_sm_context_psa_key_id;

  // If we can load it (and possibly derive it), then it's good
  status = sl_zb_sec_man_load_key_context(context);

  // Restore the context key ID
  zb_sm_context_psa_key_id = temp;

  return status;
}

//helper function for HMAC w/ AES-MMO, ported from hmac.c to avoid
//dependency on the deprecated emberHmacAesHash API
static void xorKeyWithByte(const uint8_t key[ENCRYPTION_BLOCK_SIZE],
                           uint8_t byte,
                           uint8_t result[ENCRYPTION_BLOCK_SIZE])
{
  uint8_t i;
  for (i = 0; i < ENCRYPTION_BLOCK_SIZE; i++) {
    result[i] = key[i] ^ byte;
  }
}

//This is still handled through software on Vault-supported parts,
//as the AES-MMO algorithm used for hashing is not supported by
//the Vault hardware needed for internal crypto operations.
void sl_zb_sec_man_hmac_aes_mmo(const uint8_t* input,
                                const uint8_t data_length,
                                uint8_t* output)
{
  //export referenced key from Vault; store it locally so it isn't
  //kept around for longer than necessary
  uint8_t zb_sec_man_hmac_key[EMBER_ENCRYPTION_KEY_SIZE];
  //returned by PSA as the number of bytes actually used for the key;
  //should be 16 as we're only using keys of that size
  size_t keyLength;
  sl_sec_man_export_key(zb_sm_context_psa_key_id,
                        zb_sec_man_hmac_key,
                        (size_t) EMBER_ENCRYPTION_KEY_SIZE,
                        &keyLength);

  uint8_t buffer[ENCRYPTION_BLOCK_SIZE];
  uint8_t run;
  EmberAesMmoHashContext context;

  for (run = 0; run < 2; run++) {
    xorKeyWithByte((const uint8_t*) &zb_sec_man_hmac_key,
                   (run == 0
                    ? 0x36
                    : 0x5C),
                   buffer);

    emberAesMmoHashInit(&context);
    emberAesMmoHashUpdate(&context, ENCRYPTION_BLOCK_SIZE, buffer);
    emberAesMmoHashFinal(&context,
                         (run == 0
                          ? data_length
                          : ENCRYPTION_BLOCK_SIZE),
                         (run == 0
                          ? input
                          : output));
    MEMMOVE(output, context.result, ENCRYPTION_BLOCK_SIZE);
  }
}

sl_status_t sl_zb_sec_man_aes_ccm(uint8_t* nonce,
                                  bool encrypt,
                                  const uint8_t* input,
                                  uint8_t encryption_start_index,
                                  uint8_t length,
                                  uint8_t* output)
{
  sl_sec_man_status_t status = sl_sec_man_aes_ccm_crypt(zb_sm_context_psa_key_id, nonce, encrypt,
                                                        input, encryption_start_index,
                                                        length, output);

  return sec_man_to_sl_status(status);
}

sl_status_t sec_man_to_sl_status(sl_sec_man_status_t sec_man_error)
{
  switch (sec_man_error) {
    case SL_SECURITY_MAN_VERIFICATION_FAILED:
      return SL_STATUS_INVALID_SIGNATURE;
    case SL_SECURITY_MAN_INVALID_PARAMS:
      return SL_STATUS_INVALID_PARAMETER;
    case SL_SECURITY_MAN_SUCCESS:
      return SL_STATUS_OK;
    default:
      return SL_STATUS_FAIL;
  }
  return SL_STATUS_FAIL;
}

// This is here until we figure out how to replace everyone who calls this
// and not break make test
void emAesEncrypt(uint8_t* block, const uint8_t* key)
{
  size_t output_size = 0;
  psa_key_attributes_t key_attr = PSA_KEY_ATTRIBUTES_INIT;

  psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&key_attr, PSA_BYTES_TO_BITS(EMBER_ENCRYPTION_KEY_SIZE));

  psa_status_t status = CIPHER_SINGLE_SHOT_ENC_FCT(
    &key_attr,
    key,
    EMBER_ENCRYPTION_KEY_SIZE,
    PSA_ALG_ECB_NO_PADDING,
    NULL, 0,
    block, SECURITY_BLOCK_SIZE,
    block, SECURITY_BLOCK_SIZE,
    &output_size);

  psa_reset_key_attributes(&key_attr);

  assert(status == PSA_SUCCESS);
  assert(output_size == SECURITY_BLOCK_SIZE);
}

// This is here until we figure out how to replace everyone who calls this
// and not break make test
void emAesDecrypt(uint8_t* block, const uint8_t* key)
{
  size_t output_size = 0;
  psa_key_attributes_t key_attr = PSA_KEY_ATTRIBUTES_INIT;

  psa_set_key_type(&key_attr, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&key_attr, PSA_BYTES_TO_BITS(EMBER_ENCRYPTION_KEY_SIZE));

  psa_status_t status = CIPHER_SINGLE_SHOT_DEC_FCT(
    &key_attr,
    key,
    EMBER_ENCRYPTION_KEY_SIZE,
    PSA_ALG_ECB_NO_PADDING,
    block, SECURITY_BLOCK_SIZE,
    block, SECURITY_BLOCK_SIZE,
    &output_size);

  psa_reset_key_attributes(&key_attr);

  assert(status == PSA_SUCCESS);
  assert(output_size == SECURITY_BLOCK_SIZE);
}

// This is here until we figure out how to replace everyone who calls this
// and not break make test
void emGetKeyFromCore(uint8_t* key)
{
  size_t keyLength;
  (void)sl_sec_man_export_key(zb_sm_context_psa_key_id,
                              key,
                              (size_t)EMBER_ENCRYPTION_KEY_SIZE,
                              &keyLength);
}
