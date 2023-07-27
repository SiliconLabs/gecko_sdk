/**
 * @file  sli_zigbee_zdo_cluster_filter.h
 * @brief Allows for configuration of ZDO policies restricting certain clusters
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

#ifndef SLI_ZIGBEE_ZDO_CLUSTER_FILTER_H
#define SLI_ZIGBEE_ZDO_CLUSTER_FILTER_H

#include "stack/include/ember-types.h"

bool sli_zigbee_get_zdo_configuration_mode(void);

void sli_zigbee_zdo_set_restricted_cluster_list(uint16_t* pClusterList, uint8_t count);

bool sli_zigbee_zdo_cluster_command_is_authorized(EmberNodeId sender,
                                                  bool was_encrypted,
                                                  uint16_t cluster_id,
                                                  bool was_broadcast,
                                                  EmberApsOption options,
                                                  uint8_t sequence_number);

#endif // SLI_ZIGBEE_ZDO_CLUSTER_FILTER_H
