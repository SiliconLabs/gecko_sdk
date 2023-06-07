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
#include "sl_bluetooth.h"
#include "sl_bt_stack_config.h"
#include "sl_bt_rtos_config.h"
#include "sl_bt_rtos_adaptation.h"
#include "sl_component_catalog.h"

#ifdef CONFIGURATION_HEADER
#include CONFIGURATION_HEADER
#endif // CONFIGURATION_HEADER

// Bluetooth event flag definitions. These flags are used with the RTOS event
// flags object `bluetooth_event_flags`.
#define SL_BT_RTOS_EVENT_FLAG_STACK            0x00000001U    //Bluetooth task needs an update
#define SL_BT_RTOS_EVENT_FLAG_LL               0x00000002U    //Linklayer task needs an update
#define SL_BT_RTOS_EVENT_FLAG_CMD_WAITING      0x00000004U    //Bluetooth command is waiting to be processed
#define SL_BT_RTOS_EVENT_FLAG_RSP_WAITING      0x00000008U    //Bluetooth response is waiting to be processed
#define SL_BT_RTOS_EVENT_FLAG_EVT_WAITING      0x00000010U    //Bluetooth event is waiting to be processed
#define SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED      0x00000020U    //Bluetooth event is handled
#define SL_BT_RTOS_EVENT_FLAG_STOPPED          0x00000040U    //Bluetooth stack has been stopped

// Definitions for Bluetooth state flags that are needed already before the RTOS
// kernel has been started, i.e. if the application calls
// `sl_bt_system_start_bluetooth()` from `app_init()`. These flags are used with
// the static state variable `bluetooth_state_flags`.
#define SL_BT_RTOS_STATE_FLAG_KERNEL_STARTED  0x01U  // The RTOS kernel has been started
#define SL_BT_RTOS_STATE_FLAG_STARTING        0x02U  // The Bluetooth stack is starting
#define SL_BT_RTOS_STATE_FLAG_STARTED         0x04U  // The Bluetooth stack has successfully started
#define SL_BT_RTOS_STATE_FLAG_STOPPING        0x08U  // The Bluetooth stack is stopping

static volatile uint8_t bluetooth_state_flags = 0;

void sli_bgapi_cmd_handler_delegate(uint32_t header, sl_bgapi_handler, const void*);

static volatile sl_bt_msg_t bluetooth_evt_instance;

static volatile uint32_t command_header;
static volatile void* command_data;
static volatile sl_bgapi_handler command_handler_func = NULL;

//Bluetooth stack thread
static void bluetooth_thread(void *p_arg);
static volatile osThreadId_t tid_thread_bluetooth;

static const osThreadAttr_t thread_bluetooth_attr = {
  .name = "Bluetooth stack",
  .stack_size = SL_BT_RTOS_HOST_STACK_TASK_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_HOST_STACK_TASK_PRIORITY
};

//Bluetooth linklayer thread
static void linklayer_thread(void *p_arg);
static volatile osThreadId_t tid_thread_link_layer;
static const osThreadAttr_t thread_Linklayer_attr = {
  .name = "Bluetooth linklayer",
  .stack_size = SL_BT_RTOS_LINK_LAYER_TASK_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_LINK_LAYER_TASK_PRIORITY
};

//Bluetooth event handler thread
#ifndef SL_BT_DISABLE_EVENT_TASK
static void event_handler_thread(void *p_arg);
static volatile osThreadId_t tid_thread_event_handler;
static const osThreadAttr_t thread_event_handler_attr = {
  .name = "Bluetooth event handler",
  .stack_size = SL_BT_RTOS_EVENT_HANDLER_STACK_SIZE,
  .priority = (osPriority_t) SL_BT_RTOS_EVENT_HANDLER_TASK_PRIORITY
};
#endif

static volatile osEventFlagsId_t bluetooth_event_flags;

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

static uint32_t bgapi_command_recursion_count = 0;

static sl_status_t start_rtos_adaptation()
{
  // This function is called internally in this file. Callers guarantee the
  // necessary locking, so we can manipulate the flags safely.

  osThreadId_t bluetooth_tid = NULL;

  // If the Bluetooth stack is stopping, we cannot accept a new request to start
  // the stack until the previous stopping has finished
  if (bluetooth_state_flags & SL_BT_RTOS_STATE_FLAG_STOPPING) {
    return SL_STATUS_INVALID_STATE;
  }

  // If the stack is already starting or started, the new request to start
  // requires no actions
  if (bluetooth_state_flags & (SL_BT_RTOS_STATE_FLAG_STARTING | SL_BT_RTOS_STATE_FLAG_STARTED)) {
    return SL_STATUS_OK;
  }

  // We need to start the stack now. First create the event flags.
  EFM_ASSERT(bluetooth_event_flags == NULL);
  bluetooth_event_flags = osEventFlagsNew(NULL);
  if (bluetooth_event_flags == NULL) {
    return SL_STATUS_FAIL;
  }

  // Create mutex for Bluetooth stack
  EFM_ASSERT(bluetooth_mutex_id == NULL);
  bluetooth_mutex_id = osMutexNew(&bluetooth_mutex_attr);
  if (bluetooth_mutex_id == NULL) {
    goto cleanup;
  }

  sli_bgapi_set_cmd_handler_delegate(sli_bt_cmd_handler_rtos_delegate);

  // We have committed to starting the stack and we expect `bluetooth_thread()`
  // to continue the start-up.
  bluetooth_state_flags |= SL_BT_RTOS_STATE_FLAG_STARTING;

  // Create thread for Bluetooth stack. Note that we specifically do *not*
  // assign `tid_thread_bluetooth` here. When the thread is created, its
  // priority may be higher than the current thread, so Bluetooth starts running
  // before this thread has a chance to set the thread ID. To solve this
  // potential race condition, we let the Bluetooth thread itself set
  // `tid_thread_bluetooth` when it starts running. This way setting the thread
  // ID is always synchronous to starting the stack inside the thread.
  EFM_ASSERT(tid_thread_bluetooth == NULL);
  bluetooth_tid = osThreadNew(bluetooth_thread, NULL, &thread_bluetooth_attr);
  if (bluetooth_tid == NULL) {
    // We failed to create the thread, so the start won't be able to proceed.
    // Clear the starting flag to keep the state consistent.
    bluetooth_state_flags &= ~SL_BT_RTOS_STATE_FLAG_STARTING;
    goto cleanup;
  }

  return SL_STATUS_OK;

  cleanup:
  // Cleanup everything we managed to create
  if (bluetooth_mutex_id != NULL) {
    (void) osMutexDelete(bluetooth_mutex_id);
    bluetooth_mutex_id = NULL;
  }
  (void) osEventFlagsDelete(bluetooth_event_flags);
  bluetooth_event_flags = NULL;

  return SL_STATUS_FAIL;
}

sl_status_t sl_bt_rtos_init()
{
  // Initialize the Bluetooth stack
  sl_bt_init();

  // The Bluetooth stack including its RTOS adaptation is started with a BGAPI
  // command. The mutex for BGAPI synchronization is therefore always created
  // already at init-time and is never deleted.
  bgapi_mutex_id = osMutexNew(&bgapi_mutex_attr);
  bgapi_command_recursion_count = 0;
  if (bgapi_mutex_id == NULL) {
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

//This callback is called from interrupt context (Kernel Aware)
//sets flag to trigger Link Layer Task
void sli_bt_rtos_ll_callback()
{
  osEventFlagsSet(bluetooth_event_flags,
                  SL_BT_RTOS_EVENT_FLAG_LL);
}
//This callback is called from Bluetooth stack
//Called from kernel aware interrupt context (RTCC interrupt) and from Bluetooth task
//sets flag to trigger running Bluetooth stack
void sli_bt_rtos_stack_callback()
{
  osEventFlagsSet(bluetooth_event_flags,
                  SL_BT_RTOS_EVENT_FLAG_STACK);
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
  tid_thread_bluetooth = osThreadGetId();

  uint8_t next_evt_index_to_check = 0;
  uint32_t flags = SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED;
  sl_status_t start_status = SL_STATUS_OK;

  // Create thread for Linklayer
  EFM_ASSERT(tid_thread_link_layer == NULL);
  tid_thread_link_layer = osThreadNew(linklayer_thread,
                                      NULL,
                                      &thread_Linklayer_attr);
  if (tid_thread_link_layer == NULL) {
    start_status = SL_STATUS_FAIL;
  }

  // Create thread for Bluetooth event handler
#ifndef SL_BT_DISABLE_EVENT_TASK
  if (start_status == SL_STATUS_OK) {
    EFM_ASSERT(tid_thread_event_handler == NULL);
    tid_thread_event_handler = osThreadNew(event_handler_thread,
                                           NULL,
                                           &thread_event_handler_attr);
  }
  if (tid_thread_event_handler == NULL) {
    start_status = SL_STATUS_FAIL;
  }
#endif

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
    updated_state_flags &= ~SL_BT_RTOS_STATE_FLAG_STARTING;
    updated_state_flags |= SL_BT_RTOS_STATE_FLAG_STARTED;
    bluetooth_state_flags = updated_state_flags;
  } else {
    // We failed to start, so consider the stack stopped already in the local
    // flags. This way we won't enter the processing loop at all, but proceed to
    // cleaning up after the loop. The state flags in `bluetooth_state_flags`
    // continue to show the "starting" state until we've finished cleaning up.
    flags |= SL_BT_RTOS_EVENT_FLAG_STOPPED;
  }

  // We run the command processing loop as long as the stack has not been stopped
  while ((flags & SL_BT_RTOS_EVENT_FLAG_STOPPED) == 0) {
    //Command needs to be sent to Bluetooth stack
    if (flags & SL_BT_RTOS_EVENT_FLAG_CMD_WAITING) {
      uint32_t header = command_header;
      sl_bgapi_handler cmd_handler = command_handler_func;
      sli_bgapi_cmd_handler_delegate(header, cmd_handler, (void*)command_data);
      command_handler_func = NULL;
      flags &= ~SL_BT_RTOS_EVENT_FLAG_CMD_WAITING;
      osEventFlagsSet(bluetooth_event_flags,
                      SL_BT_RTOS_EVENT_FLAG_RSP_WAITING);
    }

    //Run Bluetooth stack. Pop the next event for application
    sl_bt_run();
    if (flags & SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED) {
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
        osEventFlagsSet(bluetooth_event_flags, SL_BT_RTOS_EVENT_FLAG_EVT_WAITING);
        flags &= ~SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED;
      }
    }

    uint32_t timeout = sli_bt_can_sleep_ticks();
    if (timeout == 0 && (flags & SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED)) {
      continue;
    }
    flags |= osEventFlagsWait(bluetooth_event_flags,
                              SL_BT_RTOS_EVENT_FLAG_STACK
                              + SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED
                              + SL_BT_RTOS_EVENT_FLAG_CMD_WAITING
                              + SL_BT_RTOS_EVENT_FLAG_STOPPED,
                              osFlagsWaitAny,
                              osWaitForever);
    if ((flags & 0x80000000u) == 0x80000000u) {
      // in case of error, reset the flag and continue
      flags = SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED;
      continue;
    }
    // flag_stack is used to wakeup from pend and then sl_bt_event_pending() is used to check if event is queued
    // even if event stays in queue and task again sleeps, it is woke up by evt_handled and then it can be processed.
  }

  // The stack has stopped processing commands and has already finished its own
  // cleanup of resources. It's now time for the RTOS adaptation to cleanup its
  // own resources. First delete the threads that we created for the link layer
  // and for the event handler.
  if (tid_thread_link_layer != NULL) {
    (void) osThreadTerminate(tid_thread_link_layer);
    tid_thread_link_layer = NULL;
  }
#ifndef SL_BT_DISABLE_EVENT_TASK
  if (tid_thread_event_handler != NULL) {
    (void) osThreadTerminate(tid_thread_event_handler);
    tid_thread_event_handler = NULL;
  }
#endif

  // Delete the synchronization primitives
  (void) osMutexDelete(bluetooth_mutex_id);
  bluetooth_mutex_id = NULL;
  (void) osEventFlagsDelete(bluetooth_event_flags);
  bluetooth_event_flags = NULL;

  // In case we've failed to start, we will directly deliver a system error
  // event to the application in the code below. To allow the application to
  // retry when it gets the error event, we need to clean all global state first
  // and finish the cleanup locally in the current thread when the event handler
  // returns. We take ownership of all remaining RTOS objects (this thread
  // itself) and clear the state to indicate the kernel is started but the stack
  // is stopped.
  tid_thread_bluetooth = NULL;
  bluetooth_state_flags = SL_BT_RTOS_STATE_FLAG_KERNEL_STARTED;

  // If we failed to start the stack, we generate a system error event and
  // deliver it directly to the application with a function call from this
  // thread.
  if (start_status != SL_STATUS_OK) {
    uint32_t evt_len = sizeof(bluetooth_evt_instance.data.evt_system_error);
    bluetooth_evt_instance.header = sl_bt_evt_system_error_id | (evt_len << 8);
    bluetooth_evt_instance.data.evt_system_error.reason = (uint16_t) start_status;
    bluetooth_evt_instance.data.evt_system_error.data.len = 0;
    sl_bt_process_event((sl_bt_msg_t*) &bluetooth_evt_instance);
  }

  // Finally terminate this thread itself
  (void) osThreadTerminate(osThreadGetId());
}

static void linklayer_thread(void *p_arg)
{
  (void)p_arg;

  while (1) {
    osEventFlagsWait(bluetooth_event_flags,
                     SL_BT_RTOS_EVENT_FLAG_LL,
                     osFlagsWaitAny,
                     osWaitForever);

    sl_bt_priority_handle();
  }
}

// Event task, this calls the application code
#ifndef SL_BT_DISABLE_EVENT_TASK
static void event_handler_thread(void *p_arg)
{
  (void)p_arg;

  while (1) {
    osEventFlagsWait(bluetooth_event_flags,
                     SL_BT_RTOS_EVENT_FLAG_EVT_WAITING,
                     osFlagsWaitAny,
                     osWaitForever);
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

    osEventFlagsSet(bluetooth_event_flags,
                    SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED);
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
  if (osThreadGetId() == tid_thread_bluetooth) {
    // If we're already in the Bluetooth stack thread, the BGAPI command will be handled as a direct
    // function call; as opposed to signalling ourselves that there's a command waiting, like what
    // would happen in all other threads
    handler(payload);
    return;
  }
  //Command structure is filled, notify the stack
  osEventFlagsSet(bluetooth_event_flags,
                  SL_BT_RTOS_EVENT_FLAG_CMD_WAITING);
  //wait for response
  osEventFlagsWait(bluetooth_event_flags,
                   SL_BT_RTOS_EVENT_FLAG_RSP_WAITING,
                   osFlagsWaitAny,
                   osWaitForever);
}

static sl_status_t osFlags2sl_status(uint32_t os_flags)
{
  switch (os_flags) {
    case osFlagsErrorParameter:
      return SL_STATUS_INVALID_PARAMETER;
    case osFlagsErrorTimeout:
      return SL_STATUS_TIMEOUT;
    case osFlagsErrorISR:
      return SL_STATUS_ISR;
    default:
      return SL_STATUS_FAIL;
  }
}

sl_status_t sl_bt_rtos_has_event_waiting()
{
  uint32_t flags = osEventFlagsWait(bluetooth_event_flags,
                                    SL_BT_RTOS_EVENT_FLAG_EVT_WAITING,
                                    osFlagsWaitAny | osFlagsNoClear,
                                    0);

  if ((flags & 0x80000000u) == 0x80000000u) {
    return osFlags2sl_status(flags); //some error returned
  } else {
    if ((flags & SL_BT_RTOS_EVENT_FLAG_EVT_WAITING)
        == SL_BT_RTOS_EVENT_FLAG_EVT_WAITING) {
      return SL_STATUS_OK;
    } else {
      return SL_STATUS_FAIL;
    }
  }
}

sl_status_t sl_bt_rtos_event_wait(bool blocking)
{
  uint32_t timeout = blocking ? osWaitForever : 0u;
  uint32_t flags = osEventFlagsWait(bluetooth_event_flags,
                                    SL_BT_RTOS_EVENT_FLAG_EVT_WAITING,
                                    osFlagsWaitAny | osFlagsNoClear,
                                    timeout);

  if ((flags & 0x80000000u) == 0x80000000u) {
    return osFlags2sl_status(flags); //some error returned
  } else {
    if ((flags & SL_BT_RTOS_EVENT_FLAG_EVT_WAITING)
        == SL_BT_RTOS_EVENT_FLAG_EVT_WAITING) {
      osEventFlagsClear(bluetooth_event_flags, SL_BT_RTOS_EVENT_FLAG_EVT_WAITING);
      return SL_STATUS_OK;
    } else {
      return SL_STATUS_FAIL;
    }
  }
}

sl_status_t sl_bt_rtos_set_event_handled()
{
  uint32_t flags = osEventFlagsSet(bluetooth_event_flags,
                                   SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED);

  if ((flags & 0x80000000u) == 0x80000000u) {
    return osFlags2sl_status(flags); //some error returned
  } else {
    if ((flags & SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED)
        == SL_BT_RTOS_EVENT_FLAG_EVT_HANDLED) {
      return SL_STATUS_OK;
    } else {
      return SL_STATUS_FAIL;
    }
  }
}

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
      return SL_STATUS_FAIL; //return this error for codes haven't been mapped yet
  }
}

// Called by Bluetooth stack to lock BGAPI for exclusive access
sl_status_t sli_bgapi_lock()
{
  osStatus_t ret = osMutexAcquire(bgapi_mutex_id, 0);
  if (ret == osOK) {
    // Able to immediately acquire
    bgapi_command_recursion_count++;
    return SL_STATUS_OK;
  } else if ((ret != osOK)
             && (osThreadGetId() == tid_thread_bluetooth)) {
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

// Called by Bluetooth stack to release the lock obtained by @ref sli_bgapi_lock
void sli_bgapi_unlock()
{
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
  bluetooth_state_flags |= SL_BT_RTOS_STATE_FLAG_KERNEL_STARTED;
}

// Start the Bluetooth RTOS adaptation
sl_status_t sli_bt_start_rtos_adaptation()
{
  sl_status_t status = SL_STATUS_FAIL;

  // See if the kernel has been started already
  if (bluetooth_state_flags & SL_BT_RTOS_STATE_FLAG_KERNEL_STARTED) {
    // The kernel has been started, so RTOS synchronization primitives are
    // available. Protect the operation with the BGAPI mutex.
    status = sli_bgapi_lock();
    if (status == SL_STATUS_OK) {
      status = start_rtos_adaptation();
      sli_bgapi_unlock();
    }
  } else {
    // The kernel has not been started, so the application must be calling
    // `sl_bt_system_start_bluetooth()` from `app_init()`. The init is
    // single-threaded, so we can safely just start the RTOS adaptation.
    status = start_rtos_adaptation();
  }

  return status;
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
  bluetooth_state_flags |= SL_BT_RTOS_STATE_FLAG_STOPPING;
}

// Stop the Bluetooth RTOS adaptation
void sli_bt_stop_rtos_adaptation()
{
  // Set the event flag to indicate that the stack has been stopped. The
  // Bluetooth thread will cleanup and exit. This graceful stopping can only
  // happen after a successful start, so the event flags object must be OK. This
  // can therefore never fail.
  uint32_t flags = osEventFlagsSet(bluetooth_event_flags, SL_BT_RTOS_EVENT_FLAG_STOPPED);
  EFM_ASSERT((flags & 0x80000000u) == 0u);
  (void) flags;
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
