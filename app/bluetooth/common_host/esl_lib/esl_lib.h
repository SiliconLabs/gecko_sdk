/***************************************************************************//**
 * @file
 * @brief ESL Access Point Host Library.
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

#ifndef ESL_LIB_H
#define ESL_LIB_H

#include <stdint.h>
#include "sl_status.h"
#include "sl_slist.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

// Invalid handle
#define ESL_LIB_INVALID_HANDLE                 NULL
#define ESL_LIB_INVALID_SERVICE_HANDLE         (UINT32_MAX)
#define ESL_LIB_INVALID_CHARACTERISTIC_HANDLE  (UINT16_MAX)

// LTK size (128 bit)
#define ESL_LIB_LTK_SIZE                       16
#define ESL_LIB_OOB_SIZE                       32
#define ESL_LIB_PASSKEY_SIZE                   4

#define ESL_LIB_ARRAY_HEADER_SIZE              (sizeof(uint8_t))
#define ESL_LIB_LONG_ARRAY_HEADER_SIZE         (sizeof(uint32_t))

#define ESL_LIB_TLV_HEADER_LEN                 (sizeof(esl_lib_tlv_t))

// Periodic advertisement interval for PAwR train.
// Value in units of 1.25 ms.
#define ESL_LIB_PERIODIC_ADV_MIN_INTERVAL_DEFAULT  1233
// Number of subevents, practically has to be equal to the supported number
// of ESL groups.
#define ESL_LIB_PERIODIC_ADV_MAX_INTERVAL_DEFAULT ESL_LIB_PERIODIC_ADV_MIN_INTERVAL_DEFAULT
// Scalable up to 7140 tags in 28 groups
#define ESL_LIB_PAWR_SUBEVENT_COUNT_DEFAULT        28
// 55 ms
#define ESL_LIB_PAWR_SUBEVENT_INTERVAL_DEFAULT     44
// Time between the advertising packet in a subevent and the first response
// slot. Value in units of 1.25 ms.
#define ESL_LIB_PAWR_RESPONSE_SLOT_DELAY_DEFAULT   30
// Time between response slots. Value in units of 0.125 ms.
// 0.75 ms enough for up to 75 bytes on 1M phy
// (including LL overhead plus T_IFS)
#define ESL_LIB_PAWR_RESPONSE_SLOT_SPACING_DEFAULT 6
// Number of subevent response slots, 23 is the absolute maximum of possible
// opcodes in a single sync packet of 48 bytes (= max. payload by ESLP spec)
#define ESL_LIB_PAWR_RESPONSE_SLOT_COUNT_DEFAULT   23

// -------------------------------
// General type definitions

// Boolean type
typedef enum esl_lib_bool_e {
  ESL_LIB_FALSE = 0,
  ESL_LIB_TRUE  = 1
} esl_lib_bool_t;

/// Node identification type
typedef enum esl_lib_node_id_type_e {
  ESL_LIB_NODE_ID_TYPE_NONE,
  ESL_LIB_NODE_ID_TYPE_ADDRESS,
  ESL_LIB_NODE_ID_TYPE_CONNECTION,
  ESL_LIB_NODE_ID_TYPE_PAWR,
} esl_lib_node_id_type_t;

/// Connection state type
typedef enum esl_lib_connection_state_e {
  ESL_LIB_CONNECTION_STATE_OFF,
  ESL_LIB_CONNECTION_STATE_CONNECTING,
  ESL_LIB_CONNECTION_STATE_RECONNECTING,
  ESL_LIB_CONNECTION_STATE_CONNECTION_OPENED,
  ESL_LIB_CONNECTION_STATE_APPLYING_LTK,
  ESL_LIB_CONNECTION_STATE_NEW_BOND_REQUIRED,
  ESL_LIB_CONNECTION_STATE_BONDING,
  ESL_LIB_CONNECTION_STATE_BONDING_FAIL_RECONNECT,
  ESL_LIB_CONNECTION_STATE_SERVICE_DISCOVERY,
  ESL_LIB_CONNECTION_STATE_DIS_DISCOVERY,
  ESL_LIB_CONNECTION_STATE_ESL_DISCOVERY,
  ESL_LIB_CONNECTION_STATE_ESL_SUBSCRIBE,
  ESL_LIB_CONNECTION_STATE_OTS_INIT,
  ESL_LIB_CONNECTION_STATE_CONNECTED,
  ESL_LIB_CONNECTION_STATE_GET_TAG_INFO,
  ESL_LIB_CONNECTION_STATE_OTS_IMAGE_TRANSFER,
  ESL_LIB_CONNECTION_STATE_OTS_GET_TYPE,
  ESL_LIB_CONNECTION_STATE_PAST_INIT,
  ESL_LIB_CONNECTION_STATE_PAST_CLOSE_CONNECTION,
  ESL_LIB_CONNECTION_STATE_WRITE_CONTROL_POINT,
  ESL_LIB_CONNECTION_STATE_CONFIGURE_TAG
} esl_lib_connection_state_t;

/// PAwR state type
typedef enum esl_lib_pawr_state_e {
  ESL_LIB_PAWR_STATE_INIT,
  ESL_LIB_PAWR_STATE_IDLE,
  ESL_LIB_PAWR_STATE_RUNNING
} esl_lib_pawr_state_t;

/// Common state type
typedef enum esl_lib_core_state_e {
  ESL_LIB_CORE_STATE_IDLE,
  ESL_LIB_CORE_STATE_CONNECTING
} esl_lib_core_state_t;

/// PAwR handle type
typedef void *esl_lib_pawr_handle_t;

/// Connection handle type
typedef void *esl_lib_connection_handle_t;

/// Node address type
typedef struct esl_lib_address_s {
  union {
    struct {
      uint8_t addr[6];  ///<  @brief Bluetooth address in reverse byte order */
    } address;
    uint8_t addr[6];    ///<  @brief alternative access to the bd_addr address
  };
  uint8_t address_type; ///<  @brief Bluetooth address type
} esl_lib_address_t;

typedef struct esl_lib_pawr_subevent_s {
  esl_lib_pawr_handle_t     handle;            ///< PAwR handle
  uint8_t                   subevent;          ///< Subevent
} esl_lib_pawr_subevent_t;

/// Combined node identification type
typedef struct esl_lib_node_id_s {
  esl_lib_node_id_type_t        type;              ///< Node ID type
  union esl_lib_node_id_id_u {
    esl_lib_connection_handle_t connection_handle; ///< Connection handle
    esl_lib_pawr_subevent_t     pawr;              ///< PAwR type
    esl_lib_address_t           address;           ///< BLE address
  }                             id;
} esl_lib_node_id_t;

/// Array type
typedef struct esl_lib_array_s {
  uint8_t len;     ///< Number of bytes stored in @p data
  uint8_t data[0]; ///< Data bytes
} esl_lib_array_t;

/// Long array type
typedef struct esl_lib_long_array_s {
  uint32_t len;     ///< Number of bytes stored in @p data
  uint8_t  data[0]; ///< Data bytes
} esl_lib_long_array_t;

/// PAWR configuration
typedef struct esl_lib_pawr_config_s {
  struct esl_lib_pawr_config_adv_interval_s {
    uint16_t               min;              ///< Minimum interval
    uint16_t               max;              ///< Maximum interval
  }                        adv_interval;     ///< Advertising interval
  struct esl_lib_pawr_config_subevent_s {
    uint8_t                count;            ///< Subevent count
    uint8_t                interval;         ///< Subevent interval
  }                        subevent;         ///< Subevent config
  struct esl_lib_pawr_config_response_slot_s {
    uint8_t                delay;            ///< Response slot delay
    uint8_t                spacing;          ///< Response slot spacing
    uint8_t                count;            ///< Response slot count
  }                        response_slot;    ///< Response slot config
} esl_lib_pawr_config_t;

/// Scan parameters
typedef struct esl_lib_scan_parameters_s {
  uint8_t  mode;                 ///< Passive or active scan, 0x0: passive, 0x1: active
  uint16_t interval;             /**< Scan interval. Time = Value x 0.625 ms,
                                      Range: 0x0004 to 0xFFFF, Time Range: 2.5 ms to 40.96 s */
  uint16_t window;               ///< Scan window. Range and factor is the same as for interval above.
  uint8_t  scanning_phy;         /**< The scanning PHY(s). Values:
                                      0x1: Initiate the scanning on the 1M PHY,
                                      0x4: Initiate the scanning on the Coded PHY,
                                      0x5: Simultaneous scanning by initiating the scanning on
                                           the 1M and Coded PHY alternatively. */
  uint8_t  discover_mode;        /**< Bluetooth discovery Mode. Values:
                                      0x0: Discover only limited discoverable devices,
                                      0x1: Discover limited and general discoverable devices,
                                      0x2: Discover non-discoverable, limited and general
                                      discoverable devices. */
} esl_lib_scan_parameters_t;

/// ESL host library event codes
typedef enum esl_lib_evt_type_e {
  ESL_LIB_EVT_SYSTEM_BOOT,
  ESL_LIB_EVT_SCAN_STATUS,
  ESL_LIB_EVT_TAG_FOUND,
  ESL_LIB_EVT_TAG_INFO,
  ESL_LIB_EVT_CONFIGURE_TAG_RESPONSE,
  ESL_LIB_EVT_CONNECTION_CLOSED,
  ESL_LIB_EVT_CONNECTION_OPENED,
  ESL_LIB_EVT_BONDING_DATA,
  ESL_LIB_EVT_BONDING_FINISHED,
  ESL_LIB_EVT_PAWR_STATUS,
  ESL_LIB_EVT_PAWR_RESPONSE,
  ESL_LIB_EVT_PAWR_DATA_REQUEST,
  ESL_LIB_EVT_SHUTDOWN_READY,
  ESL_LIB_EVT_ERROR,
  ESL_LIB_EVT_IMAGE_TRANSFER_FINISHED,
  ESL_LIB_EVT_IMAGE_TYPE,
  ESL_LIB_EVT_CONTROL_POINT_RESPONSE,
  ESL_LIB_EVT_CONTROL_POINT_NOTIFICATION,
  ESL_LIB_EVT_GENERAL,
} esl_lib_evt_type_t;

/// ESL host library event status codes
typedef enum esl_lib_status_e {
  ESL_LIB_STATUS_NO_ERROR,
  ESL_LIB_STATUS_UNSPECIFIED_ERROR,
  ESL_LIB_STATUS_UNASSOCITED,
  ESL_LIB_STATUS_GATT_TIMEOUT,
  ESL_LIB_STATUS_BONDING_FAILED,
  ESL_LIB_STATUS_FEATURE_NOT_SUPPORTED,
  ESL_LIB_STATUS_INVALID_STATE,
  ESL_LIB_STATUS_INVALID_PARAMETERS,
  ESL_LIB_STATUS_UNEXPECTED_RESET,
  ESL_LIB_STATUS_GATT_ERROR,
  ESL_LIB_STATUS_CONN_TIMEOUT,
  ESL_LIB_STATUS_CONN_LOST,
  ESL_LIB_STATUS_CONN_FAILED,
  ESL_LIB_STATUS_CONN_CLOSE_FAILED,
  ESL_LIB_STATUS_CONN_DISCOVERY_FAILED,
  ESL_LIB_STATUS_CONN_SUBSCRIBE_FAILED,
  ESL_LIB_STATUS_CONN_READ_FAILED,
  ESL_LIB_STATUS_CONN_CONFIG_FAILED,
  ESL_LIB_STATUS_LINK_LAYER,
  ESL_LIB_STATUS_NO_PAWR_SYNC,
  ESL_LIB_STATUS_OTS_ERROR,
  ESL_LIB_STATUS_OTS_GOTO_FAILED,
  ESL_LIB_STATUS_OTS_INIT_FAILED,
  ESL_LIB_STATUS_OTS_WRITE_RESP_FAILED,
  ESL_LIB_STATUS_OTS_UNEXPECTED_OFFSET,
  ESL_LIB_STATUS_OTS_TRANSFER_FAILED,
  ESL_LIB_STATUS_OTS_META_READ_FAILED,
  ESL_LIB_STATUS_SCAN_START_FAILED,
  ESL_LIB_STATUS_SCAN_STOP_FAILED,
  ESL_LIB_STATUS_SCAN_CONFIG_FAILED,
  ESL_LIB_STATUS_INIT_FAILED,
  ESL_LIB_STATUS_PAWR_START_FAILED,
  ESL_LIB_STATUS_PAWR_STOP_FAILED,
  ESL_LIB_STATUS_PAWR_CONFIG_FAILED,
  ESL_LIB_STATUS_PAWR_SET_DATA_FAILED,
  ESL_LIB_STATUS_RESOURCE_EXCEEDED,
  ESL_LIB_STATUS_PAST_INIT_FAILED,
  ESL_LIB_STATUS_CONN_WRITE_CP_FAILED,
  ESL_LIB_STATUS_CONN_TAG_CONFIG_FAILED,
  ESL_LIB_STATUS_CONTROL_FAILED,
  ESL_LIB_STATUS_UNKNOWN_COMMAND,
} esl_lib_status_t;

// -------------------------------
// Event data types

/// Event data type
typedef enum esl_lib_data_type_e {
  // GATT related
  ESL_LIB_DATA_TYPE_UNINITIALIZED,
  ESL_LIB_DATA_TYPE_GATT_ESL_ADDRESS,
  ESL_LIB_DATA_TYPE_GATT_AP_SYNC_KEY,
  ESL_LIB_DATA_TYPE_GATT_RESPONSE_KEY,
  ESL_LIB_DATA_TYPE_GATT_CONTROL_POINT,
  ESL_LIB_DATA_TYPE_GATT_CURRENT_TIME,
  ESL_LIB_DATA_TYPE_GATT_DISPLAY_INFO,
  ESL_LIB_DATA_TYPE_GATT_IMAGE_INFO,
  ESL_LIB_DATA_TYPE_GATT_SENSOR_INFO,
  ESL_LIB_DATA_TYPE_GATT_LED_INFO,
  ESL_LIB_DATA_TYPE_GATT_PNP_ID,
  ESL_LIB_DATA_TYPE_GATT_SERIAL_NUMBER,
  ESL_LIB_DATA_TYPE_GATT_OTS_FEATURE,
  ESL_LIB_DATA_TYPE_GATT_OTS_OBJECT_TYPE,
  // PAWR ralated
  ESL_LIB_DATA_TYPE_PAWR_DATA,
  ESL_LIB_DATA_TYPE_PAWR_RESP_SLOT,
  ESL_LIB_DATA_TYPE_PAWR_SUBEVENT,
  ESL_LIB_DATA_TYPE_SUBEVENT_START,
  ESL_LIB_DATA_TYPE_SUBEVENT_DATA_COUNT,
} esl_lib_data_type_t;

/// Type-Length-Value (TLV) type
typedef struct esl_lib_tlv_s {
  esl_lib_data_type_t  type;   ///< Event data type
  esl_lib_long_array_t data;   ///< Length and value
} esl_lib_tlv_t;

/// OTS features
typedef struct esl_lib_ots_features_s {
  uint32_t oacp_features;
  uint32_t olcp_features;
} esl_lib_ots_features_t;

/// GATT characteristic index
typedef enum esl_lib_characteristic_index_e {
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_ADDRESS               = 0,
  ESL_LIB_CHARACTERISTIC_INDEX_AP_SYNC_KEY_MATERIAL      = 1,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_RESPONSE_KEY_MATERIAL = 2,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_CURRENT_ABSOLUTE_TIME = 3,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_DISPLAY_INFORMATION   = 4,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_IMAGE_INFORMATION     = 5,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_SENSOR_INFORMATION    = 6,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_LED_INFORMATION       = 7,
  ESL_LIB_CHARACTERISTIC_INDEX_ESL_CONTROL_POINT         = 8,
  ESL_LIB_CHARACTERISTIC_INDEX_SIZE                      = 9
} esl_lib_characteristic_index_t;

typedef enum esl_lib_characteristic_index_dis_e {
  ESL_LIB_CHARACTERISTIC_INDEX_DIS_PNP_ID                = 0,
  ESL_LIB_CHARACTERISTIC_INDEX_DIS_SN                    = 1,
  ESL_LIB_CHARACTERISTIC_INDEX_DIS_SIZE                  = 2
} esl_lib_characteristic_index_dis_t;

/// OTS GATT Database handles
typedef uint16_t esl_lib_ots_gattdb_handles_t[12];

/// GATT Database handles
typedef struct esl_lib_gattdb_handles_s {
  struct esl_lib_gattdb_handles_services_s {
    uint32_t esl;
    uint32_t ots;
    uint32_t dis;
  } services;
  uint16_t esl_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_SIZE];
  uint16_t dis_characteristics[ESL_LIB_CHARACTERISTIC_INDEX_DIS_SIZE];
  esl_lib_ots_gattdb_handles_t ots_characteristics;
} esl_lib_gattdb_handles_t;

// -------------------------------
// Event data structures

/// System boot event
typedef struct esl_lib_evt_system_boot_s {
  esl_lib_address_t address;     ///< Radio BLE address (NCP)
  uint32_t          radio_id;    ///< Radio ID
  sl_status_t       status;      ///< Status code
} esl_lib_evt_system_boot_t;

/// Scan status type
typedef struct esl_lib_evt_scan_status_s {
  esl_lib_bool_t            enabled;         ///< Scan enabled or disabled
  esl_lib_bool_t            configured;      ///< Scan configuration state
  esl_lib_scan_parameters_t parameters;      ///< Scan parameters
} esl_lib_evt_scan_status_t;

/// Tag found event
typedef struct esl_lib_evt_tag_found_s {
  esl_lib_address_t address;      ///< BLE address
  int8_t            rssi;         ///< RSSI value
} esl_lib_evt_tag_found_t;

/// Tag information event (variable length)
typedef struct esl_lib_evt_tag_info_s {
  esl_lib_connection_handle_t  connection_handle; ///< Connection handle
  esl_lib_long_array_t         tlv_data;          ///< Byte array of TLVs
} esl_lib_evt_tag_info_t;

/// Tag configuration response event
typedef struct esl_lib_evt_tag_config_response_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_data_type_t         type;              ///< Data type
  sl_status_t                 status;            ///< Status
} esl_lib_evt_configure_tag_response_t;

/// ESL control point response event
typedef struct esl_lib_evt_control_point_response_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  sl_status_t                 status;            ///< Status
  esl_lib_array_t             data_sent;         ///< Data sent in write
} esl_lib_evt_control_point_response_t;

/// ESL control point notification
typedef struct esl_lib_evt_control_point_notification_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_array_t             data;              ///< Data
} esl_lib_evt_control_point_notification_t;

/// Connection closed event
typedef struct esl_lib_evt_connection_closed_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_address_t           address;           ///< BLE address
  sl_status_t                 reason;            ///< Reason
} esl_lib_evt_connection_closed_t;

/// Connection opened event
typedef struct esl_lib_evt_connection_opened_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_address_t           address;           ///< BLE address
  esl_lib_gattdb_handles_t    gattdb_handles;    ///< GATT database handles
} esl_lib_evt_connection_opened_t;

/// Bonding data event
typedef struct esl_lib_evt_bonding_data_s {
  esl_lib_connection_handle_t connection_handle;     ///< Connection handle
  esl_lib_address_t           address;               ///< BLE address
  uint8_t                     ltk[ESL_LIB_LTK_SIZE]; ///< LTK data
} esl_lib_evt_bonding_data_t;

/// Bonding finished event
typedef struct esl_lib_evt_bonding_finished_s {
  esl_lib_connection_handle_t connection_handle;     ///< Connection handle
  esl_lib_address_t           address;               ///< BLE address
} esl_lib_evt_bonding_finished_t;

/// PAwR status event
typedef struct esl_lib_evt_pawr_status_s {
  esl_lib_pawr_handle_t       pawr_handle; ///< PAwR handle
  esl_lib_bool_t              enabled;     ///< Started or stopped
  esl_lib_bool_t              configured;  ///< Configuration status
  esl_lib_pawr_config_t       config;      ///< PAwR configuration
} esl_lib_evt_pawr_status_t;

/// ESL image transfer finished
typedef struct esl_lib_evt_image_transfer_finished_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  uint8_t                     img_index;         ///< Image index
  sl_status_t                 status;            ///< Status
} esl_lib_evt_image_transfer_finished_t;

/// ESL image type event data
typedef struct esl_lib_evt_image_type_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  uint8_t                     img_index;         ///< Image index
  esl_lib_long_array_t        type_data;         ///< Image type
} esl_lib_evt_image_type_t;

/// PAWR response (variable length)
typedef struct esl_lib_evt_pawr_response_s {
  esl_lib_pawr_handle_t pawr_handle;   ///< PAwR handle
  uint8_t               response_slot; ///< Response slot
  uint8_t               subevent;      ///< Subevent
  esl_lib_long_array_t  data;          ///< PAwR Data
} esl_lib_evt_pawr_response_t;

/// PAWR data request
typedef struct esl_lib_evt_pawr_data_request_s {
  esl_lib_pawr_handle_t pawr_handle;         ///< PAwR handle
  uint8_t               subevent_start;      ///< Subevent start
  uint8_t               subevent_data_count; ///< Subevent data count
} esl_lib_evt_pawr_data_request_t;

/// OTS object type response type
typedef struct esl_lib_evt_ots_return_type_s {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  uint8_t                     img_index;         ///< Image index
  uint8_t                     object_type;       ///< Object type
  uint16_t                    gatt_status;       ///< GATT status
} esl_lib_evt_ots_return_type_t;

typedef union esl_lib_status_data_u {
  esl_lib_core_state_t       core_state;       ///< Core state
  esl_lib_connection_state_t connection_state; ///< Connection state
  esl_lib_pawr_state_t       pawr_state;       ///< PAwR state
} esl_lib_status_data_t;

/// Error event
typedef struct esl_lib_evt_error_s {
  esl_lib_node_id_t      node_id;      ///< Node ID
  esl_lib_status_t       lib_status;   ///< Library status
  sl_status_t            sl_status;    ///< Silicon Labs Status code
  esl_lib_status_data_t  data;         ///< Specific status data
} esl_lib_evt_error_t;

/// Event data union type
typedef union esl_lib_evt_data_u {
  esl_lib_evt_system_boot_t                evt_boot;                       ///< Boot event data
  esl_lib_evt_scan_status_t                evt_scan_status;                ///< Scan status data
  esl_lib_evt_tag_found_t                  evt_tag_found;                  ///< Tag found during scanning
  esl_lib_evt_tag_info_t                   evt_tag_info;                   ///< Tag information values
  esl_lib_evt_configure_tag_response_t     evt_configure_tag_response;     ///< Tag configuration response
  esl_lib_evt_control_point_response_t     evt_control_point_response;     ///< ESL Control Point response
  esl_lib_evt_control_point_notification_t evt_control_point_notification; ///< ESL Control Point notification
  esl_lib_evt_connection_closed_t          evt_connection_closed;          ///< Connection closed
  esl_lib_evt_connection_opened_t          evt_connection_opened;          ///< Connection opened
  esl_lib_evt_bonding_data_t               evt_bonding_data;               ///< Bonding data
  esl_lib_evt_bonding_finished_t           evt_bonding_finished;           ///< Bonding finished
  esl_lib_evt_image_transfer_finished_t    evt_image_transfer_finished;    ///< Image transfer finished
  esl_lib_evt_image_type_t                 evt_image_type;                 ///< Image type received
  esl_lib_evt_pawr_status_t                evt_pawr_status;                ///< PAwR status
  esl_lib_evt_pawr_response_t              evt_pawr_response;              ///< PAWR response
  esl_lib_evt_pawr_data_request_t          evt_pawr_data_request;          ///< PAWR data request
  esl_lib_evt_error_t                      evt_error;                      ///< Error event
  esl_lib_long_array_t                     evt_general;                    ///< General event type
} esl_lib_evt_data_t;

/// Key type
typedef enum esl_lib_key_type_e {
  ESL_LIB_KEY_TYPE_NO_KEY,
  ESL_LIB_KEY_TYPE_LTK,
  ESL_LIB_KEY_TYPE_PASSKEY,
  ESL_LIB_KEY_TYPE_OOB_DATA
} esl_lib_key_type_t;

// -------------------------------
// Callback types

/***************************************************************************//**
 * ESL Library event handler function type
 * @param[in] evt_code Event type code.
 * @param[in] evt_data Event data.
 ******************************************************************************/
typedef void (*esl_lib_on_event_t)(esl_lib_evt_type_t evt_code,
                                   esl_lib_evt_data_t *evt_data);

// -------------------------------
// Logging types

/// Log levels
typedef enum esl_lib_log_level_e {
  ESL_LIB_LOG_LEVEL_DEBUG,
  ESL_LIB_LOG_LEVEL_INFO,
  ESL_LIB_LOG_LEVEL_WARNING,
  ESL_LIB_LOG_LEVEL_ERROR,
  ESL_LIB_LOG_LEVEL_CRITICAL
} esl_lib_log_level_t;

/***************************************************************************//**
 * ESL Library logging callback function type
 * @param[in] level    Log level.
 * @param[in] module   Module name.
 * @param[in] log      Log text.
 * @param[in] file     Source file of the log message.
 * @param[in] line     Line number within the source file.
 * @param[in] function The function name that the logging is initiated from.
 ******************************************************************************/
typedef void (*esl_lib_log_callback_t)(esl_lib_log_level_t level,
                                       char                *module,
                                       char                *log,
                                       char                *file,
                                       int                 line,
                                       char                *function);

// -----------------------------------------------------------------------------
// Library public functions

// -------------------------------
// Library management functions

/**************************************************************************//**
 * Start ESL host library.
 * @param[in] config        Library configuration character string.
 * @param[in] event_handler Event handler callback function.
 * @param[in] log_fn        Log function or NULL if no logging is required.
 *
 * @return Status.
 * @note This function should be called from a separate thread, because
 *       it starts the main execution loop of the library. It returns only
 *       when some error condition occurs or esl_lib_stop() called.
 *****************************************************************************/
sl_status_t esl_lib_start(char                   *config,
                          esl_lib_on_event_t     event_handler,
                          esl_lib_log_callback_t log_fn);

/**************************************************************************//**
 * Stop ESL host library processing.
 *
 * @return Status.
 *****************************************************************************/
sl_status_t esl_lib_stop(void);

// -------------------------------
// Connection handling

/**************************************************************************//**
 * Connect to a node using either Bluetooth address or PAwR parameters.
 * @param[in] address  The address to connect to.
 * @param[in] pawr     PAwR parameters if the connection is requested based on
 *                     the PAwR subevent or NULL if connection is requested
 *                     based on legacy advertisement.
 * @param[in] identity Pointer to AP identity address.
 *                     NULL means no change in identity.
 * @param[in] key_type Key type
 * @param[in] key      Pointer to key material. NULL Can be only used with
 *                     ESL_LIB_KEY_TYPE_NO_KEY as key_type.
 * @param[in] gattdb   Pointer to GATT database handles
 *                     NULL means the discovery will be done.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_connect(esl_lib_address_t         address,
                            esl_lib_pawr_subevent_t   *pawr,
                            esl_lib_address_t         *identity,
                            esl_lib_key_type_t        key_type,
                            esl_lib_array_t           *key,
                            esl_lib_gattdb_handles_t  *gattdb);

/**************************************************************************//**
 * Close connection to the tag.
 * @param[in] connection_handle Connection handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_close_connection(esl_lib_connection_handle_t connection_handle);

// -------------------------------
// ESL information

/**************************************************************************//**
 * Read all information from the connected tag.
 * @param[in] connection_handle Connection handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_get_tag_info(esl_lib_connection_handle_t connection_handle);

/**************************************************************************//**
 * Configure a tag during connection.
 * @param[in] connection_handle Connection handle.
 * @param[in] tlv_data          Configuration TLV data.
 * @param[in] att_response      Require ATT response (force Write With Response).
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_configure_tag(esl_lib_connection_handle_t connection_handle,
                                  esl_lib_long_array_t        *tlv_data,
                                  esl_lib_bool_t              att_response);

/**************************************************************************//**
 * Write ESL Control Point with a command.
 * @param[in] connection_handle Connection handle.
 * @param[in] data              Payload data.
 * @param[in] att_response      Require ATT response (force Write With Response).
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_write_control_point(esl_lib_connection_handle_t connection_handle,
                                        esl_lib_array_t             *data,
                                        esl_lib_bool_t              att_response);

// -------------------------------
// PAwR functions

/**************************************************************************//**
 * Create a PAwR set.
 * @param[out] handle_out Created PAwR handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_create(esl_lib_pawr_handle_t *handle_out);

/**************************************************************************//**
 * Remove a PAwR set.
 * @param[in] pawr_handle PAwR handle to delete.
 *
 * @return Status code.
 * @note PAwR must be stopped before removal.
 *****************************************************************************/
sl_status_t esl_lib_pawr_remove(esl_lib_pawr_handle_t pawr_handle);

/**************************************************************************//**
 * Start periodic advertisement with responses (PAwR).
 * @param[in] pawr_handle PAwR handle.
 * @param[in] enable      Enable (true) or disable (false)
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_enable(esl_lib_pawr_handle_t pawr_handle,
                                esl_lib_bool_t        enable);

/**************************************************************************//**
 * Set periodic advertisement with responses data.
 * @param[in] pawr_handle PAwR handle.
 * @param[in] subevent    Subevent number.
 * @param[in] payload     Payload data.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_pawr_set_data(esl_lib_pawr_handle_t pawr_handle,
                                  uint8_t               subevent,
                                  uint8_t               response_slot_max,
                                  esl_lib_array_t       *payload);

/**************************************************************************//**
 * Configure periodic advertisement with responses (PAwR).
 * @param[in] pawr_handle PAwR handle.
 * @param[in] pawr_config Periodic advertisement with responses data structure
 *                        pointer.
 *
 * @return Status code.
 * @note Configuration will be effective on next PAwR start.
 *****************************************************************************/
sl_status_t esl_lib_pawr_configure(esl_lib_pawr_handle_t       pawr_handle,
                                   const esl_lib_pawr_config_t *pawr_config);

/**************************************************************************//**
 * Get PAwR status including configuration.
 * @param[in] pawr_handle PAwR handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_get_pawr_status(esl_lib_pawr_handle_t pawr_handle);

/**************************************************************************//**
 * Initiate periodic advertisement sync transfer.
 * @param[in] connection_handle Connection handle.
 * @param[in] pawr_handle       PAwR handle.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_initiate_past(esl_lib_connection_handle_t connection_handle,
                                  esl_lib_pawr_handle_t       pawr_handle);

// -------------------------------
// Image transfer

/**************************************************************************//**
 * Write image.
 * @param[in] connection_handle Connection handle.
 * @param[in] img_index         Image index.
 * @param[in] img_size          Image size in bytes.
 * @param[in] img_data          Image data pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_write_image(esl_lib_connection_handle_t connection_handle,
                                uint8_t                     img_index,
                                size_t                      img_size,
                                void                        *img_data);

/**************************************************************************//**
 * Get image type (OTS Object Type).
 * @param[in] connection_handle Connection handle.
 * @param[in] img_index         Image index.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_get_image_type(esl_lib_connection_handle_t connection_handle,
                                   uint8_t                     img_index);

// -------------------------------
// Scanning

/**************************************************************************//**
 * Configure scanning.
 * @param[in] params Scan parameters structure pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_scan_configure(esl_lib_scan_parameters_t *params);

/**************************************************************************//**
 * Enable or disable scan.
 * @param[in] enable Desired status of the scanning.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_scan_enable(esl_lib_bool_t enable);

/**************************************************************************//**
 * Get scan status and configuration parameters.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_get_scan_status(void);

/**************************************************************************//**
 * Send a general command to the ESL Library.
 * This function is for internal use only.
 *
 * @param[in] cmd_code Command code.
 * @param[in] data     Pointer to data.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_general_cmd(uint8_t              cmd_code,
                                esl_lib_long_array_t *data);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_H
