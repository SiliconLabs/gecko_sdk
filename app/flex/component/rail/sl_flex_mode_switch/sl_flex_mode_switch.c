/***************************************************************************//**
 * @file
 * @brief app_cli.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "sl_component_catalog.h"
#include "rail.h"
#include "sl_rail_util_init.h"
#include "app_init.h"
#include "sl_simple_led_instances.h"
#include "app_log.h"
#include "sl_rail_util_init_inst0_config.h"
#include "rail_config.h"
#include "app_assert.h"
#include "sl_flex_mode_switch.h"
#include "sl_flex_packet_asm.h"
#include "sl_sleeptimer.h"
#include "sl_flex_mode_switch.h"
#include "pa_conversions_efr32.h"
#include "sl_status.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define MSPHR_LENGTH 2U
#define MS_PACKET_LENGTH 18U

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// List of detected channel numbers
radio_info_t radio_info = {
  .mode_switch_capable_channels = 0U,
  .channel_list = { 0U }
};

const char* mode_switch_state_strings[] = {
  "MS_IDLE",
  "MS_REQUESTED",
  "MS_INITED",
  "MS_SENDING_MS_START_PACKET",
  "MS_ON_NEW_PHY",
  "MS_RETURN_TO_BASE_PHY",
  "MS_SENDING_MS_END_PACKET"
};

const char* phy_modulation_strings[] = {
  "M_OFDM",
  "M_OQPSK",
  "M_BPSK",
  "M_GFSK",
  "M_2FSK",
  "M_UNDEFINED"
};

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// Mode switch packet header
static uint8_t ms_phr[MSPHR_LENGTH] = { 0, 0 };
/// Current state of the mode switch process
static volatile mode_switch_state_t ms_state = MS_IDLE;
/// Phy mode id to switch
static volatile uint8_t ms_new_phy_mode_id = 0xFFU;
/// Radio channel number after mode switch
volatile uint16_t ms_new_channel = 0xFFFFU;
/// The channel used for the upcoming transmission
static volatile uint16_t current_channel = 0U;
/// The channel the device returns to from mode switch
static volatile uint16_t base_channel = 0U;
/// Buffer of the packet to be sent
static uint8_t tx_frame_buffer[128];
/// The time in seconds that the device is in the new phy during mode switch
static volatile uint32_t ms_duration = 0U;
/// Timer for the mode switch process
static sl_sleeptimer_timer_handle_t mode_switch_timer;
/// Radio power configuration pointer
static RAIL_TxPowerConfig_t *txPowerConfigPtr = NULL;
/// Radio power
static RAIL_TxPower_t power = 140U;
/// WiSUN FSK packet FCS is on/off
static uint8_t fsk_fcs_type = 0U;
/// WiSUN FSK packet whitening is on/off
static uint8_t fsk_whitening = 1U;
/// WiSUN OFDM, rate specifies the data rate of the payload and is equal to the numerical value of the MCS
static uint8_t ofdm_rate = 0x00;
// rate: 5 bits wide,
//  The Rate field (RA4-RA0) specifies the data rate of the payload
//  and is equal to the numerical value of the MCS
// 0x0 BPSK, coding rate 1/2, 4 x frequency repetition
// 0x1 BPSK, coding rate 1/2, 2 x frequency repetition
// 0x2 QPSK, coding rate 1/2, 2 x frequency repetition
// 0x3 QPSK, coding rate 1/2
// 0x4 QPSK, coding rate 3/4
// 0x5 16-QAM, coding rate 1/2
// 0x6 16-QAM, coding rate 3/4
/// WiSUN OFDM, the scrambler field specifies the scrambling seed
static uint8_t ofdm_scrambler = 0x00;
/// Enable to print extra information about the received or sent packets
static bool print_packet_details = true;

/// A configuration structure for IEEE 802.15.4 in RAIL.
static const RAIL_IEEE802154_Config_t config = {
  .addresses = NULL,
  .ackConfig = {
    .enable = true,
    .ackTimeout = 672,
    .rxTransitions = {
      .success = RAIL_RF_STATE_RX,
      .error = RAIL_RF_STATE_RX
    },
    .txTransitions = {
      .success = RAIL_RF_STATE_RX,
      .error = RAIL_RF_STATE_RX
    }
  },
  .timings = {
    .idleToTx = 110,
    .idleToRx = 110,
    .rxToTx = 192,
    // Make txToRx slightly lower than desired to make sure we get to RX in time
    .txToRx = 182,
    .rxSearchTimeout = 0,
    .txToRxSearchTimeout = 0,
    .txToTx = 0
  },
  .framesMask = RAIL_IEEE802154_ACCEPT_STANDARD_FRAMES,
  .promiscuousMode = false,
  .isPanCoordinator = false,
  .defaultFramePendingInOutgoingAcks = false
};

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
* Callback function for the mode switch timer
*
* @param handle Pointer to the sleeptimer handle
* @param data Pointer to delay flag
******************************************************************************/
static void ms_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data);

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * This function gets the static fcs_type value.
 *****************************************************************************/
uint8_t get_fsk_fcs_type(void)
{
  return fsk_fcs_type;
}

/******************************************************************************
 * This function sets the static fcs_type value.
 *****************************************************************************/
void set_fsk_fcs_type(uint8_t new_fsk_fcs_type)
{
  if (new_fsk_fcs_type < 2) {
    fsk_fcs_type = new_fsk_fcs_type;
  } else {
    app_log_warning("Set FSK type: %d is higher then 0x01\n", new_fsk_fcs_type);
  }
}

/******************************************************************************
 * This function gets the static whitening value.
 *****************************************************************************/
uint8_t get_fsk_whitening(void)
{
  return fsk_whitening;
}

/******************************************************************************
 * This function sets the static fsk_whitening value.
 *****************************************************************************/
void set_fsk_whitening(uint8_t new_fsk_whitening)
{
  if (new_fsk_whitening < 2) {
    fsk_whitening = new_fsk_whitening;
  } else {
    app_log_warning("Set FSK whitening: %d is higher then 0x01\n", new_fsk_whitening);
  }
}

/******************************************************************************
 * This function gets the static rate value.
 *****************************************************************************/
uint8_t get_ofdm_rate(void)
{
  return ofdm_rate;
}

/******************************************************************************
 * This function sets the static rate value.
 *****************************************************************************/
void set_ofdm_rate(uint8_t new_ofdm_rate)
{
  if (new_ofdm_rate < 7) {
    ofdm_rate = new_ofdm_rate;
    if (get_phy_modulation_from_channel(current_channel) == M_OFDM) {
      ms_new_phy_mode_id = get_phy_mode_id_from_channel(current_channel);
      ms_new_phy_mode_id = ms_new_phy_mode_id + ofdm_rate;
    }
  } else {
    app_log_warning("Set OFDM rate: %d is higher then 0x06\n", new_ofdm_rate);
  }
}

/******************************************************************************
 * This function gets the static scrambler value.
 *****************************************************************************/
uint8_t get_ofdm_scrambler(void)
{
  return ofdm_scrambler;
}

/******************************************************************************
 * This function sets the static scrambler value.
 *****************************************************************************/
void set_ofdm_scrambler(uint8_t new_ofdm_scrambler)
{
  ofdm_scrambler = new_ofdm_scrambler;
}

/******************************************************************************
 * This function gets the static print_packet_details value.
 *****************************************************************************/
bool get_print_packet_details(void)
{
  return print_packet_details;
}

/******************************************************************************
 * This function sets the static print_packet_details value.
 *****************************************************************************/
void set_print_packet_details(bool new_print_packet_details)
{
  print_packet_details = new_print_packet_details;
}

/******************************************************************************
 * This function calibrates the radio.
 *****************************************************************************/
void calibrate_radio(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "calibrate_radio error: NULL handle\n");

  // Calibration on OFDM is sufficient for FSK as well
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  RAIL_AntennaSel_t rf_path = RAIL_ANTENNA_AUTO;

  // Finding the first channel with OFDM modulation
  for (uint8_t i = 0; i < radio_info.mode_switch_capable_channels; i++) {
    if (radio_info.channel_list[i].modulation == M_OFDM) {
      current_channel = radio_info.channel_list[i].channel_number;
      break;
    }
  }

  RAIL_StartRx(rail_handle, current_channel, NULL);
  status = RAIL_GetRfPath(rail_handle, &rf_path);

  if (status == RAIL_STATUS_NO_ERROR) {
    RAIL_Idle(rail_handle, RAIL_IDLE_ABORT, false);
    status = RAIL_CalibrateIrAlt(rail_handle, NULL, rf_path);
    if (status == RAIL_STATUS_NO_ERROR) {
      app_log_info("IR calibration OK\n");
    } else {
      app_log_warning("IR calibration ERROR: %d\n", (uint8_t)status);
    }
  }
}

/******************************************************************************
 * API to init and set the IEEE802154 hardware acceleration.
 *****************************************************************************/
void init_ieee802154_for_mode_switch(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "init_ieee802154_for_mode_switch error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  status = RAIL_IEEE802154_Init(rail_handle, &config);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_IEEE802154_Init error: %d\n",
             status);
}

/******************************************************************************
 * API to enable DUALSYNC in Tx and Rx in case of FSK FEC usage.
 *****************************************************************************/
void init_rx_option_for_mode_switch(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "init_rx_option_for_mode_switch error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  RAIL_RxOptions_t enable_dualsync = RAIL_RX_OPTION_ENABLE_DUALSYNC;

  status = RAIL_ConfigRxOptions(rail_handle,
                                RAIL_RX_OPTIONS_ALL,
                                enable_dualsync);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_ConfigRxOptions error: %d\n",
             status);
}

/******************************************************************************
 * API to enable Mode Switch and dynamic FEC.
 *****************************************************************************/
void init_ieee802154g_option_for_mode_switch(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "init_ieee802154g_option_for_mode_switch error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  RAIL_IEEE802154_GOptions_t ieee802154g_option =
    (1 << RAIL_IEEE802154_G_OPTION_GB868_SHIFT)
    | (1 << RAIL_IEEE802154_G_OPTION_DYNFEC_SHIFT)
    | (1 << RAIL_IEEE802154_G_OPTION_WISUN_MODESWITCH_SHIFT);

  status = RAIL_IEEE802154_ConfigGOptions(rail_handle,
                                          RAIL_IEEE802154_G_OPTIONS_ALL,
                                          ieee802154g_option);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_IEEE802154_ConfigGOptions error: %d\n",
             status);
}

/******************************************************************************
 * API to diasble MAC filtering on packet received.
 *****************************************************************************/
void enable_promiscuous_mode_for_mode_switch(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "enable_promiscuous_mode_for_mode_switch error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  status = RAIL_IEEE802154_SetPromiscuousMode(rail_handle, true);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_IEEE802154_SetPromiscuousMode error: %d\n",
             status);
}

/******************************************************************************
 * API to enable Start and End event for Mode Switch.
 *****************************************************************************/
void enable_mode_switch_events(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "enable_mode_switch_events error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  RAIL_Events_t enable_modeswitch = SL_RAIL_UTIL_INIT_EVENT_INST0_MASK
                                    | RAIL_EVENT_IEEE802154_MODESWITCH_START
                                    | RAIL_EVENT_IEEE802154_MODESWITCH_END;

  status = RAIL_ConfigEvents(rail_handle, RAIL_EVENTS_ALL, enable_modeswitch);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_ConfigEvents error: %d\n",
             status);
}

/******************************************************************************
 * API to initialize the power amplifier.
 *****************************************************************************/
void init_rail_pa_settings(void)
{
  txPowerConfigPtr = sl_rail_util_pa_get_tx_power_config_subghz();
}

/******************************************************************************
 * API to update the power amplifier settings.
 *****************************************************************************/
void update_rail_pa_settings(RAIL_Handle_t rail_handle, uint16_t channel)
{
  app_assert(rail_handle != NULL,
             "update_rail_pa_settings error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  phy_modulation_e modulation = get_phy_modulation_from_channel(channel);

#if defined(SL_CATALOG_RAIL_UTIL_EFF_PRESENT)
  if (modulation == M_OFDM) {
    if (txPowerConfigPtr->mode != RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM) {
      txPowerConfigPtr->mode = RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM;
      status = RAIL_ConfigTxPower(rail_handle, txPowerConfigPtr);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
      status = RAIL_SetTxPowerDbm(rail_handle, power);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
    }
  } else if (modulation == M_2FSK) {
    if (txPowerConfigPtr->mode != RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM) {
      txPowerConfigPtr->mode = RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM;
      status = RAIL_ConfigTxPower(rail_handle, txPowerConfigPtr);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
      status = RAIL_SetTxPowerDbm(rail_handle, power);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
    }
  }
#else
  if (modulation == M_OFDM) {
    if (txPowerConfigPtr->mode != RAIL_TX_POWER_MODE_OFDM_PA) {
      txPowerConfigPtr->mode = RAIL_TX_POWER_MODE_OFDM_PA;
      status = RAIL_ConfigTxPower(rail_handle, txPowerConfigPtr);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
      status = RAIL_SetTxPowerDbm(rail_handle, power);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
    }
  } else if (modulation == M_2FSK) {
    if (txPowerConfigPtr->mode != RAIL_TX_POWER_MODE_SUBGIG_HIGHEST) {
      txPowerConfigPtr->mode = RAIL_TX_POWER_MODE_SUBGIG_HIGHEST;
      status = RAIL_ConfigTxPower(rail_handle, txPowerConfigPtr);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
      status = RAIL_SetTxPowerDbm(rail_handle, power);
      app_assert(status == RAIL_STATUS_NO_ERROR, "PA setting failed");
    }
  }
#endif
  else {
    app_log_warning("Unknown modulation %d\n", modulation);
  }
}

/******************************************************************************
 * This function configures the basic parameters for the mode switch process.
 *****************************************************************************/
void init_mode_switch(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "init_mode_switch error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  // Save available channels locally
  update_channel_list(rail_handle);

  // Radio calibration
  calibrate_radio(rail_handle);

  base_channel = channelConfigs[0]->configs[0].channelNumberStart;
  current_channel = base_channel;
  set_new_phy_mode_id(radio_info.channel_list[0].phy_mode_id);

  RAIL_StartRx(rail_handle, current_channel, NULL);

  // Set Radio to Idle to be able to set the following settings
  RAIL_Idle(rail_handle, RAIL_IDLE, true);

  // Init and set the IEEE802154 hardware acceleration
  init_ieee802154_for_mode_switch(rail_handle);

  // Enable DUALSYNC in Tx and Rx in case of FSK FEC usage
  // in the channel-based multi-PHY
  init_rx_option_for_mode_switch(rail_handle);

  // Enable Mode Switch and dynamic FEC
  init_ieee802154g_option_for_mode_switch(rail_handle);

  status = RAIL_StartRx(rail_handle, current_channel, NULL);
  app_assert(status == RAIL_STATUS_NO_ERROR,
             "RAIL_StartRx error: %d\n",
             status);

  // Avoid MAC filtering on packet received
  enable_promiscuous_mode_for_mode_switch(rail_handle);

  // Enable Start and End event for Mode Switch
  enable_mode_switch_events(rail_handle);

  // Init the PA setting for Mode Switch
  init_rail_pa_settings();
}

/******************************************************************************
 * API to calculate modulation from PHY mode id.
 *****************************************************************************/
phy_modulation_e calculate_modulation_from_phy_mode_id(const uint8_t phy_mode_id)
{
  phy_modulation_e modulation = M_UNDEFINED;

  if ((phy_mode_id >> 4) < 2) {
    modulation = M_2FSK;
  } else {
    modulation = M_OFDM;
  }

  return modulation;
}

/******************************************************************************
 * API to update channel configurations locally.
 *****************************************************************************/
void update_channel_list(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "update_channel_list error: NULL handle\n");

  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  uint8_t next = 0U;
  uint16_t channel = CHANNEL_DOES_NOT_EXIST;
  phy_modulation_e modulation = M_UNDEFINED;

  memset(&radio_info, 0, sizeof(radio_info_t));
  for (uint8_t i = 0; i < WISUN_MODESWITCHPHRS_ARRAY_SIZE; i++) {
    channel = CHANNEL_DOES_NOT_EXIST;
    status = RAIL_IEEE802154_ComputeChannelFromPhyModeId(rail_handle,
                                                         wisun_modeSwitchPhrs[i].phyModeId,
                                                         &channel);
    if (status != RAIL_STATUS_NO_ERROR) {
      // it failes because it is the selected channel
      (void) RAIL_GetChannel(rail_handle, &channel);
    }
    if (channel != CHANNEL_DOES_NOT_EXIST) {
      if (next >= MAX_SELECTEBLE_CHANNEL) {
        break;
      }
      for (uint8_t j = 0; j < channelConfigs[0]->length; j++) {
        if (channel == channelConfigs[0]->configs[j].channelNumberStart) {
          modulation = calculate_modulation_from_phy_mode_id(wisun_modeSwitchPhrs[i].phyModeId);
          radio_info.channel_list[next].channel_number = channel;
          radio_info.channel_list[next].phy_mode_id = wisun_modeSwitchPhrs[i].phyModeId;
          radio_info.channel_list[next].modulation = modulation;
          radio_info.channel_list[next++].phy_mode_index = i;
          radio_info.mode_switch_capable_channels++;
          break;
        }
      }
    }
  }
  print_channel_list();
}

/******************************************************************************
 * API to print channel configurations.
 *****************************************************************************/
void print_channel_list(void)
{
  app_log_info("Found %d channels\n",
               radio_info.mode_switch_capable_channels);
  for (uint8_t i = 0; i < radio_info.mode_switch_capable_channels; i++) {
    if (radio_info.channel_list[i].modulation == M_OFDM) {
      app_log_info("  Ch number: %5d phyModeId: %3d modulation: %s rate: %1d\n",
                   radio_info.channel_list[i].channel_number,
                   radio_info.channel_list[i].phy_mode_id,
                   phy_modulation_strings[(uint8_t)radio_info.channel_list[i].modulation],
                   (radio_info.channel_list[i].phy_mode_id & 0x0F));
    } else {
      app_log_info("  Ch number: %5d phyModeId: %3d modulation: %s\n",
                   radio_info.channel_list[i].channel_number,
                   radio_info.channel_list[i].phy_mode_id,
                   phy_modulation_strings[(uint8_t)radio_info.channel_list[i].modulation]);
    }
  }
  app_log_info("NOTE: Although multiple channel configs may be available,\n"
               "      Config 0 is assumed for use.\n");
}

/******************************************************************************
 * API to trigger mode switch transmission.
 *****************************************************************************/
sl_status_t trig_mode_switch_tx(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "trig_mode_switch_tx error: NULL handle\n");

  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;
  sl_status_t status = SL_STATUS_OK;
  uint32_t phr = 0U;
  uint32_t duration_in_sec = ms_duration * 1000U;
  uint16_t channel = CHANNEL_DOES_NOT_EXIST;
  uint16_t i = count_phy_mode_id_index(ms_new_phy_mode_id);
  uint8_t phy_mode_id = ms_new_phy_mode_id;

  if (i == PHY_MODE_ID_DOES_NOT_EXIST) {
    status = SL_STATUS_INVALID_PARAMETER;
  }

  if (status == SL_STATUS_OK) {
    rail_status = RAIL_IEEE802154_ComputeChannelFromPhyModeId(rail_handle,
                                                              phy_mode_id,
                                                              &channel);
    if (rail_status == RAIL_STATUS_NO_ERROR) {
      ms_new_channel = channel;
      status = SL_STATUS_OK;
    } else {
      status = SL_STATUS_INVALID_PARAMETER;
    }
  }

  if (status == SL_STATUS_OK) {
    phr = wisun_modeSwitchPhrs[i].phr;
    phr = __RBIT(phr);
    phr >>= 16;
    memcpy(ms_phr, &(wisun_modeSwitchPhrs[i].phr), MSPHR_LENGTH);
    if (ms_duration) {
      status = sl_sleeptimer_start_timer_ms(&mode_switch_timer,
                                            duration_in_sec,
                                            ms_timer_callback,
                                            NULL,
                                            0,
                                            0);
    }
  }

  if (status == SL_STATUS_OK) {
    ms_state = MS_INITED;
    if (radio_info.channel_list[i].modulation ==  M_OFDM) {
      ofdm_rate = phy_mode_id & 0x0F;
    }
  } else {
    ms_state = MS_IDLE;
  }

  return status;
}

/******************************************************************************
 * The API to get the payload from the radio frame.
 *****************************************************************************/
uint16_t unpack_packet(uint8_t *rx_destination,
                       const RAIL_RxPacketInfo_t *packet_information,
                       uint8_t **start_of_payload,
                       phy_modulation_e modulation)
{
  if ((rx_destination == NULL)
      || (packet_information == NULL)
      || (start_of_payload == NULL)) {
    return 0;
  }

  uint16_t payload_size = 0U;

  RAIL_CopyRxPacket(rx_destination, packet_information);
  if (modulation == M_2FSK) {
    *start_of_payload
      = sl_flex_802154_packet_unpack_sunfsk_2byte_data_frame(packet_information,
                                                             &fsk_fcs_type,
                                                             &fsk_whitening,
                                                             &payload_size,
                                                             rx_destination);
  } else if (modulation == M_OFDM) {
    *start_of_payload
      = sl_flex_802154_packet_unpack_ofdm_data_frame(packet_information,
                                                     &ofdm_rate,
                                                     &ofdm_scrambler,
                                                     &payload_size,
                                                     rx_destination);
  } else {
    app_log_warning("Unkown modulation\n");
  }

  ms_new_phy_mode_id = get_phy_mode_id_from_channel(current_channel);
  if (modulation == M_OFDM) {
    ms_new_phy_mode_id += ofdm_rate;
  }

  return payload_size;
}

/******************************************************************************
 * API to prepare the packet for sending and load it into the RAIL TX FIFO.
 *****************************************************************************/
void prepare_package(RAIL_Handle_t rail_handle,
                     uint8_t *out_data,
                     uint16_t length,
                     phy_modulation_e modulation)
{
  app_assert(rail_handle != NULL,
             "prepare_package error: NULL handle\n");

  if (out_data == NULL) {
    return;
  }

  uint16_t bytes_written_in_fifo = 0U;
  uint16_t packet_size = 0U;

  if (ms_state == MS_INITED) {
    memcpy(tx_frame_buffer, &ms_phr, sizeof(ms_phr));
    packet_size = MS_PACKET_LENGTH;
  } else {
    if (modulation == M_2FSK) {
      sl_flex_802154_packet_pack_sunfsk_2bytes_data_frame(fsk_fcs_type,
                                                          fsk_whitening,
                                                          length,
                                                          out_data,
                                                          &packet_size,
                                                          tx_frame_buffer);
    } else if (modulation == M_OFDM) {
      sl_flex_802154_packet_pack_ofdm_data_frame(ofdm_rate,
                                                 ofdm_scrambler,
                                                 length,
                                                 out_data,
                                                 &packet_size,
                                                 tx_frame_buffer);
    } else {
      app_log_warning("Unkown modulation\n");
    }
  }
  bytes_written_in_fifo = RAIL_WriteTxFifo(rail_handle,
                                           tx_frame_buffer,
                                           packet_size,
                                           true);
  app_assert(bytes_written_in_fifo == packet_size,
             "RAIL_WriteTxFifo() failed to write in fifo"
             "(%d bytes instead of %d bytes)\n",
             bytes_written_in_fifo,
             packet_size);
}

/******************************************************************************
 * API to get the current state of the mode switch process.
 *****************************************************************************/
mode_switch_state_t get_ms_state(void)
{
  return ms_state;
}

/******************************************************************************
 * API to get the text equivalent of the current mode switch state.
 *****************************************************************************/
const char* get_ms_state_str(void)
{
  return mode_switch_state_strings[(uint8_t)ms_state];
}

/******************************************************************************
 * API to set the current state of the mode switch process.
 *****************************************************************************/
void set_ms_state(mode_switch_state_t new_state)
{
  ms_state = new_state;
}

/******************************************************************************
 * API to get the text equivalent of the modulation of the current channel.
 *****************************************************************************/
const char* get_phy_modulation_str(void)
{
  phy_modulation_e phy_mod = get_phy_modulation_from_channel(current_channel);

  return phy_modulation_strings[(uint8_t)phy_mod];
}

/******************************************************************************
 * API to request mode switch.
 *****************************************************************************/
sl_status_t request_mode_switch(void)
{
  sl_status_t status = SL_STATUS_OK;
  phy_modulation_e phy_mod = get_phy_modulation_from_channel(current_channel);

  if (ms_state == MS_IDLE && phy_mod == M_2FSK) {
    ms_state = MS_REQUESTED;
  } else {
    status = SL_STATUS_INVALID_STATE;
  }

  return status;
}

/******************************************************************************
 * API to count the index of the given phy_mode_id.
 *****************************************************************************/
uint16_t count_phy_mode_id_index(const uint8_t phy_mode_id)
{
  uint16_t index = PHY_MODE_ID_DOES_NOT_EXIST;

  for (uint16_t i = 0; i < WISUN_MODESWITCHPHRS_ARRAY_SIZE; i++) {
    if (wisun_modeSwitchPhrs[i].phyModeId == phy_mode_id) {
      index = i;
      break;
    }
  }

  return index;
}

/******************************************************************************
 * API to get the index of the given channel.
 *****************************************************************************/
uint16_t get_channel_index(const uint16_t new_channel)
{
  uint16_t index = CHANNEL_DOES_NOT_EXIST;

  for (uint16_t i = 0; i < radio_info.mode_switch_capable_channels; i++) {
    if (radio_info.channel_list[i].channel_number == new_channel) {
      index = i;
      break;
    }
  }

  return index;
}

/******************************************************************************
 * API to set new phy mode id for mode switch.
 *****************************************************************************/
sl_status_t set_new_phy_mode_id(const uint8_t new_phy_mode_id)
{
  sl_status_t status = SL_STATUS_OK;
  uint16_t phy_mode_id_index = count_phy_mode_id_index(new_phy_mode_id);

  if (phy_mode_id_index == PHY_MODE_ID_DOES_NOT_EXIST) {
    status = SL_STATUS_INVALID_PARAMETER;
  } else {
    ms_new_phy_mode_id = new_phy_mode_id;
  }

  return status;
}

/******************************************************************************
 * API to get the currently used phy mode id.
 *****************************************************************************/
uint8_t get_phy_mode_id(void)
{
  uint8_t phy_mode_id = ms_new_phy_mode_id;

  return phy_mode_id;
}

/******************************************************************************
 * API to set time the device spends on the new channel.
 *****************************************************************************/
sl_status_t set_mode_switch_duration(const uint32_t duration)
{
  sl_status_t status = SL_STATUS_OK;

  if (duration > MODE_SWITCH_DURATION_MAX) {
    status = SL_STATUS_INVALID_PARAMETER;
  } else {
    ms_duration = duration;
  }
  return status;
}

/******************************************************************************
 * API to set the currently used channel.
 *****************************************************************************/
RAIL_Status_t set_channel(const uint16_t new_channel)
{
  RAIL_Handle_t rail_handle = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  status = RAIL_StartRx(rail_handle, new_channel, NULL);
  if (status == RAIL_STATUS_NO_ERROR) {
    current_channel = new_channel;
    app_log_info("Channel is set to %d\n", current_channel);
  }

  ms_new_phy_mode_id = get_phy_mode_id_from_channel(current_channel);
  if (get_phy_modulation_from_channel(current_channel) == M_OFDM) {
    ms_new_phy_mode_id = ms_new_phy_mode_id + ofdm_rate;
  }

  return status;
}

/******************************************************************************
 * API to get the currently used channel.
 *****************************************************************************/
uint16_t get_channel(void)
{
  return current_channel;
}

/******************************************************************************
 * API to get the new channel to be set with the mode switch process.
 *****************************************************************************/
uint16_t get_ms_new_channel(void)
{
  return ms_new_channel;
}

/******************************************************************************
 * API to get the channel to be set after returning from mode switch.
 *****************************************************************************/
uint16_t get_base_channel(void)
{
  return base_channel;
}

/******************************************************************************
 * API to switch the radio channel during the mode switch process.
 *****************************************************************************/
RAIL_Status_t switch_to_ms_channel(RAIL_Handle_t rail_handle)
{
  app_assert(rail_handle != NULL,
             "switch_to_ms_channel error: NULL handle\n");

  uint16_t ms_channel = 0U;
  RAIL_Status_t status = RAIL_GetChannel(rail_handle, &ms_channel);

  if (status == RAIL_STATUS_NO_ERROR) {
    base_channel = current_channel;
    status = set_channel(ms_channel);
    update_rail_pa_settings(rail_handle, ms_channel);
  }

  return status;
}

/******************************************************************************
 * API to set the radio back to the base channel from the mode switch channel.
 *****************************************************************************/
RAIL_Status_t return_to_base_channel(void)
{
  RAIL_Status_t status = set_channel(base_channel);

  if (status == RAIL_STATUS_NO_ERROR) {
    ms_state = MS_IDLE;
  }
  ms_new_phy_mode_id = get_phy_mode_id_from_channel(current_channel);

  return status;
}

/******************************************************************************
 * API to get the PHY mode id of the given channel.
 *****************************************************************************/
uint8_t get_phy_mode_id_from_channel(const uint16_t channel)
{
  uint8_t phy_mode_id = 0;

  for (uint8_t i = 0; i < radio_info.mode_switch_capable_channels; i++) {
    if (radio_info.channel_list[i].channel_number == channel) {
      phy_mode_id = radio_info.channel_list[i].phy_mode_id;
      break;
    }
  }

  return phy_mode_id;
}

/******************************************************************************
 * API to get the PHY modulation of the given channel.
 *****************************************************************************/
phy_modulation_e get_phy_modulation_from_channel(const uint16_t channel)
{
  phy_modulation_e phy_modulation = M_UNDEFINED;

  for (uint8_t i = 0; i < radio_info.mode_switch_capable_channels; i++) {
    if (radio_info.channel_list[i].channel_number == channel) {
      phy_modulation = radio_info.channel_list[i].modulation;
      break;
    }
  }

  return phy_modulation;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Callback function for the mode switch timer.
 *****************************************************************************/
static void ms_timer_callback(sl_sleeptimer_timer_handle_t *handle,
                              void *data)
{
  (void) data;
  (void) handle;

  ms_state = MS_RETURN_TO_BASE_PHY;
}
