/***************************************************************************//**
 * # License
 * <b> Copyright 2021 Silicon Laboratories Inc. www.silabs.com </b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * https://www.silabs.com/about-us/legal/master-software-license-agreement
 * By installing, copying or otherwise using this software, you agree to the
 * terms of the MSLA.
 *
 ******************************************************************************/

/**
 * @file
 * Defines configuration extension for zpal-uart.
 */

#include <stdint.h>

typedef struct {
  uint8_t tx_pin;                                 ///< Pin for UART Tx.
  uint8_t tx_port;                                ///< Port for UART Tx pin.
  uint8_t tx_loc;                                 ///< Location number for UART Tx pin.
  uint8_t rx_pin;                                 ///< Pin for UART Rx.
  uint8_t rx_port;                                ///< Port for UART Rx pin.
  uint8_t rx_loc;                                 ///< Location number for UART Tx pin.
} zpal_uart_config_ext_t;
