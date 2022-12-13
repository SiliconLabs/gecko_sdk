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
static bool is_ok_to_sleep(void *context);
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
                                     size_t buffer_length,
                                     bool no_wait);

static bool uart_handle_rx_dma_complete(unsigned int chan,
                                        unsigned int seq,
                                        void* user_param);

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
  context->dma.data_available = false;
  context->rx_buffer = config->rx_buffer;
  context->rx_buffer_len = config->rx_buffer_length;
  context->read_ptr = context->rx_buffer;
  context->lf_to_crlf = config->lf_to_crlf;
  context->sw_flow_control = config->sw_flow_control;
  context->ctrl_char_scan_ptr = context->read_ptr;
  context->xon = true;
  context->remote_xon = true;
  context->tx = tx;
  context->tx_completed = tx_completed;
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
  uart->is_ok_to_sleep = is_ok_to_sleep;
  context->sleep = SL_POWER_MANAGER_IGNORE;
#endif
  uart->set_rx_energy_mode_restriction = set_rx_energy_mode_restriction;
  uart->get_rx_energy_mode_restriction = get_rx_energy_mode_restriction;
  context->tx_em = (sl_power_manager_em_t)tx_em_req;
  context->rx_em = (sl_power_manager_em_t)rx_em_req;
  context->em_req_added = false;
  context->tx_idle = true;
  set_rx_energy_mode_restriction(context, config->rx_when_sleeping);
  NVIC_ClearPendingIRQ(config->tx_irq_number);
  NVIC_EnableIRQ(config->tx_irq_number);
#endif

  //Enable the DMA for 1 byte to detect if data is available
  context->dma.active_desc.dst = context->rx_buffer;
  context->dma.active_desc.count = 1;
  context->read_ptr = context->rx_buffer;
  ecode = DMADRV_PeripheralMemory(context->dma.channel,
                                  context->dma.cfg.peripheral_signal,
                                  context->dma.active_desc.dst,
                                  context->dma.cfg.src,
                                  true,
                                  1,
                                  context->dma.cfg.size,
                                  uart_handle_rx_dma_complete,
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

/**************************************************************************//**
 * @brief   Checks if IOStream is ready for sleep.
 *****************************************************************************/
static bool is_ok_to_sleep(void *context)
{
  bool dma_active;
  Ecode_t ecode;
  size_t xfercnt;
  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t *)context;
  unsigned int channel = uart_context->dma.channel;

  // Pause transfer for safety when checking DMA status
  ecode = DMADRV_PauseTransfer(channel);
  EFM_ASSERT(ecode == ECODE_OK);
  ecode = DMADRV_TransferActive(channel, &dma_active);
  EFM_ASSERT(ecode == ECODE_OK);

  {
    // DMA is stopped, need to read data from IOStream or data will be dropped and new data will not
    // wakeup the core.
    if (dma_active == false) {
      // Call resume transfer even if the DMA is inactive, or else it won't be resumed
      // at the next start.
      ecode = DMADRV_ResumeTransfer(channel);
      EFM_ASSERT(ecode == ECODE_OK);
      return false;
    }
  }

  // DMA is active. Arm it for a single byte to be able to detect new data.
  {
    // Stop the DMA
    ecode = DMADRV_StopTransfer(channel);
    EFM_ASSERT(ecode == ECODE_OK);

    #if defined(LDMA_PRESENT)
    xfercnt = 1 + ((LDMA->CH[channel].CTRL & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);
    #elif defined(DMA_PRESENT)
    xfercnt = 1 + ((DMA->CH[channel].CTRL & _DMA_CTRL_N_MINUS_1_MASK) >> _DMA_CTRL_N_MINUS_1_SHIFT);
    #endif

    // Advance the DMA by the number of bytes already received
    EFM_ASSERT(xfercnt <= uart_context->dma.active_desc.count);
    xfercnt = (uart_context->dma.active_desc.count - xfercnt);
    uart_context->dma.active_desc.dst += xfercnt;

    // Arm for a single byte tranfer to detect next byte
    uart_context->dma.active_desc.count = 1;
    xfercnt = uart_context->dma.active_desc.count; // Needed to avoid volatile access warning with IAR

    // Prep the DMA
    ecode = DMADRV_PeripheralMemory(channel,
                                    uart_context->dma.cfg.peripheral_signal,
                                    uart_context->dma.active_desc.dst,
                                    uart_context->dma.cfg.src,
                                    true,
                                    xfercnt,
                                    uart_context->dma.cfg.size,
                                    uart_handle_rx_dma_complete,
                                    uart_context
                                    );
    EFM_ASSERT(ecode == ECODE_OK);
  }
  // Resume the transfer
  ecode = DMADRV_ResumeTransfer(channel);
  EFM_ASSERT(ecode == ECODE_OK);
  return true;
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
      if (uart_context->dma.data_available == true) {
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
  DMADRV_DeInit();

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
  uint8_t *write_ptr;
  int remaining;
  Ecode_t ecode;
  size_t len;

  char *control_char = NULL;
  char *xon = NULL;
  char *xoff = NULL;

  if (uart_context->dma.data_available == false) {
    EFM_ASSERT(uart_context->ctrl_char_scan_ptr == uart_context->read_ptr);
    return;
  }

  ecode = DMADRV_TransferRemainingCount(uart_context->dma.channel, &remaining);
  EFM_ASSERT(ecode == ECODE_OK);

  // When DMA is full, check only the newest character for a ctrl char.
  if (uart_context->dma.active_desc.count == 0) {
    // The newest character is the one just behind the write_ptr
    uint8_t *newest_byte;
    write_ptr = uart_context->dma.active_desc.dst;
    if (write_ptr == uart_context->rx_buffer) {
      newest_byte = uart_context->rx_buffer + uart_context->rx_buffer_len;
    } else {
      newest_byte = write_ptr - 1;
    }

    if (*newest_byte == UARTXON) {
      uart_context->xon = true;
    } else if (*newest_byte == UARTXOFF) {
      uart_context->xon = false;
    }
  }
  // When DMA is not full, scan all data between the write_ptr and the scan_ptr
  else {
    write_ptr = uart_context->dma.active_desc.dst;
    write_ptr += (uart_context->dma.active_desc.count - remaining);

    while (write_ptr != uart_context->ctrl_char_scan_ptr) {
      if (write_ptr > uart_context->ctrl_char_scan_ptr) {
        // [   RX Data |  ]
        //    ^         ^
        // scan_ptr   write_ptr
        // Scan between write_ptr and scan_ptr
        len = write_ptr - uart_context->ctrl_char_scan_ptr;
        xon = (char*) sl_memrchr(uart_context->ctrl_char_scan_ptr, (char) UARTXON, len);
        xoff = (char*) sl_memrchr(uart_context->ctrl_char_scan_ptr, (char) UARTXOFF, len);
        write_ptr = uart_context->ctrl_char_scan_ptr;
      } else {
        // [Newest Data  | Oldest Data ]
        //            ^            ^
        //    write_ptr     scan_ptr
        // Scan between write_ptr and rx_buffer origin
        len = write_ptr - uart_context->rx_buffer;
        xon = (char*) sl_memrchr(uart_context->rx_buffer, (char) UARTXON, len);
        xoff = (char*) sl_memrchr(uart_context->rx_buffer, (char) UARTXOFF, len);
        write_ptr = uart_context->rx_buffer + uart_context->rx_buffer_len;
      }

      // Process the ctrl char if found
      if (xon != NULL) {
        control_char = xon;
      }
      if (xoff != NULL) {
        if (xon != NULL) {
          // Found two ctrl characters, get the more recent one
          control_char = xon > xoff ? xon : xoff;
        } else {
          control_char = xoff;
        }
      }

      if (control_char != NULL) {
        // Make the most recent control character active
        uart_context->xon = control_char == xon ? true : false;
        break;
      }
    }
  }

  // Set ctrl_char_scan_end_ptr to the most recent received byte, to avoid
  // re-scanning the same area on subsequent call
  uart_context->ctrl_char_scan_ptr = uart_context->dma.active_desc.dst;
  uart_context->ctrl_char_scan_ptr += (uart_context->dma.active_desc.count - remaining);
  // Wrap the ctrl_char_scan_ptr around
  if (uart_context->ctrl_char_scan_ptr >= (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
    uart_context->ctrl_char_scan_ptr = uart_context->rx_buffer + (uart_context->ctrl_char_scan_ptr
                                                                  - (uart_context->rx_buffer + uart_context->rx_buffer_len));
  }
}

/***************************************************************************//**
 * Internal stream write implementation
 ******************************************************************************/
static sl_status_t nolock_uart_write(void *context,
                                     const void *buffer,
                                     size_t buffer_length,
                                     bool no_wait)
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
    if (no_wait) {
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
    } else {
      bool xon = false;
      if (uart_context->sw_flow_control == true) {
        CORE_ENTER_ATOMIC();
        scan_for_ctrl_char(uart_context);
        CORE_EXIT_ATOMIC();
      }
      sl_atomic_load(xon, uart_context->xon);
      if (xon || no_wait) {
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
      }       // Active wait if xon is false
    }
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

  nolock_uart_write(context, buffer, buffer_length, false);

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
      return SL_STATUS_INVALID_STATE; // Can happen if a task deinit and another try to read at sametime
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
 * DMA complete interrupt handle.
 ******************************************************************************/
static bool uart_handle_rx_dma_complete(unsigned int chan, unsigned int seq, void* user_param)
{
  // Finished the Periph->mem xfer, re-arm the dma for the next available descriptor
  (void) seq;
  Ecode_t ecode;
  uint8_t *write_ptr;
  uint8_t *dst;
  size_t count;

  sl_iostream_uart_context_t *uart_context = (sl_iostream_uart_context_t*)user_param;
  #if defined(SL_CATALOG_KERNEL_PRESENT)
  bool unlock_read = false;
  #elif defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  // Wakeup from sleep to give a chance to the system to read the available data. If the
  // data isn't entirely read, the system will go back to sleep.
  uart_context->sleep = SL_POWER_MANAGER_WAKEUP;
  #endif

  // Check that active descriptor was valid
  EFM_ASSERT((uart_context->dma.active_desc.dst >= uart_context->rx_buffer)
             && (uart_context->dma.active_desc.dst < (uart_context->rx_buffer + uart_context->rx_buffer_len)));

  // Check if this is the first byte detection descriptor
  if (uart_context->dma.data_available == false) {
    // Detected first byte, go to next byte
    uart_context->dma.active_desc.dst += 1;
    uart_context->dma.active_desc.count -= 1;

    // Set the data_available flag
    uart_context->dma.data_available = true;
    #if defined(SL_CATALOG_KERNEL_PRESENT)
    unlock_read = true;
    #endif
  }
  // Reached the end of the active descriptor, check for available space from the read_ptr
  // Calculate write_ptr
  write_ptr = uart_context->dma.active_desc.dst;
  write_ptr += uart_context->dma.active_desc.count;

  // Check for overflow
  EFM_ASSERT(write_ptr >= uart_context->rx_buffer
             && write_ptr <= (uart_context->rx_buffer + uart_context->rx_buffer_len));

  if (write_ptr == (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
    // DMA Reached the end of the UART RX Buffer
    // [Obselte data | Oldest data ]
    //                ^             ^
    //         read_ptr     write_ptr
    // Start a transfer from rx_buffer to read_ptr
    uart_context->dma.active_desc.dst = uart_context->rx_buffer;
    uart_context->dma.active_desc.count = (size_t)(uart_context->read_ptr - uart_context->rx_buffer);
  } else if (write_ptr <= uart_context->read_ptr) {
    // DMA stopped while behind the read_ptr
    // [Newest Data | Oldest Data]
    //            ---^
    //       write_ptr
    //        read_ptr
    // Start a tranfer from write_ptr to read_ptr
    uart_context->dma.active_desc.dst = write_ptr;
    uart_context->dma.active_desc.count = uart_context->read_ptr - write_ptr;
  } else {
    // DMA stopped while ahead of read_ptr
    // [Valid Data | Obselete Data]
    //  ^           ^
    //  read_ptr    write_ptr
    // Start a tranfer from write_ptr to the end of the rx_buffer
    uart_context->dma.active_desc.dst = write_ptr;
    uart_context->dma.active_desc.count = (uart_context->rx_buffer + uart_context->rx_buffer_len) - write_ptr;
  }
  write_ptr = uart_context->dma.active_desc.dst;
  write_ptr += uart_context->dma.active_desc.count;
  EFM_ASSERT(write_ptr >=  uart_context->rx_buffer
             && write_ptr <= (uart_context->rx_buffer + uart_context->rx_buffer_len));

  // This means we just filled up the DMA. In SWFlowControl, make sure there is always at least one
  // byte available in the DMA to detect any SWFlowControl characters received from the remote.
  if (uart_context->sw_flow_control == true && uart_context->dma.active_desc.count == 0) {
    // DMA is full, send the first UARTXOFF.
    // If more data is received and the peripheral's FIFO overflows, additionnal
    // UARTXOFFs will be sent in the peripheral's IRQ handler
    sl_atomic_store(uart_context->remote_xon, false);
    char c = UARTXOFF;
    nolock_uart_write(uart_context, &c, sizeof(c), true);

    // Set the DMA to overwrite the last received character, so that we can always
    // receive a control character
    if (uart_context->dma.active_desc.dst == uart_context->rx_buffer) {
      // dst just wrapped around the buffer
      dst = uart_context->rx_buffer + (uart_context->rx_buffer_len - 1);
    } else {
      dst = uart_context->dma.active_desc.dst - 1;
    }

    count = 1;
    ecode = DMADRV_PeripheralMemory(chan,
                                    uart_context->dma.cfg.peripheral_signal,
                                    dst,
                                    uart_context->dma.cfg.src,
                                    true,
                                    count,
                                    uart_context->dma.cfg.size,
                                    uart_handle_rx_dma_complete,
                                    uart_context
                                    );
    EFM_ASSERT(ecode == ECODE_OK);
  }
  // Start the next transfer, if available
  else if (uart_context->dma.active_desc.count > 0) {
    dst = uart_context->dma.active_desc.dst;
    count = uart_context->dma.active_desc.count;
    ecode = DMADRV_PeripheralMemory(chan,
                                    uart_context->dma.cfg.peripheral_signal,
                                    dst,
                                    uart_context->dma.cfg.src,
                                    true,
                                    count,
                                    uart_context->dma.cfg.size,
                                    uart_handle_rx_dma_complete,
                                    uart_context
                                    );
    EFM_ASSERT(ecode == ECODE_OK);

    if (uart_context->sw_flow_control == true) {
      if (uart_context->remote_xon == false) {
        // UART was in UARTXOFF state, send UARTXON
        sl_atomic_store(uart_context->remote_xon, true);
        char c = UARTXON;
        nolock_uart_write(uart_context, &c, sizeof(c), true);
      }
    }
  }

  #if defined(SL_CATALOG_KERNEL_PRESENT)
  // Release the semaphore to unlock the read_thread.
  if (uart_context->block == true && unlock_read == true) {
    osKernelState_t state = osKernelGetState();
    osStatus_t status;
    if ((state == osKernelRunning) || (state == osKernelLocked)) {
      status = osSemaphoreRelease(uart_context->read_signal);
      EFM_ASSERT(status == osOK);
    }
  }
  #endif

  return true;
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

  if (uart_context->dma.data_available == false) {
    #if defined(SL_CATALOG_KERNEL_PRESENT)
    if (uart_context->block) {
      EFM_ASSERT(false); // Should always have data in blocking mode
    }
    #endif
    return 0;
  }

  uint8_t *write_ptr;
  bool dma_inactive;
  int remaining;
  Ecode_t ecode;
  uint8_t *dst;
  size_t count;

  unsigned int channel = uart_context->dma.channel;
  size_t read_size = 0;
  size_t num_bytes_available = 0;

  uint8_t *read_start = uart_context->read_ptr;
  // Get tranfer remaining from DMADRV
  ecode = DMADRV_PauseTransfer(channel);   // Pause for safety
  EFM_ASSERT(ecode == ECODE_OK);
  ecode = DMADRV_TransferRemainingCount(channel, &remaining);
  EFM_ASSERT(ecode == ECODE_OK);
  ecode = DMADRV_TransferDone(channel, &dma_inactive);
  EFM_ASSERT(ecode == ECODE_OK);

  // Calculate write_ptr
  write_ptr = uart_context->dma.active_desc.dst;
  write_ptr += (uart_context->dma.active_desc.count - remaining);

  // Calculate the number of bytes available for read
  if (write_ptr > read_start) {
    num_bytes_available = write_ptr - read_start;
  } else {
    num_bytes_available = (uart_context->rx_buffer + uart_context->rx_buffer_len) - read_start;
  }

  EFM_ASSERT(num_bytes_available > 0);

  // Calculate size of read in this iteration
  if (num_bytes_available > buffer_len) {
    // User buffer not big enough to read all data, data will still be available after read
    read_size = buffer_len;
  } else {
    // User buffer big enough to read all data in this iteration
    read_size = num_bytes_available;
  }

  // Update the DMA to reuse the available space
  if (dma_inactive) {
    if (write_ptr == (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
      // DMA stopped at the end of the buffer
      // [Obselete data | Newest Data]
      //                 ^           ^
      //          read_start   write_ptr
      // Start a transfer over the obselete data
      uart_context->dma.active_desc.dst = uart_context->rx_buffer;
      uart_context->dma.active_desc.count = (size_t)(read_start - uart_context->rx_buffer) + read_size;
      write_ptr = uart_context->dma.active_desc.dst;
    } else if (write_ptr <= read_start) {
      // DMA stopped while writing behind the read_start.
      // [Newest Data | Oldest Data]
      //             ^ ^
      //     write_ptr read_start
      // Start a transfer from the write_ptr to the read_start
      uart_context->dma.active_desc.dst = write_ptr;
      uart_context->dma.active_desc.count = read_size;
      write_ptr = uart_context->dma.active_desc.dst;
    } else if (write_ptr > read_start
               && write_ptr < (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
      // DMA stopped while writing ahead the read_start.
      // [Newest Data|Obselete data]
      //  ^           ^
      //  read_start  write_ptr
      // Start a transfer from the write_ptr to the end of the rx_buffer
      uart_context->dma.active_desc.dst = write_ptr;
      uart_context->dma.active_desc.count = (uart_context->rx_buffer + uart_context->rx_buffer_len)
                                            - write_ptr;
      write_ptr = uart_context->dma.active_desc.dst;
    } else {
      // DMA stopped in an unkown location
      EFM_ASSERT(0);
    }

    // Just read data, should always have at least 1 byte available
    EFM_ASSERT(uart_context->dma.active_desc.count > 0);

    // Prepare the next transfer
    dst = uart_context->dma.active_desc.dst;
    count = uart_context->dma.active_desc.count;
    ecode = DMADRV_PeripheralMemory(channel,
                                    uart_context->dma.cfg.peripheral_signal,
                                    dst,
                                    uart_context->dma.cfg.src,
                                    true,
                                    count,
                                    uart_context->dma.cfg.size,
                                    uart_handle_rx_dma_complete,
                                    uart_context
                                    );
    EFM_ASSERT(ecode == ECODE_OK);

    if (uart_context->sw_flow_control == true) {
      if (uart_context->remote_xon == false) {
        sl_atomic_store(uart_context->remote_xon, true);
        char c = UARTXON;
        nolock_uart_write(uart_context, &c, sizeof(c), true);
      }
    }
  } else {
    // DMA is active.
    if (write_ptr < read_start) {
      // DMA is active and behind the read_start
      // [ Newest Data | Oldest Data]
      //              ^ ^
      //      write_ptr read_start
      // Update the DMA registers and active_descriptor to use the new space
      uart_context->dma.active_desc.count += read_size;

      size_t xfercnt;
    #if defined(LDMA_PRESENT)
      xfercnt = (LDMA->CH[channel].CTRL & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT;
      xfercnt += read_size;
      // Check for overflow
      EFM_ASSERT((uintptr_t)(LDMA->CH[channel].DST + xfercnt)
                 < (uintptr_t)(uart_context->rx_buffer + uart_context->rx_buffer_len));
      LDMA->CH[channel].CTRL &= ~_LDMA_CH_CTRL_XFERCNT_MASK;
      LDMA->CH[channel].CTRL |= xfercnt << _LDMA_CH_CTRL_XFERCNT_SHIFT;
    #elif defined(DMA_PRESENT)
      xfercnt = (DMA->CH[channel].CTRL & _DMA_CTRL_N_MINUS_1_MASK) >> _DMA_CTRL_N_MINUS_1_SHIFT;
      xfercnt += read_size;
      DMA->CH[channel].CTRL &= ~_DMA_CTRL_N_MINUS_1_MASK;
      DMA->CH[channel].CTRL |= xfercnt << _DMA_CTRL_N_MINUS_1_SHIFT;
    #endif
    } else if (write_ptr == read_start) {
      // This means the DMA should have been stopped
      EFM_ASSERT(0);
    } // else, nothing to do since the DMA is already primed.
  }

  // Move read_ptr to the end of the current read
  if ((read_start + read_size) >= (uart_context->rx_buffer + uart_context->rx_buffer_len)) {
    uart_context->read_ptr = (read_start + read_size) - uart_context->rx_buffer_len;
  } else {
    uart_context->read_ptr += read_size;
  }

  // This means all of the data has been read from the rx_buffer
  if (uart_context->read_ptr == write_ptr) {
    // Reset first byte detection.
    uart_context->dma.data_available = false;

    // Update the active descriptor to use the available space
    uart_context->dma.active_desc.dst = write_ptr;

    // Start a single byte tranfer to detect first byte
    uart_context->dma.active_desc.count = 1;
    ecode = DMADRV_StopTransfer(channel);
    EFM_ASSERT(ecode == ECODE_OK);
    dst = uart_context->dma.active_desc.dst;
    count = uart_context->dma.active_desc.count;
    ecode = DMADRV_PeripheralMemory(channel,
                                    uart_context->dma.cfg.peripheral_signal,
                                    dst,
                                    uart_context->dma.cfg.src,
                                    true,
                                    count,
                                    uart_context->dma.cfg.size,
                                    uart_handle_rx_dma_complete,
                                    uart_context
                                    );
    EFM_ASSERT(ecode == ECODE_OK);
    if (uart_context->sw_flow_control == true) {
      if (uart_context->remote_xon == false) {
        sl_atomic_store(uart_context->remote_xon, true);
        char c = UARTXON;
        nolock_uart_write(uart_context, &c, sizeof(c), true);
      }
    }
  } else {
    // This means there is still data to be served to the user from rx_buffer
    uart_context->dma.data_available = true;

    #if defined(SL_CATALOG_KERNEL_PRESENT)
    // Release the semaphore to unlock the next read
    if (uart_context->block == true) {
      osKernelState_t state = osKernelGetState();
      osStatus_t status;
      if ((state == osKernelRunning) || (state == osKernelLocked)) {
        status = osSemaphoreRelease(uart_context->read_signal);
        EFM_ASSERT(status == osOK);
      }
    }
    #endif
  }

  // Scan for control characters in the read data
  if (uart_context->sw_flow_control == true) {
    uint8_t* ctrl_char = NULL;
    size_t num_ctrl_char = 0;

    for (size_t i = 0; i < read_size; i++) {
      // Check if the character at read_ptr[i] is a ctrl_char
      ctrl_char = read_start[i] == UARTXON ? &read_start[i] : NULL;
      ctrl_char = read_start[i] == UARTXOFF ? &read_start[i] : ctrl_char;

      if (ctrl_char != NULL) {
        num_ctrl_char++;
        // Control char found. Check if it is the newest.
        if (read_start <= uart_context->ctrl_char_scan_ptr
            && ctrl_char >= uart_context->ctrl_char_scan_ptr) {
          // Newest control character found, make it active
          uart_context->xon = (*ctrl_char == UARTXON);
        } // Else, the control character was already processed in a scan_for_ctrl_char call,
          // since the ctrl_scan_ptr was wrapped behind the read_start or it was farther than
          // the detected ctrl_char.
      } else {
        // No control character found, write data to user buffer
        buffer[i] = read_start[i];
      }
    }

    // Check if ctrl_char_scan_ptr was passed in this scan
    if (read_start <= uart_context->ctrl_char_scan_ptr
        && (read_start + read_size) > uart_context->ctrl_char_scan_ptr) {
      // Update the ctrl_char_scan to the end the section that was just read
      uart_context->ctrl_char_scan_ptr = uart_context->read_ptr;
    }

    // Decrease read_size since the control characters are not written to user buffer
    read_size -= num_ctrl_char;
  } else {
    // Write RX Data to the user buffer
    memcpy(buffer, read_start, read_size);
  }

  // Finished updating the descriptor, resume the transfer
  ecode = DMADRV_ResumeTransfer(channel);
  EFM_ASSERT(ecode == ECODE_OK);

  return read_size;
}
