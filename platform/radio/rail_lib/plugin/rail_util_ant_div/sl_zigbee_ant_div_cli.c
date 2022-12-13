/***************************************************************************//**
 * @file
 * @brief sl_zigbee_ant_div_cli.c
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#include "sl_cli.h"
#include "sl_zigbee_debug_print.h"
#ifdef EZSP_HOST
#include "app/util/ezsp/ezsp-protocol.h"
#include "app/util/ezsp/ezsp.h"
#ifdef RAIL_SIM_EZSP
#include "af_main.h"
#else
#include "af.h"
#include "app/framework/util/af-main.h"
#endif //EZSP_SIM
#else //!EZSP_HOST
#include "sl_rail_util_ant_div.h"
#endif //EZSP_HOST

//-----------------------------------------------------------------------------
// Get TX antenna mode (0-don't switch,1-primary,2-secondary,3-TX antenna diversity)
// Console Command : "plugin antenna get-antenna-mode"
// Console Response: "TX antenna mode:<antennaMode>"
void emberAfPluginAntennaGetAntennaTxMode(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
#ifdef EZSP_HOST
  uint8_t antennaMode;
  uint8_t valueLength = sizeof(antennaMode);

  ezspGetValue(EZSP_VALUE_ANTENNA_MODE, &valueLength, &antennaMode);
#else //!EZSP_HOST
  sl_rail_util_antenna_mode_t antennaMode = sl_rail_util_ant_div_get_tx_antenna_mode();
#endif //EZSP_HOST
  sl_zigbee_app_debug_print("TX antenna mode:%d", antennaMode);
}

//-----------------------------------------------------------------------------
// Set TX antenna mode (0-don't switch,1-primary,2-secondary,3-TX antenna diversity)
// Console Command : "plugin antenna set-antenna-mode <antennaMode>"
// Console Response: "TX antenna mode:<antennaMode>"
void emberAfPluginAntennaSetAntennaTxMode(sl_cli_command_arg_t *arguments)
{
  uint8_t antennaMode = sl_cli_get_argument_uint8(arguments, 0);
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(antennaMode);

  emberAfSetEzspValue(EZSP_VALUE_ANTENNA_MODE,
                      valueLength,
                      &antennaMode,
                      "set TX antenna mode");
#else //!EZSP_HOST
  sl_rail_util_ant_div_set_tx_antenna_mode((sl_rail_util_antenna_mode_t)antennaMode);
#endif //EZSP_HOST
  emberAfPluginAntennaGetAntennaTxMode(arguments);
}

//-----------------------------------------------------------------------------
// Get RX antenna mode (0-don't switch,1-primary,2-secondary,3-RX antenna diversity)
// Console Command : "plugin antenna get-antenna-rx-mode"
// Console Response: "RX Antenna Mode: 0x<antennaMode>"
void emberAfPluginAntennaGetAntennaRxMode(sl_cli_command_arg_t *arguments)
{
  (void)arguments;
#ifdef EZSP_HOST
  uint8_t antennaMode;
  uint8_t valueLength = sizeof(antennaMode);

  ezspGetValue(EZSP_VALUE_ANTENNA_RX_MODE, &valueLength, &antennaMode);
#else //!EZSP_HOST
  sl_rail_util_antenna_mode_t antennaMode = sl_rail_util_ant_div_get_rx_antenna_mode();
#endif //EZSP_HOST
  sl_zigbee_app_debug_print("RX antenna mode:%d", antennaMode);
}

//-----------------------------------------------------------------------------
// Set RX antenna mode (0-don't switch,1-primary,2-secondary,3-RX antenna diversity)
// Console Command : "plugin antenna set-antenna-mode 0x<antennaMode>"
// Console Response: "RX Antenna Mode: 0x<antennaMode>"
void emberAfPluginAntennaSetAntennaRxMode(sl_cli_command_arg_t *arguments)
{
  uint8_t antennaMode = sl_cli_get_argument_uint8(arguments, 0);
#ifdef EZSP_HOST
  uint8_t valueLength = sizeof(antennaMode);

  emberAfSetEzspValue(EZSP_VALUE_ANTENNA_RX_MODE,
                      valueLength,
                      &antennaMode,
                      "set RX antenna mode");
#else //!EZSP_HOST
  sl_rail_util_ant_div_set_rx_antenna_mode((sl_rail_util_antenna_mode_t)antennaMode);
#endif //EZSP_HOST
  emberAfPluginAntennaGetAntennaRxMode(arguments);
}
