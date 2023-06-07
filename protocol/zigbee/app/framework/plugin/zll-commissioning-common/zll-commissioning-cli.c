/***************************************************************************//**
 * @file
 * @brief CLI for the ZLL Commissioning Common plugin.
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
// TODO: EMZIGBEE-6719
#include "zll-commissioning-common.h"

#ifdef SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_CLIENT_PRESENT
#include "zll-commissioning-client.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_SERVER_PRESENT
#include "zll-commissioning-server.h"
#endif

//---Forward Decleration
void printChannels(sl_cli_command_arg_t *arguments);
static uint32_t channelMasks[] = {
  0x02108800UL, // standard (11, 15, 20, 25)
  0x04211000UL, // +1 (12, 16, 21, 26)
  0x004A2000UL, // +2 (13, 17, 22, 19)
  0x01844000UL, // +3 (14, 18, 23, 24)
  0x07FFF800UL, // all (11--26)
};

// Internal APIs.
extern EmberStatus sli_zigbee_af_zll_form_network(uint8_t channel, int8_t power, EmberPanId panId);
extern EmberZllPolicy sli_zigbee_af_zll_get_policy(void);

// plugin zll-commissioning form <channel:1> <power:1> <pan id:2>
void formNetwork(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = sli_zigbee_af_zll_form_network(sl_cli_get_argument_uint8(arguments, 0),       // channel
                                                      sl_cli_get_argument_uint16(arguments, 1), // power
                                                      (EmberPanId)sl_cli_get_argument_uint16(arguments, 2)); // pan id
  emberAfAppPrintln("%p 0x%x", "form", status);
}

// Leaving intact for legacy CLI purposes, but for generated CLI, the options have been moved to
// scanTouchLink().

// plugin zll-commissioning link [device|identify|reset]
void initiateTouchLink(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT
  EmberStatus status;
  switch (sl_cli_get_argument_count(arguments)) {
    case 0:
      status = emberAfZllInitiateTouchLink();
      emberAfAppPrintln("%p 0x%x", "touch link", status);
      return;
    case 1:
      if (memcmp(arguments->argv[arguments->arg_ofs - 1], "device", strlen("device")) == 0 ) {
        status = emberAfZllDeviceInformationRequest();
        emberAfAppPrintln("%p 0x%x", "device information", status);
        return;
      } else if (memcmp(arguments->argv[arguments->arg_ofs - 1], "identify", strlen("identify")) == 0 ) {
        status = emberAfZllIdentifyRequest();
        emberAfAppPrintln("%p 0x%x", "identify", status);
        return;
      }
      if (memcmp(arguments->argv[arguments->arg_ofs - 1], "reset", strlen("reset")) == 0 ) {
        status = emberAfZllResetToFactoryNewRequest();
        emberAfAppPrintln("%p 0x%x", "reset to factory new", status);
        return;
      }
      // -1 because we're smarter than command-interpreter2.
      // switch (*arguments->argv[arguments->arg_ofs - 1]) {
      //   case 'd':
      //     status = emberAfZllDeviceInformationRequest();
      //     emberAfAppPrintln("%p 0x%x", "device information", status);
      //     return;
      //   case 'i':
      //     status = emberAfZllIdentifyRequest();
      //     emberAfAppPrintln("%p 0x%x", "identify", status);
      //     return;
      //   case 'r':
      //     status = emberAfZllResetToFactoryNewRequest();
      //     emberAfAppPrintln("%p 0x%x", "reset to factory new", status);
      //     return;
      //   default:
      //     return;
      //}
  }
  emberAfAppPrintln("Usage:");
  emberAfAppPrintln("plugin zll-commissioning link");
  emberAfAppPrintln("plugin zll-commissioning link device");
  emberAfAppPrintln("plugin zll-commissioning link identify");
  emberAfAppPrintln("plugin zll-commissioning link reset");
#else
  emberAfAppPrintln("zll commissioning client plugin not found");
#endif
}

// Generated CLI version of "link" commands

// plugin zll-commissioning scan [device|identify|reset]
void scanTouchLink(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT
  EmberStatus status;
  if (memcmp(arguments->argv[arguments->arg_ofs - 1], "device", strlen("device")) == 0 ) {
    status = emberAfZllDeviceInformationRequest();
    emberAfAppPrintln("%p 0x%x", "device information", status);
    return;
  } else if (memcmp(arguments->argv[arguments->arg_ofs - 1], "identify", strlen("identify")) == 0 ) {
    status = emberAfZllIdentifyRequest();
    emberAfAppPrintln("%p 0x%x", "identify", status);
    return;
  }
  if (memcmp(arguments->argv[arguments->arg_ofs - 1], "reset", strlen("reset")) == 0 ) {
    status = emberAfZllResetToFactoryNewRequest();
    emberAfAppPrintln("%p 0x%x", "reset to factory new", status);
    return;
  }
  // switch (*(arguments->argv[arguments->arg_ofs - 1])) {
  //   case 'd':
  //     status = emberAfZllDeviceInformationRequest();
  //     emberAfAppPrintln("%p 0x%x", "device information", status);
  //     return;
  //   case 'i':
  //     status = emberAfZllIdentifyRequest();
  //     emberAfAppPrintln("%p 0x%x", "identify", status);
  //     return;
  //   case 'r':
  //     status = emberAfZllResetToFactoryNewRequest();
  //     emberAfAppPrintln("%p 0x%x", "reset to factory new", status);
  //     return;
  // }
#else
  emberAfAppPrintln("zll commissioning client plugin not found");
#endif
}

// plugin zll-commissioning abort
void abortTouchLink(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT
  emberAfZllAbortTouchLink();
  emberAfAppPrintln("%p", "touch link aborted");
#else
  emberAfAppPrintln("zll commissioning client plugin not found");
#endif
}

// plugin zll-commissioning info <destination:2> <src endpoint:1> <dst endpoint:1>
void endpointInformation(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 eui64;
  EmberStatus status = EMBER_INVALID_ENDPOINT;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  if (index != 0xFF && index < FIXED_ENDPOINT_COUNT) {
    // If the profile interop bit in the ZllInformation bitmask is cleared,
    // then we set the profile ID in our response to the ZLL profile ID.
    // If the bit is set, then we use the profile ID specified for the endpoint.
    uint8_t deviceVersion = emberAfDeviceVersionFromIndex(index);
    EmberTokTypeStackZllData token;
    emberZllGetTokenStackZllData(&token);
    EmberAfProfileId profileId = (token.bitmask & EMBER_ZLL_STATE_PROFILE_INTEROP
                                  ? emberAfProfileIdFromIndex(index)
                                  : EMBER_ZLL_PROFILE_ID);
    emberAfGetEui64(eui64);
    emberAfFillCommandZllCommissioningClusterEndpointInformation(eui64,
                                                                 emberAfGetNodeId(),
                                                                 endpoint,
                                                                 profileId,
                                                                 emberAfDeviceIdFromIndex(index),
                                                                 deviceVersion);
    emberAfSetCommandEndpoints(endpoint,
                               sl_cli_get_argument_uint8(arguments, 2));
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                       sl_cli_get_argument_uint16(arguments, 0));
  }
  emberAfAppPrintln("%p 0x%x", "endpoint information", status);
}

// plugin zll-commissioning groups <destination:2> <src endpoint:1> <dst endpoint:1> <startIndex:1>
void getGroupIdentifiersRequest(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = EMBER_INVALID_ENDPOINT;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  if (index != 0xFF) {
    emberAfFillCommandZllCommissioningClusterGetGroupIdentifiersRequest(sl_cli_get_argument_uint8(arguments, 3));
    emberAfSetCommandEndpoints(endpoint,
                               sl_cli_get_argument_uint8(arguments, 2));
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                       sl_cli_get_argument_uint16(arguments, 0));
  }
  emberAfAppPrintln("%p 0x%x", "get group identifiers", status);
}

// plugin zll-commissioning endpoints <destination:2> <src endpoint:1> <dst endpoint:1> <startIndex:1>
void getEndpointListRequest(sl_cli_command_arg_t *arguments)
{
  EmberStatus status = EMBER_INVALID_ENDPOINT;
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  if (index != 0xFF) {
    emberAfFillCommandZllCommissioningClusterGetEndpointListRequest(sl_cli_get_argument_uint8(arguments, 3));
    emberAfSetCommandEndpoints(endpoint,
                               sl_cli_get_argument_uint8(arguments, 2));
    status = emberAfSendCommandUnicast(EMBER_OUTGOING_DIRECT,
                                       sl_cli_get_argument_uint16(arguments, 0));
  }
  emberAfAppPrintln("%p 0x%x", "get endpoint list", status);
}

// plugin zll-commissioning set-rx-on <duration:4>
void setRxOn(sl_cli_command_arg_t *arguments)
{
  uint32_t duration = (uint32_t)sl_cli_get_argument_uint32(arguments, 0);
  emberZllSetRxOnWhenIdle(duration);
  emberAfAppPrintln("%p %p %d %p", "Rx-On-When-Idle", "set for", duration, "ms");
}

// plugin zll-commissioning cancel-rx-on
void cancelRxOn(sl_cli_command_arg_t *arguments)
{
  emberZllCancelRxOnWhenIdle(); // cancel rx on
  emberAfAppPrintln("%p %p", "Rx-On-When-Idle", "cancelled");
}

// plugin zll-commissioning rx-on-active
void rxOnStatus(sl_cli_command_arg_t *arguments)
{
  bool status = emberZllRxOnWhenIdleGetActive();
  emberAfAppPrintln("%p %p", "Rx-On-When-Idle", status ? "active" : "inactive");
}

void printZllTokens(sl_cli_command_arg_t *arguments)
{
  EmberTokTypeStackZllData token;
  EmberTokTypeStackZllSecurity security;
  emberZllGetTokenStackZllData(&token);
  emberZllGetTokenStackZllSecurity(&security);

  emberAfAppFlush();
  emberAfAppPrintln("ZLL Tokens");
  emberAfAppPrintln("Bitmask: 0x%4x", token.bitmask);
  emberAfAppPrintln("Free Node IDs,  Min: 0x%2x, Max: 0x%2x",
                    token.freeNodeIdMin,
                    token.freeNodeIdMax);
  emberAfAppFlush();
  emberAfAppPrintln("Free Group IDs, Min: 0x%2x, Max: 0x%2x",
                    token.freeGroupIdMin,
                    token.freeGroupIdMax);
  emberAfAppFlush();
  emberAfAppPrintln("My Group ID Min: 0x%2x",
                    token.myGroupIdMin);
  emberAfAppFlush();
  emberAfAppPrintln("RSSI Correction: %d",
                    token.rssiCorrection);
  emberAfAppFlush();

  emberAfAppPrintln("Security Bitmask: 0x%4x", security.bitmask);
  emberAfAppFlush();
  emberAfAppPrintln("Security Key Index: %d", security.keyIndex);
  emberAfAppFlush();
  emberAfAppPrint("Security Encryption Key: ");
  emberAfAppDebugExec(emberAfPrintZigbeeKey(security.encryptionKey));
  emberAfAppPrintln("");
  emberAfAppFlush();
}

void setScanChannel(sl_cli_command_arg_t *arguments)
{
  uint8_t channel = sl_cli_get_argument_uint8(arguments, 0);

  if (channel == 0) {
    emberSetZllPrimaryChannelMask(0);
  } else {
    if (channel > EMBER_MAX_802_15_4_CHANNEL_NUMBER
        || channel < EMBER_MIN_802_15_4_CHANNEL_NUMBER) {
      emberAfAppPrintln("Invalid channel %d", channel);
      return;
    }
    emberSetZllPrimaryChannelMask(1 << channel);

#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_SERVER
    if (emberNetworkState() == EMBER_NO_NETWORK) {
      // If we are not joined, then we also change the default channel.
      emberSetLogicalAndRadioChannel(channel);
      emberAfAppPrintln("Setting default channel to %d", channel);
    }
#endif
  }

  printChannels(arguments);
}

void setSecondaryScanChannel(sl_cli_command_arg_t *arguments)
{
  uint8_t channel = sl_cli_get_argument_uint8(arguments, 0);

  if (channel == 0) {
    emberSetZllSecondaryChannelMask(0);
  } else {
    if (channel > EMBER_MAX_802_15_4_CHANNEL_NUMBER
        || channel < EMBER_MIN_802_15_4_CHANNEL_NUMBER) {
      emberAfAppPrintln("Invalid channel %d", channel);
      return;
    }
    emberSetZllSecondaryChannelMask(1 << channel);
  }
  printChannels(arguments);
}

void setScanMask(sl_cli_command_arg_t *arguments)
{
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  if (COUNTOF(channelMasks) <= index) {
    emberAfAppPrintln("Invalid channel mask index %d", index);
    return;
  }
  emberSetZllPrimaryChannelMask(channelMasks[index]);
  printChannels(arguments);
}

void setIdentifyDuration(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT
  sli_zigbee_af_zll_identify_duration_sec = sl_cli_get_argument_uint16(arguments, 0);
#endif //EMBER_AF_PLUGIN_ZLL_COMMISSIONING_LINK_INITIATOR
}

void statusCommand(sl_cli_command_arg_t *arguments)
{
  printChannels(arguments);
  printZllTokens(arguments);

  // Use the Ember API, not the framework API, for host-side
  emberAfAppPrintln("%p %d", "Current channel:", emberGetRadioChannel());
  emberAfAppPrintln("%p %d", "Touchlinking policy:", sli_zigbee_af_zll_get_policy());
}

void printChannels(sl_cli_command_arg_t *arguments)
{
  emberAfAppPrint("%p channels: ", "Primary");
  emberAfAppDebugExec(emberAfPrintChannelListFromMask(emberGetZllPrimaryChannelMask()));
  emberAfAppPrintln(" (0x%4x)", emberGetZllPrimaryChannelMask());
#if (EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_SCAN_SECONDARY_CHANNELS == 1)
  emberAfAppPrint("%p channels: ", "Secondary");
  emberAfAppDebugExec(emberAfPrintChannelListFromMask(emberGetZllSecondaryChannelMask()));
  emberAfAppPrintln(" (0x%4x)", emberGetZllSecondaryChannelMask());
#endif
}

void joinable(sl_cli_command_arg_t *arguments)
{
#if (defined EMBER_AF_PLUGIN_ZLL_COMMISSIONING_NETWORK) || (defined SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_NETWORK_PRESENT)
  EmberStatus status = emberAfStartSearchForJoinableNetworkCallback();
  emberAfAppPrintln("%p 0x%x", "joinable", status);
#else
  emberAfAppPrintln("zll commissioning network plugin not found");
#endif
}

void unused(sl_cli_command_arg_t *arguments)
{
#if (defined EMBER_AF_PLUGIN_ZLL_COMMISSIONING_NETWORK) || (defined SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_NETWORK_PRESENT)
  EmberStatus status = emberAfFindUnusedPanIdAndFormCallback();
  emberAfAppPrintln("%p 0x%x", "unused", status);
#else
  emberAfAppPrintln("zll commissioning network plugin not found");
#endif
}

void noTouchlinkForNFN(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_SERVER
  emberAfZllNoTouchlinkForNFN();
#else
  emberAfAppPrintln("zll commissioning server plugin not found");
#endif
}

void noResetForNFN(sl_cli_command_arg_t *arguments)
{
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_SERVER
  emberAfZllNoResetForNFN();
#else
  emberAfAppPrintln("zll commissioning server plugin not found");
#endif
}

void enable(sl_cli_command_arg_t *arguments)
{
  emberAfZllEnable();
}

void disable(sl_cli_command_arg_t *arguments)
{
  emberAfZllDisable();
}
