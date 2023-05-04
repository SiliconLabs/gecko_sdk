/***************************************************************************//**
 * @file
 * @brief IO Stream EUSART Component.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_status.h"
#include "sl_slist.h"
#include "sl_iostream.h"
#include "sl_iostream_uart.h"
#include "sli_iostream_uart.h"
#include "sl_iostream_eusart.h"
#include "sl_atomic.h"

#if (defined(SL_CATALOG_POWER_MANAGER_PRESENT))
#include "sl_power_manager.h"
#endif

#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "em_device.h"
#include "em_core.h"
#include "em_eusart.h"
#include "em_gpio.h"

/*******************************************************************************
 **************************   LOCAL VARIABLES   ********************************
 ******************************************************************************/

#if (defined(SL_CATALOG_POWER_MANAGER_PRESENT))
static sl_power_manager_em_transition_event_handle_t on_power_manager_event_handle;

static void on_power_manager_event(sl_power_manager_em_t from,
                                   sl_power_manager_em_t to);

static sl_power_manager_em_transition_event_info_t on_power_manager_event_info =
{
  .event_mask = (SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM2 | SL_POWER_MANAGER_EVENT_TRANSITION_LEAVING_EM3),
  .on_event = on_power_manager_event,
};

// List of EUSART streams
sl_slist_node_t *eusart_stream_list = NULL;
#endif

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static sl_status_t eusart_tx(void *context,
                             char c);

static void eusart_set_next_byte_detect(void *context);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
static void eusart_tx_completed(void *context, bool enable);
#endif

static sl_status_t eusart_deinit(void *context);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * EUSART Stream init
 ******************************************************************************/
sl_status_t sl_iostream_eusart_init(sl_iostream_uart_t *iostream_uart,
                                    sl_iostream_uart_config_t *uart_config,
                                    EUSART_UartInit_TypeDef *init,
                                    sl_iostream_eusart_config_t *eusart_config,
                                    sl_iostream_eusart_context_t *eusart_context)
{
  EUSART_AdvancedInit_TypeDef advanced_init = EUSART_ADVANCED_INIT_DEFAULT;
  sl_status_t status;
  bool cts = false;
  bool rts = false;
  uint8_t em_req = 1;

  // Set advanced Settings in config init struct
  if (eusart_config->flow_control != eusartHwFlowControlNone) {
    advanced_init.hwFlowControl = eusart_config->flow_control;
  }
  advanced_init.dmaWakeUpOnRx = true;
  init->advancedSettings = &advanced_init;

  if (eusart_config->enable_high_frequency) {
    em_req = 1;
  } else {
    em_req = 2;
  }

  status = sli_iostream_uart_context_init(iostream_uart,
                                          &eusart_context->context,
                                          uart_config,
                                          eusart_tx,
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
                                          eusart_tx_completed,
#else
                                          NULL,
#endif
                                          eusart_set_next_byte_detect,
                                          eusart_deinit,
                                          em_req,
                                          em_req);
  if (status != SL_STATUS_OK) {
    return status;
  }

  eusart_context->clock = eusart_config->clock;
  eusart_context->rx_pin = eusart_config->rx_pin;
  eusart_context->rx_port = eusart_config->rx_port;
  eusart_context->tx_pin = eusart_config->tx_pin;
  eusart_context->tx_port = eusart_config->tx_port;
  eusart_context->cts_pin = eusart_config->cts_pin;
  eusart_context->cts_port = eusart_config->cts_port;
  eusart_context->rts_pin = eusart_config->rts_pin;
  eusart_context->rts_port = eusart_config->rts_port;

  eusart_context->eusart = eusart_config->eusart;

  // Configure GPIO pins
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure TX and RX GPIOs
  GPIO_PinModeSet(eusart_config->tx_port, eusart_config->tx_pin, gpioModePushPull, 1);
  GPIO_PinModeSet(eusart_config->rx_port, eusart_config->rx_pin, gpioModeInputPull, 1);

  // Configure EUSART for basic async operation
  init->enable = eusartDisable;
  eusart_context->flags = 0;

  CMU_ClockEnable(eusart_config->clock, true);
  if (eusart_config->enable_high_frequency == false) {
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2) \
    || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7)
    CMU_ClockEnable(cmuClock_EM23GRPACLK, true);
#if defined(EUART_PRESENT)
    CMU_CLOCK_SELECT_SET(EUART0CLK, EM23GRPACLK);
#elif defined(EUSART_PRESENT)
    CMU_CLOCK_SELECT_SET(EUSART0CLK, EM23GRPACLK);
#else
#error Missing EU(S)ART peripheral
#endif
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
    CMU_ClockEnable(cmuClock_LFRCO, true);
    if (eusart_config->clock == cmuClock_EUSART0
        || eusart_config->clock == cmuClock_EUSART0CLK) {
      CMU_CLOCK_SELECT_SET(EUSART0CLK, LFRCO);
    }
#else
#error Unsupported board configuration
#endif
    EUSART_UartInitLf(eusart_config->eusart, init);
  } else {
#if defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2) \
    || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_7)
    CMU_ClockEnable(cmuClock_EM01GRPACLK, true);
#if defined(EUART_PRESENT)
    CMU_CLOCK_SELECT_SET(EUART0CLK, EM01GRPACLK);
#elif defined(EUSART_PRESENT)
    CMU_CLOCK_SELECT_SET(EUSART0CLK, EM01GRPACLK);
#else
#error Missing EU(S)ART peripheral
#endif
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG >= 3)
    CMU_CLOCK_SELECT_SET(EM01GRPCCLK, HFRCODPLL);
    if (eusart_config->clock == cmuClock_EUSART0
        || eusart_config->clock == cmuClock_EUSART0CLK) {
      CMU_CLOCK_SELECT_SET(EUSART0CLK, EM01GRPCCLK);
    }
#else
#error Unsupported board configuration
#endif

    EUSART_UartInitHf(eusart_config->eusart, init);
    eusart_context->flags |= SLI_IOSTREAM_UART_FLAG_HIGH_FREQUENCY;
  }
#if defined(EUART_COUNT) && (EUART_COUNT > 0)
  GPIO->EUARTROUTE->ROUTEEN = GPIO_EUART_ROUTEEN_TXPEN;
  GPIO->EUARTROUTE->TXROUTE = (eusart_config->tx_port << _GPIO_EUART_TXROUTE_PORT_SHIFT)
                              | (eusart_config->tx_pin << _GPIO_EUART_TXROUTE_PIN_SHIFT);
  GPIO->EUARTROUTE->RXROUTE = (eusart_config->rx_port << _GPIO_EUART_RXROUTE_PORT_SHIFT)
                              | (eusart_config->rx_pin << _GPIO_EUART_RXROUTE_PIN_SHIFT);
#else
  GPIO->EUSARTROUTE[eusart_config->port_index].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN;
  GPIO->EUSARTROUTE[eusart_config->port_index].TXROUTE =
    (eusart_config->tx_port << _GPIO_EUSART_TXROUTE_PORT_SHIFT)
    | (eusart_config->tx_pin << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[eusart_config->port_index].RXROUTE =
    (eusart_config->rx_port << _GPIO_EUSART_RXROUTE_PORT_SHIFT)
    | (eusart_config->rx_pin << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
#endif
  // Configure GPIOs for hwflowcontrol
  switch (eusart_config->flow_control) {
    case eusartHwFlowControlNone:
      break;
    case eusartHwFlowControlCts:
      cts = true;
      eusart_context->flags |= SLI_IOSTREAM_UART_FLAG_CTS;
      break;
    case eusartHwFlowControlRts:
      rts = true;
      eusart_context->flags |= SLI_IOSTREAM_UART_FLAG_RTS;
      break;
    case eusartHwFlowControlCtsAndRts:
      cts = true;
      rts = true;
      eusart_context->flags |= SLI_IOSTREAM_UART_FLAG_CTS | SLI_IOSTREAM_UART_FLAG_RTS;
      break;
    default:
      return SL_STATUS_INVALID_CONFIGURATION;
  }

  if (cts == true) {
    GPIO_PinModeSet(eusart_config->cts_port, eusart_config->cts_pin, gpioModeInputPull, 0);
#if defined(EUART_COUNT) && (EUART_COUNT > 0)
    GPIO->EUARTROUTE_SET->CTSROUTE = (eusart_config->cts_port << _GPIO_EUART_CTSROUTE_PORT_SHIFT)
                                     | (eusart_config->cts_pin << _GPIO_EUART_CTSROUTE_PIN_SHIFT);
#else
    GPIO->EUSARTROUTE_SET[eusart_config->port_index].CTSROUTE =
      (eusart_config->cts_port << _GPIO_EUSART_CTSROUTE_PORT_SHIFT)
      | (eusart_config->cts_pin << _GPIO_EUSART_CTSROUTE_PIN_SHIFT);
#endif
  }
  if (rts == true) {
    GPIO_PinModeSet(eusart_config->rts_port, eusart_config->rts_pin, gpioModePushPull, 0);
#if defined(EUART_COUNT) && (EUART_COUNT > 0)
    GPIO->EUARTROUTE_SET->ROUTEEN = GPIO_EUART_ROUTEEN_RTSPEN;
    GPIO->EUARTROUTE_SET->RTSROUTE = (eusart_config->rts_port << _GPIO_EUART_RTSROUTE_PORT_SHIFT)
                                     | (eusart_config->rts_pin << _GPIO_EUART_RTSROUTE_PIN_SHIFT);
#else
    GPIO->EUSARTROUTE_SET[eusart_config->port_index].ROUTEEN = GPIO_EUSART_ROUTEEN_RTSPEN;
    GPIO->EUSARTROUTE_SET[eusart_config->port_index].RTSROUTE =
      (eusart_config->rts_port << _GPIO_EUSART_RTSROUTE_PORT_SHIFT)
      | (eusart_config->rts_pin << _GPIO_EUSART_RTSROUTE_PIN_SHIFT);
#endif
  }

  // Enable RX interrupts
  EUSART_IntEnable(eusart_context->eusart, EUSART_IF_RXFL);

  // Finally enable EUSART
  EUSART_Enable(eusart_config->eusart, eusartEnable);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  // Subscribe to notification to re-enable eusart after deepsleep.
  if (eusart_stream_list == NULL) {
    sl_power_manager_subscribe_em_transition_event(&on_power_manager_event_handle, &on_power_manager_event_info);
  }
  sl_slist_push(&eusart_stream_list, &eusart_context->node);
#endif

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * @brief EUSART IRQ Handler
 *****************************************************************************/
void sl_iostream_eusart_irq_handler(sl_iostream_uart_t *iostream_uart)
{
  sl_iostream_eusart_context_t *eusart_context = (sl_iostream_eusart_context_t *) iostream_uart->stream.context;

  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  // Handle Transmit Complete Events
  if (eusart_context->eusart->IF & EUSART_IF_TXC) {
    EUSART_IntClear(eusart_context->eusart, EUSART_IF_TXC);
    // Check if the Status register has the TXC flag as well since the flag will clean itself
    // if other transmissions are queued contrary to the IF flag
    if ((EUSART_StatusGet(eusart_context->eusart) & _EUSART_STATUS_TXC_MASK) != 0) {
      sli_uart_txc(&eusart_context->context);
    }
  }
  #endif

  // Handle RXFL events
  if (eusart_context->eusart->IF & EUSART_IF_RXFL) {
  #if !defined(SL_CATALOG_KERNEL_PRESENT) && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
    // Always wakeup the core up from RX IRQ
    eusart_context->context.sleep = SL_POWER_MANAGER_WAKEUP;
  #endif

    // Clear the IF
    eusart_context->eusart->IF_CLR = EUSART_IF_RXFL;
    // Detected new byte, signal the core
    if (eusart_context->context.rx_data_available == false) {
      // Disable the IRQ until the RX Buffer is emptied, or becomes full
      EUSART_IntDisable(eusart_context->eusart, EUSART_IF_RXFL);
      sl_atomic_store(eusart_context->context.rx_data_available, true);
      #if defined(SL_CATALOG_KERNEL_PRESENT)
      // Unlock the read thread
      if (eusart_context->context.block) {
        if (osSemaphoreGetCount(eusart_context->context.read_signal) == 0) {
          osStatus_t status = osSemaphoreRelease(eusart_context->context.read_signal);
          EFM_ASSERT(status == osOK);
        }
      }
      #endif // SL_CATALOG_KERNEL_PRESENT
      return;
    }

    // Rx Buffer full, check if last byte is control character
    if (eusart_context->context.rx_buffer_full == true) {
      // Check if most recent byte is flow control (we will lose this data)
      if (eusart_context->context.sw_flow_control == true) {
        // Send XOFF to indicate RX buffer is full
        sl_atomic_store(eusart_context->context.remote_xon, false);
        EUSART_Tx(eusart_context->eusart, UARTXOFF);

        // Make sure RXFL stays enabled to avoid deadlock if both sides are full
        EUSART_IntEnable(eusart_context->eusart, EUSART_IF_RXFL);

        // Check if received byte is control char
        char dropped_byte;
        dropped_byte = (char)eusart_context->eusart->RXDATA;

        if (dropped_byte == UARTXON) {
          sl_atomic_store(eusart_context->context.xon, true);
        } else if (dropped_byte == UARTXOFF) {
          sl_atomic_store(eusart_context->context.xon, false);
        }

        // Found most recent control character, set the scan pointer to the end of the received data
        if (dropped_byte == UARTXON || dropped_byte == UARTXOFF) {
          eusart_context->context.ctrl_char_scan_ptr = (uint8_t*)LDMA->CH[eusart_context->context.dma.channel].DST - 1;
        }
        // The byte is now lost...
        return;
      }
      // Can reach here if data was available and next byte detect was enabled (e.g. for sleep).
      // Disable RXFL IRQ to avoid looping in IRQ forever.
      EUSART_IntDisable(eusart_context->eusart, EUSART_IF_RXFL);
    }
  }
}

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * Internal stream write implementation
 ******************************************************************************/
static sl_status_t eusart_tx(void *context,
                             char c)
{
  sl_iostream_eusart_context_t *eusart_context = (sl_iostream_eusart_context_t *)context;

  EUSART_Tx(eusart_context->eusart, c);

#if defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
/* Wait until transmit buffer is empty */
  while (!(EUSART_StatusGet(eusart_context->eusart) & EUSART_STATUS_TXC)) ;
#endif

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Enable EUSART Rx Data Valid (RXFL) Interrupt and set the RXFL IF to reflect
 * the current status of the RX FIFO.
 * Make sure the DMA is not running when calling this function.
 ******************************************************************************/
static void eusart_set_next_byte_detect(void *context)
{
  sl_iostream_eusart_context_t *eusart_context = (sl_iostream_eusart_context_t *)context;
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_CRITICAL();
  // Update the IF to reflect the STATUS register (IF is not updated automatically by hardware)
  if (eusart_context->eusart->STATUS & EUSART_STATUS_RXFL) {
    EUSART_IntSet(eusart_context->eusart, EUSART_IF_RXFL);
  } else {
    EUSART_IntClear(eusart_context->eusart, EUSART_IF_RXFL);
  }
  // Enable the IRQ handler
  EUSART_IntEnable(eusart_context->eusart, EUSART_IF_RXFL);
  CORE_EXIT_CRITICAL();
}

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
/***************************************************************************//**
 * Enable/Disable EUSART Tx Complete (TXC) Interrupt
 ******************************************************************************/
static void eusart_tx_completed(void *context, bool enable)
{
  (void)context;
  (void)enable;

  sl_iostream_eusart_context_t *eusart_context = (sl_iostream_eusart_context_t *)context;
  if (enable) {
    EUSART_IntEnable(eusart_context->eusart, EUSART_IF_TXC);
  } else {
    EUSART_IntDisable(eusart_context->eusart, EUSART_IF_TXC);
    EUSART_IntClear(eusart_context->eusart, EUSART_IF_TXC);
  }
}
#endif

/***************************************************************************//**
 * EUSART Stream De-init.
 ******************************************************************************/
static sl_status_t eusart_deinit(void *context)
{
  sl_iostream_eusart_context_t *eusart_context = (sl_iostream_eusart_context_t *)context;

  // Wait until transfert is completed
  while (!(EUSART_StatusGet(eusart_context->eusart) & EUSART_STATUS_TXFL)) {
  }

  // De-Configure TX and RX GPIOs
  GPIO_PinModeSet(eusart_context->tx_port, eusart_context->tx_pin, gpioModeDisabled, 0);
  GPIO_PinModeSet(eusart_context->rx_port, eusart_context->rx_pin, gpioModeDisabled, 0);

  // De-Configure Flow Control GPIOs
  if (eusart_context->flags & SLI_IOSTREAM_UART_FLAG_CTS) {
    GPIO_PinModeSet(eusart_context->cts_port, eusart_context->cts_pin, gpioModeDisabled, 0);
  }
  if (eusart_context->flags & SLI_IOSTREAM_UART_FLAG_RTS) {
    GPIO_PinModeSet(eusart_context->rts_port, eusart_context->rts_pin, gpioModeDisabled, 0);
  }

  // Disable EUSART IRQ
  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  EUSART_IntDisable(eusart_context->eusart, EUSART_IF_TXC);
  #endif
  EUSART_IntDisable(eusart_context->eusart, EUSART_IF_RXFL);

  // Disable EUSART peripheral
  EUSART_Enable(eusart_context->eusart, eusartDisable);

  // Disable EUSART Clock
  CMU_ClockEnable(eusart_context->clock, false);

  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  // Subscribe to notification to re-enable eusart after deepsleep.
  sl_slist_remove(&eusart_stream_list, &eusart_context->node);
  if (eusart_stream_list == NULL) {
    sl_power_manager_unsubscribe_em_transition_event(&on_power_manager_event_handle);
  }
#endif

  return SL_STATUS_OK;
}

#if (defined(SL_CATALOG_POWER_MANAGER_PRESENT))
/***************************************************************************//**
 * Power Manager callback notification for EUSART.
 * It is used to re-enabled EUSART module after deepsleeping.
 ******************************************************************************/
static void on_power_manager_event(sl_power_manager_em_t from,
                                   sl_power_manager_em_t to)
{
  (void)from;

  if (to == SL_POWER_MANAGER_EM1
      || to == SL_POWER_MANAGER_EM0) {
    sl_iostream_eusart_context_t *eusart_context;
    SL_SLIST_FOR_EACH_ENTRY(eusart_stream_list, eusart_context, sl_iostream_eusart_context_t, node) {
      EUSART_Enable(eusart_context->eusart, eusartEnable);
    }
  }
}
#endif
