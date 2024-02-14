/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core utility functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_WISUN_APP_CORE_UTIL_H
#define SL_WISUN_APP_CORE_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

#include <stdint.h>
#include <stdlib.h>
#include "sl_wisun_types.h"
#include "sl_status.h"
#include "sl_wisun_app_core.h"
#include "cmsis_os2.h"
#include "sl_wisun_config.h"
#include "sl_wisun_app_core_config.h"
#include "app_project_info.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/// Exit from thread (wrapper)
#define exit(exitcode)                                    \
  do {                                                    \
    printf("[%s] Exit: %d\n",                             \
           osThreadGetName(osThreadGetId()), (exitcode)); \
    osThreadTerminate(osThreadGetId());                   \
  } while (0)

/// Assert POSIX API result with thread exit
#define assert_res(val, message)                                                     \
  do {                                                                               \
    printf("%s [%ld] %s.\n", message, (int32_t)val, (val == -1) ? "error" : "done"); \
    if ((val) == -1) {                                                               \
      exit(-1);                                                                      \
    }                                                                                \
  } while (0)

/// Convert stack size byte to word size
#define app_stack_size_word_to_byte(stack_size_word) \
  ((stack_size_word * sizeof(void *)) & 0xFFFFFFF8U)

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @ingroup SL_WISUN_APP_CORE_API
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * @brief Initialize Wi-SUN project information.
 * @details Init internal instance
 * @param[in] app_name Application name
 *****************************************************************************/
void sl_wisun_app_core_util_project_info_init(const char * app_name);

/**************************************************************************//**
 * @brief Print Wi-SUN project information.
 * @details Print project info in pretty or json format.
 * @param[in] json_format Json format required indicator
 *****************************************************************************/
void sl_wisun_app_core_util_project_info_print(const bool json_format);

/**************************************************************************//**
 * @brief Get Wi-SUN Project info
 * @details Get a constant instance of internal Wi-SUN project info
 * @return app_project_info_t * Project info
 *****************************************************************************/
const app_project_info_t * sl_wisun_app_core_util_project_info_get(void);

/**************************************************************************//**
 * @brief Wait for the connection.
 * @details This function doesn't call the sl_wisun_app_core_network_connect() function.
 *          The function provides a delay loop with optional heart beat printing
 *          till the connection state has not been changed.
 *****************************************************************************/
void sl_wisun_app_core_util_wait_for_connection(void);

/**************************************************************************//**
 * @brief Connect and wait for connection.
 * @details The function calls sl_wisun_app_core_network_connect() function and
 *          sl_wisun_app_core_util_wait_for_connection() function.
 *          It can be useful at the beginning of application thread.
 *****************************************************************************/
void sl_wisun_app_core_util_connect_and_wait(void);

/**************************************************************************//**
 * @brief The network is connected.
 * @details Wrapper function of join state getter
 * @return true Connected
 * @return false Not connected
 *****************************************************************************/
bool sl_wisun_app_core_util_network_is_connected(void);

/**************************************************************************//**
 * @brief Thread dispatch function
 * @details For low power LFN mode, the delay value is 'SL_WISUN_APP_CORE_THREAD_LP_DISPATCH_MS',
 *          for FFN mode, the delay is 1ms
 *****************************************************************************/
void sl_wisun_app_core_util_dispatch_thread(void);

/** @}*/

#ifdef __cplusplus
}
#endif

#endif  // SL_WISUN_APP_UTIL_H
