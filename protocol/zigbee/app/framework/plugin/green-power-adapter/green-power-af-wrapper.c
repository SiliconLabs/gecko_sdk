/***************************************************************************//**
 * @file
 * @brief
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "green-power-af-wrapper.h"

WEAK(uint16_t emberAfPrintActiveArea) = 0;

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM == 1)
WEAK(EmberAfStatus emberAfReadAttributeWrapper(uint8_t endpoint,
                                               EmberAfClusterId cluster,
                                               EmberAfAttributeId attributeID,
                                               uint8_t mask,
                                               uint8_t *dataPtr,
                                               uint8_t readLength,
                                               EmberAfAttributeType *dataType))
{
  return 0xff;
}

WEAK(EmberAfStatus emberAfWriteAttributeWrapper(uint8_t endpoint,
                                                EmberAfClusterId cluster,
                                                EmberAfAttributeId attributeID,
                                                uint8_t mask,
                                                uint8_t* dataPtr,
                                                EmberAfAttributeType dataType))
{
  return 0xff;
}

WEAK(EmberAfStatus emberAfWriteClientAttributeWrapper(uint8_t endpoint,
                                                      EmberAfClusterId cluster,
                                                      EmberAfAttributeId attributeID,
                                                      uint8_t* dataPtr,
                                                      EmberAfAttributeType dataType))
{
  return 0xff;
}

WEAK(bool emberAfContainsServerWrapper(uint8_t endpoint, EmberAfClusterId clusterId))
{
  return false;
}

WEAK(bool emberAfContainsClientWrapper(uint8_t endpoint, EmberAfClusterId clusterId))
{
  return false;
}
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_ATTRIBUTE_SYSTEM == 1)

WEAK(uint8_t emberAfGetRadioChannelWrapper(void))
{
  return emberGetRadioChannel();
}

#if (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_AF_INTERFACE == 1)
WEAK(EmberApsFrame *emberAfGetCommandApsFrameWrapper(void))
{
  return NULL;
}

WEAK(EmberStatus emberAfSendCommandUnicastWrapper(EmberOutgoingMessageType type,
                                                  uint16_t indexOrDestination))
{
  return 0xff;
}

WEAK(EmberStatus emberAfSendCommandBroadcastWithAliasWrapper(EmberNodeId destination,
                                                             EmberNodeId alias,
                                                             uint8_t sequence))
{
  return 0xff;
}

WEAK(EmberStatus emberAfSendCommandMulticastWithAliasWrapper(EmberMulticastId multicastId, EmberNodeId alias, uint8_t sequence))
{
  return 0xff;
}

WEAK(uint16_t emberAfFillExternalBufferWrapper(uint8_t frameControl,
                                               EmberAfClusterId clusterId,
                                               uint8_t commandId,
                                               const char *format,
                                               ...))
{
  return 0xff;
}
#endif // (EMBER_AF_PLUGIN_GREEN_POWER_ADAPTER_USE_CUSTOM_AF_INTERFACE == 1)

WEAK(void emberAfCopyInt16u(uint8_t *data, uint16_t index, uint16_t x))
{
  data[index]   = (uint8_t) ( ((x)    ) & 0xFFu);
  data[index + 1] = (uint8_t) ( ((x) >> 8) & 0xFFu);
}

WEAK(void emberAfCopyInt24u(uint8_t *data, uint16_t index, uint32_t x))
{
  data[index]   = (uint8_t) ( ((x)    ) & 0xFFu);
  data[index + 1] = (uint8_t) ( ((x) >> 8) & 0xFFu);
  data[index + 2] = (uint8_t) ( ((x) >> 16) & 0xFFu);
}

WEAK(void emberAfCopyInt32u(uint8_t *data, uint16_t index, uint32_t x))
{
  data[index]   = (uint8_t) ( ((x)    ) & 0xFFu);
  data[index + 1] = (uint8_t) ( ((x) >> 8) & 0xFFu);
  data[index + 2] = (uint8_t) ( ((x) >> 16) & 0xFFu);
  data[index + 3] = (uint8_t) ( ((x) >> 24) & 0xFFu);
}

WEAK(void emberAfCopyString(uint8_t *dest, uint8_t *src, uint8_t size))
{
  if ( src == NULL ) {
    dest[0] = 0u; // Zero out the length of string
  } else if (src[0] == 0xFFu) {
    dest[0] = src[0];
  } else {
    uint8_t length = emberAfStringLength(src);
    if (size < length) {
      length = size;
    }
    MEMMOVE(dest + 1, src + 1, length);
    dest[0] = length;
  }
}

WEAK(void emberAfCopyLongString(uint8_t *dest, uint8_t *src, uint16_t size))
{
  if ( src == NULL ) {
    dest[0] = dest[1] = 0u; // Zero out the length of string
  } else if ((src[0] == 0xFFu)
             && (src[1] == 0xFFu)) {
    dest[0] = 0xFFu;
    dest[1] = 0xFFu;
  } else {
    uint16_t length = emberAfLongStringLength(src);
    if (size < length) {
      length = size;
    }
    MEMMOVE(dest + 2, src + 2, length);
    dest[0] = LOW_BYTE(length);
    dest[1] = HIGH_BYTE(length);
  }
}

#if (BIGENDIAN_CPU)
  #define EM_BIG_ENDIAN true
#else
  #define EM_BIG_ENDIAN false
#endif

// You can pass in val1 as NULL, which will assume that it is
// pointing to an array of all zeroes. This is used so that
// default value of NULL is treated as all zeroes.
WEAK(int8_t emberAfCompareValues(uint8_t* val1,
                                 uint8_t* val2,
                                 uint8_t len,
                                 bool signedNumber))
{
  uint8_t i, j, k;
  if (signedNumber) { // signed number comparison
    if (len <= 4) { // only number with 32-bits or less is supported
      int32_t accum1 = 0x0;
      int32_t accum2 = 0x0;
      int32_t all1s = -1;

      for (i = 0; i < len; i++) {
        j = (val1 == NULL
             ? 0
             : (EM_BIG_ENDIAN ? val1[i] : val1[(len - 1) - i])
             );
        accum1 |= j << (8 * (len - 1 - i));

        k = (EM_BIG_ENDIAN
             ? val2[i]
             : val2[(len - 1) - i]);
        accum2 |= k << (8 * (len - 1 - i));
      }

      // sign extending, no need for 32-bits numbers
      if (len < 4) {
        if ((accum1 & (1 << (8 * len - 1))) != 0) { // check sign
          accum1 |= all1s - ((1 << (len * 8)) - 1);
        }
        if ((accum2 & (1 << (8 * len - 1))) != 0) { // check sign
          accum2 |= all1s - ((1 << (len * 8)) - 1);
        }
      }

      if (accum1 > accum2) {
        return 1;
      } else if (accum1 < accum2) {
        return -1;
      } else {
        return 0;
      }
    } else { // not supported
      return 0;
    }
  } else { // regular unsigned number comparison
    for (i = 0; i < len; i++) {
      j = (val1 == NULL
           ? 0
           : (EM_BIG_ENDIAN ? val1[i] : val1[(len - 1) - i])
           );
      k = (EM_BIG_ENDIAN
           ? val2[i]
           : val2[(len - 1) - i]);

      if (j > k) {
        return 1;
      } else if (k > j) {
        return -1;
      } else {
        // MISRA requires ..else if.. to have terminating else.
      }
    }
    return 0;
  }
}

// Zigbee spec says types between signed 8 bit and signed 64 bit
WEAK(bool emberAfIsTypeSigned(EmberAfAttributeType dataType))
{
  return (dataType >= ZCL_INT8S_ATTRIBUTE_TYPE
          && dataType <= ZCL_INT64S_ATTRIBUTE_TYPE);
}

WEAK(bool emberAfGroupsClusterEndpointInGroupCallback(uint8_t endpoint,
                                                      uint16_t groupId))
{
  return false;
}

WEAK(EmberNodeId emberAfGetNodeId(void))
{
  return emberGetNodeId();
}

WEAK(void emberAfGetEui64(EmberEUI64 returnEui64))
{
  MEMMOVE(returnEui64, emberGetEui64(), EUI64_SIZE);
}

WEAK(EmberPanId emberAfGetPanId(void))
{
  return emberGetPanId();
}
WEAK(uint8_t emberAfGetBindingIndex(void))
{
  return emberGetBindingIndex();
}

WEAK(uint8_t emberAfGetAddressIndex(void))
{
  EmberEUI64 longId;
  EmberEUI64 longIdIterator;
  uint8_t i;

  if ((emberGetSenderEui64(longId)) == EMBER_SUCCESS) {
    for (i = 0; i < EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE; i++) {
      emberGetAddressTableRemoteEui64(i, longIdIterator);
      if (MEMCOMPARE(longIdIterator, longId, EUI64_SIZE) == 0) {
        return i;
      }
    }
  } else {
    EmberNodeId nodeId = emberGetSender();
    if (nodeId == EMBER_NULL_NODE_ID) {
      return EMBER_NULL_ADDRESS_TABLE_INDEX;
    }
    for (i = 0; i < EMBER_AF_PLUGIN_ADDRESS_TABLE_SIZE; i++) {
      if (emberGetAddressTableRemoteNodeId(i) == nodeId) {
        return i;
      }
    }
  }
  return EMBER_NULL_ADDRESS_TABLE_INDEX;
}

bool emberAfIsCurrentSecurityProfileSmartEnergy(void)
{
  return false;
}

WEAK(uint8_t emberAfGetOpenNetworkDurationSec(void))
{
  return 0;
}

WEAK(bool sli_zigbee_af_service_discovery_incoming(EmberNodeId sender,
                                                   EmberApsFrame *apsFrame,
                                                   const uint8_t *message,
                                                   uint16_t length))
{
  return false;
}
WEAK(EmberStatus zaTrustCenterSecurityInit(bool centralizedNetwork))
{
  return 0;
}
WEAK(EmberStatus zaNodeSecurityInit(bool centralizedNetwork))
{
  return 0;
}

WEAK(EmberStatus zaTrustCenterSecurityPolicyInit(void))
{
  return 0;
}
WEAK(void emberAfGetMfgString(uint8_t* returnData))
{
}

WEAK(EmberStatus emberAfGetNodeType(EmberNodeType *nodeType))
{
  return emberGetNodeType(nodeType);
}

WEAK(EmberStatus emberSendZigDevRequest(EmberNodeId destination,
                                        uint16_t clusterId,
                                        EmberApsOption options,
                                        uint8_t *contents,
                                        uint8_t length))
{
  return 0;
}

WEAK(EmberStatus sli_zigbee_af_send(EmberOutgoingMessageType type,
                                    uint16_t indexOrDestination,
                                    EmberApsFrame *apsFrame,
                                    uint8_t messageLength,
                                    uint8_t *message,
                                    uint16_t *messageTag,
                                    EmberNodeId alias,
                                    uint8_t sequence))
{
  return 0;
}

WEAK(void emberAfPrint(uint16_t area, const char * formatString, ...))
{
}

WEAK(bool emberAfPrintEnabled(uint16_t area))
{
  return false;
}

WEAK(void emberAfPrintBuffer(uint16_t area,
                             const uint8_t *buffer,
                             uint16_t bufferLen,
                             bool withSpace))
{
}
WEAK(void emberAfPrintln(uint16_t functionality, const char * formatString, ...))
{
}

WEAK(bool emberAfMemoryByteCompare(const uint8_t *bytes, uint8_t count, uint8_t target))
{
  uint8_t i;
  for (i = 0; i < count; i++) {
    if (*bytes != target) {
      return false;
    }
    bytes++;
  }
  return true;
}
