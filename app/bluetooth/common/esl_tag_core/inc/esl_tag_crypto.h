/***************************************************************************//**
 * @file
 * @brief ESL Tag basic cryptographic interface declarations
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef ESL_TAG_CRYPTO_H
#define ESL_TAG_CRYPTO_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>

/**************************************************************************//**
 * Message encryption function
 * @param[in]     msg Pointer to the message to be encrypted
 * @param[in|out] len Pointer to a variable containing the length of the
 *                    message to be encrypted [in bytes]
 * @return void* Pointer to the encrypted message on success, NULL otherwise.
 * @note         Also changes the value of *len to the resulting length on
 *               successful operation.
 *****************************************************************************/
void* esl_core_encrypt_message(void *msg, uint8_t *len);

/**************************************************************************//**
 * Message decryption function
 * @param[in]     msg Pointer to the message to be decrypted
 * @param[in|out] len Pointer to a variable containing the length of the
 *                    message to be decrypted [in bytes]
 * @return void* Pointer to the decrypted message on success, NULL otherwise.
 * @note         Also changes the value of *len to the resulting length on
 *               successful operation.
 *****************************************************************************/
void* esl_core_decrypt_message(void *msg, uint8_t *len);
/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_CRYPTO_H
