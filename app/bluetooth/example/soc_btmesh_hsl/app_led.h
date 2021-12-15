/***************************************************************************//**
 * @file
 * @brief Application interface for LEDs
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef APP_LED_H
#define APP_LED_H

#include <stdint.h>

/***************************************************************************//**
 * Sets the lightness level of the LED.
 *
 * @param[in] level  lightness level (0-65535)
 *
 ******************************************************************************/
void app_led_set_level(uint16_t level);

/***************************************************************************//**
 * Sets the hue of the LED if present.
 *
 * @param[in] hue  hue level (0-65535)
 *
 ******************************************************************************/
void app_led_set_hue(uint16_t hue);

/***************************************************************************//**
 * Sets the saturation of the LED if present.
 *
 * @param[in] saturation  saturation level (0-65535)
 *
 ******************************************************************************/
void app_led_set_saturation(uint16_t saturation);

/***************************************************************************//**
 * Gets the maximum lightness value
 *
 * @return maximum lightness value.
 ******************************************************************************/
uint16_t app_led_get_max(void);

/***************************************************************************//**
 * Init LED drivers
 *
 ******************************************************************************/
void app_led_init(void);

/***************************************************************************//**
 * Change buttons to leds in case of shared pin
 *
 ******************************************************************************/
void app_led_change_buttons_to_leds(void);

#endif // APP_LED_H
