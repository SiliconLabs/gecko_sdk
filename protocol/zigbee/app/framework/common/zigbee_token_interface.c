/***************************************************************************//**
 * @brief ZigBee Application Framework token management code.
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

#include PLATFORM_HEADER
#include "hal.h"
#include "stack/include/ember.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_SECURE_KEY_STORAGE_PRESENT
extern void zb_sec_man_delete_all_keys(void);
#endif

#if (defined(SL_CATALOG_TOKEN_MANAGER_PRESENT))

#include "sl_token_api.h"
#include "sl_token_manager.h"

// The following interfaces are wrapper on top of platform service token manager
// APIs. The reason for providing an access to token get and set from a host is to
// allow an NCP-Host application to completely backup the token area and restore
// on a new hardware.

#if (defined(USE_NVM3))
// The following implementation is based on NVM3 tokens.

// This function check if a token is excluded and should not be reset to default value
static bool is_token_excluded(bool exclude_outgoing_fc, bool exclude_boot_counter, uint32_t nvm3_key)
{
  bool ret = false;
  if (exclude_outgoing_fc) {
    uint32_t excluded_nvm3_outgoing_fc[] = { NVM3KEY_STACK_NONCE_COUNTER, NVM3KEY_STACK_APS_FRAME_COUNTER };
    for (uint8_t i = 0; i < (sizeof(excluded_nvm3_outgoing_fc) / sizeof(uint32_t)); i++) {
      if (excluded_nvm3_outgoing_fc[i] == nvm3_key) {
        ret = true;
        break;
      }
    }
  }
  if (exclude_boot_counter && (NVM3KEY_STACK_BOOT_COUNTER == nvm3_key)) {
    ret = true;
  }
  return ret;
}

void sl_zigbee_token_factory_reset(bool exclude_outgoing_fc, bool exclude_boot_counter)
{
  uint8_t num_of_tokens = emberGetTokenCount();
  for (uint8_t token_idx = 0; token_idx < num_of_tokens; token_idx++) {
    EmberTokenInfo token_info;
    EmberStatus status = emberGetTokenInfo(token_idx, &token_info);
    if (status == EMBER_SUCCESS) {
      if (!is_token_excluded(exclude_outgoing_fc, exclude_boot_counter, token_info.nvm3Key)) {
        for (uint8_t arrayIndex = 0; arrayIndex < token_info.arraySize; arrayIndex++) {
          EmberTokenData token_data;
          token_data.size = token_info.size;
          token_data.data = (void*) tokenDefaults[token_idx];
          // restore to default token value
          emberSetTokenData(token_info.nvm3Key,
                            arrayIndex,
                            &token_data);
        }
        halResetWatchdog();
      }
    }
  }
#ifdef SL_CATALOG_ZIGBEE_SECURE_KEY_STORAGE_PRESENT
  // delete all zigbee managed psa keys
  zb_sec_man_delete_all_keys();
#endif // SL_CATALOG_ZIGBEE_SECURE_KEY_STORAGE_PRESENT
}

uint8_t emberGetTokenCount(void)
{
  return (TOKEN_COUNT);
}

EmberStatus emberGetTokenInfo(uint8_t index,
                              EmberTokenInfo *tokenInfo)
{
  if (index >= (TOKEN_COUNT)) {
    return EMBER_INDEX_OUT_OF_RANGE;
  }
  tokenInfo->nvm3Key = tokenNvm3Keys[index];
  tokenInfo->isIdx = tokenIsIdx[index];
  tokenInfo->isCnt = tokenIsCnt[index];
  tokenInfo->size = tokenSize[index];
  tokenInfo->arraySize = tokenArraySize[index];

  return EMBER_SUCCESS;
}

EmberStatus emberGetTokenData(uint32_t token,
                              uint32_t index,
                              EmberTokenData *tokenData)
{
  // Look up the token size from the token key because
  // sl_token_get_data needs the size to be passed.
  for (uint8_t i = 0; i < emberGetTokenCount(); i++) {
    if (token == tokenNvm3Keys[i]) {
      tokenData->size = tokenSize[i];
      Ecode_t s = sl_token_get_data(token,
                                    index,
                                    tokenData->data,
                                    tokenData->size);
      return (s == ECODE_OK ? EMBER_SUCCESS : EMBER_ERR_FATAL);
    }
  }
  tokenData->size = 0;
  return EMBER_ERR_FATAL;
}

EmberStatus emberSetTokenData(uint32_t token,
                              uint32_t index,
                              EmberTokenData *tokenData)
{
  Ecode_t s = sl_token_set_data(token,
                                index,
                                tokenData->data,
                                tokenData->size);
  if (s != ECODE_OK) {
    tokenData->size = 0;
  }
  return (s == ECODE_OK ? EMBER_SUCCESS : EMBER_ERR_FATAL);
}

// Strong implementation to restore the EUI64 incase backup/restore
void emberGetRestoredEui64(EmberEUI64 eui64)
{
  uint8_t blank[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t restoredEui64[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  EmberTokenData tokenData;
  tokenData.size = 0;
  tokenData.data = (void *)restoredEui64;
  EmberStatus status = emberGetTokenData(NVM3KEY_STACK_RESTORED_EUI64,
                                         0,
                                         &tokenData);
  if (status == EMBER_SUCCESS
      && tokenData.size == sizeof(EmberEUI64)) {
    if (0 == MEMCOMPARE(blank,
                        restoredEui64,
                        sizeof(EmberEUI64))) {
      // There is no restored EUI64, no action
    } else {
      // There is a restored EUI available, so use that.
      MEMCOPY(eui64, restoredEui64, sizeof(EmberEUI64));
    }
  }
}
#endif // USE_NVM3
// If not NVM3, for any other NVM variant such as SimEE 2 it is not supported.
// The APis are stubbed as weak functions, hence application can override.
#endif // SL_CATALOG_TOKEN_MANAGER_PRESENT

// Extended to support the zigbeed that uses host token.
#if defined(SL_CATALOG_ZIGBEE_STACK_UNIX_PRESENT)
#include PLATFORM_HEADER
#include CONFIGURATION_HEADER
#include "platform/service/legacy_host/inc/token.h"
#include <syslog.h>

extern const uint16_t tokenCreators[];
extern const bool tokenIsCnt[];
extern const uint8_t tokenSize[];
extern const uint8_t tokenArraySize[];
extern const void * const tokenDefaults[];

// From the token interface
uint8_t emberGetTokenCount(void)
{
  return (TOKEN_COUNT);
}

EmberStatus emberGetTokenInfo(uint8_t index,
                              EmberTokenInfo *tokenInfo)
{
  if (index >= (TOKEN_COUNT)) {
    return EMBER_INDEX_OUT_OF_RANGE;
  }
  tokenInfo->nvm3Key = tokenCreators[index];
  tokenInfo->isIdx = 1;
  tokenInfo->isCnt = tokenIsCnt[index];
  tokenInfo->size = tokenSize[index];
  tokenInfo->arraySize = tokenArraySize[index];
  return EMBER_SUCCESS;
}

EmberStatus emberGetTokenData(uint32_t token,
                              uint32_t index,
                              EmberTokenData *tokenData)
{
  // Look up the token size from the token key because
  // sl_token_get_data needs the size to be passed.
  for (uint16_t i = 0; i < emberGetTokenCount(); i++) {
    if (token == tokenCreators[i]) {
      tokenData->size = tokenSize[i];
      //syslog(LOG_INFO, "Getting : Creator = %04X Token = %d index = %d tokenData->size = %d",token, i, index, tokenData->size);
      halInternalGetTokenData(tokenData->data, i, index, tokenData->size);
      return EMBER_SUCCESS;
    }
  }
  tokenData->size = 0;
  return EMBER_ERR_FATAL;
}

EmberStatus emberSetTokenData(uint32_t token,
                              uint32_t index,
                              EmberTokenData *tokenData)
{
  for (uint8_t i = 0; i < emberGetTokenCount(); i++) {
    if (token == tokenCreators[i]) {
      //syslog(LOG_INFO, "Setting : Creator = %04X Token = %d index = %d tokenData->size = %d",token, i, index, tokenData->size);
      halInternalSetTokenData(i, index, tokenData->data, tokenData->size);
      return EMBER_SUCCESS;
    }
  }
  return EMBER_ERR_FATAL;
}

// Strong implementation to restore the EUI64 for zigbeed in case backup/restore
void emberGetRestoredEui64(EmberEUI64 eui64)
{
  uint8_t blank[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  uint8_t restoredEui64[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  EmberTokenData tokenData;
  tokenData.size = 0;
  tokenData.data = (void *)restoredEui64;
  EmberStatus status = emberGetTokenData(CREATOR_STACK_RESTORED_EUI64,
                                         0,
                                         &tokenData);
  if (status == EMBER_SUCCESS
      && tokenData.size == sizeof(EmberEUI64)) {
    if (0 == MEMCOMPARE(blank,
                        restoredEui64,
                        sizeof(EmberEUI64))) {
      // There is no restored EUI64, no action
    } else {
      // There is a restored EUI available, so use that.
      MEMCOPY(eui64, restoredEui64, sizeof(EmberEUI64));
    }
  }
}

#endif // SL_CATALOG_ZIGBEE_STACK_UNIX_PRESENT
