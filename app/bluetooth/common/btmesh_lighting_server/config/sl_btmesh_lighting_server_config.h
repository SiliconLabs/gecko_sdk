/***************************************************************************//**
 * @file
 * @brief
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
#ifndef SL_BTMESH_LIGHTING_SERVER_CONFIG_H
#define SL_BTMESH_LIGHTING_SERVER_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Light Lightness Server configuration

// <o LIGHTING_SERVER_NVM_SAVE_TIME> Timeout [ms] for saving States of the model to NVM.
// <i> Default: 5000
// <i> Timeout [ms] for saving States of the model to NVM.
#define LIGHTING_SERVER_NVM_SAVE_TIME   (5000)

// <o LIGHTING_SERVER_PS_KEY> PS Key for NVM Page where the States of the Lighting Model are saved.
// <i> Default: 0x4004
// <i> PS Key for NVM Page where the States of the Lighting Model are saved.
#define LIGHTING_SERVER_PS_KEY   (0x4004)

// <o LIGHTING_SERVER_PWM_UPDATE_PERIOD> Periodicity [ms] for updating the PWM duty cycle during a transition.
// <i> Default: 1
// <i> Periodicity [ms] for updating the PWM duty cycle during a transition.
#define LIGHTING_SERVER_PWM_UPDATE_PERIOD   (1)

// <o LIGHTING_SERVER_UI_UPDATE_PERIOD> for updating the UI with lightness level during a transition.
// <i> Default: 100
// <i> Periodicity [ms] for updating the UI with lightness level during a transition.
#define LIGHTING_SERVER_UI_UPDATE_PERIOD   (100)

// <o LIGHTING_SERVER_PWM_MINIMUM_BRIGHTNESS> Timer value for minimum PWM duty cycle.
// <i> Default: 1
// <i> Timer value for minimum PWM duty cycle.
#define LIGHTING_SERVER_PWM_MINIMUM_BRIGHTNESS   (1)

// <o LIGHTING_SERVER_PWM_MAXIMUM_BRIGHTNESS> Timer value for maximum PWM duty cycle.
// <i> Default: 0xFFFE
// <i> Timer value for minimum PWM duty cycle.
#define LIGHTING_SERVER_PWM_MAXIMUM_BRIGHTNESS   (0xFFFE)

// <h> Lightness Range

// <o LIGHTING_SERVER_LIGHTNESS_MIN> Minimum lightness value <0x0001-0xFFFF>
// <i> Determines the minimum non-zero lightness an element is configured to emit.
// <i> Default: 0x0001
#define LIGHTING_SERVER_LIGHTNESS_MIN   0x0001

// <o LIGHTING_SERVER_LIGHTNESS_MAX> Maximum lightness value <0x0001-0xFFFF>
// <i> Determines the maximum lightness an element is configured to emit.
// <i> The value of the Light Lightness Range Max state shall be greater than
// <i> or equal to the value of the Light Lightness Range Min state.
// <i> Default: 0xFFFF
#define LIGHTING_SERVER_LIGHTNESS_MAX   0xFFFF

//</h>

// <e LIGHTING_SERVER_LOGGING> Enable Logging
// <i> Default: 1
// <i> Enable / disable Logging for Lighting Server model specific messages for this component.
#define LIGHTING_SERVER_LOGGING   (1)

// <q LIGHTING_SERVER_DEBUG_PRINTS_FOR_STATE_CHANGE_EVENTS> Enable debug prints for each server state changed event.
// <i> Default: 0
// <i> Enable debug prints for each server state changed event.
#define LIGHTING_SERVER_DEBUG_PRINTS_FOR_STATE_CHANGE_EVENTS   (0)

// </e>

// </h>

// <<< end of configuration section >>>

// The PWM update period shall not be greater than the UI update period
#if (LIGHTING_SERVER_UI_UPDATE_PERIOD) < (LIGHTING_SERVER_PWM_UPDATE_PERIOD)
#error "The LIGHTING_SERVER_PWM_UPDATE_PERIOD shall be less than LIGHTING_SERVER_UI_UPDATE_PERIOD."
#endif

// Lightness maximum value cannot be less than minimum value
#if (LIGHTING_SERVER_LIGHTNESS_MAX) < (LIGHTING_SERVER_LIGHTNESS_MIN)
#error The value of the Lightness Range Max shall be greater than or equal to \
  the value of the Lightness Range Min state.
#endif // (LIGHTING_SERVER_LIGHTNESS_MAX) < (LIGHTING_SERVER_LIGHTNESS_MIN)

#endif // SL_BTMESH_LIGHTING_SERVER_CONFIG_H
