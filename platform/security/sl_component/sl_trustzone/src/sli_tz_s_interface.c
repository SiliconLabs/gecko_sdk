/***************************************************************************//**
 * @file
 * @brief Silicon Labs TrustZone Secure Library Interface.
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

#if defined(TZ_SERVICE_CONFIG_PRESENT)
  #include "tz_service_config_autogen.h"
#endif

#include "sli_tz_iovec_check.h"
#include "sli_tz_s_interface.h"

#include "sl_assert.h"

#include "tfm_crypto_defs.h"
#include "psa/client.h"

#if defined(TZ_SERVICE_PSA_CRYPTO_PRESENT)
#include "sli_tz_service_psa_crypto.h"
#endif // TZ_SERVICE_PSA_CRYPTO_PRESENT
#include "sli_tz_service_syscfg.h"
#if defined(TZ_SERVICE_NVM3_PRESENT) || defined(TZ_SERVICE_PSA_ITS_PRESENT)
  #include "sli_tz_service_nvm3.h"
#endif // TZ_SERVICE_NVM3_PRESENT || TZ_SERVICE_PSA_ITS_PRESENT
#if defined(TZ_SERVICE_MSC_PRESENT)
  #include "sli_tz_service_msc.h"
  #include "em_msc.h"
#endif // TZ_SERVICE_MSC_PRESENT
#if defined(TZ_SERVICE_PSA_ITS_PRESENT)
  #include "sli_tz_service_its.h"
#endif // TZ_SERVICE_PSA_ITS_PRESENT
#if defined(TZ_SERVICE_SE_MANAGER_PRESENT)
  #include "sli_tz_service_se_manager.h"
#endif // TZ_SERVICE_SE_MANAGER_PRESENT
#if defined(TZ_SERVICE_ATTESTATION_PRESENT)
  #include "sli_tz_service_attestation.h"
#endif // TZ_SERVICE_ATTESTATION_PRESENT

#include "sli_tz_s_interface_funcs_autogen.h"

//------------------------------------------------------------------------------
// Global secure dispatch functions

#if defined(TZ_SERVICE_PSA_CRYPTO_PRESENT)
int32_t sli_tz_s_interface_dispatch_crypto(psa_invec in_vec[],
                                           size_t in_len,
                                           psa_outvec out_vec[],
                                           size_t out_len)
{
  EFM_ASSERT(sizeof(crypto_function_table) / sizeof(crypto_function_table[0])
             == TFM_CRYPTO_SID_MAX);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  const struct tfm_crypto_pack_iovec *iov = iovec_copy.in_vec[0].base;
  uint32_t function_id = iov->sfn_id;
  if (function_id >= TFM_CRYPTO_SID_MAX) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  iovec_fn fn = crypto_function_table[function_id];

  status = fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);

  // For certain functions, the .len field of one of the outvecs is used in
  // order to communicate one of the output values. We therefore have to copy
  // back any potential updates from the outvec copy to the origin living in NS.
  for (size_t i = 0; i < out_len; ++i) {
    out_vec[i].len = iovec_copy.out_vec[i].len;
  }

  return status;
}
#endif // TZ_SERVICE_PSA_CRYPTO_PRESENT

#if defined(TZ_SERVICE_SYSCFG_PRESENT) \
  || defined(TZ_SERVICE_MSC_PRESENT)
int32_t sli_tz_s_interface_dispatch_simple(uint32_t sid,
                                           uint32_t arg)
{
  EFM_ASSERT(sizeof(simple_function_table) / sizeof(simple_function_table[0])
             == SLI_TZ_SIMPLE_MAX_SID);
  EFM_ASSERT(sid < SLI_TZ_SIMPLE_MAX_SID);
  return simple_function_table[sid](arg);
}

int32_t sli_tz_s_interface_dispatch_simple_no_args(uint32_t sid)
{
  EFM_ASSERT(sizeof(simple_function_table_no_args) / sizeof(simple_function_table_no_args[0])
             == SLI_TZ_SIMPLE_NO_ARGS_MAX_SID);
  EFM_ASSERT(sid < SLI_TZ_SIMPLE_NO_ARGS_MAX_SID);
  return simple_function_table_no_args[sid]();
}

#endif //TZ_SERVICE_SYSCFG_PRESENT || TZ_SERVICE_MSC_PRESENT

#if defined(TZ_SERVICE_MSC_PRESENT)
int32_t sli_tz_s_interface_dispatch_msc(sli_tz_invec in_vec[],
                                        size_t in_len,
                                        sli_tz_outvec out_vec[],
                                        size_t out_len)
{
  EFM_ASSERT(sizeof(msc_function_table) / sizeof(msc_function_table[0])
             == SLI_TZ_SERVICE_MSC_MAX_SID);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return mscReturnInvalidAddr;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_MSC_MAX_SID) {
    return mscReturnInvalidAddr;
  }
  iovec_fn fn = msc_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // TZ_SERVICE_MSC_PRESENT
#if defined(TZ_SERVICE_PSA_ITS_PRESENT) \
  || defined(TZ_SERVICE_NVM3_PRESENT)
int32_t sli_tz_s_interface_dispatch_nvm3(sli_tz_invec in_vec[],
                                         size_t in_len,
                                         sli_tz_outvec out_vec[],
                                         size_t out_len)
{
  EFM_ASSERT(sizeof(nvm3_function_table) / sizeof(nvm3_function_table[0])
             == SLI_TZ_SERVICE_NVM3_MAX_SID);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_NVM3_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  iovec_fn fn = nvm3_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // defined(TZ_SERVICE_PSA_ITS_PRESENT) || defined(TZ_SERVICE_NVM3_PRESENT)

#if defined(TZ_SERVICE_PSA_ITS_PRESENT)
int32_t sli_tz_s_interface_dispatch_its(psa_invec in_vec[],
                                        size_t in_len,
                                        psa_outvec out_vec[],
                                        size_t out_len)
{
  EFM_ASSERT(sizeof(its_function_table) / sizeof(its_function_table[0])
             == SLI_TZ_SERVICE_ITS_MAX_SID);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_ITS_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  iovec_fn fn = its_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // TZ_SERVICE_PSA_ITS_PRESENT

#if defined(TZ_SERVICE_SE_MANAGER_PRESENT)
int32_t sli_tz_s_interface_dispatch_se_manager(sli_tz_invec in_vec[],
                                               size_t in_len,
                                               sli_tz_outvec out_vec[],
                                               size_t out_len)
{
  EFM_ASSERT(sizeof(se_manager_function_table) / sizeof(se_manager_function_table[0])
             == SLI_TZ_SERVICE_SE_MANAGER_MAX_SID);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_SE_MANAGER_MAX_SID) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  iovec_fn fn = se_manager_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // TZ_SERVICE_SE_MANAGER_PRESENT

#if defined(TZ_SERVICE_ATTESTATION_PRESENT)
int32_t sli_tz_s_interface_dispatch_attestation(psa_invec in_vec[],
                                                size_t in_len,
                                                psa_outvec out_vec[],
                                                size_t out_len)
{
  EFM_ASSERT(sizeof(attestation_function_table) / sizeof(attestation_function_table[0])
             == SLI_TZ_SERVICE_ATTESTATION_MAX_SID);
  sli_tz_iovec_params_t iovec_copy = { 0 };

  uint32_t status = sli_tz_iovecs_live_in_ns(in_vec,
                                             in_len,
                                             out_vec,
                                             out_len,
                                             &iovec_copy);
  if (status != SLI_TZ_IOVEC_OK) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_ATTESTATION_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  iovec_fn fn = attestation_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // TZ_SERVICE_ATTESTATION_PRESENT
