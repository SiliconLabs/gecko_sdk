/***************************************************************************//**
 * @file af-host.c
 * @brief Host-specific APIs and infrastructure code.
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
#include "micro.h"
#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif

#include "app/framework/util/af-main.h"
#include "app/framework/util/common.h"
#include "app/framework/util/attribute-storage.h"
#include "app/framework/security/crypto-state.h"
#include "zigbee_host_callback_dispatcher.h"

// ZDO - ZigBee Device Object
#include "app/util/zigbee-framework/zigbee-device-common.h"
#include "app/util/zigbee-framework/zigbee-device-host.h"

#include "app/framework/plugin/zcl-framework-core/zcl-framework-core.h"

#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
#include "app/framework/plugin/fragmentation/fragmentation.h"
#endif // SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT

#define MAX_CLUSTER (EZSP_MAX_FRAME_LENGTH) / 2 //currently == 94
#define UNKNOWN_NETWORK_STATE 0xFF

// This is used to store the local EUI of the NCP when using
// fake certificates.
// Fake certificates are constructed by setting the data to all F's
// but using the device's real IEEE in the cert.  The Key establishment
// code requires access to the local IEEE to do this.
EmberEUI64 sli_802154mac_local_eui64;

// the stack version that the NCP is running
static uint16_t ncpStackVer;
static uint32_t ezsp_error_queue_full_counter = 0;
// We only get the sender EUI callback when the sender EUI is in the incoming
// message. This keeps track of if the value in the variable is valid or not.
// This is set to VALID (true) when the callback happens and set to INVALID
// (false) at the end of IncomingMessageHandler.
static bool currentSenderEui64IsValid;
static EmberEUI64 currentSenderEui64;
static EmberNodeId currentSender = EMBER_NULL_NODE_ID;

static uint16_t cachedConfigIdValues[EZSP_CONFIG_ID_MAX + 1];
static bool cacheConfigIdValuesAllowed = false;
static bool ncpNeedsResetAndInit = false;
static uint8_t currentBindingIndex = EMBER_NULL_BINDING;
static uint8_t currentAddressIndex = EMBER_NULL_ADDRESS_TABLE_INDEX;
static uint8_t ezspSequenceNumber = 0;

typedef struct {
  EmberNodeId nodeId;
  EmberPanId  panId;
  EmberNetworkStatus networkState;
  uint8_t radioChannel;
} NetworkCache;
static NetworkCache networkCache[EMBER_SUPPORTED_NETWORKS];

//------------------------------------------------------------------------------
// Forward declarations
void sli_zigbee_af_reset_and_init_ncp(void);
static uint8_t getNcpConfigItem(EzspConfigId id);
static void createEndpoint(uint8_t endpointIndex);
static uint8_t ezspNextSequence(void);

//------------------------------------------------------------------------------
// Internal callbacks

void sli_zigbee_af_initCallback(void)
{
  //Initialize the hal
  halInit();

  emberAfAppPrintln("Reset info: %d (%p)",
                    halGetResetInfo(),
                    halGetResetString());
  emberAfCoreFlush();

  // This will initialize the stack of networks maintained by the framework,
  // including setting the default network.
  sli_zigbee_af_initializeNetworkIndexStack();

  // We must initialize the endpoint information first so
  // that they are correctly added by sli_zigbee_af_reset_and_init_ncp()
  emberAfEndpointConfigure();

  // initialize the network co-processor (NCP)
  sli_zigbee_af_reset_and_init_ncp();
}

//------------------------------------------------------------------------------
// Public APIs

uint8_t emberAfGetAddressIndex(void)
{
  return currentAddressIndex;
}

uint8_t emberAfGetAddressTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_ADDRESS_TABLE_SIZE);
}

uint8_t emberAfGetBindingIndex(void)
{
  return currentBindingIndex;
}

uint8_t emberAfGetBindingTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_BINDING_TABLE_SIZE);
}

EmberStatus emberAfGetChildData(uint8_t index,
                                EmberChildData *childData)
{
  return ezspGetChildData(index, childData);
}

uint8_t emberAfGetChildTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_MAX_END_DEVICE_CHILDREN);
}

void emberAfGetMfgString(uint8_t* returnData)
{
  static uint8_t mfgString[MFG_STRING_MAX_LENGTH];
  static bool mfgStringRetrieved = false;

  if (mfgStringRetrieved == false) {
    ezspGetMfgToken(EZSP_MFG_STRING, mfgString);
    mfgStringRetrieved = true;
  }
  // NOTE:  The MFG string is not NULL terminated.
  MEMMOVE(returnData, mfgString, MFG_STRING_MAX_LENGTH);
}

// Platform dependent interface to get various stack parameters.
void emberAfGetEui64(EmberEUI64 returnEui64)
{
  MEMCOPY(returnEui64, sli_802154mac_local_eui64, EUI64_SIZE);
}

uint8_t emberAfGetKeyTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_KEY_TABLE_SIZE);
}

uint8_t emberAfGetNeighborTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_NEIGHBOR_TABLE_SIZE);
}

EmberStatus emberAfGetNetworkParameters(EmberNodeType* nodeType,
                                        EmberNetworkParameters* parameters)
{
  return ezspGetNetworkParameters(nodeType, parameters);
}

// Because an EZSP call can be expensive in terms of bandwidth,
// we cache the node ID so it can be quickly retrieved by the host.
EmberNodeId emberAfGetNodeId(void)
{
  uint8_t networkIndex = emberGetCurrentNetwork();
  if (networkCache[networkIndex].nodeId == EMBER_NULL_NODE_ID) {
    networkCache[networkIndex].nodeId = emberGetNodeId();
  }
  return networkCache[networkIndex].nodeId;
}

EmberStatus emberAfGetNodeType(EmberNodeType *nodeType)
{
  EmberNetworkParameters parameters;
  return ezspGetNetworkParameters(nodeType, &parameters);
}

uint8_t emberAfGetOpenNetworkDurationSec(void)
{
  uint8_t openTimeSec;
  uint8_t valueLength = 1;
  ezspGetValue(EZSP_VALUE_NWK_OPEN_DURATION,
               &valueLength,
               &openTimeSec);
  return openTimeSec;
}

EmberPanId emberAfGetPanId(void)
{
  uint8_t networkIndex = emberGetCurrentNetwork();
  if (networkCache[networkIndex].panId == 0xFFFF) {
    EmberNodeType nodeType;
    EmberNetworkParameters parameters;
    emberAfGetNetworkParameters(&nodeType, &parameters);
    networkCache[networkIndex].panId = parameters.panId;
  }
  return networkCache[networkIndex].panId;
}

uint8_t emberAfGetRadioChannel(void)
{
  uint8_t networkIndex = emberGetCurrentNetwork();
  if (networkCache[networkIndex].radioChannel == 0xFF) {
    EmberNodeType nodeType;
    EmberNetworkParameters parameters;
    emberAfGetNetworkParameters(&nodeType, &parameters);
    networkCache[networkIndex].radioChannel = parameters.radioChannel;
  }
  return networkCache[networkIndex].radioChannel;
}

uint8_t emberAfGetRouteTableSize(void)
{
  return getNcpConfigItem(EZSP_CONFIG_ROUTE_TABLE_SIZE);
}

uint8_t emberAfGetSecurityLevel(void)
{
  return getNcpConfigItem(EZSP_CONFIG_SECURITY_LEVEL);
}

uint8_t emberAfGetSleepyMulticastConfig(void)
{
  return getNcpConfigItem(EZSP_CONFIG_SEND_MULTICASTS_TO_SLEEPY_ADDRESS);
}

EmberStatus emberAfGetSourceRouteTableEntry(uint8_t index,
                                            EmberNodeId *destination,
                                            uint8_t *closerIndex)
{
  return ezspGetSourceRouteTableEntry(index,
                                      destination,
                                      closerIndex);
}

uint8_t emberAfGetSourceRouteTableFilledSize(void)
{
  return ezspGetSourceRouteTableFilledSize();
}

uint8_t emberAfGetSourceRouteTableTotalSize(void)
{
  return ezspGetSourceRouteTableTotalSize();
}

uint8_t emberAfGetStackProfile(void)
{
  return getNcpConfigItem(EZSP_CONFIG_STACK_PROFILE);
}

bool emberAfMemoryByteCompare(const uint8_t* pointer,
                              uint8_t count,
                              uint8_t byteValue)
{
  uint8_t i;
  for (i = 0; i < count; i++, pointer++) {
    if (*pointer != byteValue) {
      return false;
    }
  }
  return true;
}

// On the System-on-a-chip this function is provided by the stack.
// Here is a copy for the host based applications.
void emberReverseMemCopy(uint8_t* dest, const uint8_t* src, uint16_t length)
{
  uint16_t i;
  uint16_t j = (length - 1);

  for ( i = 0; i < length; i++) {
    dest[i] = src[j];
    j--;
  }
}

EmberNetworkStatus emberAfNetworkState(void)
{
  uint8_t networkIndex = emberGetCurrentNetwork();
  if (networkCache[networkIndex].networkState == UNKNOWN_NETWORK_STATE) {
    networkCache[networkIndex].networkState = emberNetworkState();
  }
  return networkCache[networkIndex].networkState;
}

EmberNodeId emberGetSender(void)
{
  return currentSender;
}

bool emberStackIsUp(void)
{
  EmberStatus status = emberNetworkState();
  return (status == EMBER_JOINED_NETWORK
          || status == EMBER_JOINED_NETWORK_NO_PARENT);
}

// this function sets an EZSP config value and
// prints out the results to the serial output
EzspStatus emberAfSetEzspConfigValue(EzspConfigId configId,
                                     uint16_t value,
                                     const char * configIdName)
{
  uint16_t old_value;
  // Some configuration values cannot be written past a certain point
  // Check to see if the old config value is the same as the new so it doesnt
  // print a bunch of errors when the host is restarted without the NCP undergoing a reset
  EzspStatus ezspStatus = ezspGetConfigurationValue(configId, &old_value);
  if (ezspStatus == EZSP_SUCCESS && old_value != value ) {
    ezspStatus = ezspSetConfigurationValue(configId, value);
  }
  emberAfAppFlush();
  emberAfAppPrint("Ezsp Config: set %p to 0x%2x:", configIdName, value);

  emberAfAppDebugExec(sli_zigbee_af_print_status("set", ezspStatus));
  emberAfAppFlush();

  emberAfAppPrintln("");
  emberAfAppFlush();

  // If this fails, odds are the simulated NCP doesn't have enough
  // memory allocated to it.
  // EZSP_ERROR_INVALID_ID status for unsupported configuration IDs on NCP such as
  // ZLL where not all NCPs need or support it.
  EMBER_TEST_ASSERT((ezspStatus == EZSP_SUCCESS) || (ezspStatus == EZSP_ERROR_INVALID_ID));
  return ezspStatus;
}

// this function sets an EZSP policy and
// prints out the results to the serial output
EzspStatus emberAfSetEzspPolicy(EzspPolicyId policyId,
                                EzspDecisionId decisionId,
                                const char * policyName,
                                const char * decisionName)
{
  EzspStatus ezspStatus = ezspSetPolicy(policyId,
                                        decisionId);
  emberAfAppPrint("Ezsp Policy: set %p to \"%p\":",
                  policyName,
                  decisionName);
  emberAfAppDebugExec(sli_zigbee_af_print_status("set",
                                                 ezspStatus));
  emberAfAppPrintln("");
  emberAfAppFlush();
  return ezspStatus;
}

// this function sets an EZSP value and
// prints out the results to the serial output
EzspStatus emberAfSetEzspValue(EzspValueId valueId,
                               uint8_t valueLength,
                               uint8_t *value,
                               const char * valueName)

{
  EzspStatus ezspStatus = ezspSetValue(valueId, valueLength, value);

  emberAfAppPrint("Ezsp Value : set %p to ", valueName);

  // print the value based on the length of the value
  // for length 1/2/4 bytes, fetch int of that length and promote to 32 bits for printing
  switch (valueLength) {
    case 1:
      emberAfAppPrint("0x%4x:", (uint32_t)(*value));
      break;
    case 2:
      emberAfAppPrint("0x%4x:", (uint32_t)(*((uint16_t *)value)));
      break;
    case 4:
      emberAfAppPrint("0x%4x:", (uint32_t)(*((uint32_t *)value)));
      break;
    default:
      emberAfAppPrint("{val of len %x}:", valueLength);
      break;
  }

  emberAfAppDebugExec(sli_zigbee_af_print_status("set", ezspStatus));
  emberAfAppPrintln("");
  emberAfAppFlush();
  return ezspStatus;
}

// This will cache all config items to make sure
// repeated calls do not go all the way to the NCP.
static uint8_t getNcpConfigItem(EzspConfigId id)
{
  // In case we can't cache config items yet, we need a temp
  // variable to store the retrieved EZSP config ID.
  uint16_t temp = 0xFFFF;
  uint16_t *configItemPtr = &temp;
  bool cacheValid;

  EMBER_TEST_ASSERT(id <= EZSP_CONFIG_ID_MAX);

  cacheValid = (cacheConfigIdValuesAllowed
                && id <= EZSP_CONFIG_ID_MAX);

  if (cacheValid) {
    configItemPtr = &(cachedConfigIdValues[id]);
  }

  if (*configItemPtr == 0xFFFF
      && EZSP_SUCCESS != ezspGetConfigurationValue(id, configItemPtr)) {
    // We return a 0 size (for tables) on error to prevent code from using the
    // invalid value of 0xFFFF.  This is particularly necessary for loops that
    // iterate over all indexes.
    return 0;
  }

  return (uint8_t)(*configItemPtr);
}

EmberStatus emberGetSenderEui64(EmberEUI64 senderEui64)
{
  // if the current sender EUI is valid then copy it in and send it back
  if (currentSenderEui64IsValid) {
    MEMMOVE(senderEui64, currentSenderEui64, EUI64_SIZE);
    return EMBER_SUCCESS;
  }
  // in the not valid case just return error
  return EMBER_ERR_FATAL;
}

bool emberAfNcpNeedsReset(void)
{
  return ncpNeedsResetAndInit;
}

//------------------------------------------------------------------------------
// Internal APIs

// initialize the network co-processor (NCP)
void sli_zigbee_af_reset_and_init_ncp(void)
{
  uint8_t ep;
  EzspStatus ezspStatus;
  uint16_t seed0, seed1;

  emberAfPreNcpResetCallback();

  // ezspInit resets the NCP by calling halNcpHardReset on a SPI host or
  // ashResetNcp on a UART host
  ezspStatus = ezspInit();

  if (ezspStatus != EZSP_SUCCESS) {
    emberAfCorePrintln("ERROR: ezspForceReset 0x%x", ezspStatus);
    emberAfCoreFlush();
    assert(false);
  }

  // send the version command before any other commands
  sli_zigbee_af_cli_version_command();

  // The random number generator on the host needs to be seeded with some
  // random data, which we can get from the NCP.
  ezspGetRandomNumber(&seed0);
  ezspGetRandomNumber(&seed1);
  halStackSeedRandom(((uint32_t)seed1 << 16) | (uint32_t)seed0);

  // set the address table size
  emberAfSetEzspConfigValue(EZSP_CONFIG_ADDRESS_TABLE_SIZE,
                            EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE,
                            "address table size");

  // set the trust center address cache size
  emberAfSetEzspConfigValue(EZSP_CONFIG_TRUST_CENTER_ADDRESS_CACHE_SIZE,
                            EMBER_AF_PLUGIN_ADDRESS_TABLE_TRUST_CENTER_CACHE_SIZE,
                            "TC addr cache");

  // BUG 14222: If stack profile is 2 (ZigBee Pro), we need to enforce
  // the standard stack configuration values for that feature set.
  if ( EMBER_STACK_PROFILE == 2 ) {
    // MAC indirect timeout should be 7.68 secs
    emberAfSetEzspConfigValue(EZSP_CONFIG_INDIRECT_TRANSMISSION_TIMEOUT,
                              7680,
                              "MAC indirect TX timeout");

    // Max hops should be 2 * nwkMaxDepth, where nwkMaxDepth is 15
    emberAfSetEzspConfigValue(EZSP_CONFIG_MAX_HOPS,
                              30,
                              "max hops");
  }

  emberAfSetEzspConfigValue(EZSP_CONFIG_TX_POWER_MODE,
                            EMBER_AF_TX_POWER_MODE,
                            "tx power mode");

  emberAfSetEzspConfigValue(EZSP_CONFIG_SUPPORTED_NETWORKS,
                            EMBER_SUPPORTED_NETWORKS,
                            "supported networks");
  sli_zigbee_af_network_security_init();

  uint8_t mode = EMBER_END_DEVICE_KEEP_ALIVE_SUPPORT_MODE;

  emberAfSetEzspValue(EZSP_VALUE_END_DEVICE_KEEP_ALIVE_SUPPORT_MODE,
                      1,       // value length
                      &mode,
                      "end device keep alive support mode");

  // allow other devices to modify the binding table
  emberAfSetEzspPolicy(EZSP_BINDING_MODIFICATION_POLICY,
                       EZSP_CHECK_BINDING_MODIFICATIONS_ARE_VALID_ENDPOINT_CLUSTERS,
                       "binding modify",
                       "allow for valid endpoints & clusters only");

  // return message tag and message contents in ezspMessageSentHandler()
  emberAfSetEzspPolicy(EZSP_MESSAGE_CONTENTS_IN_CALLBACK_POLICY,
                       EZSP_MESSAGE_TAG_AND_CONTENTS_IN_CALLBACK,
                       "message content in msgSent",
                       "return");

  {
    uint8_t value[2];
    value[0] = LOW_BYTE(EMBER_AF_INCOMING_BUFFER_LENGTH);
    value[1] = HIGH_BYTE(EMBER_AF_INCOMING_BUFFER_LENGTH);
    emberAfSetEzspValue(EZSP_VALUE_MAXIMUM_INCOMING_TRANSFER_SIZE,
                        2,     // value length
                        value,
                        "maximum incoming transfer size");
    value[0] = LOW_BYTE(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);
    value[1] = HIGH_BYTE(EMBER_AF_MAXIMUM_SEND_PAYLOAD_LENGTH);
    emberAfSetEzspValue(EZSP_VALUE_MAXIMUM_OUTGOING_TRANSFER_SIZE,
                        2,     // value length
                        value,
                        "maximum outgoing transfer size");

    value[0] = LOW_BYTE(SL_ZIGBEE_TRANSIENT_DEVICE_DEFAULT_TIMEOUT_MS);
    value[1] = HIGH_BYTE(SL_ZIGBEE_TRANSIENT_DEVICE_DEFAULT_TIMEOUT_MS);
    emberAfSetEzspValue(EZSP_VALUE_TRANSIENT_DEVICE_TIMEOUT,
                        2,
                        value,
                        "default timeout for transient device table");
  }

  // Set the manufacturing code. This is defined by ZigBee document 053874r10
  // Ember's ID is 0x1002 and is the default, but this can be overridden in App Builder.
  emberSetManufacturerCode(EMBER_AF_MANUFACTURER_CODE);

  sli_zb_af_ncp_init();
  emberAfNcpInitCallback();

#ifdef EMBER_AF_MAX_TOTAL_CLUSTER_COUNT
#if EMBER_AF_MAX_TOTAL_CLUSTER_COUNT > MAX_CLUSTER
#error "ERROR: too many clusters are enabled on some of the endpoints"
#endif
#endif //#ifdef EMBER_AF_MAX_TOTAL_CLUSTER_COUNT

  // create endpoints
  for ( ep = 0; ep < emberAfEndpointCount(); ep++ ) {
    EzspEndpointFlags flags;
    uint8_t endpoint = emberAfEndpointFromIndex(ep);;

    // check to see if ezspAddEndpoint needs to be called
    // if ezspInit is called without NCP reset, ezspAddEndpoint is not necessary and will return an error
    if ( ezspGetEndpointFlags(endpoint, &flags) != EZSP_SUCCESS ) {
      createEndpoint(ep);
    } else {
      emberAfAppPrintln("Ezsp Endpoint %d previously added", endpoint);
    }
  }

  MEMSET(cachedConfigIdValues, 0xFF, ((EZSP_CONFIG_ID_MAX + 1) * sizeof(uint16_t)));
  cacheConfigIdValuesAllowed = true;

  // Set the localEui64 global
  ezspGetEui64(sli_802154mac_local_eui64);

  // Initialize messageSentCallbacks table
  sli_zigbee_af_initialize_message_sent_callback_array();
}
#ifdef EZSP_CPC
extern bool in_ncp_reset(void);
#else
#define in_ncp_reset() false
#endif
void sli_zigbee_af_host_framework_tick(void)
{
  do {
    halResetWatchdog();   // Periodically reset the watchdog.

    // see if the NCP has anything waiting to send us
    ezspTick();

    while (ezspCallbackPending()) {
      ezspCallback();
    }

    // check if we have hit an EZSP Error and need to reset and init the NCP
    if (ncpNeedsResetAndInit || in_ncp_reset() ) {
      ncpNeedsResetAndInit = false;
      // re-initialize the NCP
      emberAfAppPrint("ezsp_error_queue_full_counter = 0x%0X\n", ezsp_error_queue_full_counter);
      ezsp_error_queue_full_counter = 0;
      sli_zigbee_af_reset_and_init_ncp();
      sli_zigbee_af_network_init(SL_ZIGBEE_INIT_LEVEL_DONE);
    }
    // Wait until ECC operations are done.  Don't allow any of the clusters
    // to send messages as the NCP is busy doing ECC
  } while (sli_zigbee_af_is_crypto_operation_in_progress());
}

void sli_zigbee_af_clear_network_cache(uint8_t networkIndex)
{
  networkCache[networkIndex].nodeId = EMBER_NULL_NODE_ID;
  networkCache[networkIndex].panId = 0xFFFF;
  networkCache[networkIndex].networkState = UNKNOWN_NETWORK_STATE;
  networkCache[networkIndex].radioChannel = 0xFF;
}

void sli_zigbee_af_cli_version_command(void)
{
  // If there was an ezsp error prior to this function call that leads to bad information
  // being read from the NCP, the host asserts (ncp stack type is not mesh, ezsp version mismatch, etc)

  // This is especially important for info command where there is a ton of information that is read and
  // while the ezsp error handler fires, the main loop needs to run again before the cause of the error handler
  // is actually addressed. However, the info command will finish executing and the host will assert before
  // the error handler fires, causing the host to crash

  if (ncpNeedsResetAndInit) {
    return;
  }

  // Note that NCP == Network Co-Processor
  EmberVersion versionStruct;

  // the EZSP protocol version that the NCP is using
  uint8_t ncpEzspProtocolVer;

  // the stackType that the NCP is running
  uint8_t ncpStackType;

  // the EZSP protocol version that the Host is running
  // we are the host so we set this value
  uint8_t hostEzspProtocolVer = EZSP_PROTOCOL_VERSION;

  // send the Host version number to the NCP. The NCP returns the EZSP
  // version that the NCP is running along with the stackType and stackVersion
  ncpEzspProtocolVer = ezspVersion(hostEzspProtocolVer,
                                   &ncpStackType,
                                   &ncpStackVer);

  // verify that the stack type is what is expected
  if (ncpStackType != EZSP_STACK_TYPE_MESH) {
    emberAfAppPrint("ERROR: stack type 0x%x is not expected!",
                    ncpStackType);
    assert(false);
  }

  // verify that the NCP EZSP Protocol version is what is expected
  if (ncpEzspProtocolVer != EZSP_PROTOCOL_VERSION) {
    emberAfAppPrint("ERROR: NCP EZSP protocol version of 0x%x does not match Host version 0x%x\r\n",
                    ncpEzspProtocolVer,
                    hostEzspProtocolVer);
    assert(false);
  }

  emberAfAppPrint("ezsp ver 0x%x stack type 0x%x ",
                  ncpEzspProtocolVer, ncpStackType, ncpStackVer);

  if (EZSP_SUCCESS != ezspGetVersionStruct(&versionStruct)) {
    // NCP has Old style version number
    emberAfAppPrintln("stack ver [0x%2x]", ncpStackVer);
  } else {
    // NCP has new style version number
    sli_zigbee_af_parse_and_print_version(versionStruct);
  }
  emberAfAppFlush();
}

uint8_t sli_zigbee_af_get_packet_buffer_free_count(void)
{
  uint8_t freeCount;
  uint8_t valueLength = 1;
  ezspGetValue(EZSP_VALUE_FREE_BUFFERS,
               &valueLength,
               &freeCount);
  return freeCount;
}

uint8_t sli_zigbee_af_get_packet_buffer_total_count(void)
{
  uint16_t value;
  ezspGetConfigurationValue(EZSP_CONFIG_PACKET_BUFFER_COUNT,
                            &value);
  return (uint8_t)value;
}

EmberStatus sli_zigbee_af_send(EmberOutgoingMessageType type,
                               uint16_t indexOrDestination,
                               EmberApsFrame *apsFrame,
                               uint8_t messageLength,
                               uint8_t *message,
                               uint16_t *messageTag,
                               EmberNodeId alias,
                               uint8_t sequence)
{
  EmberStatus status = EMBER_SUCCESS;
  *messageTag = ezspNextSequence();

  switch (type) {
    case EMBER_OUTGOING_VIA_BINDING:
    case EMBER_OUTGOING_VIA_ADDRESS_TABLE:
    case EMBER_OUTGOING_DIRECT:
    {
      status = ezspSendUnicast(type,
                               indexOrDestination,
                               apsFrame,
                               *messageTag,
                               (uint8_t)messageLength,
                               message,
                               &apsFrame->sequence);

      break;
    }
    case EMBER_OUTGOING_MULTICAST:
    {
      status = ezspSendMulticast(apsFrame,
                                 ZA_MAX_HOPS, // hops
                                 ZA_MAX_HOPS, // nonmember radius
                                 *messageTag,
                                 messageLength,
                                 message,
                                 &apsFrame->sequence);
      break;
    }
    case EMBER_OUTGOING_MULTICAST_WITH_ALIAS:
    {
      status = ezspSendMulticastWithAlias(apsFrame,
                                          apsFrame->radius,  //radius
                                          apsFrame->radius,  //nonmember radius
                                          alias,
                                          sequence,
                                          *messageTag,
                                          messageLength,
                                          message,
                                          &apsFrame->sequence);
      break;
    }
    case EMBER_OUTGOING_BROADCAST:
    {
      status = ezspSendBroadcast(indexOrDestination,
                                 apsFrame,
                                 ZA_MAX_HOPS, // radius
                                 *messageTag,
                                 messageLength,
                                 message,
                                 &apsFrame->sequence);
      break;
    }
    case EMBER_OUTGOING_BROADCAST_WITH_ALIAS:
      status = ezspProxyBroadcast(alias,
                                  indexOrDestination,
                                  sequence,
                                  apsFrame,
                                  apsFrame->radius,   // radius
                                  *messageTag,
                                  messageLength,
                                  message,
                                  &apsFrame->sequence);
      break;
    default:
      status = EMBER_BAD_ARGUMENT;
  }

  return status;
}

void sli_zigbee_af_print_ezsp_endpoint_flags(uint8_t endpoint)
{
  EzspEndpointFlags flags;
  EzspStatus status = ezspGetEndpointFlags(endpoint,
                                           &flags);
  if (status != EZSP_SUCCESS) {
    emberAfCorePrint("Error retrieving EZSP endpoint flags.");
  } else {
    emberAfCorePrint("- EZSP Endpoint flags: 0x%04X", flags);
  }
}

// WARNING:  This function executes in ISR context
void halNcpIsAwakeIsr(bool isAwake)
{
  if (isAwake) {
    emberAfNcpIsAwakeIsrCallback();
  } else {
    // If we got indication that the NCP failed to wake up
    // there is not much that can be done.  We will reset the
    // host (which in turn will reset the NCP) and that will
    // hopefully bring things back in sync.
    assert(0);
  }
}

//------------------------------------------------------------------------------
// Static functions

// Creates the endpoint for 260 by calling ezspAddEndpoint()
static void createEndpoint(uint8_t endpointIndex)
{
  uint16_t clusterList[MAX_CLUSTER];
  uint16_t *inClusterList;
  uint16_t *outClusterList;

  uint8_t endpoint = emberAfEndpointFromIndex(endpointIndex);

  //to cover the code path that gets here after unexpected NCP reset
  bool initiallyDisabled = !emberAfEndpointIsEnabled(endpoint);
  if (initiallyDisabled) {
    emberAfEndpointEnableDisable(endpoint, true);
  }

  uint8_t inClusterCount;
  uint8_t outClusterCount;

  {
    EmberStatus status = emberAfPushEndpointNetworkIndex(endpoint);
    if (status != EMBER_SUCCESS) {
      emberAfAppPrintln("Error in creating endpoint %d: 0x%x", endpoint, status);
      return;
    }
  }

  // Lay out clusters in the arrays.
  inClusterList = clusterList;
  inClusterCount = emberAfGetClustersFromEndpoint(endpoint, inClusterList, MAX_CLUSTER, true);

  outClusterList = clusterList + inClusterCount;
  outClusterCount = emberAfGetClustersFromEndpoint(endpoint, outClusterList, (MAX_CLUSTER - inClusterCount), false);

  // Call EZSP function with data.
  {
    EzspStatus status = ezspAddEndpoint(endpoint,
                                        emberAfProfileIdFromIndex(endpointIndex),
                                        emberAfDeviceIdFromIndex(endpointIndex),
                                        emberAfDeviceVersionFromIndex(endpointIndex),
                                        inClusterCount,
                                        outClusterCount,
                                        (uint16_t *)inClusterList,
                                        (uint16_t *)outClusterList);
    if (status == EZSP_SUCCESS) {
      //this is to sync the host and NCP, after an internal EZSP ERROR and NCP reset
      if (initiallyDisabled) {
        emberAfEndpointEnableDisable(endpoint, false);
      }
      emberAfAppPrintln("Ezsp Endpoint %d added, profile 0x%2x, in clusters: %d, out clusters %d",
                        endpoint,
                        emberAfProfileIdFromIndex(endpointIndex),
                        inClusterCount,
                        outClusterCount);
    } else {
      emberAfAppPrintln("Error in creating endpoint %d: 0x%x", endpoint, status);
    }
  }

  (void) emberAfPopNetworkIndex();
}

static uint8_t ezspNextSequence(void)
{
  return ((++ezspSequenceNumber) & EMBER_AF_MESSAGE_TAG_MASK);
}

//------------------------------------------------------------------------------
// EZSP Handlers

// This is called when an EZSP error is reported
void ezspErrorHandler(EzspStatus status)
{
  if ( status != EZSP_ERROR_QUEUE_FULL ) {
    emberAfCorePrintln("ERROR: ezspErrorHandler 0x%x", status);
  } else {
    ezsp_error_queue_full_counter++;
  }
  emberAfCoreFlush();

  ncpNeedsResetAndInit |= emberAfPluginZclFrameworkCoreEzspErrorCallback(status);
}

// This is not called if the incoming message
// did not contain the EUI64 of the sender.
void ezspIncomingSenderEui64Handler(EmberEUI64 senderEui64)
{
  // current sender is now valid
  MEMMOVE(currentSenderEui64, senderEui64, EUI64_SIZE);
  currentSenderEui64IsValid = true;
}

//------------------------------------------------------------------------------
// Stack Callbacks for Dispatcher

void sli_zigbee_af_incoming_message_callback(EmberIncomingMessageType type,
                                             EmberApsFrame *apsFrame,
                                             uint8_t lastHopLqi,
                                             int8_t lastHopRssi,
                                             EmberNodeId sender,
                                             uint8_t bindingIndex,
                                             uint8_t addressIndex,
                                             uint8_t messageLength,
                                             uint8_t *messageContents)
{
  uint8_t sourceRouteOverhead;
  (void) emberAfPushCallbackNetworkIndex();

  // The following code caches valid Source Route overheads sent pro actively
  // by the NCP and uses it once to calculate the overhead for a target, after
  // which it gets cleared.
  sourceRouteOverhead = getSourceRouteOverhead(messageLength);
  emberAfSetSourceRouteOverheadCallback(sender, sourceRouteOverhead);

  currentSender = sender;
  currentBindingIndex = bindingIndex;
  currentAddressIndex = addressIndex;
  sli_zigbee_af_incoming_message_handler(type,
                                         apsFrame,
                                         lastHopLqi,
                                         lastHopRssi,
                                         messageLength,
                                         messageContents);
  currentSenderEui64IsValid = false;
  currentSender = EMBER_NULL_NODE_ID;
  currentBindingIndex = EMBER_NULL_BINDING;
  currentAddressIndex = EMBER_NULL_ADDRESS_TABLE_INDEX;

  // Invalidate the sourceRouteOverhead cached at the end of the current incomingMessageHandler
  emberAfSetSourceRouteOverheadCallback(sender, EZSP_SOURCE_ROUTE_OVERHEAD_UNKNOWN);
  (void) emberAfPopNetworkIndex();
}

extern void sli_zigbee_af_message_sent(EmberOutgoingMessageType type,
                                       uint16_t indexOrDestination,
                                       EmberApsFrame *apsFrame,
                                       uint8_t messageTag,
                                       EmberStatus status,
                                       uint8_t messageLength,
                                       uint8_t *messageContents);

// Called when a message we sent is acked by the destination or when an
// ack fails to arrive after several retransmissions.
void sli_zigbee_af_message_sent_callback(EmberOutgoingMessageType type,
                                         uint16_t indexOrDestination,
                                         EmberApsFrame *apsFrame,
                                         uint8_t messageTag,
                                         EmberStatus status,
                                         uint8_t messageLength,
                                         uint8_t *messageContents)
{
#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
  // This call if returns true, ends up calling
  // sli_zigbee_af_fragmentation_message_sent_handler() when the last fragment was received.
  if (sli_zigbee_af_fragmentation_message_sent(apsFrame, status)) {
    return;
  }
#endif //SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT

  sli_zigbee_af_message_sent_handler(type,
                                     indexOrDestination,
                                     apsFrame,
                                     status,
                                     messageLength,
                                     messageContents,
                                     messageTag);

  // Generated dispatcher
  sli_zigbee_af_message_sent(type,
                             indexOrDestination,
                             apsFrame,
                             messageTag,
                             status,
                             messageLength,
                             messageContents);
}

#ifdef SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
void sli_zigbee_af_fragmentation_message_sent_handler(EmberOutgoingMessageType type,
                                                      uint16_t indexOrDestination,
                                                      EmberApsFrame *apsFrame,
                                                      uint8_t *buffer,
                                                      uint16_t bufLen,
                                                      EmberStatus status,
                                                      uint16_t messageTag)
{
  // the fragmented message is no longer in process
  emberAfDebugPrintln("%pend.", "Fragmentation:");

  sli_zigbee_af_message_sent_handler(type,
                                     indexOrDestination,
                                     apsFrame,
                                     status,
                                     bufLen,
                                     buffer,
                                     messageTag);

  // Generated dispatcher
  sli_zigbee_af_message_sent(type,
                             indexOrDestination,
                             apsFrame,
                             messageTag,
                             status,
                             bufLen,
                             buffer);

  // EMZIGBEE-4437: setting back the buffers to the original in case someone set
  // that to something else.
  emberAfSetExternalBuffer(appResponseData,
                           EMBER_AF_RESPONSE_BUFFER_LEN,
                           &appResponseLength,
                           &emberAfResponseApsFrame);
}
#endif // SL_CATALOG_ZIGBEE_FRAGMENTATION_PRESENT
