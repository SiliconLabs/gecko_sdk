/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application core component configuration header.
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
#ifndef SL_WISUN_APP_CORE_CONFIG_H
#define SL_WISUN_APP_CORE_CONFIG_H

/**************************************************************************//**
 * @defgroup SL_WISUN_APP_CORE_CONFIG Utility configuration
 * @ingroup SL_WISUN_APP_CORE
 * @{
 *****************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>


// <h> Regional Regulation

// corresponds to SL_WISUN_REGULATION_NONE
#define SL_WISUN_APP_CORE_REGULATION_NONE                      0U

// corresponds to SL_WISUN_REGULATION_ARIB
#define SL_WISUN_APP_CORE_REGULATION_ARIB                      1U

// <h> Regulation
// <o SL_WISUN_APP_CORE_REGULATION> Name of the Wi-SUN regional regulation or None
// <SL_WISUN_APP_CORE_REGULATION_NONE=> None
// <SL_WISUN_APP_CORE_REGULATION_ARIB=> ARIB
// <i> Default: SL_WISUN_SL_WISUN_APP_CORE_REGULATION_NONE
#define SL_WISUN_APP_CORE_REGULATION                            SL_WISUN_APP_CORE_REGULATION_NONE
// </h> Regulation

// <h> Wi-SUN regulation transmission budget
// <o SL_WISUN_APP_CORE_TX_BUDGET> Number of milliseconds per hour allowed to transmit in case of regional regulation.
// <i> Default: 720000 ms(corresponding to ARIB regulation)
#define SL_WISUN_APP_CORE_TX_BUDGET                             720000UL
// </h> Wi-SUN regulation transmission budget in milliseconds.

// <h> Wi-SUN regulation warning and alert thresholds
// <o SL_WISUN_APP_CORE_DEFAULT_REGULATION_WARNING_THRESHOLD> Transmission duration level warning threshold in percent or -1 to disable
// <i> Default: 85 %
#define SL_WISUN_APP_CORE_DEFAULT_REGULATION_WARNING_THRESHOLD  85U

// <o SL_WISUN_APP_CORE_DEFAULT_REGULATION_ALERT_THRESHOLD> Transmission duration level alert threshold in percent or -1 to disable
// <i> Default: 95 %
#define SL_WISUN_APP_CORE_DEFAULT_REGULATION_ALERT_THRESHOLD    95U
// </h> Wi-SUN regulation warning and alert thresholds

// </h> Regional Regulation set upon connection

// <h> Wi-SUN Application thread setup
// <o SL_WISUN_APP_CORE_MAIN_STACK_SIZE_WORD> Recommended Application thread stack size
// <i> Default: 256 word
#define SL_WISUN_APP_CORE_MAIN_STACK_SIZE_WORD                  256UL

// <o SL_WISUN_APP_CORE_THREAD_LP_DISPATCH_MS> Thread dispatch delay for low power mode
// <i> Default: 1000
#define SL_WISUN_APP_CORE_THREAD_LP_DISPATCH_MS                 1000UL

// </h> Wi-SUN Application thread setup

// <<< end of configuration section >>>

/** @}*/

#endif // SL_WISUN_APPLICATION_UTIL_CONFIG_H
