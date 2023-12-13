/***************************************************************************/ /**
 * @file
 * @brief Private CPC system endpoint primary. For internal use by other parts
 *        of CPC but not to be used by external users.
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

#ifndef SLI_CPC_SYSTEM_PRIMARY_H
#define SLI_CPC_SYSTEM_PRIMARY_H

#include "sl_common.h"
#include "sl_enum.h"
#include "sli_cpc_system_common.h"
#include "sli_cpc_timer.h"

#ifdef __cplusplus
extern "C"
{
#endif

SL_ENUM_GENERIC(sli_cpc_system_ep_frame_type_t, uint8_t) {
  SYSTEM_EP_UFRAME,
  SYSTEM_EP_IFRAME
};

typedef struct  {
  sl_slist_node_t node_commands;
  sl_slist_node_t node_retries;
  sli_cpc_system_cmd_t command;
  void *on_final;
  void *on_final_arg;
  uint8_t retry_count;
  sli_cpc_system_ep_frame_type_t frame_type;
  uint32_t retry_timeout_tick;
  sl_status_t error_status;
  sli_cpc_timer_handle_t timer;
  bool is_first_try;
  bool being_transmitted;
} sli_cpc_system_command_handle_t;

/***************************************************************************//**
 * Callback for the no-op command.
 *
 * @brief
 *   This callback is called when the PRIMARY receives the reply from the SECONDARY.
 ******************************************************************************/
typedef void (*sli_cpc_system_noop_cmd_callback_t)(sl_status_t status);

/***************************************************************************//**
 * Callback for the reset command.
 *
 * @brief
 *   This callback is called when the PRIMARY receives the reply from the SECONDARY.
 *
 * @param
 *   [in] status
 *     The SECONDARY will return STATUS_OK if the reset will occur in the
 *     desired mode. STATUS_FAILURE will be returned otherwise.
 ******************************************************************************/
typedef void (*sli_cpc_system_reset_cmd_callback_t)(sl_status_t command_status,
                                                    sl_cpc_system_status_t reset_status);

/***************************************************************************//**
 * Callback for the property-get or set command.
 *
 * @param
 *   [in] property_id
 *     The ID of the property from the previously issued property-get/set.
 *
 *   [in] property_value
 *     A pointer to the value returned by the SECONDARY. Has to be casted to an
 *     appropriate value in function of the property ID.
 *
 *   [in] property_length
 *     The length of the property value in bytes.
 *
 *   [in] reply_arg
 *     Value passed as `on_property_set_reply_arg` or `on_property_get_reply_arg`
 *     in `sli_cpc_system_cmd_property_set` or `sli_cpc_system_cmd_property_get`
 *     respectively.
 ******************************************************************************/
typedef void (*sli_cpc_system_property_get_set_cmd_callback_t)(sli_cpc_property_id_t property_id,
                                                               void *property_value,
                                                               size_t property_length,
                                                               void *reply_arg,
                                                               sl_status_t status);

/***************************************************************************//**
 * Send no-operation command query.
 *
 * @brief
 *   This command can be seen like a ping command. Like its name implies, this
 *   command does nothing except generating a bidirectional transaction to
 *   assert the link is functional.
 *
 * @param
 *   [in] callback
 *     The callback upon receiving the reply of the command.
 *
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_noop(sli_cpc_system_noop_cmd_callback_t on_noop_reply,
                                    void *on_noop_reply_arg,
                                    uint8_t retry_count_max,
                                    uint32_t retry_timeout_ms);

/***************************************************************************//**
 * Send a property-get query.
 *
 * @brief
 *   This command sends a property-get request to the SECONDARY.
 *
 * @note
 *   Only one property-get/set can be issued a a time. Otherwise SL_STATUS_BUSY
 *   is returned.
 *
 * @note
 *   retry_count_max must be 0 for I-Frame.
 *
 * @param
 *   [in] callback
 *     The callback upon receiving the reply of the command.
 *
 *   [in] property_id
 *     The ID of the property to get.
 *
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_property_get(sli_cpc_system_property_get_set_cmd_callback_t on_property_get_reply,
                                            void *on_property_get_reply_arg,
                                            sli_cpc_property_id_t property_id,
                                            uint8_t retry_count_max,
                                            uint32_t retry_timeout_ms,
                                            sli_cpc_system_ep_frame_type_t frame_type);

/***************************************************************************//**
 * Send a property-set request to the SECONDARY.
 *
 * @brief
 *   This command sends a property-set request to the SECONDARY.
 *
 * @note
 *   Only one property-get/set can be issued a a time. Otherwise SL_STATUS_BUSY
 *   is returned.
 *
 * @note
 *   retry_count_max must be 0 for I-Frame.
 *
 * @param
 *   [in] callback
 *     The callback upon receiving the reply of the command.
 *
 *   [in] property_id
 *     The ID of the property to get.
 *
 *   [in] value
 *     The value of the property to set.
 *
 *   [in] value_length
 *     The length of the value.
 *
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_property_set(sli_cpc_system_property_get_set_cmd_callback_t on_property_set_reply,
                                            void *on_property_set_reply_arg,
                                            sli_cpc_property_id_t property_id,
                                            uint8_t retry_count_max,
                                            uint32_t retry_timeout_ms,
                                            const void *value,
                                            size_t value_length,
                                            sli_cpc_system_ep_frame_type_t frame_type);

/***************************************************************************//**
 * Send a reset query.
 *
 * @brief
 *   This command sends a reset request to the SECONDARY.
 *
 * @note
 *   Prior to a reboot, the PROP_BOOTLOADER_REBOOT_MODE must be set to the
 *   desired reboot mode.
 *
 * @param
 *   [in] callback
 *     The callback upon receiving the reply of the command.
 *
 ******************************************************************************/
sl_status_t sli_cpc_system_cmd_reboot(sli_cpc_system_reset_cmd_callback_t on_reset_reply,
                                      void *on_reset_reply_arg,
                                      uint8_t retry_count_max,
                                      uint32_t retry_timeout_ms);

/***************************************************************************//**
 * Get a a system command handle.
 *
 * @param[out] item Address of the variable that will receive the item pointer.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_get_system_command_handle(sli_cpc_system_command_handle_t **item);

/***************************************************************************//**
 * Free CPC system command handle.
 *
 * @param[in] item Pointer to system command handle to free.
 *
 * @return Status code.
 ******************************************************************************/
sl_status_t sli_cpc_free_system_command_handle(sli_cpc_system_command_handle_t *item);

/***************************************************************************//**
 * Notify primary's system endpoint that a reset occurred on the secondary
 *
 * @param
 *   [in] reset_reason
 *     reset reason sent by the secondary
 *
 ******************************************************************************/
void sli_cpc_system_notify_reset(sl_cpc_system_status_t reset_reason);

/***************************************************************************//**
 * Check if the system endpoint is ready for normal operations (ie. it's
 * connected to the secondary and the reboot sequence is finished).
 *
 * @return true if ready, false otherwise
 ******************************************************************************/
bool sli_cpc_system_is_ready(void);

/***************************************************************************//**
 * Start the system endpoint, connnecting it to the secondary.
 *
 * @return SL_STATUS_OK if no errors, otherwise another sl_status_t.
 ******************************************************************************/
sl_status_t sli_cpc_system_start(void);

#ifdef __cplusplus
}
#endif

#endif /* SLI_CPC_SYSTEM_PRIMARY_H */
