/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone attestation service (non-secure side).
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

#include "sli_tz_service_attestation.h"
#include "sli_tz_ns_interface.h"
#include "sli_tz_s_interface.h"

//------------------------------------------------------------------------------
// Function definitions

psa_status_t sl_tz_attestation_get_public_key(uint8_t *key_buffer,
                                              size_t key_size)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_ATTESTATION_GET_PUBLIC_KEY_SID;
  psa_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
  };
  psa_outvec out_vec[] = {
    { .base = key_buffer, .len = key_size }
  };

  return (psa_status_t)sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn)sli_tz_s_interface_dispatch_attestation,
    (uint32_t)in_vec,
    IOVEC_LEN(in_vec),
    (uint32_t)out_vec,
    IOVEC_LEN(out_vec));
}

psa_status_t
psa_initial_attest_get_token(const uint8_t *auth_challenge,
                             size_t         challenge_size,
                             uint8_t       *token_buf,
                             size_t         token_buf_size,
                             size_t        *token_size)
{
  psa_status_t status = PSA_ERROR_GENERIC_ERROR;
  sli_tz_fn_id fn_id = INITIAL_ATTEST_GET_TOKEN_SID;
  psa_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { .base = auth_challenge, .len = challenge_size },
  };
  psa_outvec out_vec[] = {
    { .base = token_buf, .len = token_buf_size },
    { .base = token_size, .len = sizeof(token_size) }
  };

  status = (psa_status_t)sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn)sli_tz_s_interface_dispatch_attestation,
    (uint32_t)in_vec,
    IOVEC_LEN(in_vec),
    (uint32_t)out_vec,
    IOVEC_LEN(out_vec));

  return status;
}

psa_status_t
psa_initial_attest_get_token_size(size_t challenge_size,
                                  size_t *token_size)
{
  sli_tz_fn_id fn_id = INITIAL_ATTEST_GET_TOKEN_SIZE_SID;
  psa_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { .base = &challenge_size, .len = sizeof(challenge_size) },
  };
  psa_outvec out_vec[] = {
    { .base = token_size, .len = sizeof(token_size) }
  };

  return (psa_status_t)sli_tz_ns_interface_dispatch(
    (sli_tz_veneer_fn)sli_tz_s_interface_dispatch_attestation,
    (uint32_t)in_vec,
    IOVEC_LEN(in_vec),
    (uint32_t)out_vec,
    IOVEC_LEN(out_vec));
}
