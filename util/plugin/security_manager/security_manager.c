/***************************************************************************//**
 * @file
 * @brief This file implements abstracting the PSA CRYPTO interface.
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

#include "security_manager.h"
#include "em_device.h"
#include "em_system.h"
#include "psa/crypto.h"
#include "sl_psa_crypto.h"
#include "sli_psa_crypto.h"
#include "psa/internal_trusted_storage.h"
#include "psa/sli_internal_trusted_storage.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT
#if defined(SL_CATALOG_NVM3_PRESENT)
#include "nvm3.h"
#endif

#define SL_SEC_MAN_AES_BLOCK_SIZE       16
#define SL_SEC_MAN_TRANSIENT_KEY_ID 0x200F0

static bool is_security_manager_initialised = false;

psa_status_t sl_sec_man_init(void)
{
  psa_status_t status = PSA_SUCCESS;
  if (!is_security_manager_initialised) {
    status = psa_crypto_init();

    if (status == PSA_SUCCESS) {
      is_security_manager_initialised = true;
    }
  }

  return status;
}

static void sl_sec_man_set_key_attributes(psa_key_id_t *        sl_psa_key_id,
                                          psa_key_attributes_t *sl_psa_key_attr,
                                          psa_key_type_t        sl_psa_key_type,
                                          psa_algorithm_t       sl_psa_key_algorithm,
                                          psa_key_usage_t       sl_psa_key_usage,
                                          psa_key_persistence_t sl_psa_key_persistence,
                                          size_t                sl_psa_key_len)
{
  psa_key_location_t sl_psa_key_location = PSA_KEY_LOCATION_LOCAL_STORAGE;

#if defined(SEMAILBOX_PRESENT)
  if (SYSTEM_GetSecurityCapability() == securityCapabilityVault) {
    sl_psa_key_location = SL_PSA_KEY_LOCATION_WRAPPED;
  }

  // Dont wrap volatile keys used for HMAC operation, as opaque keys cannot be used for multi-part HMAC.
  if (sl_psa_key_type == PSA_KEY_TYPE_HMAC && sl_psa_key_persistence == PSA_KEY_PERSISTENCE_VOLATILE) {
    sl_psa_key_location = PSA_KEY_LOCATION_LOCAL_STORAGE;
  }
#endif
  psa_key_lifetime_t sl_psa_key_lifetime =
    PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(sl_psa_key_persistence, sl_psa_key_location);

  if (sl_psa_key_persistence == PSA_KEY_PERSISTENCE_DEFAULT) {
    psa_set_key_id(sl_psa_key_attr, *sl_psa_key_id);
  }

  psa_set_key_lifetime(sl_psa_key_attr, sl_psa_key_lifetime);
  psa_set_key_usage_flags(sl_psa_key_attr, sl_psa_key_usage);
  psa_set_key_algorithm(sl_psa_key_attr, sl_psa_key_algorithm);
  psa_set_key_type(sl_psa_key_attr, sl_psa_key_type);
  psa_set_key_bits(sl_psa_key_attr, sl_psa_key_len);
}

psa_status_t sl_sec_man_import_key(psa_key_id_t *        sl_psa_key_id,
                                   psa_key_type_t        sl_psa_key_type,
                                   psa_algorithm_t       sl_psa_key_algorithm,
                                   psa_key_usage_t       sl_psa_key_usage,
                                   psa_key_persistence_t sl_psa_key_persistence,
                                   const uint8_t *       sl_psa_key_literal,
                                   size_t                sl_key_literal_len)
{
  psa_status_t         status;
  psa_key_attributes_t sl_psa_key_attr = PSA_KEY_ATTRIBUTES_INIT;

  if ((sl_psa_key_id == NULL) || (sl_psa_key_literal == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  sl_sec_man_set_key_attributes(sl_psa_key_id, &sl_psa_key_attr, sl_psa_key_type, sl_psa_key_algorithm,
                                sl_psa_key_usage, sl_psa_key_persistence, (sl_key_literal_len * 8));

  /* Import the key */
  status = psa_import_key(&sl_psa_key_attr, sl_psa_key_literal, sl_key_literal_len, sl_psa_key_id);

  exit:
  return status;
}

psa_status_t sl_sec_man_generate_key(psa_key_id_t *        sl_psa_key_id,
                                     psa_key_type_t        sl_psa_key_type,
                                     psa_algorithm_t       sl_psa_key_algorithm,
                                     psa_key_usage_t       sl_psa_key_usage,
                                     psa_key_persistence_t sl_psa_key_persistence,
                                     size_t                sl_psa_key_len)
{
  psa_status_t         status;
  psa_key_attributes_t sl_psa_key_attr = PSA_KEY_ATTRIBUTES_INIT;

  if (sl_psa_key_id == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  sl_sec_man_set_key_attributes(sl_psa_key_id, &sl_psa_key_attr, sl_psa_key_type, sl_psa_key_algorithm,
                                sl_psa_key_usage, sl_psa_key_persistence, sl_psa_key_len);

  /* Import the key */
  status = psa_generate_key(&sl_psa_key_attr, sl_psa_key_id);

  exit:
  return status;
}

psa_status_t sl_sec_man_export_key(psa_key_id_t sl_psa_key_id,
                                   uint8_t *    sl_psa_key_buffer,
                                   size_t       sl_psa_key_buffer_len,
                                   size_t *     sl_psa_key_len)
{
  psa_status_t status;

  if ((sl_psa_key_buffer == NULL) || (sl_psa_key_len == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_export_key(sl_psa_key_id, sl_psa_key_buffer, sl_psa_key_buffer_len, sl_psa_key_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_get_key_attributes(psa_key_id_t          sl_psa_key_id,
                                           psa_key_attributes_t *sl_psa_key_attributes)
{
  psa_status_t status;

  if (sl_psa_key_attributes == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_get_key_attributes(sl_psa_key_id, sl_psa_key_attributes);

  exit:
  return status;
}

psa_status_t sl_sec_man_destroy_key(psa_key_id_t sl_psa_key_id)
{
  return psa_destroy_key(sl_psa_key_id);
}

psa_status_t sl_sec_man_copy_key(psa_key_id_t          sl_psa_source_key_id,
                                 psa_key_attributes_t *sl_psa_key_attributes,
                                 psa_key_id_t         *sl_psa_dest_key_id)
{
  psa_status_t          status;
  bool                  overwrite_original;

  if (sl_psa_key_attributes == NULL || sl_psa_dest_key_id == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  // Do we need to overwrite original key?
  overwrite_original    = (sl_psa_source_key_id == *sl_psa_dest_key_id);

  if (overwrite_original) {
#ifndef SL_TRUSTZONE_NONSECURE
    // Set the target key id to a default value.
    // Note, this needs to be either in thread or zigbee NVM range.
    *sl_psa_dest_key_id = SL_SEC_MAN_TRANSIENT_KEY_ID;
#else
    status = PSA_ERROR_NOT_SUPPORTED;
    goto exit;
#endif
  }

  // Set the key id for the new key
  psa_set_key_id(sl_psa_key_attributes, *sl_psa_dest_key_id);
  // Copy the key from source to destnation
  status = psa_copy_key(sl_psa_source_key_id, sl_psa_key_attributes, sl_psa_dest_key_id);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

#ifndef SL_TRUSTZONE_NONSECURE
  if (overwrite_original) {
    // After making a copy, if we need to replace the old key,
    // first destroy the original key.
    psa_destroy_key(sl_psa_source_key_id);
    //Set the new key's keyid to match the original keyid
    status = sli_psa_its_change_key_id(*sl_psa_dest_key_id, sl_psa_source_key_id);
  }
#endif
  exit:
  return status;
}

psa_status_t sl_sec_man_aes_encrypt(psa_key_id_t    sl_psa_key_id,
                                    psa_algorithm_t sl_psa_aes_alg,
                                    const uint8_t * sl_psa_aes_input,
                                    uint8_t *       sl_psa_aes_output)
{
  size_t                 sl_psa_aes_enc_len = 0;
  psa_status_t  status = PSA_SUCCESS;

  if ((sl_psa_aes_input == NULL) || (sl_psa_aes_output == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_cipher_encrypt(sl_psa_key_id, sl_psa_aes_alg, sl_psa_aes_input, SL_SEC_MAN_AES_BLOCK_SIZE, sl_psa_aes_output,
                              SL_SEC_MAN_AES_BLOCK_SIZE, &sl_psa_aes_enc_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_aes_decrypt(psa_key_id_t    sl_psa_key_id,
                                    psa_algorithm_t sl_psa_aes_alg,
                                    const uint8_t * sl_psa_aes_input,
                                    uint8_t *       sl_psa_aes_output)
{
  size_t                 sl_psa_aes_enc_len = 0;
  psa_status_t  status = PSA_SUCCESS;

  if ((sl_psa_aes_input == NULL) || (sl_psa_aes_output == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_cipher_decrypt(sl_psa_key_id, sl_psa_aes_alg, sl_psa_aes_input, SL_SEC_MAN_AES_BLOCK_SIZE, sl_psa_aes_output,
                              SL_SEC_MAN_AES_BLOCK_SIZE, &sl_psa_aes_enc_len);

  exit:
  return status;
}

//Use PSA for AES-CCM* encryption and tagging operations
psa_status_t sl_sec_man_aes_ccm_crypt(psa_key_id_t sl_psa_key_id,
                                      uint8_t* nonce,
                                      bool encrypt,
                                      const uint8_t* input,
                                      uint8_t encryption_start_index,
                                      uint8_t length,
                                      uint8_t mic_length,
                                      uint8_t* output)
{
  psa_status_t psa_status;
  //contains size of output + MIC
  size_t output_length;

  size_t NONCE_LENGTH = 13;

  //return full output packet (including unencrypted authentication data)
  memmove(output, input, encryption_start_index);

  psa_algorithm_t aes_ccm_tag_alg = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, mic_length);

  if (encrypt) {
    psa_status = psa_aead_encrypt(
      sl_psa_key_id,
      aes_ccm_tag_alg,
      (const uint8_t *) nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index,
      output + encryption_start_index, length - encryption_start_index + mic_length, &output_length);
  } else {
    psa_status = psa_aead_decrypt(
      sl_psa_key_id,
      aes_ccm_tag_alg,
      (const uint8_t *) nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index + mic_length,
      output + encryption_start_index, length - encryption_start_index, &output_length);
  }

  if (psa_status == PSA_ERROR_INVALID_SIGNATURE) {
    return psa_status;
  }
  if (psa_status != PSA_SUCCESS || (!encrypt && output_length != (size_t) (length - encryption_start_index))
      || (encrypt && output_length != (size_t) (length + mic_length - encryption_start_index))) {
    return PSA_ERROR_INVALID_ARGUMENT;
  } else {
    return PSA_SUCCESS;
  }
}

psa_status_t sl_sec_man_hmac_start(psa_mac_operation_t *sl_psa_hmac_ctx, psa_key_id_t sl_psa_key_id)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_hmac_ctx == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_mac_sign_setup(sl_psa_hmac_ctx, sl_psa_key_id, PSA_ALG_HMAC(PSA_ALG_SHA_256));
  exit:
  return status;
}

psa_status_t sl_sec_man_hmac_update(psa_mac_operation_t *sl_psa_hmac_ctx,
                                    const uint8_t *      sl_psa_hmac_buffer,
                                    size_t               sl_psa_hmac_buffer_len)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_psa_hmac_ctx == NULL) || (sl_psa_hmac_buffer == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_mac_update(sl_psa_hmac_ctx, sl_psa_hmac_buffer, sl_psa_hmac_buffer_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_hmac_finish(psa_mac_operation_t *sl_psa_hmac_ctx,
                                    const uint8_t *      sl_psa_hmac_buffer,
                                    size_t               sl_psa_hmac_buffer_len)
{
  psa_status_t status            = PSA_SUCCESS;
  size_t              sl_psa_mac_length = 0;

  if ((sl_psa_hmac_ctx == NULL) || (sl_psa_hmac_buffer == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_mac_sign_finish(sl_psa_hmac_ctx, (uint8_t *)sl_psa_hmac_buffer,
                               sl_psa_hmac_buffer_len, &sl_psa_mac_length);
  exit:
  return status;
}

psa_status_t sl_sec_man_hmac_deinit(psa_mac_operation_t *sl_psa_hmac_ctx)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_hmac_ctx == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_mac_abort(sl_psa_hmac_ctx);

  exit:
  return status;
}

psa_status_t sl_sec_man_key_derivation_extract(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                               psa_algorithm_t                 sl_psa_key_derivation_algorithm,
                                               psa_key_id_t                    sl_psa_key_id,
                                               const uint8_t *                 sl_psa_key_derivation_salt,
                                               uint16_t                        sl_psa_key_derivation_salt_length)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_key_derivation_ctx == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  *sl_psa_key_derivation_ctx = psa_key_derivation_operation_init();

  // PRK is calculated as HMAC-Hash(aSalt, aInputKey)
  status = psa_key_derivation_setup(sl_psa_key_derivation_ctx, PSA_ALG_HKDF(sl_psa_key_derivation_algorithm));

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_key_derivation_input_bytes(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_SALT,
                                          sl_psa_key_derivation_salt, sl_psa_key_derivation_salt_length);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_key_derivation_input_key(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_SECRET, sl_psa_key_id);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  exit:

  if (status != PSA_SUCCESS) {
    psa_key_derivation_abort(sl_psa_key_derivation_ctx);
  }

  return status;
}

psa_status_t sl_sec_man_key_derivation_expand(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                              const uint8_t *                 sl_psa_key_derivation_info,
                                              uint16_t                        sl_psa_key_derivation_info_length,
                                              uint8_t *                       sl_psa_key_derivation_output_key,
                                              uint16_t sl_psa_key_derivation_output_key_len)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_psa_key_derivation_ctx == NULL) || (sl_psa_key_derivation_output_key == NULL)
      || (sl_psa_key_derivation_info == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_key_derivation_input_bytes(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_INFO,
                                          sl_psa_key_derivation_info, sl_psa_key_derivation_info_length);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_key_derivation_output_bytes(sl_psa_key_derivation_ctx, sl_psa_key_derivation_output_key,
                                           sl_psa_key_derivation_output_key_len);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  exit:

  if (status != PSA_SUCCESS) {
    psa_key_derivation_abort(sl_psa_key_derivation_ctx);
  }

  return status;
}

psa_hash_operation_t sl_sec_man_hash_init(void)
{
  return psa_hash_operation_init();
}

psa_status_t sl_sec_man_hash_deinit(psa_hash_operation_t *sl_psa_hash_ctx)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_hash_ctx == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_hash_abort(sl_psa_hash_ctx);

  exit:
  return status;
}

psa_status_t sl_sec_man_hash_start(psa_hash_operation_t *sl_psa_hash_ctx, psa_algorithm_t sl_psa_hash_alg)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_hash_ctx == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_hash_setup(sl_psa_hash_ctx, sl_psa_hash_alg);

  exit:
  return status;
}

psa_status_t sl_sec_man_hash_update(psa_hash_operation_t *sl_psa_hash_ctx,
                                    uint8_t *             sl_psa_hash_buffer,
                                    uint16_t              sl_psa_hash_buffer_len)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_psa_hash_ctx == NULL) || (sl_psa_hash_buffer == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_hash_update(sl_psa_hash_ctx, sl_psa_hash_buffer, sl_psa_hash_buffer_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_hash_finish(psa_hash_operation_t *sl_psa_hash_ctx,
                                    uint8_t *             sl_psa_hash,
                                    uint16_t              sl_psa_hash_size,
                                    size_t *              sl_psa_hash_len)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_psa_hash_ctx == NULL) || (sl_psa_hash == NULL) || (sl_psa_hash_len == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_hash_finish(sl_psa_hash_ctx, sl_psa_hash, sl_psa_hash_size, sl_psa_hash_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_get_random(uint8_t               *sl_psa_output_buffer,
                                   uint16_t              sl_psa_output_size)
{
  psa_status_t status = PSA_SUCCESS;

  if (sl_psa_output_buffer == NULL) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_generate_random(sl_psa_output_buffer, sl_psa_output_size);

  exit:
  return status;
}

psa_status_t sl_sec_man_export_public_key(psa_key_id_t        sl_psa_key_id,
                                          uint8_t             *sl_psa_output_buffer,
                                          size_t              sl_output_buffer_size,
                                          size_t              *sl_psa_key_len)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_psa_output_buffer == NULL) && (sl_psa_key_len == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  status = psa_export_public_key(sl_psa_key_id, sl_psa_output_buffer, sl_output_buffer_size, sl_psa_key_len);

  exit:
  return status;
}

psa_status_t sl_sec_man_sign(psa_key_id_t        sl_psa_key_id,
                             psa_algorithm_t     sl_dsa_algorithm,
                             const uint8_t       *sl_dsa_input_buf,
                             size_t              sl_dsa_input_size,
                             uint8_t             *sl_dsa_signature_buf,
                             size_t              sl_dsa_signature_size,
                             size_t              *sl_dsa_signature_len,
                             bool                sl_is_hash)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_dsa_input_buf == NULL) && (sl_dsa_signature_buf == NULL) && (sl_dsa_signature_len == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (sl_is_hash) {
    status = psa_sign_hash(sl_psa_key_id,
                           sl_dsa_algorithm,
                           sl_dsa_input_buf,
                           sl_dsa_input_size,
                           sl_dsa_signature_buf,
                           sl_dsa_signature_size,
                           sl_dsa_signature_len);
  } else {
    status = psa_sign_message(sl_psa_key_id,
                              sl_dsa_algorithm,
                              sl_dsa_input_buf,
                              sl_dsa_input_size,
                              sl_dsa_signature_buf,
                              sl_dsa_signature_size,
                              sl_dsa_signature_len);
  }

  exit:
  return status;
}

psa_status_t sl_sec_man_verify(psa_key_id_t        sl_psa_key_id,
                               psa_algorithm_t     sl_dsa_algorithm,
                               const uint8_t       *sl_dsa_input_buf,
                               size_t              sl_dsa_input_size,
                               const uint8_t       *sl_dsa_signature_buf,
                               size_t              sl_dsa_signature_size,
                               bool                sl_is_hash)
{
  psa_status_t status = PSA_SUCCESS;

  if ((sl_dsa_input_buf == NULL) && (sl_dsa_signature_buf == NULL)) {
    status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (sl_is_hash) {
    status = psa_verify_hash(sl_psa_key_id,
                             sl_dsa_algorithm,
                             sl_dsa_input_buf,
                             sl_dsa_input_size,
                             sl_dsa_signature_buf,
                             sl_dsa_signature_size);
  } else {
    status = psa_verify_message(sl_psa_key_id,
                                sl_dsa_algorithm,
                                sl_dsa_input_buf,
                                sl_dsa_input_size,
                                sl_dsa_signature_buf,
                                sl_dsa_signature_size);
  }

  exit:
  return status;
}
