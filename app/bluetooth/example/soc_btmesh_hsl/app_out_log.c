/***************************************************************************//**
 * @file
 * @brief Application Output Log code
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdbool.h>
#include "em_common.h"
#include "sl_status.h"

#include "app.h"
#include "app_log.h"

#include "sl_btmesh_api.h"
#include "sl_btmesh_friend.h"
#include "sl_btmesh_hsl_server.h"
#include "sl_btmesh_lighting_server.h"
#include "sl_btmesh_provisioning_decorator.h"
#include "sl_btmesh_factory_reset.h"

#define UINT16_TO_PERCENTAGE(level) ((((uint32_t)(level) * 100) + 32767) / 65535)
#define UINT16_TO_DEGREE(level) ((((uint32_t)(level) * 360) + 32767) / 65535)

// -----------------------------------------------------------------------------
// BT mesh Friend Node Callbacks

/*******************************************************************************
 * Called when the Friend Node establishes friendship with another node.
 *
 * @param[in] netkey_index Index of the network key used in friendship
 * @param[in] lpn_address Low Power Node address
 *
 ******************************************************************************/
void sl_btmesh_friend_on_friendship_established(uint16_t netkey_index,
                                                uint16_t lpn_address)
{
  app_log("BT mesh Friendship established with LPN "
          "(netkey idx: %d, lpn addr: 0x%04x)\r\n",
          netkey_index,
          lpn_address);
  (void)netkey_index;
  (void)lpn_address;
}

/*******************************************************************************
 * Called when the friendship that was successfully established with a Low Power
 * Node has been terminated.
 *
 * @param[in] netkey_index Index of the network key used in friendship
 * @param[in] lpn_address Low Power Node address
 * @param[in] reason Reason for friendship termination
 *
 ******************************************************************************/
void sl_btmesh_friend_on_friendship_terminated(uint16_t netkey_index,
                                               uint16_t lpn_address,
                                               uint16_t reason)
{
  app_log("BT mesh Friendship terminated with LPN "
          "(netkey idx: %d, lpn addr: 0x%04x, reason: 0x%04x)\r\n",
          netkey_index,
          lpn_address,
          reason);
  (void)netkey_index;
  (void)lpn_address;
  (void)reason;
}

// -----------------------------------------------------------------------------
// BT mesh HSL Callbacks

/*******************************************************************************
 * Called when the UI shall be updated with the changed HSL Model state during
 * a transition. The rate of this callback can be controlled by changing the
 * HSL_SERVER_HUE_UI_UPDATE_PERIOD macro.
 *
 * @param[in] hue  Hue value.
 ******************************************************************************/
void sl_btmesh_hsl_hue_on_ui_update(uint16_t hue)
{
  app_log("BT mesh HSL Hue:      %4udeg\r\n", UINT16_TO_DEGREE(hue));
  (void)hue;
}

/*******************************************************************************
 * Called when the UI shall be updated with the changed HSL Model state during
 * a transition. The rate of this callback can be controlled by changing the
 * HSL_SERVER_SATURATION_UI_UPDATE_PERIOD macro.
 *
 * @param[in] saturation  Saturation value.
 ******************************************************************************/
void sl_btmesh_hsl_saturation_on_ui_update(uint16_t saturation)
{
  app_log("BT mesh HSL Saturation: %4u%%\r\n",
          UINT16_TO_PERCENTAGE(saturation));
  (void)saturation;
}

// -----------------------------------------------------------------------------
// BT mesh Lightning Server Callbacks

/*******************************************************************************
 * Called when the UI shall be updated with the changed state of
 * lightning server during a transition. The rate of this callback can be
 * controlled by changing the LIGHTING_SERVER_UI_UPDATE_PERIOD macro.
 *
 * @param[in] lightness_level lightness level (0x0001 - FFFE)
 *
 ******************************************************************************/
void sl_btmesh_lighting_server_on_ui_update(uint16_t lightness_level)
{
  app_log("BT mesh Lightness:     %5u%%\r\n",
          UINT16_TO_PERCENTAGE(lightness_level));
  (void)lightness_level;
}

// -----------------------------------------------------------------------------
// Provisioning Decorator Callbacks

/*******************************************************************************
 * Called at node initialization time to provide provisioning information
 *
 * @param[in] provisioned  true: provisioned, false: unprovisioned
 * @param[in] address      Unicast address of the primary element of the node.
                           Ignored if unprovisioned.
 * @param[in] iv_index     IV index for the first network of the node
                           Ignored if unprovisioned.
 *
 ******************************************************************************/
void sl_btmesh_on_provision_init_status(bool provisioned,
                                        uint16_t address,
                                        uint32_t iv_index)
{
  if (provisioned) {
    app_show_btmesh_node_provisioned(address, iv_index);
  } else {
    app_log("BT mesh node is unprovisioned, "
            "started unprovisioned beaconing...\r\n");
  }
}

// -----------------------------------------------------------------------------
// Provisioning Decorator Callbacks

/*******************************************************************************
 * Called when the Provisioning starts
 *
 * @param[in] result  Result code. 0: success, non-zero: error
 *
 ******************************************************************************/
void app_show_btmesh_node_provisioning_started(uint16_t result)
{
  app_log("BT mesh node provisioning is started (result: 0x%04x)\r\n",
          result);
  (void)result;
}

/*******************************************************************************
 * Called when the Provisioning finishes successfully
 *
 * @param[in] address      Unicast address of the primary element of the node.
                           Ignored if unprovisioned.
 * @param[in] iv_index     IV index for the first network of the node
                           Ignored if unprovisioned.
 *
 ******************************************************************************/
void app_show_btmesh_node_provisioned(uint16_t address,
                                      uint32_t iv_index)
{
  app_log("BT mesh node is provisioned (address: 0x%04x, iv_index: 0x%x)\r\n",
          address,
          iv_index);
  (void)address;
  (void)iv_index;
}

/*******************************************************************************
 * Called when the Provisioning fails
 *
 * @param[in] result  Result code. 0: success, non-zero: error
 *
 ******************************************************************************/
void sl_btmesh_on_node_provisioning_failed(uint16_t result)
{
  app_log("BT mesh node provisioning failed (result: 0x%04x)\r\n", result);
  (void) result;
}

// -----------------------------------------------------------------------------
// Factory Reset Callback

/*******************************************************************************
 * Shows the node reset information
 ******************************************************************************/
void app_show_btmesh_node_reset(void)
{
  app_log("Node reset\r\n");
}

/*******************************************************************************
 * Called when full reset is established, before system reset
 ******************************************************************************/
void sl_btmesh_factory_reset_on_full_reset(void)
{
  app_log("Factory reset\r\n");
}
