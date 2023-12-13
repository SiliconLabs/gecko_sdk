/***************************************************************************//**
 * @file
 * @brief Implementation of additional key functionality that is
 * necessary for a Full Zigbee Pro Stack.  This includes things
 * like setting and getting the Trust Center Master Key, and
 * sending and processing Requests for Keys.
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

#include "core/ember-multi-network.h"
#include "stack/include/ember-types.h"
#include "hal/hal.h"
#include "include/error.h"
#include "aps-keys-full.h"

#include "stack/include/cbke-crypto-engine.h"
#include "stack/include/zigbee-security-manager.h"

extern void sli_zigbee_request_key_timeout_control(bool start, bool useBdbTimeoutValues);
extern bool sli_zigbee_is_token_data_initialized(uint8_t* data, uint8_t length);
extern uint32_t sli_zigbee_get_aps_frame_counter(void);
extern bool sli_zigbee_is_null_key(EmberKeyData * key);
extern bool sli_zigbee_get_trust_center_eui64(EmberEUI64 address);
extern bool sli_zigbee_are_keys_authorized_by_default(void);

const EmberLibraryStatus sli_zigbee_security_link_keys_library_status =
  EMBER_LIBRARY_PRESENT_MASK;

//------------------------------------------------------------------------------
// Forward Declarations

//------------------------------------------------------------------------------
// The link key table.

void sli_zigbee_aps_security_read_frame_counters(void)
{
  MEMSET(sli_zigbee_incoming_aps_frame_counters,
         0x0,
         emberKeyTableSize * sizeof(uint32_t));
}

// Copy the indicated key.  Returns false on bad index or no valid key data.
// Note: this no longer fills in result->keyData. ZB SM will fill that, grabbing
// the key from either tokens or PSA

EmberStatus sli_zigbee_get_key_table_entry(uint8_t index, EmberKeyStruct *result)
{
  tokTypeStackKeyTable tok;

  if (emberKeyTableSize <= index) {
    return EMBER_INDEX_OUT_OF_RANGE;
  }

  halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, index);

  if ( !sli_zigbee_is_token_data_initialized(&(tok[KEY_ENTRY_IEEE_OFFSET]),
                                             EUI64_SIZE + EMBER_ENCRYPTION_KEY_SIZE) ) {
    return EMBER_TABLE_ENTRY_ERASED;
  }

  MEMMOVE(result->partnerEUI64,
          &(tok[KEY_ENTRY_IEEE_OFFSET]),
          EUI64_SIZE);
  result->bitmask = EMBER_KEY_HAS_PARTNER_EUI64;

  if ((tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_AUTHORIZED_KEY_MASK)
      != KEY_TABLE_UNAUTHORIZED_KEY) {
    result->bitmask |= EMBER_KEY_IS_AUTHORIZED;
  }
  if (tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_SLEEPY_END_DEVICE) {
    result->bitmask |= EMBER_KEY_PARTNER_IS_SLEEPY;
  }
  if (tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_SYMMETRIC_PASSPHRASE) {
    result->bitmask |= EMBER_KEY_IS_AUTHENTICATION_TOKEN;
  }

  if ( (tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_TYPE_MASK)
       == KEY_TABLE_TYPE_LINK_KEY ) {
    result->type = EMBER_APPLICATION_LINK_KEY;
    result->incomingFrameCounter = sli_zigbee_incoming_aps_frame_counters[index];
    result->outgoingFrameCounter = sli_zigbee_get_aps_frame_counter();
    result->bitmask |= (EMBER_KEY_HAS_INCOMING_FRAME_COUNTER
                        | EMBER_KEY_HAS_OUTGOING_FRAME_COUNTER);
  } else {
    return EMBER_KEY_INVALID;
  }

  if (tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_ENTRY_HAS_PSA_ID) {
    result->bitmask |= EMBER_KEY_HAS_PSA_ID;
  }

  return EMBER_SUCCESS;
}

uint8_t sli_zigbee_find_key_table_entry(EmberEUI64 address, bool linkKey, uint8_t bitmask)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  context.flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

  if (!linkKey) {
    return EMBER_INVALID_CALL;
  }

  uint8_t i;
  EmberEUI64 NULL_EUI = { 0, 0, 0, 0, 0, 0, 0, 0 };
  bool lookForEmptyEntry =
    (address == NULL
     || (0 == MEMCOMPARE(address, NULL_EUI, EUI64_SIZE)));

  for ( i = 0; i < emberKeyTableSize; i++) {
    tokTypeStackKeyTable tok;
    //Set token to some invalid initial value
    memset(&tok, 0xFF, sizeof (tok));

    uint8_t tokenBitmask;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, i);
    tokenBitmask = tok[KEY_ENTRY_INFO_OFFSET];

    //Check if token read was unsuccessful and assert
    if ( tokenBitmask == 0xFF ) {
      assert(false);
    }

    if (lookForEmptyEntry) {
      if (!sli_zigbee_is_token_data_initialized(&tok[KEY_ENTRY_IEEE_OFFSET], EUI64_SIZE)) {
        return i;
      }
    } else {
      context.key_index = i;
      status = sl_zb_sec_man_check_key_context(&context);

      if ((0 == MEMCOMPARE(&tok[KEY_ENTRY_IEEE_OFFSET],
                           address,
                           EUI64_SIZE))
          && ((status == SL_STATUS_OK))
          && ((tokenBitmask & KEY_TABLE_TYPE_MASK) == KEY_TABLE_TYPE_LINK_KEY)
          && ((bitmask == 0xFF) || (bitmask == 0 && !(tokenBitmask & KEY_TABLE_SYMMETRIC_PASSPHRASE)) || (bitmask != 0 && (bitmask & tokenBitmask) == bitmask))  // match bitmask only if bitmask is valid
          && sli_zigbee_get_key_entry_network_index(tokenBitmask) == sli_zigbee_get_current_network_index()) { // search only for those keys with the correct nwk index
        return i;
      }
    }
  }
  return 0xFF;
}

// This function searches through the Key table to find an entry
// that has the same Address and key type as the passed value.
// If NULL is passed in for the address then it finds the first
// unused entry (type is ignored) and sets passed index.

uint8_t emberFindKeyTableEntry(EmberEUI64 address, bool linkKey)
{
  if (!linkKey) {
    return EMBER_INVALID_CALL;
  }

  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t key_data;

  status = sl_zb_sec_man_export_link_key_by_eui(address,
                                                &context,
                                                &plaintext_key,
                                                &key_data);
  if (status != SL_STATUS_OK) {
    return 0xFF;
  }
  return context.key_index;
}

EmberStatus emberEraseKeyTableEntry(uint8_t index)
{
  sl_status_t status;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  context.key_index = index;
  context.flags = ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;
  status = sl_zb_sec_man_delete_key(&context);

  return (status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_KEY_TABLE_INVALID_ADDRESS;
}

// If erase = true, only the 'index' parameter matters.  The rest may be 0.
EmberStatus sli_zigbee_af_set_key_table_entry(bool erase,
                                              uint8_t index,
                                              EmberKeyStruct* keyStruct)
{
  tokTypeStackKeyTable tok;

  if (emberKeyTableSize <= index) {
    return EMBER_INDEX_OUT_OF_RANGE;
  }

  if ( erase ) {
    MEMSET(&tok, 0, sizeof(tokTypeStackKeyTable));
  } else {
    EmberEUI64 tcAddress;
    uint8_t existingIndex = emberFindKeyTableEntry(keyStruct->partnerEUI64, KEY_TABLE_TYPE_LINK_KEY);
    if ( emberIsLocalEui64(keyStruct->partnerEUI64)
         || (existingIndex != 0xFF && existingIndex != index) ) {
      EmberKeyStruct duplicate;
      (void) sli_zigbee_get_key_table_entry(existingIndex, &duplicate);
      // NOTE however we make an exception if one (and only one) of them is an authentication token
      if (!((duplicate.bitmask ^ keyStruct->bitmask) & EMBER_KEY_IS_AUTHENTICATION_TOKEN)) {
        // Don't allow an application to setup a key in the table with
        // a duplicate address of another entry (which is not this one).
        return EMBER_KEY_TABLE_INVALID_ADDRESS;
      }
    }

    // NOTE non-tc devices will store their authentication token in the link key table
    if (!(keyStruct->bitmask & EMBER_KEY_IS_AUTHENTICATION_TOKEN)
        && sli_zigbee_get_trust_center_eui64(tcAddress)
        && (0 == MEMCOMPARE(keyStruct->partnerEUI64, tcAddress, EUI64_SIZE))) {
      // Standard Security:
      // Don't allow an application to setup a link key in the key
      // table to the TC.  If we are the TC, this doesn't make any sense.
      // If we are not the TC, the key table is for app keys.  We can't
      // have an app key with the TC (per the spec).

      return EMBER_KEY_TABLE_INVALID_ADDRESS;
    }
    MEMMOVE(&(tok[KEY_ENTRY_IEEE_OFFSET]), keyStruct->partnerEUI64, EUI64_SIZE);

    tok[KEY_ENTRY_INFO_OFFSET] = (KEY_TABLE_TYPE_LINK_KEY
                                  | (sli_zigbee_are_keys_authorized_by_default()
                                     ? 0
                                     : KEY_TABLE_UNAUTHORIZED_KEY)
                                  | (sli_zigbee_get_current_network_index() // set the nwk index
                                     << KEY_TABLE_TYPE_NETWORK_INDEX_OFFSET)
                                  | (keyStruct->bitmask & EMBER_KEY_IS_AUTHENTICATION_TOKEN
                                     ? KEY_TABLE_SYMMETRIC_PASSPHRASE : 0));
  }
  sli_zigbee_incoming_aps_frame_counters[index] = 0;
  halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, index, (void*)&tok);

  return EMBER_SUCCESS;
}

EmberStatus sli_zigbee_update_key_state(uint8_t index,
                                        uint8_t setFlags,
                                        uint8_t clearFlags)
{
  if (emberKeyTableSize <= index) {
    return EMBER_INDEX_OUT_OF_RANGE;
  } else {
    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, index);

    if (!sli_zigbee_is_token_data_initialized((uint8_t*)&tok, sizeof(tokTypeStackKeyTable))) {
      return EMBER_KEY_INVALID;
    }
    tok[KEY_ENTRY_INFO_OFFSET] &= (uint8_t) (~clearFlags);
    tok[KEY_ENTRY_INFO_OFFSET] |= setFlags;

    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, index, (void*)&tok);
  }
  return EMBER_SUCCESS;
}

void sli_zigbee_note_sleepy_device_in_key_table(EmberEUI64 eui64, bool sleepy)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_export_link_key_by_eui(eui64, &context, NULL, NULL);
  if (context.key_index != 0xFF) {
    sli_zigbee_update_key_note_end_device(context.key_index, sleepy);
  }
}

//------------------------------------------------------------------------------

bool sli_zigbee_process_application_link_key(EmberEUI64 partnerEui64,
                                             bool amInitiator,
                                             EmberKeyData* keyData)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;
  context.key_index = 0xFF;
  MEMMOVE(context.eui64, partnerEui64, sizeof(EmberEUI64));

  if (SL_STATUS_OK != sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t*) keyData)) {
    sli_zigbee_call_zigbee_key_establishment_handler(partnerEui64, EMBER_KEY_TABLE_FULL);
    return false;
  }

  if (context.key_index == 0xFF) {
    return false;
  }
  // Assume all Application keys sent by the Trust Center are authorized.
  sli_zigbee_update_key_authorization(context.key_index,
                                      true); // key is authorized

  sli_zigbee_call_zigbee_key_establishment_handler(partnerEui64,
                                                   EMBER_APP_LINK_KEY_ESTABLISHED);

  sli_zigbee_request_key_timeout_control(false, false);

  return true;
}

//------------------------------------------------------------------------------

// Clear all the entries belonging to the current network.
EmberStatus emberClearKeyTable(void)
{
  uint8_t i;
  for ( i = 0; i < emberKeyTableSize; i++) {
#if !defined(EMBER_MULTI_NETWORK_STRIPPED)
    tokTypeStackKeyTable tok;
    //Set token to some invalid initial value
    memset(&tok, 0xFF, sizeof (tok));

    uint8_t tokenBitmask;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, i);

    tokenBitmask = tok[KEY_ENTRY_INFO_OFFSET];

    //Check if token read was unsuccessful
    if ( tokenBitmask == 0xFF ) {
      assert(false);
    }

    if (sli_zigbee_get_key_entry_network_index(tokenBitmask) == sli_zigbee_get_current_network_index()) {
#endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)
    emberEraseKeyTableEntry(i);

    // closing bracket for MISRA Compliance
    #if !defined(EMBER_MULTI_NETWORK_STRIPPED)
  }
    #endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)
  }

  return EMBER_SUCCESS;
}
