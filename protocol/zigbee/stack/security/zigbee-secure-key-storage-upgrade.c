/***************************************************************************//**
 * @file
 * @brief Code to upgrade existing devices onto images using secure key storage.
 * Keys are taken from classic key storage (plaintext NVM3 tokens) and imported
 * into Secure Vault.  Key data is erased from the tokens afterward and metadata
 * is set if applicable to indicate that the key is present in Vault.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "stack/security/zigbee-secure-key-storage-upgrade.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

//headers used in non-Vault security manager implementation
#include "hal.h" // for TOKEN_resolution
#include "stack/config/token-stack.h"
#include "stack/include/stack-info.h"
#include "stack/include/security.h"

extern void sli_zigbee_stack_token_primitive(bool tokenRead,
                                             void* tokenStruct,
                                             uint16_t tokenAddress,
                                             uint8_t length);

//number of keys per type that passed/failed upgrade
uint8_t keys_passed[NUMBER_OF_KEY_TYPES] = { 0 };
uint8_t keys_failed[NUMBER_OF_KEY_TYPES] = { 0 };

sl_status_t zb_sec_man_upgrade_link_key_table(void)
{
  //avoid compiler issues for builds without a key table
  #if (EMBER_KEY_TABLE_SIZE > 0)
  uint8_t i;
  EmberEUI64 invalidEUI64 = { 0 };
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  //As upgrade procedure iterates through each valid key index,
  //mark this flag as valid to ensure the check for an already migrated
  //key returns an accurate result.
  context.flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

  for (i = 0; i < EMBER_KEY_TABLE_SIZE; i++) {
    sl_zb_sec_man_key_t plaintext_key;
    context.key_index = i;
    sl_status_t is_key_migrated = sl_zb_sec_man_check_key_context(&context);
    //If there is already a valid key stored in Vault, we don't need to migrate anything.
    //Continuing instead of returning a status to handle the hypothetical situation
    //that some but not all key table entries have a PSA ID.
    if (is_key_migrated == SL_STATUS_OK) {
      continue;
    }

    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, i);
    MEMMOVE(&(plaintext_key.key),
            &(tok[KEY_ENTRY_KEY_DATA_OFFSET]),
            EMBER_ENCRYPTION_KEY_SIZE);

    //Context needs to have EUI64 set to avoid import issues with metadata
    MEMMOVE(&(context.eui64),
            &(tok[KEY_ENTRY_IEEE_OFFSET]),
            EUI64_SIZE);

    if (MEMCOMPARE(context.eui64, invalidEUI64, EUI64_SIZE) == 0) {
      continue;
    }
    sl_status_t vault_import_status;

    vault_import_status = sl_zb_sec_man_import_key(&context, &plaintext_key);
    //continue to next index if we couldn't import the key.  It is possible that stored
    //"key data" may have been imported successfully into PSA storage from an invalid table entry.
    if (vault_import_status != SL_STATUS_OK) {
      keys_failed[KEYS_STATUS_LINK]++;
      continue;
    }
    //clear out token data; don't have space in bitmask to write that this key
    //now lives in Secure Vault
    //Value of an erased token is all 0xFF bytes
    MEMSET(&(tok[KEY_ENTRY_KEY_DATA_OFFSET]),
           0xFF,
           EMBER_ENCRYPTION_KEY_SIZE);

    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, i, &tok);
    keys_passed[KEYS_STATUS_LINK]++;
  }
  return SL_STATUS_OK;
  #endif // (EMBER_KEY_TABLE_SIZE > 0)
  return SL_STATUS_NOT_SUPPORTED;
}

#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
sl_status_t zb_sec_man_upgrade_gp_proxy_table(void)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY;
  sl_status_t vault_import_status;
  uint8_t i;

  for (i = 0; i < sli_zigbee_gp_proxy_table_size; i++) {
    context.key_index = i;
    sl_status_t is_key_migrated = sl_zb_sec_man_check_key_context(&context);
    //no need to move key over if Vault has an entry for it
    if (is_key_migrated == SL_STATUS_OK) {
      continue;
    }

    sl_zb_sec_man_key_t plaintext_key;
    tokTypeStackGpProxyTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_PROXY_TABLE, i);
    MEMMOVE(&plaintext_key.key, tok.gpdKey, EMBER_ENCRYPTION_KEY_SIZE);

    vault_import_status = sl_zb_sec_man_import_key(&context, &plaintext_key);

    if (vault_import_status != SL_STATUS_OK) {
      keys_failed[KEYS_STATUS_GP]++;
      continue;
    }
    //erase token by writing all 0xFF to it
    MEMSET(&tok, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
    halCommonSetIndexedToken(TOKEN_STACK_GP_PROXY_TABLE, i, &tok);
    keys_passed[KEYS_STATUS_GP]++;
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_upgrade_gp_sink_table(void)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY;
  sl_status_t vault_import_status;
  uint8_t i;

  for (i = 0; i < sli_zigbee_gp_sink_table_size; i++) {
    context.key_index = i;
    sl_status_t is_key_migrated = sl_zb_sec_man_check_key_context(&context);
    //no need to move key over if Vault has an entry for it
    if (is_key_migrated == SL_STATUS_OK) {
      continue;
    }

    sl_zb_sec_man_key_t plaintext_key;
    tokTypeStackGpSinkTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_SINK_TABLE, i);
    MEMMOVE(&plaintext_key.key, tok.gpdKey, EMBER_ENCRYPTION_KEY_SIZE);

    vault_import_status = sl_zb_sec_man_import_key(&context, &plaintext_key);
    if (vault_import_status != SL_STATUS_OK) {
      keys_failed[KEYS_STATUS_GP]++;
      continue;
    }
    //erase plaintext token's key data by setting it to all 0xFF
    MEMSET(&tok, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
    halCommonSetIndexedToken(TOKEN_STACK_GP_SINK_TABLE, i, &tok);
    keys_passed[KEYS_STATUS_GP]++;
  }
  return SL_STATUS_OK;
}
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)

sl_status_t zb_sec_man_upgrade_nwk_key(uint8_t key_index)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;
  context.key_index = key_index;

  sl_status_t is_key_migrated = sl_zb_sec_man_check_key_context(&context);
  // move key if it hasn't been moved already.
  if (is_key_migrated != SL_STATUS_OK) {
    sl_zb_sec_man_key_t plaintext_key;
    sl_status_t vault_import_status;

    tokTypeStackKeys tok;
    if (context.key_index == 1) {
      sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
    } else {
      sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
    }
    MEMMOVE(&plaintext_key.key, tok.networkKey, EMBER_ENCRYPTION_KEY_SIZE);

    vault_import_status = sl_zb_sec_man_import_key(&context, &plaintext_key);
    // exit with error if we couldn't import the key
    if (vault_import_status != SL_STATUS_OK) {
      keys_failed[KEYS_STATUS_NETWORK]++;
      return SL_STATUS_FAIL;
    }
    // "erase" the non-secure vault key by setting it to the null token value
    MEMSET(&tok.networkKey, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
    //write the cleared token data back to NVM3
    if (context.key_index == 1) {
      sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
    } else {
      sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
    }
    keys_passed[KEYS_STATUS_NETWORK]++;
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_upgrade_tc_link_key(void)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK;

  sl_status_t is_key_migrated = sl_zb_sec_man_check_key_context(&context);
  // move key if it hasn't been moved already.
  if (is_key_migrated != SL_STATUS_OK) {
    sl_zb_sec_man_key_t plaintext_key;
    sl_status_t vault_import_status;

    tokTypeStackTrustCenter tok;
    sli_zigbee_stack_token_primitive(true, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
    MEMMOVE(&plaintext_key.key, tok.key, EMBER_ENCRYPTION_KEY_SIZE);

    vault_import_status = sl_zb_sec_man_import_key(&context, &plaintext_key);
    // exit with error if we couldn't import the key
    if (vault_import_status != SL_STATUS_OK) {
      keys_failed[KEYS_STATUS_LINK]++;
      return SL_STATUS_FAIL;
    }
    // "erase" the non-secure vault key
    MEMSET(&tok.key, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
    // write cleared token data to NVM3; previous call to import already marked this key as
    // having been migrated away from token
    sli_zigbee_stack_token_primitive(false, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
    keys_passed[KEYS_STATUS_LINK]++;
  }
  return SL_STATUS_OK;
}

#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
sl_status_t zb_sec_man_upgrade_zll_key(void)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  //Check both key types associated with the ZLL token.
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY;
  sl_status_t is_key_migrated_enc = sl_zb_sec_man_check_key_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY;
  sl_status_t is_key_migrated_pre = sl_zb_sec_man_check_key_context(&context);

  // move key if it hasn't been moved already.
  if (is_key_migrated_enc != SL_STATUS_OK || is_key_migrated_pre != SL_STATUS_OK) {
    sl_zb_sec_man_key_t plaintext_key;
    tokTypeStackZllSecurity zllSecurityToken;
    halCommonGetToken(&zllSecurityToken, TOKEN_STACK_ZLL_SECURITY);

    sl_status_t vault_import_status_enc = SL_STATUS_FAIL;
    sl_status_t vault_import_status_pre = SL_STATUS_FAIL;
    // Move one type of key over at a time.
    if (is_key_migrated_enc != SL_STATUS_OK) {
      MEMMOVE(&plaintext_key.key, zllSecurityToken.encryptionKey,
              EMBER_ENCRYPTION_KEY_SIZE);
      context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY;
      vault_import_status_enc = sl_zb_sec_man_import_key(&context, &plaintext_key);
      if (vault_import_status_enc != SL_STATUS_OK) {
        keys_failed[KEYS_STATUS_ZLL]++;
      } else {
        keys_passed[KEYS_STATUS_ZLL]++;
      }
    }
    if (is_key_migrated_pre != SL_STATUS_OK) {
      MEMMOVE(&plaintext_key.key, zllSecurityToken.preconfiguredKey,
              EMBER_ENCRYPTION_KEY_SIZE);
      context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY;
      vault_import_status_pre = sl_zb_sec_man_import_key(&context, &plaintext_key);
      if (vault_import_status_pre != SL_STATUS_OK) {
        keys_failed[KEYS_STATUS_ZLL]++;
      } else {
        keys_passed[KEYS_STATUS_ZLL]++;
      }
    }

    if (keys_passed[KEYS_STATUS_ZLL] > 0) {
      // "erase" the non-secure key data from token if import was successful
      if (vault_import_status_enc == SL_STATUS_OK) {
        MEMSET(&zllSecurityToken.encryptionKey, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
      }
      if (vault_import_status_pre == SL_STATUS_OK) {
        MEMSET(&zllSecurityToken.preconfiguredKey, 0xFF, EMBER_ENCRYPTION_KEY_SIZE);
      }
      halCommonSetToken(TOKEN_STACK_ZLL_SECURITY, &zllSecurityToken);
    }
  }

  return SL_STATUS_OK;
}
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)

void sli_zb_sec_man_upgrade_key_storage(void)
{
  //Disable watchdog timer so it doesn't interrupt the upgrade
  //process if more than 50 keys are being migrated.
  bool wdog_enabled = halInternalWatchDogEnabled();
  if (wdog_enabled) {
    halInternalDisableWatchDog(MICRO_DISABLE_WATCH_DOG_KEY);
  }

  //current network key
  (void) zb_sec_man_upgrade_nwk_key(0);

  //alternate network key
  (void) zb_sec_man_upgrade_nwk_key(1);

  (void) zb_sec_man_upgrade_tc_link_key();

  #if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)
  (void) zb_sec_man_upgrade_zll_key();
  #endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT)

  (void) zb_sec_man_upgrade_link_key_table();

  #if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT)
  (void) zb_sec_man_upgrade_gp_proxy_table();
  (void) zb_sec_man_upgrade_gp_sink_table();
  #endif

  uint16_t total_keys_passed = 0;
  uint16_t total_keys_failed = 0;
  for (uint8_t i = 0; i < NUMBER_OF_KEY_TYPES; i++) {
    total_keys_passed += keys_passed[i];
    total_keys_failed += keys_failed[i];
  }

  #ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  //print upgrade status if any keys needed to be migrated
  if (total_keys_passed > 0 || total_keys_failed > 0) {
    local_printf("Successfully migrated %d keys to PSA.\n", total_keys_passed);
    local_printf("Failed to migrate %d keys (which may also be invalid).\n", total_keys_failed);
  }
  #endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT

  if (wdog_enabled) {
    halInternalEnableWatchDog();
  }
}
