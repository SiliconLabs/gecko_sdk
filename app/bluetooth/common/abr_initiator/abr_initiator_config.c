/***************************************************************************//**
 * @file
 * @brief ABR initiator configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_bt_api.h"
#include "abr_initiator_config.h"

sl_status_t abr_initiator_config_set_default(abr_initiator_config_t *config)
{
  // Main mode. mode_2: RTP, mode_1: RTT
  config->mode =                        sl_bt_cs_mode_pbr;
  // Submode
  config->submode =                     sl_bt_cs_mode_rtt;
  // Minimum suggested duration for each ABR subevent in microseconds. Range: 0x01 to 0xFFFFFF
  config->min_subevent_len =            1;
  // Maximum suggested duration for each ABR subevent in microseconds. Range: 0x01 to 0xFFFFFF
  config->max_subevent_len =            0xffff;
  // In 1.25ms units, 20ms
  config->min_connection_interval =     16;
  // In 1.25ms units, 20ms
  config->max_connection_interval =     16;
  // Scan interval
  config->scan_interval =               16;
  // Scan window
  config->scan_window =                 16;
  // Minimum duration in number of connection events between consecutive measurement procedure.
  // Range: 0x01 to 0xFF
  config->min_interval =                5;
  // Maximum duration in number of connection events between consecutive measurement procedure.
  // Range: 0x01 to 0xFF
  config->max_interval =                5;
  // Procedure execution number
  config->max_procedure_count =         1;
  // Scanning PHY
  config->scan_phy =                    sl_bt_gap_phy_coding_1m_uncoded;
  // Connection PHY
  config->phy =                         sl_bt_gap_phy_coding_1m_uncoded;
  // Only one channel is supported
  config->config_id =                   1;
  // Range: 0x02 to 0xA0
  config->min_main_mode_steps =         0xff;
  // Range: 0x02 to 0xA0
  config->max_main_mode_steps =         0xff;
  // The number of main mode steps taken from the end of the last ABR subevent
  // to be repeated at the beginning of the current ABR subevent directly after
  // the last Mode 0 step of that event. Range: 0x01 to 0x03
  config->main_mode_repetition =        0;
  // Number of Mode 0 steps to be included at the beginning of the test ABR subevent.
  config->mode0_step =                  3;
  // The number of times the channel_map field will be cycled through for non-Mode 0 steps within a ABR procedure.
  // Range: 0x01 to 0x03
  config->channel_map_repetition =      1;
  // Number of channels skipped in each rising and falling sequence. Range: 2 to 8
  config->ch3c_jump =                   2;
  // Maximum duration for each measurement procedure. Value in units of 0.625 ms
  // Range: 0x0001 to 0xFFFF
  config->max_procedure_duration =      0xffff;
  // Transmit power delta, in signed dB.
  config->tx_pwr_delta =                0x80;
  // Antenna configuration index. Range: 0x01 to 0x07
  config->antenna_config =              0;
  // BT address for filtering reflectors
  config->filter_address =              NULL;
  // The preferred peer-ordered antenna elements to be used by the remote device
  // for the antenna configuration denoted by the tone antenna config selection.
  config->preferred_peer_antenna =      0;
  // CS power
  config->max_tx_power_dbm =            20;
  // Value: 0x00. Write ABR configuration in the local controller only
  // Value: 0x01. Write ABR configuration in both the local and remote controller using a configuration procedure
  config->create_context =              1;
  // RSSI measurement enabled
  config->rssi_measurement_enabled =    false;
  // Reference RSSI value of the Tx device at 1.0 m distance in dBm
  config->rssi_tx_power =               -40.0F;
  // Peripheral latency, which defines how many connection intervals the peripheral
  // can skip if it has no data to send
  config->latency =                     0;
  // Supervision timeout
  config->timeout =                     200;
  // Minimum length of the connection event
  config->min_ce_length =               0;
  // Maximum length of the connection event
  config->max_ce_length =               0xffff;
  // Antenna identifier to be used for ABR
  config->cs_sync_antenna =             1;
  // Connection maximum TX power in dBm
  config->tx_power_requested_max_dbm =  10;
  // Connection minimum TX power in dBm
  config->tx_power_requested_min_dbm =  -10;
  // RTT type
  config->rtt_type =                    sl_bt_cs_rtt_type_fractional_96_bit_sounding;
  // Channel selection type.
  config->channel_selection_type =      sl_bt_cs_channel_selection_algorithm_3b;
  // Ch3c shape.
  config->ch3c_shape =                  sl_bt_cs_ch3c_shape_hat;
  // Companion signal enable/disable.
  config->companion_signal_enable =     sl_bt_cs_companion_signal_status_disable;

  switch (config->mode) {
    case sl_bt_cs_mode_rtt: // RTT
      config->submode = 0xff;
      break;
    case sl_bt_cs_mode_pbr: // Phase based
      config->submode = sl_bt_cs_mode_rtt;
      break;
    default:
      return SL_STATUS_INVALID_PARAMETER;
      break;
  }

  return SL_STATUS_OK;
}
