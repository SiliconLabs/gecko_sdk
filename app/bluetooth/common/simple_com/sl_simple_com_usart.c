/***************************************************************************//**
 * @file
 * @brief Simple Communication Interface (UART)
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

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "sl_status.h"
#include "em_common.h"
#include "em_core.h"
#include "sl_uartdrv_instances.h"
#include "app_assert.h"
#include "sl_simple_com.h"
#include "sl_simple_com_config.h"
#if defined(SL_SIMPLE_COM_ROBUST) && SL_SIMPLE_COM_ROBUST == 1
#include "sl_simple_com_robust.h"
#endif // SL_SIMPLE_COM_ROBUST
#ifdef EFR32BG1_USART_E202_WORKAROUND
#include "sl_sleeptimer.h"
#endif // EFR32BG1_USART_E202_WORKAROUND

// Store UARTDRV handle to use with Simple COM
static UARTDRV_Handle_t uartdrv_handle = NULL;
static IRQn_Type irq_number;

// store the maximum waiting time for a callback
static uint32_t time_to_wait_tx_callback = 0;

// store the returned values of TX callback
typedef struct {
  UARTDRV_Handle_t handle;
  uint32_t         timeout;
  sl_status_t      status;
  bool             finished;
} tx_cb_sig;

static tx_cb_sig tx_cb_signal = { 0 };

// UART receive and transmit buffers
static uint8_t rx_buf[SL_SIMPLE_COM_RX_BUF_SIZE] = { 0 };
static uint8_t tx_buf[SL_SIMPLE_COM_TX_BUF_SIZE] = { 0 };

#ifdef EFR32BG1_USART_E202_WORKAROUND
// Internal timer and counter for receive
// EFR32BG1 - USART_E202 workaround
static sl_sleeptimer_timer_handle_t receive_timer;
static uint32_t received_count = 0;
#endif // EFR32BG1_USART_E202_WORKAROUND

// Internal UART receive and transmit callback
static void transmit_cb(UARTDRV_Handle_t handle,
                        Ecode_t transferStatus,
                        uint8_t *data,
                        UARTDRV_Count_t transferCount);
static void receive_cb(UARTDRV_Handle_t handle,
                       Ecode_t transferStatus,
                       uint8_t *data,
                       UARTDRV_Count_t transferCount);
// Helper functions to ensure reception
static Ecode_t cancel_receive(UARTDRV_Handle_t handle);
static Ecode_t get_tail_buffer(UARTDRV_Buffer_FifoQueue_t *queue,
                               UARTDRV_Buffer_t **buffer);
static Ecode_t dequeue_buffer(UARTDRV_Buffer_FifoQueue_t *queue,
                              UARTDRV_Buffer_t **buffer);

static IRQn_Type irq_number_from_handle(UARTDRV_Handle_t handle);

static Ecode_t uart_receive_start(UARTDRV_Handle_t handle);

void sli_simple_com_isr(void);

// -----------------------------------------------------------------------------
// Public functions (API implementation)

/**************************************************************************//**
 * Simple COM initialization function
 *****************************************************************************/
void sl_simple_com_init(void)
{
  // clear RX and TX buffers
  memset(rx_buf, 0, sizeof(rx_buf));
  memset(tx_buf, 0, sizeof(tx_buf));

  // Get the default UARTDRV handle to use for Simple COM
  uartdrv_handle = sl_uartdrv_get_default();
  irq_number = irq_number_from_handle(uartdrv_handle);
  app_assert(irq_number >= (IRQn_Type)(0), "Unknown UARTDRV handle\n");

  // calculate the maximum amount of time to wait for UART TX buffer to empty
  time_to_wait_tx_callback = CMU_ClockFreqGet(cmuClock_CORE)
                             / USART_BaudrateGet(uartdrv_handle->peripheral.uart)
                             * 4;
}

/**************************************************************************//**
 * Simple COM step function
 *****************************************************************************/
void sl_simple_com_step(void)
{
  if (tx_cb_signal.finished) {
    // Wait until UART finished transfer
    if ((!(UARTDRV_GetPeripheralStatus(tx_cb_signal.handle) & UARTDRV_STATUS_TXC))
        && (tx_cb_signal.timeout < time_to_wait_tx_callback)) {
      tx_cb_signal.timeout++;
      sl_simple_com_os_task_proceed();
    } else {
      // Clear TX buffer
      tx_cb_signal.timeout = 0;
      tx_cb_signal.finished = false;
      // Call public callback API
      sl_simple_com_transmit_cb(ECODE_EMDRV_UARTDRV_OK == tx_cb_signal.status
                                ? SL_STATUS_OK : SL_STATUS_FAIL);
    }
  }
}

/**************************************************************************//**
 * UART transmit function
 *
 * Transmits len bytes of data through the UART interface using DMA.
 *
 * @param[out] len Message length
 * @param[out] data Message data
 *****************************************************************************/
void sl_simple_com_transmit(uint32_t len, const uint8_t *data)
{
  Ecode_t ec;
  // Make a copy of the data to be sent to guarantee its integrity until
  // transmission completes
#if defined(SL_SIMPLE_COM_ROBUST) && SL_SIMPLE_COM_ROBUST == 1
  app_assert(sl_simple_com_robust_get_pack_buffer_size(len) <= SL_SIMPLE_COM_TX_BUF_SIZE,
             "TX length is bigger than allocated buffer\n");
  len = sl_simple_com_robust_pack_data(tx_buf, data, (size_t)len);
#else // SL_SIMPLE_COM_ROBUST
  app_assert(len <= SL_SIMPLE_COM_TX_BUF_SIZE,
             "TX length is bigger than allocated buffer\n");
  memcpy((void *)tx_buf, (void *)data, (size_t)len);
#endif // SL_SIMPLE_COM_ROBUST

  // Transmit data using a non-blocking transmit function
  ec = UARTDRV_Transmit(uartdrv_handle,
                        tx_buf,
                        len,
                        transmit_cb);
  app_assert(ECODE_EMDRV_UARTDRV_OK == ec,
             "[E: 0x%04x] Failed to start transmitting\n",
             (int)ec);
  (void)ec;
  sl_simple_com_os_task_proceed();
}

/**************************************************************************//**
 * UART receive function
 *
 * Starts reception on UART interface using DMA.
 *
 * @note The problem with standard UART reception is that it needs the exact
 * amount of bytes to read. This implementation starts a timer to measure idle
 * time on the bus and based on that puts the received message into the buffer.
 *****************************************************************************/
void sl_simple_com_receive(void)
{
  Ecode_t ec;
  // Clear pending RX interrupt flag in NVIC
  NVIC_ClearPendingIRQ(irq_number);
  NVIC_EnableIRQ(irq_number);
  // Setup RX timeout to 255 bit-time
  uartdrv_handle->peripheral.uart->TIMECMP1 = \
    (USART_TIMECMP1_TSTOP_RXACT
     | USART_TIMECMP1_TSTART_RXEOF
     | (0xff << _USART_TIMECMP1_TCMPVAL_SHIFT));
  // Clear any USART interrupt flags
  USART_IntClear(uartdrv_handle->peripheral.uart, _USART_IF_MASK);
  USART_IntEnable(uartdrv_handle->peripheral.uart, USART_IF_TXIDLE | USART_IF_TCMP1);
  ec = uart_receive_start(uartdrv_handle);
  app_assert(ECODE_EMDRV_UARTDRV_OK == ec,
             "[E: 0x%04x] Failed to start receiving\n",
             (int)ec);
  (void)ec;
}

/**************************************************************************//**
 * UART transmit completed callback
 *
 * Called after UART transmit is finished.
 *
 * @param[in] status Status of the transmission
 *
 * @note Weak implementation
 *  Called after DMA is complete, the UART transmission might be still ongoing
 *****************************************************************************/
SL_WEAK void sl_simple_com_transmit_cb(sl_status_t status)
{
  (void)status;
}

/**************************************************************************//**
 * UART receive completed callback
 *
 * Called after UART receive is finished.
 *
 * @param[in] status Status of the reception
 * @param[in] len Received message length
 * @param[in] data Data received
 *
 * @note Weak implementation
 *****************************************************************************/
SL_WEAK void sl_simple_com_receive_cb(sl_status_t status,
                                      uint32_t len,
                                      uint8_t *data)
{
  (void)status;
  (void)data;
  (void)len;
}

// -----------------------------------------------------------------------------
// Private functions

#ifdef EFR32BG1_USART_E202_WORKAROUND
// EFR32BG1 - USART_E202 workaround
static void timer_callback(sl_sleeptimer_timer_handle_t *handle,
                           void *data)
{
  (void)handle;
  (void)data;

  // Assert nRTS
  if (uartdrv_handle->fcType != uartdrvFlowControlHwUart) {
    UARTDRV_FlowControlSet(uartdrv_handle, uartdrvFlowControlOff);
  }

  // Get received bytes
  uint8_t* buffer = NULL;
  uint32_t received = 0;
  uint32_t remaining = 0;
  UARTDRV_GetReceiveStatus(uartdrv_handle, &buffer, &received, &remaining);

  // if no change in that time callback is needed
  if (received_count == received) {
    sl_sleeptimer_stop_timer(&receive_timer);
    CORE_DECLARE_IRQ_STATE;
    CORE_ENTER_ATOMIC();

    // cancel previous block receive operation
    (void)cancel_receive(uartdrv_handle);
    uart_receive_start(uartdrv_handle);
    CORE_EXIT_ATOMIC();
    received_count = 0;
  } else {
    // otherwise register received bytes for the next run
    received_count = received;
  }
}

#endif // EFR32BG1_USART_E202_WORKAROUND

/******************************************************************************
 * UART interrupt handler
 *
 * Called when the set timer for tx idle states finished.
 *
 * @note automatically restarts the timer and starts a new reception.
 * @note TODO: this should be provided by UARTDRV
 *****************************************************************************/
void sli_simple_com_isr(void)
{
  // RX timeout, stop transfer and handle what we got in buffer
  if (uartdrv_handle->peripheral.uart->IF & USART_IF_TCMP1) {
    CORE_DECLARE_IRQ_STATE;

    // Assert nRTS
    if (uartdrv_handle->fcType != uartdrvFlowControlHwUart) {
      UARTDRV_FlowControlSet(uartdrv_handle, uartdrvFlowControlOff);
    }

    CORE_ENTER_ATOMIC();
    // stop the timer
    uartdrv_handle->peripheral.uart->TIMECMP1 &= \
      ~_USART_TIMECMP1_TSTART_MASK;
    uartdrv_handle->peripheral.uart->TIMECMP1 |= \
      USART_TIMECMP1_TSTART_RXEOF;
    // clear timer interrupt
    USART_IntClear(uartdrv_handle->peripheral.uart,
                   USART_IF_TCMP1);
#ifdef EFR32BG1_USART_E202_WORKAROUND
    // EFR32BG1 - USART_E202 workaround
    sl_sleeptimer_stop_timer(&receive_timer);
    sl_sleeptimer_start_periodic_timer(
      &receive_timer,
      sl_sleeptimer_ms_to_tick(1),
      timer_callback,
      NULL,
      0,
      0);
    uint8_t* buffer = NULL;
    uint32_t received = 0;
    uint32_t remaining = 0;
    UARTDRV_GetReceiveStatus(uartdrv_handle, &buffer, &received, &remaining);
    received_count = received;
#else
    // cancel previous block receive operation
    (void)cancel_receive(uartdrv_handle);
    uart_receive_start(uartdrv_handle);
#endif // EFR32BG1_USART_E202_WORKAROUND
    CORE_EXIT_ATOMIC();
  }
}

/******************************************************************************
 * Internal UART transmit completed callback
 *
 * Called after UART transmit is finished.
 *
 * @param[in] handle UART driver handle
 * @param[in] transferStatus Status of the transfer
 * @param[in] data Transmitted data
 * @param[in] transferCount Number of sent bytes
 *
 * @note Calls public sl_simple_com_transmit_cb
 *  Called after DMA is complete, the UART transmission might be still ongoing
 *****************************************************************************/
static void transmit_cb(UARTDRV_Handle_t handle,
                        Ecode_t transferStatus,
                        uint8_t *data,
                        UARTDRV_Count_t transferCount)
{
  (void)data;
  (void)transferCount;

  CORE_ATOMIC_SECTION(
    tx_cb_signal.status = transferStatus;
    tx_cb_signal.handle = handle;
    tx_cb_signal.timeout = 0;
    tx_cb_signal.finished = true;
    )
  sl_simple_com_os_task_proceed();
}

/******************************************************************************
 * Internal UART receive completed callback
 *
 * Called after UART receive is finished.
 *
 * @param[in] handle UART driver handle
 * @param[in] transferStatus Status of the transfer
 * @param[in] data Received data
 * @param[in] transferCount Number of received bytes
 *
 * @note Calls public sl_simple_com_receive_cb
 *****************************************************************************/
static void receive_cb(UARTDRV_Handle_t handle,
                       Ecode_t transferStatus,
                       uint8_t *data,
                       UARTDRV_Count_t transferCount)
{
  (void)handle;

#if defined(SL_SIMPLE_COM_ROBUST) && SL_SIMPLE_COM_ROBUST == 1
  if (transferCount > 0) {
    sl_simple_com_robust_result_t result = sl_simple_com_robust_unpack_data(data,
                                                                            transferCount);

    // Call public callback API
    sl_simple_com_receive_cb((ECODE_EMDRV_UARTDRV_OK == transferStatus
                              ? SL_STATUS_OK : SL_STATUS_FAIL | result.status),
                             result.payload_size,
                             result.payload);
  } else {
#else // SL_SIMPLE_COM_ROBUST
  {
#endif // SL_SIMPLE_COM_ROBUST
    // Call public callback API
    sl_simple_com_receive_cb(ECODE_EMDRV_UARTDRV_OK == transferStatus
                             ? SL_STATUS_OK : SL_STATUS_FAIL,
                             transferCount,
                             data);
  }

  sl_simple_com_os_task_proceed();
}

/******************************************************************************
 * Cancel previous block receive operation.
 *
 * @param[in] handle UART driver handle
 *****************************************************************************/
static Ecode_t cancel_receive(UARTDRV_Handle_t handle)
{
  UARTDRV_Buffer_t *rxBuffer;
  Ecode_t status;
  CORE_DECLARE_IRQ_STATE;

  if (handle == NULL) {
    return ECODE_EMDRV_UARTDRV_ILLEGAL_HANDLE;
  }

  CORE_ENTER_ATOMIC();
  if (handle->rxQueue->used == 0) {
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_IDLE;
  }

  // -------------------------------
  // Stop the current DMA transfer
  (void)DMADRV_StopTransfer(handle->rxDmaCh);
  handle->rxDmaActive = false;
  // Update the transfer status of the active transfer
  status = get_tail_buffer(handle->rxQueue, &rxBuffer);
  // If aborting was in progress when DMA completed, the ISR could be deferred
  // until after the critical section. In this case, the buffers no longer
  // exist, even though the DMA complete callback was called.
  if (status == ECODE_EMDRV_UARTDRV_QUEUE_EMPTY) {
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  EFM_ASSERT(rxBuffer != NULL);
  (void)DMADRV_TransferRemainingCount(handle->rxDmaCh,
                                      (int *)&rxBuffer->itemsRemaining);
  rxBuffer->transferStatus = ECODE_EMDRV_UARTDRV_ABORTED;

  // -------------------------------
  // Dequeue all transfers and call callback
  while (handle->rxQueue->used > 0) {
    (void)dequeue_buffer(handle->rxQueue, &rxBuffer);
    // Call the callback
    if (rxBuffer->callback != NULL) {
      if (rxBuffer->callback != NULL) {
        rxBuffer->callback(handle,
                           ECODE_EMDRV_UARTDRV_OK,
                           rxBuffer->data,
                           rxBuffer->transferCount - rxBuffer->itemsRemaining);
      }
    }
  }

  // -------------------------------
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_UARTDRV_OK;
}

/******************************************************************************
 * Gets the buffer tail.
 *
 * @param[in] queue Input buffer
 * @param[out] buffer Output buffer
 *****************************************************************************/
static Ecode_t get_tail_buffer(UARTDRV_Buffer_FifoQueue_t *queue,
                               UARTDRV_Buffer_t **buffer)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  if (queue->used == 0) {
    *buffer = NULL;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  *buffer = &queue->fifo[queue->tail];

  CORE_EXIT_ATOMIC();
  return ECODE_EMDRV_UARTDRV_OK;
}

/******************************************************************************
 * Dequeues buffer
 *
 * Moves through the buffer.
 *
 * @param[in] queue Input buffer
 * @param[out] buffer Output buffer
 *****************************************************************************/
static Ecode_t dequeue_buffer(UARTDRV_Buffer_FifoQueue_t *queue,
                              UARTDRV_Buffer_t **buffer)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  if (queue->used == 0) {
    *buffer = NULL;
    CORE_EXIT_ATOMIC();
    return ECODE_EMDRV_UARTDRV_QUEUE_EMPTY;
  }
  *buffer = &queue->fifo[queue->tail];
  queue->tail = (queue->tail + 1) % queue->size;
  queue->used--;
  CORE_EXIT_ATOMIC();

  return ECODE_EMDRV_UARTDRV_OK;
}

/******************************************************************************
 * Get NVIC IRQ number from UARTDRV handle
 *
 * @param[in] handle UART driver handle
 * @return Interrupt number
 *****************************************************************************/
static IRQn_Type irq_number_from_handle(UARTDRV_Handle_t handle)
{
  IRQn_Type irq_number = (IRQn_Type)(-1);

  switch ((uint32_t)handle->peripheral.uart) {
#if defined(USART0_BASE)
    case USART0_BASE:
      irq_number = USART0_RX_IRQn;
      break;
#endif
#if defined(USART1_BASE)
    case USART1_BASE:
      irq_number = USART1_RX_IRQn;
      break;
#endif
#if defined(USART2_BASE)
    case USART2_BASE:
      irq_number = USART2_RX_IRQn;
      break;
#endif
#if defined(USART3_BASE)
    case USART3_BASE:
      irq_number = USART3_RX_IRQn;
      break;
#endif
    default:
      app_assert(false, "Unknown UARTDRV handle\n");
      break;
  }

  return irq_number;
}

/******************************************************************************
 * Start / resume UARTDRV receiving
 *
 * @param[in] handle UART driver handle
 * @return UARTDRV reported result of the operation
 *****************************************************************************/
static Ecode_t uart_receive_start(UARTDRV_Handle_t handle)
{
  Ecode_t ec = UARTDRV_Receive(handle, rx_buf, sizeof(rx_buf), receive_cb);

  if (ec == ECODE_EMDRV_UARTDRV_OK) {
    // De-assert nRTS or send XON
    if (uartdrv_handle->fcType != uartdrvFlowControlHwUart) {
      UARTDRV_FlowControlSet(uartdrv_handle, uartdrvFlowControlAuto);
    }
  }

  return ec;
}
/******************************************************************************
 * Function to trigger the OS task to proceed
 *
 * @note Weak implementation.
 *****************************************************************************/
SL_WEAK void sl_simple_com_os_task_proceed(void)
{
  // No action on bare metal implementation
}
