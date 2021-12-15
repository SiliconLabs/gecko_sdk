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

// -------------------------------------
// Includes

#if defined(MBEDTLS_CONFIG_FILE)
#include MBEDTLS_CONFIG_FILE
#else
#include "mbedtls/config.h"
#endif

#if defined(MBEDTLS_PSA_CRYPTO_STORAGE_C) && !defined(MBEDTLS_PSA_ITS_FILE_C)

#include "psa/internal_trusted_storage.h"
#include "nvm3_default.h"
#include "mbedtls/platform.h"
#include <stdbool.h>
#include <string.h>

// -------------------------------------
// Defines

#define SLI_PSA_ITS_META_MAGIC_V1   (0x05E175D1UL)
#define SLI_PSA_ITS_META_MAGIC_V2   (0x5E175D10UL)

/* Allocated range of NVM3 IDs for PSA ITS usage */
#define SLI_PSA_ITS_NVM3_RANGE_BASE  (0x83100UL)
#define SLI_PSA_ITS_NVM3_RANGE_SIZE  (0x00400UL)

#ifndef SL_PSA_ITS_MAX_FILES
#define SL_PSA_ITS_MAX_FILES    SLI_PSA_ITS_NVM3_RANGE_SIZE
#endif

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

// -------------------------------------
// Structs

#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)
typedef struct {
  uint32_t magic;
  psa_storage_uid_t uid;
  psa_storage_create_flags_t flags;
} sl_its_file_meta_v1_t;
#endif /* SLI_ITS_SUPPORT_V1_FORMAT */

// Due to alignment constraints on the 64-bit UID, the v2 header struct is
// serialized to 16 bytes instead of the 24 bytes the v1 header compiles to.
typedef struct {
  uint32_t magic;
  psa_storage_create_flags_t flags;
  psa_storage_uid_t uid;
} sl_its_file_meta_v2_t;

// -------------------------------------
// Local function prototypes

static nvm3_ObjectKey_t get_nvm3_id(psa_storage_uid_t uid, bool find_empty_slot);
static nvm3_ObjectKey_t prepare_its_get_nvm3_id(psa_storage_uid_t uid);

// -------------------------------------
// Local function definitions

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
  return (bool)(nvm3_uid_set_cache[bin] >> offset);
}

static void init_cache()
{
  size_t num_keys_referenced_by_nvm3;
  nvm3_ObjectKey_t keys_referenced_by_nvm3[SLI_PSA_ITS_CACHE_INIT_CHUNK_SIZE];

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
                                                   range_end);

    for (size_t i = 0; i < num_keys_referenced_by_nvm3; i++) {
      cache_set(keys_referenced_by_nvm3[i]);
    }
  }

  nvm3_uid_set_cache_initialized = true;
}

// Read the file metadata for a specific NVM3 ID
static Ecode_t get_file_metadata(nvm3_ObjectKey_t key,
                                 sl_its_file_meta_v2_t* metadata,
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
                                        sizeof(sl_its_file_meta_v2_t));
  if (status != ECODE_NVM3_OK) {
    return status;
  }

#if defined(SLI_PSA_ITS_SUPPORT_V1_FORMAT)
  // Re-read in v1 header format and translate to the latest structure version
  if (metadata->magic == SLI_PSA_ITS_META_MAGIC_V1) {
    sl_its_file_meta_v1_t key_meta_v1;
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
      *its_file_offset = sizeof(sl_its_file_meta_v2_t);
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
  sl_its_file_meta_v2_t key_meta;

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
  if (nvm3_initDefault() != ECODE_NVM3_OK) {
    return SLI_PSA_ITS_NVM3_RANGE_END + 1U;
  }

  if (nvm3_uid_set_cache_initialized == false) {
    init_cache();
  }

  return get_nvm3_id(uid, false);
}

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
 */
psa_status_t psa_its_set(psa_storage_uid_t uid,
                         uint32_t data_length,
                         const void *p_data,
                         psa_storage_create_flags_t create_flags)
{
  if ((data_length != 0U) && (p_data == NULL)) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  if (create_flags != PSA_STORAGE_FLAG_WRITE_ONCE
      && create_flags != PSA_STORAGE_FLAG_NONE) {
    return PSA_ERROR_NOT_SUPPORTED;
  }

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  Ecode_t status;
  psa_status_t ret = PSA_SUCCESS;
  sl_its_file_meta_v2_t* its_file_meta;
  size_t its_file_size = data_length + sizeof(sl_its_file_meta_v2_t);
  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size);
  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }
  memset(its_file_buffer, 0, its_file_size);

  its_file_meta = (sl_its_file_meta_v2_t *)its_file_buffer;
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
    } else {
      if (its_file_meta->flags == PSA_STORAGE_FLAG_WRITE_ONCE) {
        ret = PSA_ERROR_NOT_PERMITTED;
        goto exit;
      }
    }
  }

  its_file_meta->flags = create_flags;
  if (data_length != 0U) {
    memcpy(its_file_buffer + sizeof(sl_its_file_meta_v2_t), ((uint8_t*)p_data), data_length);
  }
  status = nvm3_writeData(nvm3_defaultHandle, nvm3_object_id, its_file_buffer, its_file_size);

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    cache_set(nvm3_object_id);
  } else {
    ret = PSA_ERROR_STORAGE_FAILURE;
  }

  exit:
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size);
  mbedtls_free(its_file_buffer);
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

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_v2_t its_file_meta;
  size_t its_file_size = 0;
  size_t its_file_offset = 0;

  status = get_file_metadata(nvm3_object_id, &its_file_meta, &its_file_offset, &its_file_size);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  if (data_length != 0U) {
    if ((data_offset >= its_file_size) && (its_file_size != 0U)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }

    if ((its_file_size == 0U) && (data_offset != 0U)) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  } else {
    // Allow the offset at the data size boundary if the requested amount of data is zero.
    if (data_offset > its_file_size) {
      return PSA_ERROR_INVALID_ARGUMENT;
    }
  }

  if (data_length > (its_file_size - data_offset)) {
    *p_data_length = its_file_size - data_offset;
  } else {
    *p_data_length = data_length;
  }

  status = nvm3_readPartialData(nvm3_defaultHandle, nvm3_object_id, p_data, its_file_offset + data_offset, *p_data_length);

  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  return PSA_SUCCESS;
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
 */
psa_status_t psa_its_get_info(psa_storage_uid_t uid,
                              struct psa_storage_info_t *p_info)
{
  if (p_info == NULL) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_v2_t its_file_meta;
  size_t its_file_size = 0;
  size_t its_file_offset = 0;

  status = get_file_metadata(nvm3_object_id, &its_file_meta, &its_file_offset, &its_file_size);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  p_info->flags = its_file_meta.flags;
  p_info->size = its_file_size;
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
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  Ecode_t status;
  sl_its_file_meta_v2_t its_file_meta;

  status = get_file_metadata(nvm3_object_id, &its_file_meta, NULL, NULL);
  if (status == SLI_PSA_ITS_ECODE_NO_VALID_HEADER) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }
  if (status != ECODE_NVM3_OK
      && status != SLI_PSA_ITS_ECODE_NEEDS_UPGRADE) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  if (its_file_meta.flags == PSA_STORAGE_FLAG_WRITE_ONCE) {
    return PSA_ERROR_NOT_PERMITTED;
  }

  status = nvm3_deleteObject(nvm3_defaultHandle, nvm3_object_id);

  if (status == ECODE_NVM3_OK) {
    // Power-loss might occur, however upon boot, the look-up table will be
    // re-filled as long as the data has been successfully written to NVM3.
    if (previous_lookup.set && previous_lookup.uid == uid) {
      previous_lookup.set = false;
    }
    cache_clear(nvm3_object_id);

    return PSA_SUCCESS;
  } else {
    return PSA_ERROR_STORAGE_FAILURE;
  }
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
  return(  ( (uint64_t) unsigned_owner_id << 32)
           | MBEDTLS_SVC_KEY_ID_GET_KEY_ID(key) );
#else
  /* Use the key id directly as a file name.
   * psa_is_key_id_valid() in psa_crypto_slot_management.c
   * is responsible for ensuring that key identifiers do not have a
   * value that is reserved for non-key files. */
  return(key);
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

  // Check whether the key to migrate exists on disk
  nvm3_ObjectKey_t nvm3_object_id = prepare_its_get_nvm3_id(old_uid);
  if (nvm3_object_id > SLI_PSA_ITS_NVM3_RANGE_END) {
    return PSA_ERROR_DOES_NOT_EXIST;
  }

  // Get total length to allocate
  status = nvm3_getObjectInfo(nvm3_defaultHandle,
                              nvm3_object_id,
                              &obj_type,
                              &its_file_size);
  if (status != ECODE_NVM3_OK) {
    return PSA_ERROR_STORAGE_FAILURE;
  }

  // Allocate temporary buffer and cast it to the metadata format
  uint8_t *its_file_buffer = mbedtls_calloc(1, its_file_size);
  sl_its_file_meta_v2_t* metadata = (sl_its_file_meta_v2_t*) its_file_buffer;

  if (its_file_buffer == NULL) {
    return PSA_ERROR_INSUFFICIENT_MEMORY;
  }

  // Read contents of pre-existing key into the temporary buffer
  status = nvm3_readData(nvm3_defaultHandle,
                         nvm3_object_id,
                         its_file_buffer,
                         its_file_size);
  if (status != ECODE_NVM3_OK) {
    psa_status = PSA_ERROR_STORAGE_FAILURE;
    goto exit;
  }

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
  // Clear and free key buffer before return.
  memset(its_file_buffer, 0, its_file_size);
  mbedtls_free(its_file_buffer);
  return psa_status;
}

#endif // MBEDTLS_PSA_CRYPTO_STORAGE_C && !MBEDTLS_PSA_ITS_FILE_C
