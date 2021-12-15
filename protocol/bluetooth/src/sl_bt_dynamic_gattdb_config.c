/***************************************************************************//**
 *@brief Bluetooth dynamic GATT database configuration
 *******************************************************************************
 * # License
 * <b> Copyright 2021 Silicon Laboratories Inc.www.silabs.com </b>
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
#include "sli_bt_gattdb_def.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#if defined(SL_CATALOG_BLUETOOTH_FEATURE_DYNAMIC_GATTDB_PRESENT)
#include "sl_bt_dynamic_gattdb_config.h"
  #if SL_BT_GATTDB_ENABLE_GATT_CACHING == 1
    #define GATTDB_ENABLE_GATT_CACHING SLI_BT_GATTDB_CONFIG_FLAG_ENABLE_GATT_CACHING
  #else
    #define GATTDB_ENABLE_GATT_CACHING 0
  #endif
  #if SL_BT_GATTDB_INCLUDE_STATIC_DATABASE == 1
    #define GATTDB_INCLUDE_STATIC      SLI_BT_GATTDB_CONFIG_FLAG_INCLUDE_STATIC_DB
  #else
    #define GATTDB_INCLUDE_STATIC      0
#endif
#else
  #define GATTDB_ENABLE_GATT_CACHING SLI_BT_GATTDB_CONFIG_FLAG_ENABLE_GATT_CACHING
  #define GATTDB_INCLUDE_STATIC      SLI_BT_GATTDB_CONFIG_FLAG_INCLUDE_STATIC_DB
#endif // SL_COMPONENT_CATALOG_PRESENT

#define SL_BT_GATTDB_CONFIG                                        \
  {                                                                \
    .flags = (GATTDB_ENABLE_GATT_CACHING | GATTDB_INCLUDE_STATIC), \
  }

/**
 * The configuration for dynamic GATT feature. It remains in flash and is
 * always available for the feature to re-initialize when on-demand start
 * feature is used.
 */
const sli_bt_gattdb_config_t gattdb_config = SL_BT_GATTDB_CONFIG;

extern sl_status_t sli_bt_dynamic_gattdb_configure(const sli_bt_gattdb_config_t*);

sl_status_t sl_bt_dynamic_gattdb_configure()
{
  return sli_bt_dynamic_gattdb_configure(&gattdb_config);
}
