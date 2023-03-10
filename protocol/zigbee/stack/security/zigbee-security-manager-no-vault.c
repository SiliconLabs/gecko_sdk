/***************************************************************************//**
 * @file
 * @brief Implementation of security-related APIs, including key storage, key
 *   fetching, and crypto operations. In this file, keys are stored in NVM3.
 *   This file is only compiled for parts without Vault support.
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
#include "hal.h" // for TOKEN_resolution
#include "stack/include/security.h"
#include "stack/config/token-stack.h"
#include "stack/platform/micro/aes.h"
#include "stack/include/stack-info.h"
#include "stack/include/aes-mmo.h"

#ifdef UC_BUILD
 #include "sl_component_catalog.h"
#endif // UC_BUILD

// Externs
extern void emGetKeyFromCore(uint8_t* key);
extern void emLoadKeyIntoCore(const uint8_t* key);
extern EmberStatus emAddTransientLinkKey(const EmberKeyStruct* keyStruct);
extern EmberStatus emGetTransientKeyTableEntry(uint8_t index, EmberTransientKeyData *transientKeyData);
extern bool emGetTrustCenterEui64(EmberEUI64 address);
extern bool findTransientLinkKey(const EmberEUI64 eui64ToFind,
                                 EmberTransientKeyData *keyDataReturn,
                                 EmberKeyStructBitmask* bitmask);
extern bool removeTransientLinkKey(const EmberEUI64 eui64ToFind,
                                   EmberKeyStructBitmask* bitmask);
extern void emStackTokenPrimitive(bool tokenRead,
                                  void* tokenStruct,
                                  uint16_t tokenAddress,
                                  uint8_t length);
extern EmberStatus emGetKeyTableEntry(uint8_t index, EmberKeyStruct *result);
extern uint8_t emFindKeyTableEntry(EmberEUI64 address, bool linkKey);
extern void emMfgSecurityConfigModifyKey(EmberKeyData* key);
extern bool emMemoryByteCompare(const uint8_t *bytes, uint8_t count, uint8_t target);
extern bool emIsTokenDataInitialized(uint8_t* data, uint8_t length);
extern EmberStatus emSetKeyTableEntry(bool erase,
                                      uint8_t index,
                                      EmberKeyStruct* keyStruct);
extern bool emIsNullKey(EmberKeyData * key);
//used for software fallback of CCM*
extern void emStandAloneEncryptBlock(uint8_t *block);

// Globals
// The global context key, or key that is used in crypto operations
static uint8_t zb_sec_man_context_key[EMBER_ENCRYPTION_KEY_SIZE];

// A scratch key that we only need temporarily, like CBKE operations
static uint8_t zb_sec_man_internal_key[EMBER_ENCRYPTION_KEY_SIZE];

// Eventually pull this from aps-keys-full.h
#define KEY_TABLE_ENTRY_HAS_PSA_ID          (BIT(6))

sl_status_t zb_sec_man_store_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  tokTypeStackKeys tok;
  if (context->key_index == 1) {
    emStackTokenPrimitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
    MEMMOVE(tok.networkKey, plaintext_key->key, sizeof(plaintext_key->key));
    emStackTokenPrimitive(false, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  } else {
    emStackTokenPrimitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
    MEMMOVE(tok.networkKey, plaintext_key->key, sizeof(plaintext_key->key));
    emStackTokenPrimitive(false, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  }

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_nwk_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  tokTypeStackKeys tok;
  if (context->key_index == 1) {
    emStackTokenPrimitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  } else {
    emStackTokenPrimitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  }
  MEMMOVE(plaintext_key->key, tok.networkKey, sizeof(plaintext_key->key));
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key)
{
  tokTypeStackTrustCenter tok;
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  MEMMOVE(tok.key, plaintext_key->key, sizeof(plaintext_key->key));
  emStackTokenPrimitive(false, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_tc_link_key(sl_zb_sec_man_context_t* context,
                                         sl_zb_sec_man_key_t* plaintext_key)
{
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

  tokTypeStackTrustCenter tok;
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_TRUST_CENTER, TOKEN_STACK_TRUST_CENTER_SIZE);
  MEMMOVE(plaintext_key->key, tok.key, sizeof(plaintext_key->key));

  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key)
{
  EmberStatus status;
  EmberKeyStruct keyStruct;

  // Transient keys are typically used on Trust Centers
  // Advanced users can utilize them as another means of trying multiple keys
  // when joining a trust center (e.g. using a set of wildcard keys to act like
  // multiple preconfigured key slot keys)

  MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));
  MEMMOVE(keyStruct.partnerEUI64, context->eui64, EUI64_SIZE);
  MEMMOVE(emberKeyContents(&(keyStruct.key)), plaintext_key, EMBER_ENCRYPTION_KEY_SIZE);
  keyStruct.bitmask |= EMBER_KEY_HAS_KEY_DATA;
  keyStruct.type = EMBER_TRUST_CENTER_LINK_KEY;

  if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
    keyStruct.bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
  }

  status = emAddTransientLinkKey(&keyStruct);

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_fetch_transient_key(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_key_t* plaintext_key)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberTransientKeyData transientKeyData;

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = emGetTransientKeyTableEntry(context->key_index, &transientKeyData);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    EmberKeyStructBitmask bitmask = 0;
    if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
      bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
    }
    bool found = findTransientLinkKey(context->eui64, &transientKeyData, &bitmask);
    status = found ? EMBER_SUCCESS : EMBER_NOT_FOUND;
  }

  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }

  MEMMOVE(context->eui64, transientKeyData.eui64, EUI64_SIZE);
  context->multi_network_index = transientKeyData.networkIndex;
  if (transientKeyData.bitmask & EMBER_UNCONFIRMED_TRANSIENT_KEY) {
    context->flags |= ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY;
  }
  MEMMOVE(plaintext_key->key, transientKeyData.keyData.contents, EMBER_ENCRYPTION_KEY_SIZE);

  return SL_STATUS_OK;
}

#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
sl_status_t zb_sec_man_fetch_secure_ezsp_key(sl_zb_sec_man_context_t* context,
                                             sl_zb_sec_man_key_t * plaintext_key)
{
  tokTypeSecureEzspSecurityKey tok;
  halCommonGetToken(&tok, TOKEN_SECURE_EZSP_SECURITY_KEY);
  MEMMOVE(plaintext_key->key, tok.contents, sizeof(plaintext_key->key));
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_secure_ezsp_key(sl_zb_sec_man_context_t* context,
                                             sl_zb_sec_man_key_t * plaintext_key)
{
  tokTypeSecureEzspSecurityKey tok;
  halCommonGetToken(&tok, TOKEN_SECURE_EZSP_SECURITY_KEY);
  MEMMOVE(tok.contents, plaintext_key->key, sizeof(plaintext_key->key));
  halCommonSetToken(TOKEN_SECURE_EZSP_SECURITY_KEY, &tok);
  return SL_STATUS_OK;
}
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)

#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
sl_status_t zb_sec_man_fetch_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  tokTypeStackZllSecurity zllSecurityToken;
  halCommonGetToken(&zllSecurityToken, TOKEN_STACK_ZLL_SECURITY);
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY) {
    MEMMOVE(plaintext_key->key,
            zllSecurityToken.encryptionKey,
            EMBER_ENCRYPTION_KEY_SIZE);
  } else {
    MEMMOVE(plaintext_key->key,
            zllSecurityToken.preconfiguredKey,
            EMBER_ENCRYPTION_KEY_SIZE);
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_zll_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key)
{
  tokTypeStackZllSecurity zllSecurityToken;
  halCommonGetToken(&zllSecurityToken, TOKEN_STACK_ZLL_SECURITY);
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY) {
    MEMMOVE(zllSecurityToken.encryptionKey,
            plaintext_key->key,
            EMBER_ENCRYPTION_KEY_SIZE);
  } else {
    MEMMOVE(zllSecurityToken.preconfiguredKey,
            plaintext_key->key,
            EMBER_ENCRYPTION_KEY_SIZE);
  }
  halCommonSetToken(TOKEN_STACK_ZLL_SECURITY, &zllSecurityToken);
  return SL_STATUS_OK;
}
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)

#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
sl_status_t zb_sec_man_fetch_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key)
{
  uint8_t index = context->key_index;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY) {
    tokTypeStackGpProxyTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_PROXY_TABLE, index);
    MEMMOVE(plaintext_key->key, tok.gpdKey, EMBER_ENCRYPTION_KEY_SIZE);
  } else {
    tokTypeStackGpSinkTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_SINK_TABLE, index);
    MEMMOVE(plaintext_key->key, tok.gpdKey, EMBER_ENCRYPTION_KEY_SIZE);
  }
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_store_gp_key(sl_zb_sec_man_context_t* context,
                                    sl_zb_sec_man_key_t* plaintext_key)
{
  uint8_t index = context->key_index;
  if (context->core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY) {
    tokTypeStackGpProxyTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_PROXY_TABLE, index);
    MEMMOVE(tok.gpdKey, plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);
    halCommonSetIndexedToken(TOKEN_STACK_GP_PROXY_TABLE, index, &tok);
  } else {
    tokTypeStackGpSinkTableEntry tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_GP_SINK_TABLE, index);
    MEMMOVE(tok.gpdKey, plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);
    halCommonSetIndexedToken(TOKEN_STACK_GP_SINK_TABLE, index, &tok);
  }
  return SL_STATUS_OK;
}
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)

sl_status_t zb_sec_man_store_in_link_key_table(sl_zb_sec_man_context_t* context,
                                               sl_zb_sec_man_key_t* plaintext_key)
{
  EmberKeyStruct keyStruct;
  MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));
  MEMMOVE(keyStruct.partnerEUI64, context->eui64, EUI64_SIZE);
  MEMMOVE(keyStruct.key.contents, plaintext_key->key, EMBER_ENCRYPTION_KEY_SIZE);
  keyStruct.type = EMBER_APPLICATION_LINK_KEY;

  EmberStatus status = emSetKeyTableEntry(false,  // no delete
                                          context->key_index,
                                          &keyStruct);

  if (status == EMBER_SUCCESS) {
    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, context->key_index);
    MEMMOVE(&(tok[KEY_ENTRY_KEY_DATA_OFFSET]),
            plaintext_key->key,
            EMBER_ENCRYPTION_KEY_SIZE);
    tok[KEY_ENTRY_INFO_OFFSET] |= EMBER_KEY_HAS_KEY_DATA;
    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, context->key_index, (void*)&tok);
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t zb_sec_man_fetch_from_link_key_table(sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key)
{
  EmberStatus status = EMBER_ERR_FATAL;
  EmberKeyStruct keyStruct;
  bool lookForEmptyEntry = emMemoryByteCompare(context->eui64, EUI64_SIZE, 0x0);

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    status = emGetKeyTableEntry(context->key_index, &keyStruct);
    MEMMOVE(context->eui64, keyStruct.partnerEUI64, EUI64_SIZE);
  } else if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    context->key_index = emFindKeyTableEntry(context->eui64, true); // linkKey
    status = (context->key_index != 0xFF) ? EMBER_SUCCESS : EMBER_NOT_FOUND;
    if (context->key_index != 0xFF && !lookForEmptyEntry) {
      status = emGetKeyTableEntry(context->key_index, &keyStruct);
    }
  }

  if (status != EMBER_SUCCESS) {
    return SL_STATUS_NOT_FOUND;
  }

  tokTypeStackKeyTable tok;
  halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, context->key_index);
  // Ensure that the token does not point to a PSA ID. If this asserts, it
  // means you have attempted to downgrade from an image that stored keys in
  // secure vault to an image that does not; this is prohibited. The token
  // houses the ID in PSA where the key lives, and since we don't have PSA
  // support, we can't possibly function correctly. This is a misconfiguration.
  // Either flash an image with the Zigbee Secure Key Storage component or
  // masserase to blow away your tokens (which will wipe your persistence)
  assert((tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_ENTRY_HAS_PSA_ID) == 0);
  MEMMOVE(plaintext_key->key,
          &(tok[KEY_ENTRY_KEY_DATA_OFFSET]),
          EMBER_ENCRYPTION_KEY_SIZE);

  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_delete_transient_key(sl_zb_sec_man_context_t* context)
{
  EmberTransientKeyData transientKeyData = { 0 };

  if (context->flags & ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY) {
    transientKeyData.bitmask |= EMBER_UNCONFIRMED_TRANSIENT_KEY;
  }

  if (context->flags & ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID) {
    EmberStatus status = emGetTransientKeyTableEntry(context->key_index, &transientKeyData);
    if (status != EMBER_SUCCESS) {
      return SL_STATUS_NOT_FOUND;
    }
  }

  return (removeTransientLinkKey(context->eui64, &transientKeyData.bitmask) ? SL_STATUS_OK : SL_STATUS_NOT_FOUND);
}

sl_status_t sl_zb_sec_man_delete_key_table_key(sl_zb_sec_man_context_t* context)
{
  EmberStatus status = EMBER_ERR_FATAL;

  if (context->flags & ZB_SEC_MAN_FLAG_EUI_IS_VALID) {
    context->key_index = emFindKeyTableEntry(context->eui64, true); // linkKey
  }

  if (context->key_index != 0xFF) {
    EmberKeyStruct keyStruct;
    MEMSET(&keyStruct, 0, sizeof(EmberKeyStruct));
    status = emSetKeyTableEntry(true,   // delete
                                context->key_index,
                                NULL);  // key data, don't care
  }

  return (status == EMBER_SUCCESS) ? SL_STATUS_OK : SL_STATUS_NOT_FOUND;
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

//Code ported over from emberHmacAesHash; has Zigbee security manager
//handle key loading instead of taking in key data as an argument.

void sl_zb_sec_man_hmac_aes_mmo(const uint8_t* input,
                                const uint8_t data_length,
                                uint8_t* output)
{
  //load key from other function calls first
  emGetKeyFromCore((uint8_t*) &zb_sec_man_context_key);

  uint8_t buffer[ENCRYPTION_BLOCK_SIZE];
  uint8_t run;
  EmberAesMmoHashContext context;

  for (run = 0; run < 2; run++) {
    xorKeyWithByte((const uint8_t*) &zb_sec_man_context_key,
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

#if defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM) && defined(PSA_WANT_ALG_CCM) && defined(MBEDTLS_PSA_CRYPTO_DRIVERS)
sl_status_t sl_zb_sec_man_aes_ccm(uint8_t* nonce,
                                  bool encrypt,
                                  const uint8_t* input,
                                  uint8_t encryption_start_index,
                                  uint8_t length,
                                  uint8_t* output)
{
  //Ported over from the PSA implementations inside ccm-star.c
  psa_status_t psa_status;
  size_t tag_len;
  size_t output_length;
  psa_key_attributes_t attr = PSA_KEY_ATTRIBUTES_INIT;

  psa_set_key_type(&attr, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attr, PSA_BYTES_TO_BITS(sizeof(zb_sec_man_context_key)));

  //copy the auth data to output buffer
  if (input != output) {
    MEMMOVE(output, input, encryption_start_index);
  }

  if (encrypt) {
    psa_status = AEAD_ENCRYPT_TAG_FCT(
      &attr, zb_sec_man_context_key, sizeof(zb_sec_man_context_key),
      PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, MIC_LENGTH),
      nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index,
      output + encryption_start_index, length - encryption_start_index, &output_length,
      output + length, MIC_LENGTH, &tag_len);
  } else {
    psa_status = AEAD_DECRYPT_TAG_FCT(
      &attr, zb_sec_man_context_key, sizeof(zb_sec_man_context_key),
      PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, MIC_LENGTH),
      nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index,
      input + length, MIC_LENGTH,
      output + encryption_start_index, length - encryption_start_index, &output_length);
  }

  psa_reset_key_attributes(&attr);

  if (psa_status == PSA_ERROR_INVALID_SIGNATURE) {
    return SL_STATUS_INVALID_SIGNATURE;
  }

  if (psa_status != PSA_SUCCESS || output_length != (uint8_t) (length - encryption_start_index)
      || (encrypt && tag_len != MIC_LENGTH)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    return SL_STATUS_OK;
  }
}

#else //no support for PSA APIs at all; compile with software implementation of CCM*.
//ported from ccm-star.c
//Define these if ccm-star is no longer being included
#ifndef CCM_STAR_HEADER
#define STANDALONE_FLAGS_INDEX                   0
#define STANDALONE_NONCE_INDEX                   1
#define STANDALONE_VARIABLE_FIELD_INDEX_HIGH    14
#define STANDALONE_VARIABLE_FIELD_INDEX_LOW     15
#endif

#ifndef TEMP_BUFFER_SIZE
#define TEMP_BUFFER_SIZE 256
#endif

static uint8_t encryptionBlock[ENCRYPTION_BLOCK_SIZE];

static void encryptNonce(uint8_t *nonce,
                         uint8_t flagsMask,
                         uint16_t variableField,
                         uint8_t block[ENCRYPTION_BLOCK_SIZE])
{
  MEMCOPY(block + STANDALONE_NONCE_INDEX, nonce, NONCE_LENGTH);

  block[STANDALONE_FLAGS_INDEX] = flagsMask;
  block[STANDALONE_VARIABLE_FIELD_INDEX_HIGH] = HIGH_BYTE(variableField);
  block[STANDALONE_VARIABLE_FIELD_INDEX_LOW] = LOW_BYTE(variableField);

  emStandAloneEncryptBlock(block);
}

static uint16_t min(uint16_t num1,
                    uint16_t num2)
{
  if (num1 <= num2) {
    return num1;
  }
  return num2;
}

static uint8_t xorBytesIntoBlock(uint8_t *block,
                                 uint8_t blockIndex,
                                 const uint8_t *bytes,
                                 uint16_t count)
{
  uint16_t i;

  for (i = 0; i < count; ) {
    uint16_t needed = ENCRYPTION_BLOCK_SIZE - blockIndex;
    uint16_t todo = count - i;
    uint16_t copied = min(todo, needed);
    uint16_t j;

    for (j = 0; j < copied; j++, blockIndex++) {
      block[blockIndex] ^= *bytes++;
    }
    i += copied;

    if (blockIndex == ENCRYPTION_BLOCK_SIZE) {
      emStandAloneEncryptBlock(block);
      blockIndex = 0;
    }
  }
  return blockIndex;
}

static void ccmEncryptData(uint8_t *bytes,
                           uint16_t length,
                           uint8_t blockCount,
                           uint8_t *nonce)
{
  while (length > 0) {
    uint8_t todo = min(length, ENCRYPTION_BLOCK_SIZE);
    uint8_t i;
    encryptNonce(nonce, 0x01, blockCount, encryptionBlock);
    blockCount += 1;

    for (i = 0; i < todo; i++) {
      *bytes++ ^= encryptionBlock[i];
    }

    length -= todo;
  }
}

static sl_status_t zb_sec_man_calc_encrypt_mic(uint8_t* nonce,
                                               uint8_t* data,
                                               uint8_t encryption_start_index,
                                               uint8_t length)
{
  uint8_t blockIndex = 2;     // skip over frame length field
  uint8_t *chunk = data;
  uint16_t chunklen;
  uint8_t phase;

  chunklen = encryption_start_index;
  encryptNonce(nonce, 0x49, length - encryption_start_index, encryptionBlock);
  // first two bytes are the 16-bit representation of the frame length,
  // high byte first
  encryptionBlock[0] ^= HIGH_BYTE(encryption_start_index);
  encryptionBlock[1] ^= LOW_BYTE(encryption_start_index);
  // phase 0: go over authenticated data
  // phase 1: go over the payload
  for (phase = 0; phase < 2; phase++) {
    blockIndex = xorBytesIntoBlock(encryptionBlock,
                                   blockIndex,
                                   chunk,
                                   chunklen);
    chunk = data + encryption_start_index;
    chunklen = length - encryption_start_index;

    // finish off authData if not on an encryption block boundary
    if (blockIndex > 0) {
      emStandAloneEncryptBlock(encryptionBlock);
      blockIndex = 0;
    }
  }

  MEMCOPY(data + length, encryptionBlock, MIC_LENGTH);
  // The MIC gets encrypted as block zero of the message.
  ccmEncryptData(data + length, MIC_LENGTH, 0, nonce);
  return SL_STATUS_OK;
}

//Software implementation here is based on implementation for emberCcmCalculateAndEncryptMic,
//but assumes packet input/output format.
//output points to auth data, with encrypt data at encryption_start_index past it and MIC
//starting at output + length (4 bytes long)
sl_status_t sl_zb_sec_man_aes_ccm(uint8_t* nonce,
                                  bool encrypt,
                                  const uint8_t* input,
                                  uint8_t encryption_start_index,
                                  uint8_t length,
                                  uint8_t* output)
{
  //Move input into output location for in-place encryption
  MEMCOPY(output, input, length);
  bool authenticated;
  if (encrypt) {
    zb_sec_man_calc_encrypt_mic(nonce, output, encryption_start_index, length);
    if (length > encryption_start_index) {
      ccmEncryptData(output + encryption_start_index, length - encryption_start_index, 1, nonce);
    }
  } else {
    ccmEncryptData(output + encryption_start_index, length - encryption_start_index, 1, nonce);
    uint8_t temp[TEMP_BUFFER_SIZE];
    MEMCOPY(temp, output, length);
    zb_sec_man_calc_encrypt_mic(nonce, temp, encryption_start_index, length);
    authenticated = MEMCOMPARE(input + length, temp + length, MIC_LENGTH) == 0;
    if (!authenticated) {
      //MIC check failed
      return SL_STATUS_INVALID_SIGNATURE;
    }
  }

  return SL_STATUS_OK;
}

#endif // defined(MBEDTLS_PSA_ACCEL_KEY_TYPE_AES) && defined(MBEDTLS_PSA_ACCEL_ALG_CCM) && defined(PSA_WANT_ALG_CCM) && defined(MBEDTLS_PSA_CRYPTO_DRIVERS)

sl_status_t sl_zb_sec_man_check_key_context(sl_zb_sec_man_context_t* context)
{
  //finds the key itself for non-Vault implementation, but doesn't return it
  sl_zb_sec_man_key_t test_key_data;

  //If export key succeeds, the context is able to properly extract a key.
  //Returns not found if context couldn't be used to load a key.
  sl_status_t export_status = sl_zb_sec_man_export_key(context, &test_key_data);
  if (export_status == SL_STATUS_OK) {
    return SL_STATUS_OK;
  }
  return SL_STATUS_NOT_FOUND;
}

//generate derived key from security context, key, and requested type.
sl_status_t zb_sec_man_derive_key(sl_zb_sec_man_key_t* source_key,
                                  const sl_zb_sec_man_context_t* context,
                                  sl_zb_sec_man_key_t* derived_key)
{
  uint8_t tag;

  //source_key is used as the key for hashing;
  //When loading a key context that includes a derived key,
  //callers must set the core key type correctly to ensure that
  //key derivation is done correctly.

  emLoadKeyIntoCore((uint8_t*) source_key);

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
    case SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE:
      return SL_STATUS_INVALID_PARAMETER;
      break;
    default:
      break;
  }
  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_delete_key(sl_zb_sec_man_context_t* context)
{
  sl_status_t status = SL_STATUS_INVALID_PARAMETER;

  // Every non-indexed key is simply overwritten with 0s
  sl_zb_sec_man_key_t null_key;
  MEMSET(null_key.key, 0, sizeof(null_key.key));

  switch (context->core_key_type) {
    case SL_ZB_SEC_MAN_KEY_TYPE_NETWORK:
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
#if defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
    case SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY:
#endif // defined(SL_CATALOG_ZIGBEE_NCP_SECURE_EZSP_PRESENT)
#if defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY:
#endif // defined(SL_CATALOG_ZIGBEE_LIGHT_LINK_PRESENT) || defined(EMBER_TEST)
#if defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY:
    case SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY:
#endif // defined(SL_CATALOG_ZIGBEE_GREEN_POWER_PRESENT) || defined(EMBER_TEST)
    case SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL:
      status = sl_zb_sec_man_import_key(context, &null_key);
      break;
    // Everything starting here is an indexed key
    case SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT:
      status = sl_zb_sec_man_delete_transient_key(context);
      break;
    case SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK:
      status = sl_zb_sec_man_delete_key_table_key(context);
      break;
    default:
      break;
  }

  return status;
}

/*
 * This function will load the specified core key type into the Security Manager's internal Context.
 * If the derived key type is one other than SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE it will derive the requested key
 * and load it into the Zigbee Security Manager context.
 * Any subsequent encryption or hash operations will be done with that loaded context.
 * For SL_ZB_SEC_MAN_KEY_TYPE_NETWORK, the key index is the primary/alternate key identifier.
 * For SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK:
 * If the device is the trust center the key index will be the link key table entry.
 * If the device is a regular node it will load the device's trust center link key.
 *
 */
sl_status_t sl_zb_sec_man_load_key_context(sl_zb_sec_man_context_t* context)
{
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_export_key(context, &plaintext_key);
  if (context->derived_type != SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE) {
    sl_zb_sec_man_key_t derived_key;
    zb_sec_man_derive_key(&plaintext_key, context, &derived_key);
    MEMCOPY(&zb_sec_man_context_key, &derived_key, EMBER_ENCRYPTION_KEY_SIZE);
  } else {
    MEMCOPY(&zb_sec_man_context_key, &plaintext_key, EMBER_ENCRYPTION_KEY_SIZE);
  }
  //TODO: Investigate removing this (and only using zb_sec_man_context_key as the "core")
  emLoadKeyIntoCore((const uint8_t *)&zb_sec_man_context_key);
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_delete_key_by_psa_id(UNUSED uint32_t psa_id)
{
  return SL_STATUS_NOT_SUPPORTED;
}

sl_status_t zb_sec_man_store_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  MEMMOVE(&zb_sec_man_internal_key, plaintext_key, EMBER_ENCRYPTION_KEY_SIZE);
  return SL_STATUS_OK;
}

sl_status_t zb_sec_man_fetch_internal_key(UNUSED sl_zb_sec_man_context_t* context,
                                          sl_zb_sec_man_key_t* plaintext_key)
{
  MEMMOVE(plaintext_key, &zb_sec_man_internal_key, EMBER_ENCRYPTION_KEY_SIZE);
  return SL_STATUS_OK;
}

sl_status_t sl_zb_sec_man_get_network_key_info(sl_zb_sec_man_network_key_info_t * network_key_info)
{
  tokTypeStackKeys tok;
  //Fetch Alternate nwk key info
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_ALTERNATE_KEY, TOKEN_STACK_ALTERNATE_KEY_SIZE);
  network_key_info->alt_network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->alternate_network_key_set = !emIsNullKey((EmberKeyData*)tok.networkKey);
  //Fetch nwk key info
  emStackTokenPrimitive(true, &tok, TOKEN_STACK_KEYS, TOKEN_STACK_KEYS_SIZE);
  network_key_info->network_key_sequence_number = tok.activeKeySeqNum;
  network_key_info->network_key_set = !emIsNullKey((EmberKeyData*)tok.networkKey);
  return SL_STATUS_OK;
}
