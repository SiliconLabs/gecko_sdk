/***************************************************************************//**
 * @file
 * @brief ESL Tag Sensor component configuration macros
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
#ifndef ESL_TAG_SENSOR_CONFIG_H
#define ESL_TAG_SENSOR_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_sensor
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ESL Tag Sensor: built-in sensors configuration

// <o ESL_SENSOR_INFO_POOL_SIZE> Sensor Data Structures pool size <4-254>
// <i> Define the size of the statically allocated RAM area for sensor object store on the ESL Tag.
// <i> The exact size of the storage space required depends on the number and type of sensors to be registered.
// <i> Default: 32
#define ESL_SENSOR_INFO_POOL_SIZE                   32

// <q ESL_SENSOR_INPUT_VOLTAGE_ENABLE> Battery voltage
// <i> Enables the 'Present Input Voltage' sensor.
// <i> Default: On
#define ESL_SENSOR_INPUT_VOLTAGE_ENABLE             1

// <q ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE> Operating temperature
// <i> Enables the 'Present Device Operating Temperature' sensor.
// <i> Default: On
#define ESL_SENSOR_OPERATING_TEMPERATURE_ENABLE     1

// <e ESL_SENSOR_FW_REVISION_ENABLE> Firmware revision
// <i> Enables the 'Device Firmware Revision' sensor.
// <i> For more info on semantic versioning, see https://semver.org/
// <i> Default: On
#define ESL_SENSOR_FW_REVISION_ENABLE               1

// <o ESL_SENSOR_FW_REVISION_MAJOR> Major <0-99>
// <i> Semantic firmware versioning: major field.
#define ESL_SENSOR_FW_REVISION_MAJOR                1

// <o ESL_SENSOR_FW_REVISION_MINOR> Minor <0-99>
// <i> Semantic firmware versioning: minor field.
#define ESL_SENSOR_FW_REVISION_MINOR                0

// <o ESL_SENSOR_FW_REVISION_PATCH> Patch <0-99>
// <i> Semantic firmware versioning: patch field.
#define ESL_SENSOR_FW_REVISION_PATCH                0
// </e>

// <e ESL_SENSOR_MANUFACTURING_DATE_ENABLE> Date of manufacturing
// <i> Enables the 'Date of Manufacturing' sensor.
// <i> Default: On
#define ESL_SENSOR_MANUFACTURING_DATE_ENABLE        1

// <o ESL_SENSOR_MANUFACTURING_DAY> Day <1-31>
// <i> Day of the manufacturing date.
#define ESL_SENSOR_MANUFACTURING_DAY                20

// <o ESL_SENSOR_MANUFACTURING_MONTH> Month
// <1=> January
// <2=> February
// <3=> March
// <4=> April
// <5=> May
// <6=> June
// <7=> July
// <8=> August
// <9=> September
// <10=> October
// <11=> November
// <12=> December
// <i> Month of the manufacturing date.
#define ESL_SENSOR_MANUFACTURING_MONTH              6

// <o ESL_SENSOR_MANUFACTURING_YEAR> Year <2022-2082>
// <i> Year of the manufacturing date.
#define ESL_SENSOR_MANUFACTURING_YEAR               2022
// </e>

// <e ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE> Operating temperature range
// <i> Enables the 'Device Operating Temperature Range' sensor.
// <i> Default: On
#define ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_ENABLE  1

// <o ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MIN> Minimum temperature <-55..125>
// <i> Temperature range: 'Minimum Temperature' field.
// <i> Default: 0 [degree Celsius]
#define ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MIN     0

// <o ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MAX> Maximum temperature <-55..125>
// <i> Temperature range: 'Maximum Temperature' field.
// <i> Default: 70 [degree Celsius]
#define ESL_SENSOR_DEVICE_TEMPERATURE_RANGE_MAX     70
// </e>

// </h>

// <<< end of configuration section >>>

/** @} (end addtogroup esl_tag_sensor) */
#endif // ESL_TAG_SENSOR_CONFIG_H
