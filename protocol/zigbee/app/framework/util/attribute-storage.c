/***************************************************************************//**
 * @file
 * @brief Contains the per-endpoint configuration of attribute tables.
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
#include "attribute-storage.h"
#include "common.h"
#ifndef EMBER_SCRIPTED_TEST
#include "zigbee_zcl_callback_dispatcher.h"
#include "zigbee_af_cluster_functions.h"
#else
extern void sli_zigbee_af_reset_attributes(uint8_t endpointId);
#undef FIXED_ENDPOINT_COUNT
#define FIXED_ENDPOINT_COUNT (10)
#endif
//------------------------------------------------------------------------------
// Globals
// This is not declared CONST in order to handle dynamic endpoint information
// retrieved from tokens.
EmberAfDefinedEndpoint sli_zigbee_af_endpoints[MAX_ENDPOINT_COUNT];

#if (ATTRIBUTE_MAX_SIZE == 0)
#define ACTUAL_ATTRIBUTE_SIZE 1
#else
#define ACTUAL_ATTRIBUTE_SIZE ATTRIBUTE_MAX_SIZE
#endif

uint8_t attributeData[ACTUAL_ATTRIBUTE_SIZE];

#if (!defined(ATTRIBUTE_SINGLETONS_SIZE)) \
  || (ATTRIBUTE_SINGLETONS_SIZE == 0)
#define ACTUAL_SINGLETONS_SIZE 1
#else
#define ACTUAL_SINGLETONS_SIZE ATTRIBUTE_SINGLETONS_SIZE
#endif
uint8_t singletonAttributeData[ACTUAL_SINGLETONS_SIZE];

#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
uint8_t emberEndpointCount = 0;
#else // !SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#if defined(EMBER_AF_NCP) && defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT)
extern uint8_t emberNcpEndpointCount;
#ifdef emberEndpointCount
#undef emberEndpointCount
#endif // emberEndpointCount
#define emberEndpointCount emberNcpEndpointCount
#else // !(defined(EMBER_AF_NCP) && defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT))
extern uint8_t emberEndpointCount;
#endif // defined(EMBER_AF_NCP) && defined(SL_CATALOG_ZIGBEE_AF_SUPPORT_PRESENT)
#endif //SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT

// If we have attributes that are more than 2 bytes, then
// we need this data block for the defaults
#if (GENERATED_DEFAULTS_COUNT > 0)
const uint8_t generatedDefaults[]               = GENERATED_DEFAULTS;
#endif // GENERATED_DEFAULTS

#ifdef GENERATED_MIN_MAX_DEFAULTS
// App Builder does not define GENERATED_MIN_MAX_DEFAULT_COUNT, while
// zap does, but if the defined value is 0, it means GENERATED_MIN_MAX_DEFAULTS
// is empty and we should not define minMaxDefaults
#if !defined(GENERATED_MIN_MAX_DEFAULT_COUNT) || (GENERATED_MIN_MAX_DEFAULT_COUNT > 0)
const EmberAfAttributeMinMaxValue minMaxDefaults[]          = GENERATED_MIN_MAX_DEFAULTS;
#endif // !GENERATED_MIN_MAX_DEFAULTS || GENERATED_MIN_MAX_DEFAULTS > 0
#endif // GENERATED_MIN_MAX_DEFAULTS

#ifndef EMBER_SCRIPTED_TEST
const emberClusterFunctionStructure generatedClusterFunctions[] = GENERATED_FUNCTION_STRUCTURES_ARRAY;
#else
//unused?
const emberClusterFunctionStructure generatedClusterFunctions[1];
#endif

#ifdef EMBER_AF_SUPPORT_COMMAND_DISCOVERY
#if (EMBER_AF_GENERATED_COMMAND_COUNT > 0)
const EmberAfCommandMetadata generatedCommands[] = GENERATED_COMMANDS;
#endif // EMBER_AF_GENERATED_COMMAND_COUNT
#if (GENERATED_COMMAND_MANUFACTURER_CODE_COUNT > 0)
const EmberAfManufacturerCodeEntry commandManufacturerCodes[] = GENERATED_COMMAND_MANUFACTURER_CODES;
const uint16_t commandManufacturerCodeCount = GENERATED_COMMAND_MANUFACTURER_CODE_COUNT;
#endif // GENERATED_COMMAND_MANUFACTURER_CODE_COUNT
#endif // EMBER_AF_SUPPORT_COMMAND_DISCOVERY

const EmberAfAttributeMetadata generatedAttributes[] = GENERATED_ATTRIBUTES;
const EmberAfCluster generatedClusters[]          = GENERATED_CLUSTERS;
const EmberAfEndpointType generatedEmberAfEndpointTypes[]   = GENERATED_ENDPOINT_TYPES;

#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
sli_zigbee_af_zigbee_pro_network sli_zigbee_af_zigbee_pro_networks[] =
{ { SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE, SLI_ZIGBEE_PRIMARY_NETWORK_SECURITY_TYPE } };
#else
#ifndef EMBER_SCRIPTED_TEST
#ifdef SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#if (EMBER_SUPPORTED_NETWORKS == 1)
const sli_zigbee_af_zigbee_pro_network sli_zigbee_af_zigbee_pro_networks[] =
{ { SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE, SLI_ZIGBEE_PRIMARY_NETWORK_SECURITY_TYPE } };
#elif (EMBER_SUPPORTED_NETWORKS == 2)
const sli_zigbee_af_zigbee_pro_network sli_zigbee_af_zigbee_pro_networks[] =
{ { SLI_ZIGBEE_PRIMARY_NETWORK_DEVICE_TYPE, SLI_ZIGBEE_PRIMARY_NETWORK_SECURITY_TYPE },
  { SLI_ZIGBEE_SECONDARY_NETWORK_DEVICE_TYPE, SLI_ZIGBEE_SECONDARY_NETWORK_SECURITY_TYPE } };
#else
  #error "wrong network count"
#endif
#endif // SL_CATALOG_ZIGBEE_ZCL_FRAMEWORK_CORE_PRESENT
#else
const sli_zigbee_af_zigbee_pro_network sli_zigbee_af_zigbee_pro_networks[] = { EMBER_COORDINATOR, EMBER_AF_SECURITY_PROFILE_HA };
#endif
#endif
const EmberAfManufacturerCodeEntry clusterManufacturerCodes[] = GENERATED_CLUSTER_MANUFACTURER_CODES;
const uint16_t clusterManufacturerCodeCount = GENERATED_CLUSTER_MANUFACTURER_CODE_COUNT;
const EmberAfManufacturerCodeEntry attributeManufacturerCodes[] = GENERATED_ATTRIBUTE_MANUFACTURER_CODES;
const uint16_t attributeManufacturerCodeCount = GENERATED_ATTRIBUTE_MANUFACTURER_CODE_COUNT;

#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
// All generated clusters are enabled by default
static uint8_t clusterExtendedData[COUNTOF(generatedClusters)];
#define CLUSTER_MASK_DISABLED (0x01u)
#define CLUSTER_MASK_ENABLED  (0x00u)
#define emberAfClusterIsEnabled(clusterData) ((bool)((clusterData & CLUSTER_MASK_DISABLED) == 0))
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

#if !defined(EMBER_SCRIPTED_TEST)
#define endpointNumber(x)        fixedEndpoints[x]
#define endpointProfileId(x)     fixedProfileIds[x]
#define endpointDeviceId(x)      fixedDeviceIds[x]
#define endpointDeviceVersion(x) fixedDeviceVersions[x]
// Added 'Macro' to silence MISRA warning about conflict with synonymous vars.
#define endpointTypeMacro(x)     (EmberAfEndpointType*)&(generatedEmberAfEndpointTypes[fixedEmberAfEndpointTypes[x]])
#define endpointNetworkIndex(x)  fixedNetworks[x]
#else
#if !defined (__ATTRIBUTE_STORAGE_TEST__)
#define endpointNumber(index) (50 + index)
#define endpointTypeMacro(index) ((EmberAfEndpointType*)&(generatedEmberAfEndpointTypes[0]))
#define endpointNetworkIndex(index) (0)
#define endpointProfileId(index) (0xABBA)
#define endpointDeviceId(index) (0xBEEF)
#define endpointDeviceVersion(index) (0xBA)
#endif
#endif

//------------------------------------------------------------------------------
// Forward declarations

// Returns endpoint index within a given cluster
static uint8_t findClusterEndpointIndex(uint8_t endpoint, EmberAfClusterId clusterId, uint8_t mask, uint16_t manufacturerCode);

#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
// Returns cluster index in generatedClusters using given cluster
static uint8_t findClusterIdxInGeneratedList(EmberAfCluster *cluster);
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
//------------------------------------------------------------------------------

// Initial configuration
void emberAfEndpointConfigure(void)
{
  uint8_t ep;

#if !defined(EMBER_SCRIPTED_TEST)
  uint8_t fixedEndpoints[] = FIXED_ENDPOINT_ARRAY;
  uint16_t fixedProfileIds[] = FIXED_PROFILE_IDS;
  uint16_t fixedDeviceIds[] = FIXED_DEVICE_IDS;
  uint8_t fixedDeviceVersions[] = FIXED_DEVICE_VERSIONS;
  uint8_t fixedEmberAfEndpointTypes[] = FIXED_ENDPOINT_TYPES;
  uint8_t fixedNetworks[] = FIXED_NETWORKS;
#endif

  emberEndpointCount = MAX_ENDPOINT_COUNT;
  for ( ep = 0; ep < emberEndpointCount; ep++ ) {
    sli_zigbee_af_endpoints[ep].endpoint      = endpointNumber(ep);
    sli_zigbee_af_endpoints[ep].profileId     = endpointProfileId(ep);
    sli_zigbee_af_endpoints[ep].deviceId      = endpointDeviceId(ep);
    sli_zigbee_af_endpoints[ep].deviceVersion = endpointDeviceVersion(ep);
    sli_zigbee_af_endpoints[ep].endpointType  = endpointTypeMacro(ep);
    sli_zigbee_af_endpoints[ep].networkIndex  = endpointNetworkIndex(ep);
    sli_zigbee_af_endpoints[ep].bitmask = EMBER_AF_ENDPOINT_ENABLED;
  }
}

void emberAfSetEndpointCount(uint8_t dynamicEndpointCount)
{
  emberEndpointCount = FIXED_ENDPOINT_COUNT + dynamicEndpointCount;
}

uint8_t emberAfFixedEndpointCount(void)
{
  return FIXED_ENDPOINT_COUNT;
}

uint8_t emberAfEndpointCount(void)
{
  return emberEndpointCount;
}

bool emberAfEndpointIndexIsEnabled(uint8_t index)
{
  return (sli_zigbee_af_endpoints[index].bitmask & EMBER_AF_ENDPOINT_ENABLED);
}

// some data types (like strings) are sent OTA in human readable order
// (how they are read) instead of little endian as the data types are.
bool emberAfIsThisDataTypeAStringType(EmberAfAttributeType dataType)
{
  return (dataType == ZCL_OCTET_STRING_ATTRIBUTE_TYPE
          || dataType == ZCL_CHAR_STRING_ATTRIBUTE_TYPE
          || dataType == ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPE
          || dataType == ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE);
}

bool emberAfIsStringAttributeType(EmberAfAttributeType attributeType)
{
  return (attributeType == ZCL_OCTET_STRING_ATTRIBUTE_TYPE
          || attributeType == ZCL_CHAR_STRING_ATTRIBUTE_TYPE);
}

bool emberAfIsLongStringAttributeType(EmberAfAttributeType attributeType)
{
  return (attributeType == ZCL_LONG_OCTET_STRING_ATTRIBUTE_TYPE
          || attributeType == ZCL_LONG_CHAR_STRING_ATTRIBUTE_TYPE);
}

// This function is used to call the per-cluster default response callback
void emberAfClusterDefaultResponseWithMfgCodeCallback(uint8_t endpoint,
                                                      EmberAfClusterId clusterId,
                                                      uint8_t commandId,
                                                      EmberAfStatus status,
                                                      uint8_t clientServerMask,
                                                      uint16_t manufacturerCode)
{
  EmberAfCluster *cluster = emberAfFindClusterWithMfgCode(endpoint,
                                                          clusterId,
                                                          clientServerMask,
                                                          manufacturerCode);
  if (cluster != NULL) {
    EmberAfGenericClusterFunction f =
      emberAfFindClusterFunction(cluster,
                                 CLUSTER_MASK_DEFAULT_RESPONSE_FUNCTION);
    if (f != NULL) {
      emberAfPushEndpointNetworkIndex(endpoint);
      ((EmberAfDefaultResponseFunction)f)(endpoint, commandId, status);
      (void) emberAfPopNetworkIndex();
    }
  }
}

// This function is used to call the per-cluster default response callback, and
// wraps the emberAfClusterDefaultResponseWithMfgCodeCallback with a
// EMBER_AF_NULL_MANUFACTURER_CODE.
void emberAfClusterDefaultResponseCallback(uint8_t endpoint,
                                           EmberAfClusterId clusterId,
                                           uint8_t commandId,
                                           EmberAfStatus status,
                                           uint8_t clientServerMask)
{
  emberAfClusterDefaultResponseWithMfgCodeCallback(endpoint,
                                                   clusterId,
                                                   commandId,
                                                   status,
                                                   clientServerMask,
                                                   EMBER_AF_NULL_MANUFACTURER_CODE);
}

// This function is used to call the per-cluster message sent callback
void emberAfClusterMessageSentWithMfgCodeCallback(EmberOutgoingMessageType type,
                                                  uint16_t indexOrDestination,
                                                  EmberApsFrame *apsFrame,
                                                  uint16_t msgLen,
                                                  uint8_t *message,
                                                  EmberStatus status,
                                                  uint16_t mfgCode)
{
  if (apsFrame != NULL && message != NULL && msgLen != 0) {
    EmberAfCluster *cluster = emberAfFindClusterWithMfgCode(apsFrame->sourceEndpoint,
                                                            apsFrame->clusterId,
                                                            (((message[0]
                                                               & ZCL_FRAME_CONTROL_DIRECTION_MASK)
                                                              == ZCL_FRAME_CONTROL_SERVER_TO_CLIENT)
                                                             ? CLUSTER_MASK_SERVER
                                                             : CLUSTER_MASK_CLIENT),
                                                            mfgCode);
    if (cluster != NULL) {
      EmberAfGenericClusterFunction f =
        emberAfFindClusterFunction(cluster,
                                   CLUSTER_MASK_MESSAGE_SENT_FUNCTION);
      if (f != NULL) {
        emberAfPushEndpointNetworkIndex(apsFrame->sourceEndpoint);
        ((EmberAfMessageSentFunction)f)(type,
                                        indexOrDestination,
                                        apsFrame,
                                        msgLen,
                                        message,
                                        status);
        (void) emberAfPopNetworkIndex();
      }
    }
  }
}

// This function is used to call the per-cluster message sent callback, and
// wraps the emberAfClusterMessageSentWithMfgCodeCallback with a
// EMBER_AF_NULL_MANUFACTURER_CODE.
void emberAfClusterMessageSentCallback(EmberOutgoingMessageType type,
                                       uint16_t indexOrDestination,
                                       EmberApsFrame *apsFrame,
                                       uint16_t msgLen,
                                       uint8_t *message,
                                       EmberStatus status)
{
  emberAfClusterMessageSentWithMfgCodeCallback(type,
                                               indexOrDestination,
                                               apsFrame,
                                               msgLen,
                                               message,
                                               status,
                                               EMBER_AF_NULL_MANUFACTURER_CODE);
}

// This function is used to call the per-cluster attribute changed callback
void sli_zigbee_af_cluster_attribute_changed_callback(uint8_t endpoint,
                                                      EmberAfClusterId clusterId,
                                                      EmberAfAttributeId attributeId,
                                                      uint8_t clientServerMask,
                                                      uint16_t manufacturerCode)
{
  EmberAfCluster *cluster = emberAfFindClusterWithMfgCode(endpoint,
                                                          clusterId,
                                                          clientServerMask,
                                                          manufacturerCode);
  if (cluster != NULL) {
    if (manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE) {
      EmberAfGenericClusterFunction f =
        emberAfFindClusterFunction(cluster,
                                   CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION);
      if (f != NULL) {
        emberAfPushEndpointNetworkIndex(endpoint);
        ((EmberAfClusterAttributeChangedCallback)f)(endpoint, attributeId);
        (void) emberAfPopNetworkIndex();
      }
    } else {
      EmberAfGenericClusterFunction f =
        emberAfFindClusterFunction(cluster,
                                   CLUSTER_MASK_MANUFACTURER_SPECIFIC_ATTRIBUTE_CHANGED_FUNCTION);
      if (f != NULL) {
        emberAfPushEndpointNetworkIndex(endpoint);
        ((EmberAfManufacturerSpecificClusterAttributeChangedCallback)f)(endpoint,
                                                                        attributeId,
                                                                        manufacturerCode);
        (void) emberAfPopNetworkIndex();
      }
    }
  }
}

// This function is used to call the per-cluster pre-attribute changed callback
EmberAfStatus sli_zigbee_af_cluster_pre_attribute_changed_callback(uint8_t endpoint,
                                                                   EmberAfClusterId clusterId,
                                                                   EmberAfAttributeId attributeId,
                                                                   uint8_t clientServerMask,
                                                                   uint16_t manufacturerCode,
                                                                   EmberAfAttributeType attributeType,
                                                                   uint8_t size,
                                                                   uint8_t* value)
{
  EmberAfCluster *cluster = emberAfFindClusterWithMfgCode(endpoint,
                                                          clusterId,
                                                          clientServerMask,
                                                          manufacturerCode);
  if (cluster == NULL) {
    return EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE;
  } else {
    EmberAfStatus status = EMBER_ZCL_STATUS_SUCCESS;
    if (manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE) {
      EmberAfGenericClusterFunction f =
        emberAfFindClusterFunction(cluster,
                                   CLUSTER_MASK_PRE_ATTRIBUTE_CHANGED_FUNCTION);
      if (f != NULL) {
        emberAfPushEndpointNetworkIndex(endpoint);
        status = ((EmberAfClusterPreAttributeChangedCallback)f)(endpoint,
                                                                attributeId,
                                                                attributeType,
                                                                size,
                                                                value);
        (void) emberAfPopNetworkIndex();
      }
    }
    return status;
  }
}

static void initializeEndpoint(EmberAfDefinedEndpoint* definedEndpoint)
{
  uint8_t clusterIndex;
  EmberAfEndpointType* epType = definedEndpoint->endpointType;
  emberAfPushEndpointNetworkIndex(definedEndpoint->endpoint);
  for ( clusterIndex = 0;
        clusterIndex < epType->clusterCount;
        clusterIndex++ ) {
    EmberAfCluster *cluster = &(epType->cluster[clusterIndex]);
    EmberAfGenericClusterFunction f;
    emberAfClusterInitCallback(definedEndpoint->endpoint, cluster->clusterId);
    f = emberAfFindClusterFunction(cluster, CLUSTER_MASK_INIT_FUNCTION);
    if ( f != NULL ) {
      ((EmberAfInitFunction)f)(definedEndpoint->endpoint);
    }
  }
  (void) emberAfPopNetworkIndex();
}

// Calls the init functions.
void sli_zigbee_af_call_inits(void)
{
  uint8_t index;
  for ( index = 0; index < emberAfEndpointCount(); index++ ) {
    if (emberAfEndpointIndexIsEnabled(index)) {
      initializeEndpoint(&(sli_zigbee_af_endpoints[index]));
    }
  }
}

// Returns the pointer to metadata, or null if it is not found
EmberAfAttributeMetadata *emberAfLocateAttributeMetadata(uint8_t endpoint,
                                                         EmberAfClusterId clusterId,
                                                         EmberAfAttributeId attributeId,
                                                         uint8_t mask,
                                                         uint16_t manufacturerCode)
{
  EmberAfAttributeMetadata *metadata = NULL;
  EmberAfAttributeSearchRecord record;
  record.endpoint = endpoint;
  record.clusterId = clusterId;
  record.clusterMask = mask;
  record.attributeId = attributeId;
  record.manufacturerCode = manufacturerCode;
  sli_zigbee_af_read_or_write_attribute(&record,
                                        &metadata,
                                        NULL, // buffer
                                        0, // buffer size
                                        false); // write?
  return metadata;
}

static uint8_t* singletonAttributeLocation(EmberAfAttributeMetadata *am)
{
  EmberAfAttributeMetadata *m = (EmberAfAttributeMetadata *)&(generatedAttributes[0]);
  uint16_t index = 0;
  while ( m < am ) {
    if ((m->mask & ATTRIBUTE_MASK_SINGLETON) != 0U) {
      index += m->size;
    }
    m++;
  }
  return (uint8_t *)(singletonAttributeData + index);
}

// This function does mem copy, but smartly, which means that if the type is a
// string, it will copy as much as it can.
// If src == NULL, then this method will set memory to zeroes
static EmberAfStatus typeSensitiveMemCopy(uint8_t* dest,
                                          uint8_t* src,
                                          EmberAfAttributeMetadata * am,
                                          bool write,
                                          uint16_t attributeReadDestBufferSize)
{
  EmberAfAttributeType attributeType = am->attributeType;
  uint16_t size = (attributeReadDestBufferSize == 0) ? am->size : attributeReadDestBufferSize;

  // String attribute: Copy[Long]String function will manage string size appropriately.
  // Non-string attribute: limit set/move to attribute size as specified in attribute metadata.
  if (emberAfIsStringAttributeType(attributeType)) {
    emberAfCopyString(dest, src, size - 1);
  } else if (emberAfIsLongStringAttributeType(attributeType)) {
    emberAfCopyLongString(dest, src, size - 2);
  } else {
    if (!write && attributeReadDestBufferSize != 0 && attributeReadDestBufferSize < am->size) {
      return EMBER_ZCL_STATUS_INSUFFICIENT_SPACE;
    }
    if ( src == NULL ) {
      MEMSET(dest, 0, am->size);
    } else {
      MEMMOVE(dest, src, am->size);
    }
  }
  return EMBER_ZCL_STATUS_SUCCESS;
}

// Returns the manufacturer code or ::EMBER_AF_NULL_MANUFACTURER_CODE if none
// could be found.
static uint16_t getManufacturerCode(EmberAfManufacturerCodeEntry *codes,
                                    uint16_t codeTableSize,
                                    uint16_t tableIndex)
{
  uint16_t i;
  for (i = 0; i < codeTableSize; i++) {
    if (codes->index == tableIndex) {
      return codes->manufacturerCode;
    }
    codes++;
  }
  return EMBER_AF_NULL_MANUFACTURER_CODE;
}

// This function basically wraps getManufacturerCode with the parameters
// associating an attributes metadata with its code.
uint16_t emberAfGetMfgCode(EmberAfAttributeMetadata *metadata)
{
  return getManufacturerCode((EmberAfManufacturerCodeEntry *) attributeManufacturerCodes,
                             attributeManufacturerCodeCount,
                             (metadata - generatedAttributes));
}

uint16_t sli_zigbee_af_get_manufacturer_code_for_attribute(EmberAfCluster *cluster,
                                                           EmberAfAttributeMetadata *attMetaData)
{
  return (emberAfClusterIsManufacturerSpecific(cluster)
          ? sli_zigbee_af_get_manufacturer_code_for_cluster(cluster)
          : emberAfGetMfgCode(attMetaData));
}

uint16_t sli_zigbee_af_get_manufacturer_code_for_cluster(EmberAfCluster *cluster)
{
  return getManufacturerCode((EmberAfManufacturerCodeEntry *)clusterManufacturerCodes,
                             clusterManufacturerCodeCount,
                             (cluster - generatedClusters));
}

/**
 * @brief Matches a cluster based on cluster id, direction and manufacturer code.
 *   This function assumes that the passed cluster's endpoint already
 *   matches the endpoint of the EmberAfAttributeSearchRecord.
 *
 * Cluster's match if:
 *   1. Cluster ids match AND
 *   2. Cluster directions match as defined by cluster->mask
 *        and attRecord->clusterMask AND
 *   3. If the clusters are mf specific, their mfg codes match.
 */
bool sli_zigbee_af_match_cluster(EmberAfCluster *cluster,
                                 EmberAfAttributeSearchRecord *attRecord)
{
  return (cluster->clusterId == attRecord->clusterId
          && cluster->mask & attRecord->clusterMask
          && (!emberAfClusterIsManufacturerSpecific(cluster)
              || (sli_zigbee_af_get_manufacturer_code_for_cluster(cluster)
                  == attRecord->manufacturerCode)));
}

/**
 * @brief Matches an attribute based on attribute id and manufacturer code.
 *   This function assumes that the passed cluster already matches the
 *   clusterId, direction and mf specificity of the passed
 *   EmberAfAttributeSearchRecord.
 *
 * Note: If both the attribute and cluster are manufacturer specific,
 *   the cluster's mf code gets precedence.
 *
 * Attributes match if:
 *   1. Att ids match AND
 *      a. cluster IS mf specific OR
 *      b. both stored and saught attributes are NOT mf specific OR
 *      c. stored att IS mf specific AND mfg codes match.
 */
bool sli_zigbee_af_match_attribute(EmberAfCluster *cluster,
                                   EmberAfAttributeMetadata *am,
                                   EmberAfAttributeSearchRecord *attRecord)
{
  return (am->attributeId == attRecord->attributeId
          && (emberAfClusterIsManufacturerSpecific(cluster)
              || (sli_zigbee_af_get_manufacturer_code_for_attribute(cluster, am)
                  == attRecord->manufacturerCode)));
}

// When reading non-string attributes, this function returns an error when destination
// buffer isn't large enough to accommodate the attribute type.  For strings, the
// function will copy at most readLength bytes.  This means the resulting string
// may be truncated.  The length byte(s) in the resulting string will reflect
// any truncation.  If readLength is zero, we are working with backwards-
// compatibility wrapper functions and we just cross our fingers and hope for
// the best.
//
// When writing attributes, readLength is ignored.  For non-string attributes,
// this function assumes the source buffer is the same size as the attribute
// type.  For strings, the function will copy as many bytes as will fit in the
// attribute.  This means the resulting string may be truncated.  The length
// byte(s) in the resulting string will reflect any truncated.
EmberAfStatus sli_zigbee_af_read_or_write_attribute(EmberAfAttributeSearchRecord *attRecord,
                                                    EmberAfAttributeMetadata **metadata,
                                                    uint8_t *buffer,
                                                    uint16_t readLength,
                                                    bool write)
{
  uint8_t i;
  uint16_t attributeOffsetIndex = 0;

  for (i = 0; i < emberAfEndpointCount(); i++) {
    if (sli_zigbee_af_endpoints[i].endpoint == attRecord->endpoint) {
      EmberAfEndpointType *endpointType = sli_zigbee_af_endpoints[i].endpointType;
      uint8_t clusterIndex;
      if (!emberAfEndpointIndexIsEnabled(i)) {
        continue;
      }
      for (clusterIndex = 0;
           clusterIndex < endpointType->clusterCount;
           clusterIndex++) {
        EmberAfCluster *cluster = &(endpointType->cluster[clusterIndex]);
        if (sli_zigbee_af_match_cluster(cluster, attRecord)) { // Got the cluster
          uint16_t attrIndex;
          for (attrIndex = 0;
               attrIndex < cluster->attributeCount;
               attrIndex++) {
            EmberAfAttributeMetadata *am = &(cluster->attributes[attrIndex]);
            if (sli_zigbee_af_match_attribute(cluster,
                                              am,
                                              attRecord)) { // Got the attribute
              // If passed metadata location is not null, populate
              if (metadata != NULL) {
                *metadata = am;
              }

              {
                uint8_t *attributeLocation = (am->mask & ATTRIBUTE_MASK_SINGLETON
                                              ? singletonAttributeLocation(am)
                                              : attributeData + attributeOffsetIndex);
                uint8_t *src, *dst;
                if (write) {
                  src = buffer;
                  dst = attributeLocation;
                  if (!emberAfAttributeWriteAccessCallback(attRecord->endpoint,
                                                           attRecord->clusterId,
                                                           sli_zigbee_af_get_manufacturer_code_for_attribute(cluster, am),
                                                           am->attributeId)) {
                    return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
                  }
                } else {
                  if (buffer == NULL) {
                    return EMBER_ZCL_STATUS_SUCCESS;
                  }

                  src = attributeLocation;
                  dst = buffer;
                  if (!emberAfAttributeReadAccessCallback(attRecord->endpoint,
                                                          attRecord->clusterId,
                                                          sli_zigbee_af_get_manufacturer_code_for_attribute(cluster, am),
                                                          am->attributeId)) {
                    return EMBER_ZCL_STATUS_NOT_AUTHORIZED;
                  }
                }

                return (am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE
                        ? (write)
                        ? emberAfExternalAttributeWriteCallback(attRecord->endpoint,
                                                                attRecord->clusterId,
                                                                am,
                                                                sli_zigbee_af_get_manufacturer_code_for_attribute(cluster, am),
                                                                buffer)
                        : emberAfExternalAttributeReadCallback(attRecord->endpoint,
                                                               attRecord->clusterId,
                                                               am,
                                                               sli_zigbee_af_get_manufacturer_code_for_attribute(cluster, am),
                                                               buffer,
                                                               emberAfAttributeSize(am))
                        : typeSensitiveMemCopy(dst,
                                               src,
                                               am,
                                               write,
                                               readLength));
              }
            } else { // Not the attribute we are looking for
              // Increase the index if attribute is not externally stored
              if (!(am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE)
                  && !(am->mask & ATTRIBUTE_MASK_SINGLETON) ) {
                attributeOffsetIndex += emberAfAttributeSize(am);
              }
            }
          }
        } else { // Not the cluster we are looking for
          attributeOffsetIndex += cluster->clusterSize;
        }
      }
    } else { // Not the endpoint we are looking for
      attributeOffsetIndex += sli_zigbee_af_endpoints[i].endpointType->endpointSize;
    }
  }
  return EMBER_ZCL_STATUS_UNSUPPORTED_ATTRIBUTE; // Sorry, attribute was not found.
}

// Check if a cluster is implemented or not. If yes, the cluster is returned.
// If the cluster is not manufacturerSpecific [ClusterId < FC00] then
// manufacturerCode argument is ignored otherwise checked.
//
// mask = 0 -> find either client or server
// mask = CLUSTER_MASK_CLIENT -> find client
// mask = CLUSTER_MASK_SERVER -> find server
static EmberAfCluster *findClusterInTypeWithMfgCode(EmberAfEndpointType *endpointType,
                                                    EmberAfClusterId clusterId,
                                                    EmberAfClusterMask mask,
                                                    uint16_t manufacturerCode,
                                                    bool ignoreDisabledClusters)
{
  uint8_t i;
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
  uint8_t clusterIdx;
  uint8_t clusterData;
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

  for (i = 0; i < endpointType->clusterCount; i++) {
    EmberAfCluster *cluster = &(endpointType->cluster[i]);
    #if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
    #if !defined(EMBER_SCRIPTED_TEST)
    clusterIdx = findClusterIdxInGeneratedList(cluster);
    if (0xFF == clusterIdx) {
      // Invalid cluster
      continue;
    }

    clusterData = clusterExtendedData[clusterIdx];
    if (ignoreDisabledClusters == false || emberAfClusterIsEnabled(clusterData)) {
    #endif //EMBER_SCRIPTED_TEST
    #endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
    if (cluster->clusterId == clusterId
        && (mask == 0
            || (mask == CLUSTER_MASK_CLIENT && emberAfClusterIsClient(cluster))
            || (mask == CLUSTER_MASK_SERVER && emberAfClusterIsServer(cluster)))
        && (!emberAfClusterIsManufacturerSpecific(cluster)
            || (sli_zigbee_af_get_manufacturer_code_for_cluster(cluster)
                == manufacturerCode)
            // For compatibility with older stack api, we ignore manufacturer code here
            // if the manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE
            || manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE)) {
      return cluster;
    }
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
  }
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
  }
  return NULL;
}

EmberAfCluster *emberAfFindClusterInTypeWithMfgCode(EmberAfEndpointType *endpointType,
                                                    EmberAfClusterId clusterId,
                                                    EmberAfClusterMask mask,
                                                    uint16_t manufacturerCode)
{
  return findClusterInTypeWithMfgCode(endpointType,
                                      clusterId,
                                      mask,
                                      manufacturerCode,
                                      true // Skip disabled cluster
                                      );
}

// This functions wraps emberAfFindClusterInTypeWithMfgCode with
// a manufacturerCode of EMBER_AF_NULL_MANUFACTURER_CODE.
EmberAfCluster *emberAfFindClusterInType(EmberAfEndpointType *endpointType,
                                         EmberAfClusterId clusterId,
                                         EmberAfClusterMask mask)
{
  return emberAfFindClusterInTypeWithMfgCode(endpointType,
                                             clusterId,
                                             mask,
                                             EMBER_AF_NULL_MANUFACTURER_CODE);
}

// This code is used during unit tests for clusters that do not involve manufacturer code.
// Should this code be used in other locations, manufacturerCode should be added.
uint8_t emberAfClusterIndex(uint8_t endpoint,
                            EmberAfClusterId clusterId,
                            EmberAfClusterMask mask)
{
  uint8_t ep;
  uint8_t index = 0xFF;
  for ( ep = 0; ep < emberAfEndpointCount(); ep++ ) {
    EmberAfEndpointType *endpointType = sli_zigbee_af_endpoints[ep].endpointType;
    if ( emberAfFindClusterInTypeWithMfgCode(endpointType, clusterId, mask, EMBER_AF_NULL_MANUFACTURER_CODE) != NULL ) {
      index++;
      if ( sli_zigbee_af_endpoints[ep].endpoint == endpoint ) {
        return index;
      }
    }
  }
  return 0xFF;
}

// Returns true uf endpoint contains passed cluster
bool emberAfContainsClusterWithMfgCode(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, 0, manufacturerCode) != NULL);
}

// Returns true if endpoint contains passed cluster as a server
bool emberAfContainsServerWithMfgCode(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, CLUSTER_MASK_SERVER, manufacturerCode) != NULL);
}

// Returns true if endpoint contains passed cluster as a client
bool emberAfContainsClientWithMfgCode(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, CLUSTER_MASK_CLIENT, manufacturerCode) != NULL);
}

// Wraps emberAfContainsClusterWithMfgCode with EMBER_AF_NULL_MANUFACTURER_CODE
// This will find the first cluster that has the clusterId given, regardless of mfgCode.
bool emberAfContainsCluster(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, 0, EMBER_AF_NULL_MANUFACTURER_CODE) != NULL);
}

// Wraps emberAfContainsServerWithMfgCode with EMBER_AF_NULL_MANUFACTURER_CODE
// This will find the first server that has the clusterId given, regardless of mfgCode.
bool emberAfContainsServer(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, CLUSTER_MASK_SERVER, EMBER_AF_NULL_MANUFACTURER_CODE) != NULL);
}

// Wraps emberAfContainsClientWithMfgCode with EMBER_AF_NULL_MANUFACTURER_CODE
// This will find the first client that has the clusterId given, regardless of mfgCode.
bool emberAfContainsClient(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return (emberAfFindClusterWithMfgCode(endpoint, clusterId, CLUSTER_MASK_CLIENT, EMBER_AF_NULL_MANUFACTURER_CODE) != NULL);
}

// Finds the cluster that matches endpoint, clusterId, direction, and manufacturerCode.
EmberAfCluster *emberAfFindClusterWithMfgCode(uint8_t endpoint,
                                              EmberAfClusterId clusterId,
                                              EmberAfClusterMask mask,
                                              uint16_t manufacturerCode)
{
  uint8_t ep = emberAfIndexFromEndpoint(endpoint);
  if ((ep >= FIXED_ENDPOINT_COUNT) || ep == 0xFF ) {
    return NULL;
  } else {
    return emberAfFindClusterInTypeWithMfgCode(sli_zigbee_af_endpoints[ep].endpointType, clusterId, mask, manufacturerCode);
  }
}

// This function wraps emberAfFindClusterWithMfgCode with EMBER_AF_NULL_MANUFACTURER_CODE
// and will ignore the manufacturerCode when trying to find clusters.
// This will return the first cluster in the cluster table that matches the parameters given.
EmberAfCluster *emberAfFindCluster(uint8_t endpoint,
                                   EmberAfClusterId clusterId,
                                   EmberAfClusterMask mask)
{
  return emberAfFindClusterWithMfgCode(endpoint, clusterId, mask, EMBER_AF_NULL_MANUFACTURER_CODE);
}

// Returns cluster within the endpoint; Does not ignore disabled endpoints
EmberAfCluster *emberAfFindClusterIncludingDisabledEndpointsWithMfgCode(uint8_t endpoint,
                                                                        EmberAfClusterId clusterId,
                                                                        EmberAfClusterMask mask,
                                                                        uint16_t manufacturerCode)
{
#if (MAX_ENDPOINT_COUNT > 0)
  uint8_t ep = emberAfIndexFromEndpointIncludingDisabledEndpoints(endpoint);
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
  if (ep == 0xFF) {
    return NULL;
  }
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
  if (ep < MAX_ENDPOINT_COUNT) {
    return emberAfFindClusterInTypeWithMfgCode(sli_zigbee_af_endpoints[ep].endpointType, clusterId, mask, manufacturerCode);
  }
#endif // (MAX_ENDPOINT_COUNT > 0)
  return NULL;
}

// Returns cluster within the endpoint; Does not ignore disabled endpoints
// This will ignore manufacturerCode.
EmberAfCluster *emberAfFindClusterIncludingDisabledEndpoints(uint8_t endpoint,
                                                             EmberAfClusterId clusterId,
                                                             EmberAfClusterMask mask)
{
  return emberAfFindClusterIncludingDisabledEndpointsWithMfgCode(endpoint, clusterId, mask, EMBER_AF_NULL_MANUFACTURER_CODE);
}

// Server wrapper for findClusterEndpointIndex.
static uint8_t emberAfFindClusterServerEndpointIndexWithMfgCode(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode)
{
  return findClusterEndpointIndex(endpoint, clusterId, CLUSTER_MASK_SERVER, manufacturerCode);
}

// Client wrapper for findClusterEndpointIndex.
static uint8_t emberAfFindClusterClientEndpointIndexWithMfgCode(uint8_t endpoint, EmberAfClusterId clusterId, uint16_t manufacturerCode)
{
  return findClusterEndpointIndex(endpoint, clusterId, CLUSTER_MASK_CLIENT, manufacturerCode);
}

// Server wrapper for findClusterEndpointIndex
// This will ignore manufacturerCode, and return the index for the first server that matches on clusterId
uint8_t emberAfFindClusterServerEndpointIndex(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return emberAfFindClusterServerEndpointIndexWithMfgCode(endpoint, clusterId, EMBER_AF_NULL_MANUFACTURER_CODE);
}

// Client wrapper for findClusterEndpointIndex
// This will ignore manufacturerCode, and return the index for the first client that matches on clusterId
uint8_t emberAfFindClusterClientEndpointIndex(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return emberAfFindClusterClientEndpointIndexWithMfgCode(endpoint, clusterId, EMBER_AF_NULL_MANUFACTURER_CODE);
}

// Returns the endpoint index within a given cluster
static uint8_t findClusterEndpointIndex(uint8_t endpoint, EmberAfClusterId clusterId, uint8_t mask, uint16_t manufacturerCode)
{
  uint8_t i, epi = 0;

  if (emberAfFindClusterWithMfgCode(endpoint, clusterId, mask, manufacturerCode) == NULL) {
    return 0xFF;
  }

  for (i = 0; i < emberAfEndpointCount(); i++) {
    if (sli_zigbee_af_endpoints[i].endpoint == endpoint) {
      break;
    }
    epi += (emberAfFindClusterIncludingDisabledEndpointsWithMfgCode(sli_zigbee_af_endpoints[i].endpoint, clusterId, mask, manufacturerCode) != NULL) ? 1 : 0;
  }

  return epi;
}

#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
// Calculate cluster index in generatedClusters[].
// Returns 0xff if not found
static uint8_t findClusterIdxInGeneratedList(EmberAfCluster *cluster)
{
  if (cluster != NULL) {
    uint8_t clusterIdx;
    if (((uint32_t)cluster >= (uint32_t)generatedClusters)
        && ((uint32_t)cluster < (uint32_t)(generatedClusters) + sizeof(generatedClusters))) {
      clusterIdx = ((uint32_t)cluster - (uint32_t)generatedClusters) / sizeof(generatedClusters[0]);
      return clusterIdx;
    }
  }
  return 0xFF;
}

// Returns the cluster index in generatedClusters[] within a given {endpoint, cluster, mask, manuCode}
// Returns 0xff if not found
static uint8_t findClusterIdxInGeneratedListByEndpoint(uint8_t endpoint, EmberAfClusterId clusterId,
                                                       uint8_t mask, uint16_t manufacturerCode)
{
  uint8_t i;
  uint8_t epi = emberAfIndexFromEndpoint(endpoint);
  bool clusterFound;
  if ( epi != 0xFF ) {
    EmberAfEndpointType *endpointType = sli_zigbee_af_endpoints[epi].endpointType;
    uint8_t clusterCount = endpointType->clusterCount;
    EmberAfCluster *cluster = NULL;
    clusterFound = false;

    for (i = 0; i < clusterCount; i++) {
      cluster = &(endpointType->cluster[i]);
      // add mask (CLUSTER_MASK_DISABLED) for enabled cluster only
      if (cluster->clusterId == clusterId
          && (mask == 0
              || (mask == CLUSTER_MASK_CLIENT && emberAfClusterIsClient(cluster))
              || (mask == CLUSTER_MASK_SERVER && emberAfClusterIsServer(cluster)))
          && (!emberAfClusterIsManufacturerSpecific(cluster)
              || (sli_zigbee_af_get_manufacturer_code_for_cluster(cluster)
                  == manufacturerCode)
              // For compatibility with older stack api, we ignore manufacturer code here
              // if the manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE
              || manufacturerCode == EMBER_AF_NULL_MANUFACTURER_CODE)) {
        clusterFound = true;
        break;
      }
    }

    //calculate idx in generatedClusters[].
    if (clusterFound) {
      return findClusterIdxInGeneratedList(cluster);
    }
  }

  return 0xFF;
}
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

static uint8_t findIndexFromEndpoint(uint8_t endpoint, bool ignoreDisabledEndpoints)
{
  uint8_t epi;
  for (epi = 0; epi < emberAfEndpointCount(); epi++) {
    if (sli_zigbee_af_endpoints[epi].endpoint == endpoint
        && (!ignoreDisabledEndpoints
            || sli_zigbee_af_endpoints[epi].bitmask & EMBER_AF_ENDPOINT_ENABLED)) {
      return epi;
    }
  }
  return 0xFF;
}

bool emberAfEndpointIsEnabled(uint8_t endpoint)
{
  uint8_t index = findIndexFromEndpoint(endpoint,
                                        false);  // ignore disabled endpoints?

  EMBER_TEST_ASSERT(0xFF != index);

  if (0xFF == index) {
    return false;
  }

  return emberAfEndpointIndexIsEnabled(index);
}

bool emberAfEndpointEnableDisable(uint8_t endpoint, bool enable)
{
  uint8_t index = findIndexFromEndpoint(endpoint,
                                        false);  // ignore disabled endpoints?
  bool currentlyEnabled;

  if (0xFF == index) {
    return false;
  }

  currentlyEnabled = sli_zigbee_af_endpoints[index].bitmask & EMBER_AF_ENDPOINT_ENABLED;

  if (enable) {
    sli_zigbee_af_endpoints[index].bitmask |= EMBER_AF_ENDPOINT_ENABLED;
  } else {
    sli_zigbee_af_endpoints[index].bitmask &= EMBER_AF_ENDPOINT_DISABLED;
  }

#if defined(EZSP_HOST)
  ezspSetEndpointFlags(endpoint,
                       (enable
                        ? EZSP_ENDPOINT_ENABLED
                        : EZSP_ENDPOINT_DISABLED));
#endif

  if (currentlyEnabled != enable) {
    if (enable) {
      initializeEndpoint(&(sli_zigbee_af_endpoints[index]));
    } else {
      uint8_t i;
      for (i = 0; i < sli_zigbee_af_endpoints[index].endpointType->clusterCount; i++) {
        EmberAfCluster* cluster = &((sli_zigbee_af_endpoints[index].endpointType->cluster)[i]);
//        emberAfCorePrintln("Disabling cluster tick for ep:%d, cluster:0x%2X, %p",
//                           endpoint,
//                           cluster->clusterId,
//                           ((cluster->mask & CLUSTER_MASK_CLIENT)
//                            ? "client"
//                            : "server"));
//        emberAfCoreFlush();
        sl_zigbee_zcl_deactivate_cluster_tick(endpoint,
                                              cluster->clusterId,
                                              (cluster->mask & CLUSTER_MASK_CLIENT
                                               ? EMBER_AF_CLIENT_CLUSTER_TICK
                                               : EMBER_AF_SERVER_CLUSTER_TICK));
      }
    }
  }

  return true;
}

#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
bool emberAfClusterEnableDisable(uint8_t endpoint,
                                 EmberAfClusterId clusterId,
                                 EmberAfClusterMask mask,
                                 bool enable)
{
  uint8_t clusterData;
  EmberAfCluster *cluster = NULL;
  bool currentlyEnabled;
  uint8_t clusterIdx;

  clusterIdx = findClusterIdxInGeneratedListByEndpoint(endpoint, clusterId,
                                                       mask, EMBER_AF_NULL_MANUFACTURER_CODE);

  if (0xFF == clusterIdx) {
    return false;
  }

  cluster = (EmberAfCluster*)&generatedClusters[clusterIdx];

  clusterData = clusterExtendedData[clusterIdx];
  currentlyEnabled = emberAfClusterIsEnabled(clusterData);

  if (currentlyEnabled != enable) {
    if (enable) {
      clusterData &= ~CLUSTER_MASK_DISABLED;
      emberAfClusterInitCallback(endpoint, cluster->clusterId);
      EmberAfGenericClusterFunction f = emberAfFindClusterFunction(cluster, CLUSTER_MASK_INIT_FUNCTION);
      if (f != NULL) {
        ((EmberAfInitFunction)f)(endpoint);
      }
    } else {
      clusterData |= CLUSTER_MASK_DISABLED;
      sl_zigbee_zcl_deactivate_cluster_tick(endpoint,
                                            cluster->clusterId,
                                            (cluster->mask & CLUSTER_MASK_CLIENT
                                             ? EMBER_AF_CLIENT_CLUSTER_TICK
                                             : EMBER_AF_SERVER_CLUSTER_TICK));
    }
    clusterExtendedData[clusterIdx] = clusterData;
  }

  return true;
}

bool emberAfIsClusterEnabled(uint8_t endpoint,
                             EmberAfClusterId clusterId,
                             EmberAfClusterMask mask)
{
  uint8_t clusterData;
  uint8_t clusterIdx = findClusterIdxInGeneratedListByEndpoint(endpoint, clusterId,
                                                               mask, EMBER_AF_NULL_MANUFACTURER_CODE);
  if (0xFF == clusterIdx) {
    return false;
  }
  clusterData = clusterExtendedData[clusterIdx];

  return emberAfClusterIsEnabled(clusterData);
}
#endif // EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

// Returns the index of a given endpoint.  Does not consider disabled endpoints.
uint8_t emberAfIndexFromEndpoint(uint8_t endpoint)
{
  return findIndexFromEndpoint(endpoint,
                               true);    // ignore disabled endpoints?
}

// Returns the index of a given endpoint.  Considers disabled endpoints.
uint8_t emberAfIndexFromEndpointIncludingDisabledEndpoints(uint8_t endpoint)
{
  return findIndexFromEndpoint(endpoint,
                               false);    // ignore disabled endpoints?
}

uint8_t emberAfEndpointFromIndex(uint8_t index)
{
  return sli_zigbee_af_endpoints[index].endpoint;
}

// If server == true, returns the number of server clusters,
// otherwise number of client clusters on this endpoint
uint8_t emberAfClusterCount(uint8_t endpoint, bool server)
{
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  uint8_t i, c = 0;
  EmberAfDefinedEndpoint *de;
  EmberAfCluster *cluster;
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
  uint8_t clusterIdx;
  uint8_t clusterData;
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
  if ( index == 0xFF || (index >= MAX_ENDPOINT_COUNT)) {
    return 0;
  }
  de = &(sli_zigbee_af_endpoints[index]);
  if ( de->endpointType == NULL) {
    return 0;
  }
  for ( i = 0; i < de->endpointType->clusterCount; i++ ) {
    cluster = &(de->endpointType->cluster[i]);
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
    /* Don't count
     * if cluster is disabled
     */
    clusterIdx = findClusterIdxInGeneratedList(cluster);
    if (0xFF == clusterIdx) {
      continue;
    }
    clusterData = clusterExtendedData[clusterIdx];
    if (false == emberAfClusterIsEnabled(clusterData)) {
      continue;
    }
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME
    if ( server && emberAfClusterIsServer(cluster) ) {
      c++;
    }
    if ( (!server) && emberAfClusterIsClient(cluster) ) {
      c++;
    }
  }
  return c;
}

uint8_t emberAfGetClusterCountForEndpoint(uint8_t endpoint)
{
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  if ( index == 0xFF || (index >= MAX_ENDPOINT_COUNT)) {
    return 0;
  }
  return sli_zigbee_af_endpoints[index].endpointType->clusterCount;
}

// Note the difference in implementation from emberAfGetNthCluster().
// emberAfGetClusterByIndex() retrieves the cluster by index regardless of server/client
// and those indexes may be DIFFERENT than the indexes returned from
// emberAfGetNthCluster().  In other words:
//
//  - Use emberAfGetClustersFromEndpoint()  with emberAfGetNthCluster()
//  - Use emberAfGetClusterCountForEndpoint() with emberAfGetClusterByIndex()
//
// Don't mix them.
EmberAfCluster* emberAfGetClusterByIndex(uint8_t endpoint, uint8_t clusterIndex)
{
  uint8_t endpointIndex = emberAfIndexFromEndpoint(endpoint);
  EmberAfDefinedEndpoint* definedEndpoint;

  if (endpointIndex == 0xFF || (endpointIndex >= MAX_ENDPOINT_COUNT)) {
    return NULL;
  }
  definedEndpoint = &(sli_zigbee_af_endpoints[endpointIndex]);

  if (clusterIndex >= definedEndpoint->endpointType->clusterCount) {
    return NULL;
  }
  return &(definedEndpoint->endpointType->cluster[clusterIndex]);
}

EmberAfProfileId emberAfGetProfileIdForEndpoint(uint8_t endpoint)
{
  uint8_t endpointIndex = emberAfIndexFromEndpoint(endpoint);
  if (endpointIndex == 0xFF || (endpointIndex >= MAX_ENDPOINT_COUNT)) {
    return EMBER_AF_INVALID_PROFILE_ID;
  }
  return sli_zigbee_af_endpoints[endpointIndex].profileId;
}

uint16_t emberAfGetDeviceIdForEndpoint(uint8_t endpoint)
{
  uint8_t endpointIndex = emberAfIndexFromEndpoint(endpoint);
  if (endpointIndex == 0xFF || (endpointIndex >= MAX_ENDPOINT_COUNT)) {
    return EMBER_AF_INVALID_PROFILE_ID;
  }
  return sli_zigbee_af_endpoints[endpointIndex].deviceId;
}

// Returns the cluster of Nth server or client cluster,
// depending on server toggle.
EmberAfCluster *emberAfGetNthCluster(uint8_t endpoint, uint8_t n, bool server)
{
  uint8_t index = emberAfIndexFromEndpoint(endpoint);
  EmberAfDefinedEndpoint *de;
  uint8_t i, c = 0;
  EmberAfCluster *cluster;
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
  uint8_t clusterIdx;
  uint8_t clusterData;
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

  if ( index == 0xFF || (index >= MAX_ENDPOINT_COUNT)) {
    return NULL;
  }
  de = &(sli_zigbee_af_endpoints[index]);

  for ( i = 0; i < de->endpointType->clusterCount; i++ ) {
    cluster = &(de->endpointType->cluster[i]);
#if (EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME == 1)
#if !defined(EMBER_SCRIPTED_TEST)
    /* Don't count
     * if cluster is disabled
     */
    clusterIdx = findClusterIdxInGeneratedList(cluster);
    if (0xFF == clusterIdx) {
      continue;
    }
    clusterData = clusterExtendedData[clusterIdx];
    if (false == emberAfClusterIsEnabled(clusterData)) {
      continue;
    }
#endif //EMBER_SCRIPTED_TEST
#endif //EMBER_AF_PLUGIN_ZCL_CLUSTER_ENABLE_DISABLE_RUN_TIME

    if ( (server && emberAfClusterIsServer(cluster) )
         || ( (!server) &&  emberAfClusterIsClient(cluster) ) ) {
      if ( c == n ) {
#ifdef SL_CATALOG_ZIGBEE_TEST_HARNESS_Z3_PRESENT
        // Apply cluster suppression for match descriptor response.
        if ((server && emberAfGetSuppressCluster(cluster->clusterId, false))
            || (!server && emberAfGetSuppressCluster(cluster->clusterId, true))) {
          emberAfDebugPrintln("emberAfGetNthCluster - skipping: server = %d, cluster = %2X", server, cluster->clusterId);
          return NULL;
        }
#endif
        return cluster;
      }
      c++;
    }
  }
  return NULL;
}

// Returns number of clusters put into the passed cluster list
// for the given endpoint and client/server polarity
uint8_t emberAfGetClustersFromEndpoint(uint8_t endpoint, EmberAfClusterId *clusterList, uint8_t listLen, bool server)
{
  uint8_t clusterCount = emberAfClusterCount(endpoint, server);
  uint8_t i;
  EmberAfCluster *cluster;
  if (clusterCount > listLen) {
    clusterCount = listLen;
  }
  for (i = 0; i < clusterCount; i++) {
    cluster = emberAfGetNthCluster(endpoint, i, server);
    clusterList[i] = (cluster == NULL ? 0xFFFF : cluster->clusterId);
  }
  return clusterCount;
}

void emberAfInitializeAttributes(uint8_t endpoint)
{
  sli_zigbee_af_load_attribute_defaults(endpoint, false);
}

void emberAfResetAttributes(uint8_t endpoint)
{
  sli_zigbee_af_load_attribute_defaults(endpoint, true);
  sli_zigbee_af_reset_attributes(endpoint);
}

void sli_zigbee_af_load_attribute_defaults(uint8_t endpoint, bool writeTokens)
{
  uint8_t ep, clusterI, curNetwork = emberGetCurrentNetwork();
  uint16_t attr;
  uint8_t *ptr;
  uint8_t epCount = emberAfEndpointCount();

  for ( ep = 0; ep < epCount; ep++ ) {
    EmberAfDefinedEndpoint *de;
    if (endpoint != EMBER_BROADCAST_ENDPOINT) {
      ep = emberAfIndexFromEndpoint(endpoint);
      if (ep == 0xFF || (ep >= FIXED_ENDPOINT_COUNT)) {
        return;
      }
    }
    de = &(sli_zigbee_af_endpoints[ep]);

    // Ensure that the endpoint is on the current network
    if (endpoint == EMBER_BROADCAST_ENDPOINT
        && de->networkIndex != curNetwork) {
      continue;
    }
    for ( clusterI = 0; clusterI < de->endpointType->clusterCount; clusterI++) {
      EmberAfCluster *cluster = &(de->endpointType->cluster[clusterI]);

      // when the attributeCount is high, the loop takes too long to run and a
      // watchdog kicks in causing a reset. As a workaround, we'll
      // conditionally manually reset the watchdog. 300 sounds like a good
      // magic number for now.
      if (cluster->attributeCount > 300) {
        halResetWatchdog();
      }
      for ( attr = 0; attr < cluster->attributeCount; attr++) {
        EmberAfAttributeMetadata *am = &(cluster->attributes[attr]);
        if (!(am->mask & ATTRIBUTE_MASK_EXTERNAL_STORAGE)) {
          EmberAfAttributeSearchRecord record;
          record.endpoint = de->endpoint;
          record.clusterId = cluster->clusterId;
          record.clusterMask = (emberAfAttributeIsClient(am)
                                ? CLUSTER_MASK_CLIENT
                                : CLUSTER_MASK_SERVER);
          record.attributeId = am->attributeId;
          record.manufacturerCode = sli_zigbee_af_get_manufacturer_code_for_attribute(cluster,
                                                                                      am);
          if ((am->mask & ATTRIBUTE_MASK_MIN_MAX) != 0U) {
            if ( emberAfAttributeSize(am) <= 2 ) {
              ptr = (uint8_t*)&(am->defaultValue.ptrToMinMaxValue->defaultValue.defaultValue);
            } else {
              ptr = (uint8_t*)am->defaultValue.ptrToMinMaxValue->defaultValue.ptrToDefaultValue;
            }
          } else {
            if ( emberAfAttributeSize(am) <= 2 ) {
              ptr = (uint8_t*)&(am->defaultValue.defaultValue);
            } else {
              ptr = (uint8_t*)am->defaultValue.ptrToDefaultValue;
            }
          }
          // At this point, ptr either points to a default value, or is NULL, in which case
          // it should be treated as if it is pointing to an array of all zeroes.

#if (BIGENDIAN_CPU)
          // The default value for one- and two-byte attributes is stored in an
          // uint16_t.  On big-endian platforms, a pointer to the default value of
          // a one-byte attribute will point to the wrong byte.  So, for those
          // cases, nudge the pointer forward so it points to the correct byte.
          if (emberAfAttributeSize(am) == 1 && ptr != NULL) {
            ptr++;
          }
#endif //BIGENDIAN_CPU
          sli_zigbee_af_read_or_write_attribute(&record,
                                                NULL, // metadata - unused
                                                ptr,
                                                0, // buffer size - unused
                                                true); // write?
          if (writeTokens) {
            sli_zigbee_af_save_attribute_to_token(ptr, de->endpoint, record.clusterId, am);
          }
        }
      }
    }
    if (endpoint != EMBER_BROADCAST_ENDPOINT) {
      break;
    }
  }

  if (!writeTokens) {
    sli_zigbee_af_load_attributes_from_tokens(endpoint);
  }
}

void sli_zigbee_af_load_attributes_from_tokens(uint8_t endpoint)
{
  // On EZSP host we currently do not support this. We need to come up with some
  // callbacks.
#ifndef EZSP_HOST
#ifdef GENERATED_TOKEN_LOADER
  GENERATED_TOKEN_LOADER(endpoint);
#endif // GENERATED_TOKEN_LOADER
#endif // EZSP_HOST
}

// 'data' argument may be null, since we changed the ptrToDefaultValue
// to be null instead of pointing to all zeroes.
// This function has to be able to deal with that.
void sli_zigbee_af_save_attribute_to_token(uint8_t *data,
                                           uint8_t endpoint,
                                           EmberAfClusterId clusterId,
                                           EmberAfAttributeMetadata *metadata)
{
  // Get out of here if this attribute doesn't have a token.
  if ( !emberAfAttributeIsTokenized(metadata)) {
    return;
  }

// On EZSP host we currently do not support this. We need to come up with some
// callbacks.
#ifndef EZSP_HOST
#ifdef GENERATED_TOKEN_SAVER
  GENERATED_TOKEN_SAVER;
#endif // GENERATED_TOKEN_SAVER
#endif // EZSP_HOST
}

// This function returns the function pointer from the cluster functions array,
// The functionMask must be a single flag out of the following ("OR"-ing is not allowed):
// CLUSTER_MASK_INIT_FUNCTION, CLUSTER_MASK_ATTRIBUTE_CHANGED_FUNCTION, CLUSTER_MASK_DEFAULT_RESPONSE_FUNCTION,
// CLUSTER_MASK_MESSAGE_SENT_FUNCTION, CLUSTER_MASK_MANUFACTURER_SPECIFIC_ATTRIBUTE_CHANGED_FUNCTION,
// CLUSTER_MASK_PRE_ATTRIBUTE_CHANGED_FUNCTION
EmberAfGenericClusterFunction
emberAfFindClusterFunction(EmberAfCluster *cluster,
                           EmberAfClusterMask functionMask)
{
  #ifndef EMBER_SCRIPTED_TEST
  const emberClusterFunctionStructure *funcStruct = &generatedClusterFunctions[0];

  for (int i = 0; i < (int)(sizeof(generatedClusterFunctions) / sizeof(emberClusterFunctionStructure)); i++) {
    if ((funcStruct->clusterId == cluster->clusterId)
        && (funcStruct->functionMask & cluster->mask & (CLUSTER_MASK_SERVER | CLUSTER_MASK_CLIENT))
        && (functionMask & funcStruct->functionMask)) {
      return funcStruct->functionPtr;
    }
    funcStruct++;
  }

  return NULL;
  #else
  //For unit tests where generatedClusterFunctions is not populated
  EmberAfClusterMask mask = 0x01;
  uint8_t functionIndex = 0;
  if ((cluster->mask & functionMask) == 0) {
    return NULL;
  }

  while (mask < functionMask) {
    if ((cluster->mask & mask) != 0) {
      functionIndex++;
    }
    mask <<= 1;
  }
  return cluster->functions[functionIndex];
  #endif
}

#ifdef EMBER_AF_SUPPORT_COMMAND_DISCOVERY

static UNUSED uint16_t get_manufacturer_code_for_command(EmberAfCommandMetadata *command)
{
#if (GENERATED_COMMAND_MANUFACTURER_CODE_COUNT > 0)
  return getManufacturerCode((EmberAfManufacturerCodeEntry *)commandManufacturerCodes,
                             commandManufacturerCodeCount,
                             (command - generatedCommands));
#else // !GENERATED_COMMAND_MANUFACTURER_CODE_COUNT
  return EMBER_AF_NULL_MANUFACTURER_CODE;
#endif // GENERATED_COMMAND_MANUFACTURER_CODE_COUNT
}

// Resolve the manufacturing code for a command when the Discover Command
// request specifies the wildcard 0xFFFF for the mfg code. Choose the mfg code
// for the first mfg-specific command at or following the startId. Iterate
// through all commands to choose the smallest mfg code if the command is
// overloaded by more than one mfg-specific implementation of that command ID.
// If no valid mfg code is resolved, return 0xFFFF.
uint16_t sli_zigbee_af_resolve_mfg_code_for_discover_command(bool outgoing,
                                                             EmberAfClusterCommand *cmd,
                                                             uint16_t clusterId,
                                                             uint8_t startId)
{
  uint16_t commandMfgCode = 0xFFFF;
#if (EMBER_AF_GENERATED_COMMAND_COUNT > 0)
  bool foundFirst = false;
  uint8_t foundCmdId = 0;
  uint8_t cmdDirMask = 0;

  // determine the appropriate mask to match the request
  // discover commands generated, client is asking server what commands do you generate?
  if (outgoing && (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER)) {
    cmdDirMask = COMMAND_MASK_OUTGOING_SERVER;
    // discover commands generated server is asking client what commands do you generate?
  } else if (outgoing && (cmd->direction == ZCL_DIRECTION_SERVER_TO_CLIENT)) {
    cmdDirMask = COMMAND_MASK_OUTGOING_CLIENT;
    // discover commands received client is asking server what commands do you receive?
  } else if (!outgoing && (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER)) {
    cmdDirMask = COMMAND_MASK_INCOMING_SERVER;
    // discover commands received server is asking client what commands do you receive?
  } else {
    cmdDirMask = COMMAND_MASK_INCOMING_CLIENT;
  }
  for ( uint16_t i = 0; i < EMBER_AF_GENERATED_COMMAND_COUNT; i++ ) {
    if ( generatedCommands[i].clusterId != clusterId ) {
      continue;
    }

    if ((generatedCommands[i].mask & cmdDirMask) == 0 ) {
      continue;
    }

    // Only start from the passed command id
    if (generatedCommands[i].commandId < startId) {
      continue;
    }

    // After having previously found a first mfg-spec candidate,
    // ignore an attr that has a higher attrId.
    if (foundFirst && generatedCommands[i].commandId > foundCmdId) {
      continue;
    }

    // Get command's mfg-code. Update the search state if:
    // this is the first qualifying cmd found;
    // else, this qualifying cmd has a lower cmdId than prior cmd found;
    // else, this cmdId equals prior, prefer this cmd's lower mfg-code.
    if ( generatedCommands[i].mask & COMMAND_MASK_MANUFACTURER_SPECIFIC ) {
      uint16_t candidateMfgCode
        = get_manufacturer_code_for_command( (EmberAfCommandMetadata*) &(generatedCommands[i]));
      if (!foundFirst
          || generatedCommands[i].commandId < foundCmdId
          || candidateMfgCode < commandMfgCode) {
        foundFirst = true;
        foundCmdId = generatedCommands[i].commandId;
        commandMfgCode = candidateMfgCode;
      }
    }
  }
#endif // EMBER_AF_GENERATED_COMMAND_COUNT
  return commandMfgCode;
}

/**
 * This function populates command IDs into a given buffer.
 *
 * It returns true if commands are complete, meaning there are NO MORE
 * commands that would be returned after the last command.
 * It returns false, if there were more commands, but were not populated
 * because of maxIdCount limitation.
 */
bool emberAfExtractCommandIds(bool outgoing,
                              EmberAfClusterCommand *cmd,
                              uint16_t clusterId,
                              uint8_t *buffer,
                              uint16_t bufferLength,
                              uint16_t *bufferIndex,
                              uint8_t startId,
                              uint8_t maxIdCount)
{
  bool returnValue = true;
#if (EMBER_AF_GENERATED_COMMAND_COUNT > 0)
  uint16_t i, count = 0;
  uint8_t cmdDirMask = 0;
  // determine the appropriate mask to match the request
  // discover commands generated, client is asking server what commands do you generate?
  if (outgoing && (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER)) {
    cmdDirMask = COMMAND_MASK_OUTGOING_SERVER;
    // discover commands generated server is asking client what commands do you generate?
  } else if (outgoing && (cmd->direction == ZCL_DIRECTION_SERVER_TO_CLIENT)) {
    cmdDirMask = COMMAND_MASK_OUTGOING_CLIENT;
    // discover commands received client is asking server what commands do you receive?
  } else if (!outgoing && (cmd->direction == ZCL_DIRECTION_CLIENT_TO_SERVER)) {
    cmdDirMask = COMMAND_MASK_INCOMING_SERVER;
    // discover commands received server is asking client what commands do you receive?
  } else {
    cmdDirMask = COMMAND_MASK_INCOMING_CLIENT;
  }
  for ( i = 0; i < EMBER_AF_GENERATED_COMMAND_COUNT; i++ ) {
    if ( generatedCommands[i].clusterId != clusterId ) {
      continue;
    }

    if ((generatedCommands[i].mask & cmdDirMask) == 0 ) {
      continue;
    }

    // Only start from the passed command id
    if (generatedCommands[i].commandId < startId) {
      continue;
    }

    // According to spec: if cmd->mfgSpecific is set, then we ONLY return the
    // mfg specific commands. If it's not, then we ONLY return non-mfg specific.
    if ( generatedCommands[i].mask & COMMAND_MASK_MANUFACTURER_SPECIFIC ) {
      // Command is Mfg specific
      if ( !cmd->mfgSpecific ) {
        continue;                        // ignore if asking for not mfg specific
      }
      if ( cmd->mfgCode != get_manufacturer_code_for_command( (EmberAfCommandMetadata*) &(generatedCommands[i]))) {
        continue;                        // Ignore if mfg code doesn't match the commands
      }
    } else {
      // Command is not mfg specific.
      if ( cmd->mfgSpecific ) {
        continue;                       // Ignore if asking for mfg specific
      }
    }

    // The one we are about to put in, is beyond the maxIdCount,
    // so instead of populating it in, we set the return flag to
    // false and get out of here.
    if ( maxIdCount == count || count >= bufferLength ) {
      returnValue = false;
      break;
    }
    buffer[count] = generatedCommands[i].commandId;
    (*bufferIndex)++;
    count++;
  }
#endif // EMBER_AF_GENERATED_COMMAND_COUNT
  return returnValue;
}
#else
// We just need an empty stub if we don't support it
bool emberAfExtractCommandIds(bool outgoing,
                              EmberAfClusterCommand *cmd,
                              uint16_t clusterId,
                              uint8_t *buffer,
                              uint16_t bufferLength,
                              uint16_t *bufferIndex,
                              uint8_t startId,
                              uint8_t maxIdCount)
{
  return true;
}
#endif
