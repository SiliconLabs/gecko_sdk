/***************************************************************************//**
 * @file
 * @brief TrustZone secure SE Manager service (non-secure side).
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

#include "sli_tz_ns_interface.h"
#include "sli_tz_s_interface.h"

#include "sli_tz_util.h"
#include "sli_tz_service_se_manager.h"
#include "sl_se_manager.h"
#include "sl_se_manager_util.h"

#include "em_device.h"

//------------------------------------------------------------------------------
// Function definitions

/***************************************************************************//**
 * Dummy implementation for init.
 ******************************************************************************/
sl_status_t sl_se_init(void)
{
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Dummy implementation for deinit.
 ******************************************************************************/
sl_status_t sl_se_deinit(void)
{
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Validate SE firmware image.
 ******************************************************************************/
sl_status_t sl_se_check_se_image(sl_se_command_context_t *cmd_ctx,
                                 void *image_addr)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_CHECKSEIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { image_addr, sizeof(image_addr) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Apply SE firmware image.
 ******************************************************************************/
sl_status_t sl_se_apply_se_image(sl_se_command_context_t *cmd_ctx,
                                 void *image_addr)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_APPLYSEIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { image_addr, sizeof(image_addr) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Get upgrade status of SE firmware image.
 ******************************************************************************/
sl_status_t sl_se_get_upgrade_status_se_image(sl_se_command_context_t *cmd_ctx,
                                              uint32_t *status,
                                              uint32_t *prev_version)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETUPGRADESTATUSSEIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { status, sizeof(uint32_t) },
    { prev_version, sizeof(uint32_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Validate Host firmware image.
 ******************************************************************************/
sl_status_t sl_se_check_host_image(sl_se_command_context_t *cmd_ctx,
                                   void *image_addr,
                                   uint32_t size)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_CHECKHOSTIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { image_addr, size },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Apply Host firmware image.
 ******************************************************************************/
sl_status_t sl_se_apply_host_image(sl_se_command_context_t *cmd_ctx,
                                   void *image_addr,
                                   uint32_t size)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_APPLYHOSTIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { image_addr, size },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Get upgrade status of Host firmware image.
 ******************************************************************************/
sl_status_t sl_se_get_upgrade_status_host_image(sl_se_command_context_t *cmd_ctx,
                                                uint32_t *status,
                                                uint32_t *prev_version)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETUPGRADESTATUSHOSTIMAGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { status, sizeof(uint32_t) },
    { prev_version, sizeof(uint32_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Initialize key to be stored in the SE OTP flash.
 ******************************************************************************/
sl_status_t sl_se_init_otp_key(sl_se_command_context_t *cmd_ctx,
                               sl_se_device_key_type_t key_type,
                               void *key,
                               uint32_t num_bytes)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_INITOTPKEY_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { &key_type, sizeof(sl_se_device_key_type_t) },
    { key, num_bytes },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Read a public key stored in the SE.
 ******************************************************************************/
sl_status_t sl_se_read_pubkey(sl_se_command_context_t *cmd_ctx,
                              sl_se_device_key_type_t key_type,
                              void *key,
                              uint32_t num_bytes)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_READPUBKEY_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { &key_type, sizeof(sl_se_device_key_type_t) },
  };
  sli_tz_outvec out_vec[] = {
    { key, num_bytes },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Initialize SE OTP configuration.
 ******************************************************************************/
sl_status_t sl_se_init_otp(sl_se_command_context_t *cmd_ctx,
                           sl_se_otp_init_t *otp_init)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_INITOTP_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { otp_init, sizeof(sl_se_otp_init_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Read SE OTP configuration.
 ******************************************************************************/
sl_status_t sl_se_read_otp(sl_se_command_context_t *cmd_ctx,
                           sl_se_otp_init_t *otp_settings)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_READOTP_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { otp_settings, sizeof(sl_se_otp_init_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Read the SE firmware version.
 ******************************************************************************/
sl_status_t sl_se_get_se_version(sl_se_command_context_t *cmd_ctx,
                                 uint32_t *version)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETSEVERSION_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { version, sizeof(uint32_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Returns the current debug lock configuration.
 ******************************************************************************/
sl_status_t sl_se_get_debug_lock_status(sl_se_command_context_t *cmd_ctx,
                                        sl_se_debug_status_t *debug_status)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETDEBUGLOCKSTATUS_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { debug_status, sizeof(sl_se_debug_status_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Enables the debug lock for the part.
 ******************************************************************************/
sl_status_t sl_se_apply_debug_lock(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_APPLYDEBUGLOCK_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Read the OTP firmware version of the SE module.
 ******************************************************************************/
sl_status_t sl_se_get_otp_version(sl_se_command_context_t *cmd_ctx,
                                  uint32_t *version)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETOTPVERSION_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { version, sizeof(uint32_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

#if defined(CRYPTOACC_PRESENT)

/***************************************************************************//**
 * From VSE mailbox read which command, if any, was executed.
 ******************************************************************************/
sl_status_t sl_se_read_executed_command(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_READEXECUTEDCOMMAND_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Acknowledge and get status and output data of a completed command.
 ******************************************************************************/
sl_status_t sl_se_ack_command(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_ACKCOMMAND_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

#endif //defined(CRYPTOACC_PRESENT)

#if defined(SEMAILBOX_PRESENT)

/***************************************************************************//**
 * Returns the current boot status, versions and system configuration.
 ******************************************************************************/
sl_status_t sl_se_get_status(sl_se_command_context_t *cmd_ctx,
                             sl_se_status_t *status)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETSTATUS_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { status, sizeof(sl_se_status_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Read the serial number of the SE module.
 ******************************************************************************/
sl_status_t sl_se_get_serialnumber(sl_se_command_context_t *cmd_ctx,
                                   void *serial)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETSERIALNUMBER_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    // Based on the function API, we know that the serial buffer should be 16 b.
    { serial, 16 },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Enables the secure debug functionality.
 ******************************************************************************/
sl_status_t sl_se_enable_secure_debug(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_ENABLESECUREDEBUG_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Disables the secure debug functionality.
 ******************************************************************************/
sl_status_t sl_se_disable_secure_debug(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_DISABLESECUREDEBUG_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Set options on the debug interface.
 ******************************************************************************/
sl_status_t sl_se_set_debug_options(sl_se_command_context_t *cmd_ctx,
                                    const sl_se_debug_options_t *debug_options)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_SETDEBUGOPTIONS_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { debug_options, sizeof(sl_se_debug_options_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Performs a device mass erase and debug unlock.
 ******************************************************************************/
sl_status_t sl_se_erase_device(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_ERASEDEVICE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Disabled device erase functionality.
 ******************************************************************************/
sl_status_t sl_se_disable_device_erase(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_DISABLEDEVICEERASE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Request challenge from SE which can be used to open debug access.
 ******************************************************************************/
sl_status_t sl_se_get_challenge(sl_se_command_context_t *cmd_ctx,
                                sl_se_challenge_t challenge)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETCHALLENGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { challenge, sizeof(sl_se_challenge_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Invalidate current challenge and make a new challenge.
 ******************************************************************************/
sl_status_t sl_se_roll_challenge(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_ROLLCHALLENGE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Unlock debug access using certificate signed with challenge.
 ******************************************************************************/
sl_status_t sl_se_open_debug(sl_se_command_context_t *cmd_ctx,
                             void *cert, uint32_t len,
                             const sl_se_debug_options_t *debug_options)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_OPENDEBUG_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { cert, len },
    { debug_options, sizeof(sl_se_debug_options_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_1)

/***************************************************************************//**
 * Writes data to User Data section in MTP. Write data must be aligned to
 * word size and contain a number of bytes that is divisable by four.
 ******************************************************************************/
sl_status_t sl_se_write_user_data(sl_se_command_context_t *cmd_ctx,
                                  uint32_t offset,
                                  void *data,
                                  uint32_t num_bytes)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_WRITEUSERDATA_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { &offset, sizeof(uint32_t) },
    { data, num_bytes },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Erases User Data section in MTP.
 ******************************************************************************/
sl_status_t sl_se_erase_user_data(sl_se_command_context_t *cmd_ctx)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_ERASEUSERDATA_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

/***************************************************************************//**
 * Read the EMU->RSTCAUSE after a tamper reset. This function should be called
 * if EMU->RSTCAUSE has been cleared upon boot.
 ******************************************************************************/
sl_status_t sl_se_get_reset_cause(sl_se_command_context_t *cmd_ctx,
                                  uint32_t* reset_cause)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETRESETCAUSE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { reset_cause, sizeof(uint32_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

#endif // _SILICON_LABS_32B_SERIES_2_CONFIG_1

/***************************************************************************//**
 * Read size of stored certificates in SE.
 ******************************************************************************/
sl_status_t sl_se_read_cert_size(sl_se_command_context_t *cmd_ctx,
                                 sl_se_cert_size_type_t *cert_size)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_READCERTSIZE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
  };
  sli_tz_outvec out_vec[] = {
    { cert_size, sizeof(sl_se_cert_size_type_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

/***************************************************************************//**
 * Read stored certificates in SE.
 ******************************************************************************/
sl_status_t sl_se_read_cert(sl_se_command_context_t *cmd_ctx,
                            sl_se_cert_type_t cert_type,
                            void *cert,
                            uint32_t num_bytes)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_READCERT_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { &cert_type, sizeof(sl_se_cert_type_t) },
  };
  sli_tz_outvec out_vec[] = {
    { cert, num_bytes },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)out_vec,
                                                   IOVEC_LEN(out_vec));
}

#if (_SILICON_LABS_SECURITY_FEATURE == _SILICON_LABS_SECURITY_FEATURE_VAULT)

/***************************************************************************//**
 * Temporarily disable tamper configuration using certificate signed with
 * challenge.
 ******************************************************************************/
sl_status_t sl_se_disable_tamper(sl_se_command_context_t *cmd_ctx,
                                 void *cert,
                                 uint32_t len,
                                 sl_se_tamper_signals_t tamper_signals)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_DISABLETAMPER_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { cert, len },
    { &tamper_signals, sizeof(sl_se_tamper_signals_t) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

#if (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)

/***************************************************************************//**
 *   Read the latest cached tamper reset cause. The returned value is the index
 *   of the tamper source that caused a reset.
 *   Requires SE version 2.2.1 or above.
 ******************************************************************************/
sl_status_t sl_se_get_tamper_reset_cause(sl_se_command_context_t *cmd_ctx,
                                         bool *was_tamper_reset,
                                         uint32_t *reset_cause)
{
  sli_tz_fn_id fn_id = SLI_TZ_SERVICE_SE_MANAGER_GETTAMPERRESETCAUSE_SID;
  sli_tz_invec in_vec[] = {
    { .base = &fn_id, .len = sizeof(sli_tz_fn_id) },
    { cmd_ctx, sizeof(sl_se_command_context_t) },
    { was_tamper_reset, sizeof(bool*) },
    { reset_cause, sizeof(uint32_t*) },
  };

  return (sl_status_t)sli_tz_ns_interface_dispatch((sli_tz_veneer_fn)sli_tz_s_interface_dispatch_se_manager,
                                                   (uint32_t)in_vec,
                                                   IOVEC_LEN(in_vec),
                                                   (uint32_t)NULL,
                                                   0);
}

#endif // _SILICON_LABS_32B_SERIES_2_CONFIG >= 3
#endif // _SILICON_LABS_SECURITY_FEATURE_VAULT
#endif // SEMAILBOX_PRESENT
