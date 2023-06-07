/***************************************************************************//**
 * @file
 * @brief This file defines the standalone bootloader server CLI.
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
#include "app/framework/include/af-types.h"
#include "app/framework/plugin/standalone-bootloader-common/bootloader-protocol.h"
#include "standalone-bootloader-server.h"
#include "app/framework/plugin/ota-common/ota-cli.h"

#include "app/util/serial/sl_zigbee_command_interpreter.h"

//------------------------------------------------------------------------------
// Forward declarations
void sendLaunchRequestToTarget(sl_cli_command_arg_t *arguments)
{
  uint8_t index = sl_cli_get_argument_uint8(arguments, 0);
  EmberAfOtaImageId id = sli_zigbee_af_ota_find_image_id_by_index(index);
  uint8_t tag =  sl_cli_get_argument_uint8(arguments, 1);

  emberAfPluginStandaloneBootloaderServerStartClientBootloadWithCurrentTarget(&id, tag);
}

void sendLaunchRequestToEui(sl_cli_command_arg_t *arguments)
{
  EmberEUI64 longId;
  uint8_t index = sl_cli_get_argument_uint8(arguments, 1);
  EmberAfOtaImageId id = sli_zigbee_af_ota_find_image_id_by_index(index);
  uint8_t tag =  sl_cli_get_argument_uint8(arguments, 2);
  sl_zigbee_copy_eui64_arg(arguments, 0, longId, false);

  emberAfPluginStandaloneBootloaderServerStartClientBootload(longId, &id, tag);
}
