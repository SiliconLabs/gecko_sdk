/***************************************************************************//**
 * @file
 * @brief Interface definition for AES functionality.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SILABS_AES_H
#define SILABS_AES_H

// This function loads the 16 byte key into the AES hardware accelerator.
void sli_util_load_key_into_core(const uint8_t* key);

// This function retrieves the 16 byte key from the AES hardware accelerator.
void sli_zigbee_get_key_from_core(uint8_t* key);

// This function encrypts the 16 byte plaintext block with the previously-loaded
// 16 byte key using the AES hardware accelerator.
// The resulting 16 byte ciphertext is written to the block parameter,
// overwriting the plaintext.
void sli_util_stand_alone_encrypt_block(uint8_t* block);

// sli_zigbee_aes_encrypt performs AES encryption in ECB mode on the plaintext pointed to
// by the block parameter, using the key pointed to by the key parameter, and
// places the resulting ciphertext into the 16 bytes of memory pointed to by the
// block parameter (overwriting the supplied plaintext).  Any existing key is
// destroyed.
void sli_zigbee_aes_encrypt(uint8_t* block, const uint8_t* key);

// sli_zigbee_aes_decrypt performs AES decryption in ECB mode on the ciphertext pointed to
// by the block parameter, using the key pointed to by the key parameter, and
// places the resulting plaintext into the 16 bytes of memory pointed to by the
// block parameter (overwriting the supplied cyphertext).  Any existing key is
// destroyed.
void sli_zigbee_aes_decrypt(uint8_t* block, const uint8_t* key);

#endif //__AES_H__
