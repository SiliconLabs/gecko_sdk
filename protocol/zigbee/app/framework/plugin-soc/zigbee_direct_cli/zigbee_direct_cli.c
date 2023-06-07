/***************************************************************************//**
 * @file zigbee_direct_cli.c
 * @brief Zigbee Direct - CLI code
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "hal.h"
#include "ember.h"
#include "af.h"
#include "sl_cli.h"
#ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "sl_zigbee_debug_print.h"
#endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#include "zigbee_direct_common.h"
#include "app/framework/security/af-security.h"

void sli_zigbee_direct_print_keys(void)
{
  EmberKeyData basic_key;
  tokTypeMfgInstallationCode tok_install_code;

  sl_zigbee_core_debug_println("Zigbee Direct Interface State: %d", sl_zigbee_direct_interface_state);
  sl_zigbee_core_debug_println("Zigbee Direct Anonymous Join Timeout: %d sec", sl_zigbee_direct_anonymous_join_timeout_sec);

  sl_zigbee_direct_calculate_basic_key(sl_zvd_eui, emberKeyContents(&basic_key));
  sl_zigbee_core_debug_print("Basic Key:");
  emberAfPrintZigbeeKey(emberKeyContents(&basic_key));
  sl_zigbee_core_debug_println("");

  sl_zigbee_core_debug_print("Admin Key:");
  emberAfPrintZigbeeKey(admin_key);
  sl_zigbee_core_debug_println("");

  halCommonGetMfgToken(&tok_install_code, TOKEN_MFG_INSTALLATION_CODE);
  sli_zigbee_af_install_code_to_key(tok_install_code.value, 18, &basic_key);
  sl_zigbee_core_debug_print("Install Code based Key:");
  emberAfPrintZigbeeKey(emberKeyContents(&basic_key));
  sl_zigbee_core_debug_println("");
}

void sl_zigbee_direct_reset_outgoing_counter(void)
{
  outgoing_counter = 0;
  sl_zigbee_direct_anonymous_join_timeout_sec = 0;
  halCommonSetToken(TOKEN_PLUGIN_ZDD_JOIN_TIMEOUT, &sl_zigbee_direct_anonymous_join_timeout_sec);
  sl_zigbee_core_debug_println("Outgoing frame counter was reset.");
}

void sl_zigbee_direct_set_anonymous_join_timeout(sl_cli_command_arg_t *arguments)
{
  uint32_t timeout = (uint32_t)sl_cli_get_argument_uint32(arguments, 0);
  if (timeout > 0x100000) {
    sl_zigbee_core_debug_println("Cannot set timeout above 0x100000.");
    return;
  }

  sl_zigbee_direct_anonymous_join_timeout_sec = timeout;
  sl_zigbee_core_debug_println("sl_zigbee_direct_anonymous_join_timeout_sec was set to %d sec.", timeout);
}
