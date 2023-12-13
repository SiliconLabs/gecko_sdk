/***************************************************************************//**
 * @file high_bandwidth_phy.h
 * @brief High bandwidth phy APIs, types, macros and globals.
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

#ifndef HIGH_BANDWIDTH_PHY__H
#define HIGH_BANDWIDTH_PHY__H

#include PLATFORM_HEADER
#include "sl_status.h"
#include "rail_types.h"
#include "buffer_manager/buffer-management.h"
#include "sl_cli.h"

/**
 * Transmits a High-BW-Phy packet consisting of <len-1> bytes of payload
 * Note that there is a 4 byte CRC which is tacked on later and is not part
 * of the packet parameter
 * @param[in] payload Pointer to bytes of transmitted data
 *                packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *                packet[2] .. packet[Length] payload
 *
 * CAUTION: Do not call this function from any other RTOS task context except Zigbee
 * This calls into a function that manipulates buffers and will cause unpredictable errors if this rule is not
 * followed
 */
sl_status_t sl_high_bw_phy_transmit(uint8_t *payload);
/**
 * Configures receive callback function
 * Note that packet does not include 4 byte CRC.
 *  @param[in] Function pointer to receive callback
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *              linkQuality of received packet
 *              rssi of received packet
 *
 * Note: By default, sl_high_bw_phy_rx_cb fires upon receiving a High-BW-phy packet
 * The user is free to override this callback by calling this function and supplying
 * a different receive callback
 */
void sl_high_bw_phy_config_rx_callback(void (*rx_callback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi));
/**
 * Configures CSMA parameters for high bw phy packet
 *
 * @param[in]  Pointer to csma params used on high speed phy packets
 *
 */
void sl_high_bw_phy_config_csma_params(RAIL_CsmaConfig_t *csma_params);
/**
 * Configures priority for high bw phy packet
 * (Note that this is mainly for high bw phy transmissions
 * @param[in]  Pointer to csma params used on high speed phy packets
 *
 */
void sl_high_bw_phy_config_radio_priorities(EmberMultiprotocolPriorities *priorities);
/**
 * Clears count of High-BW-Phy received packets
 *
 */
void sl_high_bw_phy_clr_stats_command(sl_cli_command_arg_t *arguments);
/**
 * Prints count of High-BW-Phy received packets
 *
 */
void sl_high_bw_phy_print_stats_command(sl_cli_command_arg_t *arguments);
/**
 * CLI Command handler to transmit High-BW-Phy packet
 * @param[in] length Transmits a packet that contains <length-1> bytes using the high-BW-phy
 */
void sl_high_bw_phy_tx_command(sl_cli_command_arg_t *arguments);
/**
 * Default receive callback function for High-BW-phy packets
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *              linkQuality of received packet
 *              rssi of received packet
 *
 * @param[out] packet pointer
 */
void sl_high_bw_phy_rx_cb(uint8_t *packet, uint8_t linkQuality, int8_t rssi);
#endif //HIGH_BANDWIDTH_PHY__H
