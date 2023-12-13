/***************************************************************************//**
 * @file
 * @brief Declarations of types used by Zigbee Security Manager.
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
#ifndef _ZIGBEE_SECURITY_MANAGER_TYPES_H_
#define _ZIGBEE_SECURITY_MANAGER_TYPES_H_

/**
 * @addtogroup zigbee_security_manager
 *
 * This file describes type definitions used for Zigbee security features.
 *
 * See zigbee-security-manager-types.h for source code.
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
  /** @brief This is the ZLL encryption key for use by algorithms that require it. */
  SL_ZB_SEC_MAN_KEY_TYPE_ZLL_ENCRYPTION_KEY,
  /** @brief For ZLL, this is the pre-configured link key used during classical ZigBee commissioning. */
  SL_ZB_SEC_MAN_KEY_TYPE_ZLL_PRECONFIGURED_KEY,
  /** @brief This is a Green Power Device (GPD) key used on a Proxy device. */
  SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_PROXY_TABLE_KEY,
  /** @brief This is a Green Power Device (GPD) key used on a Sink device. */
  SL_ZB_SEC_MAN_KEY_TYPE_GREEN_POWER_SINK_TABLE_KEY,
  /** @brief This is a generic key type intended to be loaded for one-time hashing or
   * crypto operations. This key is not persisted.  Intended for use by the Zigbee stack. */
  SL_ZB_SEC_MAN_KEY_TYPE_INTERNAL
};
typedef uint8_t sl_zb_sec_man_key_type_t;

/** @brief Derived keys are calculated when performing Zigbee crypto operations. The stack
 * makes use of these derivations.
 * Compounding derivations can be specified by using an or-equals on two derived types if
 * applicable; this is limited to performing the key-transport, key-load, or verify-key hashes
 * on either the TC Swap Out or TC Hashed Link keys.*/
#ifdef DOXYGEN_SHOULD_SKIP_THIS
enum sl_zb_sec_man_derived_key_type_t
#else
typedef uint16_t sl_zb_sec_man_derived_key_type_t;
enum
#endif
{
  /** @brief Perform no derivation; use the key as is. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_NONE = 0x0000,
  /** @brief Perform the Key-Transport-Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_TRANSPORT_KEY = 0x0001,
  /** @brief Perform the Key-Load-Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_KEY_LOAD_KEY = 0x0002,
  /** @brief Perform the Verify Key hash. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_VERIFY_KEY = 0x0004,
  /** @brief Perform a simple AES hash of the key for TC backup. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_SWAP_OUT_KEY = 0x0008,
  /** @brief For a TC using hashed link keys, hashed the root key against the supplied EUI in context. */
  SL_ZB_SEC_MAN_DERIVED_KEY_TYPE_TC_HASHED_LINK_KEY = 0x0010,
};

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
  /** @brief Internal use only.  This indicates that the key being added was derived via
   * dynamic link key negotiation.  This may be used in conjunction with the above
   * ::ZB_SEC_MAN_FLAG_UNCONFIRMED_TRANSIENT_KEY while the derived link key awaits
   * confirmation
   */
  ZB_SEC_MAN_FLAG_AUTHENTICATED_DYNAMIC_LINK_KEY = 0x08,
  /** @brief Internal use only.  This indicates that the "key" being added is instead the
   * symmetric passphrase to be stored in the link key table. This flag will trigger the
   * addition of the KEY_TABLE_SYMMETRIC_PASSPHRASE bitmask when storing the symmetric
   * passphrase so that it can be differentiated from other keys with the same EUI64.
   */
  ZB_SEC_MAN_FLAG_SYMMETRIC_PASSPHRASE = 0x10,
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
  //Unused for classic key storage.
  //The algorithm type should be brought in by psa/crypto_types.h.  Zigbee Security Manager
  //uses PSA_ALG_ECB_NO_PADDING for keys with AES-ECB encryption, and defines ZB_PSA_ALG as
  //AES-CCM with a 4-byte tag, used as this field's default value otherwise.
  uint32_t psa_key_alg_permission;
} sl_zb_sec_man_context_t;

/** @brief This data structure contains the metadata pertaining to an network key */
typedef struct {
  bool network_key_set;
  bool alternate_network_key_set;
  uint8_t network_key_sequence_number;
  uint8_t alt_network_key_sequence_number;
  uint32_t network_key_frame_counter;
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

#endif
