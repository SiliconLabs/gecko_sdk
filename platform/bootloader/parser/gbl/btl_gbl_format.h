/***************************************************************************//**
 * @file
 * @brief Definitions for the Silicon Labs GBL format
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/
#ifndef BTL_GBL_FORMAT_H
#define BTL_GBL_FORMAT_H

#include <stdint.h>
#include "api/application_properties.h"

/***************************************************************************//**
 * @addtogroup Components
 * @{
 * @addtogroup ImageParser Image Parser
 * @{
 * @addtogroup GblParser GBL Parser
 * @{
 * @addtogroup GblParserFormat GBL Format
 * @{
 ******************************************************************************/

// -------------------------------
// Defines

// -----------------------------------------------------------------------------
// GBL version

/// Magic word indicating GBL image
#define GBL_IMAGE_MAGIC_WORD                0xE35050E3UL
/// Major version of the GBL spec
#define GBL_COMPATIBILITY_MAJOR_VERSION     0x03000000UL

// -------------------------------
// Tag IDs

/// Tag ID for the GBL header tag
#define GBL_TAG_ID_HEADER_V3                0x03A617EBUL
/// Tag ID for the GBL bootloader tag
#define GBL_TAG_ID_BOOTLOADER               0xF50909F5UL
/// Tag ID for the GBL application info tag
#define GBL_TAG_ID_APPLICATION              0xF40A0AF4UL
/// Tag ID for the GBL metadata tag
#define GBL_TAG_ID_METADATA                 0xF60808F6UL
/// Tag ID for the GBL flash program tag
#define GBL_TAG_ID_PROG                     0xFE0101FEUL
/// Tag ID for the GBL flash erase&program tag
#define GBL_TAG_ID_ERASEPROG                0xFD0303FDUL
/// Tag ID for the GBL end tag
#define GBL_TAG_ID_END                      0xFC0404FCUL
/// Tag ID for the SE upgrade tag
#define GBL_TAG_ID_SE_UPGRADE               0x5EA617EBUL

// Encryption-related tags
/// Tag ID for the GBL encryption header tag
#define GBL_TAG_ID_ENC_HEADER               0xFB0505FBUL
/// Tag ID for the GBL encryption init tag
#define GBL_TAG_ID_ENC_INIT                 0xFA0606FAUL
/// Tag ID for the GBL encryption data tag
#define GBL_TAG_ID_ENC_GBL_DATA             0xF90707F9UL

// Signature-related tags
/// Tag ID for the GBL ECDSA secp256r1 signature tag
#define GBL_TAG_ID_SIGNATURE_ECDSA_P256     0xF70A0AF7UL
/// Tag ID for the GBL ECDSA certfificate tag
#define GBL_TAG_ID_CERTIFICATE_ECDSA_P256   0xF30B0BF3UL

// -------------------------------
// GBL types

/// GBL type: Standard GBL
#define GBL_TYPE_NONE                       0x00000000UL
/// GBL type: AES-CCM encrypted GBL
#define GBL_TYPE_ENCRYPTION_AESCCM          0x00000001UL
/// GBL type: ECDSA P256-signed GBL
#define GBL_TYPE_SIGNATURE_ECDSA            0x00000100UL

// -------------------------------
// Structs

/// GBL tag header. Must be the first element in all GBL tags.
typedef struct {
  uint32_t  tagId;            ///< Tag ID
  uint32_t  length;           ///< Length (in bytes) of the rest of the tag
} GblTagHeader_t;

/// GBL header tag type.
typedef struct {
  GblTagHeader_t header;      ///< Tag ID and length
  uint32_t       version;     ///< Version of the GBL spec used in this file
  uint32_t       type;        ///< Type of GBL
} GblHeader_t;

/// GBL application tag type.
typedef struct {
  GblTagHeader_t    header;   ///< Tag ID and length
  ApplicationData_t appInfo;  ///< Information about the application
} GblApplication_t;

/// GBL bootloader tag type.
typedef struct {
  GblTagHeader_t header;             ///< Tag ID and length
  uint32_t       bootloaderVersion;  ///< Version number of the bootloader
  uint32_t       address;            ///< Address of the bootloader
  uint8_t        *data;              ///< Array of data for bootloader upgrade
} GblBootloader_t;

/// GBL SE upgrade tag type.
typedef struct {
  GblTagHeader_t header;             ///< Tag ID and length
  uint32_t       blobSize;           ///< Size of the SE upgrade blob
  uint32_t       version;            ///< Version of the SE image
  uint8_t        *data;              ///< Array of data for SE upgrade
} GblSeUpgrade_t;

/// GBL metadata tag type.
typedef struct {
  GblTagHeader_t header;      ///< Tag ID and length
  uint8_t        *metaData;   ///< Array of metadata
} GblMetadata_t;

/// GBL flash program tag type.
typedef struct {
  GblTagHeader_t header;            ///< Tag ID and length
  uint32_t       flashStartAddress; ///< Address to start flashing
  uint8_t        *data;             ///< Array of data to flash
} GblProg_t;

/// GBL end tag type.
typedef struct {
  GblTagHeader_t header;      ///< Tag ID and length
  uint32_t       gblCrc;      ///< CRC32 of the entire GBL file.
} GblEnd_t;

/// GBL encryption init tag type. Used with AES-CCM encryption.
typedef struct {
  GblTagHeader_t header;      ///< Tag ID and length
  uint32_t       msgLen;      ///< Length of the cipher text in bytes
  uint8_t        nonce[12];   ///< @brief Random nonce used for AES-CTR in
                              ///< this message
} GblEncryptionInitAesCcm_t;

/// GBL encryption data tag type.
typedef struct {
  GblTagHeader_t header;            ///< Tag ID and length
  uint8_t        *encryptedGblData; ///< @brief Encrypted data
                                    ///< @details After decryption, this data
                                    ///< must represent one or more complete
                                    ///< unencrypted GBL tags.
} GblEncryptionData_t;

/// GBL certificate chain for signing
typedef struct {
  GblTagHeader_t header;                ///< Tag ID and length
  ApplicationCertificate_t certificate; ///< Certificate used to verify GBL
} GblCertificateEcdsaP256_t;

/// GBL ECDSA secp256r1 signature tag type.
typedef struct {
  GblTagHeader_t header;  ///< Tag ID and length
  uint8_t        r[32];   ///< R-point of ECDSA secp256r1 signature
  uint8_t        s[32];   ///< S-point of ECDSA secp256r1 signature
} GblSignatureEcdsaP256_t;

/** @} addtogroup GblParserFormat */
/** @} addtogroup GblParser */
/** @} addtogroup ImageParser */
/** @} addtogroup Components */

#endif // BTL_GBL_FORMAT_H
