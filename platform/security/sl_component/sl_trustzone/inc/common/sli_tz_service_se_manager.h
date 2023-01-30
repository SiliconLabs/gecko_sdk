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

#include "sli_tz_util.h"
#include "sl_status.h"
#include "em_device.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sli_tz_funcs_sids_autogen.h"

//------------------------------------------------------------------------------
// Function declarations

sl_status_t sli_tz_se_check_se_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_apply_se_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_upgrade_status_se_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_check_host_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_apply_host_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_upgrade_status_host_image(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_init_otp_key(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_read_pubkey(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_init_otp(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_read_otp(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_se_version(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_debug_lock_status(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_apply_debug_lock(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_otp_version(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);

// VSE only.
#if defined(CRYPTOACC_PRESENT)
sl_status_t sli_tz_se_read_executed_command(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_ack_command(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#endif // CRYPTOACC_PRESENT

// HSE only.
#if defined(SEMAILBOX_PRESENT)
sl_status_t sli_tz_se_get_status(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_serialnumber(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_enable_secure_debug(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_disable_secure_debug(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_set_debug_options(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_erase_device(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_disable_device_erase(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_challenge(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_roll_challenge(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_open_debug(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_read_cert_size(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_read_cert(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)
sl_status_t sli_tz_se_write_user_data(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_erase_user_data(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
sl_status_t sli_tz_se_get_reset_cause(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_1
#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)
sl_status_t sli_tz_se_disable_tamper(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
sl_status_t sli_tz_se_get_tamper_reset_cause(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG >= 3
#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
#endif // SEMAILBOX_PRESENT

#ifdef __cplusplus
}
#endif

#endif // __SLI_TZ_SERVICE_SE_MANAGER_H__
