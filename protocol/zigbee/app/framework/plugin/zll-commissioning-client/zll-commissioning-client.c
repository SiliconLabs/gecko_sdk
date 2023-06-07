/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Commissioning Client plugin, which implements the
 *        client side of the ZLL protocol.
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
#include "app/framework/util/common.h"
#include  "mac-phy.h"

#include "sl_signature_decode.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#include "zll-commissioning.h"
#include "zll-commissioning-client-config.h"
#ifdef SL_CATALOG_ZIGBEE_NETWORK_CREATOR_PRESENT
#include "network-creator.h"
#define NETWORK_CREATOR_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
#include "test-harness-z3-zll.h"
#define TEST_HARNESS_Z3_PRESENT
#endif

// The code below assumes that there is exactly one network and that it is
// ZigBee PRO.
#if EMBER_SUPPORTED_NETWORKS != 1
  #error ZLL is not supported with multiple networks.
#endif

//------------------------------------------------------------------------------
// Globals

#define ZLL_DEVICE_INFORMATION_RECORD_SIZE 16

#define isRequestingPriority(state) ((state) & EMBER_ZLL_STATE_LINK_PRIORITY_REQUEST)

static bool radioOnForRequestOnly = false;

sl_zigbee_event_t sli_zigbee_af_zll_commissioning_client_touch_link_event;
#define touchLinkEvent &sli_zigbee_af_zll_commissioning_client_touch_link_event

static uint8_t currentChannel;
static int8_t rssi;

uint16_t sli_zigbee_af_zll_identify_duration_sec = EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_IDENTIFY_DURATION;

#ifdef PLUGIN_DEBUG
static const uint8_t sli_zigbee_af_zll_commissioning_plugin_name[] = "ZLL Commissioning Client";
#define PLUGIN_NAME sli_zigbee_af_zll_commissioning_plugin_name
#endif

static bool scanningPrimaryChannels = false;

// Module state
static enum {
  CLIENT_INITIAL,
  CLIENT_SCANNING,
  CLIENT_REQUESTING_INFO,
  CLIENT_AWAITING_RESPONSE,
  CLIENT_REQUESTING_IDENTITY,
  CLIENT_TOUCHLINKING,
} moduleState = CLIENT_INITIAL;

static uint8_t nextSubDeviceIndex = 0;

#ifdef EMBER_TEST
// Limit this delay for scripted tests, to prevent the transaction timing out,
// especially for a host side test.
  #define EMBER_AF_PLUGIN_ZLL_COMMISSIONING_TOUCH_LINK_MILLISECONDS_DELAY 2500
#else
  #define EMBER_AF_PLUGIN_ZLL_COMMISSIONING_TOUCH_LINK_MILLISECONDS_DELAY \
  (EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_TOUCH_LINK_SECONDS_DELAY * MILLISECOND_TICKS_PER_SECOND)
#endif

#define JOIN_RESPONSE_TIMEOUT_QS 20

// Parameters for Network Creator callbacks - note, for a client, we use the
// radio power defined for this plugin, not the power defined for the Network
// Creator plugin, in order that both client and server use the same power.
static EmberPanId networkCreatorPanId = 0xFFFF;
static int8_t networkCreatorRadioPower = EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER;

// Note, currently we set a random extended PAN ID for both client and server created
// networks during standard touchlink commissioning (even if the client wants otherwise.)

// Private ZLL commissioning functions
bool sli_zigbee_af_zll_am_factory_new(void);
EmberNodeType sli_zigbee_af_zll_get_logical_node_type(void);
void sli_zigbee_af_zll_touch_link_complete(void);

// Forward references
void sli_zigbee_af_zll_abort_touch_link(EmberAfZllCommissioningStatus reason);

//------------------------------------------------------------------------------
// Module private functions

static uint32_t getChannelMask(void)
{
  uint32_t channelMask = 0;
  if (scanningPrimaryChannels) {
    channelMask = emberGetZllPrimaryChannelMask();
#ifdef SCAN_SECONDARY_CHANNELS
  } else {
    channelMask = emberGetZllSecondaryChannelMask();
#endif
  }
  debugPrintln("getChannelMask: mask = %4X, scanningPrimary = %d", channelMask, scanningPrimaryChannels);
  return channelMask;
}

static EmberStatus sendDeviceInformationRequest(uint8_t startIndex)
{
  EmberStatus status;
  (void) emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                    | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                    | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                   ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                   ZCL_DEVICE_INFORMATION_REQUEST_COMMAND_ID,
                                   "wu",
                                   sli_zigbee_af_zll_network.securityAlgorithm.transactionId,
                                   startIndex);
  status = emberAfSendCommandInterPan(0xFFFF,                // destination pan id
                                      sli_zigbee_af_zll_network.eui64,
                                      EMBER_NULL_NODE_ID,    // node id - ignored
                                      0x0000,                // group id - ignored
                                      EMBER_ZLL_PROFILE_ID);
  if (status == EMBER_SUCCESS) {
    moduleState = CLIENT_AWAITING_RESPONSE;
    sl_zigbee_event_set_delay_ms(touchLinkEvent,
                                 EMBER_AF_PLUGIN_ZLL_COMMISSIONING_TOUCH_LINK_MILLISECONDS_DELAY);
  } else {
    emberAfAppPrintln("%p%p failed 0x%x",
                      "Error: ",
                      "Device information request",
                      status);
  }
  return status;
}

static EmberStatus sendIdentifyRequest(uint16_t identifyDuration)
{
  EmberStatus status;
  (void) emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                    | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                    | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                   ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                   ZCL_IDENTIFY_REQUEST_COMMAND_ID,
                                   "wv",
                                   sli_zigbee_af_zll_network.securityAlgorithm.transactionId,
                                   identifyDuration);
  status = emberAfSendCommandInterPan(0xFFFF,                // destination pan id
                                      sli_zigbee_af_zll_network.eui64,
                                      EMBER_NULL_NODE_ID,    // node id - ignored
                                      0x0000,                // group id - ignored
                                      EMBER_ZLL_PROFILE_ID);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p%p failed 0x%x",
                      "Error: ",
                      "Identify request",
                      status);
  }
  return status;
}

static EmberStatus sendResetToFactoryNewRequest(void)
{
  EmberStatus status;
  (void) emberAfFillExternalBuffer((ZCL_CLUSTER_SPECIFIC_COMMAND
                                    | ZCL_FRAME_CONTROL_CLIENT_TO_SERVER
                                    | ZCL_DISABLE_DEFAULT_RESPONSE_MASK),
                                   ZCL_ZLL_COMMISSIONING_CLUSTER_ID,
                                   ZCL_RESET_TO_FACTORY_NEW_REQUEST_COMMAND_ID,
                                   "w",
                                   sli_zigbee_af_zll_network.securityAlgorithm.transactionId);
  status = emberAfSendCommandInterPan(0xFFFF,                // destination pan id
                                      sli_zigbee_af_zll_network.eui64,
                                      EMBER_NULL_NODE_ID,    // node id - ignored
                                      0x0000,                // group id - ignored
                                      EMBER_ZLL_PROFILE_ID);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p%p failed 0x%x",
                      "Error: ",
                      "Reset to factory new request",
                      status);
  }
  return status;
}

static const sl_signature_t sl_zll_device_info_record_signature = {
  6,
  SL_SIGNATURE_FIELD_MASK_BLOB | EUI64_SIZE, offsetof(EmberZllDeviceInfoRecord, ieeeAddress),
  SL_SIGNATURE_FIELD_1_BYTE, offsetof(EmberZllDeviceInfoRecord, endpointId),
  SL_SIGNATURE_FIELD_2_BYTES, offsetof(EmberZllDeviceInfoRecord, profileId),
  SL_SIGNATURE_FIELD_2_BYTES, offsetof(EmberZllDeviceInfoRecord, deviceId),
  SL_SIGNATURE_FIELD_1_BYTE, offsetof(EmberZllDeviceInfoRecord, version),
  SL_SIGNATURE_FIELD_1_BYTE, offsetof(EmberZllDeviceInfoRecord, groupIdCount),
};
static void deviceInformationResponseHandler(const EmberEUI64 source,
                                             uint32_t transaction,
                                             uint8_t numberOfSubDevices,
                                             uint8_t startIndex,
                                             uint8_t deviceInformationRecordCount,
                                             uint8_t *deviceInformationRecordList)
{
  sl_zigbee_event_set_inactive(touchLinkEvent);

  uint16_t deviceInformationRecordListLen = (deviceInformationRecordCount
                                             * ZLL_DEVICE_INFORMATION_RECORD_SIZE);
  uint8_t i;
  bool validResponse = ((sli_zigbee_af_zll_network.securityAlgorithm.transactionId == transaction)
                        && MEMCOMPARE(sli_zigbee_af_zll_network.eui64, source, EUI64_SIZE) == 0);

  emberAfZllCommissioningClusterFlush();
  emberAfZllCommissioningClusterPrint("RX: DeviceInformationResponse 0x%4x, 0x%x, 0x%x, 0x%x,",
                                      transaction,
                                      numberOfSubDevices,
                                      startIndex,
                                      deviceInformationRecordCount);
  emberAfZllCommissioningClusterFlush();
  for (i = 0; i < deviceInformationRecordCount; i++) {
    EmberZllDeviceInfoRecord tempDeviceInfoRecord;
    uint8_t sort;
    sl_signature_decode(deviceInformationRecordList,
                        deviceInformationRecordListLen,
                        i * (8 + EUI64_SIZE),
                        sl_zll_device_info_record_signature,
                        (uint8_t*)&tempDeviceInfoRecord);
    sort = emberAfGetInt8u(deviceInformationRecordList, (i + 1) * (8 + EUI64_SIZE) - 1, deviceInformationRecordListLen);
    emberAfZllCommissioningClusterPrint(" [");
    emberAfZllCommissioningClusterDebugExec(emberAfPrintBigEndianEui64(tempDeviceInfoRecord.ieeeAddress));
    emberAfZllCommissioningClusterPrint(" 0x%x 0x%2x 0x%2x 0x%x 0x%x 0x%x",
                                        tempDeviceInfoRecord.endpointId,
                                        tempDeviceInfoRecord.profileId,
                                        tempDeviceInfoRecord.deviceId,
                                        tempDeviceInfoRecord.version,
                                        tempDeviceInfoRecord.groupIdCount,
                                        sort);
    emberAfZllCommissioningClusterFlush();

    if (validResponse
        && (sli_zigbee_af_zll_sub_device_count
            < EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_SUB_DEVICE_TABLE_SIZE)) {
      memcpy(&(sli_zigbee_af_zll_sub_devices[sli_zigbee_af_zll_sub_device_count]), &tempDeviceInfoRecord, sizeof(EmberZllDeviceInfoRecord));
      sli_zigbee_af_zll_sub_device_count++;
    } else {
      emberAfZllCommissioningClusterPrint(" (ignored)");
    }
    emberAfZllCommissioningClusterPrint("]");
    emberAfZllCommissioningClusterFlush();
  }
  emberAfZllCommissioningClusterPrintln("");

  if (validResponse
      && (sli_zigbee_af_zll_sub_device_count
          < EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_SUB_DEVICE_TABLE_SIZE)
      && sli_zigbee_af_zll_sub_device_count < numberOfSubDevices) {
    nextSubDeviceIndex = startIndex + deviceInformationRecordCount;
    moduleState = CLIENT_REQUESTING_INFO;
  } else {
    moduleState = CLIENT_REQUESTING_IDENTITY;

    if (radioOnForRequestOnly) {
      emberZllSetRadioIdleMode(EMBER_RADIO_POWER_MODE_OFF);
      radioOnForRequestOnly = false;
    }
  }
  sl_zigbee_event_set_active(touchLinkEvent);
}

static bool amInitiator(void)
{
  EmberTokTypeStackZllData token;
  emberZllGetTokenStackZllData(&token);
  return token.bitmask & EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE;
}

static EmberStatus startScan(uint8_t purpose)
{
  EmberStatus status = EMBER_INVALID_CALL;
  if (touchLinkInProgress()) {
    emberAfAppPrintln("%pTouch linking in progress", "Error: ");
  } else if (!amInitiator()) {
    emberAfAppPrintln("%pDevice is not an initiator", "Error: ");
  } else {
    emberAfZllSetInitialSecurityState();

    // Use the Ember API, not the framework API, otherwise host-side returns zero if network down
    currentChannel = emberGetRadioChannel();
    debugPrintln("startScan: purpose = %X, flags = %2X, current channel = %d", purpose, sli_zigbee_af_zll_flags, currentChannel);

    scanningPrimaryChannels = true;
    uint32_t channelMask = getChannelMask();
    if (channelMask == 0) {
      // If there are no primary channels, then get the secondary mask.
      scanningPrimaryChannels = false;
      channelMask = getChannelMask();
    }

    if (channelMask != 0) {
      status = emberZllStartScan(channelMask,
                                 EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_SCAN_POWER_LEVEL,
                                 sli_zigbee_af_zll_get_logical_node_type());
      if (status == EMBER_SUCCESS) {
        sli_zigbee_af_zll_flags = purpose;
        moduleState = CLIENT_SCANNING;
      } else {
        emberAfAppPrintln("%p%p%p0x%x",
                          "Error: ",
                          "Touch linking failed: ",
                          "could not start scan: ",
                          status);
      }
    } else {
      emberAfAppPrintln("%p%p0x%x",
                        "Error: ",
                        "Touch linking failed: ",
                        "no scan channels configured");
    }
  }
  return status;
}

static bool isSameNetwork(const EmberZllNetwork *network)
{
  EmberNodeType nodeType;
  EmberNetworkParameters parameters;
  EmberStatus status = emberAfGetNetworkParameters(&nodeType, &parameters);

  // Note, we only check the Extended Pan Id, not the Short Pan Id, nor the
  // Network Update Id.
  return (status == EMBER_SUCCESS
          && (MEMCOMPARE(parameters.extendedPanId,
                         network->zigbeeNetwork.extendedPanId,
                         EXTENDED_PAN_ID_SIZE) == 0));
}

static bool isTouchlinkPermitted(const EmberZllNetwork *networkInfo)
{
  // Basic checks for a Z3.0 touchlink initiator.
  if (networkInfo->nodeType == EMBER_UNKNOWN_DEVICE) {
    // The target must be a known device type.
    debugPrintln("isTouchlinkPermitted: Error - Target is unknown node type %d", networkInfo->nodeType);
    return false;
  }

  // Get current run-time network status. (Note that emberGetNodeType() may
  // report an actual node type even if a previous touchlink failed, e.g.
  // if the initiator was orphaned and was unable to rejoin)
  EmberNetworkStatus networkStatus = emberNetworkState();
  EmberCurrentSecurityState securityState;
  bool networkUp;

  if (networkStatus == EMBER_JOINED_NETWORK
      || networkStatus == EMBER_JOINED_NETWORK_NO_PARENT) {
    networkUp = true;
    if (emberGetCurrentSecurityState(&securityState) != EMBER_SUCCESS) {
      // It is possible that we're orphaned but attempting to rejoin here, but we'll
      // fail the touchlink anyway, since it would probably collide with the rejoining
      // procedure. (emberGetCurrentSecurityState() fails if we are rejoining even
      // though emberNetworkState() reports EMBER_JOINED_NETWORK_NO_PARENT)
      debugPrintln("emberGetCurrentSecurityState failure");
      return false;
    } else {
      // We're either joined or orphaned and not attempting to rejoin; in
      // either case we can proceed with the next stage of validation.
      debugPrintln("isTouchlinkPermitted: security bitmask = %2X,flags = %2X",
                   securityState.bitmask, sli_zigbee_af_zll_flags);
    }
  } else {
    networkUp = false;
    debugPrintln("isTouchlinkPermitted: initiator is not joined");
  }

  if (scanForReset() || scanForTouchLink()) {
    // When scanning for touch linking or reset, the initiator need not be
    // on a network, but if it is, then it may not be on a different centralized
    // network, unless the (non-compliant) centralized network support is enabled.
    if (networkUp
        && (securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE) == 0
        && !isSameNetwork(networkInfo)) {
      debugPrintln("isTouchlinkPermitted: Error - Initiator on centralized network");
      return false;
    }
  }

  if (scanForTouchLink() && !networkUp) {
    // When scanning for touch linking, and if the initiator is not on a network,
    // either initiator or target must be able to form a network. If centralized
    // network touchlink initiating is supported, the initiating device must
    // be coordinator-capable.
    if (sli_zigbee_af_zll_get_logical_node_type() != EMBER_ROUTER && networkInfo->nodeType != EMBER_ROUTER) {
      debugPrintln("isTouchlinkPermitted: Error - Neither end can form a network");
      debugPrintln("our type = %d, their type = %d", sli_zigbee_af_zll_get_logical_node_type(), networkInfo->nodeType);
      return false;
    }
  }
  return true;
}

// Returns an integer greater than, equal to, or less than zero, according to
// whether target t1 is better than, equal to, or worse than target t2 in terms
// of requested priority with corrected signal strength serving as tiebreaker.
static int8_t targetCompare(const EmberZllNetwork *t1,
                            int8_t r1,
                            const EmberZllNetwork *t2,
                            int8_t r2)
{
  // When considering two targets, if only one has requested priority, that one
  // is chosen.
  if (isRequestingPriority(t1->state)
      && !isRequestingPriority(t2->state)) {
    return 1;
  } else if (!isRequestingPriority(t1->state)
             && isRequestingPriority(t2->state)) {
    return -1;
  }

  // If the priority of both targets is the same, the correct signal strength
  // is considered.  The strongest corrected signal wins.
  emberAfDebugPrintln("Signal strengths: r1 = %d, t1->corr = %d, r2 = %d, t2->corr = %d",
                      r1, t1->rssiCorrection, r2, t2->rssiCorrection);
  if (r1 + t1->rssiCorrection < r2 + t2->rssiCorrection) {
    return -1;
  } else if (r2 + t2->rssiCorrection < r1 + t1->rssiCorrection) {
    return 1;
  }

  // If we got here, both targets are considered equal.
  return 0;
}

static void processScanComplete(EmberStatus scanStatus)
{
  EmberStatus status;
  debugPrintln("processScanComplete - status = %X", scanStatus);

  if (scanStatus != EMBER_SUCCESS) {
    emberAfAppPrintln("%p%p0x%x",
                      "Error: ",
                      "Touch linking failed due to preemption: ",
                      scanStatus);

    // Factory new initiator preempted by an NFN initiator.
    sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_PREEMPTED_BY_STACK);

    if (emberZllGetRadioIdleMode() == EMBER_RADIO_POWER_MODE_OFF) {
      // Start a short rx-on period to cover an incoming network request.
      emberZllSetRxOnWhenIdle(JOIN_RESPONSE_TIMEOUT_QS * 250 * 2);
    }
  } else if (abortingTouchLink()) {
    debugPrintln("processScanComplete: aborted by application");
    sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_ABORTED_BY_APPLICATION);
  }

  if (touchLinkInProgress()) {
#ifdef SCAN_SECONDARY_CHANNELS
    if (scanningPrimaryChannels) {
      scanningPrimaryChannels = false;
      uint32_t channelMask = getChannelMask();
      if (channelMask != 0) {
        status = emberZllStartScan(channelMask,
                                   EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_SCAN_POWER_LEVEL,
                                   sli_zigbee_af_zll_get_logical_node_type());
        if (status == EMBER_SUCCESS) {
          // We will continue on the second scan complete callback.
          return;
        }
        emberAfAppPrintln("%p%p0x%x",
                          "Error: ",
                          "could not start secondary channel scan: ",
                          status);
      }
      debugPrintln("processScanComplete: no secondary channels, dropping thru");
    }
#endif // SCAN_SECONDARY_CHANNELS
    sli_zigbee_af_zll_flags |= SCAN_COMPLETE;

    // Inform the API that scanning is complete for this transaction.
    emberZllScanningComplete();

    if (targetNetworkFound()) {
      status = emberSetLogicalAndRadioChannel(sli_zigbee_af_zll_network.zigbeeNetwork.channel);
      if (status != EMBER_SUCCESS) {
        emberAfAppPrintln("%p%p%p0x%x",
                          "Error: ",
                          "Touch linking failed: ",
                          "could not change channel: ",
                          status);
        sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_CHANNEL_CHANGE_FAILED);
        return;
      }

      // When scanning for the purposes of touch linking or requesting device
      // information and the target has more than one sub device, turn the
      // receiver on (so we can actually receive the response) and send out the
      // first request.  If the target only has one sub device, its data will
      // have already been received in the ScanRequest.
      if ((scanForTouchLink() || scanForDeviceInformation())
          && sli_zigbee_af_zll_network.numberSubDevices != 1) {
        debugPrintln("processScanComplete: sending first device info request");

        // Turn receiver on if it is currently off so we can receive
        // the Device Info Response.
        if (emberZllGetRadioIdleMode() == EMBER_RADIO_POWER_MODE_OFF) {
          if (sli_zigbee_af_zll_am_factory_new()) {
            // If we're factory new, start a short rx-on period to cover the request.
            emberZllSetRxOnWhenIdle(JOIN_RESPONSE_TIMEOUT_QS * 250);
          } else {
            // We're joined as a sleepy end-device - rx-on may be active and
            // suspended, or expired, or never started in the first place.
            emberZllSetRadioIdleMode(EMBER_RADIO_POWER_MODE_RX_ON);
            radioOnForRequestOnly = true;
          }
        }
        nextSubDeviceIndex = 0;
        moduleState = CLIENT_REQUESTING_INFO;
      } else {
        moduleState = CLIENT_REQUESTING_IDENTITY;
      }
      sl_zigbee_event_set_active(touchLinkEvent);
    } else {
      emberAfAppPrintln("%p%p%p",
                        "Error: ",
                        "Touch linking failed: ",
                        "no networks were found");
      sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_NO_NETWORKS_FOUND);
    }
  } else {
    debugPrintln("processScanComplete: no touchlink in progress");
  }
}

//------------------------------------------------------------------------------
// ZLL commissioning private functions

void sli_zigbee_af_zll_abort_touch_link(EmberAfZllCommissioningStatus reason)
{
  sli_zigbee_af_zll_flags = INITIAL;
  moduleState = CLIENT_INITIAL;
  debugPrintln("sli_zigbee_af_zll_abort_touch_link: reason = %d", reason);
  if (sl_zigbee_event_is_scheduled(touchLinkEvent)) {
    sl_zigbee_event_set_inactive(touchLinkEvent);
    if (radioOnForRequestOnly) {
      emberZllSetRadioIdleMode(EMBER_RADIO_POWER_MODE_OFF);
      radioOnForRequestOnly = false;
    }
    sendIdentifyRequest(0x0000); // exit identify mode
  }
  EmberStatus status;
  if (emberNetworkState() == EMBER_JOINED_NETWORK
      || emberNetworkState() == EMBER_JOINED_NETWORK_NO_PARENT) {
    status = emberSetRadioChannel(currentChannel);
  } else {
    status = emberSetLogicalAndRadioChannel(currentChannel);
  }
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p0x%x%p%d",
                      "Error: ",
                      status,
                      " - could not restore channel to: ",
                      currentChannel);
  }
  if (reason == EMBER_AF_ZLL_NETWORK_UPDATE_OPERATION) {
    sli_zigbee_af_zll_touch_link_complete();
  } else {
    emberAfPluginZllCommissioningTouchLinkFailedCallback(reason);
  }

  // Inform the API that scanning is complete for this transaction.
  emberZllScanningComplete();
}

#ifdef NETWORK_CREATOR_PRESENT
void sli_zigbee_af_zll_finish_network_formation_for_router(EmberStatus status)
{
  if (status == EMBER_NETWORK_UP) {
    // Make ourselves not factory new, and reset the ZLL address and group space
    // we are using node id 0x0001 ourselves.
    EmberTokTypeStackZllData token;
    emberZllGetTokenStackZllData(&token);
    token.bitmask &= ~EMBER_ZLL_STATE_FACTORY_NEW;
    token.freeNodeIdMin = EMBER_ZLL_MIN_NODE_ID + 1;  // start with 0x0002
    token.freeNodeIdMax = EMBER_ZLL_MAX_NODE_ID;
    token.myGroupIdMin = (EMBER_ZLL_GROUP_ADDRESSES == 0
                          ? EMBER_ZLL_NULL_GROUP_ID
                          : EMBER_ZLL_MIN_GROUP_ID);
    token.freeGroupIdMin = EMBER_ZLL_MIN_GROUP_ID + EMBER_ZLL_GROUP_ADDRESSES;
    token.freeGroupIdMax = EMBER_ZLL_MAX_GROUP_ID;
    emberZllSetTokenStackZllData(&token);

    if (touchLinkInProgress()) {
      // Save the new channel.
      // (Use the Ember API, not the framework API, otherwise host-side returns zero if network down)
      currentChannel = emberGetRadioChannel();

      // Switch back to the target's current channel to send the network request,
      // in case we formed on a different one.
      emberSetLogicalAndRadioChannel(sli_zigbee_af_zll_network.zigbeeNetwork.channel);

      // Set the target's new channel to our current channel.
      sli_zigbee_af_zll_network.zigbeeNetwork.channel = currentChannel;

      debugPrintln("Zll Comm stack status: our chan = %d, target chan = %d", currentChannel, sli_zigbee_af_zll_network.zigbeeNetwork.channel);

      // Kick the client touchlinking event.
#ifdef EMBER_TEST
      // Short delay to prevent beacon collision.
      sl_zigbee_event_set_delay_ms(touchLinkEvent, 100);
#else
      sl_zigbee_event_set_active(touchLinkEvent);
#endif // EMBER_TEST
    }
  } else if (touchLinkInProgress()) {
    emberAfAppPrintln("%p%p%p0x%x",
                      "Error: ",
                      "Touch linking failed: ",
                      "could not form network: ",
                      status);
    sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_NETWORK_FORMATION_FAILED);
  }
  sli_zigbee_af_zll_flags &= ~FORMING_NETWORK;
}

extern uint32_t sli_zigbee_af_network_creator_primary_channel_mask;
extern uint32_t sli_zigbee_af_network_creator_secondary_channel_mask;
EmberStatus sli_zigbee_af_zll_form_networkForRouterInitiator(uint8_t channel, int8_t radioPower, EmberPanId panId)
{
  EmberStatus status;

  // Initialize ZLL security.
  status = emberAfZllSetInitialSecurityState();
  if (status != EMBER_SUCCESS) {
    debugPrintln("sli_zigbee_af_zll_form_networkForRouterInitiator: unable to initialize security, status = %X", status);
    return status;
  }

  // Form network with a random extended PAN ID, if no channel is specified, otherwise
  // assume the caller has set the extended PAN ID. (The sli_zigbee_af_extended_pan_id value
  // is global to the framework and used in the network-creator plugin.)
  if (channel == 0) {
    MEMSET(sli_zigbee_af_extended_pan_id, 0xFF, EXTENDED_PAN_ID_SIZE);
  }

  // Per the BDB spec, we scan on the ZLL primary channels, unless a channel
  // has been specified (e.g. for a 'plugin test-harness z3 start-as-router')
  sli_zigbee_af_network_creator_primary_channel_mask = channel ? (uint32_t) (1 << channel) : emberGetZllPrimaryChannelMask();
  sli_zigbee_af_network_creator_secondary_channel_mask = 0;

  // Set node id for emberFormNetwork, to override random id generation.
  emberSetNodeId(EMBER_ZLL_MIN_NODE_ID);  // our node id = 0x0001

  // Set the radio transmit power and PAN id for the Network Creator callbacks.
  networkCreatorRadioPower = radioPower;
  networkCreatorPanId = panId;

  debugPrintln("sli_zigbee_af_zll_form_networkForRouterInitiator: chan mask = %4X", sli_zigbee_af_network_creator_primary_channel_mask);

  status = emberAfPluginNetworkCreatorStart(false); // distributed network

  if (status == EMBER_SUCCESS) {
    sli_zigbee_af_zll_flags |= FORMING_NETWORK;
  }
  return status;
}
#endif // NETWORK_CREATOR_PRESENT

// This function is required to support the following CLI commands:
//   plugin test-harness z3 set-pan-id
//   plugin test-harness z3 start-as-router
void sli_zigbee_af_zll_set_pan_id(EmberPanId panId)
{
  networkCreatorPanId = panId;
}

bool sli_zigbee_af_zll_commissioning_client_interpan_pre_message_received_callback(const EmberAfInterpanHeader *header,
                                                                                   uint8_t msgLen,
                                                                                   uint8_t *message)
{
  uint32_t transaction;
  uint8_t frameControl, commandId, msgIndex;

  // If the message isn't for the ZLL Commissioning cluster, drop it with an
  // indication that we didn't handle it.
  if (header->profileId != EMBER_ZLL_PROFILE_ID
      || header->clusterId != ZCL_ZLL_COMMISSIONING_CLUSTER_ID) {
    return false;
  }

  if (header->messageType != EMBER_AF_INTER_PAN_UNICAST
      || !(header->options & EMBER_AF_INTERPAN_OPTION_MAC_HAS_LONG_ADDRESS)
      || msgLen < ZLL_HEADER_OVERHEAD) {
    return false;
  }

  // Verify that the frame control byte makes sense.  Accept only the legacy
  // format or simple client-to-server or server-to-client messages (i.e., no
  // manufacturer-specific commands, etc.)  For non-legacy messages, check that
  // the frame control is correct for the command.  The check is based on
  // DeviceInformationResponse because it is the only server-to-client command
  // we care about.
  frameControl = message[ZLL_HEADER_FRAME_CONTROL_OFFSET];
  commandId = message[ZLL_HEADER_COMMAND_ID_OFFSET];
  if (frameControl != ZLL_FRAME_CONTROL_LEGACY
      && frameControl != ZLL_FRAME_CONTROL_SERVER_TO_CLIENT) {
    return false;
  }

  msgIndex = ZLL_HEADER_TRANSACTION_ID_OFFSET;
  transaction = emberAfGetInt32u(message, msgIndex, msgLen);
  msgIndex += 4;

  if (commandId == ZCL_DEVICE_INFORMATION_RESPONSE_COMMAND_ID) {
    if (msgIndex + 3 <= msgLen) {
      uint8_t numberOfSubDevices, startIndex, deviceInformationRecordCount;
      numberOfSubDevices = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      startIndex = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      deviceInformationRecordCount = emberAfGetInt8u(message, msgIndex, msgLen);
      msgIndex++;
      if ((msgIndex
           + deviceInformationRecordCount * ZLL_DEVICE_INFORMATION_RECORD_SIZE)
          <= msgLen) {
        uint8_t *deviceInformationRecordList = message + msgIndex;
        deviceInformationResponseHandler(header->longAddress,
                                         transaction,
                                         numberOfSubDevices,
                                         startIndex,
                                         deviceInformationRecordCount,
                                         deviceInformationRecordList);
      }
    }
    return true;
  }

  // Return false for unhandled messages, since we are multiplexing the pre-message handler.
  return false;
}

//------------------------------------------------------------------------------
// Public functions

EmberStatus emberAfZllInitiateTouchLink(void)
{
  return startScan(SCAN_FOR_TOUCH_LINK);
}

EmberStatus emberAfZllDeviceInformationRequest(void)
{
  return startScan(SCAN_FOR_DEVICE_INFORMATION);
}

EmberStatus emberAfZllIdentifyRequest(void)
{
  return startScan(SCAN_FOR_IDENTIFY);
}

EmberStatus emberAfZllResetToFactoryNewRequest(void)
{
  return startScan(SCAN_FOR_RESET);
}

void emberAfZllAbortTouchLink(void)
{
  if (touchLinkInProgress()) {
    // If the scanning portion of touch linking is already finished, we can
    // abort right away.  If not, we need to stop the scan and wait for the
    // stack to inform us when the scan is done.
    emberAfAppPrintln("%p%p%p",
                      "Error: ",
                      "Touch linking failed: ",
                      "aborted by application");
    if (scanComplete()) {
      sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_ABORTED_BY_APPLICATION);
    } else {
      sli_zigbee_af_zll_flags |= ABORTING_TOUCH_LINK;
      emberStopScan();
    }
  }
}

#ifdef EZSP_HOST
void sli_zigbee_af_zll_network_found_callback(EmberZllNetwork *networkInfo,
                                              bool isDeviceInfoNull,
                                              EmberZllDeviceInfoRecord *deviceInfo,
                                              uint8_t lastHopLqi,
                                              int8_t lastHopRssi)
{
  debugPrintln("ezspZllNwkFound: node type = %d, flags = %0x2X", networkInfo->nodeType, sli_zigbee_af_zll_flags);
  if (touchLinkInProgress()) {
    if (isTouchlinkPermitted(networkInfo)) {
      if (!targetNetworkFound()
          || 0 < targetCompare(networkInfo, lastHopRssi, &sli_zigbee_af_zll_network, rssi)) {
        MEMMOVE(&sli_zigbee_af_zll_network, networkInfo, sizeof(EmberZllNetwork));
        sli_zigbee_af_zll_sub_device_count = 0;
        if (!isDeviceInfoNull) {
          MEMMOVE(&sli_zigbee_af_zll_sub_devices[0], deviceInfo, sizeof(EmberZllDeviceInfoRecord));
          sli_zigbee_af_zll_sub_device_count++;
        }
        rssi = lastHopRssi;
        sli_zigbee_af_zll_flags |= TARGET_NETWORK_FOUND;
      }
    } else {
      debugPrintln("ezspZllNwkFound: touchlink is not permitted");
    }
  }
}

#else // !EZSP_HOST

void sli_zigbee_af_zll_network_found_callback(const EmberZllNetwork *networkInfo,
                                              const EmberZllDeviceInfoRecord *deviceInfo)
{
  debugPrintln("emberZllNwkFound: chan = %d, node type = %d, flags = %02X", networkInfo->zigbeeNetwork.channel, networkInfo->nodeType, sli_zigbee_af_zll_flags);
  if (touchLinkInProgress()) {
    if (isTouchlinkPermitted(networkInfo)) {
      int8_t lastHopRssi;
      emberGetLastHopRssi(&lastHopRssi);
      if (!targetNetworkFound()
          || 0 < targetCompare(networkInfo, lastHopRssi, &sli_zigbee_af_zll_network, rssi)) {
        MEMMOVE(&sli_zigbee_af_zll_network, networkInfo, sizeof(EmberZllNetwork));
        sli_zigbee_af_zll_sub_device_count = 0;
        if (deviceInfo != NULL) {
          MEMMOVE(&sli_zigbee_af_zll_sub_devices[0], deviceInfo, sizeof(EmberZllDeviceInfoRecord));
          sli_zigbee_af_zll_sub_device_count++;
        }
        rssi = lastHopRssi;
        sli_zigbee_af_zll_flags |= TARGET_NETWORK_FOUND;
      }
    } else {
      debugPrintln("emberZllNwkFound: touchlink is not permitted");
    }
  }

#ifdef TEST_HARNESS_Z3_PRESENT
  sli_zigbee_af_test_harness_z3_zll_network_found_callback(networkInfo);
#endif
}
#endif // EZSP_HOST

void sli_zigbee_af_zll_scan_complete_callback(EmberStatus scanStatus)
{
  debugPrintln("%p: scan complete", PLUGIN_NAME);
  processScanComplete(scanStatus);

#ifdef TEST_HARNESS_Z3_PRESENT
  sli_zigbee_af_test_harness_z3_zll_scan_complete_callback(scanStatus);
#endif
}

#ifdef EZSP_HOST

void sli_zigbee_af_zll_address_assignment_callback(EmberZllAddressAssignment *addressInfo,
                                                   uint8_t lastHopLqi,
                                                   int8_t lastHopRssi)
{
  if (touchLinkInProgress()) {
    sli_zigbee_af_zll_network.nodeId = addressInfo->nodeId;
  }
}

#else // !EZSP_HOST

void sli_zigbee_af_zll_address_assignment_callback(const EmberZllAddressAssignment *addressInfo)
{
  if (touchLinkInProgress()) {
    debugPrintln("emberZllAddressAssignmentHandler: node id = %2X", addressInfo->nodeId);
    sli_zigbee_af_zll_network.nodeId = addressInfo->nodeId;
  }
}
#endif // EZSP_HOST

void emberAfPluginZllCommissioningClientTouchLinkEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status = EMBER_SUCCESS;
  sl_zigbee_event_set_inactive(touchLinkEvent);
  debugPrintln("TouchlinkEventHandler: flags = %X", sli_zigbee_af_zll_flags);

  if (!touchLinkInProgress()) {
    return;
  }

  switch (moduleState) {
    case CLIENT_REQUESTING_INFO:
      debugPrintln("EH: Sending device info request");
      status = sendDeviceInformationRequest(nextSubDeviceIndex);
      if (status != EMBER_SUCCESS) {
        emberAfAppPrintln("%p%p%p0x%x",
                          "Error: ",
                          "Touch linking failed: ",
                          "could not send device information request: ",
                          status);
        sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_SENDING_DEVICE_INFORMATION_REQUEST_FAILED);
      }
      break;

    case CLIENT_AWAITING_RESPONSE:
      // Timeout - give up.
      emberAfAppPrintln("%p%p%p0x%x",
                        "Error: ",
                        "Touch linking failed: ",
                        "no reply to device information request: ",
                        status);
      sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_SENDING_DEVICE_INFORMATION_REQUEST_FAILED);
      break;

    case CLIENT_REQUESTING_IDENTITY:
      debugPrintln("EH - Sending identify request");
      status = sendIdentifyRequest(sli_zigbee_af_zll_identify_duration_sec);
      if (status == EMBER_SUCCESS) {
        moduleState = CLIENT_TOUCHLINKING;
        sl_zigbee_event_set_delay_ms(touchLinkEvent,
                                     EMBER_AF_PLUGIN_ZLL_COMMISSIONING_TOUCH_LINK_MILLISECONDS_DELAY);
      } else {
        emberAfAppPrintln("%p%p%p0x%x",
                          "Error: ",
                          "Touch linking failed: ",
                          "could not send identify request: ",
                          status);
        sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_SENDING_IDENTIFY_REQUEST_FAILED);
      }
      break;

    case CLIENT_TOUCHLINKING:
      status = sendIdentifyRequest(0);
      if (scanForTouchLink()) {
        debugPrintln("EH - Proceeding with touchlink");
        // If we are not factory new, we want to bring the target into our
        // existing network, so we set the channel to our own channel, either
        // our original channel, or the channel we formed on, if we are (were)
        // a factory-new router initiator.
        // Otherwise, we'll use whatever channel the target is on presently.
        if (!sli_zigbee_af_zll_am_factory_new()) {
          sli_zigbee_af_zll_network.zigbeeNetwork.channel = currentChannel;
        }
#ifdef NETWORK_CREATOR_PRESENT
        else if (sli_zigbee_af_current_zigbee_pro_network != NULL
                 && sli_zigbee_af_current_zigbee_pro_network->nodeType <= EMBER_ROUTER) {
          // If we are factory new and a router, then we need to form a network
          // to become non-factory new. See the BDB spec's touchlink procedure
          // for an initiator, steps 13, 21 and 22.
          status = sli_zigbee_af_zll_form_networkForRouterInitiator(0,
                                                                    EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER,
                                                                    0xffff);
          if (status != EMBER_SUCCESS) {
            emberAfAppPrintln("%p%p%p0x%x",
                              "Error: ",
                              "Touch linking failed: ",
                              "could not start network formation: ",
                              status);
            sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_NETWORK_FORMATION_FAILED);
          }
          return;
        }
#endif // NETWORK_CREATOR_PRESENT
        else {
          // If we are a factory new (end device) initiator, then let the
          // target chose the channel.
          sli_zigbee_af_zll_network.zigbeeNetwork.channel = 0;
        }
        emberAfZllSetInitialSecurityState();
        emberAfAppPrintln("%p%p%p",
                          "Sending ",
                          sli_zigbee_af_zll_am_factory_new() ? "start" : "join",
                          " request to target");
        sli_zigbee_af_initiatorRejoinRetryCount = 0;
        status = emberZllJoinTarget(&sli_zigbee_af_zll_network);
        if (status == EMBER_SUCCESS) {
          // We're finished here; the touchlink completion is handled by
          // the stack status handler in zll-commissioning-common.c
          moduleState = CLIENT_INITIAL;
        } else {
          // Check that it's not a non-fatal status, for example, if
          // emberZllJoinTarget() is sending a network update.
          if (status == EMBER_OPERATION_IN_PROGRESS) {
            // Abort, but report touchlink complete to application.
            sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_NETWORK_UPDATE_OPERATION);
          } else {
            emberAfAppPrintln("%p%p%p0x%x",
                              "Error: ",
                              "Touch linking failed: ",
                              "could not send start/join: ",
                              status);
            sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_SENDING_START_JOIN_FAILED);
          }
        }
      } else {
        if (scanForReset()) {
          status = sendResetToFactoryNewRequest();
          if (status != EMBER_SUCCESS) {
            emberAfAppPrintln("%p%p%p0x%x",
                              "Error: ",
                              "Touch linking failed: ",
                              "could not send reset: ",
                              status);
            sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_SENDING_RESET_TO_FACTORY_NEW_REQUEST_FAILED);
          }
        }

        // For all non-link scan types.
        if (status == EMBER_SUCCESS) {
          emberSetRadioChannel(currentChannel);
          sli_zigbee_af_zll_touch_link_complete();
          moduleState = CLIENT_INITIAL;
        }
      }
      break;

    default:
      break;
  }
}

void sli_zigbee_af_zll_commissioning_client_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_event_init(touchLinkEvent,
                       emberAfPluginZllCommissioningClientTouchLinkEventHandler);
}

/** @brief Get Pan Id
 *
 * This callback is called when the Network Creator plugin needs the PAN ID for
 * the network it is about to create. By default, the callback will return a
 * random 16-bit value.
 *
 */
EmberPanId emberAfPluginNetworkCreatorGetPanIdCallback(void)
{
  return (networkCreatorPanId == 0xFFFF
          ? emberGetPseudoRandomNumber()
          : networkCreatorPanId);
}

/** @brief Get Power For Radio Channel
 *
 * This callback is called when the Network Creator plugin needs the radio power for
 * the network it is about to create. By default, the callback will use the radio
 * power specified in the relevant plugin option.
 *
 */
int8_t emberAfPluginNetworkCreatorGetRadioPowerCallback(void)
{
  return networkCreatorRadioPower;
}
