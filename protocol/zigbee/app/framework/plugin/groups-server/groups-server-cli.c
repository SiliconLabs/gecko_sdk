/***************************************************************************//**
 * @file
 * @brief CLI for the Groups Server plugin.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include "app/framework/include/af.h"
#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "groups-server.h"

// plugin groups-server print
void sli_zigbee_af_groups_server_cli_print(sl_cli_command_arg_t *args)
{
  EmberStatus status;
  uint8_t i;

  for (i = 0; i < EMBER_BINDING_TABLE_SIZE; i++) {
    EmberBindingTableEntry entry;
    status = emberGetBinding(i, &entry);
    if ((status == EMBER_SUCCESS) && (entry.type == EMBER_MULTICAST_BINDING)) {
      emberAfCorePrintln("ep[%x] id[%2x]", entry.local,
                         HIGH_LOW_TO_INT(entry.identifier[1], entry.identifier[0]));
    }
  }
}

// plugin groups-server clear
void sli_zigbee_af_groups_server_cli_clear(sl_cli_command_arg_t *args)
{
  emberAfCorePrintln("Clearing all groups.");
  emberAfGroupsClusterClearGroupTableCallback(EMBER_BROADCAST_ENDPOINT);
}
