/***************************************************************************//**
 * @file sl_zigbee_security_manager_dlk_ecc.c
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

#include "sl_zigbee_security_manager_dlk_ecc.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_PRESENT
#include "stack/include/sl_zigbee_security_manager_dlk_ecc_test_vectors.h"
#endif

// NOTE for EmberStatus
#include "ember-types.h"
// NOTE for sha-256 primitives
#include "mbedtls/sha256.h"
// NOTE for compute_shared and gen_public primitives
#include "mbedtls/ecdh.h"
// NOTE for mbedtls_strerror
#include "mbedtls/error.h"
// NOTE for emberReverseMemCopy
#include "stack/include/byte-utilities.h"
// NOTE for emberGetStrongRandomNumber...
#include "ember-random-api.h"
// NOTE for emberAesHashSimple
#include "stack/include/aes-mmo.h"

/// operation specific
// NOTE the below procedures are specific to the underlying key agreement scheme
// [ECDHE-PSK] Elliptic Curve Diffie-Hellman Ephemeral (with PSK salting)

static sl_status_t ecdhe_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

static sl_status_t ecdhe_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

static sl_status_t ecdhe_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

static sl_status_t ecdhe_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

// [SPEKE] Secure Passphrase Ephemeral Key Exchange

static sl_status_t speke_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

static sl_status_t speke_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

sl_status_t sli_zb_sec_man_speke_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t *our_eui,
                                                      uint8_t *their_eui);

static sl_status_t speke_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx);

#define HMAC_SHA_256_OUTPUT_SIZE 32
/**
 * @brief performs a keyed hmac using SHA-256 as the underlying hash function
 * @param key a pointer to the key data
 * @param key_len the length of 'key' in bytes
 * @param data a pointer to the input data
 * @param data_len the length of 'data' in bytes
 * @param result[OUT] a pointer argument where the resulting digest will be written
 * @note result must contain enough memory for a 32-byte output digest
 */
void sl_zb_sec_man_hmac_sha_256(
  uint8_t *key,
  uint8_t key_len,
  uint8_t *data,
  uint8_t data_len,
  uint8_t *result);

// NOTE need emberHmacAesHash without pulling in all of security.h
extern void emberHmacAesHash(const uint8_t *key,
                             const uint8_t *data,
                             uint8_t dataLength,
                             uint8_t *result);

// NOTE here's a wrapper function for providing rng to crypto calls
static int f_rng_wrapper(void *prng, unsigned char *out, size_t num)
{
  if (num % 2) {
    uint16_t temp;
    emberGetStrongRandomNumber(&temp);
    *out = LOW_BYTE(temp);
    out++;
    num--;
  }
  int count = num / 2;
  uint16_t *shortPtr = (uint16_t *)out;
  return emberGetStrongRandomNumberArray(shortPtr, count);
}

static sli_zb_dlk_ecc_config_t dlk_ecc_valid_configurations[] =
{
  { DLK_ECC_OPERATION_ECDHE_PSK, DLK_ECC_CURVE_P256, DLK_ECC_HASH_SHA_256 },
  { DLK_ECC_OPERATION_SPEKE, DLK_ECC_CURVE_25519, DLK_ECC_HASH_SHA_256 },
  { DLK_ECC_OPERATION_SPEKE, DLK_ECC_CURVE_25519, DLK_ECC_HASH_AES_MMO_128 },
  // NOTE sentinel value
  { DLK_ECC_OPERATION_INVALID, DLK_ECC_CURVE_INVALID, DLK_ECC_HASH_INVALID }
};

bool sli_zigbee_is_supported_ecc_operation(sli_zb_dlk_ecc_config_t *ecc_config)
{
  sli_zb_dlk_ecc_config_t *config_cursor = dlk_ecc_valid_configurations;
  while (config_cursor != NULL) {
    if (config_cursor->operation_id == ecc_config->operation_id
        && config_cursor->curve_id == ecc_config->curve_id
        && config_cursor->hash_id == ecc_config->hash_id) {
      break;
    } else if (config_cursor->operation_id == DLK_ECC_OPERATION_INVALID
               && config_cursor->curve_id == DLK_ECC_CURVE_INVALID
               && config_cursor->hash_id == DLK_ECC_HASH_INVALID) {
      // NOTE sentinel value
      config_cursor = NULL;
    } else {
      config_cursor++;
    }
  }
  return config_cursor != NULL;
}

// generic ecc operations
sl_status_t sli_zb_sec_man_ecc_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                    sli_zb_dlk_ecc_config_t *ecc_config,
                                    uint8_t *psk)
{
  if (dlk_ecc_ctx == NULL || psk == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  if (!sli_zigbee_is_supported_ecc_operation(ecc_config)) {
    return SL_STATUS_NOT_AVAILABLE;
  }

  // NOTE: assume if ecc_config points to internal struct, it has already been set
  if (&dlk_ecc_ctx->config != ecc_config) {
    memmove(&dlk_ecc_ctx->config, ecc_config, sizeof(sli_zb_dlk_ecc_config_t));
  }
  // set the psk
  memmove(dlk_ecc_ctx->psk, psk, DLK_KEY_SIZE);
  // perform additional steps per key negotiation scheme
  switch (dlk_ecc_ctx->config.operation_id) {
    case DLK_ECC_OPERATION_ECDHE_PSK:
      return ecdhe_init(dlk_ecc_ctx);
    case DLK_ECC_OPERATION_SPEKE:
      return speke_init(dlk_ecc_ctx);
    default:
      // UNREACHABLE
      return SL_STATUS_NOT_SUPPORTED;
  }
}

void sli_zb_sec_man_ecc_free(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  if (dlk_ecc_ctx == NULL) {
    return;
  }
  mbedtls_mpi_free(&dlk_ecc_ctx->d);
  mbedtls_ecp_group_free(&dlk_ecc_ctx->ecc_group);
  mbedtls_ecp_point_free(&dlk_ecc_ctx->Q);
  mbedtls_ecp_point_free(&dlk_ecc_ctx->Qp);
  mbedtls_mpi_free(&dlk_ecc_ctx->x_k);
  // clear out struct
  memset(dlk_ecc_ctx, 0, sizeof(sli_zb_sec_man_dlk_ecc_context_t));
}

sl_status_t sli_zb_sec_man_ecc_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                uint8_t *public_key_buff,
                                                size_t *key_len_out)
{
  if (dlk_ecc_ctx == NULL || public_key_buff == NULL || key_len_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  sl_status_t status;
  switch (dlk_ecc_ctx->config.operation_id) {
    case DLK_ECC_OPERATION_ECDHE_PSK:
      status = ecdhe_generate_keypair(dlk_ecc_ctx);
      break;
    case DLK_ECC_OPERATION_SPEKE:
      status = speke_generate_keypair(dlk_ecc_ctx);
      break;
    default:
      // UNREACHABLE
      return SL_STATUS_NOT_SUPPORTED;
  }
  if (status != SL_STATUS_OK) {
    return status;
  }
  return sli_zb_sec_man_ecc_export_public_key(dlk_ecc_ctx, false, public_key_buff, key_len_out);
}

sl_status_t sli_zb_sec_man_ecc_extract_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                     uint8_t *peer_public_key,
                                                     size_t peer_key_len)
{
  if (dlk_ecc_ctx == NULL || peer_public_key == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  // HOWEVER the format of the public key might be different depending on the curve...
  // NOTE right now the protocols are such that we do not need to validate the expected len by curve
  sl_status_t status = sli_zb_sec_man_ecc_import_peer_public_key(dlk_ecc_ctx, peer_public_key, peer_key_len);
  if (status != SL_STATUS_OK) {
    return status;
  }
  // NOTE this step is the same regardless of key agreement scheme
  int crypto_ret = mbedtls_ecdh_compute_shared(&dlk_ecc_ctx->ecc_group,
                                               &dlk_ecc_ctx->x_k,
                                               &dlk_ecc_ctx->Qp,
                                               &dlk_ecc_ctx->d,
                                               f_rng_wrapper,
                                               NULL);
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sli_zb_sec_man_ecc_expand_shared_secret(
  sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
  uint8_t *our_eui,
  uint8_t *their_eui)
{
  if (dlk_ecc_ctx == NULL || our_eui == NULL || their_eui == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  switch (dlk_ecc_ctx->config.operation_id) {
    case DLK_ECC_OPERATION_ECDHE_PSK:
      // NOTE euis are not needed for ecdhe
      return ecdhe_expand_shared_secret(dlk_ecc_ctx);
    case DLK_ECC_OPERATION_SPEKE:
      return sli_zb_sec_man_speke_expand_shared_secret(dlk_ecc_ctx, our_eui, their_eui);
    default:
      // UNREACHABLE
      return SL_STATUS_NOT_SUPPORTED;
  }
}

sl_status_t sli_zb_sec_man_ecc_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  if (dlk_ecc_ctx == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  switch (dlk_ecc_ctx->config.operation_id) {
    case DLK_ECC_OPERATION_SPEKE:
      return speke_derive_link_key(dlk_ecc_ctx);
    case DLK_ECC_OPERATION_ECDHE_PSK:
      return ecdhe_derive_link_key(dlk_ecc_ctx);
    default:
      // UNREACHABLE
      return SL_STATUS_NOT_SUPPORTED;
  }
}

sl_status_t sli_zb_sec_man_ecc_export_public_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                 bool is_peer,
                                                 uint8_t *public_key_buff,
                                                 size_t *public_key_len)
{
  if (dlk_ecc_ctx == NULL || public_key_buff == NULL || public_key_len == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  mbedtls_ecp_point *Q = is_peer ? &dlk_ecc_ctx->Qp : &dlk_ecc_ctx->Q;
  size_t bytes_written;
  int crypto_ret = -1;
  // get the x coordinate
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_P256) {
    // P256 uses big endianess
    crypto_ret = mbedtls_mpi_write_binary(&Q->MBEDTLS_PRIVATE(X), public_key_buff, DLK_ECC_COORDINATE_SIZE);
  } else {
    // CURVE_25519 uses little endianess
    crypto_ret = mbedtls_mpi_write_binary_le(&Q->MBEDTLS_PRIVATE(X), public_key_buff, DLK_ECC_COORDINATE_SIZE);
  }
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_WRITE;
  }
  bytes_written = DLK_ECC_COORDINATE_SIZE;
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_P256) {
    // get the y coordinate
    crypto_ret = mbedtls_mpi_write_binary(&Q->MBEDTLS_PRIVATE(Y), public_key_buff + bytes_written, DLK_ECC_COORDINATE_SIZE);
    if (crypto_ret != 0) {
      return SL_STATUS_OBJECT_WRITE;
    }
    bytes_written += DLK_ECC_COORDINATE_SIZE;
  }
  *public_key_len = bytes_written;
  return SL_STATUS_OK;
}

sl_status_t sli_zb_sec_man_ecc_import_peer_public_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t *public_key_buff,
                                                      size_t public_key_len)
{
  if (dlk_ecc_ctx == NULL || public_key_buff == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  int crypto_ret = -1;
  // set the Z coord
  crypto_ret = mbedtls_mpi_lset(&dlk_ecc_ctx->Qp.MBEDTLS_PRIVATE(Z), 1);
  if (crypto_ret != 0) {
    return SL_STATUS_FAIL;
  }
  // read in the x coordinate
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_P256) {
    // P256 uses big endianess
    crypto_ret = mbedtls_mpi_read_binary(&dlk_ecc_ctx->Qp.MBEDTLS_PRIVATE(X), public_key_buff, DLK_ECC_COORDINATE_SIZE);
  } else {
    // CURVE_25519 uses little endianess
    crypto_ret = mbedtls_mpi_read_binary_le(&dlk_ecc_ctx->Qp.MBEDTLS_PRIVATE(X), public_key_buff, DLK_ECC_COORDINATE_SIZE);
  }
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_READ;
  }
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_P256) {
    // read in the y coordinate
    crypto_ret = mbedtls_mpi_read_binary(&dlk_ecc_ctx->Qp.MBEDTLS_PRIVATE(Y), public_key_buff + DLK_ECC_COORDINATE_SIZE, DLK_ECC_COORDINATE_SIZE);
  }
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_READ;
  }
  crypto_ret = mbedtls_ecp_check_pubkey(&dlk_ecc_ctx->ecc_group, &dlk_ecc_ctx->Qp);
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

sl_status_t sli_zb_sec_man_ecc_export_link_key_result(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t **derived_key_out)
{
  if (dlk_ecc_ctx == NULL || derived_key_out == NULL) {
    return SL_STATUS_NULL_POINTER;
  }
  *derived_key_out = dlk_ecc_ctx->derived_key;
  return SL_STATUS_OK;
}

// NOTE the below procedures are specific to the underlying key agreement scheme
// [ECDHE-PSK] Elliptic Curve Diffie-Hellman Ephemeral (with PSK salting)

static sl_status_t ecdhe_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  // NOTE right now only p-256 is supported for ecdhe
  if (dlk_ecc_ctx->config.curve_id != DLK_ECC_CURVE_P256) {
    return SL_STATUS_NOT_SUPPORTED;
  }
  int crypto_ret = mbedtls_ecp_group_load(&dlk_ecc_ctx->ecc_group,
                                          MBEDTLS_ECP_DP_SECP256R1);
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t ecdhe_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  // NOTE we checked the inputs in the calling function?
  int crypto_ret = mbedtls_ecdh_gen_public(&dlk_ecc_ctx->ecc_group,
                                           &dlk_ecc_ctx->d,
                                           &dlk_ecc_ctx->Q,
                                           f_rng_wrapper,
                                           NULL);
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t ecdhe_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  // NOTE the context arg should have been checked in the calling function
  uint8_t buffer[DLK_ECC_COORDINATE_SIZE + DLK_KEY_SIZE];
  int crypto_ret = -1;
  int buffLen = DLK_ECC_COORDINATE_SIZE + DLK_KEY_SIZE;
  crypto_ret = mbedtls_mpi_write_binary_le(&dlk_ecc_ctx->x_k, buffer, DLK_ECC_COORDINATE_SIZE);
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_WRITE;
  }

  memcpy(buffer + DLK_ECC_COORDINATE_SIZE, dlk_ecc_ctx->psk, DLK_KEY_SIZE);
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    crypto_ret = mbedtls_sha256(buffer, buffLen, dlk_ecc_ctx->secret, 0);
  } else {
    return SL_STATUS_NOT_SUPPORTED;
  }
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t ecdhe_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  uint8_t result[SHA_HASH_DIGEST_LENGTH];
  uint8_t data[1] = { 1 };

  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    sl_zb_sec_man_hmac_sha_256(dlk_ecc_ctx->secret, MAX_SHARED_SECRET_LEN, data, 1, result);
  } else {
    return SL_STATUS_NOT_SUPPORTED;
  }
  // NOTE max digest is 256 bits, we only need 128 bits for encryption key
  memcpy(dlk_ecc_ctx->derived_key, result, DLK_KEY_SIZE);
  return SL_STATUS_OK;
}

// [SPEKE] Secure Passphrase Ephemeral Key Exchange

// x25519 procedure for processing generator points
// non-canonical generator points G must be reduced to the modulo field
// https://tools.ietf.org/html/rfc7748#section-5
#define X25519_BITS 255
#define X25519_MASK ((1 << (X25519_BITS % 8)) - 1)
#define X25519_U_DECODE(u) ((u)[31] &= X25519_MASK)

// NOTE key clamp is required for SPEKE with curve25519
static void x25519_key_clamp(uint8_t keyBytes[32])
{
  keyBytes[0]  &= 248;
  keyBytes[31] &= 127;
  keyBytes[31] |= 64;
}

#ifdef SL_CATALOG_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_PRESENT
static inline int speke_test_vector_load_private_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  // TEST VECTORS

  sli_zigbee_dlk_ecc_test_vector_profile_data_t *profile = ((sli_zigbee_dlk_ecc_test_vector_bundle_t*)dlk_ecc_ctx->test)->profile;
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_25519) {
    // perform a key clamp on the pre-set values
    // X25519 only
    x25519_key_clamp(profile->GIVEN_privkey);
  }
  // read the big endian private key into the context
  int crypto_ret = mbedtls_mpi_read_binary_le(&dlk_ecc_ctx->d, profile->GIVEN_privkey, DLK_ECC_COORDINATE_SIZE);
  if (crypto_ret != 0) {
    return crypto_ret;
  }
  // calculate the public point by multiplying the private key with the generator point
  return mbedtls_ecp_mul(&dlk_ecc_ctx->ecc_group,
                         &dlk_ecc_ctx->Q,
                         &dlk_ecc_ctx->d,
                         &dlk_ecc_ctx->ecc_group.G,
                         f_rng_wrapper,
                         NULL);
}
#else
#define speke_test_vector_load_private_key(ctx) ((void) (ctx))
#endif // SL_CATALOG_ZIGBEE_SECURITY_MANAGER_DLK_ECC_TEST_VECTORS_PRESENT

static sl_status_t speke_init(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  int crypto_ret = mbedtls_ecp_group_load(&dlk_ecc_ctx->ecc_group, MBEDTLS_ECP_DP_CURVE25519);
  if (crypto_ret != 0) {
    return SL_STATUS_INITIALIZATION;
  }
  // "hash generator point"
  uint8_t speke_generator_data[DLK_ECC_COORDINATE_SIZE];
  mbedtls_ecp_point *g = &dlk_ecc_ctx->ecc_group.G;
  // hash psk in little endian
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    // perform a cyclic extension
    for (uint8_t i = 0; i < 2; i++) {
      EmberStatus status = emberAesHashSimple(DLK_KEY_SIZE, dlk_ecc_ctx->psk, speke_generator_data + (i * AES_HASH_DIGEST_LENGTH));
      if (status != 0) {
        return status;
      }
    }
  } else { // SHA256
    mbedtls_sha256(dlk_ecc_ctx->psk, DLK_KEY_SIZE, speke_generator_data, 0);
    // set byte[0] = 0x09
    speke_generator_data[0] = 0x09;
  }
  // set coordiantes of G
  crypto_ret = mbedtls_mpi_lset(&g->MBEDTLS_PRIVATE(Z), 1);
  if (crypto_ret != 0) {
    return SL_STATUS_FAIL;
  }
  crypto_ret = mbedtls_mpi_read_binary_le(&g->MBEDTLS_PRIVATE(X), speke_generator_data, DLK_ECC_COORDINATE_SIZE);
  return (crypto_ret == 0) ? SL_STATUS_OK : SL_STATUS_FAIL;
}

static sl_status_t speke_generate_keypair(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  (void) x25519_key_clamp;
  int crypto_ret = -1;
  bool clipped = false;
  if (dlk_ecc_ctx->config.curve_id == DLK_ECC_CURVE_25519) {
    // NOTE clearing the high bit of the generator point G forces it to fall into the canonical values Curve25519,
    // which prevents mbedtls from throwing an error.  We need to keep track of when we need to reset
    // the bit so we don't interfere with hashing operations later on.
    clipped = mbedtls_mpi_cmp_mpi(&dlk_ecc_ctx->ecc_group.G.MBEDTLS_PRIVATE(X), &dlk_ecc_ctx->ecc_group.P) == 1;
    crypto_ret = mbedtls_mpi_set_bit(&dlk_ecc_ctx->ecc_group.G.MBEDTLS_PRIVATE(X), dlk_ecc_ctx->ecc_group.pbits, 0);
    if (crypto_ret != 0) {
      return SL_STATUS_FAIL;
    }
  }
  if (dlk_ecc_ctx->test != NULL) {
    speke_test_vector_load_private_key(dlk_ecc_ctx);
  } else {
    crypto_ret = mbedtls_ecdh_gen_public(&dlk_ecc_ctx->ecc_group,
                                         &dlk_ecc_ctx->d,
                                         &dlk_ecc_ctx->Q,
                                         f_rng_wrapper,
                                         NULL);
  }
  if (crypto_ret != 0) {
    return SL_STATUS_FAIL;
  }
  if (clipped) {
    // NOTE restoring the high bit
    crypto_ret = mbedtls_mpi_set_bit(&dlk_ecc_ctx->ecc_group.G.MBEDTLS_PRIVATE(X), dlk_ecc_ctx->ecc_group.pbits, 1);
  }
  if (crypto_ret != 0) {
    return SL_STATUS_FAIL;
  }
  return SL_STATUS_OK;
}

// shared secret components
#define EUI64_SIZE 8
#define SESSION_ID_COMPONENT_LENGTH (EUI64_SIZE + DLK_ECC_COORDINATE_SIZE)
#define SESSION_IDENTITY_LENGTH (2 * SESSION_ID_COMPONENT_LENGTH)
#define SECRET_HASH_INPUT_LENGTH (2 * DLK_ECC_COORDINATE_SIZE + SESSION_IDENTITY_LENGTH)

// NOTE compare eui64 as uint64_t values
typedef union EUI64_u {
  uint64_t as_word;
  uint8_t as_bytes[EUI64_SIZE];
} EUI64_t;

typedef union {
  mbedtls_sha256_context sha;
  EmberAesMmoHashContext aes_mmo;
} dlk_ecc_hash_ctx_t;

sl_status_t sli_zb_sec_man_speke_expand_shared_secret(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx,
                                                      uint8_t *our_eui,
                                                      uint8_t *their_eui)
{
  int crypto_ret = -1;
  uint8_t hash_input[SESSION_IDENTITY_LENGTH];
  // == SPEKE shared secret
  // *) calculate session Identity I
  //      - determine order by comparing eui64, smaller goes first
  //      - I = A_min | Q_min | A_max | Q_max
  //      - concatenate together min | max
  // *) hash x_k | I | G
  // =====
  dlk_ecc_hash_ctx_t hash_ctx;
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    mbedtls_sha256_init(&hash_ctx.sha);
    // NOTE 0 == !is224
    mbedtls_sha256_starts(&hash_ctx.sha, 0);
  } else if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    emberAesMmoHashInit(&hash_ctx.aes_mmo);
  }
  // serialize x_k
  crypto_ret = mbedtls_mpi_write_binary_le(&dlk_ecc_ctx->x_k, hash_input, DLK_ECC_COORDINATE_SIZE);
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_WRITE;
  }
  // hash x_k to get a partial digest
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    crypto_ret = mbedtls_sha256_update(&hash_ctx.sha, hash_input, DLK_ECC_COORDINATE_SIZE);
    if (crypto_ret != 0) {
      return SL_STATUS_FAIL;
    }
  } else if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    EmberStatus em_status = emberAesMmoHashUpdate(&hash_ctx.aes_mmo, DLK_ECC_COORDINATE_SIZE, hash_input);
    if (em_status != EMBER_SUCCESS) {
      return SL_STATUS_FAIL;
    }
  }
  // construct session identity I
  uint8_t *identity_cursor = hash_input;
  // determine which component goes first
  EUI64_t our_eui_compare;
  memmove(our_eui_compare.as_bytes, our_eui, EUI64_SIZE);
  EUI64_t their_eui_compare;
  memmove(their_eui_compare.as_bytes, their_eui, EUI64_SIZE);
  // NOTE technically euis cannot be equal because then they would not be unique
  EUI64_t *first_component = their_eui_compare.as_word < our_eui_compare.as_word ? &their_eui_compare : &our_eui_compare;
  EUI64_t *second_component = their_eui_compare.as_word < our_eui_compare.as_word ? &our_eui_compare : &their_eui_compare;
  // NOTE polarity here matches export_public_key
  bool get_peer = first_component->as_word == their_eui_compare.as_word;
  // serialize the first I component (EUI followed by public key)
  memmove(identity_cursor, first_component->as_bytes, EUI64_SIZE);
  identity_cursor += EUI64_SIZE;
  size_t public_key_len;
  sl_status_t status = sli_zb_sec_man_ecc_export_public_key(dlk_ecc_ctx, get_peer, identity_cursor, &public_key_len);
  if (status != SL_STATUS_OK) {
    return status;
  }
  identity_cursor += public_key_len;
  // reverse the order and repeat
  get_peer = !get_peer;
  // serialize the second I component (EUI followed by public key)
  memmove(identity_cursor, second_component->as_bytes, EUI64_SIZE);
  identity_cursor += EUI64_SIZE;
  status = sli_zb_sec_man_ecc_export_public_key(dlk_ecc_ctx, get_peer, identity_cursor, &public_key_len);
  if (status != SL_STATUS_OK) {
    return status;
  }
  // hash the entirety of I
  // NOTE due to a restriction on 'emberAesMmoHashUpdate' input must align with a 16-byte block
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    crypto_ret = mbedtls_sha256_update(&hash_ctx.sha, hash_input, SESSION_IDENTITY_LENGTH);
    if (crypto_ret != 0) {
      return SL_STATUS_FAIL;
    }
  } else if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    EmberStatus em_status = emberAesMmoHashUpdate(&hash_ctx.aes_mmo, SESSION_IDENTITY_LENGTH, hash_input);
    if (em_status != EMBER_SUCCESS) {
      return SL_STATUS_FAIL;
    }
  }
  // serialize and hash the Generator point G
  crypto_ret = mbedtls_mpi_write_binary_le(&dlk_ecc_ctx->ecc_group.G.MBEDTLS_PRIVATE(X), hash_input, DLK_ECC_COORDINATE_SIZE);
  if (crypto_ret != 0) {
    return SL_STATUS_OBJECT_WRITE;
  }
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    crypto_ret = mbedtls_sha256_update(&hash_ctx.sha, hash_input, DLK_ECC_COORDINATE_SIZE);
    if (crypto_ret != 0) {
      return SL_STATUS_FAIL;
    }
    crypto_ret = mbedtls_sha256_finish(&hash_ctx.sha, dlk_ecc_ctx->secret);
    if (crypto_ret != 0) {
      return SL_STATUS_FAIL;
    }
  } else if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    EmberStatus em_status = emberAesMmoHashUpdate(&hash_ctx.aes_mmo, DLK_ECC_COORDINATE_SIZE, hash_input);
    if (em_status != EMBER_SUCCESS) {
      return SL_STATUS_FAIL;
    }
    em_status = emberAesMmoHashFinal(&hash_ctx.aes_mmo, 0, NULL);
    if (em_status != EMBER_SUCCESS) {
      return SL_STATUS_FAIL;
    }
    memmove(dlk_ecc_ctx->secret, hash_ctx.aes_mmo.result, EMBER_AES_HASH_BLOCK_SIZE);
  }
  return SL_STATUS_OK;
}

static sl_status_t speke_derive_link_key(sli_zb_sec_man_dlk_ecc_context_t *dlk_ecc_ctx)
{
  // run the secret through KDF with input {1}
  uint8_t data[1] = { 1 };
  if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_AES_MMO_128) {
    emberHmacAesHash(dlk_ecc_ctx->secret, data, 1, dlk_ecc_ctx->derived_key);
  } else if (dlk_ecc_ctx->config.hash_id == DLK_ECC_HASH_SHA_256) {
    uint8_t sha_digest[SHA_HASH_DIGEST_LENGTH];
    sl_zb_sec_man_hmac_sha_256(dlk_ecc_ctx->secret, MAX_SHARED_SECRET_LEN, data, 1, sha_digest);
    memmove(dlk_ecc_ctx->derived_key, sha_digest, DLK_KEY_SIZE);
  } else {
    // UNREACHABLE
    return SL_STATUS_NOT_SUPPORTED;
  }
  return SL_STATUS_OK;
}

#define HMAC_SHA_256_BLOCK_SIZE 64
// NOTE relocate / consolidate
static void xorKeyWithByte(uint8_t *key,
                           uint8_t byte,
                           uint8_t *result)
{
  int i;
  for (i = 0; i < HMAC_SHA_256_BLOCK_SIZE; i++) {
    result[i] = key[i] ^ byte;
  }
}

static void sli_hmac_sha_256_impl(mbedtls_sha256_context *sha_ctx,
                                  uint8_t *key,
                                  uint8_t keyLength,
                                  uint8_t *data,
                                  uint8_t dataLength,
                                  uint8_t *result)
{
  uint8_t buffer[HMAC_SHA_256_BLOCK_SIZE];
  uint8_t keyp[HMAC_SHA_256_BLOCK_SIZE];
  uint8_t run;

  if (keyLength > HMAC_SHA_256_BLOCK_SIZE) {
    // hash keys longer than BLOCK_SIZE
    mbedtls_sha256_starts(sha_ctx, 0);
    mbedtls_sha256_update(sha_ctx, key, keyLength);
    mbedtls_sha256_finish(sha_ctx, keyp);
  }
  if (keyLength < HMAC_SHA_256_BLOCK_SIZE) {
    // pad short keys with 0
    MEMCOPY(keyp, key, keyLength);
    MEMSET(keyp + keyLength, 0, HMAC_SHA_256_BLOCK_SIZE - keyLength);
  }

  for (run = 0; run < 2; run++) {
    // produce inner/outer xord key
    xorKeyWithByte(keyp,
                   (run == 0 ? 0x36 : 0x5c),
                   buffer);
    // run the hash to produce the result
    mbedtls_sha256_starts(sha_ctx, 0);
    mbedtls_sha256_update(sha_ctx, buffer, HMAC_SHA_256_BLOCK_SIZE);
    if (run == 0) {
      mbedtls_sha256_update(sha_ctx, data, dataLength);
    } else {
      mbedtls_sha256_update(sha_ctx, result, HMAC_SHA_256_OUTPUT_SIZE);
    }
    mbedtls_sha256_finish(sha_ctx, result);
  }
}

void sl_zb_sec_man_hmac_sha_256(uint8_t *key,
                                uint8_t key_len,
                                uint8_t *data,
                                uint8_t data_len,
                                uint8_t *result)
{
  mbedtls_sha256_context sha_ctx;
  mbedtls_sha256_init(&sha_ctx);
  sli_hmac_sha_256_impl(&sha_ctx, key, key_len, data, data_len, result);
  mbedtls_sha256_free(&sha_ctx);
}
