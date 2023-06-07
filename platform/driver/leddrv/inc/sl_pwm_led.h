/***************************************************************************//**
 * @file
 * @brief Simple PWM LED Driver
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SL_SIMPLE_PWM_LED_HAL_H
#define SL_SIMPLE_PWM_LED_HAL_H

#include "sl_led.h"
#include "em_timer.h"
#include "em_cmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/// A Simple PWM LED
typedef struct {
  void   (*set_color)(void *context, uint16_t color);  ///< Member function to set color of PWM LED
  void   (*get_color)(void *context, uint16_t *color); ///< Member function to get color of PWM LED

  uint8_t           channel;      /**< TIMER channel */
  GPIO_Port_TypeDef port;         /**< GPIO port */
  uint8_t           pin;          /**< GPIO pin */
#if defined(_SILICON_LABS_32B_SERIES_0) || defined(_SILICON_LABS_32B_SERIES_1)
  uint8_t           location;     /**< GPIO location */
#endif
  uint16_t          level;        /**< PWM duty cycle [0-65535] */
  uint8_t           polarity;     /**< GPIO polarity (active high/low) */
  sl_led_state_t    state;        /**< Current state (ON/OFF) */
  TIMER_TypeDef     *timer;       /**< TIMER instance */
  uint32_t          frequency;    /**< PWM frequency */
  uint32_t          resolution;   /**< PWM resolution (dimming steps) */
} sl_led_pwm_t;

/***************************************************************************//**
 * Initialize the PWM LED.
 *
 * @param[in] context         Pointer to PWM LED specific data
 *
 * @return    Status Code:
 *              - SL_STATUS_OK   Success
 *              - SL_STATUS_FAIL Init error
 ******************************************************************************/
sl_status_t sl_pwm_led_init(void *context);

/***************************************************************************//**
 * Start the PWM LED. This enables the GPIO timer route.
 *
 * @param[in] context         Pointer to PWM LED specific data
 *
 ******************************************************************************/
void sl_pwm_led_start(void *context);

/***************************************************************************//**
 * Stop the PWM LED.  This disables the GPIO timer route.
 *
 * @param[in] context         Pointer to PWM LED specific data
 *
 ******************************************************************************/
void sl_pwm_led_stop(void *context);

/***************************************************************************//**
 * Set color of PWM LED.
 *
 * @param[in] led             Pointer to PWM LED specific data.
 *
 * @param[in] color           Color level (PWM duty-cycle [0-65535])
 ******************************************************************************/
void sl_pwm_led_set_color(void *led, uint16_t color);

/***************************************************************************//**
 * Get color of PWM LED.
 *
 * @param[in] led             Pointer to PWM LED specific data.
 *
 * @param[out] color          Color level (PWM duty-cycle [0-65535])
 ******************************************************************************/
void sl_pwm_led_get_color(void *led, uint16_t *color);

#ifdef __cplusplus
}
#endif

#endif
