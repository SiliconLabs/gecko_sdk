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
#include "af.h"

bool sli_zigbee_af_groups_cluster_binding_group_match(uint8_t endpoint,
                                                      uint16_t groupId,
                                                      EmberBindingTableEntry *entry);
bool sli_zigbee_af_groups_cluster_is_group_present(uint8_t endpoint, uint16_t groupId);
