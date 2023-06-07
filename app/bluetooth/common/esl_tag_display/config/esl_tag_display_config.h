/***************************************************************************//**
 * @file
 * @brief ESL Tag Display component configuration macros
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
#ifndef ESL_TAG_DISPLAY_CONFIG_H
#define ESL_TAG_DISPLAY_CONFIG_H

/***********************************************************************************************//**
 * @addtogroup esl_tag_display
 * @{
 **************************************************************************************************/

// <<< Use Configuration Wizard in Context Menu >>>

// <h> ESL Tag Display configuration

// <o ESL_TAG_MAX_DISPLAYS> Display instances <1-102>
// <i> Default: 1
// <i> Define the maximum number of displays the ESL Tag utilizes. The absolute maximum number of displays comes from the ESL Service Specification.
#define ESL_TAG_MAX_DISPLAYS      (1)

// </h>

// <<< end of configuration section >>>

/** @} (end addtogroup esl_tag_display) */
#endif // ESL_TAG_DISPLAY_CONFIG_H
