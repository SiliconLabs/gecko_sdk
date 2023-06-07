/***************************************************************************//**
 * @file
 * @brief ESL Tag logging configuration macros
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
#ifndef ESL_LOG_CONFIG_H
#define ESL_LOG_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_cli_test_harness
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ESL Tag CLI Test Harness configuration

// <e ESL_CORE_LOG_ENABLE> ESL Core global logging
// <i> Enables the ESL Core logging in general.
// <i> Default: On
#define ESL_CORE_LOG_ENABLE                 1

// <q ESL_LOG_COMPONENT_APP_ENABLE> ESL Tag example application messages
// <i> Enables the logging for the ESL Tag example application code.
// <i> Default: On
#define ESL_LOG_COMPONENT_APP_ENABLE        1

// <q ESL_LOG_COMPONENT_CORE_ENABLE> ESL Core component messages
// <i> Enables the logging for the ESL Core component.
// <i> Default: On
#define ESL_LOG_COMPONENT_CORE_ENABLE       1

// <q ESL_LOG_COMPONENT_DISPLAY_ENABLE> ESL Display component messages
// <i> Enables the logging for the ESL Display component.
// <i> Default: On
#define ESL_LOG_COMPONENT_DISPLAY_ENABLE    1

// <q ESL_LOG_COMPONENT_RAM_IMAGE_ENABLE> ESL RAM image component messages
// <i> Enables the logging for the ESL RAM image component.
// <i> Default: On
#define ESL_LOG_COMPONENT_RAM_IMAGE_ENABLE  1

// <q ESL_LOG_COMPONENT_NVM_IMAGE_ENABLE> ESL NVM image component messages
// <i> Enables the logging for the ESL NVM image component.
// <i> Default: On
#define ESL_LOG_COMPONENT_NVM_IMAGE_ENABLE  1

// <q ESL_LOG_COMPONENT_LED_ENABLE> ESL LED component messages
// <i> Enables the logging for the ESL LED component.
// <i> Default: On
#define ESL_LOG_COMPONENT_LED_ENABLE        1

// <q ESL_LOG_COMPONENT_OTS_ENABLE> ESL OTS Server component messages
// <i> Enables the logging for the ESL OTS Server component.
// <i> Default: On
#define ESL_LOG_COMPONENT_OTS_ENABLE        1

// <q ESL_LOG_COMPONENT_SENSOR_ENABLE> ESL Sensor component messages
// <i> Enables the logging for the ESL Sensor component.
// <i> Default: On
#define ESL_LOG_COMPONENT_SENSOR_ENABLE     1

// </e>

// </h>

// <<< end of configuration section >>>

/** @} (end addtogroup esl_tag_cli_test_harness) */
#endif // ESL_LOG_CONFIG_H
