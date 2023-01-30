/***************************************************************************//**
 * @file
 * @brief app_cli.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "app_log.h"
#include "sl_cli.h"
#include "app_process.h"
#include "app_init.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif

#include "rail_config.h"
#include "sl_rail_util_init.h"
#include "sl_flex_mode_switch.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/******************************************************************************
 * CLI - trig_mode_switch: Triggering mode switch.
 *****************************************************************************/
void cli_trig_mode_switch(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_trig_mode_switch error: Wrong argument\n");
    return;
  }

  uint8_t arg_count = 0U;
  uint8_t new_phy_mode_id = 0U;
  uint32_t mode_switch_duration = 0U;
  sl_status_t ms_request_status = SL_STATUS_OK;

  arg_count = sl_cli_get_argument_count(arguments);
  new_phy_mode_id = sl_cli_get_argument_uint8(arguments, 0);
  if (arg_count == 2) {
    mode_switch_duration = sl_cli_get_argument_uint32(arguments, 1);
  }

  ms_request_status = set_new_phy_mode_id(new_phy_mode_id);
  if (ms_request_status != SL_STATUS_OK) {
    app_log_warning("ERROR set_new_phy_mode_id: 0x%04X\n",
                    (uint16_t)ms_request_status);
    return;
  } else {
    app_log_info("Mode switch phy mode id is set to %d\n",
                 new_phy_mode_id);
  }

  ms_request_status = set_mode_switch_duration(mode_switch_duration);
  if (ms_request_status != SL_STATUS_OK) {
    app_log_warning("ERROR set_mode_switch_duration: 0x%04X\n",
                    (uint16_t)ms_request_status);
    return;
  }

  ms_request_status = request_mode_switch();
  if (ms_request_status != SL_STATUS_OK) {
    app_log_info("Mode switch failed, status: 0x%04X\n",
                 (uint16_t)ms_request_status);
  } else {
    app_log_info("Mode switch requested\n");
  }
}

/******************************************************************************
 * CLI - end_mode_switch: Sending end mode switch packet.
 *****************************************************************************/
void cli_end_mode_switch(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  mode_switch_state_t ms_state = get_ms_state();
  const char* ms_state_str = get_ms_state_str();

  if (ms_state == MS_ON_NEW_PHY) {
    set_ms_state(MS_RETURN_TO_BASE_PHY);
  } else {
    app_log_info("The application must be in MS_ON_NEW_PHY state.\n"
                 "Current state is %s\n",
                 ms_state_str);
  }
}

/******************************************************************************
 * CLI - set_channel: Set the next channel to be used.
 *****************************************************************************/
void cli_set_channel(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_channel error: Wrong argument\n");
    return;
  }

  uint16_t ch_index = CHANNEL_DOES_NOT_EXIST;
  uint16_t previous_channel = get_channel();
  uint16_t new_channel = sl_cli_get_argument_uint16(arguments, 0);

  // Check if channel is valid in Channel Config 0
  ch_index = get_channel_index(new_channel);

  if (ch_index != CHANNEL_DOES_NOT_EXIST) {
    RAIL_Handle_t rail_handle
      = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);
    set_channel(new_channel);
    set_ms_state(MS_IDLE);
    app_log_info("New channel: %d Previous channel: %d\n",
                 new_channel,
                 previous_channel);
    update_rail_pa_settings(rail_handle, new_channel);
  } else {
    app_log_info("ERROR: Channel %d not available\n", new_channel);
  }
}

/******************************************************************************
 * CLI - get_available_channels: API to print available radio channels.
 *****************************************************************************/
void cli_get_available_channels(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  print_channel_list();
}

/******************************************************************************
 * CLI - get_fsk_fcs_type: API to print WiSUN FSK FCS type.
 *****************************************************************************/
void cli_get_fsk_fcs_type(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  app_log_info("Current FSK FCS Type: %d\n", get_fsk_fcs_type());
}

/******************************************************************************
 * CLI - set_fsk_fcs_type: API to set WiSUN FSK FCS type.
 *****************************************************************************/
void cli_set_fsk_fcs_type(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_fsk_fcs_type error: Wrong argument\n");
    return;
  }

  uint8_t fsk_fcs_type = sl_cli_get_argument_uint8(arguments, 0);

  set_fsk_fcs_type(fsk_fcs_type);
  app_log_info("Current FSK FCS Type: %d\n", get_fsk_fcs_type());
}

/******************************************************************************
 * CLI - get_fsk_whitening: API to print WiSUN FSK whitening.
 *****************************************************************************/
void cli_get_fsk_whitening(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  app_log_info("Current FSK whitening: %d\n", get_fsk_whitening());
}

/******************************************************************************
 * CLI - set_fsk_whitening: API to set WiSUN FSK whitening.
 *****************************************************************************/
void cli_set_fsk_whitening(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_fsk_whitening error: Wrong argument\n");
    return;
  }

  uint8_t fsk_whitening = sl_cli_get_argument_uint8(arguments, 0);

  set_fsk_whitening(fsk_whitening);
  app_log_info("Current FSK whitening: %d\n", get_fsk_whitening());
}

/******************************************************************************
 * CLI - get_ofdm_rate: API to print WiSUN OFDM rate.
 *****************************************************************************/
void cli_get_ofdm_rate(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  app_log_info("Current OFDM rate: %d\n", get_ofdm_rate());
}

/******************************************************************************
 * CLI - set_ofdm_rate: API to set WiSUN OFDM rate.
 *****************************************************************************/
void cli_set_ofdm_rate(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_ofdm_rate error: Wrong argument\n");
    return;
  }

  uint8_t ofdm_rate = sl_cli_get_argument_uint8(arguments, 0);

  set_ofdm_rate(ofdm_rate);
  app_log_info("Current OFDM rate: %d\n", get_ofdm_rate());
}

/******************************************************************************
 * CLI - get_ofdm_scrambler: API to print WiSUN OFDM scrambler.
 *****************************************************************************/
void cli_get_ofdm_scrambler(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  app_log_info("Current OFDM scrambler: %d\n", get_ofdm_scrambler());
}

/******************************************************************************
 * CLI - set_ofdm_scrambler: API to set WiSUN OFDM scrambler.
 *****************************************************************************/
void cli_set_ofdm_scrambler(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_ofdm_scrambler error: Wrong argument\n");
    return;
  }

  uint8_t ofdm_scrambler = sl_cli_get_argument_uint8(arguments, 0);

  set_ofdm_scrambler(ofdm_scrambler);
  app_log_info("Current OFDM scrambler: %d\n", get_ofdm_scrambler());
}

/******************************************************************************
 * CLI - get_print_packet_details: API to get extra packet info settings state.
 *****************************************************************************/
void cli_get_print_packet_details(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  app_log_info("Packet details is %s\n",
               get_print_packet_details() ? "ON" : "OFF");
}

/******************************************************************************
 * CLI - set_print_packet_details: API to enable/disable extra packet info.
 *****************************************************************************/
void cli_set_print_packet_details(sl_cli_command_arg_t *arguments)
{
  if ((arguments == NULL)
      || (arguments->argv == NULL)
      || (arguments->argv[arguments->arg_ofs + 0] == NULL)) {
    app_log_error("cli_set_print_packet_details error: Wrong argument\n");
    return;
  }
  bool print_packet_details = (bool) sl_cli_get_argument_uint8(arguments, 0);

  set_print_packet_details(print_packet_details);
  app_log_info("Packet details is %s\n",
               get_print_packet_details() ? "ON" : "OFF");
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
