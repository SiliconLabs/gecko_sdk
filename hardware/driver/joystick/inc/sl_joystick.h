/***************************************************************************//**
 * @file
 * @brief Analog Joystick Driver
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

#ifndef SL_JOYSTICK_H
#define SL_JOYSTICK_H

#include "sl_common.h"
#include "sl_status.h"
#include "em_gpio.h"
#include "sl_enum.h"
#include "sl_joystick_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************//**
 * @addtogroup joystick Joystick API
 * @brief Joystick API
 * @{
 ******************************************************************************/

/*******************************************************************************
 ******************************   DEFINES   ************************************
 ******************************************************************************/

#ifndef ENABLE_SECONDARY_DIRECTIONS
// By default, return the four cardinal directions only (N, S, E, W)
#define ENABLE_SECONDARY_DIRECTIONS 0
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN
#if (ENABLE_SECONDARY_DIRECTIONS == 0)
#define JOYSTICK_MV_ERROR      JOYSTICK_MV_ERR_CARDINAL_ONLY           // tolerance in mV for cardinal
#elif (ENABLE_SECONDARY_DIRECTIONS == 1)
#define JOYSTICK_MV_ERROR      JOYSTICK_MV_ERR_CARDINAL_AND_SECONDARY  // tolerance in mV for cardinal and secondary
#endif
/// @endcond

/// MACROS to Set CLK_SRC_ADC_FREQ and CLK_ADC_FREQ
#define CLK_SRC_ADC_FREQ          5000000 ///< A MACRO for clock source ADC frequency, clock source ADC frequency is 5MHZ.
#define CLK_ADC_FREQ              1000000 ///< A MACRO for clock ADC, clock ADC frequency is 1 MHz.

/// Default Joystick handle structure
#define JOYSTICK_HANDLE_DEFAULT                                                 \
  {                                                                             \
    SL_JOYSTICK_PORT,                 /*Joystick gpio port*/                    \
    SL_JOYSTICK_PIN,                  /*Joystick gpio pin*/                     \
    SL_JOYSTICK_DISABLED,             /*Joystick signal acquisition not start*/ \
  } ///< Default Joystick handle structure

/*******************************************************************************
 *****************************   DATA TYPES   *********************************
 ******************************************************************************/

/// @name Direction Enums
/// @anchor dir_enums
/// @{
/// @enum sl_joystick_position_t
/// @brief enum for finding the position of Joystick.
SL_ENUM(sl_joystick_position_t) {
  JOYSTICK_NONE = 0u,    ///< Not pressed
  JOYSTICK_C,            ///< Center
  JOYSTICK_N,            ///< North
  JOYSTICK_E,            ///< East
  JOYSTICK_S,            ///< South
  JOYSTICK_W,            ///< West
#if (ENABLE_SECONDARY_DIRECTIONS == 1)
  JOYSTICK_NE,           ///< Northeast
  JOYSTICK_NW,           ///< Northwest
  JOYSTICK_SE,           ///< Southeast
  JOYSTICK_SW,           ///< Southwest
#endif
};

/// @}

/// Joystick state (ENABLE / DISABLE) enum.
SL_ENUM(sl_joystick_state_t) {
  SL_JOYSTICK_DISABLED = 0U,        ///< Analog Joystick data acquisition is disabled
  SL_JOYSTICK_ENABLED  = 1U,        ///< Analog Joystick data acquisition is enabled
};

/// Joystick handle
typedef struct {
  GPIO_Port_TypeDef          port;           ///< Joystick port
  uint8_t                    pin;            ///< Joystick pin
  sl_joystick_state_t        state;          ///< State of joystick
} sl_joystick;

/// sl_joystick_t is the alias name of sl_joystick.
typedef sl_joystick sl_joystick_t;

/*******************************************************************************
 *****************************   PROTOTYPES   **********************************
 ******************************************************************************/

/***************************************************************************//**
 * Joystick init. This function should be called before calling any other
 * Joystick function. Sets up the ADC.
 *
 * @param[in] joystick_handle            Pointer to joystick handle
 *
 * @return    Status Code:
 *              - SL_STATUS_OK                      Success
 *              - SL_STATUS_ALLOCATION_FAILED       Bus Allocation error
 ******************************************************************************/
sl_status_t sl_joystick_init(sl_joystick_t *joystick_handle);

/***************************************************************************//**
 * Get joystick position.
 *
 * @param[in] joystick_handle             Pointer to joystick handle
 *
 * @param[out] pos                        Pointer to output variable of type sl_joystick_position_t
 *
 * @return    Status Code:
 *              - SL_STATUS_OK            Success
 *              - SL_STATUS_NOT_READY     Joystick acquition not started error
 *
 ******************************************************************************/
sl_status_t sl_joystick_get_position(sl_joystick_t *joystick_handle, sl_joystick_position_t* pos);

/***************************************************************************//**
 * Start Analog Joystick data acquisition.
 *
 * @param[in] joystick_handle            Pointer to joystick handle
 *
 ******************************************************************************/
void sl_joystick_start(sl_joystick_t *joystick_handle);

/***************************************************************************//**
 * Stop Analog Joystick data acquisition.
 *
 * @param[in] joystick_handle            Pointer to joystick handle
 *
 ******************************************************************************/
void sl_joystick_stop(sl_joystick_t *joystick_handle);

/** @} (end addtogroup joystick) */

// ******** THE REST OF THE FILE IS DOCUMENTATION ONLY !***********************
/// @addtogroup joystick Joystick API
/// @{
///
///   @details
///
///   @li @ref joystickdrv_intro
///   @li @ref joystickdrv_config
///   @li @ref joystickdrv_usage
///
///   @n @section joystickdrv_intro Introduction
///
///   The joystick driver is a platform board level software module that provides the
///   functionality to initialize and read joystick position through the joystick
///   hardware present on the Wireless Pro Kit (BRD4002A)
///
///   @n @section joystickdrv_config Configuration
///
///   Joystick driver allows configuring the rate of signal acquisition. This can be
///   configured from the joystick component, available options are:
///   - 100 samples/second
///   - 1000 samples/second
///   - 5000 samples/second
///   - 10000 samples/second
///   - 25000 samples/second
///
///   Joystick driver also allows configuring the voltage values which correspond
///   to a particular joystick position
///
///   @n @section joystickdrv_usage Usage
///
///   Once the joystick handle of type sl_joystick_t is defined, joystick functions
///   can be called being passed the defined handle. The functions include the following:
///
///
///   @ref sl_joystick_init must be called followed by sl_joystick_start before
///   attempting to read the position of the joystick.
///
///   The  @ref sl_joystick_get_position is used to update the position,
///   and needs to be called from a tick function or similar by the user.
///
///   Basic example code to show usage of Joystick driver
///   @code{.c}
///
///#include "sl_joystick.h"
///
///sl_joystick_t sl_joystick_handle = JOYSTICK_HANDLE_DEFAULT
///
///int main( void )
///{
///   // Initialize driver
///   sl_joystick_init(&sl_joystick_handle);
///
///   // Start acquiring joystick signal
///   sl_joystick_start(&sl_joystick_handle);
///
///   sl_joystick_position_t pos;
///
///   while (1) {
///
///   sl_joystick_get_position(&sl_joystick_handle, &pos);
///
///   ...
///
///   }
///}
///
///   @endcode
///
/// @} end group joystick ********************************************************/

#ifdef __cplusplus
}
#endif

#endif // SL_JOYSTICK_H
