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
#include "app/framework/plugin/network-creator-security/network-creator-security.h"
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
#include "address-table.h"
#include "core/ember-multi-network.h"
#include "framework/packet-header.h"

#ifdef SL_CATALOG_ZIGBEE_END_DEVICE_SUPPORT_PRESENT
#include "app/framework/plugin/end-device-support/end-device-support.h"
#endif
#ifdef EZSP_HOST
// NCP
  #define addTransientLinkKey        ezspAddTransientLinkKey
#else
// SoC
  #define addTransientLinkKey        emberAddTransientLinkKey
#endif

//------------------------------------------------------------------------------
// Added to get access to the packet buffer network frame while handling the
// Handoff callback.
#define ZIGBEE_DESTINATION_ADDRESS_INDEX 2
#define ZIGBEE_SOURCE_ADDRESS_INDEX      4
#define ZIGBEE_SEQUENCE_INDEX            7
#define NWK_MAC_HEADER_SIZE              8
#define emZigbeeSequence(frame) \
  ((frame)[ZIGBEE_SEQUENCE_INDEX])
#define emZigbeeDestination(frame) \
  emberFetchLowHighInt16u((frame) + ZIGBEE_DESTINATION_ADDRESS_INDEX)
#define emZigbeeSource(frame) \
  emberFetchLowHighInt16u((frame) + ZIGBEE_SOURCE_ADDRESS_INDEX)
#define emHeaderRoutingFrame(header) \
  (sli_zigbee_packet_header_contents(header))

EmberMessageBuffer emTempHandoffHeader;
// -----------------------------------------------------------------------------
// Constants
#define RX_ON_DELAY_MS 10000
EmberStatus emberUserDescriptorRequest(EmberNodeId target,
                                       EmberApsOption options);

// -----------------------------------------------------------------------------
// Extern functions
extern EmberZllState sli_zigbee_zll_get_state(void);
extern void emRadioEnableAddressMatching(uint8_t enable);
extern void sli_zigbee_af_zll_set_pan_id(EmberPanId panId);

// -----------------------------------------------------------------------------
// Globals

sli_zigbee_af_test_harness_z3_device_mode_type sli_zigbee_af_test_harness_z3_device_mode = EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZR_NOT_ADDRESS_ASSIGNABLE;

sl_zigbee_event_t emberAfPluginTestHarnessZ3OpenNetworkEvent;
#define z3OpenNetworkEventControl (&emberAfPluginTestHarnessZ3OpenNetworkEvent)
void emberAfPluginTestHarnessZ3OpenNetworkEventHandler(sl_zigbee_event_t * event);
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ResetKeyEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3BeaconSendEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ZllStuffEvent;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ZdoSendEventControl;
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3ResetEventControl;
extern void sli_zigbee_set_network_key(EmberKeyData* key,
                                       uint8_t keySequenceNumber,
                                       bool current);
uint16_t sli_zigbee_af_test_harness_z3_touchlink_profile_id = EMBER_ZLL_PROFILE_ID;

extern EmberZllNetwork zllNetwork;

// function prototypes
static bool layeredHandlingMode(EmberZigbeePacketType packetType,
                                uint8_t* packetData,
                                uint8_t* size_p,
                                void *data);
static EmberKeyData preProgrammedNwkKey = {
  .contents = {
    0x00, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
  }
};

sl_zigbee_event_t emberAfPluginTestHarnessZ3ResetEventControl;

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
  sl_zigbee_event_init(&emberAfPluginTestHarnessZ3ResetEventControl,
                       emberAfPluginTestHarnessZ3ResetEventHandler);
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
#define PRINTING_MASK_ZCL    BIT(4)
#define PRINTING_MASK_RAW         BIT(5)

#define DROP_PLME  BIT(0)
#define DROP_MLME  BIT(1)
#define DROP_MCPSD BIT(2)
#define DROP_NLME  BIT(3)
#define DROP_NLDE  BIT(4)
#define DROP_APSDE BIT(5)

#define INDICATION_LAYER_PLME  BIT(0)
#define INDICATION_LAYER_MLME  BIT(1)
#define INDICATION_LAYER_MCPSD BIT(2)
#define INDICATION_LAYER_NLME  BIT(3)
#define INDICATION_LAYER_NLDE  BIT(4)
#define INDICATION_LAYER_APSDE BIT(5)

#define CONFIRMATION_LAYER_PLME  BIT(0)
#define CONFIRMATION_LAYER_MLME  BIT(1)
#define CONFIRMATION_LAYER_MCPSD BIT(2)
#define CONFIRMATION_LAYER_NLME  BIT(3)
#define CONFIRMATION_LAYER_NLDE  BIT(4)
#define CONFIRMATION_LAYER_APSDE BIT(5)

// Print Mask
static uint8_t printingMask = PRINTING_MASK_ZCL; // always print zcl commands
// Layer select masks
// Drop Mask
static uint8_t dropMask = 0;
// Monitor Indication
static uint8_t indicationMask = 0;
// Monitor Confirmation
static uint8_t confirmationMask = 0;

// -----------------------------------------------------------------------------
// Callbacks
extern bool sli_zigbee_test_harness_z3_ignore_rejoin_commands;
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
  if (layeredHandlingMode(packetType,
                          packetData,
                          size_p,
                          data)) {
    return EMBER_DROP_PACKET;
  }
  //if (wiresharkCapture) {
  //  return EMBER_DROP_PACKET;
  //}
  switch (packetType) {
    case EMBER_ZIGBEE_PACKET_TYPE_RAW_MAC:
#ifdef EMBER_PROMISCUOUS_MODE_SUPPORT
      // Do some filtering if we are in promiscuous mode.
      if (!emRadioAddressMatchingEnabled()) {
        uint8_t macHeaderLength = emMacHeaderLength(packetData);

        // Look at the stub NWK and APS headers to see if we have an interpan msg.
        if ((packetData[macHeaderLength] & 0x03) == 0x03
            && (packetData[macHeaderLength + 2] & 0x03) == 0x03) {
          sl_zigbee_app_debug_println("Allowing interpan message");
        }
        // Allow if we have a PAN ID match.
        else if (emberAfGetInt16u(packetData, 3, packetLength) == emberGetPanId()) {
          sl_zigbee_app_debug_println("PAN ID match");
        }
        // Otherwise, only allow broadcasts.
        else if (emberAfGetInt16u(packetData, 5, packetLength) != 0xFFFF) {  // broadcast addr
          sl_zigbee_app_debug_println("Dropping unicast message");
          act = EMBER_DROP_PACKET;
        }
        // Finally, check the source long address (in the NWK header).
        else if (emberAfGetInt16u(packetData, 0, packetLength) & 0xC000) {  // source addr present in MAC hdr?
          emberAfAppPrint("sourceEui64: ");
          emberAfAppPrintBuffer(packetData + macHeaderLength + 8, 8, true); // spaces?
          sl_zigbee_app_debug_println("");
          emberAfAppPrint("tgt source address:");
          emberAfAppPrintBuffer(zllNetwork.eui64, 8, true); // spaces?
          sl_zigbee_app_debug_println("");

          if (MEMCOMPARE(zllNetwork.eui64, packetData + macHeaderLength + 8, EUI64_SIZE)) {
            sl_zigbee_app_debug_println("Unknown source address, dropping");
            act = EMBER_DROP_PACKET;
          }
        }
      }
#endif // #ifdef EMBER_PROMISCUOUS_MODE_SUPPORT

      if (act == EMBER_ACCEPT_PACKET && (printingMask & PRINTING_MASK_RAW)) {
        emberAfCorePrint("raw mac:rx %d bytes [", packetLength);
        emberAfCorePrintBuffer(packetData, packetLength, true);
        emberAfCorePrintln("]");
      }
      break;

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
        // Ignore the leave if the request bit is set.
        if (packetData[networkHeaderSize + 1] & (uint8_t)BIT(6)) {
          act = EMBER_DROP_PACKET;
        }
      } else if (commandId == NWK_REJOIN_REQUEST_COMMAND
                 && sli_zigbee_test_harness_z3_ignore_rejoin_commands) {
        act = EMBER_DROP_PACKET;
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA: {
      // TODO: We're currently just printing the APS header for the
      // benefit of WWAH testing - we may need to make this more
      // general for GP testing.
      if (printingMask & PRINTING_MASK_NWK) { // borrowing this bit for now
        // Unpack the aps header
        uint8_t *finger = (uint8_t*) packetData;
        uint8_t fc = *finger++;
        if ((fc & 0x03) == 0) { // APS data
          uint8_t delivery_mode = (fc & 0x0c) >> 2;
          uint16_t group_address = 0;
          uint8_t dest_ep = 0;
          if (delivery_mode == 3) { // groupcast
            group_address = emberAfGetInt16u(finger, 0, packetLength);
            finger += 2;
          } else {
            dest_ep = *finger++;
          }
          uint16_t cluster = emberAfGetInt16u(finger, 0, packetLength);
          finger += 2;
          uint16_t profile = emberAfGetInt16u(finger, 0, packetLength);
          finger += 2;
          uint8_t source_ep = *finger++;
          uint8_t seq = *finger++;

          emberAfCorePrintln("APS header: fc %X grp %2X dst_ep %X clst %2X pfl %2X src_ep %X seq %X",
                             fc, group_address, dest_ep, cluster, profile, source_ep, seq);
        }
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

    case EMBER_ZIGBEE_PACKET_TYPE_APS_DATA: {
      emberAfDebugPrintln("Error: unsupported incoming EmberZigbeePacketType %X.", packetType);
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
        emberAfCorePrintln("]", packetLength);
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
    case EMBER_ZIGBEE_PACKET_TYPE_INTERPAN:
    case EMBER_ZIGBEE_PACKET_TYPE_ZCL: {
      if (printingMask & PRINTING_MASK_ZCL) {
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
      // (the frame type sub-field of the frame control byte is 0b11)
      if ((packetData[macHeaderLength + 2] & 0x03) == 0x03) {
        emberAfDebugPrintln("emberOutgoingPH - sending interpan msg");
        act = sli_zigbee_af_test_harness_z3_zll_modify_interpan_command(packetData,
                                                                        macHeaderLength);
      }
      break;
    }
    // Nothing to modify
    default:
      emberAfDebugPrintln("Error: unsupported outgoing EmberZigbeePacketType %X.", packetType);
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
  uint8_t mask = 0xFF;

  switch (sl_zigbee_cli_get_argument_string_and_length(arguments, -2, NULL)[0]) {
    case 'b':
      mask = PRINTING_MASK_BEACONS;
      break;
    case 'z': // this can be zdo or zcl : hence choose the correct one
      if (sl_zigbee_cli_get_argument_string_and_length(arguments, -2, NULL)[1] == 'c') {
        mask = PRINTING_MASK_ZCL;
      } else if (sl_zigbee_cli_get_argument_string_and_length(arguments, -2, NULL)[1] == 'd') {
        mask = PRINTING_MASK_ZDO;
      }
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
  if (status == EMBER_NETWORK_UP) {
    if (emberAfGetNodeId() == EMBER_TRUST_CENTER_NODE_ID) {
      // Set the key request policy here, once (so it can be overridden), depending
      // on whether we are a WWAH client (which will usually be true now).
      uint8_t keyRequestPolicy;
#ifdef ZCL_USING_SL_WWAH_CLUSTER_CLIENT
      keyRequestPolicy = EMBER_ALLOW_TC_LINK_KEY_REQUEST_AND_GENERATE_NEW_KEY;
#else
      keyRequestPolicy = EMBER_ALLOW_TC_LINK_KEY_REQUEST_AND_SEND_CURRENT_KEY;
#endif
#ifdef EZSP_HOST
      ezspSetPolicy(EZSP_TC_KEY_REQUEST_POLICY, keyRequestPolicy);
      ezspGetConfigurationValue(EZSP_CONFIG_TRANSIENT_KEY_TIMEOUT_S,
                                &transientKeyTimeoutS);
#else
      emberTrustCenterLinkKeyRequestPolicy = keyRequestPolicy;
#endif
    }
  }
  if (status == EMBER_NETWORK_UP || status == EMBER_JOIN_FAILED) {
    EmberZllState zllState = sli_zigbee_zll_get_state();
    if (zllState & EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE) {
      // Re-enable address matching whether the join succeeded or not.
      emRadioEnableAddressMatching(true);
    }
  }
}

void emberAfPluginTestHarnessZ3OpenNetworkEventHandler(sl_zigbee_event_t * event)
{
  sl_zigbee_event_set_inactive(z3OpenNetworkEventControl);
  EmberEUI64 wildcardEui64 = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, };

  // The open network event handler is called when the network is opened via
  // Network Steering or a plain permit join, to support ZTT scripts which do
  // not use Network Creator Open [With Key], by copying the appropriate joining key
  // to the Transient Link Key table.
  EmberCurrentSecurityState securityState;

  if (emberGetCurrentSecurityState(&securityState) != EMBER_SUCCESS) {
    // Orphaned and rejoining - unlikely, but delay and try again anyway.
    emberAfDebugPrintln("emberGetCurrentSecurityState failure");
    sl_zigbee_event_set_delay_ms(z3OpenNetworkEventControl,
                                 MILLISECOND_TICKS_PER_SECOND);
    return;
  }

  EmberNodeType nodeType;  // Use the Ember API directly, to be on safe side.

  emberGetNodeType(&nodeType);
  if (nodeType == EMBER_COORDINATOR
      || (nodeType == EMBER_ROUTER
          && (securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE) == 0)) {
    // Centralized network - copy the HA link key into the transient key table,
    // and reset the join policy, in case we did a 'pl network-creator-security close'.
    sl_zb_sec_man_key_t centralizedKey = ZIGBEE_PROFILE_INTEROPERABILITY_LINK_KEY;

    // Make sure the trust center lets everyone on the network and
    // allows key requests.
    (void) sl_zb_sec_man_import_transient_key(wildcardEui64, &centralizedKey);
    zaTrustCenterSetJoinPolicy(EMBER_USE_PRECONFIGURED_KEY);
  } else if (nodeType == EMBER_ROUTER) {
    // Copy the (non-ZLL) distributed test key into the transient key table,
    // and reset the join policy, in case we did a 'pl network-creator-security close'.
    sl_zb_sec_man_key_t myKey;

    EmberKeyData distributedTestKey = EMBER_ZLL_CERTIFICATION_PRECONFIGURED_LINK_KEY; // D0, D1, D2...
    MEMCOPY(&myKey.key, &distributedTestKey, EMBER_ENCRYPTION_KEY_SIZE);
    (void)sl_zb_sec_man_import_transient_key(wildcardEui64, &myKey);
    zaTrustCenterSetJoinPolicy(EMBER_USE_PRECONFIGURED_KEY);
  }
}

// -----------------------------------------------------------------------------
// Core CLI commands

// plugin test-harness z3 reset
void sli_zigbee_af_test_harness_z3_reset_command(SL_CLI_COMMAND_ARG)
{
  // Leave network and clear tables - this will complete synchronously,
  // without waiting for a network down.
  emberAfZllResetToFactoryNew();

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Reset",
                     EMBER_SUCCESS);
  // Allow time for the println.
  sl_zigbee_event_set_delay_ms(&emberAfPluginTestHarnessZ3ResetEventControl, 100);
}

void emberAfPluginTestHarnessZ3ResetEventHandler(sl_zigbee_event_t * event)
{
  // Clear volatile data.
  halReboot();
}

// plugin test-harness z3 set-device-mode <mode:1>
void sli_zigbee_af_test_harness_z3_set_device_mode_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status = EMBER_BAD_ARGUMENT;

  sli_zigbee_af_test_harness_z3_device_mode_type mode
    = sl_cli_get_argument_uint8(arguments, 0);
  emberAfCorePrintln("mode = %d", mode);
  if (mode <= EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_MAX) {
    sli_zigbee_af_test_harness_z3_device_mode = mode;
    // Update the Framework node type.
    if ((mode & 0xFE) == EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZR_NOT_ADDRESS_ASSIGNABLE) {
      sli_zigbee_af_current_zigbee_pro_network->nodeType = EMBER_ROUTER;
    } else if ((mode & 0xFE) == EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZED_NOT_ADDRESS_ASSIGNABLE) {
      sli_zigbee_af_current_zigbee_pro_network->nodeType = EMBER_END_DEVICE;
#ifdef SL_CATALOG_ZIGBEE_END_DEVICE_SUPPORT_PRESENT
      sli_zigbee_af_end_device_support_polling_init();
#endif
    } else {
      sli_zigbee_af_current_zigbee_pro_network->nodeType = EMBER_SLEEPY_END_DEVICE;
#ifdef SL_CATALOG_ZIGBEE_END_DEVICE_SUPPORT_PRESENT
      sli_zigbee_af_end_device_support_polling_init();
#endif
    }

    // Update the ZLL node type for incoming scan requests, and
    // outgoing requests via the Zll Comm plugin.
    emberSetZllNodeType(sli_zigbee_af_current_zigbee_pro_network->nodeType);

    // Update the address capable bit, in order that the initiator
    // bit is correctly set on a scan request.
    EmberTokTypeStackZllData token;
    emberZllGetTokenStackZllData(&token);
    if ((sli_zigbee_af_test_harness_z3_device_mode & EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZR_ADDRESS_ASSIGNABLE) == 1) {
      token.bitmask |= EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE;
    } else {
      token.bitmask &= ~EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE;
    }
    emberZllSetTokenStackZllData(&token);
    status = EMBER_SUCCESS;
    emberAfCorePrintln("Device mode = %d, node type = %d",
                       sli_zigbee_af_test_harness_z3_device_mode,
                       sli_zigbee_af_current_zigbee_pro_network->nodeType);
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
        sl_zigbee_app_debug_println("ERR: Calculated CRC does not match -len");
      } else if (EMBER_BAD_ARGUMENT == status) {
        sl_zigbee_app_debug_println("ERR: Install Code must be 8, 10, 14, or 18 bytes in "
                                    "length");
      } else {
        sl_zigbee_app_debug_println("ERR: AES-MMO hash failed: 0x%X", status);
      }
      return;
    }

    // Add the key to transient key.
    sl_status_t key_status = sl_zb_sec_man_import_transient_key(eui64, (sl_zb_sec_man_key_t*)&key);
    status = ((key_status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_NO_BUFFERS);
    emberAfAppDebugExec(sli_zigbee_af_print_status("Set joining link key", status));
    sl_zigbee_app_debug_println("");
    emberAfAppFlush();
  } else {
    // We currently clear all the transient keys.
    emberClearTransientLinkKeys();
    sl_zigbee_app_debug_println("Success: Clear joining link key");
  }
#else
  UNUSED_VAR(doClear);
  sl_zigbee_app_debug_println("Security Core Library must be included to use this command.");
#endif
#else
  emberAfCorePrintln("%s: %s %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Install code",
                     (doClear ? "clear" : "set"),
                     EMBER_INVALID_CALL);
#endif
}

// Following code is an extention to support the GP testing by
// adding more cli to TH as a layered req/confirm and indication.
void sli_zigbee_test_harness_z3_layer_select(SL_CLI_COMMAND_ARG)
{
  uint8_t tempDropMask = 0;
  uint8_t tempIndMask = 0;
  uint8_t tempCfmMask = 0;
  // plme, mlme, mcpsd, nlme, nlde, apsde
  if (memcmp(sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL), "mcpsd", 5) == 0) {
    tempDropMask = DROP_MCPSD;
    tempIndMask = INDICATION_LAYER_MCPSD;
    tempCfmMask = CONFIRMATION_LAYER_MCPSD;
  } else if (memcmp(sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL), "apsde", 5) == 0) {
    tempDropMask = DROP_APSDE;
    tempIndMask = INDICATION_LAYER_APSDE;
    tempCfmMask = CONFIRMATION_LAYER_APSDE;
  } else if (memcmp(sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL), "nlde", 4) == 0) {
    tempDropMask = DROP_NLDE;
    tempIndMask = INDICATION_LAYER_NLDE;
    tempCfmMask = CONFIRMATION_LAYER_NLDE;
  }

  bool drop = (bool)sl_cli_get_argument_uint8(arguments, 0);
  if (drop) {
    SETBITS(dropMask, tempDropMask);
  } else {
    CLEARBITS(dropMask, tempDropMask);
  }
  bool ind = (bool)sl_cli_get_argument_uint8(arguments, 1);
  if (ind) {
    SETBITS(indicationMask, tempIndMask);
  } else {
    CLEARBITS(indicationMask, tempIndMask);
  }
  bool cfm = (bool)sl_cli_get_argument_uint8(arguments, 2);
  if (cfm) {
    SETBITS(confirmationMask, tempCfmMask);
  } else {
    CLEARBITS(confirmationMask, tempCfmMask);
  }

  emberAfCorePrintln("layer-select-cfm 0x%X 0x%X 0x%X",
                     dropMask, indicationMask, confirmationMask);
}
static void printApsdeCfm(uint8_t dstMode,
                          uint8_t * dstAddrStr,
                          uint16_t dstAddr,
                          EmberApsFrame * apsFrame,
                          uint8_t status)
{
  if (confirmationMask & CONFIRMATION_LAYER_APSDE) {
    emberAfCorePrintln("");
    emberAfCorePrint("apsde-cfm 0x%X {", dstMode);                // Dst Mode
    if (dstMode == 3) {
      emberAfCorePrintBuffer(dstAddrStr, 8, false);
    } else {
      emberAfCorePrint("%X%X", (uint8_t)dstAddr, (uint8_t)(dstAddr >> 8));
    }
    emberAfCorePrintln("} 0x%X 0x%X 0x%X",
                       apsFrame->destinationEndpoint,           // Dst Endpoint
                       apsFrame->sourceEndpoint,                // Src Endpoint
                       status);                                 // Status
  }
}
// sends out an APSDE-DATA.request
void sl_zigbee_test_harness_z3_apsde_data_request(SL_CLI_COMMAND_ARG)
{
  uint8_t dstMode = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  uint8_t dstAddrStr[8] = { 0 }; //this could be a 16 bit address or ieee address depending on the address mode
  sl_zigbee_copy_hex_arg(arguments, 1, dstAddrStr, 8, true);
  uint16_t dstAddr = ((uint16_t)dstAddrStr[7] << 8) + dstAddrStr[6];
  EmberApsFrame apsFrame = { 0 };
  apsFrame.destinationEndpoint = (uint8_t)sl_cli_get_argument_uint8(arguments, 2);
  apsFrame.profileId = (uint16_t)sl_cli_get_argument_uint16(arguments, 3);
  apsFrame.clusterId = (uint16_t)sl_cli_get_argument_uint16(arguments, 4);
  apsFrame.sourceEndpoint = (uint8_t)sl_cli_get_argument_uint8(arguments, 5);
  uint8_t asduLength = (uint8_t)sl_cli_get_argument_uint8(arguments, 6);
  uint8_t asdu[140] = { 0 };
  sl_zigbee_copy_hex_arg(arguments, 7, asdu, asduLength, false);
  uint8_t options = (uint8_t)sl_cli_get_argument_uint8(arguments, 8);
  bool useAlias = (bool)sl_cli_get_argument_uint8(arguments, 9);
  EmberNodeId alias = (uint16_t)sl_cli_get_argument_uint16(arguments, 10);
  uint8_t aliasSequence = (uint8_t)sl_cli_get_argument_uint8(arguments, 11);
  apsFrame.radius = (uint8_t)sl_cli_get_argument_uint8(arguments, 12);
  // Common options from input arguement
  apsFrame.options |= (options & 0x01) ? EMBER_APS_OPTION_ENCRYPTION : 0; // 0x01 = Security enabled transmission
  //apsFrame.options |= (options & 0x02) ? <how do we do it > ;           // 0x02 = Use NWK key
  apsFrame.options |= (options & 0x04) ? EMBER_APS_OPTION_RETRY : 0;      // 0x04 = Acknowledged transmission
  apsFrame.options |= (options & 0x08) ? EMBER_APS_OPTION_FRAGMENT : 0;   // 0x08 = Fragmentation permitted
  //apsFrame.options |= (options & 0x10) ? <how do we do it >;            // 0x10 = Include extended nonce in APS security frame.
  uint16_t messageTag = 0; // This is the APSDE Identifier
  EmberStatus status = EMBER_SUCCESS;
  uint8_t sendAddressMode = dstMode;
  uint16_t indexOrDest = dstAddr;
  switch (dstMode) {
    case 0: //DstAddress and DstEndpoint not present - BOUND Mode
    {
      apsFrame.options |= EMBER_APS_OPTION_RETRY;
      sendAddressMode = EMBER_OUTGOING_VIA_BINDING;
      for (int i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
        EmberBindingTableEntry candidate;
        status = emberGetBinding(i, &candidate);
        if (status == EMBER_SUCCESS
            && candidate.local == apsFrame.sourceEndpoint
            && candidate.clusterId == apsFrame.clusterId) {
          indexOrDest = i;
          status = EMBER_SUCCESS;
          break;
        }
        status = 0xA8; // APSDE DATA CFM code: NO_BOUND_DEVICE
      }
      break;
    }
    case 1: //16-bit group address for DstAddress; DstEndpoint not present
      sendAddressMode = useAlias ? EMBER_OUTGOING_MULTICAST_WITH_ALIAS : EMBER_OUTGOING_MULTICAST;
      apsFrame.groupId = dstAddr;
      apsFrame.sequence = useAlias ? aliasSequence : apsFrame.sequence;
      apsFrame.options |= useAlias ? EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER : 0;
      break;
    case 2: //16-bit address for DstAddress and DstEndpoint present
      sendAddressMode = EMBER_OUTGOING_DIRECT;
      if (dstAddr > 0xFFF8) {
        sendAddressMode = useAlias ? EMBER_OUTGOING_BROADCAST_WITH_ALIAS : EMBER_OUTGOING_BROADCAST;
        apsFrame.sequence = useAlias ? aliasSequence : apsFrame.sequence;
        apsFrame.options |= useAlias ? EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER : 0;
      }
      break;
    case 3: //64-bit extended address for DstAddress and DstEnd- point present
    {
      uint8_t index = emberAfLookupAddressTableEntryByEui64(dstAddrStr);
      if (index == EMBER_NULL_ADDRESS_TABLE_INDEX) {
        status = 0xA9;//APSDE DATA CFM code : NO_SHORT_ADDRESS
        break;
      }
      indexOrDest = index;
      sendAddressMode = EMBER_OUTGOING_VIA_ADDRESS_TABLE;
      apsFrame.options |= EMBER_APS_OPTION_DESTINATION_EUI64;
      break;
    }
    default:
      break;
  }

  // No error in any of the parameter selction yet
  if (status == EMBER_SUCCESS) {
    status = sli_zigbee_af_send(sendAddressMode,//EmberOutgoingMessageType type,
                                indexOrDest, //uint16_t indexOrDestination,
                                &apsFrame, //EmberApsFrame *apsFrame,
                                asduLength, //uint8_t messageLength,
                                asdu, //uint8_t *message,
                                &messageTag, //uint16_t *messageTag,
                                alias, //EmberNodeId alias,
                                aliasSequence); //uint8_t sequence);
  }
  // Synchronous confirm to ensure packet is submitted to network successfully.
  emberAfCorePrintln("apsde-syncfm 0x%X", status);
  // In case of a send submission failure the confirm is called here immediately
  if (status != EMBER_SUCCESS) {
    printApsdeCfm(dstMode, dstAddrStr, dstAddr, &apsFrame, status);
  }
}

#ifndef EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE
#define EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE 0
#endif

#if (defined EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE) && (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE != 0)
uint8_t mapHandleToBuffer[2 * (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE)] = { 0xFF, 0xFF, 0xFF, 0xFF };
bool mapHandleToBufferInitFlag = false;
static bool bufferToHandleEntryExists(uint8_t buffer, uint8_t msduHandle)
{
  for (int i = 0; i < (2 * (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE)); i += 2) {
    if (mapHandleToBuffer[i] == buffer
        && mapHandleToBuffer[i + 1] == msduHandle) {
      return true;
    }
  }
  return false;
}
static bool pushMap(uint8_t buffer, uint8_t msduHandle)
{
  if (!mapHandleToBufferInitFlag) {
    mapHandleToBufferInitFlag = true;
    memset(mapHandleToBuffer, 0xFF, (2 * (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE)));
  }
  if (bufferToHandleEntryExists(buffer, msduHandle)) {
    return false;// entry present, means last handle is not cleared
  }
  for (int i = 0; i < (2 * (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE)); i += 2) {
    if (mapHandleToBuffer[i] == 0xFF) { // get an empty slot and add
      mapHandleToBuffer[i] = buffer;
      mapHandleToBuffer[i + 1] = msduHandle;
      return true;
    }
  }
  return false;
}
static uint8_t popMap(uint8_t buffer) // takes the buffer and pops the msduhandle from map
{
  uint8_t msduHandle = 0xFF;
  for (int i = 0; i < (2 * (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE)); i += 2) {
    if (mapHandleToBuffer[i] == buffer) {
      mapHandleToBuffer[i] = 0xFF;
      msduHandle = mapHandleToBuffer[i + 1];
      mapHandleToBuffer[i + 1] = 0xFF;
    }
  }
  return msduHandle;
}
#endif

// this is the confirmation for the MAC messages
void emberAfRawTransmitCompleteCallback(EmberMessageBuffer message,
                                        EmberStatus status)
{
#if (defined EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE) && (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE != 0)
  uint8_t msduHandle = popMap(message);
#else
  uint8_t msduHandle = message;
#endif
  if (!(confirmationMask & CONFIRMATION_LAYER_MCPSD)) {
    return; // if cfm mask not enabled , return;
  }
  if (msduHandle != 0xFF) {
    emberAfCorePrintln("mcpsd-cfm 0x%X 0x%X", msduHandle, status);
  }
}

extern uint8_t currentSentMessageTag;

/** @brief Message Sent
 *
 * This function is called by the application framework from the message sent
 * handler, when it is informed by the stack regarding the message sent status.
 * All of the values passed to the emberMessageSentHandler are passed on to this
 * callback. This provides an opportunity for the application to verify that its
 * message has been sent successfully and take the appropriate action. This
 * callback should return a bool value of true or false. A value of true
 * indicates that the message sent notification has been handled and should not
 * be handled by the application framework.
 *
 * @param type   Ver.: always
 * @param indexOrDestination   Ver.: always
 * @param apsFrame   Ver.: always
 * @param msgLen   Ver.: always
 * @param message   Ver.: always
 * @param status   Ver.: always
 */
bool emberAfMessageSentCallback(EmberOutgoingMessageType type,
                                int16u indexOrDestination,
                                EmberApsFrame* apsFrame,
                                int16u msgLen,
                                int8u* message,
                                EmberStatus status)
{
  // Print NL confirmation first, if enabled!
  if (confirmationMask & CONFIRMATION_LAYER_NLDE) {
    emberAfCorePrintln("");
    emberAfCorePrintln("nlde-cfm 0x%X 0x%X", currentSentMessageTag, status);
  }
  uint8_t mode = 0;
  uint8_t dstAddrStr[8];
  uint16_t dstAddr = indexOrDestination;
  switch (type) {
    case EMBER_OUTGOING_BROADCAST:
    case EMBER_OUTGOING_BROADCAST_WITH_ALIAS:
    case EMBER_OUTGOING_DIRECT:
      mode = 2;
      break;
    case EMBER_OUTGOING_MULTICAST:
    case EMBER_OUTGOING_MULTICAST_WITH_ALIAS:
      dstAddr = apsFrame->groupId;
      mode = 1;
      break;
    case EMBER_OUTGOING_VIA_ADDRESS_TABLE:
      mode = 3;
      emberGetAddressTableRemoteEui64(indexOrDestination, dstAddrStr);
      break;
    case EMBER_OUTGOING_VIA_BINDING:
    {
      EmberBindingTableEntry candidate;
      emberGetBinding(indexOrDestination, &candidate);
      mode = 0;
      break;
    }
    default:
      break;
  }
  printApsdeCfm(mode,
                dstAddrStr,
                dstAddr,
                apsFrame,
                status);
  return false;
}
// sends out an zigbee NLDE-DATA.request
// This one of the very tricky one to implement and it is partial, the reason is that
// the service layer primitive should be able to carry out request with access to security,
// NIB attributes - which is not available at the moment.So to implement this, what is done is
// break down the treat nsdu as apdu and extract the header information and asdu, then use the
// emberAfSend function.
void sl_zigbee_test_harness_z3_nlde_data_request(SL_CLI_COMMAND_ARG)
{
  EmberApsFrame apsFrame = { 0 };
  uint8_t dstAddrMode = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);    // Destination Address Mode : 0x02 = 16 bit short address.
  uint16_t dstAddr = (uint16_t)sl_cli_get_argument_uint16(arguments, 1);      // Destination NWK Address
  uint8_t nsduLength = (uint8_t)sl_cli_get_argument_uint8(arguments, 2);     // NSDU Length
  uint8_t nsdu[200] = { 0 };
  sl_zigbee_copy_hex_arg(arguments, 3, nsdu, nsduLength, true);               // NSDU
  uint8_t nsduHandle = (uint8_t)sl_cli_get_argument_uint8(arguments, 4);     // NSDU Handle
  bool useAlias = (bool)sl_cli_get_argument_uint8(arguments, 5);       // Use Alias for source address
  //NOTE : This EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER falg lets the frame formatter
  // to pick up the supplied frame sequence number the apsFrame.
  // APSDE Data req uses the an internal APS couneter and NWK seq number for normal transmission.
  // It uses supplied sequence (i.e. APS counter = NWK seq) for alias.
  // NLDE receives an NSDU that holds an APS frame, with a counter in side it,
  // to use that counter in the outgoing payload it is needed to use the above flag.
  // (else an auto incremented APS counter will be used by stack - which is an issue.)
  // That is the reason why the flag is used unconditionally, instead of following way
  //  // apsFrame.options |= (useAlias ? EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER : 0);
  apsFrame.options |= EMBER_APS_OPTION_USE_ALIAS_SEQUENCE_NUMBER;

  uint16_t aliasSrcAddr = (uint16_t)sl_cli_get_argument_uint16(arguments, 6); // Alias Source address
  uint8_t aliasSeqNo = (uint8_t)sl_cli_get_argument_uint8(arguments, 7);     // Alias Sequence number
  apsFrame.radius = (uint8_t)sl_cli_get_argument_uint8(arguments, 8);        // radius
  uint8_t nonmemberRadius = (uint8_t)sl_cli_get_argument_uint8(arguments, 9);// Non member radius : We ignore this and this as max hops
  uint8_t discoverRoute = (uint8_t)sl_cli_get_argument_uint8(arguments, 10); // Discover Route
  apsFrame.options |= (discoverRoute ? EMBER_APS_OPTION_ENABLE_ROUTE_DISCOVERY : 0);
  bool securityEnable = (bool)sl_cli_get_argument_uint8(arguments, 11);// Security Enabled : We always send the NWK encrypted messages, so this input is ignored

  //nsdu = apdu = (APS Header + APS Payload)
  //To use the emAfSend for NLDE-DATA.request, it would be required to pick up - clusterId, profile,
  // Extract those from header
  uint8_t index = 0;
  // FC
  uint8_t apsFc = nsdu[index];
  uint8_t frameType = (apsFc & 0x03); // FC b[1-0]
  uint8_t apsDeliveryMode = ((apsFc >> 2) & 0x03);
  //uint8_t apsAckFormat = ((apsFc >> 4) & 0x01);
  bool apsSecurityEnable = (apsFc & 0x20) ? true : false;
  bool apsAck = (apsFc & 0x40) ? true : false;
  bool apsExtHeaderPresent = (apsFc & 0x80) ? true : false;
  // End of FC
  index += 1;
  // only process APS frame type = data at the moment
  if (frameType) {
    return;
  }

  EmberOutgoingMessageType type = EMBER_OUTGOING_DIRECT;
  switch (apsDeliveryMode) {
    case 0x03: // GCAST
      apsFrame.groupId = ((uint16_t)nsdu[index + 1] << 8) + nsdu[index];
      index += 2;
      type = useAlias ? EMBER_OUTGOING_MULTICAST_WITH_ALIAS : EMBER_OUTGOING_MULTICAST;
      break;
    case 0x02: // BCAST
      type = useAlias ? EMBER_OUTGOING_BROADCAST_WITH_ALIAS : EMBER_OUTGOING_BROADCAST;
      apsFrame.destinationEndpoint = nsdu[index];
      index += 1;
      break;
    case 0x00: // UNICAST
      type = EMBER_OUTGOING_DIRECT;
      apsFrame.destinationEndpoint = nsdu[index];
      index += 1;
      break;
    default:
      break;
  }
  apsFrame.clusterId = ((uint16_t)nsdu[index + 1] << 8) + nsdu[index];
  index += 2;
  apsFrame.profileId = ((uint16_t)nsdu[index + 1] << 8) + nsdu[index];
  index += 2;
  apsFrame.sourceEndpoint = nsdu[index];
  index += 1;
  apsFrame.sequence = useAlias ? aliasSeqNo : nsdu[index];
  index += 1;
  uint8_t asduLength = nsduLength - index; //that is actually ZCP PDU (ZCL Header + ZCL SDU) length
  uint8_t * asdu = &nsdu[index];
  uint16_t messageTag = nsduHandle; // This is the NLDE Identifier, the stack will rewite it

  EmberStatus status = sli_zigbee_af_send(type,    //EmberOutgoingMessageType type,
                                          dstAddr, //uint16_t indexOrDestination,
                                          &apsFrame, //EmberApsFrame *apsFrame,
                                          asduLength, //uint8_t messageLength,
                                          asdu, //uint8_t *message,
                                          &messageTag, //uint16_t *messageTag,
                                          aliasSrcAddr, //EmberNodeId alias,
                                          aliasSeqNo); //uint8_t sequence);
  emberAfCorePrintln("nlde-syncfm 0x%X 0x%X", messageTag, status); // Synchronous confirm to ensure packet is submitted to network successfully.
  UNUSED_VAR(dstAddrMode);
  UNUSED_VAR(nonmemberRadius);
  UNUSED_VAR(securityEnable);
  UNUSED_VAR(apsSecurityEnable);
  UNUSED_VAR(apsAck);
  UNUSED_VAR(apsExtHeaderPresent);
}

// sends out an MCPS-DATA.request
void sl_zigbee_test_harness_z3_mcps_data_request(SL_CLI_COMMAND_ARG)
{
  uint8_t srcMode = (uint8_t)sl_cli_get_argument_uint8(arguments, 0); //0 x 00 = no address (addressing fields omitted).
  //0 x 01 = reserved.
  //0 x 02 = 16 bit short address.
  //0 x 03 = 64 bit extended address.
  uint16_t srcPanId = (uint16_t)sl_cli_get_argument_uint16(arguments, 1);
  uint8_t srcAddrStr[8] = { 0 }; //this could be a 16 bit address or ieee address depending on the address mode
  sl_zigbee_copy_hex_arg(arguments, 2, srcAddrStr, 8, true);
  uint8_t dstMode = (uint8_t)sl_cli_get_argument_uint8(arguments, 3);
  uint16_t dstPanId = (uint16_t)sl_cli_get_argument_uint16(arguments, 4);
  uint8_t dstAddrStr[8] = { 0 }; //this could be a 16 bit address or ieee address depending on the address mode
  sl_zigbee_copy_hex_arg(arguments, 5, dstAddrStr, 8, true);
  uint8_t msduLength = (uint8_t)sl_cli_get_argument_uint8(arguments, 6);
  uint8_t msduHandle = (uint8_t)sl_cli_get_argument_uint8(arguments, 8);
  uint8_t options = (uint8_t)sl_cli_get_argument_uint8(arguments, 9); //0 x 01 = acknowledged transmission.
  //0 x 02 = GTS transmission.
  //0 x 04 = indirect transmission.
  //0 x 08 = security enabled transmission.
  uint8_t message[200];
  message[0] = 1;                                  // MAC Header LSB Bit[2-0] : 0=beacon, 1=data, 2=ack, 3=MAC command
  message[0] |= (options & 0x08) ? 0x08 : 0;       // MAC Header LSB Bit[  3] : Security Enable
                                                   // MAC Header LSB Bit[  4] : Frame Pending
  message[0] |= (options & 0x01) ? 0x20 : 0;       // MAC Header LSB Bit[  5] : Security Enable
  message[0] |= (srcPanId == dstPanId) ? 0x40 : 0; // MAC Header LSB Bit[  6] : Intra-PAN

  message[1] =  dstMode << 2; // MAC Header MSB Bit[3-2]
  message[1] |= srcMode << 6; // MAC Header MSB Bit[7-6]
  //message[2]; // this is picked up internally from the macDSN when using the raw send command emberSendRawMessage;
  uint8_t index = 3;
  if (dstMode) {
    message[index] = dstPanId;
    message[index + 1] = dstPanId >> 8;
    index += 2;
    if (dstMode == 2) {
      message[index] = dstAddrStr[6];
      message[index + 1] = dstAddrStr[7];
      index += 2;
    } else if (dstMode == 3) {
      memcpy(&message[index], dstAddrStr, 8);
      index += 8;
    }
  }
  if (srcMode) {
    if ((srcPanId != dstPanId)) {
      message[index] = srcPanId;
      message[index + 1] = srcPanId >> 8;
      index += 2;
    }
    if (srcMode == 2) {
      message[index] = srcAddrStr[6];
      message[index + 1] = srcAddrStr[7];
      index += 2;
    } else if (srcMode == 3) {
      memcpy(&message[index], srcAddrStr, 8);
      index += 8;
    }
  }
  uint8_t *msdu = &message[index];
  sl_zigbee_copy_hex_arg(arguments, 7, msdu, msduLength, true);
  index += msduLength;
  EmberStatus status = 1;
  EmberMessageBuffer buffer = emberFillLinkedBuffers(message, index);
  if (buffer != EMBER_NULL_MESSAGE_BUFFER) {
#if (defined EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE) && (EMBER_AF_TEST_HARNESS_Z3_PLUGIN_MCPS_HANDLE_TO_BUFFER_MAP_SIZE != 0)
    if (pushMap(buffer, msduHandle)) { // Make sure we can hold the handle map for confirmation before sending
      status = emberSendRawMessage(buffer);
    }
#else
    status = emberSendRawMessage(buffer);
    msduHandle = buffer;
#endif
    emberReleaseMessageBuffer(buffer); // Release the message buffer in all cases.
  }
  emberAfCorePrintln("mcpsd-syncfm 0x%X 0x%X", msduHandle, status); // Synchronous confirm to ensure packet is submitted to network successfully.
}

//NWK Layer Attribute Get
void sl_zigbee_test_harness_z3_nwk_pib_get_request(SL_CLI_COMMAND_ARG)
{
  uint8_t status = 1;
  uint8_t pibNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  EmberEUI64 myEui64;
  uint16_t nodeId;
  uint8_t pibValueLength = 0;
  uint8_t pibValue[20] = { 0 };
  EmberNodeType type = EMBER_UNKNOWN_DEVICE;
  EmberNetworkParameters parameters;
  emberAfGetNetworkParameters(&type, &parameters);

  if (EMBER_UNKNOWN_DEVICE != type) {
    switch (pibNumber) {
      case 0x80: // PAN Id
        status = 0;
        pibValueLength = 2;
        memcpy(pibValue, (uint8_t*)(&parameters.panId), pibValueLength);
        break;
      case 0x9A: // Ext PAN Id
        status = 0;
        pibValueLength = 8;
        memcpy(pibValue, (uint8_t*)(parameters.extendedPanId), pibValueLength);
        break;
      case 0x96: // Node Short Id
        status = 0;
        nodeId = emberGetNodeId();
        pibValueLength = 2;
        memcpy(pibValue, (uint8_t*)(&nodeId), pibValueLength);
        break;
      case 0xAE: // Node Long Id
        status = 0;
        emberAfGetEui64(myEui64);
        pibValueLength = 8;
        memcpy(pibValue, (uint8_t*)(myEui64), pibValueLength);
        break;
      default:
        break;
    }
  }
  emberAfCorePrintln("");
  emberAfCorePrint("nlme-get-cfm 0x%X 0x%X 0x%X {", status, pibNumber, pibValueLength);
  emberAfCorePrintBuffer(pibValue, pibValueLength, false);
  emberAfCorePrintln("}");
}
// MAC Layer Attribute Get
void sl_zigbee_test_harness_z3_mac_pib_get_request(SL_CLI_COMMAND_ARG)
{
  uint8_t status = 1;
  uint8_t pibNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  uint8_t pibValueLength = 0;
  uint8_t pibValue[20] = { 0 };
  emberAfCorePrintln("");
  emberAfCorePrint("mlme-get-cfm 0x%X 0x%X 0x%X {", status, pibNumber, pibValueLength);
  emberAfCorePrintBuffer(pibValue, pibValueLength, false);
  emberAfCorePrintln("}");
}
extern void sl_mac_set_next_sequence(uint8_t seq_num);

extern void sli_802154mac_radio_enable_auto_ack(bool enable);
extern bool sli_zigbee_address_matching_is_enabled;
// MAC Layer Attribute Set
void sli_zigbee_test_harness_z3_mac_pib_set_request(SL_CLI_COMMAND_ARG)
{
  uint8_t pibNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  uint8_t pibDataLength = (uint8_t)sl_cli_get_argument_uint8(arguments, 1);
  uint8_t data[20] = { 0 };
  sl_zigbee_copy_string_arg(arguments, 2, data, pibDataLength, false);
  uint8_t status = 1;
  switch (pibNumber) {
    case 0x4c: // macDSN ( Mac data Sequence number), Type = INT8U, one byte
      sl_mac_set_next_sequence(((uint8_t)data[0] - 1));
      status = 0;
      break;
    case 0x51: // macPromiscuousMode, Type = BOOLEAN, one byte
      emRadioEnableAddressMatching((data[0] ? false : true));
      sli_802154mac_radio_enable_auto_ack((data[0] ? false : true));
      status = 0;
      sli_zigbee_address_matching_is_enabled = data[0];
      break;
    case 0x52: // macRxOnWhenIdle, Type = BOOLEAN , one byte
      //emRadioSetIdleMode(EMBER_RADIO_POWER_MODE_RX_ON);
      if (data[0]) {
        //emRadioSetIdleMode(EMBER_RADIO_POWER_MODE_RX_ON);
        emberZllSetRxOnWhenIdle(0xFFFFFFFF);
      } else {
        emberZllSetRxOnWhenIdle(0);
      }
      status = 0;
      break;
    default:
      break;
  }
  emberAfCorePrintln("mlme-set-cfm 0x%X 0x%X", status, pibNumber);
}

// PHY Layer Attribute Get
void sli_zigbee_test_harness_z3_pib_get_request(SL_CLI_COMMAND_ARG)
{
  uint8_t status = 1;
  uint8_t pibNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  uint8_t pibValueLength = 0;
  uint8_t pibValue[20] = { 0 };
  switch (pibNumber) {
    case 0x00: // phyCurrentChannel
      pibValue[0] = sl_mac_lower_mac_get_radio_channel(PHY_INDEX_NATIVE);
      pibValueLength = 1;
      status = 0;
      break;
    default:
      break;
  }
  emberAfCorePrintln("");
  emberAfCorePrint("plme-get-cfm 0x%X 0x%X 0x%X {", status, pibNumber, pibValueLength);
  emberAfCorePrintBuffer(pibValue, pibValueLength, false);
  emberAfCorePrintln("}");
}
// PHY Layer Attribute Set
void sli_zigbee_test_harness_z3_pib_set_request(SL_CLI_COMMAND_ARG)
{
  uint8_t pibNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  uint8_t pibDataLength = (uint8_t)sl_cli_get_argument_uint8(arguments, 1);
  uint8_t data[20] = { 0 };
  sl_zigbee_copy_string_arg(arguments, 2, data, pibDataLength, false);
  uint8_t status = 1;
  switch (pibNumber) {
    case 0x00: // phyCurrentChannel
      if (sl_mac_lower_mac_set_radio_channel(PHY_INDEX_NATIVE, (data[0])) == EMBER_PHY_INVALID_CHANNEL) {
        status = 1;
      } else {
        // The PHY has changed the channel,now change the network channel
        sli_zigbee_stack_radio_channel = data[0];
        status = 0;
      }
      break;
    default:
      break;
  }
  emberAfCorePrintln("plme-set-cfm 0x%X 0x%X", status, pibNumber);
}
// Does the indication printing and return TRUE if the packet need to be dropped
static bool layeredHandlingMode(EmberZigbeePacketType packetType,
                                uint8_t* packetData,
                                uint8_t* size_p,
                                void *data)
{
  bool drop = false;
  uint8_t packetLength = *size_p;
  // Layer printing --------------------------
  switch (packetType) {
    // packetType EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA is decrypted NWK payload
    case EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA: {
      if (indicationMask & INDICATION_LAYER_NLDE) {
        uint8_t *frame                = emHeaderRoutingFrame(emTempHandoffHeader);
        EmberNodeId zigbeeDestination = emZigbeeDestination(frame);
        EmberNodeId zigbeeSource      = emZigbeeSource(frame);
        uint8_t nwkSeqNumber = emZigbeeSequence(frame);
        bool securityUse = (((frame)[1]) & 0x02u);
        emberAfCorePrintln("");
        emberAfCorePrint("nlde-ind 0x%X ", nwkSeqNumber);
        emberAfCorePrint("0x%X 0x%2X 0x%2X 0x%X {",
                         2, zigbeeDestination, zigbeeSource, (*size_p - NWK_MAC_HEADER_SIZE));
        emberAfCorePrintBuffer((packetData + NWK_MAC_HEADER_SIZE), (*size_p - NWK_MAC_HEADER_SIZE), false);   // spaces?
        emberAfCorePrint("}");

        extern uint8_t sli_zigbee_current_lqi;
        uint8_t linkQuality = sli_zigbee_current_lqi;
        emberAfCorePrintln(" 0x%X 0x%X", linkQuality, securityUse);
      }
      if (dropMask & DROP_NLDE) {
        drop = true;
        return drop;
      }
    }
    break;

    case EMBER_ZIGBEE_PACKET_TYPE_APS_DATA:
    {
      uint8_t *frame                = emHeaderRoutingFrame(emTempHandoffHeader);
      EmberNodeId zigbeeDestination = emZigbeeDestination(frame);
      EmberNodeId zigbeeSource      = emZigbeeSource(frame);
      if (indicationMask & INDICATION_LAYER_APSDE) {
        // Pick up the network header to get the addresses

        uint8_t *finger = (uint8_t*) packetData;
        uint8_t fc = *finger++;
        if ((fc & 0x03) == 0) { // b[1-0] - 00=data,01=Cmd,10=Ack,11=InterPan APS
          uint8_t deliveryMode = ((fc & 0x0c) >> 2); // b[2-3] - 00=UCAST, 01=Reserved, 10=BCAST, 11=GCAST
          uint16_t group_address = 0;
          uint8_t dest_ep = 0;
          if (deliveryMode == 3) { // groupcast
            group_address = emberAfGetInt16u(finger, 0, packetLength);
            finger += 2;
          } else {
            dest_ep = *finger++;
          }
          uint16_t cluster = emberAfGetInt16u(finger, 0, packetLength);
          finger += 2;
          uint16_t profile = emberAfGetInt16u(finger, 0, packetLength);
          finger += 2;
          uint8_t source_ep = *finger++;
          uint8_t apsCounter = *finger++;
          uint8_t dstMode = 0xFF;
          uint16_t dstAddress = 0xFFFF;
          switch (deliveryMode) {
            case 0: //00=UCAST
              dstMode = 2; //0x02 = 16-bit address for DstAddress and DstEndpoint present
              dstAddress = zigbeeDestination; // need to get this from the nwk frame
              break;
            case 2:
              dstMode = 2;
              break;
            case 3:
              dstMode = 1;
              dstAddress = group_address;
              break;
            default:
              break;
          }
          uint8_t srcMode = 2; // Assumed - need to pull this out from nwk frame
          uint16_t srcAddress = zigbeeSource; // get current sender from the nwk frame
          if (*size_p >= (finger - packetData)) {
            emberAfCorePrintln("");
            emberAfCorePrint("apsde-ind 0x%X ", apsCounter);
            // DstAddMode: 0=RESER, 1=GCAST, 2=UCAST, 3=EUI64, 4= EUI64withOutEp
            emberAfCorePrint("0x%X {%X%X} 0x%X 0x%X {%X%X} 0x%X 0x%2X 0x%2X 0x%X {",
                             dstMode, (uint8_t)dstAddress, (uint8_t)(dstAddress >> 8), dest_ep,
                             srcMode, (uint8_t)srcAddress, (uint8_t)(srcAddress >> 8), source_ep,
                             profile, cluster, (*size_p - (finger - packetData)));
            emberAfCorePrintBuffer(finger, (*size_p - (finger - packetData)), false); // spaces?
            emberAfCorePrint("}");
            uint8_t status = 0;
            uint8_t securityStatus = 0xAC; //SECURED_NWK_KEY : An ASDU was received that was secured using a network key
            // This variable emCurrentLqi is updated with current frame LQI in function emNetworkCheckIncomingQueue,
            // before calling the packethandoff function with type = EMBER_ZIGBEE_PACKET_TYPE_NWK_DATA. So lets us just use that.
            extern uint8_t sli_zigbee_current_lqi;
            uint8_t linkQuality = sli_zigbee_current_lqi;
            emberAfCorePrintln(" 0x%X 0x%X 0x%X", status, securityStatus, linkQuality);
          }
        }
      }
      if (dropMask & DROP_APSDE) {
        drop = true;
        return drop;
      }
      break;
    }
    case EMBER_ZIGBEE_PACKET_TYPE_RAW_MAC: {
      // For EMBER_ZIGBEE_PACKET_TYPE_RAW_MAC, there is an 8 bytes of PHY appended info
      // consider those bytes while taking length
      if (indicationMask & INDICATION_LAYER_MCPSD) {
        uint8_t frameType = (packetData[0] & 0x07);               // Frame Type : MAC FC Low Bit[2-0]
        if (frameType != 1) { // if not DATA (then it 'll be Beacon or Ack or Command), then handle as MLME at a different place, not here
          return false;
        }
        bool securityUse = (packetData[0] & 0x08) ? true : false; // Security use : MAC FC Low Bit[3]
        bool intraPan = (packetData[0] & 0x40) ? true : false;    // Intra PAN : MAC FC Low Bit[6]
        uint8_t dstMode =  ((packetData[1] & 0x0c) >> 2);         // Dst Mode : MAC FC High Bit [3-2]
        uint8_t srcMode =  ((packetData[1] & 0xc0) >> 6);         // Src Mode : MAC FC High Bit [7-6]
        uint8_t macSeqNo = packetData[2];
        uint8_t index = 3; // Addressing mode starts from this index
        // Extract destination addressing details
        uint16_t dstPanId = 0;
        uint8_t *dstAddr = NULL;
        if (dstMode) {
          dstPanId = ((uint16_t)(packetData[index + 1]) << 8) + packetData[index];
          index += 2;
          if (dstMode == 2) { //16-Bit short address
            dstAddr = &(packetData[index]);
            index += 2;
          } else if (dstMode == 3) { // Long address
            dstAddr = &(packetData[index]);
            index += 8;
          }
        }
        // Extract destination addressing details
        uint16_t srcPanId = dstPanId;
        uint8_t *srcAddr = NULL;
        if (srcMode) {
          if (!intraPan) { // In case of Intra-PAN, Source PAN ID is not present in incoming command
            srcPanId = ((uint16_t)(packetData[index + 1]) << 8) + packetData[index];
            index += 2;
          }
          if (srcMode == 2) { //16-Bit short address
            srcAddr = &(packetData[index]);
            index += 2;
          } else if (srcMode == 3) { // Long address
            srcAddr = &(packetData[index]);
            index += 8;
          }
        }
        emberAfCorePrintln("");
        emberAfCorePrint("mcpsd-ind 0x%X ", macSeqNo);
        // Print Source addressing details
        emberAfCorePrint("0x%X ", srcMode);
        emberAfCorePrint("0x%2X ", srcPanId);
        emberAfCorePrint("{");
        if (srcMode == 2) {
          emberAfCorePrintBuffer(srcAddr, 2, false);
        } else if (srcMode == 3) {
          emberAfCorePrintBuffer(srcAddr, 8, false);
        } else {
          emberAfCorePrint("%X", 0);
        }
        emberAfCorePrint("} ");
        // Print Destination addressing details
        emberAfCorePrint("0x%X ", dstMode);
        emberAfCorePrint("0x%2X ", dstPanId);
        emberAfCorePrint("{");
        if (dstMode == 2) {
          emberAfCorePrintBuffer(dstAddr, 2, false);
        } else if (dstMode == 3) {
          emberAfCorePrintBuffer(dstAddr, 8, false);
        } else {
          emberAfCorePrint("%X", 0);
        }
        emberAfCorePrint("} ");
        uint8_t msduLength = (packetLength - index - NWK_MAC_HEADER_SIZE);  // Packet Length -  header (i.e index) - 8 bytes of PHY Added Info
        emberAfCorePrint("0x%X {", msduLength);
        emberAfCorePrintBuffer(&packetData[index], msduLength, false);
        emberAfCorePrint("} ");
        uint8_t *appndedInfoBytes = &packetData[packetLength - NWK_MAC_HEADER_SIZE];
        uint8_t linkQuality = appndedInfoBytes[3]; // Appended Info byte array index 3 holds the LQI - ref: phy-appended-info.h
        emberAfCorePrint("0x%X ", linkQuality); // Link Quality
        emberAfCorePrint("0x%X ", securityUse); // Security Use
        emberAfCorePrintln("0x%X", 8); // ACL Entry Index
      }
      if (dropMask & DROP_MCPSD) {
        drop = true;
        return drop;
      }
      break;
    }
    default:
      break;
  }
  //--------------------------------------------
  return drop;
}

// plugin test-harness z3 set-network-key [networkKey:-1]
void sli_zigbee_test_harness_z3_set_network_key_command(SL_CLI_COMMAND_ARG)
{
  uint8_t status = EMBER_ERR_FATAL;
  if (emberGetNodeId() == 0xFFFE) {
    status = EMBER_SUCCESS;
    sl_zigbee_copy_hex_arg(arguments, 0,
                           preProgrammedNwkKey.contents,
                           EMBER_ENCRYPTION_KEY_SIZE,
                           true);
  }
  emberAfCorePrintln("test-harness z3 set-network-key-cfm 0x%X", status);
}

bool sl_zigbee_af_network_creator_security_get_key_callback(EmberKeyData * keyData)
{
  MEMMOVE(keyData->contents,
          preProgrammedNwkKey.contents,
          EMBER_ENCRYPTION_KEY_SIZE);
  return true;
}
// plugin test-harness z3 set-network-key-with-options
// [networkKey:-1] [sequenceNumber:1] [current:1]
void sli_zigbee_test_harness_z3_network_key_with_options_command(SL_CLI_COMMAND_ARG)
{
#ifndef EZSP_HOST
  // EMZIGBEE-4614: The emberAfPluginTestHarnessSetNwkKeyCommand
  // is for a Test Harness feature to support the WWAH Test Case
  // where the harness device needs to use a specific network key.
  EmberKeyData keyData;
  sl_zigbee_copy_key_arg(0, 0, &keyData);

  uint8_t keySequenceNumber = (uint8_t)sl_cli_get_argument_uint8(arguments, 1);
  bool current = (bool)sl_cli_get_argument_uint8(arguments, 2);
  sli_zigbee_set_network_key(&keyData, keySequenceNumber, current);
  emberAfCorePrintln("%p: %p: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Set network key with options",
                     EMBER_SUCCESS);
#else
  emberAfCorePrintln("%p: %p : %p : 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Set network key",
                     "Not supported on host",
                     EMBER_INVALID_CALL);
#endif
}

void zdoUserCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  EmberStatus status = emberUserDescriptorRequest(target,
                                                  EMBER_AF_DEFAULT_APS_OPTIONS);
  sl_zigbee_app_debug_println("ZDO user desc req %x", status);
}

#define APP_ZDO_BUFFER_SIZE 32
static uint8_t zdoRawBuffer[APP_ZDO_BUFFER_SIZE + ZDO_MESSAGE_OVERHEAD];

void zdoRawCommand(sl_cli_command_arg_t *args)
{
  EmberNodeId target = (EmberNodeId)sl_cli_get_argument_uint16(args, 0);
  uint16_t cluster = (uint16_t)sl_cli_get_argument_uint16(args, 1);
  uint8_t size = sl_zigbee_copy_hex_arg((args), 2, zdoRawBuffer + ZDO_MESSAGE_OVERHEAD, APP_ZDO_BUFFER_SIZE, false);
  EmberStatus status = emberSendZigDevRequest(target,
                                              cluster,
                                              EMBER_AF_DEFAULT_APS_OPTIONS,
                                              zdoRawBuffer,
                                              size + 1); // incl overhead (seq no)
  sl_zigbee_app_debug_println("ZDO raw req %x, %d bytes", status, size);
}

EmberStatus emberUserDescriptorRequest(EmberNodeId target,
                                       EmberApsOption options)
{
  uint8_t contents[ZDO_MESSAGE_OVERHEAD + 2];
  uint8_t *payload = contents + ZDO_MESSAGE_OVERHEAD;
  payload[0] = LOW_BYTE(target);
  payload[1] = HIGH_BYTE(target);
  return emberSendZigDevRequest(target,
                                USER_DESCRIPTOR_REQUEST,
                                options,
                                contents,
                                sizeof(contents));
}
