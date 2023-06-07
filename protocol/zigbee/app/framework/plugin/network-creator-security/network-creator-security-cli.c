/***************************************************************************//**
 * @file
 * @brief CLI for the Network Creator Security plugin.
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

#include "app/framework/include/af.h"
#include "network-creator-security.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "network-creator-security-config.h"
#include "stack/include/zigbee-security-manager.h"

// plugin network_creator_security [open|close]
void sli_zigbee_af_network_creator_security_open_or_close_network_command(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  uint8_t position = sl_cli_get_command_count(arguments) - 1;
  bool open = memcmp(sl_cli_get_command_string(arguments, position), "open", strlen("open")) == 0;

  status = (open
            ? emberAfPluginNetworkCreatorSecurityOpenNetwork()
            : emberAfPluginNetworkCreatorSecurityCloseNetwork());

  sl_zigbee_core_debug_println("%s: %s network: 0x%02X",
                               EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_PLUGIN_NAME,
                               (open ? "Open" : "Close"),
                               status);
}

extern EmberKeyData distributedKey;

void sli_zigbee_af_network_creator_security_set_joining_link_key_command(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 eui64;
  sl_zb_sec_man_key_t keyData;
  sl_status_t status;
  size_t len = 16;
  sl_zigbee_copy_eui64_arg(arguments, 0, eui64, true);
  //emberCopyKeyArgument(1, &keyData);
  uint8_t *ptr_string = sl_cli_get_argument_hex(arguments, 1, &len);
  MEMSET(keyData.key, 0, EMBER_ENCRYPTION_KEY_SIZE);
  MEMMOVE(keyData.key, ptr_string, EMBER_ENCRYPTION_KEY_SIZE); // Is the padding correct?

  status = sl_zb_sec_man_import_transient_key(eui64,
                                              &keyData);

  emberAfCorePrintln("%s: %s: 0x%X",
                     EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_PLUGIN_NAME,
                     "Set joining link key",
                     status);
}

void sli_zigbee_af_network_creator_security_clear_joining_link_key_command(sl_cli_command_arg_t *arguments)
{
  emberClearTransientLinkKeys();

  emberAfCorePrintln("%s: %s: 0x%X",
                     EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_PLUGIN_NAME,
                     "Clear joining link keys",
                     EMBER_SUCCESS);
}

void sli_zigbee_af_network_creator_security_open_network_with_key_command(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 eui64;
  EmberKeyData keyData;
  EmberStatus status;
  size_t len = 16;
  sl_zigbee_copy_eui64_arg(arguments, 0, eui64, true);
  //emberCopyKeyArgument(1, &keyData);
  uint8_t *ptr_string = sl_cli_get_argument_hex(arguments, 1, &len);
  MEMSET(keyData.contents, 0, EMBER_ENCRYPTION_KEY_SIZE);
  MEMMOVE(keyData.contents, ptr_string, EMBER_ENCRYPTION_KEY_SIZE);  // Is the padding correct?

  status = emberAfPluginNetworkCreatorSecurityOpenNetworkWithKeyPair(eui64, keyData);

  emberAfCorePrintln("%s: Open network: 0x%X",
                     EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_PLUGIN_NAME,
                     status);
}

void sli_zigbee_af_network_creator_security_configure_distributed_key(sl_cli_command_arg_t *arguments)
{
  size_t len = 16;
  uint8_t *ptr_string = sl_cli_get_argument_hex(arguments, 0, &len);
  MEMSET(distributedKey.contents, 0, EMBER_ENCRYPTION_KEY_SIZE);
  MEMMOVE(distributedKey.contents, ptr_string, EMBER_ENCRYPTION_KEY_SIZE); // Is the padding correct?
}
