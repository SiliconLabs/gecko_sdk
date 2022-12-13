/***************************************************************************//**
 * @file
 * @brief Implements NCP-side secure EZSP functionality.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include PLATFORM_HEADER

#include "stack/include/ember.h"
#include "hal/hal.h"
#include "app/util/ezsp/ezsp-protocol.h"
#include "stack/include/zigbee-security-manager.h"

//------------------------------------------------------------------------------
// Internal functions and handlers.

EzspStatus emSecureEzspInit(void)
{
  if (emSecureEzspIsSecurityKeySet()) {
    emSecureEzspSetSecurityType(SECURE_EZSP_SECURITY_TYPE_TEMPORARY);

    sl_zb_sec_man_context_t context;
    sl_zb_sec_man_init_context(&context);
    context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY;
    //TODO: Remove the call to export_key here, replace RAM storage of secure EZSP key with
    //pre-loading a key held by security manager
    sl_zb_sec_man_export_key(&context, (sl_zb_sec_man_key_t *)emSecureEzspGetSecurityKey());
    sl_zb_sec_man_load_key_context(&context);
    emSecureEzspSetState(SECURE_EZSP_STATE_PARAMETERS_PENDING);
  }
  return EZSP_SUCCESS;
}

EzspStatus emSecureEzspSetSecurityKey(EmberKeyData *securityKey)
{
  if (emSecureEzspIsSecurityKeySet()) {
    return EZSP_ERROR_SECURITY_KEY_ALREADY_SET;
  }
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY;
  sl_zb_sec_man_import_key(&context, (sl_zb_sec_man_key_t *)securityKey);
  emSecureEzspSetState(SECURE_EZSP_STATE_PARAMETERS_PENDING);

  MEMMOVE(emberKeyContents(emSecureEzspGetSecurityKey()),
          emberKeyContents(securityKey),
          EMBER_ENCRYPTION_KEY_SIZE);
  return EZSP_SUCCESS;
}

EzspStatus emSecureEzspReset(void)
{
  // Reset temporary token
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_SECURE_EZSP_KEY;
  sl_zb_sec_man_delete_key(&context);

  // Leave network
  emberLeaveNetwork();

  // Deinit secure EZSP parameters
  emSecureEzspDeInit();

  return EZSP_SUCCESS;
}
