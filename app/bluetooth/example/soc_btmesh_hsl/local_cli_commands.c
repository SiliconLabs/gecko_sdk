/***************************************************************************//**
 * @file local_cli_commands.c
 * @brief CLI commands file
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifdef SL_COMPONENT_CATALOG_PRESENT
#include "sl_component_catalog.h"
#endif // SL_COMPONENT_CATALOG_PRESENT

#ifdef SL_CATALOG_CLI_PRESENT
#include "sl_btmesh.h"
#include "sl_bluetooth.h"
#include "sl_cli.h"
#include "app_log.h"
#include "app_assert.h"

/***************************************************************************//**
 * CLI Command to read BT Address and mesh UUID.
 ******************************************************************************/
void info(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
  bd_addr address;
  uint8_t address_type;
  uuid_128 uuid;

  sl_status_t sc = sl_bt_system_get_identity_address(&address, &address_type);
  app_assert_status_f(sc, "Failed to get Bluetooth address\r\n");
  app_log("Bluetooth %s address: %02X:%02X:%02X:%02X:%02X:%02X\r\n",
          address_type ? "static random" : "public device",
          address.addr[5],
          address.addr[4],
          address.addr[3],
          address.addr[2],
          address.addr[1],
          address.addr[0]);

  sc = sl_btmesh_node_get_uuid(&uuid);
  app_assert_status_f(sc, "Failed to get Bluetooth mesh uuid\r\n");
  app_log("Bluetooth mesh UUID: %02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X"
          "%02X%02X%02X%02X%02X\r\n",
          uuid.data[0],
          uuid.data[1],
          uuid.data[2],
          uuid.data[3],
          uuid.data[4],
          uuid.data[5],
          uuid.data[6],
          uuid.data[7],
          uuid.data[8],
          uuid.data[9],
          uuid.data[10],
          uuid.data[11],
          uuid.data[12],
          uuid.data[13],
          uuid.data[14],
          uuid.data[15]);
}

#endif // SL_CATALOG_CLI_PRESENT
