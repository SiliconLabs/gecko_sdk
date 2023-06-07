/***************************************************************************//**
 * @file
 * @brief ZigBee specific debug print macros and API declarations.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_ZIGBEE_DEBUG_PRINT_H
#define SL_ZIGBEE_DEBUG_PRINT_H

#include <stdbool.h>
#include <stdint.h>
#include "sl_status.h"

#ifdef SL_COMPONENT_CATALOG_PRESENT
 #include "sl_component_catalog.h"
 #ifdef SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
  #include "sl_zigbee_debug_print_config.h"
 #endif // SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT
#endif // SL_COMPONENT_CATALOG_PRESENT

/**
 * @defgroup debug-print Debug Print
 * @ingroup component
 * @brief API and Callbacks for the Debug Print Component
 */

/**
 * @addtogroup debug-print
 * @{
 */

//------------------------------------------------------------------------------
// Internal APIs and defines

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void sli_zigbee_debug_print(uint32_t group_type, bool new_line, const char* format, ...);
#endif

#if defined(EMBER_TEST) && !defined(ZIGBEE_PRO_COMPLIANCE_ON_HOST)
#include <stdint.h>
#include "tool/simulator/child/up_misc/printf-sim.h"
#define local_printf printf_sim
#define local_vprintf vprintf_sim
#else
#ifdef EZSP_HOST
#include <stdio.h>
#else // EZSP_HOST
#include "printf.h"
#endif // EZSP_HOST
#define local_printf printf
#define local_vprintf vprintf
#endif

//------------------------------------------------------------------------------
// Public types and APIs

enum sl_zigbee_debug_print_type {
  SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK             = 0x01,
  SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE              = 0x02,
  SL_ZIGBEE_DEBUG_PRINT_TYPE_APP               = 0x04,
  SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL               = 0x08,
  SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG   = 0x10,
};

/**
 * @name API
 * @{
 */
/** Enable groups in debug prints.
 *
 * @param group_type Ver.: always
 * @param enabled value Ver.: always
 *
 * @return sl_status_t status code
 *
 */
sl_status_t sl_zigbee_debug_print_enable_group(uint32_t group_type, bool enable);

void sli_zigbee_debug_print_buffer(uint32_t group_type,
                                   const uint8_t *buffer,
                                   uint16_t buffer_length,
                                   bool with_space,
                                   const char* format_string);

/** @} */ // end of name APIs
#if (SL_ZIGBEE_DEBUG_STACK_GROUP_ENABLED == 1)
#define sl_zigbee_stack_debug_print(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK), false, __VA_ARGS__)
#define sl_zigbee_stack_debug_println(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK), true, __VA_ARGS__)
#define sl_zigbee_stack_debug_print_buffer(buffer, length, with_space) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK), (buffer), (length), (with_space), "%02X")
#define sl_zigbee_stack_debug_print_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK), buffer + 1, emberAfStringLength(buffer), false, "%c")
#define sl_zigbee_stack_debug_print_long_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_STACK), buffer + 2, emberAfLongStringLength(buffer), false, "%c")
#else
#define sl_zigbee_stack_debug_print(...)
#define sl_zigbee_stack_debug_println(...)
#define sl_zigbee_stack_debug_print_buffer(...)
#define sl_zigbee_stack_debug_print_string(...)
#define sl_zigbee_stack_debug_print_long_string(...)
#endif

#if (SL_ZIGBEE_DEBUG_CORE_GROUP_ENABLED == 1)
#define sl_zigbee_core_debug_print(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE), false, __VA_ARGS__)
#define sl_zigbee_core_debug_println(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE), true, __VA_ARGS__)
#define sl_zigbee_core_debug_print_buffer(buffer, length, with_space) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE), (buffer), (length), (with_space), "%02X")
#define sl_zigbee_core_debug_print_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE), buffer + 1, emberAfStringLength(buffer), false, "%c")
#define sl_zigbee_core_debug_print_long_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_CORE), buffer + 2, emberAfLongStringLength(buffer), false, "%c")
#else
#define sl_zigbee_core_debug_print(...)
#define sl_zigbee_core_debug_println(...)
#define sl_zigbee_core_debug_print_buffer(...)
#define sl_zigbee_core_debug_print_string(...)
#define sl_zigbee_core_debug_print_long_string(...)
#endif

#if (SL_ZIGBEE_DEBUG_APP_GROUP_ENABLED == 1)
#define sl_zigbee_app_debug_print(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_APP), false, __VA_ARGS__)
#define sl_zigbee_app_debug_println(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_APP), true, __VA_ARGS__)
#define sl_zigbee_app_debug_print_buffer(buffer, length, with_space) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_APP), (buffer), (length), (with_space), "%02X")
#define sl_zigbee_app_debug_print_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_APP), buffer + 1, emberAfStringLength(buffer), false, "%c")
#define sl_zigbee_app_debug_print_long_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_APP), buffer + 2, emberAfLongStringLength(buffer), false, "%c")
#else
#define sl_zigbee_app_debug_print(...)
#define sl_zigbee_app_debug_println(...)
#define sl_zigbee_app_debug_print_buffer(...)
#define sl_zigbee_app_debug_print_string(...)
#define sl_zigbee_app_debug_print_long_string(...)
#endif

#if (SL_ZIGBEE_DEBUG_ZCL_GROUP_ENABLED == 1)
#define sl_zigbee_zcl_debug_print(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL), false, __VA_ARGS__)
#define sl_zigbee_zcl_debug_println(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL), true, __VA_ARGS__)
#define sl_zigbee_zcl_debug_print_buffer(buffer, length, with_space) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL), (buffer), (length), (with_space), "%02X")
#define sl_zigbee_zcl_debug_print_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL), buffer + 1, emberAfStringLength(buffer), false, "%c")
#define sl_zigbee_zcl_debug_print_long_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_ZCL), buffer + 2, emberAfLongStringLength(buffer), false, "%c")
#else
#define sl_zigbee_zcl_debug_print(...)
#define sl_zigbee_zcl_debug_println(...)
#define sl_zigbee_zcl_debug_print_buffer(...)
#define sl_zigbee_zcl_debug_print_string(...)
#define sl_zigbee_zcl_debug_print_long_string(...)
#endif

#if (SL_ZIGBEE_DEBUG_PRINTS_ZCL_LEGACY_AF_DEBUG_ENABLED == 1)
#define sl_zigbee_legacy_af_debug_print(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG), false, __VA_ARGS__)
#define sl_zigbee_legacy_af_debug_println(...) sli_zigbee_debug_print(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG), true, __VA_ARGS__)
#define sl_zigbee_legacy_af_debug_print_buffer(buffer, length, with_space) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG), (buffer), (length), (with_space), "%02X")
#define sl_zigbee_legacy_af_debug_print_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG), buffer + 1, emberAfStringLength(buffer), false, "%c")
#define sl_zigbee_legacy_af_debug_print_long_string(buffer) sli_zigbee_debug_print_buffer(((uint32_t)SL_ZIGBEE_DEBUG_PRINT_TYPE_LEGACY_AF_DEBUG), buffer + 2, emberAfLongStringLength(buffer), false, "%c")
#else
#define sl_zigbee_legacy_af_debug_print(...)
#define sl_zigbee_legacy_af_debug_println(...)
#define sl_zigbee_legacy_af_debug_print_buffer(...)
#define sl_zigbee_legacy_af_debug_print_string(...)
#define sl_zigbee_legacy_af_debug_print_long_string(...)
#endif

/** @} */ // end of debug-print

#endif // SL_ZIGBEE_DEBUG_PRINT_H
