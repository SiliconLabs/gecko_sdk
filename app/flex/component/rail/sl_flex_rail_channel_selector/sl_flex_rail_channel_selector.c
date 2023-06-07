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
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_flex_rail_channel_selector.h"
#include "sl_flex_rail_channel_selector_config.h"
#include "sl_rail_util_init.h"
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
static volatile uint16_t selected_channel = 0;

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Set which channel the app will communicate on
 *****************************************************************************/
uint8_t set_selected_channel(uint16_t new_channel)
{
  uint16_t start = channelConfigs[0]->configs[0U].channelNumberStart;
  uint16_t end = channelConfigs[0]->configs[0U].channelNumberEnd;
  if (start <= new_channel && new_channel <= end) {
    selected_channel = new_channel;
    return 1;
  } else {
#if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_error("Out of range! Correct range is %d - %d\n", start, end);
#endif
    return 0;
  }
}

/******************************************************************************
 * Get which channel the app will communicate on
 *****************************************************************************/
uint16_t get_selected_channel(void)
{
  return selected_channel;
}

/*****************************************************************************
* Apply default channel setting
*****************************************************************************/
void set_configured_channel(void)
{
  uint8_t success = set_selected_channel(DEFAULT_CHANNEL);
#if defined(SL_CATALOG_APP_ASSERT_PRESENT)
  app_assert(success == 1,
             "Default channel is not in range\n");
#else
  while (!success) ;
#endif
}

/******************************************************************************
 * Restarts the RX operation on the selected channel
 *****************************************************************************/
RAIL_Status_t restart_rx_channel(void)
{
  RAIL_Handle_t rail_handle = sl_rail_util_get_handle(SL_RAIL_UTIL_HANDLE_INST0);
  RAIL_Status_t status = RAIL_StartRx(rail_handle, get_selected_channel(), NULL);
#if defined(SL_CATALOG_APP_LOG_PRESENT)
  if (status != RAIL_STATUS_NO_ERROR) {
    app_log_warning("After initialization RAIL_StartRx() result:%d\n", status);
  }
#endif
  return status;
}
