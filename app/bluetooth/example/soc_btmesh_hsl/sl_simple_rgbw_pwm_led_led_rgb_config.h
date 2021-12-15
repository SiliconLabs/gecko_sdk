/***************************************************************************//**
 * @file
 * @brief Simple RGBW PWM Led Driver Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef SL_SIMPLE_RGBW_PWM_LED_LED_RGB_CONFIG_H
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Simple RGBW PWM LED Configuration
// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_FREQUENCY> PWM frequency [Hz]
// <i> Sets the frequency of the PWM signal
// <i> 0 = Don't care
// <i> Default: 10000
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_FREQUENCY      10000

// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RESOLUTION> PWM resolution <2-65536>
// <i> Specifies the PWM (dimming) resolution. I.e. if you want a
// <i> dimming resolution that takes the input values from 0 to 99,
// <i> set this value to 100
// <i> Default: 256
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RESOLUTION     256

// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_POLARITY> Red LED Polarity
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_POLARITY   SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH

// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_POLARITY> Green LED Polarity
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_POLARITY SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH

// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_POLARITY> Blue LED Polarity
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_POLARITY  SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH

// <o SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_POLARITY> White LED Polarity
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_POLARITY SL_SIMPLE_RGBW_PWM_LED_POLARITY_ACTIVE_HIGH
// </h> end led configuration

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <timer channel=RED,GREEN,BLUE,WHITE> SL_SIMPLE_RGBW_PWM_LED_LED_RGB
// $[TIMER_SL_SIMPLE_RGBW_PWM_LED_LED_RGB]
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_PERIPHERAL TIMER1
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_PERIPHERAL_NO 1

#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_CHANNEL 0
// TIMER1 CC0 on PD11
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_PORT  gpioPortD
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_PIN   11
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_RED_LOC   19

#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_CHANNEL 1
// TIMER1 CC1 on PD12
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_PORT gpioPortD
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_PIN 12
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_GREEN_LOC 19

#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_CHANNEL 2
// TIMER1 CC2 on PD13
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_PORT gpioPortD
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_PIN  13
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_BLUE_LOC  19

#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_CHANNEL 3
// TIMER1 CC3 on PC6
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_PORT gpioPortC
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_PIN 6
#define SL_SIMPLE_RGBW_PWM_LED_LED_RGB_WHITE_LOC 8
// [TIMER_SL_SIMPLE_RGBW_PWM_LED_LED_RGB]$

// <<< sl:end pin_tool >>>

#endif // SL_SIMPLE_RGBW_PWM_LED_LED_RGB_CONFIG_H
