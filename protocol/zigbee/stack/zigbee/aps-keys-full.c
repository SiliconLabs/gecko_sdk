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

extern void emRequestKeyTimeoutControl(bool start, bool useBdbTimeoutValues);
extern bool emIsTokenDataInitialized(uint8_t* data, uint8_t length);
extern uint32_t emGetApsFrameCounter(void);
extern bool emIsNullKey(EmberKeyData * key);
extern bool emGetTrustCenterEui64(EmberEUI64 address);
extern bool emAreKeysAuthorizedByDefault(void);

const EmberLibraryStatus emSecurityLinkKeysLibraryStatus =
  EMBER_LIBRARY_PRESENT_MASK;

//------------------------------------------------------------------------------
// Forward Declarations

//------------------------------------------------------------------------------
// The link key table.

void emApsSecurityReadFrameCounters(void)
{
  MEMSET(emIncomingApsFrameCounters,
         0x0,
         emberKeyTableSize * sizeof(uint32_t));
}

// Copy the indicated key.  Returns false on bad index or no valid key data.
// Note: this no longer fills in result->keyData. ZB SM will fill that, grabbing
// the key from either tokens or PSA

EmberStatus emGetKeyTableEntry(uint8_t index, EmberKeyStruct *result)
{
  tokTypeStackKeyTable tok;

  if (emberKeyTableSize <= index) {
    return EMBER_INDEX_OUT_OF_RANGE;
  }

  halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, index);

  if ( !emIsTokenDataInitialized(&(tok[KEY_ENTRY_IEEE_OFFSET]),
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

  if ( (tok[KEY_ENTRY_INFO_OFFSET] & KEY_TABLE_TYPE_MASK)
       == KEY_TABLE_TYPE_LINK_KEY ) {
    result->type = EMBER_APPLICATION_LINK_KEY;
    result->incomingFrameCounter = emIncomingApsFrameCounters[index];
    result->outgoingFrameCounter = emGetApsFrameCounter();
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

uint8_t emFindKeyTableEntry(EmberEUI64 address, bool linkKey)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t key_data;

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
      if (!emIsTokenDataInitialized(&tok[KEY_ENTRY_IEEE_OFFSET], EUI64_SIZE)) {
        return i;
      }
    } else {
      status = sl_zb_sec_man_export_link_key_by_index(i,
                                                      &context,
                                                      &plaintext_key,
                                                      &key_data);

      if ((0 == MEMCOMPARE(&tok[KEY_ENTRY_IEEE_OFFSET],
                           address,
                           EUI64_SIZE))
          && ((status == SL_STATUS_OK) && !emIsNullKey((EmberKeyData *)plaintext_key.key))
          && ((tokenBitmask & KEY_TABLE_TYPE_MASK) == KEY_TABLE_TYPE_LINK_KEY)
          && emGetKeyEntryNetworkIndex(tokenBitmask) // search only for those
          == emGetCurrentNetworkIndex()) {       // keys with the correct nwk index
        return i;
      }
    }
  }
  return 0xFF;
}

EmberStatus emberGetKeyTableEntry(uint8_t index, EmberKeyStruct *result)
{
  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t key_data;

  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK;

  status = sl_zb_sec_man_export_link_key_by_index(index,
                                                  &context,
                                                  &plaintext_key,
                                                  &key_data);

  if (status != SL_STATUS_OK) {
    return EMBER_NOT_FOUND;
  }

  MEMMOVE(result->partnerEUI64, context.eui64, EUI64_SIZE);
  result->incomingFrameCounter = key_data.incoming_frame_counter;
  result->outgoingFrameCounter = key_data.outgoing_frame_counter;
  result->bitmask = key_data.bitmask;
  MEMMOVE(result->key.contents, plaintext_key.key, EMBER_ENCRYPTION_KEY_SIZE);

  return EMBER_SUCCESS;
}

EmberStatus emberAddOrUpdateKeyTableEntry(EmberEUI64 address,
                                          bool linkKey,
                                          EmberKeyData* keyData)
{
  if (!linkKey) {
    return EMBER_INVALID_CALL;
  }

  if (!KEY_TABLE_TYPE_LINK_KEY) {
    return EMBER_INVALID_CALL;
  }

  sl_status_t status;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t key_metadata;
  EmberEUI64 emptyEui;
  MEMSET(emptyEui, 0, sizeof(EmberEUI64));

  // Try to find the exact EUI first, so to update it
  status = sl_zb_sec_man_export_link_key_by_eui(address,
                                                &context,
                                                &plaintext_key,
                                                &key_metadata);

  // If we didn't find it, find a free entry
  if (status != SL_STATUS_OK) {
    status = sl_zb_sec_man_export_link_key_by_eui(emptyEui,
                                                  &context,
                                                  &plaintext_key,
                                                  &key_metadata);
  }

  if (status == SL_STATUS_OK) {
    status = sl_zb_sec_man_import_link_key(context.key_index,
                                           address,
                                           (sl_zb_sec_man_key_t*)keyData);
    return (status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_KEY_TABLE_INVALID_ADDRESS;
  }

  return EMBER_TABLE_FULL;
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

EmberStatus emberSetKeyTableEntry(uint8_t index,
                                  EmberEUI64 address,
                                  bool linkKey,
                                  EmberKeyData* keyData)
{
  sl_status_t status;
  status = sl_zb_sec_man_import_link_key(index, address, (sl_zb_sec_man_key_t*)keyData->contents);

  return (status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_KEY_TABLE_INVALID_ADDRESS;
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
EmberStatus emSetKeyTableEntry(bool erase,
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
      // Don't allow an application to setup a key in the table with
      // a duplicate address of another entry (which is not this one).
      return EMBER_KEY_TABLE_INVALID_ADDRESS;
    }

    if (emGetTrustCenterEui64(tcAddress)
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
                                  | (emAreKeysAuthorizedByDefault()
                                     ? 0
                                     : KEY_TABLE_UNAUTHORIZED_KEY)
                                  | (emGetCurrentNetworkIndex() // set the nwk index
                                     << KEY_TABLE_TYPE_NETWORK_INDEX_OFFSET));
  }
  emIncomingApsFrameCounters[index] = 0;
  halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, index, (void*)&tok);

  return EMBER_SUCCESS;
}

EmberStatus emUpdateKeyState(uint8_t index,
                             uint8_t setFlags,
                             uint8_t clearFlags)
{
  if (emberKeyTableSize <= index) {
    return EMBER_INDEX_OUT_OF_RANGE;
  } else {
    tokTypeStackKeyTable tok;
    halCommonGetIndexedToken(&tok, TOKEN_STACK_KEY_TABLE, index);

    if (!emIsTokenDataInitialized((uint8_t*)&tok, sizeof(tokTypeStackKeyTable))) {
      return EMBER_KEY_INVALID;
    }
    tok[KEY_ENTRY_INFO_OFFSET] &= (uint8_t) (~clearFlags);
    tok[KEY_ENTRY_INFO_OFFSET] |= setFlags;

    halCommonSetIndexedToken(TOKEN_STACK_KEY_TABLE, index, (void*)&tok);
  }
  return EMBER_SUCCESS;
}

void emNoteSleepyDeviceInKeyTable(EmberEUI64 eui64, bool sleepy)
{
  uint8_t index = emberFindKeyTableEntry(eui64, KEY_TABLE_TYPE_LINK_KEY);
  if (index != 0xFF) {
    emUpdateKeyNoteEndDevice(index, sleepy);
  }
}

//------------------------------------------------------------------------------

bool emProcessApplicationLinkKey(EmberEUI64 partnerEui64,
                                 bool amInitiator,
                                 EmberKeyData* keyData)
{
  uint8_t index;

  if ( EMBER_SUCCESS
       != emberAddOrUpdateKeyTableEntry(partnerEui64,
                                        KEY_TABLE_TYPE_LINK_KEY,
                                        keyData) ) {
    emCallZigbeeKeyEstablishmentHandler(partnerEui64, EMBER_KEY_TABLE_FULL);
    return false;
  }

  index = emberFindKeyTableEntry(partnerEui64, KEY_TABLE_TYPE_LINK_KEY);
  if (index == 0xFF) {
    return false;
  }
  // Assume all Application keys sent by the Trust Center are authorized.
  emUpdateKeyAuthorization(index,
                           true);  // key is authorized

  emCallZigbeeKeyEstablishmentHandler(partnerEui64,
                                      EMBER_APP_LINK_KEY_ESTABLISHED);

  emRequestKeyTimeoutControl(false, false);

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

    if (emGetKeyEntryNetworkIndex(tokenBitmask) == emGetCurrentNetworkIndex()) {
#endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)
    emberEraseKeyTableEntry(i);

    // closing bracket for MISRA Compliance
    #if !defined(EMBER_MULTI_NETWORK_STRIPPED)
  }
    #endif // !defined(EMBER_MULTI_NETWORK_STRIPPED)
  }

  return EMBER_SUCCESS;
}
