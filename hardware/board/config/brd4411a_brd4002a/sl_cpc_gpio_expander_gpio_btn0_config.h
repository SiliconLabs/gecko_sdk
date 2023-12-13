/***************************************************************************//**
 * @file
 * @brief CPC GPIO Expander instance configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_CPC_GPIO_EXPANDER_GPIO_BTN0_CONFIG_H
#define SL_CPC_GPIO_EXPANDER_GPIO_BTN0_CONFIG_H

// <s SL_CPC_GPIO_EXPANDER_GPIO_BTN0_NAME> GPIO Pin Name
// <i> Specify the name of the GPIO pin instance which is reported to the Host/Primary device
// <i> Default: "UNDEFINED"
#define SL_CPC_GPIO_EXPANDER_GPIO_BTN0_NAME               "BTN0"

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_CPC_GPIO_EXPANDER_GPIO_BTN0
// $[GPIO_SL_CPC_GPIO_EXPANDER_GPIO_BTN0]
#define SL_CPC_GPIO_EXPANDER_GPIO_BTN0_PORT      gpioPortB
#define SL_CPC_GPIO_EXPANDER_GPIO_BTN0_PIN       1

// [GPIO_SL_CPC_GPIO_EXPANDER_GPIO_BTN0]$

// <<< sl:end pin_tool >>>

#endif /* SL_CPC_GPIO_EXPANDER_GPIO_BTN0_CONFIG_H */
