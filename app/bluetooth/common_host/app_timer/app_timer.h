/***************************************************************************//**
 * @file
 * @brief Timer common header
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

#ifndef APP_TIMER_H
#define APP_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include "sl_status.h"

#if defined(__APPLE__)
#include "app_timer_mac.h"
#elif defined(POSIX) && POSIX == 1
#include "app_timer_posix.h"
#else
#include "app_timer_win.h"
#endif // #if defined(POSIX) && POSIX == 1

/**************************************************************************//**
 * @addtogroup timer
 * @{
 *****************************************************************************/

/// Type definitions
typedef struct app_timer app_timer_t;

/***************************************************************************//**
 * Expected prototype of the user's callback function which is called when a
 * timer expires.
 *
 * @param timer Pointer to the timer handle.
 * @param data An extra parameter for the user application.
 ******************************************************************************/
typedef void (*app_timer_callback_t)(app_timer_t *timer, void *data);

/// Structure to populate timers
struct app_timer {
  app_timer_handle_t app_timer_handle;  // Platform specific parameters
  app_timer_callback_t callback;        // Pointer to user defined callback
  void *callback_data;                  // Pointer to callback data
  uint32_t timeout;                     // Time elapsed before timer trigger
  bool periodic;                        // Periodicity indication
  app_timer_t *next;                    // Pointer to next timer if exist
};

// -----------------------------------------------------------------------------
// Function declarations

/***************************************************************************//**
 * Timer init
 *
 * Platform specific initalization function which prepares necessary signals or
 * handlers to enable timer operations.
 ******************************************************************************/
void app_timer_init(void);

/***************************************************************************//**
 * Main function
 *
 * Main function for timer components. Poll timers and call their respective
 * callback functions if they expire. For POSIX environment, remove one-shot
 * timers from linked list if expired.
 ******************************************************************************/
void sli_app_timer_step(void);

/***************************************************************************//**
 * Start a timer
 *
 * @param[in] timer Pointer to the timer
 * @param[in] timeout_ms Timer timeout in miliseconds
 * @param[in] callback Callback function that is called when timeout expires
 * @param[in] callback_data Pointer to user data that will be passed to callback
 * @param[in] is_periodic Indicate periodicity
 *
 * @returns Status of the operation
 *
 * Start a timer with the provided parameters, restart if the timer had been
 * already started.
 ******************************************************************************/
sl_status_t app_timer_start(app_timer_t *timer,
                            uint32_t timeout_ms,
                            app_timer_callback_t callback,
                            void *callback_data,
                            bool is_periodic);

/***************************************************************************//**
 * Stop timer
 *
 * @param[in] timer Pointer to the timer to be stopped
 *
 * @return Status of the operation
 *
 * Stop the already running timer referenced by the parameters
 ******************************************************************************/
sl_status_t app_timer_stop(app_timer_t *timer);

/** @} (end addtogroup timer) */
#endif // APP_TIMER_H
