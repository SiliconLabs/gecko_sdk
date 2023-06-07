/***************************************************************************//**
 * @file sl_zigbee_zdo_dlk_negotiation.h
 * @brief declarations of ZDO interface for dynamic link key negotiation
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

#ifndef SL_ZIGBEE_ZDO_CONFIGURATION_H
#define SL_ZIGBEE_ZDO_CONFIGURATION_H

#include "core/ember-stack.h"
#include "core/ember-multi-network.h"
#include "include/error.h"

/**
 * @brief Send out a zdo get configuration request
 */
sl_status_t sl_zigbee_zdo_get_configuration_req(EmberNodeId device_short, bool encrypt, uint8_t *tag_ids, uint8_t count);

/**
 * @brief Send out a zdo setconfiguration request
 */
sl_status_t sl_zigbee_zdo_set_add_configuration(uint8_t tag_id, size_t zdo_config_arg_len, uint8_t *zdo_config_arg);

/**
 * @brief Set the TLVs for a zdo set configuration request
 */
sl_status_t sl_zigbee_zdo_set_send_configuration_req(EmberNodeId device_short, bool encrypt);

#endif //SL_ZIGBEE_ZDO_CONFIGURATION_H
