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
#include "sl_wisun_app_core_util_config.h"

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
/* Connect and wait */
void app_wisun_connect_and_wait(void)
{
  app_wisun_network_connect();
  app_wisun_wait_for_connection();
}

/* Waiting for connection */
void app_wisun_wait_for_connection(void)
{
#if (HEARTBEAT_ENABLED == 1)
  uint8_t dot_line_cnt = 0;
#endif
  msleep(10);
  printf("\n");
  while (1) {
    if (app_wisun_network_is_connected()) {
      break;
    }
#if (HEARTBEAT_ENABLED == 1)
    printf((dot_line_cnt == HEARBEAT_SECTION_LENGTH ? "[%ds]\n" : "#"), dot_line_cnt);
    dot_line_cnt = dot_line_cnt == HEARBEAT_SECTION_LENGTH ? 0 : dot_line_cnt + 1;
#endif
    msleep(1000); // 1s
  }
}

bool app_wisun_network_is_connected(void)
{
  sl_wisun_join_state_t join_state = SL_WISUN_JOIN_STATE_DISCONNECTED;
  (void) sl_wisun_get_join_state(&join_state);
  return join_state == SL_WISUN_JOIN_STATE_OPERATIONAL ? true : false;
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
