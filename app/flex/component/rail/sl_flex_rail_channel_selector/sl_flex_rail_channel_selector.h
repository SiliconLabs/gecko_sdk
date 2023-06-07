/***************************************************************************//**
 * @file
 * @brief Channel selection file.
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

#ifndef SL_FLEX_RAIL_CHANNEL_SELECTOR_H_
#define SL_FLEX_RAIL_CHANNEL_SELECTOR_H_

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_component_catalog.h"
#include "rail.h"
#if defined(SL_CATALOG_APP_LOG_PRESENT)
#include "app_log.h"
#endif
#if defined(SL_CATALOG_APP_ASSERT_PRESENT)
#include "app_assert.h"
#endif
#include "rail_config.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/*****************************************************************************
* Apply default channel setting
*****************************************************************************/
void set_configured_channel(void);

/******************************************************************************
 * Set which channel the app will communicate on.
 *
 * @param new_channel requested new channel number
 * @return 1 is channel number is valid else 0
 *****************************************************************************/
uint8_t set_selected_channel(uint16_t new_channel);

/******************************************************************************
 * Get which channel the app will communicate on.
 *
 * @return channel number
 *****************************************************************************/
uint16_t get_selected_channel(void);

/******************************************************************************
 * Restarts the RX operation on the selected channel
 *
 * @return status of the StartRX function
 *****************************************************************************/
RAIL_Status_t restart_rx_channel(void);

#endif /* SL_FLEX_RAIL_CHANNEL_SELECTOR_H_ */
