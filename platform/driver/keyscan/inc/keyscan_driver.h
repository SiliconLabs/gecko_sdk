/***************************************************************************//**
 * @file
 * @brief KEYSCAN driver API definition.
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

/**************************************************************************//**
 *
 * @addtogroup keyscan_driver KEYSCAN - Keypad Scanner Driver
 * @brief Keyscan driver.
 *
 * @{
 *
 *****************************************************************************/

#ifndef KEYSCAN_DRIVER_H
#define KEYSCAN_DRIVER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "em_device.h"
#include "sl_slist.h"
#include "sl_status.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *********************************   ENUM   ************************************
 ******************************************************************************/

/// KEYSCAN status values.
typedef enum {
  SL_KEYSCAN_STATUS_KEYPRESS_VALID = 0,
  SL_KEYSCAN_STATUS_KEYPRESS_INVALID,
  SL_KEYSCAN_STATUS_KEYPRESS_RELEASED
} sl_keyscan_driver_status_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/// A Keyscan event handler
typedef void (*sl_keyscan_driver_process_keyscan_event)(uint8_t  *p_keyscan_matrix,
                                                        sl_keyscan_driver_status_t status);

/// An Event Handle
typedef struct {
  sl_slist_node_t node;                              ///< List node.
  sl_keyscan_driver_process_keyscan_event on_event;  ///< Function that must be called when the event occurs.
} sl_keyscan_driver_process_keyscan_event_handle_t;

/***************************************************************************//**
 * @brief
 *   Initializes the keyscan driver.
 *
 * @return
 *   0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_keyscan_driver_init(void);

/***************************************************************************//**
 * @brief
 *   Registers an event callback to be called on Keyscan event.
 *
 * @param[in]
 *   event_handle  Event handle to register
 *
 * @note
 *   An EFM_ASSERT is thrown if the handle is NULL.
 * @note
 *   Must be called before init function.
 ******************************************************************************/
void sl_keyscan_driver_subscribe_event(sl_keyscan_driver_process_keyscan_event_handle_t  *event_handle);

/***************************************************************************//**
 * @brief
 *   Unregisters an event callback to be called on Keyscan event.
 *
 * @param[in]
 *   event_handle  Event handle which must be unregistered (must have been
 *                      registered previously).
 *
 * @note
 *   An EFM_ASSERT is thrown if the handle is not found or is NULL.
 ******************************************************************************/
void sl_keyscan_driver_unsubscribe_event(sl_keyscan_driver_process_keyscan_event_handle_t  *event_handle);

/***************************************************************************//**
 * @brief
 *   Starts the keyscan scan.
 *
 * @return
 *   0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_keyscan_driver_start_scan(void);

/***************************************************************************//**
 * @brief
 *   Stops the keyscan scan.
 *
 * @return
 *   0 if successful. Error code otherwise.
 ******************************************************************************/
sl_status_t sl_keyscan_driver_stop_scan(void);

/** @} (end group keyscan_driver) */

/* *INDENT-OFF* */
/* THE REST OF THE FILE IS DOCUMENTATION ONLY! */
/// @addtogroup keyscan_driver
/// @{
///
///   @details
///
///
///   @n @section keyscan_intro Introduction
///
///   A low-energy keypad scanner (KEYSCAN) which can scan up to a 6x8 matrix of keyboard switches.
///   The KEYSCAN peripheral contains logic for debounce and settling time, allowing it to scan through
///   the switch matrix autonomously in EM0 and EM1, and interrupt the processor when a key press is detected.
///
///   @n @section keyscan_configuration Configuration Options
///
///   Some properties of the KEYSCAN driver are compile-time configurable.
///   These properties are stored in a file named keyscan_driver_config.h.
///   A template for this file, containing default values, is in the keyscan/config folder.
///   Currently the configuration options are as follows:
///
///   @li Number of columns in keyscan.
///   @li Number of rows in keyscan.
///   @li Duration of the scan period per column.
///   @li Duration of debounce period once a key press is detected.
///   @li Duration of the stable period after the debounce stage.
///   @li Enable or disable single-press functionality.
///
///   To configure KEYSCAN, provide a custom configuration file. This is an example keyscan_driver_config.h file:
///   @code{.c}
/// #ifndef KEYSCAN_DRIVER_CONFIG_H
/// #define KEYSCAN_DRIVER_CONFIG_H
///
/// // <o SL_KEYSCAN_DRIVER_COLUMN_NUMBER> Number of columns in keyscan <1-8>
/// // <i> Default: 1
/// #define SL_KEYSCAN_DRIVER_COLUMN_NUMBER 1
///
/// // <o SL_KEYSCAN_DRIVER_ROW_NUMBER> Number of rows in keyscan <3-6>
/// // <i> Default: 3
/// #define SL_KEYSCAN_DRIVER_ROW_NUMBER    3
///
/// // <o SL_KEYSCAN_DRIVER_SCAN_DELAY_MS> Scan Delay
/// //    <SL_KEYSCAN_DELAY_2MS=>     2ms
/// //    <SL_KEYSCAN_DELAY_4MS=>     4ms
/// //    <SL_KEYSCAN_DELAY_6MS=>     6ms
/// //    <SL_KEYSCAN_DELAY_8MS=>     8ms
/// //    <SL_KEYSCAN_DELAY_10MS=>    10ms
/// //    <SL_KEYSCAN_DELAY_12MS=>    12ms
/// //    <SL_KEYSCAN_DELAY_14MS=>    14ms
/// //    <SL_KEYSCAN_DELAY_16MS=>    16ms
/// //    <SL_KEYSCAN_DELAY_18MS=>    18ms
/// //    <SL_KEYSCAN_DELAY_20MS=>    20ms
/// //    <SL_KEYSCAN_DELAY_22MS=>    22ms
/// //    <SL_KEYSCAN_DELAY_24MS=>    24ms
/// //    <SL_KEYSCAN_DELAY_26MS=>    26ms
/// //    <SL_KEYSCAN_DELAY_28MS=>    28ms
/// //    <SL_KEYSCAN_DELAY_30MS=>    30ms
/// //    <SL_KEYSCAN_DELAY_32MS=>    32ms
/// // <i> Duration of the scan period per column
/// // <i> Default: SL_KEYSCAN_DELAY_2MS
/// #define SL_KEYSCAN_DRIVER_SCAN_DELAY_MS    SL_KEYSCAN_DELAY_2MS
///
/// // <o SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS> Debounce Delay
/// //    <SL_KEYSCAN_DELAY_2MS=>     2ms
/// //    <SL_KEYSCAN_DELAY_4MS=>     4ms
/// //    <SL_KEYSCAN_DELAY_6MS=>     6ms
/// //    <SL_KEYSCAN_DELAY_8MS=>     8ms
/// //    <SL_KEYSCAN_DELAY_10MS=>    10ms
/// //    <SL_KEYSCAN_DELAY_12MS=>    12ms
/// //    <SL_KEYSCAN_DELAY_14MS=>    14ms
/// //    <SL_KEYSCAN_DELAY_16MS=>    16ms
/// //    <SL_KEYSCAN_DELAY_18MS=>    18ms
/// //    <SL_KEYSCAN_DELAY_20MS=>    20ms
/// //    <SL_KEYSCAN_DELAY_22MS=>    22ms
/// //    <SL_KEYSCAN_DELAY_24MS=>    24ms
/// //    <SL_KEYSCAN_DELAY_26MS=>    26ms
/// //    <SL_KEYSCAN_DELAY_28MS=>    28ms
/// //    <SL_KEYSCAN_DELAY_30MS=>    30ms
/// //    <SL_KEYSCAN_DELAY_32MS=>    32ms
/// // <i> Duration of debounce period once a key press is detected.
/// // <i> Default: SL_KEYSCAN_DELAY_2MS
/// #define SL_KEYSCAN_DRIVER_DEBOUNCE_DELAY_MS    SL_KEYSCAN_DELAY_2MS
///
/// // <o SL_KEYSCAN_DRIVER_STABLE_DELAY_MS> Stable Delay
/// //    <SL_KEYSCAN_DELAY_2MS=>     2ms
/// //    <SL_KEYSCAN_DELAY_4MS=>     4ms
/// //    <SL_KEYSCAN_DELAY_6MS=>     6ms
/// //    <SL_KEYSCAN_DELAY_8MS=>     8ms
/// //    <SL_KEYSCAN_DELAY_10MS=>    10ms
/// //    <SL_KEYSCAN_DELAY_12MS=>    12ms
/// //    <SL_KEYSCAN_DELAY_14MS=>    14ms
/// //    <SL_KEYSCAN_DELAY_16MS=>    16ms
/// //    <SL_KEYSCAN_DELAY_18MS=>    18ms
/// //    <SL_KEYSCAN_DELAY_20MS=>    20ms
/// //    <SL_KEYSCAN_DELAY_22MS=>    22ms
/// //    <SL_KEYSCAN_DELAY_24MS=>    24ms
/// //    <SL_KEYSCAN_DELAY_26MS=>    26ms
/// //    <SL_KEYSCAN_DELAY_28MS=>    28ms
/// //    <SL_KEYSCAN_DELAY_30MS=>    30ms
/// //    <SL_KEYSCAN_DELAY_32MS=>    32ms
/// // <i> Duration of the stable period after the debounce stage.
/// // <i> Default: SL_KEYSCAN_DELAY_2MS
/// // #define SL_KEYSCAN_DRIVER_STABLE_DELAY_MS    SL_KEYSCAN_DELAY_2MS
/// //
/// // <q SL_KEYSCAN_DRIVER_SINGLEPRESS> keyscan single-press functionality
/// // <i> Enable or disable single-press functionality.
/// // <i> Default: 0
/// #define SL_KEYSCAN_DRIVER_SINGLEPRESS  0
///
/// #endif /* KEYSCAN_DRIVER_CONFIG_H */
///   @endcode
///
///   @n @section keyscan_usage Usage
///
///   The expected flow of execution is:
///
///   @li Initialize the driver.
///   @li Register an event callback to be called on Keyscan event.
///   @li Start the scan.
///   @li Interrupt-based event to read the keypresses.
///
///   Initialization is done by calling @ref sl_keyscan_driver_init(). It will
///   prepare the internal structure and GPIO configuration.
///
///   When initialization is done successfully, scanning can be started by calling
///   @ref sl_keyscan_driver_start_scan().
///
///
///   Here is a complete example:
///
///   @code{.c}
/// #include "keyscan_driver.h"
///
/// /*******************************************************************************
///  *********************   LOCAL FUNCTION PROTOTYPES   ***************************
///  ******************************************************************************/
///
/// static void on_event(uint8_t *p_keyscan_matrix, sl_keyscan_driver_status_t status);
/// static sl_keyscan_driver_process_keyscan_event_handle_t handle =
/// {
///   .on_event = on_event,
/// };
///
/// /*******************************************************************************
///  **************************   GLOBAL FUNCTIONS   *******************************
///  ******************************************************************************/
/// static void on_event(uint8_t *p_keyscan_matrix, sl_keyscan_driver_status_t status)
/// {
///   (void)p_keyscan_matrix;
///
///   switch (status) {
///     // Singlepress mode: key press detected.
///     case SL_KEYSCAN_STATUS_KEYPRESS_VALID:
///       break;
///     // Multipress mode: all keys are released.
///     case SL_KEYSCAN_STATUS_KEYPRESS_RELEASED:
///       break;
///     default:
///       EFM_ASSERT(false);
///       break;
///   }
/// }
///
/// int main( void )
/// {
///   // Initialize KEYSCAN.
///   sl_keyscan_driver_init();
///   // Set callback to be called when processing interrupt
///   sl_keyscan_driver_subscribe_event(&handle);
///   // Start the keypad scanner.
///   sl_keyscan_driver_start_scan();
///
///   return 0;
/// }
///   @endcode
///
/// @} (end addtogroup keyscan_driver)

#ifdef __cplusplus
}
#endif

#endif /* KEYSCAN_DRIVER_H */
