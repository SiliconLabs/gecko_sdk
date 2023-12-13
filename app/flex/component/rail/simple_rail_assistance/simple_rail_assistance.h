/***************************************************************************//**
 * @file
 * @brief simple_rail_assistance.h
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
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
#ifndef SIMPLE_RAIL_ASSISTANCE_H
#define SIMPLE_RAIL_ASSISTANCE_H

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_component_catalog.h"
#if defined(SL_CATALOG_APP_ASSERT_PRESENT)
#include "app_assert.h"
#else
#if defined(SL_CATALOG_PRINTF_PRESENT)
#include "printf.h"
#endif
#endif
#if defined(SL_CATALOG_APP_LOG_PRESENT)
#include "app_log.h"
#else
#if defined(SL_CATALOG_PRINTF_PRESENT)
#include "printf.h"
#endif
#endif

#if defined(SL_CATALOG_SIMPLE_LED_PRESENT)
#include "sl_simple_led_instances.h"
#endif
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------
#if !defined(SL_CATALOG_APP_LOG_PRESENT)
#if defined(SL_CATALOG_PRINTF_PRESENT)
#define app_log_info(...)    printf(__VA_ARGS__)
#define app_log_warning(...) printf(__VA_ARGS__)
#define app_log_error(...)   printf(__VA_ARGS__)
#else
#define app_log_info(...)
#define app_log_warning(...)
#define app_log_error(...)
#endif
#endif

#if !defined(SL_CATALOG_APP_ASSERT_PRESENT)
#if defined(SL_CATALOG_PRINTF_PRESENT)
#define app_assert(expr, ...) \
  do {                        \
    if (!(expr)) {            \
      printf(__VA_ARGS__);    \
      while (1) ;             \
    }                         \
  } while (0)
#else
#define app_assert(expr, ...) \
  do {                        \
    if (!(expr)) {            \
      while (1) ;             \
    }                         \
  } while (0)
#endif
#endif
// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------
/******************************************************************************
 * API to toggle the dedicated receive LED on board
 *****************************************************************************/
void toggle_receive_led();

/******************************************************************************
 * API to toggle the dedicated send LED on board
 *****************************************************************************/
void toggle_send_led();

/******************************************************************************
 * API to set 0 the dedicated receive LED on board
 *****************************************************************************/
void clear_receive_led();

/******************************************************************************
 * API to set 1 the dedicated receive LED on board
 *****************************************************************************/
void set_receive_led();

/******************************************************************************
 * API to set 1 the dedicated send LED on board
 *****************************************************************************/
void set_send_led();

/******************************************************************************
 * API to set 0 the dedicated send LED on board
 *****************************************************************************/
void clear_send_led();

#endif  // SIMPLE_RAIL_ASSISTANCE_H
