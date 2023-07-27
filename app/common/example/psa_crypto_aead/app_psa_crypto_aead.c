/***************************************************************************//**
 * @file app_psa_crypto_aead.c
 * @brief PSA Crypto AEAD functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "app_psa_crypto_aead.h"

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

/// Debug output template
static inline psa_status_t print_aead_error(psa_status_t ret)
{
  if (ret != PSA_SUCCESS) {
    printf("Failed: %ld\n", ret);
  }
  return ret;
}

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define NPART_STEPS (4) // The number of steps demonstrated in 'multipart' aead
#if ((NPART_STEPS) <= 1)
#error multipart aead requires steps > 1
#endif

/// return_on_error will call psa_aead_abort(&op) to zero this struct
static psa_aead_operation_t op = { 0 };

/// cleanup macro
#define return_on_error(CODE)                    \
  do {                                           \
    psa_status_t __r = print_aead_error(CODE);   \
    if (__r != PSA_SUCCESS) {                    \
      psa_aead_abort(&op);/*Free all resources*/ \
      cipher_msg_len = 0;                        \
      return __r;                                \
    }                                            \
  } while (0)

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Nonce buffer for AEAD
static uint8_t nonce_buf[NONCE_SIZE];

/// Nonce length for AEAD
static size_t nonce_len;

/// Additional data buffer for AEAD
static uint8_t ad_buf[AD_SIZE];

/// Additional data length for AEAD
static size_t ad_len;

/// Plain message buffer
static uint8_t plain_msg_buf[PLAIN_MSG_SIZE];

/// Plain message length
static size_t plain_msg_len;

/// Cipher message buffer
static uint8_t cipher_msg_buf[CIPHER_MSG_SIZE];

/// Cipher message length
static size_t cipher_msg_len;

/// AEAD output length
static size_t out_len;

/// Buffer for hash value
static uint8_t hash_buf[PSA_HASH_LENGTH(PSA_ALG_SHA_256)];

/// Hash length
static size_t hash_len;

// Buffer for tag
static uint8_t tag_buf[PSA_HASH_MAX_SIZE];

// Tag length
static size_t tag_len;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/***************************************************************************//**
 * Get associated data buffer pointer.
 ******************************************************************************/
uint8_t * get_ad_buf_ptr(void)
{
  return(ad_buf);
}

/***************************************************************************//**
 * Get nonce buffer pointer.
 ******************************************************************************/
uint8_t * get_nonce_buf_ptr(void)
{
  return(nonce_buf);
}

/***************************************************************************//**
 * Get plain message buffer pointer.
 ******************************************************************************/
uint8_t * get_plain_msg_buf_ptr(void)
{
  return(plain_msg_buf);
}

/***************************************************************************//**
 * Get cipher message buffer pointer.
 ******************************************************************************/
uint8_t * get_cipher_msg_buf_ptr(void)
{
  return(cipher_msg_buf);
}

/***************************************************************************//**
 * Set nonce length.
 ******************************************************************************/
void set_nonce_len(uint8_t length)
{
  nonce_len = length;
}

/***************************************************************************//**
 * Set additional data length.
 ******************************************************************************/
void set_ad_len(size_t length)
{
  ad_len = length;
}

/***************************************************************************//**
 * Set plain message length.
 ******************************************************************************/
void set_plain_msg_len(size_t length)
{
  plain_msg_len = length;
}

/***************************************************************************//**
 * Generate random numbers and save them to a buffer.
 ******************************************************************************/
psa_status_t generate_random_number(uint8_t *buf, uint32_t size)
{
  print_error_cycle(psa_generate_random(buf, size));
}

/***************************************************************************//**
 * Compute the hash of the message.
 ******************************************************************************/
psa_status_t compute_msg_hash(void)
{
  print_error_cycle(psa_hash_compute(PSA_ALG_SHA_256,
                                     plain_msg_buf,
                                     plain_msg_len,
                                     hash_buf,
                                     sizeof(hash_buf),
                                     &hash_len));
}

/***************************************************************************//**
 * Compute the SHA256 hash of a message and compare it with an expected value.
 ******************************************************************************/
psa_status_t compare_msg_hash(void)
{
  print_error_cycle(psa_hash_compare(PSA_ALG_SHA_256,
                                     plain_msg_buf,
                                     plain_msg_len,
                                     hash_buf,
                                     hash_len));
}

#define NPART_STEPS (4)

/***************************************************************************//**
 * Process an authenticated encryption using singlepart API
 ******************************************************************************/
psa_status_t encrypt_aead(void)
{
  psa_algorithm_t algo = get_key_algo();
  if (algo == 0) {
    return(PSA_ERROR_NOT_SUPPORTED);
  }

  print_error_cycle(psa_aead_encrypt(get_key_id(),
                                     algo,
                                     nonce_buf,
                                     nonce_len,
                                     ad_buf,
                                     ad_len,
                                     plain_msg_buf,
                                     plain_msg_len,
                                     cipher_msg_buf,
                                     sizeof(cipher_msg_buf),
                                     &out_len));
}

/***************************************************************************//**
 * Process an authenticated decryption using singlepart API
 ******************************************************************************/
psa_status_t decrypt_aead(void)
{
  psa_algorithm_t algo = get_key_algo();
  if (algo == 0) {
    return(PSA_ERROR_NOT_SUPPORTED);
  }

  print_error_cycle(psa_aead_decrypt(get_key_id(),
                                     algo,
                                     nonce_buf,
                                     nonce_len,
                                     ad_buf,
                                     ad_len,
                                     cipher_msg_buf,
                                     out_len,
                                     plain_msg_buf,
                                     sizeof(plain_msg_buf),
                                     &out_len));
}

/***************************************************************************//**
 * Process an authenticated AEAD using multipart API
 ******************************************************************************/
psa_status_t multipart_aead(bool is_encrypt)
{
  psa_algorithm_t algo = get_key_algo();
  psa_status_t ret = PSA_SUCCESS;

  if (algo == 0) {
    return(PSA_ERROR_NOT_SUPPORTED);
  }

  // This demonstration will perform multipart AEAD in N-steps
  // and will illustrate the order of API calls to make
  // the last step in a multipart aead call is to 'finalize' the computation
  size_t step = 0;

  // 1. Set up a multi-part aead context and initialize its algo and key
  printf("  . %scryption setup...\n", (is_encrypt ? "En" : "De"));
  if (is_encrypt) {
    return_on_error(psa_aead_encrypt_setup(&op, get_key_id(), algo));
  } else {
    return_on_error(psa_aead_decrypt_setup(&op, get_key_id(), algo));
  }

  // Use either the plaintext width or the ciphertext width
  const size_t input_len = (is_encrypt ? plain_msg_len : cipher_msg_len);

  // 2. optionally set length.
  //    Note setting length is mandatory for CCM and optional otherwise.
  if (algo == PSA_ALG_CCM) {
    printf("  + Setting length: ad: %u, msg: %u\n", ad_len, input_len);
    return_on_error(psa_aead_set_lengths(&op, ad_len, input_len));
  }

  // 3. set nonce - must be called after psa_aead_set_lengths or
  //    PSA_ERROR_BAD_STATE is returned
  //    note for encrypt psa_aead_generate_nonce may be used
  printf("  + Setting nonce (len=%u)...\n", nonce_len);
  return_on_error(psa_aead_set_nonce(&op, nonce_buf, nonce_len));

  // 4. update additional data - note that additional data is authenticated
  //    but not encrypted. Typically used for headers or other non-private data
  //    that requires integrity but not secrecy.
  printf("  . Updating AD...\n");
  return_on_error(psa_aead_update_ad(&op,
                                     ad_buf,
                                     ad_len));

  // 5. update plaintext - note that this is authenticated and encrypted.
  //    multipart process will be done over the whole data in NPART_STEPS
  step = 0;
  size_t frag_size = (input_len / NPART_STEPS);

  // The width of the output needs to be stored for subsequent steps
  size_t bytes_out = 0;
  size_t out_total = 0;

  // during an encrypt phase input is plaintext and output is ciphertext
  // vice-versa during a decrypt phase
  uint8_t *input =  (is_encrypt ? plain_msg_buf  : cipher_msg_buf);
  uint8_t *output = (is_encrypt ? cipher_msg_buf : plain_msg_buf);

  // The maximum output buffer width
  const size_t out_sz = (is_encrypt ? sizeof(cipher_msg_buf) : sizeof(plain_msg_buf));

  // demonstrating equal NPART_STEPS to process the whole input data using multipart AEAD
  // note that equal parts are not required - and multipart AEAD can be performed on
  // streaming data as it arrives...
  // Note also that bytes_out may be less than input bytes - during normal operation
  // the required temporary buffer output may not  match the number of bytes input
  printf("  . %scryption...\n", (is_encrypt ? "Plaintext En" : "Ciphertext De"));
  while ( input_len - (frag_size * step) >= frag_size) {
    return_on_error(psa_aead_update(&op,
                                    input + out_total,
                                    frag_size,
                                    output + out_total,
                                    out_sz - out_total,
                                    &bytes_out));

    // when successful, bytes_out holds the number of actual bytes output as a result
    // of the 'update' call ... which may be different from the number of bytes input
    out_total += bytes_out; // accumulate output length...
    step++;
  }

  // 5. update plaintext, continued.
  // If the fragments processed above would have a remainder, handle that here...
  if (input_len % frag_size) {
    frag_size = input_len % frag_size;
    return_on_error(psa_aead_update(&op,
                                    input + out_total,
                                    frag_size,
                                    output + out_total,
                                    out_sz - out_total,
                                    &bytes_out));

    out_total += bytes_out; // accumulate output length...
  }

  // 6 Finish the multipart AEAD operation...
  // Note that the last step for an encrypt phase is 'finish'
  // while for decrypt it is 'verify'
  // _finish will store the authentication tag in tag_buf...
  // _verify will return PSA_ERROR_INVALID_SIGNATURE
  // if the tag does not match...
  printf("  + Finishing multipart aead...\n");
  if (is_encrypt) {
    return_on_error(psa_aead_finish(&op,
                                    cipher_msg_buf + out_total,
                                    out_sz - out_total,
                                    &bytes_out,
                                    tag_buf,
                                    sizeof(tag_buf),
                                    &tag_len));

    cipher_msg_len = out_total + bytes_out;
  } else {
    return_on_error(ret = psa_aead_verify(&op,
                                          plain_msg_buf + out_total,
                                          out_sz - out_total,
                                          &bytes_out,
                                          tag_buf,
                                          tag_len));

    plain_msg_len = out_total + bytes_out;
  }

  return ret;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
