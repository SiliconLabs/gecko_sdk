/***************************************************************************//**
 * @file
 * @brief Pacgaking Assitent CLI file.
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
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_flex_rail_package_assistant.h"
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
void cli_get_print_package_info(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
#if defined(SL_CATALOG_APP_LOG_PRESENT)
  app_log_info("Print setting is %s\n", get_print_packet_info() > 0 ? "ON" : "OFF");
#endif
}

/******************************************************************************
 * CLI - set_print_package_info message: Get the print setting
 *****************************************************************************/
void cli_set_print_package_info(sl_cli_command_arg_t *arguments)
{
  uint8_t new_print_settings = sl_cli_get_argument_uint8(arguments, 0);
  if (new_print_settings > 0) {
    set_print_packet_info(1U);
  } else {
    set_print_packet_info(0U);
  }
#if defined(SL_CATALOG_APP_LOG_PRESENT)
  app_log_info("Print setting is %s\n", get_print_packet_info() > 0 ? "ON" : "OFF");
#endif
}
