/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure attestation service.
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

#ifndef __SLI_TZ_ATTESTATION_VENEERS_H__
#define __SLI_TZ_ATTESTATION_VENEERS_H__

#include <stdint.h>
#include <stdbool.h>

#include "sli_tz_util.h"
#include "psa/crypto_types.h"
#include "psa/client.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sli_tz_funcs_sids_autogen.h"

//-------------------------------------
// Full services (IOVEC usage)

/**
 * \brief Get attestation public key.
 */
psa_status_t sli_tz_attestation_get_public_key(psa_invec in_vec[],
                                               size_t in_len,
                                               psa_outvec out_vec[],
                                               size_t out_len);

/**
 * \brief Get IAT attestation token.
 */
psa_status_t sli_initial_attest_get_token(psa_invec in_vec[],
                                          size_t in_len,
                                          psa_outvec out_vec[],
                                          size_t out_len);

/**
 * \brief  Get IAT attestation token size.
 */
psa_status_t sli_initial_attest_get_token_size(psa_invec in_vec[],
                                               size_t in_len,
                                               psa_outvec out_vec[],
                                               size_t out_len);

#ifdef __cplusplus
}
#endif

#endif // __SLI_TZ_ATTESTATION_VENEERS_H__
