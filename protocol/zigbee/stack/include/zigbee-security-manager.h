/***************************************************************************//**
 * @file
 * @brief Declarations of security-related APIs, including key storage, key
 *   fetching, and crypto operations. Keys are ultimately stored in secure
 *   storage for capable parts (like certain Series 2 chips) or in NVM3 tokens.
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

#ifndef _ZIGBEE_SECURITY_MANAGER_H_
#define _ZIGBEE_SECURITY_MANAGER_H_

#include "sl_status.h"
#include "stack/include/ember-types.h"
#include "stack/include/zigbee-security-manager-types.h"
#include "stack/include/zigbee-device-stack.h"
/**
 * @addtogroup zigbee_security_manager
 *
 * This file describes functionality for Zigbee security features. This
 * includes storing and fetching various keys, as well as invoking crypto
 * operations.
 *
 * See zigbee_security_manager.h for source code.
 * @{
 */

// CCM* operation defines
#ifndef DOXYGEN_SHOULD_SKIP_THIS
 #ifndef NONCE_LENGTH
  #define MESSAGE_LENGTH_FIELD_SIZE (2)
  #define NONCE_LENGTH (15 - MESSAGE_LENGTH_FIELD_SIZE)
  #define ENCRYPTION_BLOCK_SIZE (16)
 #endif // NONCE_LENGTH
#endif // DOXYGEN_SHOULD_SKIP_THIS

/** @brief This routine will initialize a Security Manager context correctly for use in subsequent function calls.
 *
 */
void sl_zb_sec_man_init_context(sl_zb_sec_man_context_t* context);

/** @brief Import a key into storage. Certain keys are
 * indexed, while others are not, as described here.<br>
 * If context->core_key_type is..<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_NETWORK, then context->key_index dictates whether to
 * import the current (active) network key (index 0) or the alternate network
 * key (index 1).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT, then context->eui64 must be
 * set. context->key_index is unused.<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK, then context->key_index determines which
 * index in the persisted key table that the entry should be stored to.
 * context->eui64 must also be set.
 * If context->key_index is 0xFF, a suitable key index will be found (either one
 * storing an existing key with address of context->eui64, or an open entry),
 * and context->key_index will be updated with where the entry was stored. <br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY or
 * SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY, then context->key_index
 * dictates which key entry to import. These Green Power keys are indexed keys,
 * and there are EMBER_GP_PROXY_TABLE_SIZE/EMBER_GP_SINK_TABLE_SIZE many of them.<br>
 *<br>
 * For all other key types, both context->key_index and context->eui64 are not
 * used.<br>
 *<br>
 * @param context [IN] The context to set. The context dictates which key type
 * to save, key_index (if applicable) into the relevant key storage, eui64 (if
 * applicable), etc.
 * @param plaintext_key [IN] The key to import.
 *
 * @note The context->derived_type must be SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE,
 * else, an error will be thrown. Key derivations, which are used in crypto
 * operations, are performed using the ::sl_zb_sec_man_load_key_context routine.
 *
 * @return SL_STATUS_OK upon success, a valid error code otherwise.
 */
sl_status_t sl_zb_sec_man_import_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);

/** @brief Import a link key, or SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK
 * key, into storage.
 *
 * @param index [IN] The index to set or overwrite in the key table for keys of
 * type SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK.  If index is set to 0xFF (255), then
 * the key will either overwrite whichever key table entry has an EUI of address
 * (if one exists) or write to the first available key table entry.  The index
 * that the key was placed into will not be returned by this API.
 * @param address [IN] The EUI belonging to the key.
 * @param plaintext_key [IN] A pointer to the key to import.
 *
 * @return SL_STATUS_OK upon success, a valid error code otherwise.
 *
 */
sl_status_t sl_zb_sec_man_import_link_key(uint8_t index,
                                          EmberEUI64 address,
                                          sl_zb_sec_man_key_t* plaintext_key);

/** @brief Export an APS link key by index.
 *
 */
sl_status_t sl_zb_sec_man_export_link_key_by_index(uint8_t index,
                                                   sl_zb_sec_man_context_t* context,
                                                   sl_zb_sec_man_key_t* plaintext_key,
                                                   sl_zb_sec_man_aps_key_metadata_t* key_data);

/** @brief Search through the Key table to find an entry
 * that has the same EUI address as the passed value.
 * If NULL is passed in for the address then it finds the first
 * unused entry and sets the index in the context.
 * It is valid to pass in NULL to plaintext_key or key_data in case
 * the index of the referenced key is desired but not its value or
 * other metadata.
 */
sl_status_t sl_zb_sec_man_export_link_key_by_eui(EmberEUI64 eui,
                                                 sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key,
                                                 sl_zb_sec_man_aps_key_metadata_t* key_data);

/** @brief Return true if a link key is available for securing messages
 * sent to the remote device.
 * This function simply checks for the existence of a key, it doesn't care if the key is authorized or not.
 * This function searches in a few different places, and it may always return true if certain bits/policies are set.
 * E.g: On trust center, this function always returns true if hashed link keys are used
 * (EMBER_TRUST_CENTER_USES_HASHED_LINK_KEY), or if EMBER_TRUST_CENTER_GLOBAL_LINK_KEY is set.
 *
 * @param eui The long address of some other device in the network.
 * @return bool Returns true if a link key can be retrieved/computed for securing messages sent to the remote EUI
 * passed as argument.  Returns false if a link key is not available for that EUI.
 */
bool sl_zb_sec_man_have_link_key(EmberEUI64 eui);

/**
 * @brief Add a transient or temporary key entry to key storage.
 * A key entry added with this API is timed out after
 * ::EMBER_TRANSIENT_KEY_TIMEOUT_S seconds, unless the key entry was added using
 * the Network Creator Security component, in which case the key will time out
 * after the longer between
 * ::EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_NETWORK_OPEN_TIME_S seconds and
 * ::EMBER_TRANSIENT_KEY_TIMEOUT_S seconds.
 *
 * @param eui64 [IN] An EmberEUI64 to import.
 * @param key [IN] A sl_zb_sec_man_key_t* to import.
 *
 * @return See ::zb_sec_man_import_transient_key for return information.
 */
#define sl_zb_sec_man_import_transient_key(eui64, key) zb_sec_man_import_transient_key(eui64, key, ZB_SEC_MAN_FLAG_NONE)

/**
 * @brief Search for a transient, or temporary, key
 * entry from key storage by EUI.
 *
 * @param eui64 [IN] The EUI to search for.
 * @param context [OUT] The context about the key, filled in upon success.
 * @param plaintext_key [OUT] If the security configuration allows for it, filled in
 *  with the key contents upon success.
 * @param key_data [OUT] Filled in with metadata about the key upon success.
 *
 * @return sl_status_t SL_STATUS_OK upon success, SL_STATUS_NOT_FOUND otherwise.
 */
sl_status_t sl_zb_sec_man_export_transient_key_by_eui(EmberEUI64 eui64,
                                                      sl_zb_sec_man_context_t* context,
                                                      sl_zb_sec_man_key_t* plaintext_key,
                                                      sl_zb_sec_man_aps_key_metadata_t* key_data);

/**
 * @brief Search for a transient, or temporary, key
 * entry from key storage by key index.
 *
 * @param index [IN] The key_index to fetch.
 * @param context [OUT] The context about the key, filled in upon success.
 * @param plaintext_key [OUT] If the security configuration allows for it, filled in
 *  with the key contents upon success.
 * @param key_data [OUT] Filled in with metadata about the key upon success.
 *
 * @return sl_status_t SL_STATUS_OK upon success, SL_STATUS_NOT_FOUND otherwise.
 */
sl_status_t sl_zb_sec_man_export_transient_key_by_index(uint8_t index,
                                                        sl_zb_sec_man_context_t* context,
                                                        sl_zb_sec_man_key_t* plaintext_key,
                                                        sl_zb_sec_man_aps_key_metadata_t* key_data);

/** @brief Export a key from storage. Certain keys are
 * indexed, while others are not, as described here.<br>
 * If context->core_key_type is..<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_NETWORK, then context->key_index dictates whether to
 * export the current (active) network key (index 0) or the alternate network
 * key (index 1).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK, then context->eui64 is checked if
 * context->flags is set to ZB_SEC_MAN_FLAG_EUI_IS_VALID. If the EUI supplied
 * does not match the TC EUI stored on the local device (if it is known), then
 * an error is thrown.<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT, then keys may be searched by
 * context->eui64 or context->key_index. context->flags determines how to search
 * (see ::sl_zigbee_sec_man_flags_t).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK, then keys may be searched by
 * context->eui64 or context->key_index. context->flags determines how to search
 * (see ::sl_zigbee_sec_man_flags_t).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY or
 * SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY, then context->key_index
 * dictates which key entry to export. These Green Power keys are indexed keys,
 * and there are EMBER_GP_PROXY_TABLE_SIZE/EMBER_GP_SINK_TABLE_SIZE many of them.<br>
 *<br>
 * For all other key types, both context->key_index and context->eui64 are not
 * used.<br>
 *<br>
 * @param context [IN/OUT] The context to set. The context dictates which key
 * type to export, which key_index (if applicable) into the relevant key
 * storage, which eui64 (if applicable), etc.
 * @param plaintext_key [OUT] The key to export.
 *
 * @note The context->derived_type must be SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE.
 * Other values are ignored.
 *
 * @return SL_STATUS_OK upon success, a valid error code otherwise.
 */
sl_status_t sl_zb_sec_man_export_key(sl_zb_sec_man_context_t* context,
                                     sl_zb_sec_man_key_t* plaintext_key);

/**
 * @brief Search for a transient, or temporary, key
 * and deletes it from key storage. Keys can be searched by EUI or key_index
 * based on context->flags (see ::ZB_SEC_MAN_FLAG_EUI_IS_VALID and
 * ::ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID).
 *
 * @param context [IN] The context to use to look up a key entry.
 * If the ZB_SEC_MAN_FLAG_EUI_IS_VALID flag is set in context->flags, then
 * the context->eui field is used to search for and delete the key.
 * If the ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID flag is set in context->flags, then
 * the context->key_index field is used to search for and delete the key.
 *
 * @return sl_status_t SL_STATUS_OK upon success, an error code otherwise.
 */
sl_status_t sl_zb_sec_man_delete_transient_key(sl_zb_sec_man_context_t* context);

/**
 * @brief Delete the key table entry, or a key of type
 * SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK, from storage. Keys can be searched by EUI or
 * key_index based on context->flags (see ::ZB_SEC_MAN_FLAG_EUI_IS_VALID and
 * ::ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID).
 *
 * @param context [IN] The context to use to look up a key entry.
 * If the ZB_SEC_MAN_FLAG_EUI_IS_VALID flag is set in context->flags, then
 * the context->eui field is used to search for and delete the key.
 * If the ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID flag is set in context->flags, then
 * the context->key_index field is used to search for and delete the key.
 *
 * @return sl_status_t SL_STATUS_OK upon success, an error code otherwise.
 */
sl_status_t sl_zb_sec_man_delete_key_table_key(sl_zb_sec_man_context_t* context);

/**
 * @brief Check that the passed key exists and can be successfully loaded.
 * This function does not actually load the context, but only checks that it can be loaded.
 *
 * @param context [IN] The context to check for validity. The fields that must be set depend
 * on the key type set in the context, as enough information is needed to identify the key.
 *
 * @return sl_status_t SL_STATUS_OK upon success, SL_STATUS_NOT_FOUND otherwise.
 */
sl_status_t sl_zb_sec_man_check_key_context(sl_zb_sec_man_context_t* context);

/**
 * @brief Retrieve information about the network key and alternate network key.
 * It will not retrieve the actual network key contents.
 *
 * @param network_key_info [OUT] The network key info struct used to store network key metadata,
 * containing information about whether the current and next network keys are set, and the
 * sequence numbers associated with each key.
 *
 * @return sl_status_t SL_STATUS_OK
 *
 */
sl_status_t sl_zb_sec_man_get_network_key_info(sl_zb_sec_man_network_key_info_t* network_key_info);

/** @brief Retrieve metadata about an APS key.
 * It does not retrieve the actual key contents.
 *
 * @param context [IN/OUT] The context to use to look up a key entry. If the
 *  user calls this function with the ::ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID bit
 *  set in the context->flag field, then the key_index field in the context
 *  argument dictates which entry to retrieve. For keys with timeout and
 *  application link keys, the key_index retrieves the indexed entry into the
 *  respective table. Upon success, the eui64 field in the context is updated.
 *  If the user calls this function with the
 *  ::ZB_SEC_MAN_FLAG_EUI_IS_VALID bit set in the
 *  context->flag field, then the eui64 field in the context argument
 *  dictates which entry to retrieve. If the context->core_key_type argument is
 *  set to SL_ZB_SEC_MAN_KEY_TYPE_NETWORK, an error is returned as network keys
 *  are not tied to any specific EUI.
 *  If neither the ::ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID bit nor the
 *  ::ZB_SEC_MAN_FLAG_EUI_IS_VALID bit is set in context->flags, then an error
 *  will be returned by this function.
 *  Upon success in fetching a key, the other fields in this argument are
 *  updated (e.g. a successful search by key_index will update the euii64
 *  field).
 *
 * @param key_data [OUT] Metadata to fill in.
 *
 * @return SL_STATUS_OK if successful, SL_STATUS_NOT_FOUND if
 *  the key_index or eui64 does not result in a found entry,
 *  SL_STATUS_INVALID_TYPE if the core key type is not an APS layer key (e.g.
 *  SL_ZB_SEC_MAN_KEY_TYPE_NETWORK), or SL_STATUS_INVALID_MODE if core_key_type
 *  is SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK and the initial security state does not
 *  indicate the a preconfigured key has been set (that is, both
 *  EMBER_HAVE_PRECONFIGURED_KEY and
 *  EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE have not been set in the
 *  initial security state).
 */
sl_status_t sl_zb_sec_man_get_aps_key_info(sl_zb_sec_man_context_t* context,
                                           sl_zb_sec_man_aps_key_metadata_t* key_data);

/** @brief Delete a key from storage. Certain keys are
 * indexed, while others are not, as described here.<br>
 * If context->core_key_type is..<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_NETWORK, then context->key_index dictates whether to
 * delete the current (active) network key (index 0) or the alternate network
 * key (index 1).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT, then keys may be searched by
 * context->eui64 or context->key_index. context->flags determines how to search
 * (see ::sl_zigbee_sec_man_flags_t).<br>
 * ..SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK, then keys may be searched by
 * context->eui64 or context->key_index. context->flags determines how to search
 * (see ::sl_zigbee_sec_man_flags_t).<br>
 * * ..SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY or
 * SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY, then context->key_index
 * dictates which key entry to delete. These Green Power keys are indexed keys,
 * and there are EMBER_GP_PROXY_TABLE_SIZE/EMBER_GP_SINK_TABLE_SIZE many of them.<br>
 *<br>
 * For all other key types, both context->key_index and context->eui64 are not
 * used.<br>
 *<br>
 * @param context [IN] The context to use to look up a key.
 *
 * @return sl_status_t SL_STATUS_OK upon success, an error code otherwise.
 */
sl_status_t sl_zb_sec_man_delete_key(sl_zb_sec_man_context_t* context);

/**
 * @brief Load the specified key into the Security Manager's
 * internal context.
 * Any subsequent crypto operations will be done with that loaded context.
 *
 * @param context [IN] The context to use to look up which key to load.
 * If the derived key type is not SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE, then an
 * appropriate key derivation scheme is applied to the key fetched according to
 * the context supplied.
 *
 * @note Enough information must be passed into context to properly identify the
 * requested key, which is dependent on the key type requested. See
 * ::sl_zb_sec_man_export_key for the requirements of the context argument based
 * on core_key_type.
 *
 * @return SL_STATUS_OK upon success, an error code otherwise.
 */
sl_status_t sl_zb_sec_man_load_key_context(sl_zb_sec_man_context_t* context);

/**
 * @brief Using a previously set key context, the Security Manager will perform
 * an HMAC (keyed hash) using AES-MMO as the hashing algorithm, and AES-128 for
 * the underlying block encryption.
 *
 * @param input [IN] Data to be hashed.  The keyed part of the keyed hash comes
 * from the previously loaded context, so only data is input here.
 *
 * @param data_length [IN] Length of the data to be hashed.
 *
 * @param output [OUT] Hashed data.
 *
 */
void sl_zb_sec_man_hmac_aes_mmo(const uint8_t* input,
                                const uint8_t data_length,
                                uint8_t* output);

/**
 * @brief Encrypt the specified data using AES-CCM with AES-128 and a MIC of the requested length (in  * bytes).  See documentation for sl_zb_sec_ * man_aes_ccm for information on parameters besides mic_length.
 *
 * @param mic_length [IN] Length of the MIC to output.  Currently supported MIC lengths are 4 bytes
 * and 8 bytes.
 *
 */
sl_status_t sl_zb_sec_man_aes_ccm_extended(uint8_t* nonce,
                                           bool encrypt,
                                           const uint8_t* input,
                                           uint8_t encryption_start_index,
                                           uint8_t length,
                                           uint8_t mic_length,
                                           uint8_t* output);

/**
 * @brief Encrypt the specified data using AES-CCM with AES-128 and a 4-byte MIC.
 *
 * @param nonce [IN] Nonce value used as part of CCM* encryption.
 *
 * @param encrypt [IN] Encryption/decryption mode.  True if encrypting, false for authenticated
 * decryption.  True when using this function for unauthenticated decryption (decrypt
 * bytes in input and do not verify the end of input as a MIC).
 *
 * @param input [IN] Input to the CCM* encryption operation.  The function assumes this is in packet
 * format, where authenticated data begins at the location pointed to by input, and is followed by
 * authenticated data.  For authenticated decryption, the MIC is assumed to be located following the
 * encrypted data.
 *
 * @param encryption_start_index [IN] Length of the authenticated data, equivalent to the index in
 * input where data to be encrypted/decrypted begins.
 *
 * @param length [IN] Total length of authenticated + encrypted data.
 *
 * @param output [OUT] Output to the CCM* operation. When encrypt is true, this must have space for
 * the input length plus a 4-byte MIC.  For authenticated decryption, it must have size at least as
 * large as the input length.
 *
 */
#define sl_zb_sec_man_aes_ccm(nonce, encrypt, input, encryption_start_index, length, output) \
  sl_zb_sec_man_aes_ccm_extended(nonce, encrypt, input, encryption_start_index, length, 4, output)

/**
 * @brief Perform AES-128 crypto on the specified 16-byte block using a previously loaded context.
 *
 * @param encrypt [IN] true if encrypting, else decrypt
 *
 * @param input [IN] Input, expected to be 16 bytes long.
 *
 * @param output [OUT] Output of the AES-128 encryption operation.
 *
 */
sl_status_t sl_zb_sec_man_aes_128_crypt_block(bool encrypt,
                                              const uint8_t* input,
                                              uint8_t* output);

// Symmetric Passphrase functions

/** @brief Finds the Link Key Table index of the symmetric passphase of the given device EUI64.
 *
 * This function will return the Link Key Table index of the symmetric passphase of the given
 * device EUI64, and will return 0xFF if no matching symmetric passphrase is found.
 *
 * @param address EUI64 of device
 *
 * @return An uint8_t value that indicates the index of the stored symmetric passphrase
 * in the link key table.
 */
uint8_t sl_zb_sec_man_find_symmetric_passphrase_key_table_index(EmberEUI64 address);

/** @brief Imports the symmetric passphrase to the Link Key Table.
 *
 * This function will use Security Manager methods to store the given symmetric
 * passphrase in the Link Key Table at the given index with matching EUI64.
 *
 * @param erase whether to erase the key at the given index with matching address
 * @param index Link Key Table index to store symmetric passphrase
 * @param address device EUI64
 * @param key_data pointer to symmetric passphrase memory
 *
 * @return An ::EmberStatus value that indicates the success or failure of
 * importing the symmetric passphrase into the Link Key Table.
 */
sl_status_t sl_zb_sec_man_import_symmetric_passphrase(uint8_t index,
                                                      EmberEUI64 address,
                                                      EmberKeyData* key_data);

/** @brief Exports the symmetric passphrase from the Link Key Table.
 *
 * This function will use Security Manager methods to export the given symmetric
 * passphrase from the Link Key Table matching EUI64.
 *
 * @param address device EUI64
 * @param key_data pointer to symmetric passphrase memory
 *
 * @return An ::EmberStatus value that indicates the success or failure of
 * exporting the symmetric passphrase into the Link Key Table.
 */
sl_status_t sl_zb_sec_man_export_symmetric_passphrase(EmberEUI64 address,
                                                      EmberKeyData* key_data);

/** @brief Updates the device address of a symmetric passphrase entry.
 *
 * This function will update the device address of a symmetric passphrase entry
 * in the Link Key Table that matches the given old device address with the new
 * device address.
 *
 * @param old_eui64 Old device address
 * @param new_eui64 New device address
 *
 * @return An ::EmberStatus value that indicates the success or failure of
 * updating the Link Key Table entry's device EUI64
 */
sl_status_t sl_zb_sec_man_update_symmetric_passphrase_eui(EmberEUI64 old_eui64,
                                                          EmberEUI64 new_eui64);

/**
 * @brief Returns whether a Symmetric Passphrase can be stored
 *
 * The determination of whether a new Symmetric Passphrase can be stored is made
 * by checking if one already exists inside the key table with the same EUI64
 *
 * @param address device address
 * @return a boolean representing whether a Symmetric Passphrase can be stored
 */
#define sl_zb_sec_man_symmetric_passphrase_update_allowed(address) \
  (sl_zb_sec_man_find_symmetric_passphrase_key_table_index(address) == 0xFF)

/**
 * @brief Checks whether a new link key with a device can be stored.
 *
 * @param eui64 device address
 * @return True if a new link key could be stored (there is either an
 * existing entry with this device's EUI64 or a free entry for a new device),
 * false if not (table is full).
 */
bool sl_zigbee_sec_man_link_key_slot_available(EmberEUI64 eui64);

/**
 * @brief Check whether the key referenced by a given context has a specified value.
 * This API is only compatible with keys that permit the standard Zigbee encryption algorithm
 * and have a core key type that is not SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL.
 *
 * @param context Reference to the key being checked
 * @param test_key Value to test for
 *
 * @return True if the key referenced by context has the value test_key, false otherwise.
 */
bool sl_zb_sec_man_compare_key_to_value(sl_zb_sec_man_context_t* context, const sl_zb_sec_man_key_t* test_key);

// Internal APIs
#ifndef DOXYGEN_SHOULD_SKIP_THIS
sl_status_t zb_sec_man_import_transient_key(EmberEUI64 eui64,
                                            sl_zb_sec_man_key_t* plaintext_key,
                                            sl_zigbee_sec_man_flags_t flags);

void zb_sec_man_set_network_key_info(sl_zb_sec_man_network_key_info_t* network_key_info);

void sl_zb_sec_man_set_context_aes_ecb_alg(sl_zb_sec_man_context_t* context);
void sl_zb_sec_man_set_context_extended_ccm_alg(sl_zb_sec_man_context_t* context);

//Used by EZSP so hosts can retrieve information about the NCP's key storage.
//Implemented as its own NCP function because the EZSP command handler calling
//it can be built in libraries, which won't have the SL catalog defines present
//to make a correct decision on what the value of ZB_SEC_MAN_VERSION should be.
uint8_t zb_sec_man_version(void);
//VERSION 0:  No PSA storage
//VERSION 1:  PSA storage present
#if defined (SL_CATALOG_ZIGBEE_SECURE_KEY_STORAGE_PRESENT)
#define ZB_SEC_MAN_VERSION 1
#else
#define ZB_SEC_MAN_VERSION 0
#endif

//wrapper macros for EZSP frame usage (map calls from autogenerated code to the actual handler).
//Any other code should be calling the sl_zb_sec_man APIs directly.

#define emberImportKey sl_zb_sec_man_import_key

#define emberInitSecurityManagerContext sl_zb_sec_man_init_context

#define emberExportKey(context, key, status) \
  status = sl_zb_sec_man_export_key(context, key);

#define emberGetNetworkKeyInfo sl_zb_sec_man_get_network_key_info

#define emberGetApsKeyInfo(context, eui, key_metadata, status)      \
  do {                                                              \
    status = sl_zb_sec_man_get_aps_key_info(context, key_metadata); \
    MEMMOVE(eui, context.eui64, EUI64_SIZE);                        \
  } while (0)

#define emberImportLinkKey sl_zb_sec_man_import_link_key
#define emberCheckKeyContext sl_zb_sec_man_check_key_context
#define emberImportTransientKey zb_sec_man_import_transient_key

#define emberExportLinkKeyByIndex(index, eui, plaintext_key, key_data, status)                 \
  do {                                                                                         \
    sl_zb_sec_man_context_t context;                                                           \
    status = sl_zb_sec_man_export_link_key_by_index(index, &context, plaintext_key, key_data); \
    MEMMOVE(eui, context.eui64, EUI64_SIZE);                                                   \
  } while (0)

#define emberExportLinkKeyByEui(eui, plaintext_key, index, key_data, status)               \
  do {                                                                                     \
    sl_zb_sec_man_context_t context;                                                       \
    status = sl_zb_sec_man_export_link_key_by_eui(eui, &context, plaintext_key, key_data); \
    index = context.key_index;                                                             \
  } while (0)

#define emberExportTransientKeyByIndex(index, context, plaintext_key, key_data, status) \
  status = sl_zb_sec_man_export_transient_key_by_index(index, context, plaintext_key, key_data);

#define emberExportTransientKeyByEui(eui, context, plaintext_key, key_data, status) \
  status = sl_zb_sec_man_export_transient_key_by_eui(eui, context, plaintext_key, key_data);

#endif // DOXYGEN_SHOULD_SKIP_THIS

/** @} END addtogroup */

#endif /* _ZIGBEE_SECURITY_MANAGER_H_ */
