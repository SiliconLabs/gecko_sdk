/***************************************************************************//**
 * @file
 * @brief app_process.h
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#ifndef SL_FLEX_MODE_SWITCH_H
#define SL_FLEX_MODE_SWITCH_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "rail.h"
#include "rail_config.h"
#include "sl_status.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define MAX_SELECTEBLE_CHANNEL WISUN_MODESWITCHPHRS_ARRAY_SIZE
#define MODE_SWITCH_DURATION_MAX 10U
#define PHY_MODE_ID_DOES_NOT_EXIST (0xFFFFU)
#define CHANNEL_DOES_NOT_EXIST (0xFFFFU)

/** Mode switch states */
typedef enum mode_switch_state {
  MS_IDLE,
  MS_REQUESTED,
  MS_INITED,
  MS_SENDING_MS_START_PACKET,
  MS_ON_NEW_PHY,
  MS_RETURN_TO_BASE_PHY,
  MS_SENDING_MS_END_PACKET
} mode_switch_state_t;

/** PHY modulation scheme */
typedef enum phy_modulation_e {
  M_OFDM,       ///< QFDM
  M_OQPSK,      ///< OQPSK
  M_BPSK,       ///< BPSK
  M_GFSK,       ///< GFSK
  M_2FSK,       ///< 2FSK
  M_UNDEFINED   ///< UNDEFINED
} phy_modulation_e;

typedef struct mode_switch_channel {
  uint16_t channel_number;
  uint16_t phy_mode_id;
  phy_modulation_e modulation;
  uint8_t phy_mode_index;
} mode_switch_channel_t;

typedef struct radio_info {
  mode_switch_channel_t channel_list[MAX_SELECTEBLE_CHANNEL];
  uint8_t mode_switch_capable_channels;
} radio_info_t;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * API to get the PHY's FCS setting of the given channel.
 *
 * @param None
 * @returns PHY's FCS setting of the given channel
 *****************************************************************************/
uint8_t get_fsk_fcs_type(void);

/**************************************************************************//**
 * API to set the WiSUN FSK FCS type field of the packet header.
 *
 * @param new_fsk_fcs_type New fcs_type to set
 * @returns None
 *****************************************************************************/
void set_fsk_fcs_type(uint8_t new_fsk_fcs_type);

/**************************************************************************//**
 * API to get the PHY's whitening setting of the given channel.
 *
 * @param None
 * @returns PHY's whitening setting of the given channel
 *****************************************************************************/
uint8_t get_fsk_whitening(void);

/**************************************************************************//**
 * API to set the WiSUN FSK whitening field of the packet header.
 *
 * @param new_fsk_whitening New whitening to set
 * @returns None
 *****************************************************************************/
void set_fsk_whitening(uint8_t new_fsk_whitening);

/**************************************************************************//**
 * API to get the PHY's OFDM rate setting of the given channel.
 *
 * @param None
 * @returns PHY's OFDM rate setting of the given channel
 *****************************************************************************/
uint8_t get_ofdm_rate(void);

/**************************************************************************//**
 * API to set the WiSUN OFDM rate field of the packet header.
 *
 * @param new_ofdm_rate New rate to set
 * @returns None
 *****************************************************************************/
void set_ofdm_rate(uint8_t new_ofdm_rate);

/**************************************************************************//**
 * API to get the PHY's OFDM scrambler setting of the given channel.
 *
 * @param None
 * @returns PHY's OFDM scrambler setting of the given channel
 *****************************************************************************/
uint8_t get_ofdm_scrambler(void);

/**************************************************************************//**
 * API to set the WiSUN OFDM scrambler field of the packet header.
 *
 * @param new_ofdm_scrambler New scrambler to set
 * @returns None
 *****************************************************************************/
void set_ofdm_scrambler(uint8_t new_ofdm_scrambler);

/**************************************************************************//**
 * API to get the extra print setting of the TX and RX packets.
 *
 * @param None
 * @returns Extra print setting of the TX and RX packets is ON/OFF
 *****************************************************************************/
bool get_print_packet_details(void);

/**************************************************************************//**
 * API to set the the extra print setting of the TX and RX packets.
 *
 * @param new_print_packet_details New print settings
 * @returns None
 *****************************************************************************/
void set_print_packet_details(bool new_print_packet_details);

/**************************************************************************//**
 * This function calibrates the radio.
 *
 * @param rail_handle A RAIL insance handle
 * @returns None
 *****************************************************************************/
void calibrate_radio(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to init and set the IEEE802154 hardware acceleration.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void init_ieee802154_for_mode_switch(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to enable DUALSYNC in Tx and Rx in case of FSK FEC usage.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void init_rx_option_for_mode_switch(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to enable Mode Switch and dynamic FEC.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void init_ieee802154g_option_for_mode_switch(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to diasble MAC filtering on packet received.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void enable_promiscuous_mode_for_mode_switch(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to enable Start and End event for Mode Switch.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void enable_mode_switch_events(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to initialize the power amplifier.
 *
 * @param None
 * @returns None
 *****************************************************************************/
void init_rail_pa_settings(void);

/**************************************************************************//**
 * API to update the power amplifier settings.
 *
 * @param rail_handle A RAIL instance handle
 * @param channel Radio channel to update the PA settings for
 * @returns None
 *****************************************************************************/
void update_rail_pa_settings(RAIL_Handle_t rail_handle, uint16_t channel);

/**************************************************************************//**
 * API to configure the basic parameters for the mode switch process.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *
 * Radio should useFSK modulation settings.
 *****************************************************************************/
void init_mode_switch(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * The API to get the payload from the radio frame.
 *
 * @param rx_destination Where should the full packet be unpacked
 * @param packet_information A place to store all the information of the packet
 * @param start_of_payload Pointer where the payload starts
 * @param modulation Modulation of the sending channel
 * @returns The length of the received payload
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination,
                       const RAIL_RxPacketInfo_t *packet_information,
                       uint8_t **start_of_payload,
                       phy_modulation_e modulation);

/**************************************************************************//**
 * API to prepare the packet for sending and load it into the RAIL TX FIFO.
 *
 * @param rail_handle A RAIL instance handle
 * @param out_data The payload buffer
 * @param length The length of the payload
 * @param modulation Modulation of the sending channel
 * @returns None
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle,
                     uint8_t *out_data,
                     uint16_t length,
                     phy_modulation_e modulation);

/**************************************************************************//**
 * API to calculate modulation from PHY mode id.
 *
 * @param phy_mode_id Phy mode id to calculate the modulation from
 * @returns Modulation type
 *****************************************************************************/
phy_modulation_e calculate_modulation_from_phy_mode_id(const uint8_t phy_mode_id);

/**************************************************************************//**
 * API to update channel configurations locally.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
void update_channel_list(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to print channel configurations.
 *
 * @param None
 * @returns None
 *****************************************************************************/
void print_channel_list(void);

/**************************************************************************//**
 * API to trigger mode switch transmission.
 *
 * @param rail_handle A RAIL instance handle
 * @returns SL_STATUS_OK on success, errorcode on error
 *****************************************************************************/
sl_status_t trig_mode_switch_tx(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to get the current state of the mode switch process.
 *
 * @param None
 * @returns Current state of the mode switch process
 *****************************************************************************/
mode_switch_state_t get_ms_state(void);

/**************************************************************************//**
 * API to get the text equivalent of the current mode switch state.
 *
 * @param None
 * @returns Text equivalent of the current mode switch state
 *****************************************************************************/
const char* get_ms_state_str(void);

/**************************************************************************//**
 * API to set the current state of the mode switch process.
 *
 * @param new_state New mode switch state to set
 * @returns None
 *****************************************************************************/
void set_ms_state(mode_switch_state_t new_state);

/**************************************************************************//**
 * API to get the text equivalent of the modulation of the current channel.
 *
 * @param None
 * @returns Text equivalent of the modulation of the current channel
 *****************************************************************************/
const char* get_phy_modulation_str(void);

/**************************************************************************//**
 * API to request mode switch.
 *
 * @param None
 * @returns SL_STATUS_OK on success
 *          SL_STATUS_INVALID_STATE if ms_state is not MS_IDLE
 *****************************************************************************/
sl_status_t request_mode_switch(void);

/**************************************************************************//**
 * API to count the index of the given phy_mode_id.
 *
 * @param phy_mode_id Phy mode id to check
 * @returns Index of the phy mode id if exists
 *          PHY_MODE_ID_DOES_NOT_EXIST if not
 *****************************************************************************/
uint16_t count_phy_mode_id_index(const uint8_t phy_mode_id);

/**************************************************************************//**
 * API to get the index of the given channel.
 *
 * @param new_channel Channel to check
 * @returns Index of the channel if exists
 *          CHANNEL_DOES_NOT_EXIST if not
 *****************************************************************************/
uint16_t get_channel_index(const uint16_t new_channel);

/**************************************************************************//**
 * API to set new phy mode id for mode switch.
 *
 * @param new_phy_mode_id New phy mode id to set
 * @returns SL_STATUS_OK on success
 *          SL_STATUS_INVALID_PARAMETER if new_phy_mode_id does not exist
 *****************************************************************************/
sl_status_t set_new_phy_mode_id(const uint8_t new_phy_mode_id);

/**************************************************************************//**
 * API to get the currently used phy mode id.
 *
 * @param None
 * @returns Currently used phy mode id
 *****************************************************************************/
uint8_t get_phy_mode_id(void);

/**************************************************************************//**
 * API to set time the device spends on the new channel.
 *
 * @param duration Time in seconds the device spends on the new channel, 0 = inf
 * @returns SL_STATUS_OK on success
 *          SL_STATUS_INVALID_PARAMETER if duration is bigger,
 *          than MODE_SWITCH_DURATION_MAX
 *****************************************************************************/
sl_status_t set_mode_switch_duration(const uint32_t duration);

/**************************************************************************//**
 * API to set the currently used channel.
 *
 * @param new_channel New channel to set
 * @returns RAIL_STATUS_NO_ERROR on success, RAIL errorcode on error
 *****************************************************************************/
RAIL_Status_t set_channel(const uint16_t new_channel);

/**************************************************************************//**
 * API to set the currently used channel.
 *
 * @param None New channel to set
 * @returns The currently used channel
 *****************************************************************************/
uint16_t get_channel(void);

/**************************************************************************//**
 * API to get the new channel to be set with the mode switch process.
 *
 * @param None
 * @returns New channel to be set with the mode switch process
 *****************************************************************************/
uint16_t get_ms_new_channel(void);

/**************************************************************************//**
 * API to get the channel to be set after returning from mode switch.
 *
 * @param None
 * @returns Channel to set after returning from mode switch
 *****************************************************************************/
uint16_t get_base_channel(void);

/**************************************************************************//**
 * API to switch the radio channel during the mode switch process.
 *
 * @param rail_handle A RAIL instance handle
 * @returns RAIL_STATUS_NO_ERROR on success, RAIL errorcode on error
 *****************************************************************************/
RAIL_Status_t switch_to_ms_channel(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to set the radio back to the base channel from the mode switch channel.
 *
 * @param None
 * @returns RAIL_STATUS_NO_ERROR on success, RAIL errorcode on error
 *****************************************************************************/
RAIL_Status_t return_to_base_channel(void);

/**************************************************************************//**
 * API to get the PHY mode id of the given channel.
 *
 * @param channel Radio channel
 * @returns PHY mode id of the given channel
 *****************************************************************************/
uint8_t get_phy_mode_id_from_channel(const uint16_t channel);

/**************************************************************************//**
 * API to get the PHY modulation of the given channel.
 *
 * @param channel Radio channel
 * @returns PHY modulation of the given channel
 *****************************************************************************/
phy_modulation_e get_phy_modulation_from_channel(const uint16_t channel);

#endif  // SL_FLEX_MODE_SWITCH_H
