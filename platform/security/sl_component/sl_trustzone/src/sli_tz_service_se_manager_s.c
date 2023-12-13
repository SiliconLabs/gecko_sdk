/***************************************************************************//**
 * @file
 * @brief TrustZone secure SE Manager service (secure side).
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

#include <stddef.h>
#include <stdint.h>

#include "sli_tz_util.h"
#include "sli_tz_iovec_check.h"

#include "sli_tz_service_se_manager.h"
#include "sl_se_manager.h"
#include "sl_se_manager_util.h"

#include "em_device.h"

//------------------------------------------------------------------------------
// Macros

/**
 * \brief Validate the number of IOVECs passed.
 */
#define _TZ_SE_MANAGER_ASSERT_N_IOVECS(expected_invecs, expected_outvecs) \
  SLI_TZ_IOVEC_ASSERT_N_IOVECS(expected_invecs, expected_outvecs, SL_STATUS_INVALID_PARAMETER)

/**
 * \brief Validate the number of IOVECs passed.
 */
#define _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(iovec, expected_struct_type) \
  SLI_TZ_IOVEC_ASSERT_STRUCT_SIZE(iovec, expected_struct_type, SL_STATUS_INVALID_PARAMETER)

//------------------------------------------------------------------------------
// Function definitions

sl_status_t sli_tz_se_check_se_image(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *image_addr = (void *)in_vec[2].base;

  // Output arguments
  (void)out_vec;

  return sl_se_check_se_image(cmd_ctx, image_addr);
}

sl_status_t sli_tz_se_apply_se_image(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *image_addr = (void *)in_vec[2].base;

  // Output arguments
  (void)out_vec;

  return sl_se_apply_se_image(cmd_ctx, image_addr);
}

sl_status_t sli_tz_se_get_upgrade_status_se_image(sli_tz_invec in_vec[],
                                                  size_t in_len,
                                                  sli_tz_outvec out_vec[],
                                                  size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], uint32_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[3], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  uint32_t *status = (uint32_t *)in_vec[2].base;
  uint32_t *prev_version = (uint32_t *)in_vec[3].base;

  // Output arguments
  (void)out_vec;

  return sl_se_get_upgrade_status_se_image(cmd_ctx, status, prev_version);
}

sl_status_t sli_tz_se_check_host_image(sli_tz_invec in_vec[],
                                       size_t in_len,
                                       sli_tz_outvec out_vec[],
                                       size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *image_addr = (void *)in_vec[2].base;
  uint32_t size = in_vec[2].len;

  // Output arguments
  (void)out_vec;

  return sl_se_check_host_image(cmd_ctx, image_addr, size);
}

sl_status_t sli_tz_se_apply_host_image(sli_tz_invec in_vec[],
                                       size_t in_len,
                                       sli_tz_outvec out_vec[],
                                       size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *image_addr = (void *)in_vec[2].base;
  uint32_t size = in_vec[2].len;

  // Output arguments
  (void)out_vec;

  return sl_se_apply_host_image(cmd_ctx, image_addr, size);
}

sl_status_t sli_tz_se_get_upgrade_status_host_image(sli_tz_invec in_vec[],
                                                    size_t in_len,
                                                    sli_tz_outvec out_vec[],
                                                    size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], uint32_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[3], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  uint32_t *status = (uint32_t *)in_vec[2].base;
  uint32_t *prev_version = (uint32_t *)in_vec[3].base;

  // Output arguments
  (void)out_vec;

  return sl_se_get_upgrade_status_host_image(cmd_ctx,
                                             status,
                                             prev_version);
}

sl_status_t sli_tz_se_init_otp_key(sli_tz_invec in_vec[],
                                   size_t in_len,
                                   sli_tz_outvec out_vec[],
                                   size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], sl_se_device_key_type_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  sl_se_device_key_type_t key_type =
    *((sl_se_device_key_type_t *)in_vec[2].base);
  void *key = (void *)in_vec[3].base;
  uint32_t num_bytes = in_vec[3].len;

  // Output arguments
  (void)out_vec;

  return sl_se_init_otp_key(cmd_ctx, key_type, key, num_bytes);
}

sl_status_t sli_tz_se_read_pubkey(sli_tz_invec in_vec[],
                                  size_t in_len,
                                  sli_tz_outvec out_vec[],
                                  size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], sl_se_device_key_type_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  sl_se_device_key_type_t key_type =
    *((sl_se_device_key_type_t *)in_vec[2].base);

  // Output arguments
  void *key = out_vec[0].base;
  uint32_t num_bytes = out_vec[0].len;

  return sl_se_read_pubkey(cmd_ctx, key_type, key, num_bytes);
}

sl_status_t sli_tz_se_init_otp(sli_tz_invec in_vec[],
                               size_t in_len,
                               sli_tz_outvec out_vec[],
                               size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], sl_se_otp_init_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  sl_se_otp_init_t *otp_init = (sl_se_otp_init_t *)in_vec[2].base;

  // Output arguments
  (void)out_vec;

  return sl_se_init_otp(cmd_ctx, otp_init);
}

sl_status_t sli_tz_se_read_otp(sli_tz_invec in_vec[],
                               size_t in_len,
                               sli_tz_outvec out_vec[],
                               size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], sl_se_otp_init_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  sl_se_otp_init_t *otp_settings = (sl_se_otp_init_t *)out_vec[0].base;

  return sl_se_read_otp(cmd_ctx, otp_settings);
}

sl_status_t sli_tz_se_get_se_version(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  uint32_t *version = (uint32_t *)out_vec[0].base;

  return sl_se_get_se_version(cmd_ctx, version);
}

sl_status_t sli_tz_se_get_debug_lock_status(sli_tz_invec in_vec[],
                                            size_t in_len,
                                            sli_tz_outvec out_vec[],
                                            size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], sl_se_debug_status_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  sl_se_debug_status_t *debug_status = (sl_se_debug_status_t *)out_vec[0].base;

  return sl_se_get_debug_lock_status(cmd_ctx, debug_status);
}

sl_status_t sli_tz_se_apply_debug_lock(sli_tz_invec in_vec[],
                                       size_t in_len,
                                       sli_tz_outvec out_vec[],
                                       size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_apply_debug_lock(cmd_ctx);
}

sl_status_t sli_tz_se_get_otp_version(sli_tz_invec in_vec[],
                                      size_t in_len,
                                      sli_tz_outvec out_vec[],
                                      size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  uint32_t *version = (uint32_t *)out_vec[0].base;

  return sl_se_get_otp_version(cmd_ctx, version);
}

#if defined(CRYPTOACC_PRESENT)

sl_status_t sli_tz_se_read_executed_command(sli_tz_invec in_vec[],
                                            size_t in_len,
                                            sli_tz_outvec out_vec[],
                                            size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_read_executed_command(cmd_ctx);
}

sl_status_t sli_tz_se_ack_command(sli_tz_invec in_vec[],
                                  size_t in_len,
                                  sli_tz_outvec out_vec[],
                                  size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_ack_command(cmd_ctx);
}

#endif // CRYPTOACC_PRESENT

#if defined(SEMAILBOX_PRESENT)

sl_status_t sli_tz_se_get_status(sli_tz_invec in_vec[],
                                 size_t in_len,
                                 sli_tz_outvec out_vec[],
                                 size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], sl_se_status_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  sl_se_status_t *status = (sl_se_status_t *)out_vec[0].base;

  return sl_se_get_status(cmd_ctx, status);
}

sl_status_t sli_tz_se_get_serialnumber(sli_tz_invec in_vec[],
                                       size_t in_len,
                                       sli_tz_outvec out_vec[],
                                       size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Based on the function API, we know that the serial buffer should be 16 b.
  EFM_ASSERT(out_vec[0].len == 16);

  // Output arguments
  void *serial = out_vec[0].base;

  return sl_se_get_serialnumber(cmd_ctx, serial);
}

sl_status_t sli_tz_se_enable_secure_debug(sli_tz_invec in_vec[],
                                          size_t in_len,
                                          sli_tz_outvec out_vec[],
                                          size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_enable_secure_debug(cmd_ctx);
}

sl_status_t sli_tz_se_disable_secure_debug(sli_tz_invec in_vec[],
                                           size_t in_len,
                                           sli_tz_outvec out_vec[],
                                           size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_disable_secure_debug(cmd_ctx);
}

sl_status_t sli_tz_se_set_debug_options(sli_tz_invec in_vec[],
                                        size_t in_len,
                                        sli_tz_outvec out_vec[],
                                        size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], sl_se_debug_options_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  const sl_se_debug_options_t *debug_options =
    (sl_se_debug_options_t *)in_vec[2].base;

  // Output arguments
  (void)out_vec;

  return sl_se_set_debug_options(cmd_ctx, debug_options);
}

sl_status_t sli_tz_se_erase_device(sli_tz_invec in_vec[],
                                   size_t in_len,
                                   sli_tz_outvec out_vec[],
                                   size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_erase_device(cmd_ctx);
}

sl_status_t sli_tz_se_disable_device_erase(sli_tz_invec in_vec[],
                                           size_t in_len,
                                           sli_tz_outvec out_vec[],
                                           size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_disable_device_erase(cmd_ctx);
}

sl_status_t sli_tz_se_get_challenge(sli_tz_invec in_vec[],
                                    size_t in_len,
                                    sli_tz_outvec out_vec[],
                                    size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], sl_se_challenge_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  sl_se_challenge_t *challenge = out_vec[0].base;

  return sl_se_get_challenge(cmd_ctx, *challenge);
}

sl_status_t sli_tz_se_roll_challenge(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_roll_challenge(cmd_ctx);
}

sl_status_t sli_tz_se_open_debug(sli_tz_invec in_vec[],
                                 size_t in_len,
                                 sli_tz_outvec out_vec[],
                                 size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[3], sl_se_debug_options_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *cert = (void *)in_vec[2].base;
  uint32_t len = in_vec[2].len;
  sl_se_debug_options_t *debug_options =
    (sl_se_debug_options_t *)in_vec[3].base;

  // Output arguments
  (void)out_vec;

  return sl_se_open_debug(cmd_ctx, cert, len, debug_options);
}

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)

sl_status_t sli_tz_se_write_user_data(sli_tz_invec in_vec[],
                                      size_t in_len,
                                      sli_tz_outvec out_vec[],
                                      size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  uint32_t offset = *((uint32_t *)in_vec[2].base);
  void *data = (void *)in_vec[3].base;
  uint32_t num_bytes = in_vec[3].len;

  // Output arguments
  (void)out_vec;

  return sl_se_write_user_data(cmd_ctx, offset, data, num_bytes);
}

sl_status_t sli_tz_se_erase_user_data(sli_tz_invec in_vec[],
                                      size_t in_len,
                                      sli_tz_outvec out_vec[],
                                      size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  (void)out_vec;

  return sl_se_erase_user_data(cmd_ctx);
}

sl_status_t sli_tz_se_get_reset_cause(sli_tz_invec in_vec[],
                                      size_t in_len,
                                      sli_tz_outvec out_vec[],
                                      size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], uint32_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  uint32_t *reset_cause = (uint32_t *)out_vec[0].base;

  return sl_se_get_reset_cause(cmd_ctx, reset_cause);
}

#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_1

sl_status_t sli_tz_se_read_cert_size(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(2, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(out_vec[0], sl_se_cert_size_type_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;

  // Output arguments
  sl_se_cert_size_type_t *cert_size = (sl_se_cert_size_type_t *)out_vec[0].base;

  return sl_se_read_cert_size(cmd_ctx, cert_size);
}

sl_status_t sli_tz_se_read_cert(sli_tz_invec in_vec[],
                                size_t in_len,
                                sli_tz_outvec out_vec[],
                                size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(3, 1);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], sl_se_cert_type_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  sl_se_cert_type_t cert_type = *((sl_se_cert_type_t *)in_vec[2].base);

  // Output arguments
  void *cert = out_vec[0].base;
  uint32_t num_bytes = out_vec[0].len;

  return sl_se_read_cert(cmd_ctx, cert_type, cert, num_bytes);
}

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

sl_status_t sli_tz_se_disable_tamper(sli_tz_invec in_vec[],
                                     size_t in_len,
                                     sli_tz_outvec out_vec[],
                                     size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[3], sl_se_tamper_signals_t);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  void *cert = (void *)in_vec[2].base;
  uint32_t len = in_vec[2].len;
  sl_se_tamper_signals_t tamper_signals =
    *((sl_se_tamper_signals_t*)in_vec[3].base);

  // Output arguments
  (void)out_vec;

  return sl_se_disable_tamper(cmd_ctx, cert, len, tamper_signals);
}

#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)

/***************************************************************************//**
 *   Read the latest cached tamper reset cause. The returned value is the index
 *   of the tamper source that caused a reset.
 *   Requires SE version 2.2.1 or above.
 ******************************************************************************/
sl_status_t sli_tz_se_get_tamper_reset_cause(sli_tz_invec in_vec[],
                                             size_t in_len,
                                             sli_tz_outvec out_vec[],
                                             size_t out_len)
{
  _TZ_SE_MANAGER_ASSERT_N_IOVECS(4, 0);

  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[1], sl_se_command_context_t);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[2], bool*);
  _TZ_SE_MANAGER_ASSERT_IOVEC_STRUCT_SIZE(in_vec[3], uint32_t*);

  // Input arguments
  sl_se_command_context_t *cmd_ctx = (sl_se_command_context_t *)in_vec[1].base;
  bool *was_tamper_reset = (bool *)in_vec[2].base;
  uint32_t *reset_cause = (uint32_t*) in_vec[3].base;

  // Output arguments
  (void)out_vec;

  return sl_se_get_tamper_reset_cause(cmd_ctx, was_tamper_reset, reset_cause);
}
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG >= 3
#endif // VAULT
#endif // SEMAILBOX_PRESENT
