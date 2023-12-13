/***************************************************************************//**
 * @file
 * @brief SLEEPTIMER API implementation.
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
#include <time.h>
#include <stdlib.h>

#include "em_device.h"
#include "em_core_generic.h"
#include "sl_sleeptimer.h"
#include "sli_sleeptimer_hal.h"
#include "sl_atomic.h"
#include "sl_sleeptimer_config.h"

#if defined(SL_COMPONENT_CATALOG_PRESENT)
#include "sl_component_catalog.h"
#endif
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
#include "sl_power_manager.h"
#include "sli_power_manager.h"
#endif

#define TIME_UNIX_EPOCH                         (1970u)
#define TIME_NTP_EPOCH                          (1900u)
#define TIME_ZIGBEE_EPOCH                       (2000u)
#define TIME_64_EPOCH                           TIME_NTP_EPOCH
#define TIME_NTP_UNIX_EPOCH_DIFF                (TIME_UNIX_EPOCH - TIME_NTP_EPOCH)
#define TIME_ZIGBEE_UNIX_EPOCH_DIFF             (TIME_ZIGBEE_EPOCH - TIME_UNIX_EPOCH)
#define TIME_DAY_COUNT_NTP_TO_UNIX_EPOCH        (TIME_NTP_UNIX_EPOCH_DIFF * 365u + 17u)                  ///< 70 years and 17 leap days
#define TIME_DAY_COUNT_ZIGBEE_TO_UNIX_EPOCH     (TIME_ZIGBEE_UNIX_EPOCH_DIFF * 365u + 7u)                ///< 30 years and 7 leap days
#define TIME_SEC_PER_DAY                        (60u * 60u * 24u)
#define TIME_NTP_EPOCH_OFFSET_SEC               (TIME_DAY_COUNT_NTP_TO_UNIX_EPOCH * TIME_SEC_PER_DAY)
#define TIME_ZIGBEE_EPOCH_OFFSET_SEC            (TIME_DAY_COUNT_ZIGBEE_TO_UNIX_EPOCH * TIME_SEC_PER_DAY)
#define TIME_DAY_PER_YEAR                       (365u)
#define TIME_SEC_PER_YEAR                       (TIME_SEC_PER_DAY * TIME_DAY_PER_YEAR)
#define TIME_UNIX_TIMESTAMP_MAX                 (0x7FFFFFFF)
#define TIME_64_BIT_UNIX_TIMESTAMP_MAX          (0x497968BD7F)                                           /// Max 64 bit timestamp supported is 11:59:59 PM 12/31/11899
#define TIME_UNIX_YEAR_MAX                      (2038u - TIME_NTP_EPOCH)                                 ///< Max UNIX year based from a 1900 epoch
#define TIME_64_BIT_YEAR_MAX                    (11899u - TIME_NTP_EPOCH)                                ///< Max 64 bit format year based from a 1900 epoch
#define TIME_64_TO_32_EPOCH_OFFSET_SEC          TIME_NTP_EPOCH_OFFSET_SEC
#define TIME_UNIX_TO_NTP_MAX                    (0xFFFFFFFF - TIME_NTP_EPOCH_OFFSET_SEC)

// Minimum count difference used when evaluating if a timer expired or not after an interrupt
// by comparing the current count value and the expected expiration count value.
// The difference should be null or of few ticks since the counter never stop.
#define MIN_DIFF_BETWEEN_COUNT_AND_EXPIRATION  2

/// @brief Time Format.
SLEEPTIMER_ENUM(sl_sleeptimer_time_format_t) {
  TIME_FORMAT_UNIX = 0,           ///< Number of seconds since January 1, 1970, 00:00. Type is signed, so represented on 31 bit.
  TIME_FORMAT_NTP = 1,            ///< Number of seconds since January 1, 1900, 00:00. Type is unsigned, so represented on 32 bit.
  TIME_FORMAT_ZIGBEE_CLUSTER = 2, ///< Number of seconds since January 1, 2000, 00:00. Type is unsigned, so represented on 32 bit.
  TIME_FORMAT_UNIX_64_BIT = 3,    ///< Number of seconds since January 1, 1900, 00:00. Type is unsigned, so represented on 64 bit.
};

// tick_count, it can wrap around.
typedef uint32_t sl_sleeptimer_tick_count_t;

// Overflow counter used to provide 64-bits tick count.
static volatile uint16_t overflow_counter;

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
// Current time count.
static sl_sleeptimer_timestamp_64_t second_count;
// Tick rest when the frequency is not a divider of the timer width.
static uint32_t overflow_tick_rest = 0;
// Current time zone offset.
static sl_sleeptimer_time_zone_offset_t tz_offset = 0;
// Precalculated tick rest in case of overflow.
static uint32_t calculated_tick_rest = 0;
// Precalculated timer overflow duration in seconds.
static uint32_t calculated_sec_count = 0;
#endif

// Timer frequency in Hz.
static uint32_t timer_frequency;

// Head of timer list.
static sl_sleeptimer_timer_handle_t *timer_head;

// Count at last update of delta of first timer.
static volatile sl_sleeptimer_tick_count_t last_delta_update_count;

// Initialization flag.
static bool is_sleeptimer_initialized = false;

// Flag that indicates if power manager's timer will expire at next compare match.
static bool next_timer_to_expire_is_power_manager = false;

// Precalculated value to avoid millisecond to tick conversion overflow.
static uint32_t max_millisecond_conversion;

// Sleep on ISR exit flag.
static bool sleep_on_isr_exit = false;

static void delta_list_insert_timer(sl_sleeptimer_timer_handle_t *handle,
                                    sl_sleeptimer_tick_count_t timeout);

static sl_status_t delta_list_remove_timer(sl_sleeptimer_timer_handle_t *handle);

static void set_comparator_for_next_timer(void);

static void update_delta_list(void);

__STATIC_INLINE uint32_t div_to_log2(uint32_t div);

__STATIC_INLINE bool is_power_of_2(uint32_t nbr);

static sl_status_t create_timer(sl_sleeptimer_timer_handle_t *handle,
                                sl_sleeptimer_tick_count_t timeout_initial,
                                sl_sleeptimer_tick_count_t timeout_periodic,
                                sl_sleeptimer_timer_callback_t callback,
                                void *callback_data,
                                uint8_t priority,
                                uint16_t option_flags);

static void update_next_timer_to_expire_is_power_manager(void);

static void delay_callback(sl_sleeptimer_timer_handle_t *handle,
                           void *data);

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
static bool is_leap_year(uint16_t year);
static uint16_t number_of_leap_days(uint32_t base_year, uint32_t current_year);

static sl_sleeptimer_weekDay_t compute_day_of_week(uint32_t day);
static sl_sleeptimer_weekDay_t compute_day_of_week_64(uint64_t day);
static uint16_t compute_day_of_year(sl_sleeptimer_month_t month, uint8_t day, bool isLeapYear);

static bool is_valid_time(sl_sleeptimer_timestamp_t time,
                          sl_sleeptimer_time_format_t format,
                          sl_sleeptimer_time_zone_offset_t time_zone);

static bool is_valid_time_64(sl_sleeptimer_timestamp_64_t time,
                             sl_sleeptimer_time_format_t format,
                             sl_sleeptimer_time_zone_offset_t time_zone);

static bool is_valid_date(sl_sleeptimer_date_t *date);

static bool is_valid_date_64(sl_sleeptimer_date_t *date);

static const uint8_t days_in_month[2u][12] = {
  /* Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec */
  { 31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u },
  { 31u, 29u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u }
};
#endif

/**************************************************************************//**
 * Initializes sleep timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_init(void)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  if (!is_sleeptimer_initialized) {
    timer_head  = NULL;
    last_delta_update_count = 0u;
    overflow_counter = 0u;
    sleeptimer_hal_init_timer();
    sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_OF);
    timer_frequency = sleeptimer_hal_get_timer_frequency();
    if (timer_frequency == 0) {
      CORE_EXIT_ATOMIC();
      return SL_STATUS_INVALID_CONFIGURATION;
    }

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
    second_count = 0;
    calculated_tick_rest = ((uint64_t)UINT32_MAX + 1) % (uint64_t)timer_frequency;
    calculated_sec_count = (((uint64_t)UINT32_MAX + 1) / (uint64_t)timer_frequency);
#endif
    max_millisecond_conversion = (uint32_t)(((uint64_t)UINT32_MAX * (uint64_t)1000u) / timer_frequency);
    is_sleeptimer_initialized = true;
  }
  CORE_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Starts a 32 bits timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_start_timer(sl_sleeptimer_timer_handle_t *handle,
                                      uint32_t timeout,
                                      sl_sleeptimer_timer_callback_t callback,
                                      void *callback_data,
                                      uint8_t priority,
                                      uint16_t option_flags)
{
  bool is_running = false;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  handle->conversion_error = 0;
  handle->accumulated_error = 0;

  sl_sleeptimer_is_timer_running(handle, &is_running);
  if (is_running == true) {
    return SL_STATUS_NOT_READY;
  }

  return create_timer(handle,
                      timeout,
                      0,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Restarts a 32 bits timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_restart_timer(sl_sleeptimer_timer_handle_t *handle,
                                        uint32_t timeout,
                                        sl_sleeptimer_timer_callback_t callback,
                                        void *callback_data,
                                        uint8_t priority,
                                        uint16_t option_flags)
{
  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  handle->conversion_error = 0;
  handle->accumulated_error = 0;

  //Trying to stop the Timer. Failing to do so implies the timer is not running.
  sl_sleeptimer_stop_timer(handle);

  //Creates the timer in any case.
  return create_timer(handle,
                      timeout,
                      0,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Starts a 32 bits periodic timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_start_periodic_timer(sl_sleeptimer_timer_handle_t *handle,
                                               uint32_t timeout,
                                               sl_sleeptimer_timer_callback_t callback,
                                               void *callback_data,
                                               uint8_t priority,
                                               uint16_t option_flags)
{
  bool is_running = false;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  handle->conversion_error = 0;
  handle->accumulated_error = 0;

  sl_sleeptimer_is_timer_running(handle, &is_running);
  if (is_running == true) {
    return SL_STATUS_INVALID_STATE;
  }

  return create_timer(handle,
                      timeout,
                      timeout,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Starts a 32 bits periodic timer using milliseconds as the timebase.
 *****************************************************************************/
sl_status_t sl_sleeptimer_start_periodic_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                  uint32_t timeout_ms,
                                                  sl_sleeptimer_timer_callback_t callback,
                                                  void *callback_data,
                                                  uint8_t priority,
                                                  uint16_t option_flags)
{
  bool is_running = false;
  sl_status_t status;
  uint32_t timeout_tick;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  sl_sleeptimer_is_timer_running(handle, &is_running);
  if (is_running == true) {
    return SL_STATUS_INVALID_STATE;
  }

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  // Calculate ms to ticks conversion error
  handle->conversion_error = 1000
                             - ((uint64_t)(timeout_ms * sl_sleeptimer_get_timer_frequency())
                                % 1000);
  if (handle->conversion_error == 1000) {
    handle->conversion_error = 0;
  }
  // Initialize accumulated error to 0. The calculated conversion error will
  // be added to this variable each time a timer in the series of periodic timers
  // expires.
  handle->accumulated_error = 0;

  return create_timer(handle,
                      timeout_tick,
                      timeout_tick,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Restarts a 32 bits periodic timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_restart_periodic_timer(sl_sleeptimer_timer_handle_t *handle,
                                                 uint32_t timeout,
                                                 sl_sleeptimer_timer_callback_t callback,
                                                 void *callback_data,
                                                 uint8_t priority,
                                                 uint16_t option_flags)
{
  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  handle->conversion_error = 0;
  handle->accumulated_error = 0;

  //Trying to stop the Timer. Failing to do so implies the timer has already been stopped.
  sl_sleeptimer_stop_timer(handle);

  //Creates the timer in any case.
  return create_timer(handle,
                      timeout,
                      timeout,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Restarts a 32 bits periodic timer using milliseconds as the timebase.
 *****************************************************************************/
sl_status_t sl_sleeptimer_restart_periodic_timer_ms(sl_sleeptimer_timer_handle_t *handle,
                                                    uint32_t timeout_ms,
                                                    sl_sleeptimer_timer_callback_t callback,
                                                    void *callback_data,
                                                    uint8_t priority,
                                                    uint16_t option_flags)
{
  sl_status_t status;
  uint32_t timeout_tick;

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  status = sl_sleeptimer_ms32_to_tick(timeout_ms, &timeout_tick);
  if (status != SL_STATUS_OK) {
    return status;
  }

  // Calculate ms to ticks conversion error
  handle->conversion_error = 1000
                             - ((uint64_t)(timeout_ms * sl_sleeptimer_get_timer_frequency())
                                % 1000);
  if (handle->conversion_error == 1000) {
    handle->conversion_error = 0;
  }

  // Initialize accumulated error to 0. The calculated conversion error will
  // be added to this variable each time a timer in the series of periodic timers
  // expires.
  handle->accumulated_error = 0;

  //Trying to stop the Timer. Failing to do so implies the timer has already been stopped.
  sl_sleeptimer_stop_timer(handle);

  //Creates the timer in any case.
  return create_timer(handle,
                      timeout_tick,
                      timeout_tick,
                      callback,
                      callback_data,
                      priority,
                      option_flags);
}

/**************************************************************************//**
 * Stops a 32 bits timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_stop_timer(sl_sleeptimer_timer_handle_t *handle)
{
  CORE_DECLARE_IRQ_STATE;
  sl_status_t error;
  bool set_comparator = false;

  // Disable PRS compare and capture channel, if configured for early wakeup
#if ((SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_SYSRTC) \
  && defined(SL_CATALOG_POWER_MANAGER_PRESENT)                     \
  && !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT))
  if (handle->option_flags == (SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG | SLI_SLEEPTIMER_POWER_MANAGER_HF_ACCURACY_CLK_FLAG)) {
    sleeptimer_hal_disable_prs_compare_and_capture_channel();
  }
#endif

  if (handle == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  CORE_ENTER_CRITICAL();
  update_delta_list();

  // If first timer in list, update timer comparator.
  if (timer_head == handle) {
    set_comparator = true;
  }

  error = delta_list_remove_timer(handle);
  if (error != SL_STATUS_OK) {
    CORE_EXIT_CRITICAL();

    return error;
  }

  if (set_comparator && timer_head) {
    set_comparator_for_next_timer();
  } else if (!timer_head) {
    sleeptimer_hal_disable_int(SLEEPTIMER_EVENT_COMP);
  }

  CORE_EXIT_CRITICAL();

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Gets the status of a timer.
 *****************************************************************************/
sl_status_t sl_sleeptimer_is_timer_running(sl_sleeptimer_timer_handle_t *handle,
                                           bool *running)
{
  CORE_DECLARE_IRQ_STATE;
  sl_sleeptimer_timer_handle_t *current;

  if (handle == NULL || running == NULL) {
    return SL_STATUS_NULL_POINTER;
  } else {
    *running = false;
    CORE_ENTER_ATOMIC();
    current = timer_head;
    while (current != NULL && !*running) {
      if (current == handle) {
        *running = true;
      } else {
        current = current->next;
      }
    }
    CORE_EXIT_ATOMIC();
  }
  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Gets a 32 bits timer's time remaining.
 *****************************************************************************/
sl_status_t sl_sleeptimer_get_timer_time_remaining(sl_sleeptimer_timer_handle_t *handle,
                                                   uint32_t *time)
{
  CORE_DECLARE_IRQ_STATE;
  sl_sleeptimer_timer_handle_t *current;

  if (handle == NULL || time == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  CORE_ENTER_ATOMIC();

  update_delta_list();
  *time  = handle->delta;

  // Retrieve timer in list and add the deltas.
  current = timer_head;
  while (current != handle && current != NULL) {
    *time += current->delta;
    current = current->next;
  }

  if (current != handle) {
    CORE_EXIT_ATOMIC();

    return SL_STATUS_NOT_READY;
  }

  // Substract time since last compare match.
  if (*time > sleeptimer_hal_get_counter() - last_delta_update_count) {
    *time -= sleeptimer_hal_get_counter() - last_delta_update_count;
  } else {
    *time = 0;
  }

  CORE_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/**************************************************************************//**
 * Gets the time remaining until the first timer with the matching set of flags
 * expires.
 *****************************************************************************/
sl_status_t sl_sleeptimer_get_remaining_time_of_first_timer(uint16_t option_flags,
                                                            uint32_t *time_remaining)
{
  CORE_DECLARE_IRQ_STATE;
  sl_sleeptimer_timer_handle_t *current;
  uint32_t time = 0;

  CORE_ENTER_ATOMIC();
  // parse list and retrieve first timer with option flags requirement.
  current = timer_head;
  while (current != NULL) {
    // save time remaining for timer.
    time += current->delta;
    // Check if the current timer has the flags requested
    if (current->option_flags == option_flags
        || option_flags == SL_SLEEPTIMER_ANY_FLAG) {
      // Substract time since last compare match.
      if (time > (sleeptimer_hal_get_counter() - last_delta_update_count)) {
        time -= (sleeptimer_hal_get_counter() - last_delta_update_count);
      } else {
        time = 0;
      }
      *time_remaining = time;
      CORE_EXIT_ATOMIC();

      return SL_STATUS_OK;
    }
    current = current->next;
  }
  CORE_EXIT_ATOMIC();

  return SL_STATUS_EMPTY;
}

/**************************************************************************//**
 * Determines if next timer to expire has the option flag
 * "SL_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG".
 *
 * @note This function is for internal use only.
 *
 * @note A check to validate that the Power Manager Sleeptimer is expired on
 *       top of being the next timer was added. This is because
 *       this function is called when coming back from EM2 sleep to validate
 *       that the system woke up because of this precise timer expiration.
 *       Some race conditions, seen with FreeRTOS, could create invalid RTC
 *       interrupt leading to believe that the power manager timer was expired
 *       when it was not.
 *****************************************************************************/
bool sli_sleeptimer_is_power_manager_timer_next_to_expire(void)
{
  bool next_timer_is_power_manager;

  sl_atomic_load(next_timer_is_power_manager, next_timer_to_expire_is_power_manager);

  // Make sure that the Power Manager Sleeptimer is actually expired in addition
  // to being the next timer.
  if ((next_timer_is_power_manager)
      && ((sl_sleeptimer_get_tick_count() - timer_head->timeout_expected_tc) > MIN_DIFF_BETWEEN_COUNT_AND_EXPIRATION)) {
    next_timer_is_power_manager = false;
  }

  return next_timer_is_power_manager;
}

/***************************************************************************//**
* Gets current 32 bits tick count.
*******************************************************************************/
uint32_t sl_sleeptimer_get_tick_count(void)
{
  uint32_t cnt;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  cnt = sleeptimer_hal_get_counter();
  CORE_EXIT_ATOMIC();

  return cnt;
}

/***************************************************************************//**
* Gets current 64 bits tick count.
*******************************************************************************/
uint64_t sl_sleeptimer_get_tick_count64(void)
{
  uint32_t tick_cnt;
  uint32_t of_cnt;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  tick_cnt = sleeptimer_hal_get_counter();
  of_cnt = overflow_counter;

  if (sli_sleeptimer_hal_is_int_status_set(SLEEPTIMER_EVENT_OF)) {
    tick_cnt = sleeptimer_hal_get_counter();
    of_cnt++;
  }
  CORE_EXIT_ATOMIC();

  return (((uint64_t) of_cnt) << 32) | tick_cnt;
}

/***************************************************************************//**
 * Get timer frequency.
 ******************************************************************************/
uint32_t sl_sleeptimer_get_timer_frequency(void)
{
  return timer_frequency;
}

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
/***************************************************************************//**
 * Retrieves current 32 bit time.
 ******************************************************************************/
sl_sleeptimer_timestamp_t sl_sleeptimer_get_time(void)
{
  uint64_t temp_time = sl_sleeptimer_get_time_64();
  // Add offset for 64 to 32 bit time
  if (temp_time >= TIME_64_TO_32_EPOCH_OFFSET_SEC) {
    temp_time -= TIME_64_TO_32_EPOCH_OFFSET_SEC;
  }
  // Return lower 32 bits of 64 bit time
  uint32_t time = (temp_time & 0xFFFFFFFF);

  return time;
}

/***************************************************************************//**
 * Retrieves current 64 bit time.
 ******************************************************************************/
sl_sleeptimer_timestamp_64_t sl_sleeptimer_get_time_64(void)
{
  uint32_t cnt = 0u;
  uint32_t freq = 0u;
  sl_sleeptimer_timestamp_64_t time;
  CORE_DECLARE_IRQ_STATE;

  cnt = sleeptimer_hal_get_counter();
  freq = sl_sleeptimer_get_timer_frequency();

  CORE_ENTER_ATOMIC();
  time = second_count + cnt / freq;

  if (cnt % freq + overflow_tick_rest >= freq) {
    time++;
  }
  CORE_EXIT_ATOMIC();

  return time;
}

/***************************************************************************//**
 * Sets current time from 32 bit variable.
 ******************************************************************************/
sl_status_t sl_sleeptimer_set_time(sl_sleeptimer_timestamp_t time)
{
  // convert 32 bit time to 64 bit time
  uint64_t temp_time = time + TIME_64_TO_32_EPOCH_OFFSET_SEC;
  sl_status_t err_code = sl_sleeptimer_set_time_64(temp_time);
  return err_code;
}

/***************************************************************************//**
 * Sets current time from 64 bit variable.
 ******************************************************************************/
sl_status_t sl_sleeptimer_set_time_64(sl_sleeptimer_timestamp_64_t time)
{
  uint32_t freq = 0u;
  uint32_t counter_sec = 0u;
  uint32_t cnt = 0;
  CORE_DECLARE_IRQ_STATE;

  // convert 64 bit time to 32 bit time
  if (!is_valid_time_64(time, TIME_FORMAT_UNIX_64_BIT, 0u)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  freq = sl_sleeptimer_get_timer_frequency();
  cnt = sleeptimer_hal_get_counter();

  CORE_ENTER_ATOMIC();
  // store 64 bit time as 64 bits's
  second_count = time;

  // Convert 64 bit time to 32 bit time in order to check for overflow
  // i.e. if 32 bit time is >=counter_sec
  uint64_t temp_time = second_count - TIME_64_TO_32_EPOCH_OFFSET_SEC;
  uint32_t second_time_32 = (temp_time & 0xFFFFFFFF);

  overflow_tick_rest = 0;
  counter_sec = cnt / freq;

  if (second_time_32 >= counter_sec) {
    second_count -= counter_sec;
  } else {
    CORE_EXIT_ATOMIC();

    return SL_STATUS_INVALID_PARAMETER;
  }

  CORE_EXIT_ATOMIC();

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Gets current date.
 ******************************************************************************/
sl_status_t sl_sleeptimer_get_datetime(sl_sleeptimer_date_t *date)
{
  sl_sleeptimer_timestamp_64_t time = 0u;
  sl_sleeptimer_time_zone_offset_t tz;
  sl_status_t err_code = SL_STATUS_OK;

  // Fetch 64 bit timestamp
  time = sl_sleeptimer_get_time_64();
  tz = sl_sleeptimer_get_tz();
  err_code = sl_sleeptimer_convert_time_to_date_64(time, tz, date);

  return err_code;
}

/***************************************************************************//**
 * Sets current time, in date format.
 ******************************************************************************/
sl_status_t sl_sleeptimer_set_datetime(sl_sleeptimer_date_t *date)
{
  sl_sleeptimer_timestamp_64_t time = 0u;
  sl_status_t err_code = SL_STATUS_OK;
  CORE_DECLARE_IRQ_STATE;

  if (!is_valid_date_64(date)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  err_code = sl_sleeptimer_convert_date_to_time_64(date, &time);
  if (err_code != SL_STATUS_OK) {
    return err_code;
  }

  CORE_ENTER_ATOMIC();
  // sets the 64 bit second_time value
  err_code = sl_sleeptimer_set_time_64(time);
  if (err_code == SL_STATUS_OK) {
    sl_sleeptimer_set_tz(date->time_zone);
  }
  CORE_EXIT_ATOMIC();

  return err_code;
}

/***************************************************************************//**
 * Builds a date time structure based on the provided parameters.
 ******************************************************************************/
sl_status_t sl_sleeptimer_build_datetime(sl_sleeptimer_date_t *date,
                                         uint16_t year,
                                         sl_sleeptimer_month_t month,
                                         uint8_t month_day,
                                         uint8_t hour,
                                         uint8_t min,
                                         uint8_t sec,
                                         sl_sleeptimer_time_zone_offset_t tz_offset)
{
  if (date == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // If year is smaller than 1900, assume NTP Epoch is used.
  date->year = ((year < TIME_NTP_EPOCH) ? year : (year - TIME_NTP_EPOCH));
  date->month = month;
  date->month_day = month_day;
  date->hour = hour;
  date->min = min;
  date->sec = sec;
  date->time_zone = tz_offset;

  // Validate that input parameters are correct before filing the missing fields
  if (!is_valid_date(date)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  date->day_of_year = compute_day_of_year(date->month, date->month_day, is_leap_year(date->year));
  date->day_of_week = compute_day_of_week(((date->year - TIME_NTP_UNIX_EPOCH_DIFF)  * TIME_DAY_PER_YEAR)
                                          + number_of_leap_days(TIME_UNIX_EPOCH, (date->year + TIME_NTP_EPOCH))
                                          + date->day_of_year - 1);

  return SL_STATUS_OK;
}

/***************************************************************************//**
 * Builds a date time structure based on the provided parameters.
 ******************************************************************************/
sl_status_t sl_sleeptimer_build_datetime_64(sl_sleeptimer_date_t *date,
                                            uint16_t year,
                                            sl_sleeptimer_month_t month,
                                            uint8_t month_day,
                                            uint8_t hour,
                                            uint8_t min,
                                            uint8_t sec,
                                            sl_sleeptimer_time_zone_offset_t tz_offset)
{
  if (date == NULL) {
    return SL_STATUS_NULL_POINTER;
  }

  // Ensure that year is greater than 1900 and based on 0 epoch
  if (year < TIME_NTP_EPOCH) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  // Convert year based on 0 epoch to a valid date->year based on 1900 epoch
  date->year = (year - TIME_NTP_EPOCH);
  date->month = month;
  date->month_day = month_day;
  date->hour = hour;
  date->min = min;
  date->sec = sec;
  date->time_zone = tz_offset;

  // Validate that input parameters are correct before filing the missing fields
  if (!is_valid_date_64(date)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  date->day_of_year = compute_day_of_year(date->month, date->month_day, is_leap_year(date->year));
  date->day_of_week = compute_day_of_week_64((date->year * TIME_DAY_PER_YEAR)
                                             + number_of_leap_days(TIME_NTP_EPOCH, (date->year + TIME_NTP_EPOCH))
                                             + date->day_of_year - 1);

  return SL_STATUS_OK;
}

/*******************************************************************************
 * Convert a 32 bit time stamp into a date structure.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_time_to_date(sl_sleeptimer_timestamp_t time,
                                               sl_sleeptimer_time_zone_offset_t time_zone,
                                               sl_sleeptimer_date_t *date)
{
  // convert 32 bit timestamp to 64 bit
  sl_sleeptimer_timestamp_64_t temp_time = (uint64_t)time + TIME_64_TO_32_EPOCH_OFFSET_SEC;
  sl_status_t err_code = sl_sleeptimer_convert_time_to_date_64(temp_time, time_zone, date);
  return err_code;
}

/*******************************************************************************
 * Convert a 64 bit time stamp into a date structure.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_time_to_date_64(sl_sleeptimer_timestamp_64_t time,
                                                  sl_sleeptimer_time_zone_offset_t time_zone,
                                                  sl_sleeptimer_date_t *date)
{
  uint16_t full_year = 0;
  uint16_t leap_day = 0;
  uint8_t leap_year_flag = 0;
  uint8_t current_month = 0;

  if (!is_valid_time_64(time, TIME_FORMAT_UNIX_64_BIT, time_zone)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  time += time_zone;  // add UTC offset to convert to Standard Time
  date->sec = time % 60;
  time /= 60;
  date->min = time % 60;
  time /= 60;
  date->hour = time % 24;
  time /= 24; // time is now the number of days since 1900

  date->day_of_week = (sl_sleeptimer_weekDay_t)compute_day_of_week_64(time);

  full_year = time / TIME_DAY_PER_YEAR; // Approximates the number of full years
  uint32_t base_year = 1900u;
  uint32_t current_year = full_year + base_year;

  if (full_year > 4) { // 1904 is the first leap year since 1900
    leap_day = number_of_leap_days(base_year, current_year);  // Approximates the number of leap days.
    full_year = (time - leap_day) / TIME_DAY_PER_YEAR; // Computes the number of year integrating the leap days.
    current_year = full_year + base_year;
    leap_day = number_of_leap_days(base_year, current_year); // Computes the actual number of leap days of the previous years.
  }
  date->year = full_year; // Year in date struct must be based on a 1900 epoch.
  if (is_leap_year(date->year)) {
    leap_year_flag = 1;
  }

  time = (time - leap_day) - (TIME_DAY_PER_YEAR * full_year);  // Subtracts days of previous year.
  date->day_of_year = time + 1;

  while (time >= days_in_month[leap_year_flag][current_month]) {
    time -= days_in_month[leap_year_flag][current_month]; // Subtracts the number of days of the passed month.
    current_month++;
  }
  date->month = (sl_sleeptimer_month_t)current_month;
  date->month_day = time + 1;
  date->time_zone = time_zone;

  return SL_STATUS_OK;
}

/*******************************************************************************
 * Convert a date structure into a 32 bit time stamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_date_to_time(sl_sleeptimer_date_t *date,
                                               sl_sleeptimer_timestamp_t *time)
{
  // Create a 64 bit time stamp
  sl_sleeptimer_timestamp_64_t temp_time =  0;
  sl_status_t err_code = sl_sleeptimer_convert_date_to_time_64(date, &temp_time);

  if (err_code != SL_STATUS_OK) {
    return err_code;
  }
  // Convert 64 bit time to 32 bit time

  sl_sleeptimer_timestamp_64_t time_32 = temp_time;
  time_32 -= TIME_64_TO_32_EPOCH_OFFSET_SEC;
  *time = (time_32 & 0xFFFFFFFF);

  return err_code;
}

/*******************************************************************************
 * Convert a date structure into a 64 bit time stamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_date_to_time_64(sl_sleeptimer_date_t *date,
                                                  sl_sleeptimer_timestamp_64_t *time)
{
  uint16_t month_days = 0;
  uint8_t  month;
  uint16_t  full_year = 0;
  uint8_t  leap_year_flag = 0;
  uint16_t  leap_days = 0;

  if (!is_valid_date_64(date)) {
    return SL_STATUS_INVALID_PARAMETER;
  }

  full_year = (date->year);                                  // base year for 64 bits its 1900 not 1970
  month = date->month;                              // offset to get months value from 1 to 12.

  uint32_t base_year = 1900u;
  uint32_t current_year = full_year + base_year;

  *time = (full_year * (uint64_t)TIME_SEC_PER_YEAR);

  if (full_year > 4) {                                       // 1904 is the first leap year since 1900
    leap_days = number_of_leap_days(base_year, current_year);
    month_days = leap_days;
  }

  if (is_leap_year(date->year)) {
    leap_year_flag = 1;
  }

  for (int i = 0; i < month; i++) {
    month_days += days_in_month[leap_year_flag][i];         // Add the number of days of the month of the year.
  }

  month_days += (date->month_day - 1);                       // Add full days of the current month.
  *time += month_days * TIME_SEC_PER_DAY;
  *time += (3600 * date->hour) + (60 * date->min) + date->sec;
  *time -= date->time_zone;

  return SL_STATUS_OK;
}

/*******************************************************************************
 * Convert a date structure to string.
 ******************************************************************************/
uint32_t sl_sleeptimer_convert_date_to_str(char *str,
                                           size_t size,
                                           const uint8_t *format,
                                           sl_sleeptimer_date_t *date)
{
  uint32_t  return_size = 0u;
  if (is_valid_date(date)) {
    struct tm date_struct;

    date_struct.tm_hour = date->hour;
    date_struct.tm_mday = date->month_day;
    date_struct.tm_min = date->min;
    date_struct.tm_mon = date->month;
    date_struct.tm_sec = date->sec;
    date_struct.tm_wday = date->day_of_week;
    date_struct.tm_yday = date->day_of_year;
    date_struct.tm_year = date->year;

    return_size = strftime(str,
                           size,
                           (const char *)format,
                           &date_struct);
  }

  return return_size;
}

/***************************************************************************//**
 * Sets time zone offset.
 *
 * @param  offset  Time zone offset, in seconds.
 ******************************************************************************/
void sl_sleeptimer_set_tz(sl_sleeptimer_time_zone_offset_t offset)
{
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  tz_offset = offset;
  CORE_EXIT_ATOMIC();
}

/***************************************************************************//**
 * Gets time zone offset.
 *
 * @return Time zone offset, in seconds.
 ******************************************************************************/
sl_sleeptimer_time_zone_offset_t sl_sleeptimer_get_tz(void)
{
  sl_sleeptimer_time_zone_offset_t offset;
  CORE_DECLARE_IRQ_STATE;

  CORE_ENTER_ATOMIC();
  offset = tz_offset;
  CORE_EXIT_ATOMIC();

  return offset;
}

/***************************************************************************//**
 * Converts Unix 32 timestamp into NTP timestamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_unix_time_to_ntp(sl_sleeptimer_timestamp_t time,
                                                   uint32_t *ntp_time)
{
  if (time > TIME_UNIX_TO_NTP_MAX) {
    // Maximum Unix timestamp that can be converted to NTP is 2085978495
    return SL_STATUS_INVALID_PARAMETER;
  }

  uint32_t temp_ntp_time;
  temp_ntp_time = time + TIME_NTP_EPOCH_OFFSET_SEC;
  if (!is_valid_time(temp_ntp_time, TIME_FORMAT_NTP, 0u)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    *ntp_time = temp_ntp_time;
    return SL_STATUS_OK;
  }
}

/***************************************************************************//**
 * Converts NTP timestamp into Unix timestamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_ntp_time_to_unix(uint32_t ntp_time,
                                                   sl_sleeptimer_timestamp_t *time)
{
  uint32_t temp_time;
  temp_time = ntp_time - TIME_NTP_EPOCH_OFFSET_SEC;
  if (!is_valid_time(temp_time, TIME_FORMAT_UNIX, 0u)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    *time = temp_time;
    return SL_STATUS_OK;
  }
}

/***************************************************************************//**
 * Converts Unix timestamp into Zigbee timestamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_unix_time_to_zigbee(sl_sleeptimer_timestamp_t time,
                                                      uint32_t *zigbee_time)
{
  uint32_t temp_zigbee_time;
  temp_zigbee_time = time - TIME_ZIGBEE_EPOCH_OFFSET_SEC;
  if (!is_valid_time(temp_zigbee_time, TIME_FORMAT_ZIGBEE_CLUSTER, 0u)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    *zigbee_time = temp_zigbee_time;
    return SL_STATUS_OK;
  }
}

/***************************************************************************//**
 * Converts Zigbee timestamp into Unix timestamp.
 ******************************************************************************/
sl_status_t sl_sleeptimer_convert_zigbee_time_to_unix(uint32_t zigbee_time,
                                                      sl_sleeptimer_timestamp_t *time)
{
  uint32_t temp_time;
  temp_time = zigbee_time + TIME_ZIGBEE_EPOCH_OFFSET_SEC;
  if (!is_valid_time(temp_time, TIME_FORMAT_UNIX, 0u)) {
    return SL_STATUS_INVALID_PARAMETER;
  } else {
    *time = temp_time;
    return SL_STATUS_OK;
  }
}

#endif // SL_SLEEPTIMER_WALLCLOCK_CONFIG

/*******************************************************************************
 * Active delay of 'time_ms' milliseconds.
 ******************************************************************************/
void sl_sleeptimer_delay_millisecond(uint16_t time_ms)
{
  volatile bool wait = true;
  sl_status_t error_code;
  sl_sleeptimer_timer_handle_t delay_timer;
  uint32_t delay = sl_sleeptimer_ms_to_tick(time_ms);

  error_code = sl_sleeptimer_start_timer(&delay_timer,
                                         delay,
                                         delay_callback,
                                         (void *)&wait,
                                         0,
                                         0);
  if (error_code == SL_STATUS_OK) {
    while (wait) { // Active delay loop.
    }
  }
}

/*******************************************************************************
 * Converts milliseconds in ticks.
 ******************************************************************************/
uint32_t sl_sleeptimer_ms_to_tick(uint16_t time_ms)
{
  return (uint32_t)((((uint64_t)time_ms * timer_frequency) + 999) / 1000);
}

/*******************************************************************************
 * Converts 32-bits milliseconds in ticks.
 ******************************************************************************/
sl_status_t sl_sleeptimer_ms32_to_tick(uint32_t time_ms,
                                       uint32_t *tick)
{
  if (time_ms <= max_millisecond_conversion) {
    *tick = (uint32_t)((((uint64_t)time_ms * timer_frequency) + 999) / 1000u);
    return SL_STATUS_OK;
  } else {
    return SL_STATUS_INVALID_PARAMETER;
  }
}

/***************************************************************************//**
 * Gets the maximum value that can be passed to the functions that have a
 * 32-bits time or timeout argument expressed in milliseconds.
 ******************************************************************************/
uint32_t sl_sleeptimer_get_max_ms32_conversion(void)
{
  return max_millisecond_conversion;
}

/*******************************************************************************
 * Converts ticks in milliseconds.
 ******************************************************************************/
uint32_t sl_sleeptimer_tick_to_ms(uint32_t tick)
{
  uint32_t time_ms;
  time_ms = 0;

  if (timer_frequency != 0u) {
    if (is_power_of_2(timer_frequency)) {
      time_ms = (uint32_t)(((uint64_t)tick * (uint64_t)1000u) >> div_to_log2(timer_frequency));
    } else {
      time_ms = (uint32_t)(((uint64_t)tick * (uint64_t)1000u) / timer_frequency);
    }
  }

  return time_ms;
}

/*******************************************************************************
 * Converts 64-bits ticks in milliseconds.
 ******************************************************************************/
sl_status_t sl_sleeptimer_tick64_to_ms(uint64_t tick,
                                       uint64_t *ms)

{
  if ((tick <= UINT64_MAX / 1000)
      && (timer_frequency != 0u)) {
    if (is_power_of_2(timer_frequency)) {
      *ms =  (uint64_t)(((uint64_t)tick * (uint64_t)1000u) >> div_to_log2(timer_frequency));
      return SL_STATUS_OK;
    } else {
      *ms = (uint64_t)(((uint64_t)tick * (uint64_t)1000u) / timer_frequency);
      return SL_STATUS_OK;
    }
  } else {
    return SL_STATUS_INVALID_PARAMETER;
  }
}

/*******************************************************************************
 * Process timer interrupt.
 *
 * @param local_flag Flag indicating the type of timer interrupt.
 ******************************************************************************/
void process_timer_irq(uint8_t local_flag)
{
  CORE_DECLARE_IRQ_STATE;
  if (local_flag & SLEEPTIMER_EVENT_OF) {
#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
    uint32_t timer_freq = sl_sleeptimer_get_timer_frequency();

    overflow_tick_rest += calculated_tick_rest;
    if (overflow_tick_rest >= timer_freq) {
      second_count++;
      overflow_tick_rest -= timer_freq;
    }
    second_count = second_count + calculated_sec_count;
#endif
    overflow_counter++;

    update_delta_list();

    if (timer_head) {
      set_comparator_for_next_timer();
    }
  }

  if (local_flag & SLEEPTIMER_EVENT_COMP) {
    sl_sleeptimer_timer_handle_t *current = NULL;

    uint32_t nb_timer_expire = 0u;
    uint16_t option_flags = 0;

    CORE_ENTER_ATOMIC();
    // Make sure the timers list is up to date with the time elapsed since the last update
    update_delta_list();

    // Process all timers that have expired.
    while ((timer_head) && (timer_head->delta == 0)) {
      sl_sleeptimer_timer_handle_t *temp = timer_head;
      current = timer_head;
      int32_t periodic_correction = 0u;
      int64_t timeout_temp = 0;
      bool skip_remove = false;

      // Process timers with higher priority first
      while ((temp != NULL) && (temp->delta == 0)) {
        if (current->priority > temp->priority) {
          current = temp;
        }
        temp = temp->next;
      }
      CORE_EXIT_ATOMIC();

      // Check if current periodic timer was delayed more than its actual timeout value
      // and keep it at the head of the timers list if it's the case so that the
      // callback function can be called the number of required time.
      if (current->timeout_periodic != 0u) {
        timeout_temp = current->timeout_periodic;

        periodic_correction = sleeptimer_hal_get_counter() - current->timeout_expected_tc;
        if (periodic_correction > timeout_temp) {
          skip_remove = true;
          current->timeout_expected_tc += current->timeout_periodic;
        }
      }

      // Remove current timer from timer list except if the current timer is a periodic timer
      // that was intentionally kept at the head of the timers list.
      if (skip_remove != true) {
        CORE_ENTER_ATOMIC();
        delta_list_remove_timer(current);
        CORE_EXIT_ATOMIC();
      }

      // Re-insert periodic timer that was previsouly removed from the list
      // and compensate for any deviation from the periodic timer frequency.
      if (current->timeout_periodic != 0u && skip_remove != true) {
        timeout_temp -= periodic_correction;
        EFM_ASSERT(timeout_temp >= 0);
        // Compensate for drift caused by ms to ticks conversion
        if (current->conversion_error > 0) {
          // Increment accumulated error by the ms to ticks conversion error
          current->accumulated_error += current->conversion_error;
          // If the accumulated error exceeds a tick, subtract that tick from the next
          // periodic timer's timeout value.
          if (current->accumulated_error >= 1000) {
            current->accumulated_error -= 1000;
            timeout_temp -= 1;
            current->timeout_expected_tc -= 1;
          }
        }
        CORE_ENTER_ATOMIC();
        delta_list_insert_timer(current, (sl_sleeptimer_tick_count_t)timeout_temp);
        current->timeout_expected_tc += current->timeout_periodic;
        CORE_EXIT_ATOMIC();
      }

      // Save current option flag and the number of timers that expired.
      option_flags = current->option_flags;
      nb_timer_expire++;

      // Call current timer callback function if any.
      if (current->callback != NULL) {
        current->callback(current, current->callback_data);
      }

      CORE_ENTER_ATOMIC();

      // Re-update the list to account for delays during timer's callback.
      update_delta_list();
    }

    // If the only timer expired is the internal Power Manager one,
    // from the Sleeptimer perspective, the system can go back to sleep after the ISR handling.
    sleep_on_isr_exit = false;
    if (nb_timer_expire == 1u) {
      if (option_flags & SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG) {
        sleep_on_isr_exit = true;
      }
    }

    if (timer_head) {
      set_comparator_for_next_timer();
    } else {
      sleeptimer_hal_disable_int(SLEEPTIMER_EVENT_COMP);
    }
    CORE_EXIT_ATOMIC();
  }
}

/*******************************************************************************
 * Timer expiration callback for the delay function.
 *
 * @param handle Pointer to handle to timer.
 * @param data Pointer to delay flag.
 ******************************************************************************/
static void delay_callback(sl_sleeptimer_timer_handle_t *handle,
                           void *data)
{
  volatile bool *wait_flag = (bool *)data;

  (void)handle;  // Unused parameter.

  *wait_flag = false;
}

/*******************************************************************************
 * Inserts a timer in the delta list.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout Timer timeout, in ticks.
 ******************************************************************************/
static void delta_list_insert_timer(sl_sleeptimer_timer_handle_t *handle,
                                    sl_sleeptimer_tick_count_t timeout)
{
  sl_sleeptimer_tick_count_t local_handle_delta = timeout;

#ifdef SL_CATALOG_POWER_MANAGER_PRESENT
  // If Power Manager is present, it's possible that a clock restore is needed right away
  // if we are in the context of a deepsleep and the timeout value is smaller than the restore time.
  // If it's the case, the restore will be started and the timeout value will be updated to match
  // the restore delay.
  if (handle->option_flags == 0) {
    uint32_t wakeup_delay = sli_power_manager_get_restore_delay();

    if (local_handle_delta < wakeup_delay) {
      local_handle_delta = wakeup_delay;
      sli_power_manager_initiate_restore();
    }
  }
#endif

  handle->delta = local_handle_delta;

  if (timer_head != NULL) {
    sl_sleeptimer_timer_handle_t *prev = NULL;
    sl_sleeptimer_timer_handle_t *current = timer_head;
    // Find timer position taking into accounts the deltas and priority.
    while (current != NULL
           && (local_handle_delta >= current->delta || current->delta == 0u
               || (((local_handle_delta - current->delta) == 0) && (handle->priority > current->priority)))) {
      local_handle_delta -= current->delta;
      handle->delta = local_handle_delta;
      prev = current;
      current = current->next;
    }

    // Insert timer in middle of delta list.
    if (prev != NULL) {
      prev->next = handle;
    } else {
      timer_head = handle;
    }
    handle->next = current;

    if (current != NULL) {
      current->delta -= local_handle_delta;
    }
  } else {
    timer_head = handle;
    handle->next = NULL;
  }
}

/*******************************************************************************
 * Removes a timer from delta list.
 *
 * @param handle Pointer to handle to timer.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
static sl_status_t delta_list_remove_timer(sl_sleeptimer_timer_handle_t *handle)
{
  sl_sleeptimer_timer_handle_t *prev = NULL;
  sl_sleeptimer_timer_handle_t *current = timer_head;

  // Retrieve timer in delta list.
  while (current != NULL && current != handle) {
    prev = current;
    current = current->next;
  }

  if (current != handle) {
    return SL_STATUS_INVALID_STATE;
  }

  if (prev != NULL) {
    prev->next = handle->next;
  } else {
    timer_head = handle->next;
  }

  // Update delta of next timer
  if (handle->next != NULL) {
    handle->next->delta += handle->delta;
  }

  return SL_STATUS_OK;
}

/*******************************************************************************
 * Sets comparator for next timer.
 ******************************************************************************/
static void set_comparator_for_next_timer(void)
{
  if (timer_head->delta > 0) {
    sl_sleeptimer_tick_count_t compare_value;

    compare_value = last_delta_update_count + timer_head->delta;

    sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_COMP);
    sleeptimer_hal_set_compare(compare_value);
  } else {
    // In case timer has already expire, don't attempt to set comparator. Just
    // trigger compare match interrupt.
    sleeptimer_hal_enable_int(SLEEPTIMER_EVENT_COMP);
    sleeptimer_hal_set_int(SLEEPTIMER_EVENT_COMP);
  }

  update_next_timer_to_expire_is_power_manager();
}

/*******************************************************************************
 * Updates timer list's deltas.
 ******************************************************************************/
static void update_delta_list(void)
{
  sl_sleeptimer_tick_count_t current_cnt = sleeptimer_hal_get_counter();
  sl_sleeptimer_timer_handle_t *timer_handle = timer_head;
  sl_sleeptimer_tick_count_t time_diff = current_cnt - last_delta_update_count;

  // Go through the delta timer list and update every necessary deltas
  // according to the time elapsed since the last update.
  while (timer_handle != NULL && time_diff > 0) {
    if (timer_handle->delta >= time_diff) {
      timer_handle->delta -= time_diff;
      time_diff = 0;
    } else {
      time_diff -= timer_handle->delta;
      timer_handle->delta = 0;
    }
    timer_handle = timer_handle->next;
  }

  last_delta_update_count = current_cnt;
}

/*******************************************************************************
 * Creates and start a 32 bits timer.
 *
 * @param handle Pointer to handle to timer.
 * @param timeout_initial Initial timeout, in timer ticks.
 * @param timeout_periodic Periodic timeout, in timer ticks. This timeout
 *        applies once timeoutInitial expires. Can be set to 0 for a one
 *        shot timer.
 * @param callback Callback function that will be called when
 *        initial/periodic timeout expires.
 * @param callback_data Pointer to user data that will be passed to callback.
 * @param priority Priority of callback. Useful in case multiple timer expire
 *        at the same time. 0 = highest priority.
 *
 * @return 0 if successful. Error code otherwise.
 ******************************************************************************/
static sl_status_t create_timer(sl_sleeptimer_timer_handle_t *handle,
                                sl_sleeptimer_tick_count_t timeout_initial,
                                sl_sleeptimer_tick_count_t timeout_periodic,
                                sl_sleeptimer_timer_callback_t callback,
                                void *callback_data,
                                uint8_t priority,
                                uint16_t option_flags)
{
  CORE_DECLARE_IRQ_STATE;

  handle->priority = priority;
  handle->callback_data = callback_data;
  handle->next = NULL;
  handle->timeout_periodic = timeout_periodic;
  handle->callback = callback;
  handle->option_flags = option_flags;
  if (timeout_periodic == 0) {
    handle->timeout_expected_tc = sleeptimer_hal_get_counter() + timeout_initial;
  } else {
    handle->timeout_expected_tc = sleeptimer_hal_get_counter() + timeout_periodic;
  }

  if (timeout_initial == 0) {
    handle->delta = 0;
    if (handle->callback != NULL) {
      handle->callback(handle, handle->callback_data);
    }
    if (timeout_periodic != 0) {
      timeout_initial = timeout_periodic;
    } else {
      return SL_STATUS_OK;
    }
  }

#if ((SL_SLEEPTIMER_PERIPHERAL == SL_SLEEPTIMER_PERIPHERAL_SYSRTC) \
  && defined(SL_CATALOG_POWER_MANAGER_PRESENT)                     \
  && !defined(SL_CATALOG_POWER_MANAGER_NO_DEEPSLEEP_PRESENT))
  if (option_flags == (SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG | SLI_SLEEPTIMER_POWER_MANAGER_HF_ACCURACY_CLK_FLAG)) {
    HFXO0->CTRL |= HFXO_CTRL_EM23ONDEMAND;
    sleeptimer_hal_set_compare_prs_hfxo_startup(timeout_initial);
    return SL_STATUS_OK;
  }
#endif

  CORE_ENTER_CRITICAL();
  update_delta_list();
  delta_list_insert_timer(handle, timeout_initial);

  // If first timer, update timer comparator.
  if (timer_head == handle) {
    set_comparator_for_next_timer();
  }

  CORE_EXIT_CRITICAL();

  return SL_STATUS_OK;
}

/*******************************************************************************
 * Updates internal flag that indicates if next timer to expire is the power
 * manager's one.
 ******************************************************************************/
static void update_next_timer_to_expire_is_power_manager(void)
{
  sl_sleeptimer_timer_handle_t *current = timer_head;
  uint32_t delta_diff_with_first = 0;

  next_timer_to_expire_is_power_manager = false;

  while (delta_diff_with_first <= 1) {
    if (current->option_flags & SLI_SLEEPTIMER_POWER_MANAGER_EARLY_WAKEUP_TIMER_FLAG) {
      next_timer_to_expire_is_power_manager = true;
      break;
    }

    current = current->next;
    if (current == NULL) {
      break;
    }

    delta_diff_with_first += current->delta;
  }
}

/**************************************************************************//**
 * Determines if the power manager's early wakeup expired during the last ISR
 * and it was the only timer to expire in that period.
 *
 * @return true if power manager sleep can return to sleep,
 *         false otherwise.
 *****************************************************************************/
bool sl_sleeptimer_is_power_manager_early_restore_timer_latest_to_expire(void)
{
  CORE_DECLARE_IRQ_STATE;
  bool sleep;

  CORE_ENTER_ATOMIC();
  sleep = sleep_on_isr_exit;
  CORE_EXIT_ATOMIC();

  return sleep;
}

/*******************************************************************************
 * Convert dividend to logarithmic value. It only works for even
 * numbers equal to 2^n.
 *
 * @param  div An unscaled dividend.
 *
 * @return Logarithm of 2.
 ******************************************************************************/
__STATIC_INLINE uint32_t div_to_log2(uint32_t div)
{
  return 31UL - __CLZ(div);  // Count leading zeroes and "reverse" result.
}

/*******************************************************************************
 * Determines if a number is a power of two.
 *
 * @param  nbr Input value.
 *
 * @return True if the number is a power of two.
 ******************************************************************************/
__STATIC_INLINE bool is_power_of_2(uint32_t nbr)
{
  if ((((nbr) != 0u) && (((nbr) & ((nbr) - 1u)) == 0u))) {
    return true;
  } else {
    return false;
  }
}

#if SL_SLEEPTIMER_WALLCLOCK_CONFIG
/*******************************************************************************
 * Compute the day of the week.
 *
 * @param day Days since January 1st of 1970.
 *
 * @return the day of the week.
 ******************************************************************************/
static sl_sleeptimer_weekDay_t compute_day_of_week(uint32_t day)
{
  return (sl_sleeptimer_weekDay_t)((day + 4) % 7); // January 1st was a Thursday(4) in 1970
}

/*******************************************************************************
 * Compute the day of the week.
 *
 * @param day Days since January 1st of 1900.
 *
 * @return the day of the week.
 ******************************************************************************/
static sl_sleeptimer_weekDay_t compute_day_of_week_64(uint64_t day)
{
  return (sl_sleeptimer_weekDay_t)((day + 1) % 7);  // January 1st was a Monday(1) in 1900
}

/*******************************************************************************
 * Compute the day of the year. This function assumes that the inputs are properly
 * sanitized.
 *
 * @param month Number of months since January.
 * @param day Day of the month
 * @param is_leap_year Specifies if the year computed against is a leap year.
 *
 * @return the number of days since the beginning of the year
 ******************************************************************************/
static uint16_t compute_day_of_year(sl_sleeptimer_month_t month, uint8_t day, bool is_leap_year)
{
  uint8_t i;
  uint16_t dayOfYear = 0;

  for (i = 0; i < month; ++i) {
    dayOfYear += days_in_month[is_leap_year][i];
  }
  dayOfYear += day;

  return dayOfYear;
}

/*******************************************************************************
 * Checks if the year is a leap year.
 *
 * @param year Year to check.
 *
 * @return true if the year is a leap year. False otherwise.
 ******************************************************************************/
static bool is_leap_year(uint16_t year)
{
  // 1900 is not a leap year but 0 % anything is 0.
  if (year == 0) {
    return false;
  }

  bool leap_year;

  leap_year = (((year %   4u) == 0u)
               && (((year % 100u) != 0u) || ((year % 400u) == 0u))) ? true : false;

  return (leap_year);
}

/*******************************************************************************
 * Checks if the time stamp, format and time zone are
 *  within the supported range.
 *
 * @param base_year Year to start from to compute leap days.
 * @param current_year Year end at for computing leap days.
 *
 * @return leap_days Days number of leap days between base_year and current_year.
 ******************************************************************************/
static uint16_t number_of_leap_days(uint32_t base_year, uint32_t current_year)
{
  // Regular leap years
  uint16_t lo_reg = (base_year - 0) / 4;
  uint16_t hi_reg = (current_year - 1) / 4;
  uint16_t leap_days = hi_reg - lo_reg;

  // Account for non leap years
  uint16_t lo_century = (base_year - 0) / 100;
  uint16_t hi_century = (current_year - 1) / 100;
  leap_days -= hi_century - lo_century;

  // Account for quad century leap years
  uint16_t lo_quad = (base_year - 0) / 400;
  uint16_t hi_quad = (current_year - 1) / 400;
  leap_days += hi_quad - lo_quad;

  return (leap_days);
}

/*******************************************************************************
 * Checks if the time stamp, format and time zone are
 *  within the supported range.
 *
 * @param time Time stamp to check.
 * @param format Format of the time.
 * @param time_zone Time zone offset in second.
 *
 * @return true if the time is valid. False otherwise.
 ******************************************************************************/
static bool is_valid_time(sl_sleeptimer_timestamp_t time,
                          sl_sleeptimer_time_format_t format,
                          sl_sleeptimer_time_zone_offset_t time_zone)
{
  bool valid_time = false;

  // Check for overflow.
  if ((time_zone < 0 && time > (uint32_t)abs(time_zone)) \
      || (time_zone >= 0 && (time <= UINT32_MAX - time_zone))) {
    valid_time = true;
  }
  if (format == TIME_FORMAT_UNIX) {
    if (time > TIME_UNIX_TIMESTAMP_MAX) { // Check if Unix time stamp is an unsigned 31 bits.
      valid_time = false;
    }
  } else {
    if ((format == TIME_FORMAT_NTP) && (time >= TIME_NTP_EPOCH_OFFSET_SEC)) {
      valid_time &= true;
    } else if ((format == TIME_FORMAT_ZIGBEE_CLUSTER) && (time <= TIME_UNIX_TIMESTAMP_MAX - TIME_ZIGBEE_EPOCH_OFFSET_SEC)) {
      valid_time &= true;
    } else {
      valid_time = false;
    }
  }
  return valid_time;
}

/*******************************************************************************
 * Checks if the time stamp, format and time zone are
 *  within the supported range.
 *
 * @param time Time stamp to check.
 * @param format Format of the time.
 * @param time_zone Time zone offset in second.
 *
 * @return true if the time is valid. False otherwise.
 ******************************************************************************/
static bool is_valid_time_64(sl_sleeptimer_timestamp_64_t time,
                             sl_sleeptimer_time_format_t format,
                             sl_sleeptimer_time_zone_offset_t time_zone)
{
  bool valid_time = false;

  // Check for overflow.
  if ((time_zone < 0 && time > (uint64_t)abs(time_zone))
      || (time_zone >= 0 && (time <= UINT64_MAX - time_zone))) {
    valid_time = true;
  }
  if (format == TIME_FORMAT_UNIX_64_BIT) {
    if (time > TIME_64_BIT_UNIX_TIMESTAMP_MAX) { // Check if time stamp is an unsigned 64 bits.
      valid_time = false;
    }
  }
  return valid_time;
}

/*******************************************************************************
 * Checks if the date is valid.
 *
 * @param date Date to check.
 *
 * @return true if the date is valid. False otherwise.
 ******************************************************************************/
static bool is_valid_date(sl_sleeptimer_date_t *date)
{
  if ((date == NULL)
      || (date->year > TIME_UNIX_YEAR_MAX)
      || (date->month > MONTH_DECEMBER)
      || (date->month_day == 0 || date->month_day > days_in_month[is_leap_year(date->year)][date->month])
      || (date->hour > 23)
      || (date->min > 59)
      || (date->sec > 59)) {
    return false;
  }

  // Unix is valid until the 19th of January 2038 at 03:14:07
  if (date->year == TIME_UNIX_YEAR_MAX) {
    if ((uint8_t)date->month > (uint8_t)MONTH_JANUARY) {
      return false;
    } else if (date->month_day > 19) {
      return false;
    } else if (date->hour > 3) {
      return false;
    } else if (date->min > 14) {
      return false;
    } else if (date->sec > 7) {
      return false;
    }
  }

  return true;
}

/*******************************************************************************
 * Checks if the date is valid.
 *
 * @param date Date to check.
 *
 * @return true if the date is valid. False otherwise.
 ******************************************************************************/
static bool is_valid_date_64(sl_sleeptimer_date_t *date)
{
  if ((date == NULL)
      || (date->year > TIME_64_BIT_YEAR_MAX)
      || (date->month > MONTH_DECEMBER)
      || (date->month_day == 0 || date->month_day > days_in_month[is_leap_year(date->year)][date->month])
      || (date->hour > 23)
      || (date->min > 59)
      || (date->sec > 59)) {
    return false;
  }
  return true;
}
#endif

/*******************************************************************************
 * @brief
 *   Gets the precision (in PPM) of the sleeptimer's clock.
 *
 * @return
 *   Clock accuracy, in PPM.
 *
 ******************************************************************************/
uint16_t sl_sleeptimer_get_clock_accuracy(void)
{
  return sleeptimer_hal_get_clock_accuracy();
}

/***************************************************************************//**
 * @brief
 *   Update sleep_on_isr_exit flag.
 *
 * @param flag Value update_sleep_on_isr_exit will be set to.
 ******************************************************************************/
void sli_sleeptimer_update_sleep_on_isr_exit(bool flag)
{
  sleep_on_isr_exit = flag;
}

/*******************************************************************************
 * Gets the associated peripheral capture channel current value.
 ******************************************************************************/
uint32_t sli_sleeptimer_get_capture(void)
{
  return sleeptimer_hal_get_capture();
}

/*******************************************************************************
 * Resets the PRS signal triggered by the associated peripheral.
 ******************************************************************************/
void sli_sleeptimer_reset_prs_signal(void)
{
  sleeptimer_hal_reset_prs_signal();
}
