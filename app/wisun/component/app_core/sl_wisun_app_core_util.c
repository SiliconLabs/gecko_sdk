/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core utility functions
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include <string.h>
#include "sl_wisun_api.h"
#include "sl_wisun_app_core_util.h"
#include "sl_wisun_app_core_config.h"
#include "sl_wisun_app_core.h"
#include "app_project_info.h"
#include "sl_wisun_config.h"
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

/// Project info instance
static app_project_info_t _app_project_info = { 0 };

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

/* Init project info */
void sl_wisun_app_core_util_project_info_init(const char * app_name)
{
  const app_project_info_version_t *stack_ver = NULL;
  app_project_info_get(&_app_project_info);
  _app_project_info.project_name = app_name;

  // print app name
  printf("\n%s\n", _app_project_info.project_name);

  // print stack version
  stack_ver = app_project_info_get_version(APP_PROJECT_INFO_VERSION_ID_WISUN, &_app_project_info);
  app_project_info_print_version(stack_ver, printf, "* Wi-SUN Stack version", true);
}

/* Print project info */
void sl_wisun_app_core_util_project_info_print(const bool json_format)
{
  if (json_format) {
    app_project_info_print_json(&_app_project_info, printf);
  } else {
    app_project_info_print_pretty(&_app_project_info, printf);
  }
}

/* Connect and wait */
void sl_wisun_app_core_util_connect_and_wait(void)
{
  sl_wisun_app_core_network_connect();
  sl_wisun_app_core_util_wait_for_connection();
}

/* Waiting for connection */
void sl_wisun_app_core_util_wait_for_connection(void)
{
  (void) sl_wisun_app_core_wait_state((1 << SL_WISUN_APP_CORE_STATE_NETWORK_CONNECTED), osWaitForever);
}

bool sl_wisun_app_core_util_network_is_connected(void)
{
  sl_wisun_join_state_t join_state = sl_wisun_app_core_get_join_state();
  return join_state == SL_WISUN_JOIN_STATE_OPERATIONAL ? true : false;
}

void sl_wisun_app_core_util_dispatch_thread(void)
{
#if !defined(WISUN_CONFIG_DEVICE_TYPE)
  uint8_t device_type = SL_WISUN_ROUTER;
#else
  uint8_t device_type = WISUN_CONFIG_DEVICE_TYPE;
#endif

  if (device_type == SL_WISUN_LFN) {
    osDelay(SL_WISUN_APP_CORE_THREAD_LP_DISPATCH_MS);
  } else {
    osDelay(1UL);
  }
}

const app_project_info_t * sl_wisun_app_core_util_project_info_get(void)
{
  return (const app_project_info_t * ) &_app_project_info;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
