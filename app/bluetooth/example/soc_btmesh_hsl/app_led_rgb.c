/***************************************************************************//**
 * @file
 * @brief LED Application code
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

#include "app_led.h"
#include "sl_btmesh.h"
#include "sl_btmesh_lighting_server.h"
#include "sl_btmesh_lighting_server_config.h"
#include "sl_btmesh_hsl_server.h"
#include "board_4166a.h"

// -----------------------------------------------------------------------------
// Definitions

#define RGB_LED_MASK        0xF           // Use all LEDs

// -----------------------------------------------------------------------------
// Private variables

static uint16_t light_level = 0;
static uint16_t hue_level = 0;
static uint16_t saturation_level = 0;

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
  rgb_led_set(RGB_LED_MASK, light_level, hue_level, saturation_level);
}

/*******************************************************************************
 * Sets the hue of the LED if present.
 *
 * @param[in] hue  Hue level.
 *
 ******************************************************************************/
void app_led_set_hue(uint16_t hue)
{
  hue_level = hue;
  rgb_led_set(RGB_LED_MASK, light_level, hue_level, saturation_level);
}

/*******************************************************************************
 * Sets the hue of the LED if present.
 *
 * @param[in] hue  Hue level.
 *
 ******************************************************************************/
void app_led_set_saturation(uint16_t saturation)
{
  saturation_level = saturation;
  rgb_led_set(RGB_LED_MASK, light_level, hue_level, saturation_level);
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
