/***************************************************************************//**
 * @file
 * @brief Encrypted Advertisement Data core interfaces.
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
#ifndef SL_BT_EAD_CORE_H
#define SL_BT_EAD_CORE_H

/***********************************************************************************************//**
 * @addtogroup ead_core
 * @{
 **************************************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "sl_bgapi.h"
#include "sl_status.h"

/// @typedef Session key, CORE Version Denver r04, Vol 3, Part C, Table 12.10
typedef uint8_t                         sl_bt_ead_session_key_t[16];

/// @typedef Init. Vector, CORE Version Denver r04, Vol 3, Part C, Table 12.10
typedef uint8_t                         sl_bt_ead_iv_t[8];

/// @typedef EAD Randomizer, Core Supplement Spec. d11, Part A, 1.23.1
typedef uint8_t                         sl_bt_ead_randomizer_t[5];

/// @typedef EAD MIC, inherits CCM parameters of Core v5.3, Vol 6, Part E, S. 1
typedef uint8_t                         sl_bt_ead_mic_t[4];

/// @typedef Pointer to EAD Key Material structure
typedef struct sl_bt_ead_key_material_s *sl_bt_ead_key_material_p;

/// @typedef Pointer to EAD Nonce structure
typedef struct sl_bt_ead_nonce_s        *sl_bt_ead_nonce_p;

/// @typedef Advertising and Scan Response data
typedef struct sl_bt_ead_ad_structure_s *sl_bt_ead_ad_structure_p;

/// EAD Key Material, CORE Denver r04, Vol 3, Part C, 12.6
PACKSTRUCT(struct sl_bt_ead_key_material_s {
  sl_bt_ead_session_key_t key;
  sl_bt_ead_iv_t          iv;
});

/// EAD Nonce, Core Supplement Spec. d11, Part A, 1.23.3
PACKSTRUCT(struct sl_bt_ead_nonce_s {
  sl_bt_ead_randomizer_t  randomizer;
  sl_bt_ead_iv_t          iv;
});

/// Advertising and Scan Response data struct, Core v5.3, Vol 3, Part C, S. 11
PACKSTRUCT(struct sl_bt_ead_ad_structure_s {
  uint8_t                 length;
  uint8_t                 ad_type;
  sl_bt_ead_randomizer_t  *randomizer;
  uint8_t                 *ad_data;
  sl_bt_ead_mic_t         *mic;
});

/// EAD Randomizer size
#define SL_BT_EAD_RANDOMIZER_SIZE       sizeof(sl_bt_ead_randomizer_t)

/// EAD Key Material size
#define SL_BT_EAD_KEY_MATERIAL_SIZE     sizeof(struct sl_bt_ead_key_material_s)

/// EAD Session Key size
#define SL_BT_EAD_SESSION_KEY_SIZE      sizeof(sl_bt_ead_session_key_t)

/// EAD Nonce size
#define SL_BT_EAD_NONCE_SIZE            sizeof(struct sl_bt_ead_nonce_s)

/// EAD IV size
#define SL_BT_EAD_IV_SIZE               sizeof(sl_bt_ead_iv_t)

/// EAD Message Integrity Check size
#define SL_BT_EAD_MIC_SIZE              sizeof(sl_bt_ead_mic_t)

/// Advertising Data - header length field size
#define SL_BT_EAD_LENGTH_FIELD_SIZE     sizeof(uint8_t)

/// Advertising Data - header AD Type field size
#define SL_BT_EAD_TYPE_FIELD_SIZE       sizeof(uint8_t)

/// Advertising Data header size, Core Ver.5.3, Vol 3. Part C, Fig.11.1
#define SL_BT_EAD_HEADER_SIZE             (SL_BT_EAD_LENGTH_FIELD_SIZE \
                                           + SL_BT_EAD_TYPE_FIELD_SIZE)

/// EAD Message full packet size overhead
#define SL_BT_EAD_PACKET_OVERHEAD         (SL_BT_EAD_RANDOMIZER_SIZE \
                                           + SL_BT_EAD_MIC_SIZE      \
                                           + SL_BT_EAD_HEADER_SIZE)

/// EAD Message packet size overhead without the length field
#define SL_BT_EAD_PACKET_REDUCED_OVERHEAD (SL_BT_EAD_RANDOMIZER_SIZE \
                                           + SL_BT_EAD_MIC_SIZE      \
                                           + SL_BT_EAD_TYPE_FIELD_SIZE)

/// Encrypted Data AD Type
#define SL_BT_ENCRYPTED_DATA_AD_TYPE      0x31

/// B1 block, octet 2 (header) for EAD encryption, CSS d11, Part A, 1.23.3
#define SL_BT_ENCRYPTED_DATA_B1_HEADER    0xEA

/// EAD Key Material Characteristics UUID
#define SL_BT_ENCRYPTED_KEY_MATERIAL_UUID 0x2B88

/**************************************************************************//**
 * Update the Randomizer field of the EAD Nonce value with newly generated value
 * @param[in|out] nonce - Pointer to the EAD Nonce struct to be updated
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_randomizer_update(sl_bt_ead_nonce_p nonce);

/**************************************************************************//**
 * Set the Randomizer field of the EAD Nonce value manually to a given value
 * @note Falls back to @ref sl_bt_ead_randomizer_update() if Randomizer is NULL
 * @param[in] randomizer - Value to be set in the Nonce
 * @param[out] nonce - Pointer to the EAD Nonce struct to be updated
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_randomizer_set(sl_bt_ead_randomizer_t randomizer,
                                     sl_bt_ead_nonce_p nonce);

/**************************************************************************//**
 * (Re)initialize the entire Nonce value with the new key material provided
 * @note According to the Supplement to the Bluetooth Core Specification (d11)
 *       Part A, Section 1.23.3: the session key shall be set to a value
 *       determined by a higher layer specification or otherwise negotiated
 *       between the devices that are sending and receiving  the encrypted AD
 *       type. Any session keys with at least 128 bits of entropy may be used.
 *       The byte order of the session key field will be swapped in-place within
 *       the key_material in|out parameter after the invocation!
 *
 * @param[in|out] key_material - Pointer to the key material in the higher layer
 * @param[in] randomizer - Pointer to the desired Randomizer value type or
 *                         NULL. The Nonce will get a new random value during
 *                         the invocation if NULL is passed.
 * @param[out] nonce - Pointer to the complete EAD Nonce structure. Can be
 *                     also omitted by passing NULL, in which case only the
 *                     session key will be prepared. This is useful for in-place
 *                     decryption with @ref sl_bt_ead_unpack_decrypt(), and not
 *                     meant to be used this way, otherwise.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_session_init(sl_bt_ead_key_material_p key_material,
                                   sl_bt_ead_randomizer_t   randomizer,
                                   sl_bt_ead_nonce_p        nonce);

/**************************************************************************//**
 * Encrypt message in-place using EAD encryption
 * @param[in] key_material - Pointer to the key material in the higher layer
 * @param[in] nonce - Pointer to the complete EAD Nonce structure
 * @param[in] length - Length of the data to be encrypted
 * @param[in|out] data - Pointer to the original message, contains encrypted
 *                       message on success.
 * @param[out] mic - Pointer to the mic storage space
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_encrypt(sl_bt_ead_key_material_p key_material,
                              sl_bt_ead_nonce_p        nonce,
                              uint8_t                  length,
                              uint8_t                  *data,
                              sl_bt_ead_mic_t          mic);

/**************************************************************************//**
 * Decrypt message in-place that is encrypted with EAD
 * @param[in] key_material - Pointer to the key material in the higher layer
 * @param[in] nonce - Pointer to the (received!) Nonce structure
 * @param[in] mic - Message integrity check value of the given message
 * @param[in] length - Length of the data to be decrypted
 * @param[in|out] data - Pointer to the encrypted message, contains decrypted
 *                       message on success.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_decrypt(sl_bt_ead_key_material_p key_material,
                              sl_bt_ead_nonce_p        nonce,
                              sl_bt_ead_mic_t          mic,
                              uint8_t                  length,
                              uint8_t                  *data);

/**************************************************************************//**
 * Unpack advertising data that is encrypted with EAD and decrypt the message
 * in place.
 * @param[in] key_material - Pointer to the key material in the higher layer
 * @param[in|out] data - Reference of the pointer to the full encrypted message
 *                       in Advertising, Periodic Advertising, and Scan Response
 *                       data format specified by Core v5.3, Vol 3, Part C,
 *                       Section 11. Will be updated to the address to the
 *                       decrypted message on success.
 * @param[out] length - Length of the decrypted data
 * @note: This function obfuscates the input data since every operation is done
 *        in place for the best possible speed. If the input data memory is
 *        allocated on the heap, then its original address and size has to be
 *        kept for proper deallocation. Consequently, it's also the caller's
 *        responsibility to make a copy of the resulting decrypted message if
 *        needed, before freeing up the storage space.
 *        Using this method instead of calling @ref sl_bt_ead_unpack_ad_data and
 *        then @ref sl_bt_ead_decrypt can be slightly faster, but also
 *        requires more care when used.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_unpack_decrypt(sl_bt_ead_key_material_p key_material,
                                     uint8_t                  **data,
                                     uint8_t                  *length);

/**************************************************************************//**
 * Pack encrypted EAD AD_Data to Advertising, Periodic Advertising, and Scan
 * Response data format specified by Core v5.3, Vol 3, Part C, Section 11
 * @param[in] ad_info - Pointer to the AD Data structure to be packed
 * @param[in|out] size - In: size of the EAD Data buffer, out: packed length
 * @param[out] pack_buf - Pointer to the complete EAD Data buffer
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_pack_ad_data(sl_bt_ead_ad_structure_p ad_info,
                                   uint8_t         *size,
                                   uint8_t         *pack_buf);

/**************************************************************************//**
 * Unpack encrypted EAD Data from Advertising, Periodic Advertising, and Scan
 * Response data format specified by Core v5.3, Vol 3, Part C, Section 11
 * @param[in] packed_data - Pointer to the incoming EAD Data
 * @param[in|out] ad_info - Pointer to the AD Data struct for unpacked results.
 *                          The 'length' parameter in the struct must be pre-set
 *                          to the 'ad_data' buffer size.
 * @return sl_status_t
 *****************************************************************************/
sl_status_t sl_bt_ead_unpack_ad_data(uint8_t                  *packed_data,
                                     sl_bt_ead_ad_structure_p ad_info);

#ifdef __cplusplus
};
#endif

/** @} (end addtogroup ead_core) */
#endif // SL_BT_EAD_CORE_H
