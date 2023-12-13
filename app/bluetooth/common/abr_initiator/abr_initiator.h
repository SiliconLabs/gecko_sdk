/***************************************************************************//**
 * @file
 * @brief ABR initiator application.
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

#ifndef ABR_INITIATOR_H
#define ABR_INITIATOR_H

#include "sl_rtl_clib_api.h"
#include "abr_initiator_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 ********************************  TYPEDEFS  ***********************************
 ******************************************************************************/

/// Address length
#define ADR_LEN 6

/**************************************************************************//**
 * ABR initiator set initial state.
 * @param[in] state abr_initiator_config_t
 *****************************************************************************/
void abr_initiator_set_initial_state(abr_initiator_config_t *state);

/**************************************************************************//**
 * ABR initiator init function that sets the first discovery and
 * initiator config and register the selected callback function pointer as a
 * callback for the distance measurement.
 * @param[in] result_cb abr_result_cb_t
 * @param[in] initiator_config pointer to the initiator config struct
 *****************************************************************************/
void abr_initiator_init(abr_result_cb_t result_cb,
                        abr_initiator_config_t *initiator_config);

/**************************************************************************//**
 * ABR initiator deinit
 *****************************************************************************/
void abr_initiator_deinit(void);

/**************************************************************************//**
 * ABR initiator public function that configures and enables the radio
 * and starts scanning.
 *****************************************************************************/
void abr_initiator_enable(void);

/**************************************************************************//**
 * Bluetooth stack event handler.
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void bt_on_event_initiator(sl_bt_msg_t *evt);

/**************************************************************************//**
 * Periodically called step function.
 *****************************************************************************/
void abr_initiator_step(void);

/**************************************************************************//**
 * Initialize RTL library.
 * @param[in] handle RTL library item handle.
 * @param[in] abr_mode Specifying ABR method.
 *****************************************************************************/
void abr_rtl_library_init(sl_rtl_abr_libitem *handle, uint8_t abr_mode);

/**************************************************************************//**
 * Process a channel sounding result event from the initiator.
 * @param[in] evt_cs_result sl.bt.cs.result package.
 * @return true if it is necessary to restart the cs procedure.
 *****************************************************************************/
bool abr_process_initiator_cs_result(sl_bt_evt_cs_result_t *evt_cs_result);

/**************************************************************************//**
 * Process a channel sounding result event from the reflector.
 * @param[in] evt_cs_result sl.bt.cs.result package.
 * @param[in] initiator_connection Initiator connection handle from BLE stack.
 * @return true if it is necessary to restart the cs procedure.
 *****************************************************************************/
bool abr_process_reflector_cs_result(sl_bt_evt_cs_result_t *evt_cs_result, uint8_t initiator_connection);

/**************************************************************************//**
 * Get Board Name from target.
 * Antenna switching should only work on BRD4406A.
 * @return true if the board the target is running on is BRD4406A.
 *****************************************************************************/
bool abr_initiator_decide_antenna_switching();

/**************************************************************************//**
 * Get antenna offset value from target.
 *****************************************************************************/
void abr_set_antenna_offset();

#ifdef __cplusplus
};
#endif

#endif // ABR_INITIATOR_H
