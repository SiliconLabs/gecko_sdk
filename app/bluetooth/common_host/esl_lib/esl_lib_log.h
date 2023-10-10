/***************************************************************************//**
 * @file
 * @brief ESL AP Library - Logging header
 *******************************************************************************
 * # License
 * <b>Copyright 2023 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef ESL_LIB_LOG_H
#define ESL_LIB_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "esl_lib.h"
#include "app_log.h"

#define ESL_LIB_LOG_BUFFER_SIZE      2048
#define ESL_LIB_LOG_ADDR_FORMAT      "type %u %s address: %02X:%02X:%02X:%02X:%02X:%02X"
#define ESL_LIB_LOG_HANDLE_FORMAT    "[0x%p] "
#define ESL_LIB_LOG_ADDR(_addr)                 \
  (_addr).address_type,                         \
  ((_addr).address_type ? "random" : "public"), \
  (_addr).address.addr[5],                      \
  (_addr).address.addr[4],                      \
  (_addr).address.addr[3],                      \
  (_addr).address.addr[2],                      \
  (_addr).address.addr[1],                      \
  (_addr).address.addr[0]

#define ESL_LIB_LOG_BD_ADDR(_bd_addr) \
  (_bd_addr).addr[5],                 \
  (_bd_addr).addr[4],                 \
  (_bd_addr).addr[3],                 \
  (_bd_addr).addr[2],                 \
  (_bd_addr).addr[1],                 \
  (_bd_addr).addr[0]

/// Logging structure type
typedef struct {
  esl_lib_log_callback_t callback;
} esl_lib_log_t;

#define esl_lib_log(level, module, ...)      \
  do {                                       \
    if (esl_lib_log.callback != NULL) {      \
      char buffer[ESL_LIB_LOG_BUFFER_SIZE];  \
      snprintf(buffer,                       \
               ESL_LIB_LOG_BUFFER_SIZE,      \
               __VA_ARGS__);                 \
      esl_lib_log.callback(level,            \
                           module,           \
                           (char*)buffer,    \
                           (char*)__FILE__,  \
                           (int)__LINE__,    \
                           (char*)__func__); \
    }                                        \
  } while (0)

#define ESL_LIB_LOG_MODULE_CORE       "CORE"
#define ESL_LIB_LOG_MODULE_CONNECTION "CONN"
#define ESL_LIB_LOG_MODULE_PAWR       "PAwR"
#define ESL_LIB_LOG_MODULE_AP_CONTROL "APC"
#define ESL_LIB_LOG_MODULE_API        "API"
#define ESL_LIB_LOG_MODULE_IT         "IT"

#define esl_lib_log_debug(module, ...) esl_lib_log(ESL_LIB_LOG_LEVEL_DEBUG, module, __VA_ARGS__)
#define esl_lib_log_info(module, ...) esl_lib_log(ESL_LIB_LOG_LEVEL_INFO, module, __VA_ARGS__)
#define esl_lib_log_warning(module, ...) esl_lib_log(ESL_LIB_LOG_LEVEL_WARNING, module, __VA_ARGS__)
#define esl_lib_log_error(module, ...)  esl_lib_log(ESL_LIB_LOG_LEVEL_ERROR, module, __VA_ARGS__)
#define esl_lib_log_critical(module, ...) esl_lib_log(ESL_LIB_LOG_LEVEL_CRITICAL, module, __VA_ARGS__)

#define esl_lib_log_core_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_CORE, __VA_ARGS__)
#define esl_lib_log_core_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_CORE, __VA_ARGS__)
#define esl_lib_log_core_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_CORE, __VA_ARGS__)
#define esl_lib_log_core_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_CORE, __VA_ARGS__)
#define esl_lib_log_core_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_CORE, __VA_ARGS__)

#define esl_lib_log_connection_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_CONNECTION, __VA_ARGS__)
#define esl_lib_log_connection_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_CONNECTION, __VA_ARGS__)
#define esl_lib_log_connection_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_CONNECTION, __VA_ARGS__)
#define esl_lib_log_connection_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_CONNECTION, __VA_ARGS__)
#define esl_lib_log_connection_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_CONNECTION, __VA_ARGS__)

#define esl_lib_log_pawr_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_PAWR, __VA_ARGS__)
#define esl_lib_log_pawr_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_PAWR, __VA_ARGS__)
#define esl_lib_log_pawr_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_PAWR, __VA_ARGS__)
#define esl_lib_log_pawr_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_PAWR, __VA_ARGS__)
#define esl_lib_log_pawr_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_PAWR, __VA_ARGS__)

#define esl_lib_log_ap_control_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_AP_CONTROL, __VA_ARGS__)
#define esl_lib_log_ap_control_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_AP_CONTROL, __VA_ARGS__)
#define esl_lib_log_ap_control_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_AP_CONTROL, __VA_ARGS__)
#define esl_lib_log_ap_control_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_AP_CONTROL, __VA_ARGS__)
#define esl_lib_log_ap_control_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_AP_CONTROL, __VA_ARGS__)

#define esl_lib_log_api_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_API, __VA_ARGS__)
#define esl_lib_log_api_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_API, __VA_ARGS__)
#define esl_lib_log_api_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_API, __VA_ARGS__)
#define esl_lib_log_api_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_API, __VA_ARGS__)
#define esl_lib_log_api_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_API, __VA_ARGS__)

#define esl_lib_log_it_debug(...) esl_lib_log_debug(ESL_LIB_LOG_MODULE_IT, __VA_ARGS__)
#define esl_lib_log_it_info(...) esl_lib_log_info(ESL_LIB_LOG_MODULE_IT, __VA_ARGS__)
#define esl_lib_log_it_warning(...) esl_lib_log_warning(ESL_LIB_LOG_MODULE_IT, __VA_ARGS__)
#define esl_lib_log_it_error(...)  esl_lib_log_error(ESL_LIB_LOG_MODULE_IT, __VA_ARGS__)
#define esl_lib_log_it_critical(...) esl_lib_log_critical(ESL_LIB_LOG_MODULE_IT, __VA_ARGS__)

/// Logging storage variable
extern esl_lib_log_t esl_lib_log;

/**************************************************************************//**
 * Set callback function for logging.
 *
 * @param[in]  callback Logging callback function or NULL to disable logging.
 *
 * @return Status code.
 *****************************************************************************/
void esl_lib_log_set_callback(esl_lib_log_callback_t callback);

#ifdef __cplusplus
};
#endif

#endif // ESL_LIB_LOG_H
