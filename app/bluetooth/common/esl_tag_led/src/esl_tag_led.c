/***************************************************************************//**
 * @file
 * @brief ESL Tag LED component logic.
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
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "sl_sleeptimer.h"
#include "gatt_db.h"
#include "esl_tag_log.h"
#include "esl_tag_led.h"
#include "esl_tag_image_core.h"
#include "em_common.h"

// An arbitrary big value to tell if a LED is currently inactive
#define ESL_LED_PATTERN_INACTIVE      UINT8_MAX
// Another arbitrary value to tell if a LED is continuously active
#define ESL_LED_PATTERN_IGNORED       0
// LED control pattern highest bit position by ESL Service specification
#define ESL_LED_PATTERN_MAX_MSB       39

// Extended LED object type, containing additional function pointers and data
// for internal use
typedef struct {
  esl_led_type_t               *info;
  sl_sleeptimer_timer_handle_t timer_handle;
  uint32_t                     start_time;
  esl_led_control_t            control;
  uint8_t                      pattern_position;
} esl_led_object_t;

// Internal LED registry type
typedef PACKSTRUCT (struct {
  esl_led_object_t  *next_object;
  uint8_t           led_count;
}) esl_led_registry_t;

// LED info array - max. number of elements is defined in config header
static esl_led_type_t         led_info[ESL_TAG_MAX_LEDS];

// LED object array for internal use
static esl_led_object_t       led_object[ESL_TAG_MAX_LEDS];

// LED registry structure
static esl_led_registry_t     led_registry;

/******************************************************************************
 * Get LED information characteristic data
 * Returns with all LED data in a format which can be easily write to the ESL
 * LED Information characteristic.
 * @param[out] uint8_t* size of the ESL LED info data
 * @param[out] void** pointer to the serialized ESL LED Information data array
 *****************************************************************************/
static inline void esl_led_get_all_info(uint16_t *data_size, void **out)
{
  *data_size = led_registry.led_count;

  // having the characteristic with zero length of data is invalid!
  if (*data_size == 0) {
    // this is a 'user error' condition, still the GATT request shall succeed
    // once the ESL access point tries to read it, thus we need at least one
    // LED to be reported even if this "shadow" LED itself won't be functional
    // without a proper registration during the ESL boot event
    *data_size = sizeof(esl_led_type_t);
  }

  *out = (void *)led_info;
}

/******************************************************************************
 * Find ESL LED state in control pattern at given position
 *
 * @param[in] control esl_led_control_t * type of pointer of the ESL LED control
 *            block to check
 * @param[in] position uint8_t bit position to check
 *****************************************************************************/
static inline bool esl_led_get_pattern_state(esl_led_control_t* control,
                                             uint8_t position)
{
  uint8_t data_index   = position >> 3;   // fast division by 8
  uint8_t bit_index    = position & 0x07; // fast modulo 8

  return (bool)(control->pattern.data[data_index] & (1 << bit_index));
}

/******************************************************************************
 * Find ESL LED control pattern most significant bit
 *
 * @param[in] control esl_led_control_t * type of pointer of the ESL LED control
 *            block to analyze
 *****************************************************************************/
static uint8_t esl_led_find_pattern_msb(esl_led_control_t* control)
{
  uint8_t msb_position = ESL_LED_PATTERN_MAX_MSB;
  uint8_t data_index   = msb_position >> 3;   // fast division by 8
  uint8_t bit_index    = msb_position & 0x07; // fast modulo 8

  // search through the pattern data from "left to right" until the first
  // '1' is found according to ESL Service Specification v0.9
  // Section 3.10.2.10.2.2
  while ((msb_position <= ESL_LED_PATTERN_MAX_MSB)
         && !(control->pattern.data[data_index] & (1 << bit_index))) {
    data_index = --msb_position >> 3;
    bit_index  = msb_position & 0x07;
  }

  return msb_position;
}

/******************************************************************************
 * ESL Tag internal LED on function.
 * Calls out for public method @ref sl_esl_led_on, and handles internal registry
 * status according to the result.
 * @return sl_status_t
 *****************************************************************************/
static sl_status_t esl_led_internal_led_on(uint8_t led_index,
                                           esl_led_gamut_control_t gamut)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (led_index < led_registry.led_count) {
    // call the user method responsible to physically turn on the LED
    result = esl_led_on(led_index, gamut);

    // according to the result, adjust internal database
    if (result == SL_STATUS_OK) {
      esl_led_type_t type = led_info[led_index] & ESL_LED_TYPE_MASK;

      // implements ESL Service Spec. d09r18, Section 3.10.3.3.1
      esl_core_set_basic_state_bit(ESL_BASIC_STATE_ACTIVE_LED_BIT, ESL_SET);

      if (type == ESL_LED_TYPE_SRGB) {
        esl_led_type_t new_info = 0;

        // get red color component
        new_info |= esl_led_get_red_value(gamut) << ESL_LED_RED_GAMUT_SHIFT;

        // get green color component
        new_info |= esl_led_get_green_value(gamut) << ESL_LED_GREEN_GAMUT_SHIFT;

        // get blue color component
        new_info |= esl_led_get_blue_value(gamut) << ESL_LED_BLUE_GAMUT_SHIFT;

        // put all together after bit manipulation
        type |= new_info;

        // keep ESL LED characteristic data up-to date
        led_info[led_index] = type;
      }
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_LED,
                    ESL_LOG_LEVEL_WARNING,
                    "ESL LED couldn't be turned on.");
    }
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_LED,
                  ESL_LOG_LEVEL_WARNING,
                  "ESL LED index out of bounds!");
  }

  return result;
}

/******************************************************************************
 * ESL Tag internal LED off function.
 * Calls out for public method @ref sl_esl_led_off, and handles internal
 * registry status according to the result.
 * @return sl_status_t
 *****************************************************************************/
static sl_status_t esl_led_internal_led_off(uint8_t led_index)
{
  sl_status_t result = SL_STATUS_INVALID_INDEX;

  if (led_index < led_registry.led_count) {
    // call the user method responsible to physically turn on the LED
    result = esl_led_off(led_index);

    // according to the result, adjust internal database
    if (result == SL_STATUS_OK) {
      bool has_active = false;
      uint8_t index   = 0;

      // implements ESL Service Spec. d09r18, Section 3.10.3.3.1
      for (; !has_active && index < led_registry.led_count; index++) {
        bool current_is_active =
          (led_object[index].pattern_position <= ESL_LED_PATTERN_MAX_MSB);

        has_active = has_active || current_is_active;
      }

      if (!has_active) {
        esl_core_set_basic_state_bit(ESL_BASIC_STATE_ACTIVE_LED_BIT, ESL_CLEAR);
      }
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_LED,
                    ESL_LOG_LEVEL_WARNING,
                    "LED couldn't be turned off.");
    }
  } else {
    sl_bt_esl_log(ESL_LOG_COMPONENT_LED,
                  ESL_LOG_LEVEL_WARNING,
                  "LED index out of bounds!");
  }

  return result;
}

/******************************************************************************
 * ESL Tag internal LED control timer callback.
 * Implements the expected prototype of the user's callback function for
 * sleeptimer which is called when the timer expires.
 * Called in interrupt context.
 *
 * @param[in] timer Pointer to the timer handle.
 * @param[in] data  Extra parameter: an (esl_led_object_t *) pointer to the
 *            actual LED under control
 *****************************************************************************/
static void esl_led_timer_callback(sl_sleeptimer_timer_handle_t *timer,
                                   void *data)
{
  esl_led_object_t *led = (esl_led_object_t *)data;
  uint32_t         time = 0;
  bool             lit  = false;

  // ESL LED timer callback: improper use, *data can't be NULL!
  sl_bt_esl_assert(led != NULL);

  --(led->pattern_position);

  // check repeat type
  if ((led->control.repeats & ESL_LED_REPEATS_TYPE_MASK) == ESL_LED_REPEATS_TYPE_COUNT) {
    esl_led_repeats_type_t repeat_count;

    repeat_count = (led->control.repeats & (esl_led_repeats_type_t)(~ESL_LED_REPEATS_TYPE_MASK))
                   >> ESL_LED_REPEATS_DURATION_SHIFT;
    // check if the last bit of the pattern was just executed
    if (led->pattern_position > ESL_LED_PATTERN_MAX_MSB && repeat_count != 0) {
      --repeat_count;
      // after lowering the repeat count, store it in the control block
      led->control.repeats = (repeat_count << ESL_LED_REPEATS_DURATION_SHIFT)
                             | (ESL_LED_REPEATS_TYPE_MASK & ESL_LED_REPEATS_TYPE_COUNT);
      led->pattern_position = esl_led_find_pattern_msb(&led->control);
    }

    if (repeat_count != 0 && esl_core_get_status() != esl_state_unassociated) {
      esl_led_control_t *control = &led->control;

      lit  = esl_led_get_pattern_state(control, led->pattern_position);
      time = lit ? control->pattern.bit_on_period : control->pattern.bit_off_period;
      time = time << 1;
    } else {
      // repeat count reached or the Tag has been unassociated in the meanwhile
      led->pattern_position = ESL_LED_PATTERN_INACTIVE;
      time = 0;
      lit  = false;
    }
  } else {
    sl_status_t status;
    uint32_t    current_time;
    uint32_t    elapsed_time;
    uint64_t    ms64 = 0;
    uint64_t    current_tick = sl_sleeptimer_get_tick_count64();

    status = sl_sleeptimer_tick64_to_ms(current_tick, &ms64);

    if (status == SL_STATUS_OK) {
      esl_led_control_t *control  = &led->control;
      // the unit of the duration value is [sec] by ESL Service specification
      uint32_t          duration  = led->control.repeats >> ESL_LED_REPEATS_DURATION_SHIFT;
      // get initial remaining time in [ms] from the requested duration value
      uint32_t          remaining = 1000u * (uint32_t)duration;

      current_time = (uint32_t)ms64;
      // calculate elapsed time since switched on for the very first time
      elapsed_time = (uint32_t)(current_time - led->start_time);

      // handle underflow condition
      if (led->pattern_position > ESL_LED_PATTERN_MAX_MSB) {
        led->pattern_position = esl_led_find_pattern_msb(&led->control);
      }

      // check if we need to continue at all
      if (elapsed_time < remaining) {
        lit  = esl_led_get_pattern_state(control, led->pattern_position);
        time = lit ? control->pattern.bit_on_period : control->pattern.bit_off_period;
        time = time << 1;

        // adjust remaining time
        remaining -= elapsed_time;
        if (time > remaining) {
          // start timer (later on, see at the end) only for true remaining time
          time = remaining;
        }
      } else {
        // requested duration already ended
        led->pattern_position = ESL_LED_PATTERN_INACTIVE;
        time = 0;
        lit  = false;
      }
    } else {
      // this is an error case e.g. when the ESL Tag has been unassociated while
      // an LED control was in progress!
      led->pattern_position = ESL_LED_PATTERN_INACTIVE;
      time = 0;
      lit  = false;
    }
  }

  if (time != 0) {
    (void)sl_sleeptimer_start_timer_ms(timer,
                                       time,
                                       &esl_led_timer_callback,
                                       led,
                                       (uint8_t)INT8_MAX,
                                       SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);
  } else {
    // override the lit value if the timer does not need to be started, thus
    // avoiding the LED being ever stuck in the on state (that is, to avoid
    // a sudden battery drain)
    led->pattern_position = ESL_LED_PATTERN_INACTIVE;
    lit = false;
  }

  if (lit) {
    (void)esl_led_internal_led_on(led->control.index, led->control.gamut);
  } else {
    (void)esl_led_internal_led_off(led->control.index);
  }
}

void esl_led_init(void)
{
  uint8_t i;
  // clear all display data
  memset(led_info, 0, sizeof(led_info));
  memset(led_object, 0, sizeof(led_object));

  // 1:1 assign every led_info to the corresponding led_objects
  for (i = 0; i < ESL_TAG_MAX_LEDS; ++i) {
    led_object[i].info = &led_info[i];
    // initialize pattern position index
    led_object[i].pattern_position = ESL_LED_PATTERN_INACTIVE;
  }
  // initialize zero led count, prepare led creation / allocation
  led_registry.next_object = led_object;
  led_registry.led_count   = 0;
}

void esl_led_bt_on_event(sl_bt_msg_t *evt)
{
  switch (SL_BT_MSG_ID(evt->header)) {
    case sl_bt_evt_gatt_server_user_read_request_id:
      if (evt->data.evt_gatt_server_user_read_request.characteristic == gattdb_esl_led_info) {
        uint8_t*  raw_info;
        uint16_t  raw_size, offset;
        uint16_t  mtu_size;
        sl_status_t sc;
        (void)sc; // suppress the compiler warning if sl_bt_esl_assert disabled

        // get pointer first to the beginning of the display_info packed struct
        esl_led_get_all_info(&raw_size, (void *)&raw_info);
        // then get the offset value from the request
        offset = evt->data.evt_gatt_server_user_read_request.offset;
        // finally, adjust offset and size
        raw_info += offset;
        raw_size -= offset;

        // check current ATT_MTU limits
        sc = sl_bt_gatt_server_get_mtu(evt->data.evt_gatt_server_user_read_request.connection, &mtu_size);
        sl_bt_esl_assert(sc == SL_STATUS_OK);

        // sl_bt_gatt_server_send_user_read_response allows (ATT_MTU - 1) size
        --mtu_size; // of data to be sent at once!

        // and limit the actual data size to be sent accordingly
        raw_size = raw_size > mtu_size ? mtu_size : raw_size;

        // send data (chunk, maybe more read reqs. with offset != 0 will follow)
        sc = sl_bt_gatt_server_send_user_read_response(evt->data.evt_gatt_server_user_read_request.connection,
                                                       evt->data.evt_gatt_server_user_read_request.characteristic,
                                                       SL_STATUS_OK,
                                                       raw_size,
                                                       raw_info,
                                                       NULL);
        sl_bt_esl_assert(sc == SL_STATUS_OK);
      }
      break;

    default:
      break;
  }
}

sl_status_t esl_led_add(esl_led_type_t type,
                        uint8_t red_value,
                        uint8_t green_value,
                        uint8_t blue_value)
{
  sl_status_t result = SL_STATUS_INVALID_STATE;
  esl_state_t state  = esl_core_get_status();

  // ESL LED: adding LED after the boot event is disallowed!
  sl_bt_esl_assert(esl_state_boot == state);

  if (state == esl_state_boot) {
    result = SL_STATUS_NO_MORE_RESOURCE;

    if (led_registry.led_count < ESL_TAG_MAX_LEDS) {
      esl_led_type_t new_led = type & ESL_LED_TYPE_MASK;
      // assemble the led info for this new led

      new_led |= (red_value & ESL_LED_GENERIC_2BIT_MASK) << ESL_LED_RED_GAMUT_SHIFT;
      new_led |= (green_value & ESL_LED_GENERIC_2BIT_MASK) << ESL_LED_GREEN_GAMUT_SHIFT;
      new_led |= (blue_value & ESL_LED_GENERIC_2BIT_MASK) << ESL_LED_BLUE_GAMUT_SHIFT;

      *(led_registry.next_object->info) = new_led;

      // increase LED count
      ++led_registry.led_count;
      // get next object
      ++led_registry.next_object;
      result = SL_STATUS_OK;
    } else {
      sl_bt_esl_log(ESL_LOG_COMPONENT_LED,
                    ESL_LOG_LEVEL_ERROR,
                    "Unable to add more LED, ESL_TAG_MAX_LEDS might be low.");
    }
  }

  return result;
}

sl_status_t esl_led_control(esl_led_control_t *control_param)
{
  esl_led_gamut_control_t gamut  = control_param->gamut;
  uint8_t                 index  = control_param->index;
  sl_status_t             result = SL_STATUS_INVALID_INDEX;

  if (index < led_registry.led_count) {
    esl_led_object_t             *current_led  = &led_object[index];
    sl_sleeptimer_timer_handle_t *timer_handle = &(current_led->timer_handle);

    // do default actions in the first place: override previous LED control
    (void)sl_sleeptimer_stop_timer(timer_handle);   // ignore return status
    current_led->pattern_position = ESL_LED_PATTERN_INACTIVE;

    // handle simple LED off command as per ESL Specification v0.9
    // Section 3.10.2.10.4
    if (control_param->repeats == 0) {
      result = esl_led_internal_led_off(control_param->index);
    } else {
      uint64_t current_tick = sl_sleeptimer_get_tick_count64();
      uint64_t ms64         = 0;

      result = sl_sleeptimer_tick64_to_ms(current_tick, &ms64);
      // handle simple LED on command as per ESL Specification v0.9
      // Section 3.10.2.10.2.4
      if (control_param->repeats == ESL_LED_REPEATS_TYPE_MASK) {
        // handle the special case
        current_led->pattern_position = ESL_LED_PATTERN_IGNORED;
        // save current internal time if available, ignore any possible error
        current_led->start_time = (uint32_t)ms64;
        // this will let us enable the led in the end
        result = SL_STATUS_OK;
      } else if (!control_param->pattern.bit_on_period
                 || !control_param->pattern.bit_off_period) {
        // handle the error case defined in ESL Service Specification v0.9,
        // Section 3.10.2.10.2.2
        result = SL_STATUS_INVALID_PARAMETER;
        // the following call will override the default error response
        esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
      } else if (result == SL_STATUS_OK) {
        current_led->start_time = (uint32_t)ms64;
        current_led->control    = *control_param;   // shallow copy is just fine
        current_led->pattern_position = esl_led_find_pattern_msb(control_param);

        if (current_led->pattern_position <= ESL_LED_PATTERN_MAX_MSB) {
          result = sl_sleeptimer_start_timer_ms(timer_handle,
                                                (control_param->pattern.bit_on_period << 1),
                                                &esl_led_timer_callback,
                                                (void *)current_led,
                                                (uint8_t)INT8_MAX,
                                                SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);

          if (result != SL_STATUS_OK) {
            // set insufficient resources if the timer couldn't be started
            esl_core_set_last_error(ESL_ERROR_INSUFFICIENT_RESOURCES);
          }
        } else {
          // set invalid parameter response if the pattern is all zero
          esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
        }
      }

      if (result == SL_STATUS_OK) {
        result = esl_led_internal_led_on(control_param->index, gamut);
      }
    }

    if (result != SL_STATUS_OK) {
      // default error response for any unknown error (if not yet set)
      esl_core_set_last_error(ESL_ERROR_UNSPECIFIED);
    }
  } else {
    esl_core_set_last_error(ESL_ERROR_INVALID_PARAMETER);
  }

  return result;
}

uint8_t esl_led_get_count()
{
  return led_registry.led_count;
}

bool esl_led_is_srgb(uint8_t led_index)
{
  return (led_index < led_registry.led_count
          && (led_info[led_index] & ESL_LED_TYPE_MASK) == ESL_LED_TYPE_SRGB);
}

SL_WEAK sl_status_t esl_led_on(uint8_t led_index, esl_led_gamut_control_t gamut)
{
  (void)led_index;
  (void)gamut;

  return SL_STATUS_FAIL;
}

SL_WEAK sl_status_t esl_led_off(uint8_t led_index)
{
  (void)led_index;

  return SL_STATUS_FAIL;
}
