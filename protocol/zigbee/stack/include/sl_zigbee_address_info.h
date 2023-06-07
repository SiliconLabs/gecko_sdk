/***************************************************************************//**
 * @file sl_zigbee_address_info.h
 * @brief data type and utility functions for device long, short id pairs
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

#ifndef SL_ZIGBEE_ADDRESS_INFO_H
#define SL_ZIGBEE_ADDRESS_INFO_H

#include "ember-types.h"

/**
 * @brief a wrapper struct to group a short-id and long-id pair
 */
typedef struct device_ids {
  EmberEUI64 device_long;
  EmberNodeId device_short;
} sl_zigbee_address_info;

// here's a global instance of all wildcards
extern const sl_zigbee_address_info sl_zigbee_null_device_id_pair;

/**
 *  populates a device id pair from the component parts
 */
sl_zigbee_address_info sl_zigbee_make_device_id_pair(const EmberNodeId short_id, const EmberEUI64 long_id);

/**
 *  @brief determines whether two device id pairings match, allowing wildcards
 *  matches
 *       | MATCH(short) + WILD(long)
 *       | WILD(short) + MATCH(long)
 *       | MATCH(short) + MATCH(long)
 */
bool sl_zigbee_device_id_matches(const sl_zigbee_address_info* set_a,
                                 const sl_zigbee_address_info* set_b);

#endif // SL_ZIGBEE_ADDRESS_INFO_H
