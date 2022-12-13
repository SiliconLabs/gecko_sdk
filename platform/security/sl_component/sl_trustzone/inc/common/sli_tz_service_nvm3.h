/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone secure NVM3 service.
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

#ifndef __SLI_TZ_NVM3_VENEERS_H__
#define __SLI_TZ_NVM3_VENEERS_H__

#include "tfm_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#if defined(TZ_SERVICE_CONFIG_PRESENT)
  #include "tz_service_config_autogen.h"
#endif

#include "sli_tz_funcs_sids_autogen.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
  #include "sl_component_catalog.h"
#endif

//------------------------------------------------------------------------------
// Function declarations

psa_status_t tfm_nvm3_init_default(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_deinit_default(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#if defined(TZ_SERVICE_NVM3_PRESENT)
psa_status_t tfm_nvm3_read_partial_data(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_read_data(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_write_data(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_delete_object(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_open(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_close(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_get_object_info(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_write_counter(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_read_counter(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_increment_counter(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_erase_all(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_get_erase_count(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_set_erase_count(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_repack(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_repack_needed(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_resize(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_enum_objects(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
psa_status_t tfm_nvm3_enum_deleted_objects(sli_tz_invec *in_vec, size_t in_len, sli_tz_outvec *out_vec, size_t out_len);
#endif // defined(TZ_SERVICE_NVM3_PRESENT)

#ifdef __cplusplus
}
#endif

#endif /* __SLI_TZ_NVM3_VENEERS_H__ */
