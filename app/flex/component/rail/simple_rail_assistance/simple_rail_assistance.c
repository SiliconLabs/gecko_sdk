/***************************************************************************//**
 * @file
 * @brief simple_rail_assistance.c
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

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "simple_rail_assistance.h"
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
/******************************************************************************
 * API to toggle the dedicated receive LED on board
 *****************************************************************************/
void toggle_receive_led()
{
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_toggle(&sl_led_led0);
#endif
}

/******************************************************************************
 * API to set 1 the dedicated receive LED on board
 *****************************************************************************/
void set_receive_led()
{
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_turn_on(&sl_led_led0);
#endif
}

/******************************************************************************
 * API to set 0 the dedicated receive LED on board
 *****************************************************************************/
void clear_receive_led()
{
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_turn_off(&sl_led_led0);
#endif
}

/******************************************************************************
 * API to toggle the dedicated send LED on board
 *****************************************************************************/
void toggle_send_led()
{
#if defined(SL_CATALOG_LED1_PRESENT)
  sl_led_toggle(&sl_led_led1);
#else
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_toggle(&sl_led_led0);
#endif
#endif
}

/******************************************************************************
 * API to set 0 the dedicated send LED on board
 *****************************************************************************/
void set_send_led()
{
#if defined(SL_CATALOG_LED1_PRESENT)
  sl_led_turn_on(&sl_led_led1);
#else
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_turn_on(&sl_led_led0);
#endif
#endif
}

/******************************************************************************
 * API to set 0 the dedicated send LED on board
 *****************************************************************************/
void clear_send_led()
{
#if defined(SL_CATALOG_LED1_PRESENT)
  sl_led_turn_off(&sl_led_led1);
#else
#if defined(SL_CATALOG_LED0_PRESENT)
  sl_led_turn_off(&sl_led_led0);
#endif
#endif
}

// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
