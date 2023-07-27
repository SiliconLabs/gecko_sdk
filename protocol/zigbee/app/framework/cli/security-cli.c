/***************************************************************************//**
 * @file
 * @brief Routines to initiate key establishment, handle key establishment callbacks,
 * and print info about the security keys on the device.
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
#include "app/framework/util/af-main.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "stack/include/zigbee-security-manager.h"

#ifdef EZSP_HOST
 #define setTcRejoinsUsingWellKnownKeyAllowed(allow) \
  (void)ezspSetPolicy(EZSP_TC_REJOINS_USING_WELL_KNOWN_KEY_POLICY, (allow))
 #define setTcRejoinsUsingWellKnownKeyTimeout(timeout) \
  (void)ezspSetConfigurationValue(EZSP_CONFIG_TC_REJOINS_USING_WELL_KNOWN_KEY_TIMEOUT_S, (timeout))
#else // SoC
extern uint16_t sli_zigbee_allow_tc_rejoins_using_well_known_key_timeout_sec;
 #define setTcRejoinsUsingWellKnownKeyAllowed(allow) \
  emberSetTcRejoinsUsingWellKnownKeyAllowed((allow))
 #define setTcRejoinsUsingWellKnownKeyTimeout(timeout) \
  sli_zigbee_allow_tc_rejoins_using_well_known_key_timeout_sec = (timeout)
#endif

EmberKeyData cliPreconfiguredLinkKey = DUMMY_KEY;
EmberKeyData cliNetworkKey           = DUMMY_KEY;

static uint32_t getOutgoingApsFrameCounter(void)
{
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_aps_key_metadata_t key_data;
  sl_zb_sec_man_init_context(&context);

  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK;

  if (sl_zb_sec_man_get_aps_key_info(&context, &key_data) != SL_STATUS_OK) {
    return 0xFFFFFFFFUL;
  }
  return key_data.outgoing_frame_counter;
}

uint8_t printTransientKeyTable(void)
{
  sl_status_t status;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_aps_key_metadata_t key_info;
  uint8_t index = 0;

  sl_zigbee_core_debug_println("Index IEEE Address         NWKIndex  In FC     TTL(s) Flag    Key    ");

  status = sl_zb_sec_man_export_transient_key_by_index(index,
                                                       &context,
                                                       &plaintext_key,
                                                       &key_info);

  while (status == EMBER_SUCCESS) {
    sl_zigbee_core_debug_print("%d     ", index);
    emberAfCoreDebugExec(emberAfPrintBigEndianEui64(context.eui64));
    sl_zigbee_core_debug_print("  %d       ", context.multi_network_index);
    sl_zigbee_core_debug_print("  %08X  ", key_info.incoming_frame_counter);
    sl_zigbee_core_debug_print("0x%04X", key_info.ttl_in_seconds);
    sl_zigbee_core_debug_print(" 0x%04X  ", key_info.bitmask);
    emberAfPrintZigbeeKey((const uint8_t*)&(plaintext_key.key));
    sl_zigbee_core_debug_println("");
    emberAfCoreFlush();

    index += 1;
    status = sl_zb_sec_man_export_transient_key_by_index(index,
                                                         &context,
                                                         &plaintext_key,
                                                         &key_info);
  }

  return index;
}

uint8_t printKeyTable(bool preconfiguredKey)
{
  uint8_t i;
  uint8_t entriesUsed = 0;
  uint8_t loopCount = (preconfiguredKey ? 1 : emberAfGetKeyTableSize());

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_aps_key_metadata_t key_data;
  sl_zb_sec_man_init_context(&context);

  sl_zigbee_core_debug_println("Index IEEE Address         In FC     Type  Auth  Key");

  for (i = 0; i < loopCount; i++) {
    sl_zb_sec_man_context_t context;
    sl_zb_sec_man_init_context(&context);
    sl_zb_sec_man_key_t plaintext_key;
    sl_zb_sec_man_aps_key_metadata_t metadata;

    if (preconfiguredKey) {
      i = 0xFE; // last
      context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK;

      // Try to get whatever key type is stored in the pre-configured key slot.
      context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK;
      if ( SL_STATUS_OK
           != sl_zb_sec_man_export_key(&context, &plaintext_key) ) {
        continue;
      }
    } else if ( SL_STATUS_OK != sl_zb_sec_man_export_link_key_by_index(i, &context, &plaintext_key, &metadata) ) {
      continue;
    } else {
      // MISRA requires ..else if.. to have a terminating else.
    }

    (void)sl_zb_sec_man_get_aps_key_info(&context, &key_data);
    context.flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;

    if (!preconfiguredKey) {
      sl_zigbee_core_debug_print("%d     ", i);
    } else {
      sl_zigbee_core_debug_print("-     ");
    }
    context.flags |= ZB_SEC_MAN_FLAG_KEY_INDEX_IS_VALID;
    (void) sl_zb_sec_man_get_aps_key_info(&context, &metadata);
    emberAfCoreDebugExec(emberAfPrintBigEndianEui64(context.eui64));
    sl_zigbee_core_debug_print("  %08X  ", metadata.incoming_frame_counter);
    sl_zigbee_core_debug_print("%c     %c     ",
                               (metadata.bitmask & EMBER_KEY_IS_AUTHENTICATION_TOKEN
                                ? 'A'
                                : 'L'),
                               (metadata.bitmask & EMBER_KEY_IS_AUTHORIZED
                                ? 'y'
                                : 'n'));

    emberAfPrintZigbeeKey((const uint8_t *)&(plaintext_key.key));

    emberAfCoreFlush();
    entriesUsed++;
  }

  return entriesUsed;
}

void printKeyInfo(void)
{
  uint8_t entriesUsed;

  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;
  sl_zb_sec_man_network_key_info_t network_key_info;

  sl_zb_sec_man_init_context(&context);
  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;

#ifndef EMBER_AF_HAS_SECURITY_PROFILE_NONE
  {
    EmberMfgSecurityStruct config;
    if (EMBER_SUCCESS == emberGetMfgSecurityConfig(&config)) {
      if (!(config.keySettings & EMBER_KEY_PERMISSIONS_READING_ALLOWED)) {
        sl_zigbee_core_debug_println("");
        sl_zigbee_core_debug_print("WARNING:  READING OF KEY VALUES DISABLED BY MFG TOKEN");
        sl_zigbee_core_debug_println("");
        sl_zigbee_core_debug_println("");
        emberAfCoreFlush();
      }
    }
  }
#endif

  if ( SL_STATUS_OK != sl_zb_sec_man_export_key(&context, &plaintext_key)) {
    MEMSET(&plaintext_key.key, 0xFF, sizeof(sl_zb_sec_man_key_t));
  }

  (void)sl_zb_sec_man_get_network_key_info(&network_key_info);
  sl_zigbee_core_debug_println("%s out FC: %08X",
                               "NWK Key",
                               network_key_info.network_key_frame_counter);
  sl_zigbee_core_debug_println("%s seq num: 0x%x",
                               "NWK Key",
                               network_key_info.network_key_sequence_number);
  sl_zigbee_core_debug_print("%s: ", "NWK Key");
  emberAfPrintZigbeeKey(plaintext_key.key);

  sl_zigbee_core_debug_println("%s out FC: %08x",
                               "Link Key",
                               getOutgoingApsFrameCounter());

  sl_zigbee_core_debug_println("TC %s ", "Link Key");
  emberAfCoreFlush();
  printKeyTable(true);

  sl_zigbee_core_debug_println("%s Table", "Link Key");
  emberAfCoreFlush();
  entriesUsed = printKeyTable(false);
  UNUSED_VAR(entriesUsed);

  sl_zigbee_core_debug_println("%d/%d entries used.",
                               entriesUsed,
                               emberAfGetKeyTableSize());
  emberAfCoreFlush();

  sl_zigbee_core_debug_println("%s Table", "Transient Key");
  emberAfCoreFlush();

  entriesUsed = printTransientKeyTable();
  UNUSED_VAR(entriesUsed);

  sl_zigbee_core_debug_println("%d entr%s consuming %d packet buffer%s.",
                               entriesUsed,
                               entriesUsed > 1 ? "ies" : "y",
                               entriesUsed,
                               entriesUsed > 1 ? "s" : "");
  emberAfCoreFlush();
}

void optionSecurityAllowTrustCenterRejoinUsingWellKnownKey(sl_cli_command_arg_t *arguments)
{
  bool allow = (bool)sl_cli_get_argument_uint8(arguments, 0);
  setTcRejoinsUsingWellKnownKeyAllowed(allow);
  emberAfCorePrintln("Trust Center %p allow trust center rejoins using "
                     "well-known key.",
                     allow
                     ? "WILL"
                     : "WILL NOT");
}

void optionSecurityAllowTrustCenterRejoinUsingWellKnownKeyTimeout(sl_cli_command_arg_t *arguments)
{
  uint16_t timeout = sl_cli_get_argument_uint16(arguments, 0);
  setTcRejoinsUsingWellKnownKeyTimeout(timeout);
  emberAfCorePrintln("Set timeout for Trust Center rejoins using well-known "
                     "link key to %d seconds.",
                     timeout);
}

void optionSecuritySetKeyRequestPolicy(sl_cli_command_arg_t *arguments)
{
#ifdef EZSP_HOST
  uint8_t tcPolicy = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t appPolicy = sl_cli_get_argument_uint8(arguments, 1);

  // The EZSP policies are offset by EZSP_DENY_TC_KEY_REQUESTS and
  // EZSP_DENY_APP_KEY_REQUESTS, respectively
  tcPolicy += EZSP_DENY_TC_KEY_REQUESTS;
  appPolicy += EZSP_DENY_APP_KEY_REQUESTS;

  (void)ezspSetPolicy(EZSP_TC_KEY_REQUEST_POLICY, tcPolicy);
  (void)ezspSetPolicy(EZSP_APP_KEY_REQUEST_POLICY, appPolicy);
#else // EZSP_HOST
  emberTrustCenterLinkKeyRequestPolicy = sl_cli_get_argument_uint8(arguments, 0);
  emberAppLinkKeyRequestPolicy = sl_cli_get_argument_uint8(arguments, 1);
#endif // EZSP_HOST
}

void changeKeyCommand(sl_cli_command_arg_t *arguments)
{
  if (EMBER_NO_NETWORK != emberNetworkState()) {
    emberAfCorePrintln("%pstack must be down.", "ERROR: ");
  } else {
    uint8_t position = sl_cli_get_command_count(arguments) - 1;

    uint8_t command_first_character = sl_cli_get_command_string(arguments, position)[0];
    sl_zigbee_copy_hex_arg((arguments), 0, emberKeyContents((command_first_character == 'l'
                                                             ? &cliPreconfiguredLinkKey
                                                             : &cliNetworkKey)), EMBER_ENCRYPTION_KEY_SIZE, true);
    emberAfDebugPrintln("set key");
  }
}

void getSetMfgToken(sl_cli_command_arg_t *arguments)
{
#ifndef EMBER_AF_HAS_SECURITY_PROFILE_NONE
  EmberMfgSecurityStruct config;
  EmberStatus status;

  if (sl_cli_get_command_string(arguments, 2)[0] == 'g') {
    status = emberGetMfgSecurityConfig(&config);
    if (status == EMBER_SUCCESS) {
      emberAfSecurityPrintln("EmberKeySettings: 0x%04X", config.keySettings);
      emberAfSecurityPrintln("  Permissions: %s",
                             ((config.keySettings & EMBER_KEY_PERMISSIONS_READING_ALLOWED)
                              ? "Reading Allowed"
                              : ((config.keySettings & EMBER_KEY_PERMISSIONS_HASHING_ALLOWED)
                                 ? "Hashing only"
                                 : "NONE")));
    } else {
      emberAfSecurityPrintln("Error: Failed to get config, status: 0x%02X", status);
    }
  } else {
    uint32_t magicNumber = sl_cli_get_argument_uint32(arguments, 0);
    config.keySettings = (EmberKeySettings)sl_cli_get_argument_uint32(arguments, 1);
    status = emberSetMfgSecurityConfig(magicNumber, &config);
  }

  if (status != EMBER_SUCCESS) {
    emberAfSecurityPrintln("Failed: 0x%02X", status);
  }
#else
  emberAfSecurityPrintln("Cannot get/set mfg tokens with no security profile");
#endif // EMBER_AF_HAS_SECURITY_PROFILE_NONE
}
