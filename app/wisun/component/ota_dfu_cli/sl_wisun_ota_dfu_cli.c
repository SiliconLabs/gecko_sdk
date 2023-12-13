/***************************************************************************//**
 * @file
 * @brief OTA DFU commandline interface handler
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include <stdio.h>
#include "sl_cli.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_ota_dfu.h"
#include "sl_wisun_ota_dfu_config.h"

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

void app_fw_update_start(sl_cli_command_arg_t *arguments)
{
  sl_status_t stat = SL_STATUS_FAIL;
  (void) arguments;
  stat = sl_wisun_ota_dfu_start_fw_update();
  printf("[Firmware update %s]\n", stat == SL_STATUS_OK ? "started" : "cannot be started");
}

void app_fw_update_stop(sl_cli_command_arg_t *arguments)
{
  sl_status_t stat = SL_STATUS_FAIL;
  (void) arguments;
  stat = sl_wisun_ota_dfu_stop_fw_update();
  printf("[Firmware update %s]\n", stat == SL_STATUS_OK ? "stopped" : "cannot be stopped");
}

void app_fw_reboot_and_install(sl_cli_command_arg_t *arguments)
{
  (void) arguments;
#if SL_WISUN_OTA_DFU_AUTO_INSTALL_ENABLED
  printf("[Firmware reboot command is not available in auto-reboot mode]\n");
#else
  printf("[Installing firmware...]\n");
  (void) sl_wisun_ota_dfu_reboot_and_install();
  printf("[Firmware update reboot was unsuccesful]\n");
#endif
}

void app_fw_update_status(sl_cli_command_arg_t *arguments)
{
  const char *str = NULL;
  (void) arguments;
  str = sl_wisun_ota_dfu_get_fw_update_status_json_str();

  if (str == NULL) {
    printf("[Error: firmware update status get]\n");
  } else {
    printf("%s\n", str);
    sl_wisun_ota_dfu_free_fw_update_status_json_str(str);
  }
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
