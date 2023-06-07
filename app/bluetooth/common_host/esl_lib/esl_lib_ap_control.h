/***************************************************************************//**
 * @file
 * @brief ESL Host Library - Access Point Control header
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

#ifndef ESL_LIB_AP_CONTROL_H
#define ESL_LIB_AP_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "sl_status.h"
#include "esl_lib.h"
#include "sl_bt_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Definitions

// Handle AP Control Connection, disconnection a subscribe status
typedef enum {
  ESL_LIB_AP_CONTROL_EVT_STATUS         = 1,
  ESL_LIB_AP_CONTROL_EVT_REQUEST        = 2,
  ESL_LIB_AP_CONTROL_EVT_IMAGE_TRANSFER = 3
} esl_lib_ap_control_evt_type_t;

// AP Control Data Type
typedef struct {
  uint8_t evt_type;   // Contains event type from esl_lib_ap_control_evt_type_t
  uint8_t payload[];  // Payload/data of the event
} esl_lib_ap_control_evt_data_t;

// AP Control state
typedef enum {
  ESL_LIB_AP_CONTROL_STATE_DISCONNECTED = 0x00,
  ESL_LIB_AP_CONTROL_STATE_CONNECTED    = 0x01,
  ESL_LIB_AP_CONTROL_STATE_SUBSCRIBED   = 0x02
} esl_lib_ap_control_state_t;

// -----------------------------------------------------------------------------
// Public functions

/**************************************************************************//**
 * Initialize GATT database
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_ap_control_init(void);

/**************************************************************************//**
 * Cleanup AP control
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_ap_control_cleanup(void);

/**************************************************************************//**
 * Enable or disable advertising.
 *
 * @param[in] enable Enable (true) or disable (false) advertising
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_ap_control_adv_enable(bool enable);

/**************************************************************************//**
 * Send respose to the remote device.
 *
 * @param[in] data Pointer to data array.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_ap_control_response(esl_lib_long_array_t *data);

/**************************************************************************//**
 * Send respose for Image Tranfer to the remote device.
 *
 * @param[in] data Pointer to data array.
 *
 * @return Status code.
 *****************************************************************************/
sl_status_t esl_lib_ap_control_image_transfer_response(esl_lib_long_array_t *data);

/**************************************************************************//**
 * Bluetooth event handler.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void esl_lib_ap_control_on_bt_event(sl_bt_msg_t *evt);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_AP_CONTROL_H
