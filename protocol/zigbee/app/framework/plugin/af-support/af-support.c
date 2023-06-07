/***************************************************************************//**
 * @file af-support.c
 * @brief Application Framework Support code
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

#include "af-support.h"
#include "attribute-storage.h"

void sli_zb_af_support_init_callback(uint8_t init_level)
{
  (void)init_level;
  // configure endpoint data
  emberAfEndpointConfigure();
}

bool emberAfPreMessageReceivedCallback(EmberAfIncomingMessage* incomingMessage)
{
  // Should only handle ZCL message for GP endpoint
  if (emberAfProcessMessage(incomingMessage->apsFrame,
                            incomingMessage->type,
                            incomingMessage->message,
                            incomingMessage->msgLen,
                            incomingMessage->source,
                            NULL)) { // no inter-pan header
  }
  // Always return true so sli_zigbee_af_incoming_message_handler() should not continue to process message.
  return true;
}

bool sli_zb_af_support_incoming_message_callback(EmberApsFrame *apsFrame)
{
  if (apsFrame->destinationEndpoint == EMBER_GP_ENDPOINT
      || ((apsFrame->destinationEndpoint == EMBER_BROADCAST_ENDPOINT) \
          && (apsFrame->clusterId == ZCL_GREEN_POWER_CLUSTER_ID))) {
    return true;
  }
  return false;
}

extern bool sli_zigbee_find_endpoint_cluster(uint8_t endpoint,
                                             uint16_t requestedClusterId,
                                             EmberClusterListId listId);

bool emberAfContainsServerWrapper(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return sli_zigbee_find_endpoint_cluster(endpoint, clusterId, EMBER_INPUT_CLUSTER_LIST);
}

bool emberAfContainsClientWrapper(uint8_t endpoint, EmberAfClusterId clusterId)
{
  return sli_zigbee_find_endpoint_cluster(endpoint, clusterId, EMBER_OUTPUT_CLUSTER_LIST);
}

extern bool sli_zigbee_get_endpoint_info(uint8_t endpoint,
                                         uint8_t *returnNetworkIndex,
                                         uint16_t *returnProfileId);

bool emberAfGetEndpointInfoCallback(uint8_t endpoint,
                                    uint8_t *returnNetworkIndex,
                                    EmberAfEndpointInfoStruct *returnEndpointInfo)
{
  return sli_zigbee_get_endpoint_info(endpoint, returnNetworkIndex, &(returnEndpointInfo->profileId));
}

bool emberAfNcpDGpSentHandler(EmberStatus status, uint8_t gpepHandle)
{
  // Return true then sli_zigbee_af_d_gp_sent_callback will not send EZSP to host
  return true;
}

bool emberAfNcpGpepIncomingMessageHandler(GP_PARAMS)
{
  // Return true then sli_zigbee_af_gpep_incoming_message_callback will not send EZSP to host
  return true;
}

bool emberAfGreenPowerServerUpdateInvolveTCCallback(EmberStatus status)
{
  // Return true here to avoid writing the TCInvolved bit
  return true;
}
