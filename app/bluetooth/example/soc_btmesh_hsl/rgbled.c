/***************************************************************************//**
 * @file
 * @brief RGB LED driver for BRD4166A
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
 * Helper function for calculating RGB values from hue using helper variables.
 * If hue value passed to the function is increased by 1/3 it returns red value.
 * If hue value passed to the function is unchanged it returns green value.
 * If hue value passed to the function is decreased by 1/3 it returns blue value.
 *
 * @param[in] v1  First helper variable (range 0 to 1).
 * @param[in] v2  Second helper variable (range 0 to 1).
 * @param[in] vH  Hue value.
 *
 * @return Value of red or green or blue.
 ******************************************************************************/
double Hue_to_RGB(double v1, double v2, double vH)
{
  if ( vH < 0) {
    vH += 1;
  }
  if ( vH > 1) {
    vH -= 1;
  }
  if ( (6 * vH) < 1) {
    return (v1 + (v2 - v1) * 6 * vH);
  }
  if ((2 * vH) < 1) {
    return (v2);
  }
  if ((3 * vH) < 2) {
    return (v1 + (v2 - v1) * (2.0 / 3 - vH) * 6);
  }
  return (v1);
}

/***************************************************************************//**
 * Convert color from HSL space to RGB space
 *
 * @param[in] hue        Hue value.
 * @param[in] saturation Saturation value.
 * @param[in] lightness  Lightness value.
 *
 * @return RGB color converted from HSL space.
 ******************************************************************************/
RGB_t HSL_to_RGB(uint16_t hue, uint16_t saturation, uint16_t lightness)
{
  RGB_t color;
  double R, G, B;
  double H, S, L;
  double var_1, var_2;

  /* Change the range to (0-1) */
  H = (double)hue / 65535;
  S = (double)saturation / 65535;
  L = (double)lightness / 65535;

  if (S == 0) {
    R = L;
    G = L;
    B = L;
  } else {
    if (L < 0.5) {
      var_2 = L * (1 + S);
    } else {
      var_2 = (L + S) - (S * L);
    }

    var_1 = 2 * L - var_2;

    R = Hue_to_RGB(var_1, var_2, H + 1.0 / 3);
    G = Hue_to_RGB(var_1, var_2, H);
    B = Hue_to_RGB(var_1, var_2, H - 1.0 / 3);
  }

  color.R = (uint8_t)(255.0 * R + 0.5);
  color.G = (uint8_t)(255.0 * G + 0.5);
  color.B = (uint8_t)(255.0 * B + 0.5);
  return color;
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
 * @param[in] hue          Hue level.
 * @param[in] saturation   Saturation level.
 ******************************************************************************/
void rgb_led_set(uint8_t m, uint16_t level, uint16_t hue, uint16_t saturation)
{
  RGB_t color = HSL_to_RGB(hue, saturation, level);
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
