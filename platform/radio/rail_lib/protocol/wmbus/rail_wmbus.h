/***************************************************************************//**
 * @file
 * @brief The WMBUS specific header file for the RAIL library.
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

#ifndef __RAIL_WMBUS_H__
#define __RAIL_WMBUS_H__

#include "rail_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @addtogroup WMBUS Wireless M-Bus
/// @ingroup Protocol_Specific
/// @brief Wireless M-Bus (WMBUS) configuration
/// @{

/**
 * @enum RAIL_WMBUS_Phy_t
 * @brief The RX variant of the WMBUS T+C PHY.
 */
RAIL_ENUM(RAIL_WMBUS_Phy_t) {
  /** subPhyId indicating a mode T frame A packet */
  RAIL_WMBUS_ModeTFrameA = 0U,
  /** subPhyId indicating a mode C frame A packet */
  RAIL_WMBUS_ModeCFrameA = 2U,
  /** subPhyId indicating a mode C frame B packet */
  RAIL_WMBUS_ModeCFrameB = 3U,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_WMBUS_ModeTFrameA ((RAIL_WMBUS_Phy_t) RAIL_WMBUS_ModeTFrameA)
#define RAIL_WMBUS_ModeCFrameA ((RAIL_WMBUS_Phy_t) RAIL_WMBUS_ModeCFrameA)
#define RAIL_WMBUS_ModeCFrameB ((RAIL_WMBUS_Phy_t) RAIL_WMBUS_ModeCFrameB)
#endif //DOXYGEN_SHOULD_SKIP_THIS

/**
 * Configure WMBUS simultaneous M2O RX of T and C modes feature.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] enableSimultaneousTCRx True to enable WMBUS simultaneous M2O RX of T and C modes.
 * @return Status code indicating success of the function call.
 *
 * If simultaneous M2O RX of T and C modes is enabled, when
 * PHY_wMbus_ModeTC_M2O_100k_frameA is loaded, mode T Frame A and mode C frame
 * A/B can be received. The mode and frame type of the last received packet is
 * available in \ref RAIL_RxPacketDetails_t::subPhyId.
 *
 * @note This WMBUS feature is supported only on some parts.
 * The preprocessor symbol \ref RAIL_WMBUS_SUPPORTS_SIMULTANEOUS_T_C_RX and the
 * runtime function \ref RAIL_WMBUS_SupportsSimultaneousTCRx() may be used to
 * test for support.
 */
RAIL_Status_t RAIL_WMBUS_Config(RAIL_Handle_t railHandle,
                                bool enableSimultaneousTCRx);

/// @} // End of group WMBUS

#ifdef __cplusplus
}
#endif

#endif // __RAIL_WMBUS_H__
