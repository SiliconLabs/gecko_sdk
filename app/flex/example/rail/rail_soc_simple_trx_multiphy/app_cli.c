/***************************************************************************//**
 * @file
 * @brief app_cli.c
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <stdint.h>
#include "sl_component_catalog.h"
#include "em_chip.h"
#include "app_log.h"
#include "sl_cli.h"
#include "app_process.h"
#include "sl_rail_util_init.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif

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
 * CLI - info message: Unique ID of the board
 *****************************************************************************/
void cli_info(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  device_mode_t mode = get_device_mode();
  uint16_t active_channel = 0;
  uint8_t src = 0;
  uint8_t dest = 0;

  app_log_info("Info:\n");
  app_log_info("  MCU Id:          0x%016llX\n", SYSTEM_GetUnique());
  if (mode == M_ENDPOINT) {
    active_channel = get_active_channel();
    app_log_info("  Device mode:     endpoint\n");
    app_log_info("  Active channel:  %d\n", active_channel);
  } else {
    src = get_rx_channel();
    dest = get_tx_channel();
    app_log_info("  Device mode:     relay\n");
    app_log_info("  Direction:       ch%d -> ch%d\n", src, dest);
  }
}

/******************************************************************************
 * CLI - set_mode: Set device mode to endpoint or relay
 *****************************************************************************/
void cli_set_mode(sl_cli_command_arg_t *arguments)
{
  uint8_t new_device_mode = sl_cli_get_argument_uint8(arguments, 0);

  if (new_device_mode > 1) {
    app_log_error("Mode must be 0 or 1\n");
  } else {
    set_device_mode((device_mode_t)new_device_mode);
    app_log_info("Mode set to %s\n", new_device_mode ? "relay" : "endpoint");
  }
}

/******************************************************************************
 * CLI - set_active_channel: Select the radio channel for the endpoint device
 *****************************************************************************/
void cli_set_active_channel(sl_cli_command_arg_t *arguments)
{
  uint16_t channel = sl_cli_get_argument_uint16(arguments, 0);
  device_mode_t mode = get_device_mode();

  if (mode == M_ENDPOINT) {
    set_active_channel(channel);
    set_next_state(S_IDLE);
  } else {
    app_log_info("This command has no effect on relay devices\n");
    return;
  }

#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * CLI - send: Sets a flag indicating that a packet has to be sent
 *****************************************************************************/
void cli_send(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  device_mode_t mode = get_device_mode();
  uint16_t active_channel = get_active_channel();

  if (mode == M_ENDPOINT) {
    request_tx();
    set_next_state(S_IDLE);
    app_log_info("Send packet request on channel %d\n", active_channel);
  } else {
    app_log_info("This command has no effect on relay devices\n");
    return;
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * CLI - set_direction: Sets the direction of the data transfer
 *****************************************************************************/
void cli_set_direction(sl_cli_command_arg_t *arguments)
{
  uint8_t direction = sl_cli_get_argument_uint8(arguments, 0);
  device_mode_t mode = get_device_mode();

  if (mode == M_ENDPOINT) {
    app_log_info("This command has no effect on endpoint devices\n");
    return;
  }

  if (direction > 1) {
    app_log_error("Direction must be 0 or 1\n");
  } else {
    set_direction((direction_t)direction);
  }
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
