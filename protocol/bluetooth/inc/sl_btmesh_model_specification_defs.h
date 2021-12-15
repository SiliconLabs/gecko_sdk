/******************************************************************************/
/**
 * @file   sl_btmesh_model_specification_defs.h
 * @brief  Silicon Labs Bluetooth Mesh Model v1.0 Specification Definitions
 *
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
#ifndef SL_BTMESH_MODEL_SPECIFICATION_DEFS_H
#define SL_BTMESH_MODEL_SPECIFICATION_DEFS_H

#include "sl_btmesh_capi_types.h"

/** Generic on/off server */
#define MESH_GENERIC_ON_OFF_SERVER_MODEL_ID             0x1000
/** Generic on/off client */
#define MESH_GENERIC_ON_OFF_CLIENT_MODEL_ID             0x1001

/** Generic level server */
#define MESH_GENERIC_LEVEL_SERVER_MODEL_ID              0x1002
/** Generic level client */
#define MESH_GENERIC_LEVEL_CLIENT_MODEL_ID              0x1003

/** Generic transition time server */
#define MESH_GENERIC_TRANSITION_TIME_SERVER_MODEL_ID    0x1004
/** Generic transition time client */
#define MESH_GENERIC_TRANSITION_TIME_CLIENT_MODEL_ID    0x1005

/** Generic power on/off server */
#define MESH_GENERIC_POWER_ON_OFF_SERVER_MODEL_ID       0x1006
/** Generic power on/off setup server */
#define MESH_GENERIC_POWER_ON_OFF_SETUP_SERVER_MODEL_ID 0x1007
/** Generic power on/off client */
#define MESH_GENERIC_POWER_ON_OFF_CLIENT_MODEL_ID       0x1008

/** Generic power level server */
#define MESH_GENERIC_POWER_LEVEL_SERVER_MODEL_ID        0x1009
/** Generic power level setup server */
#define MESH_GENERIC_POWER_LEVEL_SETUP_SERVER_MODEL_ID  0x100a
/** Generic power level client */
#define MESH_GENERIC_POWER_LEVEL_CLIENT_MODEL_ID        0x100b

/** Generic battery server */
#define MESH_GENERIC_BATTERY_SERVER_MODEL_ID            0x100c
/** Generic battery client */
#define MESH_GENERIC_BATTERY_CLIENT_MODEL_ID            0x100d

/** Generic location server */
#define MESH_GENERIC_LOCATION_SERVER_MODEL_ID           0x100e
/** Generic location setup server */
#define MESH_GENERIC_LOCATION_SETUP_SERVER_MODEL_ID     0x100f
/** Generic location client */
#define MESH_GENERIC_LOCATION_CLIENT_MODEL_ID           0x1010

/** Generic admin property server */
#define MESH_GENERIC_ADMIN_PROPERTY_SERVER_MODEL_ID     0x1011
/** Generic manufacturer property server */
#define MESH_GENERIC_MANUF_PROPERTY_SERVER_MODEL_ID     0x1012
/** Generic user property server */
#define MESH_GENERIC_USER_PROPERTY_SERVER_MODEL_ID      0x1013
/** Generic client property server */
#define MESH_GENERIC_CLIENT_PROPERTY_SERVER_MODEL_ID    0x1014
/** Generic property client */
#define MESH_GENERIC_PROPERTY_CLIENT_MODEL_ID           0x1015

/** Sensor Server model ID */
#define MESH_SENSOR_SERVER_MODEL_ID                     0x1100
/** Sensor Setup Server model ID*/
#define MESH_SENSOR_SETUP_SERVER_MODEL_ID               0x1101
/** Sensor Client model ID */
#define MESH_SENSOR_CLIENT_MODEL_ID                     0x1102

/** Time Server model ID */
#define MESH_TIME_SERVER_MODEL_ID                       0x1200
/** Time Setup Server model ID */
#define MESH_TIME_SETUP_SERVER_MODEL_ID                 0x1201
/** Time Client model ID */
#define MESH_TIME_CLIENT_MODEL_ID                       0x1202

/** Scheduler Server model ID */
#define MESH_SCHEDULER_SERVER_MODEL_ID                  0x1206
/** Scheduler Setup Server model ID */
#define MESH_SCHEDULER_SETUP_SERVER_MODEL_ID            0x1207
/** Scheduler Client model ID */
#define MESH_SCHEDULER_CLIENT_MODEL_ID                  0x1208

/** Light lightness server */
#define MESH_LIGHTING_LIGHTNESS_SERVER_MODEL_ID         0x1300
/** Light lightness setup server */
#define MESH_LIGHTING_LIGHTNESS_SETUP_SERVER_MODEL_ID   0x1301
/** Light lightness client */
#define MESH_LIGHTING_LIGHTNESS_CLIENT_MODEL_ID         0x1302

/** Light CTL server */
#define MESH_LIGHTING_CTL_SERVER_MODEL_ID               0x1303
/** Light CTL setup server */
#define MESH_LIGHTING_CTL_SETUP_SERVER_MODEL_ID         0x1304
/** Light CTL client */
#define MESH_LIGHTING_CTL_CLIENT_MODEL_ID               0x1305
/** Light CTL temperature server */
#define MESH_LIGHTING_CTL_TEMPERATURE_SERVER_MODEL_ID   0x1306

/** Light HSL server */
#define MESH_LIGHTING_HSL_SERVER_MODEL_ID               0x1307
/** Light HSL setup server */
#define MESH_LIGHTING_HSL_SETUP_SERVER_MODEL_ID         0x1308
/** Light HSL client */
#define MESH_LIGHTING_HSL_CLIENT_MODEL_ID               0x1309
/** Light HSL hue server */
#define MESH_LIGHTING_HSL_HUE_SERVER_MODEL_ID           0x130a
/** Light HSL saturation server */
#define MESH_LIGHTING_HSL_SATURATION_SERVER_MODEL_ID    0x130b

/** Light xyl server */
#define MESH_LIGHTING_XYL_SERVER_MODEL_ID               0x130c
/** Light xyl setup server */
#define MESH_LIGHTING_XYL_SETUP_SERVER_MODEL_ID         0x130d
/** Light xyl client */
#define MESH_LIGHTING_XYL_CLIENT_MODEL_ID               0x130e

/**
 * Enumeration describing attributes a model supports.
 * Multiple bits can be supported.
 */
typedef enum {
  sl_btmesh_model_attributes_none       =                      0, /**< No attribute flags */
  sl_btmesh_model_supports_subscription =               (1 << 0), /**< Subscription supported */
  sl_btmesh_model_supports_publication  =               (1 << 1), /**< Publication supported */
} sl_btmesh_model_attributes_bitmask_t;

/**
 * @brief Check supported attributes bitmask for Bluetooth SIG model
 *
 * @param model_id Model ID of the model to check
 * @param attributes If model is recognized, attributes are written here
 * @return SL_STATUS_OK if model is recognized, SL_STATUS_NOT_SUPPORTED otherwise
 */
sl_status_t mesh_stack_bt_sig_model_attributes(uint16_t model_id,
                                               sl_btmesh_model_attributes_bitmask_t *attributes);

#endif
