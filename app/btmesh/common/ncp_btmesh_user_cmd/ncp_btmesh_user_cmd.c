/***************************************************************************//**
 * @file
 * @brief BGAPI user command handler.
 * Demonstrates the communication between an NCP host and NCP target using
 * BGAPI user messages, responses and events. Can be used as a starting point
 * for creating custom commands or for testing purposes.
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

#include "sl_ncp.h"
#include "ncp_btmesh_user_cmd_handler.h"
#include "ncp_btmesh_user_cmd.h"

/***************************************************************************//**
 * User command (message_to_target) handler callback.
 *
 * Handles user defined commands received from NCP host.
 * The user commands handled here are defined in ncp_btmesh_user_cmd.h and are
 * solely meant for example purposes.
 * @param[in] data Data received from NCP host.
 *
 * @note This overrides the dummy weak implementation.
 ******************************************************************************/
void sl_ncp_user_cmd_message_to_target_cb(void *data)
{
  bool cmd_handled = false;

  ncp_cmd_to_target_handler(data, &cmd_handled);

  if (cmd_handled == true) {
    return;
  }

  sl_ncp_app_user_cmd_message_to_target_cb(data);
}

/**************************************************************************//**
 * Application user command (message_to_target) handler callback.
 *
 * @note Weak implementation.
 *****************************************************************************/
SL_WEAK void sl_ncp_app_user_cmd_message_to_target_cb(void *data)
{
  (void)data;

  sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_FAIL, 0, NULL);
}
