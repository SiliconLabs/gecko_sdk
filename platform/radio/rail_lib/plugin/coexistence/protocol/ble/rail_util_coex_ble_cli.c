/***************************************************************************//**
 * @file
 * @brief rail_util_coex_ble_cli.c
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
#include "sl_cli.h"
#include "response_print.h"
#include "coexistence-ble.h"
#include "coexistence-ble-ll.h"
#include "coexistence-hal.h"
#include "rail_ble.h"
#include "rail.h"

extern const char * titleStrings[];
extern RAIL_Handle_t railHandle;

static uint16_t fastRandom(void)
{
  return COEX_HAL_GetPseudoRandom(0, 0xFFFF);
}

static void abortTxCallback(void)
{
  (void)RAIL_StopTx(railHandle, RAIL_STOP_MODE_ACTIVE);
}

void cli_coex_ble_init(sl_cli_command_arg_t *args)
{
  bool bleEnabled = RAIL_BLE_IsEnabled(railHandle);
  if (bleEnabled) {
    sl_bt_ll_coex_set_context(railHandle,
                              &abortTxCallback,
                              &fastRandom);
    sl_bt_init_coex_hal();
  }
  responsePrint(sl_cli_get_command_string(args, 0),
                "Init:%s",
                bleEnabled ? "True" : "False");
}

void cli_coex_ble_print_counters(sl_cli_command_arg_t *args)
{
  uint8_t size;
  const uint32_t *counters = NULL;

  if (sl_bt_get_coex_counters((const void **)&counters,
                              &size)
      && size >= sizeof(uint32_t)) {
    responsePrintStart(sl_cli_get_command_string(args, 0));
    size = size / sizeof(uint32_t);
    for (uint8_t id = 0U; id < size; ++id) {
      responsePrintContinue("%s: %u",
                            titleStrings[id],
                            counters[id]);
    }
    responsePrintEnd("Status:0x%x", RAIL_STATUS_NO_ERROR);
  } else {
    responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", SL_STATUS_FAIL);
  }
}

void cli_coex_ble_clear_counters(sl_cli_command_arg_t *args)
{
  (void)args;
  sl_bt_get_coex_counters(NULL, NULL);
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", 0);
}

void cli_coex_ble_set_options(sl_cli_command_arg_t *args)
{
  uint32_t mask = sl_cli_get_argument_uint32(args, 0);
  uint32_t options = sl_cli_get_argument_uint32(args, 1);
  bool status = sl_bt_set_coex_options(mask, options);

  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", status ? SL_STATUS_OK : SL_STATUS_FAIL);
}

void cli_coex_ble_get_config(sl_cli_command_arg_t *args)
{
  (void)args;
  sl_bt_ll_coex_config_t config;

  sl_bt_coex_get_config(&config);

  responsePrintStart(sl_cli_get_command_string(args, 0));
  responsePrintContinue("threshold_coex_pri: %u",
                        config.threshold_coex_pri);
  responsePrintContinue("threshold_coex_req: %u",
                        config.threshold_coex_req);
  responsePrintContinue("coex_pwm_period: %u",
                        config.coex_pwm_period);
  responsePrintEnd("coex_pwm_dutycycle: %u",
                   config.coex_pwm_dutycycle);
}

void cli_coex_ble_set_pri_threshold(sl_cli_command_arg_t *args)
{
  sl_bt_ll_coex_config_t config;

  sl_bt_coex_get_config(&config);
  config.threshold_coex_pri = sl_cli_get_argument_uint8(args, 0);
  sl_bt_coex_set_config(&config);

  cli_coex_ble_get_config(args);
}

void cli_coex_ble_set_req_threshold(sl_cli_command_arg_t *args)
{
  sl_bt_ll_coex_config_t config;

  sl_bt_coex_get_config(&config);
  config.threshold_coex_req = sl_cli_get_argument_uint8(args, 0);
  sl_bt_coex_set_config(&config);

  cli_coex_ble_get_config(args);
}

void cli_coex_ble_set_pwm_period(sl_cli_command_arg_t *args)
{
  sl_bt_ll_coex_config_t config;

  sl_bt_coex_get_config(&config);
  config.coex_pwm_period = sl_cli_get_argument_uint8(args, 0);
  sl_bt_coex_set_config(&config);

  cli_coex_ble_get_config(args);
}

void cli_coex_ble_set_pwm_dutycycle(sl_cli_command_arg_t *args)
{
  sl_bt_ll_coex_config_t config;

  sl_bt_coex_get_config(&config);
  config.coex_pwm_dutycycle = sl_cli_get_argument_uint8(args, 0);
  sl_bt_coex_set_config(&config);

  cli_coex_ble_get_config(args);
}

void cli_coex_ble_set_request_window(sl_cli_command_arg_t *args)
{
  uint16_t requestWindow = sl_cli_get_argument_uint16(args, 0);
  sl_bt_ll_coex_set_request_window(requestWindow);
  responsePrint(sl_cli_get_command_string(args, 0), "requestWindow:%u", requestWindow);
}

void cli_coex_ble_set_request(sl_cli_command_arg_t *args)
{
  bool request = (bool)sl_cli_get_argument_uint8(args, 0);
  bool scanPwmActive = (bool)sl_cli_get_argument_uint8(args, 1);
  uint8_t priority = sl_cli_get_argument_uint8(args, 2);
  if (sl_cli_get_argument_count(args) > 3) {
    uint32_t time = sl_cli_get_argument_uint32(args, 3);
    sl_bt_ll_coex_request_delayed(time, request, scanPwmActive, priority);
  } else {
    sl_bt_ll_coex_request(request, scanPwmActive, priority);
  }
  responsePrint(sl_cli_get_command_string(args, 0), "Status:0x%x", SL_STATUS_OK);
}
