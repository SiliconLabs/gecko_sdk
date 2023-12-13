/***************************************************************************//**
 * @file
 * @brief ZigBee 3.0 touchlink test harness functionality
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

#include "test-harness-z3-core.h"
#include "test-harness-z3-zll.h"
#include "test-harness-z3-mac.h"

#include "app/framework/plugin/zll-commissioning-common/zll-commissioning.h"
#include "app/framework/plugin/interpan/interpan.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_NETWORK_CREATOR_PRESENT
#include "network-creator.h"
#endif

#include "app/framework/util/common.h"

// -----------------------------------------------------------------------------
// Types

typedef struct {
  uint32_t transactionId;
  EmberAfProfileId profileId;
  uint16_t keyBitmask;
  bool setReservedInformationBits;
  uint8_t networkUpdateId;
  uint8_t numberSubDevices;
  uint8_t totalGroupIds;
  EmberEUI64 destinationEui64;
} ScanResponseData;

// -----------------------------------------------------------------------------
// Globals
extern uint8_t sli_zigbee_set_nwk_update_id(uint8_t id);
// We need this extern'd for unit tests since the zll-commissioning.h extern
// might not be compiled in.
#if defined(EMBER_SCRIPTED_TEST)
extern uint32_t sli_zigbee_af_zll_secondary_channel_mask;
#endif

EmberZllNetwork zllNetwork = { { 0, }, { 0, 0, 0 }, };  // non-static - used by -core.c
#define initZllNetwork(network) \
  do { MEMMOVE(&zllNetwork, network, sizeof(EmberZllNetwork)); } while (0);
#define deinitZllNetwork() \
  do { zllNetwork.securityAlgorithm.transactionId = 0; } while (0);
#define zllNetworkIsInit() \
  (zllNetwork.securityAlgorithm.transactionId != 0)

#define STATE_NOT_SCANNING     (0x00)
#define STATE_PRIMARY_CHANNELS (0x01)
#define STATE_SCANNING         (0x02)
static uint8_t scanningState;

#define NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE (BIT32(0))
#define NEGATIVE_BEHAVIOR_DELAY_RESPONSE     (BIT32(1))
#define NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE  (BIT32(2))
#define NEGATIVE_BEHAVIOR_POSITIVE_RESPONSE  (BIT32(3))
#define NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID (BIT32(4))
#define NEGATIVE_BEHAVIOR_BAD_COMMAND_ID     (BIT32(5))
#define NEGATIVE_BEHAVIOR_BAD_SOURCE_ADDRESS (BIT32(6))
#define NEGATIVE_BEHAVIOR_BAD_STATUS         (BIT32(7))
#define NEGATIVE_BEHAVIOR_SET_ZLL_RESERVED_BITS (BIT32(8))
#define NEGATIVE_BEHAVIOR_SET_ZB_RESERVED_BITS  (BIT32(9))
#define NEGATIVE_BEHAVIOR_CLEAR_INITIATOR_BIT   (BIT32(10))
#define NEGATIVE_BEHAVIOR_SET_INITIATOR_BIT     (BIT32(11))
static uint32_t negativeBehaviorMask = 0;
static uint8_t negativeBehaviorCommandId = 0xFF;
static uint32_t responseBehaviorMask = 0;
static uint8_t responseBehaviorCommandId = 0xFF;
static uint32_t scanBehaviorMask = 0;
static uint32_t lastTransactionId = 0;

#define ZLL_RESERVED_BITS (0x4c)
#define ZB_RESERVED_BITS  (0xf8)

uint8_t realNetworkUpdateId = 0xff;

static ScanResponseData globalScanResponseData = { 0, };
static bool isDelayingScanResponse = false;

sl_zigbee_event_t emberAfPluginTestHarnessZ3ZllStuffEvent;
#define z3ZllStuffEventControl (&emberAfPluginTestHarnessZ3ZllStuffEvent)
void emberAfPluginTestHarnessZ3ZllStuffEventHandler(sl_zigbee_event_t * event);

#define ZLL_STUFF_EVENT_CONTROL_ACTION_SCAN_RESPONSE (0x00)
#define ZLL_STUFF_EVENT_CONTROL_ACTION_NULL          (0xFF)
static uint8_t zllStuffEventControlAction;

#define RESPONSE_ID 0xACACACAC

#define ENDPOINT       0x01
#define DEVICE_ID      0x1234
#define DEVICE_VERSION 0x01
#define GROUP_COUNT    0x00

// private stack API's
void sli_zigbee_af_zll_set_forced_address_assignment(EmberZllAddressAssignment *assignment);
void sli_zigbee_af_zll_clear_forced_address_assignment(void);
extern void sli_zigbee_set_pan_id(EmberPanId panId);
extern void emRadioEnableAddressMatching(uint8_t enable);

// private plugin API's.
EmberStatus sli_zigbee_af_zll_form_networkForRouterInitiator(uint8_t channel, int8_t radioPower, EmberPanId panId);

// MAC header constants (see interpan.c for details)
//ToDo: EMZIGBEE-4854 instead of this we need to use the umac version
#ifdef EZSP_HOST
#define MAC_FRAME_SOURCE_MODE_LONG  0xC000
#define MAC_FRAME_DESTINATION_MODE_LONG    0x0C00
#endif

#define LONG_DEST_FRAME_CONTROL  (MAC_FRAME_TYPE_DATA               \
                                  | MAC_FRAME_DESTINATION_MODE_LONG \
                                  | MAC_FRAME_SOURCE_MODE_LONG)
#define MAC_ACK_REQUIRED              0x0020
#define BROADCAST_PAN_ID 0xffff

// -----------------------------------------------------------------------------
// Util

static EmberStatus startScan(void)
{
  EmberNodeType nodeType;

  nodeType = sli_zigbee_af_current_zigbee_pro_network->nodeType;

  emberAfDebugPrintln("startScan: scanningState = %X, dev mode = %d, nodeType = %d", scanningState, sli_zigbee_af_test_harness_z3_device_mode, nodeType);
  return emberZllStartScan((scanningState & STATE_PRIMARY_CHANNELS) ? emberGetZllPrimaryChannelMask() : emberGetZllSecondaryChannelMask(),
                           0, // default power
                           nodeType);
}

static EmberNodeType getLogicalNodeType(void)
{
  EmberNodeType nodeType;
  EmberStatus status = emberAfGetNodeType(&nodeType);

  // Note, we only report as a coordinator if we are a currently
  // coordinator on a centralized network, otherwise we use the
  // framework node type (which will be router in this case).
  if (status == EMBER_NOT_JOINED) {
    nodeType = sli_zigbee_af_current_zigbee_pro_network->nodeType;
  }
  emberAfCorePrintln("getLogicalNodeType: node type = %d", nodeType);
  return nodeType;
}

static uint8_t zigbeeInformation(void)
{
  uint8_t byte = 0x00;

  EmberNodeType nodeType = getLogicalNodeType();
  // Set zigbee information based on the node type
  switch (nodeType) {
    case EMBER_COORDINATOR:
      byte = 0x04; //EMBER_COORDINATOR with RX ON When Idle
      break;
    case EMBER_ROUTER:
      byte = (0x01 | 0x04); // EMBER_ROUTER with RX ON When Idle
      break;
    case EMBER_END_DEVICE:
      byte = (0x02 | 0x04);  // ED with RX ON When Idle
      break;
    case EMBER_SLEEPY_END_DEVICE:
      byte = 0x02;  // ED without RX ON When Idle
    default:
      break; // nothing
  }

  if (globalScanResponseData.setReservedInformationBits) {
    byte |= (0xF0 | 0x08);
  }

  return byte;
}

static uint8_t zllInformation(void)
{
  uint8_t byte;
  EmberTokTypeStackZllData token;

  emberZllGetTokenStackZllData(&token);
  byte = BYTE_0(token.bitmask);

  switch (sli_zigbee_af_test_harness_z3_device_mode) {
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZR_NOT_ADDRESS_ASSIGNABLE:
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZED_NOT_ADDRESS_ASSIGNABLE:
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_SLEEPY_ZED_NOT_ADDRESS_ASSIGNABLE:
      byte &= ~(EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE | EMBER_ZLL_STATE_LINK_INITIATOR);
      break;
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZR_ADDRESS_ASSIGNABLE:
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_ZED_ADDRESS_ASSIGNABLE:
    case EM_AF_PLUGIN_TEST_HARNESS_Z3_DEVICE_MODE_SLEEPY_ZED_ADDRESS_ASSIGNABLE:
    default:
      byte |= (EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE | EMBER_ZLL_STATE_LINK_INITIATOR);
      break;
  }

  if (globalScanResponseData.setReservedInformationBits) {
    byte |= (0x40 | 0x0C);
  }

  return byte;
}

extern uint32_t sli_zigbee_zll_generate_response_id(uint32_t transactionId);
// Uses the global variable globalScanResponseData.
static EmberStatus sendScanResponse(void)
{
  EmberStatus status;
  EmberNodeType nodeType;
  EmberNetworkParameters networkParams;
  static uint8_t payload[39]; // scan response payload is 39 bytes with one sub-device

  uint8_t *finger = payload;

  status = emberAfGetNetworkParameters(&nodeType, &networkParams);
  if (status == EMBER_NOT_JOINED) {
    networkParams.radioChannel = emberGetRadioChannel(); // this is our default radio channel
    do {
      emberGetTrueRandomNumberArray((uint16_t*)(&networkParams.panId), 1);
    } while (networkParams.panId == 0 || networkParams.panId == 0xffff);  // make sure it is valid
    emberGetTrueRandomNumberArray((uint16_t*)(networkParams.extendedPanId), EXTENDED_PAN_ID_SIZE >> 1);

    // Save the (dummy) PAN id for insertion into the MAC header for this message,
    // and for any subsequent touchlink responses.
    sli_zigbee_set_pan_id(networkParams.panId);
  }

  // ZCL.
  *finger++ = (ZCL_CLUSTER_SPECIFIC_COMMAND
               | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
               | ZCL_DISABLE_DEFAULT_RESPONSE_MASK);
  *finger++ = emberAfNextSequence();
  *finger++ = ZCL_SCAN_RESPONSE_COMMAND_ID;

  // ZLL.
  emberAfCopyInt32u(finger, 0, globalScanResponseData.transactionId);
  emberAfCorePrintln("sendScanResponse: tr id = %4X", globalScanResponseData.transactionId);
  finger += sizeof(globalScanResponseData.transactionId);
  *finger++ = 0x00; // RSSI correction - whatever
  *finger++ = zigbeeInformation();
  *finger++ = zllInformation();
  emberAfCopyInt16u(finger, 0, globalScanResponseData.keyBitmask);
  finger += sizeof(globalScanResponseData.keyBitmask);

  // The purpose of this stack call is really to register 'their' transaction id
  // with the zll library, in case we are expecting a proper network request to
  // follow our mangled scan response (and maybe our mangled dev info responses).
  uint32_t responseId = sli_zigbee_zll_generate_response_id(globalScanResponseData.transactionId);
  emberAfCopyInt32u(finger, 0, responseId);
  finger += sizeof(responseId);
  MEMMOVE(finger, networkParams.extendedPanId, EXTENDED_PAN_ID_SIZE);
  finger += EXTENDED_PAN_ID_SIZE;
  *finger++ = globalScanResponseData.networkUpdateId;
  *finger++ = networkParams.radioChannel;
  emberAfCopyInt16u(finger, 0, networkParams.panId);
  finger += sizeof(networkParams.panId);
  emberAfCopyInt16u(finger, 0, emberGetNodeId());  // Network address
  finger += sizeof(EmberNodeId);
  *finger++ = globalScanResponseData.numberSubDevices;
  *finger++ = globalScanResponseData.totalGroupIds;

  if (globalScanResponseData.numberSubDevices == 1) {
    // Sub-device info goes into scan response.
    *finger++ = 0x01; // endpoint
    emberAfCopyInt16u(finger, 0, globalScanResponseData.profileId);
    finger += sizeof(globalScanResponseData.profileId);
    emberAfCopyInt16u(finger, 0, DEVICE_ID);
    finger += sizeof(uint16_t);
    *finger++ = DEVICE_VERSION;
    *finger++ = GROUP_COUNT;
  }

  // Calculate actual payload length.
  uint16_t payloadLength = finger - payload;

  status = emberAfSendInterPan(0xFFFF, // pan ID
                               globalScanResponseData.destinationEui64,
                               emberLookupNodeIdByEui64(globalScanResponseData.destinationEui64),
                               0xFFFF, // multicast id - whatever
                               ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                               globalScanResponseData.profileId,
                               payloadLength,
                               payload);

  return status;
}

void sendDeviceInfoResponse(const EmberEUI64 source,
                            uint32_t transaction,
                            uint8_t startIndex)
{
  EmberEUI64 eui64;
  EmberStatus status;
  static uint8_t payload[74]; // device info max payload length = 74 (4 sub-device records)
  uint8_t *finger = payload;

  // ZCL.
  *finger++ = (ZCL_CLUSTER_SPECIFIC_COMMAND
               | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT
               | ZCL_DISABLE_DEFAULT_RESPONSE_MASK);
  *finger++ = emberAfNextSequence();
  *finger++ = ZCL_DEVICE_INFORMATION_RESPONSE_COMMAND_ID;

  // ZLL.
  emberAfCopyInt32u(finger, 0, transaction);
  finger += sizeof(transaction);
  *finger++ = globalScanResponseData.numberSubDevices;
  *finger++ = startIndex;

  uint8_t *recordCountPtr = finger++;
  *recordCountPtr = 0;

  emberAfCorePrintln("sendDeviceInfoResponse 0x%4x, 0x%x",
                     transaction,
                     startIndex);

  // Set up some canned data for all sub-records.
  emberAfGetEui64(eui64);
  uint8_t deviceVersion = emberAfDeviceVersionFromIndex(0);
  EmberAfProfileId profileId = emberAfProfileIdFromIndex(0);
  uint16_t deviceId = emberAfDeviceIdFromIndex(0);
  uint8_t groupCount = globalScanResponseData.totalGroupIds;

  for (uint8_t i = startIndex; i < globalScanResponseData.numberSubDevices && *recordCountPtr < 4; i++) {
    // Add up to four sub-device records to the message.
    emberAfDebugPrintln("Adding sub-device record: i = %d, recordCount = %d", i, *recordCountPtr);
    MEMMOVE(finger, eui64, EUI64_SIZE);
    finger += EUI64_SIZE;
    *finger++ = i + 1; // endpoint (from 1)
    emberAfCopyInt16u(finger, 0, profileId);
    finger += sizeof(profileId);
    emberAfCopyInt16u(finger, 0, deviceId);
    finger += sizeof(deviceId);
    *finger++ = deviceVersion;
    *finger++ = groupCount;
    *finger++ = i; // sort order
    (*recordCountPtr)++;
  }

  // Calculate actual payload length.
  uint8_t payloadLength = finger - payload;
  status = emberAfSendInterPan(0xFFFF, // pan ID
                               globalScanResponseData.destinationEui64,
                               emberLookupNodeIdByEui64(globalScanResponseData.destinationEui64),
                               0xFFFF, // multicast id - whatever
                               ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                               globalScanResponseData.profileId,
                               payloadLength,
                               payload);
  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("%p%p failed 0x%x",
                       "Error: ",
                       "Device information response",
                       status);
  }
}

static uint8_t networkUpdateId(void)
{
  EmberNodeType nodeType;
  EmberNetworkParameters networkParams;

  emberAfGetNetworkParameters(&nodeType, &networkParams);

  return networkParams.nwkUpdateId;
}

// -----------------------------------------------------------------------------
// Touchlink CLI Commands

// plugin test-harness z3 touchlink scan-request-process <linkInitiator:1>
// <unused:1> <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_scan_request_process_command(SL_CLI_COMMAND_ARG)
{
  EmberStatus status = EMBER_INVALID_CALL;

#ifndef EZSP_HOST
  uint8_t linkInitiator = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t options      = sl_cli_get_argument_uint32(arguments, 2);
  sl_zigbee_app_debug_println("Scan request process: linkInitiator = %d, options = %4X", linkInitiator, options);
  // Assume we're starting with the primary channel mask.
  scanningState = STATE_NOT_SCANNING | STATE_PRIMARY_CHANNELS;
  if (options & BIT32(1)) {
    // Use current channel for scanning.
    emberSetZllPrimaryChannelMask(BIT32(emberAfGetRadioChannel()));
    emberSetZllSecondaryChannelMask(0);
  } else if (options & BIT32(4)) {
    // Only use secondary channels for scanning.
    emberSetZllPrimaryChannelMask(0);
    emberSetZllSecondaryChannelMask(EMBER_ZLL_SECONDARY_CHANNEL_MASK);
    scanningState &= ~STATE_PRIMARY_CHANNELS;
  }

  // Set a mask for the outgoing message hook function.
  scanBehaviorMask = 0;
  if (options & BIT32(0)) {
    scanBehaviorMask |= NEGATIVE_BEHAVIOR_SET_ZLL_RESERVED_BITS;
  }
  if (options & BIT32(5)) {
    scanBehaviorMask |= NEGATIVE_BEHAVIOR_SET_ZB_RESERVED_BITS;
  }

  // We'll use the outgoing message hook to update the initiator bit,
  // otherwise, we would have to (temporarily) update the stack token.
  if (linkInitiator == 1) {
    scanBehaviorMask |= NEGATIVE_BEHAVIOR_SET_INITIATOR_BIT;
  } else if (linkInitiator == 0) {
    scanBehaviorMask |= NEGATIVE_BEHAVIOR_CLEAR_INITIATOR_BIT;
  }

  // Set the enabled and target bits of the touchlinking policy.
  EmberZllPolicy policy = emberZllGetPolicy();  // use Ember API directly
  policy |= EMBER_ZLL_POLICY_ENABLED;
  if (options & BIT32(3)) {
    policy &= ~EMBER_ZLL_POLICY_TARGET;   // reject scan-requests
  } else {
    policy |= EMBER_ZLL_POLICY_TARGET;
  }
  emberZllSetPolicy(policy);

  sl_zigbee_app_debug_println("Scan request process: scanningState = %d, scanBehaviorMask = %4X, policy = %X", scanningState, scanBehaviorMask, policy);

  // Set security for a new scan.
  emberAfZllSetInitialSecurityState();

  if ((status  = startScan()) == EMBER_SUCCESS) {
    scanningState |= STATE_SCANNING;
  }
#endif /* EZSP_HOST */

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Scan request process",
                     status);
}

// plugin test-harness z3 touchlink start-as-router
void sli_zigbee_af_test_harness_z3_touchlink_start_as_router_command(SL_CLI_COMMAND_ARG)
{
#ifdef SL_CATALOG_ZIGBEE_NETWORK_CREATOR_PRESENT

  EmberPanId panId = sl_cli_get_argument_uint16(arguments, 0);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 1);

  EmberStatus status = EMBER_INVALID_CALL;

  // This options bitmask is currently unused.
  (void)options;

  if (zllNetworkIsInit()) {
    status = sli_zigbee_af_zll_form_networkForRouterInitiator(zllNetwork.zigbeeNetwork.channel,
                                                              EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER,
                                                              panId);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Start as router",
                     status);
#endif
}

// plugin test-harness z3 touchlink is-scanning
void sli_zigbee_af_test_harness_z3_touchlink_is_scanning_command(SL_CLI_COMMAND_ARG)
{
  emberAfCorePrintln("scanning:%s",
                     (scanningState & STATE_SCANNING ? "true" : "false"));
}
extern uint8_t sl_mac_lower_mac_get_radio_channel(uint8_t mac_index);
// plugin test-harness z3 touchlink device-information-request
// <startIndex:1> <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_device_information_request_command(SL_CLI_COMMAND_ARG)
{
  uint8_t startIndex = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 1);

  EmberStatus status = EMBER_INVALID_CALL;

  uint32_t interpanTransactionId = zllNetwork.securityAlgorithm.transactionId;
  if (options & BIT(0)) {
    interpanTransactionId--;
  }

  emberAfDebugPrintln("DeviceInfoRq, zllNetworkIsInit(): %d, tr id = %d", zllNetworkIsInit(), interpanTransactionId);
  if (zllNetworkIsInit()) {
    (void) emberAfFillExternalBuffer(EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL,
                                     ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                     ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID,
                                     "wu",
                                     interpanTransactionId,
                                     startIndex);
    status = emberAfSendCommandInterPan(0xFFFF,                // destination pan id
                                        zllNetwork.eui64,
                                        EMBER_NULL_NODE_ID,    // node id - ignored
                                        0x0000,                // group id - ignored
                                        sli_zigbee_af_test_harness_z3_touchlink_profile_id);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Device information request",
                     status);
}

// plugin test-harness z3 touchlink device-information-request-w-target
// <startIndex:1> <shortAddress:2> <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_device_information_request_w_target_command(SL_CLI_COMMAND_ARG)
{
  uint8_t startIndex = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t shortAddress = sl_cli_get_argument_uint16(arguments, 1);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 2);

  EmberStatus status = EMBER_INVALID_CALL;

  uint32_t interpanTransactionId = zllNetwork.securityAlgorithm.transactionId;
  if (options & BIT(0)) {
    interpanTransactionId--;
  }
  (void)options;

  if (zllNetworkIsInit()) {
    (void) emberAfFillExternalBuffer(EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL,
                                     ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                     ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID,
                                     "wu",
                                     interpanTransactionId,
                                     startIndex);
    // TODO: It would probably be better to use ZDO to get the target EUI64, but
    // then we would still need to do a scan to start an active transaction.
    status = emberAfSendCommandInterPan(0xFFFF, // destination pan id
                                        zllNetwork.eui64,  // to keep NWK happy
                                        shortAddress, // node id
                                        0x0000,       // group id - ignored
                                        sli_zigbee_af_test_harness_z3_touchlink_profile_id);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Device information request w target",
                     status);
}

// plugin test-harness z3 touchlink identify-request <duration:2> <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_identify_request_command(SL_CLI_COMMAND_ARG)
{
  uint16_t duration = sl_cli_get_argument_uint16(arguments, 0);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 1);

  EmberStatus status = EMBER_INVALID_CALL;

  uint32_t interpanTransactionId = zllNetwork.securityAlgorithm.transactionId;
  if (options & BIT(0)) {
    interpanTransactionId--;
  }

  if (zllNetworkIsInit()) {
    (void) emberAfFillExternalBuffer(EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL,
                                     ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                     ZCL_IDENTIFY_REQUEST_COMMAND_ID,
                                     "wv",
                                     interpanTransactionId,
                                     duration);
    status = emberAfSendCommandInterPan(0xFFFF,     // destination pan id
                                        zllNetwork.eui64,
                                        EMBER_NULL_NODE_ID, // node id - ignored
                                        0x0000,           // group id - ignored
                                        sli_zigbee_af_test_harness_z3_touchlink_profile_id);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Identify request",
                     status);
}

// plugin test-harness z3 touchlink reset-to-factory-new-request <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_rtfn_request_command(SL_CLI_COMMAND_ARG)
{
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 0);
  EmberStatus status = EMBER_INVALID_CALL;

  // We currently do not have a way to use the option bitmask.
  (void)options;

  if (zllNetworkIsInit()) {
    (void) emberAfFillExternalBuffer(EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL,
                                     ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                     ZCL_RESET_TO_FACTORY_NEW_REQUEST_COMMAND_ID,
                                     "w",
                                     zllNetwork.securityAlgorithm.transactionId);
    if (options & BIT(0)) {
      status = emberAfSendCommandInterPan(0xFFFF,     // destination pan id
                                          NULL,       // long id - ignored
                                          EMBER_BROADCAST_ADDRESS,// bcast
                                          0x0000,     // group id - ignored
                                          sli_zigbee_af_test_harness_z3_touchlink_profile_id);
    } else {
      status = emberAfSendCommandInterPan(0xFFFF,     // destination pan id
                                          zllNetwork.eui64,
                                          EMBER_NULL_NODE_ID,// node id- ignored
                                          0x0000,          // group id - ignored
                                          sli_zigbee_af_test_harness_z3_touchlink_profile_id);
    }
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Reset to factory new request",
                     status);
}

// plugin test-harness z3 touchlink network-start-request <dstAddress:2>
// <freeAddrBegin:2> <freeAddrEnd:2> <groupIdBegin:2> <groupIdEnd:2> <options:4>
// plugin test-harness z3 touchlink network-join-router-request <dstAddress:2>
// <freeAddrBegin:2> <freeAddrEnd:2> <groupIdBegin:2> <groupIdEnd:2> <options:4>
// plugin test-harness z3 touchlink network-join-end-device-request <dstAddress:2>
// <freeAddrBegin:2> <freeAddrEnd:2> <groupIdBegin:2> <groupIdEnd:2> <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_network_command(SL_CLI_COMMAND_ARG)
{
  EmberNodeId nodeId              = sl_cli_get_argument_uint16(arguments, 0);
  EmberNodeId freeAddrBegin       = sl_cli_get_argument_uint16(arguments, 1);
  EmberNodeId freeAddrEnd         = sl_cli_get_argument_uint16(arguments, 2);
  EmberMulticastId freeGroupBegin = sl_cli_get_argument_uint16(arguments, 3);
  EmberMulticastId freeGroupEnd   = sl_cli_get_argument_uint16(arguments, 4);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 5);

  uint8_t command = 0;
  EmberTokTypeStackZllData token;
  EmberStatus status = EMBER_INVALID_CALL;
  EmberZllNetwork mangledNetwork;

  if (!zllNetworkIsInit()) {
    goto done;
  }

  switch (sl_zigbee_cli_get_argument_string_and_length(arguments, -1, NULL)[13]) {
    case '-':
      command = ZCL_NETWORK_START_REQUEST_COMMAND_ID;
      break;
    case 'r':
      command = ZCL_NETWORK_JOIN_ROUTER_REQUEST_COMMAND_ID;
      break;
    case 'e':
      command = ZCL_NETWORK_JOIN_END_DEVICE_REQUEST_COMMAND_ID;
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
      goto done;
  }

  MEMMOVE(&mangledNetwork, &zllNetwork, sizeof(EmberZllNetwork));

  emberZllGetTokenStackZllData(&token);

  if (command == ZCL_NETWORK_START_REQUEST_COMMAND_ID) {
    // Say that we are FN so that we will indeed send a network start.
    token.bitmask |= EMBER_ZLL_STATE_FACTORY_NEW;
  } else {
    // Say that we are not FN so we will send a network join.
    token.bitmask &= ~EMBER_ZLL_STATE_FACTORY_NEW;
    // Mangle the target device type so that we get the command we want.
    mangledNetwork.nodeType
      = (command == ZCL_NETWORK_JOIN_ROUTER_REQUEST_COMMAND_ID
         ? EMBER_ROUTER
         : EMBER_END_DEVICE);
  }

  // Update the node id with the node id specified in the command line,
  mangledNetwork.nodeId = nodeId;

  // Pretend the remote node is always address capable, to force the stack
  // to include the address and group range fields in the command.
  mangledNetwork.state |= EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE;

  emberZllSetTokenStackZllData(&token);

  if (command == ZCL_NETWORK_START_REQUEST_COMMAND_ID) {
    if (options & BIT32(0)) {
      mangledNetwork.securityAlgorithm.transactionId--;
    }
    if (options & BIT32(1)) {
      EmberEUI64 address[EUI64_SIZE] = {
        0xDD, 0xDE, 0xDD, 0xED, 0xDE, 0xDD, 0xED, 0xDE
      };
      MEMMOVE(mangledNetwork.eui64, address, EUI64_SIZE);
    }
  } else { // command == network join
    switch (options) {
      case BIT32(0):
        // TODO: no encryption.
        break;
      case BIT32(1):
        mangledNetwork.securityAlgorithm.bitmask = EMBER_ZLL_KEY_MASK_DEVELOPMENT;
        break;
      case BIT32(2):
        //mangledNetwork.eui64 = NULL;
        mangledNetwork.nodeId = EMBER_BROADCAST_ADDRESS;
        break;
      case BIT32(3):
        mangledNetwork.securityAlgorithm.transactionId--;
        break;
      case BIT32(4): {
        EmberEUI64 address[EUI64_SIZE] = {
          0xDD, 0xDE, 0xDD, 0xED, 0xDE, 0xDD, 0xED, 0xDE
        };
        MEMMOVE(mangledNetwork.eui64, address, EUI64_SIZE);
        break;
      }
      default:
        ; // whatever
    }
  }

  // We need to override the Stack's address and group range assignments
  EmberZllAddressAssignment forcedAssignment;
  MEMSET(&forcedAssignment, 0, sizeof(EmberZllAddressAssignment));
  forcedAssignment.freeNodeIdMin  = freeAddrBegin;
  forcedAssignment.freeNodeIdMax  = freeAddrEnd;
  forcedAssignment.freeGroupIdMin = freeGroupBegin;
  forcedAssignment.freeGroupIdMax = freeGroupEnd;
  sli_zigbee_af_zll_set_forced_address_assignment(&forcedAssignment);

  emberAfZllSetInitialSecurityState();
  status = emberZllJoinTarget(&mangledNetwork);

  sli_zigbee_af_zll_clear_forced_address_assignment();

  done:
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     (command == ZCL_NETWORK_START_REQUEST_COMMAND_ID
                      ? "Network start request"
                      : (command == ZCL_NETWORK_JOIN_ROUTER_REQUEST_COMMAND_ID
                         ? "Network join router request"
                         : "Network join end device request")),
                     status);
}

// plugin test-harness z3 touchlink network-update-request <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_network_update_request_command(SL_CLI_COMMAND_ARG)
{
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 0);

  EmberStatus status = EMBER_INVALID_CALL;
  EmberNodeType nodeType;
  EmberNetworkParameters networkParameters;
  uint8_t mangledNwkUpdateId;

  emberAfGetNetworkParameters(&nodeType, &networkParameters);

  mangledNwkUpdateId = networkParameters.nwkUpdateId;
  if (options == BIT32(0)) {
    mangledNwkUpdateId += 5;
  }

  if (zllNetworkIsInit()) {
    (void) emberAfFillExternalBuffer(EM_AF_PLUGIN_TEST_HARNESS_Z3_ZLL_CLIENT_TO_SERVER_FRAME_CONTROL,
                                     ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                     ZCL_NETWORK_UPDATE_REQUEST_COMMAND_ID,
                                     "w8uuvv",
                                     zllNetwork.securityAlgorithm.transactionId,
                                     networkParameters.extendedPanId,
                                     mangledNwkUpdateId,
                                     networkParameters.radioChannel,
                                     networkParameters.panId,
                                     emberAfGetNodeId());
    status = emberAfSendCommandInterPan(0xFFFF, // destination pan id
                                        zllNetwork.eui64,
                                        EMBER_NULL_NODE_ID, // node id - ignored
                                        0x0000,            // group id - ignored
                                        sli_zigbee_af_test_harness_z3_touchlink_profile_id);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network update request",
                     status);
}

// plugin test-harness z3 touchlink get-group-identifiers-request
// <startIndex:1>
void sli_zigbee_af_test_harness_z3_touchlink_get_group_identifiers_request_command(SL_CLI_COMMAND_ARG)
{
  uint8_t startIndex = sl_cli_get_argument_uint8(arguments, 0);
  EmberStatus status = EMBER_INVALID_CALL;
  EmberNodeId destination;

  if (zllNetworkIsInit()) {
    if ((destination = zllNetwork.nodeId) == EMBER_NULL_NODE_ID) {
      destination = emberLookupNodeIdByEui64(zllNetwork.eui64);
    }
    emberAfFillCommandZllCommissioningClusterGetGroupIdentifiersRequest(startIndex);
    emberAfSetCommandEndpoints(1, 1); // endpoints?
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, destination);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Get group identifiers request",
                     status);
}

// plugin test-harness z3 touchlink get-endpoint-list-request
// <startIndex:1>
void sli_zigbee_af_test_harness_z3_touchlink_get_endpoint_list_request_command(SL_CLI_COMMAND_ARG)
{
  uint8_t startIndex = sl_cli_get_argument_uint8(arguments, 0);
  EmberStatus status = EMBER_INVALID_CALL;
  EmberNodeId destination;

  if (zllNetworkIsInit()) {
    if ((destination = zllNetwork.nodeId) == EMBER_NULL_NODE_ID) {
      destination = emberLookupNodeIdByEui64(zllNetwork.eui64);
    }
    emberAfFillCommandZllCommissioningClusterGetEndpointListRequest(startIndex);
    emberAfSetCommandEndpoints(1, 1); // endpoints?
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, destination);
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Get endpoint list request",
                     status);
}

// plugin test-harness z3 touchlink scan-response-config <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_scan_response_config_command(SL_CLI_COMMAND_ARG)
{
  uint32_t options      = sl_cli_get_argument_uint32(arguments, 0);

  globalScanResponseData.keyBitmask = EMBER_ZLL_KEY_MASK_CERTIFICATION;
  globalScanResponseData.profileId = HA_PROFILE_ID; // use HA profile for endpoint info
  globalScanResponseData.setReservedInformationBits = false;
  globalScanResponseData.networkUpdateId = networkUpdateId();
  globalScanResponseData.totalGroupIds = 0;
  globalScanResponseData.numberSubDevices = 1;

  negativeBehaviorMask = 0;
  negativeBehaviorCommandId = 0xff;

  if (options) {
    if (options & BIT32(0)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID;
    }
    if (options & BIT32(1)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_POSITIVE_RESPONSE;
    }
    if (options & BIT32(2)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_DELAY_RESPONSE;
    }
    if (options & BIT32(3)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.keyBitmask = 0x0000;
    }
    if (options & BIT32(4)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.keyBitmask = 0x0001;
    }
    if (options & BIT32(5)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.setReservedInformationBits = true;
    }
    if (options & BIT32(6)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      // As per the nwkUpdateId roll over logic defined in the ZCL6.
      // 13.3.4.9 Frequency Agility, the following will set it low.
      globalScanResponseData.networkUpdateId += 201;
    }
    if (options & BIT32(7)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.networkUpdateId = 0x50;
    }
    if (options & BIT32(8)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE;
    }
    if (options & BIT32(9)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.numberSubDevices = 10;
    }
    if (options & BIT32(10)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.networkUpdateId += 0x5A;
    }
    if (options & BIT32(11)) {
      negativeBehaviorMask |= NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE;
      globalScanResponseData.keyBitmask = 0x0020;
    }
  }
  if (negativeBehaviorMask) {
    if (realNetworkUpdateId == 0xff) {
      // Save the real network update id.
      realNetworkUpdateId = networkUpdateId();
    }
    // Set the actual update id to match, in case we get a beacon request
    // when a ZED initiator updates its own update id in response to a scan
    // response with a higher update id.
    sli_zigbee_set_nwk_update_id(globalScanResponseData.networkUpdateId);

    negativeBehaviorCommandId = ZCL_SCAN_REQUEST_COMMAND_ID;
  } else if (realNetworkUpdateId != 0xff) {
    // Restore the real network update id on a config reset.
    sli_zigbee_set_nwk_update_id(realNetworkUpdateId);
    realNetworkUpdateId = 0xff;
  }

  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Scan response config",
                     EMBER_SUCCESS);
}
// plugin test-harness z3 touchlink network-start-response-config <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_network_start_response_config(SL_CLI_COMMAND_ARG)
{
  uint32_t options = sl_cli_get_argument_uint32(arguments, 0);

  responseBehaviorMask = 0;
  responseBehaviorCommandId = 0xff;
  if (options) {
    if (options & BIT32(0)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE;
    }
    if (options & BIT32(1)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_COMMAND_ID;
    }
    if (options & BIT32(2)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID;
    }
    if (options & BIT32(3)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_SOURCE_ADDRESS;
    }
    if (options & BIT32(4)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_STATUS;
    }
  }
  if (responseBehaviorMask) {
    responseBehaviorCommandId = ZCL_NETWORK_START_RESPONSE_COMMAND_ID;
  }

  // All options are handled in the negative behaviour callbacks
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network start response config",
                     EMBER_SUCCESS);
}

// plugin test-harness z3 touchlink network-join-router-response-config <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_network_join_router_response_config(SL_CLI_COMMAND_ARG)
{
  uint32_t options = sl_cli_get_argument_uint32(arguments, 0);

  responseBehaviorMask = 0;
  responseBehaviorCommandId = 0xff;
  if (options) {
    if (options & BIT32(0)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE;
    }
    if (options & BIT32(1)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_COMMAND_ID;
    }
    if (options & BIT32(2)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID;
    }
    if (options & BIT32(3)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_SOURCE_ADDRESS;
    }
    if (options & BIT32(4)) {
      responseBehaviorMask |= NEGATIVE_BEHAVIOR_BAD_STATUS;
    }
  }
  if (responseBehaviorMask) {
    responseBehaviorCommandId = ZCL_NETWORK_JOIN_ROUTER_RESPONSE_COMMAND_ID;
  }

  // All options are handled in the negative behaviour callbacks
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network join router response config",
                     EMBER_SUCCESS);
}

// plugin test-harness z3 touchlink device-information-response-config
// <options:4>
void sli_zigbee_af_test_harness_z3_touchlink_device_information_response_config_command(SL_CLI_COMMAND_ARG)
{
  uint32_t options = sl_cli_get_argument_uint32(arguments, 0);

  negativeBehaviorMask = 0;
  negativeBehaviorCommandId = 0xff;
  if (options & BIT32(0)) {
    negativeBehaviorMask |= NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE;
  }

  if (negativeBehaviorMask) {
    negativeBehaviorCommandId = ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID;
  }
  emberAfCorePrintln("%s: %s: 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Device information response config",
                     EMBER_SUCCESS);
}

// -----------------------------------------------------------------------------
// Framework callbacks

void sli_zigbee_af_test_harness_z3_zll_network_found_callback(const EmberZllNetwork *networkInfo)
{
  emberAfCorePrintln("%p: %p: node type = %d, zll state = 0x%2X, node id = 0x%2X, pan id = 0x%2X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network found",
                     networkInfo->nodeType,
                     networkInfo->state,
                     networkInfo->nodeId,
                     networkInfo->zigbeeNetwork.panId);
  initZllNetwork(networkInfo);
}

bool sli_zigbee_af_test_harness_z3_zll_scan_complete_callback(EmberStatus status)
{
  bool handled = false;
  if (scanningState & STATE_SCANNING) {
    // If this was a test scan, then we'll handle the scan complete, and
    // initiate a secondary channel scan if required.
    if (!zllNetworkIsInit()
        && (scanningState & STATE_PRIMARY_CHANNELS)
        && emberGetZllSecondaryChannelMask() != 0) {
      scanningState &= ~STATE_PRIMARY_CHANNELS;
      startScan();
    } else {
      emberAfCorePrintln("%p: %p: 0x%02X",
                         TEST_HARNESS_Z3_PRINT_NAME,
                         "Scan Complete",
                         EMBER_SUCCESS,
                         status);
      scanningState = STATE_NOT_SCANNING;
      if (status != EMBER_SUCCESS) {
        deinitZllNetwork();
      }
      // Tell the API that we have finished scanning, so that it won't
      // attempt to re-use our old transaction code.
      emberZllScanningComplete();
    }
    // Do NOT cancel any negative mode here on the scan request.

    // Tell zll commissioning client we've already processed the scan complete.
    handled = true;
  }
  return handled;
}

EmberPacketAction sli_zigbee_af_test_harness_z3_zll_command_callback(uint8_t  *command,
                                                                     EmberEUI64 sourceEui64)
{
  // The start index points at the beginning of the ZCL frame.
  // FRAME_CONTROL:1 | SEQUENCE:1 | COMMAND_ID:1 | start of transaction...
  uint8_t transactionIdIndex = 3;
  uint8_t commandId = command[2];
  uint32_t realTransactionId = emberFetchLowHighInt32u(command + transactionIdIndex);
  EmberPacketAction act = EMBER_ACCEPT_PACKET;
  emberAfDebugPrintln("emAfPluginTestHarnessZ3ZllCommandCallback: commandId = %X", commandId);

  // Print the source EUI64 for certain commands only
  if (commandId == ZCL_NETWORK_START_RESPONSE_COMMAND_ID
      || commandId == ZCL_NETWORK_JOIN_ROUTER_RESPONSE_COMMAND_ID
      || commandId == ZCL_SCAN_RESPONSE_COMMAND_ID) {
    emberAfCorePrint("sourceEui64: ");
    emberAfCorePrintBuffer(sourceEui64, 8, true);   // spaces?
    emberAfCorePrintln("");
  }

  if (commandId == ZCL_NETWORK_START_RESPONSE_COMMAND_ID
      || commandId == ZCL_NETWORK_JOIN_ROUTER_RESPONSE_COMMAND_ID
      || commandId == ZCL_NETWORK_JOIN_END_DEVICE_RESPONSE_COMMAND_ID ) {
    // Disable address matching until we join, in order to detect device
    // announce message from target.
    emRadioEnableAddressMatching(false);
  }
  // Ignore any negative behavior if the command doesn't match up, except
  // if the previous scan config option forces a device info request.
  // (negativeBehaviorCommandId will still be ZCL_SCAN_REQUEST_COMMAND_ID)
  if (commandId != negativeBehaviorCommandId
      && (commandId != ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID
          || globalScanResponseData.numberSubDevices == 1)) {
    return act;
  }

  globalScanResponseData.transactionId = realTransactionId;
  MEMMOVE(globalScanResponseData.destinationEui64, sourceEui64, EUI64_SIZE);

  if (negativeBehaviorMask
      & (NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE
         | NEGATIVE_BEHAVIOR_DELAY_RESPONSE
         | NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE)) {
    if (!(negativeBehaviorMask & NEGATIVE_BEHAVIOR_POSITIVE_RESPONSE)) {
      // Overwrite the transaction ID to be 0. This will make us not respond
      // to the command.
      emberStoreLowHighInt32u(command + transactionIdIndex, 0);
      act = EMBER_MANGLE_PACKET;
    }

    if (negativeBehaviorMask & NEGATIVE_BEHAVIOR_DELAY_RESPONSE) {
      // Delay 8 seconds, since this is the transaction ID lifetime. But
      // not if we are already delaying, e.g. for multiple scan requests
      // on first primary channel.
      if (!isDelayingScanResponse) {
        isDelayingScanResponse = true;
        sl_zigbee_event_set_delay_ms(z3ZllStuffEventControl,
                                     MILLISECOND_TICKS_PER_SECOND * 8);
        zllStuffEventControlAction = ZLL_STUFF_EVENT_CONTROL_ACTION_SCAN_RESPONSE;
      }
    } else if (negativeBehaviorMask & NEGATIVE_BEHAVIOR_IMMEDIATE_RESPONSE) {
      if (commandId == ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID) {
        // Send the next chunk of device info.
        uint8_t startIndex = command[transactionIdIndex + 4];
        sendDeviceInfoResponse(sourceEui64, realTransactionId, startIndex);
      } else {   // Must be a scan request
        // Send our own response immediately, but only to the first scan request.
        if (realTransactionId != lastTransactionId) {
          lastTransactionId = realTransactionId;
          sendScanResponse();
        } else {
          emberAfDebugPrintln("Dropping scan req w/dupl trans id = %4X", realTransactionId);
        }
      }
    }
  } else if (negativeBehaviorMask & NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID) {
    emberStoreLowHighInt32u(command + transactionIdIndex, realTransactionId - 1);
    act = EMBER_MANGLE_PACKET;
  }

  return act;
}

void emberAfPluginTestHarnessZ3ZllStuffEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status;

  sl_zigbee_event_set_inactive(z3ZllStuffEventControl);
  emberAfCorePrintln("emberAfPluginTestHarnessZ3ZllStuffEventHandler: entry");

  switch (zllStuffEventControlAction) {
    case ZLL_STUFF_EVENT_CONTROL_ACTION_SCAN_RESPONSE:
      isDelayingScanResponse = false;
      status = sendScanResponse();
      emberAfCorePrintln("emZllSendScanResponse, status = %X", status);
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
  }

  emberAfCorePrintln("%p: %p (0x%X): 0x%X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "ZLL event handler",
                     zllStuffEventControlAction,
                     status);

  zllStuffEventControlAction = ZLL_STUFF_EVENT_CONTROL_ACTION_NULL;
}

EmberPacketAction sli_zigbee_af_test_harness_z3_zll_modify_interpan_command(uint8_t *commandData,
                                                                            uint8_t macHeaderLength)
{
  static const EmberEUI64 badEui64 = { 0xde, 0xed, 0xdd, 0xde, 0xed, 0xdd, 0xde, 0xdd };
  EmberPacketAction act = EMBER_ACCEPT_PACKET;

  uint8_t *apsPointer = commandData + macHeaderLength + 7;
  uint8_t cmdId = *(apsPointer + 2);
  emberAfDebugPrintln("Modify Interpan: cmd id = %d, mask = %4X", cmdId, responseBehaviorMask);

  // Ignore any negative behavior if the command doesn't match up.
  if (cmdId == responseBehaviorCommandId) {
    if (responseBehaviorMask & NEGATIVE_BEHAVIOR_SUPPRESS_RESPONSE) {
      return EMBER_DROP_PACKET;
    }

    // This is the only option which affects the MAC header
    if (responseBehaviorMask & NEGATIVE_BEHAVIOR_BAD_SOURCE_ADDRESS) {
      MEMMOVE(commandData + (macHeaderLength - 8), badEui64, EUI64_SIZE);
    }

    // The remaining options pertain to the APS payload
    if (responseBehaviorMask & NEGATIVE_BEHAVIOR_BAD_COMMAND_ID) {
      *(apsPointer + 2) = ZCL_NETWORK_JOIN_END_DEVICE_RESPONSE_COMMAND_ID;
    }
    if (responseBehaviorMask & NEGATIVE_BEHAVIOR_BAD_TRANSACTION_ID) {
      MEMSET(apsPointer + 3, 0, 4);
    }
    if (responseBehaviorMask & NEGATIVE_BEHAVIOR_BAD_STATUS) {
      *(apsPointer + 7) = EMBER_ERR_FATAL;
    }

    if (responseBehaviorMask) {
      act = EMBER_MANGLE_PACKET;
    }
  } else if (cmdId == ZCL_SCAN_RESPONSE_COMMAND_ID) {
    // Ensure the zigbee and touchlink information fields are set
    // according to our device mode - this is particularly important
    // for the address assignment capability bit.
    *(apsPointer + 8) = zigbeeInformation();
    *(apsPointer + 9) = zllInformation();
    act = EMBER_MANGLE_PACKET;
  } else if (cmdId == ZCL_SCAN_REQUEST_COMMAND_ID) {
    // This is the most convenient place to set and clear bits.
    emberAfDebugPrintln("Modify Interpan: scanBehaviorMask = %4X", scanBehaviorMask);
    if (scanBehaviorMask & NEGATIVE_BEHAVIOR_SET_ZB_RESERVED_BITS) {
      *(apsPointer + 7) |= ZB_RESERVED_BITS;
    }
    if (scanBehaviorMask & NEGATIVE_BEHAVIOR_SET_ZLL_RESERVED_BITS) {
      *(apsPointer + 8) |= ZLL_RESERVED_BITS;
    }
    if (scanBehaviorMask & NEGATIVE_BEHAVIOR_CLEAR_INITIATOR_BIT) {
      *(apsPointer + 8) &= ~0x10;
    }
    if (scanBehaviorMask & NEGATIVE_BEHAVIOR_SET_INITIATOR_BIT) {
      *(apsPointer + 8) |= 0x10;
    }
    act = EMBER_MANGLE_PACKET;
  }
  return act;
}

// plugin zll-commissioning set-radio-idle-mode
void sli_zigbee_test_harness_set_radio_idle_mode(sl_cli_command_arg_t *arguments)
{
  uint8_t mode = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);
  emberZllSetRadioIdleMode(mode);
}

// plugin zll-commissioning get-radio-idle-mode
void sli_zigbee_test_harness_get_radio_idle_mode(sl_cli_command_arg_t *arguments)
{
  uint8_t mode = emberZllGetRadioIdleMode();
  emberAfAppPrintln("%p %p", "MAC Radio Idle Mode: ", mode ? "off" : "rx-on");
}
