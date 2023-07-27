/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "em_common.h"
#include "sl_ncp.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#include "app.h"

#ifdef SL_CATALOG_BTMESH_STACK_FW_UPDATE_SERVER_PRESENT
#include "ncp_btmesh_dfu.h"
#endif // SL_CATALOG_BTMESH_STACK_FW_UPDATE_SERVER_PRESENT

/***************************************************************************//**
 * Application Init.
 ******************************************************************************/
SL_WEAK void app_init(void)
{
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

/***************************************************************************//**
 * User command (message_to_target) handler callback.
 *
 * Handles user defined commands received from NCP host.
 * The user commands handled here are defined in app.h and are solely meant for
 * example purposes.
 * @param[in] data Data received from NCP host.
 *
 * @note This overrides the dummy weak implementation.
 ******************************************************************************/
void sl_ncp_user_cmd_message_to_target_cb(void *data)
{
  uint8array *cmd = (uint8array *)data;
  user_cmd_t *user_cmd = (user_cmd_t *)cmd->data;

  switch (user_cmd->hdr) {
    // -------------------------------
    // Example: user command 1.
    case USER_CMD_1_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Send response to user command 1 to NCP host.
      // Example: sending back received command.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK, cmd->len, cmd->data);
      break;

    // -------------------------------
    // Example: user command 2.
    case USER_CMD_2_ID:
      //////////////////////////////////////////////
      // Add your user command handler code here! //
      //////////////////////////////////////////////

      // Send response to user command 2 to NCP host.
      // Example: sending back received command.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_OK, cmd->len, cmd->data);
      // Send user event too.
      // Example: sending back received command as an event.
      sl_ncp_user_evt_message_to_host(cmd->len, cmd->data);
      break;

#ifdef SL_CATALOG_BTMESH_STACK_FW_UPDATE_SERVER_PRESENT
    case USER_CMD_FWID_ID: {
      sl_status_t sc = sl_btmesh_ncp_dfu_set_fwid(user_cmd->data.cmd_fwid.idx,
                                                  user_cmd->data.cmd_fwid.len,
                                                  user_cmd->data.cmd_fwid.data);
      sl_ncp_user_cmd_message_to_target_rsp(sc, cmd->len, cmd->data);
      break;
    }

    case USER_CMD_URI_ID: {
      sl_status_t sc = sl_btmesh_ncp_dfu_set_uri(user_cmd->data.cmd_uri.idx,
                                                 user_cmd->data.cmd_uri.type,
                                                 user_cmd->data.cmd_uri.len,
                                                 user_cmd->data.cmd_uri.data);
      sl_ncp_user_cmd_message_to_target_rsp(sc, cmd->len, cmd->data);
      break;
    }
#endif // SL_CATALOG_BTMESH_STACK_FW_UPDATE_SERVER_PRESENT

    // -------------------------------
    // Unknown user command.
    default:
      // Send error response to NCP host.
      sl_ncp_user_cmd_message_to_target_rsp(SL_STATUS_FAIL, 0, NULL);
      break;
  }
}
