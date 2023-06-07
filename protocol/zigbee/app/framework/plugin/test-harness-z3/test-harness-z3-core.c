/***************************************************************************//**
 * @file
 * @brief ZigBee 3.0 core test harness functionality
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
#include "app/framework/security/af-security.h"
#include "app/framework/util/attribute-storage.h" // emberAfResetAttributes()
#include "app/framework/util/af-main.h" // sli_zigbee_af_cli_version_command()
#include "app/framework/security/security-config.h" // key definitions

#include "app/util/zigbee-framework/zigbee-device-common.h"

#include "zll-commissioning.h"
#include "network-steering.h"

#include "stack/include/network-formation.h"
#include "stack/include/zigbee-security-manager.h"

#include "test-harness-z3-core.h"
#include "test-harness-z3-nwk.h"
#include "test-harness-z3-zll.h"
#include "test-harness-z3-zdo.h"
#include "test-harness-z3-mac.h"

// -----------------------------------------------------------------------------
// Constants

// -----------------------------------------------------------------------------
// Extern functions

void sli_zigbee_af_zll_set_pan_id(EmberPanId panId);

// -----------------------------------------------------------------------------
// Globals

sli_zigbee_af_test_harness_z3_device_mode_type sli_zigbee_af_test_harness_z3_device_mode;

sl_zigbee_event_t emberAfPluginTestHarnessZ3OpenNetworkEvent;
#define z3OpenNetworkEventControl (&emberAfPluginTestHarnessZ3OpenNetworkEvent)
void emberAfPluginTestHarnessZ3OpenNetworkEventHandler(sl_zigbee_event_t * event);
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ResetKeyEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3BeaconSendEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ZllStuffEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ZdoSendEventControl;

uint16_t sli_zigbee_af_test_harness_z3_touchlink_profile_id = EMBER_ZLL_PROFILE_ID;

EmberKeyData preProgrammedNwkKey = {
  .contents = {
    0x00, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  }
};

//-------internal callbacks
void sli_zigbee_af_test_harness_z3_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3OpenNetworkEvent,
                       emberAfPluginTestHarnessZ3OpenNetworkEventHandler);
  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3ResetKeyEvent,
                       emberAfPluginTestHarnessZ3ResetKeyEventHandler);
  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3BeaconSendEvent,
                       emberAfPluginTestHarnessZ3BeaconSendEventHandler);
  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3ZllStuffEvent,
                       emberAfPluginTestHarnessZ3ZllStuffEventHandler);
  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3ZdoSendEventControl,
                       emberAfPluginTestHarnessZ3ZdoSendEventHandler);
}
// -----------------------------------------------------------------------------
// Util

uint32_t sli_zigbee_af_test_harness_z3_get_significant_bit(SL_CLI_COMMAND_ARG, uint8_t commandIndex)
{
  uint32_t mask = sl_cli_get_argument_uint32(arguments, commandIndex);
  uint32_t significantBit = (1UL << 31);
  while (!(significantBit & mask) && significantBit) {
    significantBit >>= 1;
  }
  return significantBit;
}

// -----------------------------------------------------------------------------
// State

#define PRINTING_MASK_BEACONS     BIT(0)
#define PRINTING_MASK_ZDO         BIT(1)
#define PRINTING_MASK_NWK         BIT(2)
#define PRINTING_MASK_APS         BIT(3)
#define PRINTING_MASK_INTERPAN    BIT(4)
#define PRINTING_MASK_RAW         BIT(5)
static uint8_t printingMask = PRINTING_MASK_INTERPAN; // always print INTERPAN commands

// -----------------------------------------------------------------------------
// Callbacks

// Provided by the packet-handoff component
EmberPacketAction emberAfIncomingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void *data)
{
  #if !defined(ESZP_HOST)
  EmberPacketAction act = EMBER_ACCEPT_PACKET;
  uint8_t commandId, packetLength;
  commandId = packetData[0];
  packetLength = *size_p;

  switch (packetType) {
    case EMBER_ZIGBEE_PACKET_TYPE_RAW_MAC: {
      if (printingMask & PRINTING_MASK_RAW) {
        emberAfCorePrint("raw mac:rx %d bytes [", packetLength);
        emberAfCorePrintBuffer(packetData, packetLength, true);
        emberAfCorePrintln("]");
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_BEACON: {
      if (printingMask & PRINTING_MASK_BEACONS) {
        uint16_t panId = *(uint16_t*) data;
        emberAfCorePrint("beacon:rx 0x%2X, AP 0x%p, EP ",
                         panId,
                         ((packetData[1] & BEACON_ASSOCIATION_PERMIT_BIT)
                          ? "1"
                          : "0"));
        emberAfCorePrintBuffer(packetData + BEACON_EXTENDED_PAN_ID_INDEX,
                               EXTENDED_PAN_ID_SIZE,
                               true); // spaces?
        emberAfCorePrintln("");

        // Print out the full payload except beacon header, for the benefit of the beanshell tests
        emberAfCorePrint("payload[");
        emberAfCorePrintBuffer(packetData,
                               packetLength,
                               true); // spaces?
        emberAfCorePrintln("]");
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_MAC_COMMAND: {
      if (printingMask & PRINTING_MASK_BEACONS) {
        if (commandId == BEACON_REQUEST_COMMAND) {
          emberAfCorePrintln("beacon-req:rx");
        }
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_NWK_COMMAND: {
      // Add the offset to make commandID points to correct `zigbee command` part
      if (data == NULL
          || (*(uint8_t *)data >= packetLength)) {
        emberAfCorePrintln("Invalid data");
        break;
      }
      uint8_t networkHeaderSize = *(uint8_t *)data;
      commandId = packetData[networkHeaderSize];
      if (printingMask & PRINTING_MASK_NWK) {
        emberAfCorePrint("nwk:rx seq AC sec 28 cmd %X payload[",
                         commandId);
        emberAfCorePrintBuffer(packetData, packetLength, true); // spaces?
        emberAfCorePrintln("]");
      }
      if (commandId == NWK_LEAVE_COMMAND
          && sli_zigbee_af_test_harness_z3_ignore_leave_commands) {
        // Ignore the leave by turning off the request bit in the options.
        uint8_t newOptions = packetData[1] & ~BIT(6);
        packetData[1] = newOptions;
        act = EMBER_MANGLE_PACKET;
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_APS_COMMAND: {
      if (printingMask & PRINTING_MASK_APS) {
        uint8_t fc = *(uint8_t*) data;
        emberAfCorePrint("aps:rx seq AC fc %X cmd %X payload[",
                         fc,
                         commandId);
        emberAfCorePrintBuffer(packetData + 1, packetLength - 1, true); // spaces?
        emberAfCorePrintln("]");
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_ZDO: {
      EmberStatus status;
      EmberApsFrame *apsFrame = (EmberApsFrame *) data;
      if (printingMask & PRINTING_MASK_ZDO) {
        emberAfCorePrint("zdo:t%4X:%p seq %X cmd %2X payload[",
                         emberAfGetCurrentTime(),
                         "rx",
                         packetData[0],
                         apsFrame->clusterId);
        emberAfCorePrintBuffer(packetData + ZDO_MESSAGE_OVERHEAD,
                               packetLength - ZDO_MESSAGE_OVERHEAD,
                               true); // spaces?
        emberAfCorePrintln("]");
      }
      status = sli_zigbee_af_test_harness_z3_zdo_command_response_handler(packetData,
                                                                          packetLength,
                                                                          apsFrame);
      if (status != EMBER_INVALID_CALL) {
        emberAfCorePrintln("%p: %p: cluster: 0x%02X status: 0x%X",
                           TEST_HARNESS_Z3_PRINT_NAME,
                           "ZDO negative command",
                           apsFrame->clusterId | 0x8000,
                           status);
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_INTERPAN: {
      if (printingMask & PRINTING_MASK_INTERPAN) {
        emberAfCorePrint("t%4x:rx len %d, ep %X, clus 0x1000 (ZLL Commissioning) FC %X seq %X cmd %X payload[",
                         emberAfGetCurrentTime(),
                         packetLength,
                         1,             // fake endpoint 1 for zll
                         packetData[0], // frame control
                         packetData[1], // sequence
                         packetData[2]); // command
        emberAfCorePrintBuffer(packetData + 3,
                               packetLength - 3,
                               true); // spaces?
        emberAfCorePrintln("]");
        act = sli_zigbee_af_test_harness_z3_zll_command_callback(packetData,
                                                                 data);        // source eui64
      }
      break;

      //neither handle, nor error out on new types
      case EMBER_ZIGBEE_PACKET_TYPE_NWK_COMMAND_PRE_DECRYPTION:
      case EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA_PRE_DECRYPTION:
        break;
    }
    default:
      emberAfDebugPrintln("Error: unsupported incoming EmberZigbeePacketType %X.", packetType);
      break;
  }
  return act;
  #else
  return EMBER_ACCEPT_PACKET;
  #endif // ESZP_HOST
}

// Provided by the packet-handoff component
EmberPacketAction emberAfOutgoingPacketFilterCallback(EmberZigbeePacketType packetType,
                                                      uint8_t* packetData,
                                                      uint8_t* size_p,
                                                      void *data)
{
  #if !defined(ESZP_HOST)
  EmberPacketAction act = EMBER_ACCEPT_PACKET;
  uint8_t packetLength = *size_p;

  switch (packetType) {
    case EMBER_ZIGBEE_PACKET_TYPE_BEACON: {
      emberAfDebugPrintln("emberOutgoingPH - sending a beacon");
      uint8_t payloadLength = BEACON_PAYLOAD_SIZE;
      act = sli_zigbee_af_test_harness_z3_modify_beacon_payload(packetData + MAC_BEACON_SIZE,
                                                                &payloadLength);
      if (payloadLength != BEACON_PAYLOAD_SIZE) {
        emberAfDebugPrintln("Old buffer length = %d", packetLength);
        *size_p = packetLength - BEACON_PAYLOAD_SIZE + payloadLength;
        emberAfDebugPrintln("New buffer length = %d", *size_p);
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_MAC_COMMAND: {
      uint8_t macHeaderLength = sl_mac_flat_mac_header_length(packetData, false);
      uint8_t payloadDataLength = packetLength - macHeaderLength;
      assert(macHeaderLength + payloadDataLength <= COMMAND_DATA_SIZE);

      emberAfDebugPrint("mac hdr:tx %d bytes [", macHeaderLength);
      emberAfDebugPrintBuffer(packetData, macHeaderLength, true); // spaces?
      emberAfDebugPrintln("]");
      emberAfDebugPrint("mac pay:tx %d bytes [", payloadDataLength);
      emberAfDebugPrintBuffer(packetData + macHeaderLength, payloadDataLength, true);
      emberAfDebugPrintln("]");

      // look at the APS header to see if we have an interpan msg.
      if (packetData[macHeaderLength + 2] == 0x03) {
        emberAfDebugPrintln("emberOutgoingPH - sending interpan msg");
        act = sli_zigbee_af_test_harness_z3_zll_modify_interpan_command(packetData,
                                                                        macHeaderLength);
      }
      break;
    }
    // Nothing to modify
    default:
      break;
  }
  return act;
  #else
  return EMBER_ACCEPT_PACKET;
  #endif // ESZP_HOST
}

// -----------------------------------------------------------------------------
// Printing

void sli_zigbee_af_test_harness_z3_printing_command(SL_CLI_COMMAND_ARG)
{
  bool enabled = (sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL)[0] == 'e');
  uint8_t mask;

  switch (sl_zigbee_cli_get_argument_string_and_length(arguments, -2, NULL)[0]) {
    case 'b':
      mask = PRINTING_MASK_BEACONS;
      break;
    case 'z':
      mask = PRINTING_MASK_ZDO;
      break;
    case 'n':
      mask = PRINTING_MASK_NWK;
      break;
    case 'a':
      mask = PRINTING_MASK_APS;
      break;
    case 'r':
      mask = PRINTING_MASK_RAW;
      break;
    default:
      mask = 0xFF;
  }

  if (enabled) {
    SETBITS(printingMask, mask);
  } else {
    CLEARBITS(printingMask, mask);
  }

  emberAfCorePrintln("%successfully %s printing.",
                     (mask == 0xFF ? "Uns" : "S"),
                     (enabled ? "enabled" : "disabled"));
}

// -----------------------------------------------------------------------------
// Framework Callbacks

void emberAfPluginTestHarnessZ3StackStatusCallback(EmberStatus status)
{
  if (status == EMBER_NETWORK_UP
      && emberAfGetNodeId() == EMBER_TRUST_CENTER_NODE_ID) {
    // Force the network open for joining if we are the trust center.
    // This is terrible security, but this plugin is for a terrible test
    // harness app, so I feel like it lines up.
    sl_zigbee_event_set_active(z3OpenNetworkEventControl);
  }
}

void emberAfPluginTestHarnessZ3OpenNetworkEventHandler(sl_zigbee_event_t * event)
{
  sl_zigbee_event_set_inactive(z3OpenNetworkEventControl);

  if (emberAfGetNodeId() == EMBER_TRUST_CENTER_NODE_ID) {
    EmberEUI64 wildcardEui64 = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };
    sl_zb_sec_man_key_t centralizedKey = ZIGBEE_PROFILE_INTEROPERABILITY_LINK_KEY;
    uint16_t transientKeyTimeoutS;

    // Make sure the trust center lets everyone on the network and
    // allows key requests.
    (void) sl_zb_sec_man_import_transient_key(wildcardEui64, &centralizedKey);
#ifdef EZSP_HOST
    ezspSetPolicy(EZSP_TC_KEY_REQUEST_POLICY, EMBER_ALLOW_TC_LINK_KEY_REQUEST_AND_SEND_CURRENT_KEY);
    ezspGetConfigurationValue(EZSP_CONFIG_TRANSIENT_KEY_TIMEOUT_S,
                              &transientKeyTimeoutS);
#else
    emberTrustCenterLinkKeyRequestPolicy = EMBER_ALLOW_TC_LINK_KEY_REQUEST_AND_SEND_CURRENT_KEY;
    transientKeyTimeoutS = emberTransientKeyTimeoutS;
#endif

    // Make sure we reopen the network before the transient key disappears.
    // Add in a timing slop of a second to prevent any race conditions.
    sl_zigbee_event_set_delay_ms(z3OpenNetworkEventControl,
                                 ((transientKeyTimeoutS * MILLISECOND_TICKS_PER_SECOND)
                                  - MILLISECOND_TICKS_PER_SECOND));
  }
}

// -----------------------------------------------------------------------------
// Core CLI commands

// plugin test-harness z3 reset
void sli_zigbee_af_test_harness_z3_reset_command(SL_CLI_COMMAND_ARG)
{
  emberAfZllResetToFactoryNew();

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Reset",
                     EMBER_SUCCESS);
}

// plugin test-harness z3 set-device-mode <mode:1>
void sli_zigbee_af_test_harness_z3_set_device_mode_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status = EMBER_BAD_ARGUMENT;

  sli_zigbee_af_test_harness_z3_device_mode_type mode
    = sl_cli_get_argument_uint8(arguments, 0);

  if (mode <= EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_MAX) {
    sli_zigbee_af_test_harness_z3_device_mode = mode;
    status = EMBER_SUCCESS;
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Set device mode",
                     status);
}

// plugin test-harness z3 set-short-address
void sli_zigbee_af_test_harness_z3_set_short_address_command(SL_CLI_COMMAND_ARG)
{
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Set short address",
                     EMBER_INVALID_CALL);
}

// plugin test-harness z3 legacy-profile-id
void sli_zigbee_af_test_harness_z3_legacy_profile_command(SL_CLI_COMMAND_ARG)
{
  sli_zigbee_af_test_harness_z3_touchlink_profile_id = (sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL)[0] == 'e')
                                                       ? EMBER_ZLL_PROFILE_ID
                                                       : HA_PROFILE_ID;
}

// plugin test-harness z3 set-pan-id
void sli_zigbee_af_test_harness_set_network_creator_pan_id(SL_CLI_COMMAND_ARG)
{
  EmberPanId panId = sl_cli_get_argument_uint16(arguments, 0);
  sli_zigbee_af_zll_set_pan_id(panId);

  emberAfCorePrintln("Network Creator PAN ID = 0x%2X", panId);
}

// plugin test-harness z3 platform
void sli_zigbee_af_test_harness_z3_platform_command(SL_CLI_COMMAND_ARG)
{
  emberAfCorePrintln("Platform: Silicon Labs");
  emberAfCorePrint("EmberZNet ");
  sli_zigbee_af_cli_version_command();
}

// plugin test-harness z3 install-code clear
// plugin test-harness z3 install-code set <code>
void sli_zigbee_af_test_harness_z3_install_code_clear_or_set_command(SL_CLI_COMMAND_ARG)
{
  bool doClear = (sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL)[0] == 'c');

#ifndef EZSP_HOST
#if !defined(EMBER_AF_HAS_SECURITY_PROFILE_NONE)
  if (false == doClear) {
    EmberEUI64 eui64 = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff }; //wild card
    EmberKeyData key;
    EmberStatus status;
    uint8_t code[16 + 2]; // 6, 8, 12, or 16 bytes plus two-byte CRC
    uint8_t length;

    length = sl_zigbee_copy_hex_arg(arguments, 0, code, sizeof(code), false);

    // Convert the install code to a key
    status = sli_zigbee_af_install_code_to_key(code, length, &key);

    if (EMBER_SUCCESS != status) {
      if (EMBER_SECURITY_DATA_INVALID == status) {
        emberAfAppPrintln("ERR: Calculated CRC does not match -len");
      } else if (EMBER_BAD_ARGUMENT == status) {
        emberAfAppPrintln("ERR: Install Code must be 8, 10, 14, or 18 bytes in "
                          "length");
      } else {
        emberAfAppPrintln("ERR: AES-MMO hash failed: 0x%X", status);
      }
      return;
    }

    // Add the key to transient key.
    sl_status_t key_status = sl_zb_sec_man_import_transient_key(eui64, (sl_zb_sec_man_key_t*)&key);
    status = ((key_status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_NO_BUFFERS);
    emberAfAppDebugExec(sli_zigbee_af_print_status("Set joining link key", status));
    emberAfAppPrintln("");
    emberAfAppFlush();
  } else {
    // We currently clear all the transient keys.
    emberClearTransientLinkKeys();
    emberAfAppPrintln("Success: Clear joining link key");
  }
#else
  UNUSED_VAR(doClear);
  emberAfAppPrintln("Security Core Library must be included to use this command.");
#endif
#else
  emberAfCorePrintln("%s: %s %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Install code",
                     (doClear ? "clear" : "set"),
                     EMBER_INVALID_CALL);
#endif
}
