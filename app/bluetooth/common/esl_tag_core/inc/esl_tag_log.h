/***************************************************************************//**
 * @file
 * @brief ESL Tag core log interface definition.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef ESL_CORE_LOG_H
#define ESL_CORE_LOG_H
#include <stdint.h>
#include "sl_component_catalog.h"

/// ESL Tag Log Levels
#define ESL_LOG_LEVEL_CRITICAL      0
#define ESL_LOG_LEVEL_ERROR         1
#define ESL_LOG_LEVEL_WARNING       2
#define ESL_LOG_LEVEL_INFO          3
#define ESL_LOG_LEVEL_DEBUG         4

/// @typedef ESL Tag components
typedef enum {
  ESL_LOG_COMPONENT_CORE = 0,
  ESL_LOG_COMPONENT_APP,
  ESL_LOG_COMPONENT_DISPLAY,
  ESL_LOG_COMPONENT_RAM_IMAGE,
  ESL_LOG_COMPONENT_NVM_IMAGE,
  ESL_LOG_COMPONENT_LED,
  ESL_LOG_COMPONENT_OTS,
  ESL_LOG_COMPONENT_SENSOR,
  ESL_LOG_COMPONENT_CLI,
  ESL_LOG_FLAG_APPEND = 0x40,
  ESL_LOG_FLAG_NOHEADER = 0x80,
  ESL_LOG_FLAGS_MASK = (uint8_t)(~(ESL_LOG_FLAG_APPEND | ESL_LOG_FLAG_NOHEADER))
} esl_component_t;

#ifndef SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
#define sl_bt_esl_log(...)          ((void)0)
#define sl_bt_esl_log_hexdump(...)  ((void)0)
#else // !SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
/**************************************************************************//**
 * ESL Tag logging function.
 * @param[in] component The component that is logging.
 * @param[in] level Logging level.
 * @param[in] fmt Format string.
 * @param[in] ... Variadic argument list.
 *****************************************************************************/
void sli_bt_esl_logger(uint8_t component, uint8_t level, const char *fmt, ...);

/**************************************************************************//**
 * ESL Tag core hexdump function.
 * @param[in] component The component that is logging.
 * @param[in] level Logging level.
 * @param[in] p_data Data pointer.
 * @param[in] len Data lenght in bytes.
 *****************************************************************************/
void sli_bt_esl_log_hex_dump(uint8_t component,
                             uint8_t level,
                             void    *p_data,
                             uint8_t len);

#define sl_bt_esl_log(...) \
  sli_bt_esl_logger(__VA_ARGS__)
#define sl_bt_esl_log_hexdump(...) \
  sli_bt_esl_log_hex_dump(__VA_ARGS__)
#endif // !SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT

#if defined(NDEBUG) && !defined(SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT)
#define sl_bt_esl_assert(e)         ((void)0)
#else // NDEBUG && !SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT
/**************************************************************************//**
 * ESL Tag core assert function.
 * @param[in] func Name of the asserting function.
 * @param[in] file The file in which the assert happened.
 * @param[in] line The line where the assert happened.
 * @param[in] expr The expression that caused the assert.
 *****************************************************************************/
void sli_bt_esl_assert_func(const char *func,
                            const char *file,
                            const char *expr,
                            int         line);

#define sl_bt_esl_assert(e) \
  ((e) ? ((void)0) : (sli_bt_esl_assert_func(__func__, __FILE__, #e, __LINE__)))
#endif // NDEBUG && !SL_CATALOG_ESL_TAG_CLI_TEST_HARNESS_PRESENT

#endif // ESL_CORE_LOG_H
