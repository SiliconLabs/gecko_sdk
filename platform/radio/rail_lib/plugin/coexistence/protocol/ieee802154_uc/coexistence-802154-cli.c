/***************************************************************************//**
 * @file
 * @brief coexistence-802154-cli.c
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_cli.h"
#include "response_print.h"
#include "coexistence-802154.h"

void cli_coex_154_get_options(sl_cli_command_arg_t *args)
{
  sl_rail_util_coex_options_t options = sl_rail_util_coex_get_options();
  responsePrint(sl_cli_get_command_string(args, 0), "Options:0x%x", options);
}

void cli_coex_154_set_options(sl_cli_command_arg_t *args)
{
  sl_rail_util_coex_options_t options = (sl_rail_util_coex_options_t)sl_cli_get_argument_uint32(args, 0);
  sl_status_t status = sl_rail_util_coex_set_options(options);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

static bool coex_154_cli_initialized = false;

void cli_coex_154_set_enable(sl_cli_command_arg_t *args)
{
  bool enabled = !!(bool)sl_cli_get_argument_uint8(args, 0);
  if (enabled && !coex_154_cli_initialized) {
    sl_rail_util_coex_init();
    coex_154_cli_initialized = true;
  }
  sl_status_t status = sl_rail_util_coex_set_enable(enabled);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_is_enabled(sl_cli_command_arg_t *args)
{
  bool enabled = !!(bool)sl_rail_util_coex_is_enabled();
  responsePrint(sl_cli_get_command_string(args, 0), "Enabled:0x%x", enabled);
}

void cli_coex_154_set_tx_request(sl_cli_command_arg_t *args)
{
  COEX_Req_t ptaReq = (COEX_Req_t)sl_cli_get_argument_uint8(args, 0);
  sl_status_t status = sl_rail_util_coex_set_tx_request(ptaReq, NULL);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_set_rx_request(sl_cli_command_arg_t *args)
{
  COEX_Req_t ptaReq = (COEX_Req_t)sl_cli_get_argument_uint8(args, 0);
  sl_status_t status = sl_rail_util_coex_set_rx_request(ptaReq, NULL);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_set_request_pwm(sl_cli_command_arg_t *args)
{
  COEX_Req_t ptaReq = (COEX_Req_t)sl_cli_get_argument_uint8(args, 0);
  uint8_t dutyCycle = sl_cli_get_argument_uint8(args, 1);
  uint8_t periodHalfMs = sl_cli_get_argument_uint8(args, 2);
  sl_status_t status = sl_rail_util_coex_set_request_pwm(ptaReq,
                                                         NULL,
                                                         dutyCycle,
                                                         periodHalfMs);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_get_request_pwm_args(sl_cli_command_arg_t *args)
{
  const sl_rail_util_coex_pwm_args_t* pwm_args = sl_rail_util_coex_get_request_pwm_args();
  responsePrint(sl_cli_get_command_string(args, 0),
                "requestMode:0x%x, dutyCycle:%u, periodHalfMs:%u",
                pwm_args ? pwm_args->req : 0U,
                pwm_args ? pwm_args->dutyCycle : 0U,
                pwm_args ? pwm_args->periodHalfMs : 0U);
}

void cli_coex_154_set_dp_pulse_width(sl_cli_command_arg_t *args)
{
  uint8_t pulseWidthUs = sl_cli_get_argument_uint8(args, 0);
  sl_status_t status = sl_rail_util_coex_set_directional_priority_pulse_width(pulseWidthUs);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_get_dp_pulse_width(sl_cli_command_arg_t *args)
{
  uint8_t pulseWidthUs = sl_rail_util_coex_get_directional_priority_pulse_width();
  responsePrint(sl_cli_get_command_string(args, 0), "pulseWidthUs:%u", pulseWidthUs);
}

void cli_coex_154_set_phy_select_timeout(sl_cli_command_arg_t *args)
{
  uint8_t timeoutMs = sl_cli_get_argument_uint8(args, 0);
  sl_status_t status = sl_rail_util_coex_set_phy_select_timeout(timeoutMs);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
}

void cli_coex_154_get_phy_select_timeout(sl_cli_command_arg_t *args)
{
  uint8_t timeoutMs = sl_rail_util_coex_get_phy_select_timeout();
  responsePrint(sl_cli_get_command_string(args, 0), "phySelectTimeoutMs:%u", timeoutMs);
}

void cli_coex_154_is_coex_phy_selected(sl_cli_command_arg_t *args)
{
  bool enabled = !!(bool)sl_rail_util_coex_is_coex_phy_selected();
  responsePrint(sl_cli_get_command_string(args, 0), "phySelected:0x%x", enabled);
}

void cli_coex_154_get_gpio_input_override(sl_cli_command_arg_t *args)
{
  sl_rail_util_coex_gpio_index_t gpioIndex = (sl_rail_util_coex_gpio_index_t)sl_cli_get_argument_uint8(args, 0);
  if (gpioIndex < (COEX_GPIO_INDEX_COUNT - 1)) {
    bool enabled = sl_rail_util_coex_get_gpio_input_override(gpioIndex);
    responsePrint(sl_cli_get_command_string(args, 0), "gpioOverride:0x%x", enabled);
  } else {
    responsePrint(sl_cli_get_command_string(args, 0), "COEX GPIO index out of bounds!");
  }
}

void cli_coex_154_set_gpio_input_override(sl_cli_command_arg_t *args)
{
  sl_rail_util_coex_gpio_index_t gpioIndex = (sl_rail_util_coex_gpio_index_t)sl_cli_get_argument_uint8(args, 0);
  bool enabled = (bool)sl_cli_get_argument_uint8(args, 1);
  sl_status_t status = sl_rail_util_coex_set_gpio_input_override(gpioIndex, enabled);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status);
  cli_coex_154_get_gpio_input_override(args);
}
