/***************************************************************************//**
 * @file
 * @brief LED Application code
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

#include "app_led.h"
#include "sl_btmesh.h"
#include "sl_btmesh_lighting_server.h"
#include "sl_btmesh_lighting_server_config.h"
#include "sl_btmesh_ctl_server.h"
#include "board_4166a.h"

// -----------------------------------------------------------------------------
// Definitions

#define RGB_LED_MASK        0xF           // Use all LEDs

// -----------------------------------------------------------------------------
// Private variables

static uint16_t light_level = 0;
static uint16_t light_color = 0;

// -----------------------------------------------------------------------------
// Public function definitions

/*******************************************************************************
 * Sets the lightness level of the LED.
 *
 * @param[in] level  lightness level (0-65535)
 *
 ******************************************************************************/
void app_led_set_level(uint16_t level)
{
  light_level = level;
  rgb_led_set(RGB_LED_MASK, light_level, light_color);
}

/*******************************************************************************
 * Sets the color temperature of the LED if present.
 *
 * @param[in] color  Color temperature in Kelvins.
 *
 ******************************************************************************/
void app_led_set_color(uint16_t color)
{
  light_color = color;
  rgb_led_set(RGB_LED_MASK, light_level, light_color);
}

/*******************************************************************************
 * Gets the maximum lightness value
 *
 * @return maximum lightness value.
 ******************************************************************************/
uint16_t app_led_get_max(void)
{
  return SL_BTMESH_LIGHTING_SERVER_PWM_MAXIMUM_BRIGHTNESS_CFG_VAL;
}

/*******************************************************************************
 * Init LED drivers
 *
 ******************************************************************************/
void app_led_init(void)
{
  rgb_led_init();
}

/*******************************************************************************
 * Change buttons to leds in case of shared pin
 *
 ******************************************************************************/
void app_led_change_buttons_to_leds(void)
{
}
