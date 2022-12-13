/***************************************************************************//**
 * @file
 * @brief OTS Server - internal interface for RTOS adaptation
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SLI_BT_OTS_SERVER_ADAPTATION_H
#define SLI_BT_OTS_SERVER_ADAPTATION_H

#include <stdbool.h>
#include "sl_bluetooth_connection_config.h"
#include "sli_bt_ots_datatypes.h"
#include "sl_bt_ots_server.h"
#include "sl_bt_ots_server_instances.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SL_BT_OTS_SERVER_INDICATION_DATA_SIZE_MAX \
  (SL_BT_OTS_SERVER_CONFIG_INDICATION_SIZE_MAX    \
   - SL_BT_OTS_INDICATION_OVERHEAD)

// -----------------------------------------------------------------------------
// Type definitions

/// Type for indication queue
typedef struct {
  uint8_t  connection;
  uint16_t gattdb_handle;
  uint8_t  data_length;
  uint8_t  data[SL_BT_OTS_SERVER_INDICATION_DATA_SIZE_MAX];
} sli_bt_ots_indication_queue_item_t;

/**************************************************************************//**
 * Internal OTS Server system init
 *****************************************************************************/
void sli_bt_ots_server_adaptation_init(void);

/**************************************************************************//**
 * Check if the queue for a connection is empty
 * @param[in] index Storage index.
 * @retval true if the queue for the connection is empty
 *****************************************************************************/
bool sli_bt_ots_server_adaptation_indication_queue_is_empty(uint8_t index);

/**************************************************************************//**
 * Add an element to the queue for the given connection
 * @param[in] index Storage index.
 * @param[in] item  The indication item to add.
 * @return status of the operation
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_indication_queue_add(uint8_t                            index,
                                                              sli_bt_ots_indication_queue_item_t *item);

/**************************************************************************//**
 * Copy an element from the queue for the given connection
 * @param[in]  connection Storage index.
 * @param[out] item       The indication item.
 * @return status of the operation
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_indication_queue_peek(uint8_t                            index,
                                                               sli_bt_ots_indication_queue_item_t *item);

/**************************************************************************//**
 * Remove element from the queue for the given connection
 * @param[in] index Storage index.
 * @return status of the operation
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_indication_queue_remove(uint8_t index);

/**************************************************************************//**
 * Proceed with the indication queue with the next indication for the connection
 * @return status of the operation
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_indication_queue_proceed(void);

/**************************************************************************//**
 * Remove all element from the queue for the given connection
 * @param[in] index Storage index.
 * @return status of the operation
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_indication_queue_clear(uint8_t index);

/**************************************************************************//**
 * Acquire Mutex
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_acquire(void);

/**************************************************************************//**
 * Release Mutex
 *****************************************************************************/
sl_status_t sli_bt_ots_server_adaptation_release(void);

#ifdef __cplusplus
};
#endif

#endif // SLI_BT_OTS_SERVER_ADAPTATION_H
