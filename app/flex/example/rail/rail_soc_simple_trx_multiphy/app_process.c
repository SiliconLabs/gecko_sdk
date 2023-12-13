/***************************************************************************//**
 * @file
 * @brief app_tick.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "sl_component_catalog.h"
#include "simple_rail_assistance.h"
#include "sl_rail_util_init.h"
#include "app_process.h"
#include "app_init.h"
#include "sl_simple_button_instances.h"
#include "sl_flex_rail_package_assistant.h"
#include "sl_flex_rail_config.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif

#include "rail_types.h"
#include "cmsis_compiler.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Transmit data length
#define TX_PAYLOAD_LENGTH (16U)

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
/**************************************************************************//**
 * Function to select current state.
 *
 * @param None
 * @returns None
 *****************************************************************************/
static void select_state(void);

/**************************************************************************//**
 * Function to handle the S_IDLE state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_idle(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Function to handle the S_PACKET_RECEIVED state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_packet_received(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Function to handle the S_PACKET_SENT state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_packet_sent(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Function to handle the S_RX_PACKET_ERROR state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_rx_packet_error(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Function to handle the S_TX_PACKET_ERROR state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_tx_packet_error(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Function to handle the S_CALIBRATION_ERROR state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_calibration_error(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * Set RAIL Tx Fifo and start RAIL transmission.
 *
 * @param None
 * @returns None
 *****************************************************************************/
static void send_prepared_packet(void);

/**************************************************************************//**
 * Function to update the rx and tx channels properly.
 *
 * @param None
 * @returns None
 *****************************************************************************/
static void update_radio_channels(void);

/**************************************************************************//**
 * Function to toggle leds safely.
 *
 * @param channel Channel to select which led to toggle
 * @returns None
 *****************************************************************************/
static void toggle_led(uint16_t channel);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// The variable shows the actual state of the state machine
static volatile state_t state = S_IDLE;

/// The variable shows the actual mode of the device
static volatile device_mode_t device_mode = M_ENDPOINT;

/// Which channel is active
static volatile uint16_t active_channel = DEFAULT_CHANNEL;

/// Which channel will be used for rx
static volatile uint8_t rx_channel = DEFAULT_CHANNEL;

/// Which channel will be used for tx
static volatile uint8_t tx_channel = DEFAULT_CHANNEL;

/// Flag that indicates that send is requested
static volatile bool tx_requested = false;

/// Flag that indicates that a radio packet has arrived
static volatile bool packet_received = false;

/// Flag that indicates that an error has occured during reception
static volatile bool rx_error = false;

/// Flag that indicates that a radio packet has sent
static volatile bool packet_sent = false;

/// Flag that indicates that an error has occured during transmission
static volatile bool tx_error = false;

/// Flag that indicates if a calibration error has occured
static volatile bool cal_error = false;

/// Data direction in the relay device
static volatile direction_t direction = D_CH0_TO_CH1;

/// RAIL Rx packet handle
static volatile RAIL_RxPacketHandle_t rx_packet_handle;

/// Contains the last RAIL Rx/Tx error events
static volatile uint64_t current_rail_err = 0;

/// Contains the status of RAIL Calibration
static volatile RAIL_Status_t calibration_status = 0;

/// Receive FIFO
static __ALIGNED(RAIL_FIFO_ALIGNMENT) uint8_t rx_fifo[SL_FLEX_RAIL_RX_FIFO_SIZE];

/// Transmit FIFO
static __ALIGNED(RAIL_FIFO_ALIGNMENT) uint8_t tx_fifo[SL_FLEX_RAIL_TX_FIFO_SIZE];

/// Transmit packet
static uint8_t out_packet[TX_PAYLOAD_LENGTH] = {
  0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
  0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
};

static uint8_t *start_of_packet = 0;

uint16_t packet_size = 0;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Set up the rail TX fifo for later usage
 *****************************************************************************/
void set_up_tx_fifo(RAIL_Handle_t rail_handle)
{
  uint16_t allocated_tx_fifo_size = 0;

  allocated_tx_fifo_size = RAIL_SetTxFifo(rail_handle,
                                          tx_fifo,
                                          0,
                                          SL_FLEX_RAIL_TX_FIFO_SIZE);
  app_assert(allocated_tx_fifo_size == SL_FLEX_RAIL_TX_FIFO_SIZE,
             "RAIL_SetTxFifo() failed to allocate a large enough fifo "
             "(%d bytes instead of %d bytes)\n",
             allocated_tx_fifo_size,
             SL_FLEX_RAIL_TX_FIFO_SIZE);
}

/******************************************************************************
 * Application state machine, called infinitely.
 *****************************************************************************/
void app_process_action(RAIL_Handle_t rail_handle)
{
  select_state();
  switch (state) {
    case S_IDLE:
      handle_state_idle(rail_handle);
      break;

    case S_PACKET_RECEIVED:
      handle_state_packet_received(rail_handle);
      break;

    case S_PACKET_SENT:
      handle_state_packet_sent(rail_handle);
      break;

    case S_RX_PACKET_ERROR:
      handle_state_rx_packet_error(rail_handle);
      break;

    case S_TX_PACKET_ERROR:
      handle_state_tx_packet_error(rail_handle);
      break;

    case S_CALIBRATION_ERROR:
      handle_state_calibration_error(rail_handle);
      break;

    default:
      app_log_error("Unexpected Simple TRX state occurred:%d\n", state);
      break;
  }
}

/******************************************************************************
 * RAIL callback, called if a RAIL event occurs.
 *****************************************************************************/
void sl_rail_util_on_event(RAIL_Handle_t rail_handle, RAIL_Events_t events)
{
  // Handle Rx events
  if (events & RAIL_EVENTS_RX_COMPLETION) {
    if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
      // Keep the packet in the radio buffer,
      // download it later at the state machine
      rx_packet_handle = RAIL_HoldRxPacket(rail_handle);
      packet_received = true;
    } else {
      // Handle Rx error
      current_rail_err = (events & RAIL_EVENTS_RX_COMPLETION);
      tx_error = true;
    }
  }
  // Handle Tx events
  if (events & RAIL_EVENTS_TX_COMPLETION) {
    if (events & RAIL_EVENT_TX_PACKET_SENT) {
      packet_sent = true;
    } else {
      // Handle Tx error
      current_rail_err = (events & RAIL_EVENTS_TX_COMPLETION);
      rx_error = true;
    }
  }
  // Perform all calibrations when needed
  if (events & RAIL_EVENT_CAL_NEEDED) {
    calibration_status = RAIL_Calibrate(rail_handle, NULL, RAIL_CAL_ALL_PENDING);
    if (calibration_status != RAIL_STATUS_NO_ERROR) {
      current_rail_err = (events & RAIL_EVENT_CAL_NEEDED);
      cal_error = true;
    }
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Button callback, called if any button is pressed or released.
 *****************************************************************************/
void sl_button_on_change(const sl_button_t *handle)
{
  if (device_mode == M_RELAY) {
    // Relay device does nothing on button events
    return;
  }
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    tx_requested = true;
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * API to set the next state of the state machine.
 *****************************************************************************/
void set_next_state(const state_t next_state)
{
  state = next_state;
}

/******************************************************************************
 * API to set the mode of the device.
 *****************************************************************************/
void set_device_mode(const device_mode_t new_mode)
{
  device_mode = new_mode;
  // Updating radio channels according to the new device mode
  update_radio_channels();
}

/******************************************************************************
 * API to get the current mode of the device.
 *****************************************************************************/
device_mode_t get_device_mode(void)
{
  return device_mode;
}

/******************************************************************************
 * API to set the active channel.
 *****************************************************************************/
void set_active_channel(const uint16_t new_channel)
{
  RAIL_Handle_t rail_handle
    = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);

  if (RAIL_IsValidChannel(rail_handle, new_channel) != RAIL_STATUS_NO_ERROR) {
    app_log_warning("Channel is not valid\n");
    return;
  }
  active_channel = new_channel;
  // Updating radio channels according to the new active channel
  update_radio_channels();
  app_log_info("Active channel is set to %d\n", active_channel);
}

/******************************************************************************
 * API to get the currently active channel.
 *****************************************************************************/
uint16_t get_active_channel(void)
{
  return active_channel;
}

/******************************************************************************
 * API to get the channel on which the device receives data.
 *****************************************************************************/
uint16_t get_rx_channel(void)
{
  return rx_channel;
}

/******************************************************************************
 * API to get the channel on which the device transmits data.
 *****************************************************************************/
uint16_t get_tx_channel(void)
{
  return tx_channel;
}

/******************************************************************************
 * API to request a radio transmission.
 *****************************************************************************/
void request_tx(void)
{
  tx_requested = true;
}

/******************************************************************************
 * API to set the direction of the relay device.
 *****************************************************************************/
void set_direction(const direction_t new_direction)
{
  uint16_t src = 0;
  uint16_t dest = 0;

  direction = new_direction;
  // Updating radio channels according to the new direction
  update_radio_channels();
  src = rx_channel;
  dest = tx_channel;
  app_log_info("Direction set to ch%d -> ch%d\n", src, dest);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Function to select current state.
 *****************************************************************************/
static void select_state(void)
{
  if (packet_received) {
    packet_received = false;
    set_next_state(S_PACKET_RECEIVED);
  } else if (packet_sent) {
    packet_sent = false;
    set_next_state(S_PACKET_SENT);
  } else if (rx_error) {
    rx_error = false;
    set_next_state(S_RX_PACKET_ERROR);
  } else if (tx_error) {
    tx_error = false;
    set_next_state(S_TX_PACKET_ERROR);
  } else if (cal_error) {
    cal_error = false;
    set_next_state(S_CALIBRATION_ERROR);
  }
}
/******************************************************************************
 * Function to handle the S_IDLE state.
 *****************************************************************************/
static void handle_state_idle(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;

  if (tx_requested) {
    send_prepared_packet();
    tx_requested = false;
#if defined(SL_CATALOG_KERNEL_PRESENT)
    app_task_notify();
#endif
  }
}

/******************************************************************************
 * Function to handle the S_PACKET_RECEIVED state.
 *****************************************************************************/
static void handle_state_packet_received(RAIL_Handle_t rail_handle)
{
  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;
  RAIL_RxPacketInfo_t packet_info;

  if (rx_packet_handle == RAIL_RX_PACKET_HANDLE_INVALID) {
    app_log_error("RAIL_HoldRxPacket(): RAIL_RX_PACKET_HANDLE_INVALID\n");
  }
  rx_packet_handle = RAIL_GetRxPacketInfo(rail_handle,
                                          RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE,
                                          &packet_info);
  while (rx_packet_handle != RAIL_RX_PACKET_HANDLE_INVALID) {
    // Saving the received packet from the radio buffer to the local buffer

    packet_size = unpack_packet(rx_fifo, &packet_info, &start_of_packet);
    // Freeing up the radio buffer
    rail_status = RAIL_ReleaseRxPacket(rail_handle, rx_packet_handle);
    if (rail_status != RAIL_STATUS_NO_ERROR) {
      app_log_warning("RAIL_ReleaseRxPacket() error, status: %d\n", rail_status);
    }
    printf_rx_packet(start_of_packet, packet_size);
    app_log_info("On channel %d\n", rx_channel);
    if (device_mode == M_RELAY) {
      // Relay devices have to forward the received packet
      tx_requested = true;
    }
    toggle_led(rx_channel);
    rx_packet_handle = RAIL_GetRxPacketInfo(rail_handle,
                                            RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE,
                                            &packet_info);
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
  set_next_state(S_IDLE);
}

/******************************************************************************
 * Function to handle the S_PACKET_SENT state.
 *****************************************************************************/
static void handle_state_packet_sent(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  app_log_info("Packet has been sent on channel %d\n", tx_channel);
  if (device_mode == M_RELAY) {
    status = RAIL_StartRx(rail_handle, rx_channel, NULL);
    if (status != RAIL_STATUS_NO_ERROR) {
      app_log_warning("RAIL_StartRx() error, status: %d\n", status);
    }
  }
  toggle_led(tx_channel);
  set_next_state(S_IDLE);
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Function to handle the S_RX_PACKET_ERROR state.
 *****************************************************************************/
static void handle_state_rx_packet_error(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;

  app_log_error("Radio RX Error occurred\nEvents: %lld\n", current_rail_err);
  set_next_state(S_IDLE);
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Function to handle the S_TX_PACKET_ERROR state.
 *****************************************************************************/
static void handle_state_tx_packet_error(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;

  app_log_error("Radio TX Error occurred\nEvents: %lld\n", current_rail_err);
  set_next_state(S_IDLE);
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Function to handle the S_CALIBRATION_ERROR state.
 *****************************************************************************/
static void handle_state_calibration_error(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;
  uint64_t error = current_rail_err;
  RAIL_Status_t status = calibration_status;

  app_log_error("Radio Calibration Error occurred\n");
  app_log_error("Events: %lld\nRAIL_Calibrate() result:%d\n", error, status);
  set_next_state(S_IDLE);
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Set RAIL Tx Fifo and start RAIL transmission
 *****************************************************************************/
static void send_prepared_packet(void)
{
  RAIL_Handle_t rail_handle
    = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);

  RAIL_Idle(rail_handle, RAIL_IDLE, true);
  if (device_mode != M_ENDPOINT) {
    memcpy(out_packet, start_of_packet, packet_size);
  }
  prepare_package(rail_handle, out_packet, sizeof(out_packet));
  RAIL_StartTx(rail_handle, tx_channel, RAIL_TX_OPTIONS_DEFAULT, NULL);
}

/******************************************************************************
 * Function to update the rx and tx channels properly.
 *****************************************************************************/
static void update_radio_channels(void)
{
  RAIL_Handle_t rail_handle
    = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;

  if (device_mode == M_ENDPOINT) {
    rx_channel = active_channel;
    tx_channel = active_channel;
  } else {
    if (direction == D_CH0_TO_CH1) {
      rx_channel = 0;
      tx_channel = 1;
    } else {
      rx_channel = 1;
      tx_channel = 0;
    }
  }
  // Starting reception on the updated rx channel
  status = RAIL_StartRx(rail_handle, rx_channel, NULL);
  if (status != RAIL_STATUS_NO_ERROR) {
    app_log_warning("RAIL_StartRx() error, status: %d\n", status);
  }
}

/******************************************************************************
 * Function to toggle leds safely.
 *****************************************************************************/
static void toggle_led(uint16_t channel)
{
  if (channel) {
    toggle_send_led();
  } else {
    toggle_receive_led();
  }
}
