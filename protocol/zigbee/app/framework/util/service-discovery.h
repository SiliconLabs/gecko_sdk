/***************************************************************************//**
 * @file
 * @brief Interface for initiating and processing ZDO service discovery
 * (match descriptor) requests and response.
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

#ifndef SILABS_SERVICE_DISCOVERY_H
#define SILABS_SERVICE_DISCOVERY_H

#include "../include/af.h"
#define EMBER_SUPPORTED_SERVICE_DISCOVERY_STATES_PER_NETWORK 4u
// Internal Functions
void sli_zigbee_af_service_discovery_matched(EmberNodeId nodeId,
                                             uint8_t endpointListLength,
                                             uint8_t* endpointList);

// Platform specific call to send a match descriptor request.
EmberStatus sli_zigbee_af_send_match_descriptor(EmberNodeId target,
                                                EmberAfProfileId profileId,
                                                EmberAfClusterId clusterId,
                                                bool serverCluster);

bool sli_zigbee_af_service_discovery_incoming(EmberNodeId sender,
                                              EmberApsFrame* apsFrame,
                                              const uint8_t* message,
                                              uint16_t length);

void sli_zigbee_af_service_discovery_complete(uint8_t networkIndex, uint8_t sequenceNumber);

#ifndef EMBER_AF_DISCOVERY_TIMEOUT_QS
// NOTE 2.25 seconds
  #define EMBER_AF_DISCOVERY_TIMEOUT_QS (2u * 4u + 1u)
#endif

extern sl_zigbee_event_t sli_zigbee_af_service_discovery_events[EMBER_SUPPORTED_SERVICE_DISCOVERY_STATES_PER_NETWORK][EMBER_SUPPORTED_NETWORKS];
void sli_zigbee_af_service_discovery_timeout_handler(sl_zigbee_event_t *event);

#endif // SILABS_SERVICE_DISCOVERY_H
