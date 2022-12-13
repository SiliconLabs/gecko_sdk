/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure SE Manager service.
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

#ifndef __SLI_TZ_SERVICE_SE_MANAGER_H__
#define __SLI_TZ_SERVICE_SE_MANAGER_H__

#include "psa/client.h"

#include "em_device.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sli_tz_funcs_sids_autogen.h"

//------------------------------------------------------------------------------
// Function declarations

psa_status_t sli_tz_se_check_se_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_apply_se_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_upgrade_status_se_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_check_host_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_apply_host_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_upgrade_status_host_image(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_init_otp_key(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_read_pubkey(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_init_otp(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_read_otp(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_se_version(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_debug_lock_status(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_apply_debug_lock(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_otp_version(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);

// VSE only.
#if defined(CRYPTOACC_PRESENT)
psa_status_t sli_tz_se_read_executed_command(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_ack_command(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif // CRYPTOACC_PRESENT

// HSE only.
#if defined(SEMAILBOX_PRESENT)
psa_status_t sli_tz_se_get_status(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_serialnumber(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_enable_secure_debug(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_disable_secure_debug(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_set_debug_options(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_erase_device(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_disable_device_erase(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_challenge(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_roll_challenge(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_open_debug(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_read_cert_size(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_read_cert(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
psa_status_t sli_tz_se_write_user_data(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_erase_user_data(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
psa_status_t sli_tz_se_get_reset_cause(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_1
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
psa_status_t sli_tz_se_disable_tamper(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
psa_status_t sli_tz_se_get_tamper_reset_cause(psa_invec *in_vec, size_t in_len, psa_outvec *out_vec, size_t out_len);
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG >= 3
#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
#endif // SEMAILBOX_PRESENT

#ifdef __cplusplus
}
#endif

#endif // __SLI_TZ_SERVICE_SE_MANAGER_H__
