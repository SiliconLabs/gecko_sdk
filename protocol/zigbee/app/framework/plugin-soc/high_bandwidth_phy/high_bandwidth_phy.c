/***************************************************************************//**
 * @file high_bandwidth_phy.c
 * @brief High Bandwidth Phy implementation using rail_util_ieee802154_high_speed_phy
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
#include "high_bandwidth_phy.h"
#include "sl_zigbee_debug_print.h"
#include "zigbee_app_framework_event.h"
#include "ember-multi-network.h"
static sl_zigbee_event_t app_cli_event;

#define MIN_PAYLOAD_LEN 3
#define MAX_PAYLOAD_LEN 252
#define FUTURE_MAX_PAYLOAD_LEN 2049
// In future parts, there is expected to be support for 2047 byte packets
static uint8_t local_byte_array[FUTURE_MAX_PAYLOAD_LEN];
static uint32_t high_bw_phy_rx_packet_count = 0;
static uint32_t high_bw_phy_tx_packet_count = 0;
static void app_cli_event_handler(sl_zigbee_event_t *event);
extern void (*sl_high_bw_phy_rx_callback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi);
extern sl_status_t sl_mac_send_raw_high_bandwidth_phy_message(uint8_t nwk_index, uint8_t *payload);
extern void sli_mac_lower_mac_set_high_bw_csma_params (RAIL_CsmaConfig_t *csmaParams);
extern void sli_mac_lower_mac_set_high_bw_phy_radio_priorities (EmberMultiprotocolPriorities *priorities);
/**
 * Default receive callback function for High-BW-phy packets
 * Note that packet does not include 4 byte CRC
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *              linkQuality of received packet
 *              rssi of received packet
 *
 * @param[out] packet pointer
 */
void sl_high_bw_phy_rx_cb(uint8_t *packet, uint8_t linkQuality, int8_t rssi)
{
  high_bw_phy_rx_packet_count++;
  sl_zigbee_app_debug_print(" Received Packet : ");
  for (uint16_t i = 2; i <= (uint16_t)packet[0] + ((uint16_t)packet[1] << 8); i++ ) {
    sl_zigbee_app_debug_print("%02X ", packet[i]);
  }
  sl_zigbee_app_debug_println("\nLQI : %d\nRSSI : %d\n", linkQuality, rssi);
}
/**
 * Init function for High-BW-Phy events - This is called using the templates
 *
 *  @param[in] init_level
 */
void sli_high_bw_phy_init(uint8_t init_level)
{
  switch (init_level) {
    case SL_ZIGBEE_INIT_LEVEL_EVENT: {
      sl_zigbee_event_init(&app_cli_event, app_cli_event_handler);
      break;
    }
    case SL_ZIGBEE_INIT_LEVEL_DONE: {
      sl_high_bw_phy_rx_callback = sl_high_bw_phy_rx_cb;
      break;
    }
  }
}
/**
 * Configures receive callback function
 *
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
void sl_high_bw_phy_config_rx_callback(void (*rx_callback)(uint8_t *packet, uint8_t linkQuality, int8_t rssi))
{
  sl_high_bw_phy_rx_callback = rx_callback;
}
/**
 * Configures CSMA parameters for high bw phy packet
 *
 * @param[in]  Pointer to csma params used on high speed phy packets
 *
 */
void sl_high_bw_phy_config_csma_params(RAIL_CsmaConfig_t *csma_params)
{
  sli_mac_lower_mac_set_high_bw_csma_params(csma_params);
}
/**
 * Configures priority for high bw phy packet
 *
 * @param[in]  Pointer to csma params used on high speed phy packets
 *
 */
void sl_high_bw_phy_config_radio_priorities(EmberMultiprotocolPriorities *priorities)
{
  sli_mac_lower_mac_set_high_bw_phy_radio_priorities(priorities);
}

/**
 * Transmits a High-BW-Phy packet consisting of <len-1> bytes of payload
 * Note that there is a 4 byte CRC which is tacked on later and is not part
 * of the packet parameter
 * @param[in] payload Pointer to bytes of transmitted data
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 *
 * CAUTION: Do not call this function from any other RTOS task context except Zigbee
 * This fuction manipulates buffers and will cause unpredictable errors if this rule is not
 * followed
 */
sl_status_t sl_high_bw_phy_transmit(uint8_t *payload)
{
  uint16_t requested_len = (payload[1] << 8) + payload[0];
  if ( requested_len < MIN_PAYLOAD_LEN  || requested_len > MAX_PAYLOAD_LEN ) {
    return SL_STATUS_INVALID_PARAMETER;
  }
  if (sli_zigbee_state != EMBER_JOINED_NETWORK) {
    return SL_STATUS_INVALID_MODE;
  }
  high_bw_phy_tx_packet_count++;
  return sl_mac_send_raw_high_bandwidth_phy_message(sli_zigbee_get_current_network_index(), payload);
}
/**
 * CLI Command handler to transmit High-BW-Phy packet
 * @param[in] length Transmits a packet that contains <length-1> bytes using the high-BW-phy
 *              packet[0] packet[1] : 2 byte Length (packet[1] << 8 + packet[0])
 *              packet[1] .. packet[Length] payload
 */
static uint16_t length;
void sl_high_bw_phy_tx_command(sl_cli_command_arg_t *arguments)
{
  length = sl_cli_get_argument_uint16(arguments, 0);
  sl_zigbee_event_set_active(&app_cli_event);
}
/**
 * Event handler to call sl_high_bw_phy_transmit function
 * This additional step is necessary because the function manipulates buffers
 * and this cannot be done from anywhere except the zigbee task context in an RTOS
 * application
 */
static void app_cli_event_handler(sl_zigbee_event_t *event)
{
  if ( length > FUTURE_MAX_PAYLOAD_LEN ) {
    sl_zigbee_app_debug_println("Status = 0x%02x", SL_STATUS_INVALID_PARAMETER);
    return;
  }
  local_byte_array[0] = (uint8_t)(length & 0xFF);
  local_byte_array[1] = (uint8_t)(length >> 8);
  for (uint16_t i = 2; i <= length; i++) {
    local_byte_array[i] = i - 1;
  }

  sl_zigbee_app_debug_println("Status = 0x%02x", sl_high_bw_phy_transmit(local_byte_array));
}
/**
 * Clears count of High-BW-Phy received and transmitted packets
 *
 */
void sl_high_bw_phy_clr_stats_command(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  high_bw_phy_rx_packet_count = 0;
  high_bw_phy_tx_packet_count = 0;
}
/**
 * Prints count of High-BW-Phy received and transmitted packets
 *
 */
void sl_high_bw_phy_print_stats_command(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
  sl_zigbee_app_debug_println("Total number of packets received : %d", high_bw_phy_rx_packet_count);
  sl_zigbee_app_debug_println("Total number of packets transmitted : %d", high_bw_phy_tx_packet_count);
}
