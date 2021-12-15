/***************************************************************************//**
 *@brief Bluetooth LE Power Control feature initialization
 *******************************************************************************
 *# License
 * <b> Copyright 2020 Silicon Laboratories Inc.www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement(MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "sl_status.h"
#include "sl_bt_power_control_config.h"
#include "sl_bt_ll_config.h"
#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#define SL_BT_POWER_CONTROL_CONFIG                              \
  {                                                             \
    .activate_power_control = SL_BT_ACTIVATE_POWER_CONTROL,     \
    .golden_rssi_min_1m = SL_BT_GOLDEN_RSSI_MIN_1M,             \
    .golden_rssi_max_1m = SL_BT_GOLDEN_RSSI_MAX_1M,             \
    .golden_rssi_min_2m = SL_BT_GOLDEN_RSSI_MIN_2M,             \
    .golden_rssi_max_2m = SL_BT_GOLDEN_RSSI_MAX_2M,             \
    .golden_rssi_min_coded_s8 = SL_BT_GOLDEN_RSSI_MIN_CODED_S8, \
    .golden_rssi_max_coded_s8 = SL_BT_GOLDEN_RSSI_MAX_CODED_S8, \
    .golden_rssi_min_coded_s2 = SL_BT_GOLDEN_RSSI_MIN_CODED_S2, \
    .golden_rssi_max_coded_s2 = SL_BT_GOLDEN_RSSI_MAX_CODED_S2, \
  }

extern sl_status_t sli_bt_init_power_control();
extern sl_status_t ll_connPowerControlEnable(const sl_bt_ll_power_control_config_t *);

sl_status_t sl_bt_init_power_control()
{
  sl_bt_ll_power_control_config_t config = SL_BT_POWER_CONTROL_CONFIG;

  #ifdef SL_CATALOG_BLUETOOTH_CONTROLLER_ONLY_PRESENT
  return ll_connPowerControlEnable(&config);
  #else
  return sli_bt_init_power_control(&config);
  #endif
}
