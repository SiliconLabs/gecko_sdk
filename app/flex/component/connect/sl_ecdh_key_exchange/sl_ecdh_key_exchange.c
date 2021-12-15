/***************************************************************************//**
 * @file
 * @brief ECDH Key exchange component related source.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <string.h>
#include PLATFORM_HEADER
#include "hal/hal.h"
#include "mbedtls/ecdh.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/private_access.h"
#include "sl_ecdh_key_exchange.h"

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if SL_CONNECT_DEBUG_ECDH_PRINT_ENABLED == 1
  #include <stdarg.h>
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
static bool sl_peer_key_secret_generate(mbedtls_ecdh_context *peerCtx,
                                        unsigned char *ecpPointX,
                                        unsigned char *ecpPointY);
static bool sl_shared_key_load(uint8_t *key);

static bool sl_ecdh_context_init(mbedtls_ecdh_context *peerCtx,
                                 unsigned char *ecpPointX,
                                 unsigned char *ecpPointY);

static bool sl_random_number_seed(void);
static void sl_ecdh_context_reset(void);
static void sl_log(const char *fmt, ...);
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static mbedtls_ecdh_context ecdh_context;
static mbedtls_entropy_context entropy_context;
static mbedtls_ctr_drbg_context ctrDrbg;

/// The device's own public key X point buffer
static uint8_t public_x_local_key_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];
/// The device's own public key Y point buffer
static uint8_t public_y_local_key_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];
/// The other device's public key X point buffer
static uint8_t public_x_remote_key_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];
/// The other device's public key Y point buffer
static uint8_t public_y_remote_key_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];

/// Shared secret buffer
static uint8_t shared_secret_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];
/// Shared key buffer, it is calculated from shared secret by SHA256
static uint8_t shared_key_buffer[SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES];

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * Getter function of the shared key buffer.
 *
 * @return The pointer of the shared key buffer.
 *
 *****************************************************************************/
uint8_t* sl_ecdh_key_exchange_shared_key_get(void)
{
  return shared_key_buffer;
}

/**************************************************************************//**
 * Key Exchange component init function.
 *
 * @param arguments Contains the requested node id to be set, which must be
 * an integer.
 * @return If success SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK,
 * else SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR
 *
 * Initialize the randum number generator engine for the mbedTLS and generates
 * a public and private key pair for the device.
 *
 *****************************************************************************/
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_init(void)
{
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK;

  if (sl_random_number_seed() == true) {
    if (sl_ecdh_context_init(&ecdh_context, public_x_local_key_buffer, public_y_local_key_buffer) == true) {
      sl_log("Key generation complete\n");
    } else {
      sl_ecdh_context_reset();
      retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;
    }
  } else {
    sl_ecdh_context_reset();
    retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;
  }

  return retval;
}

/**************************************************************************//**
 * Shared key genaration.
 *
 * @return If success SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK,
 * else SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR
 *
 * Generates the shared key based on the device's key pair and the received
 * public key from the remote device.
 *
 *****************************************************************************/
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_shared_key_generate(void)
{
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK;

  if (sl_peer_key_secret_generate(&ecdh_context, public_x_remote_key_buffer, public_y_remote_key_buffer) == true) {
    if (sl_shared_key_load(shared_secret_buffer) == true) {
      mbedtls_sha256(shared_secret_buffer, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES, shared_key_buffer, 0);
    } else {
      retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;
    }
  } else {
    retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;
  }

  return retval;
}

/**************************************************************************//**
 * Getter function for key buffers
 *
 * @param i_buffer_id an id for the required buffer
 * @return if i_buffer_id is valid pointer to the buffer, else NULL
 *
 *
 *****************************************************************************/
uint8_t* sl_ecdh_key_exchange_buffer_get(SL_ECDH_KEY_EXCHANGE_BUFFER i_buffer_id)
{
  uint8_t* retPointer = NULL;

  switch (i_buffer_id) {
    case SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXLOCAL:  retPointer = public_x_local_key_buffer; break;
    case SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYLOCAL:  retPointer = public_y_local_key_buffer; break;
    case SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICXREMOTE: retPointer = public_x_remote_key_buffer; break;
    case SL_ECDH_KEY_EXCHANGE_BUFFER_PUBLICYREMOTE: retPointer = public_y_remote_key_buffer; break;
    default:
      break;
  }

  return retPointer;
}

/**************************************************************************//**
 * Encrypts the network key with AES
 *
 * @param i_network_key non encrypted network key buffer
 * @param o_network_key_encrypted encrypted network key buffer
 * @return If success SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK, else if the AES
 * parameters are wrong SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR_UNSUPPORTED_KEY_SIZE
 *
 *****************************************************************************/
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_network_key_encrypt(uint8_t* i_network_key, uint8_t* o_network_key_encrypted)
{
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;

  if (i_network_key != NULL && o_network_key_encrypted != NULL) {
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);

    if ( mbedtls_aes_setkey_enc(&ctx, shared_key_buffer, SL_ECDH_KEY_EXCHANGE_ENCRYPTION_KEY_SIZE_BITS) == 0 ) {
      if (mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_ENCRYPT, i_network_key, o_network_key_encrypted) == 0) {
        retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK;
      }      
    } else {
      retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR_UNSUPPORTED_KEY_SIZE;
    }
  }

  return retval;
}

/**************************************************************************//**
 * Decrypts the network key with AES
 *
 * @param i_encrypted_buffer encrypted network key buffer
 * @param o_decrypted_buffer decrypted network key buffer
 * @return If success SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK, else if the AES
 * parameters are wrong SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR_UNSUPPORTED_KEY_SIZE
 *
 *****************************************************************************/
SL_ECDH_KEY_EXCHANGE_RETURN_VALUE sl_ecdh_key_exchange_network_key_decrypt(uint8_t* i_encrypted_buffer, uint8_t* o_decrypted_buffer)
{
  SL_ECDH_KEY_EXCHANGE_RETURN_VALUE retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR;

  if ((i_encrypted_buffer != NULL) && (o_decrypted_buffer != NULL)) {
    mbedtls_aes_context ctx;
    mbedtls_aes_init(&ctx);

    if ( mbedtls_aes_setkey_dec(&ctx, shared_key_buffer, SL_ECDH_KEY_EXCHANGE_ENCRYPTION_KEY_SIZE_BITS) == 0) {
      if (mbedtls_aes_crypt_ecb(&ctx, MBEDTLS_AES_DECRYPT, i_encrypted_buffer, o_decrypted_buffer) == 0) {
        retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_OK;
      }
    } else {
      retval = SL_ECDH_KEY_EXCHANGE_RETURN_VALUE_ERROR_UNSUPPORTED_KEY_SIZE;
    }
  }

  return retval;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Use peer's key to generate shared secret
 * @param peerCtr Pointer to ECDH context
 * @param ecpPointX Pointer to ECP point X buffer
 * @param ecpPointY Pointer to ECP point Y buffer
 * @return true if successful and false otherwise.
 ******************************************************************************/
static bool sl_peer_key_secret_generate(mbedtls_ecdh_context *peerCtx,
                                        unsigned char *ecpPointX,
                                        unsigned char *ecpPointY)
{
  int ret;
  sl_log("Reading public key and computing secret...\n");

  // Read peer's key and generate shared secret
  ret = mbedtls_mpi_lset(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Qp).MBEDTLS_PRIVATE(Z), 1);
  if (ret != 0) {
    sl_log("mbedtls_mpi_lset returned %d\n", ret);
    return false;
  }

  // Read peer's X coordinate of the ECP point
  ret = mbedtls_mpi_read_binary(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Qp).MBEDTLS_PRIVATE(X), ecpPointX, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
  if (ret != 0) {
    sl_log("mbedtls_mpi_read_binary returned %d\n", ret);
    return false;
  }

  // Read peer's Y coordinate of the ECP point
  ret = mbedtls_mpi_read_binary(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Qp).MBEDTLS_PRIVATE(Y), ecpPointY, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
  if (ret != 0) {
    sl_log("mbedtls_mpi_read_binary returned %d\n", ret);
    return false;
  }

  // Com  pute the shared secret to peerCtx.z
#if defined(_SILICON_LABS_32B_SERIES_2)
  ret = mbedtls_ecdh_compute_shared(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(grp), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(z),
                                    &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Qp), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(d),
                                    NULL, &ctrDrbg);
#else
  ret = mbedtls_ecdh_compute_shared(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(grp), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(z),
                                    &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Qp), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(d),
                                    mbedtls_ctr_drbg_random, &ctrDrbg);
#endif

  if (ret != 0) {
    sl_log("mbedtls_ecdh_compute_shared returned %d\n", ret);
    return false;
  }

  return true;
}

/***************************************************************************//**
 * @brief Verify shared secret between client and server
 * @return true if successful and false otherwise.
 ******************************************************************************/
static bool sl_shared_key_load(uint8_t *key)
{
  int ret;
  (void)key;

  // Convert the shared secret into binary
  ret = mbedtls_mpi_write_binary(&ecdh_context.MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(z), key, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
  if (ret != 0) {
    sl_log("mbedtls_mpi_write_binary returned %d\n", ret);
    return false;
  }

  return true;
}

/***************************************************************************//**
 * Setup ECDH
 * @param peerCtr Pointer to ECDH context
 * @param ecpPointX Pointer to ECP point X buffer
 * @param ecpPointY Pointer to ECP point Y buffer
 * @return true if successful and false otherwise.
 ******************************************************************************/
static bool sl_ecdh_context_init(mbedtls_ecdh_context *peerCtx,
                                 unsigned char *ecpPointX,
                                 unsigned char *ecpPointY)
{
  int ret;

  sl_log("Generating keys...\n");

  // Initialize the ECDH context
  mbedtls_ecdh_init(peerCtx);

  // Setup an ECP (Elliptic Curves over Prime) group context
  // from a specific elliptic curve
  ret = mbedtls_ecp_group_load(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(grp), MBEDTLS_ECP_DP_SECP256R1);
  if (ret != 0) {
    sl_log("mbedtls_ecp_group_load returned %d\n", ret);
    return false;
  }

  // Generate an ECDH keypair on an elliptic curve
  // Private key in peerCtx.d and public key in peerCtx.Q
  ret = mbedtls_ecdh_gen_public(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(grp), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(d), &peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Q),
                                mbedtls_ctr_drbg_random, &ctrDrbg);

  if (ret != 0) {
    sl_log("mbedtls_ecdh_gen_public returned %d\n", ret);
    return false;
  }

  // Convert X coordinate of the ECP point into unsigned binary data
  ret = mbedtls_mpi_write_binary(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Q).MBEDTLS_PRIVATE(X), ecpPointX, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
  if (ret != 0) {
    sl_log("mbedtls_mpi_write_binary returned %d\n", ret);
    return false;
  }

  // Convert Y coordinate of the ECP point into unsigned binary data
  ret = mbedtls_mpi_write_binary(&peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(Q).MBEDTLS_PRIVATE(Y), ecpPointY, SL_ECDH_KEY_EXCHANGE_KEY_SIZE_BYTES);
  if (ret != 0) {
    sl_log("mbedtls_mpi_write_binary returned %d\n", ret);
    return false;
  }

  sl_log("Key size: %d bits\n", (int)peerCtx->MBEDTLS_PRIVATE(ctx).MBEDTLS_PRIVATE(mbed_ecdh).MBEDTLS_PRIVATE(grp).pbits);

  return true;
}

/***************************************************************************//**
 * Clear the context structures for ECDH
 ******************************************************************************/
static void sl_ecdh_context_reset(void)
{
  mbedtls_entropy_free(&entropy_context);
  mbedtls_ctr_drbg_free(&ctrDrbg);
  mbedtls_ecdh_free(&ecdh_context);
}

/***************************************************************************//**
 * Seed random number for ECDH
 * @return true if successful and false otherwise.
 ******************************************************************************/
static bool sl_random_number_seed(void)
{
  int ret;
  const char pers[] = "ecdh"; // String for CTR_DRBG

  sl_log("Seeding the random number generator...\n");

  // Initialize entropy and CTR_DRBG contexts
  mbedtls_entropy_init(&entropy_context);
  mbedtls_ctr_drbg_init(&ctrDrbg);

  // Setup the CTR_DRBG entropy source for first seed and future re-seeds
  if ((ret = mbedtls_ctr_drbg_seed(&ctrDrbg, mbedtls_entropy_func,
                                   &entropy_context,
                                   (const unsigned char *)pers,
                                   sizeof(pers))) != 0) {
    sl_log("mbedtls_ctr_drbg_seed returned %d\n", ret);
    return false;
  }

  return true;
}

static void sl_log(const char *fmt, ...)
{
#if SL_CONNECT_DEBUG_ECDH_PRINT_ENABLED == 1
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
#endif
}
