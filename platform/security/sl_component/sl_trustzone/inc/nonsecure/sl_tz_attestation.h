/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone attestation functions.
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

#ifndef SL_TZ_ATTESTATION_H
#define SL_TZ_ATTESTATION_H

#include "psa/crypto_types.h"
#include "psa/initial_attestation.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Get attestation public key.
 *
 * \details NOTE: On non-Vault-high devices,
 *                if the attestation key is not already generated,
 *                a call to this function will generate the attestation key
 *                and store it in ITS before returning the public key.
 *                0xFFFFFFFFFFFFFFFF is the UID used to store the attestation key.
 *                If this UID are already occupied, the pre-existing data will be
 *                overwritten unless the content is protected by the "write-once" ITS flag.
 *
 * \param[out] key_buffer        Buffer to store the attestation public key.
 *                               The buffer must be word aligned.
 * \param[in]  key_size          Size of the key buffer.
 *
 * \return      A status indicating the success/failure of the operation
 */
psa_status_t sl_tz_attestation_get_public_key(uint8_t *key_buffer,
                                              size_t key_size);

#ifdef __cplusplus
}
#endif

#endif // SL_TZ_ATTESTATION_H
