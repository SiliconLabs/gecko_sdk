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
#include <string.h>
#include PLATFORM_HEADER
#include "em_chip.h"
#include "stack/include/ember.h"
#include "hal/hal.h"
#include "sl_cli.h"
#include "app_log.h"
#include "app_process.h"
#include "sl_light_switch.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define ENABLED  "enabled"
#define DISABLED "disabled"

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------
// Connect Tx options
static EmberMessageOptions tx_options = EMBER_OPTIONS_NONE;
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// State machine of the switch
extern light_switch_state_machine_t state;
/// Indicates the light toggle request
extern bool light_toggle_required;
///This structure contains all the flags used in the state machine
extern switch_application_flags_t state_machine_flags;
// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

/******************************************************************************
 * CLI - reset command
 *****************************************************************************/
void cli_reset(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  halReboot();
}

/******************************************************************************
 * CLI - JOIN command
 *****************************************************************************/
void cli_join(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  state_machine_flags.join_request = true;
}

/******************************************************************************
 * CLI - Light toggle command
 *****************************************************************************/
void cli_toggle_light(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  if (state == S_OPERATE) {
    light_toggle_required = true;
  }
}

/******************************************************************************
 * CLI - Leave network command
 *****************************************************************************/
void cli_leave(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  emberResetNetworkState();
  state_machine_flags.leave_request = true;
}

/******************************************************************************
 * CLI - info command
 * It lists the main attributes of the current state of the node
 *****************************************************************************/
void cli_info(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  char* is_ack = ((tx_options & EMBER_OPTIONS_ACK_REQUESTED) ? ENABLED : DISABLED);
  char* is_security = ((tx_options & EMBER_OPTIONS_SECURITY_ENABLED) ? ENABLED : DISABLED);
  char* is_high_prio = ((tx_options & EMBER_OPTIONS_HIGH_PRIORITY) ? ENABLED : DISABLED);

  app_log_info("Info:\n");
  app_log_info("         MCU Id: 0x%llX\n", SYSTEM_GetUnique());
  app_log_info("  Network state: 0x%02X\n", emberNetworkState());
  app_log_info("      Node type: 0x%02X\n", emberGetNodeType());
  app_log_info("        Node id: 0x%04X\n", emberGetNodeId());
  app_log_info("         Pan id: 0x%04X\n", emberGetPanId());
  app_log_info("        Channel: %d\n", (uint16_t)emberGetRadioChannel());
  app_log_info("          Power: %d\n", (int16_t)emberGetRadioPower());
  app_log_info("     TX options: MAC acks %s, security %s, priority %s\n", is_ack, is_security, is_high_prio);
}

/******************************************************************************
 * CLI - set PAN ID
 *****************************************************************************/
void cli_set_pan_id(sl_cli_command_arg_t *arguments)
{
  uint16_t pan_id = sl_cli_get_argument_uint16(arguments, 0);
  sl_set_pan_id(pan_id);
}

/******************************************************************************
 * CLI - set the communication channel
 *****************************************************************************/
void cli_set_channel(sl_cli_command_arg_t *arguments)
{
  uint16_t channel = sl_cli_get_argument_uint16(arguments, 0);
  sl_set_channel(channel);
}
