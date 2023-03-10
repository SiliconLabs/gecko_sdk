/***************************************************************************//**
 * @file app_psa_attestation.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "app_psa_attestation.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
/***************************************************************************//**
 * @brief
 *   Parse and optionally pretty-print CBOR data.
 *
 * @param[in] cbor_data
 *   Buffer containing CBOR data.
 *
 * @param[out] nbytes_read
 *   Number of bytes read and parsed from buffer.
 *
 * @param[in] print_flag
 *   If set, print data while parsing.
 *
 * @param[in] indent_lvl
 *   Indentation level used when printing.
 *
 * @param[in] indent_width
 *   Indentation width. Number of whitespace characters per indentation level.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
static psa_status_t cbor_parse(uint8_t *cbor_data,
                               size_t *nbytes_read,
                               bool print_flag,
                               uint8_t indent_lvl,
                               uint8_t indent_width);

/***************************************************************************//**
 * @brief
 *   Parse CBOR major type and argument.
 *
 * @param[in] cbor_data
 *   Buffer containing CBOR data.
 *
 * @param[out] maj_type
 *   Pointer to uint8_t for storing major type.
 *
 * @param[out] arg
 *   Pointer to uint64_t for storing argument.
 *
 * @param[out] nbytes_read
 *   Number of bytes read and parsed from buffer.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
static psa_status_t cbor_parse_maj_and_arg(uint8_t *cbor_data,
                                           uint8_t *maj_type,
                                           uint64_t *arg,
                                           size_t *nbytes_read);

/***************************************************************************//**
 * @brief
 *   Parse and pretty-print CBOR data.
 *
 * @param[in] cbor_data
 *   Buffer containing CBOR data.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
static psa_status_t cbor_pretty_print(uint8_t *cbor_data);

/***************************************************************************//**
 * @brief
 *   Parse and pretty-print claims from attestation token.
 *
 * @param[in] token_data
 *   Buffer containing CBOR-encoded token.
 *
 * @returns Returns PSA error code, @ref crypto_values.h.
 ******************************************************************************/
static psa_status_t token_claims_pretty_print(uint8_t *token_data);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Buffer for nonce/challenge
static uint8_t nonce_buf[PSA_INITIAL_ATTEST_CHALLENGE_SIZE_64];

/// Buffer for PSA Attestation Token
static uint8_t token_buf[PSA_INITIAL_ATTEST_MAX_TOKEN_SIZE];

/// Buffer for Public Attestation Key in uncompressed point format
static uint8_t pub_key_buf[65];

/// Size of actual PSA Attestation Token in bytes
static size_t token_size;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Get size of the PSA Attestation Token.
 ******************************************************************************/
size_t get_token_size(void)
{
  return token_size;
}

/***************************************************************************//**
 * Generate random numbers and save them to a buffer.
 ******************************************************************************/
psa_status_t generate_random_number(uint32_t size)
{
  print_error_cycle(psa_generate_random(nonce_buf, size));
}

/***************************************************************************//**
 *   Print the nonce.
 ******************************************************************************/
void print_nonce(uint32_t size)
{
  size_t i;

  for (i = 0; i < size; i++) {
    if ((i % 32) == 0) {
      printf("\n%*s", 4, "");
    }
    printf("%02x ", nonce_buf[i]);
  }
  printf("\n");
}

/***************************************************************************//**
 * Get the size of the PSA Attestation Token.
 ******************************************************************************/
psa_status_t get_attested_token_size(size_t nonce_size)
{
  print_error_cycle(psa_initial_attest_get_token_size(nonce_size,
                                                      &token_size));
}

/***************************************************************************//**
 * Get the PSA Attestation Token.
 ******************************************************************************/
psa_status_t get_attested_token(size_t nonce_size)
{
  print_error_cycle(psa_initial_attest_get_token(nonce_buf,
                                                 nonce_size,
                                                 token_buf,
                                                 sizeof(token_buf),
                                                 &token_size));
}

/***************************************************************************//**
 *   Get the Public Attestation Key.
 ******************************************************************************/
psa_status_t get_public_attestation_key(void)
{
  print_error_cycle(sl_tz_attestation_get_public_key(pub_key_buf,
                                                     sizeof(pub_key_buf)));
}

/***************************************************************************//**
 *   Print the Public Attestation Key.
 ******************************************************************************/
void print_pub_key(void)
{
  size_t i;

  printf("%*s", 4, "");
  // Start from index 1 to skip the first byte for uncompressed point format
  for (i = 1; i < sizeof(pub_key_buf); i++) {
    if ((i % 33) == 0) {
      printf("\n%*s", 4, "");
    }
    printf("%02x ", pub_key_buf[i]);
  }
  printf("\n");
}

/***************************************************************************//**
 * Print attestation token and claims in both raw and human-readable format.
 ******************************************************************************/
psa_status_t print_attestation_token(void)
{
  size_t i;
  psa_status_t ret;

  printf("\nPSA Attestation Token \n");
  printf("==========================\n");
  printf("-------------------------------------------------------------------");
  printf("\nRaw token:");
  for (i = 0; i < token_size; i++) {
    if ((i % 32) == 0) {
      printf("\n%*s", 2, "");
    }
    printf("%02x ", token_buf[i]);
  }
  printf("\n\n");

  printf("COSE_Sign1 structure:\n");
  ret = cbor_pretty_print(token_buf);

  if (ret == PSA_ERROR_GENERIC_ERROR) {
    printf("[ERROR] CBOR: Not well-formed / implemented.\n");
    return ret;
  }

  printf("-------------------------------------------------------------------");
  ret = token_claims_pretty_print(token_buf);
  printf("-------------------------------------------------------------------");
  printf("\n");

  if (ret == PSA_ERROR_GENERIC_ERROR) {
    printf("[ERROR] Invalid COSE_Sign1 structure.\n");
  }
  return ret;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
/***************************************************************************//**
 * Parse and optionally pretty-print CBOR data.
 ******************************************************************************/
static psa_status_t cbor_parse(uint8_t *cbor_data,
                               size_t *nbytes_read,
                               bool print_flag,
                               uint8_t indent_lvl,
                               uint8_t indent_width)
{
  uint8_t maj_type;
  uint8_t *data_ptr;
  uint64_t arg;
  size_t item_size, nitems_in_queue;
  psa_status_t ret;
  size_t i;

  data_ptr = cbor_data;

  // Parse major type and argument of current CBOR item
  ret = cbor_parse_maj_and_arg(data_ptr, &maj_type, &arg, &item_size);
  if (ret != PSA_SUCCESS) {
    return ret;
  }
  data_ptr += item_size;

  if (print_flag) {
    printf("%*s%02x", indent_lvl * indent_width, "", cbor_data[0]);
  }

  nitems_in_queue = 0;

  switch (maj_type) {
    case CBOR_UNSIGNED_INT:
      if (print_flag) {
        printf("    ; int(%" PRIu64 ")\n", arg);
      }
      break;

    case CBOR_NEGATIVE_INT:
      if (print_flag) {
        printf("    ; int(%" PRIi64 ")\n", -(arg + 1));
      }
      break;

    case CBOR_BYTE_STR:
      if (print_flag) {
        printf("    ; byte_str(%" PRIu64 ")", arg);
        for (i = 0; i < arg; i++) {
          if ((i % 32) == 0) {
            printf("\n%*s", (indent_lvl + 1) * indent_width, "");
          }
          printf("%02x ", *(data_ptr++));
        }
        printf("\n");
      } else {
        data_ptr += arg;
      }
      break;

    case CBOR_TEXT_STR:
      if (print_flag) {
        printf("    ; text_str(%" PRIu64 ")\n", arg);
        printf("%*s\"", (indent_lvl + 1) * indent_width, "");
        for (i = 0; i < arg; i++) {
          printf("%c", *(data_ptr++));
        }
        printf("\"\n");
      } else {
        data_ptr += arg;
      }
      break;

    case CBOR_ARRAY:
      if (print_flag) {
        printf("    ; array(%" PRIu64 ")\n", arg);
      }
      nitems_in_queue = arg;
      break;

    case CBOR_MAP:
      if (print_flag) {
        printf("    ; map(%" PRIu64 ")\n", arg);
      }
      nitems_in_queue = 2 * arg;
      break;

    case CBOR_TAG:
      if (print_flag) {
        printf("    ; tag(%" PRIu64 ")\n", arg);
      }
      nitems_in_queue = 1;
      break;

    case CBOR_SIMPLE_FLOAT:

    default:
      return PSA_ERROR_GENERIC_ERROR;
  }

  // Parse queued items from CBOR array, map or tag types.
  while (nitems_in_queue--) {
    ret = cbor_parse(data_ptr,
                     &item_size,
                     print_flag,
                     indent_lvl + 1,
                     indent_width);

    if (ret != PSA_SUCCESS) {
      return ret;
    }

    data_ptr += item_size;
  }

  *nbytes_read = data_ptr - cbor_data;

  return PSA_SUCCESS;
}

/***************************************************************************//**
 * Parse CBOR major type and argument.
 ******************************************************************************/
static psa_status_t cbor_parse_maj_and_arg(uint8_t *cbor_data,
                                           uint8_t *maj_type,
                                           uint64_t *arg,
                                           size_t *nbytes_read)
{
  uint8_t add_info, arg_nbytes;
  uint8_t *data_ptr;

  data_ptr = cbor_data;
  *maj_type = *data_ptr >> 5; // High-order 3 bits
  add_info = *data_ptr & 0x1f; // Low-order 5 bits
  data_ptr++;

  *arg = 0;
  arg_nbytes = 0;

  if (add_info < 24) {
    *arg = add_info;
  } else if (add_info == 24) {
    arg_nbytes = 1;
  } else if (add_info == 25) {
    arg_nbytes = 2;
  } else if (add_info == 26) {
    arg_nbytes = 4;
  } else if (add_info == 27) {
    arg_nbytes = 8;
  } else {
    return PSA_ERROR_GENERIC_ERROR;
  }

  while (0 < arg_nbytes--) { // Read argument in network byte order
    *arg = (*arg << 8) | *(data_ptr++);
  }

  *nbytes_read = data_ptr - cbor_data;

  return PSA_SUCCESS;
}

/***************************************************************************//**
 * Parse and pretty-print CBOR data.
 ******************************************************************************/
static psa_status_t cbor_pretty_print(uint8_t *cbor_data)
{
  size_t nbytes_read = 0;
  return cbor_parse(cbor_data, &nbytes_read, true, 0, 2);
}

/***************************************************************************//**
 * Parse and pretty-print claims from attestation token.
 ******************************************************************************/
static psa_status_t token_claims_pretty_print(uint8_t *token_data)
{
  uint8_t maj_type;
  uint8_t *data_ptr;
  uint64_t arg;
  uint32_t nclaims;
  int64_t claim_id;
  size_t item_size;
  psa_status_t ret;

  if (token_data[0] != 0xd2 || token_data[1] != 0x84) {
    return PSA_ERROR_GENERIC_ERROR;
  }

  data_ptr = token_data + 2;

  // Skip protected header parameters
  ret = cbor_parse(data_ptr, &item_size, false, 0, 0);
  if (ret != PSA_SUCCESS) {
    return ret;
  }
  data_ptr += item_size;

  // Skip unprotected header parameters
  ret = cbor_parse(data_ptr, &item_size, false, 0, 0);
  if (ret != PSA_SUCCESS) {
    return ret;
  }
  data_ptr += item_size;

  // Unwrap byte string containing CBOR-encoded claims
  ret = cbor_parse_maj_and_arg(data_ptr, &maj_type, &arg, &item_size);
  if (ret != PSA_SUCCESS) {
    return ret;
  }
  data_ptr += item_size;

  if (maj_type != CBOR_BYTE_STR) {
    return PSA_ERROR_GENERIC_ERROR;
  }

  printf("\nToken claims:\n");
  cbor_pretty_print(data_ptr);

  // Parse and pretty-print the map data structure containing the claims
  printf("\nList of claims printed with human-friendly names:");
  ret = cbor_parse_maj_and_arg(data_ptr, &maj_type, &arg, &item_size);
  if (ret != PSA_SUCCESS) {
    return ret;
  }
  data_ptr += item_size;

  if (maj_type != CBOR_MAP) {
    return PSA_ERROR_GENERIC_ERROR;
  }

  nclaims = arg;
  for (uint32_t i = 0; i < nclaims; i++) {
    // Parse claim ID integer
    ret = cbor_parse_maj_and_arg(data_ptr, &maj_type, &arg, &item_size);
    if (ret != PSA_SUCCESS) {
      return ret;
    }
    data_ptr += item_size;

    if (maj_type == CBOR_UNSIGNED_INT) {
      claim_id = arg;
    } else if (maj_type == CBOR_NEGATIVE_INT) {
      claim_id = -(arg + 1);
    } else {
      return PSA_ERROR_GENERIC_ERROR;
    }

    // Parse and pretty-print claim
    printf("\n  ");
    switch (claim_id) {
      case CLAIM_ARM_PSA_PROFILE_ID:
      case CLAIM_ARM_PSA_PROFILE_ID_P1:
        printf("Profile Definition");
        break;

      case CLAIM_ARM_PSA_PARTITION_ID:
      case CLAIM_ARM_PSA_PARTITION_ID_P1:
        printf("Client ID");
        break;

      case CLAIM_ARM_PSA_LIFECYCLE:
      case CLAIM_ARM_PSA_LIFECYCLE_P1:
        printf("Security Lifecycle");
        break;

      case CLAIM_ARM_PSA_IMPLEMENTATION_ID:
      case CLAIM_ARM_PSA_IMPLEMENTATION_ID_P1:
        printf("Implementation ID");
        break;

      case CLAIM_ARM_PSA_BOOT_SEED:
      case CLAIM_ARM_PSA_BOOT_SEED_P1:
        printf("Boot seed");
        break;

      case CLAIM_ARM_PSA_SW_COMPONENTS:
      case CLAIM_ARM_PSA_SW_COMPONENTS_P1:
        printf("Software Components");
        break;

      case CLAIM_ARM_PSA_NONCE:
      case CLAIM_ARM_PSA_NONCE_P1:
        printf("Nonce");
        break;

      case CLAIM_ARM_PSA_IETF_EAT_UEID:
      case CLAIM_ARM_PSA_IETF_EAT_UEID_P1:
        printf("Instance ID");
        break;

      default:
        printf("(UNKNOWN CLAIM)");
        break;
    }

    printf(", Claim ID: %" PRIi64 "\n", claim_id);

    ret = cbor_parse(data_ptr, &item_size, true, 1, 2);
    if (ret != PSA_SUCCESS) {
      return ret;
    }
    data_ptr += item_size;
  }

  return PSA_SUCCESS;
}
