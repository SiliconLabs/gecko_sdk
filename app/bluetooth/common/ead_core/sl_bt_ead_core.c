/***************************************************************************//**
 * @file
 * @brief Encrypted Advertisement Data core functions implementation.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "em_common.h"
#include "psa/crypto.h"
#include "sl_bt_ead_core.h"
#include "psa/crypto_values.h"
#include "sli_protocol_crypto.h"
#include "sl_bt_ead_core_config.h"

// According to Core Vol 2, Part H, Section 9. the tag (= MIC) size is 32 bits
#define PSA_ALG_BLE_CCM     PSA_ALG_AEAD_WITH_SHORTENED_TAG(PSA_ALG_CCM, \
                                                            SL_BT_EAD_MIC_SIZE)

#if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
// Additional data for EAD encryption, see CSS d11, Part A, 1.23.3
static const uint8_t aad[] = { SL_BT_ENCRYPTED_DATA_B1_HEADER };
static psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
#endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)

/**************************************************************************//**
 * Update the Randomizer field of the EAD Nonce value with newly generated value
 *****************************************************************************/
sl_status_t sl_bt_ead_randomizer_update(sl_bt_ead_nonce_p nonce)
{
  sl_status_t result = SL_STATUS_FAIL;
  psa_status_t status = psa_crypto_init();

  assert(nonce != NULL);

  if (status == PSA_SUCCESS) {
    status = psa_generate_random((uint8_t *)(nonce->randomizer),
                                 SL_BT_EAD_RANDOMIZER_SIZE);
    if (status == PSA_SUCCESS) {
      result = SL_STATUS_OK;
    }
  }

  return result;
}

/**************************************************************************//**
 * Set the Randomizer field of the EAD Nonce value manually to a given value
 *****************************************************************************/
sl_status_t sl_bt_ead_randomizer_set(sl_bt_ead_randomizer_t randomizer,
                                     sl_bt_ead_nonce_p nonce)
{
  sl_status_t result = SL_STATUS_NOT_SUPPORTED;

  assert(nonce != NULL);

  if (randomizer != NULL) {
    memcpy((void *)(nonce->randomizer),
           (const void *)randomizer,
           sizeof(sl_bt_ead_randomizer_t));
    result = SL_STATUS_OK;
  } else {
    return sl_bt_ead_randomizer_update(nonce);
  }

  return result;
}

/**************************************************************************//**
 * (Re)initialize the entire Nonce value with the new key material provided
 *****************************************************************************/
sl_status_t sl_bt_ead_session_init(sl_bt_ead_key_material_p key_material,
                                   sl_bt_ead_randomizer_t   randomizer,
                                   sl_bt_ead_nonce_p        nonce)
{
  uint8_t      tmp[SL_BT_EAD_SESSION_KEY_SIZE];
  sl_status_t  result = SL_STATUS_INITIALIZATION;

  assert(key_material != NULL);

  // Make a copy of the session key, first
  memcpy(tmp, key_material->key, SL_BT_EAD_SESSION_KEY_SIZE);

  // Swap key endianness to make the sli_ccm_[crypto] functions work as expected
  for (unsigned int t = 0; t < SL_BT_EAD_SESSION_KEY_SIZE; t++) {
    key_material->key[(SL_BT_EAD_SESSION_KEY_SIZE - 1) - t] = tmp[t];
  }

  if (nonce != NULL) {
    memcpy((void *)nonce->iv,
           (const void *)key_material->iv,
           SL_BT_EAD_IV_SIZE);

    result = sl_bt_ead_randomizer_set(randomizer, nonce);
  }

  #if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  // Prepare key attributes
  psa_set_key_algorithm(&attributes, PSA_ALG_BLE_CCM);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, SL_BT_EAD_SESSION_KEY_SIZE * 8);
  #endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  return result;
}

/**************************************************************************//**
 * Encrypt message in-place using EAD encryption
 *****************************************************************************/
sl_status_t sl_bt_ead_encrypt(sl_bt_ead_key_material_p key_material,
                              sl_bt_ead_nonce_p        nonce,
                              uint8_t                  length,
                              uint8_t                  *data,
                              sl_bt_ead_mic_t          mic)
{
  sl_status_t  result = SL_STATUS_INITIALIZATION;
  #if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  psa_status_t status;
  psa_key_id_t key_id;
  uint8_t      *output_data;
  size_t       output_length;
  const size_t output_size = length + SL_BT_EAD_MIC_SIZE;
  #endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)

  assert(key_material != NULL);
  assert(nonce != NULL);
  assert(length >= 1);
  assert(data != NULL);
  assert(mic != NULL);

  #if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  // Initialize PSA Crypto
  status = psa_crypto_init();

  if (status == PSA_SUCCESS) {
    result = SL_STATUS_ALLOCATION_FAILED;
    output_data = (uint8_t *)malloc(output_size);

    if (output_data != NULL) {
      result = SL_STATUS_INVALID_KEY;
      // Import the key
      psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT);
      status = psa_import_key(&attributes,
                              key_material->key,
                              sizeof(key_material->key),
                              &key_id);

      if (status == PSA_SUCCESS) {
        result = SL_STATUS_FAIL;
        // Authenticate and encrypt
        status = psa_aead_encrypt(key_id, PSA_ALG_BLE_CCM,
                                  (const uint8_t *)nonce, SL_BT_EAD_NONCE_SIZE,
                                  aad, sizeof(aad),
                                  data, length,
                                  output_data, output_size,
                                  &output_length);

        if (status == PSA_SUCCESS) {
          memcpy(mic, output_data + length, SL_BT_EAD_MIC_SIZE);
          memcpy(data, output_data, length);
          result = SL_STATUS_OK;
        }

        free(output_data);

        // Destroy the key
        psa_destroy_key(key_id);
      }
    }
  }
  #else
  // Use the RADIOAES accelerator instead of PSA Crypto library
  // Can be up to 5-10 times faster and also produces few kilobytes less code
  result = sli_ccm_encrypt_and_tag_ble(data,
                                       length,
                                       (const unsigned char*)key_material->key,
                                       (const unsigned char*)nonce,
                                       SL_BT_ENCRYPTED_DATA_B1_HEADER,
                                       mic);
  #endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  return result;
}

/**************************************************************************//**
 * Decrypt message in-place that is encrypted with EAD
 *****************************************************************************/
sl_status_t sl_bt_ead_decrypt(sl_bt_ead_key_material_p key_material,
                              sl_bt_ead_nonce_p        nonce,
                              sl_bt_ead_mic_t          mic,
                              uint8_t                  length,
                              uint8_t                  *data)
{
  sl_status_t  result = SL_STATUS_INITIALIZATION;
  #if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  psa_status_t status;
  psa_key_id_t key_id;
  uint8_t      *output_data;
  size_t       output_length;
  const size_t output_size = length + SL_BT_EAD_MIC_SIZE;
  #endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  assert(key_material != NULL);
  assert(length >= 1);
  assert(data != NULL);
  assert(mic != NULL);

  #if (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)
  // Initialize PSA Crypto
  status = psa_crypto_init();

  if (status == PSA_SUCCESS) {
    result = SL_STATUS_ALLOCATION_FAILED;
    output_data = (uint8_t *)malloc(output_size);

    if (output_data != NULL) {
      result = SL_STATUS_INVALID_KEY;
      // Import the key
      psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DECRYPT);
      status = psa_import_key(&attributes,
                              key_material->key,
                              sizeof(key_material->key),
                              &key_id);

      if (status == PSA_SUCCESS) {
        result = SL_STATUS_FAIL;
        memcpy(output_data, data, length);
        memcpy(output_data + length, mic, SL_BT_EAD_MIC_SIZE);

        // Authenticate and encrypt
        status = psa_aead_decrypt(key_id, PSA_ALG_BLE_CCM,
                                  (const uint8_t *)nonce, SL_BT_EAD_NONCE_SIZE,
                                  aad, sizeof(aad),
                                  output_data, output_size,
                                  data, length,
                                  &output_length);

        if (status == PSA_SUCCESS) {
          result = SL_STATUS_OK;
        }

        free(output_data);

        // Destroy the key
        psa_destroy_key(key_id);
      }
    }
  }
  #else
  // Use the RADIOAES accelerator instead of PSA Crypto library
  // Can be up to 5-10 times faster and also produces few kilobytes less code
  result = sli_ccm_auth_decrypt_ble(data,
                                    length,
                                    (const unsigned char*)key_material->key,
                                    (const unsigned char*)nonce,
                                    SL_BT_ENCRYPTED_DATA_B1_HEADER,
                                    mic);
  #endif // (SL_BT_EAD_CORE_ACCELERATOR == SL_BT_EAD_CORE_USE_PSA_ACC)

  return result;
}

/**************************************************************************//**
 *  Unpack advertising data that is encrypted with EAD and decrypt the message
 *****************************************************************************/
sl_status_t sl_bt_ead_unpack_decrypt(sl_bt_ead_key_material_p key_material,
                                     uint8_t                  **data,
                                     uint8_t                  *length)
{
  sl_status_t result = SL_STATUS_INVALID_TYPE;
  uint32_t data_length;

  assert(key_material != NULL);
  assert(length != NULL);
  assert(data != NULL);
  assert(*data != NULL);

  data_length = (uint32_t)(*data)[0];
  // Check if the encrypted data has the minimum expected size
  if (data_length < SL_BT_EAD_PACKET_OVERHEAD) {
    result = SL_STATUS_INVALID_COUNT;
  } else if ((*data)[1] == SL_BT_ENCRYPTED_DATA_AD_TYPE) {
    // The type field reported an Encrypted AD Data type, continue
    struct sl_bt_ead_nonce_s nonce;

    // Init local nonce for the session before decrypt
    memcpy((void *)nonce.iv,
           (const void *)key_material->iv,
           SL_BT_EAD_IV_SIZE);

    result = sl_bt_ead_randomizer_set(*data + SL_BT_EAD_HEADER_SIZE,
                                      &nonce);

    data_length -= SL_BT_EAD_PACKET_REDUCED_OVERHEAD;

    if (result == SL_STATUS_OK) {
      uint32_t start_index = SL_BT_EAD_HEADER_SIZE + SL_BT_EAD_RANDOMIZER_SIZE;
      uint32_t mic_index = start_index + data_length;

      *length = (uint8_t)data_length;
      result = sl_bt_ead_decrypt(key_material,
                                 &nonce,
                                 *data + mic_index,
                                 *length,
                                 *data + start_index);

      if (result == SL_STATUS_OK) {
        *data += start_index;
      }
    }
  }

  return result;
}

/**************************************************************************//**
 * Pack encrypted EAD AD_Data to Advertising, Periodic Advertising, and Scan
 * Response Data packet
 *****************************************************************************/
sl_status_t sl_bt_ead_pack_ad_data(sl_bt_ead_ad_structure_p ad_info,
                                   uint8_t         *size,
                                   uint8_t         *pack_buf)
{
  sl_status_t result = SL_STATUS_WOULD_OVERFLOW;
  uint32_t    data_index;

  // Check for invalid parameters
  assert(ad_info != NULL);
  assert(size != NULL);
  assert(pack_buf != NULL);

  // Check for uninitialized ad_info structure
  assert(ad_info->randomizer != NULL);
  assert(ad_info->ad_data != NULL);
  assert(ad_info->mic != NULL);

  // Check for valid encrypted length
  if (ad_info->length < 1) {
    result = SL_STATUS_ABORT;
  } else if (*size >= (ad_info->length + SL_BT_EAD_PACKET_OVERHEAD)) {
    // Set packet length for the serialized data and the AD Type
    pack_buf[0] = ad_info->length;
    pack_buf[0] += SL_BT_EAD_PACKET_OVERHEAD - SL_BT_EAD_LENGTH_FIELD_SIZE;
    pack_buf[1] = ad_info->ad_type;

    // Copy the randomizer to the first part of the encrypted data
    data_index = SL_BT_EAD_HEADER_SIZE;
    memcpy(pack_buf + data_index,
           ad_info->randomizer,
           SL_BT_EAD_RANDOMIZER_SIZE);

    // Copy the the encrypted data
    data_index += SL_BT_EAD_RANDOMIZER_SIZE;
    memcpy(pack_buf + data_index, ad_info->ad_data, ad_info->length);

    // Copy the the MIC
    data_index += ad_info->length;
    memcpy(pack_buf + data_index, ad_info->mic, SL_BT_EAD_MIC_SIZE);

    // Set the size output variable according to the final length of the packet
    *size = data_index + SL_BT_EAD_MIC_SIZE;

    result = SL_STATUS_OK;
  }

  return result;
}

/**************************************************************************//**
 * Unpack encrypted EAD Data from Advertising, Periodic Advertising, and Scan
 * Response data format
 *****************************************************************************/
sl_status_t sl_bt_ead_unpack_ad_data(uint8_t                  *packed_data,
                                     sl_bt_ead_ad_structure_p ad_info)
{
  sl_status_t result = SL_STATUS_INVALID_TYPE;
  uint32_t data_length;

  assert(packed_data != NULL);
  assert(ad_info != NULL);
  assert(ad_info->randomizer != NULL);
  assert(ad_info->ad_data != NULL);
  assert(ad_info->mic != NULL);

  data_length = (uint32_t)packed_data[0];
  ad_info->ad_type = packed_data[1];

  // Check if the encrypted data has the minimum expected size
  if (data_length < SL_BT_EAD_PACKET_OVERHEAD) {
    result = SL_STATUS_INVALID_COUNT;
  } else if (ad_info->ad_type == SL_BT_ENCRYPTED_DATA_AD_TYPE) {
    // The type field reported an Encrypted AD Data type, get AD Data length
    data_length -= SL_BT_EAD_PACKET_REDUCED_OVERHEAD;

    if (ad_info->length >= data_length) {
      uint32_t    data_index;
      // Copy the randomizer to the first part of the encrypted data
      data_index = SL_BT_EAD_HEADER_SIZE;
      memcpy(*ad_info->randomizer,
             packed_data + data_index,
             SL_BT_EAD_RANDOMIZER_SIZE);

      // Copy the the encrypted data
      data_index += SL_BT_EAD_RANDOMIZER_SIZE;
      ad_info->length = data_length;
      memcpy(ad_info->ad_data, packed_data + data_index, ad_info->length);

      // Copy the the MIC
      data_index += ad_info->length;
      memcpy(*ad_info->mic, packed_data + data_index, SL_BT_EAD_MIC_SIZE);

      result = SL_STATUS_OK;
    } else {
      result = SL_STATUS_WOULD_OVERFLOW;
    }
  }

  return result;
}

// Workaround for a bug (feature?) in IAR compiler that may break build, see:
// https://www.iar.com/sv/knowledge/learn/programming/overriding-and-redirecting-library-modules-without-rebuilding-the-entire-library/
#if defined(__ICCARM__) && !defined(SL_CATALOG_RETARGET_STDIO_PRESENT)
SL_WEAK __ATTRIBUTES size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  // This dependency is sneakily introduced by the 3rd party mbedtls utility
  // with its dependency on stdlib printf method - for which the IAR compiler
  // apparently does not provide a sufficient __write() method by default.
  (void)handle;
  (void)buffer;
  (void)size;
  return 0;
}
#endif
