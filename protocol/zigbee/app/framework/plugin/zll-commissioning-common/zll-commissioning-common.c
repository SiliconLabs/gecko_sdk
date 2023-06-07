/***************************************************************************//**
 * @file
 * @brief Routines for the ZLL Commissioning Common plugin, which defines
 *        functions common to both server and client sides of the ZLL protocol.
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
#include "zll-commissioning-common.h"

// The code below assumes that there is exactly one network and that it is
// ZigBee PRO.
#if EMBER_SUPPORTED_NETWORKS != 1
  #error ZLL is not supported with multiple networks.
#endif

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_NETWORK_CREATOR_PRESENT
#define NETWORK_CREATOR_PRESENT
#include "network-creator.h"
#endif
#ifdef SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_CLIENT_PRESENT
#include "zll-commissioning-client-config.h"
#define ZLL_COMMISSIONING_CLIENT_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_ZLL_COMMISSIONING_SERVER_PRESENT
#define ZLL_COMMISSIONING_SERVER_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
#define TEST_HARNESS_Z3_PRESENT
#endif

//------------------------------------------------------------------------------
// Globals

#define isFactoryNew(state) ((state) & EMBER_ZLL_STATE_FACTORY_NEW)

// The target network - used by both client and server sides, the latter mainly for
// the touchlink complete callback to the application.
EmberZllNetwork sli_zigbee_af_zll_network;

#ifdef ZLL_COMMISSIONING_CLIENT_PRESENT
// Sub-device info (mainly for client, but server needs to initialize the count)
EmberZllDeviceInfoRecord sli_zigbee_af_zll_sub_devices[EMBER_AF_PLUGIN_ZLL_COMMISSIONING_CLIENT_SUB_DEVICE_TABLE_SIZE];
uint8_t sli_zigbee_af_zll_sub_device_count = 0;
#endif // ZLL_COMMISSIONING_CLIENT_PRESENT

// The module state for both client and server.
uint16_t sli_zigbee_af_zll_flags = INITIAL;

// TL Rejoin stage allows a fixed number of retries (in case Beacon responses are missing).
#define INITIATOR_REJOIN_MAX_RETRIES   4
uint8_t sli_zigbee_af_initiatorRejoinRetryCount = 0;

#ifdef PLUGIN_DEBUG
static const uint8_t sli_zigbee_af_zll_commissioning_plugin_name[] = "ZLL Commissioning Common";
#define PLUGIN_NAME sli_zigbee_af_zll_commissioning_plugin_name
#endif

#ifdef TEST_HARNESS_Z3_PRESENT
extern EmberEvent sli_zigbee_leave_event;
#endif

// Private ZLL commissioning functions
void sli_zigbee_af_zll_finish_network_formation_for_router(EmberStatus status);
void sli_zigbee_af_zll_abort_touch_link(EmberAfZllCommissioningStatus reason);
void sli_zigbee_af_zll_stack_status(EmberStatus status);
void sli_zigbee_af_zll_initialize_radio(void);
bool sli_zigbee_af_zll_stealing_allowed(void);
bool sli_zigbee_af_zll_remote_reset_allowed(void);

// Forward references
bool sli_zigbee_af_zll_am_factory_new(void);
#ifdef EZSP_HOST
void emberAfPluginZllCommissioningCommonNcpInitCallback(bool memoryAllocation);
#else
void emberAfPluginZllCommissioningCommonInitCallback(uint8_t init_level);
#endif

//------------------------------------------------------------------------------
// Module private functions

static void setProfileInteropState(void)
{
  EmberTokTypeStackZllData token;

  emberZllGetTokenStackZllData(&token);
  token.bitmask |= EMBER_ZLL_STATE_PROFILE_INTEROP;
  emberZllSetTokenStackZllData(&token);
}

static void initFactoryNew(void)
{
  // The initialization is only performed if we are factory new in the BDB sense,
  // i.e. not joined to a centralized or distributed network.
  if (sli_zigbee_af_zll_am_factory_new()) {
    emberAfAppPrintln("ZllCommInit - device is not joined to a network");

    // Set the default ZLL node type for both client and server, for Scan Request
    // and Scan Response messages respectively.
    emberSetZllNodeType((sli_zigbee_af_current_zigbee_pro_network->nodeType
                         == EMBER_COORDINATOR)
                        ? EMBER_ROUTER
                        : sli_zigbee_af_current_zigbee_pro_network->nodeType);

#ifdef ZLL_COMMISSIONING_SERVER_PRESENT
    sli_zigbee_af_zll_initialize_radio();
#endif

#ifdef ZLL_COMMISSIONING_CLIENT_PRESENT
    // Set the address assignment capability bit to true for a client in all cases.
    emberSetZllAdditionalState(EMBER_ZLL_STATE_ADDRESS_ASSIGNMENT_CAPABLE);
#endif

#ifdef ZIGBEE3_SUPPORT
    // Set interop bit here if we support Zigbee 3.0.
    setProfileInteropState();
#endif

    // Set the security state here, in case of incoming scan requests, to ensure
    // that our security key bitmask matches that of the initiator, or in case
    // we initiate a touchlink after joining by classical commissioning.
    emberAfZllSetInitialSecurityState();

    // Set the default power for a new network in all cases.
    emberSetRadioPower(EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_RADIO_TX_POWER);
  }
}

static void completeResetToFactoryNew(void)
{
  emberAfAppPrintln("Resetting to factory new");
  emberAfResetAttributes(EMBER_BROADCAST_ENDPOINT);
  emberAfGroupsClusterClearGroupTableCallback(EMBER_BROADCAST_ENDPOINT);
  emberAfScenesClusterClearSceneTableCallback(EMBER_BROADCAST_ENDPOINT);
  emberClearBindingTable();
#ifdef EZSP_HOST
  emberAfPluginZllCommissioningCommonNcpInitCallback(false);
#else
  // TODO: fix this once we port the init callback
  emberAfPluginZllCommissioningCommonInitCallback(SL_ZIGBEE_INIT_LEVEL_EVENT);
#endif
  emberAfPluginZllCommissioningCommonResetToFactoryNewCallback();
  sli_zigbee_af_zll_flags = INITIAL;
}

//------------------------------------------------------------------------------
// ZLL commissioning private functions

bool sli_zigbee_af_zll_am_factory_new(void)
{
  EmberTokTypeStackZllData token;
  emberZllGetTokenStackZllData(&token);
  return isFactoryNew(token.bitmask);
}

void sli_zigbee_af_zll_touch_link_complete(void)
{
  EmberNodeType nodeType;
  EmberNetworkParameters parameters;
  emberAfGetNetworkParameters(&nodeType, &parameters);
  sli_zigbee_af_zll_network.zigbeeNetwork.channel = parameters.radioChannel;
  sli_zigbee_af_zll_network.zigbeeNetwork.panId = parameters.panId;
  MEMMOVE(sli_zigbee_af_zll_network.zigbeeNetwork.extendedPanId,
          parameters.extendedPanId,
          EXTENDED_PAN_ID_SIZE);
  sli_zigbee_af_zll_network.zigbeeNetwork.nwkUpdateId = parameters.nwkUpdateId;
#ifdef ZLL_COMMISSIONING_CLIENT_PRESENT
  emberAfPluginZllCommissioningCommonTouchLinkCompleteCallback(&sli_zigbee_af_zll_network,
                                                               sli_zigbee_af_zll_sub_device_count,
                                                               (sli_zigbee_af_zll_sub_device_count == 0
                                                                ? NULL
                                                                : sli_zigbee_af_zll_sub_devices));
#else
  emberAfPluginZllCommissioningCommonTouchLinkCompleteCallback(&sli_zigbee_af_zll_network, 0, NULL);
#endif // ZLL_COMMISSIONING_CLIENT_PRESENT

  // Update module state after the callback call.
  sli_zigbee_af_zll_flags = INITIAL;
}

EmberNodeType sli_zigbee_af_zll_get_logical_node_type(void)
{
  EmberNodeType nodeType;
  EmberStatus status = emberAfGetNodeType(&nodeType);

  // Note, we only report as a coordinator if we are a currently
  // coordinator on a centralized network.
  if (status == EMBER_NOT_JOINED) {
    nodeType = sli_zigbee_af_current_zigbee_pro_network->nodeType;
    if (nodeType == EMBER_COORDINATOR) {
      nodeType = EMBER_ROUTER;
    }
  }
  return nodeType;
}

// The following function is not required during standard touchlink commissioning,
// but is retained to support the following CLI command (which may be used
// either client or server side), in particular for ZTT/ZUTH:
//   plugin zll-commissioning form
// Note that it WILL now result in a 'ZLL' distributed network being created, i.e.,
// a network appropriate to a address-assignment-capable touchlink initiator,
// with address and group ranges assigned to it.
EmberStatus sli_zigbee_af_zll_form_network(uint8_t channel, int8_t power, EmberPanId panId)
{
  // Create a distributed commissioning network using the ZLL link key.
  EmberZllNetwork network;
  MEMSET(&network, 0, sizeof(EmberZllNetwork));
  network.zigbeeNetwork.channel = channel;
  network.zigbeeNetwork.panId = panId;
  emberAfGetFormAndJoinExtendedPanIdCallback(network.zigbeeNetwork.extendedPanId);
  EmberTokTypeStackZllData token;
  emberZllGetTokenStackZllData(&token);
  network.state = token.bitmask & 0xffff;
  network.nodeType = sli_zigbee_af_zll_get_logical_node_type();
  emberAfZllSetInitialSecurityState();
  EmberStatus status = emberZllFormNetwork(&network, power);
  debugPrintln("%p: emberZllFormNetwork - status = %X, node type = %d", PLUGIN_NAME, status, network.nodeType);
  if (status == EMBER_SUCCESS) {
    sli_zigbee_af_zll_flags |= FORMING_NETWORK;
  }
  return status;
}

EmberZllPolicy sli_zigbee_af_zll_get_policy(void)
{
  EmberZllPolicy policy;
#ifdef EZSP_HOST
  if (ezspGetPolicy(EZSP_ZLL_POLICY, &policy) != EZSP_SUCCESS) {
    policy = EMBER_ZLL_POLICY_DISABLED;
  }
#else
  policy = emberZllGetPolicy();
#endif
  return policy;
}

//------------------------------------------------------------------------------
// Public functions

void emberAfPluginZllCommissioningCommonInitCallback(uint8_t init_level)
{
  (void)init_level;

#ifndef EZSP_HOST
  // Set the policy for both server and client.
  EmberZllPolicy policy = EMBER_ZLL_POLICY_ENABLED;
#ifdef ZLL_COMMISSIONING_SERVER_PRESENT
  policy |= EMBER_ZLL_POLICY_TARGET;
  if (sli_zigbee_af_zll_stealing_allowed()) {
    policy |= EMBER_ZLL_POLICY_STEALING_ENABLED;
  }
  if (sli_zigbee_af_zll_remote_reset_allowed()) {
    policy |= EMBER_ZLL_POLICY_REMOTE_RESET_ENABLED;
  }
#endif
  emberZllSetPolicy(policy);

  // Set the primary and secondary channel masks for both server and client.
  emberSetZllPrimaryChannelMask(EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_PRIMARY_CHANNEL_MASK);
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_SECONDARY_CHANNEL_MASK
  emberSetZllSecondaryChannelMask(EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_SECONDARY_CHANNEL_MASK);
#endif

  // Factory new initialization
  initFactoryNew();
#endif // #ifndef EZSP_HOST
}

void emberAfPluginZllCommissioningCommonNcpInitCallback(bool memoryAllocation)
{
#ifdef EZSP_HOST
  if (!memoryAllocation) {
    // Set the policy for both server and client.
    EmberZllPolicy policy = EMBER_ZLL_POLICY_ENABLED;
#ifdef ZLL_COMMISSIONING_SERVER_PRESENT
    policy |= EMBER_ZLL_POLICY_TARGET;
    if (sli_zigbee_af_zll_stealing_allowed()) {
      policy |= EMBER_ZLL_POLICY_STEALING_ENABLED;
    }
    if (sli_zigbee_af_zll_remote_reset_allowed()) {
      policy |= EMBER_ZLL_POLICY_REMOTE_RESET_ENABLED;
    }
#endif
    emberAfSetEzspPolicy(EZSP_ZLL_POLICY,
                         policy,
                         "ZLL policy",
                         "enable");

    // Set the primary and secondary channel masks for both server and client.
    emberSetZllPrimaryChannelMask(EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_PRIMARY_CHANNEL_MASK);
#ifdef EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_SECONDARY_CHANNEL_MASK
    emberSetZllSecondaryChannelMask(EMBER_AF_PLUGIN_ZLL_COMMISSIONING_COMMON_SECONDARY_CHANNEL_MASK);
#endif

    // Factory new initialization
    initFactoryNew();
  }
#endif // #ifdef EZSP_HOST
}

EmberStatus emberAfZllSetInitialSecurityState(void)
{
  EmberKeyData networkKey;
  EmberZllInitialSecurityState securityState = {
    0, // bitmask - unused
    EMBER_ZLL_KEY_INDEX_CERTIFICATION,
    EMBER_ZLL_CERTIFICATION_ENCRYPTION_KEY,
    EMBER_ZLL_CERTIFICATION_PRECONFIGURED_LINK_KEY,
  };
  EmberStatus status;

  // We can only initialize security information while not on a network - this
  // also covers the case where we are joined as a coordinator.
  if (emberAfNetworkState() != EMBER_NO_NETWORK) {
    return EMBER_SUCCESS;
  }

  status = emberAfGenerateRandomKey(&networkKey);
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p%p failed 0x%x",
                      "Error: ",
                      "Generating random key",
                      status);
    return status;
  }

  emberAfPluginZllCommissioningCommonInitialSecurityStateCallback(&securityState);
  status = emberZllSetInitialSecurityState(&networkKey, &securityState);

  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("%p%p failed 0x%x",
                      "Error: ",
                      "Initializing security",
                      status);
  }
  return status;
}

void emberAfZllResetToFactoryNew(void)
{
  // The leave will cause the ZLL state to be set to 'factory new',
  // but after a short delay.
  sli_zigbee_af_zll_flags |= RESETTING_TO_FACTORY_NEW;

  debugPrintln("emberAfZllResetToFactoryNew - flags = %X, networkState = %X", sli_zigbee_af_zll_flags, emberNetworkState());

  // Note that we won't get a network down stack status if we
  // are currently trying to join - the leave will complete silently.
  bool silentLeave = (emberNetworkState() == EMBER_JOINING_NETWORK) ? true : false;
  EmberStatus status = emberLeaveNetwork();
  if (status != EMBER_SUCCESS) {
    emberAfAppPrintln("Error: Failed to leave network, status: 0x%X", status);
  }

  // Complete the reset immediately if we're not expecting a network down status.
  if (silentLeave || status != EMBER_SUCCESS) {
    emberZllClearTokens();
    completeResetToFactoryNew();
  }
#ifdef TEST_HARNESS_Z3_PRESENT
  else if (status == EMBER_SUCCESS && !touchLinkTarget()) {
    // Complete the leave immediately without the usual delay for a local reset
    // (this is to accommodate ZTT scripts which issue a 'network leave'
    // which is immediately followed by a 'reset').
    emberEventSetActive(&sli_zigbee_leave_event);
  }
#endif
}

// TODO: renamed for naming consistency purposes
void sli_zigbee_af_zll_commissioning_common_stack_status_callback(EmberStatus status)
{
  // If we are forming a network for a router initiator, then we handle
  // this status separately.
  // During touch linking, EMBER_NETWORK_UP means the process is complete.  Any
  // other status, unless we're busy joining or rejoining, means that the touch
  // link failed.
  debugPrintln("%p: ZllCommStackStatus: status = %X, flags = %X", PLUGIN_NAME, status, sli_zigbee_af_zll_flags);

#if defined(ZLL_COMMISSIONING_CLIENT_PRESENT) && defined(NETWORK_CREATOR_PRESENT)
  if (formingNetwork()) {
    sli_zigbee_af_zll_finish_network_formation_for_router(status);
  } else
#endif

  if (resettingToFactoryNew()) { // either local or remote (TOUCH_LINK_TARGET set)
    // A reset overrides a touchlink in progress.
    if (status == EMBER_NETWORK_DOWN) {
      completeResetToFactoryNew();
    }
  } else if (touchLinkInProgress()) { // including TOUCH_LINK_TARGET
    if (status == EMBER_NETWORK_UP) {
      sli_zigbee_af_zll_touch_link_complete();
    } else if (status == EMBER_NETWORK_DOWN) {
      // We don't do anything here for a network down.
    } else {
      emberAfAppPrintln("%p%p%p: status = %X, flags = %X",
                        "Error: ",
                        "Touch linking failed: ",
                        "joining failed",
                        status, sli_zigbee_af_zll_flags);
#ifdef ZLL_COMMISSIONING_CLIENT_PRESENT
      if (!touchLinkTarget()) {
        if ((emberAfNetworkState() == EMBER_JOINED_NETWORK_NO_PARENT)
            && (sli_zigbee_af_initiatorRejoinRetryCount < INITIATOR_REJOIN_MAX_RETRIES)) {
          // The TL initiator has joined the target's Pan but the final Rejoin
          // has failed (e.g. if the target fails to send a Beacon Response
          // during the rejoin).  We allow a number of Rejoin retries here.
          ++sli_zigbee_af_initiatorRejoinRetryCount;
          emberRejoinNetwork(true);
        } else {
          sli_zigbee_af_zll_abort_touch_link(EMBER_AF_ZLL_JOINING_FAILED);
        }
      }
#endif
    }
  } else {
    // Here we catch all fresh non-ZLL network joins, and set the ZLL state accordingly.
    EmberTokTypeStackZllData token;
    emberZllGetTokenStackZllData(&token);

    if (status == EMBER_NETWORK_UP && (token.bitmask & EMBER_ZLL_STATE_FACTORY_NEW)) {
      // When either a router or an end device joins a non-ZLL network, it is
      // no longer factory new.  On a non-ZLL network, ZLL devices that are
      // normally address assignment capable do not have free network or group
      // addresses nor do they have a range of group addresses for themselves.
      // (Note, to ensure that ZLL devices will always operate as ZigBee 3.0 applications,
      // we need to set the ZLL profile interop bit even when the application
      // joins a classical ZigBee network. This way, if the device is stolen from
      // a classical ZigBee network to a ZLL network, it will operate as a
      // ZigBee 3.0 device. This is now set at plugin initialization time.)
      token.bitmask &= ~EMBER_ZLL_STATE_FACTORY_NEW;
      token.freeNodeIdMin = token.freeNodeIdMax = EMBER_ZLL_NULL_NODE_ID;
      token.myGroupIdMin = EMBER_ZLL_NULL_GROUP_ID;
      token.freeGroupIdMin = token.freeGroupIdMax = EMBER_ZLL_NULL_GROUP_ID;
      emberZllSetTokenStackZllData(&token);
      emberZllSetNonZllNetwork();
    }
    // Otherwise, we just ignore the status, for example, a network up
    // from a rejoin or a join at startup.
  }
}

bool emberAfZllTouchLinkInProgress(void)
{
  // Returns true if a touch link is in progress or false otherwise.

  return touchLinkInProgress();
}

// Note, this will cause *all* touchlink interpan messages to be dropped,
// not just touchlink requests, so it will effectively disable touchlink
// initiator, as well as touchlink target.
EmberStatus emberAfZllDisable(void)
{
  EmberZllPolicy policy = sli_zigbee_af_zll_get_policy();
  EmberStatus status;
#ifndef EZSP_HOST
  status = emberZllSetPolicy(policy & ~EMBER_ZLL_POLICY_ENABLED);
#else
  status = emberAfSetEzspPolicy(EZSP_ZLL_POLICY,
                                policy & ~EMBER_ZLL_POLICY_ENABLED,
                                "ZLL processing",
                                "disable");
#endif
  return status;
}

EmberStatus emberAfZllEnable(void)
{
  EmberZllPolicy policy = sli_zigbee_af_zll_get_policy();
  EmberStatus status;

  // Re-enable stealing and remote reset, if we have server-side, and the plugin option permits it.
  policy |= EMBER_ZLL_POLICY_ENABLED;
#ifdef ZLL_COMMISSIONING_SERVER_PRESENT
  if (sli_zigbee_af_zll_stealing_allowed()) {
    policy |= EMBER_ZLL_POLICY_STEALING_ENABLED;
  }
  if (sli_zigbee_af_zll_remote_reset_allowed()) {
    policy |= EMBER_ZLL_POLICY_REMOTE_RESET_ENABLED;
  }
#endif
#ifndef EZSP_HOST
  status = emberZllSetPolicy(policy);
#else
  status = emberAfSetEzspPolicy(EZSP_ZLL_POLICY,
                                policy,
                                "ZLL processing",
                                "enable");
#endif
  return status;
}
