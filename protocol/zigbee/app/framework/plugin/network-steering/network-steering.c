/***************************************************************************//**
 * @file
 * @brief General Procedure
 *
 * 1. Setup stack security with an Install code key (if available)
 *    If not available, skip to step 9.
 * 2. Set the channel mask to the Primary set of channels.
 * 3. Perform a scan of open networks on a single channel.
 * 4. For all beacons collected on that channel, filter out PAN IDs that are not open
 *    for joining or don't have the right stack profile (2), or are duplicates.
 * 5. For each discovered network, try to join.
 * 6. Repeat steps 3-5 until all channels in the mask are tried.
 * 7. If no networks are successfully joined, setup secondary channel mask
 *    (all channels) and repeat steps 3-6 with.
 * 8. If no networks are successfully joined, change the security
 *    to use the default well-known "ZigbeeAlliance09" key.
 * 9. Repeat steps 2-7
 *    (This will again try primary channel mask first, then secondary).
 * 10. If no networks are successsully joined, setup security to use
 *     distributed link key.
 * 11. Repeat steps 2.7.
 * 12. If no networks are joined successfully fail the whole process and return
 *     control to the application.
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

#include "app/framework/security/af-security.h" // sli_zigbee_af_clear_link_key_table()
#include "network-steering.h"
#include "network-steering-internal.h"

#include "stack/include/zigbee-security-manager.h"

#ifndef OPTIMIZE_SCANS

#include "app/framework/plugin/scan-dispatch/scan-dispatch.h"
#include "app/framework/plugin/update-tc-link-key/update-tc-link-key.h"

#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
extern EmberEventControl sl_af_test_harness_z3_opent_network_event_control;
#endif

#ifdef EMBER_TEST
  #define HIDDEN
  #define EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER 3
#else
  #define HIDDEN static
#endif

//============================================================================
// Globals

#if !defined(EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK)
  #define EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK \
  (BIT32(11) | BIT32(14))
#endif

#if !defined(EMBER_AF_PLUGIN_NETWORK_STEERING_SCAN_DURATION)
  #define EMBER_AF_PLUGIN_NETWORK_STEERING_SCAN_DURATION 5
#endif

#if !defined(EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S)
  #define EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S (180)
#endif

#ifdef RADIO_TX_CALLBACK
  #define GET_RADIO_TX_POWER(channel) emberAfPluginNetworkSteeringGetPowerForRadioChannelCallback(channel)
#else
  #define GET_RADIO_TX_POWER(channel) EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER
#endif

const char * sli_zigbee_af_network_steering_stateNames[] = {
  "None",
  // These next two states are only run if explicitly configured to do so
  // See sli_zigbee_af_network_steering_set_configured_key()
  "Scan Primary Channels and use Configured Key",
  "Scan Secondary Channels and use Configured Key",
  "Scan Primary Channels and use Install Code",
  "Scan Secondary Channels and use Install Code",
  "Scan Primary Channels and Use Centralized Key",
  "Scan Secondary Channels and Use Centralized Key",
  "Scan Primary Channels and Use Distributed Key",
  "Scan Secondary Channels and Use Distributed Key",
};

#define LAST_JOINING_STATE \
  EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_DISTRIBUTED

EmberAfPluginNetworkSteeringJoiningState sli_zigbee_af_network_steering_state
  = EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE;

const uint8_t sli_zigbee_af_network_steering_plugin_name[] = "NWK Steering";
#define PLUGIN_NAME sli_zigbee_af_network_steering_plugin_name

// #define PLUGIN_DEBUG
#if defined(PLUGIN_DEBUG)
  #define debugPrintln(...) emberAfCorePrintln(__VA_ARGS__)
  #define debugPrint(...)   emberAfCorePrint(__VA_ARGS__)
  #define debugExec(x) do { x; } while (0)
#else
  #define debugPrintln(...)
  #define debugPrint(...)
  #define debugExec(x)
#endif

#define SECONDARY_CHANNEL_MASK EMBER_ALL_802_15_4_CHANNELS_MASK

#define REQUIRED_STACK_PROFILE 2

static const EmberKeyData defaultLinkKey = {
  { 0x5A, 0x69, 0x67, 0x42, 0x65, 0x65, 0x41, 0x6C,
    0x6C, 0x69, 0x61, 0x6E, 0x63, 0x65, 0x30, 0x39 }
};
static const EmberKeyData distributedTestKey = {
  { 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7,
    0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF }
};

// These parameters allow for filtering which networks to find or which specific
// key to use
static bool gFilterByExtendedPanId = false;
static uint8_t gExtendedPanIdToFilterOn[8];
static bool gUseConfiguredKey = false;
static EmberKeyData gConfiguredKey = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
};

static bool printedMaxPanIdsWarning = false;
uint8_t sli_zigbee_af_network_steering_pan_id_index = 0;
uint8_t sli_zigbee_af_network_steering_current_channel;

// We make these into variables so that they can be changed at run time.
// This is very useful for unit and interop tests.
uint32_t sli_zigbee_af_network_steering_primary_channel_mask
  = EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK;
uint32_t sli_zigbee_af_network_steering_secondary_channel_mask
  = SECONDARY_CHANNEL_MASK;

uint8_t sli_zigbee_af_network_steering_total_beacons = 0;
uint8_t sli_zigbee_af_network_steering_join_attempts = 0;
EmberKeyData emberPluginNetworkSteeringDistributedKey;

static uint32_t currentChannelMask = 0;

sl_zigbee_event_t emberAfPluginNetworkSteeringFinishSteeringEvent[EMBER_SUPPORTED_NETWORKS];
#define finishSteeringEvent (emberAfPluginNetworkSteeringFinishSteeringEvent)
void emberAfPluginNetworkSteeringFinishSteeringEventHandler(sl_zigbee_event_t * event);

// TODO: good value for this?
// Let's try jittering our TCLK update and permit join broadcast to cut down
// on commission-time traffic.
#define FINISH_STEERING_JITTER_MIN_MS (MILLISECOND_TICKS_PER_SECOND << 1)
#define FINISH_STEERING_JITTER_MAX_MS (MILLISECOND_TICKS_PER_SECOND << 2)
#define randomJitterMS()                                               \
  ((emberGetPseudoRandomNumber()                                       \
    % (FINISH_STEERING_JITTER_MAX_MS - FINISH_STEERING_JITTER_MIN_MS)) \
   + FINISH_STEERING_JITTER_MIN_MS)
#define UPDATE_TC_LINK_KEY_JITTER_MIN_MS (MILLISECOND_TICKS_PER_SECOND * 10)
#define UPDATE_TC_LINK_KEY_JITTER_MAX_MS (MILLISECOND_TICKS_PER_SECOND * 40)

// This is an attribute specified in the BDB.
#define VERIFY_KEY_TIMEOUT_MS (5 * MILLISECOND_TICKS_PER_SECOND)

EmberAfPluginNetworkSteeringOptions sli_zigbee_af_network_steering_options_mask
  = EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIONS_NONE;

//============================================================================
// Forward Declarations

static void cleanupAndStop(EmberStatus status);
static EmberStatus stateMachineRun(void);
static uint8_t getNextChannel(void);
static EmberStatus tryNextMethod(void);
static EmberStatus setupSecurity(void);
static uint32_t jitterTimeDelayMs();
HIDDEN void scanResultsHandler(EmberAfPluginScanDispatchScanResults *results);

bool emberStackIsUp(void);

// Callback declarations for the sake of the compiler during unit tests.
int8_t emberAfPluginNetworkSteeringGetPowerForRadioChannelCallback(uint8_t channel);
bool emberAfPluginNetworkSteeringGetDistributedKeyCallback(EmberKeyData * key);
EmberNodeType emberAfPluginNetworkSteeringGetNodeTypeCallback(EmberAfPluginNetworkSteeringJoiningState state);
//============================================================================
// Internal callbacks

void sli_zigbee_af_network_steering_init_callback(uint8_t init_level)
{
  (void)init_level;

  sl_zigbee_network_event_init(finishSteeringEvent,
                               emberAfPluginNetworkSteeringFinishSteeringEventHandler);
}

//============================================================================
// State Machine

static bool addPanIdCandidate(uint16_t panId)
{
  uint16_t* panIdPointer = sli_zigbee_af_network_steering_get_stored_pan_id_pointer(0);
  if (panIdPointer == NULL) {
    emberAfCorePrintln("Error: %p could not get memory pointer for stored PAN IDs",
                       PLUGIN_NAME);
    return false;
  }
  uint8_t maxNetworks = sli_zigbee_af_network_steering_get_max_possible_pan_ids();
  uint8_t i;
  for (i = 0; i < maxNetworks; i++) {
    if (panId == *panIdPointer) {
      // We already know about this PAN, no point in recording it twice.
      debugPrintln("Ignoring duplicate PAN ID 0x%2X", panId);
      return true;
    } else if (*panIdPointer == EMBER_AF_INVALID_PAN_ID) {
      *panIdPointer = panId;
      debugPrintln("Stored PAN ID 0x%2X", *panIdPointer);
      return true;
    }
    panIdPointer++;
  }

  if (!printedMaxPanIdsWarning) {
    emberAfCorePrintln("Warning: %p Max PANs reached (%d)",
                       PLUGIN_NAME,
                       maxNetworks);
    printedMaxPanIdsWarning = true;
  }
  return true;
}

static void clearPanIdCandidates(void)
{
  printedMaxPanIdsWarning = false;
  sli_zigbee_af_network_steering_clear_stored_pan_ids();
  sli_zigbee_af_network_steering_pan_id_index = 0;
}

static uint16_t getNextCandidate(void)
{
  debugPrintln("Getting candidate at index %d", sli_zigbee_af_network_steering_pan_id_index);
  uint16_t* pointer =
    sli_zigbee_af_network_steering_get_stored_pan_id_pointer(sli_zigbee_af_network_steering_pan_id_index);
  if (pointer == NULL) {
    debugPrintln("Error: %p could not get pointer to stored PANs", PLUGIN_NAME);
    return EMBER_AF_INVALID_PAN_ID;
  }
  sli_zigbee_af_network_steering_pan_id_index++;
  return *pointer;
}

static void gotoNextChannel(void)
{
  EmberAfPluginScanDispatchScanData scanData;
  EmberStatus status;

  sli_zigbee_af_network_steering_current_channel = getNextChannel();
  if (sli_zigbee_af_network_steering_current_channel == 0) {
    debugPrintln("No more channels");
    tryNextMethod();
    return;
  }
  clearPanIdCandidates();

  // Set radio power before active scan to configure beacon request
  // Tx power level based on the plugin setting
  (void)emberSetRadioPower(EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER);

  scanData.scanType = EMBER_ACTIVE_SCAN;
  scanData.channelMask = BIT32(sli_zigbee_af_network_steering_current_channel);
  scanData.duration = EMBER_AF_PLUGIN_NETWORK_STEERING_SCAN_DURATION;
  scanData.handler = scanResultsHandler;
  status = emberAfPluginScanDispatchScheduleScan(&scanData);

  if (EMBER_SUCCESS != status) {
    emberAfCorePrintln("Error: %p start scan failed: 0x%X", PLUGIN_NAME, status);
    cleanupAndStop(status);
  } else {
    emberAfCorePrintln("Starting scan on channel %d",
                       sli_zigbee_af_network_steering_current_channel);
  }
}

void tryToJoinNetwork(void)
{
  EmberNetworkParameters networkParams;
  EmberStatus status;
  EmberNodeType nodeType;

  MEMSET(&networkParams, 0, sizeof(EmberNetworkParameters));

  networkParams.panId = getNextCandidate();
  if (networkParams.panId == EMBER_AF_INVALID_PAN_ID) {
    debugPrintln("No networks to join on channel %d", sli_zigbee_af_network_steering_current_channel);
    gotoNextChannel();
    return;
  }

  emberAfCorePrintln("%p joining 0x%2x", PLUGIN_NAME, networkParams.panId);
  networkParams.radioChannel = sli_zigbee_af_network_steering_current_channel;
  networkParams.radioTxPower = GET_RADIO_TX_POWER(sli_zigbee_af_network_steering_current_channel);
  nodeType = emberAfPluginNetworkSteeringGetNodeTypeCallback(sli_zigbee_af_network_steering_state);
  status = emberJoinNetwork(nodeType, &networkParams);
  sli_zigbee_af_network_steering_join_attempts++;
  if (EMBER_SUCCESS != status) {
    emberAfCorePrintln("Error: %p could not attempt join: 0x%X",
                       PLUGIN_NAME,
                       status);
    cleanupAndStop(status);
    return;
  }
}

//Description: Generates a random number between 10000-40000.
static uint32_t jitterTimeDelayMs()
{
  uint32_t jitterDelayMs = (emberGetPseudoRandomNumber() % (UPDATE_TC_LINK_KEY_JITTER_MAX_MS - UPDATE_TC_LINK_KEY_JITTER_MIN_MS + 1)) + UPDATE_TC_LINK_KEY_JITTER_MIN_MS;
  return jitterDelayMs;
}

// TODO: renamed for naming consistency purposes
void sli_zigbee_af_network_steering_stack_status_callback(EmberStatus status)
{
  if (sli_zigbee_af_network_steering_state
      == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE) {
    sl_zb_sec_man_context_t context;
    sl_zb_sec_man_init_context(&context);

    context.core_key_type = SL_ZB_SEC_MAN_KEY_TYPE_TC_LINK;

    sl_status_t keystatus = sl_zb_sec_man_check_key_context(&context);
    if (keystatus == SL_STATUS_OK
        && sl_zb_sec_man_compare_key_to_value(&context, (sl_zb_sec_man_key_t*)&defaultLinkKey)
        && status == EMBER_NETWORK_UP) {
      emberAfPluginUpdateTcLinkKeySetDelay(jitterTimeDelayMs());
    } else if (status == EMBER_NETWORK_DOWN) {
      emberAfPluginUpdateTcLinkKeySetInactive();
    }
    return;
  } else if (status == EMBER_NETWORK_UP) {
    emberAfCorePrintln("%p network joined.", PLUGIN_NAME);
    if (!sli_zigbee_af_network_steering_state_uses_distributed_key()
        && !(sli_zigbee_af_network_steering_options_mask
             & EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIONS_NO_TCLK_UPDATE)) {
      sli_zigbee_af_network_steering_state_set_update_tclk();
    }
    sl_zigbee_event_set_delay_ms(finishSteeringEvent, randomJitterMS());
    return;
  } else if (!emberStackIsUp()) {
    tryToJoinNetwork();
  } else {
  }
}

static void scanCompleteCallback(uint8_t channel, sl_status_t status)
{
  if (status != SL_STATUS_OK) {
    emberAfCorePrintln("Error: Scan complete handler returned 0x%X on %d", status, channel);
  } else {   // when scan is over, we always return with success
    // EMAPPFWKV2-1462 - make sure we didn't cleanupAndStop() above.
    if (sli_zigbee_af_network_steering_state
        != EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE) {
      tryToJoinNetwork();
    }
  }
}

static void networkFoundCallback(EmberZigbeeNetwork *networkFound,
                                 uint8_t lqi,
                                 int8_t rssi)
{
  sli_zigbee_af_network_steering_total_beacons++;

  if (!(networkFound->allowingJoin
        && networkFound->stackProfile == REQUIRED_STACK_PROFILE)) {
    return;
  }

  debugPrint("%p nwk found ch: %d, panID 0x%2X, xpan: ",
             PLUGIN_NAME,
             networkFound->channel,
             networkFound->panId);
  debugExec(emberAfPrintBigEndianEui64(networkFound->extendedPanId));

  // If we were told to filter by extended PAN ID, do so now
  if (gFilterByExtendedPanId) {
    if (0 != MEMCOMPARE(networkFound->extendedPanId,
                        gExtendedPanIdToFilterOn,
                        COUNTOF(gExtendedPanIdToFilterOn))) {
      debugPrint(". Skipping since we are looking for xpan: ");
      debugExec(emberAfPrintBigEndianEui64(gExtendedPanIdToFilterOn));
      debugPrintln("");
      return;
    }
  }

  debugPrintln("");

  if (!addPanIdCandidate(networkFound->panId)) {
    emberAfCorePrintln("Error: %p could not add candidate network.",
                       PLUGIN_NAME);
    cleanupAndStop(EMBER_ERR_FATAL);
    return;
  }
}

HIDDEN void scanResultsHandler(EmberAfPluginScanDispatchScanResults *results)
{
  if (emberAfPluginScanDispatchScanResultsAreComplete(results)
      || emberAfPluginScanDispatchScanResultsAreFailure(results)) {
    scanCompleteCallback(results->channel, results->status);
  } else if (results->network && results->network->panId != EMBER_AF_INVALID_PAN_ID) {
    networkFoundCallback(results->network,
                         results->lqi,
                         results->rssi);
  }
}

static EmberStatus tryNextMethod(void)
{
  sli_zigbee_af_network_steering_state++;
  if (sli_zigbee_af_network_steering_state > LAST_JOINING_STATE) {
    EmberStatus status = (sli_zigbee_af_network_steering_total_beacons > 0
                          ? EMBER_JOIN_FAILED
                          : EMBER_NO_BEACONS);
    cleanupAndStop(status);
    return status;
  }
  return stateMachineRun();
}

static void cleanupAndStop(EmberStatus status)
{
  emberAfCorePrintln("%p Stop.  Cleaning up.", PLUGIN_NAME);
  emberAfPluginNetworkSteeringCompleteCallback(status,
                                               sli_zigbee_af_network_steering_total_beacons,
                                               sli_zigbee_af_network_steering_join_attempts,
                                               sli_zigbee_af_network_steering_state);
  sli_zigbee_af_network_steering_clear_stored_pan_ids();
  sli_zigbee_af_network_steering_state = EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE;
  sli_zigbee_af_network_steering_pan_id_index = 0;
  sli_zigbee_af_network_steering_join_attempts = 0;
  sli_zigbee_af_network_steering_total_beacons = 0;
}

static uint8_t getNextChannel(void)
{
  if (sli_zigbee_af_network_steering_current_channel == 0) {
    sli_zigbee_af_network_steering_current_channel = (emberGetPseudoRandomNumber() & 0x0F)
                                                     + EMBER_MIN_802_15_4_CHANNEL_NUMBER;
    debugPrintln("Randomly choosing a starting channel %d.", sli_zigbee_af_network_steering_current_channel);
  } else {
    sli_zigbee_af_network_steering_current_channel++;
  }
  while (currentChannelMask != 0) {
    if (BIT32(sli_zigbee_af_network_steering_current_channel) & currentChannelMask) {
      currentChannelMask &= ~(BIT32(sli_zigbee_af_network_steering_current_channel));
      return sli_zigbee_af_network_steering_current_channel;
    }
    sli_zigbee_af_network_steering_current_channel++;
    if (sli_zigbee_af_network_steering_current_channel > EMBER_MAX_802_15_4_CHANNEL_NUMBER) {
      sli_zigbee_af_network_steering_current_channel = EMBER_MIN_802_15_4_CHANNEL_NUMBER;
    }
  }
  return 0;
}

static EmberStatus stateMachineRun(void)
{
  EmberStatus status = EMBER_SUCCESS;
  emberAfCorePrintln("%p State: %p",
                     PLUGIN_NAME,
                     sli_zigbee_af_network_steering_stateNames[sli_zigbee_af_network_steering_state]);

  if ((status = setupSecurity()) != EMBER_SUCCESS) {
    emberAfCorePrintln("Error: %p could not setup security: 0x%X",
                       PLUGIN_NAME,
                       status);
    return tryNextMethod();
  }

  switch (sli_zigbee_af_network_steering_state) {
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_CONFIGURED:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_INSTALL_CODE:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_CENTRALIZED:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_DISTRIBUTED:
      currentChannelMask = sli_zigbee_af_network_steering_primary_channel_mask;
      break;
    default:
      currentChannelMask = sli_zigbee_af_network_steering_secondary_channel_mask;
      break;
  }

  debugPrintln("Channel Mask: 0x%4X", currentChannelMask);
  gotoNextChannel();
  return status;
}

static EmberStatus setupSecurity(void)
{
  EmberStatus status;
  EmberInitialSecurityState state;
  EmberExtendedSecurityBitmask extended;

  state.bitmask = (EMBER_TRUST_CENTER_GLOBAL_LINK_KEY
                   | EMBER_HAVE_PRECONFIGURED_KEY
                   | EMBER_REQUIRE_ENCRYPTED_KEY
                   | EMBER_NO_FRAME_COUNTER_RESET
#ifndef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
                   // When running with a Test Harness, the Test Harness will write the install-code
                   // derived link key directly to the Transient Key Table.
                   | (sli_zigbee_af_network_steering_state_uses_install_codes()
                      ? EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE
                      : 0)
#endif
                   | (sli_zigbee_af_network_steering_state_uses_distributed_key()
                      ? EMBER_DISTRIBUTED_TRUST_CENTER_MODE
                      : 0)
                   );

  if (!emberAfPluginNetworkSteeringGetDistributedKeyCallback(&emberPluginNetworkSteeringDistributedKey)) {
    MEMMOVE(emberKeyContents(&emberPluginNetworkSteeringDistributedKey),
            emberKeyContents(&distributedTestKey),
            EMBER_ENCRYPTION_KEY_SIZE);
  }
  MEMMOVE(emberKeyContents(&(state.preconfiguredKey)),
          gUseConfiguredKey ? emberKeyContents(&(gConfiguredKey))
          : (sli_zigbee_af_network_steering_state_uses_distributed_key()
             ? emberKeyContents(&emberPluginNetworkSteeringDistributedKey)
             : emberKeyContents(&defaultLinkKey)),
          EMBER_ENCRYPTION_KEY_SIZE);

  if ((status = emberSetInitialSecurityState(&state))
      != EMBER_SUCCESS) {
    if (sli_zigbee_af_network_steering_state_uses_install_codes()
        && (status == EMBER_SECURITY_CONFIGURATION_INVALID)) {
      emberAfCorePrintln("Error: install code setup failed. Is an install "
                         "code flashed onto the device?");
    }
    goto done;
  }

  extended = (EMBER_JOINER_GLOBAL_LINK_KEY
              | EMBER_EXT_NO_FRAME_COUNTER_RESET);

  if ((status = emberSetExtendedSecurityBitmask(extended)) != EMBER_SUCCESS) {
    goto done;
  }

  sli_zigbee_af_clear_link_key_table();

  done:
  return status;
}

EmberStatus emberAfPluginNetworkSteeringStart(void)
{
  EmberStatus status = EMBER_INVALID_CALL;
  if (sli_zigbee_af_pro_is_current_network()
      && (sli_zigbee_af_network_steering_state
          == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE)) {
    if (emberAfNetworkState() == EMBER_NO_NETWORK) {
      emberAfAddToCurrentAppTasksCallback(EMBER_AF_WAITING_FOR_TC_KEY_UPDATE);     // to force sleepy device do short poll
      sli_zigbee_af_network_steering_state = gUseConfiguredKey
                                             ? EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_CONFIGURED
                                             : EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_INSTALL_CODE;

      // Stop any previous trust center link key update.
      emberAfPluginUpdateTcLinkKeyStop();

      status = stateMachineRun();
    } else {
      status = emberAfPermitJoin(EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S,
                                 true);     // Broadcast permit join?
    }
  } else {
    emberAfCorePrintln("%s is already in progress",
                       sli_zigbee_af_network_steering_plugin_name);
  }

  emberAfCorePrintln("%p: %p: 0x%X",
                     sli_zigbee_af_network_steering_plugin_name,
                     "Start",
                     status);

  return status;
}

EmberStatus emberAfPluginNetworkSteeringStop(void)
{
  if (sli_zigbee_af_network_steering_state
      == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE) {
    return EMBER_INVALID_CALL;
  }
  cleanupAndStop(EMBER_JOIN_FAILED);
  return EMBER_SUCCESS;
}

// =============================================================================
// Finish Steering

// At the end of the network steering process, we need to update the
// trust center link key (if we are in a centralized network) and broadcast
// a permit join to extend the network. This process needs to happen after
// we send our device announce and possibly our network timeout request if we
// are an end device.
void emberAfPluginNetworkSteeringFinishSteeringEventHandler(sl_zigbee_event_t * event)
{
  EmberStatus status;

  sl_zigbee_event_set_inactive(finishSteeringEvent);

  if (sli_zigbee_af_network_steering_state_verify_tclk()) {
    // If we get here, then we have failed to verify the TCLK. Therefore,
    // we leave the network.
    emberAfPluginUpdateTcLinkKeyStop();
    emberLeaveNetwork();
    emberAfCorePrintln("%p: %p",
                       PLUGIN_NAME,
                       "Key verification failed. Leaving network");
    cleanupAndStop(EMBER_ERR_FATAL);
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_TC_KEY_UPDATE);
  } else if (sli_zigbee_af_network_steering_state_update_tclk()) {
    // Start the process to update the TC link key. We will set another event
    // for the broadcast permit join.
    // Attempt a TC link key update now.
    emberAfPluginUpdateTcLinkKeySetDelay(0);
  } else {
    // Broadcast permit join to extend the network.
    // We are done!
    status = emberAfPermitJoin(EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S,
                               true);     // Broadcast permit join?
    emberAfCorePrintln("%p: %p: 0x%X",
                       PLUGIN_NAME,
                       "Broadcasting permit join",
                       status);
    cleanupAndStop(status);
    emberAfRemoveFromCurrentAppTasks(EMBER_AF_WAITING_FOR_TC_KEY_UPDATE);
  }
}

void emberAfPluginUpdateTcLinkKeyStatusCallback(EmberKeyStatus keyStatus)
{
  if (sli_zigbee_af_network_steering_state_update_tclk()) {
    emberAfCorePrintln("%p: %p: 0x%X",
                       PLUGIN_NAME,
                       "Trust center link key update status",
                       keyStatus);
    switch (keyStatus) {
      case EMBER_TRUST_CENTER_LINK_KEY_ESTABLISHED:
        // Success! But we should still wait to make sure we verify the key.
        sli_zigbee_af_network_steering_state_set_verify_tclk();
        sl_zigbee_event_set_delay_ms(finishSteeringEvent, VERIFY_KEY_TIMEOUT_MS);
        return;
      case EMBER_TRUST_CENTER_IS_PRE_R21:
      case EMBER_VERIFY_LINK_KEY_SUCCESS:
        // If the trust center is pre-r21, then we don't update the link key.
        // If the key status is that the link key has been verified, then we
        // have successfully updated our trust center link key and we are done!
        sli_zigbee_af_network_steering_state_clear_verify_tclk();
        sl_zigbee_event_set_delay_ms(finishSteeringEvent, randomJitterMS());
        break;
      default:
        // Failure!
        emberLeaveNetwork();
        cleanupAndStop(EMBER_NO_LINK_KEY_RECEIVED);
    }
    sli_zigbee_af_network_steering_state_clear_update_tclk();
  }

  return;
}

void sli_zigbee_af_network_steering_set_channel_mask(uint32_t mask, bool secondaryMask)
{
  if (secondaryMask) {
    sli_zigbee_af_network_steering_secondary_channel_mask = mask;
  } else {
    sli_zigbee_af_network_steering_primary_channel_mask = mask;
  }
}

void sli_zigbee_af_network_steering_set_extended_pan_id_filter(uint8_t* extendedPanId,
                                                               bool turnFilterOn)
{
  if (!extendedPanId) {
    return;
  }
  MEMCOPY(gExtendedPanIdToFilterOn,
          extendedPanId,
          COUNTOF(gExtendedPanIdToFilterOn));
  gFilterByExtendedPanId = turnFilterOn;
}

void sli_zigbee_af_network_steering_set_configured_key(uint8_t *key,
                                                       bool useConfiguredKey)
{
  if (!key) {
    return;
  }
  MEMCOPY(gConfiguredKey.contents, key, EMBER_ENCRYPTION_KEY_SIZE);
  gUseConfiguredKey = useConfiguredKey;
}

void sli_zigbee_af_network_steering_cleanup(EmberStatus status)
{
  cleanupAndStop(status);
}

uint8_t sli_zigbee_af_network_steering_get_current_channel()
{
  return sli_zigbee_af_network_steering_current_channel;
}

#endif // OPTIMIZE_SCANS
