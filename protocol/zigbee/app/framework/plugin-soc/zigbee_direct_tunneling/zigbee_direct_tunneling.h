/***************************************************************************//**
 * @file zigbee_direct_tunneling.h
 * @brief Zigbee Direct - Zigbee Direct tunneling code
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

#ifndef SILABS_ZIGBEE_DIRECT_TUNNELING_H
#define SILABS_ZIGBEE_DIRECT_TUNNELING_H

#include "sl_bluetooth.h"

void sl_zigbee_direct_tunnel_indicate(uint8_t *packet, uint8_t length);
void sl_zigbee_direct_tunnel_write(uint8_t connection, uint8array *writeValue);

#endif // SILABS_ZIGBEE_DIRECT_TUNNELING_H
