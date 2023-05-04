/***************************************************************************//**
 * @file
 * @brief IO Stream USART Component.
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
#include "sl_iostream.h"
#include "sl_iostream_uart.h"
#include "sli_iostream_uart.h"
#include "sl_iostream_usart.h"
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
#include "em_usart.h"
#include "em_gpio.h"

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/

static sl_status_t usart_tx(void *context,
                            char c);

static void usart_set_next_byte_detect(void *context);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
static void usart_tx_completed(void *context, bool enable);
#endif

static sl_status_t usart_deinit(void *context);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * USART Stream init
 ******************************************************************************/
sl_status_t sl_iostream_usart_init(sl_iostream_uart_t *iostream_uart,
                                   sl_iostream_uart_config_t *uart_config,
                                   USART_InitAsync_TypeDef *init,
                                   sl_iostream_usart_config_t *config,
                                   sl_iostream_usart_context_t *usart_context)
{
  sl_status_t status;
#if (_SILICON_LABS_32B_SERIES > 0)
  bool cts = false;
  bool rts = false;
#endif

  status = sli_iostream_uart_context_init(iostream_uart,
                                          &usart_context->context,
                                          uart_config,
                                          usart_tx,
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
                                          usart_tx_completed,
#else
                                          NULL,
#endif
                                          usart_set_next_byte_detect,
                                          usart_deinit,
                                          1,
                                          1);
  if (status != SL_STATUS_OK) {
    return status;
  }

  usart_context->usart = config->usart;

  //Save useful config info to usart context
  usart_context->clock = config->clock;
  usart_context->tx_pin = config->tx_pin;
  usart_context->tx_port = config->tx_port;
  usart_context->rx_pin = config->rx_pin;
  usart_context->rx_port = config->rx_port;
#if (_SILICON_LABS_32B_SERIES > 0)
  usart_context->cts_pin = config->cts_pin;
  usart_context->cts_port = config->cts_port;
  usart_context->rts_pin = config->rts_pin;
  usart_context->rts_port = config->rts_port;
#endif

  // Enable peripheral clocks
#if defined(_CMU_HFPERCLKEN0_MASK)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif
  // Configure GPIO pins
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure TX and RX GPIOs
  GPIO_PinModeSet(config->tx_port, config->tx_pin, gpioModePushPull, 1);
  GPIO_PinModeSet(config->rx_port, config->rx_pin, gpioModeInputPull, 1);

  CMU_ClockEnable(config->clock, true);

  // Configure USART for basic async operation
  init->enable = usartDisable;
  USART_InitAsync(config->usart, init);

#if defined(GPIO_USART_ROUTEEN_TXPEN)
  // Enable pins at correct USART/USART location
  GPIO->USARTROUTE[config->usart_index].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_RXPEN;
  GPIO->USARTROUTE[config->usart_index].TXROUTE = (config->tx_port << _GPIO_USART_TXROUTE_PORT_SHIFT)
                                                  | (config->tx_pin << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[config->usart_index].RXROUTE = (config->rx_port << _GPIO_USART_RXROUTE_PORT_SHIFT)
                                                  | (config->rx_pin << _GPIO_USART_RXROUTE_PIN_SHIFT);

#elif defined(USART_ROUTEPEN_RXPEN)
  // Enable pins at correct USART/USART location
  config->usart->ROUTEPEN |= USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
  config->usart->ROUTELOC0 = (config->usart->ROUTELOC0 & ~(_USART_ROUTELOC0_TXLOC_MASK | _USART_ROUTELOC0_RXLOC_MASK))
                             | (config->usart_tx_location << _USART_ROUTELOC0_TXLOC_SHIFT)
                             | (config->usart_rx_location << _USART_ROUTELOC0_RXLOC_SHIFT);
  config->usart->ROUTEPEN = USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
#else
  config->usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | (config->usart_location << _USART_ROUTE_LOCATION_SHIFT);
#endif

  // Configure GPIOs for hwflowcontrol
 #if (_SILICON_LABS_32B_SERIES > 0)
  usart_context->flags = 0;
  switch (init->hwFlowControl) {
    case usartHwFlowControlNone:
      break;
    case usartHwFlowControlCts:
      cts = true;
      usart_context->flags = SLI_IOSTREAM_UART_FLAG_CTS;
      break;
    case usartHwFlowControlRts:
      rts = true;
      usart_context->flags = SLI_IOSTREAM_UART_FLAG_RTS;
      break;
    case usartHwFlowControlCtsAndRts:
      cts = true;
      rts = true;
      usart_context->flags = SLI_IOSTREAM_UART_FLAG_CTS | SLI_IOSTREAM_UART_FLAG_RTS;
      break;
    default:
      return SL_STATUS_INVALID_CONFIGURATION;
  }

  if (cts == true) {
    GPIO_PinModeSet(config->cts_port, config->cts_pin, gpioModeInputPull, 0);

 #if defined(_USART_ROUTEPEN_RTSPEN_MASK) && defined(_USART_ROUTEPEN_CTSPEN_MASK)
    config->usart->ROUTELOC1 = (config->usart_cts_location << _USART_ROUTELOC1_CTSLOC_SHIFT);
    config->usart->CTRLX    |= USART_CTRLX_CTSEN;
    config->usart->ROUTEPEN |= USART_ROUTEPEN_CTSPEN;
 #elif defined(_GPIO_USART_ROUTEEN_MASK)
    GPIO->USARTROUTE_SET[config->usart_index].CTSROUTE = (config->cts_port << _GPIO_USART_CTSROUTE_PORT_SHIFT)
                                                         | (config->cts_pin << _GPIO_USART_CTSROUTE_PIN_SHIFT);
    config->usart->CTRLX_SET = USART_CTRLX_CTSEN;
 #endif
  }
  if (rts == true) {
    GPIO_PinModeSet(config->rts_port, config->rts_pin, gpioModePushPull, 0);
 #if defined(_USART_ROUTEPEN_RTSPEN_MASK) && defined(_USART_ROUTEPEN_CTSPEN_MASK)
    config->usart->ROUTELOC1 |= (config->usart_rts_location << _USART_ROUTELOC1_RTSLOC_SHIFT);
    config->usart->ROUTEPEN |= USART_ROUTEPEN_RTSPEN;

 #elif defined(_GPIO_USART_ROUTEEN_MASK)
    GPIO->USARTROUTE_SET[config->usart_index].ROUTEEN = GPIO_USART_ROUTEEN_RTSPEN;
    GPIO->USARTROUTE_SET[config->usart_index].RTSROUTE = (config->rts_port << _GPIO_USART_RTSROUTE_PORT_SHIFT)
                                                         | (config->rts_pin << _GPIO_USART_RTSROUTE_PIN_SHIFT);
 #endif
  }
 #endif  // Configure GPIOs for hwflowcontrol

 #if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && defined(_SILICON_LABS_32B_SERIES_2)
  usart_context->tx_port = config->tx_port;
  usart_context->tx_pin = config->tx_pin;
 #endif

  // Enable RX interrupts
  USART_IntEnable(usart_context->usart, USART_IF_RXDATAV);

  // Finally enable USART
  USART_Enable(config->usart, usartEnable);

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * @brief USART IRQ Handler.
 *****************************************************************************/
void sl_iostream_usart_irq_handler(sl_iostream_uart_t *iostream_uart)
{
  sl_iostream_usart_context_t *usart_context = (sl_iostream_usart_context_t *) iostream_uart->stream.context;

  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  // Handle Transmit Complete Events
  if (usart_context->usart->IF & USART_IF_TXC) {
    USART_IntClear(usart_context->usart, USART_IF_TXC);
    // Check if the Status register has the TXC flag as well since the flag will clean itself
    // if other transmissions are queued contrary to the IF flag
    if ((USART_StatusGet(usart_context->usart) & _USART_STATUS_TXC_MASK) != 0) {
      sli_uart_txc(&usart_context->context);
    }
    // mandatory return to avoid going into rx_data_available == false when TXC,
    // since we can't read RXDATAV flag because DMA consumes it immediately when armed.
    return;
  }
#endif

  // When this point is reached, new data was received
  #if !defined(SL_CATALOG_KERNEL_PRESENT) && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  // Always wakeup the core up from IRQ
  usart_context->context.sleep = SL_POWER_MANAGER_WAKEUP;
  #endif

  // Detected new byte, signal the core
  if (usart_context->context.rx_data_available == false) {
    // Disable the IRQ until the RX Buffer is emptied, or becomes full
    USART_IntDisable(usart_context->usart, USART_IF_RXDATAV);
    sl_atomic_store(usart_context->context.rx_data_available, true);
    #if defined(SL_CATALOG_KERNEL_PRESENT)
    // Unlock the read thread
    if (usart_context->context.block) {
      if (osSemaphoreGetCount(usart_context->context.read_signal) == 0) {
        osStatus_t status = osSemaphoreRelease(usart_context->context.read_signal);
        EFM_ASSERT(status == osOK);
      }
    }
    #endif // SL_CATALOG_KERNEL_PRESENT
    return;
  }

  // Rx Buffer full, check if last byte is control character
  if (usart_context->context.rx_buffer_full == true) {
    // Check if most recent byte is flow control (we will lose this data)
    if (usart_context->context.sw_flow_control == true) {
      // Send XOFF to indicate RX buffer is full
      sl_atomic_store(usart_context->context.remote_xon, false);
      USART_Tx(usart_context->usart, UARTXOFF);

      // Make sure RXDATAV stays enabled to avoid deadlock if both sides are full
      USART_IntEnable(usart_context->usart, USART_IF_RXDATAV);

      // Check if received byte is control char
      char dropped_byte;
      dropped_byte = (char)usart_context->usart->RXDATA;

      if (dropped_byte == UARTXON) {
        sl_atomic_store(usart_context->context.xon, true);
      } else if (dropped_byte == UARTXOFF) {
        sl_atomic_store(usart_context->context.xon, false);
      }

      // Found most recent control character, set the scan pointer to the end of the received data
      if (dropped_byte == UARTXON || dropped_byte == UARTXOFF) {
        #if defined(LDMA_PRESENT)
        usart_context->context.ctrl_char_scan_ptr = (uint8_t*)LDMA->CH[usart_context->context.dma.channel].DST - 1;
        #elif defined(DMA_PRESENT)
        DMA_DESCRIPTOR_TypeDef* desc = ((DMA_DESCRIPTOR_TypeDef *)(DMA->CTRLBASE)) + usart_context->context.dma.channel;
        usart_context->context.ctrl_char_scan_ptr = (uint8_t*)desc->DSTEND - 1;
        #else
        #error Missing (L)DMA peripheral
        #endif
      }
      // The byte is now lost...
      return;
    }
  }

  // Can reach here if data was available and next byte detect was enabled (e.g. for sleep).
  // Disable RXDATAV IRQ to avoid looping in IRQ forever.
  USART_IntDisable(usart_context->usart, USART_IF_RXDATAV);
}

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * Internal stream write implementation
 ******************************************************************************/
static sl_status_t usart_tx(void *context,
                            char c)
{
  sl_iostream_usart_context_t *usart_context = (sl_iostream_usart_context_t *)context;

  USART_Tx(usart_context->usart, (uint8_t)c);

#if defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  /* Wait until transmit buffer is empty */
  while (!(USART_StatusGet(usart_context->usart) & USART_STATUS_TXBL)) ;
#endif

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Enable USART Rx Data Valid (RXDATAV) Interrupt
 ******************************************************************************/
static void usart_set_next_byte_detect(void *context)
{
  sl_iostream_usart_context_t *usart_context = (sl_iostream_usart_context_t *)context;

  USART_IntEnable(usart_context->usart, USART_IF_RXDATAV);
}

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
/***************************************************************************//**
 * Enable/Disable USART Tx Complete (TXC) Interrupt
 ******************************************************************************/
static void usart_tx_completed(void *context, bool enable)
{
  sl_iostream_usart_context_t *usart_context = (sl_iostream_usart_context_t *)context;
  if (enable) {
    USART_IntEnable(usart_context->usart, USART_IF_TXC);
  } else {
    USART_IntDisable(usart_context->usart, USART_IF_TXC);
    USART_IntClear(usart_context->usart, USART_IF_TXC);
  }
}
#endif

/***************************************************************************//**
 * USART Stream De-init.
 ******************************************************************************/
static sl_status_t usart_deinit(void *context)
{
  sl_iostream_usart_context_t *usart_context = (sl_iostream_usart_context_t *)context;

  // Wait until transfer is completed
  while (!(USART_StatusGet(usart_context->usart) & USART_STATUS_TXBL)) {
  }

  // De-Configure TX and RX GPIOs
  GPIO_PinModeSet(usart_context->tx_port, usart_context->tx_pin, gpioModeDisabled, 0);
  GPIO_PinModeSet(usart_context->rx_port, usart_context->rx_pin, gpioModeDisabled, 0);

#if (_SILICON_LABS_32B_SERIES > 0)
  // De-Configure Flow Control GPIOs
  if (usart_context->flags & SLI_IOSTREAM_UART_FLAG_CTS) {
    GPIO_PinModeSet(usart_context->cts_port, usart_context->cts_pin, gpioModeDisabled, 0);
  }
  if (usart_context->flags & SLI_IOSTREAM_UART_FLAG_RTS) {
    GPIO_PinModeSet(usart_context->rts_port, usart_context->rts_pin, gpioModeDisabled, 0);
  }
#endif

  // Disable USART IRQ
  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  USART_IntDisable(usart_context->usart, USART_IF_TXC);
  #endif
  USART_IntDisable(usart_context->usart, USART_IF_RXDATAV);

  // Disable USART peripheral
  USART_Enable(usart_context->usart, usartDisable);

  // Disable USART Clock
  CMU_ClockEnable(usart_context->clock, false);

  return SL_STATUS_OK;
}
