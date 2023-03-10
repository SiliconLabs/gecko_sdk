/***************************************************************************//**
 * @file app_psa_attestation.h
 * @brief PSA attestation functions.
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
#ifndef APP_PSA_ATTESTATION_H
#define APP_PSA_ATTESTATION_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "psa/initial_attestation.h"
#include "sl_tz_attestation.h"
#include "app_psa_crypto_key.h"
#include "app_psa_crypto_macro.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
// Claim ID for PSA 2.0.0
typedef enum {
  CLAIM_ARM_PSA_PROFILE_ID              = 265,
  CLAIM_ARM_PSA_PARTITION_ID            = 2394,
  CLAIM_ARM_PSA_LIFECYCLE               = 2395,
  CLAIM_ARM_PSA_IMPLEMENTATION_ID       = 2396,
  CLAIM_ARM_PSA_BOOT_SEED               = 2397,
  CLAIM_ARM_PSA_SW_COMPONENTS           = 2399,
  CLAIM_ARM_PSA_NONCE                   = 10,
  CLAIM_ARM_PSA_IETF_EAT_UEID           = 256,
} attestation_claim_id_t;

// Claim ID for PSA_IOT_PROFILE_1
typedef enum {
  CLAIM_ARM_PSA_PROFILE_ID_P1           = -75000,
  CLAIM_ARM_PSA_PARTITION_ID_P1         = -75001,
  CLAIM_ARM_PSA_LIFECYCLE_P1            = -75002,
  CLAIM_ARM_PSA_IMPLEMENTATION_ID_P1    = -75003,
  CLAIM_ARM_PSA_BOOT_SEED_P1            = -75004,
  CLAIM_ARM_PSA_SW_COMPONENTS_P1        = -75006,
  CLAIM_ARM_PSA_NONCE_P1                = -75008,
  CLAIM_ARM_PSA_IETF_EAT_UEID_P1        = -75009,
} attestation_claim_id_p1_t;

typedef enum {
  CBOR_UNSIGNED_INT,
  CBOR_NEGATIVE_INT,
  CBOR_BYTE_STR,
  CBOR_TEXT_STR,
  CBOR_ARRAY,
  CBOR_MAP,
  CBOR_TAG,
  CBOR_SIMPLE_FLOAT
} cbor_major_type_t;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Get size of the PSA Attestation Token.
 *
 * @returns Returns size of the PSA Attestation Token.
 ******************************************************************************/
size_t get_token_size(void);

/***************************************************************************//**
 * Generate random numbers and save them to a buffer.
 *
 * @param[in] size
 *   Size of randomly generated number in bytes.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
psa_status_t generate_random_number(uint32_t size);

/***************************************************************************//**
 *   Print the nonce.
 *
 * @param[in] size
 *   Size of nonce in bytes.
 *
 * @returns void.
 ******************************************************************************/
void print_nonce(uint32_t size);

/***************************************************************************//**
 * @brief
 *   Get the size of the PSA Attestation Token.
 *
 * @param[in] nonce_size
 *   Size of randomly generated nonce/challenge in bytes.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
psa_status_t get_attested_token_size(size_t nonce_size);

/***************************************************************************//**
 * @brief
 *   Get the PSA Attestation Token.
 *
 * @param[in] nonce_size
 *   Size of randomly generated nonce/challenge in bytes.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
psa_status_t get_attested_token(size_t nonce_size);

/***************************************************************************//**
 * @brief
 *   Get the Public Attestation Key.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
psa_status_t get_public_attestation_key(void);

/***************************************************************************//**
 * @brief
 *   Print the Public Attestation Key.
 *
 * @returns void.
 ******************************************************************************/
void print_pub_key(void);

/***************************************************************************//**
 * @brief
 *   Print attestation token and claims in both raw and human-readable format.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
psa_status_t print_attestation_token(void);

#endif  // APP_PSA_ATTESTATION_H
