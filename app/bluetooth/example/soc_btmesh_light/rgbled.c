/***************************************************************************//**
 * @file
 * @brief RGB LED driver for BRD4166A
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

#include "sl_simple_rgbw_pwm_led_instances.h"
#include "sl_simple_rgbw_pwm_led.h"
#include "em_gpio.h"
#include "board_4166a.h"
#include <math.h>

// -----------------------------------------------------------------------------
// Type definitions

typedef struct {
  uint8_t R;  ///< Red value
  uint8_t G;  ///< Green value
  uint8_t B;  ///< Blue value
}RGB_t;

// -----------------------------------------------------------------------------
// Private function definitions

/***************************************************************************//**
 * Enable RGB LEDs with respect to the enabling bitmask.
 *
 * @param[in] enable  Enable or disable the selected LEDs.
 * @param[in] mask    LED instance mask.
 ******************************************************************************/
static void rgb_led_enable(bool enable, uint8_t mask)
{
  if ( ( (mask != 0) && (enable == true) )
       || ( ( (mask & 0xf) == 0xf) && (enable == false) ) ) {
    if ( enable ) {
      GPIO_PinOutSet(BOARD_RGBLED_PWR_EN_PORT, BOARD_RGBLED_PWR_EN_PIN);
    } else {
      GPIO_PinOutClear(BOARD_RGBLED_PWR_EN_PORT, BOARD_RGBLED_PWR_EN_PIN);
    }
  }

  int i;
  uint8_t pins[BOARD_RGBLED_COUNT] = { BOARD_RGBLED_COM0_PIN,
                                       BOARD_RGBLED_COM1_PIN,
                                       BOARD_RGBLED_COM2_PIN,
                                       BOARD_RGBLED_COM3_PIN };

  for ( i = 0; i < BOARD_RGBLED_COUNT; i++ ) {
    if ( ( (mask >> i) & 1) == 1 ) {
      if ( enable ) {
        GPIO_PinOutSet(BOARD_RGBLED_COM_PORT,
                       pins[(BOARD_RGBLED_COUNT - 1) - i]);
      } else {
        GPIO_PinOutClear(BOARD_RGBLED_COM_PORT,
                         pins[(BOARD_RGBLED_COUNT - 1) - i]);
      }
    }
  }

  return;
}

/***************************************************************************//**
 * Convert temperature to RGB color using approximation functions.
 *
 * @param[in] temperature  Color temperature in Kelvins.
 *
 * @return RGB color representing given temperature.
 ******************************************************************************/
RGB_t Temperature_to_RGB(uint16_t temperature)
{
  RGB_t color;
  double temp_R, temp_G, temp_B;

  //approximation of temperature using RGB
  if (temperature < 6563) {
    temp_R = 255;
    if (temperature < 1925) {
      temp_B = 0;
    } else {
      temp_B = temperature - 1918.74282;
      temp_B = 2.55822107 * pow(temp_B, 0.546877914);
    }
    if ( temperature < 909) {
      temp_G = 0;
    } else {
      temp_G = temperature - 636.62578769;
      temp_G = 73.13384712 * log(temp_G) - 383.76244858;
    }
  } else {
    temp_R = temperature - 5882.02392431;
    temp_R = -29.28670147 * log(temp_R) + 450.50427359;
    temp_R = temp_R + 0.5;
    temp_G = temperature - 5746.13180276;
    temp_G = -18.69512921 * log(temp_G) + 377.39334366;
    temp_B = 255;
  }

  // Norming
  double temp_max = SL_MAX(temp_R, SL_MAX(temp_G, temp_B));

  temp_R = temp_R * 255 / temp_max;
  temp_G = temp_G * 255 / temp_max;
  temp_B = temp_B * 255 / temp_max;

  color.R = temp_R > 255 ? 255 : (temp_R >= 0 ? (int)(temp_R + 0.5) : 0);
  color.G = temp_G > 255 ? 255 : (temp_G >= 0 ? (int)(temp_G + 0.5) : 0);
  color.B = temp_B > 255 ? 255 : (temp_B >= 0 ? (int)(temp_B + 0.5) : 0);

  return color;
}

/***************************************************************************//**
 * Change lightness of given color temperature.
 *
 * @param[in] color  RGB color representing color temperature.
 * @param[in] level  Lightness level of given color.
 *
 * @return RGB color representing given temperature and lightness level.
 ******************************************************************************/
RGB_t RGB_to_LightnessRGB(RGB_t color, uint16_t level)
{
  uint32_t temp_level;
  RGB_t new_color;

  temp_level = color.R * (uint32_t) level / 65535;
  new_color.R = temp_level;
  temp_level = color.G * (uint32_t) level / 65535;
  new_color.G = temp_level;
  temp_level = color.B * (uint32_t) level / 65535;
  new_color.B = temp_level;

  return new_color;
}

// -----------------------------------------------------------------------------
// Public function definitions

/*******************************************************************************
 * Initialize all LEDs.
 ******************************************************************************/
void rgb_led_init(void)
{
  GPIO_PinModeSet(BOARD_RGBLED_PWR_EN_PORT,
                  BOARD_RGBLED_PWR_EN_PIN,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(BOARD_RGBLED_COM0_PORT,
                  BOARD_RGBLED_COM0_PIN,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(BOARD_RGBLED_COM1_PORT,
                  BOARD_RGBLED_COM1_PIN,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(BOARD_RGBLED_COM2_PORT,
                  BOARD_RGBLED_COM2_PIN,
                  gpioModePushPull,
                  0);
  GPIO_PinModeSet(BOARD_RGBLED_COM3_PORT,
                  BOARD_RGBLED_COM3_PIN,
                  gpioModePushPull,
                  0);
}

/*******************************************************************************
 * De-initialize all LEDs by disabling them.
 ******************************************************************************/
void rgb_led_deinit(void)
{
  rgb_led_enable(false, 0xf);
}

/*******************************************************************************
 * Set LED color based on lightness and temperature.
 *
 * @param[in] m            LED instance mask
 * @param[in] level        Lightness level.
 * @param[in] temperature  Color temperature in Kelvins.
 ******************************************************************************/
void rgb_led_set(uint8_t m, uint16_t level, uint16_t temperature)
{
  RGB_t color = Temperature_to_RGB(temperature);
  color = RGB_to_LightnessRGB(color, level);
  rgb_led_set_rgb(m,
                  color.R,
                  color.G,
                  color.B);
}

/*******************************************************************************
 * Set LED color based on RGB components.
 *
 * @param[in] mask         LED instance mask
 * @param[in] r            Red component
 * @param[in] g            Green component
 * @param[in] b            Blue component
 ******************************************************************************/
void rgb_led_set_rgb(uint8_t m, uint8_t r, uint8_t g, uint8_t b)
{
  rgb_led_enable(false, ~m);
  rgb_led_enable(true, m);
  sl_led_set_rgbw_color(&sl_led_rgb,
                        (uint16_t)r,
                        (uint16_t)g,
                        (uint16_t)b,
                        0);
}
