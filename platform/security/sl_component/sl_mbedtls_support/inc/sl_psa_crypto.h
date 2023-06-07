/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto utility functions.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_PSA_CRYPTO_H
#define SL_PSA_CRYPTO_H

#include "psa/crypto.h"

#include "sl_psa_values.h"

#include <stddef.h>

// -----------------------------------------------------------------------------
// Functions

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * \addtogroup psa_builtin_keys
 *
 * \brief Built-in key mechanism provides access to the keys stored in hardware.
 * It can be accessed using key ID that is in the range
 * [MBEDTLS_PSA_KEY_ID_BUILTIN_MIN, MBEDLTS_PSA_KEY_ID_BUILTIN_MAX].
 *
 *
 * \note Available builtin key IDs vary for different family of devices.
 *       For devices vith VSE see \ref sl_psa_drivers_cryptoacc_builtin_keys ,
 *       and for devices with Secure Engine see \ref sl_psa_drivers_se_builtin_keys .
 * \{
 ******************************************************************************/
/** \} (end addtogroup psa_builtin_keys) */

/***************************************************************************//**
 * \addtogroup key_derivation
 *
 * If single-shot key derivation is used (sl_psa_key_derivation_single_shot),
 * following limitations have to be considered:
 * -# PBKDF2-CMAC is not suported on xG21
 * -# PBKDF2-CMAC is only KDF supported for xG27
 *
 * \{
 ******************************************************************************/
/** \} (end addtogroup key_derivation) */

/***************************************************************************//**
 * \addtogroup sl_psa_drivers
 * \{
 ******************************************************************************/

/***************************************************************************//**
 * @brief
 *   Set the location attribute of a key in PSA Crypto according to a given
 *   persistence level, and a preferred location. If the preferred location is
 *   not available, perhaps because the device does not support this location,
 *   the primary local storage (PSA_KEY_LOCATION_LOCAL_STORAGE) will be used.
 *
 * @param[out] attributes
 *   The attribute structure to write to.
 *
 * @param[in] persistence
 *   The persistence level of the key. If this is #PSA_KEY_PERSISTENCE_VOLATILE,
 *   the key will be volatile, and the key identifier attribute is reset to 0.
 *
 * @param[in] preferred_location
 *   The location of the key. Can be SL_PSA_KEY_LOCATION_WRAPPED,
 *   SL_PSA_KEY_LOCATION_BUILTIN, or PSA_KEY_LOCATION_LOCAL_STORAGE.
 ******************************************************************************/
void sl_psa_set_key_lifetime_with_location_preference(
  psa_key_attributes_t *attributes,
  psa_key_persistence_t persistence,
  psa_key_location_t preferred_location);

/***************************************************************************//**
 * @brief
 *   Get the 'most secure' location attribute of a key usable in this
 *   implementation of PSA Crypto.
 *
 * @return
 *   The 'most secure' usable location of a key. In order of preference, the
 *   following values can be returned: SL_PSA_KEY_LOCATION_WRAPPED,
 *   or PSA_KEY_LOCATION_LOCAL_STORAGE.
 ******************************************************************************/
psa_key_location_t sl_psa_get_most_secure_key_location(void);

/** \} (end addtogroup sl_psa_drivers) */

#ifdef __cplusplus
}
#endif

#endif // SL_PSA_CRYPTO_H
