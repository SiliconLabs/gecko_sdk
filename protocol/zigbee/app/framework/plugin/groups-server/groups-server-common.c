/***************************************************************************//**
 * @file
 * @brief Common code to be used by groups-server and others
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

#include "groups-server-common.h"

bool emberAfGroupsClusterEndpointInGroupCallback(uint8_t endpoint,
                                                 uint16_t groupId)
{
  return sli_zigbee_af_groups_cluster_is_group_present(endpoint, groupId);
}

bool sli_zigbee_af_groups_cluster_binding_group_match(uint8_t endpoint,
                                                      uint16_t groupId,
                                                      EmberBindingTableEntry *entry)
{
  return (entry->type == EMBER_MULTICAST_BINDING
          && entry->identifier[0] == LOW_BYTE(groupId)
          && entry->identifier[1] == HIGH_BYTE(groupId)
          && entry->local == endpoint);
}

bool sli_zigbee_af_groups_cluster_is_group_present(uint8_t endpoint, uint16_t groupId)
{
  uint8_t i;

  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    EmberBindingTableEntry binding;
    if (emberGetBinding(i, &binding) == EMBER_SUCCESS) {
      if (sli_zigbee_af_groups_cluster_binding_group_match(endpoint, groupId, &binding)) {
        return true;
      }
    }
  }

  return false;
}
