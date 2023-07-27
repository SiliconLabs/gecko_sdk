/***************************************************************************//** * @file  sli_zigbee_zdo_cluster_filter_stubs.c
 * @brief stubs for zdo cluster filter feature
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

#include "sl_common.h"
#include "stack/zigbee/sli_zigbee_zdo_cluster_filter.h"

SL_WEAK void emberSetZDOConfigurationMode(bool enabled)
{
  (void) enabled;
}

SL_WEAK bool sli_zigbee_zdo_cluster_command_is_authorized(EmberNodeId sender,
                                                          bool was_encrypted,
                                                          uint16_t cluster_id,
                                                          bool was_broadcast,
                                                          EmberApsOption options,
                                                          uint8_t sequence_number)
{
  (void) sender;
  (void) was_encrypted;
  (void) cluster_id;
  (void) was_broadcast;
  (void) options;
  (void) sequence_number;
  return true;
}
