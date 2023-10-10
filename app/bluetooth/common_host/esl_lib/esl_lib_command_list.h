/***************************************************************************//**
 * @file
 * @brief ESL Command List manipulation header.
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

#ifndef ESL_LIB_COMMAND_LIST_H
#define ESL_LIB_COMMAND_LIST_H

#include <stdint.h>
#include "sl_status.h"
#include "sl_bt_api.h"
#include "sl_slist.h"
#include "esl_lib.h"
#include "esl_lib_log.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

// Command list header length
#define ESL_LIB_COMMAND_LIST_HEADER_LEN  (sizeof(esl_lib_command_list_cmd_t) - sizeof(esl_lib_command_list_cmd_data_t))

// ESL host library command codes
typedef enum {
  ESL_LIB_CMD_CONNECT                      = 0,   // Connect to a tag (address or PAwR)
  ESL_LIB_CMD_CLOSE_CONNECTION             = 1,   // Close an existing connection
  ESL_LIB_CMD_GET_TAG_INFO                 = 2,   // Get tag info
  ESL_LIB_CMD_CONFIGURE_TAG                = 3,   // Configure tag
  ESL_LIB_CMD_PAWR_ENABLE                  = 4,   // Create and enable or disable PAwR
  ESL_LIB_CMD_PAWR_SET_DATA                = 5,   // Set PAwR data
  ESL_LIB_CMD_PAWR_CONFIGURE               = 6,   // Configure PAwR
  ESL_LIB_CMD_INITIATE_PAST                = 7,   // Initiate PAST (using connection and PAwR)
  ESL_LIB_CMD_WRITE_IMAGE                  = 8,   // Write image data
  ESL_LIB_CMD_GET_IMAGE_TYPE               = 9,   // Read type of an image
  ESL_LIB_CMD_SCAN_ENABLE                  = 10,  // Enable or disable scanning
  ESL_LIB_CMD_SCAN_CONFIG                  = 11,  // Configure scan
  ESL_LIB_CMD_WRITE_CONTROL_POINT          = 12,  // Write ESL Control Point
  ESL_LIB_CMD_GET_SCAN_STATUS              = 13,  // Get scan status
  ESL_LIB_CMD_GET_PAWR_STATUS              = 14,  // Get PAwR status
  ESL_LIB_CMD_AP_CONTROL_ADV_ENABLE        = 101, // Enable/disable AP control advertising
  ESL_LIB_CMD_AP_CONTROL_CP_RESPONSE       = 102, // Notify AP control control point
  ESL_LIB_CMD_AP_CONTROL_IT_RESPONSE       = 103  // Notify AP control image transfer
} esl_lib_cmd_t;

/// Connect TLV data type
typedef enum {
  ESL_LIB_CONNECT_DATA_TYPE_LTK,
  ESL_LIB_CONNECT_DATA_TYPE_PASSKEY,
  ESL_LIB_CONNECT_DATA_TYPE_OOB_DATA,
  ESL_LIB_CONNECT_DATA_TYPE_IDENTITY_ADDRESS,
  ESL_LIB_CONNECT_DATA_TYPE_GATTDB_HANDLES,
  ESL_LIB_CONNECT_DATA_TYPE_PAWR,
  ESL_LIB_CONNECT_DATA_TYPE_INVALID_TYPE
} esl_lib_connect_data_type_t;

/// Connect TLV structure type
typedef struct {
  esl_lib_connect_data_type_t type;
  esl_lib_array_t             data;
} esl_lib_connect_tlv_t;

/// Connect parameters
typedef struct {
  esl_lib_address_t    address;         ///< Bluetooth address
  esl_lib_connection_handle_t conn_hnd; ///< Connection handle
  uint8_t              retries_left;    ///< Number of remaining retries
  esl_lib_long_array_t tlv_data;        ///< Data containing Connect TLVs
} esl_lib_command_list_cmd_connect_t;

/// Write ESL Control Point
typedef struct {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_bool_t              att_response;      ///< Write with response
  esl_lib_array_t             data;              ///< Data
} esl_lib_command_list_cmd_write_control_point_t;

/// Configure tag
typedef struct {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_bool_t              att_response;      ///< Write with response
  esl_lib_long_array_t        tlv_data;          ///< TLV Data
} esl_lib_command_list_cmd_configure_tag_t;

/// Start periodic advertisement
typedef struct {
  esl_lib_pawr_handle_t pawr_handle; ///< PAwR handle
  esl_lib_bool_t        enable;      ///< Enable or disable
} esl_lib_command_list_cmd_pawr_enable_t;

/// Set PAwR data
typedef struct {
  esl_lib_pawr_handle_t pawr_handle;        ///< PAwR handle
  uint8_t               subevent;           ///< Subevent
  uint8_t               response_slot_max;  ///< The number of response slots to be used
  uint8_t               retry;              ///< retry count for set data
  esl_lib_array_t       data;               ///< Payload
} esl_lib_command_list_cmd_pawr_set_data_t;

/// Set PAwR config
typedef struct {
  esl_lib_pawr_handle_t pawr_handle; ///< PAwR handle
  esl_lib_pawr_config_t pawr_config; ///< PAwR configuration
} esl_lib_command_list_cmd_pawr_configure_t;

/// Initiate PAST
typedef struct {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  esl_lib_pawr_handle_t       pawr_handle;       ///< PAwR handle
} esl_lib_command_list_cmd_initiate_past_t;

/// Write image
typedef struct {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  uint8_t                     img_index;         ///< Image index
  size_t                      img_size;          ///< Image size
  uint8_t                     *img_data_copied;  ///< Image data (copied before)
} esl_lib_command_list_cmd_write_image_t;

/// Get image type
typedef struct {
  esl_lib_connection_handle_t connection_handle; ///< Connection handle
  uint8_t                     img_index;         ///< Image index
} esl_lib_command_list_cmd_get_image_type_t;

/// Write image
typedef struct {
  esl_lib_bool_t enable; ///< Connection handle
} esl_lib_command_list_cmd_scan_enable_t;

/// Command ID
typedef uint32_t esl_lib_cmd_id_t;

///< Command data union type
typedef union {
  esl_lib_command_list_cmd_connect_t             cmd_connect;               ///< Connect
  esl_lib_connection_handle_t                    cmd_close_connection;      ///< Close connection
  esl_lib_connection_handle_t                    cmd_get_tag_info;          ///< Get tag info / gatt values
  esl_lib_command_list_cmd_configure_tag_t       cmd_configure_tag;         ///< Configure tag
  esl_lib_command_list_cmd_write_control_point_t cmd_write_control_point;   ///< Write ESL Control Point
  esl_lib_command_list_cmd_pawr_enable_t         cmd_pawr_enable;           ///< Enable PAwR
  esl_lib_command_list_cmd_pawr_set_data_t       cmd_pawr_set_data;         ///< Set PAwR data
  esl_lib_command_list_cmd_pawr_configure_t      cmd_pawr_config;           ///< Configure PAWR
  esl_lib_pawr_handle_t                          cmd_get_pawr_status;       ///< Get PAwR status
  esl_lib_command_list_cmd_initiate_past_t       cmd_init_past;             ///< Initiate PAST
  esl_lib_command_list_cmd_write_image_t         cmd_write_image;           ///< Write image
  esl_lib_command_list_cmd_get_image_type_t      cmd_get_image_type;        ///< Get image type
  esl_lib_scan_parameters_t                      cmd_scan_config;           ///< Configure scanning
  esl_lib_command_list_cmd_scan_enable_t         cmd_scan_enable;           ///< Enable scan scan
  esl_lib_long_array_t                           cmd_ap_control;            ///< AP control
} esl_lib_command_list_cmd_data_t;

/// Command structure
typedef struct {
  sl_slist_node_t                 node;     ///< List node pointer
  esl_lib_cmd_t                   cmd_code; ///< Command code
  esl_lib_cmd_id_t                id;       ///< ID
  esl_lib_command_list_cmd_data_t data;     ///< Command data field
} esl_lib_command_list_cmd_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Remove command from the specified command list.
 * @param[in] list Pointer to list head pointer.
 * @param[in] cmd  Command pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_command_list_remove(sl_slist_node_t            **list,
                                        esl_lib_command_list_cmd_t *cmd);

/**************************************************************************//**
 * Get command pointer from the specified command list.
 * @param[in] list Pointer to list head pointer.
 *
 * @return Command pointer or NULL if list is empty.
 *****************************************************************************/
esl_lib_command_list_cmd_t *esl_lib_command_list_get(sl_slist_node_t **list);

/**************************************************************************//**
 * Put command to the specified command list.
 * @param[in] list Pointer to list head pointer.
 * @param[in] cmd Command pointer.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_command_list_put(sl_slist_node_t            **list,
                                     esl_lib_command_list_cmd_t *cmd);

/**************************************************************************//**
 * Remove and free all elements in the specified command list.
 *
 * @param[in] list Pointer to list head pointer.
 *****************************************************************************/
void esl_lib_command_list_cleanup(sl_slist_node_t **list);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_COMMAND_LIST_H
