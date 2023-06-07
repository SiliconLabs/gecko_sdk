/***************************************************************************//**
 * @file
 * @brief This file implements commands for configuring WMBUS simultaneous RX
 *        of T and C modes Specific Functions
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "response_print.h"

#include "rail.h"
#include "rail_wmbus.h"
#include "app_common.h"

void configWmbus(sl_cli_command_arg_t *args)
{
  CHECK_RAIL_HANDLE(sl_cli_get_command_string(args, 0));
  bool enableSimultaneousTCRx = !!sl_cli_get_argument_uint8(args, 0);
  RAIL_Status_t status = RAIL_WMBUS_Config(railHandle, enableSimultaneousTCRx);
  if (status != RAIL_STATUS_NO_ERROR) {
    responsePrintError(sl_cli_get_command_string(args, 0), 0x24, "Failed to (un)set simultaneous M2O RX of T and C modes.");
  } else {
    responsePrint(sl_cli_get_command_string(args, 0), "simultaneous M2O RX of T and C modes:%s",
                  enableSimultaneousTCRx ? "Enabled" : "Disabled");
  }
}
