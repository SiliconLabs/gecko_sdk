/***************************************************************************//**
 * @file
 * @brief CLI for the IAS Zone Client plugin.
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

#include "af.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"

#include "ias-zone-client.h"

#include "ias-zone-client-config.h"

void sli_zigbee_af_ias_zone_client_print_servers_command(sl_cli_command_arg_t *arguments)
{
  uint8_t i;
  emberAfIasZoneClusterPrintln("Index IEEE                 EP   Type   Status State ID");
  emberAfIasZoneClusterPrintln("---------------------------------------------------");
  for (i = 0; i < EMBER_AF_PLUGIN_IAS_ZONE_CLIENT_MAX_DEVICES; i++) {
    if (i < 10) {
      emberAfIasZoneClusterPrint(" ");
    }
    emberAfIasZoneClusterPrint("%d    (>)%X%X%X%X%X%X%X%X  ",
                               i,
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[7],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[6],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[5],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[4],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[3],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[2],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[1],
                               emberAfIasZoneClientKnownServers[i].ieeeAddress[0]);
    if (emberAfIasZoneClientKnownServers[i].endpoint < 10) {
      emberAfIasZoneClusterPrint(" ");
    }
    if (emberAfIasZoneClientKnownServers[i].endpoint < 100) {
      emberAfIasZoneClusterPrint(" ");
    }
    emberAfIasZoneClusterPrint("%d  ", emberAfIasZoneClientKnownServers[i].endpoint);
    emberAfIasZoneClusterPrintln("0x%2X 0x%2X 0x%X 0x%X",
                                 emberAfIasZoneClientKnownServers[i].zoneType,
                                 emberAfIasZoneClientKnownServers[i].zoneStatus,
                                 emberAfIasZoneClientKnownServers[i].zoneState,
                                 emberAfIasZoneClientKnownServers[i].zoneId);
  }
}

void sli_zigbee_af_ias_zone_client_clear_all_servers_command(sl_cli_command_arg_t *arguments)
{
  sli_zigbee_af_clear_servers();
}
