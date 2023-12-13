/***************************************************************************//**
 * @file
 * @brief This file implements the Zigbee 3.0 network steering procedure using
 * only one 15.4 scan.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "stack/include/network-formation.h"
#include "stack/include/zigbee-security-manager.h"

#ifdef OPTIMIZE_SCANS

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_SCAN_DISPATCH_PRESENT
#include "scan-dispatch.h"
#else
#include "app/framework/plugin/scan-dispatch/scan-dispatch.h"
#endif

#ifdef SL_CATALOG_ZIGBEE_UPDATE_TC_LINK_KEY_PRESENT
#include "update-tc-link-key.h"
#else
#include "app/framework/plugin/update-tc-link-key/update-tc-link-key.h"
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
  "Scan Primary Channels and use Install Code",
  "Scan Primary Channels and Use Centralized Key",
  "Scan Primary Channels and Use Distributed Key",
  "Scan Secondary Channels and use Install Code",
  "Scan Secondary Channels and Use Centralized Key",
  "Scan Secondary Channels and Use Distributed Key",
  // The Use All Keys states are run only if the plugin option is selected, in
  // which case the other states are not run
  "Scan Primary Channels and Use All Keys (install code, centralized, distributed)",
  "Scan Secondary Channels and Use All Keys (install code, centralized, distributed)",
};

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

#define SECONDARY_CHANNEL_MASK                                                        \
  ((EMBER_ALL_802_15_4_CHANNELS_MASK ^ EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK) \
   & EMBER_ALL_802_15_4_CHANNELS_MASK)

#define WILDCARD_EUI  { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }

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
static uint32_t scheduleScanChannelMask = 0;

bool emberStackIsUp(void);

// We make these into variables so that they can be changed at run time.
// This is very useful for unit and interop tests.
uint32_t sli_zigbee_af_network_steering_primary_channel_mask
  = EMBER_AF_PLUGIN_NETWORK_STEERING_CHANNEL_MASK;
uint32_t sli_zigbee_af_network_steering_secondary_channel_mask
  = SECONDARY_CHANNEL_MASK;

uint8_t sli_zigbee_af_network_steering_total_beacons = 0;
uint8_t sli_zigbee_af_network_steering_join_attempts = 0;
EmberKeyData emberPluginNetworkSteeringDistributedKey;

NetworkSteeringState steeringState = { 0 };
// Shorthand names
#define BEACON_ITERATOR         steeringState.beaconIterator
#define CURRENT_CHANNEL_MASK    steeringState.currentChannelMask

sl_zigbee_event_t emberAfPluginNetworkSteeringFinishSteeringEvent[EMBER_SUPPORTED_NETWORKS];
#define finishSteeringEvent (emberAfPluginNetworkSteeringFinishSteeringEvent)

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

#ifdef TRY_ALL_KEYS
  #define FIRST_PRIMARY_STATE     EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_USE_ALL_KEYS
  #define FIRST_SECONDARY_STATE   EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_USE_ALL_KEYS
#else // TRY_ALL_KEYS
  #define FIRST_PRIMARY_STATE     EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_INSTALL_CODE
  #define FIRST_SECONDARY_STATE   EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_INSTALL_CODE
#endif // TRY_ALL_KEYS

//============================================================================
// Externs

#ifdef EZSP_HOST
 #define setMaxBeaconsToStore(n)  { \
    uint8_t val = n;                \
    (void)ezspSetValue(EZSP_VALUE_MAX_BEACONS_TO_STORE, 1, &val); }
#else // EZSP_HOST
 #define setMaxBeaconsToStore(n)  { \
    (void)emberSetNumBeaconsToStore(n); }
#endif // EZSP_HOST
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
extern sl_zigbee_event_t emberAfPluginTestHarnessZ3OpenNetworkEvent;
#endif
//============================================================================
// Forward Declarations

static void cleanupAndStop(EmberStatus status);
static void stateMachineRun(void);
static void tryToJoinNetwork(void);
static EmberStatus goToNextState(void);
static EmberStatus setupSecurity(void);
static uint32_t jitterTimeDelayMs();
HIDDEN void scanResultsHandler(EmberAfPluginScanDispatchScanResults *results);
static EmberStatus scheduleScan(uint32_t channelMask);

// Callback declarations for the sake of the compiler during unit tests.
int8_t emberAfPluginNetworkSteeringGetPowerForRadioChannelCallback(uint8_t channel);
bool emberAfPluginNetworkSteeringGetDistributedKeyCallback(EmberKeyData * key);
EmberNodeType emberAfPluginNetworkSteeringGetNodeTypeCallback(EmberAfPluginNetworkSteeringJoiningState state);

void emberAfPluginNetworkSteeringFinishSteeringEventHandler(sl_zigbee_event_t * event);

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

void tryToJoinNetwork()
{
  EmberStatus status = EMBER_SUCCESS;
  EmberNodeType nodeType;
  int8_t radioTxPower;

  emberAfCorePrintln("Examining beacon on channel %d with panId 0x%2X",
                     BEACON_ITERATOR.beacon.channel,
                     BEACON_ITERATOR.beacon.panId);

  if (!(CURRENT_CHANNEL_MASK & BIT32(BEACON_ITERATOR.beacon.channel))) {
    emberAfCorePrintln("This beacon is not part of the current "
                       "channel mask (0x%4X)."
                       " Getting next beacon whose channel bitmask is set.",
                       CURRENT_CHANNEL_MASK);
  }

  bool filteredOut = false;
  if (gFilterByExtendedPanId) {
    if (0 != MEMCOMPARE(BEACON_ITERATOR.beacon.extendedPanId,
                        gExtendedPanIdToFilterOn,
                        COUNTOF(gExtendedPanIdToFilterOn))) {
      debugPrint(". Skipping since we are looking for xpan: ");
      debugExec(emberAfPrintBigEndianEui64(gExtendedPanIdToFilterOn));
      debugPrintln("");
      filteredOut = true;
    }
  }

  // If the retrieved beacon channel is not set in the mask or we've filtered it
  // out, get the next valid beacon
  while ((!(CURRENT_CHANNEL_MASK & BIT32(BEACON_ITERATOR.beacon.channel)))
         || filteredOut) {
    status = emberGetNextBeacon(&(BEACON_ITERATOR.beacon));

    if (status != EMBER_SUCCESS) {
      break;
    }

    filteredOut = (gFilterByExtendedPanId && MEMCOMPARE(BEACON_ITERATOR.beacon.extendedPanId,
                                                        gExtendedPanIdToFilterOn,
                                                        COUNTOF(gExtendedPanIdToFilterOn)));
  }

  if (status != EMBER_SUCCESS) {
    emberAfCorePrintln("No beacons left on current mask. Moving to next state");

    status = goToNextState();
    if (status != EMBER_SUCCESS) {
      return;
    }

    stateMachineRun();
    return;
  }

  emberAfCorePrintln("%p joining 0x%2x on channel %d",
                     PLUGIN_NAME,
                     BEACON_ITERATOR.beacon.panId,
                     BEACON_ITERATOR.beacon.channel);

  nodeType = emberAfPluginNetworkSteeringGetNodeTypeCallback(sli_zigbee_af_network_steering_state);
  radioTxPower = GET_RADIO_TX_POWER(BEACON_ITERATOR.beacon.channel);
  status = emberJoinNetworkDirectly(nodeType,
                                    &BEACON_ITERATOR.beacon,
                                    radioTxPower,
                                    true);  // clearBeaconsAfterNetworkUp
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

static bool joinedToDistributedNetwork(void)
{
  EmberCurrentSecurityState securityState;
  EmberStatus status = emberGetCurrentSecurityState(&securityState);
  if (status == EMBER_SUCCESS) {
    return (securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE);
  }
  return false;
}

void sli_zigbee_af_network_steering_stack_status_callback(EmberStatus status)
{
  emberAfCorePrintln("%p stack status 0x%X", PLUGIN_NAME, status);

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
  } else if (status == EMBER_NETWORK_UP) {
    emberAfCorePrintln("%p network joined.", PLUGIN_NAME);
    if (!sli_zigbee_af_network_steering_state_uses_distributed_key()
        && !(sli_zigbee_af_network_steering_options_mask
             & EMBER_AF_PLUGIN_NETWORK_STEERING_OPTIONS_NO_TCLK_UPDATE)
        && !joinedToDistributedNetwork()) {
      sli_zigbee_af_network_steering_state_set_update_tclk();
    }
    sl_zigbee_event_set_delay_ms(finishSteeringEvent, randomJitterMS());
  } else if (!emberStackIsUp()) {
    if (sli_zigbee_af_network_steering_state > EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE
        && sli_zigbee_af_network_steering_state < EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_FINISHED) {
      emberAfCorePrintln("%p trying next network.", PLUGIN_NAME);

      status = emberGetNextBeacon(&(BEACON_ITERATOR.beacon));
      if (status != EMBER_SUCCESS) {
        emberAfCorePrintln("No beacons left on current mask. "
                           "Moving to next state");

        status = goToNextState();
        if (status != EMBER_SUCCESS) {
          return;
        }

        stateMachineRun();
      } else {
        tryToJoinNetwork();
      }
    } else {
      cleanupAndStop(EMBER_NO_LINK_KEY_RECEIVED);
    }
  } else {
  }
}

static EmberStatus scheduleScan(uint32_t channelMask)
{
  EmberStatus status;
  EmberNodeType nodeType;
  EmberAfPluginScanDispatchScanData scanData;

  scheduleScanChannelMask = channelMask;
  // Kick off a scan and record beacons
  setMaxBeaconsToStore(EMBER_MAX_BEACONS_TO_STORE);

  MEMSET(&steeringState, 0, sizeof(steeringState));

  nodeType = emberAfPluginNetworkSteeringGetNodeTypeCallback(sli_zigbee_af_network_steering_state);

  // If the local nodeType is a router, ensure that a router scan is initated
  // This will enable the beacon-handling code will properly filter for
  // good beacons with router capacity
  if ( EMBER_ROUTER == nodeType ) {
    scanData.scanType = EMBER_ACTIVE_SCAN_ROUTER;
  } else {
    scanData.scanType = EMBER_ACTIVE_SCAN;
  }

  // Set radio power before active scan to configure beacon request
  // Tx power level based on the plugin setting
  (void)emberSetRadioPower(EMBER_AF_PLUGIN_NETWORK_STEERING_RADIO_TX_POWER);

  scanData.channelMask = channelMask;
  scanData.duration = EMBER_AF_PLUGIN_NETWORK_STEERING_SCAN_DURATION;
  scanData.handler = scanResultsHandler;
  status = emberAfPluginScanDispatchScheduleScan(&scanData);
  emberAfCorePrintln("%s: issuing scan on %s channels (mask 0x%4X)",
                     PLUGIN_NAME,
                     channelMask == sli_zigbee_af_network_steering_primary_channel_mask
                     ? "primary"
                     : "secondary",
                     channelMask);
  return status;
}

// This function is called after a channel mask has been scanned
HIDDEN void scanResultsHandler(EmberAfPluginScanDispatchScanResults *results)
{
  // If steering-stop was issued using a CLI command, ignore the results of the previously
  // started scan
  if (sli_zigbee_af_network_steering_state == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE) {
    return;
  }

  if (emberAfPluginScanDispatchScanResultsAreComplete(results)
      || emberAfPluginScanDispatchScanResultsAreFailure(results)) {
    if (results->status != SL_STATUS_OK) {
      emberAfCorePrintln("Error: Scan complete handler returned 0x%X",
                         results->status);
      return;
    }
    sli_zigbee_af_network_steering_total_beacons = emberGetNumStoredBeacons();

    emberAfCorePrintln("%s scan complete. Beacons heard: %d",
                       PLUGIN_NAME,
                       sli_zigbee_af_network_steering_total_beacons);

    if (sli_zigbee_af_network_steering_total_beacons) {
      stateMachineRun();
    } else {
      switch (sli_zigbee_af_network_steering_state) {
        case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_INSTALL_CODE:
        case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_CENTRALIZED:
        case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_DISTRIBUTED:
        case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_USE_ALL_KEYS:
          cleanupAndStop(EMBER_NO_BEACONS);
          return;
          break;
        default:
          break;
      }

      sli_zigbee_af_network_steering_state = FIRST_SECONDARY_STATE;

      (void)scheduleScan(sli_zigbee_af_network_steering_secondary_channel_mask);

      return;
    }
  }
}

static EmberStatus goToNextState(void)
{
  sli_zigbee_af_network_steering_state++;

  // If there are no more states, return error
  if ((sli_zigbee_af_network_steering_state
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_USE_ALL_KEYS)
      || (sli_zigbee_af_network_steering_state
          == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_FINISHED)) {
    cleanupAndStop(EMBER_JOIN_FAILED);
    return EMBER_JOIN_FAILED;
  }

  // When we're on the final scan-primary-channels state,
  // EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_DISTRIBUTED,
  // goToNextState simply increments sli_zigbee_af_network_steering_state and then we
  // call stateMachineRun. We take this opportunity to check if we need to scan
  // the secondary mask now
  if ((sli_zigbee_af_network_steering_state
       == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_INSTALL_CODE)
      || (sli_zigbee_af_network_steering_state
          == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_USE_ALL_KEYS)) {
    if (sli_zigbee_af_network_steering_secondary_channel_mask == 0) {
      cleanupAndStop(EMBER_JOIN_FAILED);
      return EMBER_JOIN_FAILED;
    }

    (void)scheduleScan(sli_zigbee_af_network_steering_secondary_channel_mask);

    // We need to return any error code, so that the code that called this
    // function doesn't continue doing its routine
    return EMBER_MAC_SCANNING;
  }

  return EMBER_SUCCESS;
}

static void cleanupAndStop(EmberStatus status)
{
  emberAfCorePrintln("%p Stop.  Cleaning up.", PLUGIN_NAME);
  emberAfPluginNetworkSteeringCompleteCallback(status,
                                               sli_zigbee_af_network_steering_total_beacons,
                                               sli_zigbee_af_network_steering_join_attempts,
                                               sli_zigbee_af_network_steering_state);
  sli_zigbee_af_network_steering_state = EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE;
  sli_zigbee_af_network_steering_join_attempts = 0;
  sli_zigbee_af_network_steering_total_beacons = 0;
  sl_zigbee_event_set_inactive(finishSteeringEvent);
}

// This function is called only on state transitions. This function sets up
// security, configures parameters, and then makes a call to start joining
// networks
static void stateMachineRun(void)
{
  EmberStatus status;
  emberAfCorePrintln("%p State: %p",
                     PLUGIN_NAME,
                     sli_zigbee_af_network_steering_stateNames[sli_zigbee_af_network_steering_state]);

  status = setupSecurity();

  while (status != EMBER_SUCCESS) {
    emberAfCorePrintln("Error: %p could not setup security: 0x%X",
                       PLUGIN_NAME,
                       status);

    status = goToNextState();
    if (status != EMBER_SUCCESS) {
      return;
    }

    status = setupSecurity();
  }

  // Set CURRENT_CHANNEL_MASK properly so that we can iterate over beacons
  // correctly
  switch (sli_zigbee_af_network_steering_state) {
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_INSTALL_CODE:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_CENTRALIZED:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_DISTRIBUTED:
    case EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_USE_ALL_KEYS:
      CURRENT_CHANNEL_MASK = sli_zigbee_af_network_steering_primary_channel_mask;
      break;
    default:
      CURRENT_CHANNEL_MASK = sli_zigbee_af_network_steering_secondary_channel_mask;
      break;
  }

  // Clear our stored beacon so we can iterate from the start
  status = emberGetFirstBeacon(&BEACON_ITERATOR);

  if (status != EMBER_SUCCESS) {
    cleanupAndStop(EMBER_ERR_FATAL);
    return;
  }

  tryToJoinNetwork();
}

static EmberStatus setupSecurity(void)
{
  EmberStatus status;
  EmberInitialSecurityState state;
  EmberExtendedSecurityBitmask extended;
  bool tryAllKeys = ((sli_zigbee_af_network_steering_state
                      == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_PRIMARY_USE_ALL_KEYS)
                     || (sli_zigbee_af_network_steering_state
                         == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_SCAN_SECONDARY_USE_ALL_KEYS));

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
          (sli_zigbee_af_network_steering_state_uses_distributed_key()
           ? emberKeyContents(&emberPluginNetworkSteeringDistributedKey)
           : emberKeyContents(&defaultLinkKey)),
          EMBER_ENCRYPTION_KEY_SIZE);

  status = emberSetInitialSecurityState(&state);

  // If we're trying all keys and the install code wasn't burned, setting
  // security will fail with EMBER_SECURITY_CONFIGURATION_INVALID. As a
  // consequence, we ignore the install code key and try again
  if (status == EMBER_SECURITY_CONFIGURATION_INVALID) {
    if (tryAllKeys) {
      emberAfCorePrintln("%s: WARNING: emberSetInitialSecurityState failed. "
                         "Continuing without install code.",
                         sli_zigbee_af_network_steering_plugin_name);
      state.bitmask &= ((uint16_t) ~((uint16_t)EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE));
      status = emberSetInitialSecurityState(&state);
    } else {
      if (sli_zigbee_af_network_steering_state_uses_install_codes()) {
        emberAfCorePrintln("Error: install code setup failed. Is an install "
                           "code flashed onto the device?");
      }
    }
  }

  if (status != EMBER_SUCCESS) {
    goto done;
  }

  extended = (EMBER_JOINER_GLOBAL_LINK_KEY
              | EMBER_EXT_NO_FRAME_COUNTER_RESET);

  if ((status = emberSetExtendedSecurityBitmask(extended)) != EMBER_SUCCESS) {
    goto done;
  }

  sli_zigbee_af_clear_link_key_table();

  if (tryAllKeys) {
    EmberEUI64 wildcardEui = WILDCARD_EUI;

    // The install code derived key is handled by setting the
    // EMBER_GET_PRECONFIGURED_KEY_FROM_INSTALL_CODE bit above
    // Add the centralized and distributed keys into the transient key table
    sl_status_t import_status;
    import_status = sl_zb_sec_man_import_transient_key(wildcardEui,
                                                       (sl_zb_sec_man_key_t*)&defaultLinkKey);
    if (import_status == SL_STATUS_OK) {
      import_status = sl_zb_sec_man_import_transient_key(wildcardEui,
                                                         (sl_zb_sec_man_key_t*)&emberPluginNetworkSteeringDistributedKey);
    }
    status = ((import_status == SL_STATUS_OK) ? EMBER_SUCCESS : EMBER_NO_BUFFERS);
  }

  done:
  return status;
}

EmberStatus emberAfPluginNetworkSteeringStart(void)
{
  EmberStatus status = EMBER_INVALID_CALL;
  uint32_t channelsToScan;

  if ((0 == sli_zigbee_af_network_steering_primary_channel_mask)
      && (0 == sli_zigbee_af_network_steering_secondary_channel_mask)) {
    return EMBER_INVALID_CALL;
  }

  if (sli_zigbee_af_pro_is_current_network()
      && (sli_zigbee_af_network_steering_state
          == EMBER_AF_PLUGIN_NETWORK_STEERING_STATE_NONE)) {
    if (emberAfNetworkState() == EMBER_NO_NETWORK) {
      emberAfAddToCurrentAppTasksCallback(EMBER_AF_WAITING_FOR_TC_KEY_UPDATE);
      if (sli_zigbee_af_network_steering_primary_channel_mask) {
        sli_zigbee_af_network_steering_state = FIRST_PRIMARY_STATE;
        channelsToScan = sli_zigbee_af_network_steering_primary_channel_mask;
      } else {
        sli_zigbee_af_network_steering_state = FIRST_SECONDARY_STATE;
        channelsToScan = sli_zigbee_af_network_steering_secondary_channel_mask;
      }

      // Stop any previous trust center link key update.
      emberAfPluginUpdateTcLinkKeyStop();

      status = scheduleScan(channelsToScan);
    } else {
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
      // The test harness needs to set up the correct link key
      sl_zigbee_event_set_active(&emberAfPluginTestHarnessZ3OpenNetworkEvent);
#endif
      status = emberAfPermitJoin(EMBER_AF_PLUGIN_NETWORK_STEERING_COMMISSIONING_TIME_S,
                                 true); // Broadcast permit join?
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
                               true); // Broadcast permit join?
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
      {
        // If the trust center is pre-r21, then we don't update the link key.
        // If the key status is that the link key has been verified, then we
        // have successfully updated our trust center link key and we are done!
        sli_zigbee_af_network_steering_state_clear_verify_tclk();
        uint32_t ms = randomJitterMS();
        sl_zigbee_event_set_delay_ms(finishSteeringEvent, ms);
        break;
      }
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

void sli_zigbee_af_network_steering_cleanup(EmberStatus status)
{
  cleanupAndStop(status);
}

uint8_t sli_zigbee_af_network_steering_get_current_channel()
{
  return BEACON_ITERATOR.beacon.channel;
}

#endif //  OPTIMIZE_SCANS

//------------------------------------------------------------------------------
// Weak callback definitions.

WEAK(bool emberAfPluginNetworkSteeringGetDistributedKeyCallback(EmberKeyData * key))
{
  return false;
}

WEAK(EmberNodeType emberAfPluginNetworkSteeringGetNodeTypeCallback(EmberAfPluginNetworkSteeringJoiningState state))
{
  return ((sli_zigbee_af_current_zigbee_pro_network->nodeType == EMBER_COORDINATOR)
          ? EMBER_ROUTER
          : sli_zigbee_af_current_zigbee_pro_network->nodeType);
}
