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
#include "em_system.h"

// Externs
extern bool sli_zigbee_is_null_key(EmberKeyData * key);
extern void sli_zigbee_stack_token_primitive(bool tokenRead,
                                             void* tokenStruct,
                                             uint16_t tokenAddress,
                                             uint8_t length);
extern bool sli_zigbee_get_trust_center_eui64(EmberEUI64 address);
extern EmberNodeId emberGetNodeId(void);
extern EmberStatus sli_zigbee_add_transient_link_key(const EmberKeyStruct* keyStruct);
extern EmberStatus sli_zigbee_get_transient_key_table_entry(uint8_t index, EmberTransientKeyData *transientKeyData);
extern bool findTransientLinkKey(const EmberEUI64 eui64ToFind,
                                 EmberTransientKeyData *keyDataReturn,
                                 EmberKeyStructBitmask* bitmask);
extern bool removeTransientLinkKey(const EmberEUI64 eui64ToFind,
                                   EmberKeyStructBitmask* bitmask);
static sl_status_t find_transient_key(sl_zb_sec_man_context_t* context,
                                      EmberTransientKeyData* transientKey);
static sl_status_t find_link_key_table_key(sl_zb_sec_man_context_t* context);
extern EmberStatus sli_zigbee_af_set_key_table_entry(bool erase,
                                                     uint8_t index,
                                                     EmberKeyStruct* keyStruct);
extern EmberStatus sli_zigbee_get_key_table_entry(uint8_t index, EmberKeyStruct *result);
extern void sli_legacy_mfg_security_config_modify_key(EmberKeyData* key);
extern uint8_t sli_zigbee_find_key_table_entry(EmberEUI64 address, bool linkKey, uint8_t bitmask);
extern bool sli_zigbee_af_memory_byte_compare(const uint8_t *bytes, uint8_t count, uint8_t target);

// Globals
static psa_key_id_t zb_sm_context_psa_key_id;
static psa_key_id_t zb_sec_man_internal_key_psa_id;
static psa_key_id_t zb_sec_man_derived_key_psa_id = 0;
static psa_key_id_t zb_sm_context_psa_key_id_backup;

static bool zb_sec_is_key_present(uint32_t key_id);

// Eventually pull this from aps-keys-full.h
#define KEY_TABLE_ENTRY_HAS_PSA_ID          (BIT(6))

// This bit indicates if entry in the key table is a Symmetric Passphrase
#define KEY_TABLE_SYMMETRIC_PASSPHRASE      (BIT(7))

//forward declaration
static void zb_sec_man_validate_psa_key_attributes(sl_zb_sec_man_context_t *context, psa_key_id_t key_id, psa_key_attributes_t *attributes);

void sli_zigbee_security_hardware_init(void)
{
}

void sl_zb_sec_man_init_context(sl_zb_sec_man_context_t* context)
{
  MEMSET(context, 0, sizeof(*context));
  //Set a default algorithm of PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 4).
  context->psa_key_alg_permission = ZB_PSA_ALG;
}

//Sets the context's PSA algorithm permission to PSA_ALG_ECB_NO_PADDING; getter
//exists to fix bugs involved in trying to set it directly (where code was not
//aware of some Vault-only defines when it should have been).
void sl_zb_sec_man_set_context_aes_ecb_alg(sl_zb_sec_man_context_t* context)
{
  context->psa_key_alg_permission = PSA_ALG_ECB_NO_PADDING;
}

void sl_zb_sec_man_set_context_extended_ccm_alg(sl_zb_sec_man_context_t* context)
{
  context->psa_key_alg_permission = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, 8);
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
    status = (sl_sec_man_destroy_key(key_id) == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
  }

  return status;
}

psa_key_id_t sli_zigbee_sec_man_get_psa_id_from_context(const sl_zb_sec_man_context_t* context)
{
  sl_status_t status = SL_STATUS_FAIL;
  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
      return ((context->key_index == 0) ? ZB_PSA_KEY_ID_ACTIVE_NWK_KEY : ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY);
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
      return ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
    {
      EmberTransientKeyData transientKey;
      status = find_transient_key((sl_zb_sec_man_context_t*)context, &transientKey);
      if (status == SL_STATUS_OK) {
        return transientKey.psa_id;
      }
      return 0;
    }
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
    {
      status = find_link_key_table_key((sl_zb_sec_man_context_t*)context);
      if (status == SL_STATUS_OK) {
        return (context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START);
      }
      return 0;
    }
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
      return ZB_PSA_KEY_ID_ZLL_ENCRYPT_KEY;
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
      return ZB_PSA_KEY_ID_ZLL_PRE_CONFIGURED_KEY;
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
      return ZB_PSA_KEY_ID_GP_PROXY_TABLE_START + context->key_index;
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
      return ZB_PSA_KEY_ID_GP_SINK_TABLE_START + context->key_index;
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      return zb_sec_man_internal_key_psa_id;
    default:
      return 0;
  }
}

sl_status_t sl_zb_sec_man_load_key_context(sl_zb_sec_man_context_t* context)
{
  sl_status_t status = SL_STATUS_OK;

  zb_sm_context_psa_key_id = sli_zigbee_sec_man_get_psa_id_from_context(context);

  if (zb_sm_context_psa_key_id == 0) {
    return SL_STATUS_NOT_FOUND;
  }

  psa_key_attributes_t test_key_attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_status_t test_status = sl_sec_man_get_key_attributes(zb_sm_context_psa_key_id, &test_key_attributes);

  if (test_status != PSA_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  } else if (zb_sm_context_psa_key_id >= ZB_PSA_KEY_ID_MIN
             && zb_sm_context_psa_key_id <= ZB_PSA_KEY_ID_MAX) {
    zb_sec_man_validate_psa_key_attributes(context, zb_sm_context_psa_key_id, &test_key_attributes);
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
    psa_status_t sec_man_status;

    sec_man_status = sl_sec_man_import_key(&zb_sec_man_derived_key_psa_id,
                                           ZB_PSA_KEY_TYPE,
                                           context->psa_key_alg_permission,
                                           ZB_PSA_KEY_USAGE,
                                           PSA_KEY_LIFETIME_VOLATILE,
                                           (const uint8_t*)&derived_key.key,
                                           EMBER_ENCRYPTION_KEY_SIZE);

    // Use this derived key for crypto operations
    zb_sm_context_psa_key_id = zb_sec_man_derived_key_psa_id;

    status = (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
  }

  return status;
}

//Ensure that a persistent key's attributes are consistent with the expectations of current stack version.
//Re-import them with updated attributes if they are not.
void zb_sec_man_validate_psa_key_attributes(sl_zb_sec_man_context_t *context, psa_key_id_t key_id, psa_key_attributes_t *attributes)
{
  psa_key_location_t current_location = PSA_KEY_LIFETIME_GET_LOCATION(psa_get_key_lifetime(attributes));
  psa_algorithm_t current_alg = psa_get_key_algorithm(attributes);
  bool reimported = false;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK && current_alg == 0) {
    sl_zb_sec_man_key_t plaintext_key;
    (void) sl_zb_sec_man_export_key(context, &plaintext_key);
    (void) sl_zb_sec_man_import_key(context, &plaintext_key);
    reimported = true;
  }
#if defined (SEMAILBOX_PRESENT)
  if (SYSTEM_GetSecurityCapability() == securityCapabilityVault && current_location == PSA_KEY_LOCATION_LOCAL_STORAGE && !reimported) {
    //This API is not called on volatile keys so new persistence will always be default/persistent.
    psa_key_lifetime_t new_lifetime = PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(PSA_KEY_PERSISTENCE_DEFAULT, PSA_KEY_LOCATION_SLI_SE_OPAQUE);
    psa_set_key_lifetime(attributes, new_lifetime);
    //Used so sl_sec_man_copy_key doesn't change the context key ID
    psa_key_id_t key_id_copy = key_id;
    (void) sl_sec_man_copy_key(key_id, attributes, &key_id_copy);
    reimported = true;
  }
#endif // defined (SEMAILBOX_PRESENT)
  if (reimported) {
    uint8_t current_version = 0;
    zb_sec_man_fetch_version_key(&current_version);
    if (current_version < ZB_SEC_MAN_CURRENT_VERSION_KEY) {
      zb_sec_man_store_version_key();
    }
  }
}

void zb_sec_man_backup_key_context(bool direction)
{
  if (direction) {
    MEMMOVE(&zb_sm_context_psa_key_id_backup, &zb_sm_context_psa_key_id, 4);
  } else {
    MEMMOVE(&zb_sm_context_psa_key_id, &zb_sm_context_psa_key_id_backup, 4);
  }
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

  bool has_first_derivation = false;
  zb_sm_context_psa_key_id = sli_zigbee_sec_man_get_psa_id_from_context(context);

  if ((context->derived_type & SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_SWAP_OUT_KEY) != 0) {
    emberAesHashSimple(EMBER_ENCRYPTION_KEY_SIZE,
                       (const uint8_t*) source_key,
                       (uint8_t* ) derived_key);
    has_first_derivation = true;
  } else if ((context->derived_type & SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_HASHED_LINK_KEY) != 0) {
    sl_zb_sec_man_hmac_aes_mmo(context->eui64, EUI64_SIZE, (uint8_t*) derived_key);
    has_first_derivation = true;
  }
  if (has_first_derivation) {
    //If key has multiple valid derived types, it will be one from the previous cases
    //and one from the following (as some derived types are treated more like ordinary link keys).
    //Import and load the first derivation in at this point, to have the second derivation operation computed from it.
    if (zb_sec_man_derived_key_psa_id != 0) {
      (void) sl_sec_man_destroy_key(zb_sec_man_derived_key_psa_id);
    }
    psa_status_t sec_man_status = sl_sec_man_import_key(&zb_sec_man_derived_key_psa_id,
                                                        ZB_PSA_KEY_TYPE,
                                                        context->psa_key_alg_permission,
                                                        ZB_PSA_KEY_USAGE,
                                                        PSA_KEY_LIFETIME_VOLATILE,
                                                        (const uint8_t*)&derived_key->key,
                                                        EMBER_ENCRYPTION_KEY_SIZE);
    if (sec_man_status != PSA_SUCCESS) {
      return SL_STATUS_FAIL;
    }
    zb_sm_context_psa_key_id = zb_sec_man_derived_key_psa_id;
  }
  if ((context->derived_type & SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_TRANSPORT_KEY) != 0) {
    tag = DERIVE_TRANSPORT_KEY_TAG;
    sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*)derived_key);
  } else if ((context->derived_type & SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_LOAD_KEY) != 0) {
    tag = DERIVE_LOAD_KEY_TAG;
    sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*) derived_key);
  } else if ((context->derived_type & SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_VERIFY_KEY) != 0) {
    tag = DERIVE_VERIFY_KEY_TAG;
    sl_zb_sec_man_hmac_aes_mmo(&tag, 1, (uint8_t*) derived_key);
  }
  if (context->derived_type == SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_delete_key_by_psa_id(uint32_t psa_id)
{
  psa_status_t sec_man_status = sl_sec_man_destroy_key(psa_id);

  return (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  psa_status_t status = SL_STATUS_NOT_SUPPORTED;
  uint32_t key_id;
  if (context->key_index == 0 ) {
    key_id = ZB_PSA_KEY_ID_ACTIVE_NWK_KEY;
  } else {
    key_id = ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY;
  }
  (void)sl_sec_man_destroy_key(key_id);
  status = sl_sec_man_import_key(&key_id, ZB_PSA_KEY_TYPE, context->psa_key_alg_permission,
                                 ZB_PSA_KEY_USAGE,
                                 PSA_KEY_PERSISTENCE_DEFAULT, plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);

  return status;
}

sl_status_t zb_sec_man_store_version_key(void)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  uint32_t key_id = ZB_PSA_KEY_ID_VERSION_KEY;
  //value to store is fixed; a fetched value being lower than
  //ZB_SEC_MAN_CURRENT_VERSION_KEY likely indicates some sort of
  //upgrade routine should run.
  uint8_t current_version = ZB_SEC_MAN_CURRENT_VERSION_KEY;
  (void) sl_sec_man_destroy_key(key_id);
  status = sl_sec_man_import_key(&key_id,
                                 PSA_KEY_TYPE_RAW_DATA,
                                 PSA_ALG_NONE,
                                 ZB_PSA_KEY_USAGE,
                                 PSA_KEY_PERSISTENCE_DEFAULT,
                                 &current_version,
                                 ZB_SEC_MAN_CURRENT_VERSION_KEY_SIZE);

  return ((status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL);
}

sl_status_t zb_sec_man_fetch_version_key(uint8_t* version)
{
  psa_status_t status = SL_STATUS_FAIL;
  uint32_t key_id = ZB_PSA_KEY_ID_VERSION_KEY;
  uint8_t fetched_version = 0;
  size_t    zb_sec_man_version_key_len = ZB_SEC_MAN_CURRENT_VERSION_KEY_SIZE;
  status = sl_sec_man_export_key(key_id,
                                 &fetched_version,
                                 ZB_SEC_MAN_CURRENT_VERSION_KEY_SIZE,
                                 &zb_sec_man_version_key_len);

  if (status == PSA_ERROR_INVALID_HANDLE) {
    *version = 0;
    return SL_STATUS_NOT_FOUND;
  } else if (status != PSA_SUCCESS) {
    return SL_STATUS_FAIL;
  } else {
    *version = fetched_version;
    return SL_STATUS_OK;
  }
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
  psa_status_t sec_status = sl_sec_man_export_key(key_id, plaintext_key->key,
                                                  EMBER_ENCRYPTION_KEY_SIZE,
                                                  &sl_psa_key_len);
  return sec_status == PSA_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static bool zb_sec_is_key_present(uint32_t key_id)
{
  sl_zb_sec_man_key_t plaintext_key;
  size_t    sl_psa_key_len = EMBER_ENCRYPTION_KEY_SIZE;
  psa_status_t sec_man_status = sl_sec_man_export_key(key_id,
                                                      plaintext_key.key,
                                                      EMBER_ENCRYPTION_KEY_SIZE,
                                                      &sl_psa_key_len);
  return ((sec_man_status == PSA_SUCCESS) && !sli_zigbee_is_null_key((EmberKeyData * )plaintext_key.key)) ? true : false;
}

sl_status_t sl_zb_sec_man_get_network_key_info(sl_zb_sec_man_network_key_info_t * network_key_info)
{
  tokTypeStackKeys tok;
  //Fetch Alternate nwk key info
  sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  network_key_info->alt_network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->alternate_network_key_set = zb_sec_is_key_present(ZB_PSA_KEY_ID_ALTERNATE_NWK_KEY);
  //Fetch nwk key info
  sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  network_key_info->network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->network_key_set = zb_sec_is_key_present(ZB_PSA_KEY_ID_ACTIVE_NWK_KEY);
  // Fetch nwk key frame counter info
  network_key_info->network_key_frame_counter = emberGetSecurityFrameCounter();

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t * plaintext_key)
{
  uint32_t key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
  (void) sl_sec_man_destroy_key(key_id);
  psa_status_t sec_man_status;
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         context->psa_key_alg_permission,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_PERSISTENCE_DEFAULT,
                                         (const uint8_t *)plaintext_key->key,
                                         sizeof(plaintext_key->key));
  if (sec_man_status != PSA_SUCCESS) {
    return SL_STATUS_FAIL;
  }

  // Write a bit in the token to tell the upgrade code that this token already
  // points to a PSA ID
  tokTypeStackTrustCenter tok;
  sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  if ((tok.mode & TRUST_CENTER_KEY_LIVES_IN_PSA) == 0) {
    tok.mode |= TRUST_CENTER_KEY_LIVES_IN_PSA;
    sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  }

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key)
{
  uint32_t key_id = ZB_PSA_KEY_ID_PRECONFIGURED_APS_KEY;
  EmberEUI64 tcAddress;
  if (emberGetNodeId() != 0x0000
      && sli_zigbee_get_trust_center_eui64(tcAddress)) {
    if ((context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID)
        && (0 != MEMCOMPARE(context->eui64, tcAddress, EUI64_SIZE))) {
      return SL_STATUS_NOT_FOUND;
    }
    MEMMOVE(context->eui64, tcAddress, EUI64_SIZE);
    context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
  }
  psa_status_t sec_man_status;
  size_t returned_key_len;
  sec_man_status = sl_sec_man_export_key(key_id,
                                         (uint8_t*) plaintext_key,
                                         EMBER_ENCRYPTION_KEY_SIZE,
                                         &returned_key_len);
  if (sec_man_status != PSA_SUCCESS) {
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
  psa_status_t sec_status = sl_sec_man_export_key(key_id, plaintext_key->key,
                                                  EMBER_ENCRYPTION_KEY_SIZE,
                                                  &sl_psa_key_len);
  return sec_status == PSA_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  psa_status_t status = SL_STATUS_NOT_SUPPORTED;
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
  status = sl_sec_man_import_key(&key_id, ZB_PSA_KEY_TYPE, context->psa_key_alg_permission,
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
  psa_status_t sec_status = sl_sec_man_export_key(
    key_id, plaintext_key->key,
    EMBER_ENCRYPTION_KEY_SIZE,
    // NOTE unused...
    &psa_key_len
    );
  return sec_status == PSA_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
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
  psa_status_t sec_status =
    sl_sec_man_import_key(
      &key_id,
      ZB_PSA_KEY_TYPE,
      context->psa_key_alg_permission,
      ZB_PSA_KEY_USAGE,
      PSA_KEY_PERSISTENCE_DEFAULT,
      plaintext_key->key,
      EMBER_ENCRYPTION_KEY_SIZE);
  return sec_status == PSA_SUCCESS ? SL_STATUS_OK : SL_STATUS_FAIL;
}
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)

sl_status_t zb_sec_man_store_in_link_key_table(sl_zb_sec_man_context_t* context,
                                               sl_zb_sec_man_key_t* plaintext_key)
{
  //find a key index if one wasn't given
  if (context->key_index == 0xFF) {
    EmberEUI64 null_eui;
    MEMSET(&null_eui, 0, sizeof(EmberEUI64));
    uint8_t existing_index = sli_zigbee_find_key_table_entry(context->eui64, true, 0);
    if (existing_index != 0xFF) {
      context->key_index = existing_index;
    } else {
      uint8_t open_index = sli_zigbee_find_key_table_entry(null_eui, true, 0);
      if (open_index != 0xFF) {
        context->key_index = open_index;
      }
    }
  }

  uint32_t key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;

  if (key_id >= ZB_PSA_KEY_ID_LINK_KEY_TABLE_END) {
    return SL_STATUS_NO_MORE_RESOURCE;
  }

  EmberKeyStruct keyStruct;
  MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));

  psa_status_t sec_man_status;
  // destroy first, if it exists
  (void)sl_sec_man_destroy_key(key_id);
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         context->psa_key_alg_permission,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_PERSISTENCE_DEFAULT,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  if (sec_man_status != PSA_SUCCESS) {
    return SL_STATUS_FAIL;
  }

  MEMMOVE(keyStruct.partnerEUI64, context->eui64, EUI64_SIZE);
  keyStruct.type = EMBER_APPLICATION_LINK_KEY;
  keyStruct.bitmask = context->flags & ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE
                      ? EMBER_KEY_IS_AUTHENTICATION_TOKEN : 0;

  EmberStatus status = sli_zigbee_af_set_key_table_entry(false,  // no delete
                                                         context->key_index,
                                                         &keyStruct);

  if (status == EMBER_SUCCESS) {
    // Write a bit in the token to tell code that this token
    // points to a PSA ID
    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, context->key_index);
    if ((tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_ENTRY_HAS_PSA_ID) == 0) {
      emberStoreHighLowInt32u(&tok[KEY_ENTRY_KEY_DATA_OFFSET], key_id);
      tok[KEY_ENTRY_INFO_OFFSET] |= KEY_TABLE_ENTRY_HAS_PSA_ID;
    }
    if (context->flags & ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE) {
      tok[KEY_ENTRY_INFO_OFFSET] |= KEY_TABLE_SYMMETRIC_PASSPHRASE;
    }
    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, context->key_index, (void*)&tok);
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t find_link_key_table_key(sl_zb_sec_man_context_t* context)
{
  EmberStatus status = EMBER_NOT_FOUND;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    EmberKeyStruct result = { 0 };
    status = sli_zigbee_get_key_table_entry(context->key_index, &result);
    if (status == EMBER_SUCCESS) {
      MEMMOVE(context->eui64, result.partnerEUI64, EUI64_SIZE);
      context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
    }
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    uint8_t bitmask = (context->flags & ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE) ? KEY_TABLE_SYMMETRIC_PASSPHRASE : 0;
    context->key_index = sli_zigbee_find_key_table_entry(context->eui64, true, bitmask); // linkKey
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
      && sli_zigbee_af_memory_byte_compare(context->eui64, EUI64_SIZE, 0x0)) {
    lookForEmptyEntry = true;
  }

  if (!lookForEmptyEntry) {
    uint32_t key_id = context->key_index + ZB_PSA_KEY_ID_LINK_KEY_TABLE_START;

    size_t size_returned;
    psa_status_t sec_man_status = sl_sec_man_export_key(key_id,
                                                        plaintext_key->key,
                                                        sizeof(plaintext_key->key),
                                                        &size_returned);

    if (sec_man_status != PSA_SUCCESS) {
      return SL_STATUS_FAIL;
    }
  }

  sli_legacy_mfg_security_config_modify_key((EmberKeyData*)plaintext_key);
  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_delete_key_table_key(sl_zb_sec_man_context_t* context)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    uint8_t bitmask = (context->flags & ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE) ? KEY_TABLE_SYMMETRIC_PASSPHRASE : 0;
    context->key_index = sli_zigbee_find_key_table_entry(context->eui64, true, bitmask); // linkKey
  }

  if (context->key_index != 0xFF) {
    status = sli_zigbee_af_set_key_table_entry(true,   // delete
                                               context->key_index,
                                               NULL); // key data, don't care
  }

  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }

  // remove the key from secure storage
  // We may be deleting a key that was never added to begin with (the
  // sli_zigbee_af_set_key_table_entry call above simply wipes a token and returns success),
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
  psa_status_t sec_man_status;
  sec_man_status = sl_sec_man_import_key(&key_id,
                                         ZB_PSA_KEY_TYPE,
                                         context->psa_key_alg_permission,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_LIFETIME_VOLATILE,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  if (sec_man_status != PSA_SUCCESS) {
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
  if (context->flags & ZB_SEC_MAN_FLAG_AUTHENTICATED_DYNAMIC_LINK_KEY) {
    keyStruct.bitmask |= EMBER_DLK_DERIVED_KEY;
  }
  if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    keyStruct.bitmask |= EMBER_KEY_HAS_PARTNER_EUI64;
  }

  status = sli_zigbee_add_transient_link_key(&keyStruct);

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t find_transient_key(sl_zb_sec_man_context_t* context,
                                      EmberTransientKeyData* transientKey)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = sli_zigbee_get_transient_key_table_entry(context->key_index, transientKey);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    EmberKeyStructBitmask bitmask = 0;
    if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
      bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
    }
    if (context->flags & ZB_SEC_MAN_FLAG_AUTHENTICATED_DYNAMIC_LINK_KEY) {
      bitmask |= EMBER_DLK_DERIVED_KEY;
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
    if (transientKey->bitmask & EMBER_DLK_DERIVED_KEY) {
      context->flags |= ZB_SEC_MAN_FLAG_AUTHENTICATED_DYNAMIC_LINK_KEY;
    }
    if (transientKey->bitmask & EMBER_KEY_HAS_PARTNER_EUI64) {
      context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
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
  psa_status_t sec_man_status = sl_sec_man_export_key(transientKeyData.psa_id,
                                                      plaintext_key->key,
                                                      sizeof(plaintext_key->key),
                                                      &size_returned);

  return (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sl_zb_sec_man_delete_transient_key(sl_zb_sec_man_context_t* context)
{
  EmberTransientKeyData transientKeyData = { 0 };
  EmberKeyStructBitmask bitmask = 0;
  if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
    bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
  }
  if (context->flags & ZB_SEC_MAN_FLAG_AUTHENTICATED_DYNAMIC_LINK_KEY) {
    bitmask |= EMBER_DLK_DERIVED_KEY;
  }

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    EmberStatus status = sli_zigbee_get_transient_key_table_entry(context->key_index, &transientKeyData);
    if (status != EMBER_SUCCESS) {
      return SL_STATUS_NOT_FOUND;
    }
    //place EUI in context in case it wanted to delete by index
    MEMMOVE(context->eui64, transientKeyData.eui64, sizeof(EmberEUI64));
    context->flags |= ZB_SEC_MAN_FLAG_EUI_IS_VALID;
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
  psa_status_t sec_man_status = sl_sec_man_destroy_key(transientKeyData.psa_id);

  return (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_store_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  psa_status_t sec_man_status;

  // Destroy first, if it exists
  (void)sl_sec_man_destroy_key(zb_sec_man_internal_key_psa_id);

  sec_man_status = sl_sec_man_import_key(&zb_sec_man_internal_key_psa_id,
                                         ZB_PSA_KEY_TYPE,
                                         context->psa_key_alg_permission,
                                         ZB_PSA_KEY_USAGE,
                                         PSA_KEY_LIFETIME_VOLATILE,
                                         plaintext_key->key,
                                         EMBER_ENCRYPTION_KEY_SIZE);

  return (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_fetch_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  size_t size_returned;
  psa_status_t sec_man_status = sl_sec_man_export_key(zb_sec_man_internal_key_psa_id,
                                                      plaintext_key->key,
                                                      sizeof(plaintext_key->key),
                                                      &size_returned);
  return (sec_man_status == PSA_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
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

sl_status_t sl_zb_sec_man_aes_ccm_extended(uint8_t* nonce,
                                           bool encrypt,
                                           const uint8_t* input,
                                           uint8_t encryption_start_index,
                                           uint8_t length,
                                           uint8_t mic_length,
                                           uint8_t* output)
{
  psa_status_t status = sl_sec_man_aes_ccm_crypt(zb_sm_context_psa_key_id, nonce, encrypt,
                                                 input, encryption_start_index,
                                                 length, mic_length, output);

  return psa_to_sl_status(status);
}

sl_status_t psa_to_sl_status(psa_status_t sec_man_error)
{
  switch (sec_man_error) {
    case PSA_ERROR_INVALID_SIGNATURE:
      return SL_STATUS_INVALID_SIGNATURE;
    case PSA_ERROR_INVALID_ARGUMENT:
      return SL_STATUS_INVALID_PARAMETER;
    case PSA_SUCCESS:
      return SL_STATUS_OK;
    default:
      return SL_STATUS_FAIL;
  }
  return SL_STATUS_FAIL;
}

sl_status_t sl_zb_sec_man_aes_128_crypt_block(bool encrypt,
                                              const uint8_t* input,
                                              uint8_t* output)
{
  psa_status_t status;
  if (encrypt) {
    status = sl_sec_man_aes_encrypt(zb_sm_context_psa_key_id,
                                    PSA_ALG_ECB_NO_PADDING,
                                    input,
                                    output);
  } else {
    status = sl_sec_man_aes_decrypt(zb_sm_context_psa_key_id,
                                    PSA_ALG_ECB_NO_PADDING,
                                    input,
                                    output);
  }
  return psa_to_sl_status(status);
}

void zb_sec_man_delete_all_keys(void)
{
  uint32_t psa_id;
  for (psa_id = ZB_PSA_KEY_ID_ACTIVE_NWK_KEY; psa_id < ZB_PSA_KEY_ID_GP_SINK_TABLE_END; psa_id++) {
    (void)zb_sec_man_delete_key_by_psa_id(psa_id);
  }
}

bool sl_zb_sec_man_compare_key_to_value(sl_zb_sec_man_context_t* context, const sl_zb_sec_man_key_t* test_key)
{
  //Perform the same operation on a stored key and test value to see whether they are same,
  //without requiring that the stored key be extracted outside of Secure Vault.

  //This function uses the internal/one-off key slot for its own purposes, so is incompatible with a context
  //pointing to the same slot as they would conflict.
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL) {
    return false;
  }

  //Set up some arbitrary data to encrypt with.
  #define TEST_NONCE { 0x01, 0x01, 0x02, 0x03, 0x05, 0x08, 0x0D, 0x15, 0x22, 0x37, 0x59, 0x90, 0xE9 }
  #define TEST_PACKET { 0xF0, 0xE1, 0xD2, 0xC3, 0xB4, 0xA5, 0x96, 0x87, 0x78, 0x69, 0x5A, 0x4B, 0x3C, 0x2D, 0x1E, 0x0F }
  #define TEST_PACKET_LENGTH 16

  const uint8_t test_nonce[NONCE_LENGTH] = TEST_NONCE;
  const uint8_t test_packet[TEST_PACKET_LENGTH] = TEST_PACKET;
  //Specify some part of test_packet as authentication data.  4 is an arbitrary value.
  #define KEY_COMPARE_AUTH_LENGTH 4
  #define TEST_MIC_LENGTH 4

  //Buffers for encryption output
  uint8_t output_unknown[TEST_PACKET_LENGTH + TEST_MIC_LENGTH];
  uint8_t output_known[TEST_PACKET_LENGTH + TEST_MIC_LENGTH];
  sl_zb_sec_man_load_key_context(context);
  //Use AES-CCM for this test as it is permitted by ZB_PSA_ALG
  sl_zb_sec_man_aes_ccm((uint8_t*)&test_nonce, true, (uint8_t*)&test_packet, KEY_COMPARE_AUTH_LENGTH, TEST_PACKET_LENGTH, output_unknown);
  sl_zb_sec_man_context_t test_context;
  sl_zb_sec_man_init_context(&test_context);
  test_context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL;
  sl_zb_sec_man_import_key(&test_context, (sl_zb_sec_man_key_t*)test_key);
  sl_zb_sec_man_load_key_context(&test_context);
  sl_zb_sec_man_aes_ccm((uint8_t*)&test_nonce, true, (uint8_t*)&test_packet, KEY_COMPARE_AUTH_LENGTH, TEST_PACKET_LENGTH, output_known);

  if (MEMCOMPARE(output_unknown, output_known, TEST_MIC_LENGTH + TEST_PACKET_LENGTH) == 0) {
    return true;
  }

  return false;
}
