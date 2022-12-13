/***************************************************************************/ /**
 * @file
 * @brief UART recorder  API implementation.
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
 ******************************************************************************/

#define CURRENT_MODULE_NAME  "SystemView UART recorder"

#include <stddef.h>
#include <stdbool.h>

#include "em_core.h"
#include "sl_uart_recorder.h"
#include "sl_uart_recorder_config.h"
#include "sl_status.h"
#include "sl_iostream.h"
#include "sl_iostream_uart.h"
#include "SEGGER_RTT.h"
#include "SEGGER_SYSVIEW.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "cmsis_os2.h"
#endif

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT) \
    || (defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION)
#include "sl_sleeptimer.h"
#endif

/*******************************************************************************
 *********************************   DEFINES   *********************************
 ******************************************************************************/
#define SERVER_HELLO_MSG_LEN        4
#define TARGET_HELLO_MSG_LEN        4

#define TRANSMIT_BUF_LEN            128
#define RECEIVE_BUF_LEN             16

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// Pointer to iostream uart stream
static sl_iostream_uart_t *uart_stream = NULL;

// Buffer for tx
static uint8_t uart_buf_tx[TRANSMIT_BUF_LEN];

// Buffer for rx
static uint8_t uart_buf_rx[RECEIVE_BUF_LEN];

// Current index where to write in rx buffer.
static uint8_t rx_buf_ix = 0;

// Received byte count for hello message
static bool hello_recvd = false;

// Flag indicating if hello message was sent or not.
static bool hello_sent = false;

// Flag indicating the status of SystemView. Useful to detect a status change.
static bool is_started = false;

// Hello message to send
static const uint8_t hello_msg[TARGET_HELLO_MSG_LEN] = { 'S', 'V', (SEGGER_SYSVIEW_VERSION / 10000), (SEGGER_SYSVIEW_VERSION / 1000) % 10 };  // "Hello" message expected by SysView: [ 'S', 'V', <PROTOCOL_MAJOR>, <PROTOCOL_MINOR> ]

#if defined(SL_CATALOG_KERNEL_PRESENT)
// Semaphore posted when a log happens
static osSemaphoreId_t trace_event_sem;

// Semaphore timeout
static uint32_t semaphore_timeout = SL_SYSTEMVIEW_UART_RECORDER_TASK_RX_PERIOD;

// Id of uart recorder task
static osThreadId_t uart_recorder_task_id;

// Recursion count of notification callback
static uint8_t notify_recursion_cnt = 0;

// Flag indicating if system is in sleep loop
static bool is_system_in_sleep = false;

// Flag indicating if logging occured while sleeping. If yes, will be transmitted at next wake-up
static bool has_logged_while_sleeping = false;
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT) \
    || (defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION)
// Handle on timer that will remove requirement on EM1 on expiration
static sl_sleeptimer_timer_handle_t delayed_pm_req_remove_timer;
#endif

/*******************************************************************************
 **************************   LOCAL FUNCTIONS   ********************************
 ******************************************************************************/

#if defined(SL_CATALOG_KERNEL_PRESENT)
static void uart_recorder_task_handler (void *argument);
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT) \
    || (defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION)
static void delayed_pm_req_remove_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data);
#endif

static bool read_data(void);

static void uart_recorder_process_rx_tx(void);

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize UART recorder module.
 ******************************************************************************/
sl_status_t sl_uart_recorder_init(sl_iostream_uart_t *stream)
{
  EFM_ASSERT(stream != NULL);

  uart_stream = stream;

#if defined(SL_CATALOG_KERNEL_PRESENT)
  osThreadAttr_t task_attr;

  trace_event_sem = osSemaphoreNew(UINT32_MAX, 0, NULL);
  if (trace_event_sem == NULL) {
    return SL_STATUS_FAIL;
  }

  task_attr.name = "SystemView UART Recorder";
  task_attr.priority = SL_SYSTEMVIEW_UART_RECORDER_TASK_PRIORITY;
  task_attr.stack_mem = NULL;
  task_attr.stack_size = SL_SYSTEMVIEW_UART_RECORDER_TASK_STACK_SIZE;
  task_attr.cb_mem = NULL;
  task_attr.cb_size = 0;

  uart_recorder_task_id = osThreadNew(uart_recorder_task_handler, 0, &task_attr);
  if (uart_recorder_task_id == NULL) {
    return SL_STATUS_FAIL;
  }
#endif

#if SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif

  return SL_STATUS_OK;
}

#if defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * Function called when a an event is recorded using SystemView API. This is
 * used to post a semaphore to wake the UART recorder task that transmits the
 * data via UART.
 *
 * @note  If the system is in sleep mode, the semaphore is not posted, as this
 *        would cause a system wake up which would alter the behavior of the
 *        application. Instead, the semaphore will be posted the next time the
 *        application wakes up to EM0 by itself.
 *
 * @note  A mechanism is used to avoid recursive calls of this function. This
 *        happens when the kernel attempts to log an event when the semaphore is
 *        posted.
 ******************************************************************************/
void sli_uart_recorder_notify_event_recorded(void)
{
  if (!is_system_in_sleep) {
    CORE_DECLARE_IRQ_STATE;

    CORE_ENTER_ATOMIC();
    notify_recursion_cnt++;
    if (notify_recursion_cnt == 1 && osThreadGetId() != uart_recorder_task_id) {
      CORE_EXIT_ATOMIC();
      (void)osSemaphoreRelease(trace_event_sem);
    } else {
      CORE_EXIT_ATOMIC();
    }

    CORE_ENTER_ATOMIC();
    notify_recursion_cnt--;
    CORE_EXIT_ATOMIC();
  } else {
    has_logged_while_sleeping = true;
  }
}
#endif

/***************************************************************************//**
 * Reads data from iostream and pushes it to the receive buffer.
 *
 * @return True if something was received, false otherwise.
 ******************************************************************************/
static bool read_data(void)
{
  size_t bytes_read;
  sl_status_t status;

  status = sl_iostream_read(&uart_stream->stream, &uart_buf_rx[rx_buf_ix], RECEIVE_BUF_LEN - rx_buf_ix, &bytes_read);
  if (status == SL_STATUS_OK) {
    rx_buf_ix += bytes_read;
    return true;
  } else {
    return false;
  }
}

#if !defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * SystemView UART recorder process action handler.
 ******************************************************************************/
void sl_uart_recorder_process_action(void)
{
  uart_recorder_process_rx_tx();
}
#endif

#if !defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * Determines if UART recorder is ok to enter sleep.
 ******************************************************************************/
bool sl_uart_recorder_is_ok_to_sleep(void)
{
  return (!read_data());
}
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * UART recorder task handler.
 *
 * @param argument  Task argument.
 ******************************************************************************/
static void uart_recorder_task_handler (void *argument)
{
  osStatus_t os_status;

  (void)argument;

  // Set RX as non blocking
  sl_iostream_uart_set_read_block(uart_stream, false);

  while (1) {
    os_status = osSemaphoreAcquire(trace_event_sem, semaphore_timeout);
    if ((os_status == osOK) || (os_status == osErrorTimeout)) {
      uart_recorder_process_rx_tx();
    }
  }
}
#endif

/***************************************************************************//**
 * SystemView UART recorder process RX/TX actions.
 ******************************************************************************/
static void uart_recorder_process_rx_tx(void)
{
  sl_status_t status;

  read_data();

  // First, receive hello message
  if (!hello_recvd && rx_buf_ix >= SERVER_HELLO_MSG_LEN) {
    hello_recvd = true;

    SEGGER_SYSVIEW_Start();
    is_started = true;
    rx_buf_ix-= SERVER_HELLO_MSG_LEN;

#if defined(SL_CATALOG_KERNEL_PRESENT) \
    || (defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION)
    sl_sleeptimer_start_timer_ms(&delayed_pm_req_remove_timer,
                                 SL_SYSTEMVIEW_UART_RECORDER_RX_ENABLED_DURATION,
                                 delayed_pm_req_remove_timer_callback,
                                 0,
                                 1,
                                 0);
#endif
  }

  if (SEGGER_SYSVIEW_IsStarted()) {
    // Rx
    do {
      // SystemView commands with ID >= 128 have a single digit argument.
      // The state machine in SystemView library doesn't support receiving
      // the 2 bytes separately. This ensures they are passed to the down
      // buffer at the same time.
      if (rx_buf_ix > 0 && (rx_buf_ix == RECEIVE_BUF_LEN || uart_buf_rx[rx_buf_ix - 1] < 128)) {
        SEGGER_RTT_WriteDownBuffer(SEGGER_SYSVIEW_GetChannelID(), uart_buf_rx, rx_buf_ix);
        rx_buf_ix = 0;
      }
    } while (read_data());
  }

  // Tx
  if (SEGGER_SYSVIEW_IsStarted()) {
    if (hello_sent) {
      uint32_t read_cnt;

      do {
        read_cnt = SEGGER_RTT_ReadUpBufferNoLock(SEGGER_SYSVIEW_GetChannelID(), uart_buf_tx, TRANSMIT_BUF_LEN);
        if (read_cnt > 0) {
          status = sl_iostream_write(&uart_stream->stream, uart_buf_tx, read_cnt);
        }
      } while ((status == SL_STATUS_OK) && (read_cnt == TRANSMIT_BUF_LEN));
    } else {
      status = sl_iostream_write(&uart_stream->stream, hello_msg, TARGET_HELLO_MSG_LEN);
      hello_sent = (status == SL_STATUS_OK) ? true : false;
    }
  }

  // If possible (system is not sleeping), detect if SystemView was stopped.
  if (!SEGGER_SYSVIEW_IsStarted() && is_started) {
      hello_recvd = false;
      hello_sent = false;
      is_started = false;

#if defined(SL_CATALOG_KERNEL_PRESENT)
#if SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION && defined(SL_CATALOG_POWER_MANAGER_PRESENT)
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif

      semaphore_timeout = SL_SYSTEMVIEW_UART_RECORDER_TASK_RX_PERIOD;
#endif
  }
}

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && defined(SL_CATALOG_KERNEL_PRESENT)
/***************************************************************************//**
 * Hook provided by the power manager to suspend log transmission when entering
 * sleep mode.
 ******************************************************************************/
void sli_power_manager_suspend_log_transmission(void)
{
  is_system_in_sleep = true;
  has_logged_while_sleeping = false;
}

/***************************************************************************//**
 * Hook provided by the power manager to resume log transmission when leaving
 * sleep mode.
 ******************************************************************************/
void sli_power_manager_resume_log_transmission(void)
{
  is_system_in_sleep = false;
  if (has_logged_while_sleeping) {
    (void)osSemaphoreRelease(trace_event_sem);
  }
}
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT) \
  || (defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION)
/***************************************************************************//**
 * Sleeptimer callback called after a delay specified by
 * SL_SYSTEMVIEW_UART_RECORDER_DELAY_BEFORE_EM1_REMOVE after the connection with
 * SystemView host application has been established. Used to remove the
 * requirement on EM1.
 ******************************************************************************/
static void delayed_pm_req_remove_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  (void)handle;
  (void)data;

#if defined(SL_CATALOG_POWER_MANAGER_PRESENT) && SL_SYSTEMVIEW_UART_RECORDER_PREVENT_SLEEP_BEFORE_CONNECTION
  sl_power_manager_remove_em_requirement(SL_POWER_MANAGER_EM1);
#endif

#if defined(SL_CATALOG_KERNEL_PRESENT)
  semaphore_timeout = osWaitForever;
#endif
}
#endif
