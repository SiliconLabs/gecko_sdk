/***************************************************************************//**
 * @file
 * @brief app_tick.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdint.h>
#include "sl_component_catalog.h"
#include "app_assert.h"
#include "app_log.h"
#include "rail.h"
#include "app_process.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"
#include "rail_config.h"
#include "sl_flex_packet_asm.h"
#include "rail_types.h"
#include "cmsis_compiler.h"
#include "sl_flex_mode_switch.h"
#include "sl_flex_rail_config.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Transmit data length
#define TX_PAYLOAD_LENGTH (16U)
/// Indicator of a mode switch end packet
#define MS_END_PACKET_INDICATOR (0xF0U)

/// State machine
typedef enum {
  S_PACKET_RECEIVED,
  S_PACKET_SENT,
  S_RX_PACKET_ERROR,
  S_TX_PACKET_ERROR,
  S_CALIBRATION_ERROR,
  S_IDLE
} state_t;

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
 * Function to handle the S_IDLE state.
 *
 * @param rail_handle A RAIL instance handle
 * @returns None
 *****************************************************************************/
static void handle_state_idle(RAIL_Handle_t rail_handle);

/**************************************************************************//**
 * The function printfs the received rx message.
 *
 * @param rx_buffer Msg buffer
 * @param length How many bytes should be printed out
 * @returns None
 *****************************************************************************/
static void printf_rx_packet(const uint8_t * const rx_buffer, uint16_t length);

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// Flag that indicates that send is requested
volatile bool tx_requested = false;
/// Flag, indicating received packet is forwarded to CLI or not
volatile bool rx_requested = true;

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
/// The variable shows the actual state of the state machine
static volatile state_t state = S_IDLE;

/// Contains the last RAIL Rx/Tx error events
static volatile uint64_t error_code = 0;

/// Contains the status of RAIL Calibration
static volatile RAIL_Status_t calibration_status = 0;

/// Receive and Send FIFO
static __ALIGNED(RAIL_FIFO_ALIGNMENT) uint8_t rx_fifo[SL_FLEX_RAIL_RX_FIFO_SIZE];

static __ALIGNED(RAIL_FIFO_ALIGNMENT) uint8_t tx_fifo[SL_FLEX_RAIL_TX_FIFO_SIZE];

/// Transmit packet
static uint8_t out_packet[TX_PAYLOAD_LENGTH] = {
  0x0F, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
  0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
};
/// Mode switch end packet
static uint8_t ms_end_packet[TX_PAYLOAD_LENGTH] = {
  MS_END_PACKET_INDICATOR, 0x16, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66,
  0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE
};

/// Flags to update state machine from interrupt
static volatile bool packet_recieved = false;
static volatile bool packet_sent = false;
static volatile bool rx_error = false;
static volatile bool tx_error = false;
static volatile bool cal_error = false;

/// Flag, indicating mode switch request
volatile bool ms_requested = false;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Application state machine, called infinitely
 *****************************************************************************/
void app_process_action(RAIL_Handle_t rail_handle)
{
  select_state();
  switch (state) {
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

    case S_IDLE:
      handle_state_idle(rail_handle);
      break;

    case S_CALIBRATION_ERROR:
      handle_state_calibration_error(rail_handle);
      break;

    default:
      app_log_error("Unexpected state occurred: %d\n", state);
      break;
  }
}

/******************************************************************************
 * RAIL callback, called if a RAIL event occurs.
 *****************************************************************************/
void sl_rail_util_on_event(RAIL_Handle_t rail_handle, RAIL_Events_t events)
{
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  mode_switch_state_t ms_state = get_ms_state();

  error_code = events;

  // Handle Rx events
  if (events & RAIL_EVENTS_RX_COMPLETION) {
    if (events & RAIL_EVENT_RX_PACKET_RECEIVED) {
      // Keep the packet in the radio buffer,
      // download it later at the state machine
      RAIL_HoldRxPacket(rail_handle);
      packet_recieved = true;
    } else {
      // Handle Rx error
      rx_error = true;
    }
  }
  // Handle Tx events
  if (events & RAIL_EVENTS_TX_COMPLETION) {
    if (events & RAIL_EVENT_TX_PACKET_SENT) {
      packet_sent = true;
    } else {
      // Handle Tx error
      tx_error = true;
    }
  }

  if (events & RAIL_EVENT_IEEE802154_MODESWITCH_START) {
    if (ms_state == MS_IDLE) {
      status = switch_to_ms_channel(rail_handle);
      if (status == RAIL_STATUS_NO_ERROR) {
        app_log_info("RAIL_EVENT_IEEE802154_MODESWITCH_START happened\n");
        set_ms_state(MS_ON_NEW_PHY);
      }
    } else {
      set_ms_state(MS_IDLE);
    }
  }

  if (events & RAIL_EVENT_IEEE802154_MODESWITCH_END) {
    status = return_to_base_channel();
    if (status == RAIL_STATUS_NO_ERROR) {
      app_log_info("RAIL_EVENT_IEEE802154_MODESWITCH_END happened\n");
    }
  }

  // Perform all calibrations when needed
  if (events & RAIL_EVENT_CAL_NEEDED) {
    calibration_status = RAIL_Calibrate(rail_handle, NULL, RAIL_CAL_ALL_PENDING);
    if (calibration_status != RAIL_STATUS_NO_ERROR) {
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
  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
    if (handle == &sl_button_btn0) {
      tx_requested = true;
    } else if (handle == &sl_button_btn1) {
      request_mode_switch();
    }
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

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
             "RAIL_SetTxFifo() failed to allocate a large enough fifo"
             "(%d bytes instead of %d bytes)\n",
             allocated_tx_fifo_size,
             SL_FLEX_RAIL_TX_FIFO_SIZE);
}

/******************************************************************************
 * API to request a radio transmission.
 *****************************************************************************/
void request_tx(void)
{
  tx_requested = true;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Function to select current state.
 *****************************************************************************/
static void select_state(void)
{
  if (packet_recieved) {
    packet_recieved = false;
    state = S_PACKET_RECEIVED;
  } else if (packet_sent) {
    packet_sent = false;
    state = S_PACKET_SENT;
  } else if (rx_error) {
    rx_error = false;
    state = S_RX_PACKET_ERROR;
  } else if (tx_error) {
    tx_error = false;
    state = S_TX_PACKET_ERROR;
  } else if (cal_error) {
    cal_error = false;
    state = S_CALIBRATION_ERROR;
  }
}

/******************************************************************************
 * Function to handle the S_PACKET_RECEIVED state.
 *****************************************************************************/
static void handle_state_packet_received(RAIL_Handle_t rail_handle)
{
  // Packet received:
  //  - Check whether RAIL_HoldRxPacket() was successful, i.e. packet handle is valid
  //  - Copy it to the application FIFO
  //  - Free up the radio FIFO
  //  - Return to app IDLE state (RAIL will automatically switch back to Rx radio state)
  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;
  RAIL_RxPacketHandle_t rx_packet_handle;
  RAIL_RxPacketInfo_t packet_info;
  uint8_t *start_of_packet = 0U;
  uint16_t packet_size = 0U;

  rx_packet_handle = RAIL_GetRxPacketInfo(rail_handle,
                                          RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE,
                                          &packet_info);
  while (rx_packet_handle != RAIL_RX_PACKET_HANDLE_INVALID) {
    start_of_packet = 0;
    packet_size = unpack_packet(rx_fifo,
                                &packet_info,
                                &start_of_packet,
                                get_phy_modulation_from_channel(get_channel()));
    rail_status = RAIL_ReleaseRxPacket(rail_handle, rx_packet_handle);
    if (rail_status != RAIL_STATUS_NO_ERROR) {
      app_log_warning("ERROR RAIL_ReleaseRxPacket() result: %d", rail_status);
    }
    if (rx_requested) {
      printf_rx_packet(start_of_packet, packet_size);
    }
    if (start_of_packet[0] == MS_END_PACKET_INDICATOR) {
      rail_status = return_to_base_channel();
      if (rail_status == RAIL_STATUS_NO_ERROR) {
        app_log_info("Mode switch end, returned to the base channel\n");
      } else {
        app_log_warning("Error during returning to the base channel: %d\n",
                        (uint8_t)rail_status);
      }
    }
    sl_led_toggle(&sl_led_led0);
    rx_packet_handle = RAIL_GetRxPacketInfo(rail_handle,
                                            RAIL_RX_PACKET_HANDLE_OLDEST_COMPLETE,
                                            &packet_info);
  }
  state = S_IDLE;
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Function to handle the S_PACKET_SENT state.
 *****************************************************************************/
static void handle_state_packet_sent(RAIL_Handle_t rail_handle)
{
  (void) rail_handle;
  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;
  mode_switch_state_t ms_state = get_ms_state();
  uint16_t ms_new_channel = get_ms_new_channel();

  app_log_info("Packet has been sent\n");
  if (ms_state == MS_SENDING_MS_START_PACKET) {
    set_ms_state(MS_ON_NEW_PHY);
    set_channel(ms_new_channel);
    app_log_info("Mode switch completed\n");
  }

  if (ms_state == MS_SENDING_MS_END_PACKET) {
    rail_status = return_to_base_channel();
    update_rail_pa_settings(rail_handle, get_channel());
    if (rail_status != RAIL_STATUS_NO_ERROR) {
      app_log_warning("ERROR return_to_base_channel: %d\n",
                      rail_status);
    }
  }
  if (get_print_packet_details()) {
    if (get_phy_modulation_from_channel(get_channel()) == M_OFDM) {
      app_log_info("With rate %d and scramble: %d\n",
                   get_ofdm_rate(),
                   get_ofdm_scrambler());
    } else {
      app_log_info("With fcs type %d and whitening %d:\n",
                   get_fsk_fcs_type(),
                   get_fsk_whitening());
    }
  }
#if defined(SL_CATALOG_LED1_PRESENT)
  sl_led_toggle(&sl_led_led1);
#else
  sl_led_toggle(&sl_led_led0);
#endif
  state = S_IDLE;
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

  app_log_error("Radio RX Error occurred\nEvents: 0x%llX\n", error_code);
  state = S_IDLE;
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

  app_log_error("Radio TX Error occurred\nEvents: 0x%llX\n", error_code);
  state = S_IDLE;
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
  RAIL_Status_t calibration_status_buff = RAIL_STATUS_NO_ERROR;

  calibration_status_buff = calibration_status;
  app_log_error("Radio Calibration Error occurred\nEvents: 0x%llX\n"
                "RAIL_Calibrate() result: %d\n",
                error_code,
                calibration_status_buff);
  state = S_IDLE;
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * Function to handle the S_IDLE state.
 *****************************************************************************/
static void handle_state_idle(RAIL_Handle_t rail_handle)
{
  RAIL_Status_t rail_status = RAIL_STATUS_NO_ERROR;
  sl_status_t status = SL_STATUS_OK;
  mode_switch_state_t ms_state = get_ms_state();

  if (ms_state == MS_RETURN_TO_BASE_PHY) {
    tx_requested = true;
  }

  if (ms_state == MS_REQUESTED) {
    status = trig_mode_switch_tx(rail_handle);
    if (rail_status != SL_STATUS_OK) {
      app_log_warning("ERROR RAIL_IEEE802154_ComputeChannelFromPhyModeId: %d\n",
                      (uint16_t)status);
    }
    // ms_state is changed on success
    ms_state = get_ms_state();
  }

  if (ms_state == MS_INITED) {
    tx_requested = true;
  }

  if (tx_requested) {
    if (ms_state == MS_RETURN_TO_BASE_PHY) {
      prepare_package(rail_handle,
                      ms_end_packet,
                      sizeof(ms_end_packet),
                      get_phy_modulation_from_channel(get_channel()));
      set_ms_state(MS_SENDING_MS_END_PACKET);
    } else {
      prepare_package(rail_handle,
                      out_packet,
                      sizeof(out_packet),
                      get_phy_modulation_from_channel(get_channel()));
    }
    rail_status = RAIL_StartTx(rail_handle,
                               get_channel(),
                               RAIL_TX_OPTIONS_DEFAULT,
                               NULL);
    if (rail_status == RAIL_STATUS_NO_ERROR) {
      app_log_info("RAIL_StartTx() ok\n");
      ms_state = get_ms_state();
      if (ms_state == MS_INITED) {
        set_ms_state(MS_SENDING_MS_START_PACKET);
        if (!packet_sent) {
          uint8_t i = 0;
          for (i = 0; i < 20; i++) {
            sl_power_manager_sleep();
            if (packet_sent) {
              break;
            }
          }
          if (i > 15) {
            app_log_info("Timeout happened\n");
          }
        }
        prepare_package(rail_handle,
                        out_packet,
                        sizeof(out_packet),
                        get_phy_modulation_from_channel(get_ms_new_channel()));
        update_rail_pa_settings(rail_handle, get_ms_new_channel());
        rail_status = RAIL_StartTx(rail_handle,
                                   get_ms_new_channel(),
                                   RAIL_TX_OPTIONS_DEFAULT,
                                   NULL);
        if (rail_status == RAIL_STATUS_NO_ERROR) {
          app_log_info("RAIL_StartTx() ok\n");
        } else {
          app_log_warning("ERROR RAIL_StartTx() result: %d", rail_status);
        }
      }
    } else {
      app_log_warning("ERROR RAIL_StartTx() result: %d", rail_status);
    }
    tx_requested = false;
#if defined(SL_CATALOG_KERNEL_PRESENT)
    app_task_notify();
#endif
  }
}

/******************************************************************************
 * The API forwards the received rx packet on CLI
 *****************************************************************************/
static void printf_rx_packet(const uint8_t * const rx_buffer, uint16_t length)
{
  uint16_t current_channel = get_channel();

  app_log_info("Packet has been received on channel %d:\n", current_channel);
  for (uint16_t i = 0; i < length; i++) {
    app_log_info("0x%02X", rx_buffer[i]);
    if (i < length - 1) {
      app_log_info(", ");
    } else {
      app_log_info("\n");
    }
  }
  if (get_print_packet_details()) {
    if (get_phy_modulation_from_channel(get_channel()) == M_OFDM) {
      app_log_info("With rate %d and scramble: %d\n",
                   get_ofdm_rate(),
                   get_ofdm_scrambler());
    } else {
      app_log_info("With fcs type %d and whitening %d:\n",
                   get_fsk_fcs_type(),
                   get_fsk_whitening());
    }
  }
}
