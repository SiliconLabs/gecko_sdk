/***************************************************************************//**
 * @file
 * @brief PSA ITS implementation based on Silicon Labs NVM3
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

// The psa_driver_wrappers.h file that we're including here assumes that it has
// access to private struct members. Define this here in order to avoid
// compilation errors.
#define MBEDTLS_ALLOW_PRIVATE_ACCESS

// -------------------------------------
// Includes

#include <mbedtls/build_info.h>

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && !defined(MBEDTLS_PSA_ITS_FILE_C)

#include "psa/internal_trusted_storage.h"
#include "psa/sli_internal_trusted_storage.h"
#include "nvm3_default.h"
#include "mbedtls/platform.h"
#include <stdbool.h>
#include <string.h>

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  #include <arm_cmse.h>
  #include "psa/storage_common.h"
#endif // TFM_CONFIG_SL_SECURE_LIBRARY

#if defined(SLI_PSA_ITS_ENCRYPTED)
  #include "psa_crypto_core.h"
  #include "psa_crypto_driver_wrappers.h"
  #if defined(SEMAILBOX_PRESENT)
    #include "psa/crypto_extra.h"
    #include "sl_psa_values.h"
    #include "sli_se_opaque_functions.h"
  #endif // defined(SEMAILBOX_PRESENT)
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Threading support

#if defined(MBEDTLS_THREADING_C)
#include "cmsis_os2.h"
#include "mbedtls/threading.h"

// Mutex for protecting access to the ITS instance
static mbedtls_threading_mutex_t its_mutex;
static volatile bool its_mutex_inited = false;

/**
 * \brief          Lock all task switches
 *
 * \return         Previous lock state
 *
 */
static inline int32_t lock_task_switches(void)
{
  int32_t kernel_lock_state = 0;
  osKernelState_t kernel_state = osKernelGetState();
  if (kernel_state != osKernelInactive && kernel_state != osKernelReady) {
    kernel_lock_state = osKernelLock();
  }
  return kernel_lock_state;
}

/**
 * \brief          Restores the previous lock state
 */
static inline void restore_lock_state(int32_t kernel_lock_state)
{
  osKernelState_t kernel_state = osKernelGetState();
  if (kernel_state != osKernelInactive && kernel_state != osKernelReady) {
    if (osKernelRestoreLock(kernel_lock_state) < 0) {
      EFM_ASSERT(false);
    }
  }
}

#endif // defined(MBEDTLS_THREADING_C)

/**
 * \brief Pend on the ITS mutex
 */
void sli_its_acquire_mutex(void)
{
#if defined(MBEDTLS_THREADING_C)
  if (!its_mutex_inited) {
    int32_t kernel_lock_state = lock_task_switches();
    if (!its_mutex_inited) {
      mbedtls_mutex_init(&its_mutex);
      its_mutex_inited = true;
    }
    restore_lock_state(kernel_lock_state);
  }
  if (mbedtls_mutex_lock(&its_mutex) != 0) {
    EFM_ASSERT(false);
  }
#endif
}

/**
 * \brief Free the ITS mutex.
 */
void sli_its_release_mutex(void)
{
#if defined(MBEDTLS_THREADING_C)
  if (its_mutex_inited) {
    mbedtls_mutex_unlock(&its_mutex);
  }
#endif
}

// -------------------------------------
// Defines

#if (!SL_PSA_ITS_SUPPORT_V3_DRIVER)
#define SLI_PSA_ITS_NVM3_RANGE_START SLI_PSA_ITS_NVM3_RANGE_BASE
#define SLI_PSA_ITS_NVM3_RANGE_END   SLI_PSA_ITS_NVM3_RANGE_START + SL_PSA_ITS_MAX_FILES

#define SLI_PSA_ITS_NVM3_INVALID_KEY (0)
#define SLI_PSA_ITS_NVM3_UNKNOWN_KEY (1)

#if SL_PSA_ITS_MAX_FILES > SLI_PSA_ITS_NVM3_RANGE_SIZE
#error "Trying to store more ITS files then our NVM3 range allows for"
#endif

#define SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE 16

// Enable backwards-compatibility with keys stored with a v1 header unless disabled.
#if !defined(SL_PSA_ITS_REMOVE_V1_HEADER_SUPPORT)
#define SLI_PSA_ITS_SUPPORT_V1_FORMAT
#endif

// Internal error codes local to this compile unit
#define SLI_PSA_ITS_ECODE_NO_VALID_HEADER (ECODE_EMDRV_NVM3_BASE - 1)
#define SLI_PSA_ITS_ECODE_NEEDS_UPGRADE   (ECODE_EMDRV_NVM3_BASE - 2)

// SLI_STATIC_TESTABLE is used to expose otherwise-static variables during internal testing.
#if !defined(SLI_STATIC_TESTABLE)
#define SLI_STATIC_TESTABLE static
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
// Define some cryptographic constants if not already set. This depends on the underlying
// crypto accelerator in use (CRYPTOACC has these defines, but not SEMAILBOX).
#if !defined(AES_MAC_SIZE)
#define AES_MAC_SIZE 16
#endif

#if !defined(AES_IV_GCM_SIZE)
#define AES_IV_GCM_SIZE 12
#endif

#define SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD  (AES_IV_GCM_SIZE + AES_MAC_SIZE)
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Local global static variables

SLI_STATIC_TESTABLE bool nvm3_uid_set_cache_initialized = false;
SLI_STATIC_TESTABLE uint32_t nvm3_uid_set_cache[(SL_PSA_ITS_MAX_FILES + 31) / 32] = { 0 };

typedef struct {
  psa_storage_uid_t uid;
  nvm3_ObjectKey_t object_id;
  bool set;
} previous_lookup_t;

static previous_lookup_t previous_lookup = {
  0, 0, false
};

#if defined(SLI_PSA_ITS_ENCRYPTED)
// The root key is an AES-256 key, and is therefore 32 bytes.
#define ROOT_KEY_SIZE     (32)
// The session key is derived from CMAC, which means it is equal to the AES block size, i.e. 16 bytes
#define SESSION_KEY_SIZE  (16)

#if !defined(SEMAILBOX_PRESENT)
typedef struct {
  bool initialized;
  uint8_t data[ROOT_KEY_SIZE];
} root_key_t;

static root_key_t g_root_key = {
  .initialized = false,
  .data = { 0 },
};
#endif // !defined(SEMAILBOX_PRESENT)

typedef struct {
  bool active;
  psa_storage_uid_t uid;
  uint8_t data[SESSION_KEY_SIZE];
} session_key_t;

static session_key_t g_cached_session_key = {
  .active = false,
  .uid = 0,
  .data = { 0 },
};
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Structs

#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)
typedef struct {
  uint32_t magic;
  psa_storage_uid_t uid;
  psa_storage_create_flags_t flags;
} sl_its_file_meta_v1_t;
#endif // defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)

// Due to alignment constraints on the 64-bit UID, the v2 header struct is
// serialized to 16 bytes instead of the 24 bytes the v1 header compiles to.
typedef struct {
  uint32_t magic;
  psa_storage_create_flags_t flags;
  psa_storage_uid_t uid;
} sli_its_file_meta_v2_t;

#if defined(SLI_PSA_ITS_ENCRYPTED)
typedef struct {
  uint8_t iv[AES_IV_GCM_SIZE];
  // When encrypted & authenticated, MAC is stored at the end of the data array
  uint8_t data[];
} sli_its_encrypted_blob_t;
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Local function prototypes

static nvm3_ObjectKey_t get_nvm3_id(psa_storage_uid_t uid, bool find_empty_slot);
static nvm3_ObjectKey_t prepare_its_get_nvm3_id(psa_storage_uid_t uid);

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
static inline bool object_lives_in_s(const void *object, size_t object_size);
#endif // defined(TFM_CONFIG_SL_SECURE_LIBRARY)

#if defined(SLI_PSA_ITS_ENCRYPTED)
static psa_status_t derive_session_key(uint8_t *iv,
                                       size_t iv_size,
                                       uint8_t *session_key,
                                       size_t session_key_size);

static psa_status_t encrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                     uint8_t *plaintext,
                                     size_t plaintext_size,
                                     sli_its_encrypted_blob_t *blob,
                                     size_t blob_size,
                                     size_t *blob_length);

static psa_status_t decrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                     sli_its_encrypted_blob_t *blob,
                                     size_t blob_size,
                                     uint8_t *plaintext,
                                     size_t plaintext_size,
                                     size_t *plaintext_length);

static psa_status_t authenticate_its_file(nvm3_ObjectKey_t nvm3_object_id,
                                          psa_storage_uid_t *authenticated_uid);
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Local function definitions

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
// If an object of given size is fully encapsulated in a region of
// secure domain the function returns true.
static inline bool object_lives_in_s(const void *object, size_t object_size)
{
  cmse_address_info_t cmse_flags;

  for (size_t i = 0u; i < object_size; i++) {
    cmse_flags = cmse_TTA((uint32_t *)object + i);
    if (!cmse_flags.flags.secure) {
      return false;
    }
  }

  return true;
}
#endif // defined(TFM_CONFIG_SL_SECURE_LIBRARY)

static inline void cache_set(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SLI_PSA_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  nvm3_uid_set_cache[bin] |= (1 << offset);
}

static inline void cache_clear(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SLI_PSA_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  nvm3_uid_set_cache[bin] ^= (1 << offset);
}

static inline bool cache_lookup(nvm3_ObjectKey_t key)
{
  uint32_t i = key - SLI_PSA_ITS_NVM3_RANGE_START;
  uint32_t bin = i / 32;
  uint32_t offset = i - 32 * bin;
  return (bool)((nvm3_uid_set_cache[bin] >> offset) & 0x1);
}

static void init_cache(void)
{
  size_t num_keys_referenced_by_nvm3;
  nvm3_ObjectKey_t keys_referenced_by_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE] = { 0 };

  for (nvm3_ObjectKey_t range_start = SLI_PSA_ITS_NVM3_RANGE_START;
       range_start < SLI_PSA_ITS_NVM3_RANGE_END;
       range_start += SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE) {
    nvm3_ObjectKey_t range_end = range_start + SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE;
    if (range_end > SLI_PSA_ITS_NVM3_RANGE_END) {
      range_end = SLI_PSA_ITS_NVM3_RANGE_END;
    }

    num_keys_referenced_by_nvm3 = nvm3_enumObjects(nvm3_defaultHandle,
                                                   keys_referenced_by_nvm3,
                                                   sizeof(keys_referenced_by_nvm3) / sizeof(nvm3_ObjectKey_t),
                                                   range_start,
                                                   range_end - 1);

    for (size_t i = 0; i < num_keys_referenced_by_nvm3; i++) {
      cache_set(keys_referenced_by_nvm3[i]);
    }
  }

  nvm3_uid_set_cache_initialized = true;
}

// Read the file metadata for a specific NVM3 ID
static Ecode_t get_file_metadata(nvm3_ObjectKey_t key,
                                 sli_its_file_meta_v2_t* metadata,
                                 size_t* its_file_offset,
                                 size_t* its_file_size)
{
  // Initialize output variables to safe default
  if (its_file_offset != NULL) {
    *its_file_offset = 0;
  }
  if (its_file_size != NULL) {
    *its_file_size = 0;
  }

  Ecode_t status = nvm3_readPartialData(nvm3_defaultHandle,
                                        key,
                                        metadata,
                                        0,
                                        sizeof(sli_its_file_meta_v2_t));
  if (status != ECODE_NVM3_OK) {
    return status;
  }

#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)
  // Re-read in v1 header format and translate to the latest structure version
  if (metadata->magic == SLI_PSA_ITS_META_MAGIC_V1) {
    sl_its_file_meta_v1_t key_meta_v1 = { 0 };
    status = nvm3_readPartialData(nvm3_defaultHandle,
                                  key,
                                  &key_meta_v1,
                                  0,
                                  sizeof(sl_its_file_meta_v1_t));

    if (status != ECODE_NVM3_OK) {
      return status;
    }

    metadata->flags = key_meta_v1.flags;
    metadata->uid = key_meta_v1.uid;
    metadata->magic = SLI_PSA_ITS_META_MAGIC_V2;

    if (its_file_offset != NULL) {
      *its_file_offset = sizeof(sl_its_file_meta_v1_t);
    }

    status = SLI_PSA_ITS_ECODE_NEEDS_UPGRADE;
  } else
#endif
  {
    if (its_file_offset != NULL) {
      *its_file_offset = sizeof(sli_its_file_meta_v2_t);
    }
  }

  if (metadata->magic != SLI_PSA_ITS_META_MAGIC_V2) {
    // No valid header found in this object
    return SLI_PSA_ITS_ECODE_NO_VALID_HEADER;
  }

  if (its_file_offset != NULL && its_file_size != NULL) {
    // Calculate the ITS file size if requested
    uint32_t obj_type;
    Ecode_t info_status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                             key,
                                             &obj_type,
                                             its_file_size);
    if (info_status != ECODE_NVM3_OK) {
      return info_status;
    }

    *its_file_size = *its_file_size - *its_file_offset;
  }

  return status;
}

// Search through NVM3 for uid
static nvm3_ObjectKey_t get_nvm3_id(psa_storage_uid_t uid, bool find_empty_slot)
{
  Ecode_t status;
  sli_its_file_meta_v2_t key_meta;

  if (find_empty_slot) {
    for (size_t i = 0; i < SL_PSA_ITS_MAX_FILES; i++) {
      if (!cache_lookup(i + SLI_PSA_ITS_NVM3_RANGE_START)) {
        return i + SLI_PSA_ITS_NVM3_RANGE_START;
      }
    }
  } else {
    if (previous_lookup.set) {
      if (previous_lookup.uid == uid) {
        return previous_lookup.object_id;
      }
    }

    for (size_t i = 0; i < SL_PSA_ITS_MAX_FILES; i++) {
      if (!cache_lookup(i + SLI_PSA_ITS_NVM3_RANGE_START)) {
        continue;
      }
      nvm3_ObjectKey_t object_id = i + SLI_PSA_ITS_NVM3_RANGE_START;

      status = get_file_metadata(object_id, &key_meta, NULL, NULL);

      if (status == ECODE_NVM3_OK
          || status == SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
        if (key_meta.uid == uid) {
          previous_lookup.set = true;
          previous_lookup.object_id = object_id;
          previous_lookup.uid = uid;

          return object_id;
        } else {
          continue;
        }
      }

      if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER
          || status == ECODE_NVM3_ERR_READ_DATA_SIZE) {
        // we don't expect any other data in our range then PSA ITS files.
        // delete the file if the magic doesn't match or the object on disk
        // is too small to even have full metadata.
        status = nvm3_deleteObject(nvm3_defaultHandle, object_id);
        if (status != ECODE_NVM3_OK) {
          return SLI_PSA_ITS_NVM3_RANGE_END + 1U;
        }
      }
    }
  }

  return SLI_PSA_ITS_NVM3_RANGE_END + 1U;
}

// Perform NVM3 open and fill the look-up table.
// Try to find the mapping NVM3 object ID with PSA ITS UID.
static nvm3_ObjectKey_t prepare_its_get_nvm3_id(psa_storage_uid_t uid)
{
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  // With SKL the NVM3 instance must be initialized by the NS app. We therefore check that
  // it has been opened (which is done on init) rather than actually doing the init.
  if (!nvm3_defaultHandle->hasBeenOpened) {
#else
  if (nvm3_initDefault() != ECODE_NVM3_OK) {
#endif
    return SLI_PSA_ITS_NVM3_RANGE_END + 1U;
  }

  if (nvm3_uid_set_cache_initialized == false) {
    init_cache();
  }

  return get_nvm3_id(uid, false);
}

#if defined(SLI_PSA_ITS_ENCRYPTED)
static inline void cache_session_key(uint8_t *session_key, psa_storage_uid_t uid)
{
  // Cache the session key
  memcpy(g_cached_session_key.data, session_key, sizeof(g_cached_session_key.data));
  g_cached_session_key.uid = uid;
  g_cached_session_key.active = true;
}

/**
 * \brief Derive a session key for ITS file encryption from the initialized root key and provided IV.
 *
 * \param[in] iv                Pointer to array containing the initialization vector to be used in the key derivation.
 * \param[in] iv_size           Size of the IV buffer in bytes. Must be 12 bytes (AES-GCM IV size).
 * \param[out] session_key      Pointer to array where derived session key shall be stored.
 * \param[out] session_key_size Size of the derived session key output array. Must be at least 32 bytes (AES-256 key size).
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because iv or session_key is NULL, or their sizes are incorrect.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t derive_session_key(uint8_t *iv, size_t iv_size, uint8_t *session_key, size_t session_key_size)
{
  if (iv == NULL
      || iv_size != AES_IV_GCM_SIZE
      || session_key == NULL
      || session_key_size < SESSION_KEY_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

#if defined(SEMAILBOX_PRESENT)
  // For HSE devices, use the builtin TrustZone Root Key
  psa_set_key_id(&attributes, SL_SE_BUILTIN_KEY_TRUSTZONE_ID);

  psa_key_lifetime_t reported_lifetime;
  psa_drv_slot_number_t reported_slot;
  status = mbedtls_psa_platform_get_builtin_key(psa_get_key_id(&attributes),
                                                &reported_lifetime,
                                                &reported_slot);

  if (status != PSA_SUCCESS) {
    return status;
  }

  psa_set_key_lifetime(&attributes, reported_lifetime);

  uint8_t key_buffer[sizeof(sli_se_opaque_key_context_header_t)];
  size_t key_buffer_size;
  status = sli_se_opaque_get_builtin_key(reported_slot,
                                         &attributes,
                                         key_buffer,
                                         sizeof(key_buffer),
                                         &key_buffer_size);
  if (status != PSA_SUCCESS) {
    return status;
  }
#else // defined(SEMAILBOX_PRESENT)
  // For VSE devices, use the previously initialized root key
  if (!g_root_key.initialized) {
    return PSA_ERROR_BAD_STATE;
  }

  // Prepare root key attributes
  psa_set_key_algorithm(&attributes, PSA_ALG_CMAC);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, ROOT_KEY_SIZE * 8);

  // Point the key buffer to the global root key
  uint8_t *key_buffer = (uint8_t*)g_root_key.data;
  size_t key_buffer_size = sizeof(g_root_key.data);
#endif // defined(SEMAILBOX_PRESENT)

  // Use CMAC as a key derivation function
  size_t session_key_length;
  status = psa_driver_wrapper_mac_compute(
    &attributes,
    key_buffer,
    key_buffer_size,
    PSA_ALG_CMAC,
    iv,
    iv_size,
    session_key,
    session_key_size,
    &session_key_length);

  // Verify that the key derivation was successful before transferring the key to the caller
  if (status != PSA_SUCCESS || session_key_length != SESSION_KEY_SIZE) {
    memset(session_key, 0, session_key_size);
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return status;
}

/**
 * \brief Encrypt and authenticate ITS data with AES-128-GCM, storing the result in an encrypted blob.
 *
 * \param[in] metadata        ITS metadata to be used as authenticated additional data.
 * \param[in] plaintext       Pointer to array containing data to be encrypted.
 * \param[in] plaintext_size  Size of provided plaintext data array.
 * \param[out] blob           Pointer to array where the resulting encrypted blob shall be placed.
 * \param[in] blob_size       Size of the output array. Must be at least as big as plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
 * \param[out] blob_length    Resulting size of the output blob.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t encrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                     uint8_t *plaintext,
                                     size_t plaintext_size,
                                     sli_its_encrypted_blob_t *blob,
                                     size_t blob_size,
                                     size_t *blob_length)
{
  if (metadata == NULL
      || (plaintext == NULL && plaintext_size > 0)
      || blob == NULL
      || blob_size < plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
      || blob_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Generate IV
  size_t iv_length = 0;
  psa_status_t psa_status = mbedtls_psa_external_get_random(NULL, blob->iv, AES_IV_GCM_SIZE, &iv_length);

  if (psa_status != PSA_SUCCESS || iv_length != AES_IV_GCM_SIZE) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Prepare encryption key
  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT);
  psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, SESSION_KEY_SIZE * 8);

  uint8_t session_key[SESSION_KEY_SIZE];
  psa_status = derive_session_key(blob->iv, AES_IV_GCM_SIZE, session_key, sizeof(session_key));
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  cache_session_key(session_key, metadata->uid);

  // Retrieve data to be encrypted
  if (plaintext_size != 0U) {
    memcpy(blob->data, ((uint8_t*)plaintext), plaintext_size);
  }

  // Encrypt and authenticate blob
  size_t output_length = 0;
  psa_status = psa_driver_wrapper_aead_encrypt(
    &attributes,
    session_key, sizeof(session_key),
    PSA_ALG_GCM,
    blob->iv, sizeof(blob->iv),
    (uint8_t*)metadata, sizeof(sli_its_file_meta_v2_t),    // metadata is AAD
    blob->data, plaintext_size,
    blob->data, plaintext_size + AES_MAC_SIZE,    // output == input for in-place encryption
    &output_length);

  // Clear the local session key immediately after we're done using it
  memset(session_key, 0, sizeof(session_key));

  if (psa_status != PSA_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  if (output_length != plaintext_size + AES_MAC_SIZE) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *blob_length = output_length + AES_IV_GCM_SIZE;

  return PSA_SUCCESS;
}

/**
 * \brief Decrypt and authenticate encrypted ITS data.
 *
 * \param[in] metadata          ITS metadata to be used as authenticated additional data. Must be identical to the metadata used during encryption.
 * \param[in] blob              Encrypted blob containing data to be decrypted.
 * \param[in] blob_size         Size of the encrypted blob in bytes.
 * \param[out] plaintext        Pointer to array where the decrypted plaintext shall be placed.
 * \param[in] plaintext_size    Size of the plaintext array. Must be equal to sizeof(blob->data) - AES_MAC_SIZE.
 * \param[out] plaintext_length Resulting length of the decrypted plaintext.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_INVALID_SIGANTURE      The operation failed because authentication of the decrypted data failed.
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t decrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                     sli_its_encrypted_blob_t *blob,
                                     size_t blob_size,
                                     uint8_t *plaintext,
                                     size_t plaintext_size,
                                     size_t *plaintext_length)
{
  if (metadata == NULL
      || blob == NULL
      || blob_size < plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
      || (plaintext == NULL && plaintext_size > 0)
      || plaintext_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Prepare decryption key
  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DECRYPT);
  psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, SESSION_KEY_SIZE * 8);

  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  uint8_t session_key[SESSION_KEY_SIZE];

  if (g_cached_session_key.active && g_cached_session_key.uid == metadata->uid) {
    // Use cached session key if it's already set and UID matches
    memcpy(session_key, g_cached_session_key.data, sizeof(session_key));
  } else {
    psa_status = derive_session_key(blob->iv, AES_IV_GCM_SIZE, session_key, sizeof(session_key));
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
    cache_session_key(session_key, metadata->uid);
  }

  // Decrypt and authenticate blob
  size_t output_length = 0;
  psa_status = psa_driver_wrapper_aead_decrypt(
    &attributes,
    session_key, sizeof(session_key),
    PSA_ALG_GCM,
    blob->iv, sizeof(blob->iv),
    (uint8_t*)metadata, sizeof(sli_its_file_meta_v2_t),    // metadata is AAD
    blob->data, plaintext_size + AES_MAC_SIZE,
    plaintext, plaintext_size,
    &output_length);

  // Clear the session key immediately after we're done using it
  memset(session_key, 0, sizeof(session_key));

  // Invalid signature likely means that NVM data was tampered with
  if (psa_status == PSA_ERROR_INVALID_SIGNATURE) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }

  if (psa_status != PSA_SUCCESS
      || output_length != plaintext_size) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *plaintext_length = output_length;

  return PSA_SUCCESS;
}

/**
 * \brief Authenticate encrypted ITS data and return the UID of the ITS file that was authenticated.
 *
 * \details NOTE: This function will run decrypt_its_file() internally. The difference from the decrypt_its_file()
 *          function is that authenticate_its_file() reads the NVM3 data, decrypts it in order to authenticate the
 *          stored data, and then discards the plaintext. This is needed since PSA Crypto doesn't support the
 *          GMAC primitive directly, which means we have to run a full GCM decrypt for authentication.
 *
 * \param[in] nvm3_object_id      The NVM3 id corresponding to the stored ITS file.
 * \param[out] authenticated_uid  UID for the authenticated ITS file.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_INVALID_SIGANTURE      The operation failed because authentication of the decrypted data failed.
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t authenticate_its_file(nvm3_ObjectKey_t nvm3_object_id,
                                          psa_storage_uid_t *authenticated_uid)
{
  psa_status_t ret = PSA_ERROR_CORRUPTION_DETECTED;
  sli_its_file_meta_v2_t *its_file_meta = NULL;
  sli_its_encrypted_blob_t *blob = NULL;

  uint32_t obj_type;
  size_t its_file_size = 0;
  Ecode_t status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                      nvm3_object_id,
                                      &obj_type,
                                      &its_file_size);
  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size);
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(its_file_buffer, 0, its_file_size);

  status = nvm3_readData(nvm3_defaultHandle,
                         nvm3_object_id,
                         its_file_buffer,
                         its_file_size);
  if (status != ECODE_NVM3_OK) {
    ret = PSA_ERROR_STORAGE_FAILURE;
    goto cleanup;
  }

  its_file_meta = (sli_its_file_meta_v2_t*)its_file_buffer;
  blob = (sli_its_encrypted_blob_t*)(its_file_buffer + sizeof(sli_its_file_meta_v2_t));

  // Decrypt and authenticate blob
  size_t plaintext_length;
  ret = decrypt_its_file(its_file_meta,
                         blob,
                         its_file_size - sizeof(sli_its_file_meta_v2_t),
                         blob->data,
                         its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                         &plaintext_length);

  if (ret != PSA_SUCCESS) {
    goto cleanup;
  }

  if (plaintext_length != (its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    ret = PSA_ERROR_INVALID_SIGNATURE;
    goto cleanup;
  }

  if (authenticated_uid != NULL) {
    *authenticated_uid = its_file_meta->uid;
  }

  ret = PSA_SUCCESS;

  cleanup:

  // Discard output, as we're only interested in whether the authentication check passed or not.
  memset(its_file_buffer, 0, its_file_size);
  mbedtls_free(its_file_buffer);

  return ret;
}
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Global function definitions

/**
 * \brief create a new or modify an existing uid/value pair
 *
 * \param[in] uid           the identifier for the data
 * \param[in] data_length   The size in bytes of the data in `p_data`
 * \param[in] p_data        A buffer containing the data
 * \param[in] create_flags  The flags that the data will be stored with
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_NOT_PERMITTED          The operation failed because the provided `uid` value was already created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_NOT_SUPPORTED          The operation failed because one or more of the flags provided in `create_flags` is not supported or is not valid
 * \retval      PSA_ERROR_INSUFFICIENT_STORAGE   The operation failed because there was insufficient space on the storage medium
 * \retval      PSA_ERROR_STORAGE_FAILURE        The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one of the provided pointers(`p_data`)
 *                                               is invalid, for example is `NULL` or references memory the caller cannot access
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,
                         uint32_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags)
{
  if (data_length > NVM3_MAX_OBJECT_SIZE) {
    return PSA_ERROR_STORAGE_FAILURE;
  }
  if ((data_length != 0U) && (p_data == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (create_flags != PSA_STORAGE_FLAG_WRITE_ONCE
      && create_flags != PSA_STORAGE_FLAG_NONE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
      && create_flags != PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
      ) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  if ((create_flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE)
      && (!object_lives_in_s(p_data, data_length))) {
    // The flag indicates that this data should not be set by the non-secure domain
    return PSA_ERROR_INVALID_ARGUMENT;
  }
#endif
  sli_its_acquire_mutex();
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  Ecode_t status;
  psa_status_t ret = PSA_SUCCESS;
  sli_its_file_meta_v2_t* its_file_meta;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  psa_storage_uid_t authenticated_uid;
  sli_its_encrypted_blob_t *blob = NULL;
  size_t blob_length = 0u;
  psa_status_t psa_status;

  size_t its_file_size = data_length + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#else
  size_t its_file_size = data_length;
#endif

  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size + sizeof(sli_its_file_meta_v2_t));
  if (its_file_buffer == NULL) {
    ret = PSA_ERROR_INSUFFICIENT_MEMORY;
    goto exit;
  }
  memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));

  its_file_meta = (sli_its_file_meta_v2_t *)its_file_buffer;
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    // ITS UID was not found. Request a new.
    nvm3_object_id = get_nvm3_id(0ULL, true);
    if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
      // The storage is full, or an error was returned during cleanup.
      ret = PSA_ERROR_INSUFFICIENT_STORAGE;
    } else {
      its_file_meta->uid = uid;
      its_file_meta->magic = SLI_PSA_ITS_META_MAGIC_V2;
    }
  } else {
    // ITS UID was found. Read ITS meta data.
    status = get_file_metadata(nvm3_object_id, its_file_meta, NULL, NULL);

    if (status != ECODE_NVM3_OK
        && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
      ret = PSA_ERROR_STORAGE_FAILURE;
      goto exit;
    }

    if (its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
        || its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
        ) {
      ret = PSA_ERROR_NOT_PERMITTED;
      goto exit;
    }

#if defined(SLI_PSA_ITS_ENCRYPTED)
    // If the UID already exists, authenticate the existing value and make sure the stored UID is the same.
    ret = authenticate_its_file(nvm3_object_id, &authenticated_uid);
    if (ret != PSA_SUCCESS) {
      goto exit;
    }

    if (authenticated_uid != uid) {
      ret = PSA_ERROR_NOT_PERMITTED;
      goto exit;
    }
#endif
  }

  its_file_meta->flags = create_flags;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Everything after the file metadata will make up the encrypted & authenticated blob
  blob = (sli_its_encrypted_blob_t*)(its_file_buffer + sizeof(sli_its_file_meta_v2_t));

  // Encrypt and authenticate the provided data
  psa_status = encrypt_its_file(its_file_meta,
                                (uint8_t*)p_data,
                                data_length,
                                blob,
                                its_file_size,
                                &blob_length);

  if (psa_status != PSA_SUCCESS) {
    ret = psa_status;
    goto exit;
  }

  if (blob_length != its_file_size) {
    ret = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  }

#else
  if (data_length != 0U) {
    memcpy(its_file_buffer + sizeof(sli_its_file_meta_v2_t), ((uint8_t*)p_data), data_length);
  }
#endif

  status = nvm3_writeData(nvm3_defaultHandle,
                          nvm3_object_id,
                          its_file_buffer, its_file_size + sizeof(sli_its_file_meta_v2_t));

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    cache_set(nvm3_object_id);
  } else {
    ret = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  if (its_file_buffer != NULL) {
    // Clear and free key buffer before return.
    memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));
    mbedtls_free(its_file_buffer);
  }
  sli_its_release_mutex();
  return ret;
}

/**
 * \brief Retrieve the value associated with a provided uid
 *
 * \param[in] uid               The uid value
 * \param[in] data_offset       The starting offset of the data requested
 * \param[in] data_length       the amount of data requested (and the minimum allocated size of the `p_data` buffer)
 * \param[out] p_data           The buffer where the data will be placed upon successful completion
 * \param[out] p_data_length    The amount of data returned in the p_data buffer
 *
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided `uid` value was not found in the storage
 * \retval      PSA_ERROR_BUFFER_TOO_SMALL   The operation failed because the data associated with provided uid is larger than `data_size`
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_data`, `p_data_length`)
 *                                           is invalid. For example is `NULL` or references memory the caller cannot access.
 *                                           In addition, this can also happen if an invalid offset was provided.
 */
psa_status_t psa_its_get(psa_storage_uid_t uid,
                         uint32_t data_offset,
                         uint32_t data_length,
                         void *p_data,
                         size_t *p_data_length)
{
  psa_status_t ret = PSA_ERROR_CORRUPTION_DETECTED;

  if ((data_length != 0U) && (p_data_length == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (data_length != 0U) {
    // If the request amount of data is 0, allow invalid pointer of the output buffer.
    if ((p_data == NULL)
        || ((uint32_t)p_data < SRAM_BASE)
        || ((uint32_t)p_data > (SRAM_BASE + SRAM_SIZE - data_length))) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  sli_its_encrypted_blob_t *blob = NULL;
  size_t plaintext_length;
  psa_status_t psa_status;
#endif
  size_t its_file_data_size = 0u;
  Ecode_t status;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0;
  size_t its_file_offset = 0;

  sli_its_acquire_mutex();
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    ret = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }

  status = get_file_metadata(nvm3_object_id, &its_file_meta, &its_file_offset, &its_file_size);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    ret = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    ret = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
      && !object_lives_in_s(p_data, data_length)) {
    // The flag indicates that this data should not be read back to the non-secure domain
    ret = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Subtract IV and MAC from ITS file as the below checks concern the actual data size
  its_file_data_size = its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#else
  its_file_data_size = its_file_size;
#endif

  if (data_length != 0U) {
    if ((data_offset >= its_file_data_size) && (its_file_data_size != 0U)) {
      ret = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }

    if ((its_file_data_size == 0U) && (data_offset != 0U)) {
      ret = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }
  } else {
    // Allow the offset at the data size boundary if the requested amount of data is zero.
    if (data_offset > its_file_data_size) {
      ret = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }
  }

  if (data_length > (its_file_data_size - data_offset)) {
    *p_data_length = its_file_data_size - data_offset;
  } else {
    *p_data_length = data_length;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // its_file_size includes size of sli_its_encrypted_blob_t struct
  blob = (sli_its_encrypted_blob_t*)mbedtls_calloc(1, its_file_size);
  if (blob == NULL) {
    ret = PSA_ERROR_INSUFFICIENT_MEMORY;
    goto exit;
  }
  memset(blob, 0, its_file_size);

  status = nvm3_readPartialData(nvm3_defaultHandle,
                                nvm3_object_id,
                                blob,
                                its_file_offset,
                                its_file_size);
  if (status != ECODE_NVM3_OK) {
    ret = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

  // Decrypt and authenticate blob
  psa_status = decrypt_its_file(&its_file_meta,
                                blob,
                                its_file_size,
                                blob->data,
                                its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                                &plaintext_length);

  if (psa_status != PSA_SUCCESS) {
    ret = psa_status;
    goto exit;
  }

  if (plaintext_length != (its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    ret = PSA_ERROR_INVALID_SIGNATURE;
    goto exit;
  }

  // Verify that the requested UID is equal to the retrieved and authenticated UID
  if (uid != its_file_meta.uid) {
    ret = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (*p_data_length > 0) {
    memcpy(p_data, blob->data + data_offset, *p_data_length);
  }
  ret = PSA_SUCCESS;

  exit:
  if (blob != NULL) {
    memset(blob, 0, its_file_size);
    mbedtls_free(blob);
  }
  sli_its_release_mutex();
#else
  // If no encryption is used, just read out the data and write it directly to the output buffer
  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, p_data, its_file_offset + data_offset, *p_data_length);

  if (status != ECODE_NVM3_OK) {
    ret = PSA_ERROR_STORAGE_FAILURE;
  } else {
    ret = PSA_SUCCESS;
  }

  exit:
  sli_its_release_mutex();
#endif

  return ret;
}

/**
 * \brief Retrieve the metadata about the provided uid
 *
 * \param[in] uid           The uid value
 * \param[out] p_info       A pointer to the `psa_storage_info_t` struct that will be populated with the metadata
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided uid value was not found in the storage
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_info`)
 *                                           is invalid, for example is `NULL` or references memory the caller cannot access
 * \retval      PSA_ERROR_INVALID_SIGANTURE  The operation failed because authentication of the stored metadata failed.
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  if (p_info == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  Ecode_t status;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0;
  size_t its_file_offset = 0;

  sli_its_acquire_mutex();
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }

  status = get_file_metadata(nvm3_object_id, &its_file_meta, &its_file_offset, &its_file_size);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Authenticate the ITS file (both metadata and ciphertext) before returning the metadata.
  // Note that this can potentially induce a significant performance hit.
  psa_storage_uid_t authenticated_uid;
  psa_status = authenticate_its_file(nvm3_object_id, &authenticated_uid);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  if (authenticated_uid != uid) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
    goto exit;
  }
#endif

  p_info->flags = its_file_meta.flags;
  p_info->size = its_file_size;

  psa_status = PSA_SUCCESS;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Remove IV and MAC size from file size
  p_info->size = its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#endif
  exit:
  sli_its_release_mutex();
  return psa_status;
}

/**
 * \brief Remove the provided key and its associated data from the storage
 *
 * \param[in] uid   The uid value
 *
 * \return  A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided key value was not found in the storage
 * \retval      PSA_ERROR_NOT_PERMITTED      The operation failed because the provided key value was created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 */
psa_status_t psa_its_remove(psa_storage_uid_t uid)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  Ecode_t status;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0;
  size_t its_file_offset = 0;

  sli_its_acquire_mutex();
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }

  status = get_file_metadata(nvm3_object_id, &its_file_meta, &its_file_offset, &its_file_size);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
      || its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
      ) {
    psa_status = PSA_ERROR_NOT_PERMITTED;
    goto exit;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // If the UID already exists, authenticate the existing value and make sure the stored UID is the same.
  psa_storage_uid_t authenticated_uid;
  psa_status = authenticate_its_file(nvm3_object_id, &authenticated_uid);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  if (authenticated_uid != uid) {
    psa_status = PSA_ERROR_NOT_PERMITTED;
    goto exit;
  }
#endif

  status = nvm3_deleteObject(nvm3_defaultHandle, nvm3_object_id);

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    if (previous_lookup.set && previous_lookup.uid == uid) {
      previous_lookup.set = false;
    }
    cache_clear(nvm3_object_id);

    psa_status = PSA_SUCCESS;
  } else {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  sli_its_release_mutex();
  return psa_status;
}

// -------------------------------------
// Silicon Labs extensions
static psa_storage_uid_t psa_its_identifier_of_slot(mbedtls_svc_key_id_t key)
{
#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
  // Encode the owner in the upper 32 bits. This means that if
  // owner values are nonzero (as they are on a PSA platform),
  // no key file will ever have a value less than 0x100000000, so
  // the whole range 0..0xffffffff is available for non-key files.
  uint32_t unsigned_owner_id = MBEDTLS_SVC_KEY_ID_GET_OWNER_ID(key);
  return ((uint64_t)unsigned_owner_id << 32) | MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key);
#else
  // Use the key id directly as a file name.
  // psa_is_key_id_valid() in psa_crypto_slot_management.c
  // is responsible for ensuring that key identifiers do not have a
  // value that is reserved for non-key files.
  return key;
#endif
}

psa_status_t sli_psa_its_change_key_id(mbedtls_svc_key_id_t old_id,
                                       mbedtls_svc_key_id_t new_id)
{
  psa_storage_uid_t old_uid = psa_its_identifier_of_slot(old_id);
  psa_storage_uid_t new_uid = psa_its_identifier_of_slot(new_id);
  Ecode_t status;
  uint32_t obj_type;
  size_t its_file_size = 0;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  int8_t *its_file_buffer = NULL;
  sli_its_file_meta_v2_t* metadata = NULL;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  sli_its_encrypted_blob_t *blob = NULL;
  size_t plaintext_length;
  size_t blob_length;
  psa_status_t encrypt_status;
  psa_status_t decrypt_status;
#endif
  sli_its_acquire_mutex();

  // Check whether the key to migrate exists on disk
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(old_uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    psa_status = PSA_ERROR_DOES_NOT_EXIST;
    goto exit;
  }

  // Get total length to allocate
  status = nvm3_getObjectInfo(nvm3_defaultHandle,
                              nvm3_object_id,
                              &obj_type,
                              &its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

  // Allocate temporary buffer and cast it to the metadata format
  its_file_buffer = mbedtls_calloc(1, its_file_size);
  if (its_file_buffer == NULL) {
    psa_status = PSA_ERROR_INSUFFICIENT_MEMORY;
    goto exit;
  }
  metadata = (sli_its_file_meta_v2_t*) its_file_buffer;

  // Read contents of pre-existing key into the temporary buffer
  status = nvm3_readData(nvm3_defaultHandle,
                         nvm3_object_id,
                         its_file_buffer,
                         its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Decrypt and authenticate blob
  blob = (sli_its_encrypted_blob_t*)(its_file_buffer + sizeof(sli_its_file_meta_v2_t));
  decrypt_status = decrypt_its_file(metadata,
                                    blob,
                                    its_file_size - sizeof(sli_its_file_meta_v2_t),
                                    blob->data,
                                    its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                                    &plaintext_length);

  if (decrypt_status != PSA_SUCCESS) {
    psa_status = decrypt_status;
    goto exit;
  }

  if (plaintext_length != (its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
    goto exit;
  }
#endif

  // Swap out the old UID for the new one
#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)
  if (metadata->magic == SLI_PSA_ITS_META_MAGIC_V1) {
    // Recast as v1 metadata
    sl_its_file_meta_v1_t* metadata_v1 = (sl_its_file_meta_v1_t*) its_file_buffer;
    if (metadata_v1->uid != old_uid) {
      psa_status = PSA_ERROR_CORRUPTION_DETECTED;
      goto exit;
    }
    metadata_v1->uid = new_uid;
  } else
#endif
  if (metadata->magic == SLI_PSA_ITS_META_MAGIC_V2) {
    if (metadata->uid != old_uid) {
      psa_status = PSA_ERROR_CORRUPTION_DETECTED;
      goto exit;
    }
    metadata->uid = new_uid;
  } else {
    psa_status = PSA_ERROR_CORRUPTION_DETECTED;
    goto exit;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Encrypt and authenticate the modified data data
  encrypt_status = encrypt_its_file(metadata,
                                    blob->data,
                                    plaintext_length,
                                    blob,
                                    its_file_size - sizeof(sli_its_file_meta_v2_t),
                                    &blob_length);

  if (encrypt_status != PSA_SUCCESS) {
    psa_status = encrypt_status;
    goto exit;
  }

  if (blob_length != (its_file_size - sizeof(sli_its_file_meta_v2_t))) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  }
#endif

  // Overwrite the NVM3 token with the changed buffer
  status = nvm3_writeData(nvm3_defaultHandle,
                          nvm3_object_id,
                          its_file_buffer,
                          its_file_size);
  if (status == ECODE_NVM3_OK) {
    // Update last lookup and report success
    if (previous_lookup.set) {
      if (previous_lookup.uid == old_uid) {
        previous_lookup.uid = new_uid;
      }
    }
    psa_status = PSA_SUCCESS;
  } else {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  if (its_file_buffer != NULL) {
    // Clear and free key buffer before return.
    memset(its_file_buffer, 0, its_file_size);
    mbedtls_free(its_file_buffer);
  }
  sli_its_release_mutex();
  return psa_status;
}

/**
 * \brief Check if the ITS encryption is enabled
 */
psa_status_t sli_psa_its_encrypted(void)
{
  #if defined(SLI_PSA_ITS_ENCRYPTED)
  return PSA_SUCCESS;
  #else
  return PSA_ERROR_NOT_SUPPORTED;
  #endif
}

#if defined(SLI_PSA_ITS_ENCRYPTED) && !defined(SEMAILBOX_PRESENT)
/**
 * \brief Set the root key to be used when deriving session keys for ITS encryption.
 *
 * \param[in] root_key        Buffer containing the root key.
 * \param[in] root_key_size   Size of the root key in bytes. Must be 32 (256 bits).
 *
 * \return  A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The key was successfully set.
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The root key was NULL or had an invalid size.
 * \retval      PSA_ERROR_ALREADY_EXISTS     The root key has already been initialized.
 */
psa_status_t sli_psa_its_set_root_key(uint8_t *root_key, size_t root_key_size)
{
  // Check that arguments are valid
  if (root_key == NULL || root_key_size != sizeof(g_root_key.data)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check that the root key has not already been set
  // (This is possibly too restrictive. For TrustZone usage this can be enforced by
  // not exposing the function to NS instead.)
  if (g_root_key.initialized) {
    return PSA_ERROR_ALREADY_EXISTS;
  }

  // Store the provided root key and mark it as initialized
  memcpy(g_root_key.data, root_key, sizeof(g_root_key.data));
  g_root_key.initialized = true;

  return PSA_SUCCESS;
}
#endif // defined(SLI_PSA_ITS_ENCRYPTED) && !defined(SEMAILBOX_PRESENT)

#else // (!SL_PSA_ITS_SUPPORT_V3_DRIVER)

// -------------------------------------
// Defines
#define SLI_PSA_ITS_V3_DRIVER               (0x3A)
#define SLI_PSA_ITS_V2_DRIVER               (0x74)
#define SLI_PSA_ITS_NOT_CHECKED             (0xE8)
#define SLI_PSA_ITS_V2_DRIVER_FLAG_NVM3_ID  (SLI_PSA_ITS_NVM3_RANGE_START - 1)
#define SLI_PSA_ITS_NVM3_INVALID_KEY        (0)
#define SLI_PSA_ITS_NVM3_UNKNOWN_KEY        (1)

#if SL_PSA_ITS_MAX_FILES > SLI_PSA_ITS_NVM3_RANGE_SIZE
#error "Trying to store more ITS files then our NVM3 range allows for"
#endif

#define SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE 16

// Internal error codes local to this compile unit
#define SLI_PSA_ITS_ECODE_NO_VALID_HEADER (ECODE_EMDRV_NVM3_BASE - 1)
#define SLI_PSA_ITS_ECODE_NEEDS_UPGRADE   (ECODE_EMDRV_NVM3_BASE - 2)

// SLI_STATIC_TESTABLE is used to expose otherwise-static variables during internal testing.
#if !defined(SLI_STATIC_TESTABLE)
#define SLI_STATIC_TESTABLE static
#endif

// -------------------------------------
// Local global static variables

SLI_STATIC_TESTABLE bool nvm3_uid_set_cache_initialized = false;
SLI_STATIC_TESTABLE uint32_t nvm3_uid_set_cache[(SL_PSA_ITS_MAX_FILES + 31) / 32] = { 0 };
SLI_STATIC_TESTABLE uint32_t nvm3_uid_tomb_cache[(SL_PSA_ITS_MAX_FILES + 31) / 32] = { 0 };
#if SL_PSA_ITS_SUPPORT_V2_DRIVER
SLI_STATIC_TESTABLE uint32_t its_driver_version = SLI_PSA_ITS_NOT_CHECKED;
#endif // SL_PSA_ITS_SUPPORT_V2_DRIVER

#if defined(SLI_PSA_ITS_ENCRYPTED)
// The root key is an AES-256 key, and is therefore 32 bytes.
#define ROOT_KEY_SIZE     (32)
// The session key is derived from CMAC, which means it is equal to the AES block size, i.e. 16 bytes
#define SESSION_KEY_SIZE  (16)

#if !defined(SEMAILBOX_PRESENT)
typedef struct {
  bool initialized;
  uint8_t data[ROOT_KEY_SIZE];
} root_key_t;

static root_key_t g_root_key = {
  .initialized = false,
  .data = { 0 },
};
#endif // !defined(SEMAILBOX_PRESENT)

typedef struct {
  bool active;
  psa_storage_uid_t uid;
  uint8_t data[SESSION_KEY_SIZE];
} session_key_t;

static session_key_t g_cached_session_key = {
  .active = false,
  .uid = 0,
  .data = { 0 },
};
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Structs

#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)
typedef struct {
  uint32_t magic;
  psa_storage_uid_t uid;
  psa_storage_create_flags_t flags;
} sl_its_file_meta_v1_t;
#endif // defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)

// -------------------------------------
// Local function prototypes

static psa_status_t find_nvm3_id(psa_storage_uid_t uid,
                                 bool find_empty_slot,
                                 sli_its_file_meta_v2_t* its_file_meta,
                                 size_t* its_file_offset,
                                 size_t* its_file_size,
                                 nvm3_ObjectKey_t * output_nvm3_id);
static nvm3_ObjectKey_t derive_nvm3_id(psa_storage_uid_t uid);

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
static inline bool object_lives_in_s(const void *object, size_t object_size);
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
static psa_status_t derive_session_key(uint8_t *iv,
                                       size_t iv_size,
                                       uint8_t *session_key,
                                       size_t session_key_size);

static psa_status_t sli_decrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                         sli_its_encrypted_blob_t *blob,
                                         size_t blob_size,
                                         uint8_t *plaintext,
                                         size_t plaintext_size,
                                         size_t *plaintext_length);

static psa_status_t authenticate_its_file(nvm3_ObjectKey_t nvm3_object_id,
                                          psa_storage_uid_t *authenticated_uid);
#endif

#if SL_PSA_ITS_SUPPORT_V2_DRIVER
static psa_status_t psa_its_get_legacy(nvm3_ObjectKey_t nvm3_object_id,
                                       sli_its_file_meta_v2_t* its_file_meta,
                                       size_t its_file_size,
                                       size_t its_file_offset, void *p_data);
static psa_status_t detect_legacy_versions();
static psa_status_t upgrade_all_keys();

#if defined (SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)
psa_status_t psa_its_set_v1(psa_storage_uid_t uid,
                            uint32_t data_length,
                            const void *p_data,
                            psa_storage_create_flags_t create_flags);
#endif // SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL
#endif // SL_PSA_ITS_SUPPORT_V2_DRIVER

// -------------------------------------
// Local function definitions
static inline uint32_t get_index(nvm3_ObjectKey_t key)
{
  return (key - (SLI_PSA_ITS_NVM3_RANGE_START)) / 32;
}

static inline uint32_t get_offset(nvm3_ObjectKey_t key)
{
  return (key - (SLI_PSA_ITS_NVM3_RANGE_START)) % 32;
}

static inline void set_cache(nvm3_ObjectKey_t key)
{
  nvm3_uid_set_cache[get_index(key)] |= (1 << get_offset(key));
  nvm3_uid_tomb_cache[get_index(key)] &= ~(1 << get_offset(key));
}

static inline void set_tomb(nvm3_ObjectKey_t key)
{
  nvm3_uid_tomb_cache[get_index(key)] |= (1 << get_offset(key));

  uint32_t cache_not_empty = 0;
  for ( size_t i = 0; i < (((SL_PSA_ITS_MAX_FILES) +31) / 32); i++ ) {
    cache_not_empty += nvm3_uid_set_cache[i];
  }
  if (cache_not_empty == 0) {
    for ( size_t i = 0; i < (((SL_PSA_ITS_MAX_FILES) +31) / 32); i++ ) {
      nvm3_uid_tomb_cache[i] = 0;
    }
  }
}

#if SL_PSA_ITS_SUPPORT_V2_DRIVER
static inline psa_status_t write_driver_v3()
{
  uint8_t driver_verison = SLI_PSA_ITS_V3_DRIVER;
  Ecode_t status;
  status = nvm3_writeData(nvm3_defaultHandle,
                          SLI_PSA_ITS_V2_DRIVER_FLAG_NVM3_ID,
                          &driver_verison, sizeof(uint8_t));
  if ( status != ECODE_NVM3_OK ) {
    return PSA_ERROR_STORAGE_FAILURE;
  }
  return PSA_SUCCESS;
}
#endif

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
// If an object of given size is fully encapsulated in a region of
// secure domain the function returns true.
static inline bool object_lives_in_s(const void *object, size_t object_size)
{
  cmse_address_info_t cmse_flags;

  for (size_t i = 0u; i < object_size; i++) {
    cmse_flags = cmse_TTA((uint32_t *)object + i);
    if (!cmse_flags.flags.secure) {
      return false;
    }
  }

  return true;
}
#endif

static inline void clear_cache(nvm3_ObjectKey_t key)
{
  nvm3_uid_set_cache[get_index(key)] ^= (1 << get_offset(key));
}

static inline bool lookup_cache(nvm3_ObjectKey_t key)
{
  return (bool)((nvm3_uid_set_cache[get_index(key)] >> get_offset(key)) & 0x1);
}

static inline bool lookup_tomb(nvm3_ObjectKey_t key)
{
  return (bool)((nvm3_uid_tomb_cache[get_index(key)] >> get_offset(key)) & 0x1);
}

static inline nvm3_ObjectKey_t increment_obj_id(nvm3_ObjectKey_t id)
{
  return SLI_PSA_ITS_NVM3_RANGE_START + ((id - SLI_PSA_ITS_NVM3_RANGE_START + 1)
                                         % SL_PSA_ITS_MAX_FILES);
}
static inline nvm3_ObjectKey_t prng(psa_storage_uid_t uid)
{
// Squash uid down to a 32 bit word
  nvm3_ObjectKey_t uid_32 = uid & 0xFFFFFFFF;
  nvm3_ObjectKey_t xored_32 = (uid >> 32) ^ uid_32;
  nvm3_ObjectKey_t temp;
// Accumulate all "entropy" towards the LSB, since that is where we need it
  for ( size_t i = 1; i < 4; i++ ) {
    temp = xored_32 ^ (xored_32 >> (8 * i));
    if ((temp & 0x3) != 0 ) {
      temp = temp << 2;
    }
    uid_32 = (uid_32 + temp);
  }
  return uid_32;
}

static inline nvm3_ObjectKey_t derive_nvm3_id(psa_storage_uid_t uid)
{
  return SLI_PSA_ITS_NVM3_RANGE_START + (prng(uid) % (SL_PSA_ITS_MAX_FILES));
}

static void init_cache(void)
{
  size_t num_keys_referenced_by_nvm3;
  nvm3_ObjectKey_t keys_referenced_by_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE] = { 0 };
  size_t num_del_keys_from_nvm3;
  nvm3_ObjectKey_t deleted_keys_from_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE] = { 0 };
  for (nvm3_ObjectKey_t range_start = SLI_PSA_ITS_NVM3_RANGE_START;
       range_start < SLI_PSA_ITS_NVM3_RANGE_END;
       range_start += SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE) {
    nvm3_ObjectKey_t range_end = range_start + SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE;
    if (range_end > SLI_PSA_ITS_NVM3_RANGE_END) {
      range_end = SLI_PSA_ITS_NVM3_RANGE_END;
    }

    num_keys_referenced_by_nvm3 = nvm3_enumObjects(nvm3_defaultHandle,
                                                   keys_referenced_by_nvm3,
                                                   sizeof(keys_referenced_by_nvm3) / sizeof(nvm3_ObjectKey_t),
                                                   range_start,
                                                   range_end - 1);

    for (size_t i = 0; i < num_keys_referenced_by_nvm3; i++) {
      set_cache(keys_referenced_by_nvm3[i]);
    }
    num_del_keys_from_nvm3 = nvm3_enumDeletedObjects(nvm3_defaultHandle,
                                                     deleted_keys_from_nvm3,
                                                     sizeof(deleted_keys_from_nvm3) / sizeof(nvm3_ObjectKey_t),
                                                     range_start,
                                                     range_end - 1);
    for (size_t i = 0; i < num_del_keys_from_nvm3; i++) {
      set_tomb(deleted_keys_from_nvm3[i]);
    }
  }
  nvm3_uid_set_cache_initialized = true;
}

// Read the file metadata for a specific NVM3 ID
static Ecode_t get_file_metadata(nvm3_ObjectKey_t key,
                                 sli_its_file_meta_v2_t* metadata,
                                 size_t* its_file_offset,
                                 size_t* its_file_size)
{
  // Initialize output variables to safe default
  if (its_file_offset != NULL) {
    *its_file_offset = 0;
  }
  if (its_file_size != NULL) {
    *its_file_size = 0;
  }

  Ecode_t status = nvm3_readPartialData(nvm3_defaultHandle,
                                        key,
                                        metadata,
                                        0,
                                        sizeof(sli_its_file_meta_v2_t));
  if (status != ECODE_NVM3_OK) {
    return status;
  }

#if defined (SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)
  // Re-read in v1 header format and translate to the latest structure version
  if (metadata->magic == SLI_PSA_ITS_META_MAGIC_V1) {
    sl_its_file_meta_v1_t key_meta_v1 = { 0 };
    status = nvm3_readPartialData(nvm3_defaultHandle,
                                  key,
                                  &key_meta_v1,
                                  0,
                                  sizeof(sl_its_file_meta_v1_t));

    if (status != ECODE_NVM3_OK) {
      return status;
    }

    metadata->flags = key_meta_v1.flags;
    metadata->uid = key_meta_v1.uid;
    metadata->magic = SLI_PSA_ITS_META_MAGIC_V2;

    if (its_file_offset != NULL) {
      *its_file_offset = sizeof(sl_its_file_meta_v1_t);
    }

    status = SLI_PSA_ITS_ECODE_NEEDS_UPGRADE;
  } else
#endif
  {
    if (its_file_offset != NULL) {
      *its_file_offset = sizeof(sli_its_file_meta_v2_t);
    }
  }

  if (metadata->magic != SLI_PSA_ITS_META_MAGIC_V2) {
    // No valid header found in this object
    return SLI_PSA_ITS_ECODE_NO_VALID_HEADER;
  }

  if (its_file_offset != NULL && its_file_size != NULL) {
    // Calculate the ITS file size if requested
    uint32_t obj_type;
    Ecode_t info_status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                             key,
                                             &obj_type,
                                             its_file_size);
    if (info_status != ECODE_NVM3_OK) {
      return info_status;
    }

    *its_file_size = *its_file_size - *its_file_offset;
  }

  return status;
}

#if SL_PSA_ITS_SUPPORT_V2_DRIVER
static psa_status_t psa_its_get_legacy(nvm3_ObjectKey_t nvm3_object_id,
                                       sli_its_file_meta_v2_t* its_file_meta,
                                       size_t its_file_size,
                                       size_t its_file_offset,
                                       void *p_data)
{
  Ecode_t status;
  if (its_file_size == 0) {
    if (its_file_meta != NULL) {
      return PSA_ERROR_DATA_INVALID;
    }
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sli_its_encrypted_blob_t *blob = NULL;
  size_t plaintext_length;

  // its_file_size includes size of sli_its_encrypted_blob_t struct
  blob = (sli_its_encrypted_blob_t*)mbedtls_calloc(1, its_file_size);
  if (blob == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(blob, 0, its_file_size);

  status = nvm3_readPartialData(nvm3_defaultHandle,
                                nvm3_object_id,
                                blob,
                                its_file_offset,
                                its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto cleanup;
  }

  // Decrypt and authenticate blob
  psa_status = sli_decrypt_its_file(its_file_meta,
                                    blob,
                                    its_file_size,
                                    blob->data,
                                    its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                                    &plaintext_length);

  if (psa_status != PSA_SUCCESS) {
    goto cleanup;
  }

  if (plaintext_length != (its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
    goto cleanup;
  }

  if (its_file_size + its_file_offset > 0) {
    memcpy(p_data, blob->data, its_file_size + its_file_offset);
  }
  psa_status = PSA_SUCCESS;

  cleanup:
  if (blob != NULL) {
    memset(blob, 0, its_file_size);
    mbedtls_free(blob);
  }
  return psa_status;
#else
  // If no encryption is used, just read out the data and write it directly to the output buffer
  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, p_data,
                                its_file_offset, its_file_size);

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  } else {
    return PSA_SUCCESS;
  }
#endif
}

// Function sets detect the presence of v1 and v2 its driver. If there is something
// stored in v1/v2 driver range, it sets its_driver_version to SLI_PSA_ITS_V2_DRIVER.
static psa_status_t detect_legacy_versions()
{
  uint8_t driver_verison = 0;
  Ecode_t status;
  status = nvm3_readData(nvm3_defaultHandle, SLI_PSA_ITS_V2_DRIVER_FLAG_NVM3_ID,
                         &driver_verison, sizeof(uint8_t));
  if ((status != ECODE_NVM3_OK) && (status != ECODE_NVM3_ERR_KEY_NOT_FOUND)) {
    return PSA_ERROR_STORAGE_FAILURE;
  }
  if (driver_verison == SLI_PSA_ITS_V3_DRIVER) {
    its_driver_version = SLI_PSA_ITS_V3_DRIVER;
    return PSA_SUCCESS;
  }

  size_t num_keys_referenced_by_nvm3;

  nvm3_ObjectKey_t keys_referenced_by_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE] = {
    0
  };

  for ( nvm3_ObjectKey_t range_start = SLI_PSA_ITS_NVM3_RANGE_START_V2_DRIVER;
        range_start < SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER;
        range_start += SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE ) {
    nvm3_ObjectKey_t range_end =
      range_start + SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE;
    if (range_end > SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER ) {
      range_end = SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER;
    }

    num_keys_referenced_by_nvm3 = nvm3_enumObjects(nvm3_defaultHandle,
                                                   keys_referenced_by_nvm3,
                                                   sizeof(keys_referenced_by_nvm3)
                                                   / sizeof(nvm3_ObjectKey_t),
                                                   range_start,
                                                   range_end - 1);

    if (num_keys_referenced_by_nvm3 > 0) {
      sli_its_file_meta_v2_t its_file_meta = { 0 };
      size_t its_file_size = 0;
      size_t its_file_offset = 0;
      status = get_file_metadata(keys_referenced_by_nvm3[0],
                                 &its_file_meta, &its_file_offset,
                                 &its_file_size);
      if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
        return PSA_ERROR_DOES_NOT_EXIST;
      }
      if (status != ECODE_NVM3_OK
          && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
        return PSA_ERROR_STORAGE_FAILURE;
      }

      if ((its_file_meta.magic == SLI_PSA_ITS_META_MAGIC_V1)
          || (its_file_meta.magic == SLI_PSA_ITS_META_MAGIC_V2)) {
        its_driver_version = SLI_PSA_ITS_V2_DRIVER;
        return PSA_SUCCESS;
      } else {
        return PSA_ERROR_STORAGE_FAILURE;
      }
    }
  }
  its_driver_version = SLI_PSA_ITS_V3_DRIVER;
  return PSA_SUCCESS;
}

static psa_status_t upgrade_all_keys()
{
  size_t num_keys_referenced_by_nvm3;
  nvm3_ObjectKey_t keys_referenced_by_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE] = {
    0
  };
  Ecode_t status;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;

  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_data_size;
  uint8_t * its_file_buffer = NULL;

  size_t its_file_size = 0;
  size_t its_file_offset;

  for ( nvm3_ObjectKey_t range_start = SLI_PSA_ITS_NVM3_RANGE_START_V2_DRIVER;
        range_start < SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER;
        range_start += SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE ) {
    nvm3_ObjectKey_t range_end =
      range_start + SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE;
    if (range_end >= SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER ) {
      range_end = SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER;
    }

    num_keys_referenced_by_nvm3 = nvm3_enumObjects(nvm3_defaultHandle,
                                                   keys_referenced_by_nvm3,
                                                   sizeof(keys_referenced_by_nvm3)
                                                   /
                                                   sizeof(nvm3_ObjectKey_t),
                                                   range_start,
                                                   range_end - 1);
    for ( size_t i = 0; i < num_keys_referenced_by_nvm3; i++ ) {
      its_file_size = 0;
      its_file_offset = 0;
      status = get_file_metadata(keys_referenced_by_nvm3[i],
                                 &(its_file_meta), &its_file_offset,
                                 &its_file_size);
      if ( status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
        return PSA_ERROR_DOES_NOT_EXIST;
      }
      if ( status != ECODE_NVM3_OK
           && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
        return PSA_ERROR_STORAGE_FAILURE;
      }

#if defined(SLI_PSA_ITS_ENCRYPTED)
      // Subtract IV and MAC from ITS file as the below checks concern the actual data size
      its_file_data_size = its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#else
      its_file_data_size = its_file_size;
#endif

      if ((its_file_meta.magic != SLI_PSA_ITS_META_MAGIC_V2)
          && (its_file_meta.magic != SLI_PSA_ITS_META_MAGIC_V1)) {
        return PSA_ERROR_STORAGE_FAILURE;
      }
      its_file_buffer = mbedtls_calloc(1, its_file_size + sizeof(sli_its_file_meta_v2_t));
      if (its_file_buffer == NULL) {
        return PSA_ERROR_INSUFFICIENT_MEMORY;
      }
#if defined(SLI_PSA_ITS_ENCRYPTED)
      psa_status = psa_its_get_legacy(keys_referenced_by_nvm3[i],
                                      &(its_file_meta),
                                      its_file_size,
                                      its_file_offset,
                                      its_file_buffer);
#else
      psa_status = psa_its_get_legacy(keys_referenced_by_nvm3[i],
                                      NULL,
                                      its_file_size,
                                      its_file_offset,
                                      its_file_buffer);
#endif
      if (psa_status != PSA_SUCCESS) {
        psa_status = PSA_ERROR_STORAGE_FAILURE;
        goto exit;
      }

#if defined (SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)
      if (its_file_meta.magic == SLI_PSA_ITS_META_MAGIC_V1) {
        psa_status = psa_its_set_v1(its_file_meta.uid, its_file_data_size,
                                    its_file_buffer, its_file_meta.flags);
      } else if (its_file_meta.magic == SLI_PSA_ITS_META_MAGIC_V2)
#endif
      {
        psa_status = psa_its_set(its_file_meta.uid, its_file_data_size,
                                 its_file_buffer, its_file_meta.flags);
      }

      if ((psa_status != PSA_SUCCESS) && (psa_status
                                          != PSA_ERROR_NOT_PERMITTED)) {
        goto exit;
      }
      status = nvm3_deleteObject(nvm3_defaultHandle,
                                 keys_referenced_by_nvm3[i]);

      if ( status != ECODE_NVM3_OK ) {
        psa_status = PSA_ERROR_STORAGE_FAILURE;
        goto exit;
      }
      memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));
      mbedtls_free(its_file_buffer);
    }
  }
  return PSA_SUCCESS;

  exit:
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));
  mbedtls_free(its_file_buffer);
  return psa_status;
}

#if defined (SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL)
psa_status_t psa_its_set_v1(psa_storage_uid_t uid,
                            uint32_t data_length,
                            const void *p_data,
                            psa_storage_create_flags_t create_flags)
{
  if ((data_length != 0U) && (p_data == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (create_flags != PSA_STORAGE_FLAG_WRITE_ONCE
      && create_flags != PSA_STORAGE_FLAG_NONE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
      && create_flags != PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
      ) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  if ((create_flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE)
      && (!object_lives_in_s(p_data, data_length))) {
    // The flag indicates that this data should not be set by the non-secure domain
    return PSA_ERROR_INVALID_ARGUMENT;
  }
#endif

  Ecode_t status;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sl_its_file_meta_v1_t* its_file_meta;
  nvm3_ObjectKey_t nvm3_object_id = 0;
  size_t its_file_size = data_length;

  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size + sizeof(sl_its_file_meta_v1_t));
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(its_file_buffer, 0, its_file_size + sizeof(sl_its_file_meta_v1_t));

  its_file_meta = (sl_its_file_meta_v1_t *)its_file_buffer;
  sli_its_file_meta_v2_t its_file_meta_v2;

  sli_its_acquire_mutex();
  psa_status = find_nvm3_id(uid, true, &its_file_meta_v2, NULL, NULL,
                            &nvm3_object_id);
  if (psa_status != PSA_SUCCESS) {
    if (psa_status == PSA_ERROR_DOES_NOT_EXIST) {
      psa_status = PSA_ERROR_INSUFFICIENT_STORAGE;
    }
    goto exit;
  }

  its_file_meta->magic = SLI_PSA_ITS_META_MAGIC_V1;
  its_file_meta->uid = uid;
  its_file_meta->flags = create_flags;

  if (data_length != 0U) {
    memcpy(its_file_buffer + sizeof(sl_its_file_meta_v1_t), ((uint8_t*)
                                                             p_data), data_length);
  }

  status = nvm3_writeData(nvm3_defaultHandle,
                          nvm3_object_id,
                          its_file_buffer, its_file_size + sizeof
                          (sl_its_file_meta_v1_t));

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    set_cache(nvm3_object_id);
  } else {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size + sizeof(sl_its_file_meta_v1_t));
  mbedtls_free(its_file_buffer);
  sli_its_release_mutex();
  return psa_status;
}
#endif //SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL
#endif //SL_PSA_ITS_SUPPORT_V1_DRIVER

/**
 * \brief Search through NVM3 for correct uid
 *
 * \param[in] uid               UID under what we want to store the data
 * \param[in] find_empty_slot   Indicates whether we want to find existing data or empty space for storing new.
 * \param[out] its_file_meta    Meta information of ITS file
 * \param[out] its_file_offset  Offset of ITS file
 * \param[out] its_file_size    Size of ITS file
 * \param[out] output_nvm3_id   NVM3 ID corresponding to UID.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST         The data with this UID are not stored in NVM3
 * \retval      PSA_ERROR_NOT_PERMITTED          The requested operation is not permitted
 */
static psa_status_t find_nvm3_id(psa_storage_uid_t uid,
                                 bool find_empty_slot,
                                 sli_its_file_meta_v2_t* its_file_meta,
                                 size_t* its_file_offset,
                                 size_t* its_file_size,
                                 nvm3_ObjectKey_t * output_nvm3_id)
{
  Ecode_t status;
  nvm3_ObjectKey_t tmp_id = 0;
  nvm3_ObjectKey_t nvm3_object_id = 0;
  nvm3_object_id = derive_nvm3_id(uid);

  if (nvm3_uid_set_cache_initialized == false) {
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY) \
    // With SKL the NVM3 instance must be initialized by the NS app. We therefore check that
    // it has been opened (which is done on init) rather than actually doing the init.
    if (!nvm3_defaultHandle->hasBeenOpened) {
#else
    if (nvm3_initDefault() != ECODE_NVM3_OK) {
#endif
      return PSA_ERROR_STORAGE_FAILURE;
    }

#if SL_PSA_ITS_SUPPORT_V2_DRIVER
    if ( its_driver_version == SLI_PSA_ITS_NOT_CHECKED ) {
      if ( detect_legacy_versions() != PSA_SUCCESS ) {
        return PSA_ERROR_STORAGE_FAILURE;
      }
      if ( its_driver_version == SLI_PSA_ITS_V2_DRIVER ) {
        psa_status_t psa_status = upgrade_all_keys();
        if ( psa_status != PSA_SUCCESS ) {
          return psa_status;
        }
        psa_status = write_driver_v3();
        if ( psa_status != PSA_SUCCESS ) {
          return psa_status;
        }
      } else {
        init_cache();
      }
    } else {
      init_cache();
    }
#else
    init_cache();
#endif
  }

  for (size_t i = 0; i < SL_PSA_ITS_MAX_FILES; ++i ) {
    if (!lookup_cache(nvm3_object_id)) {
      // dont exist
      if (lookup_tomb(nvm3_object_id)) {
        // tombstone
        if (tmp_id == 0 ) {
          // mark first empty space
          tmp_id = nvm3_object_id;
        }
        nvm3_object_id = increment_obj_id(nvm3_object_id);
        continue;
      } else {
        // empty space
        if (find_empty_slot) {
          if (tmp_id != 0) {
            *output_nvm3_id = tmp_id;
            return PSA_SUCCESS;
          }
          *output_nvm3_id = nvm3_object_id;
          return PSA_SUCCESS;
        } else {
          return PSA_ERROR_DOES_NOT_EXIST;
        }
      }
    }
    status = get_file_metadata(nvm3_object_id, its_file_meta, its_file_offset,
                               its_file_size);

    if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER
        || status == ECODE_NVM3_ERR_READ_DATA_SIZE) {
      // we don't expect any other data in our range then PSA ITS files.
      // delete the file if the magic doesn't match or the object on disk
      // is too small to even have full metadata.
      status = nvm3_deleteObject(nvm3_defaultHandle, nvm3_object_id);
      if (status != ECODE_NVM3_OK) {
        return PSA_ERROR_DOES_NOT_EXIST;
      }
    }

    if (status != ECODE_NVM3_OK
        && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
      return PSA_ERROR_STORAGE_FAILURE;
    }

    if (its_file_meta->uid != uid) {
      nvm3_object_id = increment_obj_id(nvm3_object_id);
    } else {
      if (find_empty_slot) {
        if (its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
            || its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
            ) {
          return PSA_ERROR_NOT_PERMITTED;
        }
      }
#if defined(SLI_PSA_ITS_ENCRYPTED)
      // If the UID already exists, authenticate the existing value and make sure the stored UID is the same.
      // Note that this can potentially induce a significant performance hit.
      psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
      psa_storage_uid_t authenticated_uid = 0;
      psa_status = authenticate_its_file(nvm3_object_id, &authenticated_uid);
      if (psa_status != PSA_SUCCESS) {
        return psa_status;
      }

      if (authenticated_uid != uid) {
        return PSA_ERROR_INVALID_SIGNATURE;
      }
#endif
      *output_nvm3_id = nvm3_object_id;
      return PSA_SUCCESS;
    }
  }
  if (find_empty_slot) {
    if (tmp_id != 0) {
      *output_nvm3_id = tmp_id;
      return PSA_SUCCESS;
    }
  }
  return PSA_ERROR_DOES_NOT_EXIST;
}

#if defined(SLI_PSA_ITS_ENCRYPTED)
static inline void cache_session_key(uint8_t *session_key, psa_storage_uid_t uid)
{
  // Cache the session key
  memcpy(g_cached_session_key.data, session_key, sizeof(g_cached_session_key.data));
  g_cached_session_key.uid = uid;
  g_cached_session_key.active = true;
}

/**
 * \brief Derive a session key for ITS file encryption from the initialized root key and provided IV.
 *
 * \param[in] iv                Pointer to array containing the initialization vector to be used in the key derivation.
 * \param[in] iv_size           Size of the IV buffer in bytes. Must be 12 bytes (AES-GCM IV size).
 * \param[out] session_key      Pointer to array where derived session key shall be stored.
 * \param[out] session_key_size Size of the derived session key output array. Must be at least 32 bytes (AES-256 key size).
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because iv or session_key is NULL, or their sizes are incorrect.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t derive_session_key(uint8_t *iv, size_t iv_size, uint8_t *session_key, size_t session_key_size)
{
  if (iv == NULL
      || iv_size != AES_GCM_IV_SIZE
      || session_key == NULL
      || session_key_size < SESSION_KEY_SIZE) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;

#if defined(SEMAILBOX_PRESENT)
  // For HSE devices, use the builtin TrustZone Root Key
  psa_set_key_id(&attributes, SL_SE_BUILTIN_KEY_TRUSTZONE_ID);

  psa_key_lifetime_t reported_lifetime;
  psa_drv_slot_number_t reported_slot;
  status = mbedtls_psa_platform_get_builtin_key(psa_get_key_id(&attributes),
                                                &reported_lifetime,
                                                &reported_slot);

  if (status != PSA_SUCCESS) {
    return status;
  }

  psa_set_key_lifetime(&attributes, reported_lifetime);

  uint8_t key_buffer[sizeof(sli_se_opaque_key_context_header_t)];
  size_t key_buffer_size;
  status = sli_se_opaque_get_builtin_key(reported_slot,
                                         &attributes,
                                         key_buffer,
                                         sizeof(key_buffer),
                                         &key_buffer_size);
  if (status != PSA_SUCCESS) {
    return status;
  }
#else // defined(SEMAILBOX_PRESENT)
  // For VSE devices, use the previously initialized root key
  if (!g_root_key.initialized) {
    return PSA_ERROR_BAD_STATE;
  }

  // Prepare root key attributes
  psa_set_key_algorithm(&attributes, PSA_ALG_CMAC);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, ROOT_KEY_SIZE * 8);

  // Point the key buffer to the global root key
  uint8_t *key_buffer = (uint8_t*)g_root_key.data;
  size_t key_buffer_size = sizeof(g_root_key.data);
#endif // defined(SEMAILBOX_PRESENT)

  // Use CMAC as a key derivation function
  size_t session_key_length;
  status = psa_driver_wrapper_mac_compute(
    &attributes,
    key_buffer,
    key_buffer_size,
    PSA_ALG_CMAC,
    iv,
    iv_size,
    session_key,
    session_key_size,
    &session_key_length);

  // Verify that the key derivation was successful before transferring the key to the caller
  if (status != PSA_SUCCESS || session_key_length != SESSION_KEY_SIZE) {
    memset(session_key, 0, session_key_size);
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  return status;
}

/**
 * \brief Encrypt and authenticate ITS data with AES-128-GCM, storing the result in an encrypted blob.
 *
 * \param[in] metadata        ITS metadata to be used as authenticated additional data.
 * \param[in] plaintext       Pointer to array containing data to be encrypted.
 * \param[in] plaintext_size  Size of provided plaintext data array.
 * \param[out] blob           Pointer to array where the resulting encrypted blob shall be placed.
 * \param[in] blob_size       Size of the output array. Must be at least as big as plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
 * \param[out] blob_length    Resulting size of the output blob.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
psa_status_t sli_encrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                  uint8_t *plaintext,
                                  size_t plaintext_size,
                                  sli_its_encrypted_blob_t *blob,
                                  size_t blob_size,
                                  size_t *blob_length)
{
  if (metadata == NULL
      || (plaintext == NULL && plaintext_size > 0)
      || blob == NULL
      || blob_size < plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
      || blob_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Generate IV
  size_t iv_length = 0;
  psa_status_t psa_status = mbedtls_psa_external_get_random(NULL, blob->iv, AES_GCM_IV_SIZE, &iv_length);

  if (psa_status != PSA_SUCCESS || iv_length != AES_GCM_IV_SIZE) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  // Prepare encryption key
  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_ENCRYPT);
  psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, SESSION_KEY_SIZE * 8);

  uint8_t session_key[SESSION_KEY_SIZE];
  psa_status = derive_session_key(blob->iv, AES_GCM_IV_SIZE, session_key, sizeof(session_key));
  if (psa_status != PSA_SUCCESS) {
    return psa_status;
  }

  cache_session_key(session_key, metadata->uid);

  // Retrieve data to be encrypted
  if (plaintext_size != 0U) {
    memcpy(blob->data, ((uint8_t*)plaintext), plaintext_size);
  }

  // Encrypt and authenticate blob
  size_t output_length = 0;
  psa_status = psa_driver_wrapper_aead_encrypt(
    &attributes,
    session_key, sizeof(session_key),
    PSA_ALG_GCM,
    blob->iv, sizeof(blob->iv),
    (uint8_t*)metadata, sizeof(sli_its_file_meta_v2_t),    // metadata is AAD
    blob->data, plaintext_size,
    blob->data, plaintext_size + AES_GCM_MAC_SIZE,    // output == input for in-place encryption
    &output_length);

  // Clear the local session key immediately after we're done using it
  memset(session_key, 0, sizeof(session_key));

  if (psa_status != PSA_SUCCESS) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  if (output_length != plaintext_size + AES_GCM_MAC_SIZE) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *blob_length = output_length + AES_GCM_IV_SIZE;

  return PSA_SUCCESS;
}

/**
 * \brief Decrypt and authenticate encrypted ITS data.
 *
 * \param[in] metadata          ITS metadata to be used as authenticated additional data. Must be identical to the metadata used during encryption.
 * \param[in] blob              Encrypted blob containing data to be decrypted.
 * \param[in] blob_size         Size of the encrypted blob in bytes.
 * \param[out] plaintext        Pointer to array where the decrypted plaintext shall be placed.
 * \param[in] plaintext_size    Size of the plaintext array. Must be equal to sizeof(blob->data) - AES_GCM_MAC_SIZE.
 * \param[out] plaintext_length Resulting length of the decrypted plaintext.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_INVALID_SIGANTURE      The operation failed because authentication of the decrypted data failed.
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t sli_decrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                         sli_its_encrypted_blob_t *blob,
                                         size_t blob_size,
                                         uint8_t *plaintext,
                                         size_t plaintext_size,
                                         size_t *plaintext_length)
{
  if (metadata == NULL
      || blob == NULL
      || blob_size < plaintext_size + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD
      || (plaintext == NULL && plaintext_size > 0)
      || plaintext_length == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Prepare decryption key
  psa_key_attributes_t attributes = PSA_KEY_ATTRIBUTES_INIT;
  psa_set_key_usage_flags(&attributes, PSA_KEY_USAGE_DECRYPT);
  psa_set_key_algorithm(&attributes, PSA_ALG_GCM);
  psa_set_key_type(&attributes, PSA_KEY_TYPE_AES);
  psa_set_key_bits(&attributes, SESSION_KEY_SIZE * 8);

  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  uint8_t session_key[SESSION_KEY_SIZE];

  if (g_cached_session_key.active && g_cached_session_key.uid == metadata->uid) {
    // Use cached session key if it's already set and UID matches
    memcpy(session_key, g_cached_session_key.data, sizeof(session_key));
  } else {
    psa_status = derive_session_key(blob->iv, AES_GCM_IV_SIZE, session_key, sizeof(session_key));
    if (psa_status != PSA_SUCCESS) {
      return psa_status;
    }
    cache_session_key(session_key, metadata->uid);
  }

  // Decrypt and authenticate blob
  size_t output_length = 0;
  psa_status = psa_driver_wrapper_aead_decrypt(
    &attributes,
    session_key, sizeof(session_key),
    PSA_ALG_GCM,
    blob->iv, sizeof(blob->iv),
    (uint8_t*)metadata, sizeof(sli_its_file_meta_v2_t),    // metadata is AAD
    blob->data, plaintext_size + AES_GCM_MAC_SIZE,
    plaintext, plaintext_size,
    &output_length);

  // Clear the session key immediately after we're done using it
  memset(session_key, 0, sizeof(session_key));

  // Invalid signature likely means that NVM data was tampered with
  if (psa_status == PSA_ERROR_INVALID_SIGNATURE) {
    return PSA_ERROR_INVALID_SIGNATURE;
  }

  if (psa_status != PSA_SUCCESS
      || output_length != plaintext_size) {
    return PSA_ERROR_HARDWARE_FAILURE;
  }

  *plaintext_length = output_length;

  return PSA_SUCCESS;
}

/**
 * \brief Authenticate encrypted ITS data and return the UID of the ITS file that was authenticated.
 *
 * \details NOTE: This function will run sli_decrypt_its_file() internally. The difference from the sli_decrypt_its_file()
 *          function is that authenticate_its_file() reads the NVM3 data, decrypts it in order to authenticate the
 *          stored data, and then discards the plaintext. This is needed since PSA Crypto doesn't support the
 *          GMAC primitive directly, which means we have to run a full GCM decrypt for authentication.
 *
 * \param[in] nvm3_object_id      The NVM3 id corresponding to the stored ITS file.
 * \param[out] authenticated_uid  UID for the authenticated ITS file.
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_INVALID_SIGANTURE      The operation failed because authentication of the decrypted data failed.
 * \retval      PSA_ERROR_BAD_STATE              The root key has not been initialized.
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one or more arguments are NULL or of invalid size.
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 */
static psa_status_t authenticate_its_file(nvm3_ObjectKey_t nvm3_object_id,
                                          psa_storage_uid_t *authenticated_uid)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sli_its_file_meta_v2_t *its_file_meta = NULL;
  sli_its_encrypted_blob_t *blob = NULL;

  uint32_t obj_type;
  size_t its_file_size = 0;
  Ecode_t status = nvm3_getObjectInfo(nvm3_defaultHandle,
                                      nvm3_object_id,
                                      &obj_type,
                                      &its_file_size);
  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size);
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(its_file_buffer, 0, its_file_size);

  status = nvm3_readData(nvm3_defaultHandle,
                         nvm3_object_id,
                         its_file_buffer,
                         its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto cleanup;
  }

  its_file_meta = (sli_its_file_meta_v2_t*)its_file_buffer;
  blob = (sli_its_encrypted_blob_t*)(its_file_buffer + sizeof(sli_its_file_meta_v2_t));

  // Decrypt and authenticate blob
  size_t plaintext_length;
  psa_status = sli_decrypt_its_file(its_file_meta,
                                    blob,
                                    its_file_size - sizeof(sli_its_file_meta_v2_t),
                                    blob->data,
                                    its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                                    &plaintext_length);

  if (psa_status != PSA_SUCCESS) {
    goto cleanup;
  }

  if (plaintext_length != (its_file_size - sizeof(sli_its_file_meta_v2_t) - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
    goto cleanup;
  }

  if (authenticated_uid != NULL) {
    *authenticated_uid = its_file_meta->uid;
  }

  psa_status = PSA_SUCCESS;

  cleanup:

  // Discard output, as we're only interested in whether the authentication check passed or not.
  memset(its_file_buffer, 0, its_file_size);
  mbedtls_free(its_file_buffer);

  return psa_status;
}
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// -------------------------------------
// Global function definitions

/**
 * \brief create a new or modify an existing uid/value pair
 *
 * \param[in] uid           the identifier for the data
 * \param[in] data_length   The size in bytes of the data in `p_data`
 * \param[in] p_data        A buffer containing the data
 * \param[in] create_flags  The flags that the data will be stored with
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                      The operation completed successfully
 * \retval      PSA_ERROR_NOT_PERMITTED          The operation failed because the provided `uid` value was already created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_NOT_SUPPORTED          The operation failed because one or more of the flags provided in `create_flags` is not supported or is not valid
 * \retval      PSA_ERROR_INSUFFICIENT_STORAGE   The operation failed because there was insufficient space on the storage medium
 * \retval      PSA_ERROR_STORAGE_FAILURE        The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT       The operation failed because one of the provided pointers(`p_data`)
 *                                               is invalid, for example is `NULL` or references memory the caller cannot access
 * \retval      PSA_ERROR_HARDWARE_FAILURE       The operation failed because an internal cryptographic operation failed.
 * \retval      PSA_ERROR_INVALID_SIGNATURE      The operation failed because the provided `uid` doesnt match the autenticated uid from the storage
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,
                         uint32_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags)
{
  if ((data_length != 0U) && (p_data == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  if ((data_length > NVM3_MAX_OBJECT_SIZE)) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  if (create_flags != PSA_STORAGE_FLAG_WRITE_ONCE
      && create_flags != PSA_STORAGE_FLAG_NONE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
      && create_flags != PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
#endif
      ) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  if ((create_flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE)
      && (!object_lives_in_s(p_data, data_length))) {
    // The flag indicates that this data should not be set by the non-secure domain
    return PSA_ERROR_INVALID_ARGUMENT;
  }
#endif

  Ecode_t status;
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sli_its_file_meta_v2_t* its_file_meta;
  nvm3_ObjectKey_t nvm3_object_id = 0;
#if defined(SLI_PSA_ITS_ENCRYPTED)
  sli_its_encrypted_blob_t *blob = NULL;
  size_t its_file_size = data_length + SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
  size_t blob_length = 0u;
#else
  size_t its_file_size = data_length;
#endif

  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size + sizeof(sli_its_file_meta_v2_t));
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));

  its_file_meta = (sli_its_file_meta_v2_t *)its_file_buffer;

  sli_its_acquire_mutex();
  psa_status = find_nvm3_id(uid, true, its_file_meta, NULL, NULL, &nvm3_object_id);
  if (psa_status != PSA_SUCCESS) {
    if (psa_status == PSA_ERROR_DOES_NOT_EXIST) {
      psa_status = PSA_ERROR_INSUFFICIENT_STORAGE;
    }
    goto exit;
  }

  its_file_meta->magic = SLI_PSA_ITS_META_MAGIC_V2;
  its_file_meta->uid = uid;
  its_file_meta->flags = create_flags;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Everything after the the file metadata will make up the encrypted & authenticated blob
  blob = (sli_its_encrypted_blob_t*)(its_file_buffer + sizeof(sli_its_file_meta_v2_t));

  // Encrypt and authenticate the provided data
  psa_status = sli_encrypt_its_file(its_file_meta,
                                    (uint8_t*)p_data,
                                    data_length,
                                    blob,
                                    its_file_size,
                                    &blob_length);

  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  if (blob_length != its_file_size) {
    psa_status = PSA_ERROR_HARDWARE_FAILURE;
    goto exit;
  }

#else
  if (data_length != 0U) {
    memcpy(its_file_buffer + sizeof(sli_its_file_meta_v2_t), ((uint8_t*)p_data), data_length);
  }
#endif

  status = nvm3_writeData(nvm3_defaultHandle,
                          nvm3_object_id,
                          its_file_buffer, its_file_size + sizeof(sli_its_file_meta_v2_t));

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    set_cache(nvm3_object_id);
  } else {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size + sizeof(sli_its_file_meta_v2_t));
  mbedtls_free(its_file_buffer);
  sli_its_release_mutex();
  return psa_status;
}

/**
 * \brief Retrieve the value associated with a provided uid
 *
 * \param[in] uid               The uid value
 * \param[in] data_offset       The starting offset of the data requested
 * \param[in] data_length       the amount of data requested (and the minimum allocated size of the `p_data` buffer)
 * \param[out] p_data           The buffer where the data will be placed upon successful completion
 * \param[out] p_data_length    The amount of data returned in the p_data buffer
 *
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided `uid` value was not found in the storage
 * \retval      PSA_ERROR_BUFFER_TOO_SMALL   The operation failed because the data associated with provided uid is larger than `data_size`
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_data`, `p_data_length`)
 *                                           is invalid. For example is `NULL` or references memory the caller cannot access.
 *                                           In addition, this can also happen if an invalid offset was provided.
 */
psa_status_t psa_its_get(psa_storage_uid_t uid,
                         uint32_t data_offset,
                         uint32_t data_length,
                         void *p_data,
                         size_t *p_data_length)
{
  if ((data_length != 0U) && (p_data_length == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (data_length != 0U) {
    // If the request amount of data is 0, allow invalid pointer of the output buffer.
    if ((p_data == NULL)
        || ((uint32_t)p_data < SRAM_BASE)
        || ((uint32_t)p_data > (SRAM_BASE + SRAM_SIZE - data_length))) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  size_t plaintext_length;
  sli_its_encrypted_blob_t *blob = NULL;
#endif
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  Ecode_t status;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0u;
  size_t its_file_data_size = 0u;
  size_t its_file_offset = 0u;
  nvm3_ObjectKey_t nvm3_object_id;

  sli_its_acquire_mutex();
  psa_status = find_nvm3_id(uid, false, &its_file_meta, &its_file_offset, &its_file_size, &nvm3_object_id);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE
      && !object_lives_in_s(p_data, data_length)) {
    // The flag indicates that this data should not be read back to the non-secure domain
    psa_status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Subtract IV and MAC from ITS file as the below checks concern the actual data size
  its_file_data_size = its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#else
  its_file_data_size = its_file_size;
#endif

  if (data_length != 0U) {
    if ((data_offset >= its_file_data_size) && (its_file_data_size != 0U)) {
      psa_status = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }

    if ((its_file_data_size == 0U) && (data_offset != 0U)) {
      psa_status = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }
  } else {
    // Allow the offset at the data size boundary if the requested amount of data is zero.
    if (data_offset > its_file_data_size) {
      psa_status = PSA_ERROR_INVALID_ARGUMENT;
      goto exit;
    }
  }

  if (data_length > (its_file_data_size - data_offset)) {
    *p_data_length = its_file_data_size - data_offset;
  } else {
    *p_data_length = data_length;
  }

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // its_file_size includes size of sli_its_encrypted_blob_t struct
  blob = (sli_its_encrypted_blob_t*)mbedtls_calloc(1, its_file_size);
  if (blob == NULL) {
    psa_status = PSA_ERROR_INSUFFICIENT_MEMORY;
    goto exit;
  }
  memset(blob, 0, its_file_size);

  status = nvm3_readPartialData(nvm3_defaultHandle,
                                nvm3_object_id,
                                blob,
                                its_file_offset,
                                its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

  // Decrypt and authenticate blob
  psa_status = sli_decrypt_its_file(&its_file_meta,
                                    blob,
                                    its_file_size,
                                    blob->data,
                                    its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD,
                                    &plaintext_length);

  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }

  if (plaintext_length != (its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD)) {
    psa_status = PSA_ERROR_INVALID_SIGNATURE;
    goto exit;
  }

  // Verify that the requested UID is equal to the retrieved and authenticated UID
  if (uid != its_file_meta.uid) {
    psa_status = PSA_ERROR_INVALID_ARGUMENT;
    goto exit;
  }

  if (*p_data_length > 0) {
    memcpy(p_data, blob->data + data_offset, *p_data_length);
  }
  psa_status = PSA_SUCCESS;

  exit:
  if (blob != NULL) {
    memset(blob, 0, its_file_size);
    mbedtls_free(blob);
  }
  sli_its_release_mutex();
#else
  // If no encryption is used, just read out the data and write it directly to the output buffer
  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, p_data, its_file_offset + data_offset, *p_data_length);

  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  } else {
    psa_status = PSA_SUCCESS;
  }

  exit:
  sli_its_release_mutex();
#endif

  return psa_status;
}

/**
 * \brief Retrieve the metadata about the provided uid
 *
 * \param[in] uid           The uid value
 * \param[out] p_info       A pointer to the `psa_storage_info_t` struct that will be populated with the metadata
 *
 * \return      A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided uid value was not found in the storage
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The operation failed because one of the provided pointers(`p_info`)
 *                                           is invalid, for example is `NULL` or references memory the caller cannot access
 * \retval      PSA_ERROR_INVALID_SIGANTURE  The operation failed because authentication of the stored metadata failed.
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info)
{
  if (p_info == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0;
  size_t its_file_offset = 0;
  nvm3_ObjectKey_t nvm3_object_id;

  sli_its_acquire_mutex();
  psa_status = find_nvm3_id(uid, false, &its_file_meta, &its_file_offset, &its_file_size, &nvm3_object_id);
  if (psa_status != PSA_SUCCESS) {
    sli_its_release_mutex();
    return psa_status;
  }

  p_info->flags = its_file_meta.flags;
  p_info->size = its_file_size;

#if defined(SLI_PSA_ITS_ENCRYPTED)
  // Remove IV and MAC size from file size
  p_info->size = its_file_size - SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD;
#endif
  sli_its_release_mutex();
  return PSA_SUCCESS;
}

/**
 * \brief Remove the provided key and its associated data from the storage
 *
 * \param[in] uid   The uid value
 *
 * \return  A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The operation completed successfully
 * \retval      PSA_ERROR_DOES_NOT_EXIST     The operation failed because the provided key value was not found in the storage
 * \retval      PSA_ERROR_NOT_PERMITTED      The operation failed because the provided key value was created with PSA_STORAGE_FLAG_WRITE_ONCE
 * \retval      PSA_ERROR_STORAGE_FAILURE    The operation failed because the physical storage has failed (Fatal error)
 */
psa_status_t psa_its_remove(psa_storage_uid_t uid)
{
  psa_status_t psa_status = PSA_ERROR_CORRUPTION_DETECTED;
  Ecode_t status;
  sli_its_file_meta_v2_t its_file_meta = { 0 };
  size_t its_file_size = 0;
  size_t its_file_offset = 0;
  nvm3_ObjectKey_t nvm3_object_id;

  sli_its_acquire_mutex();
  psa_status = find_nvm3_id(uid, false, &its_file_meta, &its_file_offset, &its_file_size, &nvm3_object_id);
  if (psa_status != PSA_SUCCESS) {
    goto exit;
  }
  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
      || (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE)
#endif
      ) {
    psa_status = PSA_ERROR_NOT_PERMITTED;
    goto exit;
  }
  status = nvm3_deleteObject(nvm3_defaultHandle, nvm3_object_id);
  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    clear_cache(nvm3_object_id);
    set_tomb(nvm3_object_id);
    psa_status = PSA_SUCCESS;
  } else {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  sli_its_release_mutex();
  return psa_status;
}

// -------------------------------------
// Silicon Labs extensions

static psa_storage_uid_t psa_its_identifier_of_slot(mbedtls_svc_key_id_t key)
{
#if defined(MBEDTLS_PSA_CRYPTO_KEY_ID_ENCODES_OWNER)
  /* Encode the owner in the upper 32 bits. This means that if
   * owner values are nonzero (as they are on a PSA platform),
   * no key file will ever have a value less than 0x100000000, so
   * the whole range 0..0xffffffff is available for non-key files. */
  uint32_t unsigned_owner_id = MBEDTLS_SVC_KEY_ID_GET_OWNER_ID(key);
  return ((uint64_t) unsigned_owner_id << 32) | MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key);
#else
  /* Use the key id directly as a file name.
   * psa_is_key_id_valid() in psa_crypto_slot_management.c
   * is responsible for ensuring that key identifiers do not have a
   * value that is reserved for non-key files. */
  return key;
#endif
}

psa_status_t sli_psa_its_change_key_id(mbedtls_svc_key_id_t old_id,
                                       mbedtls_svc_key_id_t new_id)
{
  psa_storage_uid_t old_uid = psa_its_identifier_of_slot(old_id);
  psa_storage_uid_t new_uid = psa_its_identifier_of_slot(new_id);
  size_t its_file_size = 0;
  psa_status_t status = PSA_ERROR_CORRUPTION_DETECTED;
  if (old_id == new_id) {
    return PSA_SUCCESS;
  }
  // Check whether the key to migrate exists on disk
  struct psa_storage_info_t p_info;
  status = psa_its_get_info(old_uid, &p_info);
  if (status != PSA_SUCCESS) {
    return status;
  }

  // Allocate temporary buffer and cast it to the metadata format
  uint8_t *its_file_buffer = mbedtls_calloc(1, p_info.size);
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  // Read contents of pre-existing key into the temporary buffer
  status = psa_its_get(old_uid, 0, p_info.size, its_file_buffer,
                       &its_file_size);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_its_set(new_uid, its_file_size, its_file_buffer,
                       p_info.flags);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  status = psa_its_remove(old_uid);

  if (status != PSA_SUCCESS) {
    goto exit;
  }

  exit:
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size);
  mbedtls_free(its_file_buffer);
  return status;
}

/**
 * \brief Check if the ITS encryption is enabled
 */
psa_status_t sli_psa_its_encrypted(void)
{
#if defined(SLI_PSA_ITS_ENCRYPTED)
  return PSA_SUCCESS;
#else
  return PSA_ERROR_NOT_SUPPORTED;
#endif
}

#if defined(SLI_PSA_ITS_ENCRYPTED) && !defined(SEMAILBOX_PRESENT)
/**
 * \brief Set the root key to be used when deriving session keys for ITS encryption.
 *
 * \param[in] root_key        Buffer containing the root key.
 * \param[in] root_key_size   Size of the root key in bytes. Must be 32 (256 bits).
 *
 * \return  A status indicating the success/failure of the operation
 *
 * \retval      PSA_SUCCESS                  The key was successfully set.
 * \retval      PSA_ERROR_INVALID_ARGUMENT   The root key was NULL or had an invalid size.
 * \retval      PSA_ERROR_ALREADY_EXISTS     The root key has already been initialized.
 */
psa_status_t sli_psa_its_set_root_key(uint8_t *root_key, size_t root_key_size)
{
  // Check that arguments are valid
  if (root_key == NULL || root_key_size != sizeof(g_root_key.data)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  // Check that the root key has not already been set
  // (This is possibly too restrictive. For TrustZone usage this can be enforced by
  // not exposing the function to NS instead.)
  if (g_root_key.initialized) {
    return PSA_ERROR_ALREADY_EXISTS;
  }

  // Store the provided root key and mark it as initialized
  memcpy(g_root_key.data, root_key, sizeof(g_root_key.data));
  g_root_key.initialized = true;

  return PSA_SUCCESS;
}
#endif // defined(SLI_PSA_ITS_ENCRYPTED) && !defined(SEMAILBOX_PRESENT)
#endif // (!SL_PSA_ITS_SUPPORT_V3_DRIVER)
#endif // MBEDTLS_PSA_CRYPTO_STORAGE_C && !MBEDTLS_PSA_ITS_FILE_C
