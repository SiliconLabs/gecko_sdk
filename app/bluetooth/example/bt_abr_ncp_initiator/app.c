/***************************************************************************//**
 * @file
 * @brief Core application logic.
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
#include "sl_common.h"
#include "app.h"
#include "em_gpio.h"
#include "sl_bgapi.h"
#include "sl_status.h"
#include "sl_ncp.h"
#include "sl_rail_util_hadm_antenna_offset_config.h"

#define ANTENNA_MASK_01              0b01
#define ANTENNA_MASK_10              0b10
#define USER_CMD_GET_BOARD_NAME_ID   5
#define USER_CMD_SET_ANTENNA_NUM     6
#define USER_CMD_GET_ANTENNA_OFFSET  7
#define ANTENNA_PORT                 gpioPortC
#define ANTENNA_PIN0                 0
#define ANTENNA_PIN1                 1
#define APPLY_ANTENNA_PIN(pin, value)  ((value) ? GPIO_PinOutSet(ANTENNA_PORT, pin) : GPIO_PinOutClear(ANTENNA_PORT, pin))

static void ans_set_GPIOS_for_antenna(uint8_t);

/***************************************************************************//**
 * Application Init.
 ******************************************************************************/
SL_WEAK void app_init(void)
{
  GPIO_PinModeSet(ANTENNA_PORT, ANTENNA_PIN0, gpioModePushPull, 0);
  GPIO_PinModeSet(ANTENNA_PORT, ANTENNA_PIN1, gpioModePushPull, 0);
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application code here!                              //
  // This is called infinitely.                                              //
  // Do not call blocking functions from here!                               //
  /////////////////////////////////////////////////////////////////////////////
}

void sl_ncp_user_cmd_message_to_target_cb(void *data)
{
  char *board_name = SL_BOARD_NAME;
  // Offset is different for wired and wireless antenna
  // + 1 for sending the number of antennas
  const uint16_t antenna_offsets_size = SL_RAIL_UTIL_HADM_ANTENNA_COUNT * 2 + 1;

  uint8array *cmd = (uint8array *)data;
  uint8_t user_cmd = cmd->data[0];
  int16_t antenna_offset_wired[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRED_CM;
  int16_t antenna_offset_wireless[SL_RAIL_UTIL_HADM_ANTENNA_COUNT] = SL_RAIL_UTIL_HADM_ANTENNA_OFFSET_WIRELESS_CM;
  int16_t antenna_offsets[antenna_offsets_size];

  // Number of antennas
  antenna_offsets[0] = SL_RAIL_UTIL_HADM_ANTENNA_COUNT;
  memcpy(antenna_offsets + 1, antenna_offset_wired, sizeof(antenna_offset_wired));
  memcpy(antenna_offsets + SL_RAIL_UTIL_HADM_ANTENNA_COUNT + 1, antenna_offset_wireless, sizeof(antenna_offset_wireless));

  switch (user_cmd) {
    case USER_CMD_GET_BOARD_NAME_ID:
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK,
                                            strlen(board_name),
                                            (uint8_t *)board_name);
      break;
    case USER_CMD_SET_ANTENNA_NUM:
      ans_set_GPIOS_for_antenna(cmd->data[1]);
      break;
    case USER_CMD_GET_ANTENNA_OFFSET:
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK,
                                            sizeof(antenna_offsets),
                                            (uint8_t *)antenna_offsets);
      break;
    default:
      // Unknown command arrived.
  }
}

void ans_set_GPIOS_for_antenna(uint8_t antenna_num)
{
  // Clearing the GPIOS
  GPIO_PinOutClear(ANTENNA_PORT, ANTENNA_PIN0);
  GPIO_PinOutClear(ANTENNA_PORT, ANTENNA_PIN1);
  // Set to 00 01 10 11
  // PIN0 value depends only from MASK_01 and PIN1 only from MASK_10
  APPLY_ANTENNA_PIN(ANTENNA_PIN0, (antenna_num & ANTENNA_MASK_01));
  APPLY_ANTENNA_PIN(ANTENNA_PIN1, (antenna_num & ANTENNA_MASK_10));
}
