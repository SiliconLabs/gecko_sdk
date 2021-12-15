/***************************************************************************//**
 * @file
 * @brief Mesh Generic Base library
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

#include "app_assert.h"

#include "sl_bt_api.h"
#include "sl_btmesh_api.h"

#include "sl_btmesh_generic_model_capi_types.h"
#include "sl_btmesh_lib.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#include "sl_btmesh_generic_base.h"
#include "sl_btmesh_generic_base_config.h"

sl_status_t sl_btmesh_generic_base_init(void)
{
  return mesh_lib_init(SL_BTMESH_GENERIC_BASE_REGISTRY_INIT_SIZE,
                       GENERIC_BASE_INCREMENT);
}

void sl_btmesh_generic_base_on_event(sl_btmesh_msg_t *evt)
{
  sl_status_t sc = SL_STATUS_OK;
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_btmesh_evt_node_initialized_id:
#if GENERIC_BASE_SERVER || defined(SL_CATALOG_BTMESH_LIGHTING_SERVER_PRESENT) \
      || defined(SL_CATALOG_BTMESH_CTL_SERVER_PRESENT)                        \
      || defined(SL_CATALOG_BTMESH_HSL_SERVER_PRESENT)                        \
      || defined(SL_CATALOG_BTMESH_GENERIC_ONOFF_SERVER_PRESENT)

#if GENERIC_CTL_SERVER_INIT || defined(SL_CATALOG_BTMESH_CTL_SERVER_PRESENT)      \
      || GENERIC_HSL_SERVER_INIT || defined(SL_CATALOG_BTMESH_HSL_SERVER_PRESENT) \
      || GENERIC_POWER_LEVEL_SERVER_INIT

  #if GENERIC_CTL_SERVER_INIT || defined(SL_CATALOG_BTMESH_CTL_SERVER_PRESENT)
      sc = sl_btmesh_generic_server_init_ctl();
      app_assert_status_f(sc, "Failed to init ctl server\n");
  #endif // GENERIC_CTL_SERVER_INIT
  #if GENERIC_HSL_SERVER_INIT || defined(SL_CATALOG_BTMESH_HSL_SERVER_PRESENT)
      sc = sl_btmesh_generic_server_init_hsl();
      app_assert_status_f(sc, "Failed to init hsl server\n");
  #endif // GENERIC_HSL_SERVER_INIT
  #if GENERIC_POWER_LEVEL_SERVER_INIT
      sc = sl_btmesh_generic_server_init_power_level();
      app_assert_status_f(sc, "Failed to init power level server\n");
  #endif // GENERIC_POWER_LEVEL_SERVER_INIT
#elif GENERIC_LIGHTNESS_SERVER_INIT || defined(SL_CATALOG_BTMESH_LIGHTING_SERVER_PRESENT)
      sc = sl_btmesh_generic_server_init_lightness();
      app_assert_status_f(sc, "Failed to init lightness server\n");
#else // GENERIC_CTL_SERVER_INIT || GENERIC_HSL_SERVER_INIT || GENERIC_POWER_LEVEL_SERVER_INIT
  #if GENERIC_LEVEL_SERVER_INIT
      sc = sl_btmesh_generic_server_init_level();
      app_assert_status_f(sc, "Failed to init level server\n");
  #endif // GENERIC_LEVEL_SERVER_INIT
  #if GENERIC_POWER_ON_OFF_SERVER_INIT
      sc = sl_btmesh_generic_server_init_power_on_off();
      app_assert_status_f(sc, "Failed to init power on/off server\n");
  #else //GENERIC_POWER_ON_OFF_SERVER_INIT
    #if GENERIC_ON_OFF_SERVER_INIT || defined(SL_CATALOG_BTMESH_GENERIC_ONOFF_SERVER_PRESENT)
      sc = sl_btmesh_generic_server_init_on_off();
      app_assert_status_f(sc, "Failed to init on/off server\n");
    #endif // GENERIC_ON_OFF_SERVER_INIT
    #if GENERIC_DEFAULT_TRANSITION_TIME_SERVER_INIT
      sc = sl_btmesh_generic_server_init_default_transition_time();
      app_assert_status_f(sc, "Failed to init default transition time server\n");
    #endif // GENERIC_DEFAULT_TRANSITION_TIME_SERVER_INIT
  #endif //GENERIC_POWER_ON_OFF_SERVER_INIT
#endif // GENERIC_CTL_SERVER_INIT || GENERIC_HSL_SERVER_INIT || GENERIC_POWER_LEVEL_SERVER_INIT
#if GENERIC_BATTERY_SERVER_INIT
      sc = sl_btmesh_generic_server_init_battery();
      app_assert_status_f(sc, "Failed to init battery server\n");
#endif // GENERIC_BATTERY_SERVER_INIT
#if GENERIC_LOCATION_SERVER_INIT
      sc = sl_btmesh_generic_server_init_location();
      app_assert_status_f(sc, "Failed to init location server\n");
#endif // GENERIC_LOCATION_SERVER_INIT
#if GENERIC_PROPERTY_SERVER_INIT
      sc = sl_btmesh_generic_server_init_property();
      app_assert_status_f(sc, "Failed to init property server\n");
#endif // GENERIC_PROPERTY_SERVER_INIT
      sc = sl_btmesh_generic_server_init_common();
      app_assert_status_f(sc, "Failed to common init Generic Server\n");
#endif // GENERIC_BASE_SERVER

#if GENERIC_BASE_CLIENT || defined(SL_CATALOG_BTMESH_LIGHTING_CLIENT_PRESENT) \
      || defined(SL_CATALOG_BTMESH_CTL_CLIENT_PRESENT)

#if GENERIC_ON_OFF_CLIENT_INIT || defined(SL_CATALOG_BTMESH_LIGHTING_CLIENT_PRESENT)
      sc = sl_btmesh_generic_client_init_on_off();
      app_assert_status_f(sc, "Failed to init on/off client\n");
#endif // GENERIC_ON_OFF_CLIENT_INIT || defined(SL_CATALOG_BTMESH_LIGHTING_CLIENT_PRESENT)
#if GENERIC_LEVEL_SERVER_INIT
      sc = sl_btmesh_generic_client_init_level();
      app_assert_status_f(sc, "Failed to init level client\n");
#endif // GENERIC_LEVEL_SERVER_INIT
#if GENERIC_DEFAULT_TRANSITION_TIME_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_default_transition_time();
      app_assert_status_f(sc, "Failed to init default transition time client\n");
#endif // GENERIC_DEFAULT_TRANSITION_TIME_CLIENT_INIT
#if GENERIC_POWER_ON_OFF_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_power_on_off();
      app_assert_status_f(sc, "Failed to init power on/off client\n");
#endif // GENERIC_POWER_ON_OFF_CLIENT_INIT
#if GENERIC_POWER_LEVEL_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_power_level();
      app_assert_status_f(sc, "Failed to init power level client\n");
#endif // GENERIC_POWER_LEVEL_CLIENT_INIT
#if GENERIC_BATTERY_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_battery();
      app_assert_status_f(sc, "Failed to init battery client\n");
#endif // GENERIC_BATTERY_CLIENT_INIT
#if GENERIC_LOCATION_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_location();
      app_assert_status_f(sc, "Failed to init location client\n");
#endif // GENERIC_LOCATION_CLIENT_INIT
#if GENERIC_PROPERTY_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_property();
      app_assert_status_f(sc, "Failed to init property client\n");
#endif // GENERIC_PROPERTY_CLIENT_INIT
#if GENERIC_LIGHTNESS_CLIENT_INIT || defined(SL_CATALOG_BTMESH_LIGHTING_CLIENT_PRESENT)
      sc = sl_btmesh_generic_client_init_lightness();
      app_assert_status_f(sc, "Failed to init lightness client\n");
#endif // GENERIC_LIGHTNESS_CLIENT_INIT || defined(SL_CATALOG_BTMESH_LIGHTING_CLIENT_PRESENT)
#if GENERIC_CTL_CLIENT_INIT || defined(SL_CATALOG_BTMESH_CTL_CLIENT_PRESENT)
      sc = sl_btmesh_generic_client_init_ctl();
      app_assert_status_f(sc, "Failed to init ctl client\n");
#endif // GENERIC_CTL_CLIENT_INIT || defined(SL_CATALOG_BTMESH_CTL_CLIENT_PRESENT)
#if GENERIC_HSL_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_hsl();
      app_assert_status_f(sc, "Failed to init hsl client\n");
#endif // GENERIC_HSL_CLIENT_INIT
      sc = sl_btmesh_generic_client_init_common();
      app_assert_status_f(sc, "Failed to common init Generic Client\n");

#endif // GENERIC_BASE_CLIENT
      break;
#if GENERIC_BASE_SERVER || defined(SL_CATALOG_BTMESH_LIGHTING_SERVER_PRESENT)
    case sl_btmesh_evt_generic_server_client_request_id:
    // intentional fall through
    case sl_btmesh_evt_generic_server_state_recall_id:
    // intentional fall through
    case sl_btmesh_evt_generic_server_state_changed_id:
      mesh_lib_generic_server_event_handler(evt);
      break;
#endif // GENERIC_BASE_SERVER
#if GENERIC_BASE_CLIENT
    case sl_btmesh_evt_generic_client_server_status_id:
      mesh_lib_generic_client_event_handler(evt);
      break;
#endif // GENERIC_BASE_CLIENT
  }
}
