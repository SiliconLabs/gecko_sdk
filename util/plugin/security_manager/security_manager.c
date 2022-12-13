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
#if defined(SEMAILBOX_PRESENT)
#include "sli_se_opaque_functions.h"
#include "sli_se_opaque_types.h"
#endif
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT
#if defined(SL_CATALOG_NVM3_PRESENT)
#include "nvm3.h"
#endif

#define SEC_MAN_GET_STATUS(x) (map_psa_error_to_sec_man_error(x))
#define SL_MAN_AES_BLOCK_SIZE 16

static bool is_security_manager_initialised = false;

sl_sec_man_status_t map_psa_error_to_sec_man_error(psa_status_t error)
{
  sl_sec_man_status_t retStatus;

  switch (error) {
    case PSA_SUCCESS:
      retStatus = SL_SECURITY_MAN_SUCCESS;
      break;

    case PSA_ERROR_INVALID_SIGNATURE:
      retStatus = SL_SECURITY_MAN_VERIFICATION_FAILED;
      break;

    default:
      retStatus = SL_SECURITY_MAN_ERROR;
      break;
  }

  return retStatus;
}

sl_sec_man_status_t sl_sec_man_init(void)
{
  sl_sec_man_status_t retStatus = SL_SECURITY_MAN_SUCCESS;

  if (!is_security_manager_initialised) {
    psa_status_t status             = psa_crypto_init();
    retStatus                       = SEC_MAN_GET_STATUS(status);

    if (retStatus == SL_SECURITY_MAN_SUCCESS) {
      is_security_manager_initialised = true;
    }
  }

  return retStatus;
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
    sl_psa_key_location = PSA_KEY_LOCATION_SLI_SE_OPAQUE;
  }
#endif

  psa_key_lifetime_t sl_psa_key_lifetime =
    PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(sl_psa_key_persistence, sl_psa_key_location);

  if (sl_psa_key_persistence == PSA_KEY_LIFETIME_PERSISTENT) {
    psa_set_key_id(sl_psa_key_attr, *sl_psa_key_id);
  }

  psa_set_key_usage_flags(sl_psa_key_attr, sl_psa_key_lifetime);
  psa_set_key_usage_flags(sl_psa_key_attr, sl_psa_key_usage);
  psa_set_key_algorithm(sl_psa_key_attr, sl_psa_key_algorithm);
  psa_set_key_type(sl_psa_key_attr, sl_psa_key_type);
  psa_set_key_bits(sl_psa_key_attr, sl_psa_key_len);
}

sl_sec_man_status_t sl_sec_man_import_key(psa_key_id_t *        sl_psa_key_id,
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
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  sl_sec_man_set_key_attributes(sl_psa_key_id, &sl_psa_key_attr, sl_psa_key_type, sl_psa_key_algorithm,
                                sl_psa_key_usage, sl_psa_key_persistence, (sl_key_literal_len * 8));

  /* Import the key */
  status = psa_import_key(&sl_psa_key_attr, sl_psa_key_literal, sl_key_literal_len, sl_psa_key_id);

  exit:
  return (SEC_MAN_GET_STATUS(status));
}

sl_sec_man_status_t sl_sec_man_generate_key(psa_key_id_t *        sl_psa_key_id,
                                            psa_key_type_t        sl_psa_key_type,
                                            psa_algorithm_t       sl_psa_key_algorithm,
                                            psa_key_usage_t       sl_psa_key_usage,
                                            psa_key_persistence_t sl_psa_key_persistence,
                                            size_t                sl_psa_key_len)
{
  psa_status_t         status;
  psa_key_attributes_t sl_psa_key_attr = PSA_KEY_ATTRIBUTES_INIT;

  if (sl_psa_key_id == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  sl_sec_man_set_key_attributes(sl_psa_key_id, &sl_psa_key_attr, sl_psa_key_type, sl_psa_key_algorithm,
                                sl_psa_key_usage, sl_psa_key_persistence, sl_psa_key_len);

  /* Import the key */
  status = psa_generate_key(&sl_psa_key_attr, sl_psa_key_id);

  exit:
  return (SEC_MAN_GET_STATUS(status));
}

sl_sec_man_status_t sl_sec_man_export_key(psa_key_id_t sl_psa_key_id,
                                          uint8_t *    sl_psa_key_buffer,
                                          size_t       sl_psa_key_buffer_len,
                                          size_t *     sl_psa_key_len)
{
  psa_status_t status;

  if ((sl_psa_key_buffer == NULL) || (sl_psa_key_len == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status =
    SEC_MAN_GET_STATUS(psa_export_key(sl_psa_key_id, sl_psa_key_buffer, sl_psa_key_buffer_len, sl_psa_key_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_get_key_attributes(psa_key_id_t          sl_psa_key_id,
                                                  psa_key_attributes_t *sl_psa_key_attributes)
{
  sl_sec_man_status_t status;

  if (sl_psa_key_attributes == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_get_key_attributes(sl_psa_key_id, sl_psa_key_attributes));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_destroy_key(psa_key_id_t sl_psa_key_id)
{
  return (SEC_MAN_GET_STATUS(psa_destroy_key(sl_psa_key_id)));
}

sl_sec_man_status_t sl_sec_man_aes_encrypt(psa_key_id_t    sl_psa_key_id,
                                           psa_algorithm_t sl_psa_aes_alg,
                                           const uint8_t * sl_psa_aes_input,
                                           uint8_t *       sl_psa_aes_output)
{
  size_t                 sl_psa_aes_enc_len = 0;
  sl_sec_man_status_t    status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_aes_input == NULL) || (sl_psa_aes_output == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_cipher_encrypt(sl_psa_key_id, sl_psa_aes_alg, sl_psa_aes_input, SL_MAN_AES_BLOCK_SIZE, sl_psa_aes_output,
                                                 SL_MAN_AES_BLOCK_SIZE, &sl_psa_aes_enc_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_aes_decrypt(psa_key_id_t    sl_psa_key_id,
                                           psa_algorithm_t sl_psa_aes_alg,
                                           const uint8_t * sl_psa_aes_input,
                                           uint8_t *       sl_psa_aes_output)
{
  size_t                 sl_psa_aes_enc_len = 0;
  sl_sec_man_status_t    status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_aes_input == NULL) || (sl_psa_aes_output == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_cipher_decrypt(sl_psa_key_id, sl_psa_aes_alg, sl_psa_aes_input, SL_MAN_AES_BLOCK_SIZE, sl_psa_aes_output,
                                                 SL_MAN_AES_BLOCK_SIZE, &sl_psa_aes_enc_len));

  exit:
  return status;
}

//Use PSA for AES-CCM* encryption and tagging operations
sl_sec_man_status_t sl_sec_man_aes_ccm_crypt(psa_key_id_t sl_psa_key_id,
                                             uint8_t* nonce,
                                             bool encrypt,
                                             const uint8_t* input,
                                             uint8_t encryption_start_index,
                                             uint8_t length,
                                             uint8_t* output)
{
  psa_status_t psa_status;
  //contains size of output + MIC
  size_t output_length;

  uint8_t MIC_LENGTH = 4;
  size_t NONCE_LENGTH = 13;

  //return full output packet (including unencrypted authentication data)
  memmove(output, input, encryption_start_index);

  psa_algorithm_t aes_ccm_tag_alg = PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, MIC_LENGTH);

  if (encrypt) {
    psa_status = psa_aead_encrypt(
      sl_psa_key_id,
      aes_ccm_tag_alg,
      (const uint8_t *) nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index,
      output + encryption_start_index, length - encryption_start_index + MIC_LENGTH, &output_length);
  } else {
    psa_status = psa_aead_decrypt(
      sl_psa_key_id,
      aes_ccm_tag_alg,
      (const uint8_t *) nonce, NONCE_LENGTH,
      input, encryption_start_index,
      input + encryption_start_index, length - encryption_start_index + MIC_LENGTH,
      output + encryption_start_index, length - encryption_start_index, &output_length);
  }

  if (psa_status == PSA_ERROR_INVALID_SIGNATURE) {
    return SL_SECURITY_MAN_VERIFICATION_FAILED;
  }
  if (psa_status != PSA_SUCCESS || (!encrypt && output_length != (size_t) (length - encryption_start_index))
      || (encrypt && output_length != (size_t) (length + MIC_LENGTH - encryption_start_index))) {
    return SL_SECURITY_MAN_INVALID_PARAMS;
  } else {
    return SL_SECURITY_MAN_SUCCESS;
  }
}

sl_sec_man_status_t sl_sec_man_hmac_start(psa_mac_operation_t *sl_psa_hmac_ctx, psa_key_id_t sl_psa_key_id)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_hmac_ctx == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_mac_sign_setup(sl_psa_hmac_ctx, sl_psa_key_id, PSA_ALG_HMAC(PSA_ALG_SHA_256)));
  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hmac_update(psa_mac_operation_t *sl_psa_hmac_ctx,
                                           const uint8_t *      sl_psa_hmac_buffer,
                                           size_t               sl_psa_hmac_buffer_len)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_hmac_ctx == NULL) || (sl_psa_hmac_buffer == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_mac_update(sl_psa_hmac_ctx, sl_psa_hmac_buffer, sl_psa_hmac_buffer_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hmac_finish(psa_mac_operation_t *sl_psa_hmac_ctx,
                                           const uint8_t *      sl_psa_hmac_buffer,
                                           size_t               sl_psa_hmac_buffer_len)
{
  sl_sec_man_status_t status            = SL_SECURITY_MAN_SUCCESS;
  size_t              sl_psa_mac_length = 0;

  if ((sl_psa_hmac_ctx == NULL) || (sl_psa_hmac_buffer == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_mac_sign_finish(sl_psa_hmac_ctx, (uint8_t *)sl_psa_hmac_buffer,
                                                  sl_psa_hmac_buffer_len, &sl_psa_mac_length));
  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hmac_deinit(psa_mac_operation_t *sl_psa_hmac_ctx)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_hmac_ctx == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_mac_abort(sl_psa_hmac_ctx));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_key_derivation_extract(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                                      psa_algorithm_t                 sl_psa_key_derivation_algorithm,
                                                      psa_key_id_t                    sl_psa_key_id,
                                                      const uint8_t *                 sl_psa_key_derivation_salt,
                                                      uint16_t                        sl_psa_key_derivation_salt_length)
{
  psa_status_t        sl_psa_status;
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_key_derivation_ctx == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  *sl_psa_key_derivation_ctx = psa_key_derivation_operation_init();

  // PRK is calculated as HMAC-Hash(aSalt, aInputKey)
  sl_psa_status = psa_key_derivation_setup(sl_psa_key_derivation_ctx, PSA_ALG_HKDF(sl_psa_key_derivation_algorithm));

  if (sl_psa_status != PSA_SUCCESS) {
    status = SL_SECURITY_MAN_ERROR;
    goto exit;
  }

  sl_psa_status = psa_key_derivation_input_bytes(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_SALT,
                                                 sl_psa_key_derivation_salt, sl_psa_key_derivation_salt_length);

  if (sl_psa_status != PSA_SUCCESS) {
    status = SL_SECURITY_MAN_ERROR;
    goto exit;
  }

  sl_psa_status =
    psa_key_derivation_input_key(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_SECRET, sl_psa_key_id);

  if (sl_psa_status != PSA_SUCCESS) {
    status = SL_SECURITY_MAN_ERROR;
    goto exit;
  }

  exit:

  if (status != SL_SECURITY_MAN_SUCCESS) {
    psa_key_derivation_abort(sl_psa_key_derivation_ctx);
  }

  return status;
}

sl_sec_man_status_t sl_sec_man_key_derivation_expand(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                                     const uint8_t *                 sl_psa_key_derivation_info,
                                                     uint16_t                        sl_psa_key_derivation_info_length,
                                                     uint8_t *                       sl_psa_key_derivation_output_key,
                                                     uint16_t sl_psa_key_derivation_output_key_len)
{
  psa_status_t        sl_psa_status;
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_key_derivation_ctx == NULL) || (sl_psa_key_derivation_output_key == NULL)
      || (sl_psa_key_derivation_info == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  sl_psa_status = psa_key_derivation_input_bytes(sl_psa_key_derivation_ctx, PSA_KEY_DERIVATION_INPUT_INFO,
                                                 sl_psa_key_derivation_info, sl_psa_key_derivation_info_length);

  if (sl_psa_status != PSA_SUCCESS) {
    status = SL_SECURITY_MAN_ERROR;
    goto exit;
  }

  sl_psa_status = psa_key_derivation_output_bytes(sl_psa_key_derivation_ctx, sl_psa_key_derivation_output_key,
                                                  sl_psa_key_derivation_output_key_len);

  if (sl_psa_status != PSA_SUCCESS) {
    status = SL_SECURITY_MAN_ERROR;
    goto exit;
  }

  exit:

  if (status != SL_SECURITY_MAN_SUCCESS) {
    psa_key_derivation_abort(sl_psa_key_derivation_ctx);
  }

  return status;
}

psa_hash_operation_t sl_sec_man_hash_init(void)
{
  return psa_hash_operation_init();
}

sl_sec_man_status_t sl_sec_man_hash_deinit(psa_hash_operation_t *sl_psa_hash_ctx)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_hash_ctx == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_hash_abort(sl_psa_hash_ctx));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hash_start(psa_hash_operation_t *sl_psa_hash_ctx, psa_algorithm_t sl_psa_hash_alg)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_hash_ctx == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_hash_setup(sl_psa_hash_ctx, sl_psa_hash_alg));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hash_update(psa_hash_operation_t *sl_psa_hash_ctx,
                                           uint8_t *             sl_psa_hash_buffer,
                                           uint16_t              sl_psa_hash_buffer_len)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_hash_ctx == NULL) || (sl_psa_hash_buffer == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_hash_update(sl_psa_hash_ctx, sl_psa_hash_buffer, sl_psa_hash_buffer_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_hash_finish(psa_hash_operation_t *sl_psa_hash_ctx,
                                           uint8_t *             sl_psa_hash,
                                           uint16_t              sl_psa_hash_size,
                                           size_t *              sl_psa_hash_len)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_hash_ctx == NULL) || (sl_psa_hash == NULL) || (sl_psa_hash_len == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_hash_finish(sl_psa_hash_ctx, sl_psa_hash, sl_psa_hash_size, sl_psa_hash_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_get_random(uint8_t               *sl_psa_output_buffer,
                                          uint16_t              sl_psa_output_size)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if (sl_psa_output_buffer == NULL) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_generate_random(sl_psa_output_buffer, sl_psa_output_size));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_export_public_key(psa_key_id_t        sl_psa_key_id,
                                                 uint8_t             *sl_psa_output_buffer,
                                                 size_t              sl_output_buffer_size,
                                                 size_t              *sl_psa_key_len)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_psa_output_buffer == NULL) && (sl_psa_key_len == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  status = SEC_MAN_GET_STATUS(psa_export_public_key(sl_psa_key_id, sl_psa_output_buffer, sl_output_buffer_size, sl_psa_key_len));

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_sign(psa_key_id_t        sl_psa_key_id,
                                    psa_algorithm_t     sl_dsa_algorithm,
                                    const uint8_t       *sl_dsa_input_buf,
                                    size_t              sl_dsa_input_size,
                                    uint8_t             *sl_dsa_signature_buf,
                                    size_t              sl_dsa_signature_size,
                                    size_t              *sl_dsa_signature_len,
                                    bool                sl_is_hash)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_dsa_input_buf == NULL) && (sl_dsa_signature_buf == NULL) && (sl_dsa_signature_len == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  if (sl_is_hash) {
    status = SEC_MAN_GET_STATUS(psa_sign_hash(sl_psa_key_id,
                                              sl_dsa_algorithm,
                                              sl_dsa_input_buf,
                                              sl_dsa_input_size,
                                              sl_dsa_signature_buf,
                                              sl_dsa_signature_size,
                                              sl_dsa_signature_len));
  } else {
    status = SEC_MAN_GET_STATUS(psa_sign_message(sl_psa_key_id,
                                                 sl_dsa_algorithm,
                                                 sl_dsa_input_buf,
                                                 sl_dsa_input_size,
                                                 sl_dsa_signature_buf,
                                                 sl_dsa_signature_size,
                                                 sl_dsa_signature_len));
  }

  exit:
  return status;
}

sl_sec_man_status_t sl_sec_man_verify(psa_key_id_t        sl_psa_key_id,
                                      psa_algorithm_t     sl_dsa_algorithm,
                                      const uint8_t       *sl_dsa_input_buf,
                                      size_t              sl_dsa_input_size,
                                      const uint8_t       *sl_dsa_signature_buf,
                                      size_t              sl_dsa_signature_size,
                                      bool                sl_is_hash)
{
  sl_sec_man_status_t status = SL_SECURITY_MAN_SUCCESS;

  if ((sl_dsa_input_buf == NULL) && (sl_dsa_signature_buf == NULL)) {
    status = SL_SECURITY_MAN_INVALID_PARAMS;
    goto exit;
  }

  if (sl_is_hash) {
    status = SEC_MAN_GET_STATUS(psa_verify_hash(sl_psa_key_id,
                                                sl_dsa_algorithm,
                                                sl_dsa_input_buf,
                                                sl_dsa_input_size,
                                                sl_dsa_signature_buf,
                                                sl_dsa_signature_size));
  } else {
    status = SEC_MAN_GET_STATUS(psa_verify_message(sl_psa_key_id,
                                                   sl_dsa_algorithm,
                                                   sl_dsa_input_buf,
                                                   sl_dsa_input_size,
                                                   sl_dsa_signature_buf,
                                                   sl_dsa_signature_size));
  }

  exit:
  return status;
}
