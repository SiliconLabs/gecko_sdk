/***************************************************************************//**
 * @file
 * @brief
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

#ifndef SL_BTMESH_PROVISIONEE_H
#define SL_BTMESH_PROVISIONEE_H

#include "sl_btmesh_api.h"
#include "sl_btmesh_provisionee_config.h"

/***************************************************************************//**
 * @defgroup provisionee
 * @brief
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup provisionee
 * @{
 ******************************************************************************/

#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_PUSH
/***************************************************************************//**
 * This function is called when input oob authentication is needed with push action.
 * Respond to it by calling the sl_btmesh_provisionee_input_oob_num() function.
 *
 * @param[in] input_size Input OOB size
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs that it was called.
 ******************************************************************************/
void sl_btmesh_on_input_oob_request_push(uint8_t input_size);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_TWIST
/***************************************************************************//**
 * This function is called when input oob authentication is needed with twist action.
 * Respond to it by calling the sl_btmesh_provisionee_input_oob_num() function.
 *
 * @param[in] input_size Input OOB size
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs that it was called.
 ******************************************************************************/
void sl_btmesh_on_input_oob_request_twist(uint8_t input_size);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_NUMERIC
/***************************************************************************//**
 * This function is called when input oob authentication is needed with
 * numeric input action.
 * Respond to it by calling the sl_btmesh_provisionee_input_oob_num() function.
 *
 * @param[in] input_size Input OOB size
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs that it was called.
 ******************************************************************************/
void sl_btmesh_on_input_oob_request_numeric(uint8_t input_size);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_ALPHA
/***************************************************************************//**
 * This function is called when input oob authentication is needed with
 * alphanumeric input action.
 * Respond to it by calling the sl_btmesh_provisionee_input_oob_str() function.
 *
 * @param[in] input_size Input OOB size
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs that it was called.
 ******************************************************************************/
void sl_btmesh_on_input_oob_request_alphanumeric(uint8_t input_size);

/***************************************************************************//**
 * This function must be called when the alphanumeric input action completed.
 *
 * @param[in] oob_str the string containing the alphanumeric authentication value
 * @return sl_status_t
 ******************************************************************************/
sl_status_t sl_btmesh_provisionee_input_oob_str(char* oob_str);
#endif

#if SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_PUSH   \
  || SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_TWIST \
  || SL_BTMESH_PROVISIONEE_AUTH_INPUT_OOB_NUMERIC
/***************************************************************************//**
 * This function must be called when a numeric input action completed.
 *
 * @param[in] oob_num the number containing the authentication value
 * @return sl_status_t
 ******************************************************************************/
sl_status_t sl_btmesh_provisionee_input_oob_num(uint32_t oob_num);
#endif

#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BLINK
/***************************************************************************//**
 * This function is called when output oob authentication is needed with
 * blink output action.
 *
 * @param[in] oob_num number to output by blinking
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs the oob_num parameter.
 ******************************************************************************/
void sl_btmesh_on_output_oob_blink(uint32_t oob_num);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_BEEP
/***************************************************************************//**
 * This function is called when output oob authentication is needed with
 * beep output action.
 *
 * @param[in] oob_num number to output by beeping
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs the oob_num parameter.
 ******************************************************************************/
void sl_btmesh_on_output_oob_beep(uint32_t oob_num);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_VIBRATE
/***************************************************************************//**
 * This function is called when output oob authentication is needed with
 * vibrate output action.
 *
 * @param[in] oob_num number to output by vibrating
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs the oob_num parameter.
 ******************************************************************************/
void sl_btmesh_on_output_oob_vibrate(uint32_t oob_num);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_NUMERIC
/***************************************************************************//**
 * This function is called when output oob authentication is needed with
 * numeric output action.
 *
 * @param[in] oob_num number to display
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs the oob_num parameter.
 ******************************************************************************/
void sl_btmesh_on_output_oob_numeric(uint32_t oob_num);
#endif
#if SL_BTMESH_PROVISIONEE_AUTH_OUTPUT_OOB_ALPHA
/***************************************************************************//**
 * This function is called when output oob authentication is needed with
 * alphanumeric output action.
 *
 * @param[in] oob_str string to display
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs the oob_num parameter.
 ******************************************************************************/
void sl_btmesh_on_output_oob_alphanumeric(char* oob_str);
#endif

#if SL_BTMESH_PROVISIONEE_AUTH_STATIC_OOB
/***************************************************************************//**
 * This function is called when static oob authentication is needed.
 * Respond to it by calling the sl_btmesh_node_send_static_oob_request_response()
 * function.
 *
 * @param[in] oob_size size of the required AuthValue buffer
 *
 * This is a callback which should be implemented in the application.
 * @note If no implementation is provided in the application then a default weak
 *       implementation is provided which logs that it was called.
 ******************************************************************************/
void sl_btmesh_on_static_oob_request(size_t oob_size);
#endif

/***************************************************************************//**
 * This function is called after the provisionee called the sl_btmesh_node_init()
 * or the sl_btmesh_node_init_oob() function.
 *
 * @param[in] result return value of the function call
 *
 * This is a callback which can be implemented in the application.
 * @note If no implementation is provided in the application,
 *       then the default weak implementation will be an empty function.
 ******************************************************************************/
void sl_btmesh_provisionee_on_init(sl_status_t result);

/***************************************************************************//**
 * Handle BT Mesh events for the provisionee.
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_btmesh_provisionee_on_event(sl_btmesh_msg_t *evt);

/***************************************************************************//**
 * Handle BLE events for the provisionee.
 *
 * This function is called automatically by Universal Configurator after
 * enabling the component.
 *
 * @param[in] evt  Pointer to incoming event.
 ******************************************************************************/
void sl_bt_provisionee_on_event(sl_bt_msg_t* evt);

/** @} (end addtogroup provisionee) */

#endif /* SL_BTMESH_PROVISIONEE_H */
