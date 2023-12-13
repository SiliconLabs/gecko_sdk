/***************************************************************************//**
 * @file
 * @brief ABR Antenna Switching
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

#include "abr_ans.h"
#include <string.h>

static uint8_t antenna_num = 0;
static uint8_t antenna_count;
static int16_t antenna_offset[MAX_ANTENNA_NUMBER];

void ans_antenna_switching()
{
  sl_status_t sc;
  ans_antenna_t antenna;
  uint8_t send_data[2];
  size_t response_len_temp;
  uint8_t response_data_temp[UINT8_MAX];
  app_log_info("Starting antenna switching..." APP_LOG_NL);
  ans_set_next_antenna(&antenna);
  int16_t ant_offset_cm_origin[1] = { antenna.ant_offset_cm };
  sc = sl_bt_cs_set_antenna_configuration(sizeof(antenna.ant_offset_cm), (uint8_t *) ant_offset_cm_origin);
  if (sc != SL_STATUS_OK) {
    app_log_warning("Set antenna config failed: %u" APP_LOG_NL, sc);
  }
  app_log_info("Antenna number: %u" APP_LOG_NL, antenna_num);
  send_data[0] = USER_CMD_SET_ANTENNA_NUM_ID;
  send_data[1] = antenna_num;
  sc = sl_bt_user_message_to_target(sizeof(send_data),
                                    send_data,
                                    sizeof(response_data_temp),
                                    &response_len_temp,
                                    response_data_temp);
  if (sc != SL_STATUS_OK) {
    app_log_warning("User message to target failed: %u" APP_LOG_NL, sc);
  }
}

bool ans_initiator_decide_antenna_switching(bool wired)
{
  sl_status_t sc;
  uint8_t send_data = USER_CMD_GET_BOARD_NAME_ID;
  char response_data[USER_RSP_GET_BOARD_NAME_LEN + 8];
  size_t response_len_temp[8];

  app_log_info("Board identification requested..." APP_LOG_NL);

  sc = sl_bt_user_message_to_target(sizeof(send_data),
                                    &send_data,
                                    sizeof(response_data),
                                    response_len_temp,
                                    (uint8_t*)response_data);

  if (sc != SL_STATUS_OK) {
    app_log_warning("User message to target failed: %u" APP_LOG_NL, sc);
  } else {
    response_data[USER_RSP_GET_BOARD_NAME_LEN + 7] = '\0'; // Place null character at the end
    app_log_info("Command response received. Detected board: %s." APP_LOG_NL,
                 response_data);
    if (!(memcmp(response_data, ANS_SUPPORTED_BOARD_NAME, sizeof(response_data)))) {
      return true;
    }
  }
  return false;
}

void ans_set_next_antenna(ans_antenna_t *ant)
{
  if (ant == NULL) {
    return;
  }
  ant->len = antenna_count;
  ant->id = antenna_num;
  antenna_num++;
  if (antenna_num > (antenna_count - 1)) {
    antenna_num = 0;
  }
  ant->ant_offset_cm = antenna_offset[ant->id];
}

void ans_set_antenna_offset(int16_t *offset, uint8_t offset_num)
{
  if (offset == NULL) {
    return;
  }
  antenna_count = offset_num;
  if (antenna_count > MAX_ANTENNA_NUMBER) {
    app_log_error("Antenna count exceeds max antenna number: %u" APP_LOG_NL, MAX_ANTENNA_NUMBER);
    return;
  }
  memcpy(antenna_offset, offset, sizeof(&offset));
}
