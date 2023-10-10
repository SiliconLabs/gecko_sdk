/***************************************************************************//**
 * @file
 * @brief Simple Button Driver User Config
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_SIMPLE_BUTTON_BTN0_CONFIG_H
#define SL_SIMPLE_BUTTON_BTN0_CONFIG_H

#include "em_gpio.h"
#include "sl_simple_button.h"

// <<< Use Configuration Wizard in Context Menu >>>

// <o SL_SIMPLE_BUTTON_BTN0_MODE>
// <SL_SIMPLE_BUTTON_MODE_INTERRUPT=> Interrupt
// <SL_SIMPLE_BUTTON_MODE_POLL_AND_DEBOUNCE=> Poll and Debounce
// <SL_SIMPLE_BUTTON_MODE_POLL=> Poll
// <i> Default: SL_SIMPLE_BUTTON_MODE_INTERRUPT
#define SL_SIMPLE_BUTTON_BTN0_MODE       SL_SIMPLE_BUTTON_MODE_INTERRUPT
// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>

// <gpio> SL_SIMPLE_BUTTON_BTN0
// $[GPIO_SL_SIMPLE_BUTTON_BTN0]
#define SL_SIMPLE_BUTTON_BTN0_PORT               gpioPortB
#define SL_SIMPLE_BUTTON_BTN0_PIN                0

// [GPIO_SL_SIMPLE_BUTTON_BTN0]$

// <<< sl:end pin_tool >>>

#endif // SL_SIMPLE_BUTTON_BTN0_CONFIG_H
