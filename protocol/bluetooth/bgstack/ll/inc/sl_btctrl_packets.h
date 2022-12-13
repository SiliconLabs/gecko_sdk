/***************************************************************************//**
 * @brief Packet API provides several functions to read detailed information from
 * the received packet.
 *
 * Currently only RSSI reading is supported.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_BTCTRL_PACKETS_H
#define SL_BTCTRL_PACKETS_H

#include <stdint.h>

typedef const void * sl_btctrl_packet_t;

/***************************************************************************//**
 * @addtogroup sl_btctrl_packets API to get detailed information of received packet
 * @{
 ******************************************************************************/

/**
 * Get RSSI of received packet
 *
 * @param packet Packet where the RSSI value is read from.
 * @return Signed RSSI value of the given packet in dBm.
 */
int8_t sl_btctrl_get_packet_rssi(sl_btctrl_packet_t packet);

/** @} sl_btctrl_packets */
#endif
