/***************************************************************************//**
 * @brief Adaptation for running Bluetooth in RTOS
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cmsis_os2.h>
#include "em_core.h"
#include "sl_bluetooth.h"
#include "sl_bt_stack_config.h"
#include "sl_bt_rtos_config.h"
#include "sl_bt_rtos_adaptation.h"
#include "sl_component_catalog.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif // CONFIGURATION_HEADER

// Definitions for Bluetooth state flags that are needed already before the RTOS
// kernel has been started, i.e. if the application calls
// `sl_bt_system_start_bluetooth()` from `app_init()`. These flags are used with
// the static state variable `bluetooth_state_flags`.
#define SLI_BT_RTOS_STATE_FLAG_KERNEL_STARTED  0x01U  // The RTOS kernel has been started
#define SLI_BT_RTOS_STATE_FLAG_STARTING        0x02U  // The Bluetooth stack is starting
#define SLI_BT_RTOS_STATE_FLAG_STARTED         0x04U  // The Bluetooth stack has successfully started
#define SLI_BT_RTOS_STATE_FLAG_STOPPING        0x08U  // The Bluetooth stack is stopping

// The event flags defined below are specific to a thread and are used with the
// thread context's `event_flags` field. The values would not necessarily need
// to be unique between threads. We still choose unique values to make it easier
// to detect if a flag of one thread is accidentally used with another.

// Common event flags used with @ref wait_bluetooth_rtos_thread_event_flags
#define SLI_BT_RTOS_EVENT_FLAG_ERROR                       0x80000000U  // An error has occurred while waiting for events

// Event flags for the Bluetooth thread
#define SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_WAKEUP           0x00000001U  // Bluetooth task needs an update
#define SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_COMMAND_WAITING  0x00000002U  // Bluetooth command is waiting to be processed
#define SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED    0x00000004U  // Bluetooth event posted to the event handler thread has been handled
#define SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_STOPPED          0x00000008U  // Bluetooth stack has been stopped

// Event flags for the Link Layer thread
#define SLI_BT_RTOS_LINKLAYER_THREAD_FLAG_WAKEUP           0x00000100U  // Linklayer task needs an update

// Event flags for the event handler thread
#define SLI_BT_RTOS_EVENT_THREAD_FLAG_EVENT_WAITING        0x00010000U  // Bluetooth event is waiting to be processed

static volatile uint8_t bluetooth_state_flags = 0;

void sli_bgapi_cmd_handler_delegate(uint32_t header, sl_bgapi_handler, const void*);

static volatile sl_bt_msg_t bluetooth_evt_instance;

static volatile uint32_t command_header;
static volatile void* command_data;
static volatile sl_bgapi_handler command_handler_func = NULL;

/**
 * @brief Structure to represent a thread in the Bluetooth RTOS adaptation
 */
typedef struct {
  osThreadId_t       thread_id;           ///< The ID of the thread
  osSemaphoreId_t    wakeup_semaphore_id; ///< The ID of the wakeup semaphore
  volatile uint32_t  event_flags;         ///< Event flags to be handled after wakeup
} sli_bt_rtos_thread_t;

//Bluetooth stack thread
static void bluetooth_thread(void *p_arg);
static sli_bt_rtos_thread_t thread_bluetooth;
static const osThreadAttr_t thread_bluetooth_attr = {
  .name = "Bluetooth stack",
  .stack_size = SL_BT_RTOS_HOST_STACK_TASK_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_HOST_STACK_TASK_PRIORITY
};
static const osSemaphoreAttr_t semaphore_bluetooth_attr = {
  .name = "Bluetooth stack wakeup"
};

//Bluetooth linklayer thread
static void linklayer_thread(void *p_arg);
static sli_bt_rtos_thread_t thread_linklayer;
static const osThreadAttr_t thread_linklayer_attr = {
  .name = "Bluetooth linklayer",
  .stack_size = SL_BT_RTOS_LINK_LAYER_TASK_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_LINK_LAYER_TASK_PRIORITY
};
static const osSemaphoreAttr_t semaphore_linklayer_attr = {
  .name = "Bluetooth linklayer wakeup"
};

//Bluetooth event handler thread
static sli_bt_rtos_thread_t thread_event_handler;
#ifndef SL_BT_DISABLE_EVENT_TASK
static void event_handler_thread(void *p_arg);
static const osThreadAttr_t thread_event_handler_attr = {
  .name = "Bluetooth event handler",
  .stack_size = SL_BT_RTOS_EVENT_HANDLER_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_EVENT_HANDLER_TASK_PRIORITY
};
#endif
static const osSemaphoreAttr_t semaphore_event_handler_attr = {
  .name = "Bluetooth event handler wakeup"
};

static volatile osMutexId_t bluetooth_mutex_id;
static const osMutexAttr_t bluetooth_mutex_attr = {
  .name = "Bluetooth Mutex",
  .attr_bits = osMutexRecursive | osMutexPrioInherit,
};

static volatile osMutexId_t bgapi_mutex_id;
static const osMutexAttr_t bgapi_mutex_attr = {
  .name = "BGAPI Mutex",
  .attr_bits = osMutexRecursive | osMutexPrioInherit,
};

static volatile osSemaphoreId_t bgapi_response_semaphore_id;
static const osSemaphoreAttr_t bgapi_response_semaphore_attr = {
  .name = "BGAPI response"
};

static uint32_t bgapi_command_recursion_count = 0;

/**
 * @brief Convert CMSIS-RTOS2 osStatus_t to @ref sl_status_t
 */
static sl_status_t os2sl_status(osStatus_t ret)
{
  switch (ret) {
    case osOK:
      return SL_STATUS_OK;

    case osErrorTimeout:
      return SL_STATUS_TIMEOUT;

    case osErrorISR:
      return SL_STATUS_ISR;

    case osErrorParameter:
      return SL_STATUS_INVALID_PARAMETER;

    default:
      return SL_STATUS_FAIL;
  }
}

/**
 * @brief Convert @ref wait_bluetooth_rtos_thread_event_flags() return value to @ref sl_status_t
 */
static sl_status_t event_flag_error_to_sl_status(uint32_t flags)
{
  // If the error bit is not set, the call was successful
  if ((flags & SLI_BT_RTOS_EVENT_FLAG_ERROR) == 0) {
    return SL_STATUS_OK;
  }

  // The error bit was set, so an error has occurred. The other bits store the
  // `sl_status_t` error code.
  sl_status_t status = (sl_status_t) (flags & (~SLI_BT_RTOS_EVENT_FLAG_ERROR));
  return status;
}

/**
 * @brief Delete a Bluetooth RTOS adaptation thread
 *
 * @param[out] thread The thread structure that records the info for the thread
 *   to delete
 */
static void delete_bluetooth_rtos_thread(sli_bt_rtos_thread_t *thread)
{
  EFM_ASSERT(thread != NULL);

  if (thread->thread_id != NULL) {
    (void) osThreadTerminate(thread->thread_id);
    thread->thread_id = NULL;
  }

  if (thread->wakeup_semaphore_id != NULL) {
    (void) osSemaphoreDelete(thread->wakeup_semaphore_id);
    thread->wakeup_semaphore_id = NULL;
  }
}

/**
 * @brief Create a Bluetooth RTOS adaptation thread
 *
 * This function creates a wakeup semaphore and the corresponding thread to use
 * for Bluetooth RTOS adaptation. The thread function @p thread_func will
 * receive a pointer to @p thread as the thread argument.
 *
 * To support the special case where the event thread is disabled by
 * configuration, this function may be called with @p thread_func set to NULL.
 * In this case the thread is not created, but the wakeup semaphore and the
 * event flags can be used by any calling thread to wait for an event.
 *
 * Note that this function does not automatically assign `thread_id` in @p
 * thread. To avoid race conditions between the calling thread and the thread
 * that is created, some thread creation calls need special consideration in
 * assigning the handle. This function gives the callers the flexibility to
 * choose when to assign `thread_id` in @p thread.
 *
 * @param[out] thread          The thread structure that records the info for this thread
 * @param[out] thread_id       Set to the thread ID for the created thread
 * @param[in]  semaphore_attr  Attributes of the wakeup semaphore
 * @param[in]  thread_func     Thread function
 * @param[in]  thread_attr     Attributes of the thread to create
 */
static sl_status_t create_bluetooth_rtos_thread(sli_bt_rtos_thread_t    *thread,
                                                osThreadId_t            *thread_id,
                                                const osSemaphoreAttr_t *semaphore_attr,
                                                osThreadFunc_t           thread_func,
                                                const osThreadAttr_t    *thread_attr)
{
  // Parameters must have been supplied and we can't yet have the RTOS objects
  EFM_ASSERT(thread != NULL);
  EFM_ASSERT(thread_id != NULL);
  EFM_ASSERT(thread->thread_id == NULL);
  EFM_ASSERT(thread->wakeup_semaphore_id == NULL);

  // Thread will typically immmediately start waiting on the wakeup semaphore,
  // so init event flags and create the semaphore first
  thread->event_flags = 0;
  uint32_t max_count = 1;
  uint32_t initial_count = 0;
  thread->wakeup_semaphore_id = osSemaphoreNew(max_count, initial_count, semaphore_attr);
  if (thread->wakeup_semaphore_id == NULL) {
    return SL_STATUS_FAIL;
  }

  // Create the thread itself, if a function was supplied
  if (thread_func != NULL) {
    *thread_id = osThreadNew(thread_func, thread, thread_attr);
    if (*thread_id == NULL) {
      (void) osSemaphoreDelete(thread->wakeup_semaphore_id);
      thread->wakeup_semaphore_id = NULL;
      return SL_STATUS_FAIL;
    }
  } else {
    *thread_id = NULL;
  }

  return SL_STATUS_OK;
}

/**
 * @brief Set event flags to the specifed Bluetooth RTOS adaptation thread
 *
 * This function sets the specified event flags to a Bluetooth RTOS adaptation
 * thread. The flags are bitwise OR'ed, i.e. flag bits that are zero do not
 * affect flags that have already been set. Flag bits that are set to one are
 * set to the thread and the target thread is woken up.
 *
 * @param[in,out] thread       The thread structure that records the info for this thread
 * @param[in]     event_flags  The event flags to set
 */
static void set_bluetooth_rtos_thread_event_flags(sli_bt_rtos_thread_t *thread,
                                                  uint32_t              event_flags)
{
  CORE_DECLARE_IRQ_STATE;

  // Set the flags in an atomic section
  CORE_ENTER_ATOMIC();
  thread->event_flags |= event_flags;
  CORE_EXIT_ATOMIC();

  // To avoid any risk of a race condition, we err on the side of caution and
  // always wakeup the target thread. The threads don't react to the number of
  // wakeups, but to seeing flags set, so redundant wakeups are not a problem.
  // Also, since we're using a binary semaphore, the number of wakeups won't
  // accumulate. If we wake up the thread multiple times, the semaphore clamps
  // at one token, the thread wakes up once, and sees all the flags accumulated
  // so far.
  //
  // We deliberately don't check the return code when we release the semaphore.
  // The only possible errors documented by CMSIS-RTOS2 is reaching the maximum
  // count (this is OK for us, as we're deliberately using a binary semaphore
  // that clamps to one token), and having a NULL or invalid semaphore ID. That
  // can only happen if someone else corrupts our memory, as the semaphore
  // creation is checked for success before the threads start using it. That
  // error would be unrecoverable anyway.
  (void) osSemaphoreRelease(thread->wakeup_semaphore_id);
}

/**
 * @brief Peek the event flags without waiting or clearing any
 *
 * @param[in] thread The thread structure that records the info for this thread
 *
 * @return The event flags that are set in the thread
 */
static uint32_t peek_bluetooth_rtos_thread_event_flags(sli_bt_rtos_thread_t *thread)
{
  CORE_DECLARE_IRQ_STATE;

  // Read atomically
  CORE_ENTER_ATOMIC();
  uint32_t event_flags = thread->event_flags;
  CORE_EXIT_ATOMIC();

  return event_flags;
}

/**
 * @brief Pop the current event flags in the specifed Bluetooth RTOS adaptation thread
 *
 * This function returns a bitmask of event flags that were set and clears those
 * bits in the thread structure.
 *
 * @param[in,out] thread    The thread structure that records the info for this thread
 * @param[in]  event_flags  The event flags to wait for
 *
 * @return The event flags that were set and have been cleared
 */
static uint32_t pop_bluetooth_rtos_thread_event_flags(sli_bt_rtos_thread_t *thread)
{
  CORE_DECLARE_IRQ_STATE;

  // Check and clear the flags atomically
  CORE_ENTER_ATOMIC();
  uint32_t event_flags = thread->event_flags;
  if (event_flags != 0) {
    thread->event_flags = 0;
  }
  CORE_EXIT_ATOMIC();

  return event_flags;
}

/**
 * @brief Wait for event flags in the specifed Bluetooth RTOS adaptation thread
 *
 * This function waits until at least one event flag has become set for the
 * thread. If flags are set already, the function returns immediately. The
 * function returns a bitmask of event flags that were set and clears those bits
 * in the thread structure.
 *
 * @param[in,out] thread    The thread structure that records the info for this thread
 * @param[in]  event_flags  The event flags to wait for
 *
 * @return The event flags that were set and have been cleared. If an error
 *   occurs, the flag bit @ref SLI_BT_RTOS_EVENT_FLAG_ERROR is set in the return
 *   value. Use @ref event_flag_error_to_sl_status() to get the error code as
 *   `sl_status_t`.
 */
static uint32_t wait_bluetooth_rtos_thread_event_flags(sli_bt_rtos_thread_t *thread)
{
  // Loop until we see a flag set or an error occurs
  while (1) {
    // Pop the current flags
    uint32_t event_flags = pop_bluetooth_rtos_thread_event_flags(thread);

    // If any flags were set, we're done
    if (event_flags != 0) {
      return event_flags;
    }

    // Wait on the wakeup semaphore
    osStatus_t os_status = osSemaphoreAcquire(thread->wakeup_semaphore_id, osWaitForever);
    if (os_status != osOK) {
      // An error has occurred. Set the error bit and store the `sl_status_t` in
      // the other bits where `event_flag_error_to_sl_status()` will pick them
      // up.
      sl_status_t status = os2sl_status(os_status);
      return SLI_BT_RTOS_EVENT_FLAG_ERROR | (uint32_t) status;
    }
  }
}

static sl_status_t start_rtos_adaptation()
{
  // This function is called internally in this file. Callers guarantee the
  // necessary locking, so we can manipulate the flags safely.

  // If the Bluetooth stack is stopping, we cannot accept a new request to start
  // the stack until the previous stopping has finished
  if (bluetooth_state_flags & SLI_BT_RTOS_STATE_FLAG_STOPPING) {
    return SL_STATUS_INVALID_STATE;
  }

  // If the stack is already starting or started, the new request to start
  // requires no actions
  if (bluetooth_state_flags & (SLI_BT_RTOS_STATE_FLAG_STARTING | SLI_BT_RTOS_STATE_FLAG_STARTED)) {
    return SL_STATUS_OK;
  }

  // We need to start the stack now. First create the mutex for Bluetooth stack.
  sl_status_t status = SL_STATUS_FAIL;
  EFM_ASSERT(bluetooth_mutex_id == NULL);
  bluetooth_mutex_id = osMutexNew(&bluetooth_mutex_attr);
  if (bluetooth_mutex_id == NULL) {
    goto cleanup;
  }

  // We have committed to starting the stack and we expect
  // `bluetooth_thread()` to continue the start-up.
  bluetooth_state_flags |= SLI_BT_RTOS_STATE_FLAG_STARTING;

  // Create thread for Bluetooth stack. Note that we specifically do *not*
  // assign `thread_bluetooth.thread_id` here. When the thread is created, its
  // priority may be higher than the current thread, so Bluetooth starts running
  // before this thread has a chance to set the thread ID. To solve this
  // potential race condition, we let the Bluetooth thread itself set
  // `thread_bluetooth.thread_id` when it starts running. This way setting the
  // thread ID is always synchronous to starting the stack inside the thread.
  osThreadId_t host_stack_tid = NULL;
  status = create_bluetooth_rtos_thread(&thread_bluetooth,
                                        &host_stack_tid,
                                        &semaphore_bluetooth_attr,
                                        bluetooth_thread,
                                        &thread_bluetooth_attr);
  if (status != SL_STATUS_OK) {
    // We failed to create the thread, so the start won't be able to proceed.
    // Clear the starting flag to keep the state consistent.
    bluetooth_state_flags &= ~SLI_BT_RTOS_STATE_FLAG_STARTING;
    goto cleanup;
  }

  // Now we're ready to handle BGAPI commands via the RTOS adaptation. Set the
  // BGAPI delegate.
  sli_bgapi_set_cmd_handler_delegate(sli_bt_cmd_handler_rtos_delegate);

  return SL_STATUS_OK;

  cleanup:
  // Cleanup everything we managed to create
  if (bluetooth_mutex_id != NULL) {
    (void) osMutexDelete(bluetooth_mutex_id);
    bluetooth_mutex_id = NULL;
  }

  return status;
}

sl_status_t sl_bt_rtos_init()
{
  // Initialize the Bluetooth stack
  sl_bt_init();

  // The Bluetooth stack including its RTOS adaptation is started with a BGAPI
  // command. The BGAPI synchronization primitives are therefore always created
  // already at init-time and are never deleted.
  uint32_t max_count = 1;
  uint32_t initial_count = 0;
  bgapi_response_semaphore_id = osSemaphoreNew(max_count, initial_count, &bgapi_response_semaphore_attr);
  if (bgapi_response_semaphore_id == NULL) {
    return SL_STATUS_FAIL;
  }

  bgapi_mutex_id = osMutexNew(&bgapi_mutex_attr);
  bgapi_command_recursion_count = 0;
  if (bgapi_mutex_id == NULL) {
    (void) osSemaphoreDelete(bgapi_response_semaphore_id);
    bgapi_response_semaphore_id = NULL;
    return SL_STATUS_FAIL;
  }

  // When Bluetooth on-demand start feature is not present, the RTOS adaptation
  // is always started already at init-time.
#if !defined(SL_CATALOG_BLUETOOTH_ON_DEMAND_START_PRESENT)
  sl_status_t status = start_rtos_adaptation();
  if (status != SL_STATUS_OK) {
    return status;
  }
#endif // defined(SL_CATALOG_BLUETOOTH_ON_DEMAND_START_PRESENT)

  return SL_STATUS_OK;
}

// This callback is called from interrupt context (Kernel Aware) to wake up the
// link layer task
void sli_bt_rtos_ll_callback()
{
  set_bluetooth_rtos_thread_event_flags(&thread_linklayer,
                                        SLI_BT_RTOS_LINKLAYER_THREAD_FLAG_WAKEUP);
}

// This callback is called by the Bluetooth stack to wakeup the Bluetooth
// thread. This call may come from a thread or from interrupt context.
void sli_bt_rtos_stack_callback()
{
  set_bluetooth_rtos_thread_event_flags(&thread_bluetooth,
                                        SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_WAKEUP);
}

/**
 * Internal stack function to get how long the Bluetooth stack can sleep.
 *
 * @return 0 if the stack cannot sleep;
 * Maximum value of uint32_t if the stack has no task scheduled to process;
 * The ticks (in sleeptimer frequency) the stack needs to wake up to process a task
 */
extern uint32_t sli_bt_can_sleep_ticks();

/**
 * Internal stack function to start the Bluetooth stack.
 *
 * @return SL_STATUS_OK if the stack was successfully started
 */
extern sl_status_t sli_bt_system_start_bluetooth();

#if defined(SL_CATALOG_BTMESH_PRESENT)
// This is to avoid casting a function pointer to a different type in the
// event_types table.
static sl_status_t _btmesh_pop_event(sl_bt_msg_t *msg)
{
  return sl_btmesh_pop_event((sl_btmesh_msg_t*) msg);
}
#endif

typedef struct {
  enum sl_bgapi_dev_types dev_type;
  bool (*event_pending_fn)(void);
  sl_status_t (*pop_event_fn)(sl_bt_msg_t *buffer);
} bgapi_device_type;

static const bgapi_device_type bgapi_device_table[] = {
  { sl_bgapi_dev_type_bt, sl_bt_event_pending, sl_bt_pop_event },
#if defined(SL_CATALOG_BTMESH_PRESENT)
  { sl_bgapi_dev_type_btmesh, sl_btmesh_event_pending, _btmesh_pop_event },
#endif
};

#define NUM_BGAPI_DEVICES   (sizeof(bgapi_device_table) / sizeof(bgapi_device_table[0]))

//Bluetooth task, it waits for events from bluetooth and handles them
void bluetooth_thread(void *p_arg)
{
  (void)p_arg;

  // Set the Bluetooth thread ID now that we're running
  thread_bluetooth.thread_id = osThreadGetId();

  uint8_t next_evt_index_to_check = 0;
  uint32_t flags = SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED;

  // Create thread for Linklayer
  sl_status_t start_status = create_bluetooth_rtos_thread(&thread_linklayer,
                                                          &thread_linklayer.thread_id,
                                                          &semaphore_linklayer_attr,
                                                          linklayer_thread,
                                                          &thread_linklayer_attr);

  // Create thread for Bluetooth event handler
  if (start_status == SL_STATUS_OK) {
    start_status = create_bluetooth_rtos_thread(&thread_event_handler,
                                                &thread_event_handler.thread_id,
                                                &semaphore_event_handler_attr,
#ifndef SL_BT_DISABLE_EVENT_TASK
                                                event_handler_thread,
                                                &thread_event_handler_attr
#else
                                                NULL, // No thread function
                                                NULL  // No thread attributes
#endif
                                                );
  }

  // Start the Bluetooth stack
  if (start_status == SL_STATUS_OK) {
    start_status = sli_bt_system_start_bluetooth();
  }

  if (start_status == SL_STATUS_OK) {
    // bluetooth mesh must have bluetooth started before it is initalizes
    #if defined(SL_CATALOG_BTMESH_PRESENT)
    sl_btmesh_init();
    #endif
    // Starting the stack has succeeded and we update the state accordingly.
    uint8_t updated_state_flags = bluetooth_state_flags;
    updated_state_flags &= ~SLI_BT_RTOS_STATE_FLAG_STARTING;
    updated_state_flags |= SLI_BT_RTOS_STATE_FLAG_STARTED;
    bluetooth_state_flags = updated_state_flags;
  } else {
    // We failed to start, so consider the stack stopped already in the local
    // flags. This way we won't enter the processing loop at all, but proceed to
    // cleaning up after the loop. The state flags in `bluetooth_state_flags`
    // continue to show the "starting" state until we've finished cleaning up.
    flags |= SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_STOPPED;
  }

  // We run the command processing loop as long as the stack has not been stopped
  while ((flags & SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_STOPPED) == 0) {
    //Command needs to be sent to Bluetooth stack
    if (flags & SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_COMMAND_WAITING) {
      uint32_t header = command_header;
      sl_bgapi_handler cmd_handler = command_handler_func;
      sli_bgapi_cmd_handler_delegate(header, cmd_handler, (void*)command_data);
      command_handler_func = NULL;
      flags &= ~SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_COMMAND_WAITING;
      osSemaphoreRelease(bgapi_response_semaphore_id);
    }

    //Run Bluetooth stack. Pop the next event for application
    sl_bt_run();
    if (flags & SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED) {
      bool event_popped = false;
      sl_status_t status = SL_STATUS_OK;
      for (uint8_t i = 0; i < NUM_BGAPI_DEVICES; i++) {
        // Try to get an event of a device type that was _not_ handled previously, in order to
        // prevent one device type from "starving" the other device type(s).
        // For example, Bluetooth scan reports could flood in so fast that we'd never process
        // BT Mesh events, if we always checked for Bluetooth events first.
        uint8_t evt_index = (next_evt_index_to_check + i) % NUM_BGAPI_DEVICES;
        const bgapi_device_type *dev = &bgapi_device_table[evt_index];
        if (dev->event_pending_fn()) {
          status = dev->pop_event_fn((sl_bt_msg_t*) &bluetooth_evt_instance);
          if (status == SL_STATUS_OK) {
            // Next round, start the search from the next event type (wrapping around if needed)
            next_evt_index_to_check = (evt_index + 1) % NUM_BGAPI_DEVICES;
            event_popped = true;
          }
          break;
        }
      }
      if (status != SL_STATUS_OK) {
        continue;
      }
      if (event_popped) {
        set_bluetooth_rtos_thread_event_flags(&thread_event_handler,
                                              SLI_BT_RTOS_EVENT_THREAD_FLAG_EVENT_WAITING);
        flags &= ~SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED;
      }
    }

    uint32_t timeout = sli_bt_can_sleep_ticks();
    if (timeout == 0 && (flags & SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED)) {
      continue;
    }

    // Wait for any flag to get set
    flags |= wait_bluetooth_rtos_thread_event_flags(&thread_bluetooth);
    if ((flags & SLI_BT_RTOS_EVENT_FLAG_ERROR) != 0) {
      // In case of error, reset the flags and continue
      flags = SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED;
      continue;
    }
  }

  // The stack has stopped processing commands and has already finished its own
  // cleanup of resources. It's now time for the RTOS adaptation to cleanup its
  // own resources. First delete the threads that we created for the link layer
  // and for the event handler.
  delete_bluetooth_rtos_thread(&thread_linklayer);
  delete_bluetooth_rtos_thread(&thread_event_handler);

  // Delete the synchronization primitives
  (void) osMutexDelete(bluetooth_mutex_id);
  bluetooth_mutex_id = NULL;

  // In case we've failed to start, we will directly deliver a system error
  // event to the application in the code below. To allow the application to
  // retry when it gets the error event, we need to clean all global state first
  // and finish the cleanup locally in the current thread when the event handler
  // returns. We take ownership of all remaining RTOS objects (this thread and
  // its wakeup semaphore) and clear the state to indicate the kernel is started
  // but the stack is stopped.
  thread_bluetooth.thread_id = NULL;
  (void) osSemaphoreDelete(thread_bluetooth.wakeup_semaphore_id);
  thread_bluetooth.wakeup_semaphore_id = NULL;
  bluetooth_state_flags = SLI_BT_RTOS_STATE_FLAG_KERNEL_STARTED;

  // Generate the right event to indicate the stack is not running
  if (start_status != SL_STATUS_OK) {
    // We failed to start the stack. Generate a system error event and deliver
    // it directly to the application with a function call from this thread.
    uint32_t evt_len = sizeof(bluetooth_evt_instance.data.evt_system_error);
    bluetooth_evt_instance.header = sl_bt_evt_system_error_id | (evt_len << 8);
    bluetooth_evt_instance.data.evt_system_error.reason = (uint16_t) start_status;
    bluetooth_evt_instance.data.evt_system_error.data.len = 0;
    sl_bt_process_event((sl_bt_msg_t*) &bluetooth_evt_instance);
  } else {
    // The stack started successfully, so the stopping has been a deliberate
    // request with the on-demand start feature. Generate the "system stopped"
    // event and deliver it directly to the application with a function call
    // from this thread. Note that the "system stopped" event has no
    // event-specific fields, so only the header needs to be set.
    bluetooth_evt_instance.header = sl_bt_evt_system_stopped_id;
    sl_bt_process_event((sl_bt_msg_t*) &bluetooth_evt_instance);
  }

  // Finally terminate this thread itself
  (void) osThreadTerminate(osThreadGetId());
}

static void linklayer_thread(void *p_arg)
{
  // The input parameter is our thread structure
  sli_bt_rtos_thread_t *thread = (sli_bt_rtos_thread_t *) p_arg;

  while (1) {
    // Wait for any flag to get set. Only the link layer flag is expected in
    // this thread.
    uint32_t flags = wait_bluetooth_rtos_thread_event_flags(thread);
    EFM_ASSERT(flags == SLI_BT_RTOS_LINKLAYER_THREAD_FLAG_WAKEUP);

    // Handle the event
    sl_bt_priority_handle();
  }
}

// Event task, this calls the application code
#ifndef SL_BT_DISABLE_EVENT_TASK
static void event_handler_thread(void *p_arg)
{
  // The input parameter is our thread structure
  sli_bt_rtos_thread_t *thread = (sli_bt_rtos_thread_t *) p_arg;

  while (1) {
    // Wait for any flag to get set. Only the "event waiting" flag is expected
    // in this thread.
    uint32_t flags = wait_bluetooth_rtos_thread_event_flags(thread);
    EFM_ASSERT(flags == SLI_BT_RTOS_EVENT_THREAD_FLAG_EVENT_WAITING);

    switch (SL_BGAPI_MSG_DEVICE_TYPE(bluetooth_evt_instance.header)) {
      case sl_bgapi_dev_type_bt:
        sl_bt_process_event((sl_bt_msg_t*) &bluetooth_evt_instance);
        break;
#if defined(SL_CATALOG_BTMESH_PRESENT)
      case sl_bgapi_dev_type_btmesh:
        sl_btmesh_process_event((sl_btmesh_msg_t*) &bluetooth_evt_instance);
        break;
#endif
      default:
        // This should not be possible
        EFM_ASSERT(0);
        break;
    }

    // Signal the host stack thread that the event has been handled
    set_bluetooth_rtos_thread_event_flags(&thread_bluetooth,
                                          SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED);
  }
}
#endif

//hooks for API
//called from tasks using Bluetooth API
void sli_bt_cmd_handler_rtos_delegate(uint32_t header, sl_bgapi_handler handler, const void* payload)
{
  command_header = header;
  command_handler_func = handler;
  command_data = (void*)payload;
  if (osThreadGetId() == thread_bluetooth.thread_id) {
    // If we're already in the Bluetooth stack thread, the BGAPI command will be handled as a direct
    // function call; as opposed to signalling ourselves that there's a command waiting, like what
    // would happen in all other threads
    handler(payload);
    return;
  }

  // We're starting a new command. The response semaphore cannot have an
  // available token yet.
  EFM_ASSERT(osSemaphoreGetCount(bgapi_response_semaphore_id) == 0);

  // Command structure is filled, notify the stack
  set_bluetooth_rtos_thread_event_flags(&thread_bluetooth,
                                        SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_COMMAND_WAITING);

  // Wait for response
  osSemaphoreAcquire(bgapi_response_semaphore_id, osWaitForever);
}

sl_status_t sl_bt_rtos_has_event_waiting()
{
  uint32_t flags = peek_bluetooth_rtos_thread_event_flags(&thread_event_handler);
  if ((flags & SLI_BT_RTOS_EVENT_THREAD_FLAG_EVENT_WAITING) != 0) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

sl_status_t sl_bt_rtos_event_wait(bool blocking)
{
  // If the application calls us when the RTOS adaptation is not started, return
  // an error
  if (thread_event_handler.wakeup_semaphore_id == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  uint32_t flags;
  if (blocking) {
    flags = wait_bluetooth_rtos_thread_event_flags(&thread_event_handler);
    if ((flags & SLI_BT_RTOS_EVENT_FLAG_ERROR) != 0) {
      // An error occurred
      return event_flag_error_to_sl_status(flags);
    }
  } else {
    flags = pop_bluetooth_rtos_thread_event_flags(&thread_event_handler);
  }

  if ((flags & SLI_BT_RTOS_EVENT_THREAD_FLAG_EVENT_WAITING) != 0) {
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_FAIL;
  }
}

sl_status_t sl_bt_rtos_set_event_handled()
{
  // If the application calls us when the RTOS adaptation is not started, return
  // an error
  if (thread_bluetooth.wakeup_semaphore_id == NULL) {
    return SL_STATUS_INVALID_STATE;
  }

  // Signal the host stack thread that the event has been handled
  set_bluetooth_rtos_thread_event_flags(&thread_bluetooth,
                                        SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_EVENT_HANDLED);
  return SL_STATUS_OK;
}

// Lock the BGAPI for exclusive access
sl_status_t sl_bgapi_lock(void)
{
  // If the kernel has not been started yet, the BGAPI command call must be a
  // call from `app_init()` to start the Bluetooth stack. The init is
  // single-threaded and we can safely proceed without the lock.
  if ((bluetooth_state_flags & SLI_BT_RTOS_STATE_FLAG_KERNEL_STARTED) == 0) {
    return SL_STATUS_OK;
  }

  osStatus_t ret = osMutexAcquire(bgapi_mutex_id, 0);
  if (ret == osOK) {
    // Able to immediately acquire
    bgapi_command_recursion_count++;
    return SL_STATUS_OK;
  } else if ((ret != osOK)
             && (osThreadGetId() == thread_bluetooth.thread_id)) {
    // No need to re-acquire, but increment recursion counter since the Bluetooth thread
    // is allowed to call BGAPI commands recursively
    bgapi_command_recursion_count++;
    return SL_STATUS_OK;
  } else {
    // Otherwise wait for the mutex
    ret = osMutexAcquire(bgapi_mutex_id, osWaitForever);
    if (ret == osOK) {
      bgapi_command_recursion_count++;
    }
    return os2sl_status(ret);
  }
}

// Release the lock obtained by @ref sl_bgapi_lock
void sl_bgapi_unlock(void)
{
  // If the kernel has not been started yet, the lock has not been obtained and
  // the unlock is ignored
  if ((bluetooth_state_flags & SLI_BT_RTOS_STATE_FLAG_KERNEL_STARTED) == 0) {
    return;
  }

  EFM_ASSERT(bgapi_command_recursion_count > 0);
  bgapi_command_recursion_count--;
  if (bgapi_command_recursion_count > 0) {
    return;
  }
  // Release the mutex when exiting the outermost BGAPI command
  (void) osMutexRelease(bgapi_mutex_id);
}

// Called by system initialization when kernel is starting.
void sli_bt_rtos_adaptation_kernel_start()
{
  bluetooth_state_flags |= SLI_BT_RTOS_STATE_FLAG_KERNEL_STARTED;
}

// Start the Bluetooth RTOS adaptation
sl_status_t sli_bt_start_rtos_adaptation()
{
  return start_rtos_adaptation();
}

// Prepare for stopping the Bluetooth RTOS adaptation
void sli_bt_prepare_to_stop_rtos_adaptation()
{
  // This function is called in the context of the Bluetooth thread when
  // processing the command sl_bt_system_stop_bluetooth(). The BGAPI lock is
  // already held when we enter this function and we can safely manipulate the
  // state flags. The BGAPI command handling verifies the current state and
  // calls this function only when it's really time to begin stopping. We can
  // simply always set the flag.
  bluetooth_state_flags |= SLI_BT_RTOS_STATE_FLAG_STOPPING;

  // We stop processing BGAPI commands via the RTOS adaptation, as the stack has
  // already committed to stopping. The BGAPI device has changed to a state
  // where only commands that are available when the stack is stopped are
  // reachable if the application calls a BGAPI command. It is therefore safe to
  // handle BGAPI commands via the default delegate until the stack is
  // restarted.
  sli_bgapi_set_cmd_handler_delegate(sli_bgapi_cmd_handler_delegate);
}

// Stop the Bluetooth RTOS adaptation
void sli_bt_stop_rtos_adaptation()
{
  // Set the event flag to indicate that the stack has been stopped. The
  // Bluetooth thread will cleanup and exit.
  set_bluetooth_rtos_thread_event_flags(&thread_bluetooth,
                                        SLI_BT_RTOS_BLUETOOTH_THREAD_FLAG_STOPPED);
}

sl_status_t sl_bt_bluetooth_pend()
{
  osStatus_t ret = osMutexAcquire(bluetooth_mutex_id, osWaitForever);
  return os2sl_status(ret);
}

sl_status_t sl_bt_bluetooth_post()
{
  osStatus_t ret = osMutexRelease(bluetooth_mutex_id);
  return os2sl_status(ret);
}

const sl_bt_msg_t* sl_bt_rtos_get_event()
{
  return (const sl_bt_msg_t*) &bluetooth_evt_instance;
}
