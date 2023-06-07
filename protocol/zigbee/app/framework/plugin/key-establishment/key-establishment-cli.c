/***************************************************************************//**
 * @file
 * @brief CLI for the Key Establishment plugin.
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

void sli_zigbee_af_key_establishment_start_command(sl_cli_command_arg_t *arguments)
{
  EmberStatus status;
  EmberNodeId newPartnerId = (EmberNodeId)sl_cli_get_argument_uint16(arguments, 0);
  uint8_t endpoint = sl_cli_get_argument_uint8(arguments, 1);
  emberAfCorePrintln("Starting %pment w/ 0x%2x, EP: 0x%x", \
                     "Key Establish",
                     newPartnerId,
                     endpoint);
  emberAfCoreFlush();

  status = emberAfInitiateKeyEstablishment(newPartnerId, endpoint);
  emberAfCorePrintln("%p", (status == EMBER_SUCCESS ? "Success" : "Error"));
}

void sli_zigbee_af_key_establishment_interpan_command(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 eui64;
  EmberPanId panId = (EmberPanId)sl_cli_get_argument_uint16(arguments, 0);
  EmberStatus status;
  sl_zigbee_copy_eui64_arg(arguments, 1, eui64, true);

  emberAfCorePrint("Starting %pment w/ ", "Key Establish");
  emberAfCoreDebugExec(emberAfPrintBigEndianEui64(eui64));
  emberAfCorePrintln("");
  emberAfCoreFlush();

  status = emberAfInitiateInterPanKeyEstablishment(panId, eui64);
  emberAfCorePrintln("%p", (status == EMBER_SUCCESS ? "Success" : "Error"));
}
