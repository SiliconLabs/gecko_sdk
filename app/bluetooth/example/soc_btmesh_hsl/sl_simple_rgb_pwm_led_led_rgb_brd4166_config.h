/***************************************************************************//**
 * @file
 * @brief Simple RGB PWM Led Driver Configuration
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_SIMPLE_RGB_PWM_LED_INSTANCE_CONFIG_H
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h>Simple RGB PWM LED Configuration
// <o SL_SIMPLE_RGB_PWM_LED_INSTANCE_FREQUENCY> PWM frequency [Hz]
// <i> Sets the frequency of the PWM signal
// <i> 0 = Don't care
// <i> Default: 10000
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_FREQUENCY      10000

// <o SL_SIMPLE_RGB_PWM_LED_INSTANCE_RESOLUTION> PWM resolution <2-65536>
// <i> Specifies the PWM (dimming) resolution. I.e. if you want a
// <i> dimming resolution that takes the input values from 0 to 99,
// <i> set this value to 100
// <i> Default: 256
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RESOLUTION     256

// <o SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_POLARITY> Red LED Polarity
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_POLARITY   SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH

// <o SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_POLARITY> Green LED Polarity
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_POLARITY SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH

// <o SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_POLARITY> Blue LED Polarity
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW=> Active low
// <SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH=> Active high
// <i> Default: SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_LOW
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_POLARITY  SL_SIMPLE_RGB_PWM_LED_POLARITY_ACTIVE_HIGH
// </h> end led configuration

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <timer channel=RED,GREEN,BLUE> SL_SIMPLE_RGB_PWM_LED_INSTANCE
// $[TIMER_SL_SIMPLE_RGB_PWM_LED_INSTANCE]
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_PERIPHERAL     TIMER1
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_PERIPHERAL_NO  1

#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_CHANNEL    0
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_PORT       gpioPortD
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_PIN        11
 #define SL_SIMPLE_RGB_PWM_LED_INSTANCE_RED_LOC       19

#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_CHANNEL  1
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_PORT     gpioPortD
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_PIN      12
 #define SL_SIMPLE_RGB_PWM_LED_INSTANCE_GREEN_LOC     19

#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_CHANNEL   2
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_PORT      gpioPortD
#define SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_PIN       13
 #define SL_SIMPLE_RGB_PWM_LED_INSTANCE_BLUE_LOC      19
// [TIMER_SL_SIMPLE_RGB_PWM_LED_INSTANCE]$

// <<< sl:end pin_tool >>>

#endif // SL_SIMPLE_RGB_PWM_LED_INSTANCE_CONFIG_H
