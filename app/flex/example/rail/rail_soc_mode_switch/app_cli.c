/***************************************************************************//**
 * @file
 * @brief app_cli.c
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
#include <stdint.h>
#include "sl_component_catalog.h"
#include "em_chip.h"
#include "app_log.h"
#include "sl_cli.h"
#include "rail_config.h"
#include "app_process.h"
#include "app_init.h"
#include "sl_flex_mode_switch.h"

#if defined(SL_CATALOG_KERNEL_PRESENT)
#include "app_task_init.h"
#endif

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
/// Used for indicates the current status of forwarding rx packets on UART
#define ON   "ON"
/// Used for indicates the current status of forwarding rx packets on UART
#define OFF  "OFF"

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------
/// Flag, indicating received packet is forwarded on CLI or not
extern volatile bool rx_requested;

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * CLI - info message: Useful info about the radio board and the application.
 *****************************************************************************/
void cli_info(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  uint64_t mcu_id = SYSTEM_GetUnique();
  uint16_t base_channel = get_base_channel();
  uint16_t current_channel = get_channel();
  uint8_t phy_mode_id = get_phy_mode_id();
  const char* phy_modulation_str = get_phy_modulation_str();
  const char* ms_state_str = get_ms_state_str();
  const char* fw_rf_packet = (rx_requested == true) ? ON : OFF;

  app_log_info("Info:\n");
  app_log_info("         MCU Id: 0x%016llX\n", mcu_id);
  app_log_info("Current channel: %d\n", current_channel);
  app_log_info("   Base channel: %d\n", base_channel);
  app_log_info("    PHY mode id: %d\n", phy_mode_id);
  app_log_info(" PHY modulation: %s\n", phy_modulation_str);
  app_log_info("       Ms state: %s\n", ms_state_str);
  app_log_info("   Fw RX Packet: %s\n", fw_rf_packet);
}

/******************************************************************************
 * CLI - send: Sets a flag indicating that a packet has to be sent.
 *****************************************************************************/
void cli_send_packet(sl_cli_command_arg_t *arguments)
{
  (void) arguments;

  request_tx();
  app_log_info("Send packet request\n");
#if defined(SL_CATALOG_KERNEL_PRESENT)
  app_task_notify();
#endif
}

/******************************************************************************
 * CLI - receive: Turn on/off received message forwarding to cli.
 *****************************************************************************/
void cli_receive_packet(sl_cli_command_arg_t *arguments)
{
  uint8_t rxForward = sl_cli_get_argument_uint8(arguments, 0);
  const char* str_rx_fw;

  if (rxForward == 0) {
    rx_requested = false;
    str_rx_fw = OFF;
  } else {
    rx_requested = true;
    str_rx_fw = ON;
  }

  app_log_info("Received packets: %s\n", str_rx_fw);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
