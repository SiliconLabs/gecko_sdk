/***************************************************************************//**
 * @file
 * @brief Channel Selection CLI file.
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
#include "sl_cli.h"

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

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * CLI - get_print_package_info message: Get the print setting
 *****************************************************************************/
void cli_get_channel(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
#if defined(SL_CATALOG_APP_LOG_PRESENT)
  app_log_info("Current active channel %d\n", get_selected_channel());
#endif
}

/******************************************************************************
 * CLI - set_print_package_info message: Get the print setting
 *****************************************************************************/
void cli_set_channel(sl_cli_command_arg_t *arguments)
{
  uint8_t new_channel = sl_cli_get_argument_uint16(arguments, 0);
  uint8_t success = set_selected_channel(new_channel);
#if defined(SL_CATALOG_APP_LOG_PRESENT)
  if (success) {
    app_log_info("Selected channel updated successfully\n");
  } else {
    app_log_warning("New channel is not in range\n");
  }
#endif
  RAIL_Status_t status = RAIL_STATUS_NO_ERROR;
  status = restart_rx_channel();
  if (status != RAIL_STATUS_NO_ERROR) {
#if defined(SL_CATALOG_APP_LOG_PRESENT)
    app_log_warning("RX change didn't happened\n");
#endif
  }
}
