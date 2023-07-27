/***************************************************************************//**
 * @file
 * @brief The Sidewalk specific header file for the RAIL library.
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

#ifndef RAIL_SIDEWALK_H
#define RAIL_SIDEWALK_H

#ifdef __cplusplus
extern "C" {
#endif

// Get the standard include types
#include <stdint.h>
#include <stdbool.h>

// Get the RAIL specific structures and types
#include "rail_types.h"

/// @addtogroup SIDEWALK_PHY Sidewalk Radio Configurations
/// @ingroup Protocol_Specific
/// Radio configurations for the RAIL Sidewalk Accelerator
///
/// These radio configurations are used to configure Sidewalk when a function
/// such as \ref RAIL_Sidewalk_ConfigPhy2GFSK50kbps() is called. Each radio
/// configuration listed below is compiled into the RAIL library as a weak
/// symbol that will take into account per-die defaults. If the board
/// configuration in use has different settings than the default, such as a
/// different radio subsystem clock frequency, these radio configurations can
/// be overriden to account for those settings.
/// @{

/**
 * Default PHY to use for Sidewalk 2GFSK 50kbps. Will be NULL if
 * \ref RAIL_SUPPORTS_PROTOCOL_SIDEWALK is 0.
 */
extern const RAIL_ChannelConfig_t *const RAIL_Sidewalk_Phy2GFSK50kbps;

/**
 * Switch to the 2GFSK 50kbps Sidewalk PHY.
 *
 * @param[in] railHandle A handle for RAIL instance.
 * @return A status code indicating success of the function call.
 *
 * Use this function to switch to the 2GFSK 50kbps Sidewalk PHY.
 *
 * @note The Sidewalk PHY is supported only on some parts.
 * The preprocessor symbol \ref RAIL_SUPPORTS_PROTOCOL_SIDEWALK and the
 * runtime function \ref RAIL_SupportsProtocolSidewalk() may be used to
 * test for support of the Sidewalk PHY.
 */
RAIL_Status_t RAIL_Sidewalk_ConfigPhy2GFSK50kbps(RAIL_Handle_t railHandle);

/// @} // End of group SIDEWALK_PHY

#ifdef __cplusplus
}
#endif

#endif // RAIL_SIDEWALK_H
