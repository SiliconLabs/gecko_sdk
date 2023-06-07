/***************************************************************************//**
 * @file
 * @brief IO Stream UART Component.
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
// Define module name for Power Manager debug feature
#define CURRENT_MODULE_NAME    "IOSTREAM_UART"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif

#include "sl_status.h"
#include "sl_iostream.h"
#include "sl_iostream_uart.h"
#include "sli_iostream_uart.h"
#include "sl_atomic.h"
#include "sl_string.h"

#if (defined(SL_CATALOG_KERNEL_PRESENT))
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#endif

#if (defined(SL_CATALOG_POWER_MANAGER_PRESENT))
#include "sl_power_manager.h"
#endif

#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "em_device.h"
#include "em_core.h"
#include "em_gpio.h"

#if !defined(DMA_PRESENT) && !defined(LDMA_PRESENT)
#error Missing (L)DMA peripheral
#endif

/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/
static sl_status_t uart_deinit(void *stream);

static sl_status_t uart_write(void *context,
                              const void *buffer,
                              size_t buffer_length);

static sl_status_t uart_read(void *context,
                             void *buffer,
                             size_t buffer_length,
                             size_t *bytes_read);

static void set_auto_cr_lf(void *context,
                           bool on);

static bool get_auto_cr_lf(void *context);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#if !defined(SL_CATALOG_KERNEL_PRESENT)
static sl_power_manager_on_isr_exit_t sleep_on_isr_exit(void *context);
#endif

static void set_rx_energy_mode_restriction(void *context,
                                           bool on);

static bool get_rx_energy_mode_restriction(void *context);
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT)
static void set_read_block(void *context,
                           bool on);

static bool get_read_block(void *context);
#endif

static void scan_for_ctrl_char(sl_iostream_uart_context_t * uart_context);

static sl_status_t nolock_uart_write(void *context,
                                     const void *buffer,
                                     size_t buffer_length);

static bool dma_irq_handler(unsigned int chan,
                            unsigned int seq,
                            void* user_param);

__STATIC_INLINE uint8_t* get_write_ptr(const sl_iostream_uart_context_t* uart_context);

static void update_ring_buffer(sl_iostream_uart_context_t *uart_context);

static size_t read_rx_buffer(sl_iostream_uart_context_t * uart_context,
                             uint8_t * buffer,
                             size_t buffer_len);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * UART Stream init
 ******************************************************************************/
sl_status_t sli_iostream_uart_context_init(sl_iostream_uart_t *uart,
                                           sl_iostream_uart_context_t *context,
                                           sl_iostream_uart_config_t *config,
                                           sl_status_t (*tx)(void *context, char c),
                                           void (*tx_completed)(void *context, bool enable),
                                           void (*set_next_byte_detect)(void *context),
                                           sl_status_t (*deinit)(void *context),
                                           uint8_t rx_em_req,
                                           uint8_t tx_em_req)
{
  (void)rx_em_req;
  (void)tx_em_req;
  Ecode_t ecode;

  // Configure iostream struct and context
  memset(context, 0, sizeof(*context));
  context->dma.cfg = config->dma_cfg;
  context->rx_data_available = false;
  context->rx_buffer = config->rx_buffer;
  context->rx_buffer_len = config->rx_buffer_length;
  context->rx_read_ptr = context->rx_buffer;
  context->lf_to_crlf = config->lf_to_crlf;
  context->sw_flow_control = config->sw_flow_control;
  context->ctrl_char_scan_ptr = context->rx_read_ptr;
  context->xon = true;
  context->remote_xon = true;
  context->tx = tx;
  context->tx_completed = tx_completed;
  context->set_next_byte_detect = set_next_byte_detect;
  context->deinit = deinit;
  context->rx_irq_number = config->rx_irq_number;
  #if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  context->tx_irq_number = config->tx_irq_number;
  #endif
  uart->stream.context = context;

  uart->stream.write = uart_write;
  uart->stream.read = uart_read;
  uart->set_auto_cr_lf = set_auto_cr_lf;
  uart->get_auto_cr_lf = get_auto_cr_lf;
  uart->deinit = uart_deinit;

  // Init the LDMA
  ecode = DMADRV_Init();
  if (ecode != ECODE_OK && ecode != ECODE_EMDRV_DMADRV_ALREADY_INITIALIZED) {
    return SL_STATUS_INITIALIZATION;
  }
  // Allocate the LDMA channel
  ecode = DMADRV_AllocateChannel((unsigned int *)&context->dma.channel,
                                 NULL);
  if (ecode != ECODE_OK) {
    return SL_STATUS_INITIALIZATION;
  }

#if defined(SL_CATALOG_KERNEL_PRESENT)
  uart->set_read_block = set_read_block;
  uart->get_read_block = get_read_block;
  context->block = true;

  osMutexAttr_t m_attr;
  m_attr.name = "Read Lock";
  m_attr.attr_bits = 0u;
  m_attr.cb_mem = context->read_lock_cb;
  m_attr.cb_size = osMutexCbSize;
  context->read_lock = osMutexNew(&m_attr);
  EFM_ASSERT(context->read_lock != NULL);

  m_attr.name = "Write Lock";
  m_attr.attr_bits = 0u;
  m_attr.cb_mem = context->write_lock_cb;
  context->write_lock = osMutexNew(&m_attr);
  EFM_ASSERT(context->write_lock != NULL);

  osSemaphoreAttr_t s_attr;
  s_attr.name = "Read Signal";
  s_attr.attr_bits = 0u;
  s_attr.cb_mem = context->read_signal_cb;
  s_attr.cb_size = osSemaphoreCbSize;
  context->read_signal = osSemaphoreNew(1, 0u, &s_attr);
  EFM_ASSERT(context->read_signal != NULL);

#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  #if !defined(SL_CATALOG_KERNEL_PRESENT)
  uart->sleep_on_isr_exit = sleep_on_isr_exit;
  context->sleep = SL_POWER_MANAGER_IGNORE;
  #endif // SL_CATALOG_KERNEL_PRESENT

  uart->set_rx_energy_mode_restriction = set_rx_energy_mode_restriction;
  uart->get_rx_energy_mode_restriction = get_rx_energy_mode_restriction;
  context->tx_em = (sl_power_manager_em_t)tx_em_req;
  context->rx_em = (sl_power_manager_em_t)rx_em_req;
  context->em_req_added = false;
  context->tx_idle = true;
  set_rx_energy_mode_restriction(context, config->rx_when_sleeping);
  NVIC_ClearPendingIRQ(config->tx_irq_number);
  NVIC_EnableIRQ(config->tx_irq_number);
#endif // SL_CATALOG_POWER_MANAGER_PRESENT

  // Start the (L)DMA to handle RXDATAV
  ecode = DMADRV_PeripheralMemory(context->dma.channel,
                                  context->dma.cfg.peripheral_signal,
                                  context->rx_buffer,
                                  context->dma.cfg.src,
                                  true,
                                  context->rx_buffer_len,
                                  dmadrvDataSize1,
                                  dma_irq_handler,
                                  context);

  if (ecode != ECODE_OK) {
    return SL_STATUS_INITIALIZATION;
  }

  NVIC_ClearPendingIRQ(config->rx_irq_number);
  NVIC_EnableIRQ(config->rx_irq_number);

  sl_iostream_set_system_default(&uart->stream);

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * @brief On ISR exit
 *****************************************************************************/
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_CATALOG_KERNEL_PRESENT)
static sl_power_manager_on_isr_exit_t sleep_on_isr_exit(void *context)
{
  if (context == NULL) {
    return SL_POWER_MANAGER_IGNORE;
  }

  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;

  if ((uart_context->tx_idle) && (uart_context->sleep == SL_POWER_MANAGER_SLEEP)) {
    sl_power_manager_on_isr_exit_t sleep = uart_context->sleep;
    uart_context->sleep = SL_POWER_MANAGER_IGNORE;
    return sleep;
  } else if ((uart_context->sleep == SL_POWER_MANAGER_WAKEUP)) {
    sl_power_manager_on_isr_exit_t sleep = uart_context->sleep;
    uart_context->sleep = SL_POWER_MANAGER_IGNORE;
    return sleep;
  } else {
    return SL_POWER_MANAGER_IGNORE;
  }
}
#endif

/**************************************************************************//**
 * Set LF to CRLF conversion
 *****************************************************************************/
static void set_auto_cr_lf(void *context,
                           bool on)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;

  sl_atomic_store(uart_context->lf_to_crlf, on);
}

/**************************************************************************//**
 * Get LF to CRLF conversion
 *****************************************************************************/
static bool get_auto_cr_lf(void *context)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  bool conversion;

  sl_atomic_load(conversion, uart_context->lf_to_crlf);

  return conversion;
}

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
/**************************************************************************//**
 * Set Rx when sleeping
 *****************************************************************************/
static void set_rx_energy_mode_restriction(void *context,
                                           bool on)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  bool em_req_added;

  sl_atomic_load(em_req_added, uart_context->em_req_added);
  if ((on == true)
      && (em_req_added == false)) {
    sl_power_manager_add_em_requirement(uart_context->rx_em);
    sl_atomic_store(uart_context->em_req_added, true);
  } else if ((on == false)
             && (em_req_added == true)) {
    sl_power_manager_remove_em_requirement(uart_context->rx_em);
    sl_atomic_store(uart_context->em_req_added, false);
  }
}
#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
/**************************************************************************//**
 * Get Rx when sleeping
 *****************************************************************************/
static bool get_rx_energy_mode_restriction(void *context)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  bool em_req_added;

  sl_atomic_load(em_req_added, uart_context->em_req_added);
  return em_req_added;
}
#endif

#if (defined(SL_CATALOG_KERNEL_PRESENT))
/**************************************************************************//**
 * Set read blocking mode
 *****************************************************************************/
static void set_read_block(void *context,
                           bool on)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  bool block;
  osKernelState_t state;
  osStatus_t status;

  sl_atomic_load(block, uart_context->block);
  state = osKernelGetState();
  if (state == osKernelRunning) {
    // When re-enabling block mode, re-initialize the semaphore to reflect the current state
    if (on == true && block == false) {
      // Read-signal should have been deinit when non-blocking
      EFM_ASSERT(uart_context->read_signal == NULL);

      // Init the read_signal boolean semaphore
      osSemaphoreAttr_t s_attr;
      s_attr.name = "Read Signal";
      s_attr.attr_bits = 0u;
      s_attr.cb_mem = uart_context->read_signal_cb;
      s_attr.cb_size = osSemaphoreCbSize;
      uart_context->read_signal = osSemaphoreNew(1, 0u, &s_attr);
      EFM_ASSERT(uart_context->read_signal != NULL);

      // Set the semaphore to reflect the current state
      if (uart_context->rx_data_available == true) {
        status = osSemaphoreRelease(uart_context->read_signal);
        EFM_ASSERT(status == osOK);
      }
    }
    // When disabling block mode, deinit the read_signal semaphore
    else if (on == false && block == true) {
      status = osSemaphoreDelete(uart_context->read_signal);
      EFM_ASSERT(status == osOK);
      uart_context->read_signal = NULL;
    }
  }
  // Set the block context variable
  sl_atomic_store(uart_context->block, on);
}
#endif

#if (defined(SL_CATALOG_KERNEL_PRESENT))
/**************************************************************************//**
 * Get read blocking mode
 *****************************************************************************/
static bool get_read_block(void *context)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  bool block;

  sl_atomic_load(block, uart_context->block);
  return block;
}
#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
/**************************************************************************//**
 * Signal transmit complete
 *****************************************************************************/
void sli_uart_txc(void *context)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;

  if (uart_context->tx_idle == false) {
    EFM_ASSERT(uart_context->tx_completed != NULL);
    uart_context->tx_completed(context, false);
    uart_context->tx_idle = true;
    sl_power_manager_remove_em_requirement(uart_context->tx_em);
#if !defined(SL_CATALOG_KERNEL_PRESENT)
    uart_context->sleep = SL_POWER_MANAGER_SLEEP;
#endif
  }
}
#endif

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

/***************************************************************************//**
 * UART Stream De-init
 ******************************************************************************/
static sl_status_t uart_deinit(void *stream)
{
  sl_iostream_uart_t *uart = (sl_iostream_uart_t *)stream;
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)uart->stream.context;
  sl_iostream_t *default_stream;
  sl_status_t status = SL_STATUS_OK;
  Ecode_t ecode = ECODE_OK;
#if (defined(SL_CATALOG_KERNEL_PRESENT))
  if (osKernelGetState() == osKernelRunning) {
    // Acquire locks to ensure no others task try to perform operation on the stream at sametime
    EFM_ASSERT(osMutexAcquire(uart_context->write_lock, osWaitForever) == osOK);  // If deinit is called twice in a
                                                                                  // row, the assert will trigger
    // Bypass lock if we print before the kernel is running
    EFM_ASSERT(osMutexAcquire(uart_context->read_lock, osWaitForever) == osOK);   // If deinit is called twice in a
                                                                                  //row, the assert will trigger
  }
#endif

  default_stream = sl_iostream_get_default();

  // Check if uart stream is the default and if it's the case,
  // remove it's reference as the default
  if ((sl_iostream_uart_t*)default_stream == uart) {
    sl_iostream_set_system_default(NULL);
  }

  NVIC_ClearPendingIRQ(uart_context->rx_irq_number);
  NVIC_DisableIRQ(uart_context->rx_irq_number);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  NVIC_ClearPendingIRQ(uart_context->tx_irq_number);
  NVIC_DisableIRQ(uart_context->tx_irq_number);
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT)
  // Delete Kernel synchronization objects.
  status = osSemaphoreDelete(uart_context->read_signal);
  EFM_ASSERT(status == osOK);

  status = osMutexDelete(uart_context->read_lock);
  EFM_ASSERT(status == osOK);

  status = osMutexDelete(uart_context->write_lock);
  EFM_ASSERT(status == osOK);
#endif

  // Stop the DMA
  ecode = DMADRV_StopTransfer(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);

  // Free the DMA channel
  ecode = DMADRV_FreeChannel(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);

  // Try to deinit the DMADRV
  ecode = DMADRV_DeInit();
  EFM_ASSERT(ecode == ECODE_OK || ecode == ECODE_EMDRV_DMADRV_IN_USE);

  // Clear iostream struct and context
  uart->stream.context = NULL;
  uart->stream.write = NULL;
  uart->stream.read = NULL;
  uart->set_auto_cr_lf = NULL;
  uart->get_auto_cr_lf = NULL;

  status = uart_context->deinit(uart_context);

  return status;
}

/***************************************************************************//**
 * Scan the RX Buffer from the last received byte to the last scanned position.
 ******************************************************************************/
static void scan_for_ctrl_char(sl_iostream_uart_context_t * uart_context)
{
  uint8_t *newest_byte, *current_byte;

  // No data to be scanned
  if (uart_context->rx_data_available == false) {
    EFM_ASSERT(uart_context->ctrl_char_scan_ptr == uart_context->rx_read_ptr);
    return;
  }

  #if defined(DMA_PRESENT)
  Ecode_t ecode = DMADRV_PauseTransfer(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);
  #endif // DMA_PRESENT

  // Get the newest byte received
  newest_byte = get_write_ptr(uart_context) - 1;

  #if defined(DMA_PRESENT)
  ecode = DMADRV_ResumeTransfer(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);
  #endif // DMA_PRESENT

  // Wrap newest byte ptr around the ring buffer
  if (newest_byte < uart_context->rx_buffer) {
    newest_byte = uart_context->rx_buffer + (uart_context->rx_buffer_len - 1);
  }

  // Scan the entire buffer until we reach the position of the last scan,
  // or until we find the newest control character
  current_byte = newest_byte;
  while (current_byte != uart_context->ctrl_char_scan_ptr) {
    // Found XOFF character
    if (*current_byte == UARTXON || *current_byte == UARTXOFF) {
      sl_atomic_store(uart_context->xon, (*current_byte == UARTXON));
      break;
    }

    // Decrement and wrap current byte ptr around the ring buffer
    current_byte--;
    if (current_byte < uart_context->rx_buffer) {
      current_byte = uart_context->rx_buffer + (uart_context->rx_buffer_len - 1);
    }
  }

  // Update scan pointer
  uart_context->ctrl_char_scan_ptr = newest_byte;
}

/***************************************************************************//**
 * Internal stream write implementation
 ******************************************************************************/
static sl_status_t nolock_uart_write(void *context,
                                     const void *buffer,
                                     size_t buffer_length)
{
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  char *c = (char *)buffer;
  bool lf_to_crlf = false;
  sl_status_t status = SL_STATUS_FAIL;
  CORE_DECLARE_IRQ_STATE;

  sl_atomic_load(lf_to_crlf, uart_context->lf_to_crlf);

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  CORE_ENTER_ATOMIC();
  if (uart_context->tx_idle == true) {
    CORE_EXIT_ATOMIC();
    sl_power_manager_add_em_requirement(uart_context->tx_em);
    CORE_ENTER_ATOMIC();
    uart_context->tx_idle = false;
  }
  CORE_EXIT_ATOMIC();
#endif

  uint32_t i = 0;
  while (i < buffer_length) {
    bool xon = false;
    if (uart_context->sw_flow_control == true) {
      CORE_ENTER_ATOMIC();
      scan_for_ctrl_char(uart_context);
      CORE_EXIT_ATOMIC();
    }
    sl_atomic_load(xon, uart_context->xon);
    if (xon) {
      if (lf_to_crlf == true) {
        if (*c == '\n') {
          status = uart_context->tx(uart_context, '\r');
        }
      }
      status = uart_context->tx(uart_context, *c);
      if (status != SL_STATUS_OK) {
        return status;
      }
      c++;
      i++;
    }         // Active wait if xon is false
  }

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && !defined(SL_IOSTREAM_UART_FLUSH_TX_BUFFER)
  uart_context->tx_completed(context, true);
#endif

  return status;
}

/***************************************************************************//**
 * Internal stream write implementation
 ******************************************************************************/
static sl_status_t uart_write(void *context,
                              const void *buffer,
                              size_t buffer_length)
{
#if (defined(SL_CATALOG_KERNEL_PRESENT))
  osStatus_t status;
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  if (osKernelGetState() == osKernelRunning) {
    // Bypass lock if we print before the kernel is running
    status = osMutexAcquire(uart_context->write_lock, osWaitForever);

    if (status != osOK) {
      return SL_STATUS_INVALID_STATE;       // Can happen if a task deinit and another try to write at sametime
    }
  }
#endif

  nolock_uart_write(context, buffer, buffer_length);

#if (defined(SL_CATALOG_KERNEL_PRESENT))
  if (osKernelGetState() == osKernelRunning) {
    // Bypass lock if we print before the kernel is running
    status = osMutexRelease(uart_context->write_lock);
    EFM_ASSERT(status == osOK);
  }
#endif
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Internal stream read implementation
 ******************************************************************************/
static sl_status_t uart_read(void *context,
                             void *buffer,
                             size_t buffer_length,
                             size_t *bytes_read)
{
  CORE_DECLARE_IRQ_STATE;
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;

   #if (defined(SL_CATALOG_KERNEL_PRESENT))
  osStatus_t status;
  if (osKernelGetState() == osKernelRunning) {
    // Bypass lock if we print before the kernel is running
    status = osMutexAcquire(uart_context->read_lock, osWaitForever);

    if (status != osOK) {
      return SL_STATUS_INVALID_STATE;   // Can happen if a task deinit and another try to read at sametime
    }

    if (uart_context->block) {
      EFM_ASSERT(osSemaphoreAcquire(uart_context->read_signal, osWaitForever) == osOK);
    }
  }
  #endif

  CORE_ENTER_ATOMIC();
  *bytes_read = read_rx_buffer(uart_context, (uint8_t *) buffer, (size_t)buffer_length);
  CORE_EXIT_ATOMIC();

  #if (defined(SL_CATALOG_KERNEL_PRESENT))
  if (osKernelGetState() == osKernelRunning) {
    // Bypass lock if we print before the kernel is running
    EFM_ASSERT(osMutexRelease(uart_context->read_lock) == osOK);
  }
  #endif

  if (*bytes_read == 0) {
    return SL_STATUS_EMPTY;
  } else {
    return SL_STATUS_OK;
  }
}

/***************************************************************************//**
 * Updates the (L)DMA to re-use whatever space is in the ring buffer.
 * Always returns false (no loop, check DMADRV IRQ callbacks documentation
 * for more details).
 ******************************************************************************/
static bool dma_irq_handler(unsigned int chan, unsigned int seq, void* user_param)
{
  (void) seq;
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)user_param;
  uint8_t *write_ptr;
  Ecode_t ecode;
  size_t available_space;

  // Compute next write position
  {
    // DMA is stopped, no need to pause before calling get_write_ptr()
    write_ptr = get_write_ptr(uart_context);
  }

  // Compute available space
  if (uart_context->rx_read_ptr >= write_ptr) {
    available_space = (size_t)(uart_context->rx_read_ptr - write_ptr);
  } else {
    available_space = (size_t)((uart_context->rx_buffer + uart_context->rx_buffer_len) - write_ptr);
  }

  // Space available in the RX buffer
  if (available_space > 0) {
    // Start the DMA transfer
    ecode = DMADRV_PeripheralMemory(chan,
                                    uart_context->dma.cfg.peripheral_signal,
                                    write_ptr,
                                    uart_context->dma.cfg.src,
                                    true,
                                    available_space,
                                    dmadrvDataSize1,
                                    dma_irq_handler,
                                    uart_context);
    EFM_ASSERT(ecode == ECODE_OK);
  }
  // RX buffer is full
  else {
    uart_context->rx_buffer_full = true;

    // Send first XOFF. Subsequent XOFFs will be sent by the stream's IRQ handler.
    if (uart_context->sw_flow_control) {
      sl_atomic_store(uart_context->remote_xon, false);
      uart_context->tx(uart_context, UARTXOFF);
      // Enable the RXDATAV IRQ to check if we receive a control character when buffer is full
      uart_context->set_next_byte_detect(uart_context);
    }
  }
  return false;
}

/***************************************************************************//**
 * Get the next byte to be written to by the (L)DMA.
 * When using a non-linked DMA, you should pause the DMA before calling to ensure
 * the validity of the result.
 ******************************************************************************/
__STATIC_INLINE uint8_t* get_write_ptr(const sl_iostream_uart_context_t * uart_context)
{
  uint8_t* dst;

  #if defined(DMA_PRESENT)
  int remaining;
  Ecode_t ecode;
  ecode = DMADRV_TransferRemainingCount(uart_context->dma.channel, &remaining);
  EFM_ASSERT(ecode == ECODE_OK);

  DMA_DESCRIPTOR_TypeDef* desc = ((DMA_DESCRIPTOR_TypeDef *)(DMA->CTRLBASE)) + uart_context->dma.channel;
  dst = ((uint8_t*)desc->DSTEND + 1) - remaining;

  #elif defined(LDMA_PRESENT)
  dst = (uint8_t *)LDMA->CH[uart_context->dma.channel].DST;
  #endif

  // Check for buffer over/underflow
  EFM_ASSERT(dst <= (uart_context->rx_buffer + uart_context->rx_buffer_len)
             && dst >= uart_context->rx_buffer);

  // Wrap dst around
  if (dst == (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
    dst = uart_context->rx_buffer;
  }

  return dst;
}

/***************************************************************************//**
 * Update ring buffer pointers and DMA descriptor.
 ******************************************************************************/
static void update_ring_buffer(sl_iostream_uart_context_t * uart_context)
{
  Ecode_t ecode;
  bool dma_done, irq_pending;
  uint8_t *write_ptr;

  // Made space in the buffer by reading
  uart_context->rx_buffer_full = false;

  // Pause the DMA to update
  ecode = DMADRV_PauseTransfer(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);

  // Get next byte to be written by DMA
  write_ptr = get_write_ptr(uart_context);

  // All data has been read, reset the DMA to re-use all the buffer
  if (write_ptr == uart_context->rx_read_ptr) {
    // Reset DMA to the start of the UART Rx Buffer and all control pointers
    uart_context->rx_data_available = false;
    write_ptr = uart_context->rx_buffer;
    uart_context->rx_read_ptr = write_ptr;
    if (uart_context->sw_flow_control) {
      uart_context->ctrl_char_scan_ptr = uart_context->rx_read_ptr;
    }

    // Enable RXDATAV IRQ to signal next incoming byte
    uart_context->set_next_byte_detect(uart_context);

    // Start new transfer for all rx_buffer
    ecode = DMADRV_PeripheralMemory(uart_context->dma.channel,
                                    uart_context->dma.cfg.peripheral_signal,
                                    write_ptr,
                                    uart_context->dma.cfg.src,
                                    true,
                                    uart_context->rx_buffer_len,
                                    dmadrvDataSize1,
                                    dma_irq_handler,
                                    uart_context);
    EFM_ASSERT(ecode == ECODE_OK);
  }
  // Data still available in buffer
  else {
    uart_context->rx_data_available = true;

    // Unlock read (only in Kernel)
    #if defined(SL_CATALOG_KERNEL_PRESENT)
    if (uart_context->block) {
      EFM_ASSERT(uart_context->rx_data_available);     // Should always be data available here
      if (osSemaphoreGetCount(uart_context->read_signal) == 0) {
        osStatus_t status = osSemaphoreRelease(uart_context->read_signal);
        EFM_ASSERT(status == osOK);
      }
    }
    #endif // SL_CATALOG_KERNEL_PRESENT

    // Check if DMA is still active
    ecode = DMADRV_TransferDone(uart_context->dma.channel, &dma_done);
    EFM_ASSERT(ecode == ECODE_OK);

    // DMA stopped because it was full
    if (dma_done) {
      // Check if IRQ is pending
      ecode = DMADRV_TransferCompletePending(uart_context->dma.channel, &irq_pending);
      EFM_ASSERT(ecode == ECODE_OK);

      // No IRQ pending
      if (irq_pending == false) {
        // Call IRQ handler to start a new transfer over available space
        dma_irq_handler(uart_context->dma.channel, 0, uart_context);
      }
    }
  }
  // Resume DMA
  ecode = DMADRV_ResumeTransfer(uart_context->dma.channel);
  EFM_ASSERT(ecode == ECODE_OK);
}

/***************************************************************************//**
 * Tries to read the requested amount of data.
 * Returns the number of bytes read.
 ******************************************************************************/
static size_t read_rx_buffer(sl_iostream_uart_context_t * uart_context,
                             uint8_t * buffer,
                             size_t buffer_len)
{
  if (buffer_len == 0) {
    return 0;
  }

  if (uart_context->rx_data_available == false) {
    #if defined(SL_CATALOG_KERNEL_PRESENT)
    if (uart_context->block) {
      EFM_ASSERT(false);     // Should always have data in blocking mode
    }
    #endif
    return 0;
  }
  CORE_DECLARE_IRQ_STATE;

  uint8_t *write_ptr;     // Pointer to the next byte to be written by the (L)DMA
  size_t read_size = 0;     // Number of bytes processed from the Rx Buffer
  size_t ret_val = 0;     // Number of bytes written to the user buffer

  // Compute the read_size
  {
    #if defined(DMA_PRESENT)
    Ecode_t ecode;
    ecode = DMADRV_PauseTransfer(uart_context->dma.channel);
    EFM_ASSERT(ecode == ECODE_OK);
    #endif // DMA_PRESENT

    write_ptr = get_write_ptr(uart_context);

    #if defined(DMA_PRESENT)
    ecode = DMADRV_ResumeTransfer(uart_context->dma.channel);
    EFM_ASSERT(ecode == ECODE_OK);
    #endif // DMA_PRESENT

    if (write_ptr == uart_context->rx_read_ptr) {
      // (L)DMA is wrapped over rx_read_ptr, make sure it is stopped
      EFM_ASSERT(uart_context->rx_buffer_full == true);
    }

    // (L)DMA ahead of read ptr, read data in between the (L)DMA and the read ptr
    if (write_ptr > uart_context->rx_read_ptr) {
      read_size = write_ptr - uart_context->rx_read_ptr;
    }
    // (L)DMA wrapped around RX buffer, read data between read ptr and end of RX buffer
    else {
      read_size = (uart_context->rx_buffer + uart_context->rx_buffer_len) - uart_context->rx_read_ptr;
    }

    // read the smallest amount between the data available and the size of the user buffer
    read_size = buffer_len < read_size ? buffer_len : read_size;
  }

  // Number of bytes written to user buffer can be different if control character are present
  ret_val = read_size;

  // Read data
  {
    CORE_ENTER_ATOMIC();

    // Handle control character and copy data to the user buffer
    if (uart_context->sw_flow_control == true) {
      for (size_t bytes_read = 0; bytes_read < read_size; bytes_read++) {
        // Found control character, update xon
        if (*uart_context->rx_read_ptr == (uint8_t)UARTXON || *uart_context->rx_read_ptr == (uint8_t)UARTXOFF) {
          // Current byte is the most recent scanned byte. Apply control character
          if (uart_context->rx_read_ptr == uart_context->ctrl_char_scan_ptr) {
            sl_atomic_store(uart_context->xon, (*uart_context->rx_read_ptr == (uint8_t)UARTXON));
          }
          ret_val--;
        }
        // No control character, read data and increment user buffer
        else {
          *buffer++ = *uart_context->rx_read_ptr;
        }

        // Caught up to most recent scanned byte, increment the scan ptr
        if (uart_context->rx_read_ptr == uart_context->ctrl_char_scan_ptr) {
          uart_context->ctrl_char_scan_ptr++;
        }

        // Go to next byte
        uart_context->rx_read_ptr++;
      }

      // Wrap ctrl_char_scan_ptr around the rx_buffer
      if (uart_context->ctrl_char_scan_ptr == (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
        uart_context->ctrl_char_scan_ptr = uart_context->rx_buffer;
      }

      EFM_ASSERT(uart_context->ctrl_char_scan_ptr >= uart_context->rx_buffer
                 && uart_context->ctrl_char_scan_ptr < (uart_context->rx_buffer + uart_context->rx_buffer_len));
    }
    // Copy the data to the output buffer
    else {
      memcpy(buffer, uart_context->rx_read_ptr, read_size);
      // Increment rx read ptr
      uart_context->rx_read_ptr += read_size;
    }

    // Wrap rx_read_ptr around
    if (uart_context->rx_read_ptr == (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
      uart_context->rx_read_ptr = uart_context->rx_buffer;
    }

    // Sanity check
    EFM_ASSERT(uart_context->rx_read_ptr >= uart_context->rx_buffer
               && uart_context->rx_read_ptr < (uart_context->rx_buffer + uart_context->rx_buffer_len));
  }

  // Update the ring buffer after read
  update_ring_buffer(uart_context);
  CORE_EXIT_ATOMIC();

  return ret_val;
}
