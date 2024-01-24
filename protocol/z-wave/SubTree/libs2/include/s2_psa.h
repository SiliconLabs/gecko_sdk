/* \file s2_psa.h
 * \brief KeyIDs and wrapper functions and defines over PSA APIs.
 */

/* © 2017 Silicon Laboratories Inc.
 */
#ifndef _S2_PSA_H_
#define _S2_PSA_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define ZWAVE_ECDH_SECRET_LENGTH        32
/*
 * \brief Key-Id range reserved for z-wave,
 * for storing keys persistently in secure vault
 */
#define ZWAVE_PSA_KEY_ID_MIN    0x00070000
#define ZWAVE_PSA_KEY_ID_MAX    0x0007FFFF
#define ZWAVE_PSA_KEY_ID_MARKER 0x00070012
#define ZWAVE_NET_KEY_SPAN_INDEX        01
#define ZWAVE_NET_KEY_MPAN_INDEX        02

#define ZW_PSA_ALG_CCM          0x05500100
#define ZW_PSA_ALG_CMAC         0x03c00200
#define ZW_PSA_ALG_ECB_NO_PAD   0x04404400

#define ZWAVE_PSA_AES_MAC_LENGTH         8
#define ZWAVE_PSA_AES_NONCE_LENGTH      13

/* Temporary key_ids for volatile AES keys for in-place usage */
#define ZWAVE_CCM_TEMP_ENC_KEY_ID        3
#define ZWAVE_CCM_TEMP_DEC_KEY_ID        4
#define ZWAVE_ECB_TEMP_ENC_KEY_ID        5
#define ZWAVE_CMAC_TEMP_KEY_ID           6

/**
 * \brief Mapping to PSA error code types.
 */
typedef enum {
  ZW_PSA_SUCCESS = 0,
  ZW_PSA_ERROR_ALREADY_EXISTS = -139,
  ZW_PSA_ERROR_INVALID_SIGNATURE = -149,
  ZW_PSA_STATUS_INVALID = 200 /* Refine this */
} zw_status_t;

/**
 *  \brief KeyType derived from network key
 *  Used to define keyid
 */
typedef enum
{
  ZWAVE_KEY_TYPE_SINGLE_CAST = 0x01,
  ZWAVE_KEY_TYPE_MULTI_CAST,
  ZWAVE_KEY_TYPE_NONCE
} zwave_derived_key_type_t;

/**
 * \brief Convert PSA error code types to zwave error types.
 */
extern zw_status_t convert_psa_to_zw_status (int psa_status);

/**
 * \brief PSA wrapper for ecdh shared secret computation.
 */
extern zw_status_t zw_compute_ecdh_shared_secret(const uint8_t *remote_public_key,
                                                 uint32_t keyid,
                                                 uint8_t *result);

extern zw_status_t zw_compute_inclusion_ecdh_shared_secret(const uint8_t *remote_public_key, uint8_t *result);

/**
 * \brief Convert s2 key class to key ids for accessing keys in secure vault.
 */
extern uint32_t convert_key_class_to_psa_key_id(uint8_t key_class);

#if defined(ZWAVE_PSA_SECURE_VAULT) && defined(ZWAVE_PSA_AES)
/**
 * \brief Store/import network key sent by controller, into secure vault.
 */
extern zw_status_t zw_wrap_aes_key_secure_vault(uint32_t *key_id, const uint8_t *aes_key, uint32_t key_algorithm);

/**
 * \brief Export/Read key stored in secure vault.
 */
extern zw_status_t zw_read_vault_network_key_aes_cmac(uint32_t key_id, uint8_t *buff, size_t buff_size, size_t *out_len);

/**
 * \brief PSA wrapper AES CMAC computation.
 */
extern zw_status_t zw_psa_aes_cmac(uint32_t key_id, const uint8_t *input, size_t length, uint8_t *output);

/**
 * \brief PSA wrapper for Authenticated Encryption with Associated Data (AEAD) - PSA_ALG_CCM.
 */
extern zw_status_t zw_psa_aead_encrypt_ccm(uint32_t key_id, const uint8_t *nonce, size_t nonce_len,
                                 const uint8_t *ad, size_t ad_len, const uint8_t *plain_text,
                                 size_t plain_text_len, uint8_t *cipher_text, size_t cipher_text_len,
                                 size_t *cipher_len);
/**
 * \brief PSA wrapper for  Authenticated Decryption with Associated Data (AEAD) - PSA_ALG_CCM.
 */
extern zw_status_t zw_psa_aead_decrypt_ccm(uint32_t key_id, const uint8_t *nonce, size_t nonce_len,
                                 const uint8_t *ad, size_t ad_len, const uint8_t *plain_text,
                                 size_t plain_text_len, uint8_t *cipher_text, size_t cipher_text_len,
                                 size_t *cipher_len);

/**
 * \brief PSA wrapper for AES ECB encryption
 */
extern zw_status_t zw_psa_aes_ecb_encrypt(uint32_t key_id, const uint8_t *input, uint8_t *output);

/**
 * \brief PSA wrapper for storing a key in secure vault either as peristent or volatile.
 */
extern zw_status_t zw_wrap_aes_key_secure_vault_test(uint32_t *key_id, const uint8_t *aes_key, uint32_t key_algorithm);

#endif /* defined(ZWAVE_PSA_AES) */

/**
 * \brief Mapping between key slots to PSA key ids.
 */

extern uint8_t convert_keyslot_to_key_class_id (uint8_t key_slot);

/**
 * \brief Mapping between derived keys (encryption/decryption CCM keys) to PSA key IDs.
 */

extern uint32_t convert_keyclass_to_derived_key_id (uint32_t key_class, zwave_derived_key_type_t key_type);


/**
 * \brief PSA wrapper to destroy a key stored in secure vault.
 */
extern zw_status_t zw_psa_destroy_key(uint32_t key_id);

extern void zw_security_error(zw_status_t error);

#endif // _S2_PSA_H_
