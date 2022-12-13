/**
 * @file
 * Defines configuration extension for zpal-uart.
 *
 * @copyright 2021 Silicon Laboratories Inc.
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
