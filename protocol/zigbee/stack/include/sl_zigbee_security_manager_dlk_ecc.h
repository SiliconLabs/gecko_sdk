/***************************************************************************//**
 * @file sl_zigbee_security_manager_dlk_ecc.h
 * @brief stateless computation of dynamic link key elliptic curve cryptography
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

#ifndef SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_H
#define SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_H

// NOTE for size_t
#include <stddef.h>
// NOTE for bool
#include <stdbool.h>

#include "sl_status.h"
#include "sl_enum.h"
#include "mbedtls/bignum.h"
#include "mbedtls/ecp.h"

// NOTE can be optimized by defining a config header and conditionally compiling based on curve/hash config

// NOTE same as EMBER_ENCRYPTION_KEY_SIZE
#define DLK_KEY_SIZE 16
// NOTE curve25519 encodes only x-coordinate, p-256 encodes (x,y) coordinate
#define DLK_ECC_COORDINATE_SIZE 32
#define DLK_ECC_CURVE25519_PUBLIC_KEY_SIZE DLK_ECC_COORDINATE_SIZE
#define DLK_ECC_P256_PUBLIC_KEY_SIZE DLK_ECC_COORDINATE_SIZE * 2
#define DLK_ECC_MAX_PUBLIC_KEY_SIZE DLK_ECC_P256_PUBLIC_KEY_SIZE

// NOTE helpful to know about the different hash families
#define AES_HASH_DIGEST_LENGTH 16
#define SHA_HASH_DIGEST_LENGTH 32
// NOTE must be at least as large as SHA256 digest
#define MAX_SHARED_SECRET_LEN SHA_HASH_DIGEST_LENGTH

// NOTE want to separate out the negotiation procedures from the ecc curve and hash
// right now it is only supported such that...
// AES* = (AES-MMO-128, HMAC-AES-MMO-128)
// SHA* = (SHA-256, HMAC-SHA-256)
// ECDH = P-256 + (AES* | SHA*)
// SPEKE = C25519 + (AES-* | SHA*)
// but there may be other extensions and supported methods in the future s.t.?
// SPEKE !-> C25519
// ECDH  !-> P-256

// NOTE supported configurations
typedef struct {
  uint8_t operation_id; // enum indicating which operation is being performed
  uint8_t curve_id;     // enum indicating which type of curve is being used
  uint8_t hash_id;      // enum indicating which hash function is being used
} sli_zb_dlk_ecc_config_t;

typedef struct zb_sec_man_dlk_ecc_context {
  // configuration data
  sli_zb_dlk_ecc_config_t config;
  // mbedtls values
  mbedtls_ecp_group ecc_group;    // elliptic curve group
  mbedtls_mpi d;                  // private key
  mbedtls_ecp_point Q;            // public-point
  mbedtls_ecp_point Qp;           // peer's public point
  mbedtls_mpi x_k;                // common point coordinate
  // array members
  uint8_t psk[DLK_KEY_SIZE];          // byte-array for the pre-shared key
  uint8_t secret[MAX_SHARED_SECRET_LEN];     // byte-array to store the secret value
  uint8_t derived_key[DLK_KEY_SIZE];  // byte-array to store the final link key
  // test vector data
  void *test;
} sli_zb_sec_man_dlk_ecc_context_t;

/**
 * @brief supported key agreement schemes
 */
SL_ENUM(sli_dlk_ecc_operation_id) {
  DLK_ECC_OPERATION_INVALID,
  DLK_ECC_OPERATION_ECDHE_PSK,
  DLK_ECC_OPERATION_SPEKE,
};

/**
 * @brief supported elliptic curve groups
 */
SL_ENUM(sli_dlk_ecc_curve_id) {
  DLK_ECC_CURVE_INVALID,
  DLK_ECC_CURVE_25519,
  DLK_ECC_CURVE_P256,
};

/**
 * @brief supported hash function families
 */
SL_ENUM(sli_dlk_ecc_hash_id) {
  DLK_ECC_HASH_INVALID,
  DLK_ECC_HASH_AES_MMO_128,
  DLK_ECC_HASH_SHA_256,
};

/**
 * @brief checks if given ecc operation, curve, and hash are valid
 */
bool sli_zigbee_is_supported_ecc_operation(sli_zb_dlk_ecc_config_t *ecc_config);

/// generic operations
/**
 * @brief initializes the ecc computation context and primes the elliptic curve
 * @param dlk_ecc_ctx a pointer to the context struct to store computation state
 * @param config a pointer to the context struct to store operation id, curve id, and hash id
 * @param psk a pointer to the 16-byte pre-shared key
 * @return status indicating if initialization was successful
 */
sl_status_t sli_zb_sec_man_ecc_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                    sli_zb_dlk_ecc_config_t *config,
                                    uint8_t *psk);

/**
 * @brief tears down the ecc context and frees the underlying resources
 */
void sli_zb_sec_man_ecc_free(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

/**
 * @brief generates a public/private key-pair
 * @param dlk_ecc_ctx a pointer to the context struct containing initial computation state
 * @param public_key_buff a pointer arg where the resulting public key is written if successful
 * @param key_len_out a pointer arg that will contain the resulting length in bytes of public key data
 * @return status indicating whether keypair generation was successful
 */
sl_status_t sli_zb_sec_man_ecc_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                uint8_t *public_key_buff,
                                                size_t *key_len_out);

/**
 * @brief uses peer public key to calculate the shared value
 * @param dlk_ecc_ctx a pointer to the context struct containing computation state
 * @param peer_public_key a pointer to the peer public key data
 * @param peer_key_len the length of the key data
 * @return status indicating whether elliptic curve point multiplication was successful
 */
sl_status_t sli_zb_sec_man_ecc_extract_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                     uint8_t *peer_public_key,
                                                     size_t peer_key_len);

/**
 * @brief combines shared value with session data to produce the secret value
 * @param dlk_ecc_ctx a pointer to the context struct containing computation state
 * @param our_eui the 8-byte eui64 address of the local node
 * @param their_eui the 8-byte eui64 address of the peer node
 * @return a status indicating whether computation of the shared secret was successful
 */
sl_status_t sli_zb_sec_man_ecc_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                    uint8_t *our_eui,
                                                    uint8_t *their_eui);

/**
 * @brief takes the shared secret and derives link key using kdf
 * @param dlk_ecc_ctx a pointer to the context struct containing computation state
 * @return status indicating whether final key derivation was successful
 * @note final result is stored in 'dlk_ecc_ctx->derived_key' if successful
 */
sl_status_t sli_zb_sec_man_ecc_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

/**
 * @brief serializes the generated public key into the given buffer
 * @param dlk_ecc_ctx a pointer to the context struct containing generated key
 * @param is_peer if true serialize the peer public key
 * @param public_key_buff the destination buffer to write the public key data to
 * @note must contain enough bytes to hold the key (64 bytes for DLK_ECC_CURVE_P256)
 * (32 bytes for DLK_ECC_CURVE_25519)
 * @param public_key_len a pointer arg that will contain the number of key bytes serialized
 * @return status indicating if anything went wrong
 */
sl_status_t sli_zb_sec_man_ecc_export_public_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                 bool is_peer,
                                                 uint8_t *public_key_buff,
                                                 size_t *public_key_len);

/**
 * @brief incorporates peer public key data into the ecc context
 * @param dlk_ecc_ctx a pointer to the context struct containing partial computation
 * @param public_key_buff the source buffer containing peer public key data
 * @param public_key_len the amount of key data contained in the input buffer
 * @return status indicating if something went wrong
 */
sl_status_t sli_zb_sec_man_ecc_import_peer_public_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t *public_key_buff,
                                                      size_t public_key_len);

/**
 * @brief produces the final derived key from the context
 * @param dlk_ecc_ctx a pointer to the context struct containing computation results
 * @param derived_key_out a pointer argument that will contain the derived key data if successful
 * @return status indicating whether it was possible to extract the link key
 */
sl_status_t sli_zb_sec_man_ecc_export_link_key_result(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t **derived_key_out);

#endif // SL_ZIGBEE_SECURITY_MANAGER_DLK_ECC_H
