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

#include "sl_psa_crypto.h"

#include "sli_psa_driver_features.h"

// -----------------------------------------------------------------------------
// Global functions

void sl_psa_set_key_lifetime_with_location_preference(
  psa_key_attributes_t *attributes,
  psa_key_persistence_t persistence,
  psa_key_location_t preferred_location)
{
  psa_key_location_t selected_location = PSA_KEY_LOCATION_LOCAL_STORAGE;

  switch (preferred_location) {
    // The underlying values for wrapped and built-in keys are the same. In
    // order to avoid compiler errors, we therefore use #elif in order to make
    // sure that we do not get identical switch labels.
    #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
    case SL_PSA_KEY_LOCATION_WRAPPED:
      selected_location = SL_PSA_KEY_LOCATION_WRAPPED;
      break;
    #elif defined(SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS)
    case SL_PSA_KEY_LOCATION_BUILTIN:
      selected_location = SL_PSA_KEY_LOCATION_BUILTIN;
      break;
    #endif

    default:
      // Use the already set PSA_KEY_LOCATION_LOCAL_STORAGE.
      break;
  }

  psa_key_lifetime_t lifetime =
    PSA_KEY_LIFETIME_FROM_PERSISTENCE_AND_LOCATION(persistence,
                                                   selected_location);
  psa_set_key_lifetime(attributes, lifetime);
}

psa_key_location_t sl_psa_get_most_secure_key_location(void)
{
  #if defined(SLI_PSA_DRIVER_FEATURE_WRAPPED_KEYS)
  return SL_PSA_KEY_LOCATION_WRAPPED;
  #else
  return PSA_KEY_LOCATION_LOCAL_STORAGE;
  #endif
}
