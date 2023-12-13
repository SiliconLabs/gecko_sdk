/***************************************************************************//**
 * @file
 * @brief Application commandline core
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
#include <string.h>
#include "cmsis_os2.h"
#include "sl_wisun_cli_core.h"
#include "sl_wisun_cli_util.h"
#include "sl_cmsis_os2_common.h"
#include "sl_wisun_cli_settings.h"
#include "sl_wisun_cli_util_config.h"

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

#if defined(SL_CATALOG_WISUN_APP_CLI_PRESENT)
/**************************************************************************//**
 * @brief App CLI mutex
 *****************************************************************************/
static osMutexId_t _app_wisun_cli_mtx;

/**************************************************************************//**
 * @brief App CLI Mutex attribute
 *****************************************************************************/
static const osMutexAttr_t _app_wisun_cli_mtx_attr = {
  .name      = "AppWisunCliMutex",
  .attr_bits = osMutexRecursive,
  .cb_mem    = NULL,
  .cb_size   = 0
};
#endif

// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------

#if defined(SL_CATALOG_WISUN_APP_CLI_PRESENT)
/* Public app core mutex lock */
void app_wisun_cli_mutex_lock(void)
{
  assert(osMutexAcquire(_app_wisun_cli_mtx, osWaitForever) == osOK);
}

/* Public app core mutex unlock */
void app_wisun_cli_mutex_unlock(void)
{
  assert(osMutexRelease(_app_wisun_cli_mtx) == osOK);
}
#endif

/* Init App Wi-SUN CLI component */
void app_wisun_cli_init(void)
{
#if defined(SL_CATALOG_WISUN_APP_CLI_PRESENT)
  // init cli network mutex
  _app_wisun_cli_mtx = osMutexNew(&_app_wisun_cli_mtx_attr);
  assert(_app_wisun_cli_mtx != NULL);
#endif
  app_settings_init();
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
