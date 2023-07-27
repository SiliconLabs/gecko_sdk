/***************************************************************************//**
 * @file
 * @brief CLI commands for sending various messages.
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
#include "app/framework/cli/security-cli.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/util.h"
#include "zap-config.h"
#include "zcl-cli.h"

//------------------------------------------------------------------------------
// Globals

// EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH is set in config.h
#define APP_ZCL_BUFFER_SIZE EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH

// The command-interpreter doesn't handle individual arguments longer than
// 255 bytes (since it is uses a 1-byte max-length value
#define APP_ZCL_BUFFER_SIZE_CLI \
  (APP_ZCL_BUFFER_SIZE > 255    \
   ? 255                        \
   : APP_ZCL_BUFFER_SIZE)

uint8_t appZclBuffer[APP_ZCL_BUFFER_SIZE];
uint16_t appZclBufferLen;
bool zclCmdIsBuilt = false;

uint16_t mfgSpecificId = EMBER_AF_NULL_MANUFACTURER_CODE;
uint8_t disableDefaultResponse = 0;
EmberApsFrame globalApsFrame;
static bool useNextSequence = false;
// flag to keep track of the fact that we just sent a read attr for time and
// we should set our time to the result of the read attr response
extern bool sli_zigbee_af_syncing_time;

static bool useMulticastBinding = false;

// The direction of global commands, changeable via the "zcl global direction"
// command.  By default, send from client to server, which is how the CLI always
// functioned in the past.
static uint8_t zcl_global_direction = ZCL_FRAME_CONTROL_CLIENT_TO_SERVER;

// Forward declarations
static void zcl_global_setup(uint8_t commandId, sl_cli_command_arg_t *arguments);

void sli_zigbee_af_aps_frame_endpoint_setup(uint8_t srcEndpoint,
                                            uint8_t dstEndpoint);

static void af_aps_frame_cluster_id_setup(uint16_t clusterId)
{
  // setup the global options and cluster ID
  // send command will setup profile ID and endpoints.
  globalApsFrame.options = EMBER_AF_DEFAULT_APS_OPTIONS;
  globalApsFrame.clusterId = clusterId;
}

// keys print
void keysPrintCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  sl_zigbee_core_debug_println("%sSECURITY_LEVEL: %02X",
                               "EMBER_",
                               EMBER_SECURITY_LEVEL);
  printKeyInfo();
}

void eraseKeyTableEntry(uint8_t index)
{
  EmberStatus status = emberEraseKeyTableEntry(index);

  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("%serase key %d: 0x%02X",
                                 "ERROR: ",
                                 index,
                                 status);
  }
}

// Key Delete command
void keysDeleteCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  eraseKeyTableEntry(index);
}

// keys clear
void keysClearCommand(void)
{
#if EMBER_KEY_TABLE_SIZE
  uint8_t i;
  for (i = 0; i < EMBER_KEY_TABLE_SIZE; i++) {
    eraseKeyTableEntry(i);
  }
#endif
}

static void cliBufferPrint(void)
{
  uint8_t cmdIndex = (appZclBuffer[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) ? 4 : 2;
  zclCmdIsBuilt = true;
  sl_zigbee_core_debug_println("Msg: clus 0x%04X, cmd 0x%02X, len %d",
                               globalApsFrame.clusterId,
                               appZclBuffer[cmdIndex],
                               appZclBufferLen);
  sl_zigbee_core_debug_print("buffer: ");
  sl_zigbee_core_debug_print_buffer(appZclBuffer, appZclBufferLen, true);
  sl_zigbee_core_debug_println("");
}

static void zclBufferSetup(uint8_t frameType, uint16_t clusterId, uint8_t commandId)
{
  uint8_t index = 0;
  af_aps_frame_cluster_id_setup(clusterId);
  appZclBuffer[index++] = (frameType
                           | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                           | (mfgSpecificId != EMBER_AF_NULL_MANUFACTURER_CODE
                              ? ZCL_MANUFACTURER_SPECIFIC_MASK
                              : 0)
                           | (disableDefaultResponse
                              ? ZCL_DISABLE_DEFAULT_RESPONSE_MASK
                              : 0));
  if (mfgSpecificId != EMBER_AF_NULL_MANUFACTURER_CODE) {
    appZclBuffer[index++] = (uint8_t)mfgSpecificId;
    appZclBuffer[index++] = (uint8_t)(mfgSpecificId >> 8);
  }
  appZclBuffer[index++] = emberAfNextSequence();
  appZclBuffer[index++] = commandId;
  appZclBufferLen = index;
}

void printTimeCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  emberAfPrintTime(emberAfGetCurrentTime());
}

void sli_zigbee_af_cli_bsend_command(sl_cli_command_arg_t *arguments)
{
#if (EMBER_BINDING_TABLE_SIZE > 0)
  uint8_t srcEndpointToUse;
  EmberStatus status;

  // check that cmd is built
  if (zclCmdIsBuilt == false) {
    sl_zigbee_core_debug_println("cmd not built");
    return;
  }

  srcEndpointToUse = sl_cli_get_argument_uint8(arguments, 0);

  sl_zigbee_core_debug_println("src ep %02x, clus %04x",
                               srcEndpointToUse,
                               globalApsFrame.clusterId);

  globalApsFrame.sourceEndpoint = srcEndpointToUse;
  if (useMulticastBinding) {
    sl_zigbee_core_debug_println("sending to multicast bind");
    status = emberAfSendMulticastToBindings(&globalApsFrame,
                                            appZclBufferLen,
                                            appZclBuffer);
  } else {
    // find a binding to send on
    status = emberAfSendUnicastToBindings(&globalApsFrame,
                                          appZclBufferLen,
                                          appZclBuffer);
  }
#if (defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT) && (SL_ZIGBEE_DEBUG_PRINTS_ZCL_LEGACY_AF_DEBUG_ENABLED == 1))
  sl_zigbee_legacy_af_debug_println("T%08x:TX (%s) %ccast 0x%02x%s",
                                    emberAfGetCurrentTime(),
                                    "CLI",
                                    'U',
                                    status,
                                    ((globalApsFrame.options & EMBER_APS_OPTION_ENCRYPTION)
                                     ? " w/ link key" : ""));
  sl_zigbee_legacy_af_debug_print("TX buffer: [");
  sl_zigbee_legacy_af_debug_print_buffer(appZclBuffer, appZclBufferLen, true);
  sl_zigbee_legacy_af_debug_println("]");
#else
  UNUSED_VAR(status);
#endif // (defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT) && (SL_ZIGBEE_DEBUG_PRINTS_ZCL_LEGACY_AF_DEBUG_ENABLED == 1))
#else
  sl_zigbee_core_debug_println("Error: binding table size is 0");
#endif // (EMBER_BINDING_TABLE_SIZE > 0)
}

// ******************************************************
// send <id> <src endpoint> <dst endpoint>
// send_multicast <group id> <src endpoint>
//
// FFFC = all routers
// FFFD = all non-sleepy
// FFFF = all devices, include sleepy
// ******************************************************
void sli_zigbee_cli_send_command(sl_cli_command_arg_t *arguments)
{
  uint16_t destination = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t srcEndpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t dstEndpoint = sl_cli_get_argument_count(arguments) > 2 ? sl_cli_get_argument_uint8(arguments, 2) : EMBER_BROADCAST_ENDPOINT;
  uint8_t position = sl_cli_get_command_count(arguments) - 1;
  uint8_t *commandName = (uint8_t *) sl_cli_get_command_string(arguments, position);
  EmberStatus status;
  uint8_t label;

  // check that cmd is built
  if (zclCmdIsBuilt == false) {
    sl_zigbee_core_debug_println("no cmd");
    return;
  }

  sli_zigbee_af_aps_frame_endpoint_setup(srcEndpoint, dstEndpoint);

  if (emberAfPreCliSendCallback(&globalApsFrame,
                                emberAfGetNodeId(),
                                destination,
                                appZclBuffer,
                                appZclBufferLen)) {
    return;
  }

  if (commandName[4] == '_') {
    label = 'M';
    status = emberAfSendMulticast(destination,
                                  &globalApsFrame,
                                  appZclBufferLen,
                                  appZclBuffer);
  } else if (destination >= EMBER_BROADCAST_ADDRESS) {
    label = 'B';
    status = emberAfSendBroadcast(destination,
                                  &globalApsFrame,
                                  appZclBufferLen,
                                  appZclBuffer);
  } else {
    label = 'U';
    status = emberAfSendUnicast(EMBER_OUTGOING_DIRECT,
                                destination,
                                &globalApsFrame,
                                appZclBufferLen,
                                appZclBuffer);
  }

  if (status != EMBER_SUCCESS) {
    sl_zigbee_core_debug_println("Error: CLI Send failed, status: 0x%02X", status);
  }
  UNUSED_VAR(label);
  sl_zigbee_legacy_af_debug_println("T%08x:TX (%s) %ccast 0x%02x%s",
                                    emberAfGetCurrentTime(),
                                    "CLI",
                                    label,
                                    status,
                                    ((globalApsFrame.options & EMBER_APS_OPTION_ENCRYPTION)
                                     ? " w/ link key" : ""));
  sl_zigbee_legacy_af_debug_println("TX buffer: [");
  sl_zigbee_legacy_af_debug_print_buffer(appZclBuffer, appZclBufferLen, true);
  sl_zigbee_legacy_af_debug_println("]");

  zclCmdIsBuilt = false;
  mfgSpecificId = EMBER_AF_NULL_MANUFACTURER_CODE;
  disableDefaultResponse = 0;
}

// read <endpoint:1> <cluster:2> <attribute:2> <mask:1>
void sli_zigbee_zcl_read_cli_command(sl_cli_command_arg_t *arguments)
{
  EmberAfStatus status;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 0);
  EmberAfClusterId cluster = (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 1);
  EmberAfAttributeId attribute = (EmberAfAttributeId)sl_cli_get_argument_uint16(arguments, 2);
  bool serverAttribute = (bool)sl_cli_get_argument_uint8(arguments, 3);
  uint8_t data[ATTRIBUTE_LARGEST];
  uint8_t dataType;

  sl_zigbee_core_debug_print("%s: ep: %d, cl: 0x%04X, attr: 0x%04X",
                             "read",
                             endpoint,
                             cluster,
                             attribute);
  sl_zigbee_core_debug_println(", svr: %c", (serverAttribute ? 'y' : 'n'));

  status = emberAfReadAttribute(endpoint,
                                cluster,
                                attribute,
                                (serverAttribute
                                 ? CLUSTER_MASK_SERVER
                                 : CLUSTER_MASK_CLIENT),
                                data,
                                sizeof(data),
                                &dataType);
  if (status == EMBER_ZCL_STATUS_SUCCESS) {
    if (emberAfIsStringAttributeType(dataType)) {
      sl_zigbee_core_debug_print_string(data);
    } else if (emberAfIsLongStringAttributeType(dataType)) {
      sl_zigbee_core_debug_print_long_string(data);
    } else {
      sl_zigbee_core_debug_print_buffer(data, emberAfGetDataSize(dataType), true);
    }
    sl_zigbee_core_debug_println("");
  } else {
    sl_zigbee_core_debug_println("%s: read: 0x%02x", "Error", status);
  }
}
// ******************************************************
// write <ep> <cluster> <attrID> <mask> <dataType> <data bytes>
// ******************************************************
void sli_zigbee_zcl_write_cli_command(sl_cli_command_arg_t *arguments)
{
  //uint8_t i;
  EmberAfStatus status;
  // Ensure data[] is at least two bytes to accommodate possibility
  // of zero-length LONG string having two-byte length prefix.
  uint8_t data[ATTRIBUTE_LARGEST + 1];

  uint8_t  endpoint  = sl_cli_get_argument_uint8(arguments, 0);
  uint16_t cluster   = sl_cli_get_argument_uint16(arguments, 1);
  uint16_t attribute = sl_cli_get_argument_uint16(arguments, 2);
  bool serverAttribute = sl_cli_get_argument_uint8(arguments, 3);
  uint8_t  dataType  = sl_cli_get_argument_uint8(arguments, 4);

  sl_zigbee_core_debug_print("%s: ep: %d, cl: 0x%04X, attr: 0x%04X",
                             "write",
                             endpoint,
                             cluster,
                             attribute);
  sl_zigbee_core_debug_println(", svr: %c, dtype: 0x%02X",
                               (serverAttribute ? 'y' : 'n'),
                               dataType);

  // If the data type is a string, automatically prepend a length to the data;
  // otherwise, just copy the raw bytes.
  MEMSET(data, 0, ATTRIBUTE_LARGEST);
  if (emberAfIsStringAttributeType(dataType)) {
    // string, 1-byte length prefix
    data[0] = sl_zigbee_copy_hex_arg(arguments,
                                     5,
                                     data + 1,
                                     ATTRIBUTE_LARGEST - 1,
                                     false);
  } else if (emberAfIsLongStringAttributeType(dataType)) {
    // LONG string with 2-byte length prefix.
    // CLI restricts string length to <= 255, so returned length will go
    // into lower prefix byte and upper prefix byte will be zero.
    data[0] = sl_zigbee_copy_hex_arg(arguments,
                                     5,
                                     data + 2,
                                     ATTRIBUTE_LARGEST - 2,
                                     false);
#if (ATTRIBUTE_LARGEST < 1)
#error "ATTRIBUTE_LARGEST should be greater greater than 0"
#endif
    data[1] = 0;
  } else {
    sl_zigbee_copy_hex_arg(arguments,
                           5,
                           data,
                           emberAfGetDataSize(dataType),
                           false);
  }

  status = emberAfWriteAttribute(endpoint,
                                 cluster,
                                 attribute,
                                 (serverAttribute
                                  ? CLUSTER_MASK_SERVER
                                  : CLUSTER_MASK_CLIENT),
                                 data,
                                 dataType);
  sli_zigbee_af_print_status("write", status);
  sl_zigbee_core_debug_println("");
}

static void zcl_buffer_add_byte(uint8_t byte)
{
  appZclBuffer[appZclBufferLen] = byte;
  appZclBufferLen += 1;
}

static void zcl_buffer_add_word(uint16_t word)
{
  zcl_buffer_add_byte(LOW_BYTE(word));
  zcl_buffer_add_byte(HIGH_BYTE(word));
}

static void zcl_buffer_add_int32(uint32_t value)
{
  uint8_t i;
  for (i = 0; i < 4; i++) {
    zcl_buffer_add_byte(LOW_BYTE(value));
    value = value >> 8;
  }
}

// Writes the length and contents of the string found at argIndex
// into the zcl buffer. Takes into account whether string is non-LONG
// (1-byte length prefix) or LONG (2-byte length prefix).
static void zcl_buffer_add_length_and_string(sl_cli_command_arg_t *arguments,
                                             uint8_t argIndex,
                                             bool isLongStringType)
{
  uint8_t prefixSize = (isLongStringType ? 2 : 1);
  // We protect against copying outside of the appZclBuffer
  // by passing the maximum length of the buffer, or a maximum
  // value of an uint8_t.
  uint16_t maxLength = APP_ZCL_BUFFER_SIZE - (appZclBufferLen + prefixSize);
  if (maxLength > MAX_INT8U_VALUE) {
    maxLength = MAX_INT8U_VALUE;
  }
  uint8_t length = sl_zigbee_copy_string_arg(arguments,
                                             argIndex,
                                             appZclBuffer + appZclBufferLen + prefixSize,
                                             maxLength,
                                             false);
  appZclBuffer[appZclBufferLen] = length;
  if (prefixSize == 2) {
    // CLI max string length is 255, so LONG string upper length byte is zero.
    appZclBuffer[appZclBufferLen + 1] = 0;
  }
  appZclBufferLen += length + prefixSize;
}

/**
 * @brief
 * Given a 32-bit value and a specified number of bits fewer than 32, check that
 * the value does not exceed the range of the specified number of bits.
 * @param val
 * @param bits
 * @return true if value in range else return false
 */
static bool is_zcl_data_type_in_range(uint32_t val, uint8_t bits)
{
  if (bits == 0 || bits > 31) {
    return false;
  }
  // Construct mask of the container's unused higher order bits.
  uint32_t unusedBitsMask = ~((1u << bits) - 1u);
  // Return true if the unused higher order bits are all zero.
  return (unusedBitsMask & val) == 0;
}

/**
 * @brief
 * Given a value then add n number of bytes into the zcl buffer from that value
 * @param val
 * @param noOfBytes
 */
static void add_bytes_to_zcl_buffer(uint32_t val, uint8_t noOfBytes)
{
  for (uint8_t i = 0; i < noOfBytes; i++) {
    uint8_t byteN = (uint8_t)(val >> (8u * i));
    zcl_buffer_add_byte(byteN);
  }
}

// Handles any zcl command where the argument list of the
// command is simply appended to the zcl buffer.  Handles argument types
// mentioned in the switch case below.  String arguments are written with
// a length byte first.
void sli_zigbee_zcl_simple_command(uint8_t frameControl,
                                   uint16_t clusterId,
                                   uint8_t commandId,
                                   sl_cli_command_arg_t *arguments,
                                   uint8_t *argumentTypes)
{
  uint8_t argumentIndex;
  uint8_t count = sl_cli_get_argument_count(arguments);
  uint8_t type;
  uint8_t typeIndex = 0;
  uint8_t *hex_value = 0;
  size_t hex_length = 0;

  zclBufferSetup(frameControl, clusterId, commandId);
  for (argumentIndex = 0; argumentIndex < count; argumentIndex++) {
    type = argumentTypes[typeIndex];
    // For zcl cli array arguments are referenced as optional arguments.
    // Therefore the type of the arguments should remain the same for them.
    if (type != SL_ZCL_CLI_ARG_UINT8OPT
        && type != SL_ZCL_CLI_ARG_UINT16OPT
        && type != SL_ZCL_CLI_ARG_UINT24OPT
        && type != SL_ZCL_CLI_ARG_UINT32OPT
        && type != SL_ZCL_CLI_ARG_UINT40OPT
        && type != SL_ZCL_CLI_ARG_UINT48OPT
        && type != SL_ZCL_CLI_ARG_UINT56OPT
        && type != SL_ZCL_CLI_ARG_UINT64OPT
        && type != SL_ZCL_CLI_ARG_INT8OPT
        && type != SL_ZCL_CLI_ARG_INT16OPT
        && type != SL_ZCL_CLI_ARG_INT24OPT
        && type != SL_ZCL_CLI_ARG_INT32OPT
        && type != SL_ZCL_CLI_ARG_INT40OPT
        && type != SL_ZCL_CLI_ARG_INT48OPT
        && type != SL_ZCL_CLI_ARG_INT56OPT
        && type != SL_ZCL_CLI_ARG_INT64OPT
        && type != SL_ZCL_CLI_ARG_STRINGOPT
        && type != SL_ZCL_CLI_ARG_HEXOPT) {
      typeIndex++;
    }
    switch (type) {
      case SL_ZCL_CLI_ARG_UINT8:
      case SL_ZCL_CLI_ARG_UINT8OPT:
        zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_UINT16:
      case SL_ZCL_CLI_ARG_UINT16OPT:
        zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_UINT24:
      case SL_ZCL_CLI_ARG_UINT24OPT:
        if (is_zcl_data_type_in_range(sl_cli_get_argument_uint32(arguments, argumentIndex), 24u)) {
          add_bytes_to_zcl_buffer(sl_cli_get_argument_uint32(arguments, argumentIndex), 3);
        } else {
          sl_zigbee_zcl_debug_println("Argument at index: %d is out of range", argumentIndex);
          goto kickout;
        }
        break;
      case SL_ZCL_CLI_ARG_UINT32:
      case SL_ZCL_CLI_ARG_UINT32OPT:
        zcl_buffer_add_int32(sl_cli_get_argument_uint32(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_INT8:
      case SL_ZCL_CLI_ARG_INT8OPT:
        zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_int8(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_INT16:
      case SL_ZCL_CLI_ARG_INT16OPT:
        zcl_buffer_add_word(sl_cli_get_argument_int16(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_INT24:
      case SL_ZCL_CLI_ARG_INT24OPT:
        if (is_zcl_data_type_in_range(sl_cli_get_argument_int32(arguments, argumentIndex), 24u)) {
          add_bytes_to_zcl_buffer(sl_cli_get_argument_int32(arguments, argumentIndex), 3);
        } else {
          sl_zigbee_zcl_debug_println("Argument at index: %d is out of range", argumentIndex);
          goto kickout;
        }
        break;
      case SL_ZCL_CLI_ARG_INT32:
      case SL_ZCL_CLI_ARG_INT32OPT:
        zcl_buffer_add_int32(sl_cli_get_argument_int32(arguments, argumentIndex));
        break;
      case SL_ZCL_CLI_ARG_HEX:
      case SL_ZCL_CLI_ARG_HEXOPT:
        hex_value = sl_cli_get_argument_hex(arguments, argumentIndex, &hex_length);
        for (uint8_t i = 0; i < hex_length; i++) {
          appZclBuffer[appZclBufferLen + i] = hex_value[i];
        }
        appZclBufferLen += hex_length;
        break;
      case SL_ZCL_CLI_ARG_STRING:
      case SL_ZCL_CLI_ARG_STRINGOPT:
        zcl_buffer_add_length_and_string(arguments, argumentIndex, false);
        break;
      default:
        goto kickout;
    }
  }
  kickout:
  cliBufferPrint();
}

void sli_zigbee_cli_zcl_mfg_code_command(sl_cli_command_arg_t *arguments)
{
  if (zclCmdIsBuilt) {
    sl_zigbee_zcl_debug_println("Command already built.  Cannot set MFG specific code for command.");
    return;
  }
  mfgSpecificId = sl_cli_get_argument_uint16(arguments, 0);
  sl_zigbee_zcl_debug_println("MFG Code Set for next command: 0x%04X", mfgSpecificId);
}

void sli_zigbee_cli_zcl_time_command(sl_cli_command_arg_t *arguments)
{
  emberAfSetTime(sl_cli_get_argument_uint32(arguments, 0));
}

void sli_zigbee_cli_zcl_use_next_sequence_command(sl_cli_command_arg_t *arguments)
{
  useNextSequence = sl_cli_get_argument_uint8(arguments, 0);
  sl_zigbee_zcl_debug_println("Use Next Sequence Set for next command: 0x%02X", useNextSequence);
}

void sli_zigbee_cli_zcl_x_default_resp_command(sl_cli_command_arg_t *arguments)
{
  disableDefaultResponse = sl_cli_get_argument_uint8(arguments, 0);
  sl_zigbee_zcl_debug_println("Disable Default Response Set for next command: 0x%02X", disableDefaultResponse);
}

// zcl test response on
void sli_zigbee_cli_zcl_test_response_on_command(sl_cli_command_arg_t *arguments)
{
  emberAfSetNoReplyForNextMessage(false);
}

// zcl test response off
void sli_zigbee_cli_zcl_test_response_off_command(sl_cli_command_arg_t *arguments)
{
  emberAfSetNoReplyForNextMessage(true);
}

#if defined(ZCL_USING_IDENTIFY_CLUSTER_SERVER) || defined(ZCL_USING_IDENTIFY_CLUSTER_CLIENT)
static void sli_zigbee_cli_zcl_identify_on_off_command(sl_cli_command_arg_t *arguments, uint16_t timeS)
{
  EmberAfStatus afStatus = emberAfWriteServerAttribute(
    sl_cli_get_argument_uint8(arguments, 0),                       // endpoint
    ZCL_IDENTIFY_CLUSTER_ID,
    ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
    (uint8_t *)&timeS,
    ZCL_INT16U_ATTRIBUTE_TYPE);
  if (EMBER_ZCL_STATUS_SUCCESS != afStatus) {
    sl_zigbee_legacy_af_debug_println("Identify On/Off: failed to write value 0x%04x  to cluster "
                                      "0x%04x attribute ID 0x%04x: error 0x%02x",
                                      timeS,
                                      ZCL_IDENTIFY_CLUSTER_ID,
                                      ZCL_IDENTIFY_TIME_ATTRIBUTE_ID,
                                      afStatus);
  }
}

// zcl identify on <endpoint:1> <time:2>
void sli_zigbee_cli_zcl_identify_on_command(sl_cli_command_arg_t *arguments)
{
  uint16_t timeS = 0;
  timeS = sl_cli_get_argument_uint16(arguments, 1);
  if (timeS == 0) {
    timeS = 60;
  }
  sli_zigbee_cli_zcl_identify_on_off_command(arguments, timeS);
}

// zcl identify off <endpoint:1>
void sli_zigbee_cli_zcl_identify_off_command(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_cli_zcl_identify_on_off_command(arguments, 0);
}
#endif // ZCL_USING_IDENTIFY_CLUSTER_SERVER

#if defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_SERVER) || defined(ZCL_USING_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_CLIENT)
// zcl drlc lce <eventId:4> <start:4> <duration:2> <event control:1>
void sli_zigbee_cli_zcl_drlc_load_control_event_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID,
                 ZCL_LOAD_CONTROL_EVENT_COMMAND_ID);
  zcl_buffer_add_int32(sl_cli_get_argument_uint32(arguments, 0));  // event id
  zcl_buffer_add_word(0x0fff);          // all device classes
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 1)); // UEG
  zcl_buffer_add_int32(sl_cli_get_argument_uint32(arguments, 2));  // start
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 3)); // duration
  zcl_buffer_add_byte(1);               // criticality level, normal
  zcl_buffer_add_byte(0);               // 1.1c cooling temp offset
  zcl_buffer_add_byte(0);               // 1.1c heating temp offset
  zcl_buffer_add_word(0x1a09);          // cool temp set point 23.3c
  zcl_buffer_add_word(0x1a09);          // heat temp set point
  zcl_buffer_add_byte(0x0a);            // -10% avg load percent
  zcl_buffer_add_byte(0);               // duty cycle
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 4));   // event control
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}
#endif

#if defined(ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_CLIENT) || defined(ZCL_USING_BACNET_PROTOCOL_TUNNEL_CLUSTER_SERVER)
// zcl bacnet transfer-npdu whois
void sli_zigbee_cli_zcl_bacnet_transfer_whois_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID,
                 ZCL_TRANSFER_NPDU_COMMAND_ID);
  //zclBufferAddByte(0);            // what is this?
  zcl_buffer_add_int32(0xFFFF2001);
  zcl_buffer_add_int32(0x0810FF00);
  cliBufferPrint();
}
#endif

#if defined(ZCL_USING_TUNNELING_CLUSTER_CLIENT) || defined(ZCL_USING_TUNNELING_CLUSTER_SERVER)
// zcl tunneling random-to-server <tunnel id:2> <length:2>
void sli_zigbee_cli_zcl_tunneling_random_to_server_command(sl_cli_command_arg_t *arguments)
{
  uint16_t length = sl_cli_get_argument_uint16(arguments, 1); // length of random data
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 0)); // tunnel id
  appZclBufferLen = (appZclBufferLen + length < APP_ZCL_BUFFER_SIZE
                     ? appZclBufferLen + length
                     : APP_ZCL_BUFFER_SIZE);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl tunneling transfer-to-server <tunnel id:2> <data>
void sli_zigbee_cli_zcl_tunneling_transfer_to_server_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_CLIENT_TO_SERVER_COMMAND_ID);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 0));              // tunnel id
  appZclBufferLen += sl_zigbee_copy_hex_arg(arguments,
                                            1,    // data
                                            appZclBuffer + appZclBufferLen,
                                            APP_ZCL_BUFFER_SIZE_CLI - appZclBufferLen,    // copy as much data as possible
                                            false);    // no padding
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl tunneling transfer-to-client <tunnel id:2> <data>
void sli_zigbee_cli_zcl_tunneling_transfer_to_client_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 0));              // tunnel id
  appZclBufferLen += sl_zigbee_copy_hex_arg(arguments,
                                            1,    // data
                                            appZclBuffer + appZclBufferLen,
                                            APP_ZCL_BUFFER_SIZE_CLI - appZclBufferLen,    // copy as much data as possible
                                            false);    // no padding
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}

// zcl tunneling random-to-client <tunnel id:2> <length:2>
void sli_zigbee_cli_zcl_tunneling_random_to_client_command(sl_cli_command_arg_t *arguments)
{
  uint16_t length = sl_cli_get_argument_uint16(arguments, 1); // length of random data
  zclBufferSetup(ZCL_CLUSTER_SPECIFIC_COMMAND
                 | ZCL_FRAME_CONTROL_SERVER_TO_CLIENT,
                 ZCL_TUNNELING_CLUSTER_ID,
                 ZCL_TRANSFER_DATA_SERVER_TO_CLIENT_COMMAND_ID);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 0)); // tunnel id
  appZclBufferLen = (appZclBufferLen + length < APP_ZCL_BUFFER_SIZE
                     ? appZclBufferLen + length
                     : APP_ZCL_BUFFER_SIZE);
  globalApsFrame.options |= EMBER_APS_OPTION_SOURCE_EUI64;
  cliBufferPrint();
}
#endif

// zcl global disc-com-gen <cluster id:2> <start command id:1> <max command id:1>
void sli_zigbee_cli_zcl_global_command_discovery_generated_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 0),   // cluster id
                 ZCL_DISCOVER_COMMANDS_GENERATED_COMMAND_ID);
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 1)); // start command id
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 2)); // max command ids
  cliBufferPrint();
}

// zcl global disc-com-rec <cluster id:2> <start command id:1> <max command id:1>
void sli_zigbee_cli_zcl_global_command_discovery_received_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 0),   // cluster id
                 ZCL_DISCOVER_COMMANDS_RECEIVED_COMMAND_ID);
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 1)); // start command id
  zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 2)); // max command ids
  cliBufferPrint();
}

// zcl global direction <direction:1>
void sli_zigbee_cli_zcl_global_direction_command(sl_cli_command_arg_t *arguments)
{
  zcl_global_direction = ((((uint8_t)sl_cli_get_argument_uint8(arguments, 0))
                           == ZCL_DIRECTION_CLIENT_TO_SERVER)
                          ? ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                          : ZCL_FRAME_CONTROL_SERVER_TO_CLIENT);
}

// zcl global expect-report-from-me <cluster id:2> <attribute id:2> <timeout:2>
void sli_zigbee_cli_zcl_global_expect_report_from_me_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 0), // cluster id
                 ZCL_CONFIGURE_REPORTING_COMMAND_ID);
  zcl_buffer_add_byte(EMBER_ZCL_REPORTING_DIRECTION_RECEIVED);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 1)); // attribute id
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 2)); // timeout
  cliBufferPrint();
}

// Common zcl global write api for write/nwrite/uwrite
static void zigbee_zcl_global_write_command_common(sl_cli_command_arg_t *arguments, uint8_t type_of_write)
{
  uint8_t type = sl_cli_get_argument_uint8(arguments, 2);
  uint8_t commandId = type_of_write;
  zcl_global_setup(commandId, arguments);

  if (emberAfIsThisDataTypeAStringType(type)) {
    uint8_t bytes_reserved_for_string_length = emberAfIsLongStringAttributeType(type) ? 2 : 1;
    size_t hex_array_size;
    sl_cli_get_argument_hex(arguments, 3, &hex_array_size);
    // Checking for ZCL Buffer Overflow by protecting the copy of anything
    // outside appZclBuffer
    uint16_t buffer_length_remaining = APP_ZCL_BUFFER_SIZE - (appZclBufferLen + bytes_reserved_for_string_length);
    if (hex_array_size > buffer_length_remaining) {
      hex_array_size = APP_ZCL_BUFFER_SIZE - (appZclBufferLen + bytes_reserved_for_string_length);
    }
    // Copy the string into the zclBuffer.
    sl_zigbee_copy_hex_arg(arguments,
                           3,
                           appZclBuffer + appZclBufferLen + bytes_reserved_for_string_length,
                           hex_array_size,
                           true);
    // In the zcl buffer, set the length of the string which precedes the string
    *(appZclBuffer + appZclBufferLen) = (uint8_t)hex_array_size;
    if (bytes_reserved_for_string_length == 2) {
      // Making sure the high length byte is written down as well in little endian format.
      *(appZclBuffer + appZclBufferLen + 1) = (uint8_t)(hex_array_size >> 8);
    }
    appZclBufferLen += hex_array_size + bytes_reserved_for_string_length;
  } else {
    uint8_t length = emberAfGetDataSize(type);
    sl_zigbee_copy_hex_arg(arguments,
                           3,
                           appZclBuffer + appZclBufferLen,
                           length,
                           true);    // pad with zeroes
    appZclBufferLen += length;
  }
  cliBufferPrint();
}
// zcl global write <cluster:2> <attrID:2> <type:1> <data>
void sli_zigbee_cli_zcl_global_write_command(sl_cli_command_arg_t *arguments)
{
  zigbee_zcl_global_write_command_common(arguments, ZCL_WRITE_ATTRIBUTES_COMMAND_ID);
}

// zcl global uwrite <cluster:2> <attrID:2> <type:1> <data>
void sli_zigbee_cli_zcl_global_uwrite_command(sl_cli_command_arg_t *arguments)
{
  zigbee_zcl_global_write_command_common(arguments, ZCL_WRITE_ATTRIBUTES_UNDIVIDED_COMMAND_ID);
}

// zcl global nwrite <cluster:2> <attrID:2> <type:1> <data>
void sli_zigbee_cli_zcl_global_nwrite_command(sl_cli_command_arg_t *arguments)
{
  zigbee_zcl_global_write_command_common(arguments, ZCL_WRITE_ATTRIBUTES_NO_RESPONSE_COMMAND_ID);
}

// zcl global discover <cluster> <attrID:2> <max # to report:1>
void sli_zigbee_cli_zcl_global_discover_command(sl_cli_command_arg_t *arguments)
{
  zcl_global_setup(ZCL_DISCOVER_ATTRIBUTES_COMMAND_ID, arguments);
  cliBufferPrint();
}

// zcl global read <cluster:2> <attribute:2>
void sli_zigbee_cli_zcl_global_read_command(sl_cli_command_arg_t *arguments)
{
  zcl_global_setup(ZCL_READ_ATTRIBUTES_COMMAND_ID, arguments);
  cliBufferPrint();
}

// zcl global report <src endpoint id:1> <cluster id:2> <attribute id:2> <mask:1>
void sli_zigbee_cli_zcl_global_report_command(sl_cli_command_arg_t *arguments)
{
  EmberAfStatus status;
  EmberAfClusterId clusterId = (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 1);
  EmberAfAttributeId attributeId = (EmberAfAttributeId)sl_cli_get_argument_uint16(arguments, 2);
  uint8_t mask = (uint8_t)sl_cli_get_argument_uint8(arguments, 3);
  EmberAfAttributeType type;
  uint16_t size;
  uint8_t data[ATTRIBUTE_LARGEST];

  status = emberAfReadAttribute((uint8_t)sl_cli_get_argument_uint8(arguments, 0), // endpoint
                                clusterId,
                                attributeId,
                                (mask == 0
                                 ? CLUSTER_MASK_CLIENT
                                 : CLUSTER_MASK_SERVER),
                                data,
                                sizeof(data),
                                &type);
  if (status != EMBER_ZCL_STATUS_SUCCESS) {
    sl_zigbee_zcl_debug_println("ERR: reading attribute %02x", status);
    return;
  }

  zclBufferSetup(ZCL_GLOBAL_COMMAND
                 | (mask == 0
                    ? ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                    : ZCL_FRAME_CONTROL_SERVER_TO_CLIENT),
                 clusterId,
                 ZCL_REPORT_ATTRIBUTES_COMMAND_ID);
  zcl_buffer_add_word(attributeId);
  zcl_buffer_add_byte(type);

  size = emberAfAttributeValueSize(type, data, sizeof(data));
  if (size == 0 || size > (APP_ZCL_BUFFER_SIZE - appZclBufferLen)) {
    sl_zigbee_zcl_debug_println("ERR: attribute size %d too large for buffer", size);
    return;
  }
#if (BIGENDIAN_CPU)
  if (isThisDataTypeSentLittleEndianOTA(type)) {
    emberReverseMemCopy(appZclBuffer + appZclBufferLen, data, size);
  } else {
    MEMMOVE(appZclBuffer + appZclBufferLen, data, size);
  }
#else
  MEMMOVE(appZclBuffer + appZclBufferLen, data, size);
#endif
  appZclBufferLen += size;

  cliBufferPrint();
}

// zcl global report-read <cluster> <attrID:2> <direction:1>
void sli_zigbee_cli_zcl_global_report_read_command(sl_cli_command_arg_t *arguments)
{
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 0), // cluster id
                 ZCL_READ_REPORTING_CONFIGURATION_COMMAND_ID);
  zcl_buffer_add_byte(sl_cli_get_argument_uint8(arguments, 2)); // direction
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 1)); // attribute id
  cliBufferPrint();
}

// zcl global send-me-a-report <cluster id:2> <attribute id:2> <type:1> ...
// ... <min interval:2> <max interval:2> <reportable change:1-4>
void sli_zigbee_cli_zcl_global_send_me_a_report_command(sl_cli_command_arg_t *arguments)
{
  uint8_t type = (uint8_t)sl_cli_get_argument_uint8(arguments, 2);
  uint16_t attributeId = sl_cli_get_argument_uint16(arguments, 1);
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 (EmberAfClusterId)sl_cli_get_argument_uint16(arguments, 0), // cluster id
                 ZCL_CONFIGURE_REPORTING_COMMAND_ID);
  zcl_buffer_add_byte(EMBER_ZCL_REPORTING_DIRECTION_REPORTED);
  zcl_buffer_add_word(attributeId);
  zcl_buffer_add_byte(type);           // type
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 3));  // minimum reporting interval
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 4));  // maximum reporting interval

  // If the data type is analog, then the reportable change field is the same
  // size as the data type.  Otherwise, it is omitted.
  if (emberAfGetAttributeAnalogOrDiscreteType(type)
      == EMBER_AF_DATA_TYPE_ANALOG) {
    uint8_t dataSize = emberAfGetDataSize(type);
    size_t len = dataSize;
    uint8_t *ptr_string = sl_cli_get_argument_hex(arguments, 5, &len);
    if (len != dataSize) {
      printf("Error: attribute ID 0x%04X reportable change is size %dB, but %dB entered\n",
             attributeId,
             dataSize,
             (int)len);
      return;
    }
    MEMMOVE(appZclBuffer + appZclBufferLen,
            ptr_string,
            len);
    appZclBufferLen += dataSize;
  }
  cliBufferPrint();
}

static void zcl_global_setup(uint8_t commandId, sl_cli_command_arg_t *arguments)
{
  uint16_t clusterId = (uint16_t)sl_cli_get_argument_uint16(arguments, 0);
  zclBufferSetup(ZCL_GLOBAL_COMMAND | zcl_global_direction,
                 clusterId,
                 commandId);
  zcl_buffer_add_word(sl_cli_get_argument_uint16(arguments, 1));  // attr id
  if (commandId != ZCL_READ_ATTRIBUTES_COMMAND_ID) {
    zcl_buffer_add_byte((uint8_t)sl_cli_get_argument_uint8(arguments, 2));
  }
}

// for sending raw (user defined) ZCL messages
// raw <cluster> <data bytes>
// note: limited to 0xff bytes in length

void sli_zigbee_af_cli_raw_command(sl_cli_command_arg_t *arguments)
{
  uint8_t seqNumIndex;
  uint8_t length;
  af_aps_frame_cluster_id_setup(sl_cli_get_argument_uint16(arguments, 0));
  length = sl_zigbee_copy_hex_arg(arguments, 1, appZclBuffer, APP_ZCL_BUFFER_SIZE_CLI, false);
  seqNumIndex = (appZclBuffer[0] & ZCL_MANUFACTURER_SPECIFIC_MASK) ? 3 : 1;
  if (useNextSequence) {
    appZclBuffer[seqNumIndex] = emberAfNextSequence();
  }
  appZclBufferLen = length;
  cliBufferPrint();
}

void sli_zigbee_af_cli_send_using_multicast_binding_command(sl_cli_command_arg_t *arguments)
{
  useMulticastBinding = (bool)sl_cli_get_argument_uint8(arguments, 0);
}

// timesync <id> <src endpoint> <dest endpoint>
//
// This sends a read attr for the time of the device specified. It sets a flag
// so when it gets the response it writes the time to its own time attr
void sli_zigbee_af_cli_timesync_command(sl_cli_command_arg_t *arguments)
{
  // send a read attr for time
  zclBufferSetup(ZCL_GLOBAL_COMMAND | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER,
                 ZCL_TIME_CLUSTER_ID,
                 ZCL_READ_ATTRIBUTES_COMMAND_ID);
  zcl_buffer_add_word(ZCL_TIME_ATTRIBUTE_ID);
  sli_zigbee_af_syncing_time = true;
  cliBufferPrint();
  sli_zigbee_cli_send_command(arguments);
}

void sli_zigbee_af_aps_frame_endpoint_setup(uint8_t srcEndpoint,
                                            uint8_t dstEndpoint)
{
  globalApsFrame.sourceEndpoint = (srcEndpoint == 0
                                   ? emberAfPrimaryEndpointForCurrentNetworkIndex()
                                   : srcEndpoint);
  globalApsFrame.destinationEndpoint = dstEndpoint;
}
