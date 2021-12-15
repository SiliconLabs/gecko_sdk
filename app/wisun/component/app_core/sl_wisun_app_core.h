/***************************************************************************//**
 * @file
 * @brief Wi-SUN Application Core Component
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

#ifndef __SL_WISUN_APP_CORE_H__
#define __SL_WISUN_APP_CORE_H__

#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @addtogroup SL_WISUN_APP_CORE_API Application Core
 * @{
 *****************************************************************************/

#include "sl_wisun_util.h"
#include "sl_wisun_trace_util.h"
#include "sl_wisun_app_core_util.h"

// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @addtogroup SL_WISUN_APP_CORE_API_TYPES Application Core API type definitions
 * @ingroup SL_WISUN_APP_CORE_API
 * @{
 *****************************************************************************/

/// Error flag bits enum type definition
typedef enum app_core_error_state_flag{
  /// Setting Error Flag bit
  SETTING_ERROR_FLAG_BIT = 0,
  /// Connection Failed Error Flag bit
  CONNECTION_FAILED_ERROR_FLAG_BIT,
  /// Network Size Error Flag bit
  SET_NETWORK_SIZE_ERROR_FLAG_BIT,
  /// TX Power Error Flag bit
  SET_TX_POWER_ERROR_FLAG_BIT,
  /// Trusted Certificate Error Flag bit
  SET_TRUSTED_CERTIFICATE_ERROR_FLAG_BIT,
  /// Device Certificate Error Flag bit
  SET_DEVICE_CERTIFICATE_ERROR_FLAG_BIT,
  /// Device Private Key Error Flag bit
  SET_DEVICE_PRIVATE_KEY_ERROR_FLAG_BIT,
} app_core_error_state_flag_t;

/// Current address storage structure definition
typedef struct current_addr {
  /// Link local address
  sl_wisun_ip_address_t link_local;
  /// Global address
  sl_wisun_ip_address_t global;
  /// Border Router address
  sl_wisun_ip_address_t border_router;
  /// Primary Parent address
  sl_wisun_ip_address_t primary_parent;
  /// Secondary Parent address
  sl_wisun_ip_address_t secondary_parent;
} current_addr_t;

/** @} (end SL_WISUN_APP_CORE_API_TYPES) */

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Public Function Declarations
// -----------------------------------------------------------------------------

/**************************************************************************//**
 * @brief Initialize Wi-SUN application core.
 * @details Initializing mutex, socket handler and set Wi-SUN settings.
 *****************************************************************************/
void app_wisun_core_init(void);

/**************************************************************************//**
 * @brief Get application core error.
 * @details The function retrieves the application core error status based on
 *          flag
 * @param[in] flag is the indicator of the error
 *****************************************************************************/
bool app_wisun_core_get_error(app_core_error_state_flag_t flag);

/**************************************************************************//**
 * @brief Connect to the Wi-SUN network.
 * @details Network initialization and connection.
 *          The function initializes the network with parameters
 *          (Network name, TX Power, Network size, etc.)
 *          by the stored settings in NVM
 *          if the settings component is added to the project,
 *          otherwise with the default settings.
 *****************************************************************************/
void app_wisun_network_connect(void);

/**************************************************************************//**
 * @brief Get current addresses .
 * @details Copy cached addresses into destination.
 * @param[out] dest_addresses Destination
 *****************************************************************************/
void app_wisun_get_current_addresses(current_addr_t * const dest_addresses);

/** @}*/

#ifdef __cplusplus
}
#endif
#endif
