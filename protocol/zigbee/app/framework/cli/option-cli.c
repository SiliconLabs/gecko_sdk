/***************************************************************************//**
 * @file
 * @brief CLI commands various options.
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

#include "af.h"

// This is needed to bring in the emberAfGetBindingTableSize() prototype.
#include "app/framework/util/af-main.h"
#include "app/framework/security/af-security.h"
#include "stack/include/zigbee-security-manager.h"
#include "stack/include/zigbee-device-stack.h"

void sli_zigbee_af_cli_service_discovery_callback(const EmberAfServiceDiscoveryResult* result)
{
#if ((defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)) \
  || (defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT)))
  if (!emberAfHaveDiscoveryResponseStatus(result->status)) {
    // Do nothing
  } else if (result->zdoRequestClusterId == MATCH_DESCRIPTORS_REQUEST) {
    const EmberAfEndpointList* epList = (const EmberAfEndpointList*)result->responseData;
    sl_zigbee_app_debug_println("Match %py from 0x%04X, ep %d",
                                "discover",
                                result->matchAddress,
                                epList->list[0]);
  } else if (result->zdoRequestClusterId == NETWORK_ADDRESS_REQUEST) {
    sl_zigbee_app_debug_println("NWK Address response: 0x%04X", result->matchAddress);
  } else if (result->zdoRequestClusterId == IEEE_ADDRESS_REQUEST) {
    const uint8_t* eui64ptr = (uint8_t*)(result->responseData);
    emberAfAppPrint("IEEE Address response: ");
    emberAfPrintBigEndianEui64(eui64ptr);
    sl_zigbee_app_debug_println("");
  } else {
    // MISRA requires ..else if.. to have a terminating else.
  }

  if (result->status != EMBER_AF_BROADCAST_SERVICE_DISCOVERY_RESPONSE_RECEIVED) {
    sl_zigbee_app_debug_println("Service %sy done.",
                                "discover");
  }
#endif //((defined(EMBER_AF_PRINT_ENABLE) && defined(EMBER_AF_PRINT_APP)) || (defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT)))
}

static EmberNodeId discoveryTargetNodeId = EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS;

#include "app/util/serial/sl_zigbee_command_interpreter.h"
// Common include files:
//many of the variables are defined here
#include "app/framework/util/common.h"

void optionPrintRxCommand(sl_cli_command_arg_t *arguments);
void optionBindingTablePrintCommand(sl_cli_command_arg_t *arguments);

// option binding-table print
void optionBindingTablePrintCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  EmberBindingTableEntry result;

  const char * typeStrings[] = {
    "EMPTY",
    "UNICA",
    "M2ONE",
    "MULTI",
    "?    ",
  };
  uint8_t bindings = 0;

  sl_zigbee_core_debug_println("#  type   nwk  loc   rem   clus   node   eui");
  for (i = 0; i < emberAfGetBindingTableSize(); i++) {
    EmberStatus status = emberGetBinding(i, &result);
    if (status == EMBER_SUCCESS) {
      if (result.type > EMBER_MULTICAST_BINDING) {
        result.type = 4;  // last entry in the string list above
      }
      if (result.type != EMBER_UNUSED_BINDING) {
        bindings++;
        sl_zigbee_core_debug_print("%d: ", i);
        sl_zigbee_core_debug_print("%s", typeStrings[result.type]);
        sl_zigbee_core_debug_print("  %d    0x%04X  0x%04X  0x%04X 0x%04X ",
                                   result.networkIndex,
                                   result.local,
                                   result.remote,
                                   result.clusterId,
                                   emberGetBindingRemoteNodeId(i));
        emberAfAppDebugExec(emberAfPrintBigEndianEui64(result.identifier));
        sl_zigbee_core_debug_print("\n");
      }
    } else {
      sl_zigbee_core_debug_print("emberGetBinding Error: 0x%2X\n", status);
      emberAfAppFlush();
    }
    emberAfAppFlush();
  }
  sl_zigbee_core_debug_println("%d of %d bindings used",
                               bindings,
                               emberAfGetBindingTableSize());
}

// option binding-table clear
void optionBindingTableClearCommand(sl_cli_command_arg_t *arguments)
{
  emberClearBindingTable();
}

// option print-rx-msgs [enable/disable]
void optionPrintRxCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t position = sl_cli_get_command_count(arguments) - 1;

  uint8_t command_first_character = sl_cli_get_command_string(arguments, position)[0];

  if (command_first_character == 'e') {
    emberAfPrintReceivedMessages = true;
    sl_zigbee_core_debug_println("enabled print");
  } else {
    emberAfPrintReceivedMessages = false;
    sl_zigbee_core_debug_println("disabled print");
  }
}

// option register
void optionRegisterCommand(sl_cli_command_arg_t *arguments)
{
  emberAfRegistrationStartCallback();
}

void optionDiscoveryTargetCommand(sl_cli_command_arg_t *arguments)
{
  discoveryTargetNodeId = sl_cli_get_argument_uint16(arguments, 0);
}

// option disc <profileId> <clusterId>
void optionDiscoverCommand(sl_cli_command_arg_t *arguments)
{
  EmberAfProfileId profileId = sl_cli_get_argument_uint16(arguments, 0);
  EmberAfClusterId clusterId = sl_cli_get_argument_uint16(arguments, 1);
  emberAfFindDevicesByProfileAndCluster(discoveryTargetNodeId,
                                        profileId,
                                        clusterId,
                                        EMBER_AF_SERVER_CLUSTER_DISCOVERY,
                                        sli_zigbee_af_cli_service_discovery_callback);
}

// option apsretry on/off/...
void optionApsRetryCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t position = sl_cli_get_command_count(arguments) - 1;

  uint8_t command_first_character = sl_cli_get_command_string(arguments, position)[1];

  if ( command_first_character == 'e' ) {
    emberAfSetRetryOverride(EMBER_AF_RETRY_OVERRIDE_NONE);
  } else if ( command_first_character == 'n' ) {
    emberAfSetRetryOverride(EMBER_AF_RETRY_OVERRIDE_SET);
  } else if ( command_first_character == 'f' ) {
    emberAfSetRetryOverride(EMBER_AF_RETRY_OVERRIDE_UNSET);
  } else {
    // MISRA requires ..else if.. to have a terminating else.
  }
}

// option security aps <off | on>
void optionApsSecurityCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t position = sl_cli_get_command_count(arguments) - 1;

  uint8_t command_first_character = sl_cli_get_command_string(arguments, position)[1];
  sli_zigbee_af_test_aps_security_override = (command_first_character == 'f'
                                              ? APS_TEST_SECURITY_DISABLED
                                              : APS_TEST_SECURITY_ENABLED);
}

// option link <index> <eui64 in big endian format> <key in big endian format>
void optionLinkCommand(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 partnerEUI64;
  EmberKeyData newKey;
  sl_status_t status;
  //uint8_t i;
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  sl_zigbee_copy_eui64_arg(arguments, 1, partnerEUI64, true);
  sl_zigbee_copy_hex_arg((arguments), 2, emberKeyContents((&newKey)), EMBER_ENCRYPTION_KEY_SIZE, true);
  status = sl_zb_sec_man_import_link_key(index,
                                         partnerEUI64,
                                         (sl_zb_sec_man_key_t*)&newKey);
  //temporary casting while EmberStatus type is still around
  EmberStatus status_ember = ((status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_KEY_TABLE_INVALID_ADDRESS);
  UNUSED_VAR(status_ember);
  emberAfAppDebugExec(sli_zigbee_af_print_status("add link key", status_ember));
  sl_zigbee_app_debug_println("");
  emberAfCoreFlush();
}

// option install-code <index> <eui64> <install code>
void optionInstallCodeCommand(sl_cli_command_arg_t *arguments)
{
#if (defined(EMBER_AF_HAS_SECURITY_PROFILE_SE_TEST) \
  || defined(EMBER_AF_HAS_SECURITY_PROFILE_SE_FULL) \
  || defined (EMBER_AF_HAS_SECURITY_PROFILE_Z3))

  EmberEUI64 eui64;
  EmberKeyData key;
  EmberStatus status;
  uint8_t code[16 + 2]; // 6, 8, 12, or 16 bytes plus two-byte CRC
  uint8_t length;

  length = sl_zigbee_copy_hex_arg(arguments, 2, code, sizeof(code), false);

  // Convert the install code to a key.
  status = sli_zigbee_af_install_code_to_key(code, length, &key);

  if (EMBER_SUCCESS != status) {
    if (EMBER_SECURITY_DATA_INVALID == status) {
      sl_zigbee_app_debug_println("ERR: Calculated CRC does not match");
    } else if (EMBER_BAD_ARGUMENT == status) {
      sl_zigbee_app_debug_println("ERR: Install Code must be 8, 10, 14, or 18 bytes in "
                                  "length");
    } else {
      sl_zigbee_app_debug_println("ERR: AES-MMO hash failed: 0x%x", status);
    }
    return;
  }

  sl_zigbee_copy_eui64_arg(arguments, 1, eui64, true);

  #ifndef EMBER_AF_HAS_SECURITY_PROFILE_Z3
  // Add the key to the link key table.

  sl_status_t import_status;
  import_status = sl_zb_sec_man_import_link_key(sl_cli_get_argument_uint8(arguments, 0),     // index
                                                eui64,
                                                (sl_zb_sec_man_key_t*) &key);
  status = ((import_status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_KEY_TABLE_INVALID_ADDRESS);
  emberAfAppDebugExec(sli_zigbee_af_print_status("add link key", status));

  sl_zigbee_app_debug_println("");
  emberAfAppFlush();
  #else
  // Add the key to the transient key table.
  // This will be used while the DUT joins.
  if (EMBER_SUCCESS == status) {
    sl_status_t key_status = sl_zb_sec_man_import_transient_key(eui64, (sl_zb_sec_man_key_t*)&key);
    status = ((key_status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_NO_BUFFERS);
    emberAfAppDebugExec(sli_zigbee_af_print_status("Set joining link key", status));
    sl_zigbee_app_debug_println("");
    emberAfAppFlush();
  }
  #endif

#else
  sl_zigbee_app_debug_println("This command only supports the Z3 or SE application profile.");
#endif
}

// option binding-table set <index> <cluster> <local ep> <remote ep> <EUI>
void optionBindingTableSetCommand(sl_cli_command_arg_t *arguments)
{
  EmberBindingTableEntry entry;
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 2);
  EmberStatus status = emberAfPushEndpointNetworkIndex(endpoint);
  if (status == EMBER_SUCCESS) {
    entry.type = EMBER_UNICAST_BINDING;
    entry.clusterId = (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 1);
    entry.local = endpoint;
    entry.remote = sl_cli_get_argument_uint8(arguments, 3);
    sl_zigbee_copy_eui64_arg(arguments, 4, entry.identifier, true);
    entry.networkIndex = emberGetCurrentNetwork();
    status = emberSetBinding(index, &entry);
    (void) emberAfPopNetworkIndex();
  }
  sl_zigbee_app_debug_println("set bind %d: 0x%02x", index, status);
}
