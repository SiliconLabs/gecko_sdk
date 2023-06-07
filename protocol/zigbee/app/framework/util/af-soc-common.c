/***************************************************************************//**
 * @file af-soc-common.c
 * @brief common APIs used for both SoC and NCP application when af support
 * component is enabled on NCP.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "af-main.h"
#include "attribute-storage.h"

//------------------------------------------------------------------------------
// must return the endpoint desc of the endpoint specified
bool sli_zigbee_af_get_endpoint_description(uint8_t endpoint,
                                            EmberEndpointDescription *result)
{
  if (emberAfGetEndpointDescriptionCallback(endpoint, result)) {
    return true;
  }
  uint8_t endpointIndex = emberAfIndexFromEndpoint(endpoint);
  if (endpointIndex == 0xFF
      || (endpointIndex >= MAX_ENDPOINT_COUNT)
      || (emberAfNetworkIndexFromEndpointIndex(endpointIndex)
          != emberGetCallbackNetwork())) {
    return false;
  }
  result->profileId          = emberAfProfileIdFromIndex(endpointIndex);
  result->deviceId           = emberAfDeviceIdFromIndex(endpointIndex);
  result->deviceVersion      = emberAfDeviceVersionFromIndex(endpointIndex);
  result->inputClusterCount  = emberAfClusterCount(endpoint, true);
  result->outputClusterCount = emberAfClusterCount(endpoint, false);
  return true;
}

// must return the clusterId at listIndex in the list specified for the
// endpoint specified
uint16_t sli_zigbee_af_get_endpoint_cluster(uint8_t endpoint,
                                            EmberClusterListId listId,
                                            uint8_t listIndex)
{
  EmberAfCluster *cluster = NULL;
  uint8_t endpointIndex = emberAfIndexFromEndpoint(endpoint);
  if (endpointIndex == 0xFF
      || (endpointIndex >= MAX_ENDPOINT_COUNT)
      || (emberAfNetworkIndexFromEndpointIndex(endpointIndex)
          != emberGetCallbackNetwork())) {
    return 0xFFFF;
  } else if (listId == EMBER_INPUT_CLUSTER_LIST) {
    cluster = emberAfGetNthCluster(endpoint, listIndex, true);
  } else if (listId == EMBER_OUTPUT_CLUSTER_LIST) {
    cluster = emberAfGetNthCluster(endpoint, listIndex, false);
  } else {
    // MISRA requires ..else if.. to have terminating else.
  }
  return (cluster == NULL ? 0xFFFF : cluster->clusterId);
}

uint8_t sli_zigbee_af_get_endpoint(uint8_t index)
{
  uint8_t endpoint = EMBER_AF_INVALID_ENDPOINT;
  if (emberAfGetEndpointByIndexCallback(index, &endpoint)) {
    return endpoint;
  }
  return (((emberAfNetworkIndexFromEndpointIndex(index)
            == emberGetCallbackNetwork())
           && emberAfEndpointIndexIsEnabled(index))
          ? emberAfEndpointFromIndex(index)
          : 0xFF);
}

//------------------------------------------------------------------------------
// Internal APIs

EmberStatus sli_zigbee_af_send(EmberOutgoingMessageType type,
                               uint16_t indexOrDestination,
                               EmberApsFrame *apsFrame,
                               uint8_t messageLength,
                               uint8_t *message,
                               uint16_t *messageTag,
                               EmberNodeId alias,
                               uint8_t sequence)
{
  EmberMessageBuffer payload = emberFillLinkedBuffers(message, messageLength);
  if (payload == EMBER_NULL_MESSAGE_BUFFER) {
    return EMBER_NO_BUFFERS;
  } else {
    EmberStatus status;

    *messageTag = sli_zigbee_af_calculate_message_tag_hash(message, messageLength);

    switch (type) {
      case EMBER_OUTGOING_DIRECT:
      case EMBER_OUTGOING_VIA_ADDRESS_TABLE:
      case EMBER_OUTGOING_VIA_BINDING:
        status = emberSendUnicast(type, indexOrDestination, apsFrame, payload);
        break;
      case EMBER_OUTGOING_MULTICAST:
        status = emberSendMulticast(apsFrame,
                                    ZA_MAX_HOPS, // radius
                                    ZA_MAX_HOPS, // nonmember radius
                                    payload);
        break;
      case EMBER_OUTGOING_MULTICAST_WITH_ALIAS:
        status = emberSendMulticastWithAlias(apsFrame,
                                             apsFrame->radius, //radius
                                             apsFrame->radius, //nonmember radius
                                             payload,
                                             alias,
                                             sequence);
        break;
      case EMBER_OUTGOING_BROADCAST:
        status = emberSendBroadcast(indexOrDestination,
                                    apsFrame,
                                    ZA_MAX_HOPS, // radius
                                    payload);
        break;
      case EMBER_OUTGOING_BROADCAST_WITH_ALIAS:
        status = emberProxyBroadcast(alias,
                                     indexOrDestination,
                                     sequence,
                                     apsFrame,
                                     apsFrame->radius, // radius
                                     payload);
        break;
      default:
        status = EMBER_BAD_ARGUMENT;
        break;
    }

    emberReleaseMessageBuffer(payload);

    return status;
  }
}

#define INVALID_MESSAGE_TAG 0x0000
uint16_t sli_zigbee_af_calculate_message_tag_hash(uint8_t *messageContents,
                                                  uint8_t messageLength)
{
  uint8_t temp[EMBER_ENCRYPTION_KEY_SIZE];
  uint16_t hashReturn = 0;
  emberAesHashSimple(messageLength, messageContents, temp);
  for (uint8_t i = 0; i < EMBER_ENCRYPTION_KEY_SIZE; i += 2) {
    hashReturn ^= *((uint16_t *)(temp + i));
  }
  if (hashReturn == INVALID_MESSAGE_TAG) {
    hashReturn = 1;
  }
  return hashReturn;
}
