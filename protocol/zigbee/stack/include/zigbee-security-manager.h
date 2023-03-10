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

/** @brief The list of supported key types used by Zigbee Security Manager. */
enum {
  SL_ZB_SEC_MAN_KEY_TYPE_NONE,
  /** @brief This is the network key, used for encrypting and decrypting network
   * payloads.
   * There is only one of these keys in storage. */
  SL_ZB_SEC_MAN_KEY_TYPE_NETWORK,
  /** @brief This is the Trust Center Link Key. On the joining device, this is the APS
   * key used to communicate with the trust center. On the trust center, this
   * key can be used as a root key for APS encryption and decryption when
   * communicating with joining devices (if the security policy has the
   * EMBER_TRUST_CENTER_USES_HASHED_LINK_KEY bit set).
   * There is only one of these keys in storage. */
  SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK,
  /** @brief This is a Trust Center Link Key, but it times out after either
   * ::EMBER_TRANSIENT_KEY_TIMEOUT_S or
   * ::EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_NETWORK_OPEN_TIME_S (if
   * defined), whichever is longer. This type of key is set on trust centers
   * who wish to open joining with a temporary, or transient, APS key for
   * devices to join with. Joiners who wish to try several keys when joining a
   * network may set several of these types of keys before attempting to join.
   * This is an indexed key, and local storage can fit as many keys as
   * available RAM allows. */
  SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT,
  /** @brief This is an Application link key. On both joining devices and the trust
   * center, this key is used in APS encryption and decryption when
   * communicating to a joining device.
   * This is an indexed key table of size EMBER_KEY_TABLE_SIZE, so long as there
   * is sufficient nonvolatile memory to store keys. */
  SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK,
  /** @brief Key type used to store Secure EZSP keys */
  SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY,
  /** @brief This is the ZLL encryption key for use by algorithms that require it. */
  SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY,
  /** @brief For ZLL, this is the pre-configured link key used during classical ZigBee commissioning. */
  SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY,
  /** @brief This is a Green Power Device (GPD) key used on a Proxy device. */
  SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY,
  /** @brief This is a Green Power Device (GPD) key used on a Sink device. */
  SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY,
  /** @brief This is a generic key type intended to be loaded for one-time hashing or
   * crypto operations. This key is not persisted. */
  SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL
};
typedef uint8_t sl_zb_sec_man_key_type_t;

/** @brief Derived keys are calculated when performing Zigbee crypto operations. The stack
 * makes use of these derivations. */
enum {
  /** @brief Perform no derivation; use the key as is. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE = 0,
  /** @brief Perform the Key-Transport-Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_TRANSPORT_KEY = 1,
  /** @brief Perform the Key-Load-Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_LOAD_KEY = 2,
  /** @brief Perform the Verify Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_VERIFY_KEY = 3,
  /** @brief Perform a simple AES hash of the key for TC backup. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_SWAP_OUT_KEY = 4,
  /** @brief For a TC using hashed link keys, hashed the root key against the supplied EUI in context. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_HASHED_LINK_KEY = 5
};
typedef uint8_t sl_zb_sec_man_derived_key_type_t;

/**
 * @brief Security Manager context flags.
 */
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum sl_zigbee_sec_man_flags_t
#else
typedef uint8_t sl_zigbee_sec_man_flags_t;
enum
#endif
{
  ZB_SEC_MAN_FLAG_NONE                      = 0x00,
  /** @brief For export APIs, this flag indicates the key_index parameter is valid in
   *  the ::sl_zb_sec_man_context_t structure. This bit is set by the caller
   *  when intending to search for a key by key_index. This flag has no
   *  significance for import APIs. */
  ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID        = 0x01,
  /** @brief For export APIs, this flag indicates the eui64 parameter is valid in the
   *  ::sl_zb_sec_man_context_t structure. This bit is set by the caller when
   *  intending to search for a key by eui64. It is also set when searching by
   *  key_index and an entry is found. This flag has no significance for import
   *  APIs. */
  ZB_SEC_MAN_FLAG_EUI_IS_VALID              = 0x02,
  /** @brief Internal use only. This indicates that the transient key being added is an
   * unconfirmed, updated key. This bit is set when we add a transient key and
   * the ::EmberTcLinkKeyRequestPolicy policy
   * is ::EMBER_ALLOW_TC_LINK_KEY_REQUEST_AND_GENERATE_NEW_KEY, whose behavior
   * dictates that we generate a new, unconfirmed key, send it to the requester,
   * and await for a Verify Key Confirm message. */
  ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY = 0x04,
};

/** @brief This data structure houses the context when interacting with the Zigbee
 * Security Manager APIs. For example, when importing a key into storage, the various
 * fields of this structure are used to determine which type of key is being stored. */
typedef struct {
  sl_zb_sec_man_key_type_t core_key_type;
  uint8_t key_index;
  sl_zb_sec_man_derived_key_type_t derived_type;
  EmberEUI64 eui64;
  uint8_t multi_network_index;
  sl_zigbee_sec_man_flags_t flags;
} sl_zb_sec_man_context_t;

/** @brief This data structure contains the metadata pertaining to an network key */
typedef struct {
  bool network_key_set;
  bool alternate_network_key_set;
  uint8_t network_key_sequence_number;
  uint8_t alt_network_key_sequence_number;
} sl_zb_sec_man_network_key_info_t;

/** @brief This data structure contains the metadata pertaining to an APS key */
typedef struct {
  EmberKeyStructBitmask bitmask;
  uint32_t outgoing_frame_counter;  // valid only if bitmask & EMBER_KEY_HAS_OUTGOING_FRAME_COUNTER
  uint32_t incoming_frame_counter;  // valid only if bitmask & EMBER_KEY_HAS_INCOMING_FRAME_COUNTER
  uint16_t ttl_in_seconds;          // valid only if core_key_type == SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK_WITH_TIMEOUT
} sl_zb_sec_man_aps_key_metadata_t;

/** @brief This data structure contains the key data that is passed
 *   into various other functions. */
typedef struct {
  uint8_t key[EMBER_ENCRYPTION_KEY_SIZE];
} sl_zb_sec_man_key_t;

// CCM* operation defines
#ifndef DOXYGEN_SHOULD_SKIP_THIS
 #ifndef NONCE_LENGTH
  #define MESSAGE_LENGTH_FIELD_SIZE (2)
  #define NONCE_LENGTH (15 - MESSAGE_LENGTH_FIELD_SIZE)
  #define MIC_LENGTH (4)
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
 * context->eui64 must also be set.<br>
 * * ..SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY or
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
 * type SL_ZB_SEC_MAN_KEY_TYPE_APP_LINK.
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
 */
sl_status_t sl_zb_sec_man_export_link_key_by_eui(EmberEUI64 eui,
                                                 sl_zb_sec_man_context_t* context,
                                                 sl_zb_sec_man_key_t* plaintext_key,
                                                 sl_zb_sec_man_aps_key_metadata_t* key_data);

/** @brief Return true if a link key is available for securing messages
 * sent to the remote device.
 *
 * @param remoteDevice The long address of a some other device in the network.
 * @return bool Returns true if a link key is available.
 */
sl_status_t sl_zb_sec_man_have_link_key(EmberEUI64 eui);

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
 * @brief Encrypt the specified data using AES-CCM with AES-128 and a 32-bit MIC.
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
sl_status_t sl_zb_sec_man_aes_ccm(uint8_t* nonce,
                                  bool encrypt,
                                  const uint8_t* input,
                                  uint8_t encryption_start_index,
                                  uint8_t length,
                                  uint8_t* output);

// Internal APIs
#ifndef DOXYGEN_SHOULD_SKIP_THIS
sl_status_t zb_sec_man_import_transient_key(EmberEUI64 eui64,
                                            sl_zb_sec_man_key_t* plaintext_key,
                                            sl_zigbee_sec_man_flags_t flags);

void zb_sec_man_set_network_key_info(sl_zb_sec_man_network_key_info_t* network_key_info);
#endif // DOXYGEN_SHOULD_SKIP_THIS

/** @} END addtogroup */

#endif /* _ZIGBEE_SECURITY_MANAGER_H_ */
