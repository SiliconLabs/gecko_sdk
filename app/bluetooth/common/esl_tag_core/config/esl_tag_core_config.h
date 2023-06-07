/***************************************************************************//**
 * @file
 * @brief ESL Tag Core component configuration macros
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
#ifndef ESL_TAG_CORE_CONFIG_H
#define ESL_TAG_CORE_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_core
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ESL Tag Core configuration

// <o ESL_TAG_ADVERTISING_INTERVAL_MIN> Minimum connectable advertising interval <100-10000>
// <i> Default: 750
// <i> Define the minimum time interval of connectable advertising packets in milliseconds the ESL Tag needs.
// <i> The actual advertising interval will be randomized between min and max values for system scalability.
#define ESL_TAG_ADVERTISING_INTERVAL_MIN          750

// <o ESL_TAG_ADVERTISING_INTERVAL_MAX> Maximum connectable advertising interval <100-10000>
// <i> Default: 1500
// <i> Define the maximum time interval of connectable advertising packets in milliseconds the ESL Tag allows.
#define ESL_TAG_ADVERTISING_INTERVAL_MAX          1500

// <o ESL_TAG_MAX_SYNC_LOST_COUNT> Missed sync receives before timeout [intervals]<0-3276>
// <i> Set the maximum grace period for consecutive unsuccessful PAwR receive before sync timeout.
// <i> To use the maximum timeout by PAwR specification (163,84s) regardless of the actual interval please set to zero.
// <i> Otherwise, the timeout will be [intervals]* periodic interval [ms] or the maximum - whichever is smaller.
// <i> Default: 3
#define ESL_TAG_MAX_SYNC_LOST_COUNT               3

// <q ESL_TAG_VENDOR_OPCODES_ENABLED> ESL Vendor-specific tag support
// <i> Enables the ESL Vendor-specific tag support for TLV opcodes
// <i> Default: On
#define ESL_TAG_VENDOR_OPCODES_ENABLED            1

// <e ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE> Built-in battery level measurement
// <i> Enables the built-in battery level measurement and warning on low level.
// <i> Default: On
#define ESL_TAG_BUILTIN_BATTERY_MEASURE_ENABLE    1

// <o ESL_TAG_BATTERY_LEVEL_FULL_MILLIVOLTS> Battery full level [mV]<3000-4300>
// <i> Electric potential between battery terminals at fully charge in milli Volts unit. Reference value, only.
// <i> Default: 3200
#define ESL_TAG_BATTERY_LEVEL_FULL_MILLIVOLTS     3200

// <o ESL_TAG_BATTERY_LEVEL_LOW_MILLIVOLTS> Battery low warning level [mV]<2200-2999>
// <i> Electric potential between battery terminals at which the ESL Tag shall set the Service Needed Basic State flag.
// <i> Default: 2400
#define ESL_TAG_BATTERY_LEVEL_LOW_MILLIVOLTS      2400

// <o ESL_TAG_BATTERY_MEASUREMENT_INTERVAL_MIN> Measurement validity period [minutes]<1-2880>
// <i> Set the validity period of the battery voltage measurement - this is the time interval after which a new measurement will be taken on request.
// <i> Default: 10
#define ESL_TAG_BATTERY_MEASUREMENT_INTERVAL_MIN  10

// </e>

// </h>

// <<< end of configuration section >>>

// convert ESL_TAG_BATTERY_MEASUREMENT_INTERVAL_MIN given in [min] to [ms] unit
#define ESL_TAG_BATTERY_MEASUREMENT_INTERVAL_MS \
  (ESL_TAG_BATTERY_MEASUREMENT_INTERVAL_MIN * 60 * 1000)

/** @} (end addtogroup esl_tag_core) */
#endif // ESL_TAG_CORE_CONFIG_H
