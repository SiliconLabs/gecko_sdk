/***************************************************************************//**
 * @file app.c
 * @brief Callbacks implementation and application specific code.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "app/framework/util/af-main.h"
#include "app/framework/util/util.h"
#include "app/util/zigbee-framework/zigbee-device-common.h"
#include "stack/include/trust-center.h"
#include "zap-cluster-command-parser.h"
#include <stdlib.h>
#include "stack/include/zigbee-security-manager.h"

// The number of tokens that can be written using ezspSetToken and read using
// ezspGetToken.
#define MFGSAMP_NUM_EZSP_TOKENS 8
// The size of the tokens that can be written using ezspSetToken and read using
// ezspGetToken.
#define MFGSAMP_EZSP_TOKEN_SIZE 8
// The number of manufacturing tokens.
#define MFGSAMP_NUM_EZSP_MFG_TOKENS 11
// The size of the largest EZSP Mfg token, EZSP_MFG_CBKE_DATA please refer to
// app/util/ezsp/ezsp-enum.h.
#define MFGSAMP_EZSP_TOKEN_MFG_MAXSIZE 92

extern EmberStatus emberAfTrustCenterStartNetworkKeyUpdate(void);

//----------------------
// ZCL commands handling

static void ias_ace_cluster_arm_command_handler(uint8_t armMode,
                                                uint8_t* armDisarmCode,
                                                uint8_t zoneId)
{
  uint16_t armDisarmCodeLength = emberAfStringLength(armDisarmCode);
  EmberNodeId sender = emberGetSender();
  uint16_t i;

  sl_zigbee_app_debug_print("IAS ACE Arm Received %04X", armMode);

  // Start i at 1 to skip over leading character in the byte array as it is the
  // length byte
  for (i = 1; i < armDisarmCodeLength; i++) {
    sl_zigbee_app_debug_print("%c", armDisarmCode[i]);
  }
  sl_zigbee_app_debug_println(" %02X", zoneId);

  emberAfFillCommandIasAceClusterArmResponse(armMode);
  emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, sender);
}

static void ias_ace_cluster_bypass_command_handler(uint8_t numberOfZones,
                                                   uint8_t* zoneIds,
                                                   uint8_t* armDisarmCode)
{
  EmberNodeId sender = emberGetSender();
  uint8_t i;

  sl_zigbee_app_debug_print("IAS ACE Cluster Bypass for zones ");

  for (i = 0; i < numberOfZones; i++) {
    sl_zigbee_app_debug_print("%d ", zoneIds[i]);
  }
  sl_zigbee_app_debug_println("");

  emberAfFillCommandIasAceClusterBypassResponse(numberOfZones,
                                                zoneIds,
                                                numberOfZones);
  emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT, sender);
}

static uint32_t zcl_ias_ace_cluster_server_command_handler(sl_service_opcode_t opcode,
                                                           sl_service_function_context_t *context)
{
  (void)opcode;

  EmberAfClusterCommand *cmd = (EmberAfClusterCommand *)context->data;

  switch (cmd->commandId) {
    case ZCL_ARM_COMMAND_ID:
    {
      sl_zcl_ias_ace_cluster_arm_command_t cmd_data;

      if (zcl_decode_ias_ace_cluster_arm_command(cmd, &cmd_data)
          != EMBER_ZCL_STATUS_SUCCESS) {
        return EMBER_ZCL_STATUS_UNSUP_COMMAND;
      }

      ias_ace_cluster_arm_command_handler(cmd_data.armMode,
                                          cmd_data.armDisarmCode,
                                          cmd_data.zoneId);
      return EMBER_ZCL_STATUS_SUCCESS;
    }
    case ZCL_BYPASS_COMMAND_ID:
    {
      sl_zcl_ias_ace_cluster_bypass_command_t cmd_data;

      if (zcl_decode_ias_ace_cluster_bypass_command(cmd, &cmd_data)
          != EMBER_ZCL_STATUS_SUCCESS) {
        return EMBER_ZCL_STATUS_UNSUP_COMMAND;
      }

      ias_ace_cluster_bypass_command_handler(cmd_data.numberOfZones,
                                             cmd_data.zoneIds,
                                             cmd_data.armDisarmCode);

      return EMBER_ZCL_STATUS_SUCCESS;
    }
  }

  return EMBER_ZCL_STATUS_UNSUP_COMMAND;
}

//----------------------
// Implemented Callbacks

/** @brief Init
 * Application init function
 */
void emberAfMainInitCallback(void)
{
  // Subscribe to ZCL commands for the IAS_ACE cluster, server side.
  sl_zigbee_subscribe_to_zcl_commands(ZCL_IAS_ACE_CLUSTER_ID,
                                      0xFFFF,
                                      ZCL_DIRECTION_CLIENT_TO_SERVER,
                                      zcl_ias_ace_cluster_server_command_handler);
}

#ifdef SL_CATALOG_CLI_PRESENT
//-------------------------------------
// Custom CLI commands and related code

// The manufacturing tokens are enumerated in app/util/ezsp/ezsp-protocol.h.
// The names are enumerated here to make it easier for the user.
static const char * ezspMfgTokenNames[] =
{
  "EZSP_MFG_CUSTOM_VERSION...",
  "EZSP_MFG_STRING...........",
  "EZSP_MFG_BOARD_NAME.......",
  "EZSP_MFG_MANUF_ID.........",
  "EZSP_MFG_PHY_CONFIG.......",
  "EZSP_MFG_BOOTLOAD_AES_KEY.",
  "EZSP_MFG_ASH_CONFIG.......",
  "EZSP_MFG_EZSP_STORAGE.....",
  "EZSP_STACK_CAL_DATA.......",
  "EZSP_MFG_CBKE_DATA........",
  "EZSP_MFG_INSTALLATION_CODE"
};

// Called to dump all of the tokens. This dumps the indices, the names,
// and the values using ezspGetToken and ezspGetMfgToken. The indices
// are used for read and write functions below.
void mfgappTokenDump(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  EmberStatus status;
  uint8_t tokenData[MFGSAMP_EZSP_TOKEN_MFG_MAXSIZE];
  uint8_t index, i, tokenLength;

  // first go through the tokens accessed using ezspGetToken
  sl_zigbee_app_debug_println("(data shown little endian)");
  sl_zigbee_app_debug_println("Tokens:");
  sl_zigbee_app_debug_println("idx  value:");
  for (index = 0; index < MFGSAMP_NUM_EZSP_TOKENS; index++) {
    // get the token data here
    status = ezspGetToken(index, tokenData);
    sl_zigbee_app_debug_print("[%d]", index);
    if (status == EMBER_SUCCESS) {
      // Print out the token data
      for (i = 0; i < MFGSAMP_EZSP_TOKEN_SIZE; i++) {
        sl_zigbee_app_debug_print(" %02X", tokenData[i]);
      }
      sl_zigbee_app_debug_println("");
    } else {
      // handle when ezspGetToken returns an error
      sl_zigbee_app_debug_println(" ... error 0x%02X ...", status);
    }
  }

  // now go through the tokens accessed using ezspGetMfgToken
  // the manufacturing tokens are enumerated in app/util/ezsp/ezsp-protocol.h
  // this file contains an array (ezspMfgTokenNames) representing the names.
  sl_zigbee_app_debug_println("Manufacturing Tokens:");
  sl_zigbee_app_debug_println("idx  token name                 len   value");
  for (index = 0; index < MFGSAMP_NUM_EZSP_MFG_TOKENS; index++) {
    // ezspGetMfgToken returns a length, be careful to only access
    // valid token indices.
    tokenLength = ezspGetMfgToken(index, tokenData);
    sl_zigbee_app_debug_println("[%x] %s: 0x%x:",
                                index, ezspMfgTokenNames[index], tokenLength);

    // Print out the token data
    for (i = 0; i < tokenLength; i++) {
      if ((i != 0) && ((i % 8) == 0)) {
        sl_zigbee_app_debug_println("");
        sl_zigbee_app_debug_print("                                    :");
      }
      sl_zigbee_app_debug_print(" %02X", tokenData[i]);
    }
    sl_zigbee_app_debug_println("");
  }
  sl_zigbee_app_debug_println("");
}

void changeNwkKeyCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  EmberStatus status = emberAfTrustCenterStartNetworkKeyUpdate();

  if (status != EMBER_SUCCESS) {
    sl_zigbee_app_debug_println("Change Key Error %x", status);
  } else {
    sl_zigbee_app_debug_println("Change Key Success");
  }
}

static void dcPrintKey(uint8_t label, uint8_t *key)
{
  uint8_t i;
  sl_zigbee_app_debug_println("key %x: ", label);
  for (i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i++) {
    sl_zigbee_app_debug_print("%02X", key[i]);
  }
  sl_zigbee_app_debug_println("");
}

void printNextKeyCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  sl_status_t status;
  sl_zb_sec_man_context_t context;
  sl_zb_sec_man_key_t plaintext_key;

  sl_zb_sec_man_init_context(&context);

  context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_NETWORK;
  context.key_index = 1;

  status = sl_zb_sec_man_export_key(&context, &plaintext_key);

  if (status != SL_STATUS_OK) {
    sl_zigbee_app_debug_println("Error getting key");
  } else {
    dcPrintKey(1, plaintext_key.key);
  }
}

void versionCommand(sl_cli_command_arg_t *arguments)
{
  (void)arguments;

  sl_zigbee_app_debug_print("Version:  0.1 Alpha\n");
  sl_zigbee_app_debug_println(" %s", __DATE__);
  sl_zigbee_app_debug_println(" %s", __TIME__);
  sl_zigbee_app_debug_println("");
#ifdef EMBER_TEST
  sl_zigbee_app_debug_println("Print formatter test : 0x%x=0x12, 0x%02x=0x1234 0x%04x=0x12345678",
                              0x12, 0x1234, 0x12345678);
#endif
}

void setTxPowerCommand(sl_cli_command_arg_t *arguments)
{
  int8_t dBm = sl_cli_get_argument_int8(arguments, 0);

  emberSetRadioPower(dBm);
}

#endif

#ifdef SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
bool emberAfGetEndpointInfoCallback(int8u endpoint,
                                    int8u* returnNetworkIndex,
                                    EmberAfEndpointInfoStruct* returnEndpointInfo)
{
  // In case GP endpoint is located on the NCP, the host has no way
  // to know what networkIndex and profileId that endpoint is configured.
  // User has to manually provide that data.
  if (endpoint == 242) {
    *returnNetworkIndex = 0;
    returnEndpointInfo->profileId = 0xA1E0;
    return true;
  }
  return false;
}
#endif // SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT
