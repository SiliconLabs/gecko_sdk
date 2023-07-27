/**
 * @brief Dynamic Link Key Negotiation enables support
 * for secure link key derivation using Elliptic Curve Diffie-Hellman
 * and Secure Passphrase Ephemeral Key Exchange for public-key cryptography
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

#ifndef SL_ZIGBEE_DLK_NEGOTIATION_H
#define SL_ZIGBEE_DLK_NEGOTIATION_H

// NOTE for BIT macro
// #include "platform-header.h"

// NOTE for size_t
#include <stddef.h>

#include "sl_zigbee_security_manager_dlk_ecc.h"
#include "ember-types.h"
#include "sl_zigbee_address_info.h"
// NOTE for EventControl
#include "event_queue/event-queue.h"
#include "sl_enum.h"

#define SL_DLK_EVENT_TIMEOUT_MS 10000

// NOTE the following enumerations are defined per the zigbee specification
// Key Negotiation Protocols

// NOTE supported bitmasks are 8-bit numbers
// typedef uint8_t sl_zigbee_dlk_negotiation_method;
// enum {
SL_ENUM(sl_zigbee_dlk_negotiation_method) {
  DLK_PROTOCOL_ENUM_STATIC_KEY    = 0,
  DLK_PROTOCOL_ENUM_SPEKE_C25519_AES128 = 1,
  DLK_PROTOCOL_ENUM_SPEKE_C25519_SHA256 = 2,
  // TODO where is P-256?
  DLK_PROTOCOL_ENUM_RESERVED,
};

SL_ENUM(sl_zigbee_dlk_supported_negotiation_method) {
  DLK_PROTOCOL_MASK_STATIC_KEY_REQUEST  = BIT(DLK_PROTOCOL_ENUM_STATIC_KEY),
  DLK_PROTOCOL_MASK_SPEKE_C25519_AES128 = BIT(DLK_PROTOCOL_ENUM_SPEKE_C25519_AES128),
  DLK_PROTOCOL_MASK_SPEKE_C25519_SHA256 = BIT(DLK_PROTOCOL_ENUM_SPEKE_C25519_SHA256),
  DLK_PROTOCOL_MASK_RESERVED = 0,
};

// Shared Secret Sources
SL_ENUM(sl_zigbee_dlk_negotiation_shared_secret_source) {
  DLK_SECRET_ENUM_SYMMETRIC_AUTH_TOKEN     = 0,
  DLK_SECRET_ENUM_PRECONFIG_INSTALL_CODE   = 1,
  DLK_SECRET_ENUM_VARIABLE_LENGTH_PASSCODE = 2,
  DLK_SECRET_ENUM_BASIC_ACCESS_KEY         = 3,
  DLK_SECRET_ENUM_ADMIN_ACCESS_KEY         = 4,
  DLK_SECRET_ENUM_RESERVED                 = 5,
  // NOTE 5-7 are reserved
  // NOTE well known psk is 0xff
  DLK_SECRET_ENUM_WELL_KNOWN_KEY           = 255,
};

SL_ENUM(sl_zigbee_dlk_negotiation_supported_shared_secret_source) {
  DLK_SECRET_MASK_SYMMETRIC_AUTH_TOKEN     = BIT(DLK_SECRET_ENUM_SYMMETRIC_AUTH_TOKEN),
  DLK_SECRET_MASK_PRECONFIG_INSTALL_CODE   = BIT(DLK_SECRET_ENUM_PRECONFIG_INSTALL_CODE),
  DLK_SECRET_MASK_VARIABLE_LENGTH_PASSCODE = BIT(DLK_SECRET_ENUM_VARIABLE_LENGTH_PASSCODE),
  DLK_SECRET_MASK_BASIC_ACCESS_KEY         = BIT(DLK_SECRET_ENUM_BASIC_ACCESS_KEY),
  DLK_SECRET_MASK_ADMIN_ACCESS_KEY         = BIT(DLK_SECRET_ENUM_ADMIN_ACCESS_KEY),
  DLK_SECRET_MASK_RESERVED = 0,
};

SL_ENUM(sl_zigbee_dlk_negotiation_state_t) {
  // special states
  DLK_STATE_NONE,
  DLK_STATE_OPEN,
  DLK_STATE_WAITING,
  // start
  DLK_STATE_INIT_DLK_DERIVATION,
  DLK_STATE_GENERATE_KEY_PAIR,
  DLK_STATE_START_COMPLETE,
  // finish
  DLK_STATE_EXTRACT_SHARED_SECRET,
  DLK_STATE_EXPAND_SHARED_SECRET,
  DLK_STATE_DERIVE_KEY,
  DLK_STATE_FINISH_COMPLETE,
};

// DLK Negotiation
typedef struct sli_zigbee_dlk_negotiation_context sli_zigbee_dlk_negotiation_context_t;
/**
 * @brief callback issued when public key generation completes
 * @param status the status of the key generation operation
 * @param key_data a pointer to the public key data
 * @param key_length the number of bytes of public key
 * @return status indicating whether key negotiation should continue / wait
 */

typedef sl_status_t (*sli_zigbee_dlk_start_complete_callback)(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                                              sl_status_t status,
                                                              uint8_t *key_data,
                                                              uint8_t key_length);

/**
 * @brief callback issued when dynamic link key derivation has completed
 * @param status the status of the key derivation operation
 * @param key_data a pointer to the 16-byte encryption key
 */

typedef void (*sli_zigbee_dlk_finish_complete_callback)(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                                        sl_status_t status,
                                                        uint8_t *key_data);
struct sli_zigbee_dlk_negotiation_context {
  sl_zigbee_dlk_negotiation_state_t state;
  sl_zigbee_dlk_negotiation_method session_key_protocol;
  sl_zigbee_dlk_negotiation_shared_secret_source session_secret_source;
  sli_zigbee_dlk_start_complete_callback start_complete_callback;
  sli_zigbee_dlk_finish_complete_callback finish_complete_callback;
  sl_zigbee_address_info partner;
  EmberEvent *event_control;
  sli_zb_sec_man_dlk_ecc_context_t *ecc_ctx;
  size_t key_scratch_length;
  // NOTE key_scratch_buff is used to contain various key text at different points in negotiation
  // - psk is stored after calling open until 'start' is called
  // - local public key is stored after if it is generated til after 'start_complete'
  // - peer public key is stored after calling 'finish'
  uint8_t key_scratch_buffer[DLK_ECC_MAX_PUBLIC_KEY_SIZE];
};

/**
 * @brief 'binds' a dlk context struct with the associated data and callbacks
 */
sl_status_t sli_zigbee_dlk_context_bind(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                        sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                        EmberEvent *dlk_event_control);

// TODO app callback to select key negotiation params given partner bitmask

// NOTE this assumes that before calling open, the negotiation context is 'bound' to an event control block, an ecc context, and it's callbacks
/**
 * @brief initializes a key exchange session, recording the partner id info
 * as well as negotiation parameters
 */
sl_status_t sli_zigbee_dlk_open_key_exchange(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                             sl_zigbee_address_info *partner,
                                             sl_zigbee_dlk_negotiation_method keyProtocol,
                                             sl_zigbee_dlk_negotiation_shared_secret_source secret,
                                             uint8_t *psk_bytes,
                                             sli_zigbee_dlk_start_complete_callback dlk_start_complete_callback,
                                             sli_zigbee_dlk_finish_complete_callback dlk_finish_complete_callback);

/**
 * @brief closes a negotiation session, frees resources
 */
void sli_zigbee_dlk_close_key_exchange(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx);

/**
 * @brief begins key exchange, generating a public key
 */
sl_status_t sli_zigbee_dlk_start_key_exchange(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                              sl_zigbee_address_info *partner);

/**
 * @brief use partner public key to finish key exchange and generate final key
 */
sl_status_t sli_zigbee_dlk_finish_key_exchange(sli_zigbee_dlk_negotiation_context_t *dlk_negotiation_ctx,
                                               sl_zigbee_address_info *partner,
                                               uint8_t *partner_key,
                                               size_t partner_key_length);

// for golden units the feature will need to be disable-able

#endif // SL_ZIGBEE_DLK_NEGOTIATION_H
