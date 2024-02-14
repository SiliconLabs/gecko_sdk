/***************************************************************************//**
 * @file high_datarate_phy.h
 * @brief High datarate phy APIs, types, macros and globals.
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

#ifndef HIGH_DATARATE_PHY__H
#define HIGH_DATARATE_PHY__H

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
sl_status_t sl_high_datarate_phy_transmit(uint8_t *payload);
/**
 * Configures transmit complete callback function
 *  @param[out] Function pointer to receive tx complete callback
 *              mac_index : 1 byte mac index - usually 0
 *              status: sl_status_t indicating transmit status
 *              PacketHeader of transmitted packet
 *              tag for the transmitted packet
 *
 */
void sl_high_datarate_phy_config_tx_complete_callback(void (*tx_complete_callback)(uint8_t mac_index, sl_status_t status, PacketHeader packet, uint8_t tag));
/**
 * API shall enable or disable high datarate phy packet reception
 *  @param[in] enable_f : Enable or Disable high datarate phy packet reception
 *
 */
RAIL_Status_t sl_high_datarate_phy_set_reception_enable (bool enable_f);
/**
 * Configures Rx complete callback function
 * Note that packet does not include 4 byte CRC.
 *  @param[in] Function pointer to receive callback
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *              linkQuality of received packet
 *              rssi of received packet
 *
 * Note: By default, sl_high_datarate_phy_rx_cb fires upon receiving a High-BW-phy packet
 * The user is free to override this callback by calling this function and supplying
 * a different receive callback
 */
void sl_high_datarate_phy_config_rx_callback(void (*rx_callback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi));
/**
 * Configures CSMA parameters for high datarate phy packet
 *
 * @param[in]  Pointer to csma params used on high datarate phy packets
 *
 */
void sl_high_datarate_phy_config_csma_params(RAIL_CsmaConfig_t *csma_params);
/**
 * Configures priority for high datarate phy packet
 * (Note that this is mainly for high datarate phy transmissions
 * @param[in]  Pointer to csma params used on high datarate phy packets
 *
 */
void sl_high_datarate_phy_config_radio_priorities(EmberMultiprotocolPriorities *priorities);

/**
 * Default receive callback function for High-BW-phy packets
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *              linkQuality of received packet
 *              rssi of received packet
 *
 * @param[out] packet pointer
 */
void sl_high_datarate_phy_rx_cb(uint8_t *packet, uint8_t linkQuality, int8_t rssi);
#endif //HIGH_DATARATE_PHY__H
