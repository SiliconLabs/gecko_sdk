/***************************************************************************//**
 * @file
 * @brief ZigBee 3.0 zdo test harness functionality
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

#include "app/util/zigbee-framework/zigbee-device-host.h"
#include "app/util/zigbee-framework/zigbee-device-common.h"

#include "test-harness-z3-core.h"

// -----------------------------------------------------------------------------
// Constants
#define TEST_HARNESS_ENDPOINT (1)
#define ZDO_NETWORK_UPDATE_REQUEST (0x0038)
#define ZDO_NODE_DESCRIPTOR_BAND_2400_MHZ (0x40)

#define TH_SIMPLE_DESC_REQ_PAYLOAD_LENGTH (4)
#define TH_USER_DESC_REQ_PAYLOAD_LENGTH (3)
#define TH_IEEE_ADD_REQ_PAYLOAD_LENGTH (3)
#define SERVER_MASK_HIGH (0x2C)  // r22
#define TH_USER_DESC_RSP_PAYLOAD_LENGTH (16)

// Clusters for simple descriptor response
// server
#define IN_CLUSTERS { 0x0000, 0x0003, 0x0006, 0x0008, 0x000a, 0x0019, 0x0020, 0x0025, 0x0101 }
// client
#define OUT_CLUSTERS { 0x0006, 0x0008, 0x0019, 0x0101, 0x0102, 0x0103 }
// -----------------------------------------------------------------------------
// extern functions
extern bool sli_zigbee_am_network_manager(void);

// -----------------------------------------------------------------------------
// Globals
sl_zigbee_event_t emberAfPluginTestHarnessZ3ZdoSendEventControl;

#define NULL_CURRENT_ZDO_NEGATIVE_COMMAND_CLUSTER (0x00FF)
static EmberNodeId currentZdoNegativeCommandDestination = EMBER_NULL_NODE_ID;
static uint16_t currentZdoNegativeCommandCluster = NULL_CURRENT_ZDO_NEGATIVE_COMMAND_CLUSTER;
static uint8_t currentZdoNegativeCommandFrame[64];
static uint8_t currentZdoNegativeCommandFrameLength;

uint8_t sli_zigbee_af_test_harness_z3_server_mask_high = SERVER_MASK_HIGH;

// Internal stack API.
uint8_t sli_zigbee_get_nwk_update_id(void);

// -----------------------------------------------------------------------------
// ZDO Commands

// Declared in zdo-cli.c. Used here so CLI commands can be reused.
extern uint16_t sli_zigbee_af_cli_zdo_in_clusters[];
extern uint16_t sli_zigbee_af_cli_zdo_out_clusters[];
extern uint8_t sli_zigbee_af_cli_in_cl_count;
extern uint8_t sli_zigbee_af_cli_out_cl_count;

static uint32_t negativeZdoCommandFlags = 0;
#define NEGATIVE_ZDO_COMMAND_FLAGS_OUR_NWK_ADDRESS        BIT32(0)
#define NEGATIVE_ZDO_COMMAND_FLAGS_MATCH_LIST_ABSENT      BIT32(1)
#define NEGATIVE_ZDO_COMMAND_FLAGS_SEND_POSITIVE_RESPONSE BIT32(2)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_SIMPLE_DESCRIPTOR   BIT32(3)
#define NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_KE        BIT32(4)
#define NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_SWAP      BIT32(5)
#define NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_ABSENT    BIT32(6)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_ENDPOINT_FIELDS     BIT32(7)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_NWK_ADDR            BIT32(8)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_NEGATIVE_RESPONSE   BIT32(9)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_USER_DESCRIPTOR     BIT32(10)
#define NEGATIVE_ZDO_COMMAND_FLAGS_NO_NODE_DESCRIPTOR     BIT32(11)

#ifdef EZSP_HOST

static EmberStatus sendZdoCommand(EmberNodeId destination,
                                  uint16_t clusterId,
                                  uint8_t *frame,
                                  uint8_t frameLength,
                                  uint8_t sequenceNumber)
{
  return EMBER_INVALID_CALL;
}

#else

extern EmberNodeId sli_zigbee_af_current_sender;

static EmberStatus sendZdoCommand(EmberNodeId destination,
                                  uint16_t clusterId,
                                  uint8_t *frame,
                                  uint8_t frameLength,
                                  uint8_t sequenceNumber)
{
  EmberStatus status;
  EmberMessageBuffer message;
  EmberApsFrame apsFrame = {
    EMBER_ZDO_PROFILE_ID,
    clusterId,
    EMBER_ZDO_ENDPOINT,
    EMBER_ZDO_ENDPOINT,
    (EMBER_APS_OPTION_RETRY),
    0, // group id
    0, // sequence
  };
  frame[0] = sequenceNumber ? sequenceNumber : emberNextZigDevRequestSequence();
  message = emberFillLinkedBuffers(frame, frameLength);

  if (message == EMBER_NULL_MESSAGE_BUFFER) {
    return EMBER_NO_BUFFERS;
  }

  if (emberIsZigbeeBroadcastAddress(destination)) {
    status = emberSendBroadcast(destination,
                                &apsFrame,
                                EMBER_MAX_HOPS,
                                message);
  } else {
    status = emberSendUnicast(EMBER_OUTGOING_DIRECT,
                              destination,
                              &apsFrame,
                              message);
  }

  emberReleaseMessageBuffer(message);

  return status;
}

#endif /* EZSP_HOST */
// plugin test-harness z3 mgmt permit-joining-req <timeS:2> <dstShort:2> <options:4>
void sli_zigbee_af_test_harness_z3_mgmt_permit_joining_req_command(sl_cli_command_arg_t *arguments)
{
  uint16_t permitDurationS = sl_cli_get_argument_uint16(arguments, 0);
  EmberNodeId destination  = sl_cli_get_argument_uint16(arguments, 1);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 2);

  EmberStatus status;

  status = emberPermitJoiningRequest(destination,
                                     permitDurationS,
                                     (options == BIT32(0) ? false : true),
                                     (EMBER_APS_OPTION_RETRY));

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Permit joining request",
                     status);
}

// plugin test-harness z3 mgmt leave <dstShort:2> <removeChildren:1>
// <rejoin:1> <optionBitmask:4>
void sli_zigbee_af_test_harness_z3_mgmt_leave_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId destination = sl_cli_get_argument_uint16(arguments, 0);
  // CCB 2047
  // - CCB makes the first step to depracate the 'leave and remove children' functionality.
  // - We were proactive here and deprecated it right away.
  // bool removeChildren     = (bool)emberUnsignedCommandArgument(1);

  bool rejoin             = (bool)sl_cli_get_argument_uint32(arguments, 2);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 3);

  EmberStatus status = EMBER_INVALID_CALL;
  uint8_t frame[10];
  uint8_t *finger = &frame[1];

  // Long address of destination. Bit 0 means don't put it in payload.
  if (options != BIT(0)) {
    status = emberLookupEui64ByNodeId(destination, finger);
    if (status != EMBER_SUCCESS) {
      goto done;
    }
    finger += EUI64_SIZE;
  }

  // Options.
  if (options != BIT(1)) {
    *finger = 0;
    if (rejoin) {
      *finger |= BIT(7);
    }
    finger++;
  }
  status = sendZdoCommand(destination, LEAVE_REQUEST, frame, finger - &frame[0], 0);

  done:
  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Mgmt leave",
                     status);
}

// plugin test-harness z3 mgmt nwk-update-request <scanChannel:2> <scanDuration:2>
// <scanCount:1> <dstShort:2> <option:4>
void sli_zigbee_af_test_harness_z3_mgmt_nwk_update_request_command(sl_cli_command_arg_t *arguments)
{
  uint16_t scanChannel    = sl_cli_get_argument_uint16(arguments, 0);
  uint16_t scanDuration   = sl_cli_get_argument_uint16(arguments, 1);
  uint8_t scanCount       = sl_cli_get_argument_uint8(arguments, 2);
  EmberNodeId destination = sl_cli_get_argument_uint16(arguments, 3);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 4);

  EmberStatus status;
  uint8_t frame[9];
  uint8_t *finger = &frame[1];
  EmberNetworkParameters networkParameters;
  EmberNodeType nodeType;

  status = emberAfGetNetworkParameters(&nodeType, &networkParameters);
  if (status != EMBER_SUCCESS) {
    goto done;
  }

  // Scan channel.
  emberAfCopyInt32u(finger, 0, BIT32(scanChannel));
  finger += sizeof(uint32_t);
  // Scan duration.
  *finger++ = (uint8_t)(0xFF & scanDuration); // ANDREW: Q3.
  // Scan count (table 2.90):
  // "This field shall be present only if the ScanDuration is within the
  // range of 0x00 to 0x05."
  if (scanDuration <= 5) {
    *finger++ = scanCount;
  }
  // Network update id (table 2.90):
  // "This field shall only be present of the ScanDuration is 0xfe or 0xff.
  // If the ScanDuration is 0xff, then the value in the nwkUpdateID shall
  // be ignored." (But it should still be present, unchanged.)

  if (scanDuration == 0xFE || scanDuration == 0xFF) {
    *finger++ = scanDuration == 0xFF
                ? networkParameters.nwkUpdateId
                : options == BIT(1)
                ? 0x55
                : options == BIT(0)
                ? networkParameters.nwkUpdateId - 1
                : networkParameters.nwkUpdateId + 1;
  }
  // Network manager id (table 2.90):
  // "This field shall be present only if the ScanDuration is set to 0xff,
  // and, where present, indicates the NWK address for the device with the
  // Network Manager bit set in its Node Descriptor."
  if (scanDuration == 0xFF) {
    emberAfCopyInt16u(finger, 0, networkParameters.nwkManagerId);
    finger += sizeof(uint16_t);
  }

  status = sendZdoCommand(destination,
                          ZDO_NETWORK_UPDATE_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);

  done:
  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network update request",
                     status);
}

// plugin test-harness z3 zdo zdo-reset
void sli_zigbee_af_test_harness_z3_zdo_zdo_reset_command(sl_cli_command_arg_t *arguments)
{
  currentZdoNegativeCommandCluster = NULL_CURRENT_ZDO_NEGATIVE_COMMAND_CLUSTER;
  negativeZdoCommandFlags = 0;

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "ZDO reset",
                     EMBER_SUCCESS);
}

// plugin test-harness z3 zdo node-desc-req <dstShort:2>
void sli_zigbee_af_test_harness_z3_zdo_node_desc_req_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId destination       = sl_cli_get_argument_uint16(arguments, 0);
  EmberStatus status;
  uint8_t frame[1];

  status = sendZdoCommand(destination,
                          NODE_DESCRIPTOR_REQUEST,
                          frame,
                          1, 0);

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Node descriptor request",
                     status);
}

// plugin test-harness z3 zdo zdo-node-desc-rsp-config <options:4>
void sli_zigbee_af_test_harness_z3_zdo_zdo_node_desc_rsp_config_command(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = EMBER_INVALID_CALL;

#ifndef EZSP_HOST

  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 0);
  currentZdoNegativeCommandCluster = NODE_DESCRIPTOR_RESPONSE;
  status = EMBER_BAD_ARGUMENT;

  switch (options) {
    case BIT(0):
      negativeZdoCommandFlags = 0;  // negative response only!
      status = EMBER_SUCCESS;
      break;
    case BIT(1):
      // node descriptor field absent
      negativeZdoCommandFlags = NEGATIVE_ZDO_COMMAND_FLAGS_NO_NODE_DESCRIPTOR;
      status = EMBER_SUCCESS;
      break;
  }

#endif /* EZSP_HOST */

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Node descriptor response config",
                     status);
}

// plugin test-harness z3 zdo active-endpoint-request <dstShort:2>
// <nwkAddrOfInterest:2> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_active_endpoint_request_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId destination       = sl_cli_get_argument_uint16(arguments, 0);
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 1);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 2);

  EmberStatus status;
  uint8_t frame[3], frameLength = 1;

  if (options != BIT(0)) {
    frame[1] = LOW_BYTE(nwkAddrOfInterest);
    frame[2] = HIGH_BYTE(nwkAddrOfInterest);
    frameLength += 2;
  }

  status = sendZdoCommand(destination,
                          ACTIVE_ENDPOINTS_REQUEST,
                          frame,
                          frameLength,
                          0);

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Active endpoint request",
                     status);
}

// plugin test-harness z3 zdo match-desc-req <dstShort:2>
// <nwkAddrOfInterest:2> <profileId:4> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_match_desc_req_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId destination       = sl_cli_get_argument_uint16(arguments, 0);
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t profileId            = sl_cli_get_argument_uint16(arguments, 2);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 3);

  EmberStatus status;
  uint8_t frame[32];
  uint8_t *finger = &frame[1];

  if (options != BIT(0)) {
    // Network address of interest.
    emberAfCopyInt16u(finger, 0, nwkAddrOfInterest);
    finger += sizeof(uint16_t);
  }

  // Profile id.
  emberAfCopyInt16u(finger, 0, profileId);
  finger += sizeof(uint16_t);

  if (options != BIT(1)) {
    uint8_t reallyInClustersCount
      = (options == BIT(2) ? 1 : sli_zigbee_af_cli_in_cl_count);
    uint8_t reallyOutClustersCount
      = (options == BIT(3) ? 1 : sli_zigbee_af_cli_out_cl_count);

    // In clusters.
    *finger++ = sli_zigbee_af_cli_in_cl_count;
    MEMMOVE(finger,
            sli_zigbee_af_cli_zdo_in_clusters,
            reallyInClustersCount * sizeof(uint16_t));
    finger += (reallyInClustersCount * sizeof(uint16_t));

    // Out clusters.
    *finger++ = sli_zigbee_af_cli_out_cl_count;
    MEMMOVE(finger,
            sli_zigbee_af_cli_zdo_out_clusters,
            reallyOutClustersCount * sizeof(uint16_t));
    finger += (reallyOutClustersCount * sizeof(uint16_t));
  } else {
    *finger++ = sli_zigbee_af_cli_in_cl_count;  // In clusters.
    *finger++ = sli_zigbee_af_cli_out_cl_count; // Out clusters.
  }

  status = sendZdoCommand(destination,
                          MATCH_DESCRIPTORS_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);
  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Match descriptor request",
                     status);
}

// plugin test-harness z3 zdo match-desc-rsp-config <nwkAddrOfInterest:2>
// <status:1> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_match_desc_rsp_config_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t zdoStatus             = sl_cli_get_argument_uint8(arguments, 1);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 2);

  EmberStatus status = EMBER_SUCCESS;

  // Global state.
  currentZdoNegativeCommandCluster = MATCH_DESCRIPTORS_RESPONSE;
  currentZdoNegativeCommandFrameLength = 5;

  // Positive behavior.
  currentZdoNegativeCommandFrame[1] = zdoStatus;
  currentZdoNegativeCommandFrame[2] = LOW_BYTE(nwkAddrOfInterest);
  currentZdoNegativeCommandFrame[3] = HIGH_BYTE(nwkAddrOfInterest);

  switch (options) {
    case BIT(0):
      // match list absent
      negativeZdoCommandFlags
        = (NEGATIVE_ZDO_COMMAND_FLAGS_MATCH_LIST_ABSENT);
      break;
    case BIT(1):
      // second response device not found
      negativeZdoCommandFlags
        = (NEGATIVE_ZDO_COMMAND_FLAGS_MATCH_LIST_ABSENT
           | NEGATIVE_ZDO_COMMAND_FLAGS_SEND_POSITIVE_RESPONSE);
      currentZdoNegativeCommandFrame[1] = EMBER_ZDP_DEVICE_NOT_FOUND;
      break;
    case BIT(2):
      // second response no descriptor
      negativeZdoCommandFlags
        = (NEGATIVE_ZDO_COMMAND_FLAGS_MATCH_LIST_ABSENT
           | NEGATIVE_ZDO_COMMAND_FLAGS_SEND_POSITIVE_RESPONSE);
      currentZdoNegativeCommandFrame[1] = EMBER_ZDP_NO_DESCRIPTOR;
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
      break;
  }

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Match descriptor response config",
                     status);
}

// plugin test-harness z3 zdo simple-desc-req <dstShort:2> <dstEndpoint:1>
// <nwkAddrOfInterest:2> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_simple_desc_req_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId destination       = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t endpoint              = sl_cli_get_argument_uint8(arguments, 1);
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 2);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 3);

  EmberStatus status;
  uint8_t frame[4];
  uint8_t *finger = &frame[1];

  // Network address of interest.
  if (options != BIT(0)) {
    emberAfCopyInt16u(finger, 0, nwkAddrOfInterest);
    finger += sizeof(uint16_t);
  }

  // Endpoint.
  if (options != BIT(1)) {
    *finger++ = endpoint;
  }

  status = sendZdoCommand(destination,
                          SIMPLE_DESCRIPTOR_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Simple descriptor request",
                     status);
}

// plugin test-harness z3 simple-desc-rsp-config <nwkAddrOfInterest:2>
// <status:1> <length:1> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_simple_desc_rsp_config_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t zdoStatus             = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t length                = sl_cli_get_argument_uint8(arguments, 2);
  uint32_t options              = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 3);

  EmberStatus status = EMBER_SUCCESS;

  // Global state.
  currentZdoNegativeCommandCluster = SIMPLE_DESCRIPTOR_RESPONSE;
  currentZdoNegativeCommandFrameLength = 5;

  // Positive behavior.
  currentZdoNegativeCommandFrame[1] = zdoStatus;
  emberAfCopyInt16u(currentZdoNegativeCommandFrame, 2, nwkAddrOfInterest);
  currentZdoNegativeCommandFrame[4] = length;

  // Negative behavior.
  switch (options) {
    case BIT(0):
      // simple descriptor field absent
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_NO_SIMPLE_DESCRIPTOR);
      break;
    case BIT(1):
      // do not forward to the nwk addr of interest
      break;
    case BIT(2):
      // cluster list key establishment
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_KE);
      break;
    case BIT(3):
      // swap support for client/server clusters
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_SWAP);
      break;
    case BIT(4):
      // do not send any cluster lists
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_ABSENT);
      break;
    case BIT(5):
      // send a positive command alongside a negative command
      negativeZdoCommandFlags
        = (NEGATIVE_ZDO_COMMAND_FLAGS_SEND_POSITIVE_RESPONSE
           | NEGATIVE_ZDO_COMMAND_FLAGS_NO_SIMPLE_DESCRIPTOR);
      currentZdoNegativeCommandFrame[1] = EMBER_ZDP_DEVICE_NOT_FOUND;
      currentZdoNegativeCommandFrame[4] = 0; // length
      break;
    case BIT(6):
      // do not include endpoints fields in the variable payload
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_NO_ENDPOINT_FIELDS);
      break;
    case BIT(7):
      // do not include the network address of interest
      negativeZdoCommandFlags = (NEGATIVE_ZDO_COMMAND_FLAGS_NO_NWK_ADDR);
      currentZdoNegativeCommandFrameLength -= 2;
      break;
    default:
      ; // options of 0x00 is ok
  }

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Simple descriptor response config",
                     status);
}

// plugin test-harness z3 zdo bind-group <shortAddress:2> <srcEndpoint:1>
// <dstEndpoint:1> <dstAddress:2> <cluster:2> <srcIeee:8>
void sli_zigbee_af_test_harness_z3_zdo_bind_group_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId shortAddress = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint      = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint      = sl_cli_get_argument_uint8(arguments, 2);
  uint16_t groupId         = sl_cli_get_argument_uint16(arguments, 3);
  EmberAfClusterId cluster = sl_cli_get_argument_uint16(arguments, 4);
  EmberStatus status;
  uint8_t frame[16];
  uint8_t *finger = &frame[1];

  // Not currently used.
  (void)dstEndpoint;

  // SrcAddress
  finger += sl_zigbee_copy_eui64_arg(arguments, 5, finger, true);

  // SrcEndp
  *finger++ = srcEndpoint;

  // ClusterID
  emberAfCopyInt16u(finger, 0, cluster);
  finger += sizeof(cluster);

  // DstAddrMode
  *finger++ = 0x01; // multicast

  // DstAddress
  emberAfCopyInt16u(finger, 0, groupId);
  finger += sizeof(groupId);

  status = sendZdoCommand(shortAddress,
                          BIND_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "ZDO bind group",
                     status);
}

// plugin test-harness z3 zdo nwk-addr-req <ieee:8> <requestType:1>
// <startIndex:1> <dstShort:2> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_nwk_addr_req_command(sl_cli_command_arg_t *arguments)
{
  uint8_t requestType          = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t startIndex           = sl_cli_get_argument_uint8(arguments, 2);
  EmberNodeId destinationShort = sl_cli_get_argument_uint16(arguments, 3);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 4);

  EmberStatus status;
  uint8_t frame[11];
  uint8_t *finger = &frame[1];

  if (options != BIT(0)) {
    // IEEE address.
    sl_zigbee_copy_eui64_arg(arguments, 0, finger, true);
    finger += EUI64_SIZE;

    // Request type.
    *finger++ = requestType;

    // Start index.
    *finger++ = startIndex;
  }

  status = sendZdoCommand(destinationShort,
                          NETWORK_ADDRESS_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);

  emberAfCorePrintln("%s: %ss: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Network address request",
                     status);
}

// plugin test-harness z3 zdo ieee-addr-req <nwkAddrOfInterest:2>
// <requestType:1> <startIndex:1> <dstShort:2> <options:4>
void sli_zigbee_af_test_harness_z3_zdo_ieee_addr_req_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId nwkAddrOfInterest = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t requestType           = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t startIndex            = sl_cli_get_argument_uint8(arguments, 2);
  EmberNodeId destination       = sl_cli_get_argument_uint16(arguments, 3);
  uint32_t options      = sli_zigbee_af_test_harness_z3_get_significant_bit(arguments, 4);

  EmberStatus status;
  uint8_t frame[5];
  uint8_t *finger = &frame[1];

  if (options != BIT(0)) {
    // Network address of interest.
    emberAfCopyInt16u(finger, 0, nwkAddrOfInterest);
    finger += sizeof(uint16_t);

    // Request type.
    *finger++ = requestType;

    // Start index.
    *finger++ = startIndex;
  }

  status = sendZdoCommand(destination,
                          IEEE_ADDRESS_REQUEST,
                          frame,
                          finger - &frame[0],
                          0);

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "IEEE address request",
                     status);
}

// plugin test-harness z3 nwk ieee-addr-rsp-config reset
// plugin test-harness z3 nwk ieee-addr-rsp-config issuer-nwk-address-remote-dev
// plugin test-harness z3 nwk ieee-addr-rsp-config status-device-not-found
void sli_zigbee_af_test_harness_z3_zdo_ieee_addr_rsp_config_command(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = EMBER_SUCCESS;
  char firstChar = sl_cli_get_command_string(arguments, 5)[0];

  // Global state.
  currentZdoNegativeCommandCluster = IEEE_ADDRESS_RESPONSE;
  currentZdoNegativeCommandFrameLength = 12;

  // Positive behavior.
  currentZdoNegativeCommandFrame[1] = EMBER_ZDP_SUCCESS;

  // Negative behavior.
  switch (firstChar) {
    case 'r':
      // reset
      negativeZdoCommandFlags = 0;
      currentZdoNegativeCommandCluster = NULL_CURRENT_ZDO_NEGATIVE_COMMAND_CLUSTER;
      break;
    case 'i':
      // issuer-nwk-address-remote-dev
      negativeZdoCommandFlags |= NEGATIVE_ZDO_COMMAND_FLAGS_OUR_NWK_ADDRESS;
      break;
    case 's':
      // status-device-not-found
      currentZdoNegativeCommandFrame[1] = EMBER_ZDP_DEVICE_NOT_FOUND;
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
  }

  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "IEEE address response config",
                     status);
}

// plugin test-harness z3 zdo bc-device-announce <shortAddress:2> <ieeeAddress:8>
void sli_zigbee_af_test_harness_z3_zdo_bc_device_announce_command(sl_cli_command_arg_t *arguments)
{
  EmberNodeId shortAddress = sl_cli_get_argument_uint16(arguments, 0);
  EmberEUI64 eui64;
  uint8_t frame[12];
  EmberStatus status;

  sl_zigbee_copy_eui64_arg(arguments, 1, eui64, true);

  emberAfCopyInt16u(frame, 1, shortAddress);
  MEMMOVE(frame + 3, eui64, EUI64_SIZE);
  frame[11] = 0xE0; // capability: fake like we are a router

  status = sendZdoCommand(EMBER_RX_ON_WHEN_IDLE_BROADCAST_ADDRESS,
                          END_DEVICE_ANNOUNCE,
                          frame,
                          sizeof(frame),
                          0);
  emberAfCorePrintln("%s: %s: 0x%02X",
                     TEST_HARNESS_Z3_PRINT_NAME,
                     "Broadcast device announce",
                     status);
}

#ifndef EZSP_HOST
EmberStatus sli_zigbee_af_test_harness_z3_zdo_command_response_handler(uint8_t *requestBuffer,
                                                                       uint8_t length,
                                                                       EmberApsFrame *apsFrame)
{
  emberAfDebugPrintln("sli_zigbee_af_test_harness_z3_zdo_command_response_handler: cluster = %2X", apsFrame->clusterId);
  EmberStatus status = EMBER_SUCCESS;
  uint16_t clusterId = apsFrame->clusterId;

  // Make sure the cluster id matches the negative zdo command's request.
  if (clusterId != (currentZdoNegativeCommandCluster & ~0x8000)) {
    // EMZIGBEE-1317 -The simple descriptor req to reply with a short list.
    // If no cluster is configured for negative test response
    // and a simple descriptor request is received - then handle it with
    // a shorter list of clusters so that the payload does not exhaust.
    if (clusterId == SIMPLE_DESCRIPTOR_REQUEST
        || clusterId == USER_DESCRIPTOR_REQUEST) { // No config command specified yet
      negativeZdoCommandFlags = 0;
    } else {
      return EMBER_INVALID_CALL;
    }
  }

  if (clusterId == IEEE_ADDRESS_REQUEST) {
    if (length <  TH_IEEE_ADD_REQ_PAYLOAD_LENGTH ) {
      return EMBER_INVALID_CALL;
    }
    // Perform some last second mangling of the frame.
    EmberNodeId nwkAddressOfInterest
      = HIGH_LOW_TO_INT(requestBuffer[2],
                        requestBuffer[1]);
    if (negativeZdoCommandFlags & NEGATIVE_ZDO_COMMAND_FLAGS_OUR_NWK_ADDRESS) {
      currentZdoNegativeCommandFrame[10] = LOW_BYTE(emberAfGetNodeId());
      currentZdoNegativeCommandFrame[11] = HIGH_BYTE(emberAfGetNodeId());
    } else {
      currentZdoNegativeCommandFrame[10] = LOW_BYTE(nwkAddressOfInterest);
      currentZdoNegativeCommandFrame[11] = HIGH_BYTE(nwkAddressOfInterest);
    }
    status = emberLookupEui64ByNodeId(nwkAddressOfInterest,
                                      &currentZdoNegativeCommandFrame[2]);
  } else if (clusterId == NODE_DESCRIPTOR_REQUEST && !(negativeZdoCommandFlags
                                                       & NEGATIVE_ZDO_COMMAND_FLAGS_NO_NODE_DESCRIPTOR)) {
    EmberNodeType nodetype;
    emberGetNodeType(&nodetype);
    currentZdoNegativeCommandFrame[1] = EMBER_ZDP_SUCCESS;
    currentZdoNegativeCommandFrame[2] = LOW_BYTE(emberAfGetNodeId());
    currentZdoNegativeCommandFrame[3] = HIGH_BYTE(emberAfGetNodeId());
    currentZdoNegativeCommandFrame[4] = nodetype;
    currentZdoNegativeCommandFrame[5] = ZDO_NODE_DESCRIPTOR_BAND_2400_MHZ;
    currentZdoNegativeCommandFrame[6] = sli_zigbee_descriptor_capability;
    currentZdoNegativeCommandFrame[7] = LOW_BYTE(sli_zigbee_manufacturer_code);
    currentZdoNegativeCommandFrame[8] = HIGH_BYTE(sli_zigbee_manufacturer_code);
    currentZdoNegativeCommandFrame[9] = emberMaximumApsPayloadLength();
    currentZdoNegativeCommandFrame[10] = LOW_BYTE(sli_zigbee_maximum_incoming_transfer_size);
    currentZdoNegativeCommandFrame[11] = HIGH_BYTE(sli_zigbee_maximum_incoming_transfer_size);

    uint8_t mask_lowbyte = 0;
    if (emberGetNodeId() == 0) {
      mask_lowbyte |= 0x01;
    }
    if (sli_zigbee_am_network_manager()) {
      mask_lowbyte |= 0x40;
    }
    currentZdoNegativeCommandFrame[12] = mask_lowbyte;
    currentZdoNegativeCommandFrame[13] = 0x00;

    // Set a global for the Network Creator Security key establishment callback
    sli_zigbee_af_test_harness_z3_server_mask_high = 0;

    currentZdoNegativeCommandFrame[14] = LOW_BYTE(sli_zigbee_maximum_outgoing_transfer_size);
    currentZdoNegativeCommandFrame[15] = HIGH_BYTE(sli_zigbee_maximum_outgoing_transfer_size);
    currentZdoNegativeCommandFrame[16] = 0x00;
    currentZdoNegativeCommandFrameLength = 17;
  } else if (clusterId == MATCH_DESCRIPTORS_REQUEST) {
    if (negativeZdoCommandFlags
        & NEGATIVE_ZDO_COMMAND_FLAGS_MATCH_LIST_ABSENT) {
      // Set the match length to 0.
      currentZdoNegativeCommandFrame[4] = 0;
      currentZdoNegativeCommandFrameLength = 5;
    } else {
      // TODO: fill the match desc response.
    }
  } else if (clusterId == SIMPLE_DESCRIPTOR_REQUEST
             && !(negativeZdoCommandFlags
                  & NEGATIVE_ZDO_COMMAND_FLAGS_NO_SIMPLE_DESCRIPTOR)) {
    // TODO: do we need these to be legit?
    // Servers Basic,Identify,Level, On/Off and OTA
    // Use pre-defined cluster lists.
    uint16_t inCluster[] = IN_CLUSTERS;
    uint8_t inClusterCount = sizeof(inCluster) / sizeof(uint16_t);
    uint16_t outCluster[] = OUT_CLUSTERS;
    uint8_t outClusterCount = sizeof(outCluster) / sizeof(uint16_t);
    // Simple Descriptor Request has - seq(1), short address(2),ep(1)
    if (length < TH_SIMPLE_DESC_REQ_PAYLOAD_LENGTH ) {
      // short length - return.
      return EMBER_INVALID_CALL;
    }
    uint8_t endpoint = requestBuffer[3];
    uint8_t endpointIndex
      = emberAfIndexFromEndpoint(endpoint);
    if (endpointIndex != 0xFF) {
      // If the end point is not the test end point - let ZDO handler handle it
      if (endpoint != TEST_HARNESS_ENDPOINT) {
        return EMBER_INVALID_CALL;
      }
      currentZdoNegativeCommandFrameLength = 0;
      currentZdoNegativeCommandCluster = SIMPLE_DESCRIPTOR_RESPONSE;
      // Sequence number is picked up from request - index 0
      // Account for the field length, increment the counter
      currentZdoNegativeCommandFrameLength++;
      currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
        = EMBER_ZDP_SUCCESS; //Status - Index 1
      if (!(negativeZdoCommandFlags & NEGATIVE_ZDO_COMMAND_FLAGS_NO_NWK_ADDR)) {
        currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
          = LOW_BYTE(emberAfGetNodeId()); // Index 2
        currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
          = HIGH_BYTE(emberAfGetNodeId()); // Index 3
      }
      // Length field index 2 or 4 depending the above.
      // Increment the length to account the length field itself.
      currentZdoNegativeCommandFrameLength++;

      if (!(negativeZdoCommandFlags
            & NEGATIVE_ZDO_COMMAND_FLAGS_NO_ENDPOINT_FIELDS)) {
        // endpoint
        currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
          = endpoint;
      }

      // profile id
      emberAfCopyInt16u(currentZdoNegativeCommandFrame,
                        currentZdoNegativeCommandFrameLength,
                        emberAfProfileIdFromIndex(endpointIndex));
      currentZdoNegativeCommandFrameLength += sizeof(uint16_t);

      // device id
      emberAfCopyInt16u(currentZdoNegativeCommandFrame,
                        currentZdoNegativeCommandFrameLength,
                        emberAfDeviceIdFromIndex(endpointIndex));
      currentZdoNegativeCommandFrameLength += sizeof(uint16_t);

      // device version
      currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
        = emberAfDeviceVersionFromIndex(endpointIndex);

      if (negativeZdoCommandFlags & NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_KE) {
        inCluster[0] = outCluster[0] = ZCL_KEY_ESTABLISHMENT_CLUSTER_ID;
        inClusterCount = outClusterCount = 1;
      }

      // Initialise copy order for in and out clusters
      uint8_t firstCount = inClusterCount;
      uint16_t *firstList  = inCluster;
      uint8_t secondCount = outClusterCount;
      uint16_t *secondList  = outCluster;
      // Swap flag ? - Yes, then swap it
      if (negativeZdoCommandFlags
          & NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_SWAP) {
        firstCount = outClusterCount;
        firstList  = outCluster;
        secondCount = inClusterCount;
        secondList  = inCluster;
      }
      // Copy in order only if cluster list is not absent
      if (!(negativeZdoCommandFlags
            & NEGATIVE_ZDO_COMMAND_FLAGS_CLUSTER_LIST_ABSENT)) {
        currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
          = firstCount;
        for (int i = 0; i < firstCount; i++ ) {
          emberAfCopyInt16u(currentZdoNegativeCommandFrame,
                            currentZdoNegativeCommandFrameLength,
                            firstList[i]);
          currentZdoNegativeCommandFrameLength += sizeof(uint16_t);
        }
        currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
          = secondCount;
        for (int i = 0; i < secondCount; i++ ) {
          emberAfCopyInt16u(currentZdoNegativeCommandFrame,
                            currentZdoNegativeCommandFrameLength,
                            secondList[i]);
          currentZdoNegativeCommandFrameLength += sizeof(uint16_t);
        }
      }

      if (negativeZdoCommandFlags & NEGATIVE_ZDO_COMMAND_FLAGS_NO_NWK_ADDR) {
        currentZdoNegativeCommandFrame[2] // simple descriptor length
          = (currentZdoNegativeCommandFrameLength - 3);
      } else {
        currentZdoNegativeCommandFrame[4] // simple descriptor length
          = (currentZdoNegativeCommandFrameLength - 5);
      }
    } else {
      status = EMBER_ERR_FATAL;
    }
  } else if (clusterId == USER_DESCRIPTOR_REQUEST
             && !(negativeZdoCommandFlags
                  & NEGATIVE_ZDO_COMMAND_FLAGS_NO_USER_DESCRIPTOR)) {
    // User Descriptor Request has - seq(1), short address(2)
    if (length < TH_USER_DESC_REQ_PAYLOAD_LENGTH) {
      // short length - return.
      return EMBER_INVALID_CALL;
    }
    // Note, this is currently just sends a good response for testing -
    // there are no negative command options at present.
    currentZdoNegativeCommandFrameLength = 0;
    currentZdoNegativeCommandCluster = USER_DESCRIPTOR_RESPONSE;
    // Sequence number is picked up from request - index 0
    // Account for the field length, increment the counter
    currentZdoNegativeCommandFrameLength++;
    currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
      = EMBER_ZDP_SUCCESS; //Status - Index 1
    currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
      = LOW_BYTE(emberAfGetNodeId()); // Index 2
    currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength++]
      = HIGH_BYTE(emberAfGetNodeId()); // Index 3

    // Increment the length to account the length field itself.
    currentZdoNegativeCommandFrameLength++;

    // Copy a sample user descriptor.
    static const char userDescriptor[] = "Test Harness App";
    MEMCOPY(&currentZdoNegativeCommandFrame[currentZdoNegativeCommandFrameLength], userDescriptor, TH_USER_DESC_RSP_PAYLOAD_LENGTH);
    currentZdoNegativeCommandFrameLength += TH_USER_DESC_RSP_PAYLOAD_LENGTH;

    currentZdoNegativeCommandFrame[4] // user descriptor length
      = TH_USER_DESC_RSP_PAYLOAD_LENGTH;
  }

  if (status == EMBER_SUCCESS) {
    // We use an event for this command so that the positive stuff will go
    // out of the radio first.
    currentZdoNegativeCommandDestination = sli_zigbee_af_current_sender;
    // Copy sequence number to the response frame, to keep AF discovery happy.
    currentZdoNegativeCommandFrame[0] = requestBuffer[0];
    sl_zigbee_event_set_active(&emberAfPluginTestHarnessZ3ZdoSendEventControl);
  }

  // Maybe change the cluster id to an invalid cluster so we don't process the
  // ZDO command.
  if (!(negativeZdoCommandFlags
        & NEGATIVE_ZDO_COMMAND_FLAGS_SEND_POSITIVE_RESPONSE)) {
    apsFrame->clusterId = 0xFFFF;
  }

  return status;
}
#endif /* EZSP_HOST */

void emberAfPluginTestHarnessZ3ZdoSendEventHandler(sl_zigbee_event_t * event)
{
  sl_zigbee_event_set_inactive(&emberAfPluginTestHarnessZ3ZdoSendEventControl);

  if (!(negativeZdoCommandFlags
        & NEGATIVE_ZDO_COMMAND_FLAGS_NO_NEGATIVE_RESPONSE)) {
    emberAfCorePrintln("%p: %p: 0x%X",
                       TEST_HARNESS_Z3_PRINT_NAME,
                       "ZDO send event handler",
                       sendZdoCommand(currentZdoNegativeCommandDestination,
                                      currentZdoNegativeCommandCluster,
                                      currentZdoNegativeCommandFrame,
                                      currentZdoNegativeCommandFrameLength,
                                      currentZdoNegativeCommandFrame[0]));
  }
}

// plugin test-harness z3 change-channel <newChannel:1>
void sli_zigbeee_af_test_harness_z3_change_channel(SL_CLI_COMMAND_ARG)
{
  uint8_t newChannel = (uint8_t)sl_cli_get_argument_uint8(arguments, 0);

  // Just do it, no delays.
  emberSetRadioChannel(newChannel);
}
