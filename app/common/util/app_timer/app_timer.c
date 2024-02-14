/***************************************************************************//**
 * @file
 * @brief Timer service
 *
 * Timer service for applications with less strict timing requirements.
 * This module is based on the sleeptimer, but runs the timer callbacks in
 * non-interrupt context. This behavior gives more flexibility for the callback
 * implementation but causes a less precise timing.
 *
 * @note If your application requires precise timing, please use the sleeptimer
 *       directly.
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
#include "app_timer.h"
#include "em_core.h"

// -----------------------------------------------------------------------------
// Definitions

#define LONG_TIMER_CHECK(timer) (0 != timer->overflow_max)

// -----------------------------------------------------------------------------
// Private variables

/// Number of the triggered timers.
static uint32_t trigger_count = 0;

/// Start of the linked list which contains the active timers.
static app_timer_t *app_timer_head = NULL;

// -----------------------------------------------------------------------------
// Private function declarations

/*******************************************************************************
 * Common callback for the sleeptimers.
 *
 * @param[in] handle Pointer to the sleeptimer handle.
 * @param[in] data Pointer to the sleeptimer's parent app timer.
 *
 * @note This function runs in interrupt context.
 ******************************************************************************/
static void app_timer_callback(sl_sleeptimer_timer_handle_t *handle,
                               void *data);

/*******************************************************************************
 * Append a timer to the end of the linked list.
 *
 * @param[in] timer Pointer to the timer handle.
 *
 * @pre Assumes that the timer is not present in the list.
 ******************************************************************************/
static void append_app_timer(app_timer_t *timer);

/*******************************************************************************
 * Remove a timer from the linked list.
 *
 * @param[in] timer Pointer to the timer handle.
 *
 * @return Presence of the timer in the linked list.
 * @retval true  Timer was in the list.
 * @retval false Timer was not found in the list.
 ******************************************************************************/
static bool remove_app_timer(app_timer_t *timer);

/*******************************************************************************
 * Find and return the first triggered timer from the linked list.
 *
 * @return The first triggered timer from the linked list.
 *
 * @note The trigger state is also reset, and it is removed from the list if
 * the timer is non-periodic.
 ******************************************************************************/
static app_timer_t *get_triggered_app_timer(void);

// -----------------------------------------------------------------------------
// Public function definitions

sl_status_t app_timer_start(app_timer_t *timer,
                            uint32_t timeout_ms,
                            app_timer_callback_t callback,
                            void *callback_data,
                            bool is_periodic)
{
  sl_status_t sc;
  uint32_t timeout_initial_tick;
  uint32_t timer_freq;
  uint64_t required_tick;

  // Check input parameters.
  if ((timeout_ms == 0) && is_periodic) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Make sure that timer is stopped, also check for NULL.
  sc = app_timer_stop(timer);
  if (SL_STATUS_OK != sc) {
    return sc;
  }

  timer->triggered = false;
  timer->overflow_counter = 0;
  timer->overflow_max = 0;

  // Check if the timer has to be a long one
  if (timeout_ms > sl_sleeptimer_get_max_ms32_conversion()) {
    // Calculate the required ticks
    timer_freq = sl_sleeptimer_get_timer_frequency();
    required_tick = ((uint64_t)timeout_ms * (uint64_t)timer_freq + 999)
                    / 1000;

    // Calculate the initial time in ticks for the first run and the number of
    // maximum-time runs
    timeout_initial_tick = (uint32_t)(required_tick % UINT32_MAX);
    timer->overflow_max = (uint16_t)(required_tick / UINT32_MAX);

    // Start the timer with the initial time
    sc = sl_sleeptimer_start_periodic_timer(&timer->sleeptimer_handle,
                                            timeout_initial_tick,
                                            app_timer_callback,
                                            (void*)timer,
                                            0,
                                            0);
  } else {
    // Start sleeptimer with the given timeout/period.
    if (is_periodic) {
      sc = sl_sleeptimer_start_periodic_timer_ms(
        &timer->sleeptimer_handle,
        timeout_ms,
        app_timer_callback,
        (void*)timer,
        0,
        0);
    } else {
      sc = sl_sleeptimer_start_timer_ms(
        &timer->sleeptimer_handle,
        timeout_ms,
        app_timer_callback,
        (void*)timer,
        0,
        0);
    }
  }

  if (SL_STATUS_OK == sc) {
    timer->callback = callback;
    timer->callback_data = callback_data;
    timer->periodic = is_periodic;
    timer->timeout_ms = timeout_ms;
    append_app_timer(timer);
  }
  return sc;
}

sl_status_t app_timer_stop(app_timer_t *timer)
{
  bool timer_present;

  if (timer == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // Stop sleeptimer, ignore error code if was not running.
  (void)sl_sleeptimer_stop_timer(&timer->sleeptimer_handle);

  timer_present = remove_app_timer(timer);
  if (timer_present && timer->triggered) {
    // Timer has been triggered but not served yet.
    CORE_ATOMIC_SECTION(--trigger_count; )
  }
  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Execute timer callback functions.
 ******************************************************************************/
void sli_app_timer_step(void)
{
  if (trigger_count > 0) {
    // Find triggered timers in list and call their callbacks.
    app_timer_t *timer;
    do {
      timer = get_triggered_app_timer();
      if (timer != NULL) {
        timer->callback(timer, timer->callback_data);
      }
    } while (timer != NULL);
  }
}

/***************************************************************************//**
 * Routine for power manager handler
 ******************************************************************************/
sl_power_manager_on_isr_exit_t sli_app_timer_sleep_on_isr_exit(void)
{
  sl_power_manager_on_isr_exit_t ret = SL_POWER_MANAGER_IGNORE;
  // if there is a triggered event, wake up to handle it
  if (trigger_count > 0) {
    ret = SL_POWER_MANAGER_WAKEUP;
  }
  return ret;
}

/***************************************************************************//**
 * Checks if it is ok to sleep now
 ******************************************************************************/
bool sli_app_timer_is_ok_to_sleep(void)
{
  bool ret = true;
  // if there is a triggered event, do not go to sleep
  if (trigger_count > 0) {
    ret = false;
  }
  return ret;
}

// -----------------------------------------------------------------------------
// Private function definitions

static void app_timer_callback(sl_sleeptimer_timer_handle_t *handle,
                               void *data)
{
  (void)handle;
  app_timer_t *timer = (app_timer_t*)data;
  if (timer->triggered == false) {
    if (timer->overflow_counter < timer->overflow_max) {
      // Timer has to run
      if (timer->overflow_counter == 0) {
        // For the first round, restart periodic timer with maximum value
        sl_sleeptimer_restart_periodic_timer(&timer->sleeptimer_handle,
                                             UINT32_MAX,
                                             app_timer_callback,
                                             (void*)timer,
                                             0,
                                             0);
      }
      timer->overflow_counter++;
    } else {
      if (LONG_TIMER_CHECK(timer)) {
        if (timer->periodic) {
          // Restart long timer
          app_timer_start(timer,
                          timer->timeout_ms,
                          timer->callback,
                          timer->callback_data,
                          true);
        } else {
          // Stop periodic timer
          sl_sleeptimer_stop_timer(&timer->sleeptimer_handle);
        }
      }
      timer->triggered = true;
      ++trigger_count;
    }
  }
}

static void append_app_timer(app_timer_t *timer)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  if (app_timer_head != NULL) {
    app_timer_t *current = app_timer_head;
    // Find end of list.
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = timer;
  } else {
    app_timer_head = timer;
  }
  timer->next = NULL;

  CORE_EXIT_ATOMIC();
}

static bool remove_app_timer(app_timer_t *timer)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  app_timer_t *prev = NULL;
  app_timer_t *current = app_timer_head;

  // Find timer in list.
  while (current != NULL && current != timer) {
    prev = current;
    current = current->next;
  }

  if (current != timer) {
    // Not found.
    CORE_EXIT_ATOMIC();
    return false;
  }

  if (prev != NULL) {
    prev->next = timer->next;
  } else {
    app_timer_head = timer->next;
  }
  CORE_EXIT_ATOMIC();
  return true;
}

static app_timer_t *get_triggered_app_timer(void)
{
  CORE_DECLARE_IRQ_STATE;
  CORE_ENTER_ATOMIC();

  // Find the first triggered timer in list
  app_timer_t *timer = app_timer_head;
  while (timer != NULL) {
    if (timer->triggered) {
      // Timer found
      timer->triggered = false;
      --trigger_count;
      if (!timer->periodic) {
        (void)remove_app_timer(timer);
      }

      CORE_EXIT_ATOMIC();
      return timer;
    }
    timer = timer->next;
  }

  CORE_EXIT_ATOMIC();
  return NULL;
}
