/***************************************************************************//**
 * @file
 * @brief Application init
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
#include <assert.h>
#include "app_init.h"
#include "cmsis_os2.h"
#include "sl_cmsis_os2_common.h"
#include "app.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#define APP_STACK_SIZE_BYTES   512UL

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
void app_init(void)
{
  /* Creating App main thread */
  const osThreadAttr_t app_task_attr = {
    .name        = "AppMain",
    .attr_bits   = osThreadDetached,
    .cb_mem      = NULL,
    .cb_size     = 0,
    .stack_mem   = NULL,
    .stack_size  = APP_STACK_SIZE_BYTES,
    .priority    = osPriorityNormal,
    .tz_module   = 0
  };
  osThreadId_t app_thr_id = osThreadNew(app_task,
                                        NULL,
                                        &app_task_attr);
  assert(app_thr_id != NULL);
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
