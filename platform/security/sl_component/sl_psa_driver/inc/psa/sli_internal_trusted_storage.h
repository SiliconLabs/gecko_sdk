/***************************************************************************//**
 * # License
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is Third Party Software licensed by Silicon Labs from a third party
 * and is governed by the sections of the MSLA applicable to Third Party
 * Software and the additional terms set forth below.
 *
 ******************************************************************************/
/** \file sli_internal_trusted_storage.h
 * \brief Internal interface and declarations of trusted storage.
 */

#ifndef SLI_INTERNAL_TRUSTED_STORAGE_H
#define SLI_INTERNAL_TRUSTED_STORAGE_H

#include <stddef.h>
#include <stdint.h>

#include <psa/crypto_types.h>
#include <psa/crypto_values.h>

#ifdef __cplusplus
extern "C" {
#endif
#if defined(TFM_CONFIG_SL_SECURE_LIBRARY)
#define PSA_STORAGE_FLAG_WRITE_ONCE_SECURE_ACCESSIBLE (1 << 3)
#endif // TFM_CONFIG_SL_SECURE_LIBRARY

psa_status_t sli_psa_its_change_key_id(mbedtls_svc_key_id_t old_id,
                                       mbedtls_svc_key_id_t new_id);

/**
 * \brief Check if the ITS encryption is enabled
 *
 * \details The function is added in order to support runtime checking
 *          needed by trustzone-agnostic libraries
 *
 * \retval      PSA_SUCCESS                 ITS encryption is enabled
 * \retval      PSA_ERROR_NOT_SUPPORTED     ITS encryption is not supported
 */
psa_status_t sli_psa_its_encrypted(void);

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
psa_status_t sli_psa_its_set_root_key(uint8_t *root_key, size_t root_key_size);
#endif // defined(SLI_PSA_ITS_ENCRYPTED) && !defined(SEMAILBOX_PRESENT)

/* Magic values for ITS metadata versions */
#define SLI_PSA_ITS_META_MAGIC_V1             (0x05E175D1UL)
#define SLI_PSA_ITS_META_MAGIC_V2             (0x5E175D10UL)

/* Allocated range of NVM3 IDs for PSA ITS usage */
#define SLI_PSA_ITS_NVM3_RANGE_SIZE  (0x00400UL)
#if (SL_PSA_ITS_SUPPORT_V3_DRIVER)
#define SLI_PSA_ITS_NVM3_RANGE_END   (0x87100UL)
#define SLI_PSA_ITS_NVM3_RANGE_START  (SLI_PSA_ITS_NVM3_RANGE_END - SLI_PSA_ITS_NVM3_RANGE_SIZE)
#else
#define SLI_PSA_ITS_NVM3_RANGE_BASE  (0x83100UL)
#endif

#ifndef SL_PSA_ITS_MAX_FILES
#define SL_PSA_ITS_MAX_FILES    SLI_PSA_ITS_NVM3_RANGE_SIZE
#endif

#if (SL_PSA_ITS_SUPPORT_V3_DRIVER)

#if !defined(SL_PSA_ITS_REMOVE_V1_HEADER_SUPPORT) && SL_PSA_ITS_SUPPORT_V1_DRIVER
#define SLI_PSA_ITS_SUPPORT_V1_FORMAT_INTERNAL
#endif

#if SL_PSA_ITS_SUPPORT_V2_DRIVER
#define SLI_PSA_ITS_NVM3_RANGE_START_V2_DRIVER (0x83100UL)
#define SLI_PSA_ITS_NVM3_RANGE_END_V2_DRIVER \
  SLI_PSA_ITS_NVM3_RANGE_START_V2_DRIVER + SLI_PSA_ITS_NVM3_RANGE_SIZE
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
// Define some cryptographic constants if not already set. This depends on the underlying
// crypto accelerator in use (CRYPTOACC has these defines, but not SEMAILBOX).
#define AES_GCM_MAC_SIZE 16
#define AES_GCM_IV_SIZE (12)

#define SLI_ITS_ENCRYPTED_BLOB_SIZE_OVERHEAD  (AES_GCM_IV_SIZE + AES_GCM_MAC_SIZE)
#endif // defined(SLI_PSA_ITS_ENCRYPTED)

// Due to alignment constraints on the 64-bit UID, the v2 header struct is
// serialized to 16 bytes instead of the 24 bytes the v1 header compiles to.
typedef struct {
  uint32_t magic;
  psa_storage_create_flags_t flags;
  psa_storage_uid_t uid;
} sli_its_file_meta_v2_t;

#if defined(SLI_PSA_ITS_ENCRYPTED)
typedef struct {
  uint8_t iv[AES_GCM_IV_SIZE];
  // When encrypted & authenticated, MAC is stored at the end of the data array
  uint8_t data[];
} sli_its_encrypted_blob_t;
#endif

#if defined(SLI_PSA_ITS_ENCRYPTED)
psa_status_t sli_encrypt_its_file(sli_its_file_meta_v2_t *metadata,
                                  uint8_t *plaintext,
                                  size_t plaintext_size,
                                  sli_its_encrypted_blob_t *blob,
                                  size_t blob_size,
                                  size_t *blob_length);
#endif

#endif // SL_PSA_ITS_SUPPORT_V3_DRIVER
#ifdef __cplusplus
}
#endif

#endif /* SLI_INTERNAL_TRUSTED_STORAGE_H */
