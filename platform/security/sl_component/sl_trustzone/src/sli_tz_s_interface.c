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

#include <string.h>

#if defined(TZ_SERVICE_CONFIG_PRESENT)
  #include "tz_service_config_autogen.h"
#endif

#include "psa/crypto_types.h"

#include "sli_tz_iovec_check.h"
#include "sli_tz_s_interface.h"

#include "sl_assert.h"

#include "tfm_crypto_defs.h"
#include "psa/client.h"

#if defined(TZ_SERVICE_PSA_CRYPTO_PRESENT)
  #include "sli_tz_service_psa_crypto.h"
#endif
#include "sli_tz_service_syscfg.h"
#if defined(TZ_SERVICE_NVM3_PRESENT) || defined(TZ_SERVICE_PSA_ITS_PRESENT)
  #include "sli_tz_service_nvm3.h"
  #include "nvm3.h"
#endif
#if defined(TZ_SERVICE_MSC_PRESENT)
  #include "sli_tz_service_msc.h"
#endif
#if defined(TZ_SERVICE_PSA_ITS_PRESENT)
  #include "sli_tz_service_its.h"
#endif
#if defined(TZ_SERVICE_SE_MANAGER_PRESENT)
  #include "sli_tz_service_se_manager.h"
  #include "sl_se_manager_types.h"
#endif
#if defined(TZ_SERVICE_ATTESTATION_PRESENT)
  #include "sli_tz_service_attestation.h"
#endif

#include "sli_tz_s_interface_funcs_autogen.h"

//------------------------------------------------------------------------------
// Macros

#if defined(TZ_SERVICE_NVM3_PRESENT)

  #define NVM3_FUNCTION_HAS_INIT_STRUCT_PARAM(function_id) \
  (function_id == SLI_TZ_SERVICE_NVM3_INITDEFAULT_SID      \
   || function_id == SLI_TZ_SERVICE_NVM3_OPEN_SID)

// Only applies to input parameters.
  #define NVM3_FUNCTION_HAS_HANDLE_STRUCT_PARAM(function_id) \
  !(function_id == SLI_TZ_SERVICE_NVM3_INITDEFAULT_SID       \
    || function_id == SLI_TZ_SERVICE_NVM3_DEINITDEFAULT_SID  \
    || function_id == SLI_TZ_SERVICE_NVM3_OPEN_SID           \
    || function_id == SLI_TZ_SERVICE_NVM3_SETERASECOUNT_SID)

#elif defined(TZ_SERVICE_PSA_ITS_PRESENT)

  #define NVM3_FUNCTION_HAS_INIT_STRUCT_PARAM(function_id) \
  (function_id == SLI_TZ_SERVICE_NVM3_INITDEFAULT_SID)

  #define NVM3_FUNCTION_HAS_HANDLE_STRUCT_PARAM(function_id) \
  !(function_id == SLI_TZ_SERVICE_NVM3_INITDEFAULT_SID       \
    || function_id == SLI_TZ_SERVICE_NVM3_DEINITDEFAULT_SID)

#endif // TZ_SERVICE_NVM3_PRESENT

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

#if defined(TZ_SERVICE_PSA_ITS_PRESENT) || defined(TZ_SERVICE_NVM3_PRESENT)
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
    return ECODE_NVM3_ERR_PARAMETER;
  }

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id,
                                  ECODE_NVM3_ERR_PARAMETER);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_NVM3_MAX_SID) {
    return ECODE_NVM3_ERR_PARAMETER;
  }

  // Check that potential nvm3_Init_t struct doesn't contain illegal pointers.
  nvm3_Init_t init_copy = { 0 };
  if (NVM3_FUNCTION_HAS_INIT_STRUCT_PARAM(function_id)) {
    // The init struct is passed in in_vec[1] for all functions using it.
    SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[1], nvm3_Init_t,
                                    ECODE_NVM3_ERR_PARAMETER);

    // Copy the nvm3_Init_t structure into secure RAM in order to make sure that
    // the pointers we're verifying are not modified after we have performed our
    // check (TOCTOU).
    memcpy(&init_copy, iovec_copy.in_vec[1].base, sizeof(nvm3_Init_t));
    iovec_copy.in_vec[1].base = &init_copy;

    status = sli_tz_nvm3_init_struct_points_to_ns(&init_copy);
    if (status != SLI_TZ_IOVEC_OK) {
      return ECODE_NVM3_ERR_PARAMETER;
    }
  }

  // Check that (potential) nvm3_Handle_t struct doesn't contain illegal pointers.
  nvm3_Handle_t handle_copy = { 0 };
  nvm3_Handle_t *passed_handle = (nvm3_Handle_t *)iovec_copy.in_vec[1].base;
  if (NVM3_FUNCTION_HAS_HANDLE_STRUCT_PARAM(function_id)) {
    // The handle struct is passed in in_vec[1] for all functions using it
    // (with the exception of sli_tz_nvm3_open() since it's used as an output
    // there). We don't reach here for that function, though.
    SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[1], nvm3_Handle_t,
                                    ECODE_NVM3_ERR_PARAMETER);

    // We don't need to check the values contained in the handle in case it is
    // the default instance (since that lives in secure RAM which we know the
    // NS app cannot modify). The use of the default instance handler is
    // signalled using a magic value in the nvmAdr member of the handle.
    if (SLI_TZ_SERVICE_NVM3_HANDLE_IS_DEFAULT(passed_handle)) {
      // Replace the dummy handle passed with the actual default handle.
      extern nvm3_Handle_t *nvm3_defaultHandle;
      iovec_copy.in_vec[1].base = nvm3_defaultHandle;
    } else {
      // Copy the nvm3_Handle_t structure into secure RAM in order to make sure
      // that the pointers we're verifying are not modified after we have
      // performed our check (TOCTOU).
      memcpy(&handle_copy, iovec_copy.in_vec[1].base, sizeof(nvm3_Handle_t));
      iovec_copy.in_vec[1].base = &handle_copy;

      status = sli_tz_nvm3_handle_struct_points_to_ns(&handle_copy);
      if (status != SLI_TZ_IOVEC_OK) {
        return ECODE_NVM3_ERR_PARAMETER;
      }
    }
  }

  iovec_fn fn = nvm3_function_table[function_id];
  int32_t ret = fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);

  // We need to update the original handle structure with the changes from
  // our copy, if used.
  if (NVM3_FUNCTION_HAS_HANDLE_STRUCT_PARAM(function_id)
      && !SLI_TZ_SERVICE_NVM3_HANDLE_IS_DEFAULT(passed_handle)) {
    memcpy((void *)in_vec[1].base,
           &handle_copy,
           sizeof(nvm3_Handle_t));
  }

  return ret;
}
#endif // TZ_SERVICE_PSA_ITS_PRESENT || TZ_SERVICE_NVM3_PRESENT

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

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id,
                                  PSA_ERROR_INVALID_ARGUMENT);

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

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id,
                                  SL_STATUS_INVALID_PARAMETER);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_SE_MANAGER_MAX_SID) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // The context struct is passed in in_vec[1] for all functions.
  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[1],
                                  sl_se_command_context_t,
                                  SL_STATUS_INVALID_PARAMETER);

  // Operate on a fresh sl_se_command_context_t structure in secure RAM in order
  // to make sure that the pointers we're installing into it are not modified by
  // the NS application during execution.
  sl_se_command_context_t secure_command_context = SL_SE_COMMAND_CONTEXT_INIT;
  iovec_copy.in_vec[1].base = &secure_command_context;

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

  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec_copy.in_vec[0], sli_tz_fn_id,
                                  PSA_ERROR_INVALID_ARGUMENT);

  sli_tz_fn_id function_id = *((sli_tz_fn_id *)iovec_copy.in_vec[0].base);
  if (function_id >= SLI_TZ_SERVICE_ATTESTATION_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }
  iovec_fn fn = attestation_function_table[function_id];

  return fn(iovec_copy.in_vec, in_len, iovec_copy.out_vec, out_len);
}
#endif // TZ_SERVICE_ATTESTATION_PRESENT

#if defined(TZ_SERVICE_SYSCFG_PRESENT) || defined(TZ_SERVICE_MSC_PRESENT)
int32_t sli_tz_s_interface_dispatch_simple(uint32_t sid,
                                           uint32_t arg)
{
  EFM_ASSERT(sizeof(simple_function_table) / sizeof(simple_function_table[0])
             == SLI_TZ_SIMPLE_MAX_SID);

  if (sid >= SLI_TZ_SIMPLE_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return simple_function_table[sid](arg);
}

int32_t sli_tz_s_interface_dispatch_simple_no_args(uint32_t sid)
{
  EFM_ASSERT(sizeof(simple_function_table_no_args) / sizeof(simple_function_table_no_args[0])
             == SLI_TZ_SIMPLE_NO_ARGS_MAX_SID);

  if (sid >= SLI_TZ_SIMPLE_NO_ARGS_MAX_SID) {
    return PSA_ERROR_INVALID_ARGUMENT;
  }

  return simple_function_table_no_args[sid]();
}
#endif //TZ_SERVICE_SYSCFG_PRESENT || TZ_SERVICE_MSC_PRESENT
