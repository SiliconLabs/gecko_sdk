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

#ifndef SECURITY_MANAGER_H_
#define SECURITY_MANAGER_H_

#include <psa/crypto_types.h>
#include <stdbool.h>
#include <string.h>
#include "psa/crypto.h"
#include "psa/crypto_values.h"

/**
 * Initialise the security manager module.
 *
 * This API will internally initialise the PSA module
 *
 * @retval A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_init(void);

/**
 * Import a key into PSA ITS.
 *
 * The caller must Provide a valid key.
 *
 * Based on the parameters passed, the security manager will choose the storage location.
 * For persistent keys, key_id is managed by the application, and for volatiles keys,
 * PSA will create a key_id and returns the same to the application. All the keys will be wrapped
 * before storage and the key_id is further used for all the security operations.
 *
 * @param[out]  sl_psa_key_id                       Pointer to Key Id to be used for persistent keys. If the key is stored
 *                                                  in RAM, PSA will allocate the key ID and pass it to the application. For
 *                                                  non-volatile keys, key ID provided by application will be assigned as the reference.
 * @param[in]   sl_psa_key_type                     Key type encoding for the key.
 * @param[in]   sl_psa_key_algorithm                Key algorithm encoding for the key.
 * @param[in]   sl_psa_key_usage                    Key Usage encoding for the key.
 * @param[in]   sl_psa_key_persistence              What persistence level needs to be applied to the key.
 * @param[in]   sl_psa_key_literal                  Pointer to the actual key.
 * @param[in]   sl_key_literal_len                  Length of the key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_import_key(psa_key_id_t *        sl_psa_key_id,
                                   psa_key_type_t        sl_psa_key_type,
                                   psa_algorithm_t       sl_psa_key_algorithm,
                                   psa_key_usage_t       sl_psa_key_usage,
                                   psa_key_persistence_t sl_psa_key_persistence,
                                   const uint8_t *       sl_psa_key_literal,
                                   size_t                sl_key_literal_len);

/**
 * Generates a key and stores the same in PSA.
 *
 * Based on the parameters passed, the security manager will choose the storage location.
 * For persistent keys, key_id is managed by the application, and for volatiles keys,
 * PSA will create a key_id and returns the same to the application. All the keys will be wrapped
 * before storage and the key_id is further used for all the security operations.
 *
 * @param[out]  sl_psa_key_id                       Pointer to Key Id to be used for persistent keys. If the key is stored
 *                                                  in RAM, PSA will allocate the key ID and pass it to the application. For
 *                                                  non-volatile keys, key ID provided by application will be assigned as the reference.
 * @param[in]   sl_psa_key_type                     Key type encoding for the key.
 * @param[in]   sl_psa_key_algorithm                Key algorithm encoding for the key.
 * @param[in]   sl_psa_key_usage                    Key Usage encoding for the key.
 * @param[in]   sl_psa_key_persistence              What persistence level needs to be applied to the key.
 * @param[in]   sl_psa_key_len                      Length of the key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_generate_key(psa_key_id_t *        sl_psa_key_id,
                                     psa_key_type_t        sl_psa_key_type,
                                     psa_algorithm_t       sl_psa_key_algorithm,
                                     psa_key_usage_t       sl_psa_key_usage,
                                     psa_key_persistence_t sl_psa_key_persistence,
                                     size_t                sl_psa_key_len);

/**
 * Export a key from PSA ITS.
 *
 * This API can be used to export the key stored in the PSA. Only keys marked as exportable can be
 * read back from the storage as plaintext.
 *
 * @param[in]   sl_psa_key_id                       Key ID used as a reference to the key. This is either passed to import key,
 *                                                  for persistent keys, or returned to the application in the key context, for
 *                                                  volatile keys.
 * @param[in]   sl_psa_key_buffer                   Pointer to the buffer to store the key.
 * @param[in]   sl_psa_key_buffer_len               Length of the buffer.
 * @param[out]  sl_psa_key_len                      Length of the exported key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_export_key(psa_key_id_t sl_psa_key_id,
                                   uint8_t *    sl_psa_key_buffer,
                                   size_t       sl_psa_key_buffer_len,
                                   size_t *     sl_psa_key_len);

/**
 * Get attributes for a key stored in PSA ITS.
 *
 * @param[in]   sl_psa_key_id                       Key ID used as a reference to the key.
 * @param[out]  sl_psa_key_attributes               output pointer for key attributes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_get_key_attributes(psa_key_id_t          sl_psa_key_id,
                                           psa_key_attributes_t *sl_psa_key_attributes);

/**
 * Destroy a key stored in PSA ITS.
 *
 * This API can be used to dispose a stored key from PSA.
 *
 * @param[in]   sl_psa_key_id                       Key ID used as a reference to the key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_destroy_key(psa_key_id_t sl_psa_key_id);

/**
 * Make a copy a key stored in the ITS.
 *
 * This API can be used to make copies of a key in ITS.
 * This API can also be used to change the key attributes of a existing key.
 *
 * If the source and destination key ids are the same, a copy of the original
 * key will be made with new additional attributes.
 *
 * If the source and destination keyids are different, a copy of source key is
 * made, and new attributes additional attributes, and the keyId of new key will
 * be returned.
 *
 * @note /ref psa_copy_key() only supports unwrapped source keys.
 * This API will fail if the sl_psa_source_key_id is wrapped.
 * @note There are restrictions on what attributes can be changed. Refer to /ref psa_copy_key()
 *
 * @param[in]       sl_psa_source_key_id            Key ID of the source key.
 * @param[in]       sl_psa_key_attributes           New key attributes to be added.
 * @param[inout]    sl_psa_dest_key_id              KeyId for new key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_copy_key(psa_key_id_t          sl_psa_source_key_id,
                                 psa_key_attributes_t *sl_psa_key_attributes,
                                 psa_key_id_t         *sl_psa_dest_key_id);

/**
 * API to encrypt or decrypt data using AES ECB.
 *
 * This API can be used to perform AES ECB on given data. The user will have to
 * pass a valid key reference in the form of a key_id to the API.
 *
 * @param[in]  sl_psa_key_id                        Key ID used as a reference to the key.
 * @param[in]  sl_psa_aes_alg                       AES Algorithm to use.
 * @param[in]  sl_psa_aes_input                     Pointer to the data to be encrypted or decrypted.
 * @param[out] sl_psa_aes_output                    Pointer to buffer to hold the output data.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_aes_encrypt(psa_key_id_t    sl_psa_key_id,
                                    psa_algorithm_t sl_psa_aes_alg,
                                    const uint8_t*  sl_psa_aes_input,
                                    uint8_t*        sl_psa_aes_output);

psa_status_t sl_sec_man_aes_decrypt(psa_key_id_t    sl_psa_key_id,
                                    psa_algorithm_t sl_psa_aes_alg,
                                    const uint8_t*  sl_psa_aes_input,
                                    uint8_t*        sl_psa_aes_output);

/**
 * API to encrypt data using AES-CCM*.
 *
 * This API can be used to perform AES-CCM* operations on given data which is in packet format.
 * (Authentication data is followed by the data to be encrypted/decrypted, with a MIC
 * located after the encryption data)
 * @note returns an error if given invalid psa key id
 *
 * @param[in]  sl_psa_key_id                        Key ID used as a reference to the key.
 * @param[in]  nonce                                Nonce value to use in the CCM* operation.
 * @param[in]  encrypt                              Function mode.  False for authenticated decryption,
                                                    true otherwise.
 * @param[in]  input                                Pointer to the packet to be encrypted.
 * @param[in]  encryption_start_index               Index where the data to be encrypted begins, equal to
 *                                                  the length of the authenticated data.
 * @param[in]  length                               Total combined length of authenticated and encrypted data.
 * @param[in]  mic_length                           Length of the MIC to be output after the encrypted data.
 *                                                  This must be consistent with what the referenced key
 *                                                  permits for its encryption algorithm.
 * @param[out] output                               Pointer to buffer to hold the output packet.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_aes_ccm_crypt(psa_key_id_t sl_psa_key_id,
                                      uint8_t* nonce,
                                      bool encrypt,
                                      const uint8_t* input,
                                      uint8_t encryption_start_index,
                                      uint8_t length,
                                      uint8_t mic_length,
                                      uint8_t* output);

/**
 * Start the HMAC operation.
 *
 * @param[in]   sl_psa_hmac_ctx                     Operation Context for HMAC operation.
 * @param[out]  sl_psa_key_id                       Reference to the key to be used for HMAC operation.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_hmac_start(psa_mac_operation_t *sl_psa_hmac_ctx, psa_key_id_t sl_psa_key_id);

/**
 * Update the HMAC operation with new input.
 *
 * @param[in]  sl_psa_hmac_ctx                      Operation Context for HMAC operation.
 * @param[out] sl_psa_hmac_buffer                   A pointer to the input buffer.
 * @param[in]  sl_psa_hmac_buffer_len               The length of @p sl_psa_hmac_buffer in bytes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_hmac_update(psa_mac_operation_t *sl_psa_hmac_ctx,
                                    const uint8_t *      sl_psa_hmac_buffer,
                                    size_t               sl_psa_hmac_buffer_len);

/**
 * Complete the HMAC operation.
 *
 * @param[in]  sl_psa_hmac_ctx                      Operation Context for HMAC operation.
 * @param[out] sl_psa_hmac_buffer                   A pointer to the output buffer.
 * @param[in]  sl_psa_hmac_buffer_len               The length of @p sl_psa_hmac_buffer in bytes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_hmac_finish(psa_mac_operation_t *sl_psa_hmac_ctx,
                                    const uint8_t *      sl_psa_hmac_buffer,
                                    size_t               sl_psa_hmac_buffer_len);

/**
 * Uninitialize the HMAC operation.
 *
 * @param[in]   sl_psa_hmac_ctx                     Operation Context for HMAC operation.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_hmac_deinit(psa_mac_operation_t *sl_psa_hmac_ctx);

/**
 * Perform HKDF Extract step.
 *
 * @param[in]  sl_psa_key_derivation_ctx            Operation context for key derivation operation.
 * @param[in]  sl_psa_key_derivation_algorithm      Algorithm being used for key derivation.
 * @param[in]  sl_psa_key_id                        Reference to key stored in PSA ITS.
 * @param[in]  sl_psa_key_derivation_salt           Pointer to the Salt for key derivation.
 * @param[in]  sl_psa_key_derivation_salt_length    Length of Salt.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_key_derivation_extract(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                               psa_algorithm_t                 sl_psa_key_derivation_algorithm,
                                               psa_key_id_t                    sl_psa_key_id,
                                               const uint8_t *                 sl_psa_key_derivation_salt,
                                               uint16_t sl_psa_key_derivation_salt_length);

/**
 * Perform HKDF Expand step.
 *
 * @param[in]  sl_psa_key_derivation_ctx            Operation context for HKDF operation.
 * @param[in]  sl_psa_key_derivation_info           Pointer to the Info sequence.
 * @param[in]  sl_psa_key_derivation_info_length    Length of the Info sequence.
 * @param[out] sl_psa_key_derivation_output_key     Pointer to the output Key.
 * @param[in]  sl_psa_key_derivation_output_key_len Size of the output key buffer.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_key_derivation_expand(psa_key_derivation_operation_t *sl_psa_key_derivation_ctx,
                                              const uint8_t *                 sl_psa_key_derivation_info,
                                              uint16_t                        sl_psa_key_derivation_info_length,
                                              uint8_t *                       sl_psa_key_derivation_output_key,
                                              uint16_t sl_psa_key_derivation_output_key_len);

/**
 * Initialise the hashing operation.
 *
 * @param[in]  sl_psa_hash_ctx                      Context for hashing operation.
 *
 * @retval                                          Initial value for a hash operation object.
 */
psa_hash_operation_t sl_sec_man_hash_init(void);

/**
 * De-Initialise the hashing operation.
 *
 * @param[in]  sl_psa_hash_ctx                      Context for hashing operation.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 */
psa_status_t sl_sec_man_hash_deinit(psa_hash_operation_t *sl_psa_hash_ctx);

/**
 * Start SHA-256 operation.
 *
 * @param[in]  sl_psa_hash_ctx                      Context for hashing operation.
 * @param[in]  sl_psa_hash_alg                      Hashing algorithm to use.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_hash_start(psa_hash_operation_t *sl_psa_hash_ctx, psa_algorithm_t sl_psa_hash_alg);

/**
 * Update hashing operation with new input.
 *
 * @param[in]  sl_psa_hash_ctx                      Context for hashing operation.
 * @param[out] sl_psa_hash_buffer                   A pointer to the input buffer.
 * @param[in]  sl_psa_hash_buffer_len               The length of @p sl_psa_hash_buffer in bytes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 */
psa_status_t sl_sec_man_hash_update(psa_hash_operation_t *sl_psa_hash_ctx,
                                    uint8_t *             sl_psa_hash_buffer,
                                    uint16_t              sl_psa_hash_buffer_len);

/**
 * Finish hashing operation.
 *
 * @param[in]  sl_psa_hash_ctx                      Context for hashing operation.
 * @param[in]  sl_psa_hash_hash                     A pointer to the output buffer, where hash needs to be stored.
 * @param[in]  sl_psa_hash_hash_size                The length of @p sl_psa_hash_hash in bytes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 */
psa_status_t sl_sec_man_hash_finish(psa_hash_operation_t *sl_psa_hash_ctx,
                                    uint8_t *             sl_psa_hash,
                                    uint16_t              sl_psa_hash_size,
                                    size_t *              sl_psa_hash_len);

/**
 * Generate Entropy.
 *
 * @param[in]  sl_psa_output_buffer                 Buffer to store the generated entropy.
 * @param[in]  sl_psa_output_size                   Amount of entropy needed in bytes.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_get_random(uint8_t               *sl_psa_output_buffer,
                                   uint16_t              sl_psa_output_size);

/**
 * Export the public key from the key pair.
 *
 * @param[in]  sl_psa_key_id                        Key ID used as a reference to the key.
 * @param[out] sl_psa_output_buffer                 A pointer to the output buffer to store the public key.
 * @param[in]  sl_output_buffer_size                The length of @p sl_psa_output_buffer in bytes.
 * @param[out] sl_public_key_len                    A pointer to a variable to store length of the exported public key.
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_export_public_key(psa_key_id_t        sl_psa_key_id,
                                          uint8_t             *sl_psa_output_buffer,
                                          size_t              sl_output_buffer_size,
                                          size_t              *sl_public_key_len);

/**
 * Sign the given input buffer using the algorithm specified.
 *
 * @param[in]  sl_psa_key_id                        Key ID used as a reference to the key.
 * @param[in]  sl_dsa_algorithm                     DSA Algorithm to use to perform ECDSA sign operation.
 * @param[in]  sl_dsa_input_buf                     A pointer to the input buffer.
 * @param[in]  sl_dsa_input_size                    The length of @p sl_dsa_input_buf in bytes.
 * @param[out] sl_dsa_signature_buf                 A pointer to the output buffer to store the signature.
 * @param[in]  sl_dsa_signature_size                The length of @p sl_dsa_signature_buf in bytes.
 * @param[out] sl_dsa_signature_len                 A pointer to a variable to store length of the generated signature.
 * @param[in]  sl_is_hash                           Is the input a message hash?
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 *
 */
psa_status_t sl_sec_man_sign(psa_key_id_t        sl_psa_key_id,
                             psa_algorithm_t     sl_dsa_algorithm,
                             const uint8_t       *sl_dsa_input_buf,
                             size_t              sl_dsa_input_size,
                             uint8_t             *sl_dsa_signature_buf,
                             size_t              sl_dsa_signature_size,
                             size_t              *sl_dsa_signature_len,
                             bool                sl_is_hash);

/**
 * Verify the given signature using the algorithm specified.
 *
 * @param[in]  sl_psa_key_id                        Key ID used as a reference to the key.
 * @param[in]  sl_dsa_algorithm                     DSA Algorithm to use to perform ECDSA verify operation.
 * @param[in]  sl_dsa_input_buf                     A pointer to the input buffer.
 * @param[in]  sl_dsa_input_size                    The length of @p sl_dsa_input_buf in bytes.
 * @param[in]  sl_dsa_signature_buf                 A pointer to the input buffer to store the signature.
 * @param[in]  sl_dsa_signature_size                The length of @p sl_dsa_signature_buf in bytes.
 * @param[in]  sl_is_hash                           Is the input a message hash?
 *
 * @retval                                          A psa_status_t status code. Refer to /ref psa_status_t.
 */
psa_status_t sl_sec_man_verify(psa_key_id_t        sl_psa_key_id,
                               psa_algorithm_t     sl_dsa_algorithm,
                               const uint8_t       *sl_dsa_input_buf,
                               size_t              sl_dsa_input_size,
                               const uint8_t       *sl_dsa_signature_buf,
                               size_t              sl_dsa_signature_size,
                               bool                sl_is_hash);

#endif /* SECURITY_MANAGER_H_ */
