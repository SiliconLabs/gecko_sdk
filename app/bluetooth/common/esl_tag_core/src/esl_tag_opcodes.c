/***************************************************************************//**
 * @file
 * @brief ESL Tag opcode processor implementation
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdio.h>
#include <stdbool.h>
#include "esl_tag_log.h"
#include "esl_tag_tlv.h"
#include "esl_tag_core.h"
#include "esl_tag_crypto.h"
#include "esl_tag_errors.h"
#include "esl_tag_led_core.h"
#include "esl_tag_internal.h"
#include "esl_tag_response.h"
#include "esl_tag_image_core.h"
#include "esl_tag_sensor_core.h"
#include "esl_tag_display_core.h"
#include "esl_tag_battery_internal.h"
#include "esl_tag_opcodes.h"
#include "app_scheduler.h"

// ESL Access Point unassociate & reset command delay value [in milliseconds]
#define ESL_CORE_DEFAULT_COMMAND_DELAY_MS 750

// ESL timed command absolute delay max value: 48 days [in milliseconds]
#define ESL_PLAUSIBLE_DELAY_MAX_VALUE_MS  4147200000  // ESLS d09r03, 3.10.2

// ESL response slot default value
#define ESL_NO_PAWR_RESPONSE             -1

// ESL timed (delayed) task type enumeration
typedef enum {
  esl_delayed_task_unknown = 0,
  esl_delayed_task_display,
  esl_delayed_task_led
} esl_delayed_task_type_t;

// ESL scheduled object type to keep track of a scheduled timed task
typedef struct {
  bool                        is_running;
  uint32_t                    absolute_time;
  app_scheduler_task_handle_t scheduler;
  esl_delayed_task_type_t     type;
  uint8_t                     peripheral_index;
} esl_scheduled_object_t;

// ESL timed commands register type to keep track of all scheduled items
typedef struct {
  esl_scheduled_object_t  schedule_list[APP_SCHEDULER_MAX_QUEUE_SIZE];
  uint8_t                 led_count;
  uint8_t                 display_count;
} esl_timed_command_register_t;

// ESL timed commands register instance to keep track of actual pending commands
static esl_timed_command_register_t pending_commands = { 0 };

/*******************************************************************************
 * Expose ESL LED control parameters in human readable format to debug output
 *
 * @param[in] control_data pointer to LED control data to decode
 ******************************************************************************/
static void esl_debug_led_control_parameters(esl_led_control_t *control_data)
{
#ifdef SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
  esl_led_gamut_control_t brightness = esl_led_get_brightness(control_data->gamut);

  // calculate brightness component as percentage
  brightness = ESL_LED_LEVEL_STEP_PERCENTAGE * brightness + ESL_LED_LEVEL_STEP_PERCENTAGE;

  sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                ESL_LOG_LEVEL_INFO,
                "    LED %u ",
                control_data->index);

  switch (control_data->repeats) {
    case ESL_LED_REPEATS_TYPE_TIME:
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                    ESL_LOG_LEVEL_INFO, "turned on.");
      break;

    case ESL_LED_REPEATS_TYPE_COUNT:
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                    ESL_LOG_LEVEL_INFO, "turned off.");
      break;

    default: {
      esl_led_repeats_type_t duration;

      duration = control_data->repeats >> ESL_LED_REPEATS_DURATION_SHIFT;
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                    ESL_LOG_LEVEL_INFO, "is flashing ");
      (void)duration; // remove the compiler warning if logging is disabled

      if ((control_data->repeats & ESL_LED_REPEATS_TYPE_MASK) == 0) {
        sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                      ESL_LOG_LEVEL_INFO, "%u times.",
                      duration);
      } else {
        sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                      ESL_LOG_LEVEL_INFO, "for %u seconds.",
                      duration);
      }
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                    ESL_LOG_LEVEL_INFO, "    Pattern: 0x");
      for (uint32_t i = sizeof(control_data->pattern.data); i; ) {
        sl_bt_esl_log(ESL_LOG_COMPONENT_LED | ESL_LOG_FLAG_APPEND,
                      ESL_LOG_LEVEL_INFO,
                      "%02X",
                      (uint8_t) control_data->pattern.data[--i]);
      }
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                    ESL_LOG_LEVEL_INFO,
                    "    On period %u ms, off period %u ms.",
                    2 * control_data->pattern.bit_on_period,
                    2 * control_data->pattern.bit_off_period);
    } break;
  }

  if (control_data->repeats != ESL_LED_REPEATS_TYPE_COUNT) {
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                  ESL_LOG_LEVEL_INFO,
                  "    Brightness set to %u%%",
                  brightness);

    if (esl_led_is_srgb(control_data->index)) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                    ESL_LOG_LEVEL_INFO,
                    "    Red: %u, Green: %u, Blue: %u",
                    esl_led_get_red_value(control_data->gamut),
                    esl_led_get_green_value(control_data->gamut),
                    esl_led_get_blue_value(control_data->gamut));
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_NOHEADER,
                    ESL_LOG_LEVEL_INFO,
                    "    Color field ignored.");
    }
  }
#else
  (void)control_data;
#endif // SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
}

/*******************************************************************************
 * ESL delayed unassociate task function
 *
 * @param[in] data Unused by this function but mandatory for app_scheduler tasks
 * @param[in] size Unused by this function but mandatory for app_scheduler tasks
 ******************************************************************************/
static void esl_delayed_unassociate(void *p_event_data, uint16_t event_size)
{
  (void)event_size;
  (void)p_event_data;

  esl_core_unassociate();
}

/*******************************************************************************
 * ESL delayed reset task function
 *
 * @param[in] data Unused by this function but mandatory for app_scheduler tasks
 * @param[in] size Unused by this function but mandatory for app_scheduler tasks
 ******************************************************************************/
static void esl_delayed_reset(void *p_event_data, uint16_t event_size)
{
  (void)event_size;
  (void)p_event_data;

  // delete bonding data
  (void)sl_bt_sm_delete_bondings();
  // system reset will restore the factory default state
  sl_bt_system_reset(sl_bt_system_boot_mode_normal);
}

/*******************************************************************************
 * ESL cleanup delayed task
 *
 * @param[in] cleanup_object pointer to esl_scheduled_object_t to remove from
 *                           the list of running scheduler tasks
 * @param[in] counter pointer to pending led or pending display task counter
 * @param[in] flag esl_basic_state_t flag to clear if counter reach zero
 * @note cleanup_object counter can be NULL
 ******************************************************************************/
static void cleanup_delayed_task(esl_scheduled_object_t *cleanup_object,
                                 uint8_t *counter,
                                 esl_basic_state_t flag)
{
  // counter can't be NULL!
  sl_bt_esl_assert(counter != NULL);

  if (cleanup_object) {
    CORE_DECLARE_IRQ_STATE;
    // accessing the register shall be an atomic operation
    CORE_ENTER_CRITICAL();
    // clear the running flag and stop the periodic timer
    cleanup_object->is_running = false;
    cleanup_object->type = esl_delayed_task_unknown;
    CORE_EXIT_CRITICAL();
  }

  // decrease pending count down to zero
  if (*counter && --(*counter) == 0) {
    // clear pending display basic state bit on demand
    esl_core_set_basic_state_bit(flag, ESL_CLEAR);
  }
}

/*******************************************************************************
 * ESL timed LED control task function
 *
 * @param[in] data contains pending_commands.schedule_list index and
 *                 esl_led_control_t data concatenated
 * @param[in] size Overall size of the data above
 ******************************************************************************/
static void esl_delayed_led(void *p_event_data, uint16_t event_size)
{
  // Check for the proper size, skip anything that seems invalid
  if (event_size == (sizeof(uint16_t) + sizeof(esl_led_control_t))) {
    esl_led_control_t *control_data;
    // status for internal evaluation, only
    sl_status_t result      = SL_STATUS_FAIL;
    // get register index - always at the first event data position
    uint16_t register_index = *(uint16_t *)p_event_data;
    // helper pointer for byte positioning over p_event_data
    uint8_t  *data_p = ((uint8_t *)p_event_data) + sizeof(register_index);
    // backup copy last error code, if any
    const esl_error_t last_error = esl_core_get_last_error();

    // get the event specific data according to ESLS 3.9.2.10 LED Control
    control_data = (esl_led_control_t *)data_p;
    // call actual led control
    result = esl_led_control(control_data);
    // revert last error code since timed commands shall not set any response!
    esl_core_set_last_error(last_error);

    cleanup_delayed_task(&pending_commands.schedule_list[register_index],
                         &pending_commands.led_count,
                         ESL_BASIC_STATE_PENDING_LED_BIT);
    (void)result; // suppress the compiler warning if sl_bt_esl_log disabled

    // check results, log accordingly
    if (result != SL_STATUS_OK) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_WARNING,
                    "Timed led control failed with status 0x%02lx!",
                    result);
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_INFO,
                    "Timed control as follows:");
      esl_debug_led_control_parameters(control_data);
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_DEBUG,
                    "Still pending %u",
                    pending_commands.led_count);
    }
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ESL_LOG_LEVEL_WARNING,
                  "Invalid parameters for timed led control!");
  }
}

/*******************************************************************************
 * ESL timed display image task function
 *
 * @param[in] data contains pending_commands.schedule_list index, display_index
 *                 and image index values concatenated
 * @param[in] size Overall size of the data above
 ******************************************************************************/
static void esl_delayed_display(void *p_event_data, uint16_t event_size)
{
  // Check for the proper size, skip anything that seems invalid
  if (event_size == (sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t))) {
    // get register index - always at the first event data position
    uint16_t  register_index = *(uint16_t *)p_event_data;
    // get the event specific data: display index first, then image index
    uint8_t   *display_index = ((uint8_t *)p_event_data) + sizeof(register_index);
    uint8_t   *image_index   = display_index + sizeof(*display_index);
    // status for internal evaluation, only
    sl_status_t result       = SL_STATUS_FAIL;
    // backup copy last error code, if any
    const esl_error_t last_error = esl_core_get_last_error();
    // call actual display update
    result = esl_display_update(*display_index, *image_index);
    // revert last error code since timed commands shall not set any response!
    esl_core_set_last_error(last_error);

    cleanup_delayed_task(&pending_commands.schedule_list[register_index],
                         &pending_commands.display_count,
                         ESL_BASIC_STATE_PENDING_DISPLAY_BIT);
    (void)result; // suppress the compiler warning if sl_bt_esl_log disabled

    // check results, log accordingly
    if (result != SL_STATUS_OK) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_WARNING,
                    "Timed display failed with status 0x%02lx!",
                    result);
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_INFO,
                    "Timed image %u on display %u",
                    *image_index,
                    *display_index);
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE, ESL_LOG_LEVEL_DEBUG, "Still pending %u",
                    pending_commands.display_count);
    }
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ESL_LOG_LEVEL_WARNING,
                  "Invalid parameters for timed display!");
  }
}

/*******************************************************************************
 * Remove an already scheduled task
 *
 * @param[in] object ESL scheduled object to be removed from the task scheduler
 ******************************************************************************/
static void esl_remove_delayed_command(esl_scheduled_object_t *object)
{
  sl_bt_esl_assert(object != NULL);            // Object can't be NULL!
  sl_bt_esl_assert(object->scheduler != NULL); // Object shall be initialized!
  // remove task from the scheduler
  (void)app_scheduler_remove(object->scheduler);

  // decrement appropriate counts after removal - on successful re-
  // scheduling they will be adjusted again in esl_core_process_opcode
  if (object->type == esl_delayed_task_display) {
    cleanup_delayed_task(object,
                         &pending_commands.display_count,
                         ESL_BASIC_STATE_PENDING_DISPLAY_BIT);
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ESL_LOG_LEVEL_DEBUG,
                  "Display task deleted, still pending: %u",
                  pending_commands.display_count);
  } else if (object->type == esl_delayed_task_led) {
    cleanup_delayed_task(object,
                         &pending_commands.led_count,
                         ESL_BASIC_STATE_PENDING_LED_BIT);
    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ESL_LOG_LEVEL_DEBUG,
                  "LED task deleted, still pending: %u",
                  pending_commands.led_count);
  }
}

/*******************************************************************************
 * Add a task to be scheduled with mandatory requested time and data parameters
 *
 * @param[in] task Task function to be scheduled
 * @param[in] requested_time Absolute time when the task needs to be run
 * @param[in] data The data that is passed to the task
 * @param[in] size The size of the data
 *
 * @note Deletes a pending command if the requested time is zero, according to
 *       ESL Service specification d095r13 Section 3.9.2.9.1 Handling multiple
 *       Display Timed Image commands3.9.2.11.1 Handling multiple LED Timed
 *       Control commands.
 * @return Status of the operation
 ******************************************************************************/
static sl_status_t esl_add_delayed_command(app_scheduler_task_t task,
                                           uint32_t requested_time,
                                           void *data,
                                           size_t size)
{
  CORE_DECLARE_IRQ_STATE;
  esl_delayed_task_type_t type = esl_delayed_task_unknown;
  sl_status_t result           = SL_STATUS_OK;
  uint32_t    absolute_time    = 0;
  uint16_t    free_index       = APP_SCHEDULER_MAX_QUEUE_SIZE;
  uint16_t    search_index     = 0;
  uint8_t     peripheral_index = 0;
  uint8_t     pending_flag     = 0;
  uint8_t     *counter;

  // set local type according to task type
  if (task == &esl_delayed_display) {
    type = esl_delayed_task_display;
    peripheral_index = ((esl_led_control_t *)data)->index;
    counter = &pending_commands.display_count;
    pending_flag = ESL_BASIC_STATE_PENDING_DISPLAY_BIT;
  } else if (task == &esl_delayed_led) {
    type = esl_delayed_task_led;
    peripheral_index = *(uint8_t *)data;
    counter = &pending_commands.led_count;
    pending_flag = ESL_BASIC_STATE_PENDING_LED_BIT;
  } else {
    // invalid task to add delayed!
    return SL_STATUS_ABORT;
  }

  // accessing the pending commands register shall be an atomic operation
  CORE_ENTER_CRITICAL();
  // for each entry search for either a free slot, or an occupied slot with the
  // same peripheral index
  for (; search_index < APP_SCHEDULER_MAX_QUEUE_SIZE; search_index++) {
    esl_scheduled_object_t *current_object;

    current_object = &pending_commands.schedule_list[search_index];

    // if running, then search for special conditions described in ESL Service
    // specification d095r13, Section 3.9.2.9.1 and Section 3.9.2.11.1
    if (current_object->is_running) {
      if (type == current_object->type && peripheral_index == current_object->peripheral_index) {
        // remove same tasks with same absolute_time of what's now requested
        // or if requested time is 0 (delete command)
        if (!requested_time || requested_time == current_object->absolute_time) {
          // override actual free_index for re-scheduling the task
          free_index = search_index;

          absolute_time = current_object->absolute_time;  // used as backup copy
          sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                        ESL_LOG_LEVEL_INFO,
                        "Found running task at index %u, time %lu",
                        free_index, requested_time);

          esl_remove_delayed_command(current_object);
          result = SL_STATUS_DELETED;
        } else {
          // only single delayed command per peripheral index is allowed!
          result = SL_STATUS_FULL;
        }
        break;
      }
    } else if (free_index == APP_SCHEDULER_MAX_QUEUE_SIZE) {
      // get first free available slot in the first place
      free_index = search_index;
    }
  }
  CORE_EXIT_CRITICAL();

  if (!requested_time) {
    // was a delete request, report OK only if pending task existed for given index!
    if (result == SL_STATUS_DELETED) {
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_INFO,
                    "Deleted timed request at %lu",
                    absolute_time);
      return SL_STATUS_OK;
    } else {
      esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
      result = SL_STATUS_INVALID_PARAMETER;
    }
  } else if (free_index < APP_SCHEDULER_MAX_QUEUE_SIZE && result != SL_STATUS_FULL) {
    // if there was a free slot available for scheduling and not delete request
    uint32_t delay = 0;
    app_scheduler_task_handle_t *handle_p = NULL;
    const uint16_t extended_size = size + sizeof(free_index);
    uint8_t extended_data[APP_SCHEDULER_MAX_DATA_SIZE] = { 0 };

    handle_p = &pending_commands.schedule_list[free_index].scheduler;
    result   = esl_core_read_absolute_time(&absolute_time);

    if (result != SL_STATUS_OK) {
      esl_core_set_last_error(ESL_ERROR_INVALID_STATE);
    } else {
      memcpy(extended_data, &free_index, sizeof(free_index));
      memcpy(&extended_data[sizeof(free_index)], data, size);

      delay  = requested_time - absolute_time;

      if (delay <= ESL_PLAUSIBLE_DELAY_MAX_VALUE_MS) {
        result = app_scheduler_add_delayed(task, delay, extended_data,
                                           extended_size, handle_p);

        if (result == SL_STATUS_OK) {
          esl_scheduled_object_t *current_object;
          current_object = &pending_commands.schedule_list[free_index];

          current_object->is_running       = true;
          current_object->absolute_time    = requested_time;
          current_object->type             = type;
          current_object->peripheral_index = peripheral_index;

          // increment counter on successful scheduling
          (*counter)++;
          // set pending bit of basic state, accordingly
          esl_core_set_basic_state_bit(pending_flag, ESL_SET);
          sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                        ESL_LOG_LEVEL_INFO,
                        "Register timed command after %lu ms",
                        delay);
        } else {
          sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                        ESL_LOG_LEVEL_ERROR,
                        "Register timed command failed with status %lu",
                        result);
        }
      } else {
        esl_core_set_last_error(ESL_ERROR_IMPLAUSIBLE_TIME);
        result = SL_STATUS_ABORT;
      }
    }
  } else {
    esl_core_set_last_error(ESL_ERROR_QUEUE_FULL);
    result = SL_STATUS_NO_MORE_RESOURCE;
  }

  sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                ESL_LOG_LEVEL_INFO,
                "Timed request at %lu result: 0x%04lx",
                requested_time, result);
  return result;
}

void esl_reschedule_delayed_commands(uint32_t current_absolute_time)
{
  sl_status_t result;
  uint16_t    search_index = 0;
  CORE_DECLARE_IRQ_STATE;

  // accessing the pending commands register shall be an atomic operation
  CORE_ENTER_CRITICAL();
  // for each entry search for occupied slots
  for (; search_index < APP_SCHEDULER_MAX_QUEUE_SIZE; search_index++) {
    esl_scheduled_object_t *current_object;
    uint32_t delay = 0;

    current_object = &pending_commands.schedule_list[search_index];

    // if running, then needs to be adjusted
    if (current_object->is_running) {
      uint32_t previous_delay;
      delay = current_object->absolute_time - current_absolute_time;

      if (delay > ESL_PLAUSIBLE_DELAY_MAX_VALUE_MS) {
        delay = 0; // underflow means the time has passed, run immediately!
      }
      (void)app_scheduler_get_timeout(current_object->scheduler, &previous_delay);
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_DEBUG,
                    "Task %d re-schedule from %ld ms delay to %ld ms.",
                    search_index, previous_delay, delay);
      result = app_scheduler_reschedule(current_object->scheduler, delay);

      if (result != SL_STATUS_OK) {
        sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                      ESL_LOG_LEVEL_ERROR,
                      "Task %d re-schedule failed!",
                      search_index);
        current_object->is_running = false;
        current_object->type = esl_delayed_task_unknown;
      }
    }
  }
  CORE_EXIT_CRITICAL();
}

void esl_core_purge_delayed_commands()
{
  CORE_DECLARE_IRQ_STATE;
  uint16_t search_index = 0;

  // accessing the pending commands register shall be an atomic operation
  CORE_ENTER_CRITICAL();
  // for each entry search for either a free slot, or an occupied slot with the
  // same absolute_time value of current requested_time
  for (; search_index < APP_SCHEDULER_MAX_QUEUE_SIZE; search_index++) {
    esl_scheduled_object_t *current_object;

    current_object = &pending_commands.schedule_list[search_index];

    // if running, then stop it
    if (current_object->is_running) {
      esl_remove_delayed_command(current_object);
    }
  }
  CORE_EXIT_CRITICAL();
}

sl_status_t esl_core_parse_all_opcodes(void *data, uint8_t len)
{
  esl_address_t esl_address = 0;
  sl_status_t   result = SL_STATUS_INVALID_STATE;

  bool          has_notifications = esl_core_has_notifications();
  int16_t       response_slot = ESL_NO_PAWR_RESPONSE;

  // Don't allow any command before boot
  if (esl_core_get_status() != esl_state_boot) {
    // payload length shall be within reasonable limits
    if (ESL_PAYLOAD_MAX_LENGTH > len && ESL_PAYLOAD_MIN_LENGTH <= len) {
      esl_id_t      self_id;
      uint8_t       *next_opcode = data;
      uint8_t       tlv_count    = 0;

      result = esl_core_read_esl_address(&esl_address);

      // ESL Address won't be configured properly after factory reset processed,
      // skip processing in that case
      if (result != SL_STATUS_OK && has_notifications) {
        esl_error_t error_code = ESL_ERROR_UNSPECIFIED; // according to ESLS 3.9.2.4
        // return status of esl_core_build_response can be ignored in this case
        // because there's nothing to do with it, anyway
        (void)esl_core_build_response(ESL_TLV_RESPONSE_ERROR, &error_code);
      }

      // before command processing check if Service Needed flag needs to be set
      // due to low battery - whenever a valid ESL message is received
      esl_sensor_core_check_battery_level();

      self_id = esl_core_get_id(esl_address);

      // parse all possible opcodes
      while (len >= ESL_TLV_OPCODE_MIN_LENGTH && result == SL_STATUS_OK) {
        tlv_t     opcode     = *next_opcode++;  // there's an opcode, first
        esl_id_t  id         = *next_opcode++;  // then the ESL id follows
        uint8_t   *next_data = next_opcode;     // point to data (if any)
        uint8_t   processed_length;

        // adjust 'len' by lengths of opcode and ESL id
        len -= ESL_TLV_OPCODE_MIN_LENGTH;

        // process current opcode
        result           = esl_core_process_opcode(self_id,
                                                   id,
                                                   opcode,
                                                   (void *)&next_data);
        processed_length = (next_data - next_opcode); // might be 0, it's OK

        // check for bad edge case (e.g. after a misformatted TLV)
        if (processed_length > len) {
          result = SL_STATUS_FAIL;
        } else {
          len         -= processed_length;
          next_opcode += processed_length;

          // track the proper response slot
          if (id == self_id) {
            response_slot = tlv_count;
          }

          tlv_count++;
        }
      }
    } else {
      result = SL_STATUS_INVALID_PARAMETER;
    }
  }

  if (!has_notifications && response_slot >= 0) {
    uint8_t responses[ESL_PAYLOAD_OVERHEAD + ESL_PAYLOAD_MAX_LENGTH];
    uint8_t length = esl_core_get_responses(sizeof(responses) - ESL_PAYLOAD_OVERHEAD,
                                            &responses[ESL_PAYLOAD_OVERHEAD]);

    if (length && esl_core_get_sync_handle() != SL_BT_INVALID_SYNC_HANDLE) {
      sl_status_t sc;
      (void)sc; // suppress the compiler warning if sl_bt_esl_log disabled
      uint8_t *msg;

      responses[0] = ++length;    // set length properly for LL Adv.Data frame
      responses[1] = ESL_AD_TYPE; // set ESL AD Type

      length++; // set length properly for the whole frame to be encrypted
      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_INFO,
                    "PAwR response(s): ");
      sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                            ESL_LOG_LEVEL_INFO,
                            responses,
                            length);
      msg = esl_core_encrypt_message(responses, &length);

      sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                    ESL_LOG_LEVEL_DEBUG,
                    "Encrypted: ");
      sl_bt_esl_log_hexdump(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                            ESL_LOG_LEVEL_DEBUG,
                            responses,
                            length);
      if (msg != NULL) {
        // send periodic advertisement responses
        sc = sl_bt_pawr_sync_set_response_data(esl_core_get_sync_handle(),
                                               esl_core_get_request_event(),
                                               esl_core_get_request_subevent(),
                                               esl_core_get_group_id(esl_address),
                                               (uint8_t)response_slot,
                                               length,
                                               msg);
        sl_bt_esl_log(ESL_LOG_COMPONENT_CORE | ESL_LOG_FLAG_APPEND,
                      ESL_LOG_LEVEL_INFO,
                      ", result: 0x%04lx on slot %d",
                      sc,
                      response_slot);
      }
    }
    esl_core_purge_responses();
  }

  return result;
}

sl_status_t esl_core_process_opcode(esl_id_t self_id,
                                    esl_id_t id,
                                    tlv_t opcode,
                                    void **data)
{
  sl_status_t result = SL_STATUS_OK; // if not sent for us, do nothing, it's OK
  bool        has_notifications = esl_core_has_notifications();
  bool        needs_response    = (has_notifications || (id == self_id));

  // process only TLVs addressed to this ESL Tag or broadcasted (only over PAwR!)
  if (id == self_id || (id == ESL_BROADCAST_ID && !has_notifications)) {
#ifdef ESL_TAG_VENDOR_OPCODES_ENABLED
    // check for vendor opcodes first - let them processed by the vendor callback
    if ((opcode & ESL_TLV_OPCODE_VENDOR_SPECIFIC) == ESL_TLV_OPCODE_VENDOR_SPECIFIC) {
      uint8_t *data_p  = *(uint8_t **)data;
      uint8_t data_len = esl_core_get_tlv_len(opcode);

      result = esl_core_process_vendor_opcode(opcode, data_len, data_p);

      if (result != SL_STATUS_OK) {
        esl_error_t error_code = ESL_ERROR_INVALID_OPCODE;

        if (result != SL_STATUS_NOT_SUPPORTED) {
          error_code = esl_core_get_last_error();
        }

        (void)esl_core_build_response(ESL_TLV_RESPONSE_ERROR, &error_code);
      }
      // adjust data pointer properly - custom implementation shall not care
      *data = (void *)(data_p + data_len - sizeof(opcode));
      return SL_STATUS_OK;
    }
#endif // ESL_TAG_VENDOR_OPCODES_ENABLED

    switch (opcode) {
      case ESL_TLV_OPCODE_SERVICE_RST:
        // refresh the battery level actual value
        esl_sensor_battery_read();
        // clear the service needed flag in the first place
        esl_core_set_basic_state_bit(ESL_BASIC_STATE_SERVICE_NEEDED_BIT,
                                     ESL_CLEAR);
        // call user callback in the end
        esl_core_service_reset_event(); // @suppress("No break at end of case")
      // intentional fall through to ESL_TLV_OPCODE_PING, GCC suppress follows:
      /* FALLTHRU */
      case ESL_TLV_OPCODE_PING:
        // ignore any PING sent as broadcast message over PAWR sync!
        if (needs_response) {
          // report the Basic State register for ESL_TLV_OPCODE_SERVICE_RST
          // and ESL_TLV_OPCODE_PING commands according to ESL Service Spec.
          esl_basic_state_t basic_state = esl_core_get_basic_state();
          result = esl_core_build_response(ESL_TLV_RESPONSE_BASIC_STATE,
                                           &basic_state);
        } else {
          result = SL_STATUS_OK;
        }
        break;

      case ESL_TLV_OPCODE_UNASSOCIATE: {
        esl_basic_state_t basic_state = esl_core_get_basic_state();

        // remove any pending delayed command immediately
        esl_core_purge_delayed_commands();

        // Close the connection, if opened
        (void)app_scheduler_add(&esl_core_async_disconnect, 0, 0, NULL);

        result = app_scheduler_add_delayed(&esl_delayed_unassociate,
                                           ESL_CORE_DEFAULT_COMMAND_DELAY_MS,
                                           NULL, 0, NULL);
        if (result != SL_STATUS_OK) {
          esl_core_set_last_error(ESL_ERROR_INSUFFICIENT_RESOURCES);
        } else if (needs_response) {
          result = esl_core_build_response(ESL_TLV_RESPONSE_BASIC_STATE,
                                           &basic_state);
        }
      } break;

      case ESL_TLV_OPCODE_LED_TIMED_CONTROL:
      case ESL_TLV_OPCODE_LED_CONTROL: {
        // get led control data from **data
        esl_led_control_t *control_data = *(esl_led_control_t **)data;
        // prepare for immediate or delayed command response
        uint8_t response[] = { control_data->index };
        uint8_t led_count  = esl_led_get_count();
        // step data pointer forward
        *data = (void *)((uint8_t *)control_data + sizeof(*control_data));

        // check valid range before call the actual update function
        if (control_data->index < led_count) {
          if (opcode == ESL_TLV_OPCODE_LED_CONTROL) {
            result = esl_led_control(control_data);
#ifdef SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
            if (result == SL_STATUS_OK) {
              sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                            ESL_LOG_LEVEL_INFO,
                            "Immediate LED control as follows:");
              esl_debug_led_control_parameters(control_data);
            }
#endif // SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
          } else {
            // get absolute time from **data
            uint32_t *requested_time = *((uint32_t **)data);
            // helper pointer for byte positioning over data
            uint8_t   *data_p = (uint8_t *)requested_time;
            *data = (void *)(data_p + sizeof(*requested_time));

            result = esl_add_delayed_command(&esl_delayed_led,
                                             *requested_time,
                                             control_data,
                                             sizeof(*control_data));
            if (result != SL_STATUS_OK) {
              // ESL_ERROR_QUEUE_FULL might be set already in that particular
              // error case, otherwise send ESL_ERROR_INSUFFICIENT_RESOURCES
              esl_core_set_last_error(ESL_ERROR_INSUFFICIENT_RESOURCES);
            }
          }

          if (result == SL_STATUS_OK) {
            if (needs_response) {
              // return status of esl_core_build_response can be safely ignored
              // because if the LED status response doesn't fit, then the other
              // 'Capacity Limit' error response wouldn't fit, either!
              (void)esl_core_build_response(ESL_TLV_RESPONSE_LED_STATE,
                                            response);
            }
          } else {
            esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          }
        } else {
          if (led_count != 0) {
            result = SL_STATUS_INVALID_INDEX;
            esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
          } else {
            result = SL_STATUS_NOT_AVAILABLE;
            esl_core_set_last_error(ESL_ERROR_INVALID_OPCODE);
          }

          if (opcode == ESL_TLV_OPCODE_LED_TIMED_CONTROL) {
            // skip absolute time value of the timed LED commands
            *data = (void *)((*(uint8_t **)data) + sizeof(uint32_t));
          }
        }
      } break;

      case ESL_TLV_OPCODE_REFRESH_DISPLAY: {
        // get display index from **data
        uint8_t *display_index = *((uint8_t **)data);
        // prepare for immediate response
        uint8_t response[] = { *display_index, 0 }; // image index placeholder
        uint8_t display_count = esl_display_get_count();

        // step data pointer forward
        *data = (void *)(display_index + sizeof(*display_index));

        // check valid range before call the actual update function
        if (*display_index < display_count) {
          uint8_t image_index;

          result = esl_display_refresh(*display_index, &image_index);

          if (result == SL_STATUS_OK) {
            if (needs_response) {
              // set the image index properly
              response[1] = image_index;
              result = esl_core_build_response(ESL_TLV_RESPONSE_DISPLAY_STATE,
                                               response);
            }
          } else {
            esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          }
        } else if (display_count != 0) {
          result = SL_STATUS_INVALID_INDEX;
          esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
        } else {
          result = SL_STATUS_NOT_AVAILABLE;
          esl_core_set_last_error(ESL_ERROR_INVALID_OPCODE);
        }
      } break;

      case ESL_TLV_OPCODE_DISPLAY_TIMED_IMAGE:
      case ESL_TLV_OPCODE_DISPLAY_IMAGE: {
        // get display and image indices from **data
        uint8_t *display_index = *((uint8_t **)data);
        uint8_t *image_index = display_index + sizeof(*display_index);
        // prepare for immediate or delayed command response
        uint8_t response[] = { *display_index, *image_index };

        uint8_t display_count = esl_display_get_count();

        // step data pointer forward
        *data = (void *)(image_index + sizeof(*image_index));

        // check valid range before call the actual update function
        if (*display_index  < display_count
            && *image_index < esl_image_get_count()) {
          // do immediately if it's not the timed command
          if (opcode == ESL_TLV_OPCODE_DISPLAY_IMAGE) {
            result = esl_display_update(*display_index, *image_index);
          } else {
            // get absolute time from **data
            uint32_t *requested_time = *((uint32_t **)data);
            // helper pointer for byte positioning over data
            uint8_t   *data_p = (uint8_t *)requested_time;
            *data = (void *)(data_p + sizeof(*requested_time));

            result = esl_add_delayed_command(&esl_delayed_display,
                                             *requested_time, response,
                                             sizeof(response));
            if (result != SL_STATUS_OK) {
              // ESL_ERROR_QUEUE_FULL might be set already in that particular
              // error case, otherwise send ESL_ERROR_INSUFFICIENT_RESOURCES
              esl_core_set_last_error(ESL_ERROR_INSUFFICIENT_RESOURCES);
            }
          }

          if (result == SL_STATUS_OK) {
            if (needs_response) {
              // return status of esl_core_build_response can be safely ignored
              // because if the Display status response doesn't fit, then the
              // other 'Capacity Limit' error response wouldn't fit, either!
              (void)esl_core_build_response(ESL_TLV_RESPONSE_DISPLAY_STATE,
                                            response);
            }
          } else {
            esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          }
        } else {
          result = SL_STATUS_INVALID_INDEX;
          // if the display_index is within its boundaries, then it must be
          // the image index wrong...
          if (*display_index < display_count) {
            esl_core_set_last_error(ESL_ERROR_INVALID_IMAGE_INDEX);
          } else if (display_count != 0) {
            esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
          } else {
            result = SL_STATUS_NOT_AVAILABLE;
            esl_core_set_last_error(ESL_ERROR_INVALID_OPCODE);
          }

          if (opcode == ESL_TLV_OPCODE_DISPLAY_TIMED_IMAGE) {
            // skip absolute time value of the timed display commands
            *data = (void *)((*(uint8_t **)data) + sizeof(uint32_t));
          }
        }
      } break;

      case ESL_TLV_OPCODE_FACTORY_RST:
        if (esl_core_get_status() == esl_state_synchronized) {
          result = SL_STATUS_INVALID_STATE;
          esl_core_set_last_error(ESL_ERROR_INVALID_STATE);
        } else {
          sl_status_t result;

          // remove any pending delayed command immediately
          esl_core_purge_delayed_commands();
          // Invalidate config to avoid processing any further commands according to ESLS 3.9.2.4
          esl_core_invalidate_config();
          // deferred close of the active connection
          result = app_scheduler_add(&esl_core_async_disconnect, 0, 0, NULL);

          if (result == SL_STATUS_OK) {
            result = app_scheduler_add_delayed(&esl_delayed_reset,
                                               ESL_CORE_DEFAULT_COMMAND_DELAY_MS,
                                               NULL, 0, NULL);
          }

          // brute-force fall-back case if scheduling failed
          if (result != SL_STATUS_OK) {
            // delete bonding data
            (void)sl_bt_sm_delete_bondings();
            // and do immediate reset on failed scheduling
            sl_bt_system_reset(sl_bt_system_boot_mode_normal);
          }
        }
        break;

      case ESL_TLV_OPCODE_UPDATE_COMPLETE:
        result = esl_core_update_complete();
        // Check result
        if (result == SL_STATUS_INVALID_STATE) {
          esl_core_set_last_error(ESL_ERROR_INVALID_STATE);
        }
        break;

      case ESL_TLV_OPCODE_READ_SENSOR: {
        // get sensor index from **data
        uint8_t *sensor_index = *((uint8_t **)data);
        uint8_t sensor_count = esl_sensor_get_count();

        // step data pointer forward
        *data = (void *)(sensor_index + sizeof(*sensor_index));

        // check valid range before call the actual read function
        if (*sensor_index < sensor_count) {
          // call only if not a broadcast request - else no answer is expected!
          if (id != ESL_BROADCAST_ID) {
            // esl_sensor_read() will take care of the ESL error code, if any
            result = esl_sensor_read(*sensor_index);
          }
          if (result != SL_STATUS_OK) {
            esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
          }
        } else if (sensor_count != 0) {
          result = SL_STATUS_INVALID_INDEX;
          esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
        } else {
          result = SL_STATUS_NOT_AVAILABLE;
          esl_core_set_last_error(ESL_ERROR_INVALID_OPCODE);
        }
      }
      break;

      default:
        // unknown or unimplemented opcode
        // Forward compatibility, ESL Profile d09r18, Section 3.1.3:
        result = SL_STATUS_NOT_SUPPORTED;
        esl_core_set_last_error(ESL_ERROR_INVALID_OPCODE);
        break;
    }

    sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                  ((result) ? ESL_LOG_LEVEL_ERROR : ESL_LOG_LEVEL_INFO),
                  "Opcode 0x%02x result: 0x%04lx",
                  opcode, result);

    if (result != SL_STATUS_OK) {
      // actual result value is only used up to this point, internally...
      if (needs_response) {
        esl_error_t error_code = esl_core_get_last_error();
        sl_bt_esl_log(ESL_LOG_COMPONENT_CORE,
                      ESL_LOG_LEVEL_ERROR,
                      "Last ESL error code: 0x%02x",
                      error_code);
        // return status of esl_core_build_response must be ignored in this case
        // because there's nothing left to do with it, anyway
        (void)esl_core_build_response(ESL_TLV_RESPONSE_ERROR, &error_code);
      }
      // thus, after it may transformed to an ESL error report, now we override
      result = SL_STATUS_OK;
    }
  } else {
    uint8_t *data_p  = *(uint8_t **)data;
    uint8_t data_len = esl_core_get_tlv_len(opcode);
    // adjust data pointer properly is mandatory even if isn't addressed to us!
    *data = (void *)(data_p + data_len - sizeof(opcode));

    if (has_notifications) {  // did it come from ESL CP?
      esl_error_t error_code = ESL_ERROR_INVALID_PARAMETER;
      // return status of esl_core_build_response must be ignored in this case
      // because there's nothing left to do with it, anyway
      (void)esl_core_build_response(ESL_TLV_RESPONSE_ERROR, &error_code);
    }
  }

  return result;
}

SL_WEAK sl_status_t esl_core_process_vendor_opcode(tlv_t opcode,
                                                   uint8_t input_length,
                                                   void *data)
{
  // the default implementation does nothing, see app.c in the ESL Tag Studio
  // example project app.c for an implementation tutorial
  (void)opcode;
  (void)input_length;
  (void)data;

  return SL_STATUS_NOT_SUPPORTED;
}
