/***************************************************************************//**
 * @file
 * @brief ESL Tag core interface declarations for LED functionalities.
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
#ifndef ESL_TAG_LED_CORE_H
#define ESL_TAG_LED_CORE_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"
#include "esl_tag_core.h"

/// ESL LED type
typedef uint8_t                   esl_led_type_t;

/// ESL LED color gamut control type
typedef uint8_t                   esl_led_gamut_control_t;

/// ESL LED repeats type
typedef uint16_t                  esl_led_repeats_type_t;

/// ESL LED flashing pattern ESL Service Spec. d09r18, Section 3.10.2.10.2.2
typedef PACKSTRUCT (struct {
  uint8_t                     data[5];
  uint8_t                     bit_off_period;
  uint8_t                     bit_on_period;
}) esl_led_flashing_pattern_t;

/// ESL LED Control parameter, ESL Service Spec. d09r18, Section 3.10.2.10.1
typedef PACKSTRUCT (struct {
  uint8_t                     index;
  esl_led_gamut_control_t     gamut;
  esl_led_flashing_pattern_t  pattern;
  esl_led_repeats_type_t      repeats;
}) esl_led_control_t;

// Shift values for getting / setting individual values to / from esl_led_type_t
#define ESL_LED_TYPE_SHIFT          ((esl_led_type_t)6)

// Shift values for getting / setting individual values to / from
// esl_led_gamut_control_t
#define ESL_LED_BRIGHTNESS_SHIFT    ((esl_led_gamut_control_t)6)
#define ESL_LED_RED_GAMUT_SHIFT     ((esl_led_gamut_control_t)0)
#define ESL_LED_GREEN_GAMUT_SHIFT   ((esl_led_gamut_control_t)2)
#define ESL_LED_BLUE_GAMUT_SHIFT    ((esl_led_gamut_control_t)4)

// Mask value for getting repeats_type bit
#define ESL_LED_REPEATS_TYPE_MASK   ((esl_led_repeats_type_t)0x0001)

// Value of repeat type "number of times"
#define ESL_LED_REPEATS_TYPE_COUNT  ((esl_led_repeats_type_t)0x0000)

// Value of repeat type "time duration in seconds"
#define ESL_LED_REPEATS_TYPE_TIME   ((esl_led_repeats_type_t)0x0001)

// Shift value for getting repeats_duration value (seconds)
#define ESL_LED_REPEATS_DURATION_SHIFT  ((esl_led_repeats_type_t)0x0001)

/// ESL LED type definition: sRGB
#define ESL_LED_TYPE_SRGB         ((esl_led_type_t)(0x00 << ESL_LED_TYPE_SHIFT))

/// ESL LED type definition: Monochrome
#define ESL_LED_TYPE_MONOCHROME   ((esl_led_type_t)(0x01 << ESL_LED_TYPE_SHIFT))

// Masks for getting / setting individual values to / from esl_led_type_t
#define ESL_LED_TYPE_MASK           ((esl_led_type_t)0xC0)
#define ESL_LED_GENERIC_2BIT_MASK   ((esl_led_type_t)0x03)

/// ESL LED color gamut / brightness values
#define ESL_LED_LEVEL_0             (0x00)
#define ESL_LED_LEVEL_1             (0x01)
#define ESL_LED_LEVEL_2             (0x02)
#define ESL_LED_LEVEL_3             (0x03)

/// ESL LED color gamut / brightness step percentage
#define ESL_LED_LEVEL_STEP_PERCENTAGE   25

/**************************************************************************//**
 * Function like macro getter for 2-bit brightness value from a gamut value
 * @param[in] esl_led_gamut_control_t ESL Address to get the ESL ID from
 * @return esl_led_gamut_control_t brightness
 *****************************************************************************/
#define esl_led_get_brightness(_gamut)      (esl_led_gamut_control_t) \
  ((_gamut & (ESL_LED_GENERIC_2BIT_MASK << ESL_LED_BRIGHTNESS_SHIFT)) \
   >> ESL_LED_BRIGHTNESS_SHIFT)

/**************************************************************************//**
 * Function like macro getter for 2-bit red value from a gamut value
 * @param[in] esl_led_gamut_control_t ESL Address to get the ESL ID from
 * @return esl_led_gamut_control_t red value
 *****************************************************************************/
#define esl_led_get_red_value(_gamut)       (esl_led_gamut_control_t) \
  ((_gamut & (ESL_LED_GENERIC_2BIT_MASK << ESL_LED_RED_GAMUT_SHIFT))  \
   >> ESL_LED_RED_GAMUT_SHIFT)

/**************************************************************************//**
 * Function like macro getter for 2-bit green value from a gamut value
 * @param[in] esl_led_gamut_control_t ESL Address to get the ESL ID from
 * @return esl_led_gamut_control_t green value
 *****************************************************************************/
#define esl_led_get_green_value(_gamut)     (esl_led_gamut_control_t)  \
  ((_gamut & (ESL_LED_GENERIC_2BIT_MASK << ESL_LED_GREEN_GAMUT_SHIFT)) \
   >> ESL_LED_GREEN_GAMUT_SHIFT)

/**************************************************************************//**
 * Function like macro getter for 2-bit blue value from a gamut value
 * @param[in] esl_led_gamut_control_t ESL Address to get the ESL ID from
 * @return esl_led_gamut_control_t blue value
 *****************************************************************************/
#define esl_led_get_blue_value(_gamut)      (esl_led_gamut_control_t) \
  ((_gamut & (ESL_LED_GENERIC_2BIT_MASK << ESL_LED_BLUE_GAMUT_SHIFT)) \
   >> ESL_LED_BLUE_GAMUT_SHIFT)

/**************************************************************************//**
 * ESL Tag LED init function. ESL Core component will call this during the
 * initialization of application. This call is hidden and happens automatically.
 *****************************************************************************/
void esl_led_init(void);

/**************************************************************************//**
 * ESL Tag LED control function
 * @param[in] control_param ESL LED control parameters defined by the ESL
 *                          standard - excluding the ESL ID.
 * @note      updates the active LED bit in ESL basic state register according
 *            to the actual status of all LEDs
 * @return sl_status_t
 *****************************************************************************/
sl_status_t esl_led_control(esl_led_control_t *control_param);

/**************************************************************************//**
 * Get ESL Tag LED count
 * @return Number of available LEDs
 *****************************************************************************/
uint8_t esl_led_get_count();

/**************************************************************************//**
 * Get ESL Tag LED count
 * @return Number of available LEDs
 *****************************************************************************/
bool esl_led_is_srgb(uint8_t led_index);
/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_LED_CORE_H
