/***************************************************************************//**
 * @file
 * @brief ABR Ranging Service
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

#include "app_log.h"
#include "abr_ras.h"

ras_control_point_parse_result abr_ras_parse_control_point_message(uint8_t *message, uint8_t message_len)
{
  ras_control_point_parse_result result = { .periodic_notification_mode_set_enabled = false };
  if (!message || !message_len) {
    result.opcode = ABR_RAS_OPCODE_INVALID;
    return result;
  }

  uint8_t opcode = message[0];
  switch (opcode) {
    case ABR_RAS_OPCODE_RANGING_DATA_GET_COMMAND:
    {
      if (message_len != sizeof(ras_ranging_data_get_command_t)) {
        app_log_warning("Message length mismatch, discarding" APP_LOG_NL);
        result.opcode = ABR_RAS_OPCODE_INVALID;
        return result;
      }
      ras_ranging_data_get_command_t cmd = *((ras_ranging_data_get_command_t *)(message));
      app_log_info("RAS Ranging Data Get message received; index='%u' se_idx='%u'"
                   APP_LOG_NL,
                   cmd.procedure_index,
                   cmd.subevent_index);
      if (cmd.max_number_of_notifications == 0xFF) {
        result.periodic_notification_mode_set_enabled = true;
      } else {
        result.periodic_notification_mode_set_enabled = false;
      }
      result.opcode = ABR_RAS_OPCODE_RANGING_DATA_GET_COMMAND;
      return result;
    }
    break;

    case ABR_RAS_OPCODE_RANGING_DATA_READY_INDICATION:
    {
      if (message_len != sizeof(ras_ranging_data_ready_indication_t)) {
        app_log_warning("Message length mismatch, discarding" APP_LOG_NL);
        result.opcode = ABR_RAS_OPCODE_INVALID;
        return result;
      }
      ras_ranging_data_ready_indication_t cmd = *((ras_ranging_data_ready_indication_t *)(message));
      app_log_info("RAS Ranging Data Ready message received; index='%u' num_se='%u' se_idx='%u' size='%u'" APP_LOG_NL,
                   cmd.procedure_index, cmd.number_of_subevents, cmd.subevent_index, cmd.subevent_index_data_size);
      result.opcode = ABR_RAS_OPCODE_RANGING_DATA_READY_INDICATION;
      return result;
    }
    break;

    default:
      app_log_warning("Unknown RAS Control Point message received" APP_LOG_NL);
      break;
  }

  result.opcode = ABR_RAS_OPCODE_INVALID;
  return result;
}

sl_status_t abr_ras_create_control_point_response(uint8_t *data,
                                                  uint8_t len,
                                                  bool enable_periodic_notification_mode,
                                                  ras_ranging_data_get_command_t *cmd)
{
  if (len == 0 || data == NULL || cmd == NULL) {
    return SL_STATUS_INVALID_CONFIGURATION;
  }

  ras_control_point_parse_result ras_result = abr_ras_parse_control_point_message(data, len);
  ras_opcode_t ras_opcode = ras_result.opcode;

  if (ras_opcode == ABR_RAS_OPCODE_RANGING_DATA_READY_INDICATION) {
    // Enable RAS Periodic Notification mode
    if (enable_periodic_notification_mode) {
      app_log_info("Requesting RAS Periodic Notification mode" APP_LOG_NL);
      cmd->opcode = ABR_RAS_OPCODE_RANGING_DATA_GET_COMMAND;
      cmd->antenna_path_index_filter = 0;
      cmd->keep_notification = 0;
      cmd->max_number_of_notifications = 0xFF;
      cmd->procedure_index = 0;
      cmd->subevent_index = 0;
      cmd->subevent_ranging_data_offset = 0;
    } else {
      // Request the new data manually
      app_log_info("Requesting Ranging Data" APP_LOG_NL);
      ras_ranging_data_ready_indication_t rx_cmd = *((ras_ranging_data_ready_indication_t*)(data));
      cmd->opcode = ABR_RAS_OPCODE_RANGING_DATA_GET_COMMAND;
      cmd->antenna_path_index_filter = 0;
      cmd->keep_notification = 0;
      cmd->max_number_of_notifications = 0;
      cmd->procedure_index = rx_cmd.procedure_index;
      cmd->subevent_index = rx_cmd.subevent_index;
      cmd->subevent_ranging_data_offset = 0;
    }
    return SL_STATUS_OK;
  }

  return SL_STATUS_EMPTY;
}
