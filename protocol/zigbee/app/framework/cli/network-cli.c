/***************************************************************************//**
 * @file
 * @brief Implementations for network related CLI commands.
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
#include "app/util/serial/sl_zigbee_command_interpreter.h"

// TODO: this is to bring in sli_zigbee_af_permit_join() and emberAfGetBindingTableSize()
// prototypes.
#include "app/framework/util/af-main.h"
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_PRESENT
#include "test-harness-config.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
extern EmberEvent sli_zigbee_leave_event;
#endif

uint8_t sli_zigbee_af_cli_network_index = EMBER_AF_DEFAULT_NETWORK_INDEX;
extern uint8_t sli_zigbee_af_extended_pan_id[];
static void initNetworkParams(EmberNetworkParameters *networkParams,
                              sl_cli_command_arg_t *arguments)
{
  MEMSET(networkParams, 0, sizeof(EmberNetworkParameters));
  emberAfGetFormAndJoinExtendedPanIdCallback(networkParams->extendedPanId);
  networkParams->radioChannel = sl_cli_get_argument_uint8(arguments, 0);
  networkParams->radioTxPower = sl_cli_get_argument_int8(arguments, 1);
  networkParams->panId = sl_cli_get_argument_uint16(arguments, 2);
  if (sl_cli_get_argument_count(arguments) > 3) {
    // Map the channel page into the channel, if present.
    // Page bits: 7, 6, 5 channel bits: 4...0
    uint8_t page = sl_cli_get_argument_uint8(arguments, 3);
    networkParams->radioChannel = (uint8_t)((page << 5) | (networkParams->radioChannel & 0x1F));
  }
}

// network form <channel> <power> <panid>
void networkFormCommand(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_HAS_COORDINATOR_NETWORK
  EmberStatus status;
  EmberNetworkParameters networkParams;
  initNetworkParams(&networkParams, arguments);
  status = emberAfFormNetwork(&networkParams);
  sl_zigbee_core_debug_print("form 0x%02X\n", status);
  emberAfAppFlush();
#else
  sl_zigbee_core_debug_print("only coordinators can form\n");
#endif
}

// net_join <channel> <power> <panid>
void networkJoinCommand(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  EmberNetworkParameters networkParams = { 0 };
  initNetworkParams(&networkParams, arguments);
  status = emberAfJoinNetwork(&networkParams);
  UNUSED_VAR(status);
  sl_zigbee_core_debug_print("join 0x%02X\n", status);
}

// TODO: full port of this CLI command (which includes "network broad-pjoin")
// net_pjoin <time>
void networkPermitJoinCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t duration = sl_cli_get_argument_uint8(arguments, 0);
  sli_zigbee_af_permit_join(duration, NULL);
}

// network leave
void networkLeaveCommand(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  status = emberLeaveNetwork();
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
  // Complete the leave immediately without the usual delay.
  emberEventSetActive(&sli_zigbee_leave_event);
#endif
  UNUSED_VAR(status);
  sl_zigbee_core_debug_print("%s 0x%02X\n", "leave", status);
}

// network rejoin <haveCurrentNetworkKey:1> <channelMask:4>
void networkRejoinCommand(sl_cli_command_arg_t *arguments)
{
  bool haveCurrentNetworkKey = (bool)sl_cli_get_argument_uint8(arguments, 0);
  uint32_t channelMask = sl_cli_get_argument_uint32(arguments, 1);
  if (channelMask == 0) {
    channelMask = EMBER_ALL_802_15_4_CHANNELS_MASK;
  }
  EmberStatus status = emberFindAndRejoinNetworkWithReason(haveCurrentNetworkKey,
                                                           channelMask,
                                                           EMBER_AF_REJOIN_DUE_TO_CLI_COMMAND);
  emberAfAppPrintln("%p 0x%x", "rejoin", status);
}

void networkRejoinDiffDeviceTypeCommand(sl_cli_command_arg_t *arguments)
{
  bool haveCurrentNetworkKey = sl_cli_get_argument_uint8(arguments, 0);
  uint32_t channelMask = sl_cli_get_argument_uint32(arguments, 1);
  uint8_t emberNodeType = sl_cli_get_argument_uint8(arguments, 2);
  EmberStatus status = emberFindAndRejoinNetworkWithNodeType(haveCurrentNetworkKey,
                                                             channelMask,
                                                             emberNodeType);
  emberAfAppPrintln("%p 0x%x", "rejoinDiffDeviceType", status);
}

// network extpanid <8 BYTES>
void networkExtendedPanIdCommand(sl_cli_command_arg_t *arguments)
{
  sl_zigbee_copy_eui64_arg(arguments, 0, sli_zigbee_af_extended_pan_id, true);
  emberAfSetFormAndJoinExtendedPanIdCallback(sli_zigbee_af_extended_pan_id);
  emberAfAppPrint("ext. PAN ID: ");
  emberAfAppDebugExec(emberAfPrintBigEndianEui64(sli_zigbee_af_extended_pan_id));
  emberAfAppPrintln("");
}

// check pjoin status
void networkCheckPjoinCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t open_duration = emberAfGetOpenNetworkDurationSec();
  if (open_duration > 0) {
    emberAfAppPrintln("NWK open: %u sec", open_duration);
  } else {
    emberAfAppPrintln("NWK closed");
  }
}

void findJoinableNetworkCommand(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = emberAfStartSearchForJoinableNetwork();
  emberAfCorePrintln("find joinable: 0x%X", status);
}

void findUnusedPanIdCommand(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = emberAfFindUnusedPanIdAndForm();
  emberAfCorePrintln("find unused: 0x%X", status);
}

void networkChangeChannelCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t channel = sl_cli_get_argument_uint8(arguments, 0);
  EmberStatus status = emberChannelChangeRequest(channel);
  emberAfAppPrintln("Changing to channel %d: 0x%X",
                    channel,
                    status);
}

// is defined to either 1 or 0 as a UC configuration.
#if (EMBER_AF_TC_SWAP_OUT_TEST == 1)
void networkInitCommand(sl_cli_command_arg_t *arguments)
{
  EmberNetworkInitStruct networkInitStruct = {
    EMBER_AF_CUSTOM_NETWORK_INIT_OPTIONS   // EmberNetworkInitBitmask value
  };
  EmberStatus status = emberNetworkInit(&networkInitStruct);
  emberAfAppPrintln("Network Init returned: 0x%X", status);
}
#else
void networkInitCommand(sl_cli_command_arg_t *arguments)
{
}
#endif

void networkSetCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  if (EMBER_SUPPORTED_NETWORKS <= index) {
    emberAfCorePrintln("invalid network index");
    return;
  }
  sli_zigbee_af_cli_network_index = index;
}

void networkIdCommand(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 eui64;
  emberAfGetEui64(eui64);
  emberAfCorePrint("Short ID: 0x%2X, EUI64: ", emberAfGetNodeId());
  emberAfPrintBigEndianEui64(eui64);
  emberAfCorePrintln(", Pan ID: 0x%2X", emberAfGetPanId());
}

void networkMultiPhyStartCommand(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  uint8_t page = sl_cli_get_argument_uint8(arguments, 0);
  uint8_t channel = sl_cli_get_argument_uint8(arguments, 1);
  int8_t power = sl_cli_get_argument_int8(arguments, 2);
  uint8_t optionsMask = 0;

  if (sl_cli_get_argument_count(arguments) > 3) {
    optionsMask = sl_cli_get_argument_uint8(arguments, 3);
  }

  status = emberMultiPhyStart(PHY_INDEX_PRO2PLUS, page, channel, power, optionsMask);

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Started multi-phy interface");
  } else {
    emberAfCorePrintln("Failed to %s %s 0x%X",
                       "start",
                       "multi-phy interface",
                       status);
  }
}

void networkMultiPhyStopCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t status = emberMultiPhyStop(PHY_INDEX_PRO2PLUS);

  if (status == EMBER_SUCCESS) {
    emberAfCorePrintln("Terminated %s 0x%X",
                       "multi-phy interface",
                       status);
  } else {
    emberAfCorePrintln("Failed to %s %s 0x%X",
                       "stop",
                       "multi-phy interface",
                       status);
  }
}

/* ToDo: keep or remove? needed for testing. no ezsp support. */
void changeKeepAliveModeCommand(sl_cli_command_arg_t *arguments)
{
  uint8_t keepAliveMode = sl_cli_get_argument_uint8(arguments, 0);
  if (!emberSetKeepAliveMode(keepAliveMode)) {
    emberAfAppPrintln("Keep alive support enabled.");
  } else {
    emberAfAppPrintln("failed to set keep alive mode.");
  }
}

void networkChangeChildTimeoutOptionMaskCommand(sl_cli_command_arg_t *arguments)
{
  uint16_t mask = sl_cli_get_argument_uint16(arguments, 0);
  if (!emberSetChildTimeoutOptionMask(mask)) {
    emberAfAppPrintln("successfully set the child timeout option mask.");
  } else {
    emberAfAppPrintln("failed to set the child timeout option mask.");
  }
}
