/***************************************************************************//**
 * @file
 * @brief app_process.h
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef APP_PROCESS_H
#define APP_PROCESS_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "rail.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// States of rail_soc_simple_trx_multiphy
typedef enum {
  S_IDLE,
  S_PACKET_RECEIVED,
  S_PACKET_SENT,
  S_RX_PACKET_ERROR,
  S_TX_PACKET_ERROR,
  S_CALIBRATION_ERROR
} state_t;

/// Device modes of rail_soc_simple_trx_multiphy
typedef enum {
  M_ENDPOINT,
  M_RELAY
} device_mode_t;

/// Directions of th relay devices
typedef enum {
  D_CH0_TO_CH1,
  D_CH1_TO_CH0
} direction_t;

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * API to set up the rail TX fifo for later usage.
 *
 * @param rail_handle RAIL handle update
 * @returns None
 *****************************************************************************/
void set_up_tx_fifo(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * The function is used for Application logic.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *
 * The function is used for Application logic.
 * It is called infinitely.
 *****************************************************************************/
void app_process_action(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * API to set the next state of the state machine.
 *
 * @param next_state State to set
 * @returns None
 *****************************************************************************/
void set_next_state(const state_t next_state);

/**************************************************************************//**
 * API to set the mode of the device.
 *
 * @param new_mode Mode to set
 * @returns None
 *****************************************************************************/
void set_device_mode(const device_mode_t new_mode);

/**************************************************************************//**
 * API to get the current mode of the device.
 *
 * @param None
 * @returns Current mode of the device
 *****************************************************************************/
device_mode_t get_device_mode(void);

/**************************************************************************//**
 * API to set the active channel.
 *
 * @param new_channel Channel to set
 * @returns None
 *
 * Only effective in M_ENDPOINT mode.
 *****************************************************************************/
void set_active_channel(const uint16_t new_channel);

/**************************************************************************//**
 * API to get the currently active channel.
 *
 * @param None
 * @returns Active channel
 *
 * Active channel is only interpreted in M_ENDPOINT mode.
 *****************************************************************************/
uint16_t get_active_channel(void);

/**************************************************************************//**
 * API to get the channel on which the device receives data.
 *
 * @param None
 * @returns Channel on which the device receives data
 *****************************************************************************/
uint16_t get_rx_channel(void);

/**************************************************************************//**
 * API to get the channel on which the device transmits data.
 *
 * @param None
 * @returns Channel on which the device receives data
 *****************************************************************************/
uint16_t get_tx_channel(void);

/**************************************************************************//**
 * API to request a radio transmission.
 *
 * @param None
 * @returns None
 *****************************************************************************/
void request_tx(void);

/**************************************************************************//**
 * API to set the direction of the relay device.
 *
 * @param new_direction Direction to set
 * @returns None
 *
 * Only effective in M_RELAY mode.
 *****************************************************************************/
void set_direction(const direction_t new_direction);

#endif  // APP_PROCESS_H
